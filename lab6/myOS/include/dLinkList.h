#ifndef __DLINKLIST_H__  
#define __DLINKLIST_H__

/*for double linked list*/

typedef struct dLink_node{    
    struct dLink_node * prev;
    struct dLink_node * next;    
} dLink_node;

typedef dLink_node dLinkedList;

void dLinkNodeInit(dLink_node *node);
void dLinkListInit(dLinkedList *list);

#define dLinkListIsEmpty(list) ((dLinkedList*)(list)->prev == (dLinkedList*)(list))

dLink_node *dLinkListFirstNode(dLinkedList *list);
dLink_node *dLinkListLastNode(dLinkedList *list);

void dLinkInsertBefore(dLinkedList *list, dLink_node *old, dLink_node *toBeInserted);
void dLinkInsertAfter(dLinkedList *list, dLink_node *old, dLink_node *toBeInserted);
void dLinkDelete(dLinkedList *list, dLink_node *toBeDeleted);

void dLinkInsertFifo(dLinkedList *list, dLink_node *toBeInserted);
void dLinkDeleteFifo(dLinkedList *list);

void dLinkInsertFifoBeforeTail(dLinkedList *list, dLink_node *toBeInserted);
#endif