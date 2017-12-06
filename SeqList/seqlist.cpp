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
	//构造一个空的线性表L
	L.elem = (ElemType *)malloc(LIST_INIT_SIZE*sizeof(struct Sqlist));
	if(!L.elem)
		return (OVERFLOW);			//存储分配失败
	L.length = 0;					// 空表长度为0
	L.listsize = LIST_INIT_SIZE;	// 初始存储容量
	return OK;
} // InitList_Sq

Status ListInsert_Sq(struct Sqlist &L, int i, ElemType e)
{
	//要求线性表存在，1<=i<=ListLength_Sq(L)+1
	//在第i个位置之前插入数据元素e, L的长度加1

	if(i<1||i>L.length+1){//判断i是否非法
		return ERROR;
	}
	ElemType * newbase;
	if(L.length+1 > L.listsize)
	{
		newbase = (ElemType *)realloc(L.elem, (L.listsize+LISTINCREMENT)*sizeof(ElemType));
		if(!newbase)
			exit(OVERFLOW);   //存储分配失败
		L.elem = newbase;  // 新基址
		L.listsize += LISTINCREMENT;  // 增加存储容量
	}
	ElemType * p = &(L.elem[i-1]);
	ElemType * q;
	for(q=&(L.elem[L.length-1]);q>=p;q--){
		*(q+1)= *q;
	}
	*p = e;
	L.length++;   // 表长加1
	return OK;
} //ListInsert_Sq

Status compare_equal_Sq(ElemType e1, ElemType e2)
{
	//判断两个数据元素是否相等，相等返回TRUE，不等返回FALSE
	if(e1 == e2)
		return TRUE;
	else
		return FALSE;
} //compare_equal_Sq

Status LocateElem_Sq(struct Sqlist L, ElemType e, Status (*compare)(ElemType, ElemType))
{
	//线性表L已存在，compare()是数据元素判定函数
	//返回L中第一个与e满足关系的compare()的数据元素的位序。若这样的数据元素不存在，返回0
	ElemType * p = L.elem;
	int i; // 位序
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
	//要求线性表存在
	//依次对L的每个元素调用函数visit(), 一旦visit()失败，则操作失败，返回FALSE,否则返回TRUE
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
	//要求线性表存在，1<=i<=ListLength_Sq(L)
	//e返回L中第i个数据元素的值
	e = *(L.elem + i - 1);
} //GetElem_Sq

void unionList_Sq(struct Sqlist &La, struct Sqlist Lb){
	int i=1;
	int lenB=Lb.length;
	int lenA=La.length;
	ElemType e ;
	for(i;i<=lenB;i++){
		GetElem_Sq(Lb,i,e);
		printf("Lb中第%d个元素为%d\n",i,e);
		if(!LocateElem_Sq(La,e,&compare_equal_Sq)){//在La链表中找等于Lb中第i个元素
			printf("在La末尾插入%d\n",e);
			ListInsert_Sq(La,La.length+1,e);
		}
	}
}

Status ListLength_Sq(struct Sqlist L)
{
	//要求线性表已存在
	//返回L中数据元素个数
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