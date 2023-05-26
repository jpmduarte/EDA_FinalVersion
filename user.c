#include "user.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


clientList *createClient(clientList *head,char *name, char *address, char *username, char *password, int NIF)
{
    clientList *NewClient = (clientList *)malloc(sizeof(clientList));
    NewClient->name = strdup(name);
    NewClient->address = strdup(address);
    NewClient->username = strdup(username);
    NewClient->password = strdup(password);
    NewClient->NIF = NIF;
    NewClient->balance = 0;
    NewClient->isRenting = false;
    NewClient->vehichleID = 0;
    NewClient->next = NULL;
    while (head != NULL)
    {
        if (NewClient->username == head->username)
        {
            return NULL;
        }
        head = head->next;
    }
    return NewClient;
}

// Função que adiciona um cliente à lista de clientes (no início da lista por motivos de eficiência para não haver necessidade de percorrer a lista toda para adicionar um cliente))
clientList *addClient(clientList *head, clientList *newClient)
{
    if (head == NULL)
    {
        head = newClient;
        newClient->next = NULL;
        return head;
    }

    clientList *CurrentClient = head;

    // Adiciona o novo cliente no início da lista
    newClient->next = head;
    head = newClient;
    return head;
}

void writeClientFile(clientList *head)
{
    FILE *fp;
    clientList *current = head;
    fp = fopen("clientes.txt", "w");
    int writeCount = 0;

    while (current != NULL)
    {
        writeCount++;
        fprintf(fp, "%s;%s;%s;%s;%d;%d;%d;%d;\n", current->name, current->address, current->username, current->password, current->NIF, current->balance, current->vehichleID, current->isRenting ? 1 : 0);
        current = current->next;
    }

    fclose(fp);
}

int logClient(clientList *head, char *username, char *password)
{
    clientList *current = head;
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

int getClientCount(clientList *head)
{
    int count = 0;
    while (head != NULL)
    {
        count++;
        head = head->next;
    }
    return count;
}

clientList *getClient(clientList *head, char *username, char *password)
{
    clientList *current = head;
    while (current != NULL)
    {
        if (strcmp(current->username, username) == 0)
        {
            if (strcmp(current->password, password) == 0)
            {
                return current;
            }
        }
        current = current->next;
    }
    return current;
}

void printClient(clientList *head)
{
    clientList *current = head;
    int i = 1;
    while (current != NULL)
    {
        printf("Cliente %d\n", i);
        printf("Nome: %s\n", current->name);
        printf("Morada: %s\n", current->address);
        printf("Username: %s\n", current->username);
        printf("Password: %s\n", current->password);
        printf("NIF: %d\n", current->NIF);
        printf("Saldo: %d\n", current->balance);
        printf("Está a alugar um veículo: %s\n", current->isRenting ? "Sim" : "Não");
        printf("ID do veículo alugado: %d\n", current->vehichleID);
        printf("\n");
        current = current->next;
        i++;
    }
}

clientList * getClientByUsername(clientList *head, char *username)
{
    clientList *current = head;
    while (current != NULL)
    {
        if (strcmp(current->username, username) == 0)
        {
            return current;
        }
        current = current->next;
    }
    return current;
}

clientList * removeClient(clientList *head, int NIF)
{
    clientList *current = head;
    clientList *previous = NULL;
    while (current != NULL)
    {
        if (current->NIF == NIF)
        {
            if (previous == NULL)
            {
                head = current->next;
                free(current);
                return head;
            }
            else
            {
                previous->next = current->next;
                free(current);
                return head;
            }
        }
        previous = current;
        current = current->next;
    }
    return head;
}

void rechargeBalance( clientList * loggedInClient, int amount)
{
    loggedInClient->balance += amount;
}

clientList *readClientFile(clientList *head)
{
    FILE *fp;
    fp = fopen("clientes.txt", "r");
    if (fp == NULL)
    {
        printf("Erro ao abrir o ficheiro");
        getchar();
        getchar();
        return head;
    }
    else
    {
        char line[200];
        while (fgets(line, sizeof(line), fp))
        {
            char *token = strtok(line, ";");
            if (token)
            {
                char *name = malloc(strlen(token) + 1);
                strcpy(name, token);

                token = strtok(NULL, ";");
                if (token)
                {
                    char *address = malloc(strlen(token) + 1);
                    strcpy(address, token);

                    token = strtok(NULL, ";");
                    if (token)
                    {
                        char *username = malloc(strlen(token) + 1);
                        strcpy(username, token);

                        token = strtok(NULL, ";");
                        if (token)
                        {
                            char *password = malloc(strlen(token) + 1);
                            strcpy(password, token);

                            token = strtok(NULL, ";");
                            if (token)
                            {
                                int NIF = atoi(token);

                                clientList *newClient = (clientList *)malloc(sizeof(clientList));
                                newClient->name = name;
                                newClient->address = address;
                                newClient->username = username;
                                newClient->password = password;
                                newClient->NIF = NIF;
                                newClient->balance = 0;  
                                newClient->vehichleID = 0;
                                newClient->isRenting = 0;
                                newClient->next = NULL;
                                head = addClient(head, newClient);
                            }
                        }
                    }
                }
            }
        }
        fclose(fp);
        return head;
    }
}
