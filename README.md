# mypi-esphome

This repo contains some ESPHome components for my home automation.

## `sliding_gate` component

This component is used to control a sliding gate with ESPHome.

In my case, the gate is driven by a motor which is not compatible with
Home Assistant (or I don't know how to do it). My motor doesn't report the
position and to control it, it has just a simple button. If you press the button,
the gate will

- stop (if it is moving)
- open (if it is not moving and the last direction was closing)
- close (if it is not moving and the last direction was opening)

This is OK, if you press the button manually, as you have a visual feedback of
the gate's position. But if you want to control it via Home Assistant, you need
to know the position (and the last direction) of the gate.

To get this information, I mounted a lot of magnets on the gate and 5 hall
sensors will detect the magnets. The magnets are mounted in a way,
that each position of the gate has a unique bit pattern. And they are mounted
in a way that it is possible to detect the direction of movement.

To "press" the button of the motor, I use a relay.

An interactive demo can be found [here](https://dueckminor.github.io/esphome-components/).
You can slide the gate and see here how sensors detect the gate's position and
direction.

It is able to detect 8 positions. This allows to open the gate partially or
fully.

It needs a microcontroller with at least 6 GPIO pins available (one output
and 5 input pins). I'm using an ESP8266 with the following configuration:

### Configuration `sliding_gate`

```yaml
external_components:
  - source: github://dueckminor/mypi-esp-gate
    components: [sliding_gate]
  
esphome:
  name: ...
  friendly_name: ...

cover:
  - platform: sliding_gate
    device_class: gate
    id: ...
    name: ...
    pin_dir_0: D2
    pin_pos_0: D0
    pin_pos_1: D5
    pin_pos_2: D6
    pin_dir_1: D7
    pin_relay: D1
```

## `air_shutter` component

This component is used to control an air shutter with ESPHome. Compared with
normal thermostats, air shutters are not able to heat or cool a room. They can
just increase or decrease the airflow. So, to control the temperature of a room,
you need two switches: one to increase the airflow (cool more) and one to decrease
the airflow (cool less).

In my case, I've connect 4 air shutters to one ESP8266 and needed therefor 8
relays and used a PCF8574 I/O expander to control them.

The relays are wired in a way, that only one output can be active at a time.
If both outputs are active, the air shutter will not move. This is done to avoid
damage to the air shutter.

![Air Shutter Relay Wiring Diagram](docs/air_shutter/relays.svg)

To control the air shutter, you need to know the current temperature of the room
and the target temperature. This component uses two `sensor` components to get
this information. Any Home Assistant thermostat compatible device can be used as
user interface. I'm using Homematics `HMIP-WTH-2`, but any other device which
reports the current and target temperature should work.

The `air_shutter` component compares the current and target temperatures
and activates the appropriate switch to increase or decrease the airflow.

It does this every two minutes. The higher the difference between current and
target temperature, the longer the switch will be active.

- diff < 0.2 °C: do nothing
- diff < 3.0 °C: activate the appropriate switch for diff * 10 seconds/°C
- diff >= 3.0 °C: activate the appropriate switch for 30 seconds

At the end this should lead to a comfortable temperature in the room with a
difference of less than 0.5 °C between current and target temperature.

### Configuration `air_shutter`

```yaml
external_components:
  - source:
      type: git
      url: https://github.com/dueckminor/mypi-esphome
    components: [air_shutter]

esphome:
  name: ...
  friendly_name: ...

sensor:
  - platform: homeassistant
    id: current_temperature_room_xyz
    entity_id: climate.temp_xyz
    attribute: current_temperature
  - platform: homeassistant
    id: temperature_room_xyz
    entity_id: climate.temp_xyz
    attribute: temperature

climate:
  - platform: air_shutter
    id: air_shutter_room_xyz
    switch_cool_less: out0
    switch_cool_more: out1
    current_temperature: current_temperature_room_xyz
    temperature: temperature_room_xyz
  
# Enable I2C
i2c:

# Enable PCF8574
pcf8574:
  - id: 'pcf8574_hub'
    address: 0x20

switch:
  - platform: gpio
    name: "out0"
    id: out0
    pin:
      pcf8574: pcf8574_hub
      number: 0
      mode:
        output: true
      inverted: true
  - platform: gpio
    name: "out1"
    id: out1
    pin:
      pcf8574: pcf8574_hub
      number: 1
      mode:
        output: true
      inverted: true
```
