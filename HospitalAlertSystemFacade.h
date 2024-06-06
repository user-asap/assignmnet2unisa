#ifndef HOSPITAL_ALERT_SYSTEM_FACADE_H
#define HOSPITAL_ALERT_SYSTEM_FACADE_H

#include "Patient.h"


class HospitalAlertSystemFacade
{
public:
    HospitalAlertSystemFacade();
    virtual ~HospitalAlertSystemFacade();

    void sendAlertForPatient(Patient* p);

};

#endif
