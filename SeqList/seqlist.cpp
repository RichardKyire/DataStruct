#include<stdio.h>
#include "seqlist.h"
#include<stdlib.h>

Status ListDelete_Sq_Sq(struct Sqlist &L, int i, ElemType &e){
	if(i<1||i>L.length){
		return ERROR;
	}
	ElemType *q = &(L.elem[i-1]);
	e=*q;
	for(q;q<&(L.elem[L.length-1]);q++){
		*q=*(q+1);
	}
	L.length--;
	return OK;
}
Status InitList_Sq(struct Sqlist &L)
{ 
	//����һ���յ����Ա�L
	L.elem = (ElemType *)malloc(LIST_INIT_SIZE*sizeof(struct Sqlist));
	if(!L.elem)
		return (OVERFLOW);			//�洢����ʧ��
	L.length = 0;					// �ձ���Ϊ0
	L.listsize = LIST_INIT_SIZE;	// ��ʼ�洢����
	return OK;
} // InitList_Sq

Status ListInsert_Sq(struct Sqlist &L, int i, ElemType e)
{
	//Ҫ�����Ա���ڣ�1<=i<=ListLength_Sq(L)+1
	//�ڵ�i��λ��֮ǰ��������Ԫ��e, L�ĳ��ȼ�1

	if(i<1||i>L.length+1){//�ж�i�Ƿ�Ƿ�
		return ERROR;
	}
	ElemType * newbase;
	if(L.length+1 > L.listsize)
	{
		newbase = (ElemType *)realloc(L.elem, (L.listsize+LISTINCREMENT)*sizeof(ElemType));
		if(!newbase)
			exit(OVERFLOW);   //�洢����ʧ��
		L.elem = newbase;  // �»�ַ
		L.listsize += LISTINCREMENT;  // ���Ӵ洢����
	}
	ElemType * p = &(L.elem[i-1]);
	ElemType * q;
	for(q=&(L.elem[L.length-1]);q>=p;q--){
		*(q+1)= *q;
	}
	*p = e;
	L.length++;   // ����1
	return OK;
} //ListInsert_Sq

Status compare_equal_Sq(ElemType e1, ElemType e2)
{
	//�ж���������Ԫ���Ƿ���ȣ���ȷ���TRUE�����ȷ���FALSE
	if(e1 == e2)
		return TRUE;
	else
		return FALSE;
} //compare_equal_Sq

Status LocateElem_Sq(struct Sqlist L, ElemType e, Status (*compare)(ElemType, ElemType))
{
	//���Ա�L�Ѵ��ڣ�compare()������Ԫ���ж�����
	//����L�е�һ����e�����ϵ��compare()������Ԫ�ص�λ��������������Ԫ�ز����ڣ�����0
	ElemType * p = L.elem;
	int i; // λ��
	for(i=1; i<=L.length; i++)
	{
		if(compare(e, *(p+i-1)))
		{
			return i;
		}
	}
	return 0;
} //LocateElem_Sq

Status ListTraverse_Sq(struct Sqlist L,Status (*visit)(ElemType))
{
	//Ҫ�����Ա����
	//���ζ�L��ÿ��Ԫ�ص��ú���visit(), һ��visit()ʧ�ܣ������ʧ�ܣ�����FALSE,���򷵻�TRUE
	int i;
	for(i=0; i<L.length; i++)
	{
		if(!visit(*(L.elem+i)))
			return FALSE;	    
	}
	return TRUE;
} // ListTraverse_Sq

Status visit_display_Sq(ElemType e)
{
	printf("%d ", e);
	return TRUE;
} //visit_display_Sq

void GetElem_Sq(struct Sqlist L, int i, ElemType &e)
{
	//Ҫ�����Ա���ڣ�1<=i<=ListLength_Sq(L)
	//e����L�е�i������Ԫ�ص�ֵ
	e = *(L.elem + i - 1);
} //GetElem_Sq

void unionList_Sq(struct Sqlist &La, struct Sqlist Lb){
	int i=1;
	int lenB=Lb.length;
	int lenA=La.length;
	ElemType e ;
	for(i;i<=lenB;i++){
		GetElem_Sq(Lb,i,e);
		printf("Lb�е�%d��Ԫ��Ϊ%d\n",i,e);
		if(!LocateElem_Sq(La,e,&compare_equal_Sq)){//��La�������ҵ���Lb�е�i��Ԫ��
			printf("��Laĩβ����%d\n",e);
			ListInsert_Sq(La,La.length+1,e);
		}
	}
}

Status ListLength_Sq(struct Sqlist L)
{
	//Ҫ�����Ա��Ѵ���
	//����L������Ԫ�ظ���
	return L.length;
} //ListLength_Sq

void MergeList_Sq(struct Sqlist La, struct Sqlist Lb, struct Sqlist &Lc)
{
	int i=1;
	int j=1;
	int lenA=ListLength_Sq(La);
	int lenB=ListLength_Sq(Lb);
	ElemType aElem,bElem;
	while(i<=lenA&&j<=lenB){
		GetElem_Sq(La,i++,aElem);
		GetElem_Sq(Lb,j++,bElem);
		if(aElem<bElem){
			ListInsert_Sq(Lc,Lc.length+1,aElem);
		}else{
			ListInsert_Sq(Lc,Lc.length+1,bElem);
		}
	}
	while(i<=lenA){
		GetElem_Sq(La,i++,aElem);
		ListInsert_Sq(Lc,Lc.length+1,aElem);
	}
	while(j<=lenB){
		GetElem_Sq(Lb,j++,bElem);
		ListInsert_Sq(Lc,Lc.length+1,bElem);
	}
} //MergList

void main(){
	struct Sqlist list;
	InitList_Sq(list);
	ListInsert_Sq(list,1,2);
	ListInsert_Sq(list,2,3);
	ListInsert_Sq(list,3,4);
	ListInsert_Sq(list,1,1);

	struct Sqlist Lb;
	InitList_Sq(Lb);
	ListInsert_Sq(Lb,1,5);
	ListInsert_Sq(Lb,2,6);
	ListInsert_Sq(Lb,3,7);
	ListInsert_Sq(Lb,1,1);

	unionList_Sq(list,Lb);


	ListTraverse_Sq(list,&visit_display_Sq);
//	printf("\n");
//	ElemType e;
//	ListDelete_Sq_Sq(list,1,e);
//	ListTraverse_Sq(list,&visit_display_Sq);
//	printf("\n");
//	ListInsert_Sq(list,1,1);
//	ListTraverse_Sq(list,&visit_display_Sq);
//	printf("\n");
//	printf("%d\n",p->listsize);
}