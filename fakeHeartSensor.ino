#include "adafruit-led-backpack.h"
#include "SparkFunMMA8452Q.h"

// Create an MMA8452Q object, used throughout the rest of the sketch.
MMA8452Q accel; // Default constructor, SA0 pin is HIGH
SYSTEM_MODE(SEMI_AUTOMATIC);


Adafruit_BicolorMatrix matrix = Adafruit_BicolorMatrix();
String testString = "YOUR MESSAGE HERE";
float myx = 0.0;
float prex = 0.0;
long cMillis = 0;
int gapMillis = 1000;
int rate = 0;
int outNum = 60;
int totNum = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("8x8 LED Matrix Test");
  matrix.begin(0x70);  // pass in the address
  Particle.function("writeText",writeText);
  matrix.setTextColor(LED_GREEN);
  matrix.setTextWrap(false);  // we dont want text to wrap so it scrolls nicely
  matrix.setTextSize(1);
  accel.begin(SCALE_2G, ODR_1);

}



void loop() {
  if (accel.available())
    {
		// To update acceleration values from the accelerometer, call accel.read();
        accel.read();
        //testString =  "grrrrrrr";
        myx = accel.cx;

        float change = (myx*10) - (prex*10);
        prex = myx;
        rate = rate + abs(change);

      //testString = String(abs(change));

        //testString = String(accel.cx);
    }

  if(outNum > 10){
    outNum = 0;

    totNum ++;
    testString = String(totNum);


  }
  matrix.clear();
  int len = testString.length();
  for (int x=7; x>=-(len*6); x--) {
    if ((cMillis+gapMillis) < millis()){
      outNum ++;
      cMillis = millis();

      gapMillis = 1000 -(rate*50);
      //testString = String(gapMillis);
      //rate = 0;


  }
    matrix.clear();
    matrix.setCursor(x,0);
    matrix.print(testString.c_str());
    matrix.writeDisplay();
    delay(60);
    }


}

int writeText(String command) {
  Serial.println(command);

  if(command.equals("red")){
    matrix.setTextColor(LED_RED);
  }else if(command.equals("green")){
    matrix.setTextColor(LED_GREEN);
  }else{
    testString = command;
    //myText = command;
  }


}
