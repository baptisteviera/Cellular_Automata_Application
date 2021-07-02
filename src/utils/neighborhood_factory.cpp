#include "neighborhood_factory.h"

using namespace std;
NeighborhoodStrategy* NeighborhoodFactory::production(const string neighborhoodName) const {
    if(neighborhoodName.rfind("Moore Neighborhood Generalized", 0) == 0) return new MooreNeighborhoodGeneralized(neighborhoodName, 1);
    if(neighborhoodName.rfind("Von Neumann Neighborhood Generalized", 0) == 0) return new VonNeumannNeighborhoodGeneralized(neighborhoodName, 1);
    if(neighborhoodName.rfind("Moore Neighborhood", 0) == 0) return new MooreNeighborhood;
    if(neighborhoodName.rfind("Von Neumann Neighborhood", 0) == 0) return new VonNeumannNeighborhood;
    throw "Unknown Neighborhood";
}

NeighborhoodStrategy* NeighborhoodFactory::production(const string neighborhoodName, const int radius) const {
    if(neighborhoodName.rfind("Moore Neighborhood Generalized", 0) == 0) return new MooreNeighborhoodGeneralized(neighborhoodName, radius);
    if(neighborhoodName.rfind("Von Neumann Neighborhood Generalized", 0) == 0) return new VonNeumannNeighborhoodGeneralized(neighborhoodName, radius);

    throw "Unknown Neighborhood";
}

NeighborhoodStrategy* NeighborhoodFactory::production(const string name, const int nbVoisins, int* dx, int* dy) const {
    return new ArbitraryNeighborhood(nbVoisins, dx, dy, name);
}
