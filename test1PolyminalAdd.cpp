#include <stdio.h>
#include <stdlib.h>
#include<malloc.h> //malloc、free
#include <cstdio>
#define MAXSIZE 10
#define ElementType int

//多项式加法运算实例
struct PolyNode
{
    int coef; //系数
    int expon;//指数
    struct PolyNode*link;
};
typedef struct PolyNode*Polynomial;

//自定义比较函数 相等为0 左大于右为1 右大于左为-1
int Compare(int a, int b)
{
    int flag;
    if (a==b) flag=0;
    else if(a>b) flag=1;
    else if(a<b) flag=-1;
    return flag;
}

Polynomial InitNode(int size,int P[][2])
{
    Polynomial p = (PolyNode*)malloc(sizeof(PolyNode));
    Polynomial temp = p;
    int i;
    for (i = 0; i < size; i++)
    {
        Polynomial a = (PolyNode*)malloc(sizeof(PolyNode));
        a->coef = P[i][0];
        a->expon = P[i][1];
        a->link = NULL;
        temp->link = a;
        temp = temp->link;
    }
    printf("exchange%d\n",temp);
    temp = p;
    p = p->link;
    free(temp);
    printf("init ok!");
    return p;
}

Polynomial PolyAdd(Polynomial P1,Polynomial P2)
{
    Polynomial front,rear,temp;
    int sum;
    rear = (PolyNode*)malloc(sizeof(PolyNode));
    front = rear;
    printf("ready!\n");
    printf("compare result:%d\n",Compare(P1->expon,P2->expon));
    while (P1 && P2)//两个多项式都有非零项待处理时
    {
        switch(Compare(P1->expon,P2->expon))
        {
        case 0://次数相等时，系数相加,同时P1P2都移向后一项；
            printf("case0!\n");
            sum = P1->coef + P2->coef;
            if(sum)
            {
                rear = rear->link;
                rear->coef = sum;
                rear->expon = P1->expon;
            };
            P1 = P1->link;
            P2 = P2->link;
            break;
        case 1://P1次数大于P2,P1录入，同时P1移至后一结点；
            printf("case1!\n");
            rear = rear->link;
            rear->coef = P1->coef;
            rear->expon = P1->expon;
            P1 = P1->link;
            break;
        case -1://P2次数大于P1，P2录入，同时P2移至后一结点；
            printf("case-1!\n");
            rear = rear->link;
            rear->coef = P2->coef;
            rear->expon = P2->expon;
            P2 = P2->link;
            break;
        }
        printf("%d\n",P1 && P2);
    }
    printf("while ok!s");
    //如若存在剩余的项，直接接在尾部
    for(; P1; P1 = P1->link)
    {
        rear = rear->link;
        rear->coef = P1->coef;
        rear->expon = P1->expon;
    }
    for(; P2; P2 = P2->link)
    {
        rear = rear->link;
        rear->coef = P2->coef;
        rear->expon = P2->expon;
    }
    rear->link = NULL;
    temp = front;
    front = front->link;
    printf("3ok!");
//    free(temp);
    printf("4ok!");
    return front;
}

int main()
{
    int i,j,flag;
    Polynomial P1, P2, AddResult;//新建类型为自定Polynomial的实例（多项式)P1和P2
    ElementType a[5][2] = {{3,5},{4,4},{-1,3},{2,1},{-1,0}};
    ElementType b[4][2] = {{2,4},{1,3},{-7,2},{1,1} };
    for(i=0; i<5; i++)
    {
        for(j=0; j<2; j++)
        {
            printf("a[%d,%d]=%d\n",i,j,a[i][j]);
        }
    }
    P1 = InitNode(5, a);
    P2 = InitNode(4, b);
    printf("P1[1]=[%d,%d]\n",P1->coef,P1->expon);
    AddResult=PolyAdd(P1,P2);
    for(i=0; AddResult&&(i<10); AddResult->link,i++)
    {
        printf("AddResult=[%d,%d]\n",AddResult->coef,AddResult->expon);
    }
    printf('%d',(AddResult==NULL));
    getchar();
    return 0;
};
