//
//  ECFlightItinerary.cpp
//  
//
//  Created by Yufeng Wu on 5/11/23.
//

#include "ECFlightItinerary.h"
#include "ECFlight.h"
#include <iostream>
#include <string>
#include <set>

using namespace std;


ECFlightItinerary::ECFlightItinerary() {}

ECFlightItinerary::~ECFlightItinerary() {
    // Clean up if necessary, especially if you're dealing with dynamic memory.
}

int ECFlightItinerary::GetNumSegments() const {
    return segments.size();
}

ECFlight *ECFlightItinerary::GetSegment(int segIndex) const {
    if (segIndex < 0 || segIndex >= segments.size()) {
        throw std::out_of_range("Segment index is out of range.");
    }
    return segments[segIndex];
}

double ECFlightItinerary::GetTimeAllSegments() const {
    if (segments.empty()) return 0.0;

    double departTime = segments.front()->GetDepartureTime();
    double arriveTime = segments.back()->GetArrivalTime();
    return arriveTime - departTime;
}

double ECFlightItinerary::GetFlightTime() const {
    double totalTime = 0.0;
    for (const auto &segment : segments) {
        totalTime += segment->GetArrivalTime() - segment->GetDepartureTime();
    }
    return totalTime;
}

double ECFlightItinerary::GetDepartTime() const {
    if (segments.empty()) return 0.0;
    return segments.front()->GetDepartureTime();
}

double ECFlightItinerary::GetArrivalTime() const {
    if (segments.empty()) return 0.0;
    return segments.back()->GetArrivalTime();
}

double ECFlightItinerary::GetPrice() const {
    double totalCost = 0.0;
    for (const auto &segment : segments) {
        totalCost += (segment->GetArrivalTime() - segment->GetDepartureTime()) * 120.0; // $120 per hour
    }
    return totalCost;
}

void ECFlightItinerary::AddSegment(ECFlight *flight) {
    if (!segments.empty()) {
        auto lastSegment = segments.back();
        // Ensure that the next segment departs after or when the last one arrives
        if (flight->GetDepartureTime() < lastSegment->GetArrivalTime()) {
            throw std::logic_error("New segment departs before the previous segment arrives.");
        }
    }
    segments.push_back(flight);
}

void ECFlightItinerary::removeSegment() {
    if (segments.empty()) {
        throw std::logic_error("No segments to remove.");
    }
    segments.pop_back();
}

#include <sstream>
#include <iomanip>
#include <set>

std::string ECFlightItinerary::Dump() const {
    static std::set<std::string> previousDumps; // Store all previous dumps to check for duplicates

    std::ostringstream ret;
    ret << segments[0]->GetSource();
    for (int i = 0; i < segments.size(); i++) {
        ret << ">" << segments[i]->GetDest();
    }
    
    double timeDouble = GetFlightTime();
    ret << "\nDeparts: " << std::fixed << std::setprecision(1) << GetDepartTime();
    ret << "\n" << std::fixed << std::setprecision(1) << timeDouble << " hours";
    ret << "\n$" << static_cast<int>(GetPrice());

    std::string result = ret.str();
    // Check if this result has already been dumped
    if (!previousDumps.insert(result).second) {
        return ""; // Ignore duplicates by returning empty string
    }
    return result;
}
