#include"Test.cpp"
#include"mainlib.h"
#include<windows.h>
#include<conio.h>
using namespace std;
                                        //IMPORTANT!! The passwords are the same as the usernames found in Users directory
int main(){

    //set console
    system("MODE CON COLS=115 LINES=35");
    system("Title MULTIPLE CHOICES GENERATOR AND GRADER");
    system("color F0");
    //connect
    connect(UsersFile);
    int menu;
    do
    {
        cout<<endl<<tabulations<<" ----------------------- MENU -----------------------"<<endl<<endl;
        cout<<tabulations<<"1. Generate a test "<<endl;
        cout<<tabulations<<"2. Create a question and add it to the database"<<endl;
        cout<<tabulations<<"3. Load a set of questions from a file"<<endl;
        cout<<tabulations<<"4. Grade a test"<<endl;
        cout<<tabulations<<"5. Grade multiple tests"<<endl;
        cout<<tabulations<<"6. View a previously generated test"<<endl;
        cout<<tabulations<<"7. Print a test"<<endl;
        cout<<tabulations<<"8. Disconnect"<<endl;
        cout<<tabulations<<"Choice : ";
        cin>>menu; cout<<endl;
        string msg="Now we are going to ";
        switch(menu){
            case 1 : cout<<msg<<"generate a question\n"; generate_t(); break;
            case 2 : cout<<msg<<"create a question\n"; create_question() ; break;
            case 3 : cout<<msg<<"load a set of questions from a file\n";load_questions_file(); break;
            case 4 : cout<<msg<<"grade a test\n";grade_test(); break;
            case 5 : cout<<msg<<"grade multiple tests\n";grade_tests(); break;
            case 6 : cout<<msg<<"view a previously generated test\n";view_test(); break;
            case 7 : cout<<msg<<"print a test\n";print_test(); break;
            case 8 : main(); break;
            default :
                COLOR c=RED;
                string text="Please choose a number between 1 and 8 ! ";
                colorText(text,c); cout<<endl;
        }

        cout<<"Press any key to continue .... ";
        char c=getch();
        system("cls");
    }while (true);
    return 0;
}
