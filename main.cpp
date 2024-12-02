#include "input.h"      //input file provided by the professor 
#include <vector>       //include vector library
#include "Rational.h"   //include rational header file
#include <iostream>     //include input-output library
#include <stdexcept>    //include exception handling library
#include <algorithm>    //include algorithms like sort
#include <numeric>      //include gcd and numeric utilities
#include <list>         //include list container library
#include <limits>       //include numeric limits library
#include <queue>        //include queue container library
#include <cstdlib>      //include standard library utilities
#include <string>       //include string handling utilities
#include <iomanip>      //include input-output manipulators

using namespace std;    //use standard namespace


// Function prototypes
int menuOption();
void vectorContainer();
void listContainer();
void stackContainer();
void queueContainer();
int gcd(int a, int b);
int getValidatedInteger(const std::string& prompt, int min, int max);
pair<int, int> inputRational();
Rational getValidatedRational();
void displayQueue(std::queue<Rational> q);



//main function handles program flow control
int main()
{
    do
    {
        switch (menuOption())
        {
        case 'V': vectorContainer(); break;   //option for vector container
        case 'L': listContainer(); break;     //option for list container
        case 'S': stackContainer(); break;    //option for stack container
        case 'Q': queueContainer(); break;    //option for queue container
        case 'X': exit(0); break;             //exit the program
        default: cout << "\t\tERROR - Invalid option. Please re-enter.\n"; break;
        }
        cout << "\n";
        system("pause");
    } while (true);

    return EXIT_SUCCESS;
}

//menuOption function displays user menu options
int menuOption()
{
    system("cls"); //clear the screen

    //static program title and heading
    cout << "\n\n\tA container is a holder object that stores a collection of other objects (its elements). They are";
    cout << "\n\timplemented as class templates, which allows great flexibility in the types supported as elements.";
    cout << "\n\tThe container manages the storage space for its elements and provides member functions to access them";
    cout << "\n\teither directly or through iterators (reference objects with similar properties to pointers).";

    cout << "\n\n\n\n\tCMPR121 Exam3: STL (Standard Template Library) Containers and Container Adaptors by Francisco Bumanglag";
    cout << "\n\t" << string(100, char(205));            //menu border formatting
    cout << "\n\tV. Vector Container";                   //option for vector container
    cout << "\n\tL. List Container";                     //option for list container
    cout << "\n\tS. Stack (LIFO) Container Adaptor";     //option for stack container adaptor
    cout << "\n\tQ. Queue (FIFO) Container Adaptor";     //option for queue container adaptor
    cout << "\n\t" << string(100, char(196));
    cout << "\n\tX. Exit";                              // Exit option
    cout << "\n\t" << string(100, char(205));            // Menu border formatting

    //get user menu input
    char option;
    cout << "\n\tOption: ";
    cin >> option;

    //convert input to uppercase to make it case-insensitive
    option = toupper(option);

    return option;
}


//custom GCD function
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return abs(a);
}

//helper function to validate integer input -- void vectorContainer
int getValidatedInteger(const string& prompt, int min, int max)
{
    int value;
    while (true)
    {
        cout << prompt;
        cin >> value;

        if (cin.fail()) //check for invalid input (e.g., alpha characters)
        {
            cin.clear(); //clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); //discard invalid input
            cout << "ERROR: Invalid input. Must be an integer type.\n";
        }
        else if (value < min || value > max) //check for range
        {
            cout << "ERROR: Invalid input. Must be from " << min << ".." << max << ".\n";
        }
        else
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); //clear buffer
            return value; //valid input
        }
    }
}

