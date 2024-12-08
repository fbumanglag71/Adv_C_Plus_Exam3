#include "input.h"      //input file provided by the professor 
#include <vector>       //include vector library
#include "Rational.h"   //include rational header file
#include <iostream>     //include input-output library
#include <stdexcept>    //include exception handling library
#include <algorithm>    //include algorithms like sort
#include <list>         //include list container library
#include <limits>       //include numeric limits library
#include <queue>        //include queue container library
#include <cstdlib>      //include standard library utilities
#include <string>       //include string handling utilities


using namespace std;    //use standard namespace


// Function prototypes
int menuOption();
void vectorContainer();
void listContainer();
void stackContainer();
void queueContainer();



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


//helper function to validate integer input
int getValidatedInteger(const string& prompt, int min, int max)
{
    int value;
    while (true)
    {
        cout << prompt;
        cin >> value;

        if (cin.fail())//check for invalid input (e.g., alpha characters)
        {
            cin.clear();//clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n');//discard invalid input
            cout << "\tError: invalid input. must be an integer type.\n";
        }
        else if (value < min || value > max)//check for range
        {
            cout << "\tError: invalid input. must be from " << min << ".." << max << ".\n";
        }
        else
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');//clear buffer
            return value;//valid input
        }
    }
}

//vector container function
void vectorContainer()
{
    system("cls");//clear the screen

    vector<Rational> vec;//vector to store rational numbers
    char option;//menu option

    do
    {
        //display the current state of the vector
        cout << "\n\tVectors (array) are same as dynamic arrays with the ability to resize itself automatically"
            << "\n\twhen an element is inserted or deleted, that contains their storage being handled automatically"
            << "\n\ty the container. vector elements are placed in contiguous storage so that they can be accessed"
            << "\n\tand traversed using iterators or indexes.\n";

        if (vec.empty())
        {
            cout << "\n\tThe current vector is empty.\n\n\n";
        }
        else
        {
            cout << "\n\tThe current vector contains " << vec.size() << (vec.size() == 1 ? " element: " : " elements: ") << "\n\n\t\t";
            for (const auto& r : vec)
                cout << r << " ";
            cout << endl;

            //display index and address for the vector elements
            cout << "\n\tIndex: ";
            for (size_t i = 0; i < vec.size(); ++i)
                cout << i << (i != vec.size() - 1 ? "     " : "");
            cout << "\n\tStarting address: " << &vec[0] << "\n\n";
        }

        //display vector menu options
        cout << "\n\t\tVector (list array) menu options" << endl;
        cout << string(90, char(205)) << endl;//double line
        cout << "\t\t1. Add an element" << endl;
        cout << "\t\t2. Insert an element at index" << endl;
        cout << "\t\t3. Retrieve an element from index" << endl;
        cout << "\t\t4. Erase element(s)" << endl;
        cout << "\t\t5. Sort the vector elements in ascending order" << endl;
        cout << "\t\t6. Clear all elements" << endl;
        cout << string(90, char(196)) << endl;//single line
        cout << "\t\t0. Return" << endl;
        cout << string(90, char(205)) << endl;//double line

        //get user menu input
        cout << "\n\t\tOption: ";
        cin >> option;

        try
        {
            switch (option)
            {
            case '1'://add an element
            {
                int numerator = getValidatedInteger("\t\tEnter a value (-99...99) for the numerator  : ", -99, 99);
                int denominator = getValidatedInteger("\t\tEnter a value (-99...99) for the denominator: ", -99, 99);

                Rational r(numerator, denominator);
                vec.push_back(r);

                cout << "\n\tThe rational number " << r << " has been added to the vector.\n";
                break;
            }

            case '2'://insert an element at index
            {
                int numerator = getValidatedInteger("\t\tEnter a value (-99...99) for the numerator  : ", -99, 99);
                int denominator = getValidatedInteger("\t\tEnter a value (-99...99) for the denominator: ", -99, 99);
                Rational r(numerator, denominator);

                int index = getValidatedInteger("\n\t\tInsert the rational number at index (0..." + to_string(vec.size()) + ") of the vector: ", 0, vec.size());
                vec.insert(vec.begin() + index, r);

                cout << "\n\tThe rational number " << r << " has been inserted at index " << index << " of the vector.\n";
                break;
            }

            case '3'://retrieve an element from index
            {
                if (vec.empty())
                {
                    cout << "\n\tThe vector is empty. nothing to retrieve.\n";
                    break;
                }

                int index = getValidatedInteger("\n\tEnter an index of the rational number from the vector to be retrieved (0..." + to_string(vec.size() - 1) + "): ", 0, vec.size() - 1);
                cout << "\n\t\t" << vec[index] << " is located at index(" << index << ") from the vector.\n";
                cout << "\n\t\tAddress: " << &vec[index] << "\n";
                break;
            }

            case '4'://erase element(s)
            {
                int numerator = getValidatedInteger("\t\tEnter a value (-99...99) for the numerator  : ", -99, 99);
                int denominator = getValidatedInteger("\t\tEnter a value (-99...99) for the denominator: ", -99, 99);
                Rational target(numerator, denominator);

                auto it = find(vec.begin(), vec.end(), target);
                if (it == vec.end())
                {
                    cout << "\n\tThe rational number " << target << " is not in the vector.\n";
                    break;
                }

                char choice;
                cout << "\n\tDo you want to remove (O-one or A-all) element(s): ";
                cin >> choice;
                choice = toupper(choice);

                if (choice == 'O')
                {
                    vec.erase(it);
                    cout << "\n\tThe rational number " << target << " has been removed from the vector.\n";
                }
                else if (choice == 'A')
                {
                    vec.erase(remove(vec.begin(), vec.end(), target), vec.end());
                    cout << "\n\tAll occurrences of the rational number " << target << " have been removed from the vector.\n";
                }
                break;
            }

            case '5'://sort the vector
            {
                if (vec.empty())
                {
                    cout << "\n\tThe vector is empty. nothing to sort.\n";
                    break;
                }

                sort(vec.begin(), vec.end());
                cout << "\n\tThe vector of rational numbers has been sorted in ascending order.\n";
                break;
            }

            case '6'://clear the vector
            {
                vec.clear();
                cout << "\n\tThe vector has been cleared of all rational elements.\n";
                break;
            }

            case '0'://return to main menu
                return;

            default:
                cout << "\t\tError: invalid option. please re-enter.\n";
                break;
            }
        }
        catch (const invalid_argument& e)
        {
            cout << "\t\tError: " << e.what() << endl;
        }
        catch (...)
        {
            cout << "\t\tAn unexpected error occurred.\n";
        }

        system("pause");
        system("cls");

    } while (true);
}

