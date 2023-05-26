#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gestor.h"


adminList *readAdminList(adminList *adminList)
{
    // Implementation of the readAdminList function
    // ...
    FILE *fp;
    fp = fopen("admin.txt", "r");
    if (fp == NULL)
    {
        printf("Erro ao abrir o ficheiro");
        getchar();
        getchar();
        return NULL;
    }
    else
    {
        char line[100];
        while (fgets(line, sizeof(line), fp) != NULL)
        {
            char *token = strtok(line, ";");
            if (token != NULL)
            {
                char username[50];
                strcpy(username, token);
                token = strtok(NULL, "\n");
                if (token != NULL)
                {
                    char password[50];
                    strcpy(password, token);
                    adminList = addAdmin(adminList, createAdmin(adminList, username, password));
                }
            }
        }
        fclose(fp);
        return adminList;
    }
}

adminList *createAdmin(adminList *adminhead, char *username, char *password)
{
    // Implementation of the createAdmin function
    // ...

    adminList *newAdmin = (adminList *)malloc(sizeof(adminList));
    strcpy(newAdmin->username, username);
    strcpy(newAdmin->password, password);
    newAdmin->next = NULL;
    while (adminhead != NULL)
    {
        if (newAdmin->username == adminhead->username)
        {
            return NULL;
        }
        adminhead = adminhead->next;
    }
    return newAdmin;
}

adminList *addAdmin(adminList *adminhead, adminList *newAdmin)
{
    if (adminhead == NULL)
    {
        adminhead = newAdmin;
        newAdmin->next = NULL;
        return adminhead;
    }
    else
    {
        newAdmin->next = adminhead;
        adminhead = newAdmin;
        return adminhead;
    }
}

int writeAdminList(adminList *adminhead)
{
    // Implementation of the writeAdminList function
    // ...
    FILE *fp;
    fp = fopen("admin.txt", "w");
    if (fp == NULL)
    {
        printf("Erro ao abrir o ficheiro");
        return 0;
    }
    else
    {
        adminList *current = adminhead;
        while (current != NULL)
        {
            fprintf(fp, "%s;%s\n", current->username, current->password);
            current = current->next;
        }
        fclose(fp);
    }
}

int logAdmin(adminList *adminHead, char *username, char *password)
{
    // Implementation of the logAdmin function
    // ...
    adminList *current = adminHead;
    while (current != NULL)
    {
        if (strcmp(current->username, username) == 0)
        {
            if (strcmp(current->password, password) == 0)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
        current = current->next;
    }
    return 0;
}

int getAdminListSize(adminList *adminHead)
{
    // Implementation of the getAdminListSize function
    // ...
    int size = 0;
    adminList *current = adminHead;
    while (current != NULL)
    {
        size++;
        current = current->next;
    }
    return size;
}

