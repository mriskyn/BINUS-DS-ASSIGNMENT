#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct {
    char name[50];
} Customer;

typedef struct {
    Customer data[MAX];
    int front;
    int rear;
} Queue;

void initializeQueue(Queue *q) {
    q->front = -1;
    q->rear = -1;
}

int isEmpty(Queue *q) {
    return q->front == -1;
}

int isFull(Queue *q) {
    return q->rear == MAX - 1;
}

void enqueue(Queue *q, Customer customer) {
    if (isFull(q)) {
        printf("Queue is full\n");
        return;
    }
    if (isEmpty(q)) {
        q->front = 0;
    }
    q->rear++;
    q->data[q->rear] = customer;
    printf("%s added to the queue\n", customer.name);
}

Customer dequeue(Queue *q) {
    Customer customer;
    if (isEmpty(q)) {
        printf("Queue is empty\n");
        strcpy(customer.name, "No Customer");
        return customer;
    }
    customer = q->data[q->front];
    if (q->front == q->rear) {
        q->front = q->rear = -1;
    } else {
        q->front++;
    }
    return customer;
}

void displayQueue(Queue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty\n");
        return;
    }
    printf("Queue contents:\n");
    for (int i = q->front; i <= q->rear; i++) {
        printf("%s\n", q->data[i].name);
    }
}

int main() {
    Queue queue;
    initializeQueue(&queue);

    int choice;
    Customer customer;

    while (1) {
        printf("\n");
        printf("\nMenu:\n");
        printf("1. Add customer to queue\n");
        printf("2. Remove customer from queue\n");
        printf("3. Display queue\n");
        printf("4. Exit\n");
        
        printf("Choose an option: ");
        scanf("%d", &choice);
        printf("\n");
        getchar();  // To consume newline character left by scanf
        
        switch (choice) {
            case 1:
                printf("Enter customer name: ");
                fgets(customer.name, sizeof(customer.name), stdin);
                customer.name[strcspn(customer.name, "\n")] = 0; // Remove newline character
                enqueue(&queue, customer);
                break;
            case 2:
                customer = dequeue(&queue);
                if (strcmp(customer.name, "No Customer") != 0) {
                    printf("%s removed from the queue\n", customer.name);
                }
                break;
            case 3:
                displayQueue(&queue);
                break;
            case 4:
                printf("Exiting the program.\n");
                exit(0);
            default:
                printf("Invalid choice, please try again.\n");
        }
    }

    return 0;
}
