/*
Author: Zakaria Rahman
Date: November 23rd, 2025
Description: This program collects user inputs and validates if they enter the correct input.
             Also, it demonstrates file handling by writing to a file. Additionally, it shows the usage 
             of selection statements like if else statements and switch case statements. Furthermore, 
             it also demonstrates the use of repetition structures such as the for loop, do...while loop,
             and while loop, and use of user defined functions. It also demonstrates the use of Arrays and Enumerations.
Course: ITCS 2530 (C++ Programming 1)
*/

// header files
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <ctime>


using namespace std;

// Enumeration Declaration
enum difficultyLevel { EASY = 'E', MEDIUM = 'M', HARD = 'H'};

// Declaring a constant for number of questions asked on the quiz
const int NO_OF_QUESTIONS = 5;
// Some Color Codes as Constants
const string RED = "\033[31m";
const string GREEN = "\033[32m";
const string YELLOW = "\033[33m";
const string RESET = "\033[0m";

// Constants for array size
const int NUMBER_OF_TEST_SCORES = 5;

// Function prototypes

void changeConsoleTextColor(string color);

void displayWelcomeBanner();

void collectUserInfo(string& name, string& favoriteMathSubject, int& problemsSolvedPerWeek, int& confidenceLevel, double& hoursSpentStudyingPerWeek);

double calculateEstimatedProblemsPerHour(int problemsSolvedPerWeek, double hoursSpentStudyingPerWeek);

void userInputReportFile(ofstream& userOutputFile, string& name, string& favoriteMathSubject, int& confidenceLevel, double& hoursSpentStudyingPerWeek, double& estimatedProblemsPerHour, double testScores[], double& averageTestScores);

void mathQuiz(int& noOfCorrectAnswers, char quizDifficultyLevel);

void quizFeedback(int& confidenceLevel, int& noOfCorrectAnswers);

void studentMonthlyReportCard(ofstream& reportOutputFile);

void displayStudentFavoriteSubjects(string favoriteSubjects[], const int NUMBER_OF_FAVORITE_SUBJECTS);

int main(){
    
    // Calling the function which displays a welcome banner to the user
    displayWelcomeBanner();

    // Declaring some variables
    string userName;
    string userFavoriteMathSubject;
    int userProblemsSolvedPerWeek;
    int userConfidenceLevel;
    double userHoursSpentStudyingPerWeek;
    double userEstimatedProblemsPerHour = 0.0;

    
    // Calling the 'Collect User Info' function to get the user's input
    collectUserInfo(userName, userFavoriteMathSubject, userProblemsSolvedPerWeek, userConfidenceLevel, userHoursSpentStudyingPerWeek);

    // Calling the function to calculate the user's estimated time solving each problem
    userEstimatedProblemsPerHour = calculateEstimatedProblemsPerHour(userProblemsSolvedPerWeek, userHoursSpentStudyingPerWeek);

    // Using an array to store user's last five test scores
    double userTestScores[NUMBER_OF_TEST_SCORES];

    cout << userName << ", please enter your last five " << userFavoriteMathSubject << "'s test scores: " << endl << endl;
    for (int i = 0; i < NUMBER_OF_TEST_SCORES; i++) {
        // Input Validation for each score using a do...while loop
        double score;
        bool isValid = false;
        do {
            cout << "Test Score " << i + 1 << ": ";
            if (cin >> score && score >= 0.0 && score <= 100.0) {
                userTestScores[i] = score;
                isValid = true;
            } else {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid Test Score. Please Enter a score between 0 to 100.\n";
            }
        } while(!isValid);
    }
    cout << endl;
    // Calculating and displaying the average test score
    double totalScores = 0.0;
    double userAverageTestScore = 0.0;
    for (int i = 0; i < NUMBER_OF_TEST_SCORES; i++) {
        totalScores += userTestScores[i];
    }
    userAverageTestScore = totalScores / NUMBER_OF_TEST_SCORES;
    cout << fixed << showpoint << setprecision(2);
    cout << userName << ", your average test score in " << userFavoriteMathSubject << " is: " << userAverageTestScore << endl << endl;


    // File Handling
    ofstream outputFile;

    // Calling the Function for saving the user info to a separate text file
    userInputReportFile(outputFile, userName, userFavoriteMathSubject, userConfidenceLevel, userHoursSpentStudyingPerWeek, userEstimatedProblemsPerHour, userTestScores, userAverageTestScore);

    // Calling the function to insert and display user's favorite subjects using an array
    const int NUMBER_OF_FAVORITE_SUBJECTS = 3;
    string userFavoriteSubjects[NUMBER_OF_FAVORITE_SUBJECTS];
    displayStudentFavoriteSubjects(userFavoriteSubjects, NUMBER_OF_FAVORITE_SUBJECTS);

    // Math Quiz
    cout << "Please Complete the Following Five Quesitions Math Quiz: \n" << endl;


    // Seeding the random number generator once
    srand(time(0));

    // Variable Declaration
    int numberOfCorrectAnswers = 0;

    // Using /a for loop for calling the mathQuiz functions
    char quizDifficultyLevel;
    cout << "Enter difficulty level for the quiz (E for Easy, M for Medium or H for Hard): ";
    cin >> quizDifficultyLevel;
    cout << endl;

    for (int i = 1; i <= NO_OF_QUESTIONS; i++){
        mathQuiz(numberOfCorrectAnswers, quizDifficultyLevel);
    }

    cout << endl;

    // Calling the quizFeedback function
    quizFeedback(userConfidenceLevel, numberOfCorrectAnswers);

    // Calling the function to build a report card for students
    ofstream outputReportFile;
    studentMonthlyReportCard(outputReportFile);

    return 0;
}


