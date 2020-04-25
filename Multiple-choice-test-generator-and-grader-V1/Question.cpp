#include<iostream>
#include<cstring>
#include<string>
#include<fstream>
#include<vector>
#include<cstdlib>

const std::string pathFile="DataBase/Questions/questions.txt";

using namespace std;

class Question{
   public:
        long int idQuestion;
        string description;
        string choices[5];
        string correctAnswer;
    public:
        Question();
        Question(char str[]);
        string toString();
        static bool addQuestions(string pathFile1);
        bool addQuestion();
        string generateQuestion();
        long int getQuestionId();
        string getCorrectAnswer();
};
//constructor used to create a new question
Question::Question(){
//same code in the Test constructor
//find a way to do it in a function
    //getidquestion from questionnb
    //this->questionId=value+1
    //update the questionnb file
    //allow the user to enter data

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
    correctAnswer=*i;
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
bool Question::addQuestions(string pathFile1){
    //id control to add
    //we have to update number of questions
    string line;
    ifstream f1(pathFile1.c_str());
    ofstream f(pathFile.c_str(),ios::out | ios::app);
    if ((!f.is_open()) || (!f1.is_open())){
        cout<< "error"<< endl;
        return false ;
    }
    while ( getline(f1,line) )
        f<<line<< endl;

    return true ;
}
//allow the user to add this object question to the database
bool Question::addQuestion(){
    //we have to update number of questions
    string qst=this->toString();
    ofstream f(pathFile.c_str(),ios::out | ios::app);
    if (!f.is_open()){
        cout<< "erreur"<< endl;
        return false;
    }
    else
    {
        f<<qst<<endl;
    }
    f.close();
    return true;

}

long int Question::getQuestionId(){
    return idQuestion;
}

string Question::getCorrectAnswer(){
    return correctAnswer;
}


