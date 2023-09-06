#include "header.h"

const char *RECORDS = "./data/records.txt";
char checkInput[50];
int getAccountFromFile(FILE *ptr, char name[50], struct Record *r)
{
    return fscanf(ptr, "%d %d %s %d %d/%d/%d %s %d %lf %s",
                  &r->id,
                  &r->userId,
                  name,
                  &r->accountNbr,
                  &r->deposit.month,
                  &r->deposit.day,
                  &r->deposit.year,
                  r->country,
                  &r->phone,
                  &r->amount,
                  r->accountType) != EOF;
}

void saveAccountToFile(FILE *ptr, struct User u, struct Record r)
{
    fprintf(ptr, "%d %d %s %d %d/%d/%d %s %d %.2lf %s\n\n",
            r.id,
            u.id,
            u.name,
            r.accountNbr,
            r.deposit.month,
            r.deposit.day,
            r.deposit.year,
            r.country,
            r.phone,
            r.amount,
            r.accountType);
}

void saveRecordToFile(FILE *ptr, struct Record r)
{
    fprintf(ptr, "%d %d %s %d %d/%d/%d %s %d %.2lf %s\n\n",
            r.id,
            r.userId,
            r.name,
            r.accountNbr,
            r.deposit.month,
            r.deposit.day,
            r.deposit.year,
            r.country,
            r.phone,
            r.amount,
            r.accountType);
}

void stayOrReturn(int notGood, void f(struct User u), struct User u)
{
    int option;
    if (notGood == 0)
    {
        system("clear");
        printf("\n\t\t❌ Record not found!!\n");
    invalid:
        printf("\n\t\tEnter 0 to try again, 1 to return to main menu and 2 to exit:");
        scanf("%d", &option);

        if (option == 0)
            f(u);
        else if (option == 1)
            mainMenu(u);
        else if (option == 2)
            exit(0);
        else
        {
            printf("\t\t❌Insert a valid operation!\n");
            goto invalid;
        }
    }
    else
    {
        printf("\n\t\tEnter 1 to go to the main menu and 0 to exit:");
        scanf("%d", &option);
    }
    if (option == 1)
    {
        system("clear");
        mainMenu(u);
    }
    else
    {
        system("clear");
        exit(1);
    }
}

void success(struct User u)
{
    int option;
    printf("\n\t\t✅ Success!\n\n");
invalid:
    printf("\t\tEnter 1 to go to the main menu and 0 to exit!\n");
    scanf("%d", &option);
    system("clear");
    if (option == 1)
    {
        mainMenu(u);
    }
    else if (option == 0)
    {
        exit(1);
    }
    else
    {
        printf("\t\t❌Insert a valid operation!\n");
        goto invalid;
    }
}

