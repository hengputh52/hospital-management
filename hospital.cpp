#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <stdlib.h>
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
    const string fileHistory = "patientsHistory.csv"; // History file

public:
    // Constructor
    PatientList() : Red_Top(nullptr), Yellow_Top(nullptr), Green_Top(nullptr) {
        LoadFromFile(); // Load patients from file
    }

    // Destructor
    ~PatientList() {
        SaveToFile(); // Save patients to file upon destruction
        ClearStack(Red_Top);
        ClearStack(Yellow_Top);
        ClearStack(Green_Top);
    }

    // Add a new patient
    void AddPatient() {
        system("cls");
        Patient *newPatient = new Patient;
        newPatient->Next = nullptr;

        // Input patient details
        cout << "------------------ Welcome to Sabay Hospital --------------------\n";
        cin.ignore(); // Clear the newline buffer
        newPatient->Name = InputString("Enter Your Full Name: ");
        newPatient->ID = InputInt("Enter Your ID: ");

        // Check for duplicate ID
        if (CheckDuplicateID(newPatient->ID)) {
            cout << "Error: Duplicate ID detected. Please try again.\n";
            delete newPatient;
            return;
        }

        newPatient->Age = InputInt("Enter Your Age: ");
        newPatient->Gender = InputChar("Enter Your Gender (M/F): ");
        newPatient->Telephone = InputString("Enter Your Telephone: ");
        newPatient->Date = InputString("Enter Today's Date (YYYY-MM-DD): ");
        newPatient->Symptoms = InputString("Enter Your Symptoms: ");
        newPatient->Sickness_Level = InputInt("Enter Your Sickness Level (1: Red, 2: Yellow, 3: Green): ");
        newPatient->Time_Treatment = InputInt("Enter Your Time for Treatment (in minutes): ");
        newPatient->Accompany = InputString("Enter the Name of Accompanying Person (if any): ");
        newPatient->Prescription = InputString("Enter Your Prescription: ");
        newPatient->Consultant = InputString("Enter the Name of Your Consultant Doctor: ");

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


    //search function

    void SearchPatient()
    {
        system("cls");
        cout<<"Enter the ID of the patient to search: ";
        int id;
        cin>>id;

        Patient *foundPatient = FindPatientByID(id);
        if (foundPatient) {
            cout << "Patient Found:\n";
            DisplayPatientDetails(foundPatient);
        } else {
            cout << "No patient found with ID " << id << ".\n";
        }


    }


    void UpdatePatient()
    {
        system("cls");
        int id;
        cout << "Enter the ID of the patient to update: ";
        cin >> id;

        Patient *foundPatient = FindPatientByID(id);
        if (foundPatient) {
            cout << "Patient Found:\n";
            DisplayPatientDetails(foundPatient);

            // Allow the user to update details
            cin.ignore(); // Clear the newline buffer
            foundPatient->Name = InputString("Enter Updated Full Name (or press Enter to keep the current): ");
            foundPatient->Age = InputInt("Enter Updated Age (or press -1 to keep the current): ");
            foundPatient->Gender = InputChar("Enter Updated Gender (M/F) (or press Enter to keep the current): ");
            foundPatient->Telephone = InputString("Enter Updated Telephone (or press Enter to keep the current): ");
            foundPatient->Date = InputString("Enter Updated Date (YYYY-MM-DD) (or press Enter to keep the current): ");
            foundPatient->Symptoms = InputString("Enter Updated Symptoms (or press Enter to keep the current): ");
            foundPatient->Time_Treatment = InputInt("Enter Updated Time for Treatment (or press -1 to keep the current): ");
            foundPatient->Accompany = InputString("Enter Updated Name of Accompanying Person (or press Enter to keep the current): ");
            foundPatient->Prescription = InputString("Enter Updated Prescription (or press Enter to keep the current): ");
            foundPatient->Consultant = InputString("Enter Updated Consultant Doctor (or press Enter to keep the current): ");

            SaveToFile(); // Save changes to file
            cout << "Patient information updated successfully.\n";
        } else {
            cout << "No patient found with ID " << id << ".\n";
        }
    }
    

    void DeletePatient()
    {
        system("cls");
        int id;
        cout << "Enter the ID of the patient to delete: ";
        cin >> id;

        if (DeletePatientFromStack(Red_Top, id) ||
            DeletePatientFromStack(Yellow_Top, id) ||
            DeletePatientFromStack(Green_Top, id)) {
            SaveToFile(); // Save changes to file
            cout << "Patient with ID " << id << " deleted successfully.\n";
        } else {
            cout << "No patient found with ID " << id << ".\n";
        }
    }

    bool DeletePatientFromStack(Patient *&top, int id) {
    Patient *current = top, *previous = nullptr;

    while (current) {
        if (current->ID == id) {
            if (previous) {
                previous->Next = current->Next;
            } else {
                top = current->Next; // Update top if deleting the first node
            }

            delete current; // Free memory
            return true;
        }
        previous = current;
        current = current->Next;
    }
    return false;
}


Patient *FindPatientByID(int id) {
    Patient *patient = nullptr;
    if ((patient = FindInStack(Red_Top, id))) return patient;
    if ((patient = FindInStack(Yellow_Top, id))) return patient;
    if ((patient = FindInStack(Green_Top, id))) return patient;
    return nullptr;
}



    void GenerateReportFromHistory() {
        system("cls");
        ifstream file("patientsHistory.csv");
        if (!file.is_open()) {
            cout << "Error: Unable to open the history file.\n";
            return;
        }

        int totalPatients = 0;
        int redCount = 0, yellowCount = 0, greenCount = 0;
        int maleCount = 0, femaleCount = 0;
        int minorsCount = 0, adultsCount = 0, seniorsCount = 0;

        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string name, telephone, date, symptoms, accompany, prescription, consultant;
            int id, age, sicknessLevel, timeTreatment;
            char gender;

            // Parse the CSV line
            getline(ss, name, ',');
            ss >> id;
            ss.ignore();
            ss >> age;
            ss.ignore();
            ss >> gender;
            ss.ignore();
            getline(ss, telephone, ',');
            getline(ss, date, ',');
            getline(ss, symptoms, ',');
            ss >> sicknessLevel;
            ss.ignore();
            ss >> timeTreatment;
            ss.ignore();
            getline(ss, accompany, ',');
            getline(ss, prescription, ',');
            getline(ss, consultant, ',');

            // Increment total patients
            totalPatients++;

            // Count sickness levels
            if (sicknessLevel == 1) redCount++;
            else if (sicknessLevel == 2) yellowCount++;
            else if (sicknessLevel == 3) greenCount++;

            // Count gender
            if (toupper(gender) == 'M') maleCount++;
            else if (toupper(gender) == 'F') femaleCount++;

            // Count age distribution
            if (age <= 17) minorsCount++;
            else if (age <= 59) adultsCount++;
            else seniorsCount++;
        }

        file.close();

        // Display the report
        cout << "\n--------------------- History Report ---------------------\n";
        cout << "Total Patients in History: " << totalPatients << "\n";
        cout << "Red Priority Patients: " << redCount << "\n";
        cout << "Yellow Priority Patients: " << yellowCount << "\n";
        cout << "Green Priority Patients: " << greenCount << "\n";
        cout << "Male Patients: " << maleCount << "\n";
        cout << "Female Patients: " << femaleCount << "\n";
        cout << "\nAge Distribution:\n";
        cout << " - Minors (0-17): " << minorsCount << "\n";
        cout << " - Adults (18-59): " << adultsCount << "\n";
        cout << " - Seniors (60+): " << seniorsCount << "\n";
        cout << "----------------------------------------------------------\n";
}

    
    // Display and process one patient at a time, prioritizing Red > Yellow > Green
    void ProcessPatient() {
        system("cls");
        cout << "----------------- Processing Patient ------------------\n";

        if (Pop(Red_Top)) return;    // Process from Red queue (top priority)
        if (Pop(Yellow_Top)) return; // Process from Yellow queue
        if (Pop(Green_Top)) return;  // Process from Green queue

        cout << "No patients left to process.\n";
    }

    // Display patients
    void DisplayRed() {
        system("cls");
        cout << "\nDisplaying Red Patients (Top to Bottom):\n";
        DisplayStack(Red_Top);
    }
    void DisplayYellow(){
        system("cls");
        cout << "\nDisplaying Yellow Patients (Top to Bottom):\n";
        DisplayStack(Yellow_Top);
    }
    void DisplayGreen() {
        system("cls");
        cout << "\nDisplaying Green Patients (Top to Bottom):\n";
        DisplayStack(Green_Top);
    }

    void DisplayPatients() {
        system("cls");
        DisplayRed();
        DisplayYellow();
        DisplayGreen();
    }


    // Display operated patients history
    void DisplayOperatedPatientsHistory() {
        ifstream file(fileHistory);
        if (!file.is_open()) {
            cout << "No operated patient history found.\n";
            return;
        }

        string line;
        cout << "\nDisplaying Operated Patients History:\n";
        while (getline(file, line)) {
            cout << line << endl;
        }
        file.close();
    }

