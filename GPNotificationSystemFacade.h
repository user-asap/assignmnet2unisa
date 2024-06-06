#ifndef GP_NOTIFICATION_SYSTEM_FACADE_H
#define GP_NOTIFICATION_SYSTEM_FACADE_H

#include "Patient.h"


class GPNotificationSystemFacade {
public:
    GPNotificationSystemFacade();
    virtual ~GPNotificationSystemFacade();

    void sendGPNotificationForPatient(Patient* p);
};

#endif
