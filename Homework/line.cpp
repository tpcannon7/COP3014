/*
Name: Trevor Cannon
Date: 3-16-2024
Assignment: Homework 5
Due Date: 3-28-2024
About this project: (write a small blurb about what this project's goals are/what tasks it accomplishes)
Assumptions: (write any assumptions made here (ex: assumes correct user input))

All work below was performed by Trevor Cannon
*/

#include <iostream>
#include <string>

using namespace std;

void helpMessage();

int main()
{
    const int MAXLENGTH = 20;
    char line[MAXLENGTH];

    string choice;

    helpMessage();

    cin >> choice;

    do
    {
        if (choice == "help")
        {
            helpMessage();
            cin >> choice;
        }
        

    }while(choice != "exit" || choice != "Exit");


    return 0;
}

void helpMessage()
{
  cout << "\nserve : serve next customer in the line" <<endl;
  cout << "enter $ : $ enters the line in the back" <<endl;
  cout << "cut @ $ : @ cuts in to the line in front of $" <<endl;
  cout << "leave $ : $ would leave the line" <<endl;
  cout << "status : print the status of the line" <<endl;
  cout << "first : print the item in the front of the line" <<endl;
  cout << "last : print the item in the back of the line" <<endl;
  cout << "help : reprint this menu" <<endl;
  cout << "exit : see ya!" <<endl <<endl;

  return;
}