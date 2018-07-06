/*
 * main.cpp
 *
 *  Created on: Jun 27, 2018
 *      Author: 1282716573C
 */

#include <iostream>
#include <string>
#include <fstream>
#include <string>
#include <sstream>
#include <stdio.h>
#include <vector>
#include <limits>
#include <algorithm>

#define MAX_NUM_ROOMS 100

using namespace std;

/*
 * Customer Information
 */
struct customerStructure
{
    int roomNumber;
    string customerName;
    string customerAddress;
    string customerPhone;
    bool checkedIn;
};

/*
 * Room Information
 */
struct hotelStructure
{
    int roomNumber;
    int numberBeds;
    bool isSuite;
    bool smoking;
    bool isOccupided;
};

class hotelManagement
{
public:

    hotelManagement();
    /*
     * displayMainMenu() - this handles the main menu
     */
    int displayMainMenu();

private:

    string hotelFileName;
    string customerFileName;

    ifstream customorFileStream;
    ifstream hotelFileStream;


    //customerStructure tempCustomer;

    /*
     * Container object to store data read in from a file also stores and changes made.
     */
    vector<customerStructure> customerRecord;
    vector<hotelStructure> hotelRecord;

    /*
     * bookRoomMenu() - this handles room booking menu
     */
    void bookRoomMenu();

    /*
     * loadCustomerFile - open the file and call the function to read in the data
     */
    void loadCustomerFile();

    /*
     * loadHotelFile - read in the data of the file and store it
     */
    void loadHotelFile();

    /*
     * readCustomerFile - open the file and call the function to read in the data
     */
    void readCustomerFile();

    /*
     * readHotelFile - read in the data of the file and store it
     */
    void readHotelFile();

    void bookRoomByNum();

    void bookRoomByType();
    /*
     * isValidRoomNumber - will check if the room number is a valid room number
     */
    void isValidRoomNumber(int , int&, bool& );

    /*
     * getUserInputAlpha - will ask the user a question and verify the inputed answer
     */
    void getUserInputAlpha(string , int, bool& );

    bool enterCustomerInfo(int, int);

    void displayCustomerRecordMenu();

    void findCustomInfo();

    void findByName();

    void findByRoomNum();

};

hotelManagement :: hotelManagement()
{
    /*
     *
     */
    customerFileName = "Customer_Records.txt";
    hotelFileName = "Hotel_Records.txt";

    loadCustomerFile();
    loadHotelFile();
    system("pause");
}

int hotelManagement :: displayMainMenu()
{
    /*
     * This method will display the hotel management main menu
     * 1. Book a room
     * 2.
     * 3.
     * 4.
     * 5.
     */
    int selection;
    bool exitProgram = false;

    selection = 0;
    /*
     * Using system("cls") to keep the screen clean.
     */
    system("cls");

    cout << "***********************************************" << endl;
    cout << "*      Hotel Management Main Menu             *" << endl;
    cout << "***********************************************\n" << endl;
    cout << "Select from the following menu" << endl;
    cout << "1. To book a room." << endl;
    cout << "2. Look up customer." << endl;
    cout << "3. " << endl;
    cout << "4. " << endl;
    cout << "5. " << endl;
    cout << "6. Exit program." << endl;
    cout << "Enter selection here : ";

    while (!(cin >> selection))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize> :: max(), '\n');
        cout << "You did not enter a correct menu item ." << endl;
        cout <<"Please enter a menu selection : ";
    }

    while (!exitProgram)
    {
        switch (selection)
        {
            case 1:
                cout << endl;
                cout << "Book a room has been selected." << endl;
                bookRoomMenu();
                    break;
            case 2:
                cout << endl;
                cout << "Look up a customer has been selected." << endl;
                findCustomInfo();
                    break;
            case 3: //displayRoomStatus();
                    break;
            case 4: //editCustomorRecord();
                    break;

            case 5:
            case 6:
                exitProgram = true;
                cout << "Exit program: " << selection<< endl;
                break;
            default:
                system("pause");
                cout << "Invalid Selection" << endl;
                while (!(cin >> selection))
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize> :: max(), '\n');
                    cout << "You did not enter a correct menu item ." << endl;
                    cout <<"Please enter a menu selection : ";
                }

        }
    }

    if(exitProgram)
    {
        cout << "Should call something to update the data files" << endl;
    }
    else
    {
        cout << "Calling SELF again!" << endl;
        system("pause");
        displayMainMenu();
    }
    return 0;
}

