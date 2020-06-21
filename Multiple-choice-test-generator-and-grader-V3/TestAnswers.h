#ifndef TESTANSWERS
#define TESTANSWERS

#include"Answers.h"
#include"StudentAnswer.h"
class TestAnswers : public Answers{
    private:
        void generateAnswers();
        double grade(StudentAnswers S);
    public:
        TestAnswers(std::string file);
        TestAnswers(long int TestAnswersID,std::map<long int ,std::string> m);
        void gradeTest(StudentAnswers S);
        void gradeTests(std::string DirPath);
        ~TestAnswers(){};
};

#endif /*TESTANSWERS*/
