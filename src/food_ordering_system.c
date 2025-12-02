// FOOD ORDERING SYSTEM - C PROGRAMMING MAJOR PROJECT
// Author [ADITYA RAJ MISHRA]

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAX 0.05 // 5% GST tax rate
#define MAX_ORDER_ITEMS 20 // Maximum items per order
#define MAX_MENU_ITEMS 50 // Maximum menu items supported

struct Menu {
    int code;
    char name[30]; // Item name
    float price; // Item price per unit
};

struct Order {
    int code; // Menu item code
    int qty; // Quantity
    float total; // Total price for this line
};

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Display all menu items
void displayMenu(struct Menu m[], int n) {
    int i;
    
    // Print menu
    printf("\n MENU \n");
    printf("Code\tItem\t\tPrice\n");
    
    for (i = 0; i < n; i++) {
        printf("%d\t%-15s%.2f\n", m[i].code, m[i].name, m[i].price);
    }
    
    printf("\n");
}

// Take customer order and generate bill
float takeOrder(struct Menu m[], int n) {
    struct Order order[MAX_ORDER_ITEMS]; 
    int itemCount = 0; 
    float grandTotal = 0.0f; // Running total before tax
    char ch; // User choice to continue ordering
    
    do {
        int found = 0;
        int i;
        
        // Get item code from user
        printf("\nEnter item code: ");
        if (scanf("%d", &order[itemCount].code) != 1) {
            printf("Invalid input\n");
            clearInputBuffer();
            continue;
        }

        // Search menu array for matching item code
        for (i = 0; i < n; i++) {
            if (m[i].code == order[itemCount].code) {
                found = 1;
                
                // Get quantity
                printf("Enter quantity: ");
                if (scanf("%d", &order[itemCount].qty) != 1 || order[itemCount].qty <= 0) {
                    printf("Invalid quantity\n");
                    clearInputBuffer();
                    continue;
                }
                
                // Calculate line total and add to grand total
                order[itemCount].total = m[i].price * order[itemCount].qty;
                grandTotal += order[itemCount].total;
                itemCount++;
                break;
            }
        }

        // Handle invalid item code
        if (!found) {
            printf("Invalid code\n");
            continue;
        }

        // Check maximum items limit
        if (itemCount >= MAX_ORDER_ITEMS) {
            printf("Maximum items reached.\n");
            break;
        }

        // Ask user if they want to add more items
        printf("Do you want to add another item? (y/n): ");
        clearInputBuffer();
        ch = getchar();

    } while (ch == 'y' || ch == 'Y'); // Continue if user says yes

    // Handle empty order
    if (itemCount == 0) {
        printf("\nNo items ordered\n");
        return 0.0f;
    }

    // Display bill summary
    printf("\n BILL \n");
    printf("Item\t\tQty\tTotal\n");

    // Print each ordered item 
    {
        int i, j;
        for (i = 0; i < itemCount; i++) {
            for (j = 0; j < n; j++) {
                if (m[j].code == order[i].code) {
                    printf("%-15s%d\t%.2f\n", m[j].name, order[i].qty, order[i].total);
                    break;
                }
            }
        }
    }

    // Discount code add after user finishes ordering, before tax calculation
    {
        char discountCode[20];
        float discountAmount = 0.0f;

        printf("\nEnter discount code (or press Enter to skip): ");
        clearInputBuffer();
        fgets(discountCode, sizeof(discountCode), stdin);
    
        discountCode[strcspn(discountCode, "\n")] = 0;

        if (strcmp(discountCode, "SAVE10") == 0) {
            discountAmount = grandTotal * 0.10f; // 10% discount
            printf("Discount code applied: 10%% off\n");
        } else if (strcmp(discountCode, "FLAT50") == 0) {
            discountAmount = 50.0f; // Flat 50 off
            printf("Discount code applied: ₹50 off\n");
        } else if (strlen(discountCode) > 0) {
            printf("Invalid discount code\n");
        }

        grandTotal -= discountAmount;
        if (grandTotal < 0) grandTotal = 0;
    }

    // Calculate and display final amounts with tax
    {
        float tax = grandTotal * TAX; // Calculate 5% GST
        float finalTotal = grandTotal + tax; // Final bill amount

        printf("\n");
        printf("Subtotal: %.2f\n", grandTotal);
        printf("GST(5%%): %.2f\n", tax);
        printf("Total: %.2f\n", finalTotal);

        // Save order to file
        {
            FILE *fp = fopen("orders.txt", "a"); // Open in append mode
            if (fp != NULL) {
                // Write bill summary to file
                fprintf(fp, "Subtotal: %.2f, GST: %.2f, Total Bill: %.2f\n",
                        grandTotal, tax, finalTotal);
                fclose(fp);
                printf("\nOrder saved\n");
            } else {
                printf("Error\n");
            }
        }

        // CUSTOMER RATING Added after bill payment
        {
            int rating;
            printf("\nHow would you rate our service? (1-5 stars): ");
            
            // NOTE: clearInputBuffer() removed here to fix double input issue
            
            if (scanf("%d", &rating) == 1 && rating >= 1 && rating <= 5) {
                // NOTE: Emoji changed to '*' to fix garbage output
                printf("Thank you for your %d star rating! *\n", rating);
                
                // Save rating to ratings file
                FILE *ratingFile = fopen("ratings.txt", "a");
                if (ratingFile != NULL) {
                    fprintf(ratingFile, "Rating: %d/5 stars for order worth ₹%.2f\n", rating, finalTotal);
                    fclose(ratingFile);
                    printf("feedback saved\n");
                } else {
                    printf("Note: Feedback not saved \n");
                }
            } else {
                printf("Invalid rating\n");
                clearInputBuffer();
            }
        }

        return finalTotal;
    }
}