void hotelManagement :: loadHotelFile()
{
    /*
     * Record file for hotel records
     * Holds room attributes (Room Number, Number of beds, Suite, Smoking, Occupied)
     */

    /*
     * Read in Hotel File
     */
    hotelFileStream.open(hotelFileName);

    if (hotelFileStream.fail())
    {
        cout << "\nThere was a problem opening the file.";
    }
    else
    {
        while (!hotelFileStream.eof())
        {
            readHotelFile();
        }
        cout << "\nFINISHED READING HOTEL FILE" << endl;
    }
}

void hotelManagement :: loadCustomerFile()
{
    customorFileStream.open(customerFileName);

    if (customorFileStream.fail())
    {
        cout << "\nThere was a problem opening the file.";
    }
    else
    {
        while (!customorFileStream.eof())
        {
            readCustomerFile();
        }
        cout << "\nFINISHED READING CUSTOMER FILE\n" << endl;

    }
}

void hotelManagement :: readHotelFile()
{
    string tempLine;
    hotelStructure tempHotel;

    /*
     * Get Room Number
     */
    getline(hotelFileStream, tempLine, ',');
    tempHotel.roomNumber = stoi(tempLine);

    /*
     * Get Number of Beds
     */
    getline(hotelFileStream, tempLine, ',');
    tempHotel.numberBeds = stoi(tempLine);

    /*
     * Get is it a Suite
     */
    getline(hotelFileStream, tempLine, ',');
    tempHotel.isSuite = bool(stoi(tempLine));

    /*
     * get is smoking allowed
     */
    getline(hotelFileStream, tempLine, ',');
    tempHotel.smoking = bool(stoi(tempLine));

    /*
     * Get is room occupied
     */
    getline(hotelFileStream, tempLine, '\n');
    tempHotel.isOccupided = bool(stoi(tempLine));

    hotelRecord.push_back(tempHotel);
}

void hotelManagement :: readCustomerFile ()
{
    /*
     * Read in the customer file and store it in a vector
     */
    customerStructure tempCustomer;
    string tempLine;

    getline(customorFileStream, tempLine, ',');
    tempCustomer.roomNumber = stoi(tempLine);

    getline(customorFileStream, tempCustomer.customerName, ',');

    getline(customorFileStream, tempCustomer.customerAddress, ',');

    getline(customorFileStream, tempCustomer.customerPhone, ',');

    getline(customorFileStream, tempLine, '\n');
    tempCustomer.checkedIn = bool(stoi(tempLine));

    /*
     * Add the read in structure into the vector
     */
    customerRecord.push_back(tempCustomer);

}

void hotelManagement :: bookRoomByNum()
{
    /*
     * Book a room by number
     */
    int tempRoomNum = 0, vectorIndex = 0;
    bool validBooking = false, validRoomNumber = false;

    system("cls");

    cout << "***********************************************" << endl;
    cout << "*      Booking a room by room number          *" << endl;
    cout << "***********************************************\n" << endl;
    while (!validBooking)
        {
            cout << "Enter the room number : ";
            /*
             * Check to see if the user input is correct
             */
            while(!validRoomNumber)
            {
                /*
                 * Check to see that a number has been entered
                 */
                while (!(cin >> tempRoomNum))
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize> :: max(), '\n');
                    cout << "You did not enter a correct room number ." << endl;
                    cout <<"Please enter a room number : ";
                }
                cout << endl;
                /*
                 * Check to see if this is a valid room number and set the hotelRecord index
                 */

                isValidRoomNumber(tempRoomNum, vectorIndex, validRoomNumber);

                if(!validRoomNumber)
                {
                    cout << "You have entered an invalid room number." << endl;
                    cout << "Please enter a room number : ";
                }
                cout << endl;
            }

                if (!hotelRecord[vectorIndex].isOccupided)
                {
                    cout << "This room is available" << endl;
                    validBooking = enterCustomerInfo(tempRoomNum, vectorIndex);
                }
                else
                {
                    cout << "This room Occupied." << endl;
                    validRoomNumber = false;
                }
        }


        if (validBooking)
        {
            system("cls");
            cout << "The room has successfully be book for :" << endl;

            vectorIndex = customerRecord.size() - 1;

            cout << "************************************************" << endl;
            cout << "Name    : " << customerRecord[vectorIndex].customerName << endl;
            cout << "Address : " << customerRecord[vectorIndex].customerAddress << endl;
            cout << "Phone   : " << customerRecord[vectorIndex].customerPhone << endl;
            cout << "Room    : " << customerRecord[vectorIndex].roomNumber << endl;
            cout << "************************************************" << endl;
            system("pause");
            displayMainMenu();

        }
}

