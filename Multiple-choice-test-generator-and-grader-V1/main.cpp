#include<iostream>
#include<fstream>
#include<string>
#include<set>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include"Test.cpp"

using namespace std;

void connect(string);
int main(){
    //connect
    connect("DataBase/Users/users.txt");
    cout<<"**********************************\n";

    //generate a test ( test file and response file)
    cout<<"entrer le nombre de question du test: ";
    int n;
    cin >>n;
    Test t(n);
    cout<<"\n**********************************\n";

    //create a question and add it to the database
    char ch[]="25;Cassius Clay changed his name to;Armstrong,Dallas,First,Muhammed Ali,Nirvana;Muhammed Ali";
    Question q(ch);
    cout<<"The question to add is: "<<q.toString()<<"\n";
    q.addQuestion();
    cout<<"\n**********************************\n";

    //load a set of questions from a file
    cout<<"Load questions from a file\n";
    Question::addQuestions("Others/QuestionsToAdd.txt");
    cout<<"\n**********************************\n";

    //grade a test
    TestAnswers tt("DataBase/Answers/49.txt");
    StudentAnswers s("Others/StudentNameLastname.txt");
    tt.gradeTest(s);
    return 0;
}


void connect(string usersFile){
    const char ENTER = 13;
    string login, pwd, line;
    char ch;
    bool connected=false;

     while(!connected){

        cout<<"please login\n";
        cout<<"login:"; cin>>login;
        cout<<"passeword:";
        pwd="";
        while((ch = _getch()) != ENTER){
            pwd += ch;
            cout << '*';
        }
        cout<<'\n';

        ifstream f(usersFile);
        if( !f.is_open() ){
            cout<<"an error occurred while communicating with the database";
            exit(0);
        }

        while ( getline(f,line) )
        {
            if( line == login+";"+pwd ){
                cout<<"Hello "+login<<'\n';
                connected=true;
                break;
            }
        }

        f.close();
    }
}

