#include <stdio.h>
#include <stdlib.h>

#define MAX_ACCOUNTS 100

typedef struct 
{
    int accountNumber;
    char accountHolder[100];
    double balance;
} Account;

void createAccount();
void deposit();
void withdraw();
void viewAccountDetails();
void atmTransaction();
void displayAllAccounts();
void deleteAccount();

int main() 
{
    int choice;

    do {
        printf("\nBank Management System and ATM");
        printf("\n------------------------------");
        printf("\n1. Create Account");
        printf("\n2. Deposit Money");
        printf("\n3. Withdraw Money");
        printf("\n4. View Account Details");
        printf("\n5. Perform ATM Transaction");
        printf("\n6. Display All Accounts");
        printf("\n7. Delete an Account");
        printf("\n0. Exit");
        printf("\n\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) 
		{
            case 1:
                createAccount();
                break;
            case 2:
                deposit();
                break;
            case 3:
                withdraw();
                break;
            case 4:
                viewAccountDetails();
                break;
            case 5:
                atmTransaction();
                break;
            case 6:
                displayAllAccounts();
                break;
            case 7:
                deleteAccount();
                break;
            case 0:
                printf("\nExiting the program. Goodbye!\n");
                break;
            default:
                printf("\nInvalid choice. Please try again.\n");
                break;
        }
    } while (choice != 0);

    return 0;
}

void createAccount() 
{
    Account account;
    FILE *file;

    file = fopen("accounts.dat", "ab");
    if (file == NULL) {
        printf("\nFailed to open file. Please try again.\n");
        return;
    }

    printf("\nCreating a New Account");
    printf("\n----------------------");
    printf("\nEnter Account Number: ");
    scanf("%d", &account.accountNumber);

    printf("Enter Account Holder Name: \n");
    scanf(" %[^\n]s", account.accountHolder);

    printf("Enter Initial Balance: ");
    scanf("%lf", &account.balance);

    fwrite(&account, sizeof(Account), 1, file);

    printf("\nAccount created successfully!\n");

    fclose(file);
}

void deposit() 
{
    int accountNumber;
    double amount;
    FILE *file;
    Account account;

    file = fopen("accounts.dat", "rb+");
    if (file == NULL) 
	{
        printf("\nFailed to open file. Please try again.\n");
        return;
    }

    printf("\nDeposit Money");
    printf("\n-------------");
    printf("\nEnter Account Number: ");
    scanf("%d", &accountNumber);

    while (fread(&account, sizeof(Account), 1, file) == 1) 
	{
        if (account.accountNumber == accountNumber) 
		{
            printf("Enter Amount to Deposit: ");
            scanf("%lf", &amount);

            account.balance += amount;

            fseek(file, -sizeof(Account), SEEK_CUR);
            fwrite(&account, sizeof(Account), 1, file);

            printf("\nDeposit successful!\n");
            fclose(file);
            return;
        }
    }

    printf("\nAccount not found. Please try again.\n");
    fclose(file);
}

void withdraw() 
{
    int accountNumber;
    double amount;
    FILE *file;
    Account account;

    file = fopen("accounts.dat", "rb+");
    if (file == NULL) 
	{
        printf("\nFailed to open file. Pleasetry again.\n");
return;
}

printf("\nWithdraw Money");
printf("\n--------------");
printf("\nEnter Account Number: ");
scanf("%d", &accountNumber);

while (fread(&account, sizeof(Account), 1, file) == 1) 
{
    if (account.accountNumber == accountNumber) 
	{
        printf("Enter Amount to Withdraw: ");
        scanf("%lf", &amount);

        if (account.balance >= amount) 
		{
            account.balance -= amount;

            fseek(file, -sizeof(Account), SEEK_CUR);
            fwrite(&account, sizeof(Account), 1, file);

            printf("\nWithdrawal successful!\n");
            fclose(file);
            return;
        } else {
            printf("\nInsufficient balance. Cannot withdraw.\n");
            fclose(file);
            return;
        }
    }
}

printf("\nAccount not found. Please try again.\n");
fclose(file);
}

void viewAccountDetails() 
{
int accountNumber;
FILE *file;
Account account;
file = fopen("accounts.dat", "rb");
if (file == NULL) {
    printf("\nFailed to open file. Please try again.\n");
    return;
}

printf("\nView Account Details");
printf("\n--------------------");
printf("\nEnter Account Number: ");
scanf("%d", &accountNumber);

while (fread(&account, sizeof(Account), 1, file) == 1) 
{
    if (account.accountNumber == accountNumber) 
	{
        printf("\nAccount Number: %d", account.accountNumber);
        printf("\nAccount Holder: %s", account.accountHolder);
        printf("\nBalance: $%.2lf\n", account.balance);

        fclose(file);
        return;
    }
}

printf("\nAccount not found. Please try again.\n");
fclose(file);
}

void atmTransaction() 
{
int accountNumber;
double amount;
FILE *file;
Account account;
file = fopen("accounts.dat", "rb+");
if (file == NULL) {
    printf("\nFailed to open file. Please try again.\n");
    return;
}

printf("\nATM Transaction");
printf("\n---------------");
printf("\nEnter Account Number: ");
scanf("%d", &accountNumber);

while (fread(&account, sizeof(Account), 1, file) == 1) 
{
    if (account.accountNumber == accountNumber) 
	{
        printf("Enter Amount: ");
        scanf("%lf", &amount);

        if (account.balance >= amount) 
		{
            account.balance -= amount;

            fseek(file, -sizeof(Account), SEEK_CUR);
            fwrite(&account, sizeof(Account), 1, file);

            printf("\nTransaction successful!\n");
            fclose(file);
            return;
        } else 
		{
            printf("\nInsufficient balance. Transaction failed.\n");
            fclose(file);
            return;
        }
    }
}

printf("\nAccount not found. Please try again.\n");
fclose(file);
}

void displayAllAccounts() 
{
FILE *file;
Account account;
file = fopen("accounts.dat", "rb");
if (file == NULL) 
{
    printf("\nFailed to open file. Please try again.\n");
    return;
}

printf("\nAll Accounts\n");
printf("------------\n");

while (fread(&account, sizeof(Account), 1, file) == 1) 
{
    printf("Account Number: %d\n", account.accountNumber);
    printf("Account Holder: %s\n", account.accountHolder);
    printf("Balance: $%.2lf\n\n", account.balance);
}

fclose(file);
}

void deleteAccount() 
{
int accountNumber;
FILE *file, *tempFile;
Account account;
file = fopen("accounts.dat", "rb");
if (file == NULL) {
    printf("\nFailed to open file. Please try again.\n");
    return;
}

tempFile = fopen("temp.dat", "wb");
if (tempFile == NULL) 
{
    printf("\nFailed to create temporary file. Please try again.\n");
    fclose(file);
    return;
}

printf("\nDelete an Account");
printf("\n-----------------");
printf("\nEnter Account Number: ");
scanf("%d", &accountNumber);

int accountFound = 0;

while (fread(&account, sizeof(Account), 1, file) == 1) 
{
    if (account.accountNumber == accountNumber) 
	{
        accountFound = 1;
        continue;
    }

    fwrite(&account, sizeof(Account), 1, tempFile);
}

fclose(file);
fclose(tempFile);

if (remove("accounts.dat") != 0) 
{
    printf("\nFailed to delete account. Please try again.\n");
    return;
}

if (rename("temp.dat", "accounts.dat") != 0) 
{
    printf("\nFailed to delete account. Please try again.\n");
    return;
}

if (accountFound) 
{
    printf("\nAccount deleted successfully!\n");
} else {
    printf("\nAccount not found. Please try again.\n");
}
}

