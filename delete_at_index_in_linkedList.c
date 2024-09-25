#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

struct node *head = NULL;

// Function to insert a node at the end
void insertEnd(int data) {
    struct node *newNode = (struct node*)malloc(sizeof(struct node));
    newNode->data = data;
    newNode->next = NULL;

    if (head == NULL) {
        head = newNode;
    } else {
        struct node *temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

// Function to display the linked list
void display() {
    struct node *temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// Function to delete a node at a specific index
void deleteNodeAtIndex(int index) {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }

    struct node *temp = head;

    // If head needs to be removed
    if (index == 0) {
        head = head->next;
        free(temp);
        return;
    }

    // Traverse to the node just before the node to be deleted
    for (int i = 0; temp != NULL && i < index - 1; i++) {
        temp = temp->next;
    }

    // If the index is out of bounds
    if (temp == NULL || temp->next == NULL) {
        printf("Index out of bounds.\n");
        return;
    }

    // Node temp->next is the node to be deleted
    struct node *nodeToDelete = temp->next;
    temp->next = temp->next->next;

    // Free the memory of the node to be deleted
    free(nodeToDelete);
}

int main() {
    insertEnd(10);
    insertEnd(20);
    insertEnd(30);
    insertEnd(40);
    insertEnd(50);

    printf("Original List: ");
    display();

    // Deleting node at index 2 (30 will be deleted)
    deleteNodeAtIndex(2);
    printf("After deleting node at index 2: ");
    display();

    // Deleting the first node (head)
    deleteNodeAtIndex(0);
    printf("After deleting node at index 0: ");
    display();

    // Trying to delete at an invalid index
    deleteNodeAtIndex(10);  // Out of bounds

    return 0;
}
