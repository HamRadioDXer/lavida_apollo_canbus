/******************************************************************************
 * Copyright 2018 The Apollo Authors. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/

#include "modules/canbus/vehicle/lavida/protocol/brake_cmd_060.h"

#include <algorithm>

#include "modules/drivers/canbus/common/byte.h"

namespace apollo {
namespace canbus {
namespace lavida {

using ::apollo::drivers::canbus::Byte;

const int32_t Brakecmd060::ID = 0x060;

// public
Brakecmd060::Brakecmd060() { Reset(); }

uint32_t Brakecmd060::GetPeriod() const {
  // TODO(QiL) modify every protocol's period manually
  static const uint32_t PERIOD = 20 * 1000;
  return PERIOD;
}

void Brakecmd060::UpdateData(uint8_t* data) {
  set_p_enable(data, enable_);
  set_p_clear_override(data, clear_override_);
  set_p_brake_cmd(data, brake_cmd_);
}

void Brakecmd060::Reset() {
  // TODO(QiL) you should check this manually
  enable_ = false;
  clear_override_ = false;
  brake_cmd_ = 0.0;
}





Brakecmd060* Brakecmd060::set_enable(bool enable) {
  enable_ = enable;
  return this;
}

// config detail: {'name': 'ENABLE', 'offset': 0.0, 'precision': 1.0, 'len': 1,
// 'is_signed_var': False, 'physical_range': '[0|1]', 'bit': 0, 'type': 'bool',
// 'order': 'motorola', 'physical_unit': ''}
void Brakecmd060::set_p_enable(uint8_t* data, bool enable) {
  uint8_t x = enable;

  Byte to_set(data + 3);
  to_set.set_value(static_cast<uint8_t>(x), 0, 1);
}

Brakecmd060* Brakecmd060::set_clear_override(bool clear_override) {
  clear_override_ = clear_override;
  return this;
}

// config detail: {'name': 'CLEAR_OVERRIDE', 'offset': 0.0, 'precision': 1.0,
// 'len': 1, 'is_signed_var': False, 'physical_range': '[0|1]', 'bit': 2,
// 'type': 'bool', 'order': 'motorola', 'physical_unit': ''}
void Brakecmd060::set_p_clear_override(uint8_t* data, bool clear_override) {
  uint8_t x = clear_override;

  Byte to_set(data + 3);
  to_set.set_value(static_cast<uint8_t>(x), 1, 1);
}



Brakecmd060* Brakecmd060::set_brake_cmd(double brake_cmd) {
  brake_cmd_ = brake_cmd;
  return this;
}

// config detail: {'name': 'BRAKE_CMD', 'offset': 0.0, 'precision': 0.001,
// 'len': 16, 'is_signed_var': False, 'physical_range': '[0|1]', 'bit': 15,
// 'type': 'double', 'order': 'motorola', 'physical_unit': ''}
void Brakecmd060::set_p_brake_cmd(uint8_t* data, double brake_cmd) {
//   const double scaling_bias = 0.0;   // estimated from the garage test data
//   const double scaling_gain = 0.80;  // estimated from the garage test data
//   brake_cmd = std::max(0.0, (brake_cmd - scaling_bias) / (scaling_gain * 100));
  brake_cmd = ProtocolData::BoundedValue(0.0, 65535, brake_cmd);
  // TODO(AS): fix this scaling.
  int x = static_cast<int>(brake_cmd);
  uint8_t t = 0;

  t = static_cast<uint8_t>(x & 0xFF);
  Byte to_set0(data + 0);
  to_set0.set_value(t, 0, 8);
  x >>= 8;

  t = static_cast<uint8_t>(x & 0xFF);
  Byte to_set1(data + 1);
  to_set1.set_value(t, 0, 8);
}

}  // namespace lavida
}  // namespace canbus
}  // namespace apollo
