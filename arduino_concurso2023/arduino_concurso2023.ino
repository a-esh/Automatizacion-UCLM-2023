#include <Servo.h>
Servo S_gripper;
Servo S_axis;

#include <NewPing.h>
#define TRIGGER_PIN 12
#define ECHO_PIN 11
#define MAX_DISTANCE 50
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

// Variables
int us_value = 0;
int ir_value = 0;
int us_blocker = 0;
int ir_blocker = 0;
const int ir = 6;
int time = 0;
int direction = 150;
int half = 1800;

void setup() {

  S_gripper.attach(8);
  S_axis.attach(13);
  pinMode(ir, INPUT);
  S_gripper.write(10);
  Serial.begin(9600);
}
//110 limite
void loop() {
  // Datos & Serial_Monitor
  ir_value = digitalRead(ir);
  Serial.print("ir_value = "); Serial.println(ir_value);

  us_value = sonar.ping_cm(); 
  Serial.print("us_value = "); Serial.print(us_value); Serial.println(" cm");


  // Program
  S_axis.write(direction);
  time = millis();
  if (us_value >= 7 and us_value <= 14 and us_blocker == 0) { // Block detection
    S_axis.write(90); 
    delay(0);
    S_gripper.write(111);
    delay(500);
    us_blocker = 1; 
    ir_blocker = 0; 
    direction = 30;
  }
  if (ir_value == 1 and ir_blocker == 0) { // Black line detection
    S_axis.write(90);
    S_gripper.write(10);
    delay(500);
    ir_blocker = 1;
    us_blocker = 0;
    direction = 150;
  }

}
