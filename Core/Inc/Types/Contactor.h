struct Contactor {
    GPIO_TypeDef sensePort;
    uint16_t sensePin;
    
    GPIO_TypeDef enablePort;
    uint16_t enablePin;
}

#define COMMON 0