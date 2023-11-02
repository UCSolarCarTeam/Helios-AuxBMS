#pragma once

// Refer to communications protocol

typedef struct AuxStatus
{
        //check if we need everything, check to see if anything needs to be added, removed. compare it to the new diagram
        //look for changes so we can better incorporate this data
        //communication protocal for AuxBMS 
    unsigned commonContactorState : 1; //: 1 means how many bits it is
    unsigned chargeContactorState : 1;
    unsigned dischargeContactorState : 1;
    unsigned auxVoltage : 5; 
    unsigned highVoltageEnableState : 1;
    unsigned strobeBmsLight : 1;
    unsigned allowCharge : 1; // Tells drivers controls to tell MPPTs and Motor Sculptors not to charge
    unsigned allowDischarge : 1;
    unsigned orionCanReceivedRecently : 1;
    unsigned chargeContactorError : 1;
    unsigned dischargeContactorError : 1;
    unsigned commonContactorError : 1;
    unsigned dischargeShouldTrip : 1;
    unsigned chargeShouldTrip : 1;
    unsigned chargeOpenButShouldBeClosed : 1;
    unsigned dischargeOpenButShouldBeClosed : 1;

    //Trip
    unsigned chargeTripDueToHighCellVoltage : 1;
    unsigned chargeTripDueToHighTemperatureAndCurrent : 1;
    unsigned chargeTripDueToPackCurrent : 1;
    unsigned dischargeTripDueToLowCellVoltage : 1;
    unsigned dischargeTripDueToHighTemperatureAndCurrent : 1;
    unsigned dischargeTripDueToPackCurrent : 1;
    unsigned protectionTrip : 1;
    unsigned dischargeNotClosedDueToHighCurrent: 1;
    unsigned chargeNotClosedDueToHighCurrent: 1;
    unsigned tripDueToOrionMessageTimeout : 1;
    unsigned tripDueToContactorDisconnectingUnexpectedly : 1;

} AuxStatus;
