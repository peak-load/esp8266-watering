# Watering project actor based on ESP8266

This code is actoring part of watering home pet project using ESP8266 with relay modules, controlled by GPIO where MQTT is used as messaging protocol.

Idea is quite simple and is taken from my knowledge of KNX design principles, where each actor (in this case relay module) uses own "group address" to receive commands (in this case MQTT topics) and send own state status. 

Homeassistant automation will be used to contol and monitor this device.

# Minimal testing of fuctionality (tested on Debian and Ubuntu) :smile:

- [x] Install and configure mosquitto 
`apt install -y mosquitto`

- [x] Create config for Mosquitto to disable anon access and add path to password file
```
# cat /etc/mosquitto/conf.d/auth.conf 
allow_anonymous false
password_file /etc/mosquitto/passwd
```

- [x] Create password file and set password for user peak-load
`mosquitto_passwd /etc/mosquitto/passwd peak-load`

- [x] Restart mosquito server 
`/etc/init.d/mosquitto restart`

- [x] Subscribe to see mosquitto topic changes
`mosquitto_sub -h 192.168.2.134 -v -t 'switch/pump' -u peak-load -P password`

- [x] Publish values to mosquitto topics 
```
mosquitto_pub -h 192.168.2.134 -t 'switch/pump'   -u peak-load -P password -m 0
mosquitto_pub -h 192.168.2.134 -t 'switch/valve1' -u peak-load -P password -m 0
mosquitto_pub -h 192.168.2.134 -t 'switch/valve2' -u peak-load -P password -m 0
mosquitto_pub -h 192.168.2.134 -t 'switch/valve3' -u peak-load -P password -m 0

mosquitto_pub -h 192.168.2.134 -t 'switch/pump'   -u peak-load -P password -m 1
mosquitto_pub -h 192.168.2.134 -t 'switch/valve1' -u peak-load -P password -m 1
mosquitto_pub -h 192.168.2.134 -t 'switch/valve2' -u peak-load -P password -m 1
mosquitto_pub -h 192.168.2.134 -t 'switch/valve3' -u peak-load -P password -m 1
```
