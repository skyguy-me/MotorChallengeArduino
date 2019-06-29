#include <Servo.h>
//#include <NewPing.h>

int EN1 = 6; 
int EN2 = 5;  //Roboduino Motor shield uses Pin 9
int IN1 = 7;
int IN2 = 4; //Latest version use pin 4 instead of pin 8

Servo servo;
NewPing sonar(13,12,90);

float dist[12];

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

void spin (float angle){
  float time;
  Motor1(180,false);
  Motor2(180,false);
  time = (angle/360.0) * 2700;
  delay(time); //need to figure out how to convert angle to time. current value is a placeholder 
  freeze();
}

void freeze (void) {
  Motor1(0,true);
  Motor2(0,true);
} 

float scan (void) {
  return sonar.ping_cm();
}

void mapSurroundings (void) {
  unsigned char i;
  
  for (i=0; i<12; i++){
    dist[i] = scan();
    delay(25);
    
    if(dist[i]==0){
      motorForward();
    }
    Serial.println(dist[i]);
    spin(30.0);
  }
}

float longestDist(void){
  int i;
  float mxi=0;
  float mx=0;
  for(i=0;i<12;i++){
    if(dist[i]> mx){
      mx = dist[i];
      mxi = i;}
      if(dist[i]== 0){
        return i;
      }
    
  }
  return mxi;
}

void motorForward(void) {
  Motor1(245,true);
  Motor2(255,false);
  delay(3500);
  freeze();
}
void setup() {
  int i;
  // for(i=6;i<=9;i++) //For Roboduino Motor Shield
  // pinMode(i, OUTPUT);  //set pin 6,7,8,9 to output mode
  for(i=4;i<=7;i++)  //For Arduino Motor Shield
  pinMode(i, OUTPUT);  //set pin 4,5,6,7 to output mode
  Serial.begin(9600);
  servo.attach(9);
  servo.write(90);//point the servo to center
  
}

void loop() {
 mapSurroundings();
 spin(longestDist()*30.0);
 motorForward();

}
