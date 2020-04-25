#include<iostream>
#include<string>
#include<fstream>
#include<list>
#include<stdlib.h>
#include<time.h>
#include<map>
#include"Question.cpp"
#include"TestAnswers.cpp"

using namespace std;

const string TestFile="DataBase/Tests/testId.txt";
const string questionsFile="DataBase/Questions/questions.txt";
const string questionsNb="DataBase/Questions/questionNb.txt";
const string testsDirectory="DataBase/Tests/";

class Test{
    private:
        long int testId;
        list<int> questionId;
        int numberQuestion;
        TestAnswers* answers;
    private:
        bool generateTest(int numberQuestion);
    public:
        Test(int numberQuestion=1);
};
//Test constructor takes by default
Test::Test(int numberQuestion){
    if(numberQuestion <= 0){
        numberQuestion=1;
        cout<<"You entered an invalid number of questions\n";
        cout<<"This test will be generated with the default parameters\n";
    }
    //testId
    ifstream f(TestFile);
    if( !f.is_open() ){
        cout<<"an error occurred while communicating with the database";
        exit(0);
    }
    string str;
    f>>str;
    this->testId=stol(str)+1;
    f.close();
    ofstream ff(TestFile);
    if( !ff.is_open() ){
        cout<<"an error occurred while communicating with the database";
        exit(0);
    }
    ff<<this->testId;
    ff.close();
    //numberQuestion, il faut controler que c'est positif et que ca ne depasse pas le nombre de questions
    this->numberQuestion=numberQuestion;
    //questionId and answers
    if(generateTest(numberQuestion)){
        cout<<"Test generated with success :\n";
        cout<<"\tTest file : "+to_string(testId)+".txt";
    }
}
//used by Test constractor to generate the test file and answers file
bool Test::generateTest(int numberQuestion){
    //questionId and answers
            //*****nb questions total
    ifstream f(questionsNb);
    if( !f.is_open() ){
        cout<<"an error occurred while communicating with the database";
        exit(0);
    }
    string nb;
    f>>nb;
    int numberOfQuestions=stoi(nb);
    f.close();
    if(numberOfQuestions<numberQuestion){
        cout<<" Please enter a number between 1 and "<<numberOfQuestions<<"\n";
        return false;
    }
            //*****on genere les id des questions du qcm
    set<long int> ens;
    srand(time(0));
    do{
        ens.insert(rand()%numberOfQuestions+1);
    }while(ens.size()<numberQuestion);
            //******iterate over the set, recherche des questions
    ifstream q(questionsFile);
    if( !q.is_open() ){
        cout<<"an error occurred while communicating with the database";
        exit(0);
    }
    ofstream t;
    string path=testsDirectory+to_string(testId)+".txt";
    t.open(path, ios::app | ios::out);
    if( !q.is_open() ){
        cout<<"an error occurred while communicating with the database";
        exit(0);
    }
    int i=0;
    string line;
    set<long int>::iterator it;
    map<long int, string> mapp;
    for (it = ens.begin(); it != ens.end(); ++it) {
        while (getline(q,line)){
            i++;
            if(i==*it){
                char* c = const_cast<char*>(line.c_str());
                Question qq(c);
                t<<qq.generateQuestion();
                pair <long int, string> response;
                response.first = qq.getQuestionId();
                response.second = qq.getCorrectAnswer();
                mapp.insert(response);
                break;
            }
        }
    }
    //generate correct answers
    answers=new TestAnswers(testId,mapp);
    q.close();
    return true;

}

