// Test code for console UI
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

using namespace  std;

void SetupSimulator(ECAirlineSimulator& sim) {
    sim.AddAirport("Chicago", "ORD");
    sim.AddAirport("Houston", "IAH");
    sim.AddAirport("San Francisco", "SFO");
    sim.AddAirport("New York (Newwark, NJ)", "EWR");

    sim.SetDistBtwAirports("ORD", "SFO", 2000);
    sim.SetDistBtwAirports("ORD", "EWR", 1200);
    sim.SetDistBtwAirports("IAH", "SFO", 1800);
    sim.SetDistBtwAirports("IAH", "EWR", 1500);

    sim.AddFlight("EWR", "ORD", 7.0, 5, 2000);
    sim.AddFlight("EWR", "ORD", 14.0, 5, 2000);
    sim.AddFlight("ORD", "SFO", 11.0, 10, 3000);
    sim.AddFlight("ORD", "SFO", 16.0, 10, 3000);
    sim.AddFlight("EWR", "IAH", 8.5, 5, 2200);
    sim.AddFlight("EWR", "IAH", 13.0, 5, 2200);
    sim.AddFlight("IAH", "SFO", 12.0, 10, 2800);
    sim.AddFlight("IAH", "SFO", 18.0, 10, 2800);
}

// construct a simple UI
static void Test1(ECConsoleUIView &viewTest,ECAirlineSimulator &sim)
{
    // create title 
    ECConsoleUITextLabel *title = new ECConsoleUITextLabel(22, 1, "Gupta Airlines");
    title->SetHighlight(true);
    viewTest.AddUIItem(title);
    
    // Create a border 
    string horizBar;
    for(int i=0; i<viewTest.GetColNumInView(); ++i)
    {
        horizBar += '-';
    }

    // bottom and top bar
    ECConsoleUITextLabel *topbar = new ECConsoleUITextLabel(0, 0, horizBar);
    viewTest.AddUIItem(topbar);
    ECConsoleUITextLabel *bottombar = new ECConsoleUITextLabel(0, viewTest.GetRowNumInView()-1, horizBar);
    viewTest.AddUIItem(bottombar);

     
    // Create flights listbox section with label
    ECConsoleUITextLabel *flightstop = new ECConsoleUITextLabel(20, 4, string(19, '-'));
    viewTest.AddUIItem(flightstop);
    ECConsoleUITextLabel *flightslabel = new ECConsoleUITextLabel(20, 5, "|Available Flights|");
    viewTest.AddUIItem(flightslabel);
    ECConsoleUITextLabel *flightsbottom = new ECConsoleUITextLabel(20, 6, string(19, '-'));
    viewTest.AddUIItem(flightsbottom);
   // ECConsoleUIListBox *flights = new ECConsoleUIListBox(25, 7, 45, 9);
    ECConsoleUIListBox *flights = new ECConsoleUIListBox(20, 7, 40, 9); // step size change
    for (int x = 0; x<3; x++) flights->AddChoice("");
    viewTest.AddUIItem(flights);
    
    // Create src section with label
    ECConsoleUITextLabel *srctop = new ECConsoleUITextLabel(14, 11, "-----");
    viewTest.AddUIItem(srctop);
    ECConsoleUITextLabel *srclabel = new ECConsoleUITextLabel(14, 12, "|SRC|");
    viewTest.AddUIItem(srclabel);
    ECConsoleUITextLabel *srcbottom = new ECConsoleUITextLabel(14, 13, "-----");
    viewTest.AddUIItem(srcbottom);
    ECConsoleUIListBox *src = new ECConsoleUIListBox(15, 14, 30, 16 );
    src->AddChoice("ORD");
    src->AddChoice("IAH");
    src->AddChoice("SFO");
    src->AddChoice("EWR");
    src->Choose(0);
    viewTest.AddUIItem(src);
    
    // Create des section with label
    ECConsoleUITextLabel *desttop = new ECConsoleUITextLabel(39, 11, "-----");
    viewTest.AddUIItem(desttop);
    ECConsoleUITextLabel *destlabel = new ECConsoleUITextLabel(39, 12, "|DES|");
    viewTest.AddUIItem(destlabel);
    ECConsoleUITextLabel *destbottom = new ECConsoleUITextLabel(39, 13, "-----");
    viewTest.AddUIItem(destbottom);
    ECConsoleUIListBox *dest = new ECConsoleUIListBox(40, 14, 55, 16 );
    dest->AddChoice("ORD");
    dest->AddChoice("IAH");
    dest->AddChoice("SFO");
    dest->AddChoice("EWR");
    dest->Choose(0);
    viewTest.AddUIItem(dest);
    
    // Add a text field to input name
    ECConsoleUITextLabel *pl8 = new ECConsoleUITextLabel(15, 19, "Enter Passenger Name:");
    viewTest.AddUIItem(pl8);
    ECConsoleUITextField *pt1 = new ECConsoleUITextField(viewTest.GetView(), 15, 21, 20);
    viewTest.AddUIItem(pt1);

    // create a serach button
    ECConsoleUIButton *searchButton = new ECConsoleUIButton(  25,  24,   35,  24, "Search", src, dest, flights, &sim);
    viewTest.AddUIItem(searchButton);

}


int main(int argc, char *argv[])
{
    ECAirlineSimulator sim;
    SetupSimulator(sim);

    ECTextViewImp wndTest;

    // add a status bar
    wndTest.AddStatusRow("Galaxy Airlines", "For CSE 3150 project demo only", true);
    
    // Create a console UI view
    ECConsoleUIView viewUI(&wndTest);
    
    // Add a few UI items
    Test1(viewUI, sim);
    // Display it
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