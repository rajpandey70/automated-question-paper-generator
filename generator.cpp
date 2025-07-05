#include "generator.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <cctype>
#include <set>
#include <sys/stat.h>
#include <sys/types.h>

using namespace std;

string toLower(const string& str) {
    string lower = str;
    transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
    return lower;
}

string trim(const string& s) {
    size_t start = s.find_first_not_of(" \t\n\r");
    size_t end = s.find_last_not_of(" \t\n\r");
    return (start == string::npos) ? "" : s.substr(start, end - start + 1);
}

vector<Question> loadQuestions(const string& filename) {
    vector<Question> questions;
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        Question q;
        string temp;
        getline(ss, temp, '|'); q.id = stoi(temp);
        getline(ss, q.text, '|');
        getline(ss, q.topic, '|'); q.topic = toLower(trim(q.topic));
        getline(ss, temp, '|'); q.difficulty = stoi(temp);
        getline(ss, temp, '|'); q.marks = stoi(temp);
        questions.push_back(q);
    }
    return questions;
}

vector<Question> filterQuestions(const vector<Question>& questions, const vector<int>& difficulties, const vector<string>& topics) {
    vector<Question> filtered;
    set<string> topicSet(topics.begin(), topics.end());
    for (const auto& q : questions) {
        bool diffMatch = difficulties.empty() || find(difficulties.begin(), difficulties.end(), q.difficulty) != difficulties.end();
        bool topicMatch = topics.empty() || topicSet.count(toLower(trim(q.topic))) > 0;
        if (diffMatch && topicMatch) {
            filtered.push_back(q);
        }
    }
    return filtered;
}

vector<Question> selectQuestions(const vector<Question>& questions, int totalMarks) {
    vector<Question> bestCombo;
    int bestScore = 0;
    int n = questions.size();

    // Try all combinations (works well if n <= 20)
    for (int mask = 0; mask < (1 << n); ++mask) {
        int sum = 0;
        vector<Question> combo;
        for (int i = 0; i < n; ++i) {
            if (mask & (1 << i)) {
                if (sum + questions[i].marks <= totalMarks) {
                    sum += questions[i].marks;
                    combo.push_back(questions[i]);
                }
            }
        }
        if (sum > bestScore) {
            bestScore = sum;
            bestCombo = combo;
        }
        if (bestScore == totalMarks) break;
    }
    return bestCombo;
}

bool saveQuestionPaper(const vector<Question>& paper, const string& filepath, const string& subject, const string& date) {
    struct stat info;
    if (stat("output", &info) != 0) {
        mkdir("output", 0777);
    }

    ofstream out(filepath);
    if (!out.is_open()) return false;

    out << "---------------------------------------------\n";
    out << "            Lovely Professional University\n";
    out << "---------------------------------------------\n";
    out << "Subject: " << subject << "\n";
    out << "Date: " << date << "\n";
    out << "Time: 3 Hours\n";

    int total = 0;
    for (const auto& q : paper) total += q.marks;
    out << "Maximum Marks: " << total << "\n";
    out << "---------------------------------------------\n\n";

    out << "Instructions:\n";
    out << "- Attempt all questions.\n";
    out << "- Write neat and legible answers.\n\n";

    int qno = 1;
    for (const auto& q : paper) {
        out << "Q" << qno++ << ". " << q.text << " [" << q.marks << " Marks]\n";
    }

    out.close();
    return true;
}
