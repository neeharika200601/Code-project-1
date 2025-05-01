#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct {
    int orderId;
    char customerName[50];
    char foodItem[50];
} Order;

Order queue[MAX];
int front = -1, rear = -1;

// Function to check if queue is full
int isFull() {
    return rear == MAX - 1;
}

// Function to check if queue is empty
int isEmpty() {
    return front == -1 || front > rear;
}

// Add an order to the queue
void enqueue() {
    if (isFull()) {
        printf("Queue is full! Cannot accept more orders.\n");
        return;
    }

    Order newOrder;
    printf("Enter Order ID: ");
    scanf("%d", &newOrder.orderId);
    getchar();  // consume newline

    printf("Enter Customer Name: ");
    fgets(newOrder.customerName, sizeof(newOrder.customerName), stdin);
    newOrder.customerName[strcspn(newOrder.customerName, "\n")] = '\0';  // remove newline

    printf("Enter Food Item: ");
    fgets(newOrder.foodItem, sizeof(newOrder.foodItem), stdin);
    newOrder.foodItem[strcspn(newOrder.foodItem, "\n")] = '\0';  // remove newline

    if (front == -1) front = 0;
    rear++;
    queue[rear] = newOrder;

    printf("Order added successfully!\n");
}

// Serve an order from the queue
void dequeue() {
    if (isEmpty()) {
        printf("Queue is empty! No orders to serve.\n");
        return;
    }

    printf("Serving Order ID: %d\n", queue[front].orderId);
    printf("Customer: %s\n", queue[front].customerName);
    printf("Food Item: %s\n", queue[front].foodItem);
    front++;
}

// Display all current orders
void displayQueue() {
    if (isEmpty()) {
        printf("Queue is empty.\n");
        return;
    }

    printf("Current Orders in Queue:\n");
    for (int i = front; i <= rear; i++) {
        printf("Order ID: %d | Customer: %s | Food Item: %s\n",
               queue[i].orderId, queue[i].customerName, queue[i].foodItem);
    }
}

int main() {
    int choice;

    do {
        printf("\n--- Food Delivery Queue Menu ---\n");
        printf("1. Add Order\n");
        printf("2. Serve Order\n");
        printf("3. View Queue\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();  // consume newline

        switch (choice) {
            case 1:
                enqueue();
                break;
            case 2:
                dequeue();
                break;
            case 3:
                displayQueue();
                break;
            case 4:
                printf("Exiting program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 4);

    return 0;
}
