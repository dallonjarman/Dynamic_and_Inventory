/**
 * RECOMMEND WAY TO COMPILE
 * g++ -Wall -Wextra -std=c++11 homework4.cpp -o Homework
 * ./Homework
 */

#include <algorithm> // Required for the sort function
#include <cassert> // Required for the assert function
#include <functional> // Required for the greater function
#include <iomanip> // Required for the setw function
#include <iostream> // Required for the cin and cout functions
#include <map> // Required for the map data structure
#include <queue> // Required for the queue data structure
#include <string> // Required for the string data structure
#include <unordered_map> // Required for the unordered_map data structure
#include <unordered_set> // Required for the unordered_set data structure
#include <vector> // Required for the vector data structure

// removes the need of using "std::"
using namespace std;


/*********************************************************************/
/*********************************************************************/
/****************************** INVENTORY ****************************/
/*********************************************************************/
/*********************************************************************/

// Define the InventoryItem class to hold information about each item in the inventory
// *****************************************************
// *                                                   *
// *                 INVENTORY ITEM                    *
// *                                                   *
// *****************************************************
class InventoryItem 
{

public:
    InventoryItem(const string& name, int quantity, double price) :
        m_name(name), m_quantity(quantity), m_price(price) {}

    // getters
        // this will get and return the name of the item
    const string& getName() const 
    {
        return m_name;
    }

    // this will get and return the quantity of the item
    int getQuantity() const 
    {
        return m_quantity;
    }

    // this will get and return the price of the item
    double getPrice() const 
    {
        return m_price;
    }

    // this is how you will set the quantity of an item
    void setQuantity(int quantity) 
    {
        m_quantity = quantity;
    }

    // this is how you set the price of an item
    void setPrice(double price) 
    {
        m_price = price;
    }

    // operator
    bool operator==(const InventoryItem& other) const 
    {
        return m_name == other.m_name && m_quantity == other.m_quantity && m_price == other.m_price;
    }

// Initalizes private variables
private:
    string m_name;
    int m_quantity;
    double m_price;
};

// *****************************************************
// *                                                   *
// *                 INVENTORY MANAGER                 *
// *                                                   *
/// *****************************************************
class InventoryManager 
{

public:
    InventoryManager() {}

    // Adds an item to the inventory
    void addInventoryItem(const InventoryItem& item) 
    {
        m_inventorySet.insert(item);
    }

    // Removes an item from the inventory
    void removeInventoryItem(const string& itemName) 
    {
        for (auto it = m_inventorySet.begin(); it != m_inventorySet.end(); it++) 
        {
            if (it->getName() == itemName) {
                m_inventorySet.erase(it);
                break;
            }
        }
    }

    // Finds a certain item in the inventory
    const InventoryItem* findInventoryItem(const string& itemName) const 
    {
        for (auto it = m_inventorySet.cbegin(); it != m_inventorySet.cend(); it++) 
        {
            cout << it->getName();
            if (it->getName() == itemName) 
            {
                cout << "a";
                return &(*it);
            }
        }
        cout << "b";
        return nullptr;
    }

    // Display the current inventory
    void displayInventory() const 
    {
        cout << "Current Inventory: " << endl;
        for (auto it = m_inventorySet.begin(); it != m_inventorySet.end(); it++) 
        {
            cout << it->getName() << " | Quantity: " << it->getQuantity() << " | Price: " << it->getPrice() << endl;
        }
    }

// Initalizes private variables
private:
    // Define a hash function for the InventoryManager class
    struct InventoryItemHash 
    {
        size_t operator()(const InventoryItem& item) const 
        {
            return hash<string>()(item.getName()) ^ hash<double>()(item.getPrice());
        }
    };

    unordered_set<InventoryItem, InventoryItemHash> m_inventorySet;
};

