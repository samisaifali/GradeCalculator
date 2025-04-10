#include <iostream>
#include <vector>
#include <string>
#include <windows.h>

using namespace std;

// Function to calculate weighted average
double calculateGrade(const vector<double>& scores, const vector<double>& weights) {
    double total = 0.0, weightSum = 0.0;
    for (size_t i = 0; i < scores.size(); ++i) {
        total += scores[i] * weights[i];
        weightSum += weights[i];
    }
    return (weightSum == 0) ? 0 : total / weightSum;
}

// Show a popup with the prompt, then collect input in terminal
template <typename T>
T prompt(const string& message) {
    MessageBoxA(NULL, message.c_str(), "Input", MB_OK);
    T value;
    cout << message;
    cin >> value;
    return value;
}

int main() {
    int numAssignments = prompt<int>("Enter number of assignments:");
    int numQuizzes = prompt<int>("Enter number of quizzes:");
    int numExams = prompt<int>("Enter number of exams:");

    vector<double> assignments, assignmentWeights;
    vector<double> quizzes, quizWeights;
    vector<double> exams, examWeights;

    for (int i = 0; i < numAssignments; ++i) {
        double score = prompt<double>("Enter score for assignment " + to_string(i + 1) + ":");
        double weight = prompt<double>("Enter weight for assignment " + to_string(i + 1) + " (in decimal):");
        assignments.push_back(score);
        assignmentWeights.push_back(weight);
    }

    for (int i = 0; i < numQuizzes; ++i) {
        double score = prompt<double>("Enter score for quiz " + to_string(i + 1) + ":");
        double weight = prompt<double>("Enter weight for quiz " + to_string(i + 1) + " (in decimal):");
        quizzes.push_back(score);
        quizWeights.push_back(weight);
    }

    for (int i = 0; i < numExams; ++i) {
        double score = prompt<double>("Enter score for exam " + to_string(i + 1) + ":");
        double weight = prompt<double>("Enter weight for exam " + to_string(i + 1) + " (in decimal):");
        exams.push_back(score);
        examWeights.push_back(weight);
    }

    double finalGrade = (calculateGrade(assignments, assignmentWeights) +
                         calculateGrade(quizzes, quizWeights) +
                         calculateGrade(exams, examWeights)) / 3;

    string result = "Final Grade: " + to_string(finalGrade) + "%";
    MessageBoxA(NULL, result.c_str(), "Final Grade", MB_OK);

    return 0;
}
