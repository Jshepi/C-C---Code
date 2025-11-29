#include <windows.h>
#include <gdiplus.h>
#pragma comment(lib, "gdiplus.lib")

using namespace Gdiplus;

static wchar_t imagePath[260] = L""; // 存储图片路径
static ULONG_PTR gdiplusToken;
static Image* g_pImage = NULL;
static int g_displayWidth = 0;
static int g_displayHeight = 0;
static int g_displayX = 0;
static int g_displayY = 0;

// 文件选择对话框回调函数
UINT_PTR CALLBACK OFNHookProc(HWND hdlg, UINT uiMsg, WPARAM wParam, LPARAM lParam) {
    return 0;
}

// 打开文件对话框选择图片
bool OpenFileDialog(HWND hwnd) {
    wchar_t buffer[260] = {0};
    wcscpy_s(buffer, 260, imagePath);
    
    OPENFILENAMEW ofn = {0};
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = hwnd;
    ofn.lpstrFilter = L"Image Files\0*.bmp;*.jpg;*.jpeg;*.png\0All Files\0*.*\0\0";
    ofn.lpstrFile = buffer;
    ofn.nMaxFile = sizeof(buffer)/sizeof(wchar_t);
    ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
    ofn.lpstrDefExt = L"bmp";
    
    if (GetOpenFileNameW(&ofn)) {
        wcscpy_s(imagePath, 260, buffer);
        return true;
    }
    return false;
}

// 计算图片显示参数
void CalculateDisplaySize(HWND h) {
    if (!g_pImage || g_pImage->GetLastStatus() != Ok) {
        return;
    }
    
    RECT rc;
    GetClientRect(h, &rc);
    int clientWidth = rc.right - rc.left;
    int clientHeight = rc.bottom - rc.top;
    
    UINT imageWidth = g_pImage->GetWidth();
    UINT imageHeight = g_pImage->GetHeight();
    
    // 计算缩放后的尺寸（保持宽高比，适应窗口）
    double scaleX = (double)clientWidth / imageWidth;
    double scaleY = (double)clientHeight / imageHeight;
    double scale = (scaleX < scaleY) ? scaleX : scaleY;
    
    g_displayWidth = (int)(imageWidth * scale);
    g_displayHeight = (int)(imageHeight * scale);
    
    // 计算居中位置
    g_displayX = (clientWidth - g_displayWidth) / 2;
    g_displayY = (clientHeight - g_displayHeight) / 2;
}

// 加载图片
void LoadImage(HWND h) {
    if (g_pImage) {
        delete g_pImage;
        g_pImage = NULL;
    }
    
    if (imagePath[0] == L'\0') {
        return;
    }
    
    g_pImage = Image::FromFile(imagePath);
    if (g_pImage && g_pImage->GetLastStatus() == Ok) {
        CalculateDisplaySize(h);
    } else {
        if (g_pImage) delete g_pImage;
        g_pImage = NULL;
    }
}

// 窗口消息处理函数
LRESULT CALLBACK WndProc(HWND h, UINT m, WPARAM w, LPARAM l) {
    switch(m) {
        case WM_CREATE:
            // 窗口创建时让用户选择图片
            if (OpenFileDialog(h)) {
                LoadImage(h);
                InvalidateRect(h, NULL, FALSE);
            }
            break;
            
        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(h, &ps);
            Graphics graphics(hdc);
            graphics.SetCompositingMode(CompositingModeSourceCopy);
            graphics.SetCompositingQuality(CompositingQualityHighSpeed);
            
            RECT rc;
            GetClientRect(h, &rc);
            int clientWidth = rc.right - rc.left;
            int clientHeight = rc.bottom - rc.top;
            
            // 清除背景
            SolidBrush whiteBrush(Color(255, 255, 255));
            graphics.FillRectangle(&whiteBrush, 0, 0, clientWidth, clientHeight);
            
            if (g_pImage && g_pImage->GetLastStatus() == Ok && g_displayWidth > 0 && g_displayHeight > 0) {
                graphics.SetSmoothingMode(SmoothingModeAntiAlias);
                graphics.SetInterpolationMode(InterpolationModeLowQuality);
                
                // 绘制图片
                graphics.DrawImage(g_pImage, g_displayX, g_displayY, g_displayWidth, g_displayHeight);
            } else {
                // 显示提示文字
                SolidBrush brush(Color(0, 0, 0));
                FontFamily fontFamily(L"Arial");
                Font font(&fontFamily, 16, FontStyleRegular, UnitPixel);
                
                StringFormat stringFormat;
                stringFormat.SetAlignment(StringAlignmentCenter);
                stringFormat.SetLineAlignment(StringAlignmentCenter);
                
                RectF rectF((REAL)rc.left, (REAL)rc.top, (REAL)(rc.right - rc.left), (REAL)(rc.bottom - rc.top));
                
                graphics.DrawString(L"未能加载图片，请点击重新选择有效的图片文件", -1, &font, rectF, &stringFormat, &brush);
            }
            
            EndPaint(h, &ps);
            return 0;
        }
        
        case WM_LBUTTONDOWN:
            // 鼠标左键点击时重新选择图片
            if (OpenFileDialog(h)) {
                LoadImage(h);
                InvalidateRect(h, NULL, FALSE);
            }
            break;
        
        case WM_SIZE:
            // 窗口大小改变时重新计算显示参数
            CalculateDisplaySize(h);
            InvalidateRect(h, NULL, FALSE);
            break;
            
        case WM_DESTROY:
            if (g_pImage) {
                delete g_pImage;
                g_pImage = NULL;
            }
            PostQuitMessage(0);
            return 0;
    }
    
    return DefWindowProcW(h, m, w, l);
}

int WINAPI WinMain(HINSTANCE i, HINSTANCE, LPSTR, int s) {
    // 初始化 GDI+
    GdiplusStartupInput gdiplusStartupInput;
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
    
    WNDCLASSW c = {0};
    c.lpfnWndProc = WndProc;
    c.hInstance = i;
    c.lpszClassName = L"ImageWindow";
    c.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    c.hCursor = LoadCursor(NULL, IDC_ARROW);
    
    RegisterClassW(&c);
    HWND h = CreateWindowExW(0, L"ImageWindow", L"图片查看器 - 点击窗口选择图片", 
                            WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 
                            800, 600, 0, 0, i, 0);
                            
    ShowWindow(h, s);
    UpdateWindow(h);
    
    MSG m;
    while (GetMessage(&m, 0, 0, 0)) {
        TranslateMessage(&m);
        DispatchMessage(&m);
    }
    
    // 关闭 GDI+
    GdiplusShutdown(gdiplusToken);
    
    return m.wParam;
}
