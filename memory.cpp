#include "memory.hpp"

Memory::Memory() {
    std::fill(std::begin(memory), std::end(memory), 0);
    writeM16(RESET_ADDR, ROM_START);
    std::cout << "Memory initialized successfully !\n";
}

Memory::~Memory() {
    std::cout << "Memory cleaned !\n";
}

uint8_t Memory::readM(uint16_t addr) {
    return memory[addr];
}

void Memory::writeM(uint16_t addr, uint8_t value) {
    memory[static_cast<size_t>(addr)] = value;
}

uint16_t Memory::readM16(uint16_t addr) {
    uint8_t lowB = readM(addr);
    uint8_t highB = readM(addr + 1);
    return (highB << 8) | lowB;
}

void Memory::writeM16(uint16_t addr, uint16_t value) {
    uint8_t highB = (value >> 8) & 0xFF;
    uint8_t lowB = value & 0xFF;
    writeM(addr, lowB);
    writeM(addr + 1, highB);
}

uint8_t Memory::readROM(uint16_t addr) {
    if (addr >= ROM_START && addr <= ROM_END) {
        return readM(addr);
    } else {
        std::cerr << "Attempted to read outside ROM region: " << std::hex << addr << "\n";
        return 0xFF;
    }
}

uint16_t Memory::readROM16(uint16_t addr) {
    if (addr >= ROM_START && addr <= ROM_END - 1) {
        return readM16(addr);
    } else {
        std::cerr << "Attempted to read outside ROM region: " << std::hex << addr << "\n";
        return 0xFFFF;
    }
}

uint8_t Memory::readRAM(uint16_t addr) {
    if (addr >= RAM_START && addr <= RAM_END) {
        return readM(addr);
    } else {
        std::cerr << "Attempted to read outside RAM region: " << std::hex << addr << "\n";
        return 0xFF;
    }
}

uint16_t Memory::readRAM16(uint16_t addr) {
    if (addr >= RAM_START && addr <= RAM_END - 1) {
        return readM16(addr);
    } else {
        std::cerr << "Attempted to read outside RAM region: " << std::hex << addr << "\n";
        return 0xFFFF;
    }
}

void Memory::writeRAM(uint16_t addr, uint8_t value) {
    if (addr >= RAM_START && addr <= RAM_END) {
        writeM(addr, value);
    } else {
        std::cerr << "Attempted to write outside RAM region: " << std::hex << addr << "\n";
        return;
    }
}

void Memory::writeRAM16(uint16_t addr, uint16_t value) {
    if (addr >= RAM_START && addr <= RAM_END - 1) {
        writeM16(addr, value);
    } else {
        std::cerr << "Attempted to write outside RAM region: " << std::hex << addr << "\n";
        return;
    }
}

uint8_t Memory::readIO(uint16_t addr) {
    if (addr >= IO_START && addr <= IO_END) {
        return readM(addr);
    } else {
        std::cerr << "Attempted to read outside I/O region: " << std::hex << addr << "\n";
        return 0xFF;
    }
}

uint16_t Memory::readIO16(uint16_t addr) {
    if (addr >= IO_START && addr <= IO_END - 1) {
        return readM16(addr);
    } else {
        std::cerr << "Attempted to read outside I/O region: " << std::hex << addr << "\n";
        return 0xFFFF;
    }
}

void Memory::writeIO(uint16_t addr, uint8_t value) {
    if (addr >= IO_START && addr <= IO_END) {
        writeM(addr, value);
    } else {
        std::cerr << "Attempted to write outside I/O region: " << std::hex << addr << "\n";
        return;
    }
}

void Memory::writeIO16(uint16_t addr, uint16_t value) {
    if (addr >= IO_START && addr <= IO_END - 1) {
        writeM16(addr, value);
    } else {
        std::cerr << "Attempted to write outside I/O region: " << std::hex << addr << "\n";
        return;
    }
}

 uint16_t Memory::readReset() {
    return readM(RESET_ADDR);
 }