//Void List Container Function 
void listContainer() {
    //use a list of Rational objects to represent the rational numbers
    list<Rational> rationalList;

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
            cout << "\tThe current linked list contains " << rationalList.size() << " element"
                << (rationalList.size() > 1 ? "s" : "") << ":\n\n\t";

            for (const auto& r : rationalList) {
                cout << r << " "; //display Rational numbers without borders
            }
            cout << "\n\n";

            //display header address
            cout << "\theader: " << &(*rationalList.begin()) << "\n";
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
        case '1': { //add (push) an element
            int numerator = getValidatedInteger("\t\tEnter a value (-99...99) for the numerator  : ", -99, 99);
            int denominator = getValidatedInteger("\t\tEnter a value (-99...99) for the denominator: ", -99, 99);

            Rational r(numerator, denominator); //construct Rational, applies Normalize()

            if (rationalList.empty()) {
                rationalList.push_back(r); //add to back if empty
                cout << "\n\t" << r << " has been added to the empty list.\n";
            }
            else {
                char position;
                while (true) {
                    cout << "\n\tAdd to the (F-front) or from the (B-back): ";
                    cin >> position;
                    position = tolower(position);

                    if (position == 'f') {
                        rationalList.push_back(r); //append to the end
                        cout << "\n\t" << r << " will be added to the end of the list.\n";
                        break;
                    }
                    else if (position == 'b') {
                        rationalList.push_front(r); //prepend to the start
                        cout << "\n\t" << r << " will be added to the start of the list.\n";
                        break;
                    }
                    else {
                        cout << "\tERROR: Invalid input. Please enter 'F' or 'B'.\n";
                    }
                }
            }
            system("pause");
            break;
        }

        case '2': { //insert an element
            if (rationalList.empty()) {
                cout << "\n\tThe list is empty. Cannot insert elements.\n";
                system("pause");
                break;
            }

            int numerator, denominator, refNumerator, refDenominator;

            //new element
            numerator = getValidatedInteger("\t\tEnter a value (-99...99) for the numerator  : ", -99, 99);
            denominator = getValidatedInteger("\t\tEnter a value (-99...99) for the denominator: ", -99, 99);
            Rational newRational(numerator, denominator);

            //reference element
            cout << "\n\t\tInput an existing Rational number as the insert position to be added..." << "\n";
            refNumerator = getValidatedInteger("\t\tEnter a value (-99...99) for the reference numerator  : ", -99, 99);
            refDenominator = getValidatedInteger("\t\tEnter a value (-99...99) for the reference denominator: ", -99, 99);
            Rational refRational(refNumerator, refDenominator);

            auto it = rationalList.begin();
            while (it != rationalList.end()) {
                if (*it == refRational) {
                    cout << "\n\tInsert (B-before) or (A-after): ";
                    char position;
                    cin >> position;

                    if (tolower(position) == 'a') {
                        rationalList.insert(next(it), newRational);
                        cout << "\t" << newRational << " has been inserted after " << refRational << ".\n";
                    }
                    else if (tolower(position) == 'b') {
                        rationalList.insert(it, newRational);
                        cout << "\t" << newRational << " has been inserted before " << refRational << ".\n";
                    }
                    break;
                }
                ++it;
            }

            if (it == rationalList.end()) {
                cout << "\tReference element " << refRational << " not found in the list.\n";
            }
            system("pause");
            break;
        }

        case '3': { //remove element(s)
            if (rationalList.empty()) {
                cout << "\n\tThe list is empty. Cannot remove elements.\n";
                system("pause");
                break;
            }

            int numerator = getValidatedInteger("\t\tEnter a value (-99...99) for the numerator  : ", -99, 99);
            int denominator = getValidatedInteger("\t\tEnter a value (-99...99) for the denominator: ", -99, 99);
            Rational target(numerator, denominator);

            auto it = rationalList.begin();
            while (it != rationalList.end()) {
                if (*it == target) {
                    it = rationalList.erase(it); //use return value of erase
                    cout << "\t" << target << " has been removed from the list.\n";
                }
                else {
                    ++it;
                }
            }
            system("pause");
            break;
        }

        case '4': { //sort the elements
            if (rationalList.empty()) {
                cout << "\n\tThe list is empty.\n";
                system("pause");
                break;
            }
            rationalList.sort(); //use Rational's comparison operator
            cout << "\tThe list of Rational numbers has been sorted.\n";
            system("pause");
            break;
        }

        case '5': { //clear all elements
            rationalList.clear();
            cout << "\tThe list has been cleared of all Rational elements.\n";
            system("pause");
            break;
        }

        case '0': //exit
            cout << "\n\tReturning to main menu.\n";
            //system("pause");
            break;

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
            for (size_t i = stack.size(); i-- > 0;) { //display from top to bottom
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
                int numerator = getValidatedInteger("\t\tEnter a value (-99...99) for the numerator  : ", -99, 99);
                int denominator = getValidatedInteger("\t\tEnter a value (-99...99) for the denominator: ", -99, 99);

                Rational r(numerator, denominator); //construct Rational, applies Normalize()

                stack.push_back(r); //add to the top of the stack

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
                cout << "\n\t\tThe top Rational number is: " << stack.back() << endl;
            }
            system("pause");
            break;
        }

        case '3': { //pop the top Rational number
            if (stack.empty()) {
                cout << "\n\tThe stack is empty. Nothing to pop.\n";
            }
            else {
                cout << "\n\t\t" << stack.back() << " will be popped from the stack.\n";
                stack.pop_back(); //remove the top of the stack
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

//helper function to display the current queue
void displayQueue(const queue<Rational>& q) {
    queue<Rational> tempQueue = q; //create a copy to iterate without modifying the original queue
    while (!tempQueue.empty()) {
        cout << "   " << tempQueue.front();
        tempQueue.pop();
    }
}

//Void Queue Container Function
void queueContainer() {
    system("cls");
    deque<Rational> q; //using deque to allow efficient operations at both ends
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
            cout << "\tThe current queue contains " << q.size() << " element"
                << (q.size() > 1 ? "s" : "") << ":\n\t in(rear) ";
            for (const auto& r : q) {
                cout << r << " ";
            }
            cout << "  out(front)\n";
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
        case '1': { //enqueue (push into the rear)
            try {
                int numerator = getValidatedInteger("\t\tEnter a value (-99...99) for the numerator  : ", -99, 99);
                int denominator = getValidatedInteger("\t\tEnter a value (-99...99) for the denominator: ", -99, 99);

                Rational r(numerator, denominator); //construct Rational, applies Normalize()

                q.push_front(r); //push to the rear (front of deque)
                cout << "\n\t\t" << r << " has been inserted at the rear of the queue.\n";
            }
            catch (const exception& e) {
                cout << "\n\tError: " << e.what() << endl;
            }
            system("pause");
            break;
        }

        case '2': { //rear (back)
            try {
                if (q.empty()) throw underflow_error("The queue is empty.");
                Rational r = q.front(); //retrieve the leftmost element (rear)
                cout << "\n\t\tThe rear (leftmost) Rational number is: " << r << endl;
            }
            catch (const exception& e) {
                cout << "\n\tError: " << e.what() << "\n";
            }
            system("pause");
            break;
        }

        case '3': { //front
            try {
                if (q.empty()) throw underflow_error("The queue is empty.");
                Rational r = q.back(); //retrieve the rightmost element (front)
                cout << "\n\t\tThe front (rightmost) Rational number is: " << r << endl;
            }
            catch (const exception& e) {
                cout << "\n\tError: " << e.what() << "\n";
            }
            system("pause");
            break;
        }

        case '4': { //dequeue (pop from the front)
            try {
                if (q.empty()) throw underflow_error("The queue is empty.");
                Rational r = q.back(); //retrieve and remove the rightmost element
                q.pop_back();
                cout << "\n\t\t" << r << " has been removed from the front of the queue.\n";
            }
            catch (const exception& e) {
                cout << "\n\tError: " << e.what() << "\n";
            }
            system("pause");
            break;
        }

        case '0': //return
            cout << "\n\tReturning to main menu.\n";
            //system("pause");
            return;

        default: {
            cout << "\t\tERROR: Invalid option. Please re-enter.\n";
            system("pause");
        }
        }
    } while (true);
}
