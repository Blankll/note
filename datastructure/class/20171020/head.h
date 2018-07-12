#define ElementType int
#define RIGHT 1
#define WRONG 0

typedef struct Node{
    ElementType data;
    struct Node *next;
}Node;
typedef struct Node* LinkList;


void InitCLinkList(LinkList *CL);//initliaze a Clinklist
void CreateCLinkListFromTail(LinkList CL);//CREATE From tail
void display(LinkList CL);//show the list on the screen
void destroy_list(LinkList CL);//desdtroy the list
LinkList merge_1(LinkList LA, LinkList LB);
LinkList merge_2(LinkList RA, LinkList RB);


void option_one();
