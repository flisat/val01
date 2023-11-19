#include <Adafruit_NeoPixel.h>

#define NeoPixelOutPin  17
#define NeoPixelInPin   16
#define NumPixels       8

#define AnalogInPin     26
#define AnalogOutPin    15

#define LogInPin1       0
#define LogInPin2       1
#define LogOutPin       2


int setColor[5][3] = {{255, 255, 255}, {255, 0, 0}, {0, 255, 0}, {0, 0, 255}, {0, 0, 0} };
Adafruit_NeoPixel pixels(NumPixels, NeoPixelOutPin, NEO_GRB + NEO_KHZ800);

int LogMode = random(1, 4);

void setup() {
  pixels.begin();
  pixels.setBrightness(20);
  pinMode(NeoPixelInPin, INPUT);

  pinMode(AnalogOutPin, OUTPUT);

  pinMode(LogInPin1, INPUT);
  pinMode(LogInPin2, INPUT);
  pinMode(LogOutPin, OUTPUT);
}
int j = -1;
void loop() {

  /***** ENGINE ******/
  int adcVal = analogRead(AnalogInPin)+200; //read adc
  double voltage = adcVal / 1023.0 * 3.3;
  if(voltage < 1){
    digitalWrite(AnalogOutPin, LOW);
  }else{
    analogWrite(AnalogOutPin, map(adcVal, 0, 1023, 0, 255));
  }
  /***** ENGINE ******/

  /***** LOGIC ******/
  if(LogMode == 1) {

    if(digitalRead(LogInPin1) && digitalRead(LogInPin2)){
      digitalWrite(LogOutPin, HIGH);
    }else{
      digitalWrite(LogOutPin, LOW);
    }
  } else if (LogMode == 2) {

    if(digitalRead(LogInPin1) || digitalRead(LogInPin2)){
      digitalWrite(LogOutPin, HIGH);
    }else{
      digitalWrite(LogOutPin, LOW);
    }
  } else if (LogMode == 3) {

    if(digitalRead(LogInPin1) && !digitalRead(LogInPin2) || !digitalRead(LogInPin1) && digitalRead(LogInPin2)){
      digitalWrite(LogOutPin, HIGH);
    }else{
      digitalWrite(LogOutPin, LOW);
    }
  }
  /***** LOGIC ******/

  /***** NEO PIXEL ******/
  if(digitalRead(NeoPixelInPin) == LOW) {
    j = j+1;
    LogMode = random(1, 4);
    for (int i = 0; i < NumPixels; i++) {
      pixels.setPixelColor(i, setColor[j][0], setColor[j][1], setColor[j][2]); pixels.show();
      delay(100);
    }

    if(j==4) j=-1;
  }
  /***** NEO PIXEL ******/

}