
#ifndef _SEQSTACK_ 
#define _SEQSTACK_ 

#define STACK_INIT_SIZE 1   //ջ��ʼ��ֵ
#define STACKINCREMENT 10 //ÿ������10���ռ�
#define OVERFLOW -1
#define ERROR 0
#define OK 1
#define TRUE 1
#define FALSE 0
typedef int Status;
//typedef int SElemType;

typedef struct {
	int row;    // �У�0��ʼ
	int col;    // �У�0��ʼ
}PosType;
typedef struct {
	int ord;	// ͨ������·���ϵ����
	PosType seat;   // ͨ�������Թ��е�����λ��
	int di;		//�Ӵ�ͨ��������һͨ����ķ���
}SElemType;

struct SeqStack{
	SElemType *top;
	SElemType *base;
	int stackSize;
};

Status InitStack(SeqStack &S);
Status DestroyStack(SeqStack &S);
Status ClearStack(SeqStack &S);
Status StackEmpty(SeqStack S);
int StackLength(SeqStack S);
Status GetTop(SeqStack S, SElemType &e);
int GetTop(SeqStack S);
Status Push(SeqStack &S, SElemType e);
Status Pop(SeqStack &S, SElemType &e);
Status StackTraverse(SeqStack S, Status (*visit)(SElemType));//����ջ������Ԫ��
Status visit_display(SElemType e);//����ջԪ��
Status display_char(SElemType e);
Status display_path(SElemType e);
#endif 