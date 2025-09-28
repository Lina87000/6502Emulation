#include "main.hpp"

int main() {

    auto cpu = std::make_shared<CPU>();

    std::vector<uint8_t> program = {     
    0xAD, 0x21, 0x00, // LDA $0021
    0x69, 0x21,       // ADC $21
    0x00
    };

    uint16_t program_start = 0x8000;
    // Set reset vector to program start address
    cpu->getMemory()->writeM(0xFFFC, program_start & 0xFF);        // low byte
    cpu->getMemory()->writeM(0xFFFD, (program_start >> 8) & 0xFF); // high byte
    for (size_t i = 0; i < program.size(); ++i) {
        cpu->getMemory()->writeM(program_start + i, program[i]);
    }
    cpu->getMemory()->writeM(0x0021, 0x42); // Store 0x42 at address $0021
    cpu->run();

    return 0;
}