// Function that change the console's text color
// Credit to AI and YouTube Videos
void changeConsoleTextColor(string color) {
    cout << color;
}

// Function that displays the welcome banner to the user
void displayWelcomeBanner(){
    // calling the function to change the color of the console's text
    changeConsoleTextColor(YELLOW);

    // Welcome Message
    cout << left << setfill('-') << setw(100) << "" << endl << endl;
    cout << "Welcome to the Math Aptitude Analyzer! Sharpen your Math skills and discover your true potential!" << endl << endl;
    cout << "Get ready to challenge yourself and see how strong your math skills really are!" << endl << endl;
    cout << "Please enter the following information as prompted. Thank you!" << endl << endl;
    cout << left << setfill('-') << setw(100) << "" << endl << endl;

    // Changing the color back to default
    changeConsoleTextColor(RESET);
}

// Function that collects and validates the data from the user
void collectUserInfo(string& name, string& favoriteMathSubject, int& problemsSolvedPerWeek, int& confidenceLevel, double& hoursSpentStudyingPerWeek) 
{
    // Prompts the user for inputs

    cout << "Enter your full name: ";
    getline(cin, name);
    cout << endl;

    cout << "Enter your favorite Math Subject: ";
    getline(cin, favoriteMathSubject);
    cout << endl;

    // Input Validation using while loop

    cout << "Enter the number of Math Problems Solved Per Week: ";

    while (!(cin >> problemsSolvedPerWeek)){
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid Input. Please enter a whole number: " << endl;
    }
    cout << endl;

    cout << "On a scale of 1 to 10, how confident are you in Math (1 being least and 10 being the most): ";

    while(!(cin >> confidenceLevel) || confidenceLevel < 1 || confidenceLevel > 10){
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid Input. Please enter a number between 1 - 10: ";
    }
    cout << endl;

    cout << "Enter number of hours studying Math per week: ";

    while (!(cin >> hoursSpentStudyingPerWeek) || hoursSpentStudyingPerWeek < 1 || hoursSpentStudyingPerWeek > 168){
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid Input. Please enter a number between 1 to 168: ";
    }
    cout << endl;

}

