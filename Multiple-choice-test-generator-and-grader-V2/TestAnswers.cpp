#include<dirent.h>
#include<errno.h>
#ifndef WIN32
    #include<sys/types.h>
#endif
#include<windows.h>
#include"StudentAnswer.cpp"

#ifndef NEWLIB_H
#define NEWLIB_H
    #include"lib.h"
#endif

//TestAnswers class
class TestAnswers : public Answers{
    private:
        void generateAnswers();
    public:
        TestAnswers(string file);
        TestAnswers(long int TestAnswersID,map<long int ,string> m);
        void gradeTest(StudentAnswers S);
        void gradeTests(string DirPath);
        ~TestAnswers(){};
};

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

void TestAnswers::gradeTest(StudentAnswers S){
    int i,n=0;
    map < long int , string >::iterator it,ip;
    for(auto ip= S.answerdetails.cbegin(),it = this->answerdetails.cbegin(); ip != S.answerdetails.cend(),it != this->answerdetails.cend(); ++it, ip++){
        if (it->second==ip->second){
            n++;
        }
    }
    double s=(n*20.0)/answerdetails.size();
    COLOR c=GREEN;
    string text ="The grade is: ";
    text+=s;
    colorText(text,c); cout<<endl;
}

void TestAnswers::gradeTests(string DirPath){
    DIR *dir;
    if ((dir = opendir (&DirPath[0])) == NULL) {
        perror("Error");
    }
    struct dirent *ent;
    string name;
    string FilePath;
    while ((ent = readdir (dir)) != NULL) {
        name=ent->d_name;
        if(name!="." && name!=".." && isFile(name)){
            FilePath=DirPath+"/"+name;
            try{
                StudentAnswers s(FilePath);
                cout<<name.substr(0,name.size()-4)<<" : ";  this->gradeTest(s);
            } catch(ObjectCouldNotBeCreatedException o){
                COLOR c=RED;
                string text = "error Invalid student answers file : "+name;
                colorText(text,c); cout<<endl;
            }
        }
    }
    closedir(dir);
}

