//
//  ECAirlineSimulator.hpp
//  
//
//  Created by Yufeng Wu on 5/17/23.
//  Simulate airline activities: booking, flights, etc
#include "ECPassenger.h"

#ifndef ECAirlineSimulator_h
#define ECAirlineSimulator_h

#include <string>
#include <set>
#include <vector>

class ECAirlineOperation;
class ECAirlineTicketing;
class ECAirlineFinancial;
class ECFlightItinerary;

//****************************************************************************
// Airline simulator

class ECAirlineSimulator
{
public:
    ECAirlineSimulator();
    virtual ~ECAirlineSimulator();
    
    // *****************************************************
    // Configuration
    
    // Read in airport info
    void ReadAirportInfo(const std::string &fileAirports);
    
    // Read in flight info
    void ReadFlightInfo(const std::string &fileFlights);
    
    // Read in passenger info: where to go
    void ReadPassengerInfo(const std::string &filePassengers);
    
    // Adding airport with name and IATA code
    void AddAirport(const std::string &name, const std::string &code);
    
    // Setup distaince between airport; note distance is symmetric: the distance from dest to src is the same as from src to dest
    void SetDistBtwAirports(const std::string &srcAirport, const std::string &destAirport, int dist);
    
    // Adding flights: src airport, dest airport, depart time, max number of passenger, operating cost
    void AddFlight(const std::string &srcAirport, const std::string &destAirport, double tmDepart, int maxPassengers, double costOperate );
    
    // Called to indicate no more flights to add
    void DoneFlightAdding();
    
    // get all airport codes in record
    void GetAllAirportCode(std::set<std::string> &setAirports) const;

    void AddPassengerBudget(const std::string &srcAirport, const std::string &destAirport, double budget);
    void AddPassengerBusiness(const std::string &srcAirport, const std::string &destAirport, double tmArrivalLatest);
    void AddPassengerComfort(const std::string &srcAirport, const std::string &destAirport, double tmEarliestDepart, double maxFlightTime, int maxSegments);
  

    // *****************************************************
    // Flight search
    
    // Searcch for flights; return all flights in listItineraries that go from src to dest
    void SearchForFlights(const std::string &src, const std::string &dest, std::vector<ECFlightItinerary> &listItineraries ) const;
    
    // Search preference: if no preference (this is the default), then all itineraries treated equivalent; if
    // Clear preference (i.e., no preference)
    void ClearPreference();
    
    // Add preference by invoking the following functions
    // Note: you can add multiple preference; the first added preference is used first; the later added preference as tie-breakers (the preference added earlier has precedence)
    // Prefer low price
    void PreferLowPrice();
    
    // Prefer flights with smaller flight time
    void PreferShortTime();
    
    // Prefer flights with smaller number of segments
    void PreferSmallestSegments();
    
    // Prefer early arrival
    void PreferEarlyArrival();
    
    // *****************************************************
    // Flight booking and optimization
    // Book flights for all unbooked passengers
    // In the order of passenger adding. That is, the first added passenger is to be booked the first
    void Book();
    
    // Access airlines
    ECAirlineFinancial *GetAirlineFin() { return pAirlineFin; }
    ECAirlineOperation *GetAirlineOp() { return pAirlineOp; }
    ECAirlineTicketing *GetAirlineTicketing() { return pAirlineTicket; }
    
    
private:
    // initialize
    void Init();
    
    // key data member
    ECAirlineOperation *pAirlineOp;
    ECAirlineFinancial *pAirlineFin;
    ECAirlineTicketing *pAirlineTicket;

    std::vector<ECPassengerBudget*> budgetPassengers;
    std::vector<ECPassengerBusiness*> businessPassengers;
    std::vector<ECPassengerComfort*> comfortPassengers;
};


#endif /* ECAirlineSimulator_h */