// Function for Calculation
double calculateEstimatedProblemsPerHour(int problemsSolvedPerWeek, double hoursSpentStudyingPerWeek){

    return static_cast<double> (problemsSolvedPerWeek) / hoursSpentStudyingPerWeek;
}

// Function for Writing User's Input to an Output txt file
void userInputReportFile(ofstream& userOutputFile, string& name, string& favoriteMathSubject, int& confidenceLevel, double& hoursSpentStudyingPerWeek, double& estimatedProblemsPerHour, double testScores[], double& averageTestScores) {
    
    userOutputFile.open("report.txt");

    userOutputFile << fixed << showpoint << setprecision(2);

    userOutputFile << left << setfill(' ') << setw(50) << "Name:" << right << setw(20) << setfill(' ') << name << endl;
    userOutputFile << left << setfill(' ') << setw(50) << "Favorite Math Subject:" << right << setw(20) << setfill(' ') << favoriteMathSubject << endl;
    userOutputFile << left << setfill(' ') << setw(50) << "Confidence Level:" << right << setw(20) << setfill(' ') << confidenceLevel << endl;
    userOutputFile << left << setfill(' ') << setw(50) << "# of Hours Studying Math:" << right << setw(20) << setfill(' ') << hoursSpentStudyingPerWeek << endl;
    userOutputFile << left << setfill(' ') << setw(50) << "Estimated Problems Solved Per Hour:" << right << setw(20) << setfill(' ') << estimatedProblemsPerHour << endl;
    userOutputFile << left << setfill(' ') << setw(50) << "Test Scores-" << endl;
    for (int i = 0; i < NUMBER_OF_TEST_SCORES; i++) {
        userOutputFile << left << setfill(' ') << setw(50) << "Test Score " + to_string(i+1) + ": " << right << setw(20) << setfill(' ') << testScores[i] << endl;
    }
    userOutputFile << left << setfill(' ') << setw(50) << "Average Test Scores:" << right << setw(20) << setfill(' ') << averageTestScores << endl;


    userOutputFile.close();
}

// Function for asking the user some basic arithmetic problems
void mathQuiz(int& noOfCorrectAnswers, char quizDifficultyLevel) {
    int randomNum1, randomNum2;
    int result = 0;
    int userAnswer;
    char mathOperator;

    switch(quizDifficultyLevel) {
        case EASY:
            randomNum1 = (rand() % 10) + 1;
            randomNum2 = (rand() % 10) + 1;
            break;
        case MEDIUM:
            randomNum1 = (rand() % 100) + 1;
            randomNum2 = (rand() % 100) + 1;
            break;
        case HARD:
            randomNum1 = (rand() % 1000) + 1;
            randomNum2 = (rand() % 1000) + 1;
            break;
    }

    cout << "Enter a math operator (+, -, *, /, %): ";

    while (!(cin >> mathOperator) || (mathOperator != '+' && mathOperator != '-' && mathOperator != '*' && mathOperator != '/' && mathOperator != '%')){
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid Input. Please Enter a correct Math Operator: ";
    }
        cout << endl;

        switch(mathOperator) {
            case '+':
            result = randomNum1 + randomNum2;
            break;
        case '-':
            result = randomNum1 - randomNum2;
            break;
        case '*':
            result =randomNum1 * randomNum2;
            break;
        case '/':
            result = randomNum1 / randomNum2;
            break;
        case '%':
            result = randomNum1 % randomNum2;
            break;
        }

    cout << randomNum1 << " " << mathOperator << " " << randomNum2 << " = ";
    cin >> userAnswer;
    cout << endl;

    if (userAnswer == result){
        // using the console text color function
        changeConsoleTextColor(GREEN);

        cout << "Correct! Well Done!" << endl;

        changeConsoleTextColor(RESET);
        noOfCorrectAnswers++;
    } else{
        changeConsoleTextColor(RED);
        cout << "Wrong Answer! The correct answer was: " << result << endl;
        changeConsoleTextColor(RESET);
    }
    cout << endl;
}


