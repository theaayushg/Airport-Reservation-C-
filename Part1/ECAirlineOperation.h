//
//  ECAirlineOperation.h
//  
//
//  Created by Yufeng Wu on 5/11/23.
//  About operation of an airline: especially flights management

#ifndef ECAirlineOperation_h
#define ECAirlineOperation_h

// put your code about airline operation here...
#include "ECFlight.h"
#include <vector>
#include <string>

class ECAirlineOperation {
public:
    ECAirlineOperation();
    ~ECAirlineOperation();

    void AddFlight(ECFlight* flight);
    const std::vector<ECFlight*>& GetFlights() const;

private:
    std::vector<ECFlight*> flights;
};

#endif
