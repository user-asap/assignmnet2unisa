#ifndef PATIENT_H
#define PATIENT_H

#include "Person.h"
#include <vector>
#include <memory>
#include "PatientAlertLevels.h"

class Vitals;

namespace Diagnosis {
    extern const std::string AMOGUS_SUS;
    extern const std::string E_RUSH;
    extern const std::string NOCAP_SYNDROME;
    extern const std::string TICCTOCC_BRAIN_DAMAGE;
};

class Patient : public Person {
public:
    Patient(const std::string& firstName, const std::string& lastName, std::tm birthday);

    int age() const;
    std::string uid() const;
    std::string humanReadableID() const;

    void addDiagnosis(const std::string& diagnosis);
    const std::string& primaryDiagnosis() const;
    const std::vector<std::string>& diagnoses() const;

    void addVitals(const Vitals* v, bool fromfile);
    const std::vector<const Vitals*> vitals() const;

    void setAlertLevel(AlertLevel level);
    const AlertLevel alertLevel() const { return _alertLevel; }

protected:

    void calculateAlertLevel(const Vitals* v); // added declaration of calculateAlertLevel

    std::vector<std::string> _diagnosis;
    std::vector<const Vitals*> _vitals;
    AlertLevel _alertLevel;

    friend std::ostream& operator<<(std::ostream& os, const Patient& p);
};

#endif