void hotelManagement :: bookRoomByType()
{
/*
 * Book a room by type
 * enter room requirements
 * search through available rooms and return and room number
 * call enterCustomerInfo
 */
    int numberBeds = 0, floorNum = 0, strSelectionIndex = 0, foundRoomInd = 0, floorCnt = 0, indMax = 0;
    bool isSuite = false, isSmoking = false, isFloorPref = false, isValidNum = false, bookRoom = false, foundRoom = false;
    string strQuestion;

    system("cls");

    cout << "***********************************************" << endl;
    cout << "*      Search for a room to book              *" << endl;
    cout << "***********************************************\n" << endl;


    while (!isValidNum)
    {
        cout << "How many beds? (1 or 2) : ";
        while (!(cin >> numberBeds))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize> :: max(), '\n');
            cout << "You did not enter a number for number of beds." << endl;
        }
        if (numberBeds == 1 || numberBeds == 2 )
        {
            isValidNum = true;
        }
        else
        {
            cout << "You did not enter a correct number of beds." << endl;
        }
    }

    cout << endl;

    /*
     * Verify user input for suite question is what is expected
     */
    strQuestion = "A suite or regular room (S for Suite or R for Regular) : ";
    strSelectionIndex = 0;

    getUserInputAlpha(strQuestion, strSelectionIndex, isSuite);

    /*
     * Verify user input for suite question is what is expected
     */
    strQuestion = "A Smoking room? Only available on the second floor. (Y or N) : ";
    strSelectionIndex = 4;

    getUserInputAlpha(strQuestion, strSelectionIndex, isSmoking);

    isValidNum = false;
/*
 * If a non smoking room is asked for then see if there is a floor preference
 */
    if(!isSmoking)
    {
        /*
         * Verify user input for suite question is what is expected
         */
        strQuestion = "Is there a floor preference? (Y or N) : ";
        strSelectionIndex = 4;

        getUserInputAlpha(strQuestion, strSelectionIndex, isFloorPref);

        /*
         * While inputed floor number is not valid and there is a floor pref
         * get user input
         */
        while (!isValidNum && isFloorPref)
        {
            cout << "Which floor would you like? (1 thru 10) : ";
            while (!(cin >> floorNum))
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize> :: max(), '\n');
                cout << "You did not enter a correct floor number." << endl;
            }
            if (floorNum >= 1 && floorNum <= 10 )
            {
                isValidNum = true;
            }
            else
            {
                cout << "You did not enter a correct floor number " << floorNum << endl;
            }
        }
        cout << endl;
    }
    /*
     * Else a smoking room is asked for then set floor number to 2
     * which is where the smoking rooms are located
     */
    else
    {
        floorNum = 2;
    }

    cout <<"To verify you would like a room:" << endl;
    cout << "That is on the " << floorNum << " floor" << endl;


