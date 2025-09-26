#include <iostream>
#include <stdint.h>

#include "CPU.hpp"
#include "memory.hpp"

void testCPURegisters(CPU& cpu) {
    const char* GREEN = "\033[32m";
    const char* RED = "\033[31m";
    const char* RESET = "\033[0m";
    auto passfail = [&](bool pass) { return pass ? std::string(GREEN) + "PASS" + RESET : std::string(RED) + "FAIL" + RESET; };

    cpu.setA(42);
    std::cout << "CPU::getA() == 42: " << passfail(cpu.getA() == 42) << std::endl;
    cpu.setP(0xAA);
    std::cout << "CPU::getP() == 0xAA: " << passfail(cpu.getP() == 0xAA) << std::endl;
    cpu.setPC(0x1234);
    std::cout << "CPU::getPC() == 0x1234: " << passfail(cpu.getPC() == 0x1234) << std::endl;
    cpu.setS(0x55);
    std::cout << "CPU::getS() == 0x55: " << passfail(cpu.getS() == 0x55) << std::endl;
    cpu.setX(0x77);
    std::cout << "CPU::getX() == 0x77: " << passfail(cpu.getX() == 0x77) << std::endl;
    cpu.setY(0x88);
    std::cout << "CPU::getY() == 0x88: " << passfail(cpu.getY() == 0x88) << std::endl;
}

void testMemory(std::shared_ptr<Memory> mem) {
    const char* GREEN = "\033[32m";
    const char* RED = "\033[31m";
    const char* RESET = "\033[0m";
    auto passfail = [&](bool pass) { return pass ? std::string(GREEN) + "PASS" + RESET : std::string(RED) + "FAIL" + RESET; };

    // RAM tests
    mem->writeRAM(0x0001, 0xAB);
    std::cout << "Memory::readRAM(0x0001) == 0xAB: " << passfail(mem->readRAM(0x0001) == 0xAB) << std::endl;
    mem->writeRAM16(0x0002, 0xCDEF);
    std::cout << "Memory::readRAM16(0x0002) == 0xCDEF: " << passfail(mem->readRAM16(0x0002) == 0xCDEF) << std::endl;

    // IO tests
    mem->writeIO(0x2000, 0xFE);
    std::cout << "Memory::readIO(0x2000) == 0xFE: " << passfail(mem->readIO(0x2000) == 0xFE) << std::endl;
    mem->writeIO16(0x2001, 0xBEEF);
    std::cout << "Memory::readIO16(0x2001) == 0xBEEF: " << passfail(mem->readIO16(0x2001) == 0xBEEF) << std::endl;

    // ROM tests (read only, expect default value)
    std::cout << "Memory::readROM(0x8000) == 0x00 or 0xFF: " << passfail(mem->readROM(0x8000) == 0x00 || mem->readROM(0x8000) == 0xFF) << std::endl;
    std::cout << "Memory::readROM16(0x8001) == 0x0000 or 0xFFFF: " << passfail(mem->readROM16(0x8001) == 0x0000 || mem->readROM16(0x8001) == 0xFFFF) << std::endl;
}

void testCPUFlags(std::shared_ptr<Instructions> instruct) {
    const char* GREEN = "\033[32m";
    const char* RED = "\033[31m";
    const char* RESET = "\033[0m";
    auto passfail = [&](bool pass) { return pass ? std::string(GREEN) + "PASS" + RESET : std::string(RED) + "FAIL" + RESET; };

    // Example flags: Zero, Carry, Negative, Overflow
    instruct->setFlag(Flag::Zero, true);
    std::cout << "Instructions::getFlag(Zero) == true: " << passfail(instruct->getFlag(Flag::Zero) == true) << std::endl;
    instruct->setFlag(Flag::Zero, false);
    std::cout << "Instructions::getFlag(Zero) == false: " << passfail(instruct->getFlag(Flag::Zero) == false) << std::endl;

    instruct->setFlag(Flag::Carry, true);
    std::cout << "Instructions::getFlag(Carry) == true: " << passfail(instruct->getFlag(Flag::Carry) == true) << std::endl;
    instruct->setFlag(Flag::Carry, false);
    std::cout << "Instructions::getFlag(Carry) == false: " << passfail(instruct->getFlag(Flag::Carry) == false) << std::endl;

    instruct->setFlag(Flag::Negative, true);
    std::cout << "Instructions::getFlag(Negative) == true: " << passfail(instruct->getFlag(Flag::Negative) == true) << std::endl;
    instruct->setFlag(Flag::Negative, false);
    std::cout << "Instructions::getFlag(Negative) == false: " << passfail(instruct->getFlag(Flag::Negative) == false) << std::endl;

    instruct->setFlag(Flag::Overflow, true);
    std::cout << "Instructions::getFlag(Overflow) == true: " << passfail(instruct->getFlag(Flag::Overflow) == true) << std::endl;
    instruct->setFlag(Flag::Overflow, false);
    std::cout << "Instructions::getFlag(Overflow) == false: " << passfail(instruct->getFlag(Flag::Overflow) == false) << std::endl;
}