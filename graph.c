#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

Node *CreateNode(char *location)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL)
    {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    strcpy(newNode->location, location);
    newNode->numVehicles = 0;
    newNode->numCustomers = 0;
    newNode->numEdges = 0;

    return newNode;
}

void ReadLocationsFromFile(Node graph[], int *numNodes)
{
    FILE *file = fopen("localizacoes.txt", "r");
    if (file == NULL)
    {
        printf("Failed to open the file.\n");
        return;
    }

    char line[MAX_LENGTH];
    while (fgets(line, sizeof(line), file) != NULL)
    {
        line[strcspn(line, "\n")] = '\0';

        // Create or update the node with the location
        Node *newNode = CreateNode(line);
        if (newNode != NULL)
        {
            graph[*numNodes] = *newNode;
            (*numNodes)++;
            free(newNode);
        }
    }

    fclose(file);
}

void addCustomerToNode(Node graph[], int *numNodes, char location[], int vehicleID, int customerID)
{
    int i;
    for (i = 0; i < *numNodes; i++)
    {
        if (strcmp(graph[i].location, location) == 0)
        {
            // Find the location and add the customer ID
            if (graph[i].numCustomers < MAX_CUSTOMERS)
            {
                graph[i].customerIDs[graph[i].numCustomers] = customerID;
                graph[i].numCustomers++;
            }
            return;
        }
    }
}

void AddVehicleToNode(Node graph[], int numNodes,  char *location, int vehicleID)
{
    for (int i = 0; i < numNodes; i++)
    {
        if (strcmp(graph[i].location, location) == 0)
        {
            // Update the vehicle ID if the location matches
            if (graph[i].numVehicles < MAX_VEHICLES)
            {
                graph[i].vehicleIDs[graph[i].numVehicles] = vehicleID;
                graph[i].numVehicles++;
            }
            return;
        }
    }
}

Edge createEdge(const char *destination, int weight)
{
    Edge newEdge;
    strcpy(newEdge.destination, destination);
    newEdge.weight = weight;
    return newEdge;
}

void ReadDistancesFromFile(Node graph[], int numNodes)
{
    FILE *file = fopen("distancias.txt", "r");
    if (file == NULL)
    {
        printf("Failed to open the file.\n");
        return;
    }

    char line[MAX_LENGTH];
    while (fgets(line, sizeof(line), file) != NULL)
    {
        line[strcspn(line, "\n")] = '\0';

        char *source = strtok(line, ";");
        char *destination = strtok(NULL, ";");
        int weight = atoi(strtok(NULL, ";"));

        // Find the source node
        Node *sourceNode = NULL;
        for (int i = 0; i < numNodes; i++)
        {
            if (strcmp(graph[i].location, source) == 0)
            {
                sourceNode = &graph[i];
                break;
            }
        }

        // Find the destination node
        Node *destinationNode = NULL;
        for (int i = 0; i < numNodes; i++)
        {
            if (strcmp(graph[i].location, destination) == 0)
            {
                destinationNode = &graph[i];
                break;
            }
        }

        // Create edges between the nodes if they exist
        if (sourceNode != NULL && destinationNode != NULL)
        {
            if (sourceNode->numEdges < MAX_EDGES)
            {
                Edge newEdge = createEdge(destinationNode->location, weight);
                sourceNode->edges[sourceNode->numEdges] = newEdge;
                sourceNode->numEdges++;
            }
        }
    }

    fclose(file);
}

int GetNodeIndexByLocation(Node graph[], int numNodes, char *location)
{
    for (int i = 0; i < numNodes; i++)
    {
        if (strcmp(graph[i].location, location) == 0)
        {
            return i;
        }
    }

    return -1;
}

void UpdateVehicleInNode(Node graph[], int numNodes,  char *location, int vehicleID, int newVehicleID)
{
    for (int i = 0; i < numNodes; i++)
    {
        if (strcmp(graph[i].location, location) == 0)
        {
            // Find the vehicle in the node and update its information
            for (int j = 0; j < graph[i].numVehicles; j++)
            {
                if (graph[i].vehicleIDs[j] == vehicleID)
                {
                    graph[i].vehicleIDs[j] = newVehicleID;
                    return;
                }
            }
            break;
        }
    }
}

