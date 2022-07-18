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

#include "modules/canbus/vehicle/lavida/protocol/accel_cmd_062.h"

#include <algorithm>

#include "modules/drivers/canbus/common/byte.h"

namespace apollo {
namespace canbus {
namespace lavida {

using ::apollo::drivers::canbus::Byte;

const int32_t Accelcmd062::ID = 0x062;

// public
Accelcmd062::Accelcmd062() { Reset(); }

uint32_t Accelcmd062::GetPeriod() const {
  // TODO(QiL) modify every protocol's period manually
  static const uint32_t PERIOD = 20 * 1000;
  return PERIOD;
}

void Accelcmd062::UpdateData(uint8_t* data) {
  set_p_ignore_overrides(data, ignore_overrides_);
  set_p_enable(data, enable_);
  set_p_clear_override(data, clear_override_);
  set_p_accel_cmd(data, accel_cmd_);
}

void Accelcmd062::Reset() {
  // TODO(QiL) you should check this manually
  ignore_overrides_ = false;
  enable_ = false;
  clear_override_ = false;
  accel_cmd_ = 0.0;
}

Accelcmd062* Accelcmd062::set_ignore_overrides(bool ignore_overrides) {
  ignore_overrides_ = ignore_overrides;
  return this;
}

// config detail: {'name': 'IGNORE_OVERRIDES', 'offset': 0.0, 'precision': 1.0,
// 'len': 1, 'is_signed_var': False, 'physical_range': '[0|1]', 'bit': 1,
// 'type': 'bool', 'order': 'motorola', 'physical_unit': ''}
void Accelcmd062::set_p_ignore_overrides(uint8_t* data, bool ignore_overrides) {
  uint8_t x = ignore_overrides;

  Byte to_set(data + 3);
  to_set.set_value(static_cast<uint8_t>(x), 2, 1);
}

Accelcmd062* Accelcmd062::set_enable(bool enable) {
  enable_ = enable;
  return this;
}

// config detail: {'name': 'ENABLE', 'offset': 0.0, 'precision': 1.0, 'len': 1,
// 'is_signed_var': False, 'physical_range': '[0|1]', 'bit': 0, 'type': 'bool',
// 'order': 'motorola', 'physical_unit': ''}
void Accelcmd062::set_p_enable(uint8_t* data, bool enable) {
  uint8_t x = enable;

  Byte to_set(data + 3);
  to_set.set_value(static_cast<uint8_t>(x), 0, 1);
}

Accelcmd062* Accelcmd062::set_clear_override(bool clear_override) {
  clear_override_ = clear_override;
  return this;
}

// config detail: {'name': 'CLEAR_OVERRIDE', 'offset': 0.0, 'precision': 1.0,
// 'len': 1, 'is_signed_var': False, 'physical_range': '[0|1]', 'bit': 2,
// 'type': 'bool', 'order': 'motorola', 'physical_unit': ''}
void Accelcmd062::set_p_clear_override(uint8_t* data, bool clear_override) {
  uint8_t x = clear_override;

  Byte to_set(data + 3);
  to_set.set_value(static_cast<uint8_t>(x), 1, 1);
}

Accelcmd062* Accelcmd062::set_accel_cmd(double accel_cmd) {
  accel_cmd_ = accel_cmd;
  return this;
}

// config detail: {'name': 'ACCEL_CMD', 'offset': 0.0, 'precision': 0.001,
// 'len': 16, 'is_signed_var': False, 'physical_range': '[0|1]', 'bit': 15,
// 'type': 'double', 'order': 'motorola', 'physical_unit': ''}
void Accelcmd062::set_p_accel_cmd(uint8_t* data, double accel_cmd) {
//   const double scaling_bias = 0.0;   // estimated from the garage test data
//   const double scaling_gain = 1.20;  // estimated from the garage test data
  int x = static_cast<int>(accel_cmd);
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
