#ifndef LIB_H
#define LIB_H

#include<iostream>
#include<cstring>
#include<fstream>
#include<windows.h>

const std::string QuestionsFile="DataBase/Questions/questions.txt";
const std::string QuestionsNb="DataBase/Questions/questionNb.txt";
const std::string AnswersDirectory="DataBase/Answers/";
const std::string TestsDirectory="DataBase/Tests/";
const std::string TestFile=TestsDirectory+"testId.txt";

//These are the colors used in the different messages
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

//This funtion updates the different IDs
long int updateId(std::string File){
    long int newId;
    COLOR c=RED;
    std::string str;
    std::ifstream f(File);
    if( !f.is_open() ){
        std::string text ="An Error has occurred while communicating with the database";
        colorText(text,c); std::cout<<'\n';
        exit(0);
    }
    f>>str;
    newId=stol(str)+1;
    f.close();
    std::ofstream ff(File);
    if( !ff.is_open() ){
        std::string text ="An Error has occurred while communicating with the database";
        colorText(text,c); std::cout<<'\n';
        exit(0);
    }
    ff<<newId;
    ff.close();
    return newId;
};

//This function clears unwanted spaces
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

//This Class created Object could no be created exception
class ObjectCouldNotBeCreatedException : public std::exception{
public:
    ObjectCouldNotBeCreatedException(std::string msg=""){
        COLOR c=RED;
        colorText(msg,c);
        std::cout<<'\n';
    }
};

//This function checks if the given object is weather a text file or not
bool isFile(std::string name){
    try{
        return ( (name.substr(name.size()-4,4) == ".txt") );
    } catch(std::out_of_range o){
        return false;
    }
}

//This function verifies the existence of a given file
bool exists(std::string filePath){
    std::ifstream f(filePath);
    return f.is_open();
}

#endif // LIB_H
