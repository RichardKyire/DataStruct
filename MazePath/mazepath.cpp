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
						{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};   // 迷宫地图

struct SeqStack s;
/**
 * 判断当前位置能不能通过，当前位置可通过是指该位置未曾到达过
 */
bool Pass(PosType curpos)
{
	if (1 == Map[curpos.row][curpos.col]){
	printf("{%d %d}该位置不通\n",curpos.row,curpos.col);
		return false;
	}
	return true;
}

/**
 * 在走过的地方留下足迹
 */
void FootPrint(PosType curpos)
{
	Map[curpos.row][curpos.col] = 1;
	printf("走过{%d,%d}位置\n",curpos.row,curpos.col);
}

/**
 * 下一个位置，di从1到4表示从东到北
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
			printf("{%d,%d}进栈\n",e.seat.row,e.seat.col);
			Push(s,e);
			if(currPost.row==end.row&&currPost.col==end.col){
				printf("到达终点\n");
				return OK;
			}
			currPost=NextPos(currPost,e.di);
		}else{
			if (!StackEmpty(s)) {
				Pop(s,e);
				printf("{%d,%d}出栈\n",e.seat.row,e.seat.col);
				//换个方向
				printf("当前方向%d\n",e.di);
				while (4 == e.di && !StackEmpty(s)){
					printf("e当前方向%d\n",e.di);
					Pop(s, e);	//即该位置的4方向都已经探索完成，就再退回一步
					printf("周围都无路可走\n");
					printf("{%d,%d}出栈\n",e.seat.row,e.seat.col);
				}
				if(e.di<4){
					e.di++;
					printf("换个方向%d\n",e.di);
					Push(s,e);
					printf("{%d,%d}进栈\n",e.seat.row,e.seat.col);
					currPost = NextPos(e.seat, e.di);
				}
			}
		}
	}while(!StackEmpty(s));
	return OK;
}
/**
 * 算法3.3，迷宫算法
 */
Status MazePath(PosType start, PosType end)
{
	//写出伪代码
/*
思路：
while{
当前位置，找下一个方向
存在 进栈
不存在 栈顶出栈 新栈顶元素换一个方向
}直到栈顶为空 或者 到达出口
*/
	InitStack(s);
	SElemType e;
	//找出下一个方向
	e.di=0;
	e.ord=1;
	e.seat=start;
	printf("入口入栈\n");
	printf("开始位置%d %d\n",e.seat.row,e.seat.col);
	Push(s,e);
	FootPrint(e.seat);
	int k=1;
	do{	
		int dire = 0;
		while(++dire<=4){
			printf("方向是%d\n",dire);
			PosType nextPos = NextPos(e.seat,dire);		
			if(Pass(nextPos)){
				printf("下一个位置坐标：%d %d\n",nextPos.row,nextPos.col);
				e.seat=nextPos;
				e.ord++;
				e.di=dire;
				printf("{%d,%d}入栈\n",e.seat.row,e.seat.col);
				FootPrint(e.seat);
				Push(s,e);
				if(nextPos.col==end.col&&nextPos.row==end.col){
					printf("到达出口\n");
					return OK;
				}
				dire=0;
				break;
			}
		}
		if(dire>4){
			printf("找不到出路\n");
			Pop(s,e);
			printf("{%d,%d}出栈\n",e.seat.row,e.seat.col);
			GetTop(s,e);
		}
	}while(!StackEmpty(s));
//	}while(++k<20);
	
	return OK;
}


Status display_path(SElemType e){
	switch (e.di) {
	case 1:
		printf("右\n");
		break;
	case 2:
		printf("下\n");
		break;
	case 3:
		printf("左\n");
		break;
	case 4:
		printf("上\n");
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
