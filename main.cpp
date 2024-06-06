// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <memory>
#include <string>

#include "PatientManagementSystem.h"

int main()
{
    std::string patientFile = "patients.txt";
    auto pms = std::make_unique<PatientManagementSystem>(patientFile);


    pms->init();
    pms->run();

    return 0;
}