//Vector Container Function
void vectorContainer()
{
    system("cls"); //clear the screen

    vector<Rational> vec; //vector to store Rational numbers
    char option;          //menu option

    do
    {
        //display the current state of the vector
        cout << "\n\tVectors (array) are same as dynamic arrays with the ability to resize itself automatically"
            << "\n\twhen an element is inserted or deleted, that contains their storage being handled automatically"
            << "\n\tby the container. Vector elements are placed in contiguous storage so that they can be accessed"
            << "\n\tand traversed using iterators or indexes.\n";

        if (vec.empty())
        {
            cout << "\n\tThe current vector is empty.\n\n\n";
        }
        else
        {
            cout << "\n\tThe current vector contains " << vec.size() << (vec.size() == 1 ? " element: " : " elements: ");
            for (size_t i = 0; i < vec.size(); ++i)
            {
                cout << vec[i];
                if (i != vec.size() - 1)
                    cout << " "; //add space between elements
            }
            cout << endl;

            //display index and address for the vector elements
            cout << "\n\tIndex: ";
            for (size_t i = 0; i < vec.size(); ++i)
                cout << i << (i != vec.size() - 1 ? "     " : "");
            cout << "\n\tStarting address: " << &vec[0] << "\n\n";
        }

        //display vector menu options
        cout << "\n\t\tVector (list array) Menu Options" << endl;
        cout << string(90, char(205)) << endl; //double line
        cout << "\t\t1. Add an element" << endl;
        cout << "\t\t2. Insert an element at index" << endl;
        cout << "\t\t3. Retrieve an element from index" << endl;
        cout << "\t\t4. Erase element(s)" << endl;
        cout << "\t\t5. Sort the vector elements in ascending order" << endl;
        cout << "\t\t6. Clear all elements" << endl;
        cout << string(90, char(196)) << endl; //single line
        cout << "\t\t0. Return" << endl;
        cout << string(90, char(205)) << endl; //double line

        //get user menu input
        cout << "\n\t\tOption: ";
        cin >> option;

        try
        {
            switch (option)
            {
            case '1': //add an element
            {
                cout << "\n\tInput a Rational number [numerator/denominator] to be added...\n";

                int numerator = getValidatedInteger("\t\tEnter a value (-99...99) for the numerator  : ", -99, 99);
                int denominator;
                do
                {
                    denominator = getValidatedInteger("\t\tEnter a value (-99...99) for the denominator: ", -99, 99);
                    if (denominator == 0)
                        cout << "\tERROR: Invalid input. Denominator cannot be zero.\n";
                } while (denominator == 0);

                //normalize the Rational number
                int divisor = gcd(numerator, denominator); //use custom gcd function
                numerator /= divisor;
                denominator /= divisor;

                //move negative sign to the numerator if denominator is negative
                if (denominator < 0)
                {
                    numerator *= -1;
                    denominator *= -1;
                }

                Rational r;
                r.setNumerator(numerator);
                r.setDenominator(denominator);
                vec.push_back(r);

                cout << "\n\tThe Rational number " << r << " has been added to the vector.\n";
                break;
            }

            case '2': //insert an element at index
            {
                cout << "\n\tInput a Rational number [numerator/denominator] to be inserted...\n";

                int numerator = getValidatedInteger("\t\tEnter a value (-99...99) for the numerator  : ", -99, 99);
                int denominator;
                do
                {
                    denominator = getValidatedInteger("\t\tEnter a value (-99...99) for the denominator: ", -99, 99);
                    if (denominator == 0)
                        cout << "\tERROR: Invalid input. Denominator cannot be zero.\n";
                } while (denominator == 0);

                //normalize the Rational number
                int divisor = gcd(numerator, denominator); //use custom gcd function
                numerator /= divisor;
                denominator /= divisor;

                //move negative sign to the numerator if denominator is negative
                if (denominator < 0)
                {
                    numerator *= -1;
                    denominator *= -1;
                }

                Rational r;
                r.setNumerator(numerator);
                r.setDenominator(denominator);

                //prompt for index
                int index = getValidatedInteger("\n\t\tInsert the Rational number at index (0..." + to_string(vec.size()) + ") of the vector: ", 0, vec.size());
                vec.insert(vec.begin() + index, r);

                cout << "\n\tThe Rational number " << r << " has been inserted at index " << index << " of the vector.\n";
                break;
            }

            case '3': //retrieve an element from index
            {
                if (vec.empty())
                {
                    cout << "\n\tThe vector is empty. Nothing to retrieve.\n";
                    break;
                }

                int index = getValidatedInteger("\n\tEnter an index of the Rational number from the vector to be retrieved (0..." + to_string(vec.size() - 1) + "): ", 0, vec.size() - 1);
                cout << "\n\t\t" << vec[index] << " is located at index(" << index << ") from the vector.\n";
                cout << "\n\t\tAddress: " << &vec[index] << "\n";
                break;
            }

            case '4': //erase element(s)
            {
                cout << "\n\tInput a Rational number [numerator/denominator] to be removed...\n";

                int numerator = getValidatedInteger("\t\tEnter a value (-99...99) for the numerator  : ", -99, 99);
                int denominator;
                do
                {
                    denominator = getValidatedInteger("\t\tEnter a value (-99...99) for the denominator: ", -99, 99);
                    if (denominator == 0)
                        cout << "\tERROR: Invalid input. Denominator cannot be zero.\n";
                } while (denominator == 0);

                int divisor = gcd(numerator, denominator);
                numerator /= divisor;
                denominator /= divisor;

                Rational target;
                target.setNumerator(numerator);
                target.setDenominator(denominator);

                auto it = find(vec.begin(), vec.end(), target);
                if (it == vec.end())
                {
                    cout << "\n\tThe Rational number " << target << " is not in the vector.\n";
                    break;
                }

                char choice;
                do
                {
                    cout << "\n\tDo you want to remove (O-one or A-all) element(s): ";
                    cin >> choice;
                    choice = toupper(choice);

                    if (choice != 'O' && choice != 'A')
                        cout << "ERROR: Invalid input. Must be a 'O' or 'A' character.\n";
                } while (choice != 'O' && choice != 'A');

                if (choice == 'O')
                {
                    vec.erase(it);
                    cout << "\n\tThe Rational number " << target << " has been removed from the vector.\n";
                }
                else
                {
                    vec.erase(remove(vec.begin(), vec.end(), target), vec.end());
                    cout << "\n\tAll occurrences of the Rational number " << target << " have been removed from the vector.\n";
                }
                break;
            }

            case '5': //sort the vector
            {
                if (vec.empty())
                {
                    cout << "\n\tThe vector is empty. Nothing to sort.\n";
                    break;
                }

                sort(vec.begin(), vec.end());
                cout << "\n\tThe vector of Rational numbers has been sorted in ascending order.\n";
                break;
            }

            case '6': //clear the vector
            {
                vec.clear();
                cout << "\n\tThe vector has been cleared of all Rational elements.\n";
                break;
            }

            case '0': //return to main menu
                return;

            default:
                cout << "\t\tERROR: Invalid option. Please re-enter.\n";
                break;
            }
        }
        catch (const invalid_argument& e)
        {
            cout << "\t\tERROR: " << e.what() << endl;
        }
        catch (...)
        {
            cout << "\t\tAn unexpected error occurred.\n";
        }

        system("pause");
        system("cls");

    } while (true);
}

