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
    COMMON_CURRENT_CHANNEL,
    COMMON_ENABLE_GPIO_Port, 
    COMMON_ENABLE_Pin
};

Contactor charge = {
    CHARGE_SENSE_GPIO_Port, 
    CHARGE_SENSE_Pin,
    CHARGE_CURRENT_CHANNEL,
    CHARGE_ENABLE_GPIO_Port, 
    CHARGE_ENABLE_Pin
}; 

Contactor discharge = {
    DISCHARGE_SENSE_GPIO_Port, 
    DISCHARGE_SENSE_Pin,
    DISCHARGE_CURRENT_CHANNEL,
    DISCHARGE_ENABLE_GPIO_Port, 
    DISCHARGE_ENABLE_Pin
}; 

std::unordered_map<uint8_t, Contactor> contactorMap = {{0, common}, {1, charge}, {2, discharge}};
//added this below for the list of the dischargeStates, idk if this right
std::list<Contactor> isContactorClosed = {};
//should switch to ETL if we run into any errors!!!!


//Ask jessie why this is in C++


void contactorGatekeeperTask(uint8_t contactorToClose)
{

    // read sense pin
    Contactor contactorInfo = contactorMap[contactorToClose];
    //set charge state to closing
    auxBmsContactorState.contactorInfo = CLOSING;
    //Enable the contactor then wait
    uint8_t orionDischargeEnableSense = HAL_GPIO_ReadPin(discharge.sensePort, discharge.sensePin);
    uint8_t orionChargeEnableSense = HAL_GPIO_ReadPin(charge.sensePort, charge.sensePin);
    uint8_t orionCommonEnableSense = HAL_GPIO_ReadPin(common.sensePort, common.sensePin);
    HAL_GPIO_WritePin(contactorInfo.enablePort, contactorInfo.enablePin, GPIO_PIN_SET);
    //delay variable is hardcorded
    osDelay(1000);

    // Check to make sure contactor is acutally closed and if the sense pin is closed
    uint8_t sense = !HAL_GPIO_ReadPin(contactorInfo.sensePort, contactorInfo.sensePin);
    uint8_t currentLow = isCurrentLow(1);
    orionChargeEnableSense = HAL_GPIO_ReadPin(charge.sensePort, charge.sensePin);
    orionCommonEnableSense = HAL_GPIO_ReadPin(common.sensePort, common.sensePin);
    
    if (sense && currentLow) // Common contactor closed successfully, so trigger charge to turn on
    {
        auxBmsContactorState.contactorInfo = CLOSED;
    }
    else // Common contactor not closed successfully, so delay then try again
    {
        auxBmsContactorState.contactorInfo = CONTACTOR_ERROR;
        HAL_GPIO_WritePin(contactorInfo.enablePort, contactorInfo.enablePin, GPIO_PIN_RESET);
        osDelay(1000);
        osEventFlagsSet(contactorControlEventBits, )
        //                                       ^^^I dont know what to put here for the second parameter cuz in the old code it hard-coded COMMON_CLOSED
    }
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


