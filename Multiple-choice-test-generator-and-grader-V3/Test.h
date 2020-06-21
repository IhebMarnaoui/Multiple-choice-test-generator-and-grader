#ifndef TEST
#define TEST

#include<list>
#include"Question.h"
#include"TestAnswers.h"
class Test{
    private:
        long int testId;
        std::list<int> questionId;
        int numberQuestion;
        TestAnswers* answers;
    private:
        bool generateTest(int numberQuestion);
    public:
        Test(int numberQuestion=0);
        static void printTest(long int id);
        static void checkTest(long int id);
};

#endif /*TEST*/
