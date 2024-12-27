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
    int Red_Size, Yellow_Size, Green_Size;
    Patient *Red_Front, *Red_Rear;
    Patient *Yellow_Front, *Yellow_Rear;
    Patient *Green_Front, *Green_Rear;

public:
    // Constructor
    PatientList() {
        Red_Size = Yellow_Size = Green_Size = 0;
        Red_Front = Red_Rear = NULL;
        Yellow_Front = Yellow_Rear =NULL;
        Green_Front = Green_Rear = NULL;
        
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

        ''
       

    
        cout << "Patient added successfully!\n";
    }


    void PatientOperation()
    {
        //red has to display first then yellow and green 


        cout<<"-----------------Patient Operation------------------\n";

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

    //add patient in queue
    void Enqueue(Patient *&front, Patient *&rear, Patient *newPatient)
    {
        if(IsEmpty(front))
        {
            front = rear = newPatient;
        }
        else
        {
            rear->Next = newPatient;
            rear = newPatient;
        }

    }


    //opearting the patient by remove first element in queue
    void Dequeue()
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
   bool IsEmpty(Patient *front)
   {
        return front= NULL;
   }
};

// Main function
int main() {
    PatientList hospital;

    int option;
    do{
        cout<<"---------------------Welcome to our Sabay Hospital------------------ "<<endl;
        cout<<"1. Register Patient\n";
        cout<<"2.Display All Patient\n";
        cout<<"3.Exit\n";
        cout<<"Please Choose Option Above: ";
        cin>>option;

        switch (option)
        {
            case 1:
            cout<<"---------------------------Pateint Registration--------------------\n";
            hospital.AddPatient();
            break;

            case 2:
            cout<<"-------------------------Display All Patient Information---------------\n";
            hospital.DisplayPatients();
            break;
            
            case 3:
            cout<<"------------------------------Exiting Program-----------------------\n";
            break;

            default:
            cout<<"----------Please Enter Valid Option-----------\n";

        }
    }
    while(option!=3);


    return 0;
}
