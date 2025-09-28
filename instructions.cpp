#include "instructions.hpp"
#include "CPU.hpp"

std::array<InstructionInfo, NB_OPCODES> opcodes = []{
    std::array<InstructionInfo, NB_OPCODES> arr{};
    for (size_t i = 0; i < NB_OPCODES; ++i)
        arr[i] = { "---", AddressingMode::Implied, [](AddressingMode) {} };
    arr[0x00] = { "BRK", AddressingMode::Implied, [](AddressingMode) {} };
    arr[0x01] = { "ORA", AddressingMode::IndexedIndirect, [](AddressingMode) {} };
    arr[0x05] = { "ORA", AddressingMode::ZeroPage, [](AddressingMode) {} };
    arr[0x06] = { "ASL", AddressingMode::ZeroPage, [](AddressingMode) {} };
    arr[0x08] = { "PHP", AddressingMode::Implied, [](AddressingMode) {} };
    arr[0x09] = { "ORA", AddressingMode::Immediate, [](AddressingMode) {} };
    arr[0x0A] = { "ASL", AddressingMode::Accumulator, [](AddressingMode) {} };
    arr[0x0D] = { "ORA", AddressingMode::Absolute, [](AddressingMode) {} };
    arr[0x0E] = { "ASL", AddressingMode::Absolute, [](AddressingMode) {} };
    arr[0x10] = { "BPL", AddressingMode::Relative, [](AddressingMode) {} };
    arr[0x11] = { "ORA", AddressingMode::IndirectIndexed, [](AddressingMode) {} };
    arr[0x15] = { "ORA", AddressingMode::ZeroPageX, [](AddressingMode) {} };

    arr[0x61] = { "ADC", AddressingMode::IndirectIndexed, [](AddressingMode) {} };
    arr[0x65] = { "ADC", AddressingMode::ZeroPage, [](AddressingMode) {} };
    arr[0x69] = { "ADC", AddressingMode::Immediate, [](AddressingMode) {} };
    arr[0x6D] = { "ADC", AddressingMode::Absolute, [](AddressingMode) {} };
    arr[0x71] = { "ADC", AddressingMode::IndexedIndirect, [](AddressingMode) {} };
    arr[0x75] = { "ADC", AddressingMode::ZeroPageX, [](AddressingMode) {} };
    arr[0x79] = { "ADC", AddressingMode::AbsoluteY, [](AddressingMode) {} };
    arr[0x7D] = { "ADC", AddressingMode::AbsoluteX, [](AddressingMode) {} };

    arr[0xA1] = { "LDA", AddressingMode::IndexedIndirect, [](AddressingMode) {} };
    arr[0xA5] = { "LDA", AddressingMode::ZeroPage, [](AddressingMode) {} };
    arr[0xA9] = { "LDA", AddressingMode::Immediate, [](AddressingMode) {} };
    arr[0xAD] = { "LDA", AddressingMode::Absolute, [](AddressingMode) {} };
    arr[0xB1] = { "LDA", AddressingMode::IndirectIndexed, [](AddressingMode) {} };
    arr[0xB5] = { "LDA", AddressingMode::ZeroPageX, [](AddressingMode) {} };
    arr[0xB9] = { "LDA", AddressingMode::AbsoluteY, [](AddressingMode) {} };
    arr[0xBD] = { "LDA", AddressingMode::AbsoluteX, [](AddressingMode) {} };

    arr[0xA2] = { "LDX", AddressingMode::Immediate, [](AddressingMode) {} };
    arr[0xA6] = { "LDX", AddressingMode::ZeroPage, [](AddressingMode) {} };
    arr[0xB6] = { "LDX", AddressingMode::ZeroPageY, [](AddressingMode) {} };
    arr[0xAE] = { "LDX", AddressingMode::Absolute, [](AddressingMode) {} };
    arr[0xBE] = { "LDX", AddressingMode::AbsoluteY, [](AddressingMode) {} };

    arr[0xA0] = { "LDY", AddressingMode::Immediate, [](AddressingMode) {} };
    arr[0xA4] = { "LDY", AddressingMode::ZeroPage, [](AddressingMode) {} };
    arr[0xB4] = { "LDY", AddressingMode::ZeroPageX, [](AddressingMode) {} };
    arr[0xAC] = { "LDY", AddressingMode::Absolute, [](AddressingMode) {} };
    arr[0xBC] = { "LDY", AddressingMode::AbsoluteX, [](AddressingMode) {} };

    return arr;
}();

