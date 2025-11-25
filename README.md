<div align="center">
  <img width="100%" height="300" src="https://images.unsplash.com/photo-1531297461136-82lw9b2b0a43?ixlib=rb-4.0.3&auto=format&fit=crop&w=1000&q=80" alt="Banner Image" style="object-fit: cover; border-radius: 10px;" />
</div>

<div align="center">

# Lift Authentication System
### RTOS-Based Secure Access Control Implementation on ESP32

<p align="center">
  <img src="https://img.shields.io/badge/Device-ESP32_WROOM-red?style=for-the-badge&logo=espressif" />
  <img src="https://img.shields.io/badge/OS-FreeRTOS-green?style=for-the-badge&logo=freertos" />
  <img src="https://img.shields.io/badge/Language-C++_/_Arduino-blue?style=for-the-badge&logo=arduino" />
  <img src="https://img.shields.io/badge/Sensor-RFID_RC522-orange?style=for-the-badge&logo=nfc" />
  <img src="https://img.shields.io/badge/University-Nirma_University-yellow?style=for-the-badge" />
</p>

</div>

---

## 📄 Abstract
This project presents a **Lift Authentication System** designed to enhance security and access control in multi-user environments.

The system utilizes an **ESP32 microcontroller** integrated with a **Real-Time Operating System (RTOS)** to manage time-critical authentication tasks with precision. By employing an **RFID Reader** for user verification and a keypad for floor selection, the system ensures that only authorized personnel can access specific floors. The use of FreeRTOS allows for deterministic task scheduling, ensuring that high-priority security tasks (like detecting an intrusion) do not block routine operations.

## 👥 Authors
* **Aum Makwana** (21BEC062)
* **Neel Patel** (22BEC076)
* *Dept:* Electronics and Communication - Nirma University

---

## 🛠️ Tech Stack & Hardware
<p align="left">
  <a href="#" target="_blank">
    <img src="https://img.shields.io/badge/ESP32-Microcontroller-red?logo=espressif&style=flat-square" alt="ESP32"/>
  </a>
  <a href="#" target="_blank">
    <img src="https://img.shields.io/badge/FreeRTOS-Real_Time_OS-green?logo=freertos&style=flat-square" alt="FreeRTOS"/>
  </a>
  <a href="#" target="_blank">
    <img src="https://img.shields.io/badge/Arduino_IDE-Development_Env-teal?logo=arduino&style=flat-square" alt="Arduino IDE"/>
  </a>
  <a href="#" target="_blank">
    <img src="https://img.shields.io/badge/ThingSpeak-Cloud_Logging-orange?logo=mathworks&style=flat-square" alt="ThingSpeak"/>
  </a>
</p>

| Component | Specification | Description |
| :--- | :--- | :--- |
| **Microcontroller** | ESP32-WROOM-32 | Dual-core 32-bit MCU, 240MHz, WiFi/BT. |
| **Auth Sensor** | MFRC522 RFID | 13.56MHz frequency, SPI Interface. |
| **Input Method** | 4x4 Matrix Keypad | Used for selecting floors (0-5). |
| **Display** | 16x2 LCD (I2C) | Visualizes status: "Scanning", "Access Granted". |
| **Actuators** | Relay & Buzzer | Controls lift door mechanism and security alerts. |

---

## ⚙️ Architecture & RTOS Implementation

The system software is structured around **FreeRTOS** to handle multitasking efficiently. The key tasks include:

1.  **RFID Authentication Task (High Priority):** Interrupt-driven detection of RFID tags to verify UID against a hardcoded whitelist.
2.  **User Interface Task:** Manages the 4x4 Keypad input to capture floor selection within a 4-second timeout window.
3.  **Display Task:** Updates the I2C LCD with real-time feedback (Floor Number, Auth Status) without blocking the processor.
4.  **Logging Task:** Stores access logs (UID + Timestamp) for security monitoring.

### 📸 System Diagram

<div align="center"> 
 <img width="788" height="1163" alt="ES Block Diagram" src="https://github.com/user-attachments/assets/0ae9c7fd-b0c4-448c-8d39-de0acf2fb415" />
 <br>
 <em>Block Diagram of the Lift Authentication System</em>
</div>

---

## 🔌 Hardware Pin Mapping

### ESP32 $\leftrightarrow$ Peripherals Connection

| Peripheral | Component Pin | ESP32 Pin (GPIO) | Protocol |
| :--- | :--- | :--- | :--- |
| **RFID (RC522)** | SDA (SS) | `GPIO 21` | SPI |
| | SCK | `GPIO 18` | SPI |
| | MOSI | `GPIO 23` | SPI |
| | MISO | `GPIO 19` | SPI |
| | RST | `GPIO 5` | - |
| **Keypad (Rows)** | R1, R2, R3, R4 | `13, 12, 14, 27` | Digital In |
| **Keypad (Cols)** | C1, C2, C3, C4 | `26, 25, 33, 32` | Digital Out |
| **LCD Display** | SDA | `GPIO 21` (Shared) | I2C |
| | SCL | `GPIO 22` | I2C |

*Note: The Keypad utilizes a matrix scanning algorithm to detect key presses efficiently.*

---

## 💻 Simulation & Results

The system was tested in a residential simulation scenario.

* **Authorized Access:** User scans valid card (UID `C0 E1 79 A3`), system prompts for floor. User presses '5', lift moves to Floor 5.
* **Unauthorized/Timeout:** If an invalid tag is scanned or no floor is entered within 4 seconds, access is denied and the system resets.

<div align="center"> 
  <img width="467" height="440" alt="1 (1)" src="https://github.com/user-attachments/assets/b651fac1-10f7-46d1-aac3-38ffc5971610" />
  <img width="495" height="145" alt="2" src="https://github.com/user-attachments/assets/8443affb-27d9-4f71-afd0-e70777db0e90" />
  <br>
  <em>Left: Serial Monitor Output 1 | Right: Serial Monitor Output 2 </em>
</div>
<div align="center"> 
  ![IMG_20250330_191232](https://github.com/user-attachments/assets/1051cbc8-ac8b-48a6-a902-af3a3e8ba45b)
  <br>
  <em>Hardware Implementation  </em>
</div>

### Code Snippet (Authorization Logic)
```cpp
// Check if the scanned tag matches authorized list
bool checkAuthorization(String tagID) {
    for (int i = 0; i < sizeof(authorizedTags) / sizeof(authorizedTags[0]); i++) {
        if (tagID.equals(authorizedTags[i])) {
            return true; // Tag is authorized
        }
    }
    return false; // Not authorized
}

// Logic to move lift
if (currentFloor < targetFloor) {
    Serial.println("Lift is going up...");
    // Loop through floors to simulate movement
    for (int f = currentFloor; f <= targetFloor; f++) {
        lcd.print("Floor: ");
        lcd.print(f);
        delay(1000); 
    }
}
