#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
#include <sstream>

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

// Pop-up message box with input fallback in terminal
template <typename T>
T popupInput(const string& label, const string& instructions = "") {
    string message = label + "\n\nPlease enter your response in the terminal.";
    if (!instructions.empty()) {
        message += "\n\n" + instructions;
    }
    MessageBoxA(NULL, message.c_str(), "Input Required", MB_OK | MB_ICONINFORMATION);
    
    cout << label << " ";
    T value;
    cin >> value;
    return value;
}

// Step 1: Only numAssignments moved fully to popup
int getIntInputPopup(const string& promptText) {
    char input[256];
    string label = promptText + "\n\n(Enter a number and click OK)";
    MessageBoxA(NULL, label.c_str(), "Assignments", MB_OK | MB_ICONINFORMATION);
    cout << promptText << ": ";
    cin.getline(input, 256);
    int value;
    cin >> value;
    return value;
}

int main() {
    // Step 1 – Just replace numAssignments with a full popup interaction
    int numAssignments = popupInput<int>(
        "Enter number of assignments:",
        "Enter a whole number like 3"
    );

    int numQuizzes = popupInput<int>(
        "Enter number of quizzes:",
        "Enter a whole number like 2"
    );

    int numExams = popupInput<int>(
        "Enter number of exams:",
        "Enter a whole number like 1"
    );

    vector<double> assignments, assignmentWeights;
    vector<double> quizzes, quizWeights;
    vector<double> exams, examWeights;

    for (int i = 0; i < numAssignments; ++i) {
        double score = popupInput<double>(
            "Enter score for assignment " + to_string(i + 1) + ":",
            "Score out of 100"
        );
        double weight = popupInput<double>(
            "Enter weight for assignment " + to_string(i + 1) + " (in decimal):",
            "e.g., 0.1 for 10%"
        );
        assignments.push_back(score);
        assignmentWeights.push_back(weight);
    }

    for (int i = 0; i < numQuizzes; ++i) {
        double score = popupInput<double>(
            "Enter score for quiz " + to_string(i + 1) + ":",
            "Out of 100"
        );
        double weight = popupInput<double>(
            "Enter weight for quiz " + to_string(i + 1) + " (in decimal):",
            "e.g., 0.05"
        );
        quizzes.push_back(score);
        quizWeights.push_back(weight);
    }

    for (int i = 0; i < numExams; ++i) {
        double score = popupInput<double>(
            "Enter score for exam " + to_string(i + 1) + ":",
            "Out of 100"
        );
        double weight = popupInput<double>(
            "Enter weight for exam " + to_string(i + 1) + " (in decimal):",
            "e.g., 0.4 for 40%"
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
