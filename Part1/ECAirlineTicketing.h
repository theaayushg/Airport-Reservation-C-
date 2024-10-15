//
//  ECAirlineTicketing.h
//  
//
//  Created by Yufeng Wu on 5/12/23.
//
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <set>

#include "ECFlight.h"
#include "ECFlightItinerary.h"

#ifndef ECAirlineTicketing_h
#define ECAirlineTicketing_h

// ****************************************************************************
// Airline ticketing: search for flights, issue tickets, etc
class ECAirlineTicketing {
public:
    ECAirlineTicketing();
    virtual ~ECAirlineTicketing();

    void AddFlight(const std::string &src, const std::string &dest, double tmDepart, int maxPassengers);
    void SearchFlights(const std::string &src, const std::string &dest, std::vector<ECFlightItinerary> &itineraries);

private:
    std::map<std::string, std::vector<ECFlight*>> flightsFromAirport; // Maps an airport to outgoing flights

    void DepthFirstSearch(const std::string &current, const std::string &destination, 
                          std::vector<ECFlight*> &currentPath, std::vector<ECFlightItinerary> &itineraries,
                          std::set<std::string> &visited,
                          double time);
};

#endif /* ECAirlineTicketing_h */
