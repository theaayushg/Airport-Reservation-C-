//
//  ECAirlineTicketing.cpp
//  
//
//  Created by Yufeng Wu on 5/12/23.
//

#include "ECAirlineTicketing.h"

#include "ECFlight.h"
#include "ECFlightItinerary.h"
#include <iostream>
#include <set>

ECAirlineTicketing::ECAirlineTicketing() {}

ECAirlineTicketing::~ECAirlineTicketing() {
    // Clean up dynamically allocated flights if owned by this class
}

void ECAirlineTicketing::AddFlight(const std::string &src, const std::string &dest, double tmDepart, int maxPassengers) {
    flightsFromAirport[src].push_back(new ECFlight(src, dest, tmDepart, maxPassengers));
}

void ECAirlineTicketing::SearchFlights(const std::string &src, const std::string &dest, std::vector<ECFlightItinerary> &itineraries) {
    std::vector<ECFlight*> currentPath;
    std::set<std::string> visited;
    visited.insert(src);
    DepthFirstSearch(src, dest, currentPath, itineraries, visited,  0.0);
}

void ECAirlineTicketing::DepthFirstSearch(const std::string &current, const std::string &destination, std::vector<ECFlight*> &currentPath, std::vector<ECFlightItinerary> &itineraries, std::set<std::string> &visited, double lastArrivalTime) {
    if (current == destination) {
        ECFlightItinerary itinerary;
        for (ECFlight* flight : currentPath) {
            itinerary.AddSegment(flight);
        }
        itineraries.push_back(itinerary);
        return;
    }

    auto flights = flightsFromAirport.find(current);
    if (flights == flightsFromAirport.end()) return;  // No outgoing flights from the current airport

    for (ECFlight* flight : flights->second) {
        if (flight->GetDepartureTime() >= lastArrivalTime && visited.count(flight->GetDest()) == 0) {
            visited.insert(flight->GetDest());
            currentPath.push_back(flight);
            DepthFirstSearch(flight->GetDest(), destination, currentPath, itineraries, visited, flight->GetArrivalTime());
            currentPath.pop_back();
            visited.erase(flight->GetDest());  // Allow revisiting for other paths
        }
    }
}