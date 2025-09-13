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

An interactive demo can be found [here](https://dueckminor.github.io/mypi-esphome).
You can slide the gate and see here how sensors detect the gate's position and
direction.

It is able to detect 8 positions. This allows to open the gate partially or
fully.

It needs a microcontroller with at least 6 GPIO pins available (one output
and 5 input pins). I'm using an ESP8266 with the following configuration:

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