/******************************************************************************
* Copyright 2022 Hyunwook Choi
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
******************************************************************************/

#ifndef ACTUATOR_HPP
#define ACTUATOR_HPP

#include <cmath>
#include <iostream>
#include <map>
#include <dynamixel_sdk/dynamixel_sdk.h>

#include "essential.hpp"


enum DataType
{
  BYTE = 1,
  WORD = 2,
  DWORD = 4
};

enum DataAddress
{
  RETURN_DELAY_TIME,
  TORQUE_ENABLE,
  PRESENT_ANGLE,
  PRESENT_VELOCITY,
  TARGET_VELOCITY
};

enum DataPreset
{
  TORQUE_OFF = 0,
  TORQUE_ON = 1
};

class DynamixelAX
{
public:
  enum Address
  {
    AX_12A = 12,
    RETURN_DELAY_TIME = 5,
    TORQUE_ENABLE = 24,
    MOVING_SPEED = 32,
    PRESENT_POSITION = 36,
    PRESENT_SPEED = 38
  };
  std::map<uint8_t, uint8_t> address_map_;
  uint8_t error_;

  // Angle
  static constexpr float kDegreeToRadian = M_PI / 180.0F;
  static constexpr float kLimitAngleRadian = 300.0F * kDegreeToRadian;
  static constexpr float kLimitAngleValue = 1023.0F;
  static constexpr float kHomeAngleRadian = kLimitAngleRadian / 2;
  static constexpr float kHomeAngleValue = kLimitAngleValue / 2;
  static constexpr float kRadianPerValue = kLimitAngleRadian / kLimitAngleValue;
  static constexpr float kValuePerRadian = kLimitAngleValue / kLimitAngleRadian;

  // Data buffer
  uint8_t buffer_uint8_;
  uint16_t buffer_uint16_;
};

class DynamixelXL
{
public:
  enum Address
  {
    XL430_W250 = 1060,
    RETURN_DELAY_TIME = 9,
    TORQUE_ENABLE = 64,
    GOAL_VELOCITY = 104,
    PRESENT_VELOCITY = 128,
    PRESENT_POSITION = 132
  };
  std::map<uint8_t, uint8_t> address_map_;
  uint8_t error_;

  // Angle
  static constexpr float kLimitAngleRadian = 2 * M_PI;
  static constexpr float kLimitAngleValue = 4095.0F;
  static constexpr float kHomeAngleRadian = kLimitAngleRadian / 2;
  static constexpr float kHomeAngleValue = kLimitAngleValue / 2;
  static constexpr float kRadianPerValue = kLimitAngleRadian / kLimitAngleValue;
  static constexpr float kValuePerRadian = kLimitAngleValue / kLimitAngleRadian;

  // Data buffer
  uint8_t buffer_uint8_;
  uint16_t buffer_uint16_;
  uint32_t buffer_uint32_;
};

class Actuator
{
private:
  // Dynamixel
  const char *kPortName = "/dev/U2D2";
  const float kProtocolVer = 1.0F;
  const uint32_t kBaudrate = 1000000;
  dynamixel::PortHandler *port_handler_;
  dynamixel::PacketHandler *packet_handler_;

  // Joint
  std::map<uint8_t, uint16_t> joints_;

public:
  // Dynamixel
  DynamixelAX dxl_ax_;
  DynamixelXL dxl_xl_;

  Actuator();
  ~Actuator();

  void initActuator();
  void enableActuator(uint8_t id);
  void disableActuator(uint8_t id);

  void setDataMap();
  void setReturnDelayTime(uint8_t delay);

  uint16_t getDataAddressAX(uint16_t address);
  uint16_t getDataAddressXL(uint16_t address);

  void readDataAX(uint8_t id, uint16_t address, uint32_t *data);
  void readDataXL(uint8_t id, uint16_t address, uint32_t *data);
  void readPresentAngle();
  void readPresentVelocity();

  void writeData(uint8_t id, uint16_t address, uint32_t data);
  void writeDataALL(uint16_t address, uint32_t data);
  void writeDataAX(uint8_t id, uint16_t address, uint32_t data);
  void writeDataXL(uint8_t id, uint16_t address, uint32_t data);
  void writeTargetVelocity();
  void writeTargetVelocityZero();

  void convertRadianToValue(float (&radian)[Joint::JOINT_ALL], uint32_t (&value)[Joint::JOINT_ALL]);
  void convertValueToRadian(uint32_t (&value)[Joint::JOINT_ALL], float (&radian)[Joint::JOINT_ALL]);
};

# endif  // ACTUATOR_HPP
