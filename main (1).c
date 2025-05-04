#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SIZE 100

typedef struct {
    int customerId;
    char foodName[50];
    char hotelName[50];
    char streetName[50];
    time_t orderTime;
    time_t deliveryTime;
} Order;

Order queue[SIZE];
int front = -1, rear = -1;

void printOrderDetails(Order order) {
    printf("Customer ID: %d\n", order.customerId);
    printf("Food: %s\n", order.foodName);
    printf("Hotel: %s\n", order.hotelName);
    printf("Street: %s\n", order.streetName);
    printf("Order Time: %s", ctime(&order.orderTime));
    if (order.deliveryTime != 0) {
        printf("Delivery Time: %s", ctime(&order.deliveryTime));
    } else {
        printf("Delivery Time: Not yet delivered\n");
    }
    printf("------------------------------\n");
}

void placeOrder(Order order) {
    if (rear == SIZE - 1) {
        printf("Queue is full. Cannot place more orders.\n");
        return;
    }
    if (front == -1) front = 0;
    rear++;
    queue[rear] = order;
    printf("\nOrder placed successfully:\n");
    printOrderDetails(order);
}

void processOrder() {
    if (front == -1 || front > rear) {
        printf("\nNo orders to process.\n");
        return;
    }

    queue[front].deliveryTime = time(NULL); // Set delivery time when order is processed
    printf("\nOrder Delivered:\n");
    printOrderDetails(queue[front]);
    front++;
}

void showOrders() {
    if (front == -1 || front > rear) {
        printf("\nNo pending orders.\n");
        return;
    }

    printf("\n--- Pending Orders ---\n");
    for (int i = front; i <= rear; i++) {
        printf("Order %d:\n", i - front + 1);
        printOrderDetails(queue[i]);
    }
}

void searchOrderById(int customerId) {
    if (front == -1 || front > rear) {
        printf("\nNo orders to search.\n");
        return;
    }
    for (int i = front; i <= rear; i++) {
        if (queue[i].customerId == customerId) {
            printf("\nOrder found:\n");
            printOrderDetails(queue[i]);
            return;
        }
    }
    printf("\nOrder with Customer ID %d not found.\n", customerId);
}

void cancelOrder(int customerId) {
    if (front == -1 || front > rear) {
        printf("\nNo orders to cancel.\n");
        return;
    }
    int i, found = 0;
    for (i = front; i <= rear; i++) {
        if (queue[i].customerId == customerId) {
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("\nOrder with Customer ID %d not found.\n", customerId);
        return;
    }

    // Shift elements to remove the canceled order
    for (int j = i; j < rear; j++) {
        queue[j] = queue[j + 1];
    }
    rear--;
    printf("\nOrder with Customer ID %d has been canceled.\n", customerId);
}

int main() {
    int choice;
    int orderCount = 0;

    while (1) {
        printf("\n==== Online Food Delivery Queue System ====\n");
        printf("1. Place Order\n");
        printf("2. Process Order\n");
        printf("3. Show All Orders\n");
        printf("4. Search Order by Customer ID\n");
        printf("5. Cancel Order by Customer ID\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Clear newline

        if (choice == 1) {
            Order newOrder;
            newOrder.customerId = ++orderCount;

            printf("Enter food name: ");
            fgets(newOrder.foodName, sizeof(newOrder.foodName), stdin);
            newOrder.foodName[strcspn(newOrder.foodName, "\n")] = '\0';

            printf("Enter hotel name: ");
            fgets(newOrder.hotelName, sizeof(newOrder.hotelName), stdin);
            newOrder.hotelName[strcspn(newOrder.hotelName, "\n")] = '\0';

            printf("Enter street name: ");
            fgets(newOrder.streetName, sizeof(newOrder.streetName), stdin);
            newOrder.streetName[strcspn(newOrder.streetName, "\n")] = '\0';

            newOrder.orderTime = time(NULL); // Record order time
            newOrder.deliveryTime = 0; // Initial delivery time as 0 (not yet delivered)

            placeOrder(newOrder);

        } else if (choice == 2) {
            processOrder();
        } else if (choice == 3) {
            showOrders();
        } else if (choice == 4) {
            int customerId;
            printf("\nEnter Customer ID to search: ");
            scanf("%d", &customerId);
            searchOrderById(customerId);
        } else if (choice == 5) {
            int customerId;
            printf("\nEnter Customer ID to cancel: ");
            scanf("%d", &customerId);
            cancelOrder(customerId);
        } else if (choice == 6) {
            printf("\nExiting system. Thank you!\n");
            break;
        } else {
            printf("\nInvalid choice. Please try again.\n");
        }
    }

    return 0;
}
