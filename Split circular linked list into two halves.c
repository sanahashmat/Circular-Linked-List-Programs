#include <stdio.h>
#include <stdlib.h>

// Define the structure for a node in the linked list
struct Node {
    int data;
    struct Node* next;
};

// Function to insert a new node at the beginning of a circular linked list
void push(struct Node** head_ref, int new_data) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->data = new_data;

    // If the list is empty, make the new node point to itself
    if (*head_ref == NULL) {
        new_node->next = new_node;
        *head_ref = new_node;
        return;
    }

    // Traverse to the last node
    struct Node* temp = *head_ref;
    while (temp->next != *head_ref) {
        temp = temp->next;
    }

    // Update pointers to insert the new node at the beginning
    temp->next = new_node;
    new_node->next = *head_ref;
    *head_ref = new_node;
}

// Function to split a circular linked list into two halves
void splitList(struct Node* head, struct Node** head1_ref, struct Node** head2_ref) {
    struct Node* slow_ptr = head;
    struct Node* fast_ptr = head;

    // Handle empty list or list with a single node
    if (head == NULL)
        return;

    /* If there are more than 1 nodes, fast_ptr moves twice
       as fast as slow_ptr to find the middle of the list. */
    while (fast_ptr->next != head && fast_ptr->next->next != head) {
        fast_ptr = fast_ptr->next->next;
        slow_ptr = slow_ptr->next;
    }

    /* If the number of nodes is even, fast_ptr needs to move one more step
       to point to the last node of the first half */
    if (fast_ptr->next->next == head)
        fast_ptr = fast_ptr->next;

    // Set the head of the first list
    *head1_ref = head;

    // Set the end of the first list (slow_ptr is the last node)
    fast_ptr->next = slow_ptr->next;
    slow_ptr->next = head;
    
    // Set the head of the second list
    *head2_ref = fast_ptr->next;
}

// Function to print nodes in a given circular linked list
void printList(struct Node* head) {
    struct Node* temp = head;
    if (head != NULL) {
        do {
            printf("%d ", temp->data);
            temp = temp->next;
        } while (temp != head);
    }
    printf("\n");
}

// Main function to test the program
int main() {
    // Initialize heads of original, first, and second lists
    struct Node* head = NULL;
    struct Node* head1 = NULL;
    struct Node* head2 = NULL;

    // Create a circular linked list with an even number of elements
    push(&head, 12);
    push(&head, 56);
    push(&head, 2);
    push(&head, 11);
    push(&head, 65);
    push(&head, 32);

    printf("Original Circular Linked List: ");
    printList(head);

    // Split the list
    splitList(head, &head1, &head2);

    printf("\nFirst Circular Linked List: ");
    printList(head1);

    printf("Second Circular Linked List: ");
    printList(head2);

    return 0;
}
