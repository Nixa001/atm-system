#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct User
{
    int id;
    char name[50];
    char password[50];
};

struct Date
{
    int month, day, year;
};
struct Record
{
    int id;
    int userId;
    char name[100];
    char country[100];
    int phone;
    char accountType[10];
    int accountNbr;
    double amount;
    struct Date deposit;
    struct Date withdraw;
};

// authentication functions
void loginMenu(char a[50], char pass[50]);
const char *getPassword(struct User *u);

// authentification functions Added
void registerMenu(char a[50], char pass[50]);

// system function
void createNewAcc(struct User u);
void mainMenu(struct User u);
void checkAllAccounts(struct User u);
// system function Added
void updateAccountInfo(struct User u, int accNum, int commandNum);
void checkDetailAcc(struct User u, int accID);
void makeTransaction(struct User u, int accNum, int commandNum);
void removeAccount(struct User u, int accNum);
void transfereAccount(struct User u, int accNum);

// utils functions
bool isNumber(const char *chaine);
bool IsNameContained(char *name);
bool isContainedInArray(char array[100][100], char *str);
int getIdUser(char *name);
bool isValidAccountNumber(int num, struct User u);
bool containSpace(char input[100]);