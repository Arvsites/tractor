#include "Config.h"
#include "PPM.h"
#include "MonsterMotor.h"
#include <Servo.h>

int pwmChannel_1;
int pwmChannel_3;
int pwmChannel_4;
Servo srvStop;

void setup() {
  Serial.begin(9600);
  pinMode(pinReceiverChannel_1, INPUT);
  pinMode(pinReceiverChannel_3, INPUT);
  pinMode(pinReceiverChannel_4, INPUT);

  pinMode(pinRelay, OUTPUT);
  digitalWrite(pinRelay, LOW);
  
  srvStop.attach(pinServo);
  srvStop.write(posServoStart);

  // --- подключаем и стопорим моторы руля и сцепления ---
  setupDrives();
}

void loop() {
  pwmChannel_1 = getPPM(pinReceiverChannel_1) / 10;
  pwmChannel_3 = getPPM(pinReceiverChannel_3) / 10;
  pwmChannel_4 = getPPM(pinReceiverChannel_4) / 10;

  // --- Управление стартером (реле) ---
  if(pwmChannel_4<ch4min+15) digitalWrite(pinRelay, HIGH); else digitalWrite(pinRelay, LOW);

  // --- Управление заслонкой-глушилкой (сервопривод) ---
  if(pwmChannel_4>ch4max-15) srvStop.write(posServoStop); else srvStop.write(posServoStart);

// --- Управление мотором рулевого привода ---
  Serial.println(pwmChannel_1);
  if(pwmChannel_1 <(ch1mid+3) && pwmChannel_1 > (ch1mid-3)) 
    motorOff(0);
  else if (pwmChannel_1<ch1mid)
    motorGo(0, CW,  map(pwmChannel_1, ch1mid, ch1min, 10, 255));
  else
    motorGo(0, CCW, map(pwmChannel_1, ch1mid, ch1max, 10, 255));

// --- Управление мотором привода сцепления ---
  if(pwmChannel_3 <(ch3mid+5) && pwmChannel_3 > (ch1mid-5)) 
    motorOff(1);
  else if (pwmChannel_3<ch3mid)
    motorGo(1, CW,  map(pwmChannel_3, ch3mid, ch3min, 10, 255));
  else
    motorGo(1, CCW, map(pwmChannel_3, ch3mid, ch3max, 10, 255));
}
