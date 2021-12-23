/**********************************************************************************
* Ethan Nguyen, etqnguye
* 2021 Winter CSE 101 pa1
* List.c
* Code for List ADT
*********************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "List.h"

// structs --------------------------------------------------------------------

// private NodeObj type
typedef struct NodeObj{
    LIST_ELEMENT data;
    struct NodeObj* next;
    struct NodeObj* prev;
} NodeObj;

// private Node type
typedef NodeObj* Node;

// private ListObj type
typedef struct ListObj{
    Node front;
    Node back;
    Node cursor;
    int index;
    int length;
} ListObj;


// Constructors-Destructors ---------------------------------------------------

// newNode()
// Returns reference to new Node object. Initializes next, prev and data fields.
Node newNode(LIST_ELEMENT data){
    Node N = malloc(sizeof(NodeObj));
    N->data = data;
    N->next = NULL;
    N->prev = NULL;
    return(N);
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
void freeNode(Node* pN){
    if( pN!=NULL && *pN!=NULL ){
      free(*pN);
      *pN = NULL;
    }
}

// newQueue()
// Returns reference to new empty Queue object.
List newList(){
    List L;
    L = malloc(sizeof(ListObj));
    L->front = L->back = NULL;
    L->length = 0;
    L->index = -1;
    L->cursor = NULL;
    return(L);
}

// freeList()
// Frees all heap memory associated with List *pL, and sets *pL to NULL.
void freeList(List* pL){
    while(length(*pL) > 0){
        deleteFront(*pL);
    }
    free(*pL);
    *pL = NULL;
}



// Access functions -----------------------------------------------------------


// length()
// Returns the number of elements in L.
int length(List L){
    return L->length;
}

// index();
// Returns index of cursor element if defined, -1 otherwise.
int Index(List L){
    return L->index;
}

// front()
// Returns front element of L. Pre: length()>0
LIST_ELEMENT front(List L){
    if(L->length <= 0){
        printf("List Error: calling front() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    return L->front->data;
}

// back()
// Returns back element of L. Pre: length()>0
LIST_ELEMENT back(List L){
    if(L->length <= 0){
        printf("List Error: calling back() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    return L->back->data;
}

// get()
// Returns cursor element of L. Pre: length()>0, index()>=0
LIST_ELEMENT get(List L){
    if(L->length <= 0 || L->index < 0){
        printf("List Error: calling get() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    return L->cursor->data;
}

//LIST_ELEMENT equals(List A, List B){
//    int eq = 0;
//    Node N = NULL;
//    Node M = NULL;
//
//    if( A==NULL || B==NULL ){
//       printf("List Error: calling equals() on NULL List reference\n");
//       exit(EXIT_FAILURE);
//    }
//
//    eq = ( A->length == B->length );
//    N = A->front;
//    M = B->front;
//    while( eq && N!=NULL){
//       eq = (N->data==M->data);
//       N = N->next;
//       M = M->next;
//    }
//    return eq;
//}




// Manipulation procedures ----------------------------------------------------
// Resets L to its original empty state.
void Clear(List L){
    if(L->length == 0){
        return;
    }
     Node temp = L->front;
     Node next;
     while(temp != NULL){
        next = temp->next;
        freeNode(&temp);
        temp = next;
     }  
     L->length = 0;
    L->index = -1;
   
}

// Overwrites the cursor element’s data with x.
// Pre: length()>0, index()>=0
void set(List L, LIST_ELEMENT x){
    if(L->length <= 0 || L->index < 0){
        printf("List Error: calling set() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    L->cursor->data = x;
}

// If L is non-empty, sets cursor under the front element,
// otherwise does nothing.
void moveFront(List L){
    if(L->length == 0){
        return;
    }
    L->cursor = L->front;
    
    L->index = 0;
}

// If L is non-empty, sets cursor under the back element,
// otherwise does nothing.
void moveBack(List L){
    if(L->index == 0){
        return;
    }
    L->cursor = L->back;
    L->index = L->length - 1;
}

// If cursor is defined and not at front, move cursor one
// step toward the front of L; if cursor is defined and at
// front, cursor becomes undefined; if cursor is undefined
// do nothing
void movePrev(List L){
    if(L->cursor == NULL){
        return;
    }
    if(L->cursor != NULL && L->cursor == L->front){
        L->cursor = NULL;
        L->index = -1;
        return;
    }
    L->cursor = L->cursor->prev;
    L->index -= 1;
}

// If cursor is defined and not at back, move cursor one
// step toward the back of L; if cursor is defined and at
// back, cursor becomes undefined; if cursor is undefined
// do nothing
void moveNext(List L){
    if(L->cursor == NULL){
        return;
    }
    if(L->cursor != NULL && L->cursor == L->back){
        L->cursor = NULL;
        L->index = -1;
        return;
    }
    L->cursor = L->cursor->next;
    L->index += 1;
}

// Insert new element into L. If L is non-empty,
// insertion takes place before front element.
void prepend(List L, LIST_ELEMENT x){
    Node insert = newNode(x);
    
    if(L->length > 0){
        insert->next = L->front;
        L->front->prev = insert;
        L->front = insert;
        L->length += 1;
        return;
    }
    if(L->index >= 0){
        L->index += 1;
    }
    L->front = insert;
    L->back = insert;
    L->length += 1;
    return;
}

// Insert new element into L. If L is non-empty,
// insertion takes place after back element.
void append(List L, LIST_ELEMENT x){
    Node insert = newNode(x);
    if(L->length > 0){
        insert->prev = L->back;
        L->back->next = insert;
        L->back = insert;
        L->length += 1;
        return;
    }
    L->front = insert;
    L->back = insert;
    L->length += 1;
    return;
}

// Insert new element before cursor.
// Pre: length()>0, index()>=0
void insertBefore(List L, LIST_ELEMENT x){
    if(L->length <= 0 || L->index < 0){
        printf("List Error: calling insertBefore() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    Node insert = newNode(x);
    if(L->cursor->prev != NULL){
        insert->prev = L->cursor->prev;
        L->cursor->prev->next = insert;
        
    }
    else{
      L->front = insert;
    }
    L->cursor->prev = insert;
    insert->next = L->cursor;
    L->index += 1;
    L->length += 1;
}

// Insert new element after cursor.
// Pre: length()>0, index()>=0
void insertAfter(List L, LIST_ELEMENT x){
    if(L->length <= 0 || L->index < 0){
           printf("List Error: calling insertAfter() on NULL List reference\n");
           exit(EXIT_FAILURE);
       }
    Node insert = newNode(x);
    if(L->cursor->next != NULL){
        insert->next = L->cursor->next;
        L->cursor->next->prev = insert;
    }
    else{
      L->back = insert;
    }   
    L->cursor->next = insert;
    insert->prev = L->cursor;
    L->length += 1;
}

// Delete the front element. Pre: length()>0
void deleteFront(List L){
    if(L->length <= 0){
        printf("List Error: calling deleteFront() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if(L->cursor == L->front){
        L->cursor = NULL;
        L->index = -1;
    }
    if(L->length == 1){
	freeNode(&(L->front));
    }
    else{
       Node temp = L->front;
       L->front = temp->next;
       L->front->prev = NULL;
       freeNode(&temp);
    } 
    L->length -= 1;
    
    return;
}

// Delete the back element. Pre: length()>0
void deleteBack(List L){
    if(L->length <= 0){
        printf("List Error: calling deleteback() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if(L->cursor == L->back){
        L->cursor = NULL;
        L->index = -1;
    }
    if(L->length == 1){
      freeNode(&(L->front));
    }   
    else{
       Node temp = L->back;
       L->back = temp->prev;
       L->back->next = NULL;
       freeNode(&temp);
    }
    L->length -= 1;
    
    return;
}

// Delete cursor element, making cursor undefined.
// Pre: length()>0, index()>=0
void delete(List L){
    if(L->length <=0 || L->index < 0){
        printf("List Error: calling delete() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    Node before = L->cursor->prev;
    Node after = L->cursor->next;
    if(before == NULL && after == NULL){
	L->front = NULL;
	L->back = NULL;
    }
    if(before != NULL){
        before->next = L->cursor->next;
        if(before->next == NULL){
            L->back = before;
        }
    }
    if(after != NULL){
        after->prev = L->cursor->prev;
        if(after->prev == NULL){
            L->front = after;
        }
    }
    Node temp = L->cursor;
    L->cursor = NULL;
    L->index = -1;
    L->length -= 1;
    freeNode(&temp);
    
    return;
}





// Other Functions ------------------------------------------------------------
// Prints to the file pointed to by out, a
// string representation of L consisting
// of a space separated sequence of integers,
// with front on left.
void printList(FILE * out, List L){
    moveFront(L);
    while(Index(L) >= 0){
     LIST_ELEMENT x = get(L);
     fprintf(out, "%ld ", x);
     moveNext(L);
    }
    return;
}

// Returns a new List representing the same integer
// sequence as L. The cursor in the new list is undefined,
// regardless of the state of the cursor in L. The state
// of L is unchanged.
List copyList(List L){
    List N = newList();
    int i = L->index;
    moveFront(L);
    while(Index(L) >= 0){
        LIST_ELEMENT x = get(L);
        append(N, x);
        moveNext(L);
    }
    L->index = i;
    return N;
}

