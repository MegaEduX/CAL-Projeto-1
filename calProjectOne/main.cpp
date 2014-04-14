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
    
public:
    City(std::string name, Coordinate crd) : _name(name), _coordinates(crd) {}
    
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
    
    bool operator==(const City &cmp) const {
        return (_name == cmp._name && _coordinates == cmp._coordinates);
    }
};

void fillWithHealthCenters(Graph<City> *cityGraph) {
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
        
        if (!orderedVertices.size())
            orderedVertices.insert(orderedVertices.begin(), vertex);
        else {
            for (auto it = orderedVertices.begin(); it != orderedVertices.end(); ++it)
                if (vertex->getAdj().size() > (* it)->getAdj().size()) {
                    orderedVertices.insert(it, vertex);
                    
                    break;
                }
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

int main(int argc, const char * argv[]) {
    Graph<City> cityGraph;
    
    fillWithHealthCenters(&cityGraph);
    
    std::cout << "Well, at least we got here!" << std::endl;
    
    return EXIT_SUCCESS;
}

