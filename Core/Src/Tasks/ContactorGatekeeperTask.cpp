#include "ContactorGatekeeperTask.h"
#include<list>

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

Contactor charge = {
    CHARGE_SENSE_GPIO_Port, 
    CHARGE_SENSE_Pin,
    CHARGE_ENABLE_GPIO_Port, 
    CHARGE_ENABLE_Pin
}; 

Contactor discharge = {
    DISCHARGE_SENSE_GPIO_Port, 
    DISCHARGE_SENSE_Pin,
    DISCHARGE_ENABLE_GPIO_Port, 
    DISCHARGE_ENABLE_Pin
}; 

std::unordered_map<uint8_t, Contactor> contactorMap = {{0, common}, {1, charge}, {2, discharge}};
//added this below for the list of the dischargeStates, idk if this right
std::list<Contactor> isContactorClosed = {};

void contactorGatekeeperTask(uint8_t contactorToClose)
{

    // read sense pin
    Contactor contactorInfo = contactorMap[contactorToClose];
    

    uint8_t sense = !HAL_GPIO_ReadPin(contactorInfo.sensePort, contactorInfo.sensePin);
    
    
    uint8_t isContactorClosed = auxBmsContactorState.dischargeState == CLOSED || auxBmsContactorState.dischargeState == CLOSING;
    //list of closed contactors 
    //^global in terms of this task
    //as contactor is closed it will stored into the list
    //list/vector
    //we dont need a closing state
    //assk marcelo
    //to remove the closing thing u need to always update before doing other stuff to see if it is closed
    
    //if isDischargeClosed is true it will go to isCuurentLow(1), otherwise it will go to isCurrentLow(0)
    uint8_t currentLow = isDischargeClosed ? isCurrentLow(1) : isCurrentLow(0);
    uint8_t contactorError = !(currentLow && sense);    

}




void openContactor()
{
    //get the values from the hashmap for port and pin
    HAL_GPIO_WritePin(MPPT_ENABLE_GPIO_Port, MPPT_ENABLE_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(CHARGE_ENABLE_GPIO_Port, CHARGE_ENABLE_Pin, GPIO_PIN_RESET);
    auxBmsContactorState.chargeState = OPEN;
    osThreadSetPriority (chargeContactorGatekeeperTaskHandle, osPriorityNormal);
}


