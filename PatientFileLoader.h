#ifndef PATIENT_FILE_LOADER_H
#define PATIENT_FILE_LOADER_H

#include <string>
#include <vector>
#include "AbstractPatientDatabaseLoader.h"


// forward declare the patient class
class Patient;

class PatientFileLoader : public AbstractPatientDatabaseLoader // inheritance
{
public:
    PatientFileLoader(const std::string& file);

    // loads a list of patients from a file
    std::vector<Patient*> loadPatientFile();

    // interface methods
    void initialiseConnection() override {}
    void loadPatients(std::vector<Patient*>& patientIn) override;
    void closeConnection() override {}

private:
    std::string _file;
};

#endif
