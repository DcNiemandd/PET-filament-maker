#include <AccelStepper.h>
#include "HCMotor.h"

//Definice hodnot, které se nahradí při buildu
#define HOT_END_PIN 6
#define HOT_POT A1
#define STEPPER_POT A0
#define STEPPER_MAX_SPEED 500
//Vytvoření instance motoru (jedná se o třídu - pokročilé programování, třídy mají vlastní proměnné, které si pamatují, a vlastní funkce/metody, které voláš s tečkou - heating.Init())
HCMotor heating = HCMotor();
// ^      ^          ^- jedná se o funkci, která vrátí instanci/proměnnou/objekt, nazývá se constructor
// |      ------------- název proměnné
// -------------------- typ proměnné - stejný název jako constructor
// !!! předtím to byl jiný zápis toho samého, jen jsem to rozepsal, aby bylo vidět, jak se změnilo následující
// možnosti zápisu volání constructoru:
// AccelStepper stepper1(1, 4, 2); // == direct call
// nebo
AccelStepper stepper1 = AccelStepper(1, 4, 2); // == assignment call

void setup()
{
  // Hot end inicializace
  heating.Init(); //prvotni nastaveni
  heating.attach(0, DCMOTOR, HOT_END_PIN); //ukládání hodnot do třídních proměnných viz. výše
  heating.DutyCycle(0, 100); // nastavení hodnot pro 0 V a max V. Kdyby jsi zde nastavil (0, 1024), tak to v loopu nemusíš mapovat
  
  // Navijak
  stepper1.setMaxSpeed(STEPPER_MAX_SPEED);
}
void loop()
{
  // Hot end
  int heat_power;
  heat_power = map(analogRead(POT_PIN), 0, 1024, 0, 100);
  // zde mohlo být i rovnou:
  // int Speed = map(...
  heating.OnTime(0, heat_power);

  // Navijak
  // stepper1.setSpeed((analogRead(STEPPER_POT))); // namapovat??? takhle využíváš jen polovinu potáku ((500/1024)*100) %
  int stepper_speed = map(analogRead(STEPPER_POT), 0, 1024, 0, STEPPER_MAX_SPEED); // tresnicka na dortu je přemístění čísla, které se opakuje do definů. tomu se říká magická konstanta, takhle to má název, který to popisuje
  stepper1.setSpeed(stepper_speed);
  stepper1.runSpeed();
}
