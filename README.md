
# 💧 IoT Water Level Monitoring System

An Arduino-based **Water Level Monitoring System** that measures the water level in a container using an ultrasonic sensor and displays the percentage on an I2C LCD. The system also provides visual alerts using LEDs based on water level thresholds.

This project is ideal for beginners in **IoT and Embedded Systems** and demonstrates sensor integration, signal filtering, and real-time monitoring.

---

## 🚀 Features

* 📏 Ultrasonic-based water level detection
* 📊 Percentage calculation of water level
* 🖥️ 16x2 I2C LCD display output
* 🚨 LED alerts for different water levels
* 📉 Noise reduction using averaged sensor readings
* 🔍 Serial monitor debugging support

---

## 🛠️ Components Used

* Arduino (Uno/Nano recommended)
* Ultrasonic Sensor (HC-SR04)
* 16x2 I2C LCD Display (Address: 0x27)
* Red LED
* Yellow LED
* Resistors
* Jumper Wires
* Water Container

---

## ⚙️ How It Works

1. The ultrasonic sensor sends sound pulses and calculates the distance to the water surface.

2. Multiple readings (10 samples) are averaged to reduce noise and improve stability.

3. Water level is calculated using:

   waterLevel = containerHeight + sensorOffset - distance

4. The water level is converted into percentage.

5. The LCD displays the water level percentage.

6. LEDs indicate status:

   * 🔴 **≥ 90%** → High water level
   * 🟡 **70% – 89%** → Medium level
   * ⚫ **< 70%** → Safe/Low level

---

## 📌 Pin Configuration

| Component         | Arduino Pin |
| ----------------- | ----------- |
| TRIG (Ultrasonic) | 9           |
| ECHO (Ultrasonic) | 10          |
| Red LED           | 11          |
| Yellow LED        | 12          |
| LCD (I2C)         | SDA/SCL     |

---

## 📐 Configuration Parameters

```cpp
const int containerHeight = 13;  // Height of container in cm
const int sensorOffset = 4;      // Distance of sensor from max water level
```

You can modify these values based on your container dimensions.

---

## 🧠 Filtering Technique

The function `getFilteredDistance()` takes 10 ultrasonic readings and calculates the average distance to:

* Reduce random spikes
* Improve accuracy
* Provide stable LCD readings

---

## 📟 Serial Output Example

```
Distance: 6 cm, Water Level: 11 cm, Percentage: 85%
```

Useful for debugging and calibration.

---

## 🔌 Installation & Setup

1. Install Arduino IDE.
2. Install required libraries:

   * `Wire.h`
   * `LiquidCrystal_I2C.h`
3. Connect components as per pin configuration.
4. Upload the code to Arduino.
5. Open Serial Monitor (9600 baud rate).
6. Adjust containerHeight and sensorOffset if needed.

---

## 📸 Project Output

* LCD displays:
  `Water Level: 75%`
* LEDs change based on water level.

---

## 🎯 Applications

* Household water tanks
* Smart irrigation systems
* Industrial liquid monitoring
* IoT-based automation projects
* College mini-projects

---

## 🔮 Future Improvements

* Add buzzer for overflow alert
* Add WiFi module (ESP8266/ESP32) for remote monitoring
* Send data to cloud dashboard
* Mobile app integration
* Add automatic motor control

---

## 📚 Learning Outcomes

* Sensor integration with Arduino
* Signal filtering techniques
* I2C communication
* Real-time embedded system monitoring
* Basic IoT system design

---

## 👨‍💻 Author

**P R Rhishabh**
**Shiva Satvik Reddy**

If you like this project, ⭐ star the repository!

---

If you want, I can also generate:

* A more research-oriented README (since you're into publishing research 👀)
* A resume-friendly project description
* A version formatted specifically for academic submission

Just tell me which one you need 🚀
