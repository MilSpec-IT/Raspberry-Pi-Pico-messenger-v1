#include <RadioHead.h>

#define RFM95_CS 17
#define RFM95_RST 0
#define RFM95_INT 20
#define RF95_FREQ 915.0

RH_RF95 rf95(RFM95_CS, RFM95_INT);

void setup() {
  Serial.begin(115200);
  while (!Serial) {}

  pinMode(RFM95_RST, OUTPUT);
  digitalWrite(RFM95_RST, HIGH);

  if (!rf95.init()) {
    Serial.println("LoRa init failed");
    while (1) {}
  }

  rf95.setFrequency(RF95_FREQ);
  Serial.println("LoRa init succeeded");
}

void loop() {
  if (Serial.available()) {
    String message = Serial.readStringUntil('\n');
    char buf[message.length() + 1];
    message.toCharArray(buf, message.length() + 1);
    rf95.send((uint8_t*)buf, strlen(buf));
    Serial.print("Sent: ");
    Serial.println(message);
  }

  if (rf95.available()) {
    uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);
    if (rf95.recv(buf, &len)) {
      Serial.print("Received: ");
      Serial.println((char*)buf);
    }
  }
}
