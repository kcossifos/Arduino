#include <EEPROM.h>

const byte R = 5;
const byte G = 6;
const byte B = 7;

void setup() {
pinMode(R, OUTPUT);
pinMode(G, OUTPUT);
pinMode(B, OUTPUT);

Serial.begin(56700);

analogWrite(R, EEPROM.read(0));
analogWrite(G, EEPROM.read(1));
analogWrite(B, EEPROM.read(2));
}

char buf[5];
int idx = 0;

byte save = 0;

void loop() {
while(Serial.available() > 0) {

char readByte = Serial.read();
if(readByte == 'w') {
} else if(readByte == 's') {
save = 1;
} else if(readByte == 'r' || readByte == 'g' || readByte == 'b') {
idx = 0;
int val = atoi(buf);
//if(val < 0) val = 0;
if(val > 255) val = 255;
byte addr = 0;

if(readByte == 'r') analogWrite(R, val);
if(readByte == 'g') { analogWrite(G, val); addr = 1; }
if(readByte == 'b') { analogWrite(B, val); addr = 2; }

if(save == 1) {
  
EEPROM.write(addr, val);
save = 0;
}

} else {
//_delay_ms(1);
buf[idx] = readByte;
idx++;
if(idx == 3) idx = 0;
}
}
}
