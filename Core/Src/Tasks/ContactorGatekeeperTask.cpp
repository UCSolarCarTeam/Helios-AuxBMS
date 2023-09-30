#include "ContactorGatekeeperTask.h"

void contactorGatekeeperTask(void* arg)
{
    for (;;)
    {
        contactorGatekeeper();
    }
}

Contactor common = {
    COMMON_SENSE_GPIO_Port, 
    COMMON_SENSE_Pin,
    COMMON_ENABLE_GPIO_Port, 
    COMMON_ENABLE_Pin
};

std::unordered_map<uint8_t, Contactor> contactorMap = {{1, common}};


void contactorGatekeeperTask(uint8_t contactorToClose)
{

    // read sense pin
    Contactor contactorInfo = contactorMap[contactorToClose];


    uint8_t sense = !HAL_GPIO_ReadPin(contactorInfo.sensePort, contactorInfo.sensePin);

    

}

