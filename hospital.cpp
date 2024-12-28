#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
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
};

// Define the PatientList class
class PatientList {
private:
    const string fileName = "patients.csv";      // File for current patients
    const string historyFileName = "history.csv"; // File for history

public:
    // Add a new patient
    void AddPatient() {
        Patient newPatient;

        // Input patient details
        cout << "------------------ Welcome to Sabay Hospital --------------------\n";
        cout << "Enter Your Full Name: ";
        cin.ignore();
        getline(cin, newPatient.Name);
        cout << "Enter Your ID: ";
        cin >> newPatient.ID;

        // Check for duplicate ID
        if (CheckDuplicateID(newPatient.ID)) {
            cout << "Error: Duplicate ID detected. Please try again.\n";
            return;
        }

        cout << "Enter Your Age: ";
        cin >> newPatient.Age;
        cout << "Enter Your Gender (M/F): ";
        cin >> newPatient.Gender;
        cout << "Enter Your Telephone: ";
        cin >> newPatient.Telephone;
        cout << "Enter Today's Date (YYYY-MM-DD): ";
        cin >> newPatient.Date;
        cout << "Enter Your Symptoms: ";
        cin.ignore();
        getline(cin, newPatient.Symptoms);
        cout << "Enter Your Sickness Level (1: Red, 2: Yellow, 3: Green): ";
        cin >> newPatient.Sickness_Level;
        cout << "Enter Your Time for Treatment (in minutes): ";
        cin >> newPatient.Time_Treatment;
        cout << "Enter the Name of Accompanying Person (if any): ";
        cin.ignore();
        getline(cin, newPatient.Accompany);
        cout << "Enter Your Prescription: ";
        getline(cin, newPatient.Prescription);
        cout << "Enter the Name of Your Consultant Doctor: ";
        getline(cin, newPatient.Consultant);

        // Save the patient to the `patients.csv` file
        SavePatientToFile(newPatient);

        cout << "Patient added successfully!\n";
    }

    // Display patients from the `patients.csv` file by priority
    void DisplayPatients() {
        cout << "----------------- Display Patients by Priority ------------------\n";

        ifstream file(fileName);
        if (!file.is_open()) {
            cout << "No patients found.\n";
            return;
        }

        DisplayPatientsByPriority(file, 1, "Red Patients");
        file.clear();
        file.seekg(0); // Rewind the file
        DisplayPatientsByPriority(file, 2, "Yellow Patients");
        file.clear();
        file.seekg(0); // Rewind the file
        DisplayPatientsByPriority(file, 3, "Green Patients");

        file.close();
    }

    // Process and remove a patient (pop)
    void ProcessPatient() {
        vector<Patient> allPatients = LoadPatientsFromFile();
        if (allPatients.empty()) {
            cout << "No patients left to process.\n";
            return;
        }

        // Find the highest priority patient (Red > Yellow > Green)
        int priorityOrder[] = {1, 2, 3};
        Patient *toProcess = nullptr;
        for (int priority : priorityOrder) {
            for (auto &patient : allPatients) {
                if (patient.Sickness_Level == priority) {
                    toProcess = &patient;
                    break;
                }
            }
            if (toProcess) break;
        }

        if (!toProcess) {
            cout << "No patients found to process.\n";
            return;
        }

        // Process the patient
        cout << "Processing Patient:\n";
        DisplayPatientDetails(*toProcess);

        // Store the patient in the history file
        SavePatientToHistory(*toProcess);

        // Remove the patient from the `patients.csv` file
        RemovePatientFromFile(*toProcess);
    }

    // Delete a patient by ID
    void DeletePatient() {
        cout << "Enter the ID of the patient to delete: ";
        int id;
        cin >> id;

        vector<Patient> patients = LoadPatientsFromFile();
        bool found = false;

        ofstream file(fileName, ios::trunc); // Overwrite mode
        if (!file.is_open()) {
            cout << "Error: Unable to update patient file.\n";
            return;
        }

        for (const auto &patient : patients) {
            if (patient.ID == id) {
                found = true;
                cout << "Patient with ID " << id << " has been deleted.\n";
            } else {
                SavePatientToFile(patient); // Save all other patients
            }
        }

        if (!found) {
            cout << "Patient with ID " << id << " not found.\n";
        }

        file.close();
    }