// *****************************************************
// *                                                   *
// *            PRINT INVENTORY TABLE                  *
// *                                                   *
// *****************************************************
void printInventoryTable(const unordered_map<string, InventoryItem>& inventory) 
{
    // Print the table header
    cout << left << setw(20) << "Product Name" << setw(10) << "Quantity" << setw(10) << "Price" << endl;
    cout << setfill('-') << setw(40) << "" << setfill(' ') << endl;

    // Print each item in the inventory
    for (const auto& item : inventory) 
    {
        cout << left << setw(20) << item.second.getName() << setw(10) << item.second.getQuantity()
                             << setw(10) << item.second.getPrice() << endl;
    }
}

// *****************************************************
// *                                                   *
// *                 FIND PRODUCT                      *
// *                                                   *
// *****************************************************
void findProduct ( string product, const unordered_map<string, InventoryItem>& inventoryMap) 
{

    // Finds if the product does exist within the map
    const auto it = inventoryMap.find(product);

    // Gets the product and prints the quantity and price of the product
    if (it != inventoryMap.end()) 
    {
        // Get the associated InventoryItem object
        const InventoryItem& item = it->second;

        // Prints the quantity and price of the object
        cout << "The quantity is " << item.getQuantity() << "\n";
        cout << "This price is $" << item.getPrice() << "\n\n";
    } 
    else 
    {
        // Prints a message if the product could not be found
        cout << "Item not found.\n\n";
    }
}

// *****************************************************
// *                                                   *
// *                 CHANGE VALUES                     *
// *                                                   *
// *****************************************************
void changeValues ( const string product, int quantity, double price, unordered_map<string, InventoryItem>& inventoryMap ) 
{
    
    auto it = inventoryMap.find(product);
    if (it != inventoryMap.end()) 
    {
        inventoryMap.erase(it);
        inventoryMap.insert({product, InventoryItem(product, quantity, price)});

        // logging statement
        cout << product << " has been changed.\n\n";
    }
    else 
    {
       // logging statement
       cout << product << " is not in the inventory.\n\n"; 
    }
    
    
}

// *****************************************************
// *                                                   *
// *                 ADD PRODUCTS                      *
// *                                                   *
// *****************************************************
void addProducts( int num, unordered_map<string, InventoryItem>& inventoryMap ) 
{
    // initalize variables
    string products;
    int quantity;
    double price;
    string addAnother = "yes";

    for ( auto i = 0; i < num; i++) 
    {
    // Allows user to add a product to inventory
        cout << "Name of the product would you like to add: ";
        cin >> ws;
        getline(cin, products);

        // checks to see if the product already exists in the inventory
        auto it = inventoryMap.find(products);
        if (it != inventoryMap.end()) 
        {
            cout << endl;
            cout << products << " is already in the inventory." << endl;
            cout << endl;
            break;
        }

        // Allows user to add the quantity of the product
        cout << "How many " << products << "'s do you have?: ";

        cin.clear();

        while (!(cin >> quantity) || cin.peek() != '\n') 
        {
            cout << "Invalid input. Please enter a valid number: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }


        // Allows the user to add a price to the product
        cout << "How much do these " << products << "'s cost: $";
        
        cin.clear();

        while (!(cin >> price)) 
        {
        cout << "Invalid input. Please enter a valid number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }


        cout << endl;

        // Adds the product to the map
        inventoryMap.insert(
            {
                products, InventoryItem(products, quantity, price)
            });

        auto item = inventoryMap.begin();

        cout << item->second.getQuantity() << " " << item->second.getName() << "'s" << " with a price of $" << 
                                item->second.getPrice() << " was added to inventory" << endl;
        cout << endl;

    }
}


// *************************************************************
// *                                                           *
// *                        REMOVE PRODUCT                     *
// *                                                           *
// *************************************************************
void removeProduct(const string& productName, unordered_map<string, InventoryItem>& inventoryMap) 
{
    // add a logging statement here
    cout << "Removing " << productName << " from the inventory.\n";

    auto it = inventoryMap.find(productName);
    if (it != inventoryMap.end()) 
    {
        inventoryMap.erase(it);
        cout << productName << " has been removed from the inventory.\n\n";
    }
    else 
    {
        cout << productName << " is not in the inventory.\n\n";
    }
}

// *************************************************************
// *                                                           *
// *                        TITLE                              *
// *                                                           *
// *************************************************************
void title() 
{
    cout << endl << "Welcome to Dallon's Inventory Management System" << endl;
    cout << "This mangement system allows users to keep track of items inside their store" << endl;
    cout << "You may add or remove products, change the quantity, and change the price of any time" << endl;
    cout << endl;
}

// *************************************************************
// *                                                           *
// *                        INVENTORY                          *
// *                                                           *
// *************************************************************
int inventory() 
{

    // initalize variables
    int productNum, quantity, nextStep = 0;
    double price;
    string product, printStatement;

    // Prints title
    title();

    // Creates an InventoryManager object
    InventoryManager manager;

    // Create an unordered map of InventoryItem objects
    unordered_map<string, InventoryItem> inventoryMap;

    // Ask the user for their next steps
    do 
    {
        
        // Lists of all the next steps the user can take
        cout << "Please type the following number for your next steps" << endl;
        cout << endl;
        cout << "1. Add more products" << endl;
        cout << "2. Remove a product" << endl;
        cout << "3. Change a value in a product" << endl;
        cout << "4. Print out the product list" << endl;
        cout << "5. Find a product" << endl;
        cout << "6. End program" << endl;

        // Allows the user to select their next step
        cout << "Type a number above: ";


        // Starts while loop to keep program running until user types in correct input       
        while (true) 
        {

            
            // This will ask the user for a int input until an integer input is given
            if (!(cin >> nextStep) || cin.peek() != '\n') 
            {
                cout << "Invalid input. Please enter a valid number (1-6): ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            // Checks to see if the number the user inputs is possible
            if (nextStep < 1 || nextStep > 6) 
            {
                cout << "Number out of range. ";
                cout << "Please enter a number between 1 and 6: ";
                continue;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }


        // Prints endline
        cout << endl;

        if ( nextStep == 1) 
        {
            // Asks the user how many items they would like to add 
            cout << "How many items would you like to add: ";


            // Failsafe if user inserts a word instead of a number
            while (!(cin >> productNum) || cin.peek() != '\n') 
            {
                cout << "Invalid input. Please enter a valid number: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            // calls the function addProducts to allow the user to add products
            addProducts(productNum, inventoryMap);
            

            
        }

        // Allows users to remove products
        else if ( nextStep == 2 ) 
        {

            // checks to see if there is product currently in the map
            bool noProduct = inventoryMap.empty();

            // If no product exists then it will print the users next step and leave the if statement
            if ( noProduct ) 
            {
                cout << "Please add a product before removing a product" << endl;
                cout << endl;
                continue;
            }

            // Allows the user to remove a product
            cout << "What product would you like to remove: ";
            cin >> ws;
            getline(cin, product);
            removeProduct(product, inventoryMap);
        }

        // Allows user to change the values of a product
        else if ( nextStep == 3 ) 
        {

            // checks to see if there is product currently in the map
            bool noProduct = inventoryMap.empty();

            // If no product exists then it will print the users next step and leave the if statement
            if ( noProduct ) 
            {
                cout << "Please add a product before changing the values of a product" << endl;
                cout << endl;
                continue;
            }

            // Allows the user to change parts of a product
            cout << "What product would you like to change: ";

            // Clears cin
            cin.clear();

            // If user enters in a invalid input it will nag the user till correct input is entered
            while (!(cin >> product)) 
            {
                cout << "Invalid input. Please enter a valid number: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            // Asks user for a new quantity
            cout << "What is the new quantity" << endl;

            // Clears cin
            cin.clear();

            // Nags user until valid input is given
            while (!(cin >> quantity)) 
            {
                cout << "Invalid input. Please enter a valid number: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            // Asks user for a new price
            cout << "What is the new price" << endl;

            // Clears cin
            cin.clear();

            // Nags user until correct input is given
            while (!(cin >> price)) 
            {
                cout << "Invalid input. Please enter a valid number: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            // Changes the value of the product
            changeValues(product, quantity, price, inventoryMap);
        }

        // Allows the user to print out a table of all the existing products
        else if ( nextStep == 4 ) 
        {
            // Prints the table of all your products
            printInventoryTable(inventoryMap);
            cout << endl;
        }

        // Allows the user to find a specific product
        else if ( nextStep == 5 ) 
        {

            // checks to see if there is product currently in the map
            bool noProduct = inventoryMap.empty();

            // If no product exists then it will print the users next step and leave the if statement
            if ( noProduct ) 
            {
                cout << "Please add a product before finding a product" << endl;
                cout << endl;
                continue;
            }

            // Asks the user for what product they would like to find
            cout << "What product would you like to find: ";
            cin >> ws;
            getline(cin, product);

            // calls the function and finds their product
            findProduct( product, inventoryMap );

        }

    // Ends whille loop when 6 is inserted
    } while ( nextStep != 6);


    // Return SUCCESS
    return 0;
}

/*********************************************************************/
/*********************************************************************/
/*********************** DYNAMIC STORAGE *****************************/
/*********************************************************************/
/*********************************************************************/

// ************************************************************
//
//                    struct Name
//
// ************************************************************
struct Name {
    string name;

    // Constructor
    Name(string name = "") {
        this->name = name;
        
    }
    
    // Destructor
    ~Name() {
        // Nothing to do here, but included for completeness
    }
};

// ************************************************************
// 
//                    TITLE 2
//
// ************************************************************
void title2()
{
    cout << endl;
    cout << "Name List" << endl;
    cout << "=========" << endl;
    cout << endl;
}

// ************************************************************
// *                                                          *
// *                        ADD NAME                          *
// *                                                          *
// ************************************************************
void addName(Name**& names, int& numNames, string name) 
{
    // contract check
    assert(names != nullptr);
    assert(numNames > 0);

    // Create a new Name object
    Name* newName = new Name;
    newName->name = name;

    // Create a new array of pointers to Name objects
    Name** newNames = new Name * [numNames + 1];

    // Copy the pointers from the old array to the new array
    for (int i = 0; i < numNames; i++) 
    {
        newNames[i] = names[i];
    }

    // Add the pointer to the new Name object to the new array
    newNames[numNames] = newName;

    // Delete the old array
    // What language feautre does this misuse
    // of the delete operator use?
    delete[] names;

    // Update the names array to point to the new array
    names = newNames;

    // Update the number of names
    numNames++;
}

// ************************************************************
// *                                                          *
// *                      COMPARE NAMES                       *
// *                                                          *
// ************************************************************
bool compareNames(Name* a, Name* b) 
{
    return a->name < b->name;
}

// ************************************************************
// *                                                          *
// *                    FIND NAME INDEX                       *
// *                                                          *
// ************************************************************
int findNameIndex(Name** names, int numNames, string targetName) {

    for (int i = 0; i < numNames; i++) {
        if (names[i]->name == targetName) {
            return i;
        }
    }
    // Name not found
    return -1;
}

// ************************************************************
// *                                                          *
// *                     DELETE NAME                          *
// *                                                          *
// ************************************************************
void deleteName(Name**& names, int& numNames, string name) 
{
    // add a logging statement
    cout << "Deleting Name " << name << endl;

    // Find the index of the name
    int index = findNameIndex(names, numNames, name);

    // Check if the name was found
    if (index != -1) 
    {
        // Delete the Name object
        delete names[index];

        // Create a new array of pointers to Name objects
        Name** newNames = new Name * [numNames - 1];

        // Copy the pointers from the old array to the new array
        for (int i = 0; i < index; i++) 
        {
            newNames[i] = names[i];
        }
        for (int i = index + 1; i < numNames; i++) 
        {
            newNames[i - 1] = names[i];
        }

        // Delete the old array
        delete[] names;

        // Update the names array to point to the new array
        names = newNames;

        // Update the number of names
        numNames--;
    }
}

// ************************************************************
// *                                                          *
// *                     DISPLAY NAMES                        *
// *                                                          *
// ************************************************************

bool nameExists(Name** names, int numNames, string name) 
{
    // Find the index of the name
    int index = findNameIndex(names, numNames, name);

    // Check if the name was found
    if (index != -1) 
    {
        return true;
    }
    else 
    {
        return false;
    }
}

// ************************************************************
// *                                                          *
// *                     DYNAMIC STORAGE                      *
// *                                                          *
// ************************************************************
int dynamicStorage() 
{
    // Initialize variables
    int numNames = 0;

    // print title
    title2();

    // Prompt the user to enter the number of names to store
    cout << "How many names do you want to enter? ";
    cin >> numNames;

    // contract check
    assert(numNames > 0 && numNames < 1000 && "Invalid number of names");

    // Check if the user entered a number
    while (cin.fail()) 
    {
        cout << "Invalid input. Please enter a number: ";
        cin.clear();
        cin.ignore(256, '\n');
        cin >> numNames;
    }

    // Check if the user entered a positive number
    while (numNames < 0) 
    {
        cout << "Invalid input. Please enter a positive number: ";
        cin >> numNames;
    }

    // Ignore the newline character left by cin
    cin.ignore(); 
    
    // Declare a pointer to an array of pointers to Name objects
    Name **names = nullptr; 
    
    // Try to allocate memory for the array of pointers to Name objects
    try 
    {

        // Allocate memory for the array of pointers to Name objects
        names = new Name*[numNames];
        
        // Prompt the user to enter each person's name 
        for (int i = 0; i < numNames; i++) 
        {
            names[i] = new Name; // Allocate memory for a new Name object
            cout << "Enter name " << i+1 << ": ";
            getline(cin, names[i]->name);

            // contract check
            assert(names[i]->name != "" && "Invalid name");
            
        }

        // Declare a map to store the names by category
        map<string, vector<string>> categories;

         // Prompt the user to enter the number of names to store
        int numCategory = 0;
        cout << endl;
        cout << "How many categories do you want to enter? ";
        cin >> numCategory;

        // contract check
        assert(numCategory > 0 && numCategory < 100 && "Invalid number of categories");

        // Check if the user entered a number
        while (cin.fail()) 
        {
            // Prompt the user to enter a number
            cout << "Invalid input. Please enter a number: ";
            cin.clear();
            cin.ignore(256, '\n');
            cin >> numCategory;
        }

        // Check if the user entered a positive number
        while (numCategory < 0) 
        {
            // Prompt the user to enter a positive number
            cout << "Invalid input. Please enter a positive number: ";
            cin >> numCategory;
        }


        // Ignore the newline character left by cin
        cin.ignore(); 


        // Prompt the user to enter each category name and store it in the map
        for (int i = 0; i < numCategory; i++) 
        {
            // Prompt the user to enter the category name
            string categoryName;
            cout << "Enter category name " << i+1 << ": ";
            getline(cin, categoryName);

            // contract check
            assert(categoryName != "" && "Invalid category name");

            // Add the category name to the map
            categories[categoryName] = vector<string>();
        }

        // Prompt the user to enter each person's category
        for (int i = 0; i < numNames; i++) 
        {
            // Loop through the map and prompt the user to enter the category value
            for (auto& category : categories) 
            {
                // Prompt the user to enter the category value
                cout << category.first << " for " << names[i]->name << ": ";
                string categoryValue;
                getline(cin, categoryValue);

                // contract check
                assert(categoryValue != "" && "Invalid category value");

                // Add the category value to the vector
                category.second.push_back(categoryValue);

            }
        }

        // print endline
        cout << endl;
        int choice = 0;
       

        while (choice != 7) 
        {
            cout << "Please enter a your next steps ( 1 - 7 )" << endl;
            cout << "1. Add a name " << endl;
            cout << "2. Delete a name " << endl;
            cout << "3. Add a category " << endl;
            cout << "4. Delete a category " << endl;
            cout << "5. Print the list " << endl;
            cout << "6. Search for a name" << endl;
            cout << "7. Exit" << endl;

            // Prompt the user to enter their choice
            cout << "Enter your choice: ";
            cin >> choice;
            cout << endl;
        
            // check if the user entered a number
            while (cin.fail()) 
            {
                // Prompt the user to enter a number
                cout << "Invalid input. Please enter a number: ";
                cin.clear();
                cin.ignore(256, '\n');
                cin >> choice;
            }

            // Check if the user entered a number within the range
            while (choice < 1 || choice > 7) 
            {
                // Prompt the user to enter a number within the range
                cout << "Invalid input. Please enter a number between 1 and 8: ";
                cin >> choice;
            }

                string searchName;
                int nameWidth = 20;
                int categoryWidth = 15;

            switch (choice) 
            {
                case 1:
                    // Add a name
                    // Prompt the user to enter the name
                    
                    cout << "Enter a name: ";
                    cin >> searchName;

                    // Add the name to the array of pointers to Name objects
                    addName(names, numNames, searchName);

                    // Prompt the user to enter the category values
                    for (auto& category : categories) 
                    {
                        // Prompt the user to enter the category value
                        cout << category.first << " for " << names[numNames - 1]->name << ": ";
                        string categoryValue;
                        //clear cin
                        cin.clear();
                        cin.ignore(256, '\n');

                        cin >> categoryValue;

                        // Add the category value to the vector
                        category.second.push_back(categoryValue);
                    }

                    // print endline
                    cout << endl;

                    break;
                
                case 2:
                    // Delete a name
                    // Prompt the user to enter the name
                    cout << "Enter a name: ";
                    cin >> searchName;

                    // Check to see if the name exists
                    if (!nameExists(names, numNames, searchName)) 
                    {
                        // Prompt the user to enter a different name
                        cout << "Name does not exist. Please enter a different name: ";
                        cin >> searchName;
                    }

                    // Delete the name from the array of pointers to Name objects
                    deleteName(names, numNames, searchName);

                    // Delete the category values from the map
                    for (auto& category : categories) 
                    {
                        // Delete the category value from the vector
                        category.second.pop_back();
                    }

                    // print endline
                    cout << endl;

                    break;

                case 3:
                    // Add a category
                    // Prompt the user to enter the category name
                    cout << "Enter category name: ";
                    cin >> searchName;

                    // Check to see if category already exists
                    if (categories.find(searchName) != categories.end()) 
                    {
                        // Prompt the user to enter a different category name
                        cout << "Category already exists. Please enter a different category name: ";
                        cin >> searchName;
                    }

                    // Add the category name to the map
                    categories[searchName] = vector<string>();

                    // Prompt the user to enter the category values
                    for (int i = 0; i < numNames; i++) 
                    {
                        // Prompt the user to enter the category value
                        cout << searchName << " for " << names[i]->name << ": ";
                        string categoryValue;
                        cin >> categoryValue;

                        // Add the category value to the vector
                        categories[searchName].push_back(categoryValue);
                    }

                    // print endline
                    cout << endl;

                    break;
                
                case 4:
                    // Delete category
                    // Prompt the user to enter the category name
                    cout << "Enter category name: ";
                    cin >> searchName;

                    // Check to see if category already exists
                    if (categories.find(searchName) != categories.end()) 
                    {
                        // Delete the category name from the map
                        categories.erase(searchName);

                        // print endline
                        cout << endl;
                    }

                    break;
                    
                case 5:
                    
                    // initalize variables
                     
                    // Print the header row
                    cout << setw(nameWidth) << left << "Name";
                    for (auto& category : categories) 
                    {
                        cout << setw(categoryWidth) << left << category.first;
                    }

                    // prints endline
                    cout << endl;

                    // Print a line of equals under the header row
                    for (int j = 0; j < nameWidth + categoryWidth * categories.size(); j++) 
                    {
                        cout << "=";
                    }

                    // prints endline
                    cout << endl;

                    // Print the data rows
                    for (int i = 0; i < numNames; i++) 
                    {
                        // Print the name
                        cout << setw(nameWidth) << left << names[i]->name;

                        // Print the category values
                        for (auto& category : categories) 
                        {
                            cout << setw(categoryWidth) << left << category.second[i];
                        }

                        // print endline
                        cout << endl;

                        // Print a line of dashes under the row
                        for (int j = 0; j < nameWidth + categoryWidth * categories.size(); j++) 
                        {
                            cout << "-";
                        }

                        // print endlineKe
                        cout << endl;
                    }
                    break;

                case 6:
                    // Allow the user to search for a specific name
                    cout << "Enter a name to search for: ";
                    cin >> searchName;

                    // Search for the name using the find_if function
                    Name* foundName = nullptr;

                    // Search for the name
                    for (int i = 0; i < numNames; i++) 
                    {
                        if (names[i]->name == searchName) 
                        {
                            foundName = names[i];
                            break;
                        }
                    }
                    // Display the name if it was found
                    if (foundName != nullptr) 
                    {
                        cout << "Found " << foundName->name << endl;
                        cout << endl;
                    }
                    else 
                    {
                        cout << "Name not found" << endl;
                        cout << endl;
                    }

                    // Allow the user to search for a specific name
                    int index = findNameIndex(names, numNames, searchName);

                    // Display the name if it was found
                    if (index != -1) 
                    {
                        // print the name
                        cout << "Name: " << names[index]->name << endl;

                        // print the category values
                        for (auto& category : categories) 
                        {
                            cout << category.first << ": " << category.second[index] << endl;
                        }
                    } 
                    else 
                    {
                        cout << "The name " << searchName << " was not found" << endl;
                    }

                    // print endline
                    cout << endl;

                    break;
            }
        }

        // Display a goodbye message
        cout << "Goodbye!" << endl;

        // Free the memory allocated for the Name objects
        for (int i = 0; i < numNames; i++) 
        {
            delete names[i];
        }
        delete[] names;
    }

    // Catch any exceptions thrown by the new operator
    catch (bad_alloc &ex) 
    { 
        // Display an error message and free any memory that was allocated
        cout << "Memory allocation failed: " << ex.what() << endl;

        // Free the memory allocated for the array of pointers to Name objects
        for (int i = 0; i < numNames; i++) 
        {
            delete names[i]; 
        }
        delete[] names; 
    }

    // End program
        // Return SUCCESS
    return 0;
}

// ************************************************************
// 
//                   MAIN FUNCTION
//
// ************************************************************


int main() 
{
    // prompt the user if they want to an intentory or dynamic inventory
    cout << "Would you like to create a static inventory or a dynamic inventory? (1 for static, 2 for dynamic): ";
    int choice;
    cin >> choice;

    // check to see if choice is valid
    while (choice != 1 && choice != 2) 
    {
        // prompt the user to enter a valid choice
        cout << "Please enter a valid choice: ";
        cin >> choice;
    }

    // check if the user wants to create a static inventory
    if (choice == 1) 
    {
        // create a static inventory
        inventory();
    }
    else 
    {
        // create a dynamic inventory
        dynamicStorage();
    }
}
