
#include <NewPing.h>   // include the NewPing library for this program

#include <Servo.h>

Servo myservo; //create servo object to control a servo

#define VCC_PIN 13
#define TRIGGER_PIN 12 // sonar trigger pin will be attached to Arduino pin 12
#define ECHO_PIN 11 // sonar echo pint will be attached to Arduino pin 11
#define GROUND_PIN 10

#define MAX_DISTANCE 200 // fmaximum distance set to 200 cm

#define OPEN 90 //angle at which claw is open
#define CLOSE 130 //angle at which claw is closed

#define THRES 7 //distance set for ground detection - letting claw close

#define del 150 // delay in ms

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // initialize NewPing

void printMes(int);

void setup() //do the following things once
{

  Serial.begin(9600);  // set data transmission rate to communicate with computer
  pinMode(ECHO_PIN, INPUT) ;  
  pinMode(TRIGGER_PIN, OUTPUT) ;
  pinMode(GROUND_PIN, OUTPUT);  // tell pin 10 it is going to be an output
  pinMode(VCC_PIN, OUTPUT);  // tell pin 13 it is going to be an output
  digitalWrite(GROUND_PIN,LOW); // tell pin 10 to output LOW (OV, or ground)
  digitalWrite(VCC_PIN, HIGH) ; // tell pin 13 to output HIGH (+5V)

  Serial. begin(9600); //set data transmission rate to communicate with computer

  pinMode(8,INPUT_PULLUP); //pin 8 forced to HIGH when there is no external input

  myservo.attach(9); //attaches the servo on pin 9 to the servo object

  myservo.write(OPEN); //tells servo to go to 60 degree position
  Serial.print("Claw is OPEN\n");
}


void loop() // do the following things forever
{ 
  int DISTANCE_IN_CM;

    do{
      DISTANCE_IN_CM = sonar.ping_cm();
      printMes(DISTANCE_IN_CM);
      delay(del);
    }while(DISTANCE_IN_CM > THRES || DISTANCE_IN_CM == 0); // added 0 as a test point because the sonar sometimes falsely returns 0 (we can ignore it)

    delay(1000);
    myservo.write(CLOSE); //claw senses ground so closes
    Serial.print("Claw is CLOSED\n");

    do{
      DISTANCE_IN_CM = sonar.ping_cm();
      printMes(DISTANCE_IN_CM);
      delay(del);
    }while(DISTANCE_IN_CM <= THRES);

    do{
      DISTANCE_IN_CM = sonar.ping_cm();
      printMes(DISTANCE_IN_CM);
      delay(del);
    }while(DISTANCE_IN_CM > THRES || DISTANCE_IN_CM == 0);

    myservo.write(OPEN); //claw senses ground second time so opens
    Serial.print("Claw is OPEN\n");

    do{
      DISTANCE_IN_CM = sonar.ping_cm();
      printMes(DISTANCE_IN_CM);
      delay(del);
    }while(DISTANCE_IN_CM <= THRES);
 }

// prints a message on the Serial for testing purposes
void printMes(int distance){
  
  Serial.print("Ping: "); //print “Ping:" on the computer display
  Serial.print(distance); //print the value of the variable next
  Serial.println("cm"); //print "cm" after that, then go to next line
}
