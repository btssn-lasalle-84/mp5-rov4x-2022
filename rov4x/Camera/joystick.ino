#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#define SERVOMIN  150 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  600 // This is the 'maximum' pulse length count (out of 4096)
#define USMIN  600 // This is the rounded 'minimum' microsecond length based on the minimum pulse of 150
#define USMAX  2400 // This is the rounded 'maximum' microsecond length based on the maximum pulse of 600
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

int joystick_x = A0;              // joystick x direction pin                                          
int joystick_y = A1;              // joystick y direction pin                                        
int pos_x;                   // declaring variable to stroe horizontal value
int pos_y;                   // declaring variable to stroe vertical value
int px= 1500;
int py = 1500;
uint8_t servonum1 = 0;
uint8_t servonum2 = 1;
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

void setServoPulse(uint8_t n, double pulse)
{
  double pulselength;
 
  pulselength = 1000000;   // 1,000,000 us per second
  pulselength /= SERVO_FREQ;   // Analog servos run at ~60 Hz updates
  Serial.print(pulselength); Serial.println(" us per period");
  pulselength /= 4096;  // 12 bits of resolution
  Serial.print(pulselength); Serial.println(" us per bit");
  pulse *= 1000000;  // convert input seconds to us
  pulse /= pulselength;
  Serial.println(pulse);
  pwm.setPWM(n, 0, pulse);
}

void setup()
{
  Serial.begin(9600);
  Serial.println("Test Servo");

  pwm.begin();

  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates

  delay(10);
}

void loop()
{
  pos_x = analogRead(joystick_x);
  pos_y = analogRead(joystick_y);

  Serial.println(pos_x);

  if ((pos_x > 600) && (px > 600))
  {
      px = px - 5;
      pwm.writeMicroseconds(servonum2, px);
  }
  if ((pos_x < 400) && (px < 2400))
  {
    px = px + 5;
    pwm.writeMicroseconds(servonum2, px);
}

  if ((pos_y < 600) & (py>600))
  {
    py = py-5;
    pwm.writeMicroseconds(servonum1,py);
  }

  if ((pos_y > 400) && (py < 2400))
  {
    py = py + 5;
    pwm.writeMicroseconds(servonum1, py);
  }
}
