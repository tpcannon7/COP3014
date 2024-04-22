/*

Name: Trevor Cannon
Date: 4-16-2024
Assignment: Homework #7
Due Date: 4-25-2024
About this project: Allows loading of movie database in the form of a text file in order to view certain characteristics of the movies like genre, year, runtime etc. Allows exporting of movies
based on genre, gives cumulative runtime, and prints database in order according to release year
Assumptions: Movie files are given in correct format, no trailing whitespaces in file, file will have atleast
one movie, file name will not be longer than 40 characters

All work below was performed by Trevor Cannon

*/

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

using namespace std;

struct Movies
{
    string genre;
    string movieName;
    int releaseYear;
    int runTime;
    string rating;
};


void helpMenu();
int runTimeSum(const Movies [], const int);
void sortMovies(Movies [], const int);
void exportMovies(const Movies [], const int, ofstream &);


int main() 
{
	Movies *movieArr = nullptr;
    ifstream in;
    ofstream out;
    string fileName, rating;
    int numMovies;
    char choice, fileChoice;
    bool fileLoaded = false, ratingFound;

    do
    {
        ratingFound = false;
        helpMenu();
        cout << "> ";
        cin >> choice;
        cin.ignore();

        cout << '\n';

        if (choice == '1')
        {
            if (fileLoaded)
            {
                cout << "There is a database already loaded. This will overwrite the current database." <<endl;
                cout << "Continue? (y/n) > ";
                cin >> fileChoice;
                while (tolower(fileChoice) != 'y' && tolower(fileChoice) != 'n')
                {
                    cout << "Enter y or n > ";
                    cin >> fileChoice;
                }
                if (tolower(fileChoice) == 'n')
                {
                    continue;
                }
                if (tolower(fileChoice) == 'y')
                {
                    cout << "Enter the name of the movie input file: ";
                    cin.ignore();
                    getline(cin, fileName);
                    in.open(fileName);
                }
            }

            if (!fileLoaded)
            {
                cout << "Enter the name of the movie input file: ";
                getline(cin, fileName);
                in.open(fileName);
            }

            while (!in)
            {
                cout << "Try again, invalid file name: ";
                getline(cin, fileName);
                in.open(fileName);
            }
            cout << '\n';
            fileLoaded = true;

            in >> numMovies;
            in.ignore();

            movieArr = new Movies[numMovies];

            for(int i = 0; i < numMovies; i++)
            {
                getline(in, movieArr[i].genre, ':' );
                getline(in, movieArr[i].movieName, ',' );
                in.ignore();
                in >> movieArr[i].releaseYear;
                in.ignore();
                in >> movieArr[i].runTime;
                in.ignore();
                in >> movieArr[i].rating;
                in.ignore();
            }
            in.close();
        }
        else if (choice == '2')
        {
            cout << "Total Movie Database Runtime: ";
            cout << runTimeSum(movieArr, numMovies) / 60 << " hrs " << runTimeSum(movieArr, numMovies) % 60 << " mins\n\n";
        }
        else if (choice == '3' && fileLoaded)
        {
            cout << "View movies with which rating? (G, PG, PG-13, R) > ";
            cin >> rating;

            cout << "\nMOVIES RATED " << rating <<"\n";

            for (int i = 0; i < numMovies; i++)
            {
                if (rating == movieArr[i].rating)
                {
                    ratingFound = true;
                    cout << movieArr[i].movieName << '\n';
                }
            }
            if (!ratingFound)
            {
                cout << "No movies with rating: " <<rating << '\n';
            }
            cout << '\n';
        }
        else if (choice == '3' && !fileLoaded)
            cout << "Load movie file first! Use option 1. \n\n";
        else if (choice == '4' && fileLoaded)
        {
            cout << "Exporting database by genre...\n";
            exportMovies(movieArr, numMovies, out);
            cout << "...export complete.\n\n";
        }
        else if (choice == '4' && !fileLoaded)
            cout << "Load movie file first! Use option 1. \n\n";
        else if (choice == '5' && !fileLoaded)
            cout << "Movie database already empty.\n\n";
        else if (choice == '5' && fileLoaded)
        {
            delete [] movieArr;
            movieArr = nullptr;
            numMovies = 0;
            cout << "Movie database cleared successfully.\n\n";
            fileLoaded = false;
        }
        else if (choice == '6' && !fileLoaded)
            cout << "Load movie file first! Use option 1. \n\n";
        else if (choice == '6' && fileLoaded)
        {
            sortMovies(movieArr, numMovies);

            for(int i = 0; i < numMovies; i++)
                cout << movieArr[i].releaseYear << " : " << movieArr[i].movieName <<endl; 
            cout << '\n';
        }

    }while(tolower(choice) != 'q');
    
    cout << "Thanks for using the Movie Database Organizer!";


    delete [] movieArr;

    return 0;
}

void helpMenu()
{
    cout << "1 - Load Movie File" <<endl;
    cout << "2 - View Total Movie Database Runtime" <<endl;
    cout << "3 - View Movies by Rating" <<endl;
    cout << "4 - Export Movies by Genre" <<endl;
    cout << "5 - Clear Currently Loaded Database" <<endl;
    cout << "6 - Print Database Sorted by Year" <<endl;
    cout << "Q - Quit" <<endl;
}

int runTimeSum(const Movies movieArr[], const int numMovies)
{
    int sum = 0;
    for (int i = 0; i < numMovies; i++)
    {
        sum += movieArr[i].runTime;
    }
    return sum;
}

void sortMovies(Movies movieArr[], const int numMovies)
{
    Movies temp;
    bool swap;

    do
    {
        swap = false;
        for (int i = 0; i < numMovies; i++)
        {
            if (movieArr[i].releaseYear > movieArr[i + 1].releaseYear) 
            {
                swap = true;
                temp = movieArr[i];
                movieArr[i] = movieArr[i + 1];
                movieArr[i + 1] = temp;
            }
        }
    } while (swap == true);
}

void exportMovies(const Movies movieArr[], const int numMovies, ofstream &out)
{
    out.open("action.txt");
            for (int i = 0; i < numMovies; i++)
            {
                if (movieArr[i].genre == "ACTION")
                {
                    out << movieArr[i].movieName << " (" << movieArr[i].releaseYear << ")\n" ;
                }
            }
    out.close();
    out.open("drama.txt");
    for (int i = 0; i < numMovies; i++)
    {
        if (movieArr[i].genre == "DRAMA")
        {
            out << movieArr[i].movieName << " (" << movieArr[i].releaseYear << ")\n" ;
        }
    }
    out.close();
    out.open("comedy.txt");
    for (int i = 0; i < numMovies; i++)
    {
        if (movieArr[i].genre == "COMEDY")
        {
            out << movieArr[i].movieName << " (" << movieArr[i].releaseYear << ")\n" ;
        }
    }
    out.close();
    out.open("scifi.txt");
    for (int i = 0; i < numMovies; i++)
    {
        if (movieArr[i].genre == "SCIENCE FICTION")
        {
            out << movieArr[i].movieName << " (" << movieArr[i].releaseYear << ")\n" ;
        }
    }
    out.close();
}