#pragma once
#include <unordered_map>

struct Contactor {
    GPIO_TypeDef sensePort;
    uint16_t sensePin;
    
    GPIO_TypeDef enablePort;
    uint16_t enablePin;
}
