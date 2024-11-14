#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // For sleep function

// Structure for user accounts
struct User {
    int accountNumber;
    char name[100];
    char password[50];
    double balance;
    char depositHistory[100][50];
    char transferHistory[100][50];
    int depositCount;
    int transferCount;
};

// Structure for admin
struct Admin {
    char adminName[100];
    char adminPassword[50];
};

// Function prototypes
void adminMenu(struct Admin admins[], int *numAdmins);
void userMenu(struct User users[], int *numUsers);
void adminLogin(struct Admin admins[], int numAdmins);
void adminSignUp(struct Admin admins[], int *numAdmins);
void userLogin(struct User users[], int numUsers);
void userSignUp(struct User users[], int *numUsers);
void userInterface(struct User *user);
void adminInterface();
void viewBalance(struct User *user);
void depositMoney(struct User *user);
void transferMoney(struct User users[], int numUsers, struct User *user);
void investMoney(struct User *user);
void viewTransactionHistory(struct User *user);
void logTransaction(struct User *user, const char *transactionDetails, char *transactionType);

// Constants
#define SYSTEM_IDENTITY 24115

int main() {
    struct User users[100];
    struct Admin admins[10];
    int numUsers = 0;
    int numAdmins = 0;
    int choice;

    while (1) {
        printf("\nWe Welcome You to Innovest \n");
        printf("1. Admin Login/Sign Up\n");
        printf("2. User Login/Sign Up\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                adminMenu(admins, &numAdmins);
                break;
            case 2:
                userMenu(users, &numUsers);
                break;
            case 3:
                printf("Thank you for using Innovest. Assalamualaikum!\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}

// Admin menu function
void adminMenu(struct Admin admins[], int *numAdmins) {
    int choice;
    printf("\nAdmin Menu\n");
    printf("1. Login as Admin\n");
    printf("2. Sign Up as New Admin\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            adminLogin(admins, *numAdmins);
            break;
        case 2:
            adminSignUp(admins, numAdmins);
            break;
        default:
            printf("Invalid choice. Returning to main menu.\n");
    }
}

// Admin login function
void adminLogin(struct Admin admins[], int numAdmins) {
    char name[100];
    char password[50];
    printf("Enter admin name: ");
    scanf("%s", name);
    printf("Enter password: ");
    scanf("%s", password);

    for (int i = 0; i < numAdmins; i++) {
        if (strcmp(admins[i].adminName, name) == 0 && strcmp(admins[i].adminPassword, password) == 0) {
            printf("Login successful. Welcome, %s!\n", name);
            adminInterface();
            return;
        }
    }
    printf("Invalid credentials.\n");
}

// Admin sign-up function
void adminSignUp(struct Admin admins[], int *numAdmins) {
    struct Admin newAdmin;
    printf("Enter admin name: ");
    scanf("%s", newAdmin.adminName);
    printf("Enter password: ");
    scanf("%s", newAdmin.adminPassword);

    admins[*numAdmins] = newAdmin;
    (*numAdmins)++;
    printf("Admin account created successfully.\n");
}

// Admin interface function
void adminInterface() {
    int choice;
    do {
        printf("\nAdmin Panel - Manage System\n");
        printf("1. View all user data (to be implemented)\n");
        printf("2. Manage accounts (to be implemented)\n");
        printf("3. Exit to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Feature to view all user data (to be added)\n");
                break;
            case 2:
                printf("Feature to manage accounts (to be added)\n");
                break;
            case 3:
                printf("Returning to main menu...\n");
                return;
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 3);
}

// User menu function
void userMenu(struct User users[], int *numUsers) {
    int choice;
    printf("\nUser Menu\n");
    printf("1. Login as User\n");
    printf("2. Sign Up as New User\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            userLogin(users, *numUsers);
            break;
        case 2:
            userSignUp(users, numUsers);
            break;
        default:
            printf("Invalid choice. Returning to main menu.\n");
    }
}

// User login function
void userLogin(struct User users[], int numUsers) {
    int accountNumber;
    char password[50];

    printf("Enter your account number: ");
    scanf("%d", &accountNumber);
    printf("Enter password: ");
    scanf("%s", password);

    for (int i = 0; i < numUsers; i++) {
        if (users[i].accountNumber == accountNumber && strcmp(users[i].password, password) == 0) {
            printf("Login successful. Welcome, %s!\n", users[i].name);
            userInterface(&users[i]);
            return;
        }
    }
    printf("Invalid credentials.\n");
}

// User sign-up function
void userSignUp(struct User users[], int *numUsers) {
    struct User newUser;
    newUser.accountNumber = SYSTEM_IDENTITY * 1000 + (*numUsers + 1);
    printf("Enter your name: ");
    scanf("%s", newUser.name);
    printf("Enter password: ");
    scanf("%s", newUser.password);
    newUser.balance = 0.0;
    newUser.depositCount = 0;
    newUser.transferCount = 0;

    users[*numUsers] = newUser;
    (*numUsers)++;
    printf("Welcome To Innovest Family! Your account number is %d\n", newUser.accountNumber);
}

// Function to display user interface
void userInterface(struct User *user) {
    int choice;
    do {
        printf("\nInnovest At Your Service - %s\n", user->name);
        printf("1. View Balance\n");
        printf("2. Deposit Money\n");
        printf("3. Transfer Money\n");
        printf("4. Invest Money\n");
        printf("5. View Transaction History\n");
        printf("6. Exit to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                viewBalance(user);
                break;
            case 2:
                depositMoney(user);
                break;
            case 3:
                // The transfer function needs the full list of users to check the recipient
                transferMoney(NULL, 0, user);
                break;
            case 4:
                investMoney(user);
                break;
            case 5:
                viewTransactionHistory(user);
                break;
            case 6:
                printf("Returning to main menu...\n");
                return;
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 6);
}

// Function to view balance
void viewBalance(struct User *user) {
    printf("Current balance: $%.2f\n", user->balance);
}

// Function to deposit money with verification
void depositMoney(struct User *user) {
    double amount;
    printf("Enter the amount to deposit: $");
    scanf("%lf", &amount);
    if (amount > 0) {
        printf("Please wait for verification...\n");
        for (int i = 3; i > 0; i--) {
            printf("%d...\n", i);
            sleep(1);
        }
        user->balance += amount;
        printf("Deposit successful. New balance: $%.2f\n", user->balance);
        logTransaction(user, "Deposit", "deposit");
        sleep(3); // Delay after deposit
    } else {
        printf("Invalid amount. Please try again.\n");
    }
}

// Function to transfer money
void transferMoney(struct User users[], int numUsers, struct User *user) {
    int recipientAccount;
    double amount;

    printf("Enter recipient account number: ");
    scanf("%d", &recipientAccount);
    printf("Enter the amount to transfer: $");
    scanf("%lf", &amount);

    if (amount <= 0 || amount > user->balance) {
        printf("Invalid amount. Please try again.\n");
        return;
    }

    for (int i = 0; i < numUsers; i++) {
        if (users[i].accountNumber == recipientAccount) {
            user->balance -= amount;
            users[i].balance += amount;
            printf("Transfer successful. New balance: $%.2f\n", user->balance);
            logTransaction(user, "Transfer", "transfer");
            return;
        }
    }
    printf("Recipient account not found.\n");
}


// Function to invest money with verification and investment options
void investMoney(struct User *user) {
    double amount;
    int choice;

    printf("To invest, you need to pay a fee of $200.\n");
    printf("Please wait for verification...\n");
    for (int i = 3; i > 0; i--) {
        printf("%d...\n", i);
        sleep(1);
    }

    printf("\nToday's Investment Options:\n");
    printf("1. Tech Company A\n");
    printf("2. Tech Company B\n");
    printf("3. Tech Company C\n");
    printf("4. Tech Company D\n");
    printf("5. Tech Company E\n");

    printf("Please choose your desired investment option: ");
    scanf("%d", &choice);

    // Handle investment options with a switch statement
    switch (choice) {
        case 1:
            printf("You have selected to invest in Tech Company A.\n");
            break;
        case 2:
            printf("You have selected to invest in Tech Company B.\n");
            break;
        case 3:
            printf("You have selected to invest in Tech Company C.\n");
            break;
        case 4:
            printf("You have selected to invest in Tech Company D.\n");
            break;
        case 5:
            printf("You have selected to invest in Tech Company E.\n");
            break;
        default:
            printf("Invalid option selected. Returning to the main menu.\n");
            return;
    }

    // Prompt the user for the investment amount
    printf("Enter the amount to invest (excluding the fee): $");
    scanf("%lf", &amount);

    if (amount <= 0 || (amount + 200) > user->balance) {
        printf("Invalid amount. Please try again.\n");
        return;
    }

    // Deduct the investment amount and fee
    user->balance -= (amount + 200);

    printf("Investment successful. Total amount deducted (including fee): $%.2f. New balance: $%.2f\n", amount + 200, user->balance);
    logTransaction(user, "Investment", "investment");
}


// Function to view transaction history
void viewTransactionHistory(struct User *user) {
    printf("\nDeposit History:\n");
    for (int i = 0; i < user->depositCount; i++) {
        printf("%s\n", user->depositHistory[i]);
    }
    printf("\nTransfer History:\n");
    for (int i = 0; i < user->transferCount; i++) {
        printf("%s\n", user->transferHistory[i]);
    }
}

// Function to log a transaction
void logTransaction(struct User *user, const char *transactionDetails, char *transactionType) {
    if (strcmp(transactionType, "deposit") == 0) {
        snprintf(user->depositHistory[user->depositCount++], 50, "%s - $%.2f", transactionDetails, user->balance);
    } else if (strcmp(transactionType, "transfer") == 0) {
        snprintf(user->transferHistory[user->transferCount++], 50, "%s - $%.2f", transactionDetails, user->balance);
    }
    printf("Transaction logged: %s for %s\n", transactionDetails, user->name);
}
