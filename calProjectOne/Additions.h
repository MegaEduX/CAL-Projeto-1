//
//  Additions.h
//  Code taken from: Radio Station
//
//  T3G12 - MIEIC 2012/2013
//  Eduardo Almeida, Joao Almeida and Joao Ramos
//
//  This namespace contains functions used on various parts of the program.
//

#ifndef AdditionsHeader
#define AdditionsHeader

#include <iostream>
#include <sstream>
#include <fstream>
#include <cerrno>
#include <vector>

#ifndef WIN32
int _getch();	// This is not an ISO function, so it's not available on POSIX-systems. Our solution? Let's make our own!
#endif

static const std::string esc = "__\\esc_key_pressed\\__";	// I seriously doubt that anyone will type this into a field.

namespace Additions {
    std::vector<std::string> explode(const std::string &delimiter, const std::string &str);
    
    // We ended up not using get_file_contents, but eh.
    
    std::string get_file_contents(const char *filename);
    
    std::string getline();
    
    bool checkForOnlyNumeric(std::string str);
    
    bool gotESC(std::string str);
    
    void clearConsole();
    
    void waitForReturn();
}

#endif
