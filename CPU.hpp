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

class CPU {
    private:
        Register reg;
        std::shared_ptr<Memory> memory;
        std::shared_ptr<Instructions> instruct;

    public:
        CPU();
        CPU(std::shared_ptr<Memory> mem, std::shared_ptr<Instructions> inst);
        ~CPU();

        void init();
        void reset();

        void updateFlags(uint8_t flags);

        std::shared_ptr<Memory> getMemory() { return memory; }              //Only for testing purposes
        std::shared_ptr<Instructions> getInstruct() { return instruct; }    //Only for testing purposes

        uint8_t getA() const { return reg.A; }
        uint8_t getP() const { return reg.P; }
        uint16_t getPC() const { return reg.PC; }
        uint8_t getS() const { return reg.S; }
        uint8_t getX() const { return reg.X; }
        uint8_t getY() const { return reg.Y; }

        void setA(uint8_t value) { reg.A = value; }
        void setP(uint8_t value) { reg.P = value; }
        void setPC(uint16_t value) { reg.PC = value; }
        void setS(uint8_t value) { reg.S = value; }
        void setX(uint8_t value) { reg.X = value; }
        void setY(uint8_t value) { reg.Y = value; }
};