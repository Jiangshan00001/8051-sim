/*
 * Copyright (C) 2016 Sensative AB
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include <vector>
#include <ncurses.h>
#include "command.hpp"
#include "cpu8051.hpp"
#include "instruction_coverage.hpp"
#include "shell.hpp"
#include "symbol_table.hpp"

constexpr auto blockCmd = "block";
constexpr auto breakListCmd = "break list";
constexpr auto breakSetCmd = "break set";
constexpr auto breakClearCmd = "break clear";
constexpr auto traceSfrOnCmd = "trace sfr on";
constexpr auto traceSfrOffCmd = "trace sfr off";
constexpr auto traceNoneCmd = "trace none";
constexpr auto traceAllCmd = "trace all";
constexpr auto traceInstructionCmd = "trace instruction";
constexpr auto coverageInitializeCmd = "coverage initialize";
constexpr auto coverageListCmd = "coverage list";
constexpr auto uartRxCmd = "uart rx";
constexpr auto resetCmd = "reset";
constexpr auto registersCmd = "registers";
constexpr auto stepCmd = "step once";
constexpr auto stepInstructionsCmd = "step instructions";
constexpr auto runCmd = "run";
constexpr auto goCmd = "go";
constexpr auto loadCmd = "load";
constexpr auto disassembleCmd = "disassemble";
constexpr auto flashCmd = "flash";
constexpr auto iramCmd = "iram";

Command::Command(Shell &s) :
  instructionCount(0),
  instructionLimit(0),
  breakCount(0),
  breakLimit(0),
  shell(s)
{
  shell.RegisterCommand(blockCmd, this);
  shell.RegisterCommand(breakListCmd, this);
  shell.RegisterCommand(breakSetCmd, this, {ParameterType::Numeric});
  shell.RegisterCommand(breakClearCmd, this);
  shell.RegisterCommand(traceSfrOnCmd, this);
  shell.RegisterCommand(traceSfrOffCmd, this);
  shell.RegisterCommand(traceNoneCmd, this);
  shell.RegisterCommand(traceAllCmd, this);
  shell.RegisterCommand(traceInstructionCmd, this, {ParameterType::Numeric});
  shell.RegisterCommand(coverageInitializeCmd, this);
  shell.RegisterCommand(coverageListCmd, this);
  shell.RegisterCommand(uartRxCmd, this, {ParameterType::String});
  shell.RegisterCommand(resetCmd, this);
  shell.RegisterCommand(registersCmd, this);
  shell.RegisterCommand(stepCmd, this);
  shell.RegisterCommand(stepInstructionsCmd, this, {ParameterType::Numeric});
  shell.RegisterCommand(runCmd, this);
  shell.RegisterCommand(goCmd, this, {ParameterType::Numeric});
  shell.RegisterCommand(loadCmd, this, {ParameterType::String});
  shell.RegisterCommand(disassembleCmd, this, {ParameterType::Numeric, ParameterType::Numeric});
  shell.RegisterCommand(flashCmd, this, {ParameterType::Numeric, ParameterType::Numeric});
  shell.RegisterCommand(iramCmd, this, {ParameterType::Numeric, ParameterType::Numeric});
  for (int i = 0; i < NumBreakpoints; i++)
  {
    breakpoints[i] = -1;
  }
  for (int i = 0; i < 256; i++)
  {
    trace[i] = false;
  }
}

void Command::OnCommand(Cpu8051 &cpu, std::string command, std::vector<Parameter*> parameters)
{
  cpu.alu.RegisterCallback(this, &cpu);
  if (!command.compare(blockCmd))
  {
    for (std::vector<Block*>::iterator i = cpu.blocks.begin(); i != cpu.blocks.end(); i++)
    {
      int t = (*i)->remainingTicks;
      printw("%s ", (*i)->GetName().c_str());
      if (t == -1)
      {
        printw("idle");
      }
      else
      {
        printw("%d", t);
      }
      printw("\n");
    }
  }
  else if (!command.compare(breakListCmd))
  {
    for (int i = 0; i < NumBreakpoints; i++)
    {
      if (breakpoints[i] != -1)
      {
        printw("%x\n", breakpoints[i]);
      }
    }
  }
  else if (!command.compare(breakClearCmd))
  {
    for (int i = 0; i < NumBreakpoints; i++)
    {
      breakpoints[i] = -1;
    }
  }
  else if (!command.compare(breakSetCmd))
  {
    for (int i = 0; i < NumBreakpoints; i++)
    {
      if (breakpoints[i] == -1)
      {
        breakpoints[i] = parameters[0]->number;
        break;
      }
    }
  }
  else if (!command.compare(traceSfrOnCmd))
  {
    cpu.alu.SetTraceSfr(true);
  }
  else if (!command.compare(traceSfrOffCmd))
  {
    cpu.alu.SetTraceSfr(false);
  }
  else if (!command.compare(traceAllCmd))
  {
    for (int i = 0; i <= 255; i++)
    {
      trace[i] = true;
    }
  }
  else if (!command.compare(traceNoneCmd))
  {
    for (int i = 0; i <= 255; i++)
    {
      trace[i] = true;
    }
  }
  else if (!command.compare(traceInstructionCmd))
  {
    trace[parameters[0]->number] = true;
  }
  else if (!command.compare(coverageInitializeCmd))
  {
    int total, executed;

    InstructionCoverage::GetInstance().Initialize(cpu.alu);
    InstructionCoverage::GetInstance().GetCoverage(total, executed);
    printw("Found %d instructions\n", total);
  }
  else if (!command.compare(coverageListCmd))
  {
    int total, executed;
    InstructionCoverage::GetInstance().GetCoverage(total, executed);
    printw("Total: %d executed: %d percentage: %f\n", total, executed, (100.0*executed) / total);
  }
  else if (!command.compare(uartRxCmd))
  {
    cpu.uart.SimulateRx(parameters[0]->string[0]);
  }
  else if (!command.compare(resetCmd))
  {
    cpu.Reset();
  }
  else if (!command.compare(registersCmd))
  {
    printw("PC:%4.4x ", cpu.alu.GetPC());
    printw("SP:%2.2x ", cpu.alu.GetSP());
    printw("A:%2.2x ", cpu.alu.GetA());
    printw("DPTR:%4.4x\n", cpu.alu.GetDPTR());
    for (int i = 0; i < 8; i++)
    {
      printw("R%d:%2.2x ", i, cpu.alu.GetReg(i));
    }
    printw("\n");
  }
  else if (!command.compare(stepCmd))
  {
    breakLimit = 0;
    breakCount = 0;
    instructionCount = 0;
    instructionLimit = 1;
    while (instructionCount < instructionLimit)
    {
      cpu.Tick();
    }
  }
  else if (!command.compare(stepInstructionsCmd))
  {
    breakLimit = 0;
    breakCount = 0;
    instructionCount = 0;
    instructionLimit = parameters[0]->number;
    while (instructionCount != instructionLimit)
    {
      cpu.Tick();
    }
  }
  else if (!command.compare(runCmd))
  {
    instructionCount = 0;
    instructionLimit = 0;
    breakCount = 0;
    breakLimit = 1;
    while (breakCount < breakLimit)
    {
      cpu.Tick();
    }
  }
  else if (!command.compare(goCmd))
  {
    instructionCount = 0;
    instructionLimit = 0;
    breakCount = 0;
    breakLimit = parameters[0]->number;
    while (breakCount != breakLimit)
    {
      cpu.Tick();
    }
  }
  else if (!command.compare(loadCmd))
  {
    std::string hex = "hex";
    std::string sym = "rst";
    std::string &fileName = parameters[0]->string;

    if (fileName.rfind(hex) + hex.length() == fileName.length())
    {
      int bytes = cpu.alu.flash.ParseHex(parameters[0]->string);
      printw("Read %d bytes from %s\n", bytes, fileName.c_str());
    }
    else if (fileName.rfind(sym) + sym.length() == fileName.length())
    {
      int symbols = SymbolTable::GetInstance().ParseFile(fileName);
      printw("Found %d symbols in %s\n", symbols, fileName.c_str());
    }
    else
    {
      printw("Unknown file:%s\n", fileName.c_str());
    }
  }
  else if (!command.compare(disassembleCmd))
  {
    std::uint16_t address = parameters[0]->number;
    std::uint16_t length = parameters[1]->number;
    std::uint16_t limit = address + length;
    while (address <= limit)
    {
      printw("%x %s\n", address, cpu.alu.Disassemble(address).c_str());
      address += 1 + cpu.alu.GetOperands(address);
    }
  }
  else if (!command.compare(flashCmd) || !command.compare(iramCmd))
  {
    std::uint16_t address = parameters[0]->number;
    std::uint16_t length = parameters[1]->number;
    bool newline = false;
    Memory *mem;
    if (!command.compare(flashCmd))
    {
      mem = &cpu.alu.flash;
    }
    else
    {
      mem = &cpu.alu.iram;
    }
    for (int i = 0; i < length; i++)
    {
      const int itemsPerLine = 16;
      if (i % itemsPerLine == 0)
      {
        printw("%4.4x ", address + i);
      }
      printw("%2.2x", mem->Read(address + i));
      if (i % itemsPerLine == itemsPerLine - 1)
      {
        printw("\n");
        newline = true;
      }
      else
      {
        printw(" ");
        newline = false;
      }
    }
    if (!newline)
    {
      printw("\n");
    }
  }
  refresh();
}

void Command::OnGPIOWrite(Cpu8051 &handler, std::uint8_t port, std::uint8_t bit, bool value)
{
  printw("Write %d to port %d bit %d\n", value, port, bit);
  refresh();
}

void Command::OnUARTTx(Cpu8051 &handler, char tx)
{
  printw("UART Tx:%c\n", tx);
  refresh();
}

bool Command::OnGPIORead(Cpu8051 &handler, std::uint8_t port, std::uint8_t bit)
{
  printw("Read of GPIO port %d bit %d\n", port, bit);

  int c = getch();

  if (c == '1')
  {
    printw("Logic high\n");
    return true;
  }
  else
  {
    printw("Logic low\n");
    return false;
  }
}

void Command::OnInstructionExecuted(Cpu8051 &cpu)
{
  int pc = cpu.alu.GetPC();

  instructionCount++;
  for (int i = 0; i < NumBreakpoints; i++)
  {
    if (breakpoints[i] == pc)
    {
      breakCount++;
      break;
    }
  }
  if (breakLimit && (breakCount == breakLimit))
  {
    printw("break at %4.4x\n", pc);
    refresh();
  }
  if (trace[cpu.alu.flash.Read(pc)] ||
      breakCount == breakLimit || instructionLimit > 0)
  {
    printw("%d %4.4x %s\n", cpu.GetTicks(), pc, cpu.alu.Disassemble(pc).c_str());
    refresh();
  }
}

void Command::OnReset(Cpu8051 &handler)
{
}
