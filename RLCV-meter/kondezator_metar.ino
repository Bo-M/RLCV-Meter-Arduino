#define analogPin      0          
#define chargePin      8         
#define dischargePin   10        
#define resistorValue  4700.0F   

unsigned long startTime;
unsigned long elapsedTime;
float microFarads;                
float nanoFarads;

void setup(){
  pinMode(chargePin, OUTPUT);     
  digitalWrite(chargePin, LOW);  
  Serial.begin(9600);             
}

void loop(){
  digitalWrite(chargePin, HIGH);  
  startTime = millis();
  while(analogRead(analogPin) < 648){       
  }

  elapsedTime= millis() - startTime;
  microFarads = ((float)elapsedTime / resistorValue) * 1000;   
  Serial.print(elapsedTime);       
  Serial.print(" mS    ");         

  if (microFarads > 1){
    Serial.print((long)microFarads);       
    Serial.println(" microFarads");         
  }

  else{
    nanoFarads = microFarads * 1000.0;      
    Serial.print((long)nanoFarads);         
    Serial.println(" nanoFarads");          
    delay(500); 
  }

  digitalWrite(chargePin, LOW);            
  pinMode(dischargePin, OUTPUT);            
  digitalWrite(dischargePin, LOW);          
  while(analogRead(analogPin) > 0){         
  }

  pinMode(dischargePin, INPUT);            
} 

