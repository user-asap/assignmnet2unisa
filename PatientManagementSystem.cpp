#include "PatientManagementSystem.h"

#include <iostream>
#include <map>
#include <tuple>

#include "Patient.h"
#include "PatientDatabaseLoader.h"
#include "Vitals.h"

#include "GPNotificationSystemFacade.h"
#include "HospitalAlertSystemFacade.h"

using namespace std;


PatientManagementSystem::PatientManagementSystem() :
    _patientDatabaseLoader(std::make_unique<PatientDatabaseLoader>()),
    _hospitalAlertSystem(std::make_unique<HospitalAlertSystemFacade>()),
    _gpNotificationSystem(std::make_unique<GPNotificationSystemFacade>())
{
    _patientDatabaseLoader->initialiseConnection();
}

PatientManagementSystem::~PatientManagementSystem()
{
    _patientDatabaseLoader->closeConnection();

    // clear patient memory
    for (Patient* p : _patients) {
        delete p;
    }
}

void PatientManagementSystem::init()
{
    _patientDatabaseLoader->loadPatients(_patients);
    for (Patient* p : _patients) {
        _patientLookup[p->uid()] = p;
    }

    for (Patient* p : _patients) {
        // TODO: do any processing you need here
    }
}

void PatientManagementSystem::run()
{
    printWelcomeMessage();

    bool running = true;
    while (running) {
        printMainMenu();
        int option = 0;
        cin >> option;

        // handle basic errors
        if (cin.bad()) {
            cin.clear();
            cin.ignore();
            continue;
        }

        // switch based on the selected option
        switch (option) {
        case 1:
            addVitalsRecord();
            break;
        case 2:
            printPatients();
            break;
        case 3:
            running = false;
            break;
        }
    }
}

void PatientManagementSystem::addVitalsRecord()
{
    cout << "Patients" << endl;
    printPatients();
    cout << endl;
    cout << "Enter the patient ID to declare vitals for > ";
    
    string pid { "" };
    cin >> pid;
    if (_patientLookup.count(pid)) {
        int heartRate;
        int oxygenSaturation;
        int bodyTemperature;
        int brainActivity;

        cout << "Enter hear rate: ";
        cin >> heartRate;
        cout << "Enter oxygen saturation: ";
        cin >> oxygenSaturation;
        cout << "Enter body temperature: ";
        cin >> bodyTemperature;
        cout << "Enter brain activity: ";
        cin >> brainActivity;

        Vitals* v = new Vitals(heartRate, oxygenSaturation, bodyTemperature, brainActivity);
        _patientLookup[pid]->addVitals(v);
    }
    else {
        cout << "Patient not found" << endl;
    }
}

void PatientManagementSystem::printWelcomeMessage() const
{
    cout << "WELCOME TO DOCTRACK 2000" << endl;
    cout << "------------------------" << endl;
}

void PatientManagementSystem::printMainMenu() const
{
    cout << endl << "Select an option:" << endl;
    cout << "1. Record new vitals" << endl;
    cout << "2. List patients" << endl;
    cout << "3. Quit" << endl;
    cout << "> ";
}

void PatientManagementSystem::printPatients() const
{
    for (Patient* p : _patients) {
        std::cout << *p << std::endl;
    }
}
