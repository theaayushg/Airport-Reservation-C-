//
//  ECPassenger.cpp
//  
//
//  Created by Yufeng Wu on 5/15/23.
//

#include "ECPassenger.h"
#include "ECAirlineTicketing.h"
#include "ECAirlineFinancial.h"
#include "ECFlight.h"

#include <vector>
#include <iostream>
using namespace std;

// Constructor implementations
ECPassengerBudget::ECPassengerBudget(const std::string &srcAirportIn, const std::string &destAirportIn, double budgetIn)
: ECPassenger(srcAirportIn, destAirportIn), budget(budgetIn) {}

ECPassengerBusiness::ECPassengerBusiness(const std::string &srcAirportIn, const std::string &destAirportIn, double tmArrivalLatestIn)
: ECPassenger(srcAirportIn, destAirportIn), tmArrivalLatest(tmArrivalLatestIn) {}

ECPassengerComfort::ECPassengerComfort(const std::string &srcAirportIn, const std::string &destAirportIn, double tmEarliestDepartIn, double maxFlightTimeIn, int maxSegmentsIn)
: ECPassenger(srcAirportIn, destAirportIn), tmEarliestDepart(tmEarliestDepartIn), maxFlightTime(maxFlightTimeIn), maxSegments(maxSegmentsIn) {}

// Book method override implementations
bool ECPassengerBudget::Book(ECAirlineTicketing &airlineTicketing) {
    // Implement booking logic based on budget
    return true;  // Placeholder for your logic
}

bool ECPassengerBusiness::Book(ECAirlineTicketing &airlineTicketing) {
    // Implement booking logic based on arrival deadline
    return true;  // Placeholder for your logic
}

bool ECPassengerComfort::Book(ECAirlineTicketing &airlineTicketing) {
    // Implement booking logic based on comfort preferences
    return true;  // Placeholder for your logic
}
