#include<stdio.h>
#include "slinklist.h"

//初试化
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
	if(i==0){//0代表备用列表没有空间，则返回ERROR
		return ERROR;
	}
	list[0].cur=list[i].cur;
	return i;
}

Status free(SLinkList &list,int i){//将下标为i的空间回收到备用列表中
	list[i].cur=list[0].cur;
	list[0].cur=i;
	return OK;
}

//在第i个位置插入e
Status insertSLinkList(SLinkList &list,int i,ElemType e){//处理i=1时，在第一个位置插入元素，因此要找到指向第一个元素的指针域
	int curor = MAXSIZE-1;//MAXSIZE-1 个元素指向第一个元素
	int k=0;
	while(curor!=0&&k<i-1){//找到i-1个元素
		curor=list[curor].cur;
		k++;
	}
	if(k>i-1){
		return ERROR;
	}
	int m = malloc(list);//向备用列表申请一个空间
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
	int curor = list[MAXSIZE-1].cur;//第一个元素
	while(curor!=0&&visit(list[curor].data)){
		curor=list[curor].cur;
	}
	printf("\n");
	return OK;
}

Status deleteSLinkList(SLinkList &list,int i){
	//删除链表的第i个元素
	int curor = MAXSIZE-1;//从头指针开始
	int k=0;
	while(list[curor].cur!=0&&k<i-1){//找到第i-1个元素,注意考虑i大于和等于链表长度的情况
		curor=list[curor].cur;
		k++;
	}
	int q=list[curor].cur;//第i个元素；
	if(q==0||k>i){
//		printf("ERROR\n");
		return ERROR;
	}
	list[curor].cur=list[q].cur;//思考：删除第一个元素，MAXSIZE-1头指针怎么修改？
	free(list,q);
	return OK;
}

int getLength(SLinkList &list){
	int curor = list[MAXSIZE-1].cur;
	int k=1;
	while(curor!=0){
		curor=list[curor].cur;
		k++;
	}
	return k-1;
}
int locateElem(SLinkList &list,ElemType e){
	//找到链表中第一个等于e的元素,返回该元素在链表中的位置,找不到返回0
	int curor=list[MAXSIZE-1].cur;//从第一个元素开始
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

void different(SLinkList &listA,SLinkList &listB){
	//先输入lenA,lenB表示A、B集合的个数
	int lenA,lenB;
	printf("请分别输入A和B集合的个数\n");
	scanf("%d%d",&lenA,&lenB);
	//输入A集合的元素
	init(listA);
	int i=1;
	printf("请输入集合A的元素:");
	for(i;i<=lenA;i++){
		ElemType e ;
		scanf("%d",&e);
		insertSLinkList(listA,i,e);
	}
	printf("请输入集合B的元素:");
	for(i=1;i<=lenB;i++){
		ElemType e;
		scanf("%d",&e);
		int loc = locateElem(listA,e);
		if(locateElem(listA,e)==0){//在A中找不到则插入
			travel(listA,&visitElem);
			printf("在第%d个位置插入%d\n",getLength(listA)+1,e);
			insertSLinkList(listA,1,e);
		}else{//找得到则删除
			travel(listA,&visitElem);
			printf("删除%d\n",e);
			deleteSLinkList(listA,loc);
		}
	}

}

void main(){
	SLinkList list;
	init(list);
	insertSLinkList(list,1,2);
	insertSLinkList(list,2,3);
	insertSLinkList(list,3,4);
	insertSLinkList(list,4,5);
	travel(list,&visitElem);
	printf("链表长度:%d\n",getLength(list));
	printf("5在链表的第%d个位置\n",locateElem(list,5));
	if(OK==deleteSLinkList(list,1)){
		travel(list,&visitElem);
		if(OK==deleteSLinkList(list,2)){
				travel(list,&visitElem);
			}
	}else{
		printf("删除失败\n");
	}
	SLinkList la,lb;
	different(la,lb);
	travel(la,&visitElem);

}