void createNewAcc(struct User u)
{
    struct Record r;
    struct Record cr;
    char userName[50];
    FILE *pf = fopen(RECORDS, "a+");
    int value = 0;

noAccount:
    system("clear");
    printf("\t\t\t===== New record =====\n");

dateStage:
    printf("\n\t\tEnter today's date(mm/dd/yyyy):");
    scanf("%d/%d/%d", &r.deposit.month, &r.deposit.day, &r.deposit.year);
    // Read line && check space
    char input[100];
    fgets(input, sizeof(input), stdin);
    if (containSpace(input))
    {
        printf("\n\t\t\t\t❌ Space not allowed\n");
        goto dateStage;
    }

    if (r.deposit.month <= 0 || r.deposit.month > 12 ||
        r.deposit.day <= 0 || r.deposit.day > 31 ||
        r.deposit.year < 2000 || r.deposit.year > 2100)
    {
        printf("\t\t❌Invalid date.\n");
        goto dateStage;
    }

accountNumberStage:
    printf("\n\t\tEnter the account number:");
    // scanf("%d", &r.accountNbr);

    scanf("%s", checkInput);
    if (!isNumber(checkInput))
    {
        printf("\n\t\t❌Invalid\n");
        goto accountNumberStage;
    }
    r.accountNbr = atoi(checkInput);
    if (r.accountNbr <= 0)
    {
        printf("\t\t❌Invalid account number.\n");
        goto accountNumberStage;
    }
    // Read line && check space
    fgets(input, sizeof(input), stdin);
    if (containSpace(input))
    {
        printf("\n\t\t\t\t❌ Space not allowed\n");
        goto accountNumberStage;
    }

    while (getAccountFromFile(pf, userName, &cr))
    {
        if (strcmp(userName, u.name) == 0 && cr.accountNbr == r.accountNbr)
        {
            printf("\n\t\t❌ This Account already exists for this user\n\n");
            goto noAccount;
        }
        value++;
    }
country:
    r.id = value;
    printf("\n\t\tEnter the country:");
    scanf("%s", r.country);
    // Read line && check space
    fgets(input, sizeof(input), stdin);
    if (containSpace(input))
    {
        printf("\n\t\t\t\t❌ Space not allowed\n");
        goto country;
    }

phoneNbrStage:
    printf("\n\t\tEnter the phone number:");
    // scanf("%d", &r.phone);

    scanf("%s", checkInput);
    if (!isNumber(checkInput))
    {
        printf("\n\t\t❌Invalid\n");
        goto accountNumberStage;
    }
    r.phone = atoi(checkInput);
    if (r.phone <= 0)
    {
        printf("\t\t❌Invalid phone number.\n");
        goto phoneNbrStage;
    }

depositStage:
    printf("\n\t\tEnter amount to deposit: $");
    // scanf("%lf", &r.amount);
    scanf("%s", checkInput);
    fgets(input, sizeof(input), stdin);

    if (!isNumber(checkInput))
    {
        printf("\n\t\t❌Invalid\n");
        goto accountNumberStage;
    }
    r.amount = strtod(checkInput, NULL);
    if (containSpace(input))
    {
        printf("\n\t\t\t\t❌ Space not allowed\n");
        goto depositStage;
    }
    if (r.amount <= 0)
    {
        if (r.amount == 0)
        {
            printf("\t\t❌Invalid amount.\n");
        }
        else
        {
            printf("\n\t\t❌Too less or too many for account.\n");
        }
        goto depositStage;
    }
type:
    do
    {
        printf("\n\t\tChoose the type of account:\n\t\t-> saving\n\t\t-> current\n\t\t-> fixed01(for 1 year)\n\t\t-> fixed02(for 2 years)\n\t\t-> fixed03(for 3 years)\n\n\t\tEnter your choice:");
        scanf("%s", r.accountType);
        // Read line && check space
        fgets(input, sizeof(input), stdin);
        if (containSpace(input))
        {
            printf("\n\t\t\t\t❌ Space not allowed\n");
            goto type;
        }

        if (strcmp(r.accountType, "current") != 0 && strcmp(r.accountType, "saving") != 0 &&
            strcmp(r.accountType, "fixed01") != 0 && strcmp(r.accountType, "fixed02") != 0 &&
            strcmp(r.accountType, "fixed03") != 0)
        {
            printf("\n\t\t❌This type of account doesn't exist.\n");
        }
    } while (strcmp(r.accountType, "current") != 0 && strcmp(r.accountType, "saving") != 0 &&
             strcmp(r.accountType, "fixed01") != 0 && strcmp(r.accountType, "fixed02") != 0 &&
             strcmp(r.accountType, "fixed03") != 0);

    fprintf(pf, "\n");

    saveAccountToFile(pf, u, r);

    fclose(pf);
    success(u);
}

void checkAllAccounts(struct User u)
{
    char userName[100];
    struct Record r;

    FILE *pf = fopen(RECORDS, "r");

    system("clear");
    printf("\t\t====== All accounts from user, %s =====\n\n", u.name);
    while (getAccountFromFile(pf, userName, &r))
    {
        if (strcmp(userName, u.name) == 0)
        {
            printf("\t\t_____________________\n");
            printf("\n\t\tAccount number:%d\n\t\tDeposit Date:%d/%d/%d \n\t\tcountry:%s \n\t\tPhone number:%d \n\t\tAmount deposited: $%.2f \n\t\tType Of Account:%s\n",
                   r.accountNbr,
                   r.deposit.day,
                   r.deposit.month,
                   r.deposit.year,
                   r.country,
                   r.phone,
                   r.amount,
                   r.accountType);
        }
    }
    fclose(pf);
    success(u);
}

