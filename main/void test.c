#include <stdio.h>
#include <windows.h>
int main(void)
{   
    int i ;
    float x, y;
    printf("请输入响铃次数：");
    scanf("%d",&i);
    for(y = 1.3f; y > -1.1f; y -= 0.08f) {
        for(x = -1.8f; x < 1.8f; x += 0.05f) {
            // 修改爱心方程参数，使其更宽更饱满
            float a = x*x + y*y - 1;
            if(a*a*a - (x*x)*(y*y*y) <= 0.0f) {
                printf("* ");
            } else {
                printf("  ");
            }
        }
        printf("\n");
    }
    Sleep(800);//延时0.8秒
    while(i)
    {   Beep(3500, 200);
        Beep(3500, 200);
        Sleep(800);//延时0.8秒
        i--;
    }
    return 0;
}