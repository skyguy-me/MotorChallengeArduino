//This motor shield use Pin 6,5,7,4 to control the motor
// Simply connect your motors to M1+,M1-,M2+,M2-
 
int EN1 = 6; 
int EN2 = 5;  //Roboduino Motor shield uses Pin 9
int IN1 = 7;
int IN2 = 4; //Latest version use pin 4 instead of pin 8
  
 
 
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
        
void setup()
{
    int i;
   // for(i=6;i<=9;i++) //For Roboduino Motor Shield
   // pinMode(i, OUTPUT);  //set pin 6,7,8,9 to output mode
 
    for(i=4;i<=7;i++)  //For Arduino Motor Shield
    pinMode(i, OUTPUT);  //set pin 4,5,6,7 to output mode
 
    Serial.begin(9600);  
}
 
 
void loop()
{
  int i = 0;
  while(i < 10){
      Motor1(255,true); 	
      Motor2(255,false);
      i++;
  }
  
  while(i< 0){
    Motor1(255,true); 	
     Motor2(255,true);
     i--;
    }
}


