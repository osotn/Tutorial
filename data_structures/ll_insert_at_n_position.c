// Linked List: Inserting a node at n-th position.

#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* head;

void insert(int data, int n)
{
    struct Node* temp1 = (struct Node*)malloc(sizeof(struct Node*));
    temp1->data = data;
    temp1->next = NULL;

    if (n == 0) {
        temp1->next = head;
        head = temp1;
        return;
    }

    {
        struct Node* temp2 = head;
        int i;
        for (i = 0; i < n-1; i++)
            temp2 = temp2->next;
        temp1->next = temp2->next;
        temp2->next = temp1;
    }        
}

void print() {
    printf("List is ");
    struct Node* temp = head;
    while (temp != NULL) {
        printf(" %d", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    head = NULL;

    insert(1, 0);
    insert(2, 1);
    insert(5, 2);
    print();
}
