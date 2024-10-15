//
//  ECFlight.cpp
//  
//
//  Created by Yufeng Wu on 5/11/23.
//

#include "ECFlight.h"
#include "ECAirport.h"

#include <iostream>
using namespace std;
#include <iostream>
#include <stdexcept>

using namespace std;

ECFlight::ECFlight(const std::string &srcIn, const std::string &destIn, double tmDepartIn, int maxPassengersIn)
    : source(srcIn), destination(destIn), departureTime(tmDepartIn), maxPassengers(maxPassengersIn) {}

ECFlight::~ECFlight() {}

double ECFlight::GetDepartureTime() const {
    return departureTime;
}

double ECFlight::GetArrivalTime() const {
    // Fetch the distance between the source and destination airports from ECAirportInfo
    ECAirportInfo* instance = ECAirportInfo::GetInstance();
    int distance = instance->GetDistanceBetween(source, destination);
    if (distance < 0) {
        throw std::invalid_argument("Invalid distance or airports not found");
    }

    // Calculate the flight time based on the distance and a constant speed (500 miles per hour)
    double flightTime = static_cast<double>(distance) / 500.0; // 500 miles per hour

    // Calculate and return the arrival time by adding the flight time to the departure time
    return departureTime + flightTime;
}

void ECFlight::SetMaxNumPassengers(int m) {
    maxPassengers = m;
}

std::string ECFlight::GetSource() const {
    return source;
}

std::string ECFlight::GetDest() const {
    return destination;
}
