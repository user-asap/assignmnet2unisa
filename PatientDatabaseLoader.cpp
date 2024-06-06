#include "PatientDatabaseLoader.h"

#include <iomanip>
#include <sstream>

#include "Patient.h"
#include "Vitals.h"


void PatientDatabaseLoader::initialiseConnection()
{
    // pretend this initialises a database connection
}

void PatientDatabaseLoader::loadPatients(std::vector<Patient*>& patientIn){

    // we simulate loading patients from a database here.

    // initialise a birthday from a string. This code can be reused to when loading a birthday from a file
    std::tm t{ };
    std::istringstream ss("18-02-1980");
    ss >> std::get_time(&t, "%d-%m-%Y");

    // push back a new Patient
    Patient* p = new Patient("Joe", "Mama", t);
    p->addDiagnosis(Diagnosis::NOCAP_SYNDROME);
    p->addDiagnosis(Diagnosis::TICCTOCC_BRAIN_DAMAGE);

    Vitals* v = new Vitals(90, 96, 37, 50);
    p->addVitals(v);

    patientIn.push_back(p);

}

void PatientDatabaseLoader::closeConnection()
{
    // pretend this closes the database connection
}
