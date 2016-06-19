#ifndef _ALU_HPP
#define _ALU_HPP

#include <cstdint>
#include <map>
#include <string>
#include "block.hpp"
#include "flash.hpp"
#include "sfr.hpp"

class Cpu8051;
class Command;
class Instruction;

class Alu : public Block
{
  friend class SfrSp;
  friend class SfrDpl;
  public:
    Flash *flash;
    Memory xram;
    Memory iram;
    std::string Disassemble(std::uint16_t address);
    std::uint8_t GetOperands(std::uint16_t address);
    Alu(std::string name, std::uint16_t xramSize, std::uint16_t iramSize);
    void Reset();
    void Step();
    std::uint16_t GetPC();
    std::uint8_t GetSP();
    std::uint8_t GetA();
    void SetPC(std::uint16_t pc);
    void SetSP(std::uint8_t sp);
    void SetA(std::uint8_t data);
    std::uint16_t GetDP();
    void RegisterSfr(Sfr *sfr);
    std::uint8_t GetReg(std::uint8_t reg);
    void SetReg(std::uint8_t reg, std::uint8_t value);
    void SetDPTR(std::uint16_t val);
    std::uint16_t GetDPTR();
    std::uint8_t GetB() const;
    bool GetC();
    void SetC();
    void ClrC();
    void SetAC();
    void ClrAC();
    void SetOV();
    void ClrOV();

    // Handles byte access to IRAM as well as SFR
    std::uint8_t Read(std::uint8_t address);
    void Write(std::uint8_t address, std::uint8_t value);
    // Handles writes done via 'MOVX' - these can go to either flash or external RAM
    void WriteX(std::uint16_t address, std::uint8_t value);

    // Handles bit access to bit-addressable IRAM as well as SFR
    bool ReadBit(std::uint8_t address);
    void WriteBit(std::uint8_t address, bool value);
    // Get readable name of bit address
    std::string GetBitAddressName(std::uint8_t address);

    bool GetTraceSfr();
    void SetTraceSfr(bool val);

    Memory *GetIRam() const;
    void SetFlash(Flash *flash);
    void RegisterCallback(Command *cb, Cpu8051* cpu);
    Command *GetCallback() const;
    Cpu8051* GetCallbackCpu() const;
    int CalculateRemainingTicks();
    void ClockEvent();
    void TimerInterrupt(int timer);
    void UartInterrupt();
    std::map<std::uint8_t, std::map<std::uint8_t, Sfr*> > specialFunctionRegisters;
    std::map<std::uint8_t, SfrBitAddressable*> bitAddressableSfr;
  private:
    std::map<std::uint8_t, Instruction*> instructionSet;
    std::uint16_t pc;
    Sfr sfrSP;
    Sfr sfrDPL;
    Sfr sfrDPH;
    Sfr sfrIP;
    Sfr sfrPSW;
    SfrBitAddressable sfrIE;
    Sfr sfrSFRPAGE;
    SfrBitAddressable sfrB;
    SfrBitAddressable sfrACC;
    Sfr sfrPCON;
    Sfr sfrPSCTL;
    bool traceSfr;
    int tickCount;
    Command *callbacks;
    Cpu8051* callbackCpu;
    std::uint8_t interruptPending;
};

#endif