//    system("pause");
    /*
     * If there is a floor preference, then set the index to start on that floor
     * Also set end condition to the end of that section
     */


    switch(floorNum)
    {
    /*
     * Switch on Floor number and set the index start and index max
     */

    case 1:
        floorCnt = 0;
        indMax = 10;
        break;

    case 2:
        floorCnt = 10;
        indMax = 20;
        break;

    case 3:
        floorCnt = 20;
        indMax = 30;
        break;

    case 4:
        floorCnt = 30;
        indMax = 40;
        break;

    case 5:
        floorCnt = 40;
        indMax = 50;
        break;

    case 6:
        floorCnt = 50;
        indMax = 60;
        break;

    case 7:
        floorCnt = 60;
        indMax = 70;
        break;

    case 8:
        floorCnt = 70;
        indMax = 80;
        break;

    case 9:
        floorCnt = 80;
        indMax = 90;
        break;

    case 10:
        floorCnt = 90;
        indMax = 100;
        break;

    default:
        floorCnt = 0;
        indMax = int(hotelRecord.size());
        break;

    }

    /*
     * Find the room
     */
    for (int i = floorCnt; i < indMax; i++)
    {
        /*
         * Check for Suite type, smoking type, number of beds and unoccupied rooms
         */
        if((hotelRecord[i].isSuite == isSuite) && (hotelRecord[i].smoking == isSmoking) && (hotelRecord[i].numberBeds == numberBeds) && !hotelRecord[i].isOccupided)
        {
            foundRoom = true;
            foundRoomInd = i;
            break;
        }
    }

    /*
     * Book the room
     */
    if(foundRoom)
    {
        cout << "Room " << hotelRecord[foundRoomInd].roomNumber << " is available." << endl;
        /*
         * Verify user input for suite question is what is expected
         */
        strQuestion = "Would you like to check in? (Y or N) : ";
        strSelectionIndex = 4;

        getUserInputAlpha(strQuestion, strSelectionIndex, bookRoom);

        /*
         * If answered Y then enter customer information to book the room
         */
        if (bookRoom)
        {
            enterCustomerInfo(hotelRecord[foundRoomInd].roomNumber, foundRoomInd);
        }
        /*
         * Else answered N then call bookRoomByType() again.
         */
        else
        {
            bookRoomByType();
        }
    }
    else
    {
        cout << "Nothing found ..." << endl;
        cout << "Try different parameters." << endl;
        system("pause");
        bookRoomByType();
    }

    displayMainMenu();
}

void hotelManagement :: bookRoomMenu()
{
    /*
     * Display the Book a room menu
     * Go to selection the user selects
     */
    int selection = 0;

    system("cls");

    cout << "***********************************************" << endl;
    cout << "*      Booking a room                         *" << endl;
    cout << "***********************************************\n" << endl;
    cout << "1. Book a room by room number." << endl;
    cout << "2. Look for available rooms (suites, smoking, and number of beds)." << endl;
    cout << "3. Go back to Main Menu" << endl;
    cout << "Enter selection here : ";


     while (!(cin >> selection))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize> :: max(), '\n');
            cout << "You did not enter a correct menu item ." << endl;
            cout <<"Please enter a menu selection : ";
        }

     cout << endl;

        while (selection)
        {
            switch (selection)
            {
                case 1:
                    cout << "Booking a room by room number." << endl;
                    bookRoomByNum();
                    break;
                case 2:
                    cout << "Book a room by type has been selected." << endl;
                    bookRoomByType();
                    break;
                case 3:
                    displayMainMenu();
                    break;
                case 4: //editCustomorRecord();
                        break;

                case 5:
                case 6: break;
                default:
                    cout << "Invalid Selection" << endl;
                    system("pause");
                    displayMainMenu();
            }
        }
}

void hotelManagement :: isValidRoomNumber(int tempRoomNum, int& vectorIndex, bool& validRoomNumber)
{
    /*
     * This method will check to see if the room number is valid and set the index for the room vector.
     */

    /*
     * If between room 101 and 110
     */
    if((tempRoomNum >= 101) && tempRoomNum <=110)
    {
        vectorIndex = tempRoomNum - 101;
        validRoomNumber = true;
    }
    /*
     * if between room 201 and 210
     */
    else if((tempRoomNum >= 201) && (tempRoomNum <= 210))
    {
        vectorIndex = tempRoomNum - 191;
        validRoomNumber = true;
    }
    /*
     * if between 301 to 310
     */
    else if((tempRoomNum >= 301) && (tempRoomNum <= 310))
    {
        vectorIndex = tempRoomNum - 281;
        validRoomNumber = true;
    }
    /*
     * if between 401 to 410
     */
    else if((tempRoomNum >= 401) && (tempRoomNum <= 410))
    {
        vectorIndex = tempRoomNum - 371;
        validRoomNumber = true;
    }
    /*
     * if between 501 to 510
     */
    else if((tempRoomNum >= 501) && (tempRoomNum <= 510))
    {
        vectorIndex = tempRoomNum - 461;
        validRoomNumber = true;
    }
    /*
     * if between 601 to 610
     */
    else if((tempRoomNum >= 601) && (tempRoomNum <= 610))
    {
        vectorIndex = tempRoomNum - 551;
        validRoomNumber = true;
    }
    /*
     * if between 701 to 710
     */
    else if((tempRoomNum >= 701) && (tempRoomNum <= 710))
    {
        vectorIndex = tempRoomNum - 641;
        validRoomNumber = true;
    }
    /*
     * if between 801 to 810
     */
    else if((tempRoomNum >= 801) && (tempRoomNum <= 810))
    {
        vectorIndex = tempRoomNum - 731;
        validRoomNumber = true;
    }
    /*
     * if between 901 to 910
     */
    else if((tempRoomNum >= 901) && (tempRoomNum <= 910))
    {
        vectorIndex = tempRoomNum - 821;
        validRoomNumber = true;
    }
    /*
     * if between 1001 to 1010
     */
    else if((tempRoomNum >= 1001) && (tempRoomNum <= 1010))
    {
        vectorIndex = tempRoomNum - 911;
        validRoomNumber = true;
    }
}

