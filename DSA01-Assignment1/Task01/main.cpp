
#include <iostream>
#include <iomanip>
using namespace std;

bool isPeakHour(int hour) {
    return (hour >= 8 && hour < 10) ||
           (hour >= 17 && hour < 20);
}

class SmartCard {
private:
    int balance; // Balance stored in paise

public:
    SmartCard(int initialBalance) {
        balance = initialBalance;
    }

    int getBalance() {
        return balance;
    }

    bool deductFare(int fare) {
        if (fare <= 0 || balance - fare < 5000) {
            return false;
        }

        balance -= fare;
        return true;
    }
};

class FareTable {
public:
    int getFare(int zone) {
        switch (zone) {
            case 1: return 1000; // Inner: Rs 10
            case 2: return 2000; // Middle: Rs 20
            case 3: return 3000; // Outer: Rs 30
            default: return 0;
        }
    }

    int calculateJourneyFare(int zone, int hour) {
        int baseFare = getFare(zone);

        if (baseFare == 0) {
            return 0;
        }

        if (isPeakHour(hour)) {
            return baseFare + baseFare / 5;
        }

        return baseFare;
    }
};

int main() {
    SmartCard card(10000); // Starting balance: Rs 100
    FareTable fareTable;

    cout << fixed << setprecision(2);

    cout << "--- Metro Smart-Card System ---\n\n";

    cout << "Inner zone fare: Rs "
         << fareTable.getFare(1) / 100.0 << endl;

    cout << "Middle zone fare: Rs "
         << fareTable.getFare(2) / 100.0 << endl;

    cout << "Outer zone fare: Rs "
         << fareTable.getFare(3) / 100.0 << endl;

    cout << "\n--- Peak Hour Tests ---\n";
    cout << "8 AM: " << (isPeakHour(8) ? "Peak" : "Off-peak") << endl;
    cout << "10 AM: " << (isPeakHour(10) ? "Peak" : "Off-peak") << endl;
    cout << "5 PM: " << (isPeakHour(17) ? "Peak" : "Off-peak") << endl;
    cout << "8 PM: " << (isPeakHour(20) ? "Peak" : "Off-peak") << endl;

    cout << "\n--- Journey Tests ---\n";

    int fare = fareTable.calculateJourneyFare(3, 9);

    cout << "Outer zone fare at 9 AM: Rs "
         << fare / 100.0 << endl;

    if (card.deductFare(fare)) {
        cout << "Journey allowed!" << endl;
    } else {
        cout << "Journey denied!" << endl;
    }

    cout << "Remaining balance: Rs "
         << card.getBalance() / 100.0 << endl;

    int secondFare = fareTable.calculateJourneyFare(3, 11);

    cout << "\nOuter zone fare at 11 AM: Rs "
         << secondFare / 100.0 << endl;

    if (card.deductFare(secondFare)) {
        cout << "Journey allowed!" << endl;
    } else {
        cout << "Journey denied (minimum balance rule)!" << endl;
    }

    cout << "Final balance: Rs "
         << card.getBalance() / 100.0 << endl;

    return 0;
}
