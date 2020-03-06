/*
  erster Versuch einer Alarmanlage für ein Fahrrad :-)
  V0.02
  V0.03 Alarm-LED changed to internal LED (inverted)
  V0.04 Changed Poti to MPU6050 https://github.com/jrowberg/i2cdevlib
  V0.05 Y- and Z-Values added

  */

// #define Showallvalues                             //shows values of MPU6050
#define APP_VERSION "V0.05"
#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"

// ************************************* diese Werte können angepasst werden ********************************************
int Zeitvorgabe = 3000;   // hier dann die Zeit in der eine Bewegung erkannt werden muss vorgewählt werden
int Alarmdauer = 4000;    // hier kann die Zeit angegeben werden wie lange der Alarm mindestens dauert (auch wenn keine Bewegung mehr erkannt wird)
// *********************************************************************************************************************  

int16_t ax, ay, az;
int16_t gx, gy, gz;
int Accel_x = 0;
int StartAccel_x = 0;
int DiffAccel_x = 0;
int Accel_y = 0;
int StartAccel_y = 0;
int DiffAccel_y = 0;
int Accel_z = 0;
int StartAccel_z = 0;
int DiffAccel_z = 0;

unsigned long zeit;
static unsigned long last = 0;

int Alarm_out = D7;                       // hier kann dann später die LED oder der Piezo als Signalgeber angeschlossen werden
boolean Bewegung = 0;                              // wenn Bewegung erkannt wird geht dieser Wert auf 1
boolean Zeit = 0;                                  // wenn Zeit abgelaufen ist geht dieser Wert auf 1
boolean Alarm = 0;                                 // wenn Alarm ausgelöst wird geht dieser Wert auf 1

 MPU6050 accelgyro;

                                                   // the setup function runs once when you press reset or power the board
void setup() {
  Wire.begin(D3, D4);
  Serial.begin(38400);
  pinMode(Alarm_out, OUTPUT);                      // setzt D3 (Anschluss für Alarmausgang) als Ausgang
  delay(1000);                                     // Verzögerung zum Start der Sensormessung 
  Serial.println();
  Serial.println();
  Serial.print("Starting Sensor :");
  Serial.println(APP_VERSION);
  delay(1000);  
  Serial.print ("...");    
  Serial.println("Initializing I2C devices...");
  accelgyro.initialize();                          // initialize device   
  Serial.println("Testing device connections...");
  Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");    // verify connection
  delay (1000);
}

                                                   // the loop function runs over and over again forever
void loop() { 
   
     accelgyro.getAcceleration(&ax, &ay, &az);
    // accelgyro.getRotation(&gx, &gy, &gz);

  #ifdef Showallvalues
     Serial.print(ax); Serial.print("\t");
     Serial.print(ay); Serial.print("\t");
     Serial.println(az); Serial.print("\t");    
    // Serial.print(gx); Serial.print("\t");
    // Serial.print(gy); Serial.print("\t");
    // Serial.println(gz);
  #endif

    Serial.print ("Zeit: ");
    zeit = millis();
    Serial.println(zeit);
    delay(1000);

  if (zeit < 8000) {                                  // setting actual values of MPU6050 as StartAccel 8 sec after power on
  //  Serial.print ("Startphase ");
  //  Serial.print(zeit); Serial.print("\t");
    StartAccel_x = ax;
    Serial.print("StartAccel X= "); 
    Serial.print(StartAccel_x); Serial.print("\t");
    Serial.print ("ActualAccel X= ");
    Serial.print(ax); Serial.print("\t");

    StartAccel_y = ay;
    Serial.print("StartAccel Y= "); 
    Serial.print(StartAccel_y); Serial.print("\t");
    Serial.print ("ActualAccel Y= ");
    Serial.print(ay); Serial.print("\t");

    StartAccel_z = az;
    Serial.print("StartAccel Z= "); 
    Serial.print(StartAccel_z); Serial.print("\t");
    Serial.print ("ActualAccel Z= ");
    Serial.print(az); Serial.print("\t");
  }

  Accel_x = ax;
  DiffAccel_x = Accel_x - StartAccel_x;               // calculating difference between Start and Actual Accel
  Serial.print ("Differenz X = ");
  Serial.println (DiffAccel_x);

   Accel_y = ay;
  DiffAccel_y = Accel_y - StartAccel_y;               // calculating difference between Start and Actual Accel
  Serial.print ("Differenz Y = ");
  Serial.println (DiffAccel_y);

   Accel_z = az;
  DiffAccel_z = Accel_z - StartAccel_z;               // calculating difference between Start and Actual Accel
  Serial.print ("Differenz Z = ");
  Serial.println (DiffAccel_z);
  delay(1000);
  
   if ((abs(DiffAccel_x) > 400)||(abs(DiffAccel_y) > 400)||(abs(DiffAccel_z) > 400)) { 
    Bewegung = 1;
    Serial.print ("Bewegung erkannt = ");
    Serial.print (Bewegung); Serial.print("\t");
    Serial.print ("Zeitdauer erreicht = ");
    Serial.print (Zeit); Serial.print("\t");
   }
  else
  {
    Bewegung = 0;
    Zeit = 0;
    last = millis();
    Serial.print ("Bewegung erkannt =");
    Serial.print (Bewegung); Serial.print("\t");
    Serial.print ("Zeitdauer erreicht = ");
    Serial.print (Zeit); Serial.print("\t");
   }
   
// **************************************************   Messung der Zeit ab Bewegung   
  
  if ((millis() - last) > Zeitvorgabe) {               // if movement is longer than Zeitvorgabe set Zeit = 1
  Zeit = 1;
  }
  
  // ******************************************************************************
 

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


}
