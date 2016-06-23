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

#ifndef _INSTRUCTION_COVERAGE_HPP
#define _INSTRUCTION_COVERAGE_HPP

#include <map>
#include <set>

#include "alu.hpp"

class InstructionCoverage
{
  private:
    std::map<std::uint16_t, int> executionCount;
    std::set<std::uint16_t> reachable;
  public:
    static InstructionCoverage *GetInstance();
    void Initialize(Alu &alu);
    void GetCoverage(int &totalInstructions, int &executedInstructions);
    void InstructionExecuted(std::uint16_t address);
};

#endif