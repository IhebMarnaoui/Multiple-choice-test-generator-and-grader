#include<iostream>
#include<cstring>
#include<fstream>
#include<vector>
#include<cstdlib>
#include"Question.h"

#ifndef NEWLIB_H
#define NEWLIB_H
    #include"lib.h"
#endif

using namespace std;

//constructor used to create a new question
Question::Question(){
    this->idQuestion=updateId(QuestionsNb);
    this->fillQuestion();
}
//contructor used to parses a question in the database(string) to a question object
Question::Question(char str[]){
    char * pch=strtok(str,";,");
    vector<char*> v;
    while (pch != NULL){
       v.push_back(pch);
        pch = strtok (NULL, ";,");
    }
    vector<char*>::iterator i;
    i=v.begin();
    idQuestion= atoi(*i);
    i++;
    description= *i;
    i++;
    choices[0]=*i;
    i++;
    choices[1]=*i;
    i++;
    choices[2]=*i;
    i++;
    choices[3]=*i;
    i++;
    choices[4]=*i;
    i++;
    correctAnswer=**i;
}
//contructor used to parses a question from a file
Question::Question(char str[],int a) {
    char * pch=strtok(str,";");
    vector<char*> v;
    while (pch != NULL){
       v.push_back(pch);
        pch = strtok (NULL, ";");
    }
    if( v.size() != 3){
        throw ObjectCouldNotBeCreatedException("An Error has occurred: Invalid number of attributes/Syntax error");
    };

    vector<char*>::iterator it;
    it=v.begin();
    //description
        description= *it;
    it++;
    //choices
        char * ch=strtok(*it,",");
        vector<char*> chv;
        while (ch != NULL){
           chv.push_back(ch);
            ch = strtok (NULL, ",");
        }
        if( chv.size() != 5){
            throw ObjectCouldNotBeCreatedException("An Error has occurred: Invalid number of attributes/Syntax error");
        }
        vector<char*>::iterator i;
        i=chv.begin();
        choices[0]=*i;
        i++;
        choices[1]=*i;
        i++;
        choices[2]=*i;
        i++;
        choices[3]=*i;
        i++;
        choices[4]=*i;
        for(int i=0; i<5; i++){
            string str="";
            str+=char(i+65);
            str+="-";
            if(choices[i].substr(0,2)!=str)
                throw ObjectCouldNotBeCreatedException("Please enter a valid character (A,B,C,D,E)");
        }
    it++;
    //correct answer
        string sstr(*it);
        correctAnswer=**it;
        if(sstr.size()>1 || correctAnswer<'A' || correctAnswer>'E'){
            throw ObjectCouldNotBeCreatedException("Correct answer could not be found");
        }
    //idQuestion
        idQuestion= updateId(QuestionsNb);
}
//string to be used for the test description
string Question::generateQuestion(){
    return ": "+description+"\n\t"+choices[0]+"\n\t"+choices[1]+"\n\t"+choices[2]+"\n\t"+choices[3]+"\n\t"+choices[4]+"\n";
}
//string to be used to add a question
string Question::toString(){
    string st=to_string(idQuestion);
    return st+";"+description+";"+choices[0]+","+choices[1]+","+choices[2]+","+choices[3]+","+choices[4]+";"+correctAnswer;
}
//load a set of questions from a formated file
/**static*/
bool Question::addQuestions(string pathFile){

    string line;
    ifstream f1(pathFile);
    ofstream f(QuestionsFile.c_str(),ios::out | ios::app);
    if ((!f.is_open()) || (!f1.is_open())){
        COLOR c=RED;
        string text = "An Error has occurred while trying to load the file(Please verify the file name) ";
        colorText(text,c); cout<<endl;
        return false ;
    }
    int i=0,j=0;
    while ( getline(f1,line) ){
        i++;
        try{
            Question q(&line[0],1);
            f<<q.toString()<< endl;
            COLOR c=GREEN;
            string text = "The question added with success, line  "+to_string(i);
            colorText(text,c); cout<<"\n\n";
            j++;
        } catch(ObjectCouldNotBeCreatedException &e){
            COLOR c=RED;
            string text = "The question was not added, line "+to_string(i);
            colorText(text,c); cout<<"\n\n";
        }
    }
    COLOR c=GREEN;
    string text = to_string(j)+" Question(s) were added to the database with success \n";
    colorText(text,c); cout<<endl;
    f.close();
    f1.close();
    return true ;
}
//add this object question to the database
/**private*/
bool Question::addQuestion(){
    string qst=this->toString();
    ofstream f(QuestionsFile.c_str(),ios::out | ios::app);
    if (!f.is_open()){
        COLOR c=RED;
        string text = "An Error has occurred while communicating with the database\n";
        colorText(text,c); cout<<endl;
        return false;
    }
    else
    {
        f<<qst<<endl;
    }
    f.close();
    return true;
}
/**private*/
void Question::fillQuestion(){
    COLOR c=BLUE;
    string text ="NOTE: Symbols such as ( ; , ) are not allowed to be used \n";
    colorText(text,c); cout<<endl;
    string description;getline(cin,description);
    size_t found;
    do{
        cout<< "Please enter the description of the question to add: ";
        getline(cin,description);
        found=description.find(";");
    } while( ((description=trim(description)).empty()) || found!=-1 );
    this->description=description;

    string choix="";
    size_t found1=0;found=0;
    cout<< "Now, enter the 5 choices\n";
    for(int i=0;i<5;i++){
        choix="";
        do{
            cout<< "Please enter Choice " << char(i+65) << " : ";
            getline(cin,choix);
            found=choix.find(";");
            found1=choix.find(",");
        } while((choix=trim(choix)).empty() || found!=-1 || found1!=-1);
        string str;
        str+=char(i+65);
        str+="-";
        str+=choix;
        this->choices[i]=str;
    }

    char b;
    while (true){
        cout << "Please enter the correct answer (A,B,C,D,E) : ";
        cin>>b;
        if((b=='A'||b=='a')||(b=='B'||b=='b')||(b=='C'||b=='c')||(b=='D'||b=='d')||(b=='E'||b=='e')){
            correctAnswer=b;
            break;
        }
    }
}

long int Question::getQuestionId(){
    return idQuestion;
}

char Question::getCorrectAnswer(){
    return correctAnswer;
}

int Question::getTotalNumberQuestions(){
    int nb;
    std::string str;
    std::ifstream f(QuestionsNb);
    if( !f.is_open() ){
        COLOR c=RED;
        string text = "An Error has occurred while communicating with the database\n";
        colorText(text,c); cout<<endl;
        return -1;
    } else {
        f>>str;
        f.close();
        return stoi(str);
    }
}


