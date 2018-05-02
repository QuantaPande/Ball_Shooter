#include <Wire.h>
#include <math.h>

#define Addr 0x1E               // 7-bit address of HMC5883 compass

#define motor1_A 22
#define motor1_B 23
#define motor2_A 24
#define motor2_B 25
#define motor3_A 26
#define motor3_B 27
#define motor4_A 28
#define motor4_B 29
#define motorR_1 30
#define motorR_2 31
#define motorL_1 32
#define motorL_2 33
#define motorLA1 34
#define motorLA2 35
#define motorS_1 36
#define motorS_2 37

#define motor1_pwm 8
#define motor2_pwm 9
#define motor3_pwm 10
#define motor4_pwm 11
#define motorR_pwm 4
#define motorL_pwm 5
#define motorS_pwm 6
#define motorLA_pwm 7

int pwm_ms_r = 0, pwm_ms_l = 0, i, x, y, z, time = 0;
char c[8];
double heading, elevation;
char dir;
String data;
/**********************************************************************************/


/**********************************Locomotion**************************************/
void reverse(int pwm)
{
  digitalWrite(motor1_A, 1);
  digitalWrite(motor1_B, 0);
  digitalWrite(motor2_A, 1);
  digitalWrite(motor2_B, 0);
  digitalWrite(motor3_A, 1);
  digitalWrite(motor3_B, 0);
  digitalWrite(motor4_A, 1);
  digitalWrite(motor4_B, 0);
  
  analogWrite(motor1_pwm, pwm);
  analogWrite(motor2_pwm, pwm);
  analogWrite(motor3_pwm, pwm);
  analogWrite(motor4_pwm, pwm);
}

void forward(int pwm)
{
  digitalWrite(motor1_A, 0);
  digitalWrite(motor1_B, 1);
  digitalWrite(motor2_A, 0);
  digitalWrite(motor2_B, 1);
  digitalWrite(motor3_A, 0);
  digitalWrite(motor3_B, 1);
  digitalWrite(motor4_A, 0);
  digitalWrite(motor4_B, 1);
  
  analogWrite(motor1_pwm, pwm);
  analogWrite(motor2_pwm, pwm);
  analogWrite(motor3_pwm, pwm);
  analogWrite(motor4_pwm, pwm);
}

void left(int pwm)
{
  digitalWrite(motor1_A, 0);
  digitalWrite(motor1_B, 1);
  digitalWrite(motor2_A, 0);
  digitalWrite(motor2_B, 1);
  digitalWrite(motor3_A, 1);
  digitalWrite(motor3_B, 0);
  digitalWrite(motor4_A, 1);
  digitalWrite(motor4_B, 0);
  
  analogWrite(motor1_pwm, pwm);
  analogWrite(motor2_pwm, pwm);
  analogWrite(motor3_pwm, pwm);
  analogWrite(motor4_pwm, pwm);
}

void right(int pwm)
{
  digitalWrite(motor1_A, 1);
  digitalWrite(motor1_B, 0);
  digitalWrite(motor2_A, 1);
  digitalWrite(motor2_B, 0);
  digitalWrite(motor3_A, 0);
  digitalWrite(motor3_B, 1);
  digitalWrite(motor4_A, 0);
  digitalWrite(motor4_B, 1);
  
  analogWrite(motor1_pwm, pwm);
  analogWrite(motor2_pwm, pwm);
  analogWrite(motor3_pwm, pwm);
  analogWrite(motor4_pwm, pwm);
}

void CW(int pwm)
{
  digitalWrite(motor1_A, 0);
  digitalWrite(motor1_B, 1);
  digitalWrite(motor2_A, 1);
  digitalWrite(motor2_B, 0);
  digitalWrite(motor3_A, 1);
  digitalWrite(motor3_B, 0);
  digitalWrite(motor4_A, 0);
  digitalWrite(motor4_B, 1);
  
  analogWrite(motor1_pwm, pwm);
  analogWrite(motor2_pwm, pwm);
  analogWrite(motor3_pwm, pwm);
  analogWrite(motor4_pwm, pwm);
}

void ACW(int pwm)
{
  digitalWrite(motor1_A, 1);
  digitalWrite(motor1_B, 0);
  digitalWrite(motor2_A, 0);
  digitalWrite(motor2_B, 1);
  digitalWrite(motor3_A, 0);
  digitalWrite(motor3_B, 1);
  digitalWrite(motor4_A, 1);
  digitalWrite(motor4_B, 0);
  
  analogWrite(motor1_pwm, pwm);
  analogWrite(motor2_pwm, pwm);
  analogWrite(motor3_pwm, pwm);
  analogWrite(motor4_pwm, pwm);
}

