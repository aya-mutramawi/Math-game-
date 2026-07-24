#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

//========================= Enums =========================

enum enLevel
{
    Easy = 1,
    Medium = 2,
    Hard = 3,
    MixLevel = 4
};

enum enOperation
{
    Add = 1,
    Sub = 2,
    Mult = 3,
    Div = 4,
    MixOperation = 5
};

//======================== Structures ======================

struct stQuestion
{
    int Number1;
    int Number2;

    enOperation Operation;
    enLevel Level;

    int CorrectAnswer;
    int PlayerAnswer;

    bool AnswerResult;
};

struct stQuiz
{
    stQuestion Questions[100];

    int NumberOfQuestions;

    enOperation Operation;
    enLevel Level;

    int RightAnswers = 0;
    int WrongAnswers = 0;

    bool Pass;
};

//====================== Read Data ==========================

int ReadNumberOfQuestions()
{
    int Number = 0;

    do
    {
        cout << "\nHow Many Questions (1 - 9): ";
        cin >> Number;

    } while (Number < 1 || Number > 9);

    return Number;
}

enOperation ReadOperationType()
{
    int Choice = 0;

    cout << "\nChoose Operation:\n";
    cout << "[1] Add\n";
    cout << "[2] Subtract\n";
    cout << "[3] Multiply\n";
    cout << "[4] Divide\n";
    cout << "[5] Mixed\n";
    cout << "Choice: ";

    cin >> Choice;

    return (enOperation)Choice;
}

enLevel ReadLevelType()
{
    int Choice = 0;

    do
    {
        cout << "\nChoose Level:\n";
        cout << "[1] Easy\n";
        cout << "[2] Medium\n";
        cout << "[3] Hard\n";
        cout << "[4] Mixed\n";
        cout << "Choice: ";

        cin >> Choice;

    } while (Choice < 1 || Choice > 4);

    return (enLevel)Choice;
}

//====================== Utilities ==========================

int RandomNumber(int From, int To)
{
    return rand() % (To - From + 1) + From;
}

int CalculateCorrectAnswer(int Number1, int Number2, enOperation Operation)
{
    switch (Operation)
    {
    case Add:
        return Number1 + Number2;

    case Sub:
        return Number1 - Number2;

    case Mult:
        return Number1 * Number2;

    case Div:
        return Number1 / Number2;

    default:
        return Number1 + Number2;
    }
}

//==================== Generate Question ====================

stQuestion GenerateQuestion(enLevel Level, enOperation Operation)
{
    stQuestion Question;

    if (Level == MixLevel)
        Level = (enLevel)RandomNumber(1, 3);

    if (Operation == MixOperation)
        Operation = (enOperation)RandomNumber(1, 4);

    Question.Level = Level;
    Question.Operation = Operation;

    switch (Level)
    {
    case Easy:
        Question.Number1 = RandomNumber(1, 10);
        Question.Number2 = RandomNumber(1, 10);
        break;

    case Medium:
        Question.Number1 = RandomNumber(10, 50);
        Question.Number2 = RandomNumber(10, 50);
        break;

    case Hard:
        Question.Number1 = RandomNumber(50, 100);
        Question.Number2 = RandomNumber(50, 100);
        break;
    }

    Question.CorrectAnswer =
        CalculateCorrectAnswer(
            Question.Number1,
            Question.Number2,
            Question.Operation);

    return Question;
}

void GenerateQuestions(stQuiz& Quiz)
{
    for (int i = 0; i < Quiz.NumberOfQuestions; i++)
    {
        Quiz.Questions[i] =
            GenerateQuestion(Quiz.Level, Quiz.Operation);
    }
}
char GetOperationSymbol(enOperation Operation)
{
    switch (Operation)
    {
    case Add:
        return '+';

    case Sub:
        return '-';

    case Mult:
        return '*';

    case Div:
        return '/';

    default:
        return '?';
    }
}

string GetLevelText(enLevel Level)
{
    string arrLevel[4] = { "Easy", "Medium", "Hard", "Mixed" };
    return arrLevel[Level - 1];
}

string GetOperationText(enOperation Operation)
{
    switch (Operation)
    {
    case Add:
        return "Addition";

    case Sub:
        return "Subtraction";

    case Mult:
        return "Multiplication";

    case Div:
        return "Division";

    default:
        return "Mixed";
    }
}

void PrintQuestion(stQuiz& Quiz, int QuestionNumber)
{
    cout << "\n---------------------------------\n";
    cout << "Question "
         << QuestionNumber + 1
         << "/"
         << Quiz.NumberOfQuestions
         << "\n\n";

    cout << Quiz.Questions[QuestionNumber].Number1 << endl;
    cout << Quiz.Questions[QuestionNumber].Number2 << " "
         << GetOperationSymbol(
                Quiz.Questions[QuestionNumber].Operation)
         << endl;

    cout << "-----------------\n";
}

void CheckAnswer(stQuiz& Quiz, int QuestionNumber)
{
    if (Quiz.Questions[QuestionNumber].PlayerAnswer ==
        Quiz.Questions[QuestionNumber].CorrectAnswer)
    {
        Quiz.Questions[QuestionNumber].AnswerResult = true;
        Quiz.RightAnswers++;

        cout << "\nCorrect :-)\n";
    }
    else
    {
        Quiz.Questions[QuestionNumber].AnswerResult = false;
        Quiz.WrongAnswers++;

        cout << "\nWrong :-(\n";
        cout << "Correct Answer = "
             << Quiz.Questions[QuestionNumber].CorrectAnswer
             << endl;
    }
}

void AskQuestions(stQuiz& Quiz)
{
    for (int i = 0; i < Quiz.NumberOfQuestions; i++)
    {
        PrintQuestion(Quiz, i);

        cin >> Quiz.Questions[i].PlayerAnswer;

        CheckAnswer(Quiz, i);
    }

    Quiz.Pass =
        Quiz.RightAnswers >=
        Quiz.NumberOfQuestions / 2.0;
}

string GetFinalResult(bool Pass)
{
    return (Pass ? "PASS :-)" : "FAIL :-(");
}

void PrintFinalResult(stQuiz Quiz)
{
    cout << "\n====================================";
    cout << "\n          Final Results";
    cout << "\n====================================";

    cout << "\nResult           : "
         << GetFinalResult(Quiz.Pass);

    cout << "\nQuestions        : "
         << Quiz.NumberOfQuestions;

    cout << "\nRight Answers    : "
         << Quiz.RightAnswers;

    cout << "\nWrong Answers    : "
         << Quiz.WrongAnswers;

    cout << "\nLevel            : "
         << GetLevelText(Quiz.Level);

    cout << "\nOperation        : "
         << GetOperationText(Quiz.Operation);

    cout << "\n====================================\n";
}

void PlayGame()
{
    stQuiz Quiz;

    Quiz.NumberOfQuestions = ReadNumberOfQuestions();
    Quiz.Operation = ReadOperationType();
    Quiz.Level = ReadLevelType();

    GenerateQuestions(Quiz);

    AskQuestions(Quiz);

    PrintFinalResult(Quiz);
}

void ResetScreen()
{
system("clear");    // إذا كنت تستخدم Linux استبدلها بـ system("clear");
}

void StartGame()
{
    char PlayAgain = 'Y';

    do
    {
        ResetScreen();

        PlayGame();

        cout << "\nPlay Again? (Y/N): ";
        cin >> PlayAgain;

    } while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
    srand((unsigned)time(NULL));

    StartGame();

    return 0;
}