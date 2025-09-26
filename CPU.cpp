#include "CPU.hpp"

CPU::CPU(std::shared_ptr<Memory> mem, std::shared_ptr<Instructions> inst)
    : memory(mem), instruct(inst) {
    init();
}

CPU::CPU() : memory(std::make_shared<Memory>()), instruct(std::make_shared<Instructions>()) {
    init();
    std::cout << "CPU initialized successfully !\n";
}

CPU::~CPU() {
    std::cout << "CPU shutting down...\n";
}

void CPU::init() {
    setA(0);
    setP(0);
    setPC(0);
    setS(0xFF);
    setX(0);
    setY(0);
}

void CPU::reset() {
    std::cout << "CPU restarting..\n";
    init();
    if ( memory ) memory->readReset();
}

void CPU::updateFlags(uint8_t flags) {
    reg.P = flags;
}