    // Update a patient's information by ID
    void UpdatePatient() {
        cout << "Enter the ID of the patient to update: ";
        int id;
        cin >> id;

        vector<Patient> patients = LoadPatientsFromFile();
        bool found = false;

        for (auto &patient : patients) {
            if (patient.ID == id) {
                found = true;

                cout << "Updating Patient Information:\n";
                cout << "Enter New Full Name (current: " << patient.Name << "): ";
                cin.ignore();
                getline(cin, patient.Name);
                cout << "Enter New Age (current: " << patient.Age << "): ";
                cin >> patient.Age;
                cout << "Enter New Gender (current: " << patient.Gender << "): ";
                cin >> patient.Gender;
                cout << "Enter New Telephone (current: " << patient.Telephone << "): ";
                cin >> patient.Telephone;
                cout << "Enter New Today's Date (current: " << patient.Date << "): ";
                cin >> patient.Date;
                cout << "Enter New Symptoms (current: " << patient.Symptoms << "): ";
                cin.ignore();
                getline(cin, patient.Symptoms);
                cout << "Enter New Sickness Level (current: " << patient.Sickness_Level << "): ";
                cin >> patient.Sickness_Level;
                cout << "Enter New Time for Treatment (current: " << patient.Time_Treatment << "): ";
                cin >> patient.Time_Treatment;
                cout << "Enter New Accompanying Person (current: " << patient.Accompany << "): ";
                cin.ignore();
                getline(cin, patient.Accompany);
                cout << "Enter New Prescription (current: " << patient.Prescription << "): ";
                getline(cin, patient.Prescription);
                cout << "Enter New Consultant Doctor (current: " << patient.Consultant << "): ";
                getline(cin, patient.Consultant);

                break;
            }
        }

        if (!found) {
            cout << "Patient with ID " << id << " not found.\n";
            return;
        }

        // Rewrite the updated data to the `patients.csv` file
        ofstream file(fileName, ios::trunc); // Overwrite mode
        if (!file.is_open()) {
            cout << "Error: Unable to update patient file.\n";
            return;
        }

        for (const auto &patient : patients) {
            SavePatientToFile(patient); // Save all patients including updated one
        }

        file.close();
        cout << "Patient information updated successfully.\n";
    }

    // Display the patient history from `history.csv`
    void DisplayHistory() {
        cout << "----------------- Display Patient History ------------------\n";

        ifstream file(historyFileName);
        if (!file.is_open()) {
            cout << "No history found.\n";
            return;
        }

        string line;
        while (getline(file, line)) {
            ReplaceCommasWithNewlines(line); // Format and display the line
            cout << "----------------------\n";
        }

        file.close();
    }

private:
    // Save a patient to the `patients.csv` file
    void SavePatientToFile(const Patient &patient) {
        ofstream file(fileName, ios::app); // Append mode
        if (!file.is_open()) {
            cout << "Error: Unable to save patient to file.\n";
            return;
        }

        file << patient.Name << "," << patient.ID << "," << patient.Age << "," << patient.Gender << ","
             << patient.Telephone << "," << patient.Date << "," << patient.Symptoms << ","
             << patient.Sickness_Level << "," << patient.Time_Treatment << "," << patient.Accompany << ","
             << patient.Prescription << "," << patient.Consultant << "\n";

        file.close();
    }

