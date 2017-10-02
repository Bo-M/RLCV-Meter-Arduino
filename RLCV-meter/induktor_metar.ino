//13 is the input to the circuit (connects to 150ohm resistor), 11 is the comparator/op-amp output.
//reibot.org for guide
double pulse, frequency, capacitance, inductance;
void setup(){
Serial.begin(115200);
pinMode(11, INPUT);
pinMode(13, OUTPUT);
Serial.println("Why hello!");
delay(200);
}
void loop(){
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
delay(20);
}
}
