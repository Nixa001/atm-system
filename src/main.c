#include "header.h"

void mainMenu(struct User u)
{
    int option;
    int accountNum;
    char checkInput[50];
    int commandNum;
    char ownerName[100];
    system("clear");
    printf("\n\n\t\t\t\t======= ATM =======\n\n");
    printf("\n\t\t-->> Feel free to choose one of the options below <<--\n");
    printf("\n\t\t[1]- Create a new account\n");
    printf("\n\t\t[2]- Update account information\n");
    printf("\n\t\t[3]- Check accounts\n");
    printf("\n\t\t[4]- Check list of owned account\n");
    printf("\n\t\t[5]- Make Transaction\n");
    printf("\n\t\t[6]- Remove existing account\n");
    printf("\n\t\t[7]- Transfer ownership\n");
    printf("\n\t\t[8]- Exit\n");
    scanf("%d", &option);

    switch (option)
    {
    case 1:
        createNewAcc(u);
        break;
    case 2:
    // student TODO : add your **Update account information** function
    account:
        printf("\t\tAccount number:");
        // scanf("%d", &accountNum);

        scanf("%s", checkInput);
        if (!isNumber(checkInput))
        {
            printf("\n\t\t❌Invalid\n");
            goto account;
        }
        accountNum = atoi(checkInput);
        if (!isValidAccountNumber(accountNum, u))
        {
            system("clear");
            printf("\t\t❌ This account don't exist.");
            mainMenu(u);
        }
        printf("\n\t\tWhich information do you want to update?\n\t\t1-> phone number\n\t\t2-> country\n");
        scanf("%d", &commandNum);
        updateAccountInfo(u, accountNum, commandNum);

        break;
    case 3:
        // student TODO : add your **Check the details of existing accounts** function
        printf("\t\tEnter the account number:");
        scanf("%s", checkInput);
        if (!isNumber(checkInput))
        {
            printf("\n\t\t❌Invalid\n");
            goto account;
        }
        accountNum = atoi(checkInput);
        if (!isValidAccountNumber(accountNum, u))
        {
            system("clear");
            printf("\t\t❌This account don't exist.");
            mainMenu(u);
        }
        checkDetailAcc(u, accountNum);
        break;
    case 4:
        checkAllAccounts(u);
        break;
    case 5:
    // student TODO : add your **Make transaction** function
    account1:
        printf("\t\tEnter the account number of the customer:");
        // scanf("%d", &accountNum);

        scanf("%s", checkInput);
        if (!isNumber(checkInput))
        {
            printf("\n\t\t❌Invalid\n");
            goto account1;
        }
        accountNum = atoi(checkInput);
        if (!isValidAccountNumber(accountNum, u))
        {
            system("clear");
            printf("\n\t\t❌This account don't exist.");
            mainMenu(u);
        }
        printf("\t\tDo you want to:\n\t\t\t1-> Withdraw\n\t\t\t2-> Deposit\n\n");
        printf("\t\tEnter your choice:");
        scanf("%d", &commandNum);
        makeTransaction(u, accountNum, commandNum);
        break;
    case 6:
    // student TODO : add your **Remove existing account** function
    remove:
        printf("\t\tEnter the account number you want to delete:");
        // scanf("%d", &accountNum);

        scanf("%s", checkInput);
        if (!isNumber(checkInput))
        {
            printf("\n\t\t❌Invalid\n");
            goto remove;
        }
        accountNum = atoi(checkInput);
        if (!isValidAccountNumber(accountNum, u))
        {
            system("clear");
            printf("\n\t\t❌This account don't exist.");
            mainMenu(u);
        }
        removeAccount(u, accountNum);
        break;
    case 7:
    // student TODO : add your **Transfer owner** function
    transfer:
        printf("\t\tEnter the account number you want to transfere ownership:");
        // scanf("%d", &accountNum);

        scanf("%s", checkInput);
        if (!isNumber(checkInput))
        {
            printf("\n\t\t❌Invalid\n");
            goto transfer;
        }
        accountNum = atoi(checkInput);
        if (!isValidAccountNumber(accountNum, u))
        {
            system("clear");
            printf("\n\t\t❌This account don't exist.");
            mainMenu(u);
        }
        transfereAccount(u, accountNum);
        break;
    case 8:
        exit(1);
        break;
    default:
        printf("\n\t\t❌Invalid operation!\n");
    }
};

void initMenu(struct User *u)
{
    int r = 0;
    int option;
    system("clear");
    printf("\n\n\t\t\t\t======= ATM =======\n");
    printf("\n\t\t-->> Feel free to login / register :\n");
    printf("\n\t\t[1]- login\n");
    printf("\n\t\t[2]- register\n");
    printf("\n\t\t[3]- exit\n");
    while (!r)
    {
        scanf("%d", &option);
        switch (option)
        {
        case 1:
            loginMenu(u->name, u->password);
            if (strcmp(u->password, getPassword(u)) == 0)
            {
                printf("\n\n\t\t\t\t✅Password Match!");
            }
            else
            {
                printf("\n\t\t\t\t❌Wrong password!! or User Name\n");
                exit(1);
            }
            r = 1;
            break;
        case 2:
            // student TODO : add your **Registration** function
            registerMenu(u->name, u->password);
            r = 1;
            break;
        case 3:
            exit(1);
            break;
        default:
            printf("\n\t\t❌ Insert a valid operation!\n");
        }
    }
};

int main()
{
    struct User u;

    initMenu(&u);
    mainMenu(u);
    return 0;
}
