/*
LICENSE: BEGIN
===============================================================================
@author Shan Anand
@email anand.gs@gmail.com
@source https://github.com/shan-anand
@file device.hpp
@brief NVME device definition
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
 * @file  device.hpp
 * @brief Device definition for NVME
 */

#ifndef _SID_NVME_DEVICE_H_
#define _SID_NVME_DEVICE_H_

#include <string>
#include <common/smart_ptr.hpp>
#include "datatypes.hpp"
#include "../device.hpp"

namespace sid {
namespace block {
namespace nvme {

class device;
using device_ptr = smart_ptr<device>;

/**
 * @struct device_info
 * @brief Connection interface for NVME device
 */
struct device_info
{
  block::device_type type() const override { return block::device_type::nvme; }
  std::string id() const override;

  std::string portal; //! NVME device portal
  // chap and mchap
  int lun; //! Current lun id used
};
  
/**
 * @struct device
 * @brief NVMe device interface definition
 */
class device : public block::device
{
public:
  using super = block::device;
  device();
  static device_ptr create(const device_info& _deviceInfo);

private:
  device_info m_info;
};

} // namespace nvme
} // namespace block
} // namespace sid

#endif // _SID_NVME_DEVICE_H_
