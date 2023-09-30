#include "CheckCurrentTask.h"

uint8_t isCurrentLow(uint8_t numContactorsClosed)
{
    uint32_t adcVal = readCurrentThroughContactors();
    float currentThreshold = (numContactorsClosed == 0) ? CURRENT_LOWER_THRESHOLD : CURRENT_LOWER_THRESHOLD * numContactorsClosed;

    float pwrVoltage = adcVal * (3.3 / 0xFFF) / GAIN; // change ADC value into the voltage read
    float pwrCurrent = pwrVoltage / CURRENT_SENSE_RESISTOR; // convert voltage to current
    return (pwrCurrent <= currentThreshold);
}

