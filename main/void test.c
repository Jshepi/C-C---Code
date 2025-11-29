#include <windows.h>
int main(void)
{   
    int i = 5;
    while(i)
    {   Beep(3500, 200);
        Beep(3500, 200);
        Sleep(800);//延时0.8秒
        i--;
    }
}