void checkDetailAcc(struct User u, int accountNum)
{
    char userName[100];
    struct Record r;
    FILE *pf = fopen(RECORDS, "r");

    system("clear");
    while (getAccountFromFile(pf, userName, &r))
    {
        if (strcmp(userName, u.name) == 0 &&
            r.accountNbr == accountNum)
        {
            printf("\n\t\tAccount number:%d\nDeposit Date:%d/%d/%d \ncountry:%s \nPhone number:%d \nAmount deposited: $%.2f \nType Of Account:%s\n",
                   r.accountNbr,
                   r.deposit.day,
                   r.deposit.month,
                   r.deposit.year,
                   r.country,
                   r.phone,
                   r.amount,
                   r.accountType);

            float rate;
            if (strcmp(r.accountType, "saving") == 0)
            {
                rate = 0.07;
                float interet = r.amount * (1 + rate / 12) - r.amount;
                printf(" -> You will get $%.2f as interest on day 10 of every month\n", interet);
            }
            else if (strcmp(r.accountType, "fixed01") == 0)
            {
                rate = 0.04;
                float interet = r.amount * (1 + rate / 12) - r.amount;
                interet *= 12;
                printf(" -> You will get $%.2f as interest on %d/%d/%d\n", interet,
                       r.deposit.month, r.deposit.day, r.deposit.year + 1);
            }
            else if (strcmp(r.accountType, "fixed02") == 0)
            {
                rate = 0.05;
                float interet = r.amount * (1 + rate / 12) - r.amount;
                interet *= 24;
                printf(" -> You will get $%.2f as interet on %d/%d/%d\n", interet,
                       r.deposit.month, r.deposit.day, r.deposit.year + 2);
            }
            else if (strcmp(r.accountType, "fixed03") == 0)
            {
                rate = 0.08;
                float interet = r.amount * (1 + rate / 12) - r.amount;
                interet *= 36;
                printf(" -> You will get $%.2f as interet on %d/%d/%d\n", interet,
                       r.deposit.month, r.deposit.day, r.deposit.year + 3);
            }
            else
            {
                printf("You will not get interests because the account is of type current\n");
            }

            fclose(pf);
            success(u);
        }
    }
}

void updateAccountInfo(struct User u, int accountNum, int commandNum)
{
    char userName[100];
    struct Record r;
    struct Record arr[100];
    FILE *pf = fopen(RECORDS, "a+");

    system("clear");

    int index = 0;
    while (getAccountFromFile(pf, userName, &r))
    {
        strcpy(r.name, userName);

        if (strcmp(userName, u.name) == 0 &&
            r.accountNbr == accountNum)
        {
            if (commandNum == 1)
            {
            num:
                printf("\t\tEnter the new phone number:");
                // scanf("%d", &r.phone);

                scanf("%s", checkInput);
                if (!isNumber(checkInput))
                {
                    printf("\n\t\t❌Invalid\n");
                    goto num;
                }
                r.accountNbr = atoi(checkInput);
            }
            else if (commandNum == 2)
            {
                printf("\t\tEnter the new country:");
                scanf("%s", r.country);
            }
        }

        arr[index] = r;
        index++;
    }

    // clear the file
    fclose(fopen(RECORDS, "w"));

    for (int i = 0; i < index; i++)
    {
        saveRecordToFile(pf, arr[i]);
    }

    fclose(pf);
    success(u);
}
void makeTransaction(struct User currentUser, int targetAccountNum, int transactionType)
{
    char username[100];
    struct Record currentRecord;
    struct Record updatedRecords[100];
    FILE *filePointer = fopen(RECORDS, "a+");
    int recordIndex = 0;

    while (getAccountFromFile(filePointer, username, &currentRecord))
    {
        strcpy(currentRecord.name, username);

        if (strcmp(username, currentUser.name) == 0 && currentRecord.accountNbr == targetAccountNum)
        {
            if (strcmp(currentRecord.accountType, "fixed01") == 0 ||
                strcmp(currentRecord.accountType, "fixed02") == 0 ||
                strcmp(currentRecord.accountType, "fixed03") == 0)
            {
                system("clear");
                printf("\t\t❌ You cannot deposit or withdraw cash in fixed accounts!");
                mainMenu(currentUser);
            }

            double availableBalance = currentRecord.amount;

            if (transactionType == 1)
            {
                printf("\t\tEnter the amount you want to withdraw:");
            }
            else if (transactionType == 2)
            {
                printf("\t\tEnter the amount you want to deposit:");
            }

            double transactionAmount;
            scanf("%lf", &transactionAmount);

            if (transactionAmount <= 0)
            {
                system("clear");
                printf("\t\t❌ Invalid transaction amount.");
                mainMenu(currentUser);
            }

            if (transactionType == 1 && transactionAmount > availableBalance)
            {
                system("clear");
                printf("\t\t❌ The amount you chose to withdraw is superior to your available balance");
                mainMenu(currentUser);
            }

            if (transactionType == 2 && transactionAmount > 200000)
            {
                system("clear");
                printf("\t\t❌ You cannot deposit cash greater than 200,000.");
                mainMenu(currentUser);
            }

            if (transactionType == 1)
            {
                currentRecord.amount -= transactionAmount;
            }
            else if (transactionType == 2)
            {
                currentRecord.amount += transactionAmount;
            }
        }

        updatedRecords[recordIndex] = currentRecord;
        recordIndex++;
    }

    fclose(fopen(RECORDS, "w"));

    for (int i = 0; i < recordIndex; i++)
    {
        saveRecordToFile(filePointer, updatedRecords[i]);
    }

    system("clear");
    fclose(filePointer);
    success(currentUser);
}

