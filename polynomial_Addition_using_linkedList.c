// You are using GCC
#include <stdio.h>
#include <stdlib.h>

struct Term{
    int coefficient;
    int exponent;
    struct Term* next;
};

struct Term* createTerm(int coefficient, int exponent){
    struct Term* newTerm = (struct Term*)malloc(sizeof(struct Term));
    newTerm->coefficient = coefficient;
    newTerm->exponent = exponent;
    newTerm->next = NULL;
    return newTerm;
}

void insertTerm(struct Term** head, int coefficient, int exponent){
    struct Term* newTerm = createTerm(coefficient, exponent);
    if(*head == NULL || (*head)->exponent<exponent){
        newTerm->next=*head;
        *head=newTerm;
        return;
    }
    struct Term* current = *head;
    while(current->next != NULL && current->next->exponent>=exponent){
        current = current->next;
    }
    if(current->exponent == exponent){
        current->coefficient += coefficient;
        free(newTerm);
    }
    else{
        newTerm->next = current->next;
        current->next = newTerm;
    }
}

struct Term* addPolynomial(struct Term* poly1, struct Term* poly2){
    struct Term* result = NULL;
    while(poly1 != NULL){
        insertTerm(&result, poly1->coefficient, poly1->exponent);
        poly1 = poly1->next;
    }
    while(poly2 != NULL){
        insertTerm(&result, poly2->coefficient, poly2->exponent);
        poly2 = poly2->next;
    }
    return result;
}

void printPolynomial(struct Term* head){
    if(head == NULL){
        printf("0");
        return;
    }
    
    int isFirst = 1;
    for(struct Term* current = head; current != NULL; current = current->next){
        if(!isFirst && current->coefficient>=0){
            printf(" + ");
        }
        printf("(%dx^%d)", current->coefficient, current->exponent);
        isFirst=0;
    }
}


int main(){
    struct Term* poly1 = NULL;
    struct Term* poly2 = NULL;
    int n;
    scanf("%d",&n);
    for(int i = 0 ; i < n ; i++){
        int coefficient, exponent;
        scanf("%d %d", &coefficient, &exponent);
        insertTerm(&poly1, coefficient, exponent);
    }
    
    int m;
    scanf("%d",&m);
    for(int i = 0 ; i < m ; i++){
        int coefficient, exponent;
        scanf("%d %d", &coefficient, &exponent);
        insertTerm(&poly2, coefficient, exponent);
    }
    
    struct Term* result = addPolynomial(poly1, poly2);
    printPolynomial(result);
    printf("\n");
}
