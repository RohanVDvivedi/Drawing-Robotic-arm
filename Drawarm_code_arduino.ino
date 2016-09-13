#include <Servo.h>
Servo shoulder;
Servo elbow;
Servo pen;

void setup()
{
   pen.attach(9);
   shoulder.attach(11);
   elbow.attach(10);
  Serial.begin(9600);
  // initializing servos and serial communication
}

// my serial communication function to grab the
//32 bit integer from SerialClass of my .cpp code
void send_serial_long(unsigned long i)
{
       
        unsigned char uc[4];
        uc[3]=i;
        i=i>>8;
        uc[2]=i;
        i=i>>8;
        uc[1]=i;
        i=i>>8;
        uc[0]=i;
        Serial.write(uc,4);
  }
        
        


unsigned long recieve_serial_long()
{
  unsigned long i=0;
  unsigned char uc;
  while(1)
  {
    if(Serial.available()==4)
    {
      uc=Serial.read();
      i=i+((unsigned long)uc)<<24;
      uc=Serial.read();
      i=i+(((unsigned long)uc)<<16);
      uc=Serial.read();
      i=i+(((unsigned long)uc)<<8);
      uc=Serial.read();
      i=i+(unsigned long)uc;
     
      
      break;
    }
  }
  return i;
}
// for more info on Serial class and the above 2 functions
//please refer to my github repository of Serial Class

unsigned int pen_new;
float s,e;

void loop()
{
  s=((float)(recieve_serial_long()))/10;
  send_serial_long((unsigned long)(s*10));
  e=((float)(recieve_serial_long()))/10;
  send_serial_long((unsigned long)(e*10));
  pen_new=((float)(recieve_serial_long()));
  send_serial_long((unsigned long)(pen_new));
 
 
 
 // send the acquired angles
 
   if(pen_new==1)
   {
     pen.write(90);
   }
   else if(pen_new==0)
   {
     pen.write(0);
   }
 
 
 shoulder.write(s);
 elbow.write(e);
 
}
