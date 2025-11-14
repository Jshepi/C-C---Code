#include <stdio.h>
void test(int &x)//使用&表示传参为引用，而不是值
{
	x=1024;
	printf("test函数内部 =x=%d\n",x);
}
int main()
{	int x = 1;
	printf("before x=%d\n",x);
 	test(x);
    printf("after x=%d\n",x);
}