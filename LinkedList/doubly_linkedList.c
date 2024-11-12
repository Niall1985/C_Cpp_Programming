#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
    struct node *prev;
};

struct node *head = NULL;

// Function to insert a node at the beginning of the list
void insertBeginning(int data) {
    struct node *ptr = (struct node *)malloc(sizeof(struct node));
    ptr->data = data;
    ptr->prev = NULL;
    ptr->next = head; // Point to current head
    if (head != NULL) {
        head->prev = ptr; // Update the previous head
    }
    head = ptr; // Update head to the new node
}

// Function to insert a node at the end of the list
void insertEnd(int data) {
    struct node *ptr = (struct node *)malloc(sizeof(struct node));
    ptr->data = data;
    ptr->next = NULL;

    if (head == NULL) {
        ptr->prev = NULL;
        head = ptr;
    } else {
        struct node *traverse = head;
        while (traverse->next != NULL) {
            traverse = traverse->next;
        }
        traverse->next = ptr;
        ptr->prev = traverse; // Update previous pointer
    }
}

// Function to print the list from head to tail
void printList() {
    struct node *current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// Function to print the list from tail to head
void printRev() {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }
    
    struct node *current = head;
    
    // Move to the last node
    while (current->next != NULL) {
        current = current->next;
    }

    // Print in reverse order
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->prev;
    }
    printf("\n");
}

// Function to insert a node after a given node
void insertNode(struct node *list, int data) {
    if (list == NULL) {
        printf("Given node is NULL.\n");
        return;
    }
    
    struct node *ptr = (struct node *)malloc(sizeof(struct node));
    ptr->data = data;
    ptr->next = list->next;
    ptr->prev = list;

    if (list->next != NULL) {
        list->next->prev = ptr; // Update the next node's prev pointer
    }
    
    list->next = ptr; // Link the new node after the given node
}

int main() {
    insertBeginning(1);
    insertBeginning(2);
    insertBeginning(3);
    insertBeginning(4);

    printf("List after inserting at the beginning: ");
    printList();

    insertEnd(5);
    printf("List after inserting at the end: ");
    printList();

    struct node *newNode = head->next; // Get the second node (2)
    insertNode(newNode, 10); // Insert 10 after the second node

    printf("List after inserting 10 after the second node: ");
    printList();

    printf("Reversed List: ");
    printRev();

    return 0;
}
