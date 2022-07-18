/******************************************************************************
 * Copyright 2019 The Apollo Authors. All Rights Reserved.
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

#include "modules/canbus/vehicle/lavida/protocol/steer_command_112.h"
#include "modules/drivers/canbus/common/byte.h"

namespace apollo {
namespace canbus {
namespace lavida {

using ::apollo::drivers::canbus::Byte;

const int32_t Steercommand064::ID = 0x064 ;

// public
Steercommand064::Steercommand064() { Reset(); }

uint32_t Steercommand064::GetPeriod() const {
  // modify every protocol's period manually
  static const uint32_t PERIOD = 20 * 1000;
  return PERIOD;
}

void Steercommand064::UpdateData(uint8_t* data) {
  set_p_steer_angle_en_ctrl(data, steer_angle_en_ctrl_);
  set_p_steer_angle_cmd(data, steer_angle_cmd_);
}

void Steercommand064::Reset() {
  // you should check this manually
  steer_angle_en_ctrl_ = false;
  steer_angle_cmd_ = 0.0;
}

Steercommand064* Steercommand064::set_steer_angle_en_ctrl(
    bool steer_angle_en_ctrl) {
  steer_angle_en_ctrl_ = steer_angle_en_ctrl;
  return this;
}

// config detail: {'description': 'steering angle enable bit(Command)', 'enum':
// {0: 'STEER_ANGLE_EN_CTRL_DISABLE', 1: 'STEER_ANGLE_EN_CTRL_ENABLE'},
// 'precision': 1.0, 'len': 8, 'name': 'STEER_ANGLE_EN_CTRL', 'is_signed_var':
// False, 'offset': 0.0, 'physical_range': '[0|1]', 'bit': 0, 'type': 'enum',
// 'order': 'intel', 'physical_unit': ''}
void Steercommand064::set_p_steer_angle_en_ctrl(
    uint8_t* data,
    bool steer_angle_en_ctrl) {
  int x = steer_angle_en_ctrl;

  Byte to_set(data + 2);
  to_set.set_value(static_cast<uint8_t>(x), 0, 1);
}

Steercommand064* Steercommand064::set_steer_angle_cmd(double steer_angle_cmd) {
  steer_angle_cmd_ = steer_angle_cmd;
  return this;
}

// config detail: {'description': 'Current steering angle(Command)', 'offset':
// 0.0, 'precision': 0.001, 'len': 16, 'name': 'STEER_ANGLE_CMD',
// 'is_signed_var': True, 'physical_range': '[-0.524|0.524]', 'bit': 8, 'type':
// 'double', 'order': 'intel', 'physical_unit': 'radian'}
void Steercommand064::set_p_steer_angle_cmd(uint8_t* data,
                                            double steer_angle_cmd) {
  steer_angle_cmd = ProtocolData::BoundedValue(-470, 470, steer_angle_cmd);
  int x = static_cast<int>(steer_angle_cmd);
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
