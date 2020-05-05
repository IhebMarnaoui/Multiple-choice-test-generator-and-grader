#include<iostream>
#include<string>
#include<fstream>
#include<list>
#include<cstdlib>
#include<time.h>
#include<map>
#include<set>
#include"Question.cpp"
#include"TestAnswers.cpp"

using namespace std;

const string TestsDirectory="DataBase/Tests/";
const string TestFile=TestsDirectory+"testId.txt";

class Test{
    private:
        long int testId;
        list<int> questionId;
        int numberQuestion;
        TestAnswers* answers;
    private:
        bool generateTest(int numberQuestion);
    public:
        Test(int numberQuestion=0);
        static void printTest(long int id);
        static void checkTest(long int id);
};
//Test constructor takes by default
Test::Test(int numberQuestion){
    //testId
    this->testId=updateId(TestFile);
    //control the numberQuestion
    int nbMax=Question::getTotalNumberQuestions();
    if(nbMax == -1)
        throw ObjectCouldNotBeCreatedException();
    if(numberQuestion <= 0 || numberQuestion>nbMax){
        numberQuestion=nbMax;
            COLOR c=YELLOW;
            string text ="You entered an invalid number of questions (inferior to 0 or superior to number of questions in the database\n This test will be generated with a default parameters\n";
            colorText(text,c);
    }
    //numberQuestion
    this->numberQuestion=numberQuestion;
    //questionId and answers
    if(generateTest(numberQuestion)){
        numberQuestion=nbMax;
        COLOR c=GREEN;
        string text ="Test generated with success :\n\tTest file : "+to_string(testId)+".txt";
        colorText(text,c); cout<<endl;
    } else {
        throw ObjectCouldNotBeCreatedException();
    }
}
//used by Test constractor to generate the test file and answers file
bool Test::generateTest(int numberQuestion){
    //questionId and answers
            //*****nb questions total
    ifstream f(QuestionsNb);
    if( !f.is_open() ){
        COLOR c=RED;
        string text ="an error occurred while communicating with the database";
        colorText(text,c); cout<<endl;
        return false;
    }
    string nb;
    f>>nb;
    int numberOfQuestions=stoi(nb);
    f.close();
    if(numberOfQuestions<numberQuestion){
        COLOR c=YELLOW;
        string text =" Please enter a number between 1 and "+numberOfQuestions;
        colorText(text,c); cout<<endl;
        return false;
    }
            //*****on genere les id des questions du qcm
    set<long int> ens;
    srand(time(0));
    do{
        ens.insert(rand()%numberOfQuestions+1);
    }while(ens.size()<numberQuestion);
            //******iterate over the set, recherche des questions
    ifstream q(QuestionsFile);
    if( !q.is_open() ){
        COLOR c=RED;
        string text ="an error occurred while communicating with the database";
        colorText(text,c); cout<<endl;
        return false;
    }
    ofstream t;
    string path=TestsDirectory+to_string(testId)+".txt";
    t.open(path, ios::app | ios::out);
    if( !q.is_open() ){
       COLOR c=RED;
        string text ="an error occurred while communicating with the database";
        colorText(text,c); cout<<endl;
        return false;
    }
    int i=0;
    string line;
    set<long int>::iterator it;
    map<long int, string> mapp;
    for (it = ens.begin(); it != ens.end(); ++it) {
        while (getline(q,line)){
            i++;
            if(i==*it){
                char* c = &line[0];
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

void Test::printTest(long int id){
    string file=TestsDirectory+to_string(id)+".txt";
    if(!exists(file)){
        COLOR c=RED;
        string text ="error This file doesn't exist, invalid ID\n";
        colorText(text,c); cout<<endl;
    } else {
        string str="notepad /p "+file;
        if(!system(&str[0])){
            COLOR c=RED;
            string text = "error while trying to print the file\n";
            colorText(text,c); cout<<endl;
        }
    }
}

void Test::checkTest(long int id){
    string fileTest=TestsDirectory+to_string(id)+".txt";
    string fileAnswers=AnswersDirectory+to_string(id)+".txt";
    ifstream test(fileTest);
    ifstream answers(fileAnswers);
    if (!test.is_open() || !answers.is_open()){
            COLOR c=RED;
            string text ="error Invalid Id test";
            colorText(text,c); cout<<endl;
    }
    else{
        string q, rep;
        while ( getline(test,q) && getline(answers,rep) ){
            char c_rep=rep[rep.size()-1];
            cout<<q<<endl;
            for(char c='A';c<'F';c++){
                getline(test,q);
                if(c_rep==c){
                    COLOR c=GREEN;
                    colorText(q,c); cout<<endl;
                }
                else
                    cout<<q<<endl;
            }
        }
    }
}
