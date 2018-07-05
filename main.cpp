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

#define MAX_NUM_ROOMS 100
#define TRUE 1
#define FALSE 0

using namespace std;

class hotelManagement
{
public:

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

    string hotelRecordFile;
    string customerRecordFile;

    ifstream customorFile;
    ifstream hotelFile;


    //customerStructure tempCustomer;

    vector<customerStructure> customerRecord;
    vector<hotelStructure> hotelRecord;

    hotelManagement();

    int displayMainMenu();

    void loadCustomerFile();

    void loadHotelFile();

    void readCustomerFile();

    void readHotelFile();

    void bookRoomMenu();

    void bookRoom();

    void bookRoomByType();

    void isValidRoomNumber(int , int&, bool& );

    bool enterCustomerInfo(int, int);

    void displayCustomerRecordMenu();


private:

    /*
     * Book a room
     */
    //void bookRoom();
    /*
     * Display customer records
     */
    //void displayCustomerRecords();


    /*
     * Display room status
     */
    //void displayRoomStatus();
    /*
     * Edit customer record
     */
    //void editCustomorRecord();
    /*
     * Get a rooms status
     */
    //int roomStatus(int);
    /*
     * Modify customer record
     */
    //void modifyCustomerRecord(int);
    /*
     * Delete customer record
     */
    //void deleteCustomerRecord(int);

};

hotelManagement :: hotelManagement()
{

    /*
     * Record file for current customers
     * Holds customer attributes (Room number, Customer name, Customer address, Customer phone number, check in time, check out time)
     */
    loadCustomerFile();
    loadHotelFile();
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
    cout << "6. Return to Main Menu." << endl;
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
                cout << "Book a room has been selected." << endl;
                bookRoomMenu();
                    break;
            case 2:
                cout << endl;
                cout << "Book a room by type has been selected." << endl;
                bookRoomByType();
                    break;
            case 3: //displayRoomStatus();
                    break;
            case 4: //editCustomorRecord();
                    break;

            case 5:
            case 6:
                cout << "Return to Main Menu has been selected." << endl;
                displayMainMenu();
                break;
            default:
                cout << "Invalid Selection" << endl;
                system("pause");
                displayMainMenu();

        }
    }
    return 0;
}

void hotelManagement :: loadHotelFile()
{
    /*
     * Record file for hotel records
     * Holds room attributes (Room Number, Number of beds, Suite, Smoking, Occupied)
     */
    hotelRecordFile = "Hotel_Records.txt";
    /*
     * Read in Hotel File
     */
    hotelFile.open(hotelRecordFile);

    if (hotelFile.fail())
    {
        cout << "\nThere was a problem opening the file.";
    }
    else
    {
        while (!hotelFile.eof())
        {
            readHotelFile();
        }
        cout << "\nFINISHED READING HOTEL FILE";
    }
}

void hotelManagement :: loadCustomerFile()
{
    customerRecordFile = "Customer_Records.txt";

    customorFile.open("Customer_Records.txt");

    if (customorFile.fail())
    {
        cout << "\nThere was a problem opening the file.";
    }
    else
    {
        while (!customorFile.eof())
        {
            readCustomerFile();
        }
        cout << "\nFINISHED READING CUSTOMER FILE\n";

    }
}

