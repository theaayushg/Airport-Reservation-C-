//
//  ECAirlineOperation.cpp
//  
//
//  Created by Yufeng Wu on 5/11/23.
//

#include "ECAirlineOperation.h"
#include "ECFlightItinerary.h"
#include "ECAirlineFinancial.h"

#include <iostream>
#include <string>
using namespace std;

ECAirlineOperation::ECAirlineOperation() {}

ECAirlineOperation::~ECAirlineOperation() {
    // Clean up flights if necessary
    for (auto* flight : flights) {
        delete flight;
    }
}

void ECAirlineOperation::AddFlight(ECFlight* flight) {
    flights.push_back(flight);
}

const std::vector<ECFlight*>& ECAirlineOperation::GetFlights() const {
    return flights;
}