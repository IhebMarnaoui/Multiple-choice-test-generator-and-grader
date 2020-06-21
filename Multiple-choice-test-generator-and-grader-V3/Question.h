#ifndef QUESTION
#define QUESTION

class Question{
    public:
        long int idQuestion;
        std::string description;
        std::string choices[5];
        char correctAnswer;
    private:
        void fillQuestion();
        Question(char str[],int a);
    public:
        Question();
        Question(char str[]);
        std::string toString();
        bool addQuestion();
        static bool addQuestions(std::string pathFile);
        std::string generateQuestion();
        long int getQuestionId();
        char getCorrectAnswer();
        static int getTotalNumberQuestions();
};


#endif /*QUESTION*/
