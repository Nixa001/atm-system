#include "header.h"

bool containSpace(char input[100])
{
    // check if space is contained
    if (strchr(input, ' ') != NULL)
    {
        return true;
    }
    return false;
}

// Fonction pour vérifier si une chaîne de caractères est un nombre
bool isNumber(const char *chaine)
{
    char *fin;
    strtod(chaine, &fin);

    return *fin == '\0';
}


bool isContainedInArray(char array[100][100], char *str)
{
    for (int i = 0; i < 100; i++)
    {
        if (strcmp(array[i], str) == 0)
        {
            return true;
        }
    }

    return false;
}

bool isValidAccountNumber(int num, struct User u)
{
    struct Record r;
    FILE *pf = fopen("./data/records.txt", "r+");

    while (fscanf(pf, "%d %d %s %d %d/%d/%d %s %d %lf %s",
                  &r.id, &r.userId, r.name, &r.accountNbr,
                  &r.deposit.month, &r.deposit.day,
                  &r.deposit.year, r.country,
                  &r.phone, &r.amount, r.accountType) != EOF)
    {

        if (num == r.accountNbr && strcmp(r.name, u.name) == 0)
        {
            fclose(pf);
            return true;
        }
    }
    fclose(pf);
    return false;
}

bool IsNameContained(char *name)
{
    char id[5];
    char userName[100];
    char password[100];

    FILE *pf = fopen("./data/users.txt", "r");
    while (fscanf(pf, "%s %s %s", id, userName, password) != EOF)
    {
        if (strcmp(name, userName) == 0)
        {
            return true;
        }
    }
    return false;
}

int countLines(const char *filename) 
 { 
     FILE *file = fopen(filename, "r"); 
     if (file == NULL) 
     { 
         perror("Erreur lors de l'ouverture du fichier"); 
         return -1; // Valeur de retour pour indiquer une erreur 
     } 
  
     int lineCount = 1; 
     char ch; 
  
     while ((ch = fgetc(file)) != EOF) 
     { 
         if (ch == '\n') 
         { 
             lineCount++; 
         } 
     } 
  
     fclose(file); 
     return lineCount; 
 }
