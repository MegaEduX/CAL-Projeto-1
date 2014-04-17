//
//  Reader.h
//  CAL Project One
//
//  MIEIC 2013/2014
//  Eduardo Almeida, Joao Almeida and Joao de Figueiredo
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
