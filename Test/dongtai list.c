#include<stdio.h>
#include<stdlib.h>
#define InitSize 10
typedef struct 
{   int *data;
    int MaxSize;
    int length;
}SqList;
void InitList(SqList *L)
{   
    // 为顺序表分配初始内存空间
    L->data=(int*)malloc(sizeof(int)*InitSize);
    // 设置顺序表初始长度为5
    L->length=5;
    // 设置顺序表最大容量为初始容量
    L->MaxSize=InitSize;
}
void IncreaseSize(SqList *L,int len)
{   
    // 保存原数据指针，防止内存泄漏
    int *p=L->data;
    // 分配新的内存空间，大小为原空间加上新增长度
    L->data=(int*)malloc((L->MaxSize+len)*sizeof(int));
    // 将原数据逐个复制到新分配的内存空间中
    for (int  i = 0; i <L->length; i++)
    {
        L->data[i]=p[i];
    }
    // 更新顺序表的最大容量
    L->MaxSize=L->MaxSize+len;
    free(p);
}
int main()
{   //测试
    SqList L;
    InitList(&L);
    printf("-------------------------------------\n");
    printf("|扩容前 MaxSize: %d\n", L.MaxSize);
    printf("|扩容前 data 地址: %p\n", L.data);
    IncreaseSize(&L, 5);
    printf("|----------------------------------\n");
    printf("|扩容后 MaxSize: %d\n", L.MaxSize);
    printf("|扩容后 data 地址: %p\n", L.data);
    printf("-------------------------------------\n");
    return 0;
}