#define ERROR 0
#define OK 1
#define OVERFLOW -1
typedef int Status;
typedef int QElemType;
typedef struct QNode{
	QElemType data;
	struct QNode *next;
}QNode,*QueuePtr;
typedef struct{
	QueuePtr head;
	QueuePtr tail;
}LinkQueue;

Status InitQueue (LinkQueue &Q);
Status DestroyQueue(LinkQueue &Q);
Status ClearQueue(LinkQueue &Q);
Status QueueEmpty(LinkQueue Q);
int QueueLength(LinkQueue Q);
Status GetHead(LinkQueue Q, QElemType &e);
Status EnQueue(LinkQueue &Q, QElemType e);
Status DeQueue(LinkQueue &Q, QElemType &e);
Status QueueTraverse(LinkQueue Q, Status (*visit)(QElemType &e));
Status visit_display(QElemType &e);