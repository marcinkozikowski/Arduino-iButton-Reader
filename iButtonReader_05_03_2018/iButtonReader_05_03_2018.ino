#include <OneWire.h>

OneWire  ds(12);
byte addr[8];
//String keyStatus= "false";
const String iButtonTag="01A8E0B5";
bool lastButtonState = false;


void setup(void) {
  pinMode(8, OUTPUT); //GREEN LED
  pinMode(9, OUTPUT); //RED LED
  pinMode(10, OUTPUT); //Signal
  pinMode(2,OUTPUT);//ENABLE
  pinMode(3,OUTPUT);//Input1
  Serial.begin(115200);
  Serial.println("Setup...");
}


void loop(void) {
  //getKeyCode();
  if(getKeyCode()){
      byte i;
      String tmp="";
      for( i = 5; i >0; i--) {
           tmp +=String(addr[i],HEX);           
      }
      
      String b ="";
      b=String(tmp);
      b.toUpperCase();
      Serial.println("\nTmp: "+b);
      Serial.println("iButtonTag "+iButtonTag);
      Serial.println(b);
      if(checkButton(b))
      {
        Serial.print("Pelna zgodnosc, pastylka w czytniku");
        digitalWrite(8,HIGH);
        digitalWrite(10,HIGH);
        digitalWrite(9,LOW);
        sendHighState();
      }
  }
  else if(!getKeyCode())
      {
        digitalWrite(8,LOW);
        digitalWrite(9,HIGH);
        digitalWrite(10,LOW);
        sendLowState();
        Serial.println("\nFalse ");
      }
  delay(1000);
}

bool checkButton(String readedButton){
  if(readedButton == iButtonTag){
    return true;
  }
  else return false;
  }

void sendHighState(){
  digitalWrite(2,HIGH);
  digitalWrite(3,HIGH);
}

void sendLowState(){
  digitalWrite(2,LOW);
  digitalWrite(3,LOW);
}
  
bool getKeyCode(){
  byte present = 0;
  byte data[12];
  //keyStatus="false";
  
  if ( !ds.search(addr)) {
      ds.reset_search();
      return false;
  }
  if ( OneWire::crc8( addr, 7) != addr[7]) {
      return false;
  }
  if ( addr[0] != 0x01) {
      return false;
  }
  else{
   return true;
  }
  delay(1000);
  ds.reset();
}

