#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <ctime>
#include <cstdlib>

using namespace std;

template <typename T1, typename T2>
class Pair
{
public:
    Pair(const T1 &first, const T2 &second) : first_(first), second_(second) {}

    T1 getFirst() const
    {
        return first_;
    }

    T2 getSecond() const
    {
        return second_;
    }

private:
    T1 first_;
    T2 second_;
};

class Message
{
private:
    string sender;
    string recipient;
    string content;

public:
    Message(string _sender, string _recipient, string _content)
        : sender(_sender), recipient(_recipient), content(_content) {}

    friend class Contact;
};

class Contact
{
private:
    string name;
    string phoneNumber;
    vector<Message> messages;

public:
    Contact(string _name, string _phoneNumber) : name(_name), phoneNumber(_phoneNumber) {}

    string getName() const
    {
        return name;
    }

    void displayInfo()
    {
        cout << "Name: " << name << endl;
        cout << "Phone Number: " << phoneNumber << endl;
    }

    void sendMessage(Contact &recipient, string content)
    {
        Message newMessage(name, recipient.name, content);
        recipient.receiveMessage(newMessage);
        messages.push_back(newMessage);
    }

    void receiveMessage(const Message &message)
    {
        messages.push_back(message);
    }

    void displayMessages()
    {
        cout << "Messages with " << name << ":\n";
        for (const auto &message : messages)
        {
            cout << "From: " << message.sender << endl;
            cout << "Content: " << message.content << endl;
            cout << "--------\n";
        }
    }

    friend ostream &operator<<(ostream &os, const Contact &contact);
    friend istream &operator>>(istream &is, Contact &contact);
};

ostream &operator<<(ostream &os, const Contact &contact)
{
    os << contact.name << " " << contact.phoneNumber;
    return os;
}

istream &operator>>(istream &is, Contact &contact)
{
    is >> contact.name >> contact.phoneNumber;
    return is;
}

class Game
{
public:
    virtual void play() = 0;
    virtual ~Game(){}
};

class Calculator
{
public:
    virtual double calculate(double operand1, double operand2) = 0;
    virtual ~Calculator(){}
};

class BasicCalculator : public Calculator
{
public:
    double calculate(double operand1, double operand2) override
    {
        return operand1 + operand2;
    }
};

class ScientificCalculator : public Calculator
{
public:
    double calculate(double operand1, double operand2) override
    {
        return operand1 * operand2;
    }
};

class MobilePhone
{
private:
    vector<Contact> contacts;
    Calculator *calculator;
    Game *game;
    vector<Pair<string, double>> calculatorResults;

public:
    MobilePhone() : calculator(nullptr), game(nullptr) {}

    ~MobilePhone()
    {
        delete calculator;
        delete game;
    }

    void addContact(const Contact &contact)
    {
        contacts.push_back(contact);
    }
    void performAndStoreCalculation(double operand1, double operand2, const string &description)
    {
        double result = calculate(operand1, operand2);
        calculatorResults.emplace_back(description, result);
    }

    const vector<Contact> &getContacts()
    {
        return contacts;
    }

    void listContacts()
    {
        cout << "Contacts:\n";
        for (auto &contact : contacts)
        {
            contact.displayInfo();
            cout << "--------\n";
        }
    }

    void sendMessage(const string &senderName, const string &recipientName, const string &content)
    {
        Contact *sender = nullptr;
        Contact *recipient = nullptr;

        for (auto &contact : contacts)
        {
            if (contact.getName() == senderName)
            {
                sender = &contact;
            }
            if (contact.getName() == recipientName)
            {
                recipient = &contact;
            }
        }

        if (sender && recipient)
        {
            sender->sendMessage(*recipient, content);
        }
    }

    void setCalculator(Calculator *calc)
    {
        if (calculator != nullptr)
        {
            delete calculator;
        }
        calculator = calc;
    }

    void setGame(Game *_game)
    {
        if (game != nullptr)
        {
            delete game;
        }
        game = _game;
    }

    void playGame()
    {
        if (game != nullptr)
        {
            game->play();
        }
        else
        {
            cout << "No game installed." << endl;
        }
    }

    double calculate(double operand1, double operand2)
    {
        if (calculator != nullptr)
        {
            return calculator->calculate(operand1, operand2);
        }
        else
        {
            cout << "No calculator installed." << endl;
            return 0.0;
        }
    }

    void saveContactsToFile(const string &filename)
    {
        ofstream file(filename);
        if (!file)
        {
            cerr << "Failed to open the file for writing." << endl;
            return;
        }

        for (const auto &contact : contacts)
        {
            file << contact << endl;
        }
        file.close();
    }
    void displayCalculatorResults()
    {
        cout << "Calculator Results:\n";
        for (const auto &result : calculatorResults)
        {
            cout << "Description: " << result.getFirst() << endl;
            cout << "Result: " << result.getSecond() << endl;
            cout << "--------\n";
        }
    }