void removeAccount(struct User u, int accountNum)
{
    char userName[100];
    struct Record r;
    struct Record deleted;
    struct Record arr[100];
    FILE *pf = fopen(RECORDS, "a+");

    int index = 0;
    while (getAccountFromFile(pf, userName, &r))
    {
        strcpy(r.name, userName);

        if (strcmp(userName, u.name) == 0 &&
            r.accountNbr == accountNum)
        {
            deleted = r;
        }
        else
        {
            arr[index] = r;
            index++;
        }
    }

    system("clear");
    printf("                       ===== Deleted account =====\n");
    printf("\n\t\tAccount number:%d\nDeposit Date:%d/%d/%d \ncountry:%s \nPhone number:%d \nAmount deposited: $%.2f \nType Of Account:%s\n",
           deleted.accountNbr,
           deleted.deposit.day,
           deleted.deposit.month,
           deleted.deposit.year,
           deleted.country,
           deleted.phone,
           deleted.amount,
           deleted.accountType);

    // clear the file
    fclose(fopen(RECORDS, "w"));

    for (int i = 0; i < index; i++)
    {
        saveRecordToFile(pf, arr[i]);
    }

    fclose(pf);
    success(u);
}

void transfereAccount(struct User u, int accountNum)
{
    char userName[100];
    char ownerName[100];
    struct Record r;
    struct Record arr[100];
    FILE *pf = fopen(RECORDS, "a+");

    int index = 0;
    while (getAccountFromFile(pf, userName, &r))
    {
        strcpy(r.name, userName);
        if (strcmp(userName, u.name) == 0 &&
            r.accountNbr == accountNum)
        {
            system("clear");
            printf("                       ===== Transfering account:\n");
            printf("\n\t\tAccount number:%d\nDeposit Date:%d/%d/%d \ncountry:%s \nPhone number:%d \nAmount deposited: $%.2f \nType Of Account:%s\n",
                   r.accountNbr,
                   r.deposit.day,
                   r.deposit.month,
                   r.deposit.year,
                   r.country,
                   r.phone,
                   r.amount,
                   r.accountType);
        }

        arr[index] = r;
        index++;
    }

    fclose(pf);

    printf("\t\tWhich user you want transfer ownership to (user name):");
    scanf("%s", ownerName);
    if (!IsNameContained(ownerName))
    {
        printf("\t\t❌ This user don't exist.");
        mainMenu(u);
    }
    int ownerId;
    ownerId = getIdUser(ownerName);

    for (int i = 0; i < index; i++)
    {
        if (strcmp(arr[i].name, u.name) == 0 &&
            arr[i].accountNbr == accountNum)
        {
            strcpy(arr[i].name, ownerName);
            arr[i].userId = ownerId;
        }
    }

    // clear the file
    fclose(fopen(RECORDS, "w"));

    pf = fopen(RECORDS, "a+");
    for (int i = 0; i < index; i++)
    {
        saveRecordToFile(pf, arr[i]);
    }

    fclose(pf);
    success(u);
}

int getIdUser(char *name)
{
    FILE *pf = fopen("./data/users.txt", "r+");

    char id[5];
    struct User temp;
    while (fscanf(pf, "%s %s %s", id, temp.name, temp.password) != EOF)
    {
        if (strcmp(temp.name, name) == 0)
        {
            return atoi(id);
        }
    }

    return -1;
}