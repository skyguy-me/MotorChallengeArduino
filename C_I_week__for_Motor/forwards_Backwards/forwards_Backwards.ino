#include <Servo.h>
#include <NewPing.h>

//This motor shield use Pin 6,5,7,4 to control the motor
// Simply connect your motors to M1+,M1-,M2+,M2-
 
int EN1 = 6; 
int EN2 = 5;  //Roboduino Motor shield uses Pin 9
int IN1 = 7;
int IN2 = 4; //Latest version use pin 4 instead of pin 8



Servo servo;

NewPing sonar(12,11,50);

float dist[3];

void scan (void){
  
  dist[0] = sonar.ping_cm();
  delay(500);
  
  
  servo.write(30);
  delay(500);
  dist[1] = sonar.ping_cm();
  delay(300);
  
 
  servo.write(150);
  delay(500);
  dist[2] = sonar.ping_cm();
  delay(300);
  
  servo.write(90);
}

int decide(void)
{
    int i, mx = 0,mxi =0;
    
    for (i=0;i<3;i++)
    {
      if(dist[i] >= mx) {
        mx = dist[i];
        mxi = i;
        }
    }
if (mx == 0) {
  return 10;
}

return mxi;
}

  
  
void Motor1(int pwm, boolean reverse)
        {
          analogWrite(EN1,pwm); //set pwm control, 0 for stop, and 255 for maximum speed
         if(reverse)
         {
          digitalWrite(IN1,HIGH);	
         }
        else
        {
          digitalWrite(IN1,LOW);	
         }
        } 
         
void Motor2(int pwm, boolean reverse)
        {
          analogWrite(EN2,pwm);
         if(reverse)
         {
          digitalWrite(IN2,HIGH);	
         }
        else
        {
          digitalWrite(IN2,LOW);	
         }
        } 
   
void turn(void){
   Motor1(160,true);
   Motor2(160,false);
   
} 

void turnR(void){
   Motor1(160,false);
   Motor2(160,false);
   
} 

void Stop(void)
{
   Motor1(0,true);
   Motor2(0,true); 
}
   
void setup()
{
    int i;
   // for(i=6;i<=9;i++) //For Roboduino Motor Shield
   // pinMode(i, OUTPUT);  //set pin 6,7,8,9 to output mode
 
    for(i=4;i<=7;i++)  //For Arduino Motor Shield
    pinMode(i, OUTPUT);  //set pin 4,5,6,7 to output mode
    servo.attach(10);
    Serial.begin(9600);  
  
    
    servo.write(90);
}
void returnHole(void)
{
  
} 
int moveTowardsHole(void){
  scan();
  for (int i = 0;i<3;i++)
  {    if(dist[i]<dist[i++]){
          return i;
          }  
  }
  
} 
 
void loop()
{ 
  
  scan();
  
 switch(decide()) {
   case 0:  Motor1(160,true);
      Motor2(160,true);
      delay(500);
      Stop();
      break;
      
     case 1: turnR();
      delay(500);
      Stop();
      break;
      
      case 2:  
      turn();
      delay(500);
      Stop();
      break;
      
      default:Motor1(160,true);
      Motor2(160,true);
      delay(500);
      Stop();
      break;
 } 
}