void loco_stop()
{
  digitalWrite(motor1_A, 0);
  digitalWrite(motor1_B, 0);
  digitalWrite(motor2_A, 0);
  digitalWrite(motor2_B, 0);
  digitalWrite(motor3_A, 0);
  digitalWrite(motor3_B, 0);
  digitalWrite(motor4_A, 0);
  digitalWrite(motor4_B, 0);
  
  analogWrite(motor1_pwm, 0);
  analogWrite(motor2_pwm, 0);
  analogWrite(motor3_pwm, 0);
  analogWrite(motor4_pwm, 0); 
}
/**********************************************************************************/


/********************************Shooter Mechanism*********************************/
void motor_shooter_start()
{
  digitalWrite(motorR_1, 1);
  digitalWrite(motorR_2, 0);
  digitalWrite(motorL_1, 1);
  digitalWrite(motorL_2, 0);
    
  analogWrite(motorR_pwm, pwm_ms_r);
  analogWrite(motorL_pwm, pwm_ms_l);
}

void motor_shooter_stop()
{
  digitalWrite(motorR_1, 0);
  digitalWrite(motorR_2, 0);
  digitalWrite(motorL_1, 0);
  digitalWrite(motorL_2, 0);
    
  analogWrite(motorR_pwm, 255);
  analogWrite(motorL_pwm, 255);
}

void motor_shooter_R()
{
  digitalWrite(motorR_1,1);
  digitalWrite(motorR_2,0);
  analogWrite(motorR_pwm,pwm_ms_r);
}
  
void motor_shooter_L()
{
  digitalWrite(motorL_1,1);
  digitalWrite(motorR_2,0);
  analogWrite(motorL_pwm,pwm_ms_l);
}

void shoot_start()
{
  digitalWrite(motorS_1,1);
  digitalWrite(motorS_2,0);
  analogWrite(motorS_pwm,0);
}

void shoot_stop()
{
  digitalWrite(motorS_1,0);
  digitalWrite(motorS_2,0);
  analogWrite(motorS_pwm,255);
}
/**********************************************************************************/


/*********************************Linear Actuator**********************************/
void lin_act(int dirA,int dirB,int pwm)
{
  digitalWrite(motorLA1,dirA);
  digitalWrite(motorLA2,dirB);
  analogWrite(motorLA_pwm,pwm);
}
/**********************************************************************************/


/***********************************Initialize*************************************/
void setup()
{
  Serial.begin(9600);
  Serial1.begin(9600);
  delay(1000);

  Wire.begin();
  
  Wire.beginTransmission(Addr); 
  Wire.write(byte(0x02));       //Mode register address
  Wire.write(byte(0x00));       // Set operating mode to continuous
  Wire.endTransmission();

  pinMode(motor1_A, OUTPUT);   //X dir motor 1
  pinMode(motor1_B, OUTPUT);   //X dir motor 1
  pinMode(motor2_A, OUTPUT);   //X dir motor 2
  pinMode(motor2_B, OUTPUT);   //X dir motor 2
  pinMode(motor3_A, OUTPUT);   //Y dir motor 1
  pinMode(motor3_B, OUTPUT);   //Y dir motor 1
  pinMode(motor4_A, OUTPUT);   //Y dir motor 2
  pinMode(motor4_B, OUTPUT);   //Y dir motor 2

  pinMode(motor1_pwm, OUTPUT); //X dir motor 1
  pinMode(motor2_pwm, OUTPUT); //X dir motor 2
  pinMode(motor3_pwm, OUTPUT); //Y dir motor 1
  pinMode(motor4_pwm, OUTPUT); //Y dir motor 2
  
  pinMode(motorLA1, OUTPUT);   //Linear Actuator 
  pinMode(motorLA2, OUTPUT);   //Linear Actuator 
  pinMode(motorR_1, OUTPUT);   //Shooter motor R
  pinMode(motorR_2, OUTPUT);   //Shooter motor R
  pinMode(motorL_1, OUTPUT);   //Shooter motor L
  pinMode(motorL_2, OUTPUT);   //Shooter motor L
  pinMode(motorS_1,OUTPUT);
  pinMode(motorS_2,OUTPUT);
  
  pinMode(motorLA_pwm, OUTPUT);//Linear Actuator PWM
  pinMode(motorR_pwm, OUTPUT); //Shooter motor R PWM
  pinMode(motorL_pwm, OUTPUT); //Shooter motor L PWM
  pinMode(motorS_pwm,OUTPUT);
  
  loco_stop();
  motor_shooter_stop();
  shoot_stop();
  lin_act(0,0,255);
  delay(1000);
}
/**********************************************************************************/


