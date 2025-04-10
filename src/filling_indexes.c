#include "pathfinder.h"

bridge *filling_index(struct bridge *bridges, char **islandNames, int vertexCount, int edgeCount) {

    struct bridge *updatedBridges = bridges; 
    
    for (int edgeIndex = 0; edgeIndex < edgeCount; edgeIndex++) { 
        for (int vertexIndex = 0; vertexIndex < vertexCount; vertexIndex++) { 
            if (mx_strcmp(updatedBridges[edgeIndex].island1, islandNames[vertexIndex]) == 0) {
                updatedBridges[edgeIndex].src = vertexIndex;
            } else if (mx_strcmp(updatedBridges[edgeIndex].island2, islandNames[vertexIndex]) == 0) {
                updatedBridges[edgeIndex].dest = vertexIndex; 
            }
        }
    }
    return updatedBridges; 
}
