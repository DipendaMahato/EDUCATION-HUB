#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 5   // Change according to your wiring
#define RST_PIN 22 // Change according to your wiring

MFRC522 rfid(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(115200);
  SPI.begin();            // Initialize SPI bus
  rfid.PCD_Init();        // Initialize MFRC522
  Serial.println("Place your RFID card near the reader...");
}

void loop() {
  // Check for new cards
  if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
    Serial.print("Tag UID: ");
    String tagID = "";
    for (byte i = 0; i < rfid.uid.size; i++) {
      // Convert each byte of the UID to a hex string
      tagID += String(rfid.uid.uidByte[i], HEX);
    }
    Serial.println(tagID);

    // Halt PICC (Card)
    rfid.PICC_HaltA();
  }
}