private:
    // Helper functions for input validation
    string InputString(const string &prompt) {
        cout << prompt;
        string input;
        getline(cin, input);
        return input;
    }

    int InputInt(const string &prompt) {
        cout << prompt;
        int input;
        cin >> input;
        cin.ignore(); // Clear buffer
        return input;
    }

    char InputChar(const string &prompt) {
        cout << prompt;
        char input;
        cin >> input;
        cin.ignore(); // Clear buffer
        return input;
    }

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
        DisplayPatientDetails(temp);

        // Append to history file
        AppendToHistory(temp);

        delete temp; // Free the memory
        SaveToFile(); // Update the file
        return true;
    }

    // Append a patient to the history file
    void AppendToHistory(Patient *patient) {
        ofstream file(fileHistory, ios::app);
        if (!file.is_open()) {
            cout << "Error: Unable to open history file.\n";
            return;
        }

        file << patient->Name << "," << patient->ID << "," << patient->Age << "," << patient->Gender << ","
             << patient->Telephone << "," << patient->Date << "," << patient->Symptoms << ","
             << patient->Sickness_Level << "," << patient->Time_Treatment << "," << patient->Accompany << ","
             << patient->Prescription << "," << patient->Consultant << "\n";

        file.close();
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
            DisplayPatientDetails(current);
            current = current->Next;
        }
    }

    // Display individual patient details
    void DisplayPatientDetails(Patient *patient) {
        cout << "Name: " << patient->Name << "\n";
        cout << "ID: " << patient->ID << "\n";
        cout << "Age: " << patient->Age << "\n";
        cout << "Gender: " << patient->Gender << "\n";
        cout << "Telephone: " << patient->Telephone << "\n";
        cout << "Date: " << patient->Date << "\n";
        cout << "Symptoms: " << patient->Symptoms << "\n";
        cout << "Sickness Level: " << patient->Sickness_Level << "\n";
        cout << "Time for Treatment: " << patient->Time_Treatment << "\n";
        cout << "Accompany: " << patient->Accompany << "\n";
        cout << "Prescription: " << patient->Prescription << "\n";
        cout << "Consultant: " << patient->Consultant << "\n";
    }

    // Check for duplicate patient ID
    bool CheckDuplicateID(int id) {
        return (FindInStack(Red_Top, id) || FindInStack(Yellow_Top, id) || FindInStack(Green_Top, id));
    }

    // Find a patient in a stack
    Patient* FindInStack(Patient *top, int id) {
        Patient *current = top;
        while (current) {
            if (current->ID == id) {
                return current;
            }
            current = current->Next;
        }
        return nullptr;
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

    // Clear a stack and free memory
    void ClearStack(Patient *&top) {
        while (top) {
            Patient *temp = top;
            top = top->Next;
            delete temp;
        }
    }
};

