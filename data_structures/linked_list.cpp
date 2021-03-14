// Data structres tutorial from freeCodeCamp.org
//
// Oleksandr V. Sotnikov
// (c) 2021


#include <stdio.h>

struct Node
{
    int data;
    Node* link;
};


int main(void)
{
    Node  node1, node2, node3;
    Node* head;

    printf("sizeof Node = %lu, sizeof head = %lu, sizeof int =%lu\n",
        sizeof(node1), sizeof(head), sizeof(int));

    node1.data = 2;
    node1.link = NULL;
    head = &node1;
    node2.data = 4;
    node2.link = NULL;
    node1.link = &node2;
    node3.data = 8;
    node3.link = NULL;
    node2.link = &node3;

    Node* p_node;

    // dynamic
    p_node = new Node;
    p_node->data = 2; p_node->link = NULL;
    head = p_node;
    p_node = new Node;
    p_node->data = 4; p_node->link = NULL;
    head->link = p_node;
    p_node = new Node;
    p_node->data = 8; p_node->link = NULL;
    head->link->link = p_node;

    {
        Node* p = head;
        while (p != NULL)
        {
            printf("Node %p: data = %d, link = %p\n", p, p->data, p->link);
            p = p->link;
        }
    }

    return 0;
}
