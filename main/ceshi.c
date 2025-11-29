#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int main() {
    int hours, minutes, seconds;
    int total_seconds;
    
    printf("倒计时程序\n");
    printf("请输入小时数: ");
    scanf("%d", &hours);
    printf("请输入分钟数: ");
    scanf("%d", &minutes);
    printf("请输入秒数: ");
    scanf("%d", &seconds);
    
    // 计算总秒数
    total_seconds = hours * 3600 + minutes * 60 + seconds;
    
    if (total_seconds <= 0) {
        printf("输入的时间必须大于0!\n");
        return 1;
    }
    
    printf("\n开始倒计时...\n");
    
    while (total_seconds > 0) {
        hours = total_seconds / 3600;
        minutes = (total_seconds % 3600) / 60;
        seconds = total_seconds % 60;
        
        printf("\r剩余时间: %02d:%02d:%02d", hours, minutes, seconds);
        fflush(stdout); // 强制刷新输出缓冲区
        
        Sleep(1000); // Windows下延时1秒
        total_seconds--;
    }
    
    printf("\r剩余时间: %02d:%02d:%02d\n", 0, 0, 0);
    printf("倒计时结束!\a"); // 不再发出声音
    Beep(3500, 800);// 发出提示音
    
    return 0;
}