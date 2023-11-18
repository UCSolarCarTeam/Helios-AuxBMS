#include "CheckCurrentTask.h"

uint8_t isCurrentLow()
{
    uint32_t adcVal = readCurrentThroughContactors();
    //CURRENT_LOWER_THRESHOLD
    float pwrVoltage = adcVal * (3.3 / 0xFFF) / GAIN; // change ADC value into the voltage read
    float pwrCurrent = pwrVoltage / CURRENT_SENSE_RESISTOR; // convert voltage to current
    return (pwrCurrent <= CURRENT_LOWER_THRESHOLD);
};

