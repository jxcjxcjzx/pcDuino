int pinone = A0;
int duqu = 0;
int rotate = 0;
int duquback = 0;
long time = 0;
long pastime = 0;

void setup()
{
  pinMode(pinone,INPUT);
  Serial.begin(9600);
}    


void loop()
{

  time = millis();


  duqu = analogRead(pinone);
  /*
  Serial.println(duqu);
 */
  if(duqu>500&&(duqu/100-duquback/100)!=0){
  rotate++;
  }
   if(time-pastime>1000){
     Serial.println(rotate);
     pastime = time;
     rotate = 0;
   
  }
  
  duquback = duqu;

}
