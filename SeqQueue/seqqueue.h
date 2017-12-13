#define OVERFLOW -1
#define OK 1
#define ERROR 0
#define MAXSIZE 100
#define INCREMENT 2
#define INITSIZE 2
typedef int Status;
typedef int QElemType;
typedef struct SeqQueue{
	QElemType *base;
	int head;
	int tail;
	int contentSize;
	int length;
}SeqQueue;
Status InitQueue(SeqQueue &Q);
Status DestroyQueue(SeqQueue &Q);
Status ClearQueue(SeqQueue &Q);
Status QueueEmpty(SeqQueue &Q);
Status QueueLength(SeqQueue Q);
Status GetHead(SeqQueue Q, QElemType &e);
Status EnQueue(SeqQueue &Q, QElemType e);
Status DeQueue(SeqQueue &Q, QElemType &e);
Status QueueTraverse(SeqQueue Q, Status (*visit)(QElemType &e));
Status VisitElemType(QElemType e);