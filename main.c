#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gestor.h"
#include "meio.h"
#include "graph.h"

int main()
{
    int option;
    adminList *adminHead = NULL;
    adminHead = readAdminList(adminHead);
    clientList *clientHead = NULL;
    clientHead = readClientFile(clientHead);
    vehicleList *vehicleHead = NULL;
    vehicleHead = readVehicleFile(vehicleHead);
    int numNodes = 0;
    Node graph[MAX_NODES];
    ReadLocationsFromFile(graph, &numNodes);
    ReadDistancesFromFile(graph, numNodes);
    ReadCustomersFromFile(graph, numNodes);
    ReadVehiclesFromFile(graph, numNodes);
    do
    {
        system("clear");
        printf("*****************************\n");
        printf("***      Login Menu       ***\n");
        printf("*****************************\n");
        printf("* 1 - Login como gestor     *\n");
        printf("* 2 - Login como utilizador *\n");
        printf("* 0 - Sair                  *\n");
        printf("*****************************\n");
        printf("\nInsira uma opcão: ");
        scanf("%d", &option);
        switch (option)
        {
        case 1:
            int option1;
            do
            {
                system("cls");
                printf("*****************************\n");
                printf("***      Login Menu       ***\n");
                printf("*****************************\n");
                printf("* 1 - login como gestor     *\n");
                printf("* 2 - registar como gestor  *\n");
                printf("* 0 - Sair                  *\n");
                printf("*****************************\n");
                printf("\nInsira uma opcão: ");
                scanf("%d", &option1);
                switch (option1)
                {
                case 1:
                    printf("\nInsira o seu username: ");
                    char username[50];
                    scanf("%s", username);
                    printf("\nInsira a sua password: ");
                    char password[50];
                    scanf("%s", password);
                    int login = logAdmin(adminHead, username, password);
                    if (login == 1)
                    {
                        int option2;
                        do
                        {
                            system("cls | clear");
                            printf("***************************************\n");
                            printf("***      Menu de gestão             ***\n");
                            printf("***************************************\n");
                            printf("* 1 - Listar utilizadores             *\n");
                            printf("* 2 - Adicionar utilizador            *\n");
                            printf("* 3 - Editar utilizador               *\n");
                            printf("* 4 - Remover utilizador              *\n");
                            printf("* 5 - Adicionar meio de transporte    *\n");
                            printf("* 6 - Editar meio de transporte       *\n");
                            printf("* 7 - Remover meio de transporte      *\n");
                            printf("* 8 - Listagem de meios de transporte *\n");
                            printf("* 0 - Sair                            *\n");
                            printf("***************************************\n");
                            printf("\nInsira uma opcão: ");
                            scanf("%d", &option2);
                            switch (option2)
                            {
                            case 1:
                                printClient(clientHead);
                                getchar();
                                getchar();
                                break;
                            case 2:
                                printf("\nInsira o seu username: ");
                                char username7[50];
                                scanf("%s", username7);
                                printf("\nInsira a sua password: ");
                                char password7[50];
                                scanf("%s", password7);
                                printf("\nInsira o seu nome: ");
                                char name1[50];
                                scanf("%s", name1);
                                getchar();
                                printf("\nInsira a sua morada: ");
                                char address1[100];
                                scanf("%s", address1);
                                int nif1;
                                printf("\nInsira o seu NIF: ");
                                scanf("%d", &nif1);
                                clientList *newClient = createClient(clientHead, username7, password7, name1, address1, nif1);
                                if (newClient == NULL)
                                {
                                    printf("\nCliente duplicado!\n");
                                    getchar();
                                    getchar();
                                    break;
                                }
                                int beforeSize = getClientCount(clientHead);
                                clientHead = addClient(clientHead, newClient);
                                int afterSize = getClientCount(clientHead);
                                if (beforeSize < afterSize)
                                {
                                    printf("\nRegisto efetuado com sucesso!\n");
                                    writeClientFile(clientHead);
                                    getchar();
                                    getchar();
                                }
                                else
                                {
                                    printf("Registo não foi guardado com sucesso!\n");
                                    getchar();
                                    getchar();
                                }
                                getchar();
                                getchar();
                                break;
                            case 3:
                                printf("\nInsira o username do utilizador a alterar: ");
                                char username5[50];
                                scanf("%s", username5);
                                clientList *client = getClientByUsername(clientHead, username5);
                                if (client == NULL)
                                {
                                    printf("\nUtilizador não encontrado!\n");
                                    getchar();
                                    getchar();
                                    break;
                                }
                                printf("\nInsira o seu username: ");
                                char username6[50];
                                scanf("%s", username6);
                                strcpy(client->username, username6);
                                printf("\nInsira a sua password: ");
                                char password6[50];
                                scanf("%s", password6);
                                strcpy(client->password, password6);
                                printf("\nInsira o seu nome: ");
                                char name2[50];
                                scanf("%s", name2);
                                strcpy(client->name, name2);
                                getchar();
                                printf("\nInsira a sua morada: ");
                                char address2[100];
                                scanf("%s", address2);
                                strcpy(client->address, address2);
                                int nif2;
                                printf("\nInsira o seu NIF: ");
                                scanf("%d", &nif2);
                                client->NIF = nif2;
                                printf("\nUtilizador alterado com sucesso!\n");
                                writeClientFile(clientHead);
                                getchar();
                                getchar();
                                break;
                            case 4:
                                printf("\nInsira o NIF do utilizador a remover: ");
                                int nif3;
                                scanf("%d", &nif3);
                                clientHead = removeClient(clientHead, nif3);
                                break;
                            case 5:
                                printf("\nInsira o ID do meio de transporte: ");
                                int id1;
                                scanf("%d", &id1);
                                printf("\nInsira a autonomia do meio de transporte: ");
                                int autonomy1;
                                scanf("%d", &autonomy1);
                                printf("\nInsira o custo por minuto do meio de transporte: ");
                                int cost1;
                                scanf("%d", &cost1);
                                printf("\nInsira a localizacao do meio de transporte: ");
                                char location1[50];
                                scanf("%s", location1);
                                if (isLocationOnFile(location1))
                                {
                                    vehicleList *newVehicle = createVehicle(id1, autonomy1, cost1, location1);
                                    vehicleHead = addVehicle(vehicleHead, newVehicle);
                                    writeVehicleFile(vehicleHead);
                                    printf("\nMeio de transporte adicionado com sucesso!\n");
                                    AddVehicleToNode(graph, numNodes, location1, id1);
                                    getchar();
                                    getchar();
                                }
                                else
                                {
                                    printf("\nLocalizacao nao permitida!\n");
                                    getchar();
                                    getchar();
                                }

                                break;
                            case 6:
                                printf("\nInsira o ID do meio de transporte a alterar: ");
                                int id2;
                                scanf("%d", &id2);
                                vehicleList *vehicle = searchVehicle(vehicleHead, id2);
                                if (vehicle == NULL)
                                {
                                    printf("\nMeio de transporte não encontrado!\n");
                                    getchar();
                                    getchar();
                                    break;
                                }

                                printf("\nInsira o ID do meio de transporte: ");
                                int id3;
                                scanf("%d", &id3);
                                vehicle->vehichleID = id3;

                                printf("\nInsira a autonomia do meio de transporte: ");
                                int autonomy2;
                                scanf("%d", &autonomy2);
                                vehicle->autonomy = autonomy2;

                                printf("\nInsira o custo por minuto do meio de transporte: ");
                                int cost2;
                                scanf("%d", &cost2);
                                vehicle->cost = cost2;
                                UpdateVehicleInNode(graph, numNodes, vehicle->location, id2, id3);
                                writeVehicleFile(vehicleHead);

                                printf("\nMeio de transporte alterado com sucesso!\n");
                                getchar();
                                getchar();
                                break;

                            case 7:
                                printf("\nInsira o ID do meio de transporte a remover: ");
                                int id4;
                                scanf("%d", &id4);
                                vehicleHead = removeVehicle(vehicleHead, id4);
                                writeVehicleFile(vehicleHead);
                                getchar();
                                getchar();
                                break;
                            case 8:
                                printf("1 - Listar por autonomia\n 2 - listar por localizacao\n");
                                int option3;
                                scanf("%d", &option3);
                                if (option3 == 1)
                                {
                                    // Count the number of vehicles
                                    int count = 0;
                                    vehicleList *temp = vehicleHead;
                                    while (temp != NULL)
                                    {
                                        count++;
                                        temp = temp->next;
                                    }

                                    // Perform bubble sort on autonomy
                                    for (int i = 0; i < count - 1; i++)
                                    {
                                        for (int j = 0; j < count - i - 1; j++)
                                        {
                                            if (vehicleHead->autonomy > vehicleHead->next->autonomy)
                                            {
                                                // Swap the positions of two vehicles
                                                temp = vehicleHead;
                                                vehicleHead = vehicleHead->next;
                                                temp->next = vehicleHead->next;
                                                vehicleHead->next = temp;
                                            }
                                            else
                                            {
                                                vehicleHead = vehicleHead->next;
                                            }
                                        }
                                        // Reset vehicleHead to the beginning for the next pass
                                        vehicleHead = vehicleHead->next;
                                    }

                                    // Print the sorted list of vehicles
                                    vehicleList *currentVehicle = vehicleHead;
                                    while (currentVehicle != NULL)
                                    {
                                        printf("ID: %d\n", currentVehicle->vehichleID);
                                        printf("Autonomia: %d\n", currentVehicle->autonomy);
                                        printf("Custo: %d\n", currentVehicle->cost);
                                        printf("Localizacao: %s\n", currentVehicle->location);
                                        currentVehicle = currentVehicle->next;
                                    }
                                }
                                else if (option3 == 2)
                                {
                                    printf("Insira a localizacao: ");
                                    char location[100];
                                    scanf("%s", location);
                                    ListVehiclesInNode(graph, numNodes, location);
                                }
                                else
                                {
                                    printf("Opção inválida!\n");
                                }
                                getchar();
                                getchar();
                                break;
                            case 0:
                                printf("A voltar para o main menu...\n");
                                getchar();
                                getchar();
                                break;
                            default:
                                printf("Opção inválida!\n");
                                getchar();
                                getchar();
                                break;
                            }
                        } while (option2 != 0);
                    }
                    else
                    {
                        printf("Login inválido!\n");
                    }
                    getchar();
                    getchar();
                    break;
                case 2:
                    printf("\nInsira o seu username: ");
                    char username1[50];
                    scanf("%s", username1);
                    printf("\nInsira a sua password: ");
                    char password1[50];
                    scanf("%s", password1);
                    int beforeSize1 = getAdminListSize(adminHead);
                    adminList *newAdmin = createAdmin(adminHead, username1, password1);
                    if (newAdmin == NULL)
                    {
                        printf("\nAdmin duplicado!\n");
                        getchar();
                        getchar();
                        break;
                    }
                    adminHead = addAdmin(adminHead, newAdmin);
                    writeAdminList(adminHead);
                    int afterSize1 = getAdminListSize(adminHead);
                    if (beforeSize1 < afterSize1)
                    {
                        printf("\nRegisto efetuado com sucesso!\n");
                    }
                    else
                    {
                        printf("Registo não foi guardado com sucesso!\n");
                    }
                    getchar();
                    getchar();
                    break;
                case 0:
                    printf("A voltar para o main menu...\n");
                    getchar();
                    getchar();
                    break;
                default:
                    printf("Opção inválida!\n");
                    getchar();
                    getchar();
                    break;
                }
            } while (option1 != 0);
            getchar();
            getchar();
            break;
        case 2:
            int option3;
            do
            {
                system("cls | clear");
                printf("********************************\n");
                printf("***      Login Menu          ***\n");
                printf("********************************\n");
                printf("* 1 - login como utilizador    *\n");
                printf("* 2 - registar como utilizador *\n");
                printf("* 0 - Sair                     *\n");
                printf("********************************\n");
                printf("\nInsira uma opcão: ");
                scanf("%d", &option3);
                switch (option3)
                {
                case 1:
                    printf("\nInsira o seu username: ");
                    char username4[50];
                    scanf("%s", username4);
                    printf("\nInsira a sua password: ");
                    char password4[50];
                    scanf("%s", password4);
                    int login = logClient(clientHead, username4, password4);
                    if (login == 1)
                    {
                        int option4;
                        do
                        {
                            clientList *loggedClient = getClient(clientHead, username4, password4);
                            system("clear");
                            printf("**************************************************\n");
                            printf("***             Menu de utilizador             ***\n");
                            printf("**************************************************\n");
                            printf("* 1 - Listar meios de transporte disponiveis     *\n");
                            printf("* 2 - Listar meios de transporte por localizacao *\n");
                            printf("* 3 - Reservar meio de transporte                *\n");
                            printf("* 4 - Carregar saldo                             *\n");
                            printf("* 5 - devolver meio de transporte                *\n");
                            printf("* 0 - Sair                                       *\n");
                            printf("**************************************************\n");
                            printf("\nInsira uma opcão: ");
                            scanf("%d", &option4);
                            switch (option4)
                            {
                            case 1:

                                vehicleList *currentVehicle = vehicleHead;
                                if (currentVehicle == NULL)
                                {
                                    printf("Nao existem transportes disponiveis\n");
                                    getchar();
                                    getchar();
                                    break;
                                }
                                while (currentVehicle != NULL)
                                {
                                    if (currentVehicle->autonomy > 0 && currentVehicle->isRented == 0)
                                    {
                                        printf("ID: %d\n", currentVehicle->vehichleID);
                                        printf("Autonomia: %d\n", currentVehicle->autonomy);
                                        printf("Custo por minuto: %d\n", currentVehicle->cost);
                                        printf("Localizacao: %s\n", currentVehicle->location);
                                        printf("\n");
                                    }
                                    currentVehicle = currentVehicle->next;
                                }
                                getchar();
                                getchar();
                                break;
                            case 2:
                                printf("\nInsira a localizacao: ");
                                char location[100];
                                scanf("%s", location);
                                printf("\nInsira o raio a procurar:");
                                int radius;
                                scanf("%d", &radius);
                                ListVehiclesInRadius(graph, numNodes, location, radius);
                                getchar();
                                getchar();
                                break;
                            case 3:
                                printf("\nInsira o ID do veiculo: ");
                                int vehicleID;
                                scanf("%d", &vehicleID);
                                int check = rentVehicle(vehicleHead, vehicleID, loggedClient->NIF);
                                vehicleList *VehicleLocation = searchVehicle(vehicleHead, vehicleID);
                                if (check == 0)
                                {
                                    printf("Meio de transporte reservado com sucesso!\n");
                                    addCustomerToNode(graph, &numNodes, VehicleLocation->location, vehicleID, loggedClient->NIF);
                                    getchar();
                                    getchar();
                                    break;
                                }
                                else if (check == -1)
                                {
                                    printf("Meio de transporte não encontrado!\n");
                                    getchar();
                                    getchar();
                                    break;
                                }
                                else
                                {
                                    printf("Meio de transporte nao disponivel!\n");
                                    getchar();
                                    getchar();
                                    break;
                                }
                                getchar();
                                getchar();
                                break;
                            case 4:
                                printf("\nInsira o valor a carregar: ");
                                int value;
                                scanf("%d", &value);
                                rechargeBalance(loggedClient, value);
                                getchar();
                                getchar();
                                break;
                            case 5:
                                printf("\nInsira o ID do veiculo: ");
                                int vehicleID2;
                                scanf("%d", &vehicleID2);
                                int check2 = returnVehicle(vehicleHead, vehicleID2, loggedClient->NIF, loggedClient);
                                vehicleList *aux = searchVehicle(vehicleHead, vehicleID2);
                                removeCustomerFromNode(graph,numNodes,aux->location,loggedClient->NIF);
                                if (check2 == 0)
                                {
                                    printf("Meio de transporte devolvido com sucesso!\n");
                                    getchar();
                                    getchar();
                                    break;
                                }
                                else if (check2 == -2)
                                {
                                    printf("meio de mobilidade nao foi alugado!\n");
                                    getchar();
                                    getchar();
                                    break;
                                }
                                else if (check2 == -3)
                                {
                                    printf("O NIF do cliente nao corresponde ao do aluguer!\n");
                                    getchar();
                                    getchar();
                                    break;
                                }
                                else
                                {
                                    printf("meio de mobilidade nao encontrado.\n");
                                    getchar();
                                    getchar();
                                    break;
                                }
                                getchar();
                                getchar();
                                break;
                            case 0:
                                printf("A voltar para o main menu...\n");
                                getchar();
                                getchar();
                                break;
                            default:
                                printf("Opção inválida!\n");
                                getchar();
                                getchar();
                                break;
                            }
                        } while (option4 != 0);
                    }
                    else
                    {
                        printf("Login inválido!\n");
                        getchar();
                        getchar();
                    }
                    break;
                case 2:
                    printf("\nInsira o seu username: ");
                    char username2[50];
                    scanf("%s", username2);
                    printf("\nInsira a sua password: ");
                    char password2[50];
                    scanf("%s", password2);
                    printf("\nInsira o seu nome: ");
                    char name[50];
                    scanf("%s", name);
                    getchar();
                    printf("\nInsira a sua morada: ");
                    char address[50];
                    scanf("%s", address);
                    int nif;
                    printf("\nInsira o seu NIF: ");
                    scanf("%d", &nif);
                    clientList *newClient = createClient(clientHead, username2, password2, name, address, nif);
                    if (newClient == NULL)
                    {
                        printf("\nCliente duplicado!\n");
                        getchar();
                        getchar();
                        break;
                    }
                    int beforeSize2 = getClientCount(clientHead);
                    clientHead = addClient(clientHead, newClient);
                    int afterSize2 = getClientCount(clientHead);
                    if (beforeSize2 < afterSize2)
                    {
                        printf("\nRegisto efetuado com sucesso!\n");
                        writeClientFile(clientHead);
                        getchar();
                        getchar();
                    }
                    else
                    {
                        printf("Registo não foi guardado com sucesso!\n");
                        getchar();
                        getchar();
                    }
                    break;
                case 0:
                    printf("A voltar para o main menu...\n");
                    getchar();
                    getchar();
                    break;
                default:
                    printf("Opção inválida!\n");
                    getchar();
                    getchar();
                    break;
                }
            } while (option3 != 0);
            getchar();
            getchar();
            break;
        case 0:
            printf("A sair...\n");
            SaveCustomersInGraphToFile(graph, numNodes);
            SaveVehiclesInGraphToFile(graph, numNodes);
            getchar();
            getchar();
            break;
        default:
            printf("Opção inválida!\n");
            getchar();
            getchar();
            break;
        }
    } while (option != 0);
    return 0;
}