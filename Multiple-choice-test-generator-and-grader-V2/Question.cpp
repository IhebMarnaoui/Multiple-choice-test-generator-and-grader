#include<iostream>
#include<cstring>
#include<fstream>
#include<vector>
#include<cstdlib>

#ifndef NEWLIB_H
#define NEWLIB_H
    #include"lib.h"
#endif

const std::string QuestionsFile="DataBase/Questions/questions.txt";
const std::string QuestionsNb="DataBase/Questions/questionNb.txt";

using namespace std;

class Question{
    public:
        long int idQuestion;
        string description;
        string choices[5];
        char correctAnswer;
    private:
        void fillQuestion();
        bool addQuestion();
        Question(char str[],int a);
    public:
        Question();
        Question(char str[]);
        string toString();
        static bool addQuestions(string pathFile);
        string generateQuestion();
        long int getQuestionId();
        char getCorrectAnswer();
        static int getTotalNumberQuestions();
};
//constructor used to create a new question
Question::Question(){
    this->idQuestion=updateId(QuestionsNb);
    this->fillQuestion();
    if(this->addQuestion())
        cout<<"Question added with success\n";
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
        throw ObjectCouldNotBeCreatedException("err number of attributs ';'");
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
            throw ObjectCouldNotBeCreatedException("err choices attribut ','");
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
                throw ObjectCouldNotBeCreatedException("err choices attribut (A,B,C,D)");
        }
    it++;
    //correct answer
        string sstr(*it);
        correctAnswer=**it;
        if(sstr.size()>1 || correctAnswer<'A' || correctAnswer>'E'){
            throw ObjectCouldNotBeCreatedException("err correctAnswer attribut");
        }
    //idQuestion
        idQuestion= updateId(QuestionsNb);
}
//string to be used for the test description
string Question::generateQuestion(){
    string st=to_string(idQuestion);
    return st+": "+description+"\n\t"+choices[0]+"\n\t"+choices[1]+"\n\t"+choices[2]+"\n\t"+choices[3]+"\n\t"+choices[4]+"\n";
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
    ifstream f1(pathFile.c_str());
    ofstream f(QuestionsFile.c_str(),ios::out | ios::app);
    if ((!f.is_open()) || (!f1.is_open())){
        COLOR c=RED;
        string text = "error while trying to open the files";
        colorText(text,c); cout<<endl;
        return false ;
    }
    int i=0,j=0;
    while ( getline(f1,line) ){
        i++;
        try{
            Question q(&line[0],1);
            f<<q.toString()<< endl;
            COLOR c=RED;
            string text = "Question added with success, line  "+i;
            colorText(text,c); cout<<"\n\n";
            j++;
        } catch(ObjectCouldNotBeCreatedException &e){
            COLOR c=RED;
            string text = "Question not valid, line "+i;
            colorText(text,c); cout<<"\n\n";
        }
    }
    COLOR c=GREEN;
    string text = j+" question(s) added with success to the database\n";
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
        string text = "an error occurred while communicating with the database\n";
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
    COLOR c=YELLOW;
    string text ="PS: These are forbidden symbols ; and ,\n";
    colorText(text,c); cout<<endl;
    string description;getline(cin,description);
    size_t found;
    do{
        cout<< "Description: ";
        getline(cin,description);
        found=description.find(";");
    } while( ((description=trim(description)).empty()) || found!=-1 );
    this->description=description;

    string choix="";
    size_t found1=0;found=0;
    for(int i=0;i<5;i++){
        choix="";
        do{
            cout<< "Choice " << char(i+65) << " : ";
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
        cout << "Correct answer (A,B,C,D,E) : ";
        cin>>b;
        if((b=='A')||(b=='B')||(b=='C')||(b=='D')||(b=='E')){
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
        string text = "an error occurred while communicating with the database\n";
        colorText(text,c); cout<<endl;
        return -1;
    } else {
        f>>str;
        f.close();
        return stoi(str);
    }
}


