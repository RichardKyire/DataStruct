#define OK 1
#define ERROR 0
typedef int TElemType;
typedef int Status;
typedef struct BiTNode{
	TElemType data;
	struct BiTNode *rChild;
	struct BiTNode *lChild;
}BiTNode,*BiTree;

typedef BiTree SElemType;

Status CreateBiTree(BiTree &T);
Status display(TElemType e);
Status PreOrderTraverse(BiTree T, Status (*visit)(TElemType e));
Status InOrderTraverse(BiTree T, Status (*visit)(TElemType e));
Status PostOrderTraverse(BiTree T, Status (*visit)(TElemType e));
Status LevelOrderTraverse(BiTree T, Status (*visit)(TElemType e));
Status PreOrderTraverse2(BiTree T, Status (*visit)(TElemType e));
Status InOrderTraverse2(BiTree T, Status (*visit)(TElemType e));
Status InOrderTraverse3(BiTree T, Status (*visit)(TElemType e));
Status PostOrderTraverse2(BiTree T, Status (*visit)(TElemType e));
