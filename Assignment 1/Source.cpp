// Connor Taylor
// The purpose of this program is to implement an array and linked
// list from a text file with city names and their coordinates. Then
// allow to user to add, search, delete, and print all locations. 

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <chrono>
#include <ctime>

struct location 
{
    std::string name = "";
    long double latitude = -1;
    long double longitude = -1;
};

// Defines class for using linked lists
class LinkedList 
{
private: 
    struct node 
    {
        location loc;
        node* next;
    };
    node* head;
public:
    // Precondition: None
    // Constructor
    // Postcondition: None
    LinkedList() 
    { 
        head = nullptr; 
    };

    // Precondition: Location by reference
    // Adds a new location onto the linked list
    // Postcondition: None
    void appendNode(location& loc) 
    {
        // Creates the new node
        node* newNode = new node;
        newNode->loc = loc;
        newNode->next = nullptr;

        node* nodePtr;
        // Checks if the list is empty
        if (head == nullptr) 
        {
            head = newNode;
        }
        // Traveres the list until the first empty element
        else 
        {
            nodePtr = head;
            while (nodePtr->next != nullptr) 
            {
                nodePtr = nodePtr->next;
            }
            nodePtr->next = newNode;
        }
    }

    // Precondition: Locatino by reference
    // Deletes the location in the list
    // Postcondition: None
    void deleteNode(location& loc) 
    {
        node* nodePtr;

        // Exits function if list is empty
        if (head == nullptr) 
        {
            return;
        }
        // Checks if head of list is equal to the location
        if (head->loc.name == loc.name) 
        {
            nodePtr = head->next;
            delete head;
            head = nodePtr;
        }
        else 
        {
            nodePtr = head;
            node* prevNode = head;
            // Traverses the list until it finds the location
            while (nodePtr != nullptr && nodePtr->loc.name != loc.name) 
            {
                prevNode = nodePtr;
                nodePtr = nodePtr->next;
            }
            // Deletes the node with the location
            if (nodePtr != nullptr) 
            {
                prevNode->next = nodePtr->next;
                delete nodePtr;
            }
        }
    }

    // Precondition: Location by reference
    // Searches the linked list for a location
    // Postcondition: Returns an empty location if not found, 
    //                returns same location if found with all information
    location searchList(location& loc) 
    {
        node* nodePtr = head;
        location emptLoc;

        // Traverses the list to find the location, returns if found
        while (nodePtr != nullptr) 
        {
            if (nodePtr->loc.name == loc.name || (nodePtr->loc.latitude == loc.latitude 
                    && nodePtr->loc.longitude == loc.longitude)) 
            {
                loc.name = nodePtr->loc.name;
                loc.latitude = nodePtr->loc.latitude;
                loc.longitude = nodePtr->loc.longitude;
                return loc;
            }
            nodePtr = nodePtr->next;
        }

        // Returns empty location if not found
        return emptLoc;
    }

    // Precondition: None
    // Prints all locations in the list
    // Postcondition: None
    void printList() 
    {
        node* nodePtr = head;

        std::cout << "City Name  Latitude  Longitude\n" << std::endl;
        while (nodePtr != nullptr) 
        {
            std::cout << nodePtr->loc.name << ": (" << nodePtr->loc.latitude << ", "
                      << nodePtr->loc.longitude << ")\n" << std::endl;
            nodePtr = nodePtr->next;
        }
    }

