int sensorPin=A0; //initializing pins
int voltage=4;
int val=0;


void setup() {
  pinMode(voltage,OUTPUT);
  Serial.begin(9600);
  val=analogRead(sensorPin);//reading analog signal from nodeMCU
  
}
void loop() {
  
  Serial.println(val);
  while (val>0)
  {
    Serial.print("ON Loop val: ");
    Serial.println(val);
    digitalWrite(voltage,HIGH); //turning on output  when the values are greater than 0
    val=analogRead(sensorPin);
  }
    while(val<=0)
    {
    Serial.print("OFF Loop val: ");
    Serial.println(val);
    digitalWrite(voltage,LOW); //turning off the  output  when the values are less or equal  than 0
    val=analogRead(sensorPin);
    }
    
}
