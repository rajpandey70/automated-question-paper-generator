#ifndef GENERATOR_H
#define GENERATOR_H

#include <string>
#include <vector>

struct Question {
    int id;
    std::string text;
    std::string topic;
    int difficulty; // 1=Easy, 2=Medium, 3=Hard
    int marks;
};

std::vector<Question> loadQuestions(const std::string& filename);
std::vector<Question> filterQuestions(const std::vector<Question>& questions, const std::vector<int>& difficulties, const std::vector<std::string>& topics);
std::vector<Question> selectQuestions(const std::vector<Question>& questions, int totalMarks);
bool saveQuestionPaper(const std::vector<Question>& paper, const std::string& filepath, const std::string& subject, const std::string& date);

#endif
