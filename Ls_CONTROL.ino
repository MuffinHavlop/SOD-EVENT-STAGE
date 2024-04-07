#include <PS2X_lib.h>
#include <Adafruit_PWMServoDriver.h>
#include <Wire.h>

#define PS2_DAT 12
#define PS2_CMD 13
#define PS2_CLK 14
#define PS2_ATT 15

#define PWM_DC1A 14
#define PWM_DC1B 15
#define PWM_DC4A 12
#define PWM_DC4B 13

#define PWM_DC2A 8
#define PWM_DC2B 9
#define PWM_DC3A 10
#define PWM_DC3B 11

#define MOT_LEFT 1
#define MOT_RIGHT 2

#define SPD_FAST 2047
#define SPD_MAX 4095
#define SPD_MED 1024

#define SPD_INTAKE 100 
#define SPD_WHEEL 90

bool motorState1 = false;
bool motorState2 = false;
bool motorState3 = false;
bool motorState4 = false;

Adafruit_PWMServoDriver pwm; 
PS2X myPS2;

void setup()
{                         
    Serial.begin(115200); 

    Serial.println("Mastodon's BanhMi Connected To PC. Proceeding to connect PS2 Controller");

    while (myPS2.config_gamepad(PS2_CLK, PS2_CMD, PS2_ATT, PS2_DAT) != 0)
    {
        Serial.println("Err: PS2 Controller Not Connected");
        delay(500);
    } 

    Serial.println("Controller works normally");

    pwm.begin();                          
    pwm.setOscillatorFrequency(27000000); 
    pwm.setPWMFreq(50);                   
}

void ctrl_dc(uint8_t motor, int16_t speed)
{
    switch (motor)
    {
    case 1:                                                 
        pwm.setPWM(PWM_DC1A, 0, ((speed > 0) ? speed : 0)); 
        pwm.setPWM(PWM_DC1B, 0, ((speed < 0) ? (-speed) : 0));
        break;
    case 2: 
        pwm.setPWM(PWM_DC2A, 0, ((speed > 0) ? speed : 0));
        pwm.setPWM(PWM_DC2B, 0, ((speed < 0) ? (-speed) : 0));
        break;
    case 3: // Cho bánh bên tay phải
        pwm.setPWM(PWM_DC3A, 0, ((speed > 0) ? speed : 0));
        pwm.setPWM(PWM_DC3B, 0, ((speed < 0) ? (-speed) : 0));
        break;
    case 4:
        pwm.setPWM(PWM_DC4A, 0, ((speed > 0) ? speed : 0));
        pwm.setPWM(PWM_DC4B, 0, ((speed < 0) ? (-speed) : 0));
        break;
    }
}


void loop()
{
    myPS2.read_gamepad(); // Read controller button states

  if (myPS2.ButtonPressed(PSB_R1)) { // Check if PS2 Select button is pressed
    motorState1 = !motorState1;
    if (motorState1 == true){
      ctrl_dc(MOT_LEFT, (true) ? SPD_MED : SPD_MED);
    }
    else{
      ctrl_dc(MOT_LEFT, (true) ? 0 : 0);
    }
  }

  if (myPS2.ButtonPressed(PSB_L1)) { // Check if PS2 Select button is pressed
    motorState2 = !motorState2;
    if (motorState2 == true){
      ctrl_dc(MOT_RIGHT, (true) ? SPD_MED : SPD_MED);
    }
    else{
      ctrl_dc(MOT_RIGHT, (true) ? 0 : 0);
    }
  }

  if (myPS2.ButtonPressed(PSB_L2)) { // Check if PS2 Select button is pressed
    motorState3 = !motorState3;
    if (motorState3 == true){
      ctrl_dc(MOT_RIGHT, (true) ? -SPD_MED : -SPD_MED);
    }
    else{
      ctrl_dc(MOT_RIGHT, (true) ? 0 : 0);
    }
  }
  if (myPS2.ButtonPressed(PSB_R2)) { // Check if PS2 Select button is pressed
    motorState4 = !motorState4;
    if (motorState4 == true){
      ctrl_dc(MOT_LEFT, (true) ? -SPD_MED : -SPD_MED);
    }
    else{
      ctrl_dc(MOT_LEFT, (true) ? 0 : 0);
    }
  }
}
