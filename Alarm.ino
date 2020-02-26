/*
  erster Versuch einer Alarmanlage für ein Fahrrad :-)
  */

#define APP_VERSION "V0.02"
int Alarm_out = D3;       // hier kann dann später die LED oder der Piezo als Signalgeber angeschlossen werden
int Sensor = A0;          // hier wird der Sensor (Neigungssensor) angeschlossen. Vorerst mal ein Poti.
int sensorValue = 0;      // Startwert für Sensor auf 0 gesetzt
boolean Bewegung = 0;     // wenn Bewegung erkannt wird geht dieser Wert auf 1
boolean Zeit = 0;         // wenn Zeit abgelaufen ist geht dieser Wert auf 1
boolean Alarm = 0;        // wenn Alarm ausgelöst wird geht dieser Wert auf 1
int Zeitvorgabe = 3000;   // hier dann die Zeit in der eine Bewegung erkannt werden muss vorgewählt werden
int Alarmdauer = 4000;    // hier kann die Zeit angegeben werden wie lange der Alarm mindestens dauert (auch wenn keine Bewegung mehr erkannt wird)


// the setup function runs once when you press reset or power the board
void setup() {
   Serial.begin(115200);
  pinMode(Alarm_out, OUTPUT);   // setzt D3 (Anschluss für Alarmausgang) als Ausgang
  pinMode(Sensor, INPUT);       // setzt A0 (Anschluss für Alarmsensor) als Eingang
  delay(1000);                  // Verzögerung zum Start der Sensormessung 
  Serial.println();
  Serial.println();
  Serial.print("Starting Sensor :");
  Serial.println(APP_VERSION);
  delay(1000);  
 Serial.print ("...");
 delay (1000);                 // Verzögerung zum Start der Sensormessung
 Serial.println (" ... Initialisierung abgeschlossen");
 delay (1000);                 // Verzögerung zum Start der Sensormessung 
}

// the loop function runs over and over again forever
void loop() {  
  delay (1000);
  static unsigned long last = 0;
  sensorValue = analogRead(Sensor);
  Serial.print ("Der aktuelle Sensorwert lautet ");
  Serial.println (sensorValue);
  
  // *************************************************  Abhängig vom Sensorwert kann nun etwas ausgeführt werden
  if (sensorValue > 100) { 
  Bewegung = 1;
  Serial.println ("Wert ist grösser 100");
  Serial.print ("Bewegung erkannt = ");
  Serial.println (Bewegung);
   Serial.print ("Zeitdauer erreicht = ");
  Serial.println (Zeit);
  Serial.println (" ");
  }
  else
  {
  Bewegung = 0;
  Zeit = 0;
  last = millis();
  Serial.println ("Wert ist kleiner 100");
  Serial.print ("Bewegung erkannt =");
  Serial.println (Bewegung);
  Serial.print ("Zeitdauer erreicht = ");
  Serial.println (Zeit);
  Serial.println (" ");
   }
// ******************************************************************************** 
// **************************************************   Messung der Zeit ab Bewegung   
  if ( (millis() - last) > Zeitvorgabe) {
  Zeit = 1;
  }
  // ******************************************************************************
  delay (1000);

// Alarm aktivieren ***************************************************************
if (Bewegung > 0 && Zeit > 0)
{
  Alarm = 1;
  digitalWrite(Alarm_out, Alarm);  
  Serial.print ("Alarm = " );
  Serial.println (Alarm);
  delay (Alarmdauer);
}
else
{
  Alarm = 0;
  digitalWrite(Alarm_out, Alarm);   
  Serial.print ("Alarm = " );
  Serial.println (Alarm);
}
// ********************************************************************************

}