// Main function
int main() {
    system("cls");
    PatientList hospital;
    int choice;
    int option;
    do {
        cout << "\n--------------------- Sabay Hospital ------------------\n";
        cout << "1. Register Patient\n";
        cout << "2. Display\n";
        cout << "3. Process One Patient\n";
        cout << "4. Display All Operated Patients History\n";
        cout << "5. Update Patient Information\n";
        cout << "6. Search Patient Information\n";
        cout << "7. Delete Patient Information\n";
        cout<<  "8. Generate Report\n";
        cout << "9. Exit\n";
        cout << "Choose an option: ";
        cin >> option;

        switch (option) {
            case 1:
                hospital.AddPatient();
                break;
            case 2:
                cout <<"1. Display all Red\n";
                cout <<"2. Display all Yellow\n";
                cout <<"3. Display all Green\n";
                cout <<"4. Display all\n";
                cout << "Choose an option: ";
                cin >> choice;

                switch (choice)
                {
                case 1:
                    hospital.DisplayRed();
                    break;
                case 2:
                    hospital.DisplayYellow();
                    break;
                case 3:
                    hospital.DisplayGreen();
                    break;
                case 4:
                    hospital.DisplayPatients();
                    break;
                default:
                    break;
                }
                break;
            case 3:
                hospital.ProcessPatient();
                break;
            case 4:
                hospital.DisplayOperatedPatientsHistory();
                break;
            case 5:
                hospital.UpdatePatient();
                break;
            case 6:
                hospital.SearchPatient();
                break;
            case 7:
                hospital.DeletePatient();
                break;
            case 8:
                hospital.GenerateReportFromHistory();    
                break;
            default:
                cout << "Invalid option. Try again.\n";
        }
    } while (option != 5);

    return 0;
}