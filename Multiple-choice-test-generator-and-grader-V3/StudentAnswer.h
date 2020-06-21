#ifndef STUDENTANSWERS
#define STUDENTANSWERS

#include"Answers.h"
class StudentAnswers : public Answers {
    public:
        StudentAnswers(std::string file);
        ~StudentAnswers();
};

#endif /*STUDENTANSWERS*/
