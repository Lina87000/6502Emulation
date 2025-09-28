#pragma once
#include <iostream>
#include <array>
#include <memory>
#include <stdint.h>

#include "memory.hpp"
#include "instructions.hpp"

typedef struct {
    uint8_t A;
    uint8_t P;
    uint16_t PC;
    uint8_t S;
    uint8_t X;
    uint8_t Y;
} Register;

class InstructionDispatcher;

class CPU {
    private:
        Register reg;
        std::shared_ptr<Memory> memory;
        std::shared_ptr<InstructionDispatcher> instruct;

    public:
        CPU();
        CPU(std::shared_ptr<Memory> mem, std::shared_ptr<InstructionDispatcher> inst);
        ~CPU();

        void init();
        void run();
        void reset();

        void updateFlags(uint8_t flags);

        std::shared_ptr<Memory> getMemory() { return memory; }                          //Only for testing purposes
        std::shared_ptr<InstructionDispatcher> getInstruct() { return instruct; }       //Only for testing purposes

        uint16_t Addresser(AddressingMode mode);
        void executeInstruction(uint8_t opcode);

        uint8_t iLDA(AddressingMode mode);
        uint8_t iLDX(AddressingMode mode);
        uint8_t iLDY(AddressingMode mode);
        uint8_t iADC(AddressingMode mode);

        uint8_t getA() const { return reg.A; }
        uint8_t getP() const { return reg.P; }
        uint16_t getPC() const { return reg.PC; }
        uint8_t getPC8() const { return static_cast<uint8_t>(reg.PC & 0xFF); }
        uint8_t getS() const { return reg.S; }
        uint8_t getX() const { return reg.X; }
        uint8_t getY() const { return reg.Y; }

        void setA(uint8_t value) { reg.A = value; }
        void setP(uint8_t value) { reg.P = value; }
        void setPC(uint16_t value) { reg.PC = value; }
        void setS(uint8_t value) { reg.S = value; }
        void setX(uint8_t value) { reg.X = value; }
        void setY(uint8_t value) { reg.Y = value; }

        uint16_t PCIterrate() const { return reg.PC + 1; }
};