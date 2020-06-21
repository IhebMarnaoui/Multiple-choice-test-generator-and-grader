#include<map>
#include<fstream>
#include<string>
#include<iostream>
#include<cstring>
#include<stdlib.h>
#include"Answers.h"

#ifndef NEWLIB_H
#define NEWLIB_H
    #include"lib.h"
#endif

using namespace std;

//the constructor allows to create a derived Answer object from a formatted file containing the answers of a student
Answers::Answers(string file){
    ifstream t(file);
    if( !t.is_open() ){
        throw ObjectCouldNotBeCreatedException();
    }
    string k,v,s;
    while(getline(t,s)){
        char * pch=&s[0];
        pch = strtok (pch,":");
        string a;
        a=pch;
        pch = strtok (NULL,":");
        string b;
        if(pch==NULL)
            b="Z";
        else
            b=pch;
        long int i = stoi(a);
        answerdetails[i]=b;
    }
    t.close();
}

Answers::Answers(long int AnswersID){
    ofstream t;
    this->AnswersID=AnswersID;
    string path=AnswersDirectory+to_string(AnswersID)+".txt";
    t.open(path);
    t.close();
}

Answers::~Answers() {}
