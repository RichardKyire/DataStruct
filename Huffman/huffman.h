#define OK 1
typedef int Status;
typedef struct{
	unsigned int weight;
	unsigned int parent,lchild,rchild;
}HTNode,*HuffmanTree;
typedef char * *HuffmanCode;	//��̬��������洢�շ��������

Status HuffmanCoding(HuffmanTree &HT, HuffmanCode &HC, int *w, int n);
Status Select(HuffmanTree HT, int n, int &s1, int &s2);
void max(HuffmanTree HT, int &s1, int &s2, int n);
void get_huffmanCode(HuffmanTree HT, HuffmanCode &HC, int n);