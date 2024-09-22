#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
};

struct Node* head = NULL;

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

// Function to insert a node at the front
void insertFront(int data) {
    struct Node* newNode = createNode(data);
    
    if (head == NULL) {
        head = newNode; // List is empty
    } else {
        newNode->next = head; // Link new node to the current head
        head->prev = newNode;  // Link current head back to the new node
        head = newNode;        // Move head to point to the new node
    }
}

// Function to insert a node at the end
void insertEnd(int data) {
    struct Node* newNode = createNode(data);
    
    if (head == NULL) {
        head = newNode;
        return;
    }

    struct Node* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    
    temp->next = newNode;
    newNode->prev = temp;
}

// Function to check if the list is a palindrome
int isPalindrome() {
    struct Node* front = head;
    struct Node* back = head;

    // Move back pointer to the end of the list
    while (back->next != NULL) {
        back = back->next;
    }

    // Compare elements from front and back
    while (front != NULL && back != NULL && front != back && front->prev != back) {
        if (front->data != back->data) {
            return 0; // Not a palindrome
        }
        front = front->next;
        back = back->prev;
    }
    
    return 1; // Is a palindrome
}

// Function to print the list
void printList() {
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    int n, data;
    
    printf("Enter the number of elements: ");
    scanf("%d", &n);
    
    printf("Enter %d integers to insert at the front: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &data);
        insertFront(data);
    }
    
    printf("The linked list is: ");
    printList();
    
    if (isPalindrome()) {
        printf("The list is a palindrome.\n");
    } else {
        printf("The list is not a palindrome.\n");
    }
    
    return 0;
}
