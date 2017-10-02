//Analog pin1 je voltage divider
//Analog pin1 je capatince




#include <LCD.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>


#define I2C_ADDR    0x3F // <<----- Add your address here.  Find it from I2C Scanner
#define BACKLIGHT_PIN     3
#define En_pin  2
#define Rw_pin  1
#define Rs_pin  0
#define D4_pin  4
#define D5_pin  5
#define D6_pin  6
#define D7_pin  7




#define analogPin0      0          
#define chargePin      8         
#define dischargePin   10        
float resistorValue=4700.0;

unsigned long startTime;
unsigned long elapsedTime;
float microFarads;                
float nanoFarads;


double pulse, frequency, capacitance, inductance;

int analogPin= 1;
int raw= 0;
int Vin= 5;
float Vout= 0;
float R1= 1000;
float R2= 0;
float buffer= 0;




const int button4 = 4; //Vol+
const int button5 = 5; //Switch
const int button6 = 6; //Vol-
const int button2 = 2;
const int button3 = 3;
const int button7 = 7;
const int button9 = 9;
const int button12 = 12;


float vout = 0.0;
float vin = 0.0;
float R1v = 100000.0; // resistance of R1 (100K) -see text!
float R2v = 10000.0; // resistance of R2 (10K) - see text!
int value = 0;



LiquidCrystal_I2C  lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin); 




void setup()
{
  pinMode(11, INPUT);
  pinMode(13, OUTPUT);
  pinMode(chargePin, OUTPUT);     
  digitalWrite(chargePin, LOW);  
   pinMode(button2, INPUT);
  pinMode(button3, INPUT);
  pinMode(button4, INPUT);
  pinMode(button5, INPUT);
  pinMode(button6, INPUT);
  pinMode(button7, INPUT);
  pinMode(button12, INPUT);
  pinMode(A3, INPUT);
  pinMode(A6, INPUT);
lcd.begin (16,2); //  <<----- My LCD was 16x2
// Switch on the backlight
lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
lcd.setBacklight(HIGH);
lcd.home (); // go home
  Serial.begin(9600);
}

void loop(){
   if (digitalRead(button5) == HIGH){
    R1=150;
    resistorfunction();
Serial.println(R1);}

  if (digitalRead(button6) == HIGH){
    R1=998;
    resistorfunction();
  Serial.println(R1);}

  
   if (digitalRead(button7) == HIGH){
    R1=99800;
    resistorfunction();
  Serial.println(R1);}

  
if (digitalRead(button12) == HIGH){
    R1=996000;
    resistorfunction();
    Serial.println(R1);}

//////////////////capatince
 if (digitalRead(button2) == HIGH){
    resistorValue=10000;
    capatincefunction();
  Serial.println(resistorValue);}
  
 if (digitalRead(button3) == HIGH){
  resistorValue=21200000;
  capatincefunction();
Serial.println(resistorValue);}

  if (digitalRead(button4) == HIGH){
    resistorValue=995000;
    capatincefunction();
  Serial.println(resistorValue);}
  
 if (digitalRead(A3) == HIGH){
    resistorValue=4650;
    capatincefunction();
  Serial.println(resistorValue);}
///////////////////////inductance
  if (digitalRead(button9) == HIGH){
    inductancefunction();
 // Serial.println(resistorValue);}
}
///////////////////////////voltage
if (digitalRead(A2) == HIGH){
voltagefunction();
//  Serial.println("A2");}
  



}
}









void capatincefunction() {
digitalWrite(chargePin, HIGH);  
  startTime = millis();
  while(analogRead(analogPin0) < 648){       
  }

  elapsedTime= millis() - startTime;
  microFarads = ((float)elapsedTime / resistorValue) * 1000;   
  Serial.print(elapsedTime);       
  Serial.print(" mS    ");         

  if (microFarads > 1){
    Serial.print((long)microFarads);       
    Serial.println(" microFarads");  
     lcd.setCursor(0, 1);
 lcd.print("        ");       
    lcd.setCursor(0, 1);
 lcd.print(microFarads); 
 delay(500);


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
  while(analogRead(analogPin0) > 0){         
  }
  
  pinMode(dischargePin, INPUT);      
}



void inductancefunction(){
digitalWrite(13, HIGH);
delay(5);//give some time to charge inductor.
digitalWrite(13,LOW);
delayMicroseconds(100); //make sure resination is measured
pulse = pulseIn(11,HIGH,5000);//returns 0 if timeout
if(pulse > 0.1){ //if a timeout did not occur and it took a reading:
capacitance = 2.E-6; //insert capacitance here. Currently using 2uF
frequency = 1.E6/(2*pulse);
inductance = 1./(capacitance*frequency*frequency*4.*3.14159*3.14159);//one of my profs told me just do squares like this
inductance *= 1E6; //note that this is the same as saying inductance = inductance*1E6
Serial.print("High for uS:");
Serial.print( pulse );
Serial.print("\tfrequency Hz:");
Serial.print( frequency );
Serial.print("\tinductance uH:");
Serial.println( inductance );
 lcd.setCursor(8, 0);
 lcd.print("        ");
lcd.setCursor(8, 0);
 lcd.print(inductance); 
 delay(500);


delay(20);
}}
void resistorfunction() {

raw= analogRead(analogPin);
if(raw) 
{
buffer= raw * Vin;
Vout= (buffer)/1024.0;
buffer= (Vin/Vout) -1;
R2= R1 * buffer;
Serial.print("Vout: ");
Serial.println(Vout);
Serial.print("R2: ");
Serial.println(R2);
 lcd.setCursor(0, 0);
 lcd.print("        ");
lcd.setCursor(0, 0);
 lcd.print(R2); 
 delay(500);


delay(1000);
}
  }




void voltagefunction() {
   // read the value at analog input
   value = analogRead(A6);
   vout = (value * 5.3) / 1024.0; // see text
   vin = vout / (R2v/(R1v+R2v)); 
   if (vin<0.09) {
   vin=0.0;//statement to quash undesired reading !
}
Serial.println(vin);
delay(500);
lcd.setCursor(8, 1);
 lcd.print("        ");
lcd.setCursor(8, 1);
 lcd.print(vin); 
 delay(500);


}