/**********************************************************************************/
void loop()
{
  if(Serial1.available() || dir != 0)
  {
    dir = Serial1.read();
    switch (dir)
    {
      case 'w':
        for (i = 0; i < 250; i++)
        {
          forward(i);
          i = i + 24;
          delay(100);
        }
        Serial.println(dir);
        break;

      case 's':
        for (i = 0; i < 250; i++)
        {
          reverse(i);
          i = i + 24;
          delay(100);
        }
        Serial.println(dir);
        break;

      case 'a':
        for (i = 0; i < 250; i++)
        {
          left(i);
          i = i + 24;
          delay(100);
        }
        Serial.println(dir);
        break;

      case 'd':
        for (i = 0; i < 250; i++)
        {
          right(i);
          i = i + 24;
          delay(100);
        }
        Serial.println(dir);
        break;
      
      case 'f':
        for (i = 0; i < 150; i++)
        {
          CW(i);
          i = i + 29;
          delay(100);
        }
        Serial.println(dir);
        break;
        
      case 'v':
        for (i = 0; i < 150; i++)
        {
          ACW(i);
          i = i + 29;
          delay(100);
        }
        Serial.println(dir);
        break;
        
      case 'x':
        Serial.println(dir);
        loco_stop();
        break;
      /******************************/  
      case 'i':
        motor_shooter_start();
        break;
        
      case 'o':
        motor_shooter_stop();
        break;
        
      case 'g':
        if (pwm_ms_l > 10)
        {
          pwm_ms_l -=10;
          motor_shooter_L();
        }
        break; 
      
      case 'h':
        if (pwm_ms_l < 240)
        {
          pwm_ms_l +=10;
          motor_shooter_L();
        }
        break;
         
      case 'b':
        if (pwm_ms_r > 10)
        {
          pwm_ms_r -=10;
          motor_shooter_R();
        }
        break;
        
      case 'n':
        if (pwm_ms_r < 240)
        {
          pwm_ms_r +=10;
          motor_shooter_R();
        }
        break;
        
      case 'j':
        shoot_start();
        break;
        
      case 'k':
        shoot_stop();
        break;
      /******************************/  
      case 'r':
        lin_act(1,0,0);
        Serial.println("y");
        break;
        
      case 'y':
        lin_act(0,1,0);
        Serial.println("y");
        break;
      
      case 't':
        lin_act(0,0,255);
        Serial.println("y");
        break;
      /******************************/
     }
  }

  // Initiate communications with hmc583l
  Wire.beginTransmission(Addr);
  Wire.write(byte(0x03));       // Send request to X MSB register
  Wire.endTransmission();

  Wire.requestFrom(Addr, 6);    // Request 6 bytes; 2 bytes per axis
  if(Wire.available() <=6)      // If 6 bytes available
  {    
    x = Wire.read() << 8 | Wire.read();
    z = Wire.read() << 8 | Wire.read();
    y = Wire.read() << 8 | Wire.read();
  }
  
  // Print raw values
//  Serial.print("X=");
//  Serial.print(x);
//  Serial.print(", Y=");
//  Serial.print(y);
//  Serial.print(", Z=");
//  Serial.println(z);
  heading = 0;
  elevation = 0;
  
  heading = atan2(y,x);
  elevation = atan2(z,y);
  
  if(heading<0)
  {
    heading += 2*M_PI;
  }
  
  if(elevation<0)
  {
    elevation += 2*M_PI;
  }
  
  //heading = heading*180/M_PI;
  if(time/20 > 1)
   {
     Serial1.print("Current Heading: ");
     Serial1.print(heading*180/M_PI);
     if(Serial.read() == "c")
     {
        sprintf(c, "%f", heading);
        Serial.write(c);
     }
     if(Serial.read() == 'm')
     {
        sprintf(c, "%f", elevation)
        Serial.write(c);
     }
     Serial1.print("\r\nCurrent Elevation:");
     Serial1.println(elevation*180/M_PI);
     //Serial1.println(data);
     time = 0;
   }
  delay(100);
  time++;
}
