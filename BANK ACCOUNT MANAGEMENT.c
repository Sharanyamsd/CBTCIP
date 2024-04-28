#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ACCOUNTS 10

typedef enum {
    SAVINGS,
    CURRENT
} AccountType;

typedef struct {
    int id;
    char name[100];
    double balance;
    AccountType type;
} Account;

void create_account(Account accounts[], int *num_accounts);
void deposit(Account accounts[], int num_accounts);
void withdraw(Account accounts[], int num_accounts);
void check_balance(Account accounts[], int num_accounts);
void calculate_interest(Account accounts[], int num_accounts);

int main() {
    Account accounts[MAX_ACCOUNTS];
    int num_accounts = 0;
    int choice;

    printf("Welcome to the banking system\n");

    while (1) {
        printf("\n1. Create account\n2. Deposit\n3. Withdraw\n4. Check Balance\n5. Calculate Interest\n6. Exit\n\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                create_account(accounts, &num_accounts);
                break;
            case 2:
                deposit(accounts, num_accounts);
                break;
            case 3:
                withdraw(accounts, num_accounts);
                break;
            case 4:
                check_balance(accounts, num_accounts);
                break;
            case 5:
                calculate_interest(accounts, num_accounts);
                break;
            case 6:
                printf("Exiting program...\n");
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}

void create_account(Account accounts[], int *num_accounts) {
    if (*num_accounts == MAX_ACCOUNTS) {
        printf("Maximum number of accounts reached\n");
        return;
    }

    Account account;
    account.id = *num_accounts + 1;

    printf("Enter account name: ");
    scanf("%s", account.name);

    printf("Enter initial balance: ");
    scanf("%lf", &account.balance);

    printf("Enter account type (0 for Savings, 1 for Current): ");
    int type_choice;
    scanf("%d", &type_choice);
    if (type_choice == 0) {
        account.type = SAVINGS;
    } else if (type_choice == 1) {
        account.type = CURRENT;
    } else {
        printf("Invalid account type choice\n");
        return;
    }

    accounts[*num_accounts] = account;
    (*num_accounts)++;

    printf("Account created with ID %d\n", account.id);
}

void deposit(Account accounts[], int num_accounts) {
    int id,i;
    double amount;

    printf("Enter account ID: ");
    scanf("%d", &id);

    for ( i = 0; i < num_accounts; i++) {
        if (accounts[i].id == id) {
            printf("Enter deposit amount: ");
            scanf("%lf", &amount);

            accounts[i].balance += amount;

            printf("Deposit successful. New balance:Rs %.2lf \n", accounts[i].balance);
            return;
        }
    }

    printf("Account not found\n");
}

void withdraw(Account accounts[], int num_accounts) {
    int id,i;
    double amount;

    printf("Enter account ID: ");
    scanf("%d", &id);

    for (i = 0; i < num_accounts; i++) {
        if (accounts[i].id == id) {
            printf("Enter withdrawal amount: ");
            scanf("%lf", &amount);

            if (amount > accounts[i].balance) {
                printf("Insufficient funds\n");
                return;
            }

            accounts[i].balance -= amount;

            printf("Withdrawal successful. New balance:Rs %.2lf \n", accounts[i].balance);
            return;
        }
    }

    printf("Account not found\n");
}



void check_balance(Account accounts[], int num_accounts) {
    int id,i;
    printf("Enter account ID to check balance: ");
    scanf("%d", &id);

    for ( i = 0; i < num_accounts; i++) {
        if (accounts[i].id == id) {
            printf("Balance for account %d:Rs %.2lf \n", accounts[i].id, accounts[i].balance);
            return;
        }
    }

    printf("Account not found\n");
}

void calculate_interest(Account accounts[], int num_accounts) {
	int i;
    for (i = 0; i < num_accounts; i++) {
        double interest_rate;
        if (accounts[i].type == SAVINGS) {
            interest_rate = 0.07; // 7.00% interest rate for savings account
        } else if (accounts[i].type == CURRENT) {
            interest_rate = 0.04; // 4.00% interest rate for current account
        }
        double interest = accounts[i].balance * interest_rate;
        accounts[i].balance += interest;
        printf("Interest calculated for account %d:Rs %.2lf \n", accounts[i].id, interest);
        printf("New balance for account %d:Rs %.2lf \n", accounts[i].id, accounts[i].balance);
    }
}
