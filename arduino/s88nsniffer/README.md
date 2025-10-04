
# 🏴‍☠️ S88 Sniffer – Arduino “Bus Hack”

With this Arduino sketch, you can **listen in on the S88 bus** and read the **occupancy detectors** of your model railway in real time.  
A bit of *piracy* — but the legal kind, with solder instead of swords. 😉

---

## 💡 What it does
The S88 sniffer taps into the **S88 bus** between your command station and the first S88 module.  
It shows the live state of all occupancy sensors and can **control relays or LEDS or whatever you want ** based on those signals — for example, to manage a **reverse loop**.

**First application:**  
Automatically switching a relay for a reverse loop, using two occupancy detectors (set/reset).

---

## ⚙️ Hardware
- Arduino Nano (or compatible microcontroller)  
- ULN2803 or transistor stage for driving relays or LEDs  
- S88 bus connection:
  - **CLOCK** → D2  
  - **LOAD**  → D3  
  - **DATA**  → D4  
  - **GND / +5V** as on standard S88  
- Optional relay or LED outputs

---

## 🧠 How it works
The S88 bus is basically one long **shift register**.  
On every **CLOCK** pulse, the next detector state appears on the **DATA** line.  
The **LOAD** line marks the start of a new scan.

The Arduino:
1. Listens to the `LOAD` and `CLOCK` signals  
2. Reads bits from `DATA`  
3. Builds a *frame* containing all detector states  
4. Applies **debounce filtering** to avoid noise  
5. Controls **relays** based on configurable logic (e.g., reverse loop control)

---

## 🧩 Code structure
The project is split into clean modules:

| File | Purpose |
|------|----------|
| **Config.h** | Pin definitions and constants |
| **S88Bus.cpp/h** | Interrupt-based S88 frame reader |
| **MelderManager.cpp/h** | Debounce logic for occupancy sensors |
| **Relay.cpp/h** | Set/reset relay logic with debug output |
| **main.ino** | Main loop connecting everything together |

---

## ⚡ Example – relay rules
```cpp
Relay relay1("relay1", A0, 11, 13); // set = detector 11, reset = detector 13
Relay relay2("relay2", A1, 25, 34); // set = detector 25, reset = detector 34
```

When detector 11 is active → relay1 ON  
When detector 13 is active → relay1 OFF

---

## 📺 Debug output
On the serial monitor (115200 baud) you’ll see something like:

```
[1234 ms] detector 11 -> X
[1234 ms] relay1 -> ON (SET 11)
[1300 ms] detector 13 -> X
[1300 ms] relay1 -> OFF (RESET 13)
```

---

## 🧰 Software
- Arduino IDE or PlatformIO  
- Serial monitor at **115200 baud**

---

## 🤓 Credits
Project and code by Rian De Rous  
Inspired by the idea that *“sniffing the bus”* can be a perfectly respectable hobby. 😄  

#ModelRailway #S88 #Arduino #DIY #ReverseLoop #HackTheBus
