#ifndef UNITY_H
#define UNITY_H
#include "unity.h"
#endif
#include <stdlib.h>

// ============================================================
// Forward declarations — implemented in code.c
// ============================================================

typedef struct Node {
    int value;
    struct Node *nextPtr;
} Node;

void  initNode    (Node *nodePtr, int value);
Node* createNode  (int value);
void  destroyNode (Node **nodePtrPtr);
void  destroyList (Node **headPtrPtr);
int   addFirst    (Node **headPtrPtr, Node *newNodePtr);
int   addLast     (Node **headPtrPtr, Node *newNodePtr);
Node* detachFirst (Node **headPtrPtr);
Node* detachLast  (Node **headPtrPtr);
Node* detachValue (Node **headPtrPtr, int value);
int   deleteFirst (Node **headPtrPtr);
int   deleteLast  (Node **headPtrPtr);
int   deleteValue (Node **headPtrPtr, int value);
void  destroyList (Node **headPtrPtr);
int   printList   (Node *headPtr);
int   listLength  (Node *headPtr);


// ============================================================
//  UNIT TESTS
//
//  Rules:
//  - Use TEST_ASSERT_TRUE_MESSAGE for every assertion.
//  - Do NOT use TEST_ASSERT_EQUAL — it reveals expected values.
//  - Heap tests: use createNode / destroyList.
//  - Stack tests: declare Node variables on the stack.
//  - Do NOT modify function names or signatures.
// ============================================================


// ============================================================
// test_initNode_sets_value
//
// Declare a Node on the stack.
// Call initNode with a known value.
// Verify that the value field contains that value.
// ============================================================

void test_initNode_sets_value(void)
{
    Node node;
    initNode(&node, 3);
    TEST_ASSERT_TRUE_MESSAGE(node.value == 3, "Value should match initialized value");
    
}


// ============================================================
// test_initNode_sets_next_null
//
// Declare a Node on the stack.
// Call initNode.
// Verify that nextPtr is NULL after the call.
// ============================================================

void test_initNode_sets_next_null(void)
{
    Node node;
    initNode(&node, 3);
    TEST_ASSERT_TRUE_MESSAGE(node.nextPtr == NULL, "nextPtr should be NULL");
}


// ============================================================
// test_initNode_null_guard
//
// Call initNode with NULL as the nodePtr.
// Verify the program does not crash.
// ============================================================

void test_initNode_null_guard(void)
{
    // TODO
    initNode(NULL, 3);
    TEST_ASSERT_TRUE_MESSAGE(1 == 1,
        "Error: initNode must handle NULL without crashing.");
}


// ============================================================
// test_createNode_not_null
//
// Call createNode with a known value.
// Verify the returned pointer is NOT NULL.
// Remember to free memory after the test using destroyNode.
// ============================================================

void test_createNode_not_null(void)
{
    Node *node = createNode(3);
    TEST_ASSERT_TRUE_MESSAGE(node != NULL, "created node should not be NULL");
    destroyNode(&node);
}


// ============================================================
// test_createNode_value
//
// Call createNode with a known value.
// Verify that the value field of the returned node
// contains the correct value.
// Remember to free memory after the test using destroyNode.
// ============================================================

void test_createNode_value(void)
{
    Node *node = createNode(3);
    TEST_ASSERT_TRUE_MESSAGE(node != NULL && node->value == 10, "node value should match value in createNode");
    destroyNode(&node);
}


// ============================================================
// test_createNode_next_null
//
// Call createNode.
// Verify that nextPtr of the returned node is NULL.
// Remember to free memory after the test using destroyNode.
// ============================================================

void test_createNode_next_null(void)
{
    Node *node = createNode(3);
    TEST_ASSERT_TRUE_MESSAGE(node != NULL && node->nextPtr == NULL, "nextPtr should be NULL");
    destroyNode(&node);
}


// ============================================================
// test_destroyNode_sets_null
//
// Call createNode to allocate a node.
// Call destroyNode.
// Verify that the pointer is NULL after the call.
// ============================================================

void test_destroyNode_sets_null(void)
{
    Node *node = createNode(3);
    destroyNode(&node);
    TEST_ASSERT_TRUE_MESSAGE(node == NULL, "pointer should be set to NULL");
}


// ============================================================
// test_addFirst_empty_list
//
// Start with headPtr == NULL.
// Create a node and call addFirst.
// Verify that headPtr now points to the new node.
// Clean up with destroyList.
// ============================================================

void test_addFirst_empty_list(void)
{
    Node *head = NULL;
    Node *newNode = createNode(3);
    addFirst(&head, newNode);
    TEST_ASSERT_TRUE_MESSAGE(head == newNode, "Head should point to new added node.");
    deatroyList(&head);
}


// ============================================================
// test_addFirst_non_empty
//
// Add two nodes using addFirst.
// Verify that headPtr points to the SECOND node added
// (the most recently added node is at the front).
// Verify the first node is reachable via nextPtr.
// Clean up with destroyList.
// ============================================================

