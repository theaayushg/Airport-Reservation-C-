//
//  ECConsoleUIButton.cpp
//  
//
//  Created by Yufeng Wu on 3/6/24.
//

#include "ECConsoleUIButton.h"
#include "ECConsoleUIItem.h"
#include <string>
#include <vector>
#include "ECConsoleUIListBox.h"
#include "ECAirlineSimulator.h"
#include "ECFlight.h"
#include "ECFlightItinerary.h"
#include <sstream>

//*****************************************************************************
// Console UI button: 

using namespace std;

// specifiy the portion of the view for this list box
ECConsoleUIButton :: ECConsoleUIButton(int xUL, int yUL, int xLR, int yLR, 
const std::string &strButIn, ECConsoleUIListBox *source, ECConsoleUIListBox *destination, ECConsoleUIListBox *flights, ECAirlineSimulator *sim) : ECConsoleUIItem(xUL, yUL, xLR, yLR), strButton(strButIn), source(source), destination(destination), flights(flights), sim(sim){}


// Get displayed text at a specific row
// Text is relative to the item portion (i.e., relative to (xLR, yLR))
std::string ECConsoleUIButton :: GetTextAtRow(int r) const
{
    // there is only one line
    std::string str;
    int rconv = r - GetYUL();

    if( rconv <0 || /*rconv >= 1 ||*/ rconv >= GetHeight() )
    {
        return str;
    }

    // add a row of '----' right above/below
    if( rconv == 0 || rconv == GetHeight()-1 )
    {
        str += '+';
        for( int i=1 ; i<GetWidth() - 1; ++i)
        {
            str += '-';
        }
        str += '+';
    }
    else
    {
        // begin with a '|'
        //str += '|';

        // align to the center
        if( strButton.size() < GetWidth())
        {
            str += '|';
            for(int i=1; i < (GetWidth()- strButton.size())/2; ++i )
            {
                str += ' ';
            }
        }

        str += strButton;
        for(int i=1; i < (GetWidth()- strButton.size())/2; ++i )
            {
                str += ' ';
            }
            str += '|';

        // end with a '|'
        //str += '|';
    }

    // ensure the str is not too long
    str = str.substr(0, GetWidth());
    return str;
}

// Get highlighted part (if any); return the row with highlight
// if one, return -1; also store the highlightd portion (yLeft, yRight) of this row
// Assume: at most a single row with highlighted part
int ECConsoleUIButton :: GetHighlightPosition(int &xLeft, int &xRight) const
{
    return -1;
}

// Handle enter key
void ECConsoleUIButton::HdlKeyEnter() {

    std::vector<ECFlightItinerary> listItineraries;
    std::string src = source->GRow(source->GetChoice());
    std::string dest = destination->GRow(destination->GetChoice());
    sim->SearchForFlights(src, dest, listItineraries);

    if (flights->Size() > 0)
    {
        flights->Delete();
    }

    if (src == dest) {
        flights->ClearChoices(); // Clear existing choices
        flights->AddChoice("Same Flights.");
        flights->AddChoice("Same Flights.");
        flights->AddChoice("Same Flights.");
        flights->AddChoice("Same Flights.");

        flights->Choose(0); // Choose the "No Flights." option
        flights->HdlKeyUp(); // Handle key up to ensure correct display
        return;
    }

    flights->ClearChoices();

    std::set<std::string> seenItineraries;
    int displayCount = 1;
    if (!listItineraries.empty()) {
        for (int i = 0; i < listItineraries.size(); i++) {
            std::string itineraryStr = listItineraries[i].Dump();
            if (!itineraryStr.empty() && seenItineraries.insert(itineraryStr).second) {
                std::istringstream iss(itineraryStr);
                std::vector<std::string> tempLines; // Temporarily hold lines to add
                string line;
                while (std::getline(iss, line, '\n')) {
                    tempLines.push_back(line); // Collect all lines first
                }
                for (const auto& tempLine : tempLines) {
                    std::string choiceText = tempLine;
                    if (!choiceText.empty()) {
                        choiceText = to_string(displayCount) + ": " + choiceText;
                        flights->AddChoice(choiceText);
                    }
                }

                displayCount++; // Increment the display count for the next itinerary
            }
        }
    } else {
        flights->AddChoice("No Flights.");
        flights->AddChoice("No Flights.");
        flights->AddChoice("No Flights.");
        flights->AddChoice("No Flights.");
    }

    flights->Choose(0);
    flights->HdlKeyUp();
}
