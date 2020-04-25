#include"Answers.cpp"

//StudentAnswers class
class StudentAnswers : public Answers{
    public:
        StudentAnswers(string file):Answers(file){}
        ~StudentAnswers(){};
};


//TestAnswers class
class TestAnswers : public Answers{
    private:
        void generateAnswers();
    public:
        TestAnswers(string file);
        TestAnswers(long int TestAnswersID,map<long int ,string> m);
        void gradeTest(StudentAnswers S);
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
    cout<<"The grade is: "<<n<<"\n";
}