void hotelManagement :: readHotelFile()
{
    string tempLine;
    hotelStructure tempHotel;

    /*
     * Get Room Number
     */
    getline(hotelFile, tempLine, ',');
    tempHotel.roomNumber = stoi(tempLine);

    /*
     * Get Number of Beds
     */
    getline(hotelFile, tempLine, ',');
    tempHotel.numberBeds = stoi(tempLine);

    /*
     * Get is it a Suite
     */
    getline(hotelFile, tempLine, ',');
    tempHotel.isSuite = bool(stoi(tempLine));

    /*
     * get is smoking allowed
     */
    getline(hotelFile, tempLine, ',');
    tempHotel.smoking = bool(stoi(tempLine));

    /*
     * Get is room occupied
     */
    getline(hotelFile, tempLine, '\n');
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

    getline(customorFile, tempLine, ',');
    tempCustomer.roomNumber = stoi(tempLine);
    cout << "\nRoom number is : " << tempCustomer.roomNumber;

    getline(customorFile, tempCustomer.customerName, ',');

    getline(customorFile, tempCustomer.customerAddress, ',');

    getline(customorFile, tempCustomer.customerPhone, ',');

    getline(customorFile, tempLine, '\n');
    tempCustomer.checkedIn = bool(stoi(tempLine));

    customerRecord.push_back(tempCustomer);

}

