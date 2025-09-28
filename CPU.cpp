#include "CPU.hpp"

CPU::CPU(std::shared_ptr<Memory> mem, std::shared_ptr<InstructionDispatcher> inst)
    : memory(mem), instruct(inst) {
    init();
}

CPU::CPU() {
    memory = std::make_shared<Memory>();
    instruct = std::make_shared<InstructionDispatcher>(std::shared_ptr<CPU>(this, [](CPU*){}));
    init();
    if (memory) {
        setPC(memory->read16(RESET_ADDR)); // Set PC to reset vector
    }
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

void CPU::run() {
    while(1) {
        uint8_t opcode = memory->read(getPC());
        if (opcode == 0x00) break;
        executeInstruction(opcode);
    }
}

void CPU::updateFlags(uint8_t flags) {
    reg.P = flags;
}

uint16_t CPU::Addresser(AddressingMode mode) {
    switch (mode) {
        case Immediate: {
            // Operand is at PC + 1, advance PC by 2 (opcode + operand)
            uint16_t addr = getPC() + 1;
            setPC(getPC() + 2);
            return addr;
        }
        case ZeroPage: {
            // Operand is at PC + 1, advance PC by 2
            uint8_t zp_addr = memory->read(getPC() + 1);
            setPC(getPC() + 2);
            return zp_addr;
        }
        case ZeroPageX: {
            // Operand is at PC + 1, advance PC by 2
            uint8_t zp_addr = memory->read(getPC() + 1);
            setPC(getPC() + 2);
            return static_cast<uint8_t>(zp_addr + getX());
        }
        case ZeroPageY: {
            // Operand is at PC + 1, advance PC by 2
            uint8_t zp_addr = memory->read(getPC() + 1);
            setPC(getPC() + 2);
            return static_cast<uint8_t>(zp_addr + getY());
        }
        case Absolute: {
            // Operand is at PC + 1 and PC + 2, advance PC by 3
            uint16_t abs_addr = memory->read16(getPC() + 1);
            setPC(getPC() + 3);
            return abs_addr;
        }
        case AbsoluteX: {
            uint16_t abs_addr = memory->read16(getPC() + 1);
            setPC(getPC() + 3);
            return abs_addr + getX();
        }
        case AbsoluteY: {
            uint16_t abs_addr = memory->read16(getPC() + 1);
            setPC(getPC() + 3);
            return abs_addr + getY();
        }
        case IndexedIndirect: { // (Indirect,X)
            uint8_t zp_addr = memory->read(getPC() + 1);
            setPC(getPC() + 2);
            uint8_t ptr = static_cast<uint8_t>(zp_addr + getX());
            uint8_t lowB = memory->read(ptr);
            uint8_t highB = memory->read(static_cast<uint8_t>(ptr + 1));
            return (static_cast<uint16_t>(highB) << 8) | lowB;
        }
        case IndirectIndexed: { // (Indirect),Y
            uint8_t zp_addr = memory->read(getPC() + 1);
            setPC(getPC() + 2);
            uint8_t lowB = memory->read(zp_addr);
            uint8_t highB = memory->read(static_cast<uint8_t>(zp_addr + 1));
            uint16_t base = (static_cast<uint16_t>(highB) << 8) | lowB;
            return base + getY();
        }
        case Accumulator:
        case Implied:
        case Relative:
        case Indirect:
            // These modes do not use memory addressing for operand fetch
            setPC(getPC() + 1); // Advance PC past opcode
            return 0xFFFF;
    }
    return 0xFFFF;
}

void CPU::executeInstruction(uint8_t opcode) {
    InstructionInfo instruction = instruct->DispatchInstruction(opcode);
    if (instruction.handler) {
        instruction.handler(instruction.mode);
    }
}

uint8_t CPU::iLDA(AddressingMode mode) {
    uint16_t addr = Addresser(mode);
    uint8_t value = memory->read(addr);
    setA(value);

    instruct->setFlag(Flag::Zero, value == 0);
    instruct->setFlag(Flag::Negative, value & 0x80);

    std::cout << "LDA $" << std::hex << std::uppercase << (int)value << " to A : " << std::hex << std::uppercase << (int)getA() << std::dec << '\n';

    return value;
}

uint8_t CPU::iLDX(AddressingMode mode) {
    uint16_t addr = Addresser(mode);
    uint8_t value = memory->read(addr);
    setX(value);

    instruct->setFlag(Flag::Zero, value == 0);
    instruct->setFlag(Flag::Negative, value & 0x80);

    return value;
}

uint8_t CPU::iLDY(AddressingMode mode) {
    uint16_t addr = Addresser(mode);
    uint8_t value = memory->read(addr);
    setY(value);

    instruct->setFlag(Flag::Zero, value == 0);
    instruct->setFlag(Flag::Negative, value & 0x80);

    return value;
}

uint8_t CPU::iADC(AddressingMode mode) {
    uint16_t addr = Addresser(mode);
    uint8_t value = memory->read(addr);

    uint8_t a = getA();
    uint8_t carry = instruct->getFlag(Flag::Carry) ? 1 : 0;
    uint16_t sum = a + value + carry;

    setA(static_cast<uint8_t>(sum));

    instruct->setFlag(Flag::Carry, sum > 0xFF);
    instruct->setFlag(Flag::Zero, (sum & 0xFF) == 0);
    instruct->setFlag(Flag::Negative, sum & 0x80);

    std::cout << "ADC $" << std::hex << std::uppercase << (int)value << " to A : " << std::hex << std::uppercase << (int)getA() << std::dec;
    std::cout << " | C = " << instruct->getFlag(Flag::Carry) << '\n';
    return static_cast<uint8_t>(sum);
}