/*
  erster Versuch einer Alarmanlage für ein Fahrrad :-)
  */

int Alarm_out = D3;   // hier kann dann später die LED oder der Piezo als Alarmgeber angeschlossen werden
int Sensor = A0;      // hier wird der Sensor (Neigungssensor) angeschlossen. Vorerst mal ein Poti.
int sensorValue = 0;  // Startwert für Sensor

// the setup function runs once when you press reset or power the board
void setup() {
  pinMode(Alarm_out, OUTPUT);   // setzt D3 (Anschluss für Alarmausgang) als Ausgang
  pinMode(Sensor, INPUT);       // setzt A0 (Anschluss für Alarmsensor) als Eingang
  Serial.begin(115200);
  Serial.println ("Initialisierung ....");
 Serial.print (".");
 Serial.print (".");
 Serial.print (".");
 Serial.println (".");
 delay (1000);   // Verzögerung zum Start der Sensormessung
 Serial.println (" ... Initialisierung abgeschlossen");
 delay (1000);   // Verzögerung zum Start der Sensormessung
 
}

// the loop function runs over and over again forever
void loop() {  
  sensorValue = analogRead(Sensor);
  Serial.print ("Der aktuelle Sensorwert lautet ");
  Serial.println (sensorValue);
  
  // Abhängig vom Sensorwert kann nun etwas ausgeführt werden
  if (sensorValue > 100) { 
  Serial.println ("Wert ist grösser 100");
  Serial.println ("Jetzt wird Alarm ausgelöst");
  Serial.println ("");
  digitalWrite(Alarm_out, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(100);
  digitalWrite(Alarm_out, LOW);    // turn the LED off by making the voltage LOW
  delay(100);
  }
  else
  {
  Serial.println ("Wert ist kleiner 100");
  Serial.println ("keine Alarmauslösung");
  Serial.println ("");
  digitalWrite(Alarm_out, LOW);    // turn the LED off by making the voltage LOW
  }
  /*
  digitalWrite(Alarm_out, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(Alarm_out, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);    
  */   
  // wait for a second
}
