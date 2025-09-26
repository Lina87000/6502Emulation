#include "main.hpp"

int main() {

    CPU cpu;

    testCPURegisters(cpu);
    testMemory(cpu.getMemory());
    testCPUFlags(cpu.getInstruct());

    return 0;
}