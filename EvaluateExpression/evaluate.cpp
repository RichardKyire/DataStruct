#include<stdio.h>
#include "evaluate.h"
#include "seqstack.h"
char Map[SIZE][SIZE]={{'>','>','<','<','<','>','>'},
				{'>','>','<','<','<','>','>'},
				{'>','>','<','<','<','>','>'},
				{'>','>','>','>','<','>','>'},
				{'<','<','<','<','<','=','>'},
				{'>','>','>','>',' ','>','>'},
				{'<','<','<','<','<',' ','='}
				};
int getIndex(char c){
//	printf("input char is %c\n",c);
	int i;
	switch(c){
	case '+':
		i=0;
		break;
	case '-':
		i=1;
		break;
	case '*':
		i=2;
		break;
	case '/':
		i=3;
		break;
	case '(':
		i=4;
		break;
	case ')':
		i=5;
		break;
	case '#':
		i=6;
		break;
	default:
		break;
	}
//	printf("%d\n",i);
	return i;
}
char precede(int a,int b){
	char res = Map[a][b];
//	printf("%d %d result:%c\n",a,b,res);
	return res;
}
bool IN(char c){
	if(c=='+'||c=='-'||c=='*'||c=='/'||c=='('||c==')'||c=='#')
		return true;
	return false;
}
int operate(int a,char oper,int b){

	int res;
	switch(oper){
	case '+':
		res = a+b;
		break;
	case '-':
		res = a-b;
		break;
	case '*':
		res = a*b;
		break;
	case '/':
		res = a/b;
		break;
	}
	return res;

}

SElemType evaluation(){
	SeqStack OPTR, OPND;
	InitStack(OPTR);//操作符栈
	Push(OPTR, '#');
	InitStack(OPND);//操作数栈
	char c =getchar();
	int i=0;
	while(c!='#'/*||++i<20){*/|| GetTop(OPTR) != '#'){
		if(!IN(c)){//操作数
			printf("操作数%c进栈\n",c);
			Push(OPND,c-'0');
			c=getchar();
		}else{//操作符
			int oper = GetTop(OPTR);
			printf("操作符栈顶元素是%c\n",oper);
			printf("输入操作符是%c\n",c);
			if(precede(getIndex(oper),getIndex(c))=='<'){
				printf("操作符%c进栈\n",c);
				Push(OPTR,c);
				c=getchar();
			}else if(precede(getIndex(oper),getIndex(c))=='='){
				printf("脱括号\n");
				Pop(OPTR,oper);
				c=getchar();
			}else{
				int a,b;
				Pop(OPND,b);
				printf("%d出栈\n",b);
				Pop(OPND,a);
				printf("%d出栈\n",a);
				int ther;
				Pop(OPTR,ther);
				int res = operate(a,ther,b);
				Push(OPND,res);
				printf("计算%d %c %d = %d \n",a,oper,b,res);	
			}		
		}
	}
	return GetTop(OPND);
}
void main(){
	
	printf("结果是%d\n",evaluation());
//	SeqStack s;
//	InitStack(s);
//	Push(s,'a');
//	Push(s,'b');
//	Push(s,'c');
//	printf("%c\n",GetTop(s));
//	char a='9';
//	printf("%d",a-'0');
}