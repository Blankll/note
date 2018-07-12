#define ElementType int
#define RIGHT 1
#define WRONG 0

typedef struct Node{
    struct Node *prior;
    ElementType data;
    struct Node *next;
}DNode;
typedef struct Node* DoubleList;

void InitDoubleList(DoubleList *DL);
void CreateDoubleListFromTail(DoubleList DL);
void display(DoubleList DL);
void destroy_list(DoubleList DL);
