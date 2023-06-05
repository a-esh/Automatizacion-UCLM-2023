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
int ir_blocker = 1;
const int ir = 6;
int direction_s = 0;
int horario = 180;
int a_horario = 0 ;
int time_ir = 0;
int time_ir_1 = 0;

void setup() {
  S_gripper.attach(8);
  S_axis.attach(13);
  pinMode(ir, INPUT);
  S_gripper.write(50);
  Serial.begin(9600);
  direction_s = a_horario;
}

void loop() {
  // Data & Serial_Monitor
  ir_value = digitalRead(ir);
  Serial.print("ir_value = ");
  Serial.println(ir_value);

  us_value = sonar.ping_cm();
  Serial.print("us_value = ");
  Serial.print(us_value);
  Serial.println(" cm");

  
  // Program
  S_axis.write(direction_s);
  if (us_value >= 1 and us_value <= 4  and us_blocker == 0) {  // Block detection
    S_axis.write(180);
    delay(50);
    S_axis.write(90);

    S_gripper.write(107);
    delay(200);
    us_blocker = 1;
    ir_blocker = 0;
    direction_s = horario;
  }

  time_ir = millis() - time_ir_1;
  if (ir_value == 1 and ir_blocker == 0 and time_ir > 200) {  // Black line detection
    S_gripper.write(107);

    S_axis.write(0);
    delay(50);
    S_axis.write(90);

    delay(200);
    S_gripper.write(50);
    ir_blocker = 1;
    us_blocker = 0;
    direction_s = a_horario;
    delay(9800);
    S_axis.write(direction_s);
    time_ir_1 = millis();
  }
}
