//
//  ECAirlineSimulator.cpp
//  
//
//  Created by Yufeng Wu on 5/17/23.
//

#include "ECAirlineSimulator.h"
#include "ECAirlineOperation.h"
#include "ECAirlineTicketing.h"
#include "ECAirlineFinancial.h"
#include "ECAirport.h"
#include "ECFlight.h"

#include <iostream>
using namespace std;

ECAirlineSimulator::ECAirlineSimulator() {
    pAirlineTicket = new ECAirlineTicketing();
    // pAirlineOp = new ECAirlineOperation();
    // pAirlineFin = new ECAirlineFinancial();
}

ECAirlineSimulator::~ECAirlineSimulator() {
    //delete pAirlineOp;
    delete pAirlineTicket;
    //delete pAirlineFin;
}

void ECAirlineSimulator::AddAirport(const std::string &name, const std::string &code) {
    ECAirportInfo* instance = ECAirportInfo::GetInstance();
    instance->CreateAirport(name, code);
}


void ECAirlineSimulator::SetDistBtwAirports(const std::string &srcAirport, const std::string &destAirport, int dist) {
    ECAirportInfo* instance = ECAirportInfo::GetInstance();
    instance->SetDistanceBtw(srcAirport, destAirport, dist);
}

void ECAirlineSimulator::AddFlight(const std::string &srcAirport, const std::string &destAirport, double tmDepart, int maxPassengers, double costOperate) {
    pAirlineTicket->AddFlight(srcAirport, destAirport, tmDepart, maxPassengers);
}

void ECAirlineSimulator::DoneFlightAdding() {
    int x = 69;
}

void ECAirlineSimulator::SearchForFlights(const std::string &src, const std::string &dest, std::vector<ECFlightItinerary> &listItineraries) const {
    listItineraries.clear();
    pAirlineTicket->SearchFlights(src, dest, listItineraries);
}
