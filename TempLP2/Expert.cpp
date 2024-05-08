#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Flight {
public:
    string id;
    string departure;
    string destination;
    string dtime;
    
    Flight(string id, string departure, string destination, string dtime) {
        this->id = id;
        this->departure = departure;
        this->destination = destination;
        this->dtime = dtime;
    }

    bool overlap(Flight& other) {
        return departure == other.departure && dtime == other.dtime;
    }
    
    void display() {
        cout << "Flight: " << id << ", Departure: " << departure << ", Destination: " << destination << ", Departure-Time: " << dtime << endl;
    }
};

class Airline {
public:
    vector<Flight> flights;

    bool isOverlapping(Flight& newFlight) {
        for (Flight& f : flights) {
            if (f.overlap(newFlight)) {
                return true;
            }
        }
        return false;
    }
    
    string adjustTime(string dtime, int frac) {
        int hour = stoi(dtime.substr(0, 2));
        int mins = stoi(dtime.substr(3));
        hour = (hour + frac) % 24;
        if (hour < 0) hour += 24;
        return (hour < 10 ? "0" : "") + to_string(hour) + ":" + (mins < 10 ? "0" : "") + to_string(mins);
    }
    
    bool alreadyExists(Flight& newFlight) {
        for (Flight& f : flights) {
            if (f.id == newFlight.id) {
                return true;
            }
        }
        return false;
    }
    
    void addFlight(Flight& newFlight) {
        if (alreadyExists(newFlight)) {
            cout << "Flight number already exists.\nPlease choose another flight\n"; 
        } else if (!isOverlapping(newFlight)) {
            flights.push_back(newFlight);
            cout << "Flight added successfully!\n";
        } else {
            cout << "Error: Flights are overlapped\n";
            cout << "Please choose any of the following options:\n";
            cout << "1. Add flight 1 hour after that is " << adjustTime(newFlight.dtime, 1) <<"\n";
            cout << "2. Add flight 1 hour before that is " << adjustTime(newFlight.dtime, -1) <<"\n";
            cout << "3. Cancel flight\n";
            
            int choice; 
            cout << "Enter choice: "; cin >> choice;
            if (choice == 1 || choice == 2) {
                int frac = (choice == 1) ? 1 : -1;
                Flight temp(newFlight.id, newFlight.departure, newFlight.destination, adjustTime(newFlight.dtime, frac));
                addFlight(temp);
                cout << "New flight added successfully!\n";
            } else {
                cout << "Flight cancelled!\n";
            }
        }
    }
    
    void removeFlight(string id) {
        auto it = find_if(flights.begin(), flights.end(), [&id](Flight& flight) {
            return flight.id == id;
        });
        if (it != flights.end()) {
            flights.erase(it);
            cout << "Flight removed successfully!\n";
        } else {
            cout << "Flight does not exist\n";
        }
    }
    
    void showFlightsByDeparture(string dept) {
        bool found = false;
        for (Flight& f : flights) {
            if (f.departure == dept) {
                f.display();
                found = true;
            }
        }
        if (!found) {
            cout << "No flights exist for this departure\n";
        }
    }
    
    void sortFlightsByDepartureTime() {
        if (flights.empty()) {
            cout << "Currently no flights to display\n";
        } else {
            vector<Flight> temp = flights;
            sort(temp.begin(), temp.end(), [](Flight& a, Flight& b) {
                return a.dtime < b.dtime;
            });
            for (Flight& f : temp) {
                f.display();
            }
        }
    }
    
    void displayFlights() {
        if (flights.empty()) {
            cout << "No flights scheduled.\n";
        } else {
            cout << "Scheduled Flights:\n";
            for (Flight& flight : flights) {
                flight.display();
            }
        }
    }
};

int main() {
    Airline system;
    int choice;

    do {
        cout << "\nAirline Scheduling System\n";
        cout << "1. Add Flight\n";
        cout << "2. Remove Flight\n";
        cout << "3. View Flights\n";
        cout << "4. Search Flights by Departure City\n";
        cout << "5. Display Flights Sorted by Departure Time\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string number, dep, dest, time;
                cout << "Enter flight number: ";
                cin >> number;
                cout << "Enter departure city: ";
                cin >> dep;
                cout << "Enter destination city: ";
                cin >> dest;
                cout << "Enter departure time (HH:MM): ";
                cin >> time;
                Flight newFlight(number, dep, dest, time);
                system.addFlight(newFlight);
                break;
            }
            case 2: {
                string number;
                cout << "Enter flight number to remove: ";
                cin >> number;
                system.removeFlight(number);
                break;
            }
            case 3:
                system.displayFlights();
                break;
            case 4: {
                string depCity;
                cout << "Enter departure city to search for flights: ";
                cin >> depCity;
                system.showFlightsByDeparture(depCity);
                break;
            }
            case 5:
                system.sortFlightsByDepartureTime();
                break;
            case 6:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 6);

    return 0;
}