/*
 * Langmuir probe logger
 * 
 * Amplifier connected to A0
 * 
 * Converts reading to voltage and records it in a file in an SD card.
 * pins 11,12,13 and 4 used by SPI for read/write
 * 
 */
#include<SPI.h>
#include<SD.h>
float voltage;
boolean sdinit = false;
int cs = 4, Probe = A0;
void setup() {
  if(SD.begin(cs))
    sdinit = true;
}

void loop() {
  voltage = analogRead(Probe)*0.00488; // Volts
  if(sdinit)
    process(voltage); // It writes the voltage into an sd card, but could send the data vie Serial or do something else
  delay(5); // waits 5 milliseconds to do next measurement
}
void process(float v){
  File dopen = SD.open("voltage.txt", FILE_WRITE);
  if(dopen){
    dopen.println(String(millis())+","+String(v,5)); // Writes time in millisecods and voltage
    dopen.close();
  }
}

