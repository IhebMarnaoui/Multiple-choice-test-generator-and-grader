#include"Test.cpp"
#include"mainlib.h"
#include<windows.h>
using namespace std;

int main(){

    //set console
    system("MODE CON COLS=115");
    system("Title MULTIPLE CHOICES GENERATOR AND GRADER");
    system("color F0");
    //connect
    connect(UsersFile);
    int menu;
    do
    {
        cout<<endl<<tabulations<<" ----------------------- MENU -----------------------"<<endl<<endl;
        cout<<tabulations<<"1. generate a test "<<endl;
        cout<<tabulations<<"2. create a question and add it to the database"<<endl;
        cout<<tabulations<<"3. load a set of questions from a file"<<endl;
        cout<<tabulations<<"4. grade a test"<<endl;
        cout<<tabulations<<"5. grade multiple tests"<<endl;
        cout<<tabulations<<"6. check a test"<<endl;
        cout<<tabulations<<"7. print a test"<<endl;
        cout<<tabulations<<"8. disconnect"<<endl;
        cout<<tabulations<<"Choice : ";
        cin>>menu; cout<<endl;
        switch(menu){
            case 1 : generate_t(); break;
            case 2 : create_question() ; break;
            case 3 : load_questions_file(); break;
            case 4 : grade_test(); break;
            case 5 :  grade_tests(); break;
            case 6 :  check_test(); break;
            case 7 :  print_test(); break;
            case 8 :  main(); break;
            default :
                cout<<"choose a number between 1 and 8 ! ";
        }
    }while (true);
    return 0;
}
