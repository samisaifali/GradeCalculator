#include <iostream>
#include <vector>

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

int main() {
    int numAssignments, numQuizzes, numExams;
    vector<double> assignments, quizzes, exams;
    vector<double> assignmentWeights, quizWeights, examWeights;
    double score, weight;
    
    cout << "Enter number of assignments: ";
    cin >> numAssignments;
    for (int i = 0; i < numAssignments; ++i) {
        cout << "Enter score for assignment " << i + 1 << ": ";
        cin >> score;
        assignments.push_back(score);
        cout << "Enter weight for assignment " << i + 1 << " (in decimal form): ";
        cin >> weight;
        assignmentWeights.push_back(weight);
    }
    
    cout << "Enter number of quizzes: ";
    cin >> numQuizzes;
    for (int i = 0; i < numQuizzes; ++i) {
        cout << "Enter score for quiz " << i + 1 << ": ";
        cin >> score;
        quizzes.push_back(score);
        cout << "Enter weight for quiz " << i + 1 << " (in decimal form): ";
        cin >> weight;
        quizWeights.push_back(weight);
    }
    
    cout << "Enter number of exams: ";
    cin >> numExams;
    for (int i = 0; i < numExams; ++i) {
        cout << "Enter score for exam " << i + 1 << ": ";
        cin >> score;
        exams.push_back(score);
        cout << "Enter weight for exam " << i + 1 << " (in decimal form): ";
        cin >> weight;
        examWeights.push_back(weight);
    }
    
    double finalGrade = (calculateGrade(assignments, assignmentWeights) +
                         calculateGrade(quizzes, quizWeights) +
                         calculateGrade(exams, examWeights)) / 3;
    
    cout << "Final Grade: " << finalGrade << "%" << endl;
    
    return 0;
}
