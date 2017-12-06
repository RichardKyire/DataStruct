#include<stdio.h>
#include "slinklist.h"

//���Ի�
Status init(SLinkList &list){
	int i;
	for(i=0;i<MAXSIZE-1;i++){
		list[i].cur=i+1;
	}
	list[MAXSIZE-1].cur=0;
	return OK;
}

int malloc(SLinkList &list){
	int i = list[0].cur;
	if(i==0){//0�������б�û�пռ䣬�򷵻�ERROR
		return ERROR;
	}
	list[0].cur=list[i].cur;
	return i;
}

Status free(SLinkList &list,int i){//���±�Ϊi�Ŀռ���յ������б���
	list[i].cur=list[0].cur;
	list[0].cur=i;
	return OK;
}

//�ڵ�i��λ�ò���e
Status insertSLinkList(SLinkList &list,int i,ElemType e){//����i=1ʱ���ڵ�һ��λ�ò���Ԫ�أ����Ҫ�ҵ�ָ���һ��Ԫ�ص�ָ����
	int curor = MAXSIZE-1;//MAXSIZE-1 ��Ԫ��ָ���һ��Ԫ��
	int k=0;
	while(curor!=0&&k<i-1){//�ҵ�i-1��Ԫ��
		curor=list[curor].cur;
		k++;
	}
	if(k>i-1){
		return ERROR;
	}
	int m = malloc(list);//�����б�����һ���ռ�
	list[m].data=e;
	list[m].cur=list[curor].cur;
	list[curor].cur=m;
	
	return OK;
}
Status visitElem(ElemType e){
	printf("%d ",e);
	return OK;
}
Status travel(SLinkList &list,Status (* visit)(ElemType)){
	int curor = list[MAXSIZE-1].cur;//��һ��Ԫ��
	while(curor!=0&&visit(list[curor].data)){
		curor=list[curor].cur;
	}
	printf("\n");
	return OK;
}

Status deleteSLinkList(SLinkList &list,int i){
	//ɾ������ĵ�i��Ԫ��
	int curor = MAXSIZE-1;//��ͷָ�뿪ʼ
	int k=0;
	while(list[curor].cur!=0&&k<i-1){//�ҵ���i-1��Ԫ��,ע�⿼��i���ں͵��������ȵ����
		curor=list[curor].cur;
		k++;
	}
	int q=list[curor].cur;//��i��Ԫ�أ�
	if(q==0||k>i){
//		printf("ERROR\n");
		return ERROR;
	}
	list[curor].cur=list[q].cur;
	free(list,q);
	return OK;
}

int getLength(SLinkList &list){
	int curor = list[MAXSIZE-1].cur;
	int k=1;
	while(list[curor].cur!=0){
		curor=list[curor].cur;
		k++;
	}
	return k;
}
int locateElem(SLinkList &list,ElemType e){
	//�ҵ������е�һ������e��Ԫ��,���ظ�Ԫ���������е�λ��,�Ҳ�������0
	int curor=list[MAXSIZE-1].cur;//�ӵ�һ��Ԫ�ؿ�ʼ
	int k=1;
	while(curor!=0){
		if(list[curor].data==e){
			return k;
		}
		curor=list[curor].cur;
		k++;
	}
	return 0;
}

void main(){
	SLinkList list;
	init(list);
	insertSLinkList(list,1,2);
	insertSLinkList(list,2,3);
	insertSLinkList(list,3,4);
	insertSLinkList(list,4,5);
	travel(list,&visitElem);
	printf("������:%d\n",getLength(list));
	printf("5������ĵ�%d��λ��\n",locateElem(list,5));
	if(OK==deleteSLinkList(list,6)){
		travel(list,&visitElem);
	}else{
		printf("ɾ��ʧ��\n");
	}
	
}
