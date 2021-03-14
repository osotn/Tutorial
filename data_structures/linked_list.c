// Data structres tutorial from freeCodeCamp.org
//
// Oleksandr V. Sotnikov
// (c) 2021


#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node* next;
};

void insert(struct Node** p_head, int x)
{
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->data = x;
    temp->next = *p_head;
    *p_head = temp;
}
void print(struct Node* head)
{
    printf("List is: ");
    while(head != NULL)
    {
        printf(" %d", head->data);
        head = head->next;
    }
    printf("\n");
}

int main()
{ 
    int n,i,x;
    
    struct Node* head = NULL; // empty list;

    printf("How many numbers?\n");
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        printf("Enter the number \n");
        scanf("%d", &x);
        insert(&head, x);
        print(head);
    }    
}