    void loadContactsFromFile(const string &filename)
    {
        ifstream file(filename);
        if (!file)
        {
            cerr << "Failed to open the file for reading." << endl;
            return;
        }

        Contact contact("", "");
        while (file >> contact)
        {
            contacts.push_back(contact);
        }
        file.close();
    }
};

class TicTacToe : public Game
{
private:
    vector<vector<char>> board;
    char currentPlayer;
    bool gameOver;

public:
    TicTacToe()
    {
        board = {{' ', ' ', ' '},
                 {' ', ' ', ' '},
                 {' ', ' ', ' '}};
        currentPlayer = 'X';
        gameOver = false;
    }

    void displayBoard()
    {
        cout << "Tic-Tac-Toe Board:\n";
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                cout << board[i][j];
                if (j < 2)
                {
                    cout << " | ";
                }
            }
            cout << endl;
            if (i < 2)
            {
                cout << "---------\n";
            }
        }
    }

    void switchPlayer()
    {
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }

    bool isMoveValid(int row, int col)
    {
        return (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == ' ');
    }

    bool isGameOver()
    {
        return gameOver;
    }

    bool checkWin()
    {
        for (int i = 0; i < 3; i++)
        {
            if (board[i][0] == currentPlayer && board[i][1] == currentPlayer && board[i][2] == currentPlayer)
            {
                gameOver = true;
                return true;
            }
            if (board[0][i] == currentPlayer && board[1][i] == currentPlayer && board[2][i] == currentPlayer)
            {
                gameOver = true;
                return true;
            }
        }
        if (board[0][0] == currentPlayer && board[1][1] == currentPlayer && board[2][2] == currentPlayer)
        {
            gameOver = true;
            return true;
        }
        if (board[0][2] == currentPlayer && board[1][1] == currentPlayer && board[2][0] == currentPlayer)
        {
            gameOver = true;
            return true;
        }
        return false;
    }

    void play() override
    {
        while (!isGameOver())
        {
            displayBoard();
            int row, col;
            cout << "Player " << currentPlayer << ", enter your move (row and column): ";
            cin >> row >> col;

            if (isMoveValid(row, col))
            {
                board[row][col] = currentPlayer;
                if (checkWin())
                {
                    displayBoard();
                    cout << "Player " << currentPlayer << " wins!\n";
                }
                else if (isBoardFull())
                {
                    displayBoard();
                    cout << "It's a draw!\n";
                    break;
                }
                else
                {
                    switchPlayer();
                }
            }
            else
            {
                cout << "Invalid move. Try again.\n";
            }
        }
    }

    bool isBoardFull()
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (board[i][j] == ' ')
                {
                    return false;
                }
            }
        }
        return true;
    }
};

class NumberGuessingGame : public Game
{
private:
    int numberToGuess;
    bool gameOver;

public:
    NumberGuessingGame()
    {
        srand(static_cast<unsigned>(time(nullptr))); 
        numberToGuess = rand() % 100 + 1;         
        gameOver = false;
    }

    void play() override
    {
        cout << "Welcome to the Number Guessing Game!\n";
        cout << "Try to guess the number between 1 and 100.\n";

        while (!gameOver)
        {
            int guess;
            cout << "Enter your guess: ";
            cin >> guess;

            if (guess < 1 || guess > 100)
            {
                cout << "Invalid guess. Please enter a number between 1 and 100.\n";
                continue;
            }

            if (guess < numberToGuess)
            {
                cout << "Too low! Try again.\n";
            }
            else if (guess > numberToGuess)
            {
                cout << "Too high! Try again.\n";
            }
            else
            {
                cout << "Congratulations! You guessed the number.\n";
                gameOver = true;
            }
        }
    }
};

class RockPaperScissorsGame : public Game
{
public:
    void play() override
    {
        cout << "Welcome to Rock, Paper, Scissors!\n";
        cout << "Choose: 1 (Rock), 2 (Paper), 3 (Scissors)\n";

        while (true)
        {
            int userChoice, computerChoice;
            cout << "Enter your choice: ";
            cin >> userChoice;

            if (userChoice < 1 || userChoice > 3)
            {
                cout << "Invalid choice. Please choose 1, 2, or 3.\n";
                continue;
            }

            computerChoice = rand() % 3 + 1; 

            cout << "Computer chose: " << computerChoice << endl;

            if (userChoice == computerChoice)
            {
                cout << "It's a draw!\n";
            }
            else if ((userChoice == 1 && computerChoice == 3) ||
                     (userChoice == 2 && computerChoice == 1) ||
                     (userChoice == 3 && computerChoice == 2))
            {
                cout << "You win!\n";
            }
            else
            {
                cout << "Computer wins!\n";
            }

            char playAgain;
            cout << "Play again? (y/n): ";
            cin >> playAgain;

            if (playAgain != 'y' && playAgain != 'Y')
            {
                break;
            }
        }
    }
};

