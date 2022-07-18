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

#include "modules/canbus/vehicle/lavida/protocol/shift_cmd_066.h"

#include "modules/drivers/canbus/common/byte.h"

namespace apollo {
namespace canbus {
namespace lavida {

using ::apollo::drivers::canbus::Byte;

const int32_t Shiftcmd066::ID = 0x066;

// public
Shiftcmd066::Shiftcmd066() { Reset(); }

uint32_t Shiftcmd066::GetPeriod() const {
  // TODO(QiL) modify every protocol's period manually
  static const uint32_t PERIOD = 20 * 1000;
  return PERIOD;
}

void Shiftcmd066::UpdateData(uint8_t* data) {
  set_p_enable(data, enable_);
  set_p_clear_override(data, clear_override_);
  set_p_shift_cmd(data, shift_cmd_);
}

void Shiftcmd066::Reset() {
  // TODO(QiL) you should check this manually
  enable_ = false;
  clear_override_ = false;
  shift_cmd_ = 
}

Shiftcmd066* Shiftcmd066::set_clear_override(bool clear_override) {
  clear_override_ = clear_override;
  return this;
}



Shiftcmd066* Shiftcmd066::set_enable(bool enable) {
  enable_ = enable;
  return this;
}

// config detail: {'name': 'ENABLE', 'offset': 0.0, 'precision': 1.0, 'len': 1,
// 'is_signed_var': False, 'physical_range': '[0|1]', 'bit': 0, 'type': 'bool',
// 'order': 'motorola', 'physical_unit': ''}
void Shiftcmd066::set_p_enable(uint8_t* data, bool enable) {
  uint8_t x = enable;

  Byte to_set(data + 1);
  to_set.set_value(static_cast<uint8_t>(x), 0, 3);
}

Shiftcmd066* Shiftcmd066::set_clear_override(bool clear_override) {
  clear_override_ = clear_override;
  return this;
}

// config detail: {'name': 'CLEAR_OVERRIDE', 'offset': 0.0, 'precision': 1.0,
// 'len': 1, 'is_signed_var': False, 'physical_range': '[0|1]', 'bit': 2,
// 'type': 'bool', 'order': 'motorola', 'physical_unit': ''}
void Shiftcmd066::set_p_clear_override(uint8_t* data, bool clear_override) {
  uint8_t x = clear_override;

  Byte to_set(data + 0);
  to_set.set_value(static_cast<uint8_t>(x), 7, 1);
}




Shiftcmd066* Shiftcmd066::set_shift_cmd(
    Shift_cmd_066::Shift_cmdType shift_cmd) {
  shift_cmd_ = shift_cmd;
  return this;
}

// config detail: {'description': 'FORWARD is also HIGH on vehicles with
// LOW/HIGH, PARK and LOW only available on certain Vehicles.', 'enum': {0:
// 'SHIFT_CMD_PARK', 1: 'SHIFT_CMD_REVERSE', 2: 'SHIFT_CMD_NEUTRAL', 3:
// 'SHIFT_CMD_FORWARD_HIGH', 4: 'SHIFT_CMD_LOW', 7: 'SHIFT_CMD_NONE'},
// 'precision': 1.0, 'len': 8, 'name': 'SHIFT_CMD', 'is_signed_var': False,
// 'offset': 0.0, 'physical_range': '[0|4]', 'bit': 15, 'type': 'enum', 'order':
// 'motorola', 'physical_unit': ''}
void Shiftcmd066::set_p_shift_cmd(uint8_t* data,
                                  Shift_cmd_066::Shift_cmdType shift_cmd) {
  uint8_t x = shift_cmd;

  Byte to_set(data + 0);
  to_set.set_value(static_cast<uint8_t>(x), 0, 3);
}

}  // namespace lavida
}  // namespace canbus
}  // namespace apollo
