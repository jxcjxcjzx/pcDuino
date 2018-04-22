int analogpin1 = A0;
int analogpin2 = A1;
int analogpin3 = A2;
int analogpin4 = A3;
int readinvalue1 = 0;
int readinvalue2 = 0;
int readinvalue3 = 0;
int readinvalue4 = 0;
int door = 30;
int forjudge1 = 0;
int forjudge2 = 0;
int forjudge3 = 0;
boolean toleft = false;
boolean toright = false;
boolean occupied = false;

// bizhang mokuai
 int distance=0;
 int inputPin=8; // 定义超声波信号接收接口
 int outputPin=9; // 定义超声波信号发出接口



void setup() {
  // declare the ledPin as an OUTPUT:
  pinMode(analogpin1, INPUT);  
  pinMode(analogpin2, INPUT);  
  pinMode(analogpin3, INPUT);  
  pinMode(analogpin4, INPUT);
 
 // bizhang mokuai 
  pinMode(inputPin, INPUT);
  pinMode(outputPin, OUTPUT);
 
 
  pinMode(12,OUTPUT);
  pinMode(11,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  readinvalue1 = analogRead(analogpin1);
  readinvalue2 = analogRead(analogpin2);
  readinvalue3 = analogRead(analogpin3);
  readinvalue4 = analogRead(analogpin4);   
  
  forjudge1 = (readinvalue1-readinvalue2)/door;
  forjudge2 = (readinvalue3-readinvalue1)/door; 
  forjudge3 = (readinvalue2-readinvalue4)/door;  
  
  Serial.println(forjudge1);
  Serial.println(forjudge2);
  Serial.println(forjudge3);
  
  if(forjudge1==0){
    toleft = false;
    toright = false;
  } 
  
  if(forjudge1<0&&forjudge2<0){
    turnleft();
    
    toleft=true;
    toright = false;
    
    resetright();
    occupied = true;
  }  
  
  if(forjudge1>0&&forjudge2>0){
    turnright();

    toright = true;
    toleft = false;

    resetleft();
    occupied = true;
  }  
  
  
  if(forjudge1>0&&forjudge2<0&&!occupied){
    if(toleft){
      turnleft();
      Serial.println("bug here");
      resetright();
    }
    if(toright){
      turnright();
      Serial.println("right turn");
      resetleft();
    }
    if(!toleft&&!toright){
    Serial.println("reset condition");  
    }
  }
  
  Serial.println(" ");
  delay(500);
  
  occupied = false;
  
  //bi zhang mokuai
  fashe();
  distance = pulseIn(inputPin, HIGH); // 读出脉冲时间
  distance= distance/58;   // 将脉冲时间转化为距离（单位：厘米）
  Serial.println(distance);   //输出距离值  
}
    
    
void turnleft()
{
   digitalWrite(12,HIGH);
   Serial.println("turn left");
}

void turnright()
{
  digitalWrite(11,HIGH);
  Serial.println("turn right");
}

void resetright()
{
  digitalWrite(11,LOW);
}

void resetleft()
{
  digitalWrite(12,LOW);
}



// bi zhang mokuai
 void fashe()
{
 digitalWrite(outputPin, LOW); // 使发出发出超声波信号接口低电平2μs
 delayMicroseconds(2);
 digitalWrite(outputPin, HIGH); // 使发出发出超声波信号接口高电平10μs，这里是至少10μs
 delayMicroseconds(10);
 digitalWrite(outputPin, LOW);    // 保持发出超声波信号接口低电平
}
