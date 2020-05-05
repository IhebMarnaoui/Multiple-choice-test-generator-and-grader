#ifndef MAINLIB_H
#define MAINLIB_H

#include<iostream>
#include<fstream>
#include<string>
#include<set>
#include <conio.h>
#include <stdlib.h>
#include <time.h>


const std::string OtherFiles="Others/";
const std::string UsersFile="DataBase/Users/users.txt";
const std::string tabulations="\t\t\t";
const std::string spacing="\n\n\n";


 //generate a test ( test file and response file)
void generate_t(){
        cout<<"the number of question in the test: ";
        int n;
        cin >>n;
        Test t(n);
}
    //create a question and add it to the database
void create_question(){
        Question q;
}
    //load a set of questions from a file
void load_questions_file(){
    string pathFile;
    cout<<"the path of file to add :";
    cin>>pathFile;
    Question::addQuestions(pathFile);
}
    //grade a test
void grade_test(){
    long int ID;
    string fileStudent;
    cout<<"the ID of the test to grade : ";
    cin>>ID;
    cout<<"the file of student answer : ";
    cin>>fileStudent;
    try{
        TestAnswers t(AnswersDirectory+to_string(ID)+".txt");
        StudentAnswers s(OtherFiles+fileStudent);
        t.gradeTest(s);
    } catch(ObjectCouldNotBeCreatedException o){
        COLOR c=RED;
        string text ="error Invalid Id test or student answers file\n";
        colorText(text,c); cout<<endl;
    }
}
    //grade tests
void grade_tests(){
    string dir;
    long int ID;
    cout<<"the ID of the test to grade ";
    cin>>ID;
    cout<<"the diroctory studentanswers :";
    cin>>dir;
    try{
        TestAnswers t("DataBase/Answers/"+to_string(ID)+".txt");
        t.gradeTests(dir);
    } catch(ObjectCouldNotBeCreatedException o){
        COLOR c=RED;
        string text ="error Invalid Id test or student answers file\n";
        colorText(text,c); cout<<endl;
    }
}
    //check a test
void check_test(){
    long int ID;
    cout<<"ID of the test to check :";
    cin>>ID;
    Test::checkTest(ID);
}
    // print a test
void print_test(){
    long int ID;
    cout<<"ID of the test to print with the printer :";
    cin>>ID;
    Test::printTest(ID);
}
    //conection
void connect(string usersFile){
    const char ENTER=13;
    const char DEL=127;
    const char BACKSPACE=8;

    string login, pwd, line;
    char ch;
    bool connected=false;

    while(!connected){
        system("cls");
        cout<<spacing<<spacing;
        cout<<tabulations<<tabulations<<"________Login________"<<spacing;
        cout<<tabulations<<"\t user: ";
        cin>>login;
        cout<<'\n';
        cout<<tabulations<<"\t passeword: ";
        pwd="";
        while( (ch=getch()) != ENTER ){
            if( (ch==DEL || ch==BACKSPACE)){
                if(pwd.size()==0)
                    continue;
                pwd=pwd.substr(0,pwd.size()-1);
                printf("\b \b");
            }
            else{
                pwd += ch;
                cout << '*';
            }
        }
        cout<<'\n';

        ifstream f(usersFile);
        if( !f.is_open() ){
            COLOR c=RED;
            string text ="an error occurred while communicating with the database, impossible to connect";
            colorText(text,c); cout<<endl;
            exit(0);
        }
        hash<string> str_hash;
        while ( getline(f,line) ){
            if( line == login+";"+to_string(str_hash(pwd)) ){
                cout<<"Hello "+login<<'\n';
                connected=true;
                break;
            }
        }
        f.close();

        system("cls");
    }
}
#endif // MAINLIB_H
