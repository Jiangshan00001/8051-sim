#ifndef _PORT_HPP
#define _PORT_HPP

#include "alu.hpp"
#include "block.hpp"

class Port: public Block
{
  public:
    Port(std::string name, Alu &a);
};

#endif
