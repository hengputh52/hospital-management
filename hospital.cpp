#include <iostream>
#include <fstream>
#include <sstream>
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
    Patient *Red_Top;
    Patient *Yellow_Top;
    Patient *Green_Top;
    const string fileName = "patients.csv"; // CSV file name

public:
    // Constructor
    PatientList() {
        Red_Top = nullptr;
        Yellow_Top = nullptr;
        Green_Top = nullptr;

        // Load patients from the file
        LoadFromFile();
    }

    ~PatientList() {
        SaveToFile(); // Save patients to file upon destruction
    }

    // Add a new patient
    void AddPatient() {
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
        cin.ignore();
        getline(cin, newPatient->Symptoms);
        cout << "Enter Your Sickness Level (1: Red, 2: Yellow, 3: Green): ";
        cin >> newPatient->Sickness_Level;
        cout << "Enter Your Time for Treatment (in minutes): ";
        cin >> newPatient->Time_Treatment;
        cout << "Enter the Name of Accompanying Person (if any): ";
        cin.ignore();
        getline(cin, newPatient->Accompany);
        cout << "Enter Your Prescription: ";
        getline(cin, newPatient->Prescription);
        cout << "Enter the Name of Your Consultant Doctor: ";
        getline(cin, newPatient->Consultant);

        // Push the patient to the appropriate stack (queue as stack)
        if (newPatient->Sickness_Level == 1) {
            Push(Red_Top, newPatient);
        } else if (newPatient->Sickness_Level == 2) {
            Push(Yellow_Top, newPatient);
        } else if (newPatient->Sickness_Level == 3) {
            Push(Green_Top, newPatient);
        } else {
            cout << "Invalid Sickness Level. Patient not added.\n";
            delete newPatient;
            return;
        }

        SaveToFile(); // Save patients to the file
        cout << "Patient added successfully!\n";
    }

    // Display and process one patient at a time, prioritizing Red > Yellow > Green
    void ProcessPatient() {
        cout << "----------------- Processing Patient ------------------\n";

        if (Pop(Red_Top)) return;    // Process from Red queue (top priority)
        if (Pop(Yellow_Top)) return; // Process from Yellow queue
        if (Pop(Green_Top)) return;  // Process from Green queue

        cout << "No patients left to process.\n";
    }

    // Display all patients
    void DisplayPatients() {
        cout << "\nDisplaying Red Patients (Top to Bottom):\n";
        DisplayStack(Red_Top);

        cout << "\nDisplaying Yellow Patients (Top to Bottom):\n";
        DisplayStack(Yellow_Top);

        cout << "\nDisplaying Green Patients (Top to Bottom):\n";
        DisplayStack(Green_Top);
    }

private:
    // Push a patient onto the stack (queue as stack)
    void Push(Patient *&top, Patient *newPatient) {
        newPatient->Next = top;
        top = newPatient;
    }

    // Pop a patient from the stack (queue as stack)
    bool Pop(Patient *&top) {
        if (!top) return false;

        Patient *temp = top;
        top = top->Next;

        // Display the patient details
        cout << "Processing Patient:\n";
        cout << "----------------------\n";
        cout << "Name: " << temp->Name << "\n";
        cout << "ID: " << temp->ID << "\n";
        cout << "Age: " << temp->Age << "\n";
        cout << "Gender: " << temp->Gender << "\n";
        cout << "Telephone: " << temp->Telephone << "\n";
        cout << "Date: " << temp->Date << "\n";
        cout << "Symptoms: " << temp->Symptoms << "\n";
        cout << "Sickness Level: " << temp->Sickness_Level << "\n";
        cout << "Time for Treatment: " << temp->Time_Treatment << "\n";
        cout << "Accompany: " << temp->Accompany << "\n";
        cout << "Prescription: " << temp->Prescription << "\n";
        cout << "Consultant: " << temp->Consultant << "\n";
        cout << "----------------------\n";

        delete temp; // Free the memory
        return true;
    }

    // Display the patients in a stack (queue as stack)
    void DisplayStack(Patient *top) {
        if (!top) {
            cout << "No patients in this category.\n";
            return;
        }

        Patient *current = top;
        while (current) {
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
            current = current->Next;
        }
    }

    // Check for duplicate patient ID
    bool CheckDuplicateID(int id) {
        return (FindInStack(Red_Top, id) || FindInStack(Yellow_Top, id) || FindInStack(Green_Top, id));
    }

    // Find a patient in a stack
    bool FindInStack(Patient *top, int id) {
        Patient *current = top;
        while (current) {
            if (current->ID == id) {
                return true;
            }
            current = current->Next;
        }
        return false;
    }

    // Save stacks to a CSV file
    void SaveToFile() {
        ofstream file(fileName);
        if (!file.is_open()) {
            cout << "Error: Unable to open file for saving.\n";
            return;
        }

        SaveStackToFile(file, Red_Top);
        SaveStackToFile(file, Yellow_Top);
        SaveStackToFile(file, Green_Top);

        file.close();
    }

    void SaveStackToFile(ofstream &file, Patient *top) {
        Patient *current = top;
        while (current) {
            file << current->Name << "," << current->ID << "," << current->Age << "," << current->Gender << ","
                 << current->Telephone << "," << current->Date << "," << current->Symptoms << ","
                 << current->Sickness_Level << "," << current->Time_Treatment << "," << current->Accompany << ","
                 << current->Prescription << "," << current->Consultant << "\n";
            current = current->Next;
        }
    }

    // Load patients from the file
    void LoadFromFile() {
        ifstream file(fileName);
        if (!file.is_open()) {
            cout << "No previous patient data found.\n";
            return;
        }

        string line, value;
        while (getline(file, line)) {
            stringstream ss(line);

            Patient *newPatient = new Patient;
            getline(ss, newPatient->Name, ',');
            getline(ss, value, ',');
            newPatient->ID = stoi(value);
            getline(ss, value, ',');
            newPatient->Age = stoi(value);
            getline(ss, value, ',');
            newPatient->Gender = value[0];
            getline(ss, newPatient->Telephone, ',');
            getline(ss, newPatient->Date, ',');
            getline(ss, newPatient->Symptoms, ',');
            getline(ss, value, ',');
            newPatient->Sickness_Level = stoi(value);
            getline(ss, value, ',');
            newPatient->Time_Treatment = stoi(value);
            getline(ss, newPatient->Accompany, ',');
            getline(ss, newPatient->Prescription, ',');
            getline(ss, newPatient->Consultant, ',');

            if (newPatient->Sickness_Level == 1) {
                Push(Red_Top, newPatient);
            } else if (newPatient->Sickness_Level == 2) {
                Push(Yellow_Top, newPatient);
            } else if (newPatient->Sickness_Level == 3) {
                Push(Green_Top, newPatient);
            }
        }

        file.close();
    }
};

// Main function
int main() {
    PatientList hospital;

    int option;
    do {
        cout << "\n--------------------- Sabay Hospital ------------------\n";
        cout << "1. Register Patient\n";
        cout << "2. Display All Patients\n";
        cout << "3. Process One Patient\n";
        cout << "4. Exit\n";
        cout << "Choose an option: ";
        cin >> option;

        switch (option) {
            case 1:
                hospital.AddPatient();
                break;
            case 2:
                hospital.DisplayPatients();
                break;
            case 3:
                hospital.ProcessPatient();
                break;
            case 4:
                cout << "Exiting program...\n";
                break;
            default:
                cout << "Invalid option. Try again.\n";
        }
    } while (option != 4);

    return 0;
}
