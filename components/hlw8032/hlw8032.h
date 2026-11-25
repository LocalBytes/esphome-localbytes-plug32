#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/uart/uart.h"

namespace esphome::hlw8032 {

class HLW8032Component final : public Component, public uart::UARTDevice {
  SUB_SENSOR(voltage)
  SUB_SENSOR(current)
  SUB_SENSOR(power)
  SUB_SENSOR(apparent_power)
  SUB_SENSOR(power_factor)

 public:
  void loop() override;
  void dump_config() override;

  void set_current_resistor(float current_resistor) { this->current_resistor_ = current_resistor; }
  void set_voltage_divider(float voltage_divider) { this->voltage_divider_ = voltage_divider; }
  void set_power_factor_tolerance(float power_factor_tolerance) {
    this->power_factor_tolerance_ = power_factor_tolerance;
  }
  void set_min_current(float min_current) { this->min_current_ = min_current; }

 protected:
  void parse_data_();
  uint32_t read_uint24_(uint8_t offset);

  float current_resistor_{0.001f};
  float voltage_divider_{1.720f};
  float power_factor_tolerance_{0.05f};
  float min_current_{0.05f};
  uint8_t raw_data_[24]{};
  uint8_t check_{0};
  uint8_t raw_data_index_{0};
  bool header_found_{false};
};

}  // namespace esphome::hlw8032