    // Precondition: None
    // Searches the list by finding the distance from a user selected city
    // and returning all cities within that distance
    // Postcondition: None
    void printByDist()
    {
        double dist;
        double tempDist;
        long double M_PI = 3.1415926535;
        location locDest;
        location tempLoc;
        bool found = false;
        node* nodePtr = head;

        // Gets user input and determines if it exists
        std::cout << "Enter name of specified location: ";
        std::cin.ignore();
        std::getline(std::cin, locDest.name);
        locDest = searchList(locDest);
        if (locDest.name == "") 
        {
            std::cout << "No such record exists in the existing data set.\n" << std::endl;
            return;
        }
        locDest.latitude = locDest.latitude * (M_PI / 180.0);
        locDest.longitude = locDest.longitude * (M_PI / 180.0);
        
        // Gets the distance the user wants to search within
        std::cout << "Enter distance: ";
        std::cin >> dist;

        std::cout << "\nOutput:\n";
        while (nodePtr != nullptr) 
        {
            tempLoc.latitude = nodePtr->loc.latitude * (M_PI / 180.0);
            tempLoc.longitude = nodePtr->loc.longitude * (M_PI / 180.0);
            // calculates the distance from the city the user specified 
            tempDist = 3963.191 * acos(sin(locDest.latitude) * sin(tempLoc.latitude)
                     + cos(locDest.latitude) * cos(tempLoc.latitude)
                     * cos(tempLoc.longitude - locDest.longitude));
            // if city is within the distance, and its not the same city then output it
            if (dist >= tempDist && nodePtr->loc.name != locDest.name) 
            {
                std::cout << nodePtr->loc.name << ", (" << nodePtr->loc.latitude << ", "
                          << nodePtr->loc.longitude << ")" << std::endl;
                found = true;
            }
            nodePtr = nodePtr->next;
        }

        // If there are not any cities found within that distance, this message informs the user
        if (!found) 
        {
            std::cout << "No such record exists in the existing data set." << std::endl;
        }

        std::cout << std::endl;
    }

    // Precondition: Fstream by reference
    // Deletes the location from the file
    // Postcondition: None
    void deleteLocation(std::fstream& file) 
    {
        node* nodePtr = head;
        
        // Opens the file and erases its contents
        file.open("Assignment_1_ Test Data_For Windows Users.txt", std::ofstream::out | std::ofstream::trunc);
        file << "City Name  Latitude  Longitude\n" << std::endl;
        // Rewrites the locations from the linked list to the file
        while (nodePtr != nullptr) 
        {
            file << nodePtr->loc.name << ": " << nodePtr->loc.latitude << ", "
                 << nodePtr->loc.longitude << "\n" << std::endl;
            nodePtr = nodePtr->next;
        }
        file.close();
        
        std::cout << "Location deleted successfully.\n" << std::endl;
    }

    // Precondition: None
    // Destructor
    // Postcondition: None
    ~LinkedList() 
    {
        node* nodePtr = head;
        node* next;
        // Traveres list, deleting every element
        while (nodePtr != nullptr) 
        {
            next = nodePtr->next;
            delete nodePtr;
            nodePtr = next;
        }
    }
};

// Precondition: Char by reference, int by reference
// Outputs the menu and gets user input
// Postcondition: None
void menu(char&, int&);

// Precondition: Fstream by reference
// Sees if the file is opened successfully
// Postcondition: bool
bool openFile(std::fstream&);

// Precondition: Fstream by reference
// Closes the file
// Postcondition: None
void closeFile(std::fstream&);

// Precondition: Fstream by reference, int, and pointer to a location
// Implements array from file 
// Postcondition: None
void implementArray(std::fstream&, int, location*);

// Precondition: fstream by reference, int, LinkedList by reference
// Implements LinkedList from file 
// Postcondition: None
void implementLinkedList(std::fstream&, int, LinkedList&);

// Precondition: Fstream by reference, int, pointer to location
// Inserts a location to the array
// Postcondition: None
void insert(std::fstream&, int, location*);

// Precondition: Fstream by reference, LinkedList by reference
// Inserts a location to the LinkedList
// Postcondition: None
void insert(std::fstream&, LinkedList&);

// Precondition: pointer to a location, int
// Searches for a location name in the array
// Postcondition: None
void searchName(location*, int);

// Precondition: LinkedList by reference
// Searches for a location name in the LinkedList
// Postcondition: None
void searchName(LinkedList&);

// Precondition: Pointer to a location, int
// Searches for a location'c coordinates in the array
// Postcondition: None
void searchCoord(location*, int);

