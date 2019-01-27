# Watering project actor based on ESP8266

This code is actoring part of watering home pet project using ESP8266 with relay modules, controlled by GPIO where MQTT is used as messaging protocol.

Idea is quite simple and is taken from my knowledge of KNX design principles, where each actor (in this case relay module) uses own "group address" to receive commands (in this case MQTT topics) and send own state status. 

Homeassistant automation will be used to contol and monitor this device.
