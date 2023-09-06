#include <termios.h>
#include "header.h"

char *USERS = "./data/users.txt";

void loginMenu(char a[50], char pass[50])
{
    struct termios oflags, nflags;

    system("clear");
start:
    printf("\n\n\n\t\t\t\tBank Management System 🏦\n\n\t\t\t\t User Login:");
    scanf("%s", a);
    // Read line && check space
    char input[100];
    fgets(input, sizeof(input), stdin);
    if (containSpace(input))
    {
        system("clear");
        printf("\n\t\t\t\t❌ Space not allowed\n");
        goto start;
    }

    // disabling echo
    tcgetattr(fileno(stdin), &oflags);
    nflags = oflags;
    nflags.c_lflag &= ~ECHO;
    nflags.c_lflag |= ECHONL;

    if (tcsetattr(fileno(stdin), TCSANOW, &nflags) != 0)
    {
        perror("tcsetattr");
        return exit(1);
    }
    printf("\t\t\t\tEnter the password:");
    scanf("%s", pass);

    // restore terminal
    if (tcsetattr(fileno(stdin), TCSANOW, &oflags) != 0)
    {
        perror("tcsetattr");
        return exit(1);
    }
    // Read line && check space
    fgets(input, sizeof(input), stdin);
    if (containSpace(input))
    {
        system("clear");
        printf("\n\t\t\t\t❌ Space not allowed\n");
        goto start;
    }
};

const char *getPassword(struct User *u)
{
    FILE *fp;
    struct User userChecker;
    char id[10];
    if ((fp = fopen("./data/users.txt", "r")) == NULL)
    {
        printf("\t\t\t\t❌ Error! opening file\n");
        exit(1);
    }

    while (fscanf(fp, "%s %s %s", id, userChecker.name, userChecker.password) != EOF)
    {
        if (strcmp(userChecker.name, u->name) == 0)
        {
            fclose(fp);
            u->id = atoi(id);
            char *buff = userChecker.password;
            return buff;
        }
    }

    fclose(fp);
    return "\t\t❌no user found";
}

void registerMenu(char a[50], char pass[50])
{
    struct termios oflags, nflags;
    system("clear");
start:
    printf("\n\n\n\t\t\t\tBank Management System 🏦\n\t\t\t\t\t User Login:");
    scanf("%s", a);

    // Read line && check space
    char input[100];
    fgets(input, sizeof(input), stdin);
    if (containSpace(input))
    {
        system("clear");
        printf("\n\t\t\t\t❌ Space not allowed\n");
        goto start;
    }

    // disabling echo
    tcgetattr(fileno(stdin), &oflags);
    nflags = oflags;
    nflags.c_lflag &= ~ECHO;
    nflags.c_lflag |= ECHONL;

    if (tcsetattr(fileno(stdin), TCSANOW, &nflags) != 0)
    {
        perror("tcsetattr");
        return exit(1);
    }
    printf("\n\n\t\t\t\tEnter the password to login:");
    scanf("%s", pass);

    // restore terminal
    if (tcsetattr(fileno(stdin), TCSANOW, &oflags) != 0)
    {
        perror("tcsetattr");
        return exit(1);
    }
    // Read line && check space
    // Read line && check space
    fgets(input, sizeof(input), stdin);
    if (containSpace(input))
    {
        system("clear");
        printf("\n\t\t\t\t❌ Space not allowed\n");
        goto start;
    }

    FILE *fp;
    char names[100][100];
    struct User userChecker;
    char id[5];
    int counter = 0;

    if ((fp = fopen("./data/users.txt", "a+")) == NULL)
    {
        printf("\t\t❌ Error! opening file");
        exit(1);
    }

    while (fscanf(fp, "%s %s %s", id, userChecker.name, userChecker.password) != EOF)
    {
        strcpy(names[counter], userChecker.name);
        counter++;
    }

    if (counter != 0)
    {
        fprintf(fp, "\n");
    }

    if (isContainedInArray(names, a))
    {
        printf("\t\t❌ That name is taken. Please enter another name!\n");
        exit(1);
    }
    else
    {
        fprintf(fp, "%d %s %s", counter, a, pass);
    }

    fclose(fp);
}