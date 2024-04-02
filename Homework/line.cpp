/*
Name: Trevor Cannon
Date: 3-16-2024
Assignment: Homework 5
Due Date: 4-2-2024
About this project: Allows user to create a line/queue of symbols that wait in line until they are served.
User can use various commands to manage the line.
Assumptions: User will use commands properly (like with cut command by typing two characters correctly)

All work below was performed by Trevor Cannon
*/

#include <iostream>
#include <string>
#include <cctype>

using namespace std;

//function declarations
void helpMessage();
void status(const char[], int);
bool checkLine(const char[], int, char);
int checkLine(const char[], int, char, char);
void cutLine(char[], int, char, char);
void sortLine(char [], int);


int main()
{
    //array declaration
    const int MAXLENGTH = 20;
    char line[MAXLENGTH];

    //tracks how many items are currently in line
    int currentLineLength = 0;

    //command variable + character variables for array
    string choice;
    char ch1, ch2;

    helpMessage();

    do
    {
        cout << "> ";
        cin >> choice;

        //BONUS : converts "choice" user input to all lowercase
        for (int i = 0; i < choice.size(); i++)
            choice[i] = tolower(choice[i]);

        //displays help message when help is entered
        if (choice == "help")
            helpMessage();

        //displays first item in line
        else if (choice == "first")
            cout << line[0] << " is first in line. " <<endl;

        //displays last item in line
        else if (choice == "last")
            cout << line[currentLineLength - 1] << " is last in line." <<endl;

        //serves first character in line
        else if (choice == "serve")
        {
            if (currentLineLength == 0)
            {
                cout << "The line is empty." <<endl;
            }
            else 
            {
                cout << "Serving: " <<line[0] <<endl;
                for (int i = 0; i < currentLineLength; i++)
                {
                    line[i] = line[i+1];
                }
                currentLineLength--;
            }
        }

        //enters a character into the line array
        else if (choice == "enter")
        {
            cin >> ch1;

            if (checkLine(line, currentLineLength, ch1) == true)
            {
                line[currentLineLength] = ch1;
                currentLineLength++;
            }
            else if (currentLineLength == MAXLENGTH)
            {
                cout << "The line is full." <<endl;
            }
            else
            {
                cout << ch1 << " is already in line." <<endl;
            }
        }

        //displays all items in line and gives number of items in line
        else if (choice == "status")
        {
            status(line,currentLineLength);
        }

        //allows user to cut one character in front of another currently in line
        else if (choice == "cut")
        {
            cin >> ch1;
            cin >> ch2;

            if (checkLine(line,currentLineLength,ch1, ch2) == 3)
            {
                cutLine(line, currentLineLength, ch1, ch2);
                currentLineLength++;
            }
            else if (checkLine(line,currentLineLength,ch1, ch2) == 2)
            {
                cout << "Cannot cut in front of " << ch2  << "."<<endl;
                cout << ch2 << " is not in line. " <<endl;
            }
            else if (currentLineLength == MAXLENGTH)
            {
                cout << "Cannot cut in line. Line is full." <<endl;
            }
            else if (checkLine(line,currentLineLength,ch1, ch2) == 1)
            {
                cout << ch1 << " is already in line, cannot cut in line. " <<endl;
            }
        }

        //user chosen character exits the line array
        else if (choice == "leave")
        {
            cin >> ch1;

            if (checkLine(line, currentLineLength, ch1) == false)
            {
                for (int i = 0; i < currentLineLength - 1; i++)
                {
                    if (line[i] == ch1)
                    {
                        for(int n = i; n < currentLineLength; n++)
                        {
                            line[n] = line[n+1];
                        }
                    }
                }
                currentLineLength--;
            }
            else
            {
                cout << ch1 << " is not in line." <<endl;
            }
        }

        //BONUS : sorts line according to character ASCII values, least to greatest
        else if (choice == "sort")
        {
            sortLine(line, currentLineLength);
        }
        //BONUS : error checks if invalid choice is entered
        else
        {
            if(choice != "exit")
                cout << "Invalid menu command. Try again." <<endl;
        }

    }while(choice != "exit");

    //leaves program and displays items currently in line
    if (choice == "exit")
    {
        
        cout << "There are " <<currentLineLength << " items in line ";
            for (int i = 0; i <= currentLineLength - 2; i++)
                cout << line[i] << ", ";
        cout << line[currentLineLength - 1];
    }

    return 0;
}

//reprints menu with commands
void helpMessage()
{
  cout << "-----------------COMMANDS-----------------";
  cout << "\nserve : serve next customer in the line" <<endl;
  cout << "enter $ : $ enters the line in the back" <<endl;
  cout << "cut @ $ : @ cuts in to the line in front of $" <<endl;
  cout << "leave $ : $ would leave the line" <<endl;
  cout << "status : print the status of the line" <<endl;
  cout << "first : print the item in the front of the line" <<endl;
  cout << "last : print the item in the back of the line" <<endl;
  cout << "help : reprint this menu" <<endl;
  cout << "sort : sorts line according the character ASCII values, least to greatest" <<endl;
  cout << "exit : see ya!" <<endl;
  cout << "------------------------------------------ " <<endl;
  return;
}

//function displays characters in line and number of characters in line
void status(const char line[] ,int currentLineLength)
{
    cout << "There are " <<currentLineLength << " items in line: ";
         for (int i = 0; i < currentLineLength - 1; i++)
            cout << line[i] << ", ";
        cout << line[currentLineLength - 1];
        cout <<endl;
}

//checks the line to confirm if entered only one selected chracter is present in line
bool checkLine(const char line[], int currentLineLength, char ch1)
{
    for (int i = 0; i < currentLineLength; i++)
    {
        if (line[i] == ch1)
            return false;
    }
    return true;
}

//checks if two seperate characters are present in line
int checkLine(const char line[], int currentLineLength, char ch1, char ch2)
{
    bool ch2inLine = false;
    
    for (int i = 0; i < currentLineLength; i++)
    {
        if (line[i] == ch1)
            return 1;
    }
    for (int i = 0; i < currentLineLength; i++)
    {
        if (line[i] == ch2)
            ch2inLine = true;
    }
    if (ch2inLine == true)
        return 3;
    return 2;
}

//function for cutting the line
void cutLine(char line[], int currentLineLength, char ch1, char ch2)
{
    for (int n = 0; n < currentLineLength; n++)
    {
        if (line[n] == ch2)
        {
            for (int i = currentLineLength; i > n; i-- )
            {
                line[i] = line[i-1];
            }
            line[n] = ch1;
            break;
        }
    }
    cout << ch1 << " cut in front of " <<ch2 <<endl;
}

//function sorts line according to ASCII value
void sortLine(char line[], int currentLineLength)
{
    bool swap;
    char temp;

    do
    {
        swap = false;
        for (int i = 0; i < currentLineLength - 1; i++)
        {
            if (line[i+1] < line[i])
            {
                swap = true;
                temp = line[i];
                line[i] = line [i+1];
                line[i + 1] = temp;
            }
        }


    } while (swap == true);
    
}