int main()
{
    MobilePhone myPhone;

    while (true)
    {
        cout << "\nMenu:\n";
        cout << "1. Add Contact\n";
        cout << "2. List Contacts\n";
        cout << "3. Send Message\n";
        cout << "4. View Messages\n";
        cout << "5. Set Calculator (Basic/Scientific)\n";
        cout << "6. Perform Calculation\n";
        cout << "7. Set Game (Tic-Tac-Toe)\n";
        cout << "8. Play Game (Tic-Tac-Toe)\n";
        cout << "9. Set Game (Number Guessing)\n";
        cout << "10. Play Game (Number Guessing)\n";
        cout << "11. Set Game (Rock, Paper, Scissors)\n";
        cout << "12. Play Game (Rock, Paper, Scissors)\n";
        cout << "13. Save Contacts to File\n";
        cout << "14. Load Contacts from File\n";
        cout << "15. Exit\n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            string name, phoneNumber;
            cout << "Enter Contact Name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter Phone Number: ";
            getline(cin, phoneNumber);
            Contact newContact(name, phoneNumber);
            myPhone.addContact(newContact);
            cout << "Contact added successfully." << endl;
            break;
        }
        case 2:
            myPhone.listContacts();
            break;
        case 3:
        {
            cout << "Enter sender's name: ";
            string senderName;
            cin.ignore();
            getline(cin, senderName);
            cout << "Enter recipient's name: ";
            string recipientName;
            getline(cin, recipientName);
            cout << "Enter message content: ";
            string messageContent;
            getline(cin, messageContent);

            myPhone.sendMessage(senderName, recipientName, messageContent);
            cout << "Message sent successfully." << endl;
            break;
        }
        case 4:
        {
            cout << "Enter contact's name to view messages: ";
            string contactName;
            cin.ignore();
            getline(cin, contactName);

            for (const auto &contact : myPhone.getContacts())
            {
                if (contact.getName() == contactName)
                {
                    Contact mutableContact = contact;
                    mutableContact.displayMessages();
                    break;
                }
            }
            break;
        }

        case 5:
        {
            cout << "Select Calculator Type:\n";
            cout << "1. Basic Calculator\n";
            cout << "2. Scientific Calculator\n";
            int calcChoice;
            cin >> calcChoice;
            if (calcChoice == 1)
            {
                myPhone.setCalculator(new BasicCalculator());
                cout << "Basic Calculator selected." << endl;
            }
            else if (calcChoice == 2)
            {
                myPhone.setCalculator(new ScientificCalculator());
                cout << "Scientific Calculator selected." << endl;
            }
            else
            {
                cout << "Invalid choice." << endl;
            }
            break;
        }
        case 6:
        {
            double operand1, operand2;
            cout << "Enter Operand 1: ";
            cin >> operand1;
            cout << "Enter Operand 2: ";
            cin >> operand2;
            double result = myPhone.calculate(operand1, operand2);
            cout << "Result: " << result << endl;
            myPhone.performAndStoreCalculation(5.0, 3.0, "Addition");
            myPhone.performAndStoreCalculation(5.0, 3.0, "Multiplication");
            break;
        }
        case 7:
            myPhone.setGame(new TicTacToe());
            cout << "Tic-Tac-Toe game selected." << endl;
            break;
        case 8:
            myPhone.playGame();
            break;
        case 9:
        {
            myPhone.setGame(new NumberGuessingGame());
            cout << "Number Guessing game selected." << endl;
            break;
        }
        case 10:
        {
            myPhone.playGame();
            break;
        }
        case 11:
        {
            myPhone.setGame(new RockPaperScissorsGame());
            cout << "Rock, Paper, Scissors game selected." << endl;
            break;
        }
        case 12:
        {
            myPhone.playGame();
            break;
        }
        case 13:
        {
            string filename;
            cout << "Enter the filename to save contacts: ";
            cin >> filename;
            myPhone.saveContactsToFile(filename);
            cout << "Contacts saved to file successfully." << endl;
            break;
        }
        case 14:
        {
            string filename;
            cout << "Enter the filename to load contacts: ";
            cin >> filename;
            myPhone.loadContactsFromFile(filename);
            cout << "Contacts loaded from file successfully." << endl;
            break;
        }
        case 15:
            cout << "Exiting program...\n";
            return 0;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    }
    return 0;
}
