//@@@@ author : João Duarte - Nº 23553 @@@@
// header file para a estrutura de dados mobilidades
#include <stdbool.h>
#include <time.h>
#include "user.h"
typedef struct vehicleList
{
    int clientNIF;
    int vehichleID;
    bool isRented;
    char * location;
    int autonomy;
    int cost;
    time_t rentalStartTime;
    struct vehicleList * next;
}vehicleList;

bool isLocationOnFile( char location[]);
vehicleList * createVehicle(int vehichleID, int autonomy, int cost, char * location);
vehicleList * addVehicle(vehicleList * head, vehicleList * newVehicle);
vehicleList * removeVehicle(vehicleList * head, int vehicleid);
vehicleList * searchVehicle(vehicleList * head, int vehicleid);
int writeVehicleFile(vehicleList * head);
vehicleList* readVehicleFile(vehicleList * head);
void printVehicle(vehicleList * head);
int  rentVehicle (vehicleList * head, int vehicleid, int clientNIF);
int  returnVehicle (vehicleList * head, int vehicleid, int clientNIF, clientList * loggedCLient);
char * getLocationByID(vehicleList *head, int vehicleid);