This project utilizes the ESP32 as an Access Point to host a web dashboard that displays real-time temperature and humidity readings from a DHT22 sensor. If humidity goes below 30% or above 70%, the ESP32 turns on a red LED and shows a corresponding alert on the dashboard. The data updates every 2 seconds without page refresh

<h1>💡 Wiring Schematic:</h1>
<b>ESP32 to DHT22:</b><br>
3.3V to VCC<br>
GND to GND<br>
GPIO4 to DATA (with a 10k pull-up resistor)<br><br>
<b>ESP32 to LED:</b><br>
GPIO2 to LED Anode (through a 220 ohm resistor)<br>
GND to LED Cathode<br>
