#include <iostream>
using namespace std;

// Define the Patient structure
struct Patient {
    string Name;
    int ID;
    int Age;
    char Gender;
    string Telephone;
    string Date;
    string Symptoms;
    int Sickness_Level; // 1: red, 2: yellow, 3: green
    int Time_Treatment;
    string Accompany;
    string Prescription;
    string Consultant;
    Patient *Next;
};

// Define the PatientList class
class PatientList {
private:
    int size;
    Patient *rear, *front;

public:
    // Constructor
    PatientList() {
        size = 0;
        rear = nullptr;
        front = nullptr;
    }

    // Add a new patient (enqueue)
    void AddPatient() {
        // Create a new patient node
        Patient *newPatient = new Patient;
        newPatient->Next = nullptr;

        // Input patient details
        cout << "------------------ Welcome to Sabay Hospital --------------------\n";
        cout << "Enter Your Full Name: ";
        cin.ignore(); // To clear the newline buffer
        getline(cin, newPatient->Name);
        cout << "Enter Your ID: ";
        cin >> newPatient->ID;

        // Check for duplicate ID
        if (CheckDuplicateID(newPatient->ID)) {
            cout << "Error: Duplicate ID detected. Please try again.\n";
            delete newPatient;
            return;
        }

        cout << "Enter Your Age: ";
        cin >> newPatient->Age;
        cout << "Enter Your Gender (M/F): ";
        cin >> newPatient->Gender;
        cout << "Enter Your Telephone: ";
        cin >> newPatient->Telephone;
        cout << "Enter Today's Date (YYYY-MM-DD): ";
        cin >> newPatient->Date;
        cout << "Enter Your Symptoms: ";
        cin.ignore(); // Clear buffer
        getline(cin, newPatient->Symptoms);
        cout << "Enter Your Sickness Level (1: Red, 2: Yellow, 3: Green): ";
        cin >> newPatient->Sickness_Level;
        cout << "Enter Your Time for Treatment (in minutes): ";
        cin >> newPatient->Time_Treatment;
        cout << "Enter the Name of Accompanying Person (if any): ";
        cin.ignore(); // Clear buffer
        getline(cin, newPatient->Accompany);
        cout << "Enter Your Prescription: ";
        getline(cin, newPatient->Prescription);
        cout << "Enter the Name of Your Consultant Doctor: ";
        getline(cin, newPatient->Consultant);

        // Enqueue the patient
        if (Empty()) {
            front = rear = newPatient;
        } else {
            rear->Next = newPatient;
            rear = newPatient;
        }

        size++;
        cout << "Patient added successfully!\n";
    }


    void PatientOperation()
    {
        //red has to display first then yellow and green 
    }

    // Display all patients
    void DisplayPatients() {
        if (Empty()) {
            cout << "There are no patients.\n";
            return;
        }

        Patient *current = front;
        while (current != nullptr) {
            cout << "----------------------\n";
            cout << "Name: " << current->Name << "\n";
            cout << "ID: " << current->ID << "\n";
            cout << "Age: " << current->Age << "\n";
            cout << "Gender: " << current->Gender << "\n";
            cout << "Telephone: " << current->Telephone << "\n";
            cout << "Date: " << current->Date << "\n";
            cout << "Symptoms: " << current->Symptoms << "\n";
            cout << "Sickness Level: " << current->Sickness_Level << "\n";
            cout << "Time for Treatment: " << current->Time_Treatment << "\n";
            cout << "Accompany: " << current->Accompany << "\n";
            cout << "Prescription: " << current->Prescription << "\n";
            cout << "Consultant: " << current->Consultant << "\n";
            cout << "----------------------\n";
            current = current->Next;
        }
    }

    // Check for duplicate patient ID
    bool CheckDuplicateID(int id) {
        Patient *current = front;
        while (current != nullptr) {
            if (current->ID == id) {
                return true;
            }
            current = current->Next;
        }
        return false;
    }

    // Check if the patient list is empty
    bool Empty() {
        return size == 0;
    }
};

// Main function
int main() {
    PatientList hospital;

    int option;
    do{
        cout<<"\t\t\t\t\t\t---------------------Welcome to our Sabay Hospital------------------ "<<endl;
        cout<<"\t\t\t\t\t\t1. Register Patient\n";
        cout<<"\t\t\t\t\t\t2.Display All Patient\n";
        cout<<"\t\t\t\t\t\t3.Exit\n";
        cout<<"\t\t\t\t\t\tPlease Choose Option Above: ";
        cin>>option;

        switch (option)
        {
            case 1:
            cout<<"\n\t\t\t\t\t---------------------------Pateint Registration--------------------\n";
            hospital.AddPatient();
            break;

            case 2:
            cout<<"\t\t\t\t\t-------------------------Display All Patient Information---------------\n";
            hospital.DisplayPatients();
            break;
            
            case 3:
            cout<<"\t\t\t\t\t------------------------------Exiting Program-----------------------\n";
            break;

            default:
            cout<<"\t\t\t\t\t----------Please Enter Valid Option-----------\n";

        }
    }
    while(option!=3);


    return 0;
}
