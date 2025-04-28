#include <iostream>
#include <string>

using namespace std;

// Base class: Loan
class Loan {
protected:
    int loanID;
    double amount;
    double interestRate;
    int termMonths;

public:
    static int loanCount; // static variable

    Loan(int id = 0, double amt = 0.0, double rate = 0.0, int term = 0)
        : loanID(id), amount(amt), interestRate(rate), termMonths(term) {}

    inline void setLoanDetails(int id, double amt, double rate, int term) {
        loanID = id;
        amount = amt;
        interestRate = rate;
        termMonths = term;
    }

    inline void displayLoanDetails() const {
        cout << "\nLoan ID: " << loanID;
        cout << "\nAmount: $" << amount;
        cout << "\nInterest Rate: " << interestRate << "%";
        cout << "\nTerm: " << termMonths << " months\n";
    }

    // Calculate monthly payment without pow()
    double calculateMonthlyPayment() const {
        double monthlyRate = interestRate / 100 / 12;
        double denominator = 1.0;

        for (int i = 0; i < termMonths; i++) {
            denominator *= (1 + monthlyRate);
        }

        return (amount * monthlyRate) / (1 - (1 / denominator));
    }

    static void displayLoanCount() {
        cout << "\nTotal Loans in System: " << loanCount << endl;
    }
};

//  static
int Loan::loanCount = 0;

// Derived class: Borrower
class Borrower : public Loan {
private:
    string name;
    string contact;

public:
    Borrower(int id = 0, double amt = 0.0, double rate = 0.0, int term = 0,
             string bName = "", string bContact = "")
        : Loan(id, amt, rate, term), name(bName), contact(bContact) {}

    inline void setBorrowerDetails(string bName, string bContact) {
        name = bName;
        contact = bContact;
    }

    inline void displayBorrowerDetails() const {
        cout << "\nBorrower Name: " << name;
        cout << "\nContact Info: " << contact;
        displayLoanDetails();
    }
};

// Derived class: Repayment Schedule
class RepaymentSchedule : public Loan {
public:
    RepaymentSchedule(int id = 0, double amt = 0.0, double rate = 0.0, int term = 0)
        : Loan(id, amt, rate, term) {}

    void displaySchedule() const {
        cout << "\n📌 Repayment Schedule for Loan ID " << loanID << ":\n";
        double monthlyPayment = calculateMonthlyPayment();
        for (int i = 1; i <= termMonths; ++i) {
            cout << "🗓️ Month " << i << ": Payment $" << monthlyPayment << "\n";
        }
    }
};

// Main function
int main() {
    const int MAX_LOANS = 5;
    Borrower borrowers[MAX_LOANS];
    RepaymentSchedule schedules[MAX_LOANS];
    int count = 0;

    while (true) {
        cout << "\n--- 🏦 Loan Management System ---";
        cout << "\n1️⃣ Add a New Loan";
        cout << "\n2️⃣ Display Loan Details";
        cout << "\n3️⃣ Show Repayment Schedules";
        cout << "\n4️⃣ Exit";
        cout << "\n5️⃣ Show Total Loans";
                cout << "\n";

        cout << "\n➡️ Enter your choice: ";

        int choice;
        cin >> choice;
        cin.ignore();

        if (choice == 1 && count < MAX_LOANS) {
            int id, term;
            double amount, rate;
            string name, contact;

            cout << "\n📌 Enter Loan ID: ";
            cin >> id;
            cout << "💰 Enter Loan Amount: ";
            cin >> amount;
            cout << "📊 Enter Interest Rate (%): ";
            cin >> rate;
            cout << "📆 Enter Loan Term (months): ";
            cin >> term;
            cin.ignore();
            cout << "👤 Enter Borrower Name: ";
            getline(cin, name);
            cout << "📞 Enter Contact Info: ";
            getline(cin, contact);

            borrowers[count].setLoanDetails(id, amount, rate, term);
            borrowers[count].setBorrowerDetails(name, contact);
            schedules[count].setLoanDetails(id, amount, rate, term);

            Loan::loanCount++; // UPDATE THE FUNCTION

            count++;
            cout << "✅ Loan added successfully!\n";

        } else if (choice == 2) {
            if (count == 0) {
                cout << "\n⚠️ No loans available!\n";
            } else {
                for (int i = 0; i < count; ++i) {
                    borrowers[i].displayBorrowerDetails();
                    cout << "--------------------------\n";
                }
            }

        } else if (choice == 3) {
            if (count == 0) {
                cout << "\n⚠️ No loans available!\n";
            } else {
                for (int i = 0; i < count; ++i) {
                    schedules[i].displaySchedule();
                    cout << "--------------------------\n";
                }
            }

        } else if (choice == 4) {
            cout << "\n🚪 Exiting the system...\n";
            break;

        } else if (choice == 5) {
            Loan::displayLoanCount();

        } else {
            cout << "\n❌ Invalid choice! Try again.\n";
        }
    }

    return 0;
}
