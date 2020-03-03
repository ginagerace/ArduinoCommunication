//Ryan Gaul, 669188240, rgaul2 & Gina Gerace, 664765515, ggerac3
//Lab 7: Arduino Communication
//This code is suppose to allow two arduinos to communicate. A button push
//  on one should cause an LED to light up on the other.0
//We assume that the arduinos will be able to send and receive info from each other.
//We used https://iot-guider.com/arduino/serial-communication-between-two-arduino-boards/
//  as a reference.
// Also used Lab 2 and 6 as a reference

int led1 = 12;
int ardin = 0;
int ardout = 1;
int but = 2;
int counter;
int up1;
int up2;
int butState;
int ardState;
int prevState;
int led1s;
bool change;
void setup() {
  Serial.begin(9600); //communication
  pinMode(led1, OUTPUT); //IO
  pinMode(ardin, INPUT); 
  pinMode(ardout, OUTPUT);
  pinMode(but, INPUT);

  butState = digitalRead(but); //button state
  ardState = Serial.read(); //current state
  prevState = Serial.read();
  led1s = 0; //led is off
  counter = 0; 
  bool change = false; //led is off
  delay(25);
}

void loop() {
  up1 = digitalRead(but);//for debounce 
  delay(10);
  up2 = digitalRead(but); //for debounce

  if(up1 == up2){ //debounce code
    if(up1 != butState){
        Serial.write(up1); //write the new button val
        butState = up1; //recognize the new button val
        delay(200); //dont spam it
      }
  }
  
  while(Serial.available() > 0){ //if serial is running
    if(Serial.read() == 0){ //if button is down
      while(Serial.read() == 0){ //while button is still down
        counter++; 
        delay(10);//wait while button is down
      }
      bool change = !change; //change the led
      if(change){ //make led high
        digitalWrite(led1, HIGH);
      delay(50);
      }
      else{ //make led low
        digitalWrite(led1, LOW);
      delay(50);
      }
    }
    
  }
}
