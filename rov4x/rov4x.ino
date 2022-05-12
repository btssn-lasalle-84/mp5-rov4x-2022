#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <Arduino.h>
#include <DHT.h>
#include <Adafruit_Sensor.h>
#include <Arduino.h>

#define DHTPIN  6     // indique la pin du dht
#define DHTTYPE DHT22 // indique le DHT

//joystick moteur
#define joystick_x_m 0             // joystick x                                          
#define joystick_y_m 1             // joystick y d                                     
 
// Moteur 1
#define ENA 5
#define IN1 7               //Moteur 1
#define IN2 8               //Moteur 2
 
// Motor 2
#define IN3 9               //Moteur 3
#define IN4 10              //Moteur 4
#define ENB 3
 
//joystick camera
#define joystick_x 2              // joystick x                                        
#define joystick_y 3             // joystick y

#define SERVOMIN  150 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  600 // This is the 'maximum' pulse length count (out of 4096)
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

int pos_x_m;                   // on déclare une variable "pos_x" qui prendra plus tard la valeur du joystick_x_m
int pos_y_m;                   // on déclare une variable "pos_y" qui prendra plus tard la valeur du joystick_y_m
int pos_x;                   // on déclare une variable "pos_x" qui prendra plus tard la valeur du joystick_x
int pos_y;                   // on déclare une variable "pos_y" qui prendra plus tard la valeur du joystick_y
int px = 1500;                // On indique la position de base (pan) des servomoteurs
int py = 1500;                // On indique la posistion de base (tilt) des servomoteurs
// Servomoteur 1 et 2 (pour le pan et pour le tilt)
uint8_t servonum1 = 0;
uint8_t servonum2 = 1; 
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
DHT dht(DHTPIN, DHTTYPE);

void setServoPulse(uint8_t n, double pulse)
{ //On code sur 8 bits non signés (donc les valeurs sont soit positives soit nulles)
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
 
// DEBUT CODE DES DEPLACEMENTS MOTEURS
void Avancer()
{
 //sens moteur A
 digitalWrite (IN1, HIGH);
 digitalWrite (IN2, LOW);
 analogWrite (ENA,200); //Vitesse moteur A
 //sens moteur B
 digitalWrite (IN3, HIGH);
 digitalWrite (IN4, LOW);
 analogWrite (ENB, 200); //Vitesse moteur B
}

void Reculer()
{
 //sens moteur A
 digitalWrite (IN1, LOW);
 digitalWrite (IN2, HIGH);
 analogWrite (ENA, 200); //Vitesse moteur A
 //sens moteur B
 digitalWrite (IN3, LOW);
 digitalWrite (IN4, HIGH);
 analogWrite (ENB, 200); //Vitesse moteur B
}

void Droite()
{
 // sens moteur A
 digitalWrite (IN1, HIGH);
 digitalWrite (IN2, LOW);
 analogWrite (ENA, 0); //Vitesse moteur A
 // sens moteur B
 digitalWrite (IN3, LOW);
 digitalWrite (IN4, HIGH);
 analogWrite (ENB, 200); //Vitesse moteur B
}

void Gauche()
{
 // Sens moteur A
 digitalWrite (IN1, LOW);
 digitalWrite (IN2, HIGH);
 analogWrite (ENA, 200); //Vitesse moteur A
 //sens moteur B
 digitalWrite (IN3, HIGH);
 digitalWrite (IN4, LOW);
 analogWrite (ENB, 0); //Vitesse motor B
}

void Arreter()
{
 // Sens moteur A
 digitalWrite (IN1, LOW);
 digitalWrite (IN2, LOW);
 analogWrite (ENA, 0); //Vitesse moteur A
 // Sens moteur B
 digitalWrite (IN3, LOW);
 digitalWrite (IN4, LOW);
 analogWrite (ENB, 0); //Vitesse moteur B
}
// FIN CODE DEPLACEMENTS MOTEURS

// DEBUT TRAME HUMIDITE/TEMPERATURE
void trame(int h,float t)
{
 Serial.print('$');
 Serial.print(1);
 Serial.print('-');
 Serial.print(t); // affiche la température
 Serial.print('-');
 Serial.print(h); // affiche le taux d'humidité
 Serial.print('.');
 Serial.println();
}
// FIN TRAME HUMIDITE/TEMPERATURE

// DEBUT SETUP
void setup()
{
  // SETUP MOTEUR
  pinMode (ENA, OUTPUT);
  pinMode (ENB, OUTPUT);
  pinMode (IN1, OUTPUT);
  pinMode (IN2, OUTPUT);
  pinMode (IN3, OUTPUT);
  pinMode (IN4, OUTPUT);
  // FIN SETUP MOTEUR

  // DHT 22
  Serial.begin(9600); // fréquence de transmission de bit
  dht.begin(); // initisalisation du capteur
  // FIN DHT 22

  // DEBUT SETUP CAMERA
  Serial.begin(9600);
  Serial.println("8 channel Servo test!");
 
  pwm.begin();
 
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates
  // FIN SETUP CAMERA
 
  delay(10);
}
// FIN SETUP

void loop()
{
// DEBUT LECTURE DE LA POSITION DES JOYSTICK (contrôle moteur et servomoteur)
pos_x = analogRead (joystick_x) ;  
pos_y = analogRead (joystick_y) ;
pos_x_m = analogRead (joystick_x_m) ;  
pos_y_m = analogRead (joystick_y_m) ;
// FIN DE LA LECTURE

// DEBUT DHT 22
 int h = dht.readHumidity(); // associe h à l'humidité
 float t = dht.readTemperature(); // associe t à la température
 
 if (isnan(h) || isnan(t)) { // pose une condition
   Serial.println(F("Failed to read from DHT sensor!")); // affiche la valeur
   return;
 }

 trame(h,t);
// FIN DHT 22

// DEBUT CODE MOTEUR
 if (pos_y_m>700)
 {
     Avancer();
 }
 else if (pos_y_m<300)
     Reculer(); 
 else if (pos_x_m>700)
 {
     Gauche();
 }
 else if (pos_x_m<300)
     Droite();     
 else
 {
     Arreter() ;
 }
// FIN CODE MOTEUR

// DEBUT CODE CAMERA
if ((pos_x > 600) && (px>600))
{
  px= px-5;
  pwm.writeMicroseconds(servonum2,px);
}

if ((pos_x < 400) && (px<2400))
{
  px=px+5;
  pwm.writeMicroseconds(servonum2,px);
}
 
if ((pos_y < 600) && (py>600))
{
  py= py-5;
  pwm.writeMicroseconds(servonum1,py);
}

if ((pos_y > 400) && (py<2400))
{
  py=py+5;
  pwm.writeMicroseconds(servonum1,py);
}
// FIN CODE CAMERA
}
