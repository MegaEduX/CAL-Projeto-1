//
//  Reader.cpp
//  calProjectOne
//
//  Created by Eduardo Almeida on 15/04/14.
//  Copyright (c) 2014 Bitten Apps. All rights reserved.
//

#include "Reader.h"

#include "CSVParser.h"

#include "Graph.h"

#include "Coordinate.h"
#include "City.h"

typedef enum {
    kCellName,
    kCellCoordinateLatitude,
    kCellCoordinateLongitude,
    kCellPopulation
} kCell;

Graph<City> Reader::generateGraph() {
    Graph<City> graph;
    
    CSVParser parser = CSVParser(_filePath);
    
    std::vector< std::vector<std::string> > parsed = parser.parseCSV();
    
    for (int i = 0; i < parsed.size(); i++) {
        std::string name;
        
        double latitude, longitude;
        
        int population;
        
        for (int j = 0; j < parsed[i].size(); j++) {
            std::string cell = parsed[i][j];
            
            switch (j) {
                case kCellName:
                    
                    name = cell;
                    
                    break;
                    
                case kCellCoordinateLatitude:
                    
                    latitude = atof(cell.c_str());
                    
                    break;
                    
                case kCellCoordinateLongitude:
                    
                    longitude = atof(cell.c_str());
                    
                    break;
                    
                case kCellPopulation:
                    
                    population = atoi(cell.c_str());
                    
                    break;
                    
                default:
                    
                    break;
            }
        }
        
        graph.addVertex(City(name, Coordinate(latitude, longitude), population));
    }
    
    for (int i = 0; i < graph.getVertexSet().size(); i++) {
        Vertex<City> *vertex = graph.getVertexSet()[i];
        
        for (int j = i; j < graph.getVertexSet().size(); j++) {
            Vertex<City> *vertex2 = graph.getVertexSet()[j];
            
            graph.addEdge(vertex->getInfo(), vertex2->getInfo(), vertex->getInfo().distanceTo(vertex2->getInfo()));
        }
    }
    
    return graph;
}
