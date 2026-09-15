#pragma once

#include "esphome/core/component.h"
#include "esphome/core/helpers.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/uart/uart.h"

namespace esphome::cse7766 {

static constexpr size_t CSE7766_RAW_DATA_SIZE = 24;
static constexpr uint8_t CSE7766_MAX_INVALID_POWER = 128;

class CSE7766Component final : public Component, public uart::UARTDevice {
 public:
  void set_voltage_sensor(sensor::Sensor *voltage_sensor) { voltage_sensor_ = voltage_sensor; }
  void set_current_sensor(sensor::Sensor *current_sensor) { current_sensor_ = current_sensor; }
  void set_power_sensor(sensor::Sensor *power_sensor) { power_sensor_ = power_sensor; }
  void set_energy_sensor(sensor::Sensor *energy_sensor) { energy_sensor_ = energy_sensor; }
  void set_apparent_power_sensor(sensor::Sensor *apparent_power_sensor) {
    apparent_power_sensor_ = apparent_power_sensor;
  }
  void set_reactive_power_sensor(sensor::Sensor *reactive_power_sensor) {
    reactive_power_sensor_ = reactive_power_sensor;
  }
  void set_power_factor_sensor(sensor::Sensor *power_factor_sensor) { power_factor_sensor_ = power_factor_sensor; }

  void set_voltage_multiplier(float voltage_multiplier) { voltage_multiplier_ = voltage_multiplier; }
  void set_current_multiplier(float current_multiplier) { current_multiplier_ = current_multiplier; }
  void set_power_multiplier(float power_multiplier) { power_multiplier_ = power_multiplier; }

  float get_last_voltage_ratio() const { return last_voltage_ratio_; }
  float get_last_current_ratio() const { return last_current_ratio_; }
  float get_last_power_ratio() const { return last_power_ratio_; }

  void loop() override;
  void dump_config() override;

 protected:
  bool check_byte_();
  void parse_data_();
  uint32_t get_24_bit_uint_(uint8_t start_index) const {
    return encode_uint24(this->raw_data_[start_index], this->raw_data_[start_index + 1],
                         this->raw_data_[start_index + 2]);
  }

  uint8_t raw_data_[CSE7766_RAW_DATA_SIZE];
  uint8_t raw_data_index_{0};
  uint32_t last_transmission_{0};
  sensor::Sensor *voltage_sensor_{nullptr};
  sensor::Sensor *current_sensor_{nullptr};
  sensor::Sensor *power_sensor_{nullptr};
  sensor::Sensor *energy_sensor_{nullptr};
  sensor::Sensor *apparent_power_sensor_{nullptr};
  sensor::Sensor *reactive_power_sensor_{nullptr};
  sensor::Sensor *power_factor_sensor_{nullptr};
  uint32_t cf_pulses_total_{0};
  uint16_t cf_pulses_last_{0};
  uint8_t power_invalid_count_{0};
  float voltage_multiplier_{1.0f};
  float current_multiplier_{1.0f};
  float power_multiplier_{1.0f};
  float last_voltage_ratio_{0.0f};
  float last_current_ratio_{0.0f};
  float last_power_ratio_{0.0f};
};

}  // namespace esphome::cse7766
