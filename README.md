# Smarttube
Project for the "Tube challenge" submitted for the ITQ Smart Green Island Makeathon 2019 (Las Palmas, Gran Canaria)
# Prerequisites
* Install ESP32 support for Arduino IDE: https://randomnerdtutorials.com/installing-the-esp32-board-in-arduino-ide-windows-instructions/
* Install AsyncTCP library: https://github.com/me-no-dev/AsyncTCP

# To Do
* Add Sensors
* Add dummy for expiration date und identification

# Maybes
* Implement BLE support
* Implement sleep button

# API
* http://192.168.4.1/reset: Reset current droplet count, returns success
* http://192.168.4.1/inc: Increase count by one, returns increased
* http://192.168.4.1/count: Returns current droplet count
* http://192.168.4.1/ident: Returns mediaction identification (Dummy)
* http://192.168.4.1/exp: Returns expiration date (Dummy)
* http://192.168.4.1/set/value: Sets count to "value" (Integer), returns success or failure


# EEPROM structure
* 16 byte Blocksize
Starting adress is (Device ID*16)
| Byte | Content |
| --- | --- |
| 0 | DeviceID |
| 1 | Expiration Year |
| 2 | Expiration Month |
| 3 | tmpDropcount |
| 4,5 | glocalDropcount |
| 6 | UserID |
| 7-15 | Free |
