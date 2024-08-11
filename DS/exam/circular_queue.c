#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Queue {
    int rear, front;
    int size;
    int *arr;
} Queue;

// Function to initialize the queue
Queue* createQueue(int s) {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = q->rear = -1;
    q->size = s;
    q->arr = (int*)malloc(q->size * sizeof(int));
    return q;
}

/* Function to insert an element in Circular queue */
void push(Queue* q, int value) {
    if ((q->front == 0 && q->rear == q->size - 1) || ((q->rear + 1) % q->size == q->front)) {
        printf("\nQueue is Full");
        return;
    }

    if (q->front == -1) {  /* Insert First Element */
        q->front = q->rear = 0;
        q->arr[q->rear] = value;
    } else if (q->rear == q->size - 1 && q->front != 0) {
        q->rear = 0;
        q->arr[q->rear] = value;
    } else {
        q->rear++;
        q->arr[q->rear] = value;
    }
}

// Function to delete an element from Circular Queue
int pop(Queue* q) {
    if (q->front == -1) {
        printf("\nQueue is Empty");
        return INT_MIN;
    }

    int data = q->arr[q->front];
    q->arr[q->front] = -1;
    if (q->front == q->rear) {
        q->front = -1;
        q->rear = -1;
    } else if (q->front == q->size - 1)
        q->front = 0;
    else
        q->front++;

    return data;
}

// Function displaying the elements of Circular Queue
void displayQueue(Queue* q) {
    if (q->front == -1) {
        printf("\nQueue is Empty");
        return;
    }

    printf("\nElements in Circular Queue are: ");
    if (q->rear >= q->front) {
        for (int i = q->front; i <= q->rear; i++)
            printf("%d ", q->arr[i]);
    } else {
        for (int i = q->front; i < q->size; i++)
            printf("%d ", q->arr[i]);

        for (int i = 0; i <= q->rear; i++)
            printf("%d ", q->arr[i]);
    }
}

/* Driver of the program */
int main() {
    Queue* q = createQueue(5);

    // Inserting elements in Circular Queue
    push(q, 14);
    push(q, 22);
    push(q, 13);
    push(q, -6);

    // Display elements present in Circular Queue
    displayQueue(q);

    // Deleting elements from Circular Queue
    printf("\nDeleted value = %d", pop(q));
    printf("\nDeleted value = %d", pop(q));

    displayQueue(q);

    push(q, 9);
    push(q, 20);
    push(q, 5);

    displayQueue(q);

    push(q, 20);  // This will show that the queue is full
    return 0;
}
