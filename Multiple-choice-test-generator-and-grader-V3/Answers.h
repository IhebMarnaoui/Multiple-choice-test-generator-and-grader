#ifndef ANSWERS
#define ANSWERS

#include<map>
class Answers{
    public:
        Answers(long int AnswersID);
        Answers(std::string file);
        virtual ~Answers();
        std::map < long int , std::string > answerdetails ;
    protected :
        long int AnswersID;
};

#endif /*ANSWERS*/