void test_addFirst_non_empty(void)
{
    Node *head = NULL;
    Node *node1 = createNode(3);
    Node *node2 = createNode(2);
    addFirst(&head, node1);
    addFirst(&head, node2);
    TEST_ASSERT_TRUE_MESSAGE(head == node2 && head->nextPtr == node1, "nextPtr should point to second node.");
    destroyList(&head);
}


// ============================================================
// test_addFirst_null_headptr
//
// Call addFirst with NULL as headPtrPtr.
// Verify the function returns -1.
// ============================================================

void test_addFirst_null_headptr(void)
{
    Node *newNode = createNode(3);
    int returnValue = addFirst(NULL, newNode);
    TEST_ASSERT_TRUE_MESSAGE(returnValue == -1, "addFirst shoud return -1.");
    destroyNode(&newNode);
}


// ============================================================
// test_addLast_empty_list
//
// Start with headPtr == NULL.
// Create a node and call addLast.
// Verify that headPtr points to the new node.
// Clean up with destroyList.
// ============================================================

void test_addLast_empty_list(void)
{
    Node *head = NULL;
    Node *newNode = createNode(3);
    addLast(&head, newNode);
    TEST_ASSERT_TRUE_MESSAGE(head == newNode, "head should point to last node.");
    destroyList(&head);
}


// ============================================================
// test_addLast_non_empty
//
// Add two nodes using addLast.
// Verify that headPtr points to the FIRST node added.
// Verify the second node is reachable via nextPtr.
// Verify the second node's nextPtr is NULL.
// Clean up with destroyList.
// ============================================================

void test_addLast_non_empty(void)
{
    Node *head = NULL;
    Node *node1 = createNode(3);
    Node *node2 = createNode(2);
    addLast(&head, node1);
    addLast(&head, node2);
    TEST_ASSERT_TRUE_MESSAGE(head == node1 && head->nextPtr == node2 && node2->nextPtr == NULL, "first node is still head.");
    destroyList(&head);
}


// ============================================================
// test_addLast_null_guard
//
// Call addLast with NULL as headPtrPtr.
// Verify the function returns -1.
// ============================================================

void test_addLast_null_guard(void)
{
    Node *newNode = createNode(3);
    int returnValue = addLast(NULL, newNode);
    TEST_ASSERT_TRUE_MESSAGE(returnValue == -1, "addLast should return -1.");
    destroyNode(&newNode);
}


// ============================================================
// test_detachFirst_returns_node
//
// Build a stack chain: a -> b -> NULL
// Call detachFirst.
// Verify the returned pointer equals &a.
// ============================================================

void test_detachFirst_returns_node(void)
{
    Node a, b;
    initNode(&a, 1);
    initNode(&b, 2);
    a.nextPtr = &b;
    Node *head = &a;

    Node *detached = detachFirst(&head);
    TEST_ASSERT_TRUE_MESSAGE(detached == &a, "detachFirst should return address of head.");
}


// ============================================================
// test_detachFirst_updates_head
//
// Build a stack chain: a -> b -> NULL
// Call detachFirst.
// Verify that headPtr now points to b.
// ============================================================

void test_detachFirst_updates_head(void)
{
    Node a, b;
    initNode(&a, 1);
    initNode(&b, 2);
    a.nextPtr = &b;
    Node *head = &a;

    detachFirst(&head);
    TEST_ASSERT_TRUE_MESSAGE(head == &b, "Head should go from &a to &b.");
}


// ============================================================
// test_detachFirst_empty_list
//
// Call detachFirst on an empty list (headPtr == NULL).
// Verify the function returns NULL without crashing.
// ============================================================

void test_detachFirst_empty_list(void)
{
    Node *head = NULL;
    Node *detached = detachFirst(&head);
    TEST_ASSERT_TRUE_MESSAGE(detached == NULL, "detachFirst should return NULL for empty list.");
}


// ============================================================
// test_detachValue_found
//
// Build a stack chain: a(1) -> b(2) -> c(3) -> NULL
// Call detachValue for value 2 (middle node).
// Verify the returned pointer equals &b.
// Verify a->nextPtr now points to c.
// Verify b->nextPtr is NULL after detach.
// ============================================================

void test_detachValue_found(void)
{
    Node a, b, c;
    initNode(&a, 1);
    initNode(&b, 2);
    initNode(&c, 3);
    a.nextPtr = &b;
    b.nextPtr = &c;
    Node *head = &a;

    Node *detached = detachValue(&head, 2);
    TEST_ASSERT_TRUE_MESSAGE(detached == &b && a.nextPtr == &c && b.nextPtr == NULL, "detach value should unlink the node and its nextPtr.");
}


// ============================================================
// test_detachValue_head
//
// Build a stack chain: a(1) -> b(2) -> NULL
// Call detachValue for value 1 (head node).
// Verify the returned pointer equals &a.
// Verify headPtr now points to b.
// ============================================================

void test_detachValue_head(void)
{
    Node a, b;
    initNode(&a, 1);
    initNode(&b, 2);
    a.nextPtr = &b;
    Node *head = &a;

    Node *detached = detachValue(&head, 1);
    TEST_ASSERT_TRUE_MESSAGE(detached == &a && head == &b, "Head should be updated to next node.");
}


