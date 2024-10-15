#include "ECTextViewImp.h"
#include "ECConsoleUIView.h"
#include "ECConsoleUITextLabel.h"
#include <iostream>
#include "ECConsoleUIButton.h"
#include "ECConsoleUIListBox.h"
#include "ECConsoleUITextField.h"
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

// cd Project/Part4 && \
// g++ -o TestData TestData.cpp ECAirport.cpp ECAirlineOperation.cpp ECAirlineTicketing.cpp ECAirlineFinancial.cpp ECFlightItinerary.cpp ECAirlineSimulator.cpp ECTextViewImp.cpp ECConsoleUIView.cpp ECConsoleUIListBox.cpp ECConsoleUITextField.cpp ECConsoleUIButton.cpp ECFlight.cpp ECConsoleUITextLabel.cpp debug.cpp -std=c++20 && \
// ./TestData
// g++ -o TestPart4 debug.cpp ECTest.cpp ECAirport.cpp ECAirlineOperation.cpp ECAirlineTicketing.cpp ECAirlineFinancial.cpp ECFlightItinerary.cpp ECAirlineSimulator.cpp ECTextViewImp.cpp ECConsoleUIView.cpp ECConsoleUIListBox.cpp ECConsoleUITextField.cpp ECConsoleUIButton.cpp ECFlight.cpp ECConsoleUITextLabel.cpp -std=c++20

using namespace std;

void LoadDataFromFile(const string& filename, ECAirlineSimulator& sim, ECConsoleUIListBox* src, ECConsoleUIListBox* dest) {
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        if (line.empty() || line[0] == '#') continue; // Skip comments or empty lines
        stringstream ss(line);  // Now valid with the <sstream> included
        int type;
        ss >> type;
        string code, name, destCode;
        double time, cost;
        int length, distance;
        
        switch (type) {
            case 1:  // Airport information
                ss >> code;
                getline(ss, name);  // Read the rest of the line as airport name
                if (!name.empty() && name[0] == ' ')  // Remove any leading space
                    name = name.substr(1);
                sim.AddAirport(name, code);
                // Add airport codes to src and dest
                src->AddChoice(code);
                dest->AddChoice(code);
                break;
            case 2:  // Distance information
                ss >> code >> destCode >> distance;
                sim.SetDistBtwAirports(code, destCode, distance);
                break;
            case 3:  // Flight information
                ss >> code >> destCode >> time >> length >> cost;
                sim.AddFlight(code, destCode, time, length, cost);
                break;
        }
    }
}

static void Test1(ECConsoleUIView &viewTest, ECAirlineSimulator &sim, ECConsoleUIListBox *src, ECConsoleUIListBox *dest) {
    // create title 
    ECConsoleUITextLabel *title = new ECConsoleUITextLabel(25, 1, "Galaxy Airlines Flight Reservation System");
    title->SetHighlight(true);
    viewTest.AddUIItem(title);
    
    // Create a border 
    string horizBar;
    for(int i=0; i<viewTest.GetColNumInView(); ++i) {
        horizBar += '-';
    }

    // bottom and top bar
    ECConsoleUITextLabel *topbar = new ECConsoleUITextLabel(0, 0, horizBar);
    viewTest.AddUIItem(topbar);
    ECConsoleUITextLabel *bottombar = new ECConsoleUITextLabel(0, viewTest.GetRowNumInView()-1, horizBar);
    viewTest.AddUIItem(bottombar);

    // Create src section with label
    ECConsoleUITextLabel *srclabel = new ECConsoleUITextLabel(28, 4, "Origination");
    viewTest.AddUIItem(srclabel);
    viewTest.AddUIItem(src);
    
    // Create des section with label
    ECConsoleUITextLabel *destlabel = new ECConsoleUITextLabel(51, 4, "Destination");
    viewTest.AddUIItem(destlabel);
    viewTest.AddUIItem(dest);

    // Create flights listbox section with label
    ECConsoleUITextLabel *flightstop = new ECConsoleUITextLabel(32, 12, string(25, '-'));
    viewTest.AddUIItem(flightstop);
    ECConsoleUITextLabel *flightslabel = new ECConsoleUITextLabel(35, 13, "Search for Flights");
    viewTest.AddUIItem(flightslabel);
    ECConsoleUITextLabel *flightsbottom = new ECConsoleUITextLabel(32, 14, string(25, '-'));
    viewTest.AddUIItem(flightsbottom);
    ECConsoleUIListBox *flights = new ECConsoleUIListBox(32, 15, 52, 18); // step size change
    for (int x = 0; x<3; x++) flights->AddChoice("");
    viewTest.AddUIItem(flights);

    // create a search button
    ECConsoleUIButton *searchButton = new ECConsoleUIButton(  40,  10,   50,  10, "Search", src, dest, flights, &sim);
    viewTest.AddUIItem(searchButton);

    // Add a text field to input name
    ECConsoleUITextLabel *pl8 = new ECConsoleUITextLabel(34, 20, "Enter Passenger Name:");
    viewTest.AddUIItem(pl8);
    ECConsoleUITextField *pt1 = new ECConsoleUITextField(viewTest.GetView(), 34, 22, 21);
    viewTest.AddUIItem(pt1);
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <data-file>" << endl;
        return 1;
    }
    string filename = argv[1];
    ECAirlineSimulator sim;
    ECTextViewImp wndTest;

    // add a status bar
    wndTest.AddStatusRow("Galaxy Airlines", "For CSE 3150 project demo only", true);
    
    // Create a console UI view
    ECConsoleUIView viewUI(&wndTest);
    
    // Create src and dest list boxes
    ECConsoleUIListBox *src = new ECConsoleUIListBox(32, 6, 47, 8);
    ECConsoleUIListBox *dest = new ECConsoleUIListBox(55, 6, 70, 8);

    // Add a few UI items and dynamically populate src and dest choices
    Test1(viewUI, sim, src, dest);
    
    // Load data from file and populate src and dest choices
    LoadDataFromFile(filename, sim, src, dest);

    // Display the UI
    viewUI.Refresh();
    
    // Show the window
    try {
        wndTest.Show();
    }
    catch(std::string ex)
    {
        cout << "Exception: " << ex << endl;
    }
    
    return 0;
}
