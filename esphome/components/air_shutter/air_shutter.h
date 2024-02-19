#pragma once

#include "esphome/core/component.h"
#include "esphome/core/hal.h"
#include "esphome/core/automation.h"
#include "esphome/core/controller.h"
#include "esphome/components/climate/climate.h"
#include "esphome/components/switch/switch.h"
#include "esphome/components/sensor/sensor.h"

namespace esphome {
namespace air_shutter {

class AirShutter : public climate::Climate, public Component {
public:
    virtual climate::ClimateTraits traits() override;
    virtual void control(const climate::ClimateCall &call) override;
    virtual void set_switch_cool_more(switch_::Switch *obj);
    virtual void set_switch_cool_less(switch_::Switch *obj);
    virtual void set_sensor_current_temperature(sensor::Sensor *obj);
    virtual void set_sensor_temperature(sensor::Sensor *obj);

    void setup() override;
    void loop() override;

protected:
    unsigned long last_check;
    unsigned long turned_on_time;
    unsigned long turn_off_duration;

    sensor::Sensor * sensor_temperature;
    sensor::Sensor * sensor_current_temperature;
    switch_::Switch * switch_cool_more;
    switch_::Switch * switch_cool_less;
};

}
}