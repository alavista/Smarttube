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
"http://192.168.4.1/<API-call>"
  
  * reset: Reset current droplet count
  * inc: Increase count by one
  * count: Returns current droplet count
  * ident: Returns mediaction identification (Dummy)
  * exp: Returns expiration date (Dummy)
