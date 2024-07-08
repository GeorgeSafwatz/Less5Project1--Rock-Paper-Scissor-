#include <iostream>
#include <string>
#include <cmath>
#include <Windows.h>

enum class enGameChoices {Rock =1, Paper=2, Scissor=3};
enum class enGameResults {Win , Draw, Lose};
enum class enConsoleTextColor{Green= 0x02, Red= 0x04, Black=0x07};

using namespace std;
namespace utils {
    //checkers
    static bool checkIfCinPass() {
        if (cin.fail()) {
            cin.clear();
            cin.ignore('\n');
            cerr << "Please enter an input of a valid data type" << endl;
            return false;
        }
        return true;
}
    template<typename T> bool isNumInRange(T num, T lowerLimit, T upperLimit) {
        if (num >= lowerLimit && num <= upperLimit)
        {
            return true;
        }
        cerr << "Number isn't in range " 
            <<to_string(lowerLimit) 
            <<":"
            <<to_string(upperLimit) 
            << endl;
        return false;
    }
    
    //modifiers
    static void setColor(enConsoleTextColor color) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), static_cast<int>(color));
}

    //generating
    static unsigned short generateRandomNum(unsigned short lowerLimit, unsigned short upperLimit) {
        srand(time(0));
        return rand()%(upperLimit-lowerLimit+1)+lowerLimit;
    }
    
    //prompting
    template<typename T> T prompt(string promptingText) {
        T arg;
        bool isInvalidInput= false;
        do
        {
        cout << promptingText << endl;
        cin >> arg;
        if (!checkIfCinPass())  isInvalidInput = true;
        else isInvalidInput = false;
        } while (isInvalidInput);
        return arg;
    }
    template<typename T> T promptNumBetween(string promptingText, T lowerLimit, T upperLimit) {
        T arg;
        bool isInvalidInput = false;
        do
        {
            cout << promptingText << endl;
            cin >> arg;
            if (!checkIfCinPass() || !isNumInRange(arg,lowerLimit,upperLimit))  
                isInvalidInput = true;
            else isInvalidInput = false;
        } while (isInvalidInput);
        return arg;
    }
}
using namespace utils;
 
static enGameResults handleRockPaperScissor(enGameChoices plChoice, enGameChoices cpChoice) {
    switch (plChoice)
    {
    case enGameChoices::Rock:
        if (cpChoice == enGameChoices::Rock) return enGameResults::Draw;
        if (cpChoice == enGameChoices::Paper) return enGameResults::Lose;
        if (cpChoice == enGameChoices::Scissor) return enGameResults::Win;
    case enGameChoices::Paper:
        if (cpChoice == enGameChoices::Rock) return enGameResults::Win;
        if (cpChoice == enGameChoices::Paper) return enGameResults::Draw;
        if (cpChoice == enGameChoices::Scissor) return enGameResults::Lose;
    case enGameChoices::Scissor:
        if (cpChoice == enGameChoices::Rock) return enGameResults::Lose;
        if (cpChoice == enGameChoices::Paper) return enGameResults::Win;
        if (cpChoice == enGameChoices::Scissor) return enGameResults::Draw;
    }
}
static void handleGameResults(enGameResults gameResult, unsigned short & plWins, unsigned short& cpWins) {
    switch (gameResult)
    {
    case enGameResults::Win:
        plWins++;
        setColor(enConsoleTextColor::Green);
        cout << "Player Wins!" << endl;
        break;
    case enGameResults::Lose:
        setColor(enConsoleTextColor::Red);
        cout << "Player Lose!" << endl;
        cpWins++;
        break;
    case enGameResults::Draw:
        cout << "Draw!" << endl;
        break;
    }
}
static void handleOverAllResult(unsigned short const & plWins, unsigned short const & cpWins) {
    if (plWins > cpWins)
        cout
        << "Player Wins!\n"
        << "Player wins "
        << to_string(plWins)
        << "vs computer wins "
        << to_string(cpWins)
        << endl;
    else if (cpWins > plWins)
        cout
        << "Computer Wins!\n"
        << "Computer wins "
        << to_string(cpWins)
        << "vs Play wins "
        << to_string(plWins)
        << endl;
    else
        cout
        << "It's a Draw!\n"
        << "Computer wins "
        << to_string(cpWins)
        << "vs Play wins "
        << to_string(plWins)
        << endl;
}

static void playRockPaperScissor() {
    srand(time(0));
    unsigned short plWins = 0, cpWins = 0;
    enGameChoices playerChoice, computerChoice;
    enGameResults gameResult;
    bool playAgain = true;
    while (playAgain)
    {
        playerChoice = static_cast<enGameChoices> (promptNumBetween<unsigned short>("Please enter your choice: \n1) Rock\n2) Paper\n3) Scissor", 1, 3));
        computerChoice = static_cast<enGameChoices>(generateRandomNum(1, 3));        
        gameResult = handleRockPaperScissor(playerChoice, computerChoice);
        handleGameResults(gameResult,plWins,cpWins);
        setColor(enConsoleTextColor::Black);
        playAgain = static_cast<bool>(promptNumBetween<unsigned short>("Do you want to play again?\n0) No\n1) Yes", 0, 1));
    }
    handleOverAllResult(plWins,cpWins);
}
int main()
{
    playRockPaperScissor();
}
