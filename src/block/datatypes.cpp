/*
LICENSE: BEGIN
===============================================================================
@author Shan Anand
@email anand.gs@gmail.com
@source https://github.com/shan-anand
@file datatype.cpp
@brief Implementation of block datatypes for serializing/deserializing them.
===============================================================================
MIT License

Copyright (c) 2017 Shanmuga (Anand) Gunasekaran

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
===============================================================================
LICENSE: END
*/

/**
 * @file  datatypes.cpp
 * @brief Implementation of block datatypes
 */

#include <block/datatypes.hpp>
#include <common/convert.hpp>

using namespace sid;
using namespace sid::block;

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
// local namespace
//
namespace local
{
  void validate_block_size(const uint32_t _blockSize);
  bool validate(const uint64_t _value, const uint32_t _blockSize);
  void validate(const byte_region& _byte_region, const uint32_t _blockSize);
  void validate(const io_read& _io_read, const uint32_t _blockSize);
  void validate(const io_write& _io_write, const uint32_t _blockSize);
}

//! Validate the block size
void local::validate_block_size(const uint32_t _blockSize)
{
  if ( _blockSize == 0 )
    throw sid::exception("Block size cannot be zero");
  if ( _blockSize % 2 != 0 )
    throw sid::exception("Block size must be a power of 2");
}

//! Validate the given value against the block size
bool local::validate(const uint64_t _value, const uint32_t _blockSize)
{
  return ( _value % _blockSize == 0 );
}

//! Validate the given byte region
void local::validate(const byte_region& _byte_region, const uint32_t _blockSize)
{
  if ( ! local::validate(_byte_region.offset, _blockSize) )
    throw sid::exception("Offset " + sid::to_str(_byte_region.offset) + " must be a multiple of block size ("
                         + sid::to_str(_blockSize) + ")");
  if ( ! local::validate(_byte_region.length, _blockSize) )
    throw sid::exception("Length " + sid::to_str(_byte_region.length) + "must be a multiple of block size ("
                         + sid::to_str(_blockSize) + ")");
}

//! Validate the given io_read object
void local::validate(const io_read& _io_read, const uint32_t _blockSize)
{
  local::validate(static_cast<byte_region>(_io_read), _blockSize);
  if ( _io_read.buffer == nullptr )
    throw sid::exception("Read buffer cannot be empty");
}

//! Validate the given io_write object
void local::validate(const io_write& _io_write, const uint32_t _blockSize)
{
  local::validate(static_cast<byte_region>(_io_write), _blockSize);
  if ( _io_write.buffer == nullptr )
    throw sid::exception("Write buffer cannot be empty");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
// byte_region
//
void byte_region::validate(const uint32_t _blockSize) const
{
  local::validate_block_size(_blockSize);
  local::validate(*this, _blockSize);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
// io_read
//
void io_read::validate(const uint32_t _blockSize) const
{
  local::validate_block_size(_blockSize);
  local::validate(*this, _blockSize);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
// io_reads
//
void io_reads::validate(const uint32_t _blockSize) const
{
  local::validate_block_size(_blockSize);
  for ( const auto& io : *this )
    local::validate(io, _blockSize);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
// io_write
//
void io_write::validate(const uint32_t _blockSize) const
{
  local::validate_block_size(_blockSize);
  local::validate(*this, _blockSize);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
// io_writes
//
void io_writes::validate(const uint32_t _blockSize) const
{
  local::validate_block_size(_blockSize);
  for ( const auto& io : *this )
    local::validate(io, _blockSize);
}
