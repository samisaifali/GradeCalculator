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
T prompt(const string& label, const string& instructions = "") {
    string message = label + "\n\nEnter this in the terminal below.\n";
    if (!instructions.empty()) {
        message += "\nInstructions: " + instructions;
    }
    MessageBoxA(NULL, message.c_str(), "Input Needed", MB_OK | MB_ICONINFORMATION);
    T value;
    cout << label << " ";
    cin >> value;
    return value;
}

int main() {
    int numAssignments = prompt<int>(
        "Enter number of assignments:",
        "Enter a whole number, e.g., 3"
    );

    int numQuizzes = prompt<int>(
        "Enter number of quizzes:",
        "Enter a whole number, e.g., 2"
    );

    int numExams = prompt<int>(
        "Enter number of exams:",
        "Enter a whole number, e.g., 1"
    );

    vector<double> assignments, assignmentWeights;
    vector<double> quizzes, quizWeights;
    vector<double> exams, examWeights;

    for (int i = 0; i < numAssignments; ++i) {
        double score = prompt<double>(
            "Enter score for assignment " + to_string(i + 1) + ":",
            "Enter a score out of 100, e.g., 85.5"
        );
        double weight = prompt<double>(
            "Enter weight for assignment " + to_string(i + 1) + " (in decimal):",
            "Enter weight as a decimal, e.g., 0.1 for 10%"
        );
        assignments.push_back(score);
        assignmentWeights.push_back(weight);
    }

    for (int i = 0; i < numQuizzes; ++i) {
        double score = prompt<double>(
            "Enter score for quiz " + to_string(i + 1) + ":",
            "Enter a score out of 100"
        );
        double weight = prompt<double>(
            "Enter weight for quiz " + to_string(i + 1) + " (in decimal):",
            "Decimal format only, e.g., 0.05"
        );
        quizzes.push_back(score);
        quizWeights.push_back(weight);
    }

    for (int i = 0; i < numExams; ++i) {
        double score = prompt<double>(
            "Enter score for exam " + to_string(i + 1) + ":",
            "Enter a score out of 100"
        );
        double weight = prompt<double>(
            "Enter weight for exam " + to_string(i + 1) + " (in decimal):",
            "E.g., 0.4 for 40%"
        );
        exams.push_back(score);
        examWeights.push_back(weight);
    }

    double finalGrade = (calculateGrade(assignments, assignmentWeights) +
                         calculateGrade(quizzes, quizWeights) +
                         calculateGrade(exams, examWeights)) / 3;

    string result = "Final Grade: " + to_string(finalGrade) + "%";
    MessageBoxA(NULL, result.c_str(), "Final Grade", MB_OK | MB_ICONINFORMATION);

    return 0;
}