void ListVehiclesInNode(Node graph[], int numNodes,  char *location)
{
    printf("Veiculos na localizacao '%s':\n", location);
    int found = 0;

    for (int i = 0; i < numNodes; i++)
    {
        if (strcmp(graph[i].location, location) == 0)
        {
            Node *node = &graph[i];
            if (node->numVehicles > 0)
            {
                for (int j = 0; j < node->numVehicles; j++)
                {
                    printf("Vehicle ID: %d\n", node->vehicleIDs[j]);
                }
            }
            else
            {
                printf("Nao foram encontrados veiculos na localizacao.\n");
            }
            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("localizacao '%s' nao encontrada.\n", location);
    }
}


void ListVehiclesInRadius(Node graph[], int numNodes,  char *location, int radius)
{
    printf("veiculos num raio de  %d da cidade de  '%s':\n", radius, location);
    int found = 0;

    Node *locationNode = NULL;
    for (int i = 0; i < numNodes; i++)
    {
        if (strcmp(graph[i].location, location) == 0)
        {
            locationNode = &graph[i];
            break;
        }
    }

    if (locationNode == NULL)
    {
        printf("Location not found.\n");
        return;
    }

    // Print the vehicles in the location node
    printf("veiculos em '%s':\n", locationNode->location);
    for (int i = 0; i < locationNode->numVehicles; i++)
    {
        printf("Vehicle ID: %d\n", locationNode->vehicleIDs[i]);
    }
    found = 1;

    // Iterate through all nodes and check their distance from the location node
    for (int i = 0; i < numNodes; i++)
    {
        Node *currentNode = &graph[i];

        if (currentNode != locationNode)
        {
            // Check if there is a direct edge between the location node and the current node
            for (int j = 0; j < locationNode->numEdges; j++)
            {
                if (strcmp(locationNode->edges[j].destination, currentNode->location) == 0)
                {
                    int distance = locationNode->edges[j].weight;

                    if (distance <= radius)
                    {
                        // Print the vehicles in the current node
                        printf("Veiculos em  '%s':\n", currentNode->location);
                        for (int k = 0; k < currentNode->numVehicles; k++)
                        {
                            printf("Vehicle ID: %d\n", currentNode->vehicleIDs[k]);
                        }
                        found = 1;
                    }
                    break;
                }
            }
        }
    }

    if (!found)
    {
        printf("Nao foram encontrados veiculos num raio de %d.\n", radius);
    }
}


void SaveCustomersInGraphToFile(Node graph[], int numNodes) {
    FILE *file = fopen("customersgraph.txt", "w");
    if (file == NULL) {
        printf("Error opening file for writing!\n");
        return;
    }

    int i, j;
    for (i = 0; i < numNodes; i++) {
        Node *node = &graph[i];
        for (j = 0; j < node->numCustomers; j++) {
            fprintf(file, "%s;%d\n", node->location, node->customerIDs[j]);
        }
    }

    fclose(file);
}

void SaveVehiclesInGraphToFile(Node graph[], int numNodes) {
    FILE *file = fopen("vehiclesgraph.txt", "w");
    if (file == NULL) {
        printf("Error opening file for writing!\n");
        return;
    }

    int i, j;
    for (i = 0; i < numNodes; i++) {
        Node *node = &graph[i];
        for (j = 0; j < node->numVehicles; j++) {
            fprintf(file, "%s;%d\n", node->location, node->vehicleIDs[j]);
        }
    }

    fclose(file);
}


void ReadCustomersFromFile(Node graph[], int numNodes) {
    FILE *file = fopen("customersgraph.txt", "r");
    if (file == NULL) {
        printf("Error opening customers file for reading!\n");
        return;
    }

    char line[MAX_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        char *token = strtok(line, ";");
        if (token != NULL) {
            char location[MAX_LENGTH];
            strcpy(location, token);

            token = strtok(NULL, ";");
            if (token != NULL) {
                int customerID = atoi(token);

                int nodeIndex = GetNodeIndexByLocation(graph, numNodes, location);
                if (nodeIndex != -1) {
                    Node *node = &graph[nodeIndex];
                    if (node->numCustomers < MAX_CUSTOMERS) {
                        node->customerIDs[node->numCustomers] = customerID;
                        node->numCustomers++;
                    } else {
                        printf("Maximum number of customers reached for node %s\n", location);
                    }
                } else {
                    printf("Invalid location found in customers file: %s\n", location);
                }
            }
        }
    }

    fclose(file);
    printf("Customers read from file successfully!\n");
}

void ReadVehiclesFromFile(Node graph[], int numNodes) {
    FILE *file = fopen("vehiclesgraph.txt", "r");
    if (file == NULL) {
        printf("Error opening vehicles file for reading!\n");
        return;
    }

    char line[MAX_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        char *token = strtok(line, ";");
        if (token != NULL) {
            char location[MAX_LENGTH];
            strcpy(location, token);

            token = strtok(NULL, ";");
            if (token != NULL) {
                int vehicleID = atoi(token);

                int nodeIndex = GetNodeIndexByLocation(graph, numNodes, location);
                if (nodeIndex != -1) {
                    Node *node = &graph[nodeIndex];
                    if (node->numVehicles < MAX_VEHICLES) {
                        node->vehicleIDs[node->numVehicles] = vehicleID;
                        node->numVehicles++;
                    } else {
                        printf("Maximum number of vehicles reached for node %s\n", location);
                    }
                } else {
                    printf("Invalid location found in vehicles file: %s\n", location);
                }
            }
        }
    }

    fclose(file);
    printf("Vehicles read from file successfully!\n");
}


void removeCustomerFromNode(Node graph[], int numNodes, char *location, int customerID) {
    int nodeIndex = GetNodeIndexByLocation(graph, numNodes, location);
    if (nodeIndex == -1) {
        printf("localizacao '%s' nao encontrada.\n", location);
        return;
    }

    
    Node *node = &graph[nodeIndex];

    
    int i;
    int customerIndex = -1;
    for (i = 0; i < node->numCustomers; i++) {
        if (node->customerIDs[i] == customerID) {
            customerIndex = i;
            break;
        }
    }

    if (customerIndex == -1) {
        printf("Cliente com ID '%s' nao encontrado no grafo.\n", customerID, location);
        return;
    }

    for (i = customerIndex; i < node->numCustomers - 1; i++) {
        node->customerIDs[i] = node->customerIDs[i + 1];
    }
    node->numCustomers--;
}
