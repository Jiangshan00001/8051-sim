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

#include <string>
#include <iostream>
#include "port0.hpp"
#include "sfr.hpp"
#include "port.hpp"
#include "command.hpp"

P0::P0(std::string name, Block &block, std::uint8_t address, std::uint8_t resetValue, std::set<std::uint8_t> pages):
  SfrBitAddressable(name, block, address, resetValue, pages)
{
}

bool P0::ReadBit(std::uint8_t bit)
{
  return block.alu.GetCallback()->OnGPIORead(*block.alu.GetCallbackCpu(), 0, bit);
}

Port0::Port0(std::string name, Alu &a) :
  Port(name, a),
  p0mdin("P0MDIN", *this, 0xf1, 0xff, {0x0}),
  p0mdout("P0MDOUT", *this, 0xa4, 0x00, {0x0}),
  p0("P0", *this, 0x80, 0xff, {0x0, 0xf}),
  p0skip("P0SKIP", *this, 0xd4, 0x00, {0x0}),
  xbr0("XBR0", *this, 0xe1, 0x00, {0x0})
{
}