// ============================================================
// test_detachValue_not_found
//
// Build a stack chain: a(1) -> b(2) -> NULL
// Call detachValue for a value that does not exist (e.g. 99).
// Verify the function returns NULL.
// ============================================================

void test_detachValue_not_found(void)
{
    Node a, b;
    initNode(&a, 1);
    initNode(&b, 2);
    a.nextPtr = &b;
    Node *head = &a;

    Node *detached = detachValue(&head, 99);
    TEST_ASSERT_TRUE_MESSAGE(detached == NULL, "detachValue should return NULL if not in list.");
}


// ============================================================
// test_deleteFirst_removes_node
//
// Create two heap nodes and build a list.
// Call deleteFirst.
// Verify the function returns 0.
// Verify headPtr now points to the second node.
// Clean up with destroyList.
// ============================================================

void test_deleteFirst_removes_node(void)
{
    Node *head = NULL;
    Node *n1 = createNode(10);
    Node *n2 = createNode(20);
    addLast(&head, n1);
    addLast(&head, n2);

    int returnValue = deleteFirst(&head);
    TEST_ASSERT_TRUE_MESSAGE(returnValue == 0 && head == n2, "Should return 0 and change head.");
    destroyList(&head);
}


// ============================================================
// test_deleteFirst_empty_list
//
// Call deleteFirst on an empty list.
// Verify the function returns -1 without crashing.
// ============================================================

void test_deleteFirst_empty_list(void)
{
    Node *head = NULL;
    int returnValue = deleteFirst(&head);
    TEST_ASSERT_TRUE_MESSAGE(returnValue == -1, "deleteFirst should return -1 for empty list.");
}


// ============================================================
// test_deleteValue_found
//
// Create three heap nodes: 10 -> 20 -> 30
// Call deleteValue for 20.
// Verify the function returns 0.
// Verify listLength is now 2.
// Verify 20 is no longer in the list.
// Clean up with destroyList.
// ============================================================

void test_deleteValue_found(void)
{
    Node *head = NULL;
    Node *n1 = createNode(10);
    Node *n2 = createNode(20);
    Node *n3 = createNode(30);
    addLast(&head, n1);
    addLast(&head, n2);
    addLast(&head, n3);

    int returnValue = deleteValue(&head, 20);
    int length = listLength(head);
    int foundValue = 0;
    Node *curr = head;
    while (curr != NULL){
        if (curr->value == 20){
            foundValue = 1;
        }
        curr = curr->nextPtr;
    }

    TEST_ASSERT_TRUE_MESSAGE(returnValue == 0 && length == 2 && foundValue == 0, "");
    destroyList(&head);
}


// ============================================================
// test_deleteValue_not_found
//
// Create two heap nodes: 10 -> 20
// Call deleteValue for 99.
// Verify the function returns -1.
// Verify the list is unchanged (length still 2).
// Clean up with destroyList.
// ============================================================

void test_deleteValue_not_found(void)
{
    Node *head = NULL;
    Node *n1 = createNode(10);
    Node *n2 = createNode(20);
    addLast(&head, n1);
    addLast(&head, n2);

    int returnValue = deleteValue(&head, 99);
    int length = listLength(head);
    TEST_ASSERT_TRUE_MESSAGE(returnValue == -1 && length == 2, "deleteValue should return -1 for unfound value.");
    destroyList(&head);
}


// ============================================================
// test_destroyList_empties_list
//
// Create three heap nodes and build a list.
// Call destroyList.
// Verify headPtr is NULL after the call.
// ============================================================

void test_destroyList_empties_list(void)
{
    Node *head = NULL;
    Node *n1 = createNode(10);
    Node *n2 = createNode(20);
    Node *n3 = createNode(30);
    addLast(&head, n1);
    addLast(&head, n2);
    addLast(&head, n3);

    destroyList(&head);
    TEST_ASSERT_TRUE_MESSAGE(head == NULL, "Head should be NULL after destroyList call.");
}


// ============================================================
// test_listLength_empty
//
// Call listLength with NULL.
// Verify the function returns 0.
// ============================================================

void test_listLength_empty(void)
{
    int length = listLength(NULL);
    TEST_ASSERT_TRUE_MESSAGE(length == 0, "Length of empty list should be 0.");
}


// ============================================================
// test_listLength_three
//
// Create three heap nodes and build a list.
// Call listLength.
// Verify the function returns 3.
// Clean up with destroyList.
// ============================================================

void test_listLength_three(void)
{
    Node *head = NULL;
    Node *n1 = createNode(10);
    Node *n2 = createNode(20);
    Node *n3 = createNode(30);
    addLast(&head, n1);
    addLast(&head, n2);
    addLast(&head, n3);

    int length = listLength(head);
    TEST_ASSERT_TRUE_MESSAGE(length == 3, "List length should be three.");
    destroyList(&head);
}


// ============================================================
// test_printList_empty
//
// Call printList with NULL.
// Verify the function returns -1 without crashing.
// ============================================================

void test_printList_empty(void)
{
    int returnValue = printList(NULL);
    TEST_ASSERT_TRUE_MESSAGE(returnValue == -1, "printList should return -1 for empty list.");
}