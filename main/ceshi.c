#include <stdio.h>
#include <time.h>

int main() {
    int birthYear, currentYear, age;
    
    // 获取当前年份
    time_t t = time(NULL);
    struct tm *current_time = localtime(&t);
    currentYear = current_time->tm_year + 1900;
    
    // 输入出生年份
    printf("%d\n", currentYear);
    printf("请输入您的出生年份: ");
    scanf("%d", &birthYear);
    
    // 计算年龄
    age = currentYear - birthYear;
    
    // 输出结果
    printf("您的年龄是: %d 岁\n", age);
    
    return 0;
}