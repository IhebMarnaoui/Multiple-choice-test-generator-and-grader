#include<dirent.h>
#include<errno.h>
#include<map>
#ifndef WIN32
    #include<sys/types.h>
#endif
#include<windows.h>
#include"TestAnswers.h"
#include"StudentAnswer.cpp"

#ifndef NEWLIB_H
#define NEWLIB_H
    #include"lib.h"
#endif

using namespace std;

TestAnswers::TestAnswers(string file):Answers(file){}

TestAnswers::TestAnswers(long int TestAnswersID,map<long int ,string> m): Answers(TestAnswersID) {
    this->answerdetails=m;
    this->generateAnswers();
}

void TestAnswers::generateAnswers(){
    string path=AnswersDirectory+to_string(this->AnswersID)+".txt";
    ofstream t(path);
    map < long int , string >::iterator it;
    for(auto it = this->answerdetails.cbegin(); it != this->answerdetails.cend(); ++it){
        t << it->first << ":" << it->second << endl;
    }

}

double TestAnswers::grade(StudentAnswers S){
    int n=0;
    map < long int , string >::iterator it,ip;
    for(auto ip= S.answerdetails.cbegin(),it = this->answerdetails.cbegin(); ip != S.answerdetails.cend(),it != this->answerdetails.cend(); ++it, ip++){
        if (it->second==ip->second){
            n++;
        }
    }
    return (n*20.0)/answerdetails.size();
}

void TestAnswers::gradeTest(StudentAnswers s){
    COLOR c=GREEN;
    string text ="The grade is: ";
    string ch=to_string(grade(s)).substr(0,5);
    text+= ch;
    colorText(text,c); cout<<endl;
}

void TestAnswers::gradeTests(string DirPath){
    DIR *dir;
    if ((dir = opendir (&DirPath[0])) == NULL) {
        cout<<endl;
        COLOR c=RED;
        string text="Error: No such directory is found";
        colorText(text,c);
        cout<<endl;
    }
    struct dirent *ent;
    string name;
    string FilePath;
    string text="";
    COLOR c=GREEN;
    bool actionPerformed=false;
    while ((ent = readdir (dir)) != NULL) {
        name=ent->d_name;
        if(name!="." && name!=".." && isFile(name) && name!="__grades.txt" ){
            FilePath=DirPath+"/"+name;
            try{
                StudentAnswers s(FilePath);
                double grade=this->grade(s);
                text+=name.substr(0,name.size()-4)+" : ";
                text+=to_string(grade);
                text+='\n';
                cout<<name.substr(0,name.size()-4)+" : ";
                colorText(to_string(grade).substr(0,5),c);
                cout<<'\n';
                actionPerformed=true;
            } catch(ObjectCouldNotBeCreatedException o){
                cout<<"An Error has occurred: Invalid answers file : "<<name;
                text+="An Error has occurred: Invalid answers file : "+name+'\n';
            }
        }
    }
    if(actionPerformed){
        cout<<"Would you like to save the result in a file?(Y/N) :";
        char response;
        cin>>response;
        if(response=='y'||response=='Y'){
            ofstream grades(DirPath+"/__grades.txt");
            grades<<text;
            grades.close();
            string text="Please open the __grades.txt file in the given directory to view the grades\n";
            colorText(text,c);
        }
    }
    closedir(dir);
}

