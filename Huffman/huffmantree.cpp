#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include "huffman.h"

//1-n���ҳ�Ȩ����С�������ڵ�
void select(HuffmanTree &HT,int n,int &s1,int &s2){
	printf("1-%d������С�������ڵ� s1=%d,s2=%d\n",n,s1,s2);
	int i=1;
	for(i;i<=n;i++){
		if(HT[i].parent==0){
			printf("%dû��˫��\n",i);
			printf("s1:%d��Ȩ��%d\n",s1,HT[s1].weight);
			if(HT[s1].weight==0){
				s1=i;
				printf("s1����%d\n",i);
			}else if(HT[s2].weight==0){
				s2=i;
				printf("s2����%d\n",i);
			}else{
				max(HT,s1,s2,i);
			}
		}
	}
	printf("Ȩ����С��������%d��%d\n",s1,s2);
}
Status HuffmanCoding(HuffmanTree &HT, HuffmanCode &HC, int *w, int n){
	
	int start,i,wIndex;
	int m = 2*n-1;
	start=1;
	wIndex=1;
	HT = (HuffmanTree)malloc((m+1)*sizeof(HTNode));
	//��Ȩ�����ݺ�Ҷ�ӽڵ���������1-n��λ����
	for(i=1,wIndex=1;i<=n;i++,wIndex++){
//		printf("��Ȩ�����ݺ�Ҷ�ӽڵ���������1-n��λ����\n");
		HT[i].parent=0;
		HT[i].lchild=0;
		HT[i].rchild=0;
		HT[i].weight=w[wIndex];
		printf("%d��Ȩ��Ϊ%d\n",i,w[wIndex]);
	}
	HT[0].weight=0;
	//��ʼ������ʣ��λ��(n+1��m-1)�����������ĸ��ڵ�
	for(i=n+1;i<=m;i++){
		int s1,s2;
		s1=s2=0;
		//��1��(i-1)��λ�����ҳ�Ȩ����С�������ڵ� s1,s2
		
		select(HT,i-1,s1,s2);
		
		HT[i].lchild=s1;
		printf("%d��������%d\n",i,s1);
		HT[i].rchild=s2;
		printf("%d���Һ�����%d\n",i,s2);
		HT[s1].parent=HT[s2].parent=i;
		printf("%d��%d��˫�׶���%d\n",s1,s2,i);
		HT[i].weight=HT[s1].weight+HT[s2].weight;
		HT[i].parent=0;
	}
	printf("-----------\n");

	//�����ö�����֮��Ҫ���huffman����
	//�����ַ�ʽ���huffman���룺һ���Ǵ�Ҷ�ӽڵ���ݵ����ڵ㣬����һ���ǴӸ��ڵ�׷�ݵ�Ҷ�ӽڵ�
	//��һ��
	HC = (HuffmanCode)malloc((n+1)*sizeof(char *));	
	char *cd;
	cd = (char *)malloc(n*(sizeof(char)));//�����nλ
	cd[n-1] = '\0';
	for(i=1;i<=n;i++){
		int k = n;
		unsigned int current=i;
		for(current;HT[current].parent!=0;current=HT[current].parent){//һֱ�ҵ����ڵ�
			//�ҳ�current��˫�� Ȼ���ж� ��˫�׵������ǲ��ǵ����Լ�
			int parent = HT[current].parent;
			printf("%d��˫����%d\n",i,parent);
			if(HT[parent].lchild==current){
				printf("%d�ڵ�Ȩ��%d������\n",current,HT[current].weight);
				cd[--k]='0';
			}else{
				printf("%d�ڵ�Ȩ��%d���Һ���\n",current,HT[current].weight);
				cd[--k]='1';
			}
			printf("current:%d parent:%d\n",current,parent);
		}
		HC[i] = (char *)malloc((n-k)*sizeof(char));
		strcpy(HC[i],&cd[k]);
		
	}

	return OK;


}


//��s1,s2,s3���ҳ� ��С������ 
void max(HuffmanTree HT,int &s1,int &s2, int s3){
	
	if(HT[s1].weight<HT[s2].weight){//s1��s2С��ѡ��s1������ѡ��s2
		if(HT[s3].weight<HT[s2].weight){//���s3��s2С��ѡ��s3������ѡ��s2
			s2=s3;
		}
	}else{
		if(HT[s3].weight<HT[s1].weight){//�Ѿ�ѡ��s2�����s3��s1С����ѡ��s3������ѡ��s1
			s1=s3;
		}
	}
	int i;
	if(s1>s2){
		printf("s1��s2��\n",s1,s2);
		i=s1;
		s1=s2;
		s2=i;
	}

	printf("--------%d��%d��%d����С����%d��%d\n",s1,s2,s3,s1,s2);

}

void get_huffmanCode(HuffmanTree HT, HuffmanCode &HC, int n){
	//˼· weight�Ǳ�ʶ 0����δ��������1������������ӣ�2����������Һ���
	int p,i,m;
	p=2*n-1;
	m=2*n;
	char *cd ;
	cd = (char *)malloc((n+1)*sizeof(char));
	int len=0;
	for(i=0;i<m;i++){//weight�ֶα�ɱ�ʶ�������Ҫȫ����0
		HT[i].weight=0;
	}
	while(p){
		if(0==HT[p].weight){//�����ǰ�ڵ�û�б�����
			printf("��ǰ�ڵ�%dû�б�����\n",p);
			HT[p].weight=1;
			if(HT[p].lchild!=0){
				p=HT[p].lchild;
				cd[len++]='0';
			}else if(HT[p].rchild==0){
				HC[p]=(char *)malloc((len+1)*sizeof(char));
				cd[len]='\0';
				strcpy(HC[p],cd);
			}
		}else if(1==HT[p].weight){//��ǰ�ڵ�������Ѿ�����
			printf("��ǰ�ڵ�%d�������Ѿ�������\n",p);
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
	//ΪʲôҪ�����������洢������
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