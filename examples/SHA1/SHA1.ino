#include <JHash.h>

void setup() {
  Serial.begin(115200);
  const char* data = "My Name Is JimmyTai";
  uint8_t digest[20];
  JHash::SHA1.encode((unsigned char*) data, strlen(data), digest);
  for(uint8_t i = 0; i < sizeof(digest); i++){
    char printBuf[10];
    sprintf(printBuf, "%02x", digest[i]);
    Serial.print(printBuf);
  }
}

void loop() {
  
}
