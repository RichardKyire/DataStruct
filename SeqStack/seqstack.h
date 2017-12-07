#define STACK_INIT_SIZE 1   //栈初始化值
#define STACKINCREMENT 10 //每次扩充10个空间
#define OVERFLOW -1
#define ERROR 0
#define OK 1
#define TRUE 1
#define FALSE 0
typedef int Status;
typedef int SElemType;
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
Status StackTraverse(SeqStack S, Status (*visit)(SElemType));//遍历栈的所有元素
Status visit_display(SElemType e);//访问栈元素
Status display_char(SElemType e);