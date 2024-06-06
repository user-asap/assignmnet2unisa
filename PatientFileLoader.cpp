#include "PatientFileLoader.h"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#include "Patient.h"
#include "Vitals.h"

PatientFileLoader::PatientFileLoader(const std::string& file) :
    _file(file)
{
}

std::vector<Patient*> PatientFileLoader::loadPatientFile()
{
    std::vector<Patient*> patients;

    std::ifstream inFile(_file);
    if (inFile.is_open()) {
        // TODO: load your file here
        std::string line;
        while (std::getline(inFile, line)) {
            std::istringstream ss(line);

            std::string uid, birthdayStr, name, diagnosesStr, vitalsStr;
            std::getline(ss, uid, '/'); // read until next slash character
            std::getline(ss, birthdayStr, '/');
            std::getline(ss, name, '/');
            std::getline(ss, diagnosesStr, '/');
            std::getline(ss, vitalsStr, '/');

            std::string lastName = name.substr(0, name.find(","));
            std::string firstName = name.substr(name.find(",") + 1);

            std::tm birthday = {};
            std::istringstream bdaySS(birthdayStr);
            bdaySS >> std::get_time(&birthday, "%d-%m-%Y");

            // create patient object
            Patient* patient = new Patient(firstName, lastName, birthday);

            std::istringstream diagSS(diagnosesStr);
            std::string diagnosis;
            // Adding diagnosis into patient object
            while (std::getline(diagSS, diagnosis, ',')) {
                patient->addDiagnosis(diagnosis);
            }

            std::istringstream vitalsSS(vitalsStr);
            std::string vitalStr;
            while (std::getline(vitalsSS, vitalStr, ';')) {
                std::istringstream vitalStream(vitalStr);
                int hr, spo2, bt, ba;
                char comma;
                vitalStream >> hr >> comma >> spo2 >> comma >> bt >> comma >> ba;
                // creating vitals object
                Vitals* vitals = new Vitals(hr, spo2, bt, ba);
                patient->addVitals(vitals, true); // specifies not to calculate alert 
                // Adding vitals in patient object
            }
            patients.push_back(patient); // Add patient object to Patients vector
        }
    }


    return patients; // returning vector containing list of patients
}

void PatientFileLoader::loadPatients(std::vector<Patient*>& patientIn) {
    std::vector<Patient*> patients = loadPatientFile();
    patientIn.insert(patientIn.end(), patients.begin(), patients.end());
}
