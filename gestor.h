typedef struct adminList
{
    char password[50];
    char username[50];
    struct adminList *next;
}adminList; // Lista de administradores

adminList *readAdminList(adminList *adminhead);
adminList *createAdmin(adminList *adminhead, char *username, char *password);
adminList *addAdmin(adminList *adminhead,adminList *newAdmin);
int writeAdminList(adminList *adminhead);
int logAdmin(adminList *adminhead, char *username, char *password);
int getAdminListSize(adminList *adminhead);



