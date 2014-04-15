//
//  CSVParser.h
//  Radio Station
//
//  T3G12 - MIEIC 2012/2013
//  Eduardo Almeida, Joao Almeida and Joao Ramos
//
//  This class creates and parses CSV files.
//

#ifndef CSVParserHeader
#define CSVParserHeader

#include <iostream>
#include <iomanip>
#include <fstream>

#include <vector>

class CSVParser {
    
private:
    
    std::string _filePath;
    
    std::vector<std::vector<std::string>> _cachedResult;
    
public:
    
    CSVParser();
    CSVParser(std::string filePath);
    
    ~CSVParser();
    
    std::vector<std::vector<std::string>> parseCSV();
    
    std::vector<std::string> tableHeader(bool reparse);
    
    std::vector<std::vector<std::string>> tableRows(bool reparse);
    
    std::string encodeCSV(std::vector<std::vector<std::string>> vecToEncode);
};

#endif