void hotelManagement :: getUserInputAlpha(string strQuestion, int strSelectionIndex, bool& setAnswer)
{
    /*
     * This will validate user input for char
     * Valid user input
     * Pass in question to ask and the start index for char selection array
     */
    char userInput;
    bool isAlpha = false;
    char strSelection[] = "SsRrYyNn";

    /*
     * While the user input is not a letter or the correct letter wanted continue asking the user for selection
     */
    while (!isAlpha)
    {
        /*
         * Out put the question
         */
        cout << strQuestion;
        /*
         * Get the user selection
         */
        cin >> userInput;
        cout << endl;

        /*
         * Check to see if the inputed selection is a letter
         */
        isAlpha = isalpha(userInput);

        /*
         * If the selection was not a letter state that and the loop will continue
         */
        if(!isAlpha)
        {
            cout << "You didn't enter a correct selection." << endl;
        }
        /*
         * If the selection is a letter then see if it's an expected answer
         */
        else
        {
            if ((userInput == strSelection[strSelectionIndex]) || (userInput == strSelection[strSelectionIndex+1]))
            {
                setAnswer = true;
            }
            else if ((userInput == strSelection[strSelectionIndex+2]) || (userInput == strSelection[strSelectionIndex+3]))
            {
                setAnswer = false;
            }
            else
            {
                /*
                 * The user selection wasn't part of the expected answers
                 * Set isAlpha to false and ask again
                 */
                cout << "You didn't enter a correct selection. You entered "<< userInput << endl;
                isAlpha = false;
            }
        }
    }
}

bool hotelManagement :: enterCustomerInfo(int tempHotelRoom, int hotelIndex)
{
    /*
     * Check in the customer
     * Update the customer record
     * update the hotel record
     */
    customerStructure tempCustomer;
    string tempString, tempStreet, tempCity, tempZip, strQuestion;
    int endV, strSelectionIndex;
    bool confirmCustInfo = false;

    cout << "*******************************************" << endl;
    cout << "*      Enter Customer Information         *" << endl;
    cout << "*******************************************" << endl;
    cout << endl;

    /*
     * Was having a problem with getting using input
     * After researching I found the cin.ignore
     */
    cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');

    cout << "Enter Customer Name First Name : ";
    cin >> tempString;
    tempCustomer.customerName.append(tempString);

    cout << endl;

    tempString = " ";
    tempCustomer.customerName.append(tempString);

    cout << "Enter Customer Last Name : ";
    cin >> tempString;
    tempCustomer.customerName.append(tempString);

    cout << endl;

    cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');
    cout << "Enter Customer Street Address : ";
    getline(cin, tempStreet);

    cout << endl;

    cout << "Enter Customer City : ";
    getline(cin, tempCity);

    cout << endl;

    cout << "Enter Customer Zip : ";
    getline(cin, tempZip);

    cout << endl;

    tempCustomer.customerAddress += tempStreet + " " + tempCity + " " + tempZip;

    cout << "Enter Customer Phone Number : ";
    getline(cin, tempCustomer.customerPhone);
    tempCustomer.roomNumber = tempHotelRoom;

    cout << endl;

    cout << "Hotel Index = " << hotelIndex << " Record size = " << customerRecord.size();
    tempCustomer.checkedIn = true;



    customerRecord.push_back(tempCustomer);
    cout << "Inserted customer into " << (endV = (customerRecord.size() - 1)) << endl;
    system("pause");

    /*
     * Verify that the information entered is correct
     * If it is not correct then delete the inserted vector and
     * and call enterCustomerInfo() again
     */
    cout << "************************************************" << endl;
    cout << "Verify Customer Information" << endl;
    cout << "Name    : " << customerRecord[endV].customerName << endl;
    cout << "Address : " << customerRecord[endV].customerAddress << endl;
    cout << "Phone   : " << customerRecord[endV].customerPhone << endl;
    cout << "Room    : " << customerRecord[endV].roomNumber << endl;
    cout << "************************************************" << endl;

    /*
     * Verify user input for suite question is what is expected
     */
    strQuestion = "Is the Customer Information Correct? (Y/N) : ";
    strSelectionIndex = 4;

    getUserInputAlpha(strQuestion, strSelectionIndex, confirmCustInfo);

    /*
     * If the user inputed the wrong information then allow them to reenter it.
     */
    if (!confirmCustInfo)
    {
        customerRecord.erase(customerRecord.begin() + endV);
        enterCustomerInfo(tempHotelRoom, hotelIndex);
    }
    /*
     * Set the room to occupied
     */
    hotelRecord[hotelIndex].isOccupided = tempCustomer.checkedIn;
    cout << "Room :" << hotelRecord[hotelIndex].roomNumber << " is now occupied" << endl;
    system("pause");

    return true;

}

