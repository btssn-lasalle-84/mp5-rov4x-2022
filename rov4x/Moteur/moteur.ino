#include <Arduino.h>
#include <Wire.h>
 
#define joystick_x 0              // joystick x direction pin                                          
#define joystick_y 1              // joystick y direction pin    
 
// Moteur 1
#define ENA 5
#define IN1 7
#define IN2 8
 
// Motor 2
#define IN3 9
#define IN4 10
#define ENB 3

int pos_x;                   // declaring variable to stroe horizontal value
int pos_y; 

void Avancer ()
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

void Reculer ()
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

void Droite ()
{
 //sens moteur A
 digitalWrite (IN1, HIGH);
 digitalWrite (IN2, LOW);
 analogWrite (ENA, 0); //Vitesse moteur A
 //sens moteur B
 digitalWrite (IN3, LOW);
 digitalWrite (IN4, HIGH);
 analogWrite (ENB, 200); //Vitesse moteur B
}

void Gauche ()
{
 //Sens moteur A
 digitalWrite (IN1, LOW);
 digitalWrite (IN2, HIGH);
 analogWrite (ENA, 200); //Vitesse moteur A
 //sens moteur B
 digitalWrite (IN3, HIGH);
 digitalWrite (IN4, LOW);
 analogWrite (ENB, 0); //Vitesse motor B
}

void Arreter ()
{
 //Sens moteur A
 digitalWrite (IN1, LOW);
 digitalWrite (IN2, LOW);
 analogWrite (ENA, 0); //Vitesse moteur A
 //Sens moteur B
 digitalWrite (IN3, LOW);
 digitalWrite (IN4, LOW);
 analogWrite (ENB, 0); //Vitesse moteur B
}
 
void setup ()
{
 // on déclare les pins comme sorties
 pinMode (ENA, OUTPUT);
 pinMode (ENB, OUTPUT);
 pinMode (IN1, OUTPUT);
 pinMode (IN2, OUTPUT);
 pinMode (IN3, OUTPUT);
 pinMode (IN4, OUTPUT);
}

void loop ()
{
 pos_x = analogRead (joystick_x) ;  
 pos_y = analogRead (joystick_y) ;
 Serial.println(pos_x);

 if (pos_y > 700)
 {
     Avancer();
 }
 else if (pos_y < 300)
 {
     Reculer();
 }
 else if (pos_x > 700)
 {
     Gauche();
 }
 else if (pos_x < 300)
 {
     Droite();
 }
 else
 {
     Arreter();
 }
}
