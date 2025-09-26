#include "instructions.hpp"

Instructions::Instructions() {
    std::cout << "Instructions initialized successfully !\n";
}

Instructions::~Instructions() {
    std::cout << "Instructions cleaned !\n";
}

void Instructions::setFlag(Flag flag, bool value) {
    if (value)
        flags |= (1 << static_cast<uint8_t>(flag));
    else
        flags &= ~(1 << static_cast<uint8_t>(flag));
}

bool Instructions::getFlag(Flag flag) const {
    return (flags >> static_cast<uint8_t>(flag)) & 1;
}