// Display previous orders from file
void viewPreviousOrders() {
    FILE *fp = fopen("orders.txt", "r"); // Open file in read mode
    char c;

    if (fp == NULL) { // Check if file exists
        printf("\nNo previous orders found.\n");
        return;
    }

    printf("\n Previous Orders \n");
    // Read and display entire file
    while ((c = (char)fgetc(fp)) != EOF) {
        putchar(c);
    }
    fclose(fp);
}

// Display customer ratings
void viewRatings() {
    FILE *fp = fopen("ratings.txt", "r");
    char c;

    if (fp == NULL) {
        printf("\nNo ratings\n");
        return;
    }

    printf("\n Customer Ratings \n");
    while ((c = (char)fgetc(fp)) != EOF) {
        putchar(c);
    }
    fclose(fp);
}

int main() {
    // Initialize menu array with 5 items
    struct Menu menu[] = {
        {1, "Pizza",       199.0f},
        {2, "Burger",       99.0f},
        {3, "Pasta",       149.0f},
        {4, "Sandwich",     79.0f},
        {5, "Cold Coffee",  69.0f}
    };
    int n = 5; // Number of menu items
    int choice;

    while (1) {
        // Display main menu options
        printf("\n FOOD ORDERING SYSTEM \n");
        printf("1. View Menu\n");
        printf("2. Place Order\n");
        printf("3. View Previous Orders\n");
        printf("4. View Customer Ratings\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input\n");
            clearInputBuffer();
            continue;
        }

        switch (choice) {
        case 1:
            displayMenu(menu, n); // Call menu display function
            break;
        case 2:
            takeOrder(menu, n); // Call order processing function
            break;
        case 3:
            viewPreviousOrders(); // Call file reading function
            break;
        case 4:
            viewRatings(); // Call view ratings function
            break;
        case 5:
            printf("\nThank you!\n");
            return 0;
        default:
            printf("\nInvalid choice\n");
            break;
        }
    }

    return 0;
}
