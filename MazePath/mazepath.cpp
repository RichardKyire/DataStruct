#include<stdio.h>
#include "mazepath.h"
#include "seqstack.h"

int Map[SIZE][SIZE] = { {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, 
						{1, 0, 0, 1, 0, 0, 0, 1, 0, 1}, 
						{1, 0, 0, 1, 0, 0, 0, 1, 0, 1}, 
						{1, 0, 0, 0, 0, 1, 1, 0, 0, 1}, 
						{1, 0, 1, 1, 1, 0, 0, 0, 0, 1}, 
						{1, 0, 0, 0, 1, 0, 0, 0, 0, 1}, 
						{1, 0, 1, 0, 0, 0, 1, 0, 0, 1}, 
						{1, 0, 1, 1, 1, 0, 1, 1, 0, 1},
						{1, 1, 0, 0, 0, 0, 0, 0, 0, 1}, 
						{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};   // �Թ���ͼ

struct SeqStack s;
/**
 * �жϵ�ǰλ���ܲ���ͨ������ǰλ�ÿ�ͨ����ָ��λ��δ�������
 */
bool Pass(PosType curpos)
{
	if (1 == Map[curpos.row][curpos.col]){
	printf("{%d %d}��λ�ò�ͨ\n",curpos.row,curpos.col);
		return false;
	}
	return true;
}

/**
 * ���߹��ĵط������㼣
 */
void FootPrint(PosType curpos)
{
	Map[curpos.row][curpos.col] = 1;
	printf("�߹�{%d,%d}λ��\n",curpos.row,curpos.col);
}

/**
 * ��һ��λ�ã�di��1��4��ʾ�Ӷ�����
 */
PosType NextPos(PosType pos, int di)
{
	PosType nextPos;
	switch(di){
	case 1:
		nextPos.row=pos.row;
		nextPos.col=pos.col+1;
		break;
	case 2:
		nextPos.row=pos.row+1;
		nextPos.col=pos.col;
		break;
	case 3:
		nextPos.row=pos.row;
		nextPos.col=pos.col-1;
		break;
	case 4:
		nextPos.row=pos.row-1;
		nextPos.col=pos.col;
		break;
	default:
		printf("ERROR\n");
		break;
	}
	return nextPos;
}
Status MazePath1(PosType start, PosType end){
	InitStack(s);
	PosType currPost;
	currPost=start;
	SElemType e ;
	int step =1 ;
	do{
		if(Pass(currPost)){
			FootPrint(currPost);
			e.di=1;
			e.seat=currPost;
			e.ord=step++;
			printf("{%d,%d}��ջ\n",e.seat.row,e.seat.col);
			Push(s,e);
			if(currPost.row==end.row&&currPost.col==end.col){
				printf("�����յ�\n");
				return OK;
			}
			currPost=NextPos(currPost,e.di);
		}else{
			if (!StackEmpty(s)) {
				Pop(s,e);
				printf("{%d,%d}��ջ\n",e.seat.row,e.seat.col);
				//��������
				printf("��ǰ����%d\n",e.di);
				while (4 == e.di && !StackEmpty(s)){
					printf("e��ǰ����%d\n",e.di);
					Pop(s, e);	//����λ�õ�4�����Ѿ�̽����ɣ������˻�һ��
					printf("��Χ����·����\n");
					printf("{%d,%d}��ջ\n",e.seat.row,e.seat.col);
				}
				if(e.di<4){
					e.di++;
					printf("��������%d\n",e.di);
					Push(s,e);
					printf("{%d,%d}��ջ\n",e.seat.row,e.seat.col);
					currPost = NextPos(e.seat, e.di);
				}
			}
		}
	}while(!StackEmpty(s));
	return OK;
}
/**
 * �㷨3.3���Թ��㷨
 */
Status MazePath(PosType start, PosType end)
{
	//д��α����
/*
˼·��
while{
��ǰλ�ã�����һ������
���� ��ջ
������ ջ����ջ ��ջ��Ԫ�ػ�һ������
}ֱ��ջ��Ϊ�� ���� �������
*/
	InitStack(s);
	SElemType e;
	//�ҳ���һ������
	e.di=0;
	e.ord=1;
	e.seat=start;
	printf("�����ջ\n");
	printf("��ʼλ��%d %d\n",e.seat.row,e.seat.col);
	Push(s,e);
	FootPrint(e.seat);
	int k=1;
	do{	
		int dire = 0;
		while(++dire<=4){
			printf("������%d\n",dire);
			PosType nextPos = NextPos(e.seat,dire);		
			if(Pass(nextPos)){
				printf("��һ��λ�����꣺%d %d\n",nextPos.row,nextPos.col);
				e.seat=nextPos;
				e.ord++;
				e.di=dire;
				printf("{%d,%d}��ջ\n",e.seat.row,e.seat.col);
				FootPrint(e.seat);
				Push(s,e);
				if(nextPos.col==end.col&&nextPos.row==end.col){
					printf("�������\n");
					return OK;
				}
				dire=0;
				break;
			}
		}
		if(dire>4){
			printf("�Ҳ�����·\n");
			Pop(s,e);
			printf("{%d,%d}��ջ\n",e.seat.row,e.seat.col);
			GetTop(s,e);
		}
	}while(!StackEmpty(s));
//	}while(++k<20);
	
	return OK;
}


Status display_path(SElemType e){
	switch (e.di) {
	case 1:
		printf("��\n");
		break;
	case 2:
		printf("��\n");
		break;
	case 3:
		printf("��\n");
		break;
	case 4:
		printf("��\n");
		break;
	}
	return OK;
}


int main(){
 
	PosType start ={1,1};
	PosType end ={8,8};
	
	MazePath1(start,end);
	StackTraverse(s,&(visit_display));
	return 1;
}
