#include<stdio.h>
#define Maxsize 10
typedef struct 
{   int data[Maxsize];
    int length;
    /* data */
}SqList;
void InitList(SqList &L)
{   
    for (int i = 0; i < Maxsize; i++)
    {
        L.data[i]=0;
    }
    L.length=0;
}

int main()
{   SqList L;
    InitList(L);
    printf("data[%d]=%d",L.data[0],L.data[0]);
    return 0;
}