#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include "huffman.h"

//1-n内找出权重最小的两个节点
void select(HuffmanTree &HT,int n,int &s1,int &s2){
	printf("1-%d中找最小的两个节点 s1=%d,s2=%d\n",n,s1,s2);
	int i=1;
	for(i;i<=n;i++){
		if(HT[i].parent==0){
			printf("%d没有双亲\n",i);
			printf("s1:%d的权重%d\n",s1,HT[s1].weight);
			if(HT[s1].weight==0){
				s1=i;
				printf("s1等于%d\n",i);
			}else if(HT[s2].weight==0){
				s2=i;
				printf("s2等于%d\n",i);
			}else{
				max(HT,s1,s2,i);
			}
		}
	}
	printf("权重最小的两个是%d、%d\n",s1,s2);
}
Status HuffmanCoding(HuffmanTree &HT, HuffmanCode &HC, int *w, int n){
	
	int start,i,wIndex;
	int m = 2*n-1;
	start=1;
	wIndex=1;
	HT = (HuffmanTree)malloc((m+1)*sizeof(HTNode));
	//将权重数据和叶子节点存入数组的1-n的位置中
	for(i=1,wIndex=1;i<=n;i++,wIndex++){
//		printf("将权重数据和叶子节点存入数组的1-n的位置中\n");
		HT[i].parent=0;
		HT[i].lchild=0;
		HT[i].rchild=0;
		HT[i].weight=w[wIndex];
		printf("%d的权重为%d\n",i,w[wIndex]);
	}
	HT[0].weight=0;
	//开始在数组剩余位置(n+1至m-1)构建二叉树的根节点
	for(i=n+1;i<=m;i++){
		int s1,s2;
		s1=s2=0;
		//在1至(i-1)的位置中找出权重最小的两个节点 s1,s2
		
		select(HT,i-1,s1,s2);
		
		HT[i].lchild=s1;
		printf("%d的左孩子是%d\n",i,s1);
		HT[i].rchild=s2;
		printf("%d的右孩子是%d\n",i,s2);
		HT[s1].parent=HT[s2].parent=i;
		printf("%d和%d的双亲都是%d\n",s1,s2,i);
		HT[i].weight=HT[s1].weight+HT[s2].weight;
		HT[i].parent=0;
	}
	printf("-----------\n");

	//构建好二叉树之后，要输出huffman编码
	//有两种方式输出huffman编码：一种是从叶子节点回溯到根节点，另外一种是从根节点追溯到叶子节点
	//第一种
	HC = (HuffmanCode)malloc((n+1)*sizeof(char *));	
	char *cd;
	cd = (char *)malloc(n*(sizeof(char)));//最多是n位
	cd[n-1] = '\0';
	for(i=1;i<=n;i++){
		int k = n;
		unsigned int current=i;
		for(current;HT[current].parent!=0;current=HT[current].parent){//一直找到根节点
			//找出current的双亲 然后判断 其双亲的左孩子是不是等于自己
			int parent = HT[current].parent;
			printf("%d的双亲是%d\n",i,parent);
			if(HT[parent].lchild==current){
				printf("%d节点权重%d是左孩子\n",current,HT[current].weight);
				cd[--k]='0';
			}else{
				printf("%d节点权重%d是右孩子\n",current,HT[current].weight);
				cd[--k]='1';
			}
			printf("current:%d parent:%d\n",current,parent);
		}
		HC[i] = (char *)malloc((n-k)*sizeof(char));
		strcpy(HC[i],&cd[k]);
		
	}

	return OK;


}


//在s1,s2,s3中找出 最小的两个 
void max(HuffmanTree HT,int &s1,int &s2, int s3){
	
	if(HT[s1].weight<HT[s2].weight){//s1比s2小，选中s1，否则选中s2
		if(HT[s3].weight<HT[s2].weight){//如果s3比s2小，选中s3，否则选中s2
			s2=s3;
		}
	}else{
		if(HT[s3].weight<HT[s1].weight){//已经选中s2，如果s3比s1小，则选中s3，否则选中s1
			s1=s3;
		}
	}
	int i;
	if(s1>s2){
		printf("s1比s2大\n",s1,s2);
		i=s1;
		s1=s2;
		s2=i;
	}

	printf("--------%d、%d、%d中最小的是%d和%d\n",s1,s2,s3,s1,s2);

}

void get_huffmanCode(HuffmanTree HT, HuffmanCode &HC, int n){
	//思路 weight是标识 0代表未遍历过，1代表遍历了左孩子，2代表遍历了右孩子
	int p,i,m;
	p=2*n-1;
	m=2*n;
	char *cd ;
	cd = (char *)malloc((n+1)*sizeof(char));
	int len=0;
	for(i=0;i<m;i++){//weight字段变成标识，因此需要全部置0
		HT[i].weight=0;
	}
	while(p){
		if(0==HT[p].weight){//如果当前节点没有遍历过
			printf("当前节点%d没有遍历过\n",p);
			HT[p].weight=1;
			if(HT[p].lchild!=0){
				p=HT[p].lchild;
				cd[len++]='0';
			}else if(HT[p].rchild==0){
				HC[p]=(char *)malloc((len+1)*sizeof(char));
				cd[len]='\0';
				strcpy(HC[p],cd);
			}
		}else if(1==HT[p].weight){//当前节点的左孩子已经遍历
			printf("当前节点%d的左孩子已经遍历过\n",p);
			HT[p].weight=2;
			if(HT[p].rchild!=0){			
				cd[len++]='1';
				p=HT[p].rchild;
			}
		}else{
			p=HT[p].parent;
			len--;
		}
	}

}
void main(){
	//为什么要将用数组来存储二叉树
	printf("dddd\n");

	HuffmanTree HT;
	HuffmanCode HC;
	int w[5] = {0,7,5,2,4};
	HuffmanCoding(HT, HC, w, 4);
	int i=0;
	for(i=1;i<=4;i++){
		printf("%s",HC[i]);
	}
	get_huffmanCode(HT,HC,4);	
	for(i=1;i<=4;i++){
		printf("%s ",HC[i]);
	}

}