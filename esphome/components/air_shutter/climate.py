import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import climate, sensor, switch

from esphome.const import (
    CONF_ID,
)

air_shutter_ns = cg.esphome_ns.namespace("air_shutter")
AirShutter = air_shutter_ns.class_("AirShutter", climate.Climate, cg.Component)

CONFIG_SCHEMA = cv.All(
    climate.CLIMATE_SCHEMA
    .extend(cv.COMPONENT_SCHEMA)
    .extend({
        cv.GenerateID(): cv.declare_id(AirShutter),
        cv.Required("current_temperature"): cv.use_id(sensor.Sensor),
        cv.Required("temperature"): cv.use_id(sensor.Sensor),
        cv.Required("switch_cool_more"): cv.use_id(switch.Switch),
        cv.Required("switch_cool_less"): cv.use_id(switch.Switch)
    })
)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await climate.register_climate(var, config)

    cg.add(var.set_switch_cool_more(await cg.get_variable(config['switch_cool_more'])))
    cg.add(var.set_switch_cool_less(await cg.get_variable(config['switch_cool_less'])))
    cg.add(var.set_sensor_current_temperature(await cg.get_variable(config['current_temperature'])))
    cg.add(var.set_sensor_temperature(await cg.get_variable(config['temperature'])))