// Precondition: LinkedList by reference
// Searches for a location's coordinates in the LinkedList
// Postcondition: None
void searchCoord(LinkedList&);

// Precondition: Fstream by reference, pointer to a location, int
// Deletes a location in the array by name
// Postcondition: None
void deleteName(std::fstream&, location*, int);

// Precondition: Fstream by reference, LinkedList by reference
// Deletes a location in the LinkedList by name
// Postcondition: None
void deleteName(std::fstream&, LinkedList&);

// Precondition: Fstream by reference, pointer to a location, int
// Deletes a location in the array by coordinates
// Postcondition: None
void deleteCoord(std::fstream&, location*, int);

// Precondition: Fstream by reference, LinkedList by reference
// Deletes a location in the LinkedList by coordinates
// Postcondition: None
void deleteCoord(std::fstream&, LinkedList&);

// Precondition: Pointer to a location, int
// Prints all locations within a distance from a city in the array
// Postcondition: None
void printByDist(location*, int);

// Precondition: Pointer to a location, int
// Prints all locations in the array
// Postcondition: None
void printAll(location*, int);

// Precondition: Fstream by reference
// Gets the number of locations in the text file
// Postcondition: int
int getNumLoc(std::fstream&);

// Precondition: Fstream by reference, pointer to a location, int, int
// Deletes a location from the array
// Postcondition: None
void deleteLocation(std::fstream&, location*, int, int);

int main() 
{
    std::fstream file;
    int numOfLocations;
    location* loc;
    LinkedList list;
    bool listExists = false;
    char implementationChoice = 'A';
    int operationChoice = '0';

    while (operationChoice != 8) 
    {
        // implements array based on the number of locations in the text file
        numOfLocations = getNumLoc(file);
        loc = new location[numOfLocations];
        // Calls menu to get user input
        menu(implementationChoice, operationChoice);
        // FOR ARRAY
        if (implementationChoice == 'A' || implementationChoice == 'a') 
        {
            implementArray(file, numOfLocations, loc);
            switch (operationChoice) 
            {
            case 1:
                insert(file, numOfLocations, loc);
                break;
            case 2:
                searchName(loc, numOfLocations);
                break;
            case 3:
                searchCoord(loc, numOfLocations);
                break;
            case 4:
                deleteName(file, loc, numOfLocations);
                break;
            case 5:
                deleteCoord(file, loc, numOfLocations);
                break;
            case 6:
                printByDist(loc, numOfLocations);
                break;
            case 7:
                printAll(loc, numOfLocations);
                break;
            default:
                break;
            }
        }
        // FOR LINKEDLIST
        else if (implementationChoice == 'B' || implementationChoice == 'b') 
        {
            // Checks if the list already implemented
            if (!listExists) 
            {
                implementLinkedList(file, numOfLocations, list);
                listExists = true;
            }
            switch (operationChoice) 
            {
            case 1:
                insert(file, list);
                break;
            case 2:
                searchName(list);
                break;
            case 3:
                searchCoord(list);
                break;
            case 4:
                deleteName(file, list);
                break;
            case 5:
                deleteCoord(file, list);
                break;
            case 6:
                list.printByDist();
                break;
            case 7:
                list.printList();
                break;
            default:
                break;
            }
        }  
    }
    return 0;
}

// Precondition: Fstream by reference
// Sees if the file is opened successfully
// Postcondition: bool
bool openFile(std::fstream& file) 
{
    // Opens file and checks if it is opened
    file.open("Assignment_1_ Test Data_For Windows Users.txt");
    if (!file.is_open()) 
    {
        std::cout << "Unable to open file! Ending program." << std::endl;
        return false;
    }

    return true;
}

// Precondition: Fstream by reference
// Closes the file
// Postcondition: None
void closeFile(std::fstream& file) 
{
    // Closes file and checks if it closed successfully
    file.close();
    if (file.is_open()) 
    {
        std::cout << "File failed to close." << std::endl;
    }
}

