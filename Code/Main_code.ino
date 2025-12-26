#include <Wire.h>
#include <Adafruit_GFX.h> //oled display
#include <Adafruit_SSD1306.h>
#include "HX711.h" //load cell module
#include <Wire.h>
#include <LiquidCrystal_I2C.h> //lcd
#include <SPI.h> //rfid
#include <MFRC522.h> //rfid


// OLED display settings
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET     -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// HX711 settings
#define LOADCELL_DOUT_PIN 25
#define LOADCELL_SCK_PIN 26
HX711 scale;

float calibration_factor = 480; // Adjust this value for your load cell , calibration factor= cal weight/actual weight * calibration factor

#define SS_PIN 5
#define RST_PIN 15

LiquidCrystal_I2C lcd(0x27, 16, 2); // Change I2C address if needed
MFRC522 rfid(SS_PIN, RST_PIN);

struct Item {
  byte uid[4];
  const char* name;
  float price;
};

// Replace these UIDs with your actual card UIDs
Item items[] = {
  {{0xA4, 0x44, 0x11, 0x05}, "Calculator", 380.0},
  {{0x0D, 0x44, 0x07, 0x04}, "Watch", 2000.0},
  {{0x2A, 0xB9, 0x07, 0x04}, "Almond", 200.0}
};
const int NUM_ITEMS = sizeof(items) / sizeof(items[0]);

// UID of the reset card
byte resetCardUID[4] = {0x8C, 0x5E, 0xD6, 0x00}; // The UID of your last RFID card (Stapler's UID)

float total = 0; // Running total

void setup() {
  Serial.begin(9600);

  // Initialize OLED
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // 0x3C is common I2C address
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.println("Weight:");
  display.display();

  // Initialize HX711
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(calibration_factor); // Adjust as needed
  scale.tare(); // Reset the scale to 0

  SPI.begin();
  rfid.PCD_Init();
  lcd.init();
  lcd.backlight();
  displayTotal(); // Show total at startup

}

void loop() {
  float weight = scale.get_units(2); // Average of 5 readings

  float weight_kg = weight / 1000.0; // Convert grams to kilograms

display.clearDisplay();
display.setTextSize(2);
display.setCursor(0, 0);
display.print("Weight:");
display.setTextSize(2);
display.setCursor(0, 30);
display.print(weight_kg, 3); // Show 3 decimal places
display.print(" kg");
display.display();
  delay(500); // Update twice per second

if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
    // Print UID to Serial for reference
    Serial.print("Card UID: ");
    for (byte i = 0; i < rfid.uid.size; i++) {
      Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
      Serial.print(rfid.uid.uidByte[i], HEX);
    }
    Serial.println();

    // Check if the scanned card is the reset card
    if (compareUID(rfid.uid.uidByte, resetCardUID)) {
      total = 0; // Reset the total
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Total Reset!");
      delay(2000);
      displayTotal(); // Update the display
    } else {
      // Check if UID matches any item for purchase
      bool found = false;
      for (int i = 0; i < NUM_ITEMS; i++) {
        if (compareUID(rfid.uid.uidByte, items[i].uid)) {
          total += items[i].price;
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print(items[i].name);
          lcd.setCursor(0, 1);
          lcd.print("Rs:");
          lcd.print(items[i].price, 2);
          delay(2000); // Show item details for 2 seconds

          found = true;
          break;
        }
      }
      if (!found) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Unknown Item");
        delay(2000);
      }
      displayTotal(); // Show updated total
    }
    rfid.PICC_HaltA();
  }
}

void displayTotal() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Total: Rs.");
  lcd.print(total, 2);
  lcd.setCursor(0, 1);
  lcd.print("Scan next card");
}

// Helper function to compare UIDs
bool compareUID(byte *uid1, byte *uid2) {
  for (byte i = 0; i < 4; i++) {
    if (uid1[i] != uid2[i]) return false;
  }
  return true;
}