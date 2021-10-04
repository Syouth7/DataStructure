
#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include<malloc.h> //malloc��free
#include <cstdio>
#define MAXSIZE 10
#define ElementType int

//����ʽ�ӷ�����ʵ��
struct PolyNode
{
	int coef; //ϵ��
	int expon;//ָ��
	struct PolyNode*link;
};
typedef struct PolyNode*Polynomial;

//�Զ���ȽϺ��� ���Ϊ0 �������Ϊ1 �Ҵ�����Ϊ-1
int Compare(int a, int b)
{
	int flag;
	if (a == b) flag = 0;
	else if (a>b) flag = 1;
	else if (a<b) flag = -1;
	return flag;
}

Polynomial InitNode(int size, int P[][2])
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
	printf("exchange%d\n", temp);
	temp = p;
	p = p->link;
	free(temp);
	printf("init ok!");
	return p;
}


Polynomial PolyAdd(Polynomial P1, Polynomial P2)
{
	Polynomial front, rear, temp;
	int sum;
	front = (PolyNode*)malloc(sizeof(PolyNode));
	rear = front;
	printf("ready!\n");
	printf("compare result:%d\n", Compare(P1->expon, P2->expon));
	while (P1 && P2)//��������ʽ���з����������ʱ
	{
		Polynomial b = (PolyNode*)malloc(sizeof(PolyNode));
		switch (Compare(P1->expon, P2->expon))
		{
		case 0://�������ʱ��ϵ�����,ͬʱP1P2�������һ�
			printf("case0!\n");
			sum = P1->coef + P2->coef;
			if (sum)
			{
				b->coef = sum;
				b->expon = P1->expon;
				b->link = NULL;
				rear->link = b;
				rear = rear->link;
			};
			P1 = P1->link;
			P2 = P2->link;
			break;
		case 1://P1��������P2,P1¼�룬ͬʱP1������һ��㣻
			printf("case1!\n");
			b->coef = P1->coef;
			b->expon = P1->expon;
			b->link = NULL;
			rear->link = b;
			rear = rear->link;
			P1 = P1->link;
			break;
		case -1://P2��������P1��P2¼�룬ͬʱP2������һ��㣻
			printf("case-1!\n");
			b->coef = P2->coef;
			b->expon = P2->expon;
			b->link = NULL;
			rear->link = b;
			rear = rear->link;
			P2 = P2->link;
			break;
		}
		printf("P1P2 %d\n", P1 && P2);
		printf("A=[%d,%d]\n", rear->coef, rear->expon);
	}
	printf("while ok!\n");
	//��������ʣ����ֱ�ӽ���β��
	for (; P1; P1 = P1->link)
	{
		Polynomial b = (PolyNode*)malloc(sizeof(PolyNode));
		b->coef = P1->coef;
		b->expon = P1->expon;
		b->link = NULL;
		rear->link = b;
		rear = rear->link;
		printf("A=[%d,%d]\n", rear->coef, rear->expon);
	}
	for (; P2; P2 = P2->link)
	{
		Polynomial b = (PolyNode*)malloc(sizeof(PolyNode));
		b->coef = P2->coef;
		b->expon = P2->expon;
		b->link = NULL;
		rear->link = b;
		rear = rear->link;
		printf("A=[%d,%d]\n", rear->coef, rear->expon);
	}
	temp = front;
	front = front->link;
	printf("3ok!");
	free(temp);
	printf("4ok!");
	return front;
}

int main()
{
	int i, j, flag;
	Polynomial P1, P2, AddResult;//�½�����Ϊ�Զ�Polynomial��ʵ��������ʽ)P1��P2
	ElementType a[5][2] = { { 3,5 },{ 4,4 },{ -1,3 },{ 2,1 },{ -1,0 } };
	ElementType b[4][2] = { { 2,4 },{ 1,3 },{ -7,2 },{ 1,1 } };
	for (i = 0; i<5; i++)
	{
		for (j = 0; j<2; j++)
		{
			printf("a[%d,%d]=%d\n", i, j, a[i][j]);
		}
	}
	P1 = InitNode(5, a);
	P2 = InitNode(4, b);
	printf("P1[1]=[%d,%d]\n", P1->coef, P1->expon);
	AddResult = PolyAdd(P1, P2);
	for (i = 0; AddResult && (i<10); AddResult = AddResult->link, i++)
	{
		printf("AddResult%d=[%d,%d]\n",i, AddResult->coef, AddResult->expon);
	}
	printf("4ok!");
	getchar();
	return 0;
};
