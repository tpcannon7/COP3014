/* Name: Trevor Cannon
Date: 4-1-2024
Assignment: Homework #6
Due Date: 4-11-2024

About this project: Allows user to enter a sentence (numbers, words, spaces etc.) and a word and gives
statistics (puncuation, vowels, word count, word lengths, and checks if user word is present in sentence) regarding the sentence.

Assumptions: Assumes user enters a single word, no whitespace. Assumes string will be less than 100 characters long 
and max word length is 20 characters.

All work below was performed by Trevor Cannon 
*/


#include <iostream>
#include <string>
#include <cctype>

using namespace std;

int numPunct(string);
int numVowels(string);

int main()
{
    string userString, userWord, userChoice;
    bool yesno = true;

    do
    {
        //variable declarations that reset with each loop iteration
        bool wordFound = false;
        int numPunctuation = 0, numVowel = 0, numWords = 0, letterCount = 0;
        int counts[21] = {0};

        //user entry of string and word
        cout << "Enter a sentence: ";
        getline(cin, userString);

        cout << "Enter a word: ";
        getline(cin, userWord);

        //for loop used to check puncuation, vowels, if word is present, and word lengths
        for (int i = 0; i < userString.size(); i++)
        {
            if (isspace(userString[i]) != 0)
                numWords++;
            if (userString.substr(i, userWord.size()) == userWord)
            {
                wordFound = true;
            }
            if (isspace(userString[i]) == 0)
            {
                letterCount++;
            }
            else if (isspace(userString[i]) != 0)
            {
                if (letterCount > 0)
                {
                    counts[letterCount]++;
                    letterCount = 0;
                }
            }
        }

        if (letterCount > 0)
        {
            counts[letterCount]++;
        }

        numVowel = numVowels(userString);
        numPunctuation = numPunct(userString);

        //sentence analysis printout
        cout << "Sentence Analysis: \n\n";
        cout << "Punctuation Characters: "  <<numPunctuation <<endl;
        cout << "Vowels: " <<numVowel <<endl;
        cout << "Words: " <<numWords + 1 <<endl <<endl;

        cout << "Word Lengths: \n";
        
        for (int i = 1; i < 21; i++)
        {
            if (counts[i] != 0 && counts[i] > 1)
            {
                cout << i << " characters long: " <<counts[i] << " words." <<endl;
            }
            else if (counts[i] != 0 && counts[i] == 1)
            {
                cout << i << " characters long: " <<counts[i] << " word." <<endl;
            }
        }

        if (wordFound == true)
            cout << "The word: " << '"' <<userWord << '"' << " IS part of the sentence you entered. \n";
        else
            cout << "The word: " <<'"' <<userWord <<'"' << " IS NOT part of the sentence you entered. \n";


        //prompts user if they want to continue analyzing sentences/words
        cout << "Enter another sentence/word for analysis (yes/no): ";
        cin >> userChoice;
        cout << '\n';

        //error checking of yes/no entry of user, forces user to enter either yes or no, not case-sensitive
        do
        {
            for (int i = 0; i < userChoice.size(); i++)
                userChoice[i] = tolower(userChoice[i]);
            if (userChoice == "no")
            {
                yesno = false;
                break;
            }
            else if (userChoice != "yes")
            {
                cout << "Enter a yes or no: ";
                cin >> userChoice;
            }
        }while (userChoice != "yes");

        cin.ignore();

        cout << '\n';

    }while(yesno == true);

    
     return 0;
}

//function to check number of punctuation
int numPunct(string userString)
{
    int numPunctuation = 0;
    for(int i = 0; i < userString.size(); i++)
    {
        if (ispunct(userString[i]) != 0)
            numPunctuation++;
    }
    return numPunctuation;

}

//function to check number of vowels
int numVowels(string userString)
{
    int numVowels = 0;
    for (int i = 0; i < userString.size(); i++)
    {
         if (tolower(userString[i]) == 'a'||
            tolower(userString[i]) =='e'||
            tolower(userString[i]) =='i'||
            tolower(userString[i]) =='o'||
            tolower(userString[i]) =='u')
                numVowels++;
    }
    return numVowels;
}