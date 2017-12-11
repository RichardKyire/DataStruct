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
	InitStack(OPTR);//������ջ
	Push(OPTR, '#');
	InitStack(OPND);//������ջ
	char c =getchar();
	int i=0;
	while(c!='#'/*||++i<20){*/|| GetTop(OPTR) != '#'){
		if(!IN(c)){//������
			printf("������%c��ջ\n",c);
			Push(OPND,c-'0');
			c=getchar();
		}else{//������
			int oper = GetTop(OPTR);
			printf("������ջ��Ԫ����%c\n",oper);
			printf("�����������%c\n",c);
			if(precede(getIndex(oper),getIndex(c))=='<'){
				printf("������%c��ջ\n",c);
				Push(OPTR,c);
				c=getchar();
			}else if(precede(getIndex(oper),getIndex(c))=='='){
				printf("������\n");
				Pop(OPTR,oper);
				c=getchar();
			}else{
				int a,b;
				Pop(OPND,b);
				printf("%d��ջ\n",b);
				Pop(OPND,a);
				printf("%d��ջ\n",a);
				int ther;
				Pop(OPTR,ther);
				int res = operate(a,ther,b);
				Push(OPND,res);
				printf("����%d %c %d = %d \n",a,oper,b,res);	
			}		
		}
	}
	return GetTop(OPND);
}
void main(){
	
	printf("�����%d\n",evaluation());
//	SeqStack s;
//	InitStack(s);
//	Push(s,'a');
//	Push(s,'b');
//	Push(s,'c');
//	printf("%c\n",GetTop(s));
//	char a='9';
//	printf("%d",a-'0');
}