// Precondition: Char by reference, int by reference
// Outputs the menu and gets user input
// Postcondition: None
void menu(char& implementationChoice, int& operationChoice) 
{
    // Outputs menu
    std::cout << "*************************************\n"
              << "Implementation Options :\n"
              << "A. Use an array - based list implementation\n"
              << "B. Use a linked - list implementation\n"
              << "\n"
              << "Operation Options :\n"
              << "1. Insert a record\n"
              << "2. Search for a record by name\n"
              << "3. Search for a record by coordinate\n"
              << "4. Delete a record by name\n"
              << "5. Delete a record by coordinate\n"
              << "6. Print records within a given distance of a specified location\n"
              << "7. Print all records\n"
              << "8. Exit\n" << std::endl;

    std::cout << "Enter your implementation option: ";
    std::cin >> implementationChoice;
    // Validates input
    while (implementationChoice != 'A' && implementationChoice != 'a' && 
        implementationChoice != 'B' && implementationChoice != 'b') 
    {
        std::cout << "Please enter either A or B: ";
        std::cin >> implementationChoice;
    }
    
    std::cout << "Enter your operation option: ";
    std::cin >> operationChoice;
    // Valids input
    while (operationChoice < 1 || operationChoice > 8) 
    {
        std::cout << "Please enter a number between 1 and 8: ";
        std::cin >> operationChoice;
    }

    std::cout << std::endl;
}

// Precondition: Fstream by reference, int, and pointer to a location
// Implements array from file 
// Postcondition: None
void implementArray(std::fstream& file, int numOfLocations, location* loc) 
{
    std::string temp;
    // opens the file
    if (!openFile(file)) 
    {
        return;
    }

    // Skips two lines of text document
    std::getline(file, temp, '\n');
    std::getline(file, temp, '\n');
    // Traveres text document and adds values to array
    for (int i = 0; i < numOfLocations; ++i) 
    {
        std::getline(file, temp, ':');
        loc[i].name = temp;
        std::getline(file, temp, ',');
        loc[i].latitude = std::stold(temp);
        std::getline(file, temp, '\n');
        loc[i].longitude = std::stold(temp);
        std::getline(file, temp, '\n');
    }

    closeFile(file);
}

// Precondition: fstream by reference, int, LinkedList by reference
// Implements LinkedList from file 
// Postcondition: None
void implementLinkedList(std::fstream& file, int numOfLocations, LinkedList& list) 
{
    std::string temp;
    location loc;

    // Opens the file
    if (!openFile(file)) 
    {
        return;
    }

    // Skips the first two lines of the file
    std::getline(file, temp, '\n');
    std::getline(file, temp, '\n');
    // Takes values from the file and adds locations to the LinkedList
    for (int i = 0; i < numOfLocations; ++i) 
    {
        std::getline(file, temp, ':');
        loc.name = temp;
        std::getline(file, temp, ',');
        loc.latitude = std::stold(temp);
        std::getline(file, temp, '\n');
        loc.longitude = std::stold(temp);
        std::getline(file, temp, '\n');
        list.appendNode(loc);
    }

    closeFile(file);
}


// Precondition: Fstream by reference, int, pointer to location
// Inserts a location to the array
// Postcondition: None
void insert(std::fstream& file, int numOfLocations, location* loc) 
{
    // Gets user input for the new city
    location newLoc;
    std::cout << "Enter the name of the city: ";
    std::cin.ignore();
    std::getline(std::cin, newLoc.name);
    std::cout << "Enter x coordinate of the city: ";
    std::cin >> newLoc.longitude;
    std::cout << "Enter y coordinate of the city: ";
    std::cin >> newLoc.latitude;
    
    // checks if the city is already in the array
    for (int i = 0; i < numOfLocations; ++i) 
    {
        if (newLoc.name == loc[i].name) 
        {
            std::cout << "No need to insert again, as this record exists in the existing data set.\n" << std::endl;
            return;
        }
    }

    // Adds location to the end of the array
    location* tempLoc = new location[numOfLocations + 1];
    std::copy(loc, loc + std::min(numOfLocations, numOfLocations +  1), tempLoc);
    delete[] loc;
    loc = tempLoc;

    // Adds location to the end of the file
    file.open("Assignment_1_ Test Data_For Windows Users.txt", std::ios::app);
    file << newLoc.name << ": " << newLoc.longitude << ", " << newLoc.latitude << "\n" << std::endl;
    closeFile(file);
    std::cout << "Record inserted successfully.\n" << std::endl;
}

