#define LIST_INIT_SIZE 2  // ���Ա�洢�ռ��ʼ��������
#define OVERFLOW -1
#define OK 1
#define LISTINCREMENT 10 
#define ERROR 0
#define TRUE 1
#define FALSE 0
typedef int ElemType;
typedef int Status;

struct Sqlist{
	ElemType *elem;  //�洢�ռ��ַ
	int length;    // ��ǰ����
	int listsize;  //��ǰ����Ĵ洢����
};
Status InitList_Sq(struct Sqlist &L);
void DestoryList_Sq(struct Sqlist &L);
void ClearList_Sq(struct Sqlist &L);
Status ListEmpyt_Sq(struct Sqlist L);
Status ListLength_Sq(struct Sqlist L);
void GetElem_Sq(struct Sqlist L, int i, ElemType &e);
Status compare_equal_Sq(ElemType e1, ElemType e2);
Status LocateElem_Sq(struct Sqlist L, ElemType e, Status (*compare)(ElemType, ElemType));
Status PriorElem_Sq(struct Sqlist L, ElemType cur_e, ElemType &pre_e);
Status NextrElem_Sq(struct Sqlist L, ElemType cur_e, ElemType &next_e);
Status ListInsert_Sq(struct Sqlist &L, int i, ElemType e);
Status ListDelete_Sq_Sq(struct Sqlist &L, int i, ElemType &e);
Status ListTraverse_Sq(struct Sqlist L);
Status visit_display_Sq(ElemType e);

void unionList_Sq(struct Sqlist &La, struct Sqlist Lb);
void MergeList_Sq(struct Sqlist La, struct Sqlist Lb, struct Sqlist &Lc);