#include <Wire.h>
#include <AFMotor.h>

AF_DCMotor motor_lf(2);
AF_DCMotor motor_rf(1);
AF_DCMotor motor_lb(3);
AF_DCMotor motor_rb(4);

int direction_lf = RELEASE;
int direction_rf = RELEASE;
int direction_lb = RELEASE;
int direction_rb = RELEASE;

int wheel_speed = 250;

#define COMMANDS_NUM 7

char* commands[COMMANDS_NUM] = {
  "move_forward",
  "move_backward",
  "rotate_left",
  "rotate_right",
  "shift_left",
  "shift_right",
  "stop"
};

int directions[COMMANDS_NUM][4] = {
  {FORWARD, FORWARD, FORWARD, FORWARD},
  {BACKWARD, BACKWARD, BACKWARD, BACKWARD},
  {BACKWARD, FORWARD, BACKWARD, FORWARD},
  {FORWARD, BACKWARD, FORWARD, BACKWARD},
  {BACKWARD, FORWARD, FORWARD, BACKWARD},
  {FORWARD, BACKWARD, BACKWARD, FORWARD},
  {RELEASE, RELEASE, RELEASE, RELEASE}
};

void handleMoveCommand(char* command) {
  for (int i = 0; i < COMMANDS_NUM; ++i) {
    if (strcmp(command, commands[i]) == 0) {
      direction_lf = directions[i][0];
      direction_rf = directions[i][1];
      direction_lb = directions[i][2];
      direction_rb = directions[i][3];
      return;
    }
  }

  direction_lf = RELEASE;
  direction_rf = RELEASE;
  direction_lb = RELEASE;
  direction_rb = RELEASE;
}

void onReceiveEventHandler(int len) {
  char buffer[len+1] = {0};

  for (int i = 0; i < len; ++i) {
    buffer[i] = Wire.read();
  }

  Serial.print("Got from ESP: ");
  Serial.println(buffer);

  handleMoveCommand(buffer);
}

void onRequestEventHandler() {
  Wire.write("Hello NodeMCU");
}

void setup() {
  Wire.begin(8);

  Wire.onReceive(onReceiveEventHandler);
  Wire.onRequest(onRequestEventHandler);

  Serial.begin(9600);

  motor_rf.setSpeed(wheel_speed);
  motor_lf.setSpeed(wheel_speed);
  motor_rb.setSpeed(wheel_speed);
  motor_lb.setSpeed(wheel_speed);
}

void loop() {
  motor_lf.run(direction_lf);
  motor_rf.run(direction_rf);
  motor_lb.run(direction_lb);
  motor_rb.run(direction_rb);

  delay(50);
}
