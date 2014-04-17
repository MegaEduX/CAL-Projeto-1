//
//  CSVParser.cpp
//  Code taken from: Radio Station
//
//  T3G12 - MIEIC 2012/2013
//  Eduardo Almeida, Joao Almeida and Joao Ramos
//

#include "CSVParser.h"

#include "Additions.h"

CSVParser::CSVParser() {
    
}

CSVParser::CSVParser(std::string filePath) {
    _filePath = filePath;
}

CSVParser::~CSVParser() {
    
}

//
//  parseCSV()
//
//  Return Format:
//      <vector> - representing a file
//          <vector> - representing a line
//              <string> - representing a cell
//

std::vector<std::vector<std::string>> CSVParser::parseCSV() {
    std::vector<std::vector<std::string>> returnVec;
    
    std::ifstream ifile (_filePath);
    
    std::string line;
    
    while (std::getline(ifile, line))
        returnVec.push_back(Additions::explode(",", line));
    
    _cachedResult = returnVec;
    
    return returnVec;
}

std::vector<std::string> CSVParser::tableHeader(bool reparse) {
    if (_cachedResult.size() == 0 || reparse)
        parseCSV();
    
    return _cachedResult[0];
}

std::vector<std::vector<std::string>> CSVParser::tableRows(bool reparse) {
    if (_cachedResult.size() == 0 || reparse)
        parseCSV();
    
    std::vector<std::vector<std::string>> returnVec;
    
    for (unsigned int i = 1; i < _cachedResult.size(); i++)
        returnVec.push_back(_cachedResult[i]);
    
    return returnVec;
}

std::string CSVParser::encodeCSV(std::vector<std::vector<std::string>> vecToEncode) {
    std::string returnStr;
    
    for (unsigned int i = 0; i < vecToEncode.size(); i++) {
        for (unsigned int j = 0; j < vecToEncode[i].size(); j++) {
            returnStr.append(vecToEncode[i][j]);
            
            if (j + 1 != vecToEncode[i].size())
                returnStr.append(","); // Do not append a , on EOL
        }
        
        if (i + 1 != vecToEncode.size())
            returnStr.append("\n"); // Do not append a \n on EOF
    }
    
    return returnStr;
}
