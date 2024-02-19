#include "esphome.h"
#include "esphome/core/log.h"

#include "air_shutter.h"

namespace esphome {
namespace air_shutter {

static const char *const TAG = "air_shutter";


climate::ClimateTraits AirShutter::traits() {
  auto traits = climate::ClimateTraits();
  return traits;
}

void AirShutter::control(const climate::ClimateCall &call) {

}

void AirShutter::set_switch_cool_more(switch_::Switch *obj) {
  this->switch_cool_more = obj;
}

void AirShutter::set_switch_cool_less(switch_::Switch *obj) {
    this->switch_cool_less = obj;
}

void AirShutter::set_sensor_current_temperature(sensor::Sensor *obj) {
  this->sensor_current_temperature = obj;
}

void AirShutter::set_sensor_temperature(sensor::Sensor *obj) {
  this->sensor_temperature = obj;
}

void AirShutter::setup() {
  this->last_check = millis();
  this->turn_off_duration = 0;
}

void AirShutter::loop() {
  unsigned long now = millis();
  if ((this->turn_off_duration > 0) && 
      ((now - this->turned_on_time) > this->turn_off_duration)) {
    switch_cool_more->turn_off();
    switch_cool_less->turn_off();
    this->turn_off_duration = 0;
  }

  if ((now - this->last_check) > 2*60*1000) {
    this->last_check = now;

    float have = this->sensor_current_temperature->state;
    float should = this->sensor_temperature->state;
    float diff = 0.0;
    bool cool_more = false;
    if (have > should) {
      diff = have - should;
      cool_more = true;
    } else {
      diff = should - have;
    }

    if (diff <= 0.2) { 
      return;
    }

    this->turned_on_time=now;
    this->turn_off_duration = 10000.0 * diff;
    if (this->turn_off_duration > 30000) {
      this->turn_off_duration = 30000;
    }

    ESP_LOGD(TAG,"its to %s shutter for %.0f seconds",
      cool_more ? "hot, open" : "cold, closing",
      float(this->turn_off_duration)/1000.0);

    if (cool_more) {
      this->switch_cool_more->turn_on();
    } else {
      this->switch_cool_less->turn_on();
    }
  }


}

}
}