// Function for getting a feedback based on confidence level and quiz results
void quizFeedback(int& confidenceLevel, int& noOfCorrectAnswers) {
    cout << "----- Quiz Feedback -----\n" << endl;


    // Using if/else blocks with compound boolean conditions
    if (noOfCorrectAnswers >= 4 && confidenceLevel >= 7) {
        cout << "Great! Your confidence matches your performance." << endl;
        cout << "You can try more advance problems!" << endl;
    }
    else if (noOfCorrectAnswers >= 3 && confidenceLevel >= 5) {
        cout << "Good work! Keep on practicing to improve." << endl;
        cout << "Solving more problems increases your confidence level." << endl;
    }
    else if (noOfCorrectAnswers >= 3 && confidenceLevel < 5) {
        cout << "Your performance is okay, but your confidence is low." << endl;
        cout << "Focus on building your confidence through consistent practice." << endl;
    }
    else if (noOfCorrectAnswers < 3 && confidenceLevel >=5) {
        cout << "You feel confident, but your performance shows the opposite." << endl;
        cout << "Practice fundamental concepts to match your confidence level." << endl;
    }
    else{
        cout << "Focus on basic concepts and fundamentals of Math." << endl;
        cout << "Practice regularly to improve your skills and confidence level." << endl;
    }

    cout << endl;
}


void studentMonthlyReportCard(ofstream& reportOutputFile) {
    // Building a report card for students from their teacher

    string studentLastName;
    string studentID;
    char grade;
    int testScore;
    char teacherChoiceContinue;
    string reportCardFeedback;


    cout << "----- Building Report Card For Students -----" << endl << endl;

    reportOutputFile.open("StudentsReportCard.txt");

    do {
        cout << "Enter student's last name: ";
        cin >> studentLastName;
        cout << endl;

        cout << "Enter student's ID number: ";
        cin >> studentID;
        cout << endl;

        cout << "Please enter the student's grade (A, B, C, D, E): ";
        cin >> grade;
        cout << endl;

        cout << "Please enter the student's last test score: ";
        cin >> testScore;
        cout << endl;

        if (grade == 'A' || testScore >= 90){
            reportCardFeedback = "Excellent work! Keep up the high performance.";
        }
        else if (grade == 'B' || testScore >= 80){
            reportCardFeedback = "Good job! You are doing well, but there is room for improvement.";
        }
        else if (grade == 'C' || testScore >= 70) {
            reportCardFeedback = "Fair performance. Focus on improving weaker areas.";
        }
        else {
            reportCardFeedback = "Needs improvement. Consider extra practice and studying.";
        }  

        reportOutputFile << left << setw(15) << studentLastName << setw(15) << studentID << right << setw(5) << grade << setw(8) << testScore << right << setw(90) << reportCardFeedback << endl;

        cout << "Please, enter 'N' or 'n' to quit, any other key to continue: ";
        cin >> teacherChoiceContinue;
        cout << endl;

    } while (teacherChoiceContinue != 'N' && teacherChoiceContinue != 'n');

    reportOutputFile.close();

}

// Function to insert and display user's favorite subjects
void displayStudentFavoriteSubjects(string favoriteSubjects[], const int NUMBER_OF_FAVORITE_SUBJECTS) {

    cout << "Enter Your Favorite Subjects: " << endl;
    for (int i = 0; i < NUMBER_OF_FAVORITE_SUBJECTS; i++){
        cin >> favoriteSubjects[i];
    }
    cout << endl;

    cout << "Your Favorite Subjects are- " << endl;
    for (int i = 0; i < NUMBER_OF_FAVORITE_SUBJECTS; i++) {
        changeConsoleTextColor(YELLOW);
        cout << favoriteSubjects[i] << " ";
    }
    cout << endl << endl;
    changeConsoleTextColor(RESET);
}