    // Save a patient to the `history.csv` file
    void SavePatientToHistory(const Patient &patient) {
        ofstream file(historyFileName, ios::app); // Append mode
        if (!file.is_open()) {
            cout << "Error: Unable to save patient to history file.\n";
            return;
        }

        file << patient.Name << "," << patient.ID << "," << patient.Age << "," << patient.Gender << ","
             << patient.Telephone << "," << patient.Date << "," << patient.Symptoms << ","
             << patient.Sickness_Level << "," << patient.Time_Treatment << "," << patient.Accompany << ","
             << patient.Prescription << "," << patient.Consultant << "\n";

        file.close();
    }

    // Load all patients from the `patients.csv` file
    vector<Patient> LoadPatientsFromFile() {
        vector<Patient> patients;

        ifstream file(fileName);
        if (!file.is_open()) return patients;

        string line, value;
        while (getline(file, line)) {
            stringstream ss(line);
            Patient patient;

            getline(ss, patient.Name, ',');
            getline(ss, value, ',');
            patient.ID = stoi(value);
            getline(ss, value, ',');
            patient.Age = stoi(value);
            getline(ss, value, ',');
            patient.Gender = value[0];
            getline(ss, patient.Telephone, ',');
            getline(ss, patient.Date, ',');
            getline(ss, patient.Symptoms, ',');
            getline(ss, value, ',');
            patient.Sickness_Level = stoi(value);
            getline(ss, value, ',');
            patient.Time_Treatment = stoi(value);
            getline(ss, patient.Accompany, ',');
            getline(ss, patient.Prescription, ',');
            getline(ss, patient.Consultant, ',');

            patients.push_back(patient);
        }

        file.close();
        return patients;
    }

    // Display patients by priority
    void DisplayPatientsByPriority(ifstream &file, int level, const string &title) {
        string line, value;
        cout << title << ":\n";

        while (getline(file, line)) {
            stringstream ss(line);
            getline(ss, value, ','); // Name
            string name = value;
            getline(ss, value, ','); // ID
            int id = stoi(value);
            getline(ss, value, ','); // Age
            getline(ss, value, ','); // Gender
            getline(ss, value, ','); // Telephone
            getline(ss, value, ','); // Date
            getline(ss, value, ','); // Symptoms
            getline(ss, value, ','); // Sickness_Level
            int sickness_level = stoi(value);

            if (sickness_level == level) {
                ReplaceCommasWithNewlines(line);
                cout << "----------------------\n";
            }
        }
    }

    // Display patient details
    void DisplayPatientDetails(const Patient &patient) {
        cout << "Name: " << patient.Name << "\n";
        cout << "ID: " << patient.ID << "\n";
        cout << "Age: " << patient.Age << "\n";
        cout << "Gender: " << patient.Gender << "\n";
        cout << "Telephone: " << patient.Telephone << "\n";
        cout << "Date: " << patient.Date << "\n";
        cout << "Symptoms: " << patient.Symptoms << "\n";
        cout << "Sickness Level: " << patient.Sickness_Level << "\n";
        cout << "Time for Treatment: " << patient.Time_Treatment << "\n";
        cout << "Accompany: " << patient.Accompany << "\n";
        cout << "Prescription: " << patient.Prescription << "\n";
        cout << "Consultant: " << patient.Consultant << "\n";
    }

    // Replace commas with newlines for display
    void ReplaceCommasWithNewlines(string &line) {
        for (char &ch : line) {
            if (ch == ',') ch = '\n';
        }
        cout << line << endl;
    }

    // Check for duplicate patient ID
    bool CheckDuplicateID(int id) {
        vector<Patient> patients = LoadPatientsFromFile();
        for (const auto &patient : patients) {
            if (patient.ID == id) return true;
        }
        return false;
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
        cout << "4. Delete Patient\n";
        cout << "5. Update Patient Information\n";
        cout << "6. Display Patient History\n";
        cout << "7. Exit\n";
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
                hospital.DeletePatient();
                break;
            case 5:
                hospital.UpdatePatient();
                break;
            case 6:
                hospital.DisplayHistory();
                break;
            case 7:
                cout << "Exiting program...\n";
                break;
            default:
                cout << "Invalid option. Try again.\n";
        }
    } while (option != 7);

    return 0;
}
