// @@@@ author: João Duarte - Nº 23553 @@@@
// header file para a estrutura de dados cliente

#include<stdbool.h>

typedef struct list
{
    char *name;
    char *address;
    char *username;
    char *password;
    bool isRenting;
    int vehichleID;
    int NIF;
    int balance;
    struct  list *next;
} clientList;


clientList *createClient(clientList* head,char *name, char *address, char *username, char *password, int NIF);
clientList *addClient(clientList *head, clientList *newClient);
clientList *readClientFile(clientList *head);
void writeClientFile(clientList *head);
int getClientCount(clientList *head);
int logClient(clientList *head, char *username, char *password);
clientList *getClient(clientList *head, char *username, char *password);
void printClient(clientList *head);
clientList * getClientByUsername(clientList *head, char *username);
clientList * removeClient(clientList *head, int NIF);
void rechargeBalance( clientList * loggedInClient, int amount);