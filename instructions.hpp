#pragma once
#include <iostream>
#include <array>
#include <memory>
#include <functional>
#include <cstdint>
#include <string>

typedef enum {
    Implied,
    Accumulator,
    Immediate,
    ZeroPage,
    ZeroPageX,
    ZeroPageY,
    Relative,
    Absolute,
    AbsoluteX,
    AbsoluteY,
    Indirect,
    IndexedIndirect,
    IndirectIndexed, 
} AddressingMode;

typedef struct {
    std::string_view mnemonic;
    AddressingMode mode;
    std::function<void(AddressingMode)> handler; // Add this line
} InstructionInfo;

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

constexpr size_t NB_OPCODES = 256;

extern std::array<InstructionInfo, NB_OPCODES> opcodes;

constexpr uint8_t FLAG_CARRY     = 0x01; // Carry Flag
constexpr uint8_t FLAG_ZERO      = 0x02; // Zero Flag
constexpr uint8_t FLAG_INTERRUPT = 0x04; // Interrupt Disable
constexpr uint8_t FLAG_DECIMAL   = 0x08; // Decimal Mode
constexpr uint8_t FLAG_BREAK     = 0x10; // Break Command
constexpr uint8_t FLAG_UNUSED    = 0x20; // Unused 
constexpr uint8_t FLAG_OVERFLOW  = 0x40; // Overflow Flag
constexpr uint8_t FLAG_NEGATIVE  = 0x80; // Negative Flag

class CPU;

class InstructionDispatcher {
    private:
        uint8_t flags = 0;
        std::shared_ptr<CPU> cpu;

    public:
        InstructionDispatcher() = default;
        InstructionDispatcher(std::shared_ptr<CPU> cpuPtr);
        ~InstructionDispatcher();

        InstructionInfo DispatchInstruction(uint8_t opcode);

        void setFlag(Flag flag, bool value);
        bool getFlag(Flag flag) const;
};