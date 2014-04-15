//
//  Additions.cpp
//  Radio Station
//
//  T3G12 - MIEIC 2012/2013
//  Eduardo Almeida, Joao Almeida and Joao Ramos
//

#include "Additions.h"

#ifdef WIN32 // Windows includes
#include <windows.h>
#include <conio.h>
#else // Non-Windows (POSIX) includes
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#endif

#ifndef WIN32
int _getch() {
    struct termios oldt,
    newt;
    int            ch;
    tcgetattr( STDIN_FILENO, &oldt );
    newt = oldt;
    newt.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newt );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
    return ch;
}
#endif

namespace Additions {
    void waitForReturn() {
        while (true) { // Wait 'till Keyboard hit ...
            int ch = _getch();
            
            if (ch == 13 || ch == 10)
                break;
        }
    }
    
    std::vector<std::string> explode(const std::string &delimiter, const std::string &str) {
        std::vector<std::string> arr;
        
        int strleng = (int) str.length();
        int delleng = (int) delimiter.length();
        
        if (delleng == 0)
            return arr;
        
        int i = 0;
        int k = 0;
        
        while (i < strleng) {
            int j = 0;
            while (i + j < strleng && j < delleng && str[i + j] == delimiter[j])
                j++;
            
            if (j == delleng) {
                arr.push_back(str.substr(k, i-k));
                i += delleng;
                k = i;
            } else {
                i++;
            }
        }
        
        arr.push_back(str.substr(k, i-k));
        return arr;
    }
    
    std::string get_file_contents(const char *filename) {
        std::ifstream in (filename, std::ios::in | std::ios::binary);
        
        if (in) {
            std::string contents;
            in.seekg(0, std::ios::end);
            contents.resize((unsigned int)in.tellg());
            in.seekg(0, std::ios::beg);
            in.read(&contents[0], contents.size());
            in.close();
            return(contents);
        }
        
        throw(errno);
    }
    
    //
    // Asks for a string, but allows the user to simply press
    // return in order to accept the default value.
    //
    
    bool gotESC(std::string str) {
        return !str.compare(esc);
    }
    
    //
    //  This is basically std::getline, with a few key differences:
    //      - Allows the return of an empty string;
    //      - Allows the user to cancel the input by pressing ESC (which is then checked with getESC()
    //
    
	//
	//	Also, this function needed to work on Windows and POSIX systems.
	//	As of that, it is a bit different when compiled for both.
	//
	//	We are sorry for the mess of the code it is, but that is the price to pay for portability, I guess!
	//
    
    std::string getline() {
        char ch = _getch();
        
        if ((int)ch == 13 || (int)ch == 10)
            return "";
        
        std::string str = "";
        
        while ((int)ch != 13 && (int)ch != 10) {
			bool biggerThanZero = false;
            
            if ((int) ch == 27)   // The ESC key was pressed.
                return esc;
            
            if ((int)ch == 127 || (int)ch == 8) {
                if (str.size() > 0) {
                    str = str.erase(str.size() - 1);
#ifndef WIN32
                    std::cout << '\b';
#endif
                    std::cout << " ";
                    std::cout << '\b';
                    
#ifdef WIN32
					std::cout << '\b';
					std::cout << " ";
#endif
					biggerThanZero = true;
                }
            } else
#ifdef WIN32
                if ((int) ch != 8)
#endif
					str += std::string(&ch)[0];
            
#ifdef WIN32
			if ((int) ch != 8 || biggerThanZero)
#endif
				std::cout << std::string(&ch)[0];
            
            ch = _getch();
        }
        
        return str;
    }
    
    bool checkForOnlyNumeric(std::string str) {
        return str.find_first_not_of("0123456789") == std::string::npos;
    }
    
    void clearConsole() {
#ifndef WIN32
        write(1,"\E[H\E[2J",7);
#else
        COORD upperLeftCorner = {0,0};
        DWORD charsWritten;
        DWORD conSize;
        HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO  csbi;
        
        GetConsoleScreenBufferInfo(hCon, &csbi);
        conSize = csbi.dwSize.X * csbi.dwSize.Y;
        
        FillConsoleOutputCharacter(hCon, TEXT(' '), conSize, upperLeftCorner, &charsWritten);
        GetConsoleScreenBufferInfo(hCon, &csbi);
        FillConsoleOutputAttribute(hCon, csbi.wAttributes, conSize, upperLeftCorner, &charsWritten);
        
        SetConsoleCursorPosition(hCon, upperLeftCorner);
#endif
    }
}
