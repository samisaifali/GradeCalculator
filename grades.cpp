#include <windows.h>
#include <string>
#include <vector>
#include <sstream>
#include "resource.h"

using namespace std;

// Dialog input handler
INT_PTR CALLBACK InputDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
    static string* inputBuffer;

    switch (message) {
    case WM_INITDIALOG:
        inputBuffer = reinterpret_cast<string*>(lParam);
        return TRUE;
    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK) {
            char buf[256];
            GetDlgItemTextA(hDlg, IDC_INPUT, buf, sizeof(buf));
            *inputBuffer = buf;
            EndDialog(hDlg, IDOK);
            return TRUE;
        }
        if (LOWORD(wParam) == IDCANCEL) {
            EndDialog(hDlg, IDCANCEL);
            return TRUE;
        }
        break;
    }
    return FALSE;
}

// Template function to get input via dialog
template <typename T>
T popupInput(const string& label, const string& instructions = "") {
    string fullPrompt = label;
    if (!instructions.empty()) fullPrompt += "\n\n" + instructions;
    MessageBoxA(NULL, fullPrompt.c_str(), "Instructions", MB_OK | MB_ICONINFORMATION);

    string inputText;
    if (DialogBoxParamA(NULL, MAKEINTRESOURCEA(IDD_INPUTBOX), NULL, InputDlgProc, (LPARAM)&inputText) == IDOK) {
        stringstream ss(inputText);
        T value;
        ss >> value;
        return value;
    } else {
        ExitProcess(0); // user cancelled
    }
}

// Calculate weighted average
double calculateGrade(const vector<double>& scores, const vector<double>& weights) {
    double total = 0.0, weightSum = 0.0;
    for (size_t i = 0; i < scores.size(); ++i) {
        total += scores[i] * weights[i];
        weightSum += weights[i];
    }
    return (weightSum == 0) ? 0 : total / weightSum;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int) {
    int numAssignments = popupInput<int>("Enter number of assignments:", "E.g., 3");
    int numQuizzes = popupInput<int>("Enter number of quizzes:", "E.g., 2");
    int numExams = popupInput<int>("Enter number of exams:", "E.g., 1");

    vector<double> assignments, assignmentWeights;
    vector<double> quizzes, quizWeights;
    vector<double> exams, examWeights;

    for (int i = 0; i < numAssignments; ++i) {
        assignments.push_back(popupInput<double>("Assignment " + to_string(i + 1), "Score out of 100"));
        assignmentWeights.push_back(popupInput<double>("Assignment " + to_string(i + 1), "Weight as decimal (e.g., 0.1)"));
    }

    for (int i = 0; i < numQuizzes; ++i) {
        quizzes.push_back(popupInput<double>("Quiz " + to_string(i + 1), "Score out of 100"));
        quizWeights.push_back(popupInput<double>("Quiz " + to_string(i + 1), "Weight as decimal (e.g., 0.05)"));
    }

    for (int i = 0; i < numExams; ++i) {
        exams.push_back(popupInput<double>("Exam " + to_string(i + 1), "Score out of 100"));
        examWeights.push_back(popupInput<double>("Exam " + to_string(i + 1), "Weight as decimal (e.g., 0.4)"));
    }

    double finalGrade = (calculateGrade(assignments, assignmentWeights) +
                         calculateGrade(quizzes, quizWeights) +
                         calculateGrade(exams, examWeights)) / 3;

    string result = "Final Grade: " + to_string(finalGrade) + "%";
    MessageBoxA(NULL, result.c_str(), "Final Grade", MB_OK | MB_ICONINFORMATION);
    return 0;
}
