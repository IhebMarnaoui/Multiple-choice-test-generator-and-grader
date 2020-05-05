#ifndef LIB_H
#define LIB_H

#include<iostream>
#include<cstring>
#include<fstream>
#include<windows.h>

enum COLOR{RED,BLUE,GREEN,YELLOW};
void colorText(std::string text, COLOR c){
    int foregroundColor=0;
    switch(c){
        case RED: foregroundColor=FOREGROUND_RED; break;
        case GREEN: foregroundColor=FOREGROUND_GREEN; break;
        case BLUE: foregroundColor=FOREGROUND_BLUE; break;
        case YELLOW: foregroundColor= FOREGROUND_RED | FOREGROUND_GREEN; break;
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                            foregroundColor | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
    std::cout<<text;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
}

long int updateId(std::string File){
    long int newId;
    COLOR c=RED;
    std::string str;
    std::ifstream f(File);
    if( !f.is_open() ){
        std::string text ="an error occurred while communicating with the database, cant't access the number file";
        colorText(text,c); std::cout<<'\n';
        exit(0);
    }
    f>>str;
    newId=stol(str)+1;
    f.close();
    std::ofstream ff(File);
    if( !ff.is_open() ){
        std::string text ="an error occurred while communicating with the database, cant't access the number file";
        colorText(text,c); std::cout<<'\n';
        exit(0);
    }
    ff<<newId;
    ff.close();
    return newId;
};

std::string trim(const std::string &s){
	auto start = s.begin();
	while (start != s.end() && std::isspace(*start)) {
		start++;
	}

	auto end = s.end();
	do {
		end--;
	} while (std::distance(start, end) > 0 && std::isspace(*end));

	return std::string(start, end + 1);
}

class ObjectCouldNotBeCreatedException : public std::exception{
public:
    ObjectCouldNotBeCreatedException(std::string msg=""){
        COLOR c=RED;
        colorText(msg,c);
        std::cout<<'\n';
    }
};

bool isFile(std::string name){
    try{
        return ( (name.substr(name.size()-4,4) == ".txt") );
    } catch(std::out_of_range o){
        return false;
    }
}

bool exists(std::string filePath){
    std::ifstream f(filePath);
    return f.is_open();
}

#endif // LIB_H
