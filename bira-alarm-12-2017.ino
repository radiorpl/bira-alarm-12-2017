#include <Wire.h>

//non-blinking characters
//               0    1   2  3   4   5   6    7  8    9   10 11   12 13  14  15  16  17  18  19  20  21   22 23  24  25  26  27  28  29  30  31  32  33  34  35  36
//               0    1   2  3   4   5   6    7  8    9   A  b    c  d    E   F  g   h   i   j   L   m    n  o   p   q   r   s   t   u   y   Z   -    _   ^   .  " "
byte seg0 [37] { 0,  65, 16, 0,  65, 4,  4,  64, 0,  64, 64, 5,  21, 1,  20, 84, 0,  69, 85, 1,  21, 68, 69, 5,  80, 64, 85, 4,  21, 5,  65, 16, 85, 21, 84, 85, 85 };
byte seg1 [37] { 80, 85, 68, 69, 65, 65, 64, 85, 64, 65, 64, 64, 68, 68, 64, 64, 65, 64, 84, 84, 80, 84, 68, 68, 64, 65, 68, 65, 64, 84, 65, 68, 69, 85, 85, 21, 85};

//blink
//                  0    1    2    3    4    5    6    7    8    9    A    b    c    d    E    F    g    h    i   j    L    m    n    o    p    q   r     s   t
//    																																						-   _  ^  . " "
byte segBlink0 [37] {255, 125, 223, 255, 125, 247, 247, 127, 255, 127, 127, 245, 213, 253, 215, 87,  255, 117, 85, 253, 213, 119, 117, 245, 95,  127, 85,  247, 213, 245, 125, 223, 85,  213, 87, 85,  85 };
byte segBlink1 [37] {95,  85,  119, 117, 125, 125, 127, 85,  127, 125, 127, 127, 119, 119, 127, 127, 125, 127, 87, 87,  95,  87,  119, 119, 127, 125, 119, 125, 127, 87,  125, 119, 117, 85,  85, 213, 85 };

byte digPins[4] = { 0, 1, 2, 3 };   //digit pins
byte pinCountDig = 4;				//number of digit pins
byte command [3] = { 21, 19, 20 }; //21 is first led register with auto increment, so send 21, then 2 btyes for led0-3 and then led4-7 19 is psc1, 20 is pwm1
int dig_delay = 2;

void setup(){
    for ( int pinDig = 0; pinDig < pinCountDig; pinDig++ ) {    // set digit pins as outputs
      pinMode(digPins[pinDig], OUTPUT);
  	}
	Serial.begin(9600);
	Wire.begin();					//begin i2c
	Wire.beginTransmission(96);  //set blink time
	Wire.write(command[1]);
	Wire.write(18); 			  //500ms
	Wire.write(128);				// 50% duty
	Wire.endTransmission();
	Serial.println("set up 8");
}

void write(int digit, int character){
  if (digit == 0){
	digitalWriteFast(digPins[0],HIGH); //first digit on
    digitalWriteFast(digPins[1],LOW); //other pins off
    digitalWriteFast(digPins[2],LOW);
    digitalWriteFast(digPins[3],LOW);
  	//i2c
  	Wire.beginTransmission(96);
  	Wire.write(command[0]);
	Wire.write(seg0[character]);
	Wire.write(seg1[character]);
  	Wire.endTransmission();
    delay(dig_delay);
  	Wire.beginTransmission(96);
  	Wire.write(command[0]);
	Wire.write(seg0[36]);
	Wire.write(seg1[36]);
  	Wire.endTransmission();
 }
  else if (digit == 1) {
    digitalWriteFast(digPins[0],LOW); //other pins off
    digitalWriteFast(digPins[1],HIGH); //second digit on
    digitalWriteFast(digPins[2],LOW);
    digitalWriteFast(digPins[3],LOW);
  	Wire.beginTransmission(96);
  	Wire.write(command[0]);
	Wire.write(seg0[character]);
	Wire.write(seg1[character]);
  	Wire.endTransmission();
    //Serial.println(digit);
    delay(dig_delay);
  	Wire.beginTransmission(96);
  	Wire.write(command[0]);
	Wire.write(seg0[36]);
	Wire.write(seg1[36]);
  	Wire.endTransmission();
  }
  else if (digit == 2) {
    digitalWriteFast(digPins[0],LOW); //other pins off
    digitalWriteFast(digPins[1],LOW); 
    digitalWriteFast(digPins[2],HIGH); //third digit on 
    digitalWriteFast(digPins[3],LOW);
  	Wire.beginTransmission(96);
  	Wire.write(command[0]);
	Wire.write(seg0[character]);
	Wire.write(seg1[character]);
  	Wire.endTransmission();
    delay(dig_delay);
  	Wire.beginTransmission(96);
  	Wire.write(command[0]);
	Wire.write(seg0[36]);
	Wire.write(seg1[36]);
  	Wire.endTransmission();
  }  
  else if (digit == 3) {
    digitalWriteFast(digPins[0],LOW); //other pins off
    digitalWriteFast(digPins[1],LOW); 
    digitalWriteFast(digPins[2],LOW);  
    digitalWriteFast(digPins[3],HIGH); //Fourth digit on
  	Wire.beginTransmission(96);
  	Wire.write(command[0]);
	Wire.write(seg0[character]);
	Wire.write(seg1[character]);
  	Wire.endTransmission();
    delay(dig_delay);
  	Wire.beginTransmission(96);
  	Wire.write(command[0]);
	Wire.write(seg0[36]);
	Wire.write(seg1[36]);
  	Wire.endTransmission();
  }
}

void loop(){
	write(0, 1);
	write(1, 1);
	write(2, 2);
	write(3, 3);
	//Serial.println("8");
}