//
//  ECAirport.cpp
//  
//
//  Created by Yufeng Wu on 5/11/23.
//

#include "ECAirport.h"
#include <iostream>
#include <stdexcept>

ECAirportInfo* ECAirportInfo::instance = nullptr;

ECAirportInfo* ECAirportInfo::GetInstance() {
    if (instance == nullptr) {
        instance = new ECAirportInfo();
    }
    return instance;
}

ECAirport::ECAirport() : name(""), code(""), operating(false) {}

ECAirport::ECAirport(const std::string &nameAP, const std::string &codeIATA) 
    : name(nameAP), code(codeIATA), operating(true) {}

void ECAirportInfo::CreateAirport(const std::string &name, const std::string &code) {
    airports[code] = ECAirport(name, code);
}

ECAirport &ECAirportInfo::GetAirport(const std::string &code) const {
    auto it = airports.find(code);
    if (it != airports.end()) {
        return it->second;
    }
    throw std::runtime_error("Airport not found");
}

void ECAirportInfo::SetDistanceBtw(const std::string &ap1Code, const std::string &ap2Code, int dist) {
    distanceMap[std::make_pair(ap1Code, ap2Code)] = dist;
    distanceMap[std::make_pair(ap2Code, ap1Code)] = dist;
}

int ECAirportInfo::GetDistanceBetween(const std::string &ap1Code, const std::string &ap2Code) const {
    auto key = std::make_pair(ap1Code, ap2Code);
    auto it = distanceMap.find(key);
    if (it != distanceMap.end()) {
        return it->second;
    }
    throw std::runtime_error("Distance not found");
}
