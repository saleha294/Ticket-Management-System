#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstdlib>  // For system("cls") and system("clear")
using namespace std;

class TicketReservation {
private:
    int ids[100];
    string names[100];
    string dates[100];
    string destinations[100];
    string travelClasses[100];
    double prices[100];
    string statuses[100];
    int ticketCount;

public:
    void initialize() {
        ticketCount = 0;
    }

    void bookTicket() {
        if (ticketCount >= 100) {
            cout << "Maximum ticket limit reached!" << endl;
            return;
        }

        int id = ticketCount + 1;
        string name, date, destination, travelClass;
        double price;

        cout << "Enter passenger name: ";
        cin.ignore();
        getline(cin, name);

        cout << "Enter travel date (DD/MM/YYYY): ";
        cin >> date;

        cout << "Enter destination: ";
        cin.ignore();
        getline(cin, destination);

        do {
            cout << "Enter travel class (Economy/Business/Firstclass): ";
            cin >> travelClass;
            if (travelClass != "Economy" && travelClass != "Business" && travelClass != "Firstclass") {
                cout << "Invalid travel class. Please enter Economy, Business, or Firstclass." << endl;
            }
        } while (travelClass != "Economy" && travelClass != "Business" && travelClass != "Firstclass");

        price = calculatePrice(destination, travelClass);
        string status = "Confirmed";

        ids[ticketCount] = id;
        names[ticketCount] = name;
        dates[ticketCount] = date;
        destinations[ticketCount] = destination;
        travelClasses[ticketCount] = travelClass;
        prices[ticketCount] = price;
        statuses[ticketCount] = status;
        ticketCount++;

        cout << "Ticket booked successfully! Your ticket ID is: " << id << endl;
        cout << "Total Price: Rs" << fixed << setprecision(2) << price << endl;

        saveTicketsToFile();
        waitForKeyPress();
    }

    void viewTickets() {
        if (ticketCount == 0) {
            cout << "No tickets booked yet!" << endl;
            waitForKeyPress();
            return;
        }

        cout << "\nList of Tickets:\n";
        cout << left << setw(10) << "ID" << setw(20) << "Name" << setw(15) << "Date" << setw(20) << "Destination"
             << setw(15) << "Class" << setw(10) << "Price" << setw(15) << "Status" << endl;
        cout << string(90, '-') << endl;

        for (int i = 0; i < ticketCount; i++) {
            cout << left << setw(10) << ids[i] << setw(20) << names[i] << setw(15) << dates[i]
                 << setw(20) << destinations[i] << setw(15) << travelClasses[i] << setw(10)
                 << fixed << setprecision(2) << prices[i] << setw(15) << statuses[i] << endl;
        }

        waitForKeyPress();
    }

    void cancelTicket() {
        int ticketId;
        cout << "Enter the Ticket ID to cancel: ";
        cin >> ticketId;

        bool found = false;
        for (int i = 0; i < ticketCount; i++) {
            if (ids[i] == ticketId) {
                found = true;
                if (statuses[i] == "Cancelled") {
                    cout << "Ticket with ID " << ticketId << " is already cancelled!" << endl;
                } else {
                    statuses[i] = "Cancelled";
                    cout << "Ticket with ID " << ticketId << " has been cancelled." << endl;
                }
                break;
            }
        }

        if (!found) {
            cout << "Ticket ID not found!" << endl;
        }

        saveTicketsToFile();
        waitForKeyPress();
    }

    void printTicket() {
        int ticketId;
        cout << "Enter the Ticket ID to print: ";
        cin >> ticketId;

        bool found = false;
        for (int i = 0; i < ticketCount; i++) {
            if (ids[i] == ticketId) {
                found = true;
                cout << "\n--- Ticket Details ---\n";
                cout << "Ticket ID: " << ids[i] << endl;
                cout << "Passenger Name: " << names[i] << endl;
                cout << "Travel Date: " << dates[i] << endl;
                cout << "Destination: " << destinations[i] << endl;
                cout << "Class: " << travelClasses[i] << endl;
                cout << "Price: Rs" << fixed << setprecision(2) << prices[i] << endl;
                cout << "Status: " << statuses[i] << endl;
                cout << "-----------------------\n";
                break;
            }
        }

        if (!found) {
            cout << "Ticket ID not found!" << endl;
        }

        waitForKeyPress();
    }

    void loadTicketsFromFile() {
        ifstream file("tickets.txt");
        if (!file.is_open()) {
            cout << "No existing ticket data found. Starting fresh." << endl;
            return;
        }

        while (file >> ids[ticketCount]) {
            file.ignore();
            getline(file, names[ticketCount]);
            getline(file, dates[ticketCount]);
            getline(file, destinations[ticketCount]);
            getline(file, travelClasses[ticketCount]);
            file >> prices[ticketCount];
            file.ignore();
            getline(file, statuses[ticketCount]);
            ticketCount++;
        }

        file.close();
    }

    void saveTicketsToFile() {
        ofstream file("tickets.txt");
        if (!file.is_open()) {
            cerr << "Error: Unable to save tickets to file." << endl;
            return;
        }

        for (int i = 0; i < ticketCount; i++) {
            file << ids[i] << endl;
            file << names[i] << endl;
            file << dates[i] << endl;
            file << destinations[i] << endl;
            file << travelClasses[i] << endl;
            file << fixed << setprecision(2) << prices[i] << endl;
            file << statuses[i] << endl;
        }

        file.close();
    }

private:
    double calculatePrice(const string &destination, const string &travelClass) {
        double basePrice;
        if (destination == "CityA")
            basePrice = 100.0;
        else if (destination == "CityB")
            basePrice = 150.0;
        else
            basePrice = 200.0;

        if (travelClass == "Business")
            return basePrice * 1.5;
        else if (travelClass == "Firstclass")
            return basePrice * 2.0;
        return basePrice; // Economy
    }

    void clearScreen() {
        system("cls");
    }

    void waitForKeyPress() {
        cout << "\nPress any key to continue...";
        cin.ignore();
        cin.get();
        clearScreen();
    }
};

int main() {
    TicketReservation system;
    system.initialize();

    system.loadTicketsFromFile();

    int choice;
    do {
        cout << "\n--- Ticket Reservation System ---\n";
        cout << "1. Book Ticket\n";
        cout << "2. View Tickets\n";
        cout << "3. Cancel Ticket\n";
        cout << "4. Print Ticket\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            system.bookTicket();
            break;
        case 2:
            system.viewTickets();
            break;
        case 3:
            system.cancelTicket();
            break;
        case 4:
            system.printTicket();
            break;
        case 5:
            cout << "Exiting the system. Goodbye!" << endl;
            break;
        default:
            cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 5);

    system.saveTicketsToFile();
}
