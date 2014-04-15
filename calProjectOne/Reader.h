//
//  Reader.h
//  calProjectOne
//
//  Created by Eduardo Almeida on 15/04/14.
//  Copyright (c) 2014 Bitten Apps. All rights reserved.
//

#ifndef __calProjectOne__Reader__
#define __calProjectOne__Reader__

#include <iostream>
#include <fstream>

#include "Graph.h"

#include "City.h"

class Reader {
    std::string _filePath;
    
public:
    Reader(std::string path) : _filePath(path) {
        std::ifstream inputTester(path);
        
        if (!inputTester.is_open())
            throw "Can't open file.";
    }
    
    Graph<City> generateGraph();
};

#endif /* defined(__calProjectOne__Reader__) */
