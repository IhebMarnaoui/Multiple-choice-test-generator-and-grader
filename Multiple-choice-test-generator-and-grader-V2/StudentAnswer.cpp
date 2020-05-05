#include<string>
#include"Answers.cpp"

class StudentAnswers : public Answers{
    public:
        StudentAnswers(string file):Answers(file){}
        ~StudentAnswers(){};
};
