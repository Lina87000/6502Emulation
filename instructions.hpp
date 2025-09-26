#pragma once
#include <iostream>
#include <array>
#include <memory>
#include <functional>
#include <stdint.h>

constexpr uint8_t FLAG_CARRY     = 0x01; // Carry Flag
constexpr uint8_t FLAG_ZERO      = 0x02; // Zero Flag
constexpr uint8_t FLAG_INTERRUPT = 0x04; // Interrupt Disable
constexpr uint8_t FLAG_DECIMAL   = 0x08; // Decimal Mode
constexpr uint8_t FLAG_BREAK     = 0x10; // Break Command
constexpr uint8_t FLAG_UNUSED    = 0x20; // Unused 
constexpr uint8_t FLAG_OVERFLOW  = 0x40; // Overflow Flag
constexpr uint8_t FLAG_NEGATIVE  = 0x80; // Negative Flag

constexpr uint8_t OPCodeSize = 256;

enum class Flag : uint8_t {
    Carry     = 0,
    Zero      = 1,
    Interrupt = 2,
    Decimal   = 3,
    Break     = 4,
    Unused    = 5,
    Overflow  = 6,
    Negative  = 7
};

enum class AddressingMode { 
    Immediate, 
    ZeroPage, 
    ZeroPage_X, 
    Absolute, 
    Absolute_X, 
    Absolute_Y, 
    Indirect_X, 
    Indirect_Y
};

class Instructions {
    private:
        uint8_t flags = 0;

    public:
        Instructions();
        ~Instructions();

        void setFlag(Flag flag, bool value);
        [[nodiscard]] bool getFlag(Flag flag) const;
};