void hotelManagement :: bookRoom()
{
    int tempRoomNum = 0, vectorIndex = 0;
    bool validBooking = FALSE, validRoomNumber = FALSE;

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
                    validRoomNumber = FALSE;
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
    int numberBeds = 0, floorNum = 0;
    char roomType = ' ', smokingRoom = ' ', floorPref = ' ', bookRoom = ' ';
    bool isSuite = 0, isSmoking = 0, isItOK = 0;

    system("cls");

    cout << "***********************************************" << endl;
    cout << "*      Search for a room to book              *" << endl;
    cout << "***********************************************\n" << endl;

    cout << "How many beds? (1 or 2) : ";
    cin >> numberBeds;
    cout << endl;

    cout << "A suite or regular room (S for Suite or R for Regular) : ";
    cin >> roomType;
    cout << endl;

    cout << "A Smoking room? Only available on the second floor. (Y or N) : ";
    cin >> smokingRoom;
    cout << endl;

    if(smokingRoom == 'Y' || smokingRoom == 'y')
    {
        cout << "That allows smoking." << endl;
        isSmoking = TRUE;
    }
    else if(smokingRoom == 'N' || smokingRoom == 'n')
    {
        cout << "That is non-smoking." << endl;
        isSmoking = FALSE;
    }

    while(!isItOK)
    {
        if(!isSmoking)
        {
            cout << "Is there a floor preference? (Y or N) : ";
            cin >> floorPref;
            cout << endl;
            if ((floorPref == 'Y') || (floorPref == 'y'))
                isItOK = TRUE;
        }
        else
        {
            cout << "Smoking rooms are only available on the second floor. " << endl;
            cout << "Would you still like a smoking room? (Y or N) ";
            cin >> smokingRoom;
            cout << endl;
            if(smokingRoom == 'Y' || smokingRoom == 'y')
            {
                cout << "We will continue with a smoking room on the second floor." << endl;
                isSmoking = TRUE;
                isItOK = TRUE;
                floorNum = 2;
            }
            else if(smokingRoom == 'N' || smokingRoom == 'n')
            {
                cout << "That is non-smoking." << endl;
                isSmoking = FALSE;
                isItOK = TRUE;
            }


        }
    }



    if((floorPref == 'Y' || floorPref =='y') && !isSmoking)
    {
        cout << "Which floor would you like? (1 thru 9) : ";
        cin >> floorNum;
        cout << endl;
    }

    cout <<"To verify you would like a room:" << endl;
    cout << "That is on the " << floorNum << " floor" << endl;

    if(roomType == 'S' || roomType == 's')
    {
        cout << "That the is a suite." << endl;
        isSuite = TRUE;
    }
    else if(roomType == 'R' || roomType == 'r')
    {
        cout << "That is not a suite." << endl;
        isSuite = FALSE;
    }

    system("pause");
    /*
     * If there is a floor preference, then set the index to start on that floor
     * Also set end condition to the end of that section
     */
    int floorCnt = 0, indMax = 0, foundRoom = 0;

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
            foundRoom = i;
            break;
        }
    }

    /*
     * Book the room
     */
    if(foundRoom)
    {
        cout << "Room " << hotelRecord[foundRoom].roomNumber << " is available." << endl;
        cout << "Would you like to check in? (Y or N) : ";
        cin >> bookRoom;
        if ((bookRoom == 'Y') || (bookRoom == 'y'))
        {
            enterCustomerInfo(hotelRecord[foundRoom].roomNumber, foundRoom);
        }
    }
    else
    {
        cout << "Nothing found." << endl;
        system("pause");
        bookRoomByType();
    }
    system("pause");
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
                    bookRoom();
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
        validRoomNumber = TRUE;
    }
    /*
     * if between room 201 and 210
     */
    else if((tempRoomNum >= 201) && (tempRoomNum <= 210))
    {
        vectorIndex = tempRoomNum - 191;
        validRoomNumber = TRUE;
    }
    /*
     * if between 301 to 310
     */
    else if((tempRoomNum >= 301) && (tempRoomNum <= 310))
    {
        vectorIndex = tempRoomNum - 281;
        validRoomNumber = TRUE;
    }
    /*
     * if between 401 to 410
     */
    else if((tempRoomNum >= 401) && (tempRoomNum <= 410))
    {
        vectorIndex = tempRoomNum - 371;
        validRoomNumber = TRUE;
    }
    /*
     * if between 501 to 510
     */
    else if((tempRoomNum >= 501) && (tempRoomNum <= 510))
    {
        vectorIndex = tempRoomNum - 461;
        validRoomNumber = TRUE;
    }
    /*
     * if between 601 to 610
     */
    else if((tempRoomNum >= 601) && (tempRoomNum <= 610))
    {
        vectorIndex = tempRoomNum - 551;
        validRoomNumber = TRUE;
    }
    /*
     * if between 701 to 710
     */
    else if((tempRoomNum >= 701) && (tempRoomNum <= 710))
    {
        vectorIndex = tempRoomNum - 641;
        validRoomNumber = TRUE;
    }
    /*
     * if between 801 to 810
     */
    else if((tempRoomNum >= 801) && (tempRoomNum <= 810))
    {
        vectorIndex = tempRoomNum - 731;
        validRoomNumber = TRUE;
    }
    /*
     * if between 901 to 910
     */
    else if((tempRoomNum >= 901) && (tempRoomNum <= 910))
    {
        vectorIndex = tempRoomNum - 821;
        validRoomNumber = TRUE;
    }
    /*
     * if between 1001 to 1010
     */
    else if((tempRoomNum >= 1001) && (tempRoomNum <= 1010))
    {
        vectorIndex = tempRoomNum - 911;
        validRoomNumber = TRUE;
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
    string tempString, tempStreet, tempCity, tempZip;
    int endV;
    char customerInfoCorrect = ' ';



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

    tempCustomer.checkedIn = TRUE;

    customerRecord[hotelIndex].checkedIn = tempCustomer.checkedIn;

    customerRecord.push_back(tempCustomer);
    endV = customerRecord.size() - 1;

    cout << "************************************************" << endl;
    cout << "Customer Information" << endl;
    cout << "Name    : " << customerRecord[endV].customerName << endl;
    cout << "Address : " << customerRecord[endV].customerAddress << endl;
    cout << "Phone   : " << customerRecord[endV].customerPhone << endl;
    cout << "Room    : " << customerRecord[endV].roomNumber << endl;
    cout << "************************************************" << endl;

    cout << "\nIs the Customer Information Correct? (Y/N) : ";
    cin >> customerInfoCorrect;
    cout << endl;

    /*
     * If the user inputed the wrong information then allow them to reenter it.
     */
    if ((customerInfoCorrect == 'N') || (customerInfoCorrect == 'n'))
    {
        customerRecord.erase(customerRecord.begin() + endV);
        enterCustomerInfo(tempHotelRoom, hotelIndex);
    }

    return TRUE;

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

int main()
{
    hotelManagement ourHotel;

    //ourHotel.hotelManagement();
    ourHotel.displayMainMenu();

    return 0;

}
