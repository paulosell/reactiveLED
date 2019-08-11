#include <Adafruit_NeoPixel.h>
int nleds = 30;
int pinoLED = 9;
String inString = "";  
String cores[4] = {"","","",""};
int coress[4] = {0,0,0,0};
int i = 0;
int mic = A0;
Adafruit_NeoPixel pixels=Adafruit_NeoPixel(nleds,pinoLED,NEO_GRB+NEO_KHZ800);

void setup() {

  pixels.begin();
  pixels.setBrightness(255);  
  Serial.begin(9600);
  while (!Serial) {
    ; 
  }
  pinMode(mic, INPUT);

}

void loop() {
  if(Serial.read() > 0){
    change();
  }
  int nivel = digitalRead(mic);
   
  if(nivel){
    pixels.setBrightness(255);  
    for (int i=0;i<nleds;i++){
    pixels.setPixelColor(i,pixels.Color(coress[1], coress[2], coress[3])); 
    }    

  }else {
    pixels.setBrightness(128);  
    for (int i=0;i<nleds;i++){
      pixels.setPixelColor(i,pixels.Color(coress[1], coress[2], coress[3])); 
    }
  }
   pixels.show();
   for(int i = 0; i < 4; i++){
    Serial.println(coress[i]);
   }
}


void change(){
  while (i < 4){
    while (Serial.available() > 0) {
    int inChar = Serial.parseInt();
   
      coress[i] = inChar;
      Serial.println(coress[i]);
      
      i++;
    }
  }
  
   i = 0;
}
void change_color(){
    while (i < 4){
    while (Serial.available() > 0) {
    int inChar = Serial.read();
    if (isDigit(inChar)) {
      inString += (char)inChar;
    }
    if (inChar == '\n') {
      cores[i] = inString;
      Serial.println(cores[i]);
      inString = "";   
      i++;
    }
  }
  }
   i = 0;

}
