# Airline Reservation System | C++ & WSL

## Overview
This project is a comprehensive **Airline Reservation System** built using **C++** and running on **Windows Subsystem for Linux (WSL)**. The system offers both backend and frontend functionalities, designed to handle airport and flight data, as well as user interactions for booking and searching flights.

## Features
- **Airport Information Management**: Users can search, add, and manage details about various airports.
- **Flight Data Handling**: The system manages flight details such as available flights, schedules, and capacity.
- **User-Friendly Interface**: A user-friendly graphical interface is provided, utilizing list boxes for easy airport selection and itinerary display.
- **Flight Booking & Searching**: Users can search for flights and book their itineraries within the application.
- **Passenger Information Management**: Keeps track of passenger details and associates them with their bookings.
- **Itinerary Saving/Loading**: Itineraries can be saved for future reference and reloaded as needed.
- **Optimized Performance**: The application is optimized for smooth operation, even when handling large sets of data.

## System Requirements
- **Operating System**: Linux (via WSL on Windows) or any Unix-based system
- **C++ Compiler**: Compatible with any modern C++ compiler (e.g., GCC)
- **WSL**: Windows Subsystem for Linux (for running on Windows)

## Installation
1. Clone the repository:
   git clone https://github.com/theaayushg/Airport-Reservation-C-.git
2. Navigate to the Part4 folder:
   cd Part4
3. Compile the project using the provided command:
   g++ -o TestData2 TestData2.cpp ECAirport.cpp ECAirlineOperation.cpp ECAirlineTicketing.cpp ECAirlineFinancial.cpp ECFlightItinerary.cpp ECAirlineSimulator.cpp ECTextViewImp.cpp ECConsoleUIView.cpp ECConsoleUIListBox.cpp ECConsoleUITextField.cpp ECConsoleUIButton.cpp ECFlight.cpp ECConsoleUITextLabel.cpp -std=c++20
4. Run the application:
   ./TestData2 data-file.txt

This `README.md` gives a clear overview of the project, how to set it up, and use it. Let me know if you’d like to adjust or add anything!
