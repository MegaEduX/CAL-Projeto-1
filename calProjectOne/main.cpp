//
//  main.cpp
//  calProjectOne
//
//  Created by Eduardo Almeida on 14/04/14.
//  Copyright (c) 2014 Bitten Apps. All rights reserved.
//

#include <iostream>

#include "Graph.h"

#include "Coordinate.h"
#include "City.h"

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

void _fillByOrder(std::list<Vertex<City> *> orderedVertices, double maxDistance = NOT_CALCULATED, int maxHospitals = NOT_CALCULATED) {
    for (auto it = orderedVertices.begin(); it != orderedVertices.end(); ++it) {
        if (!(* it)->getInfo().getNeedsHealthCenter())
            continue;
        
        City cityInfo = (* it)->getInfo();
        
        cityInfo.setContainsHealthCenter(true);
        cityInfo.setNeedsHealthCenter(false);
        
        (* it)->setInfo(cityInfo);
        
        for (auto it2 = (* it)->getAdj().begin(); it2 != (* it)->getAdj().end(); ++it2) {
            if (maxHospitals != NOT_CALCULATED) {
                if (!maxHospitals)
                    break;
                
                maxHospitals--;
            }
            
            Vertex<City> *dest = (* it2).getDest();
            
            City newCityInfo = dest->getInfo();
            
            if (maxDistance != NOT_CALCULATED && newCityInfo.distanceTo(cityInfo) > maxDistance)
                continue;
            
            newCityInfo.setNeedsHealthCenter(false);
            
            dest->setInfo(newCityInfo);
        }
    }
}

void fillWithHealthCentersMethodOne(Graph<City> *cityGraph, double maxDistance) {
    //
    //  Construct Graph's Edges
    //
    
    std::vector<Vertex<City> *> vertices = cityGraph->getVertexSet();
    
    std::list<Vertex<City> *> orderedVertices;
    
    for (int i = 0; i < vertices.size(); i++) {
        Vertex<City> *vertex = vertices[i];
        
        for (int j = i; j < vertices.size(); j++) {
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
        
        if (!orderedVertices.size())
            orderedVertices.insert(orderedVertices.begin(), vertex);
        else {
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
    
    _fillByOrder(orderedVertices, maxDistance);
    
    //
    //  Was this it?
    //  Probably not... :|
    //
}

void fillWithHealthCentersMethodTwo(Graph<City> *cityGraph, int healthCenterCount) {
    //
    //  Construct Graph's Edges
    //
    
    std::vector<Vertex<City> *> vertices = cityGraph->getVertexSet();
    
    std::list<Vertex<City> *> orderedVertices;
    
    for (int i = 0; i < vertices.size(); i++) {
        Vertex<City> *vertex = vertices[i];
        
        int populationServed = vertex->getInfo().getPopulation();
        
        for (int j = 0; j < vertex->getAdj().size(); j++)
            populationServed += vertex->getAdj()[j].getDest()->getInfo().getPopulation();
        
        City info = vertex->getInfo();
        
        info.setMaxPopulationServed(populationServed);
        
        vertex->setInfo(info);
    }
    
    for (int i = 0; i < vertices.size(); i++) {
        Vertex<City> *vertex = vertices[i];
        
        if (!orderedVertices.size())
            orderedVertices.insert(orderedVertices.begin(), vertex);
        else {
            bool placed = false;
            
            for (auto it = orderedVertices.begin(); it != orderedVertices.end(); ++it) {
                if (vertex->getInfo().getMaxPopulationServed() > (* it)->getInfo().getMaxPopulationServed()) {
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
    
    _fillByOrder(orderedVertices, NOT_CALCULATED, healthCenterCount);
    
    //
    //  Was this it?
    //  Probably not... :|
    //
}

int main(int argc, const char * argv[]) {
    Graph<City> cityGraph;
    
    cityGraph.addVertex(City("Maia", Coordinate(10, 10)));
    cityGraph.addVertex(City("Porto", Coordinate(20, 20)));
    //  cityGraph.addVertex(City("Cerveira", Coordinate(10.00001f, 10.00001f)));
    
    Graph<City> cityGraphTwo;
    
    fillWithHealthCentersMethodOne(&cityGraph, 5.0f);
    fillWithHealthCentersMethodTwo(&cityGraphTwo, 2);
    
    std::cout << "Well, at least we got here!" << std::endl;
    
    return EXIT_SUCCESS;
}

