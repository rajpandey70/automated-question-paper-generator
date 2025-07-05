#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <set>
#include <algorithm>
#include "generator.h"

using namespace std;

vector<int> parseDifficulties(const string& input) {
    vector<int> diffs;
    stringstream ss(input);
    string token;
    while (getline(ss, token, ',')) {
        try {
            diffs.push_back(stoi(token));
        } catch (...) {}
    }
    return diffs;
}

vector<string> parseTopics(const string& input) {
    vector<string> topics;
    stringstream ss(input);
    string token;
    while (getline(ss, token, ',')) {
        token.erase(remove_if(token.begin(), token.end(), ::isspace), token.end());
        transform(token.begin(), token.end(), token.begin(), ::tolower);
        if (!token.empty() && token != "any") topics.push_back(token);
    }
    return topics;
}

int main() {
    vector<Question> all = loadQuestions("questions.txt");
    if (all.empty()) {
        cout << "No questions loaded.\n";
        return 1;
    }

    set<string> topicsAvailable;
    for (const auto& q : all) {
        topicsAvailable.insert(q.topic);
    }

    int totalMarks;
    cout << "Enter total marks for the paper: ";
    cin >> totalMarks;
    cin.ignore();

    cout << "Enter difficulty (0=Any, 1=Easy, 2=Medium, 3=Hard). Use comma-separated (e.g., 2,3): ";
    string difficultyInput;
    getline(cin, difficultyInput);
    vector<int> difficulties = parseDifficulties(difficultyInput);

    cout << "Enter topic name(s) (comma-separated), or type 'list' to see available topics, or 'any': ";
    string topicInput;
    getline(cin, topicInput);

    if (topicInput == "list") {
        cout << "\nAvailable Topics:\n";
        for (const auto& t : topicsAvailable) {
            cout << "- " << t << "\n";
        }
        cout << "\nEnter topic name(s) again: ";
        getline(cin, topicInput);
    }

    vector<string> selectedTopics = parseTopics(topicInput);

    string subject;
    cout << "Enter subject name: ";
    getline(cin, subject);

    string date;
    cout << "Enter exam date (DD-MM-YYYY): ";
    getline(cin, date);

    vector<Question> filtered = filterQuestions(all, difficulties, selectedTopics);
    vector<Question> paper = selectQuestions(filtered, totalMarks);

    if (paper.empty()) {
        cout << "No questions found for the given criteria.\n";
        return 1;
    }

    string outputPath = "output/GeneratedPaper.txt";
    bool saved = saveQuestionPaper(paper, outputPath, subject, date);
    if (saved) {
        cout << "\n✅ Question paper generated successfully at: " << outputPath << "\n";
    } else {
        cout << "❌ Failed to save the question paper.\n";
    }

    return 0;
}
