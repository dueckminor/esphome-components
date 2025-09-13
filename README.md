# mypi-esphome

This repo contains some ESPHome components for my home automation.

## `sliding_gate` component

This component is used to control a sliding gate with ESPHome.
It uses a relay to control the motor and a 5 hall sensors to detect the gate's
position and direction.

An interactive demo can be found [here](https://dueckminor.github.io/mypi-esphome). You can slide the door and see here how sensors detect the gate's position and direction.

It is able to detect 8 positions. This allows to open the door partially or fully.

It needs a microcontroller with at least 6 GPIO pins available (one output and 5 input pins).
I'm using a Wemos D1 Mini (ESP8266) with the following pin configuration:

### Configuration

```yaml
external_components:
  - source: github://dueckminor/mypi-esp-gate
    components: [sliding_gate]
  
esphome:
  name: ...
  friendly_name: ...

esp8266:
  board: d1_mini

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