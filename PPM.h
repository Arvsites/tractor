// Анализатор PWM - сигнала по выбранному пину
unsigned int getPPM(int pinnum) {
  int result = 0;
  int time = 0;
  while(digitalRead(pinnum) == 1);
  time = micros();
  while(digitalRead(pinnum) == 0);
  result = micros()-time;
  return result;
}
