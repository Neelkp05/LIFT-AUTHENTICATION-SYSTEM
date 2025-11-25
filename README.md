![Banner Image](https://images.unsplash.com/photo-1556740758-90de374c12ad?ixlib=rb-4.0.3&auto=format&fit=crop&w=1000&h=300&q=80)

<h1 align="center">🛗 Lift Authentication System</h1>
<h3 align="center">Secure Access Control using ESP32 & FreeRTOS</h3>

<p align="center">
  A real-time, multi-tasking security system designed to restrict elevator access to authorized personnel only.
</p>

<p align="center">
  <a href="#about-the-project">About</a> •
  <a href="#key-features">Key Features</a> •
  <a href="#tech-stack">Tech Stack</a> •
  <a href="#hardware-requirements">Hardware</a> •
  <a href="#installation">Setup</a>
</p>

---

## 🔭 About The Project
[cite_start]This project presents a **Lift Authentication System** designed to enhance security and access control in residential and commercial buildings[cite: 6]. [cite_start]Unlike traditional systems, this solution leverages a **Real-Time Operating System (FreeRTOS)** to manage time-critical tasks with precision[cite: 7].

[cite_start]The system integrates an **RFID reader** for user verification and a **Keypad** for floor selection, all processed by an **ESP32 microcontroller**[cite: 14, 15]. [cite_start]It ensures that high-priority tasks (like scanning a card) are executed immediately without lagging the display or logic[cite: 108].

- [cite_start]⚡ **Performance:** Low latency response using interrupt-driven execution[cite: 98].
- [cite_start]🛡️ **Security:** Prevents unauthorized access and cloning attacks[cite: 33].
- [cite_start]🔄 **Multitasking:** Handles RFID scanning, LCD updating, and data logging simultaneously[cite: 118].

## ⚙️ Key Features
* [cite_start]**RFID Authentication:** Uses MFRC522 to scan and verify unique user IDs[cite: 77].
* [cite_start]**RTOS Implementation:** Utilizes FreeRTOS for priority-based task scheduling[cite: 135].
* [cite_start]**Interactive Interface:** 16x2 I2C LCD for real-time status and 4x4 Keypad for floor input[cite: 92, 206].
* [cite_start]**Access Control Logic:** logic to validate authorized floors and deny invalid entries[cite: 78].
* [cite_start]**Security Alerts:** Buzzer integration for unauthorized access attempts[cite: 91].

## 🛠 Tech Stack & Tools
<p align="left">
  <a href="https://www.arduino.cc/" target="_blank" rel="noreferrer">
    <img src="https://raw.githubusercontent.com/devicons/devicon/master/icons/cplusplus/cplusplus-original.svg" alt="c++" width="50" height="50"/>
  </a>
  <a href="https://www.arduino.cc/" target="_blank" rel="noreferrer">
    <img src="https://raw.githubusercontent.com/devicons/devicon/master/icons/arduino/arduino-original.svg" alt="arduino" width="50" height="50"/>
  </a>
  <a href="https://www.espressif.com/" target="_blank" rel="noreferrer">
    <img src="https://raw.githubusercontent.com/devicons/devicon/master/icons/embeddedc/embeddedc-original.svg" alt="embedded" width="50" height="50"/>
  </a>
  <a href="https://code.visualstudio.com/" target="_blank" rel="noreferrer">
    <img src="https://raw.githubusercontent.com/devicons/devicon/master/icons/vscode/vscode-original.svg" alt="vscode" width="50" height="50"/>
  </a>
</p>

## 🧩 Hardware Requirements
[cite_start]The system is built using the following components[cite: 37, 38]:

| Component | Specification | Function |
| :--- | :--- | :--- |
| **Microcontroller** | ESP32 Dev Module | [cite_start]Central processing & WiFi capabilities[cite: 42]. |
| **RFID Module** | RC522 (13.56MHz) | [cite_start]Reads user tags/cards[cite: 81]. |
| **Display** | 16x2 LCD (I2C) | [cite_start]Shows prompts, floor status, and errors[cite: 92]. |
| **Input** | 4x4 Matrix Keypad | [cite_start]Allows users to select floors[cite: 206]. |
| **Output** | Buzzer & Relay | [cite_start]Alerts and door lock mechanism[cite: 90]. |
| **Power** | 9V Battery / 5V Reg. | [cite_start]System power supply[cite: 93]. |

## 🚀 Getting Started

1.  **Clone the Repo:**
    ```sh
    git clone [https://github.com/yourusername/lift-authentication-system.git](https://github.com/yourusername/lift-authentication-system.git)
    ```
2.  **Hardware Setup:** Connect the MFRC522 to the ESP32 SPI pins (SS=21, RST=5) and the LCD to I2C pins[cite: 191, 230].
3.  **Software:** Open `lift_auth.ino` in Arduino IDE.
4.  **Library Installation:** Install `MFRC522`, `Keypad`, `LiquidCrystal_I2C`, and `FreeRTOS`.
5.  **Upload:** Connect ESP32 and upload the code.

## 📸 System Output
<p align="left">
  <img src="https://via.placeholder.com/300x150?text=LCD+Status" alt="LCD Output" width="45%" />
  <img src="https://via.placeholder.com/300x150?text=Serial+Log" alt="Serial Monitor" width="45%" />
</p>

## 👥 Authors
* [cite_start]**Aum Makwana** - *21bec062@nirmauni.ac.in* [cite: 2]
* [cite_start]**Neel Patel** - *22bec076@nirmauni.ac.in* [cite: 4]

<p align="center">
  [cite_start]<i>Dept. of Electronics and Communication, Nirma University [cite: 3]</i>
</p>
