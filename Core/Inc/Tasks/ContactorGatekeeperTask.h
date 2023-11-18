#pragma once
#include <unordered_map>

struct Contactor {
    GPIO_TypeDef sensePort;
    uint16_t sensePin;
    GPIO_TypeDef currentChannel;
    GPIO_TypeDef enablePort;
    uint16_t enablePin;
    uint8_t closed;
    uint8_t opened;
}
