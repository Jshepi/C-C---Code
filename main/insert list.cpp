#include<stdio.h>
#include<stdlib.h>
#define MAX 10

typedef struct
{
    int data[MAX];// 存储线性表元素的数组
    int length;// 线性表当前长度
}SqList;

bool ListInsert(SqList *L,int i,int e)
{
    int j;
    //检查插入位置的合法性，位置应从1到length+1之间
    if(i<1||i>L->length+1){
    printf("位置i不合法！");
    return false;
    }
    /* 检查顺序表是否已满 */
    if(L->length==MAX){
    printf("顺序表已满！");
    return false;
    }
    /* 将第i个位置及之后的元素向后移动一位 */
    for(j=L->length;j>=i;j--)
    L->data[j]=L->data[j-1];
    L->data[i-1]=e;
    L->length++;
    return true;
}

void InitList(SqList *L)
{   
    // 将顺序表中所有元素初始化为0
    for (int i = 0; i < MAX; i++)
    {
        L->data[i]=0;
    }
    L->length=0;
}

int main()
{   //初始化顺序表并测试插入功能
    //创建一个顺序表L和一个待插入元素e
    SqList L;
    int e=3;
    //初始化顺序表L
    InitList(&L);
    //打印顺序表第一个元素的值（初始化后应为0）
    printf("原本第一个元素:%d\n",L.data[0]);
    //在顺序表的第一个位置插入元素e
    ListInsert(&L,1,e);
    //打印插入元素后顺序表第一个元素的值（应为3）
    printf("插入后第一个元素:%d",L.data[0]);
    return 0;
}