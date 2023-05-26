#define MAX_LENGTH 100
#define MAX_VEHICLES 100
#define MAX_CUSTOMERS 100
#define MAX_NODES 10
#define MAX_EDGES 100

typedef struct {
    char destination[MAX_LENGTH];  // Destination node
    int weight;       // Weight of the edge
} Edge;

typedef struct node{
    char location[MAX_LENGTH];
    int vehicleIDs[MAX_VEHICLES];
    int customerIDs[MAX_CUSTOMERS];
    int numVehicles;
    int numCustomers;
    Edge edges[MAX_EDGES];  
    int numEdges;           
} Node;



void UpdateVehicleInNode(Node graph[], int numNodes,  char *location, int vehicleID, int newVehicleID);
void saveGraphToFile(Node graph[], int numNodes);
void readGraphFromFile(Node graph[], int *numNodes);
void ListVehiclesInRadius(Node graph[], int numNodes,  char *location, int radius);
void ReadLocationsFromFile(Node graph[], int *numNodes);
int GetNodeIndexByLocation(Node graph[], int numNodes, char *location);
Node *CreateNode(char *location);;
void AddVehicleToNode(Node graph[], int numNodes,  char *location, int vehicleID);
void addCustomerToNode(Node graph[], int *numNodes, char location[], int vehicleID, int customerID);
void ReadDistancesFromFile(Node graph[], int numNodes);
Edge createEdge(const char *destination, int weight);
void ListVehiclesInNode(Node graph[], int numNodes,  char *location);
void removeCustomerFromNode(Node graph[], int numNodes, char *location, int customerID);
void ReadVehiclesFromFile(Node graph[], int numNodes);
void ReadCustomersFromFile(Node graph[], int numNodes);
void SaveVehiclesInGraphToFile(Node graph[], int numNodes);
void SaveCustomersInGraphToFile(Node graph[], int numNodes);