// Liliana Jimenez Gonzalez
// 12/15/2024
// Corner Grocer Inventory Tracker

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <iomanip>
#include <limits>

using namespace std;

// Class to handle item frequency operations
class ItemTracker {
private:
    map<string, int> itemFrequency;

public:
    // Constructor to read data from the file and populate the map
    ItemTracker(const string& filename) {
        ReadInputFile(filename);
        WriteFrequencyFile("frequency.dat");
    }

    // Function to read the input file and populate the item frequency map
    void ReadInputFile(const string& filename) {
        ifstream infile(filename);
        string item;
        if (infile.is_open()) {
            while (infile >> item) {
                itemFrequency[item]++;
            }
            infile.close();
        }
        else {
            cout << "Error: Unable to open input file." << endl;
        }
    }

    // Function to write the frequency data to frequency.dat
    void WriteFrequencyFile(const string& filename) {
        ofstream outfile(filename);
        if (outfile.is_open()) {
            for (const auto& pair : itemFrequency) {
                outfile << pair.first << " " << pair.second << endl;
            }
            outfile.close();
        }
        else {
            cout << "Error: Unable to write to frequency file." << endl;
        }
    }

    // Function for Menu Option 1: Get frequency of a specific item
    void GetItemFrequency(const string& item) {
        auto it = itemFrequency.find(item);
        if (it != itemFrequency.end()) {
            cout << item << " was purchased " << it->second << " times." << endl;
        }
        else {
            cout << item << " was not purchased today." << endl;
        }
    }

    // Function for Menu Option 2: Print all items and their frequencies
    void PrintAllFrequencies() {
        cout << setw(15) << left << "Item" << "Frequency" << endl;
        cout << "---------------------------" << endl;
        for (const auto& pair : itemFrequency) {
            cout << setw(15) << left << pair.first << pair.second << endl;
        }
    }

    // Function for Menu Option 3: Print histogram of item frequencies
    void PrintHistogram() {
        cout << "Item Frequency Histogram" << endl;
        cout << "---------------------------" << endl;
        for (const auto& pair : itemFrequency) {
            cout << setw(15) << left << pair.first;
            for (int i = 0; i < pair.second; ++i) {
                cout << "*";
            }
            cout << endl;
        }
    }
};

// Function to display the menu
void DisplayMenu() {
    cout << "\nCorner Grocer Inventory Tracking" << endl;
    cout << "---------------------------------" << endl;
    cout << "1. Search for an item" << endl;
    cout << "2. Display all items purchased" << endl;
    cout << "3. Display histogram of items purchased" << endl;
    cout << "4. Exit" << endl;
    cout << "Please enter your choice (1-4): ";
}

// Main function
int main() {
    ItemTracker tracker("CS210_Project_Three_Input_File.txt");
    int choice;
    string item;

    do {
        DisplayMenu();
        cin >> choice;

        // Input validation
        while (cin.fail() || choice < 1 || choice > 4) {
            cin.clear(); // Clear error flags
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "Invalid input. Please enter a number between 1 and 4: ";
            cin >> choice;
        }

        switch (choice) {
        case 1:
            cout << "Enter the item name: ";
            cin >> item;
            tracker.GetItemFrequency(item);
            break;
        case 2:
            tracker.PrintAllFrequencies();
            break;
        case 3:
            tracker.PrintHistogram();
            break;
        case 4:
            cout << "Exiting program. Goodbye!" << endl;
            break;
        default:
            // This case should never be reached due to input validation
            break;
        }
    } while (choice != 4);

    return 0;
}