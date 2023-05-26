#include "meio.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

vehicleList * createVehicle(int vehichleID, int autonomy, int cost, char * location)
{
    vehicleList * newVehicle = (vehicleList *) malloc(sizeof(vehicleList));
    newVehicle->vehichleID = vehichleID;
    newVehicle->autonomy = autonomy;
    newVehicle->cost = cost;
    newVehicle->location = (char *) malloc(sizeof(char) * (strlen(location) + 1));
    strcpy(newVehicle->location, location);
    newVehicle->isRented = false;
    newVehicle->next = NULL;
    return newVehicle;
}

vehicleList * addVehicle(vehicleList * head, vehicleList * newVehicle)
{
    if (head == NULL)
    {
        head = newVehicle;
        return head;
    }
    vehicleList * current = head;
    while (current->next != NULL)
    {
        current = current->next;
    }
    current->next = newVehicle;
    return head;
}

int writeVehicleFile(vehicleList* head) {
    FILE* fp;
    fp = fopen("vehicle.txt", "w");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return 0;
    }

    vehicleList* current = head;
    while (current != NULL) {
        
        char rentalStartTimeString[20];
        if (current->rentalStartTime != 0) {
            struct tm* timeinfo = localtime(&(current->rentalStartTime));
            strftime(rentalStartTimeString, sizeof(rentalStartTimeString), "%Y-%m-%d %H:%M:%S", timeinfo);
        } else {
            strcpy(rentalStartTimeString, "N/A");
        }

        
        fprintf(fp, "%d;%d;%d;%s;%d;%d;%s\n", current->clientNIF, current->vehichleID, current->isRented, current->location, current->autonomy, current->cost, rentalStartTimeString);

        current = current->next;
    }

    fclose(fp);
    return 1;
}





vehicleList* readVehicleFile(vehicleList* head) {
    FILE* fp;
    fp = fopen("vehicle.txt", "r");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return head;
    }

    char line[200];
    while (fgets(line, sizeof(line), fp)) {
        vehicleList* newVehicle = (vehicleList*)malloc(sizeof(vehicleList));
        if (newVehicle == NULL) {
            printf("Memory allocation failed!\n");
            fclose(fp);
            return head;
        }

        // Extract the data from the line using sscanf
        int nRead = sscanf(line, "%d;%d;%d;%[^;];%d;%d;", &newVehicle->clientNIF, &newVehicle->vehichleID, &newVehicle->isRented,
                           newVehicle->location, &newVehicle->autonomy, &newVehicle->cost);

        if (nRead == 6) {
            newVehicle->rentalStartTime = 0;  // Set rentalStartTime to 0 initially
            newVehicle->next = NULL;

            // Add the new vehicle to the vehicle list
            head = addVehicle(head, newVehicle);
        } else {
            printf("Invalid data format in the file!\n");
            free(newVehicle);
        }
    }

    fclose(fp);
    return head;
}


vehicleList * removeVehicle(vehicleList * head, int vehicleid)
{
    vehicleList * current = head;
    vehicleList * previous = NULL;
    while (current != NULL)
    {
        if (current->vehichleID == vehicleid)
        {
            if (previous == NULL)
            {
                head = current->next;
                free(current);
                return head;
            }
            previous->next = current->next;
            free(current);
            return head;
        }
        previous = current;
        current = current->next;
    }
    return head;
}
vehicleList * searchVehicle(vehicleList * head, int vehicleid)
{
    vehicleList * current = head;
    while (current != NULL)
    {
        if (current->vehichleID == vehicleid)
        {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

int returnVehicle(vehicleList *head, int vehicleid, int clientNIF, clientList *loggedClient)
{
    vehicleList *returnedVehicle = searchVehicle(head, vehicleid);
    if (returnedVehicle == NULL)
    {
        
        return -1; 
    }

    if (returnedVehicle->isRented == false)
    {
        return -2; 
    }

    if (returnedVehicle->clientNIF != clientNIF)
    {
        return -3; 
    }
    
    time_t endTime = time(NULL);
    int cost = returnedVehicle->cost * (int) difftime(endTime,returnedVehicle->rentalStartTime ) / 60;
    printf("Custo da viagem: %d euros\n", cost);
    if (loggedClient != NULL)
    {
        loggedClient->balance =  loggedClient->balance - cost;
    }
    
    returnedVehicle->isRented = false;
    returnedVehicle->clientNIF = 0;
    returnedVehicle->rentalStartTime = 0;
    
    return 0; 
}

bool isLocationOnFile( char* location) {
    FILE* file = fopen("localizacoes.txt", "r");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return false;
    }

    char currentLocation[50];
    while (fscanf(file, "%s", currentLocation) != EOF) {
        // Compare the location with each entry in the file
        if (strcmp(location, currentLocation) == 0) {
            fclose(file);
            return true;
        }
    }

    fclose(file);
    return false;
}

char * getLocationByID(vehicleList *head, int vehicleid)
{
    vehicleList *current = head;
    while (current != NULL)
    {
        if (current->vehichleID == vehicleid)
        {
            return current->location;
        }
        current = current->next;
    }
    return NULL;
}

int rentVehicle(vehicleList *head, int vehicleid, int clientNIF)
{
    vehicleList *rentedVehicle = searchVehicle(head, vehicleid);
    if (rentedVehicle == NULL)
    {
        return -1;
    }
    if (rentedVehicle->isRented)
    {
        return -2;
    }
    rentedVehicle->clientNIF = clientNIF;
    rentedVehicle->isRented = true;
    rentedVehicle->rentalStartTime = time(NULL);
    return 0;
}
