#include <SPI.h>
#include <MFRC522.h>
#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// RFID Pin Definitions
#define RST_PIN  5    // Reset pin
#define SS_PIN   15   // Slave Select pin (changed from 21 to avoid I2C conflict)
#define MOSI_PIN 23   // SPI MOSI
#define MISO_PIN 19   // SPI MISO
#define SCK_PIN  18   // SPI Clock

MFRC522 rfid(SS_PIN, RST_PIN);

// LCD Configuration (16x2 LCD at I2C address 0x27, SDA=4, SCL=0)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Keypad Configuration
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {13, 12, 14, 27};
byte colPins[COLS] = {26, 25, 33, 32};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Authorized RFID Tags
const String authorizedTags[] = { "C0 E1 79 A3", "14 7B 4C 1D" };

// Global Variables
int currentFloor = 0;
bool floorSelected[6] = {false};

void setup() {
  Serial.begin(115200);
  Wire.begin(4, 0);  // SDA on GPIO 4, SCL on GPIO 0
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Scan RFID Tag");

  SPI.begin(SCK_PIN, MISO_PIN, MOSI_PIN, SS_PIN);
  pinMode(RST_PIN, OUTPUT);
  digitalWrite(RST_PIN, LOW);
  delay(10);
  digitalWrite(RST_PIN, HIGH);
  delay(10);
  rfid.PCD_Init();
}

void loop() {
  if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
    String tagID = getTagID();
    if (checkAuthorization(tagID)) {
      lcd.clear();
      lcd.print("Access Granted");
      delay(1000);
      handleLiftOperation();
    } else {
      lcd.clear();
      lcd.print("Access Denied");
      delay(1000);
    }
    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1();
    delay(1000);
  }
}

String getTagID() {
  String tagID = "";
  for (byte i = 0; i < rfid.uid.size; i++) {
    tagID += String(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
    tagID += String(rfid.uid.uidByte[i], HEX);
  }
  tagID.trim();
  tagID.toUpperCase();
  return tagID;
}

bool checkAuthorization(String tagID) {
  for (const auto& authorizedTag : authorizedTags) {
    if (tagID == authorizedTag) return true;
  }
  return false;
}

void handleLiftOperation() {
  memset(floorSelected, false, sizeof(floorSelected));
  lcd.clear();
  lcd.print("Select Floor (0-5)");
  unsigned long startTime = millis();
  while (millis() - startTime < 4000) {
    char key = keypad.getKey();
    if (key && key >= '0' && key <= '5') {
      int floor = key - '0';
      floorSelected[floor] = true;
      lcd.clear();
      lcd.print("Selected: ");
      lcd.print(floor);
    }
  }
  for (int i = 0; i < 6; i++) {
    if (floorSelected[i]) {
      moveLift(i);
    }
  }
}

void moveLift(int targetFloor) {
  lcd.clear();
  if (currentFloor < targetFloor) {
    lcd.print("Going Up...");
    for (int f = currentFloor; f <= targetFloor; f++) {
      updateFloorDisplay(f);
    }
  } else if (currentFloor > targetFloor) {
    lcd.print("Going Down...");
    for (int f = currentFloor; f >= targetFloor; f--) {
      updateFloorDisplay(f);
    }
  }
  lcd.clear();
  lcd.print("Arrived: ");
  lcd.print(targetFloor);
  delay(2000);
  currentFloor = targetFloor;
}

void updateFloorDisplay(int floor) {
  lcd.clear();
  lcd.print("Floor: ");
  lcd.print(floor);
  delay(1000);
}