InstructionDispatcher::InstructionDispatcher(std::shared_ptr<CPU> cpuPtr) : cpu(cpuPtr) {
    std::cout << "Instructions initialized successfully !\n";

    opcodes[0xA1].handler = [cpuPtr](AddressingMode mode) { cpuPtr->iLDA(mode); };
    opcodes[0xA5].handler = [cpuPtr](AddressingMode mode) { cpuPtr->iLDA(mode); };
    opcodes[0xA9].handler = [cpuPtr](AddressingMode mode) { cpuPtr->iLDA(mode); };
    opcodes[0xAD].handler = [cpuPtr](AddressingMode mode) { cpuPtr->iLDA(mode); };
    opcodes[0xB1].handler = [cpuPtr](AddressingMode mode) { cpuPtr->iLDA(mode); };
    opcodes[0xB5].handler = [cpuPtr](AddressingMode mode) { cpuPtr->iLDA(mode); };
    opcodes[0xB9].handler = [cpuPtr](AddressingMode mode) { cpuPtr->iLDA(mode); };
    opcodes[0xBD].handler = [cpuPtr](AddressingMode mode) { cpuPtr->iLDA(mode); };

    opcodes[0xA2].handler = [cpuPtr](AddressingMode mode) { cpuPtr->iLDX(mode); };
    opcodes[0xA6].handler = [cpuPtr](AddressingMode mode) { cpuPtr->iLDX(mode); };
    opcodes[0xB6].handler = [cpuPtr](AddressingMode mode) { cpuPtr->iLDX(mode); };
    opcodes[0xAE].handler = [cpuPtr](AddressingMode mode) { cpuPtr->iLDX(mode); };
    opcodes[0xBE].handler = [cpuPtr](AddressingMode mode) { cpuPtr->iLDX(mode); };

    opcodes[0xA0].handler = [cpuPtr](AddressingMode mode) { cpuPtr->iLDY(mode); };
    opcodes[0xA4].handler = [cpuPtr](AddressingMode mode) { cpuPtr->iLDY(mode); };
    opcodes[0xB4].handler = [cpuPtr](AddressingMode mode) { cpuPtr->iLDY(mode); };
    opcodes[0xAC].handler = [cpuPtr](AddressingMode mode) { cpuPtr->iLDY(mode); };
    opcodes[0xBC].handler = [cpuPtr](AddressingMode mode) { cpuPtr->iLDY(mode); };

    opcodes[0x61].handler = [cpuPtr](AddressingMode mode) { cpuPtr->iADC(mode); };
    opcodes[0x65].handler = [cpuPtr](AddressingMode mode) { cpuPtr->iADC(mode); };
    opcodes[0x69].handler = [cpuPtr](AddressingMode mode) { cpuPtr->iADC(mode); };
    opcodes[0x6D].handler = [cpuPtr](AddressingMode mode) { cpuPtr->iADC(mode); };
    opcodes[0x71].handler = [cpuPtr](AddressingMode mode) { cpuPtr->iADC(mode); };
    opcodes[0x75].handler = [cpuPtr](AddressingMode mode) { cpuPtr->iADC(mode); };
    opcodes[0x79].handler = [cpuPtr](AddressingMode mode) { cpuPtr->iADC(mode); };
    opcodes[0x7D].handler = [cpuPtr](AddressingMode mode) { cpuPtr->iADC(mode); };
}

InstructionDispatcher::~InstructionDispatcher() {
    std::cout << "Instructions cleaned !\n";
}

void InstructionDispatcher::setFlag(Flag flag, bool value) {
    if (value)
        flags |= (1 << static_cast<uint8_t>(flag));
    else
        flags &= ~(1 << static_cast<uint8_t>(flag));
}

bool InstructionDispatcher::getFlag(Flag flag) const {
    return (flags >> static_cast<uint8_t>(flag)) & 1;
}

InstructionInfo InstructionDispatcher::DispatchInstruction(uint8_t opcode) {
    return opcodes[opcode];
}