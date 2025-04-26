#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define MAX_ITEMS 50
#define MAX_ORDERS 20
#define MAX_USERS 10

typedef struct
{
    int id;
    char name[50];
    float price;
    int stock;
} MenuItem;

typedef struct
{
    int orderId;
    int itemId;
    int quantity;
    float totalPrice;
    int paymentMethod; 
} Order;

typedef struct
{
    char username[50];
    char password[50];
} User;


MenuItem menu[MAX_ITEMS];
Order orders[MAX_ORDERS];
User users[MAX_USERS];

int menuCount = 0, orderCount = 0, userCount = 0;
char adminUsername[] = "admin";
char adminPassword[] = "admin";
int accounts = 0;
int totalAccounts = 0;  

void addMenuItem(int id, char name[], float price, int stock)
{
    menu[menuCount].id = id;
    strcpy(menu[menuCount].name, name);
    menu[menuCount].price = price;
    menu[menuCount].stock = stock;
    menuCount++;
}

void displayMenu()
{
    printf("\n\n\n\n\n\n==========================================================\n");
    printf("||                  Resturent Menu                      ||\n");
    printf("==========================================================\n");
    // printf("||------------------------------------------------------||\n");
    for (int i = 0; i < menuCount; i++)
    {
        printf("[%d] %s - %.2f TAKA (Stock: %d)\n", menu[i].id, menu[i].name, menu[i].price, menu[i].stock);
    }

}


void processPayment(int paymentMethod, float totalPrice)
{
    switch (paymentMethod)
    {
    case 1:
        printf("Payment received via Bkash: %.2f Taka\n", totalPrice);
        break;
    case 2:
        printf("Payment received via Nogod: %.2f Taka\n", totalPrice);
        break;
    case 3:
        printf("Payment will be done after Delivery: %.2f Taka\n", totalPrice);
        break;
    case 4:
        printf("Payment received via VBank Card: %.2f Taka\n", totalPrice);
        break;
    default:
        printf("Invalid payment method selected.\n");
    }
}

void placeOrder(int orderId, int itemId, int quantity, int paymentMethod)
{
    if (itemId < 1 || itemId > menuCount || quantity > menu[itemId - 1].stock)
    {
        printf("Invalid order or insufficient stock!\n");
        return;
    }

    float totalPrice = menu[itemId - 1].price * quantity;

    processPayment(paymentMethod, totalPrice);

    orders[orderCount].orderId = orderId;
    orders[orderCount].itemId = itemId;
    orders[orderCount].quantity = quantity;
    orders[orderCount].totalPrice = totalPrice;
    orders[orderCount].paymentMethod = paymentMethod;

    menu[itemId - 1].stock -= quantity;
    orderCount++;

    printf("----------------------------------------------------------\n");
    printf("                Order placed successfully!                \n");
    printf("----------------------------------------------------------\n");
}

void displayOrders()
{
    printf("\n\n\n\n\n\n==========================================================\n");
    printf("||                    Orders List                       ||\n");
    printf("----------------------------------------------------------\n");
    if (orderCount == 0)
    {
        printf("No orders placed yet!\n");
        return;
    }
    for (int i = 0; i < orderCount; i++)
    {
        printf("Order ID: %d | Item: %s | Quantity: %d | Total: $%.2f | Payment: ",
               orders[i].orderId, menu[orders[i].itemId - 1].name, orders[i].quantity, orders[i].totalPrice);

        switch (orders[i].paymentMethod)
        {
        case 1:
            printf("Bkash\n");
            break;
        case 2:
            printf("Nogod\n");
            break;
        case 3:
            printf("Cash on Delivery\n");
            break;
        case 4:
            printf("VBank Card\n");
            break;
        default:
            printf("Unknown\n");
        }
    }
    printf("==========================================================\n");
}

void generateBill(int orderId)
{
    int found = 0;
    for (int i = 0; i < orderCount; i++)
    {
        if (orders[i].orderId == orderId)
        {
            found = 1;
            printf("\n\n\n\n\n\n----------------------------------------------------------\n");
            printf("                   Bill for Order ID: %d                 \n", orders[i].orderId);
            printf("----------------------------------------------------------\n");
            printf("(1) Item: %s\n", menu[orders[i].itemId - 1].name);
            printf("(2) Quantity: %d\n", orders[i].quantity);
            printf("(3) Price per Item: $%.2f\n", menu[orders[i].itemId - 1].price);
            printf("(4) Total Price: $%.2f\n", orders[i].totalPrice);

            printf("Payment Method: ");
            switch (orders[i].paymentMethod)
            {
            case 1:
                printf("Bkash\n");
                break;
            case 2:
                printf("Nogod\n");
                break;
            case 3:
                printf("Cash on Delivery\n");
                break;
            case 4:
                printf("VBank Card\n");
                break;
            default:
                printf("Unknown\n");
            }
            printf("----------------------------------------------------------\n");
            break;
        }
    }

    if (!found)
    {
        printf("----------------------------------------------------------\n");
        printf("                 Order ID %d not found!\n", orderId);     
        printf("----------------------------------------------------------\n");
    }
}

void registerUser()
{
    if (userCount >= MAX_USERS)
    {
        printf("Sorry, user registration is full!\n");
        return;
    }

    char username[50], password[50];
    printf("\n\n\n\n\n\n==========================================================\n");
    printf("||                   Register Page                      ||\n");
    printf("==========================================================\n");
    printf("Enter a new username: ");
    scanf("%s", username);
    printf("Enter a new password: ");
    scanf("%s", password);

    strcpy(users[userCount].username, username);
    strcpy(users[userCount].password, password);
    userCount++;

    printf("----------------------------------------------------------\n");
    printf("   Registration successful! You can now Log-in or Exit.   \n");
    printf("----------------------------------------------------------\n");
}

int loginUser()
{
    char username[50], password[50];
    printf("\n\n\n\n\n\n==========================================================\n");
    printf("||                    Login Page                        ||\n");
    printf("==========================================================\n");
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    for (int i = 0; i < userCount; i++)
    {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0)
        {
            printf("----------------------------------------------------------\n");
            printf("                    Login successful!                     \n");
            printf("----------------------------------------------------------\n");
            return 1;
        }
    }

    printf("Login failed. Invalid username or password.\n");
    return 0;
}

int adminLogin()
{
    char username[50], password[50];
    printf("\n\n\n\n\n\n==========================================================\n");
    printf("||                  Admin Login Page                    ||\n");
    printf("==========================================================\n");
    printf("Enter admin username: ");
    scanf("%s", username);
    printf("Enter admin password: ");
    scanf("%s", password);

    if (strcmp(username, adminUsername) == 0 && strcmp(password, adminPassword) == 0)
    {
        printf("----------------------------------------------------------\n");
        printf("                  Admin login successful!                 \n");
        printf("----------------------------------------------------------\n");
        return 1;
    }
    else
    {
        printf("Admin login failed. Invalid credentials.\n");
        return 0;
    }
}

void adminOperations()
{  
    int choice;
    while (1)
    {
        printf("\n\n\n\n\n\n==========================================================\n");
        printf("||                 Admin Operations                     ||\n");
        printf("||------------------------------------------------------||\n");
        printf("|| [1] Add Menu Item                                    ||\n");
        printf("|| [2] Display Orders                                   ||\n");
        printf("|| [3] View Menu                                        ||\n");
        printf("|| [4] Logout                                           ||\n");
        printf("==========================================================\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
        {
            int id, stock;
            char name[50];
            float price;
            printf("\n\n\n\n\n\n==========================================================\n");
            printf("||             Add new Item Information                 ||\n");
            printf("==========================================================\n");
            printf("Enter Item ID: ");
            scanf("%d", &id);
            printf("Enter Item Name: ");
            scanf("%s", name);
            printf("Enter Item Price(Taka): ");
            scanf("%f", &price);
            printf("Enter Item Stock: ");
            scanf("%d", &stock);
            printf("----------------------------------------------------------\n");
            printf("                      Add Sueccessfull                    \n");
            printf("----------------------------------------------------------\n");
            addMenuItem(id, name, price, stock);
            break;
        }
        case 2:
            displayOrders();
            break;
        case 3:
            displayMenu();
            break;
        case 4:
            printf("----------------------------------------------------------\n");
            printf("                     Admin logged out!                    \n");
            printf("----------------------------------------------------------\n");
            return;
        default:
            printf("Invalid choice, please try again.\n");
        }
    }
}

void loggedInOperations()
{
    int choice, orderId, itemId, quantity, paymentMethod;
    while (1)
    {
        printf("\n\n\n\n\n\n==========================================================\n");
        printf("||                       Home                           ||\n");
        printf("||------------------------------------------------------||\n");
        printf("|| [1] Display Menu                                     ||\n");
        printf("|| [2] Place Order                                      ||\n");
        printf("|| [3] Generate Bill                                    ||\n");
        printf("|| [4] Logout                                           ||\n");
        printf("==========================================================\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            displayMenu();
            break;
        case 2:
            printf("\n\n\n\n\n\n==========================================================\n");
            printf("||                Order Information                     ||\n");
            printf("==========================================================\n");
            printf("Enter Order ID: ");
            scanf("%d", &orderId);
            printf("Enter Item ID: ");
            scanf("%d", &itemId);
            printf("Enter Quantity: ");
            scanf("%d", &quantity);
            printf("Enter Payment Method (1-Bkash, 2-Nogod, 3-Cash on delivery, 4-VBank): ");
            scanf("%d", &paymentMethod);
            placeOrder(orderId, itemId, quantity, paymentMethod);
            break;
        case 3:
            printf("\n\n\n\n\n\n==========================================================\n");
            printf("||                   Bill Receipt                       ||\n");
            printf("==========================================================\n");
            printf("Enter Order ID to generate the bill: ");
            scanf("%d", &orderId);
            generateBill(orderId);
            break;
        case 4:
            printf("----------------------------------------------------------\n");
            printf("                  Logged out successfully!                \n");
            printf("----------------------------------------------------------\n");
            return; 
        default:
            printf("Invalid choice! Please try again.\n");
            break;
        }
    }
}

int main()
{
    int choice, loggedIn = 0, isAdmin = 0;

    addMenuItem(1, "Pizza", 10.99, 10);
    addMenuItem(2, "Burger", 5.49, 15);
    addMenuItem(3, "Pasta", 7.99, 8);
    addMenuItem(4, "Salad", 4.99, 12);

    SetConsoleOutputCP(CP_UTF8);
 
    printf("\n");
    printf("██╗  ██╗  █████╗    ███╗ ███╗     ███╗   ███╗  █████╗  ███╗   ██╗\n");
    printf("██║  ██║ ██╔══██╗  ████║ ████╗    ████╗ ████║ ██╔══██╗ ████╗  ██║\n"); 
    printf("███████║ ███████║ ██╔██║ ██ ██╗   ██╔████╔██║ ███████║ ██╔██╗ ██║\n");
    printf("██╔══██║ ██╔══██║ ██║ ████║ ██║   ██║╚██╔╝██║ ██╔══██║ ██║╚██╗██║\n");
    printf("██║  ██║ ██║  ██║ ██║  ██╔╝ ██║   ██║ ╚═╝ ██║ ██║  ██║ ██║ ╚████║\n");
    printf("╚═╝  ╚═╝ ╚═╝  ╚═╝ ╚═╝  ╚═╝  ╚═╝    ╚═╝    ╚═╝ ╚═╝  ╚═╝ ╚═╝  ╚═══╝\n");
    printf("\n");       

    void saveAccounts();
    void loadAccounts();  

    while (1)
    {
        printf("\n\n\n==========================================================\n");
        printf("||                WELCOME TO THE HAM MAN                ||\n");
        printf("||------------------------------------------------------||\n");
        printf("|| [1] Register                                         ||\n");
        printf("|| [2] Login                                            ||\n");
        printf("|| [3] Admin Login                                      ||\n");
        printf("|| [4] Exit                                             ||\n");
        printf("||                                                      ||\n");
        printf("||       Wishing you a good time with  HAM MAN          ||\n");
        printf("==========================================================\n");

        printf("Choose an option: ");
        scanf("%d", &choice);

        if (choice == 1)
        {
            registerUser();
        }
        else if (choice == 2)
        {
            loggedIn = loginUser();
            if (loggedIn)
            {
                loggedInOperations(); // After successful login, call loggedInOperations
            }
        }
        else if (choice == 3)
        {
            isAdmin = adminLogin();
            if (isAdmin)
            {
                adminOperations();
            }
        }
        else if (choice == 4)
        {
            printf("\n\n\n\n\n\n==========================================================\n");
            printf("||                      Thank You!                      ||\n");
            printf("||                 For Visting    HAM MAN               ||\n");
            printf("==========================================================\n");
            break; // Exit the program
        }
        else
        {
            printf("Invalid choice! Try again.\n");
        }
    }
    return 0;
}