//helper fucntion for void listContiner 
pair<int, int> inputRational() {
    int numerator, denominator;

    while (true) {
        try {
            cout << "\n\tInput a Rational number [numerator/denominator] to be added...\n";
            cout << "\tEnter a value (-99...99) for the numerator  : ";
            cin >> numerator;
            if (cin.fail()) throw invalid_argument("Invalid input for numerator.");
            if (numerator < -99 || numerator > 99) throw out_of_range("Numerator out of range.");

            cout << "\tEnter a value (-99...99) for the denominator: ";
            cin >> denominator;
            if (cin.fail()) throw invalid_argument("Invalid input for denominator.");
            if (denominator == 0) throw invalid_argument("Denominator cannot be zero.");
            if (denominator < -99 || denominator > 99) throw out_of_range("Denominator out of range.");

            //ensure denominator is positive and adjust numerator sign if needed
            if (denominator < 0) {
                numerator = -numerator;
                denominator = -denominator;
            }

            return make_pair(numerator, denominator);

        }
        catch (const invalid_argument& e) {
            cout << "\n\tError: " << e.what() << " Please enter valid numeric values.\n";
        }
        catch (const out_of_range& e) {
            cout << "\n\tError: " << e.what() << " Please enter values within the range -99 to 99.\n";
        }

        //clear invalid input
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

//Void List Container Function 
void listContainer() {
    //use a list of pairs to represent the rational numbers
    list<pair<int, int>> rationalList;

    //helper function to calculate GCD
    auto gcd = [](int a, int b) {
        while (b != 0) {
            int temp = b;
            b = a % b;
            a = temp;
        }
        return abs(a);
        };

    //helper function to simplify a rational number
    auto simplifyRational = [&](int numerator, int denominator) -> pair<int, int> {
        int gcdValue = gcd(abs(numerator), abs(denominator));
        numerator /= gcdValue;
        denominator /= gcdValue;
        if (denominator < 0) { //ensure denominator is positive
            numerator = -numerator;
            denominator = -denominator;
        }
        return { numerator, denominator };
        };

    char option;

    do {
        system("cls"); //clear the screen

        //description of linked lists
        cout << "\n\tLinked lists are sequence containers that allow non-contiguous memory allocation. As compared to \n";
        cout << "\tvector, the linked list has slow traversal, but once a position has been found, insertion and \n";
        cout << "\tdeletion are quicker.\n\n";

        //display current list status
        if (rationalList.empty()) {
            cout << "\tThe current list is empty.\n\n";
        }
        else {
            cout << "\tThe current linked list contains " << rationalList.size() << " element(s):\n\n\t";
            for (const auto& r : rationalList) {
                cout << r.first << "/" << r.second << " ";
            }
            cout << "\n\n";

            //display header address
            if (!rationalList.empty()) {
                cout << "\theader: " << &(*rationalList.begin()) << "\n";
            }
        }

        //menu options
        cout << "\n\tLinked List Menu Options\n";
        cout << string(90, char(205)) << endl;
        cout << "\t1. Add (push) an element\n";
        cout << "\t2. Insert an element after\n";
        cout << "\t3. Remove element(s)\n";
        cout << "\t4. Sort the elements in ascending order\n";
        cout << "\t5. Clear all elements\n";
        cout << string(90, char(196)) << endl;
        cout << "\t0. Return\n";
        cout << string(90, char(205)) << endl;

        //get user input for menu option
        while (true) {
            try {
                cout << "\n\tOption: ";
                cin >> option;
                if (cin.fail()) throw invalid_argument("Invalid input. Please enter a number between 0 and 5.");
                if (option < '0' || option > '5') throw out_of_range("Option out of range.");
                break;
            }
            catch (const exception& e) {
                cout << "\n\tError: " << e.what() << "\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }

        switch (option) {
        case '1': { //ddd (push) an element
            int numerator, denominator;
            auto rationalInput = inputRational(); //get rational input as a pair
            numerator = rationalInput.first;
            denominator = rationalInput.second;

            auto simplified = simplifyRational(numerator, denominator);

            if (rationalList.empty()) {
                rationalList.push_back(simplified); //add to back if empty
                cout << "\n\t" << simplified.first << "/" << simplified.second << " has been added to the empty list.\n";
            }
            else {
                cout << "\n\tAdd to the (F-front) or (B-back): ";
                char position;
                cin >> position;
                if (tolower(position) == 'f') {
                    rationalList.push_front(simplified);
                    cout << "\t" << simplified.first << "/" << simplified.second << " has been added to the front of the list.\n";
                }
                else {
                    rationalList.push_back(simplified);
                    cout << "\t" << simplified.first << "/" << simplified.second << " has been added to the back of the list.\n";
                }
            }
            break;
        }

        case '2': { //insert an element
            if (rationalList.empty()) {
                cout << "\n\tThe list is empty. Cannot insert elements.\n";
                break;
            }

            int newNumerator, newDenominator, refNumerator, refDenominator;
            auto newInput = inputRational(); //get new rational number as a pair
            newNumerator = newInput.first;
            newDenominator = newInput.second;

            auto refInput = inputRational(); //get reference rational number as a pair
            refNumerator = refInput.first;
            refDenominator = refInput.second;

            auto simplifiedNew = simplifyRational(newNumerator, newDenominator);
            auto simplifiedRef = simplifyRational(refNumerator, refDenominator);

            auto it = rationalList.begin();
            while (it != rationalList.end()) {
                if (*it == simplifiedRef) {
                    cout << "\n\tInsert (B-before) or (A-after): ";
                    char position;
                    cin >> position;

                    if (tolower(position) == 'a') {
                        rationalList.insert(next(it), simplifiedNew);
                        cout << "\t" << simplifiedNew.first << "/" << simplifiedNew.second << " has been inserted after " << refNumerator << "/" << refDenominator << ".\n";
                    }
                    else if (tolower(position) == 'b') {
                        rationalList.insert(it, simplifiedNew);
                        cout << "\t" << simplifiedNew.first << "/" << simplifiedNew.second << " has been inserted before " << refNumerator << "/" << refDenominator << ".\n";
                    }
                    break;
                }
                ++it;
            }

            if (it == rationalList.end()) {
                cout << "\tReference element " << refNumerator << "/" << refDenominator << " not found in the list.\n";
            }
            break;
        }

        case '3': { //remove element(s)
            if (rationalList.empty()) {
                cout << "\n\tThe list is empty. Cannot remove elements.\n";
                break;
            }

            int numerator, denominator;
            auto rationalInput = inputRational(); //get rational number as a pair
            numerator = rationalInput.first;
            denominator = rationalInput.second;

            auto simplified = simplifyRational(numerator, denominator);
            auto it = rationalList.begin();
            bool found = false;

            while (it != rationalList.end()) {
                if (*it == simplified) {
                    it = rationalList.erase(it); //use return value of erase
                    cout << "\t" << simplified.first << "/" << simplified.second << " has been removed from the list.\n";
                    found = true;
                    break;
                }
                else {
                    ++it;
                }
            }

            if (!found) {
                cout << "\t" << simplified.first << "/" << simplified.second << " not found in the list.\n";
            }
            break;
        }

        case '4': { //sort the elements
            rationalList.sort([](const pair<int, int>& a, const pair<int, int>& b) {
                return static_cast<double>(a.first) / a.second < static_cast<double>(b.first) / b.second;
                });
            cout << "\tThe list of Rational numbers has been sorted.\n";
            break;
        }

        case '5': { //clear all elements
            rationalList.clear();
            cout << "\tThe list has been cleared of all Rational elements.\n";
            break;
        }

        case '0': //exit
            cout << "\n\tReturning to main menu.\n";
            break;

        default:
            cout << "\n\tInvalid option. Try again.\n";
        }

        if (option != '0') {
            cout << "\nPress any key to continue . . .";
            cin.ignore().get();
        }
    } while (option != '0');
}


//Void Stack Container function 
void stackContainer() {
    system("cls");

    //use a vector of Rational objects as the stack
    vector<Rational> stack;

    //function to display the stack
    auto displayStack = [&]() {
        if (stack.empty()) {
            cout << "\tThe current stack is empty.\n";
        }
        else {
            cout << "\tThe current stack contains " << stack.size() << " element(s):\n\n\t";
            cout << " top   ";
            for (size_t i = 0; i < stack.size(); ++i) {
                cout << stack[i] << "   ";
            }
            cout << "\n\n";
        }
        };

    char option;

    do {
        system("cls");

        //description of stack
        cout << "\tStacks are type of container adaptors with LIFO (Last In First Out) type of working, where a new\n";
        cout << "\telement is added (pushed) at one end (top) and an element is removed (popped) from that end (top)\n";
        cout << "\tonly. Stack uses an encapsulated object of either vector or deque (by default) or list (sequential\n";
        cout << "\tcontainer class) as its underlying container, providing a specific set of member functions to\n";
        cout << "\taccess its elements.\n\n";

        displayStack();

        //stack menu options
        cout << "\tStack Menu Options\n";
        cout << string(90, char(205)) << endl;
        cout << "\t1. Push\n";
        cout << "\t2. Top\n";
        cout << "\t3. Pop\n";
        cout << string(90, char(196)) << endl;
        cout << "\t0. Return\n";
        cout << string(90, char(205)) << endl;
        cout << "\n\tOption: ";
        cin >> option;

        switch (option) {
        case '1': { //push a Rational number
            try {
                Rational r;
                int numerator, denominator;

                cout << "\n\tInput a Rational number to be pushed...\n";

                //get and validate numerator
                while (true) {
                    cout << "\t\tEnter a value (-99...99) for the numerator  : ";
                    cin >> numerator;

                    if (cin.fail()) {
                        cin.clear(); //clear error flag
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); //ignore invalid input
                        cout << "\t\tERROR: Invalid input. Please enter a numeric value between -99 and 99.\n";
                    }
                    else if (numerator < -99 || numerator > 99) {
                        cout << "\t\tERROR: Out of range. Please enter a value between -99 and 99.\n";
                    }
                    else {
                        break; //valid input
                    }
                }

                //get and validate denominator
                while (true) {
                    cout << "\t\tEnter a value (-99...99) for the denominator: ";
                    cin >> denominator;

                    if (cin.fail()) {
                        cin.clear(); //glear error flag
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); //ignore invalid input
                        cout << "\t\tERROR: Invalid input. Please enter a numeric value between -99 and 99.\n";
                    }
                    else if (denominator == 0) {
                        cout << "\t\tERROR: Denominator cannot be zero.\n";
                    }
                    else if (denominator < -99 || denominator > 99) {
                        cout << "\t\tERROR: Out of range. Please enter a value between -99 and 99.\n";
                    }
                    else {
                        break; //valid input
                    }
                }

                //calculate GCD to simplify the fraction
                int gcd = [](int a, int b) {
                    while (b != 0) {
                        int temp = b;
                        b = a % b;
                        a = temp;
                    }
                    return abs(a);
                    }(numerator, denominator);

                numerator /= gcd;
                denominator /= gcd;

                //ensure the denominator is always positive
                if (denominator < 0) {
                    numerator = -numerator;
                    denominator = -denominator;
                }

                r.setNumerator(numerator);
                r.setDenominator(denominator);

                //insert the Rational number at the left (top of stack)
                stack.insert(stack.begin(), r);

                cout << "\n\t\t" << r << " will be pushed onto the stack.\n";
            }
            catch (const exception& e) {
                cout << "\n\tError: " << e.what() << endl;
            }
            system("pause");
            break;
        }

        case '2': { //view the top Rational number
            if (stack.empty()) {
                cout << "\n\tThe stack is empty. Nothing to view.\n";
            }
            else {
                cout << "\n\t\tThe top Rational number is: " << stack.front() << endl;
            }
            system("pause");
            break;
        }

        case '3': { //pop the top Rational number
            if (stack.empty()) {
                cout << "\n\tThe stack is empty. Nothing to pop.\n";
            }
            else {
                cout << "\n\t\t" << stack.front() << " will be popped from the stack.\n";
                stack.erase(stack.begin());
            }
            system("pause");
            break;
        }

        case '0': //return to the main menu
            return;

        default:
            cout << "\n\tInvalid option. Please try again.\n";
            system("pause");
        }
    } while (true);
}

//helper function to validate, normalize, and simplify Rational input
Rational getValidatedRational() {
    int numerator, denominator;

    while (true) {
        try {
            cout << "\t\tEnter a value (-99...99) for the numerator  : ";
            cin >> numerator;
            if (!cin || numerator < -99 || numerator > 99)
                throw invalid_argument("Invalid numerator.");

            cout << "\t\tEnter a value (-99...99) for the denominator: ";
            cin >> denominator;
            if (!cin || denominator == 0 || denominator < -99 || denominator > 99)
                throw invalid_argument("Invalid denominator.");

            //normalize: Move negative sign to numerator
            if (denominator < 0) {
                numerator = -numerator;
                denominator = -denominator;
            }

            //simplify using GCD
            int divisor = gcd(numerator, denominator);
            numerator /= divisor;
            denominator /= divisor;

            Rational r;
            r.setNumerator(numerator);
            r.setDenominator(denominator);
            return r;

        }
        catch (const exception& e) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\t\tError: " << e.what() << "\n";
        }
    }
}
//helper function to display the current queue recursively
void displayQueue(queue<Rational> q) {
    if (q.empty()) return;
    Rational front = q.front();
    q.pop();
    displayQueue(q);
    cout << "   " << front;
}

//Void Queue Container Function 
void queueContainer() {
    system("cls");
    queue<Rational> q;
    char option;

    do {
        system("cls");

        cout << "\tQueues are a type of container adaptors that operate in a first in first out (FIFO) type of\n";
        cout << "\tarrangement. Elements are inserted/pushed (enqueued) at the rear and are removed/popped (dequeued)\n";
        cout << "\tfrom the front. Queues use an encapsulated object of deque or list (sequential container class)\n";
        cout << "\tas its underlying container, providing a specific set of member functions to access elements.\n\n";

        //display current queue status
        if (q.empty()) {
            cout << "\tThe current queue is empty.\n\n\n\n";
        }
        else {
            cout << "\tThe current queue contains " << q.size() << " element(s):\n\t in(rear)";
            displayQueue(q);
            cout << "   out(front)\n";
        }

        cout << "\n\tQueue Menu Options\n";
        cout << string(90, char(205)) << endl;
        cout << "\t1. Enqueue (push into the rear)\n";
        cout << "\t2. Rear (back)\n";
        cout << "\t3. Front\n";
        cout << "\t4. Dequeue (pop from the front)\n";
        cout << string(90, char(196)) << endl;
        cout << "\t0. Return\n";
        cout << string(90, char(205)) << endl;

        cout << "\n\tOption: ";
        cin >> option;

        switch (option) {
        case '1': { //enqueue
            Rational r = getValidatedRational();
            q.push(r);
            cout << "\n\t\t" << r << " will be enqueued (pushed) onto the queue.\n";
            system("pause");
            break;
        }

        case '2': { //rear (back)
            try {
                if (q.empty()) throw underflow_error("The queue is empty.");
                Rational r = q.back();
                cout << "\n\t\t" << r << " is at the back of the queue.\n";
                system("pause");
            }
            catch (const exception& e) {
                cout << "\n\tError: " << e.what() << "\n";
                system("pause");
            }
            break;
        }

        case '3': { //front
            try {
                if (q.empty()) throw underflow_error("The queue is empty.");
                Rational r = q.front();
                cout << "\n\t\t" << r << " is at the front of the queue.\n";
                system("pause");
            }
            catch (const exception& e) {
                cout << "\n\tError: " << e.what() << "\n";
                system("pause");
            }
            break;
        }

        case '4': { //dequeue (pop)
            try {
                if (q.empty()) throw underflow_error("The queue is empty.");
                Rational r = q.front();
                q.pop();
                cout << "\n\t\t" << r << " will be dequeued (popped) from the queue.\n";
                system("pause");
            }
            catch (const exception& e) {
                cout << "\n\tError: " << e.what() << "\n";
                system("pause");
            }
            break;
        }

        case '0': //rReturn
            return;

        default: {
            cout << "\t\tERROR: Invalid option. Please re-enter.\n";
            system("pause");
        }
        }
    } while (true);
}