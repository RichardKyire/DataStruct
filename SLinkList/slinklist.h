#define MAXSIZE 1000
#define OK 1
#define ERROR 0
typedef int Status;
typedef int ElemType;
typedef struct{
	ElemType data;
	int cur;
}component,SLinkList[MAXSIZE];

//���Ի�
Status init(SLinkList &list);

//free
Status free(SLinkList &list,int i);

//malloc
int malloc(SLinkList &list);

//����
Status insertSLinkList(SLinkList &list,int i,ElemType e);

//ɾ��
int deleteSLinkList(SLinkList &list,int i);

//����ĳ���
int getLength(SLinkList &list);

//��������
Status travel(SLinkList &list,Status (* visit)(ElemType));

//����Ԫ��
Status visitElem(ElemType e);

//����Ԫ��
int locateElem(SLinkList &list,ElemType e);

//(A-B)U(B-A)
void different(SLinkList &listA,SLinkList &listB);

