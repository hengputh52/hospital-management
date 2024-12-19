#include<iostream>
using namespace std;

struct Patient{
    string Name;
    int Age;
    char Gender;
    string Telephone;
    string Date;
    string Symptoms;
    int Sickness_Level; //1: red, yellow: 2
    int Time_Treatment; 
    string Accompany;
    string Prescription;
    string Consultant;
    Patient *Next;
};

class PatientList{
    int size;
    Patient  *rear, *front;

    //constructors
    PatientList(){
        size=0;
        rear=NULL;
        front=NULL;

    }
    void AddPatient()
    {

    }


    //add patient   = enqueue


    //display all pateints

    //display all red-level patients

    //delete / remove patient      dequeue()


    //


};




// struct Red{
//     Patient *Front;
//     Patient *Rear;

    
// };

// struct Yellow{
//     Patient *Front;
//     Patient *Rear;
    
// };

// struct Green{
//     Patient *Front;
//     Patient *Rear; 

// };

int main()
{
    
    
    return 0;
}