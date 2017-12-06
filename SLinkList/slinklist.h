#define MAXSIZE 1000
#define OK 1
#define ERROR 0
typedef int Status;
typedef int ElemType;
typedef struct{
	ElemType data;
	int cur;
}component,SLinkList[MAXSIZE];

//初试化
Status init(SLinkList &list);

//free
Status free(SLinkList &list,int i);

//malloc
int malloc(SLinkList &list);

//插入
Status insertSLinkList(SLinkList &list,int i,ElemType e);

//删除
int deleteSLinkList(SLinkList &list,int i);

//链表的长度
int getLength(SLinkList &list);

//遍历链表
Status travel(SLinkList &list,Status (* visit)(ElemType));

//访问元素
Status visitElem(ElemType e);

//查找元素
int locateElem(SLinkList &list,ElemType e);

//(A-B)U(B-A)
void different(SLinkList &listA,SLinkList &listB);

