#define OK 1
#define ERROR 0
typedef enum PointerTag {Link, Thread};	// Link == 0, Ö¸Õë; Thread == 1, ÏßË÷
typedef int TElemType;
typedef int Status;
typedef struct BiThrNode {
	TElemType data;
	struct BiThrNode *lchild, *rchild;
	PointerTag LTag, RTag;
}BiThrNode, *BiThrTree;
Status CreateBiThrTree(BiThrTree &T);
Status InOrderTraverse_Thr(BiThrTree T, Status (*visit)(TElemType e));
Status InOrderThreading(BiThrTree &Thrt, BiThrTree T);
void InThreading(BiThrTree p);