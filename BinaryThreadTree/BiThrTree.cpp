#include<stdio.h>
#include "stdlib.h"
#include "BiThrTree.h"


Status CreateBiThrTree(BiThrTree &T){
	TElemType e;
	scanf("%d",&e);
	if(e==-1){
		T=NULL;
		return OK;
	}else{
		T = (BiThrTree)malloc(sizeof(BiThrNode));
		T->data=e;
		T->LTag=Link;
		T->RTag=Link;
		printf("������%d����ڵ�:",T->data);
		CreateBiThrTree(T->lchild);
		printf("������%d���ҽڵ�:",T->data);
		CreateBiThrTree(T->rchild);
	}
	return OK;
}
BiThrTree pre;
Status InOrderThreading(BiThrTree &Thrt, BiThrTree T){
	printf("");	//��֪��ʲôԭ�򣬲�����һ���ʲô����ʾ������������������
	if (!(Thrt = (BiThrNode *)malloc(sizeof(BiThrTree)) ))	//��ͷ���
		return ERROR;
	Thrt->LTag = Link;
	Thrt->RTag = Thread;
	Thrt->rchild = Thrt;
	if (!T)
		Thrt->lchild = Thrt;		//TΪ��������ͷ�����ָ��ָ��ͷ���
	else {
		Thrt->lchild = T;		//ͷ�������ָ������
		pre = Thrt;			//pre��ʼʱָ��ͷ���
		InThreading(T);		//�����������������
		pre->rchild = Thrt;		//���һ����������������һ����������ָ��ͷ���
		pre->RTag = Thread;
		Thrt->rchild = pre;		//ͷ��������ָ�����һ�������Ľ��
	}
	return OK;

}
void InThreading(BiThrTree p){
	if(p!=NULL){
		InThreading(p->lchild);
		if(p->lchild==NULL){
			p->LTag=Thread;
			p->lchild=pre;
		}
		if(pre->rchild==NULL){
			pre->RTag=Thread;
			pre->rchild=p;
		}
		pre=p;
		InThreading(p->rchild);
	}
}

//�Һ���
BiThrTree findNextDriver(BiThrTree T){
	BiThrTree p;
	if(T->RTag==Thread){//����ұ�ʶ�����������Һ���������
		p=T->rchild;
	}else{//���򣬺����Ǳ������������ʵĵ�һ���ڵ�
		p=T->rchild;
		while(p->LTag==Link){
			p=p->lchild;
		}
	}
	return p;
}

//��ǰ��
BiThrTree findPreDriver(BiThrTree T){
	BiThrTree p;
	if(T->LTag==Thread){//������ʶ��������������������
		p=T->lchild;
	}else{//���������������һ��Ԫ����������
		p=T->lchild;
		while(p->LTag==Link){
			p=p->lchild;
		}
	}
	return p;
}

Status InOrderTraverse_Thr(BiThrTree T, Status (*visit)(TElemType e)){
	//����ջ���ǵݹ飬�������������
	BiThrTree p = T->lchild;//ָ����ڵ�
	int i=0;
	while(/*i++<10){*/p!=T){
		while(p->LTag==Link){
			p=p->lchild;
		}
		visit(p->data);
		if(p->LTag==Thread&&p->rchild!=T){
			p=p->rchild;
			visit(p->data);
		}
		p=p->rchild;
	}
	return OK;
}

Status visitElemType(TElemType e){
	printf("%d ",e);
	return OK;
}
void main(){
	printf("dddd\n");
	BiThrTree t;
	CreateBiThrTree(t);
	BiThrTree head;
	InOrderThreading(head,t);
	InOrderTraverse_Thr(head,&visitElemType);
}