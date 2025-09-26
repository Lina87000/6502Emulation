# 6502 Emulation

A simple project using modern C++ semantics to emulate the behaviour of a MOS Technology 6502 8-bit microprocessor and, more specifically, its use in the NES.

This project used as its main source the https://bugzmanov.github.io/nes_ebook/ tutorial, written initially for the Rust programming language.

## Design choice:

First off, I chose C++20 for this project mainly because it is the one I'm most versed in but also for its speed and robustness.

I use a class design to encapsulate each system such that the only way to interact with memory or instructions (or any system present in the NES design) is through the CPU.
This, for instance, prevents any unauthorised ROM write access during execution (an exception is made for testing units in development, of course).
RAII is extensively used, through smart pointers namely, to guarantee memory safety and code simplicity.

Whenever possible, `constexpr` are used for performance and safety (typically memory regions or opcodes).

## Structure:



#### The CPU



The main component of this emulator is the `CPU` (Central Processing Unit) class.

It creates, through constructor overloading, the `memory` and `instructions` objects. Each object has a shared pointer which is used to access their respective methods.

> **Note :** shared pointers are used here to prevent memory errors, as they ensure automatic destruction when appropriate and do not exceed their lifetime. It's a core concept of RAII (Ressource Acquisition Is Initialization).

The `CPU` is responsible for handling ``, using its ``, and writing/reading to/from `memory`.

> **Note :** The `CPU` does not have direct acces to memory. It can only read and write using specific public methods of the `memory` object. These methods will be detailed further.





There are 6 registers: five 8-bit and one 16-bit:
- **A** - Accumulator register (8 bits)
- **P** - Processor status register (8 bits)
- **PC** - Program Counter register (16 bits)
- **S** - Stack pointer register (8 bits)
- **X** - Index register (8 bits)
- **Y** - Index register (8 bits)

Most registers here are fairly generic if you know basic CPU architecture (if you don't, I recommend you read up on it), but I'll go into the details of the P register.
Despite being an 8-bit register, only 7 bits are used, bit 5 being unused. Each bit represents a CPU flag: `CARRY`, `ZERO`, `INTERRUPT`, `DECIMAL`, `UNUSED`, `BREAK`, `OVERFLOW` and `NEGATIVE`.
If you did some assembly before that, how does the CPU handle conditional jump conditions.

#### Memory:

The `memory` structure used by the 6502 chip is actually not that simple. We'll take the naive approach for now.
The memory has a 16-bit address bus and 8-bit memory cells. This means there are $2^{16}$ bytes or 64KB of memory.

It is split into 3 regions: `I/O`, `RAM` and `ROM`. Reading and writing to/from memory can be done 8 bits by 8 bits or 16 bits by 16 bits.

> **Note :** The above descirption is simplistic compared to reality. In reality for instance there is mirror `RAM` and all the memory isn't split in 3 continuous regions. Rather than regions they are types, from an addressing standpoint.

The `memory` has 4 private methods to read and write in 8- and 16-bit modes. These private methods are then called by public methods dedicated to each region.
This prevents unauthorised addressing and unauthorised writing to the `ROM`.

`memory` also has more specialised methods like ``, which reads a special address that points to where the `CPU` should start reading instructions when resetting happens.