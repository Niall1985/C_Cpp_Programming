#include <stdio.h>
#include <stdlib.h>

struct node {
    int coeff;      // Coefficient
    int pow;        // Power of the variable (x^pow)
    struct node* next;
};

// Function to create a new node
struct node* createNode(int coeff, int pow) {
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->coeff = coeff;
    newNode->pow = pow;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a new term at the end of the polynomial
void insertEnd(struct node** poly, int coeff, int pow) {
    struct node* newNode = createNode(coeff, pow);
    if (*poly == NULL) {
        *poly = newNode;
    } else {
        struct node* temp = *poly;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

// Function to display the polynomial
void display(struct node* poly) {
    while (poly != NULL) {
        printf("%dx^%d", poly->coeff, poly->pow);
        if (poly->next != NULL)
            printf(" + ");
        poly = poly->next;
    }
    printf("\n");
}

// Function to add two polynomials
struct node* addPolynomials(struct node* poly1, struct node* poly2) {
    struct node* result = NULL;

    while (poly1 != NULL && poly2 != NULL) {
        if (poly1->pow > poly2->pow) {
            insertEnd(&result, poly1->coeff, poly1->pow);
            poly1 = poly1->next;
        } else if (poly1->pow < poly2->pow) {
            insertEnd(&result, poly2->coeff, poly2->pow);
            poly2 = poly2->next;
        } else {
            insertEnd(&result, poly1->coeff + poly2->coeff, poly1->pow);
            poly1 = poly1->next;
            poly2 = poly2->next;
        }
    }

    // If any terms are left in poly1
    while (poly1 != NULL) {
        insertEnd(&result, poly1->coeff, poly1->pow);
        poly1 = poly1->next;
    }

    // If any terms are left in poly2
    while (poly2 != NULL) {
        insertEnd(&result, poly2->coeff, poly2->pow);
        poly2 = poly2->next;
    }

    return result;
}

int main() {
    struct node* poly1 = NULL;
    struct node* poly2 = NULL;

    // First polynomial: 3x^3 + 5x^2 + 6
    insertEnd(&poly1, 3, 3);
    insertEnd(&poly1, 5, 2);
    insertEnd(&poly1, 6, 0);

    // Second polynomial: 4x^3 + 2x^1 + 3
    insertEnd(&poly2, 4, 3);
    insertEnd(&poly2, 2, 1);
    insertEnd(&poly2, 3, 0);

    printf("First Polynomial: ");
    display(poly1);

    printf("Second Polynomial: ");
    display(poly2);

    struct node* sum = addPolynomials(poly1, poly2);

    printf("Sum of Polynomials: ");
    display(sum);

    return 0;
}
