#include<stdio.h>
#include<stdlib.h>

#define MAX_SIZE 20

#define TRUE 1
#define FALSE 0
#define ERROR -1

typedef int ElemType;
typedef int status;
typedef struct {
    ElemType data[MAX_SIZE];
    int length;
}seqlist;

status init_list(seqlist **L);
status list_empty(seqlist *L);
status list_clear(seqlist *L);
status list_get(seqlist *L, int index, ElemType *value);
status list_locate(seqlist *L, ElemType value);
status list_insert(seqlist *L, int index, ElemType value);
status list_delete(seqlist *L, int index, ElemType *value);
status list_length(seqlist *L, int length);


int main(void)
{
    seqlist *L;
    int i;
    ElemType value;
    init_list(&L);
    for(i = 0; i < MAX_SIZE; i++)
    {
        list_insert(L, i+1, i);
    }
    for(i = 0; i < MAX_SIZE; i++)
    {
        list_get(L, i + 1, &value);
        printf("%d\n", value);
    }
    printf("%d\n", L->length);

    return 0;
}

status init_list(seqlist **L)
{
    *L = (seqlist* )malloc(sizeof(seqlist));
    if(L == NULL) return FALSE;
    (*L)->length = 0;

    return TRUE;
}
status list_empty(seqlist *L)
{
    if(L->length == 0) return TRUE;
    else return FALSE;
}
status list_length(seqlist *L, int length)
{

}
status list_clear(seqlist *L)
{
    L->length = 0;

    return TRUE;
}
status list_get(seqlist *L, int index, ElemType *value)
{
    if(L->length == 0 || index < 1 || index > L->length)
    return FALSE;
    *value = L->data[index - 1];

    return TRUE;

}
status list_insert(seqlist *L, int index, ElemType value)
{
    int i;
    if(L->length == MAX_SIZE) return FALSE;
    if(index < 1 || index > L->length + 1) return FALSE;
    if(index <= L->length)
    {
        for(i = L->length - 1; i >= index - 1; i--)
        {
            L->data[i + 1] = L->data[i];
        }
    }
    L->data[index - 1] = value;
    L->length++;

    return TRUE;
}
status list_delete(seqlist *L, int index, ElemType *value)
{
    int i;
    if(L->length == 0) return FALSE;
    if(index < 1 || L->length < index) return FALSE;
    *value = L->data[index - 1];
    for(i = index - 1; i < L->length - 1; i++)
    {
        L->data[i] = L->data[index + 1];
    }
    L->length--;

    return TRUE;
}