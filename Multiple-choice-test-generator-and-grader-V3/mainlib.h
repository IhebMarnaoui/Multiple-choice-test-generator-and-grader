#ifndef MAINLIB_H
#define MAINLIB_H
#include<iostream>
#include<fstream>
#include<string>
#include<set>
#include <conio.h>
#include <stdlib.h>
#include <time.h>


const std::string UserDirectory="User/";
const std::string QuestionsDirectory="Questions_to_add/";
const std::string StudentAnswersDirectory="Student_Answers/";
const std::string UsersFile="DataBase/Users/users.txt";
const std::string tabulations="\t\t\t";
const std::string spacing="\n\n\n";


 //generate a test ( test file and response file)
void generate_t(){
        cout<<"Please enter the number of questions to add in the test : ";
        int n;
        cin >>n;
        Test t(n);
}
//create a question and add it to the database
void create_question(){

        Question q;
         if(q.addQuestion()){
            COLOR c=GREEN;
            string text ="Question added with success\n";
            colorText(text,c); cout<<endl;
        }
        else
            cout<<"An Error has occurred while adding the question to the database\n";
}
    //load a set of questions from a file
void load_questions_file(){
    string pathFile;
    cout<<"Please enter the name of the file to add : ";
    cin>>pathFile;
    Question::addQuestions(QuestionsDirectory+pathFile);
}
    //grade a test
void grade_test(){
    long int ID;
    string fileStudent;
    cout<<"Please enter the ID of the test to grade : ";
    cin>>ID;
    cout<<"Please enter the file of the test you want to correct : ";
    cin>>fileStudent;
    try{
        TestAnswers t(AnswersDirectory+to_string(ID)+".txt");
        StudentAnswers s(StudentAnswersDirectory+fileStudent);
        t.gradeTest(s);
    } catch(ObjectCouldNotBeCreatedException o){
        COLOR c=RED;
        string text ="An Error has occurred: Invalid Id or file name \n";
        colorText(text,c); cout<<endl;
    }
}
    //grade tests
void grade_tests(){
    string dir;
    long int ID;
    cout<<"Please enter the ID of the test to grade : ";
    cin>>ID;
    cout<<"Please enter the directory of the tests you want to correct : ";
    cin>>dir;
    try{
        TestAnswers t("DataBase/Answers/"+to_string(ID)+".txt");
        t.gradeTests(StudentAnswersDirectory+dir);
    } catch(ObjectCouldNotBeCreatedException o){
        COLOR c=RED;
        string text ="An Error has occurred: invalid ID";
        colorText(text,c); cout<<endl;
    }
}
    //view a test
void view_test(){
    long int ID;
    cout<<"Please enter the ID of the test you want to view : ";
    cin>>ID;
    Test::checkTest(ID);
}
    // print a test
void print_test(){
    long int ID;
    cout<<"Please enter the ID of the test you want to print : ";
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
    bool connectionfailed=false;

    while(!connected){
        system("cls");
        cout<<spacing<<spacing;
        cout<<tabulations<<tabulations<<"________Login________"<<spacing;
        if (connectionfailed){
            COLOR c=RED;
            string text = tabulations+"The username/password you've entered is incorrect. Please check again. \n";
            colorText(text,c); cout<<endl;
        }
        cout<<tabulations<<"\t username: ";
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
            string text ="An Error has occurred while communicating with the database ";
            colorText(text,c); cout<<endl;
            exit(0);
        }
        hash<string> str_hash;
        while ( getline(f,line) ){
            if( line == login+";"+to_string(str_hash(pwd)) ){
                connected=true;
                break;
            }
        }
        f.close();

        if(!connected)
            connectionfailed=true;
        else{
            system("cls");
            COLOR c=GREEN;
            string text= tabulations+tabulations+" Hello "+login;
            cout<<spacing<<spacing;
            colorText(text,c); cout<<endl;
            Sleep(1500);
        }
        system("cls");

    }
}

#endif // MAINLIB_H