// Precondition: Fstream by reference, LinkedList by reference
// Inserts a location to the LinkedList
// Postcondition: None
void insert(std::fstream& file, LinkedList& list) 
{
    // Gets user input for the new location
    location newLoc;
    std::cout << "Enter the name of the city: ";
    std::cin.ignore();
    std::getline(std::cin, newLoc.name);
    std::cout << "Enter x coordinate of the city: ";
    std::cin >> newLoc.longitude;
    std::cout << "Enter y coordinate of the city: ";
    std::cin >> newLoc.latitude;
    // Checks if the location already exists
    if(newLoc.name == list.searchList(newLoc).name) 
    {
        std::cout << "No need to insert again, as this record exists in the existing data set.\n" << std::endl;
        return;
    }
    // Adds the location to the list
    list.appendNode(newLoc);

    // Adds the location to the end of the file
    file.open("Assignment_1_ Test Data_For Windows Users.txt", std::ios::app);
    file << newLoc.name << ": " << newLoc.longitude << ", " << newLoc.latitude << "\n" << std::endl;
    closeFile(file);
    std::cout << "Record inserted successfully.\n" << std::endl;
}


// Precondition: pointer to a location, int
// Searches for a location name in the array
// Postcondition: None
void searchName(location* loc, int numOfLocations) 
{
    // Gets user input for the city they are looking for
    std::string locToFind;
    std::cout << "Enter the name of the city to be searched: ";
    std::cin.ignore();
    std::getline(std::cin, locToFind);

    // Traverses array until location is found
    for (int i = 0; i < numOfLocations; ++i) 
    {
        if (locToFind == loc[i].name) 
        {
            std::cout << loc[i].name << ", (" << loc[i].latitude
                << ", " << loc[i].longitude << ")\n" << std::endl;
            return;
        }
    }
    std::cout << "No such record exists in the existing data set.\n" << std::endl;
}

// Precondition: LinkedList by reference
// Searches for a location name in the LinkedList
// Postcondition: None
void searchName(LinkedList& list) 
{
    // Gets user input of city to find
    location locToFind;
    std::cout << "Enter the name of the city to be searched: ";
    std::cin.ignore();
    std::getline(std::cin, locToFind.name);

    // Searches list
    locToFind = list.searchList(locToFind);
    if (locToFind.name != "") 
    {
        std::cout << locToFind.name << ", (" << locToFind.latitude
            << ", " << locToFind.longitude << ")\n" << std::endl;
        return;
    }
    std::cout << "No such record exists in the existing data set.\n" << std::endl;
}

// Precondition: Pointer to a location, int
// Searches for a location'c coordinates in the array
// Postcondition: None
void searchCoord(location* loc, int numOfLocations) 
{
    // Takes user input of coordinates to search for
    location locToFind;
    std::cout << "Enter x coordinate of the city: ";
    std::cin >> locToFind.latitude;
    std::cout << "Enter y coordinate of the city: ";
    std::cin >> locToFind.longitude;

    // Traverses array looking for coordinates
    for (int i = 0; i < numOfLocations; ++i) 
    {
        if (locToFind.latitude == loc[i].latitude 
            && locToFind.longitude == loc[i].longitude) 
        {
            std::cout << loc[i].name << ", (" << loc[i].latitude
                << ", " << loc[i].longitude << ")\n" << std::endl;
            return;
        }
    }
    std::cout << "No such record exists in the existing data set\n" << std::endl;
}

