#define BRAKEVCC 0                  // резкий тормоз
#define CW       1                  // вращение по часовой стрелке
#define CCW      2                  // вращение против часовой стрелки
#define BRAKEGND 3                  // остановка

const uint8_t inApin[2] = {7, 4};   // пины ключей мотора A
const uint8_t inBpin[2] = {8, 9};   // пины ключей мотора B
const uint8_t pwmpin[2] = {5, 6};   // пины ШИМ моторов (скорость)
const uint8_t cspin[2]  = {A2, A3}; // пины токов моторов
const uint8_t enpin[2]  = {A0, A1}; // пины состояния ключей AB. Ключи открываются, если притянуть к 0.

// --- Выключение мотора ---
void motorOff(int motor)            
{
  for (int i=0; i<2; i++)
  {
    digitalWrite(inApin[i], LOW);
    digitalWrite(inBpin[i], LOW);
  }
  analogWrite(pwmpin[motor], 0);
}


// --- Включение мотора ---
void motorGo(uint8_t motor, uint8_t direct, uint8_t pwm)  
{
// если номер мотора правильный:
  if (motor <= 1)
  {
// если направление совпадает со значениями направлений:
    if (direct <=3)
    {
// если направление мотора по часовой или плавный стоп,
// устанавливаем соответствующие значения ключа А выбранного мотора:
      if (direct <=1)
        digitalWrite(inApin[motor], HIGH);
      else
        digitalWrite(inApin[motor], LOW);

// если направление мотора по часовой или резкий стоп,
// устанавливаем соответствующие значения ключа B выбранного мотора:
      if ((direct==0)||(direct==2))
        digitalWrite(inBpin[motor], HIGH);
      else
        digitalWrite(inBpin[motor], LOW);
// устанавливаем ШИМ выбранного мотора
      analogWrite(pwmpin[motor], pwm);
    }
  }
}

// --- Настройка моторов ---
void setupDrives() {
  // переводим выводы управления в режим "выход"
  for (int i=0; i<2; i++)
  {
    pinMode(inApin[i], OUTPUT);     // выводы ключей A
    pinMode(inBpin[i], OUTPUT);     // выводы ключей B
    pinMode(pwmpin[i], OUTPUT);     // выводы ШИМ
  }
  // инициируем моторы выключенными
  motorOff(0);
  motorOff(1);
}