void hotelManagement :: displayCustomerRecordMenu()
{
    system("cls");

    cout << "***********************************************" << endl;
    cout << "*      Display Customer Record                *" << endl;
    cout << "***********************************************\n" << endl;
    cout << "1. Enter a room number." << endl;
    cout << "2. Look for available rooms (suites, smoking, and number of beds)." << endl;
    cout << "3. Go back to Main Menu" << endl;
}

void hotelManagement :: findCustomInfo()
{
    /*
     * Search through the customerRecord and display customer information
     */
    int selection = 0;

    system("cls");

    cout << "***********************************************" << endl;
    cout << "*      Find Customer Information              *" << endl;
    cout << "***********************************************\n" << endl;
    cout << "Select from the following menu" << endl;
    cout << "1. Search by Customer by name." << endl;
    cout << "2. Search by room number." << endl;
    cout << "3. Return to Main Menu." << endl;
    cout << "Enter selection here : ";

        while (!(cin >> selection))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize> :: max(), '\n');
            cout << "You did not enter a correct menu item ." << endl;
            cout <<"Please enter a menu selection : ";
        }

    while (selection)
    {
        switch (selection)
        {
            case 1:
                cout << endl;
                cout << "Search by name has been selected." << endl;
                system("pause");
                findByName();
                break;
            case 2:
                cout << endl;
                cout << "Search by room number." << endl;
                findByRoomNum();
                break;
            case 3:
                cout << endl;
                cout << "Return to Main Menu." << endl;
                displayMainMenu();
                break;
            default:
                cout << "Invalid Selection" << endl;
                system("pause");
                findCustomInfo();
        }
    }
}

void hotelManagement :: findByName()
{
    /*
     * Get a partial or full name to search for
     * Display anyone found with partial or full name
     */
    string tempString, tempString1;
    bool customerFound = false;
    vector <int> indexLoc;
    vector <customerStructure> tempCustomerStore;
    /*
     * Find customer information by searching for a name
     */
    cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');
    cout << "Enter the name you want to search for : ";
    getline(cin, tempString);

    cout << "Searching for : " << tempString;

    cout << endl;
    /*
     * For the size of records found
     * print the name and room numbers
     *
     */
    for (int i = 0; i < int(customerRecord.size()); i++)
    {
        if(customerRecord[i].customerName.find(tempString) != string::npos)
        {
            indexLoc.push_back(i);
            customerFound = true;
        }
    }
    if(customerFound)
    {
        /*
         * Print out the customers found
         */
        for(int j = 0; j < int(indexLoc.size()); j++)
        {
            cout << "Customer Information" << endl;
            cout << "Customer Name : "<< customerRecord[indexLoc[j]].customerName << endl;
            cout << "Room Number   : " << customerRecord[indexLoc[j]].roomNumber << endl;
            if(customerRecord[indexLoc[j]].checkedIn)
            {
                cout << "Has checked in" << endl;
            }
            else
            {
                cout << "Is not checked in" << endl;
            }
            cout << endl;
        }
    }
    else
    {
        cout << "Customer not found" << endl;
    }

    system("pause");
    findCustomInfo();

}

void hotelManagement :: findByRoomNum()
{
    cout << "Nothing to see here yet!" << endl;

}
int main()
{
    hotelManagement ourHotel;

    //ourHotel.hotelManagement();
    ourHotel.displayMainMenu();

    return 0;

}
