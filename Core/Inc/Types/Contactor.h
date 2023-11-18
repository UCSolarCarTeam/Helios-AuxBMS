struct Contactor {
    //internal tasks for contacotrs
    //attributes of the contactors*
    //add state it is in*
    //add ememergency close contactor state*
    //very similar to contactorStateInfo~/contactorStatus in old AuxBMS

    GPIO_TypeDef sensePort;
    uint16_t sensePin;
    
    GPIO_TypeDef enablePort;
    uint16_t enablePin;
};

#define COMMON 0;
#define CHARGE 1;
#define DISCHARGE 2;
