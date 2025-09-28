#pragma once
#include <iostream>
#include <array>
#include <stdint.h>

//#include "instructions.hpp"

constexpr size_t ADDR_SIZE = 0x10000;

constexpr uint16_t RAM_START = 0x0000;
constexpr uint16_t RAM_END = 0x07FF;

constexpr uint16_t IO_START = 0x2000;
constexpr uint16_t IO_END = 0x2007;

constexpr uint16_t ROM_START = 0x8000;
constexpr uint16_t ROM_END = 0xFFFF;

constexpr uint16_t RESET_ADDR = 0xFFFC;

enum class MemMode {
    MODE_8BIT,
    MODE_16BIT
};

class Memory {
    private:
        std::array<uint8_t, ADDR_SIZE> memory;

        uint8_t readM(uint16_t addr);

        uint16_t readM16(uint16_t addr);
        void writeM16(uint16_t addr, uint16_t value);

        uint8_t readROM(uint16_t addr);
        uint16_t readROM16(uint16_t addr);

        uint8_t readRAM(uint16_t addr);
        uint16_t readRAM16(uint16_t addr);
        void writeRAM(uint16_t addr, uint8_t value);
        void writeRAM16(uint16_t addr, uint16_t value);

        uint8_t readIO(uint16_t addr);
        uint16_t readIO16(uint16_t addr);
        void writeIO(uint16_t addr, uint8_t value);
        void writeIO16(uint16_t addr, uint16_t value);

    public:
        Memory();
        ~Memory();

        uint8_t read(uint16_t addr);
        uint16_t read16(uint16_t addr);

        void write(uint16_t addr, uint8_t value);
        void write16(uint16_t addr, uint16_t value);

        void writeM(uint16_t addr, uint8_t value);


        uint16_t readReset();
};