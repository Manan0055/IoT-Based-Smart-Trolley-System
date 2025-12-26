# IoT-Based-Smart-Trolley-System

📌 Overview
This project is an IoT-based smart shopping trolley that simplifies the in-store shopping experience by integrating a manual RFID-based product scanning system and real-time item weight monitoring. The trolley enables users to scan each item by placing its RFID tag on a reader, calculates the total cost, and displays important data like item prices and weight directly on onboard displays.

With separate display units—LCD for item prices and total cost, and a 0.95" OLED (SSD1306) for weight tracking—this project offers a step towards more interactive and self-service shopping in smart retail setups.    


## Key Features

  - Manual RFID Scanning: Users scan items by placing RFID tags on the reader; the system then identifies the item and fetches its price.         
  - Real-Time Billing: Automatically calculates and displays the total bill and item-wise prices on an LCD screen.
  -  Weight Display on OLED: Shows the live weight of items in the trolley using HX711 + Load Cell, output on a 0.95-inch OLED (SSD1306) display.
  - Dual Display System:          
     LCD: Item name, price, total cost.        
     OLED: Total weight in kilograms or grams.
  -  IoT Expandable: Design is modular for future integration with cloud platforms and mobile applications.


 ## How It Works         
 
- Each product is assigned an RFID tag.           
- The shopper places the RFID tag over the RFID reader (RC522) manually to scan the item.           
- The system fetches the item's price and weight from a predefined database or code.         
- The LCD screen displays the item's name, price, and continuously updated total cost.           
- Meanwhile, the HX711 load cell measures the current weight of items in the trolley, which is shown on the OLED screen.          
- This gives the user a full view of both spending and item weight while shopping.



## Components used

- RFID Module: MFRC522
- Load Cell Sensor: 1Kg/5Kg + HX711 Amplifier
- Display 1 (Price/Total): 16x2 LCD (with or without I2C)
- Display 2 (Weight): 0.95" SSD1306 OLED
- Power Supply: 5V USB or Li-ion battery
- Optional Add-ons: Buzzer, SD card logging, Wi-Fi module (ESP8266/ESP32) for IoT/cloud

## Project Illustration   
![iot project photo](https://github.com/user-attachments/assets/b892ee6c-88cc-42ad-ae89-00227bb698d3)                                                                                       

## Tutorial Video


https://github.com/user-attachments/assets/da175a16-7ea2-437a-ad58-e2610e889285