// Precondition: LinkedList by reference
// Searches for a location's coordinates in the LinkedList
// Postcondition: None
void searchCoord(LinkedList& list) 
{
    // Takes user input of the coordinates to look for
    location locToFind;
    std::cout << "Enter x coordinate of the city: ";
    std::cin >> locToFind.latitude;
    std::cout << "Enter y coordinate of the city: ";
    std::cin >> locToFind.longitude;

    // Searches list for the coordinates
    locToFind = list.searchList(locToFind);
    if (locToFind.name != "") 
    {
        std::cout << locToFind.name << ", (" << locToFind.latitude
                  << ", " << locToFind.longitude << ")\n" << std::endl;
        return;
    }
    std::cout << "No such record exists in the existing data set\n" << std::endl;
}

// Precondition: Fstream by reference, pointer to a location, int
// Deletes a location in the array by name
// Postcondition: None
void deleteName(std::fstream& file, location* loc, int numOfLocations) 
{
    // Searches name of city to delete
    std::string locToDelete;
    std::cout << "Enter the name of the city to be deleted: ";
    std::cin.ignore();
    std::getline(std::cin, locToDelete);

    // Traverses array for the location name to dekete
    for (int i = 0; i < numOfLocations; ++i) 
    {
        if (locToDelete == loc[i].name) 
        {
            deleteLocation(file, loc, numOfLocations, i);
            return;
        }
    }
    std::cout << "No such record exists in the existing data set.\n" << std::endl;
}

// Precondition: Fstream by reference, LinkedList by reference
// Deletes a location in the LinkedList by name
// Postcondition: None
void deleteName(std::fstream& file, LinkedList& list) 
{
    // Takes name of location to delete
    location locToDelete;
    std::cout << "Enter the name of the city to be deleted: ";
    std::cin.ignore();
    std::getline(std::cin, locToDelete.name);

    // Checks that the location exists
    locToDelete = list.searchList(locToDelete);
    if (locToDelete.name == "") 
    {
        std::cout << "No such record exists in the existing data set.\n" << std::endl;
        return;
    }

    // Deletes locations from file and LinkedList
    list.deleteNode(locToDelete);
    list.deleteLocation(file);
}

// Precondition: Fstream by reference, pointer to a location, int
// Deletes a location in the array by coordinates
// Postcondition: None
void deleteCoord(std::fstream& file, location* loc, int numOfLocations) 
{
    // Takes coordinates of location to delete
    location locToDelete;
    std::cout << "Enter x coordinate of the city: ";
    std::cin >> locToDelete.latitude;
    std::cout << "Enter y coordinate of the city: ";
    std::cin >> locToDelete.longitude;

    // Traverses array for coordinates and deletes it
    for (int i = 0; i < numOfLocations; ++i) 
    {
        if (locToDelete.latitude == loc[i].latitude 
            && locToDelete.longitude == loc[i].longitude) 
        {
            deleteLocation(file, loc, numOfLocations, i);
            return;
        }
    }
    std::cout << "No such record exists in the existing data set.\n" << std::endl;
}

// Precondition: Fstream by reference, LinkedList by reference
// Deletes a location in the LinkedList by coordinates
// Postcondition: None
void deleteCoord(std::fstream& file, LinkedList& list) 
{
    // Takes input of coordinates for location to delete
    location locToDelete;
    std::cout << "Enter x coordinate of the city: ";
    std::cin >> locToDelete.latitude;
    std::cout << "Enter y coordinate of the city: ";
    std::cin >> locToDelete.longitude;

    // Checks if the location exists
    locToDelete = list.searchList(locToDelete);
    if (locToDelete.name == "") 
    {
        std::cout << "No such record exists in the existing data set.\n" << std::endl;
        return;
    }
    // Deletes the location from LinkedList and file
    list.deleteNode(locToDelete);
    list.deleteLocation(file);
}

// Precondition: Pointer to a location, int
// Prints all locations within a distance from a city in the array
// Postcondition: None
void printByDist(location* loc, int numOfLocations) 
{
    double dist;
    double tempDist;
    long double M_PI = 3.1415926535;   
    location locDest;
    location tempLoc;
    bool found = false;
    bool exists = false;

    // Takes input of name of the city
    std::cout << "Enter name of specified location: ";
    std::cin.ignore();
    std::getline(std::cin, locDest.name);
    // Traveres the array to get the coordinates
    for (int i = 0; i < numOfLocations; ++i) 
    {
        if (loc[i].name == locDest.name) 
        {
            locDest.latitude = loc[i].latitude * (M_PI / 180.0);
            locDest.longitude = loc[i].longitude * (M_PI / 180.0);
            exists = true;
        }
    }
    // If the location does not exist, exits function
    if (!exists) 
    {
        std::cout << "No such record exists in the existing data set.\n" << std::endl;
        return;
    }

    // Takes user input for the distance
    std::cout << "Enter distance: ";
    std::cin >> dist;

    std::cout << "\nOutput:\n";
    // Traveres array
    for (int i = 0; i < numOfLocations; ++i) 
    {
        // Convert to radians 
        tempLoc.latitude = loc[i].latitude * (M_PI / 180.0);
        tempLoc.longitude = loc[i].longitude * (M_PI / 180.0);
        // Calculate distance
        tempDist = 3963.191 * acos(sin(locDest.latitude) * sin(tempLoc.latitude) 
                 + cos(locDest.latitude) * cos(tempLoc.latitude) 
                 * cos(tempLoc.longitude - locDest.longitude));
        // Outputs location if it is within the distance
        if (dist >= tempDist && loc[i].name != locDest.name) 
        {
            std::cout << loc[i].name << ", (" << loc[i].latitude << ", " 
                      << loc[i].longitude << ")" << std::endl;
            found = true;
        }
    }
    // Informs user if there are no locations within that distance
    if (!found) 
    {
        std::cout << "No such record exists in the existing data set." << std::endl;
    }

    std::cout << std::endl;
}

// Precondition: Pointer to a location, int
// Prints all locations in the array
// Postcondition: None
void printAll(location* loc, int numOfLocations) 
{
    std::cout << "City Name  Latitude  Longitude\n" << std::endl;
    // Traverses array, outputting each location
    for (int i = 0; i < numOfLocations; ++i) 
    {
        std::cout << loc[i].name << ": (" << loc[i].latitude << ", " 
                  << loc[i].longitude << ")\n" << std::endl;
    }
}

// Precondition: Fstream by reference
// Gets the number of locations in the text file
// Postcondition: int
int getNumLoc(std::fstream& file) 
{
    int numOfLines = 0;
    std::string line;
    // Returns -1 if file fails to open
    if (!openFile(file)) 
    {
        return -1;
    }

    // Counts number of lines in text file
    while (std::getline(file, line)) 
    {
        ++numOfLines;
    }

    // Closes file when done
    closeFile(file);

    // Returns number of locations
    return numOfLines / 2 - 1;
}

// Precondition: Fstream by reference, pointer to a location, int, int
// Deletes a location from the array
// Postcondition: None
void deleteLocation(std::fstream& file, location* loc, int numOfLocations, int index) 
{
    // New array with one less locations
    location* newLoc = new location[numOfLocations - 1];
    // Copies old array to new one without deleted location
    std::copy(loc, loc + index, newLoc);
    std::copy(loc + index + 1, loc + numOfLocations, newLoc + index);
    delete[] loc;
    loc = newLoc;
    
    // Clears and then updates the file without deleted location
    file.open("Assignment_1_ Test Data_For Windows Users.txt", std::ofstream::out | std::ofstream::trunc);
    file << "City Name  Latitude  Longitude\n" << std::endl;
    for (int i = 0; i < numOfLocations - 1; ++i) 
    {
        file << loc[i].name << ": " << loc[i].latitude << ", " 
             << loc[i].longitude << "\n" << std::endl;
    }
    closeFile(file);
    
    std::cout << "Location deleted successfully.\n" << std::endl;
}
