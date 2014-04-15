//
//  main.cpp
//  calProjectOne
//
//  Created by Eduardo Almeida on 14/04/14.
//  Copyright (c) 2014 Bitten Apps. All rights reserved.
//

#include <iostream>

#include "Graph.h"

static double degreesToRadians = 0.0174532925;

static int NOT_CALCULATED = -1;

class Coordinate {
    double _latitude;
    double _longitude;
    
public:
    Coordinate(double lat, double lng) : _latitude(lat), _longitude(lng) {}
    
    bool operator==(const Coordinate &cmp) const {
        return (_latitude == cmp._latitude && _longitude == cmp._longitude);
    }
    
    double distanceTo(const Coordinate &crd) const {
        double dlong = (crd._longitude - _longitude) * degreesToRadians;
        double dlat = (crd._latitude - _latitude) * degreesToRadians;
        double a = pow(sin(dlat/2.0), 2) + cos(_latitude * degreesToRadians) * cos(crd._latitude * degreesToRadians) * pow(sin(dlong/2.0), 2);
        double c = 2 * atan2(sqrt(a), sqrt(1-a));
        double d = 6367 * c;
        
        return d;
    }
};

class City {
    std::string _name;
    
    Coordinate _coordinates;
    
    bool _healthCenter = false;
    
    bool _needsHealthCenter = true;
    
    //  Step One Variables
    
    double _viableCount;
    
    //  Step Two Variables
    
    double _population;
    
    double _maxPopulationServed = NOT_CALCULATED;
    
public:
    City(std::string name, Coordinate crd, int popl = -1) : _name(name), _coordinates(crd), _population(popl) {}
    
    std::string getName() {
        return _name;
    }
    
    Coordinate getCoordinates() {
        return _coordinates;
    }
    
    double distanceTo(const City &city) const {
        return _coordinates.distanceTo(city._coordinates);
    }
    
    void setContainsHealthCenter(bool contains) {
        _healthCenter = contains;
    }
    
    bool getContainsHealthCenter() {
        return _healthCenter;
    }
    
    void setNeedsHealthCenter(bool needs) {
        _needsHealthCenter = needs;
    }
    
    bool getNeedsHealthCenter() {
        return _needsHealthCenter;
    }
    
    void setHealthCenterViableCount(double count) {
        _viableCount = count;
    }
    
    double getHealthCareViableCount() {
        return _viableCount;
    }
    
    bool operator==(const City &cmp) const {
        return (_name == cmp._name && _coordinates == cmp._coordinates);
    }
};

void _methodOneSetupVertex(Vertex<City> *vertex, double maxDistance) {
    //
    //  Fill the vertex object with information about how many cities
    //  it can serve (within a maximum distance) if a health care center
    //  is built on it.
    //
    
    unsigned int viableCount = 0;
    
    vector<Edge<City>> edges = vertex->getAdj();
    
    for (auto it2 = edges.begin(); it2 != edges.end(); ++it2)
        if ((* it2).getWeight() <= maxDistance)
            viableCount++;
    
    City cityInfo = vertex->getInfo();
    
    cityInfo.setHealthCenterViableCount(viableCount);
    
    vertex->setInfo(cityInfo);
}

void fillWithHealthCentersMethodOne(Graph<City> *cityGraph, double maxDistance) {
    //
    //  Construct Graph's Edges
    //
    
    std::vector<Vertex<City> *> vertices = cityGraph->getVertexSet();
    
    std::list<Vertex<City> *> orderedVertices;
    
    for (int i = 0; i < vertices.size(); i++) {
        Vertex<City> *vertex = vertices[i];
        
        for (int j = 0; j < vertices.size() && i < j; j++) {
            Vertex<City> *vertex2 = vertices[j];
            
            double edgeWidth = vertex->getInfo().distanceTo(vertex2->getInfo());
            
            cityGraph->addEdge(vertex->getInfo(), vertex2->getInfo(), edgeWidth);
        }
        
        //
        //  Let's do it this way:
        //
        //  Let's maintain an ordered list (by edge count) of the vertices...
        //  And start filling! (but after. not now.)
        //
        
        _methodOneSetupVertex(vertex, maxDistance);
        
        if (!orderedVertices.size()) {
            orderedVertices.insert(orderedVertices.begin(), vertex);
        } else {
            bool placed = false;
            
            for (auto it = orderedVertices.begin(); it != orderedVertices.end(); ++it) {
                if (vertex->getInfo().getHealthCareViableCount() > (* it)->getInfo().getHealthCareViableCount()) {
                    orderedVertices.insert(it, vertex);
                    
                    placed = true;
                    
                    break;
                }
            }
            
            if (!placed)
                orderedVertices.insert(orderedVertices.end(), vertex);
        }
    }
    
    //
    //  We should now have a graph and an ordered list of vertices.
    //
    
    for (auto it = orderedVertices.begin(); it != orderedVertices.end(); ++it) {
        if ((* it)->getInfo().getNeedsHealthCenter())
            continue;
        
        City newCityInfo = (* it)->getInfo();
        
        newCityInfo.setContainsHealthCenter(true);
        newCityInfo.setNeedsHealthCenter(false);
        
        (* it)->setInfo(newCityInfo);
        
        for (auto it2 = (* it)->getAdj().begin(); it2 != (* it)->getAdj().end(); ++it2) {
            Vertex<City> *dest = (* it2).getDest();
            
            newCityInfo = dest->getInfo();
            
            newCityInfo.setNeedsHealthCenter(false);
            
            dest->setInfo(newCityInfo);
        }
    }
    
    //
    //  Was this it?
    //  Probably not... :|
    //
}

void fillWithHealthCentersMethodTwo(Graph<City> *cityGraph, int healthCenterCount) {
    
}

int main(int argc, const char * argv[]) {
    Graph<City> cityGraph;
    
    fillWithHealthCentersMethodOne(&cityGraph, 5.0f);
    
    std::cout << "Well, at least we got here!" << std::endl;
    
    return EXIT_SUCCESS;
}

