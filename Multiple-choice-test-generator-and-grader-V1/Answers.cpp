#include<map>
#include<fstream>
#include<string>
#include<iostream>
#include<cstring>

using namespace std;

const string AnswersDirectory="DataBase/Answers/";

class Answers
{
    public:
        Answers(long int AnswersID);
        Answers(string file);
        void answersConsult();
        virtual ~Answers()=0;
        map < long int , string > answerdetails ;
    protected :
        long int AnswersID;
};
//the constructor allows to create a derived Answer object from a formatted file containing the answers of a student
Answers::Answers(string file){
    ifstream t (file);
    string k,v;
    while(!t.eof()){
        string s;
        getline(t,s);
        /*int l=s.length();
        char tab[l];
        for (int i=0;i<l;i++){
            tab[i]=s[i];
        }*/
        char * pch=const_cast<char*>(s.c_str());
        pch = strtok (pch,":");
        string a;
        a=pch;
        pch = strtok (NULL, ":");
        string b;
        b=pch;
        long int i = stoi(a);
        answerdetails[i]=b;
    }
    cout<<"say hello to the world\n";
}
Answers::Answers(long int AnswersID){
    ofstream t;
    this->AnswersID=AnswersID;
    string path=AnswersDirectory+to_string(AnswersID)+".txt";
    t.open(path);
    t.close();
}
Answers::~Answers() {}