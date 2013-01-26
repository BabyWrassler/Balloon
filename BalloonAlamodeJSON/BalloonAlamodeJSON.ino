#include <SPI.h>
#include <SoftwareSerial.h>

SoftwareSerial xBeeSerial =  SoftwareSerial(10, 11);
String response; // Used for debugging to print the chars to the Serial Monitor
int responseValue = 0;
char charIn;

unsigned long timestamp;
long latitude;
long longitude;
long altitude;
int gxaxis;
int gyaxis;
int gzaxis;
int axaxis;
int ayaxis;
int azaxis;
int mxaxis;
int myaxis;
int mzaxis;
int pressure;

void setup() {
  xBeeSerial.begin(9600);
  delay(100);
  xBeeSerial.flush();
  delay(100);
  Serial.begin(9600);
  delay(100); 
  Serial.flush();
  delay(100);
  randomSeed(analogRead(0)); // For random sensor values to test serial communication and web display
  Serial.println("Setup completed.");
}

void loop()
{
  if(xBeeSerial.available()){  //is there anything to read?
    delay(100); // Wait for all the data to come in
    while(xBeeSerial.available()) {
      charIn = xBeeSerial.read(); // read a char from the buffer
      if (charIn == '\n') {
        //Serial.println("Received: \"" + response + "\"");
        decodeCommand();
      } else {
        if( isDigit(charIn) )// is this an ascii digit between 0 and 9?
        {
          responseValue = (responseValue * 10) + (charIn - '0'); // yes, accumulate the value
        }
        //response += charIn; // append that char to the string response
        Serial.print(charIn);
      }
    }
  }
}

void decodeCommand()
{
      if (responseValue == 0)
      {  
        Serial.println("Command Zero Received.");
        // Do something fancy, like reboot the system
      }
      else if (0 < responseValue < 101) // Set a realistic limit
      {
        Serial.print("Response Value: ");
        Serial.println(responseValue);

        xBeeSerial.print("[ ");
        xBeeSerial.print(responseValue);
        //xBeeSerial.print(",");
        for (int d = responseValue; d > 0; d--) {
          readSensors(); // just for testing, this will be SD card code later
          //Serial.println(timestamp);
          xBeeSerial.print(", { \"timestamp\":");
          xBeeSerial.print(timestamp);
          xBeeSerial.print(", \"latitude\":");
          xBeeSerial.print(latitude);
          xBeeSerial.print(", \"longitude\":");
          xBeeSerial.print(longitude);
          xBeeSerial.print(", \"altitude\":");
          xBeeSerial.print(altitude);
          xBeeSerial.print(", \"gxaxis\":");
          xBeeSerial.print(gxaxis);
          xBeeSerial.print(", \"gyaxis\":");
          xBeeSerial.print(gyaxis);
          xBeeSerial.print(", \"gzaxis\":");
          xBeeSerial.print(gzaxis);
          xBeeSerial.print(", \"axaxis\":");
          xBeeSerial.print(axaxis);
          xBeeSerial.print(", \"ayaxis\":");
          xBeeSerial.print(ayaxis);
          xBeeSerial.print(", \"azaxis\":");
          xBeeSerial.print(azaxis);
          xBeeSerial.print(", \"mxaxis\":");
          xBeeSerial.print(mxaxis);
          xBeeSerial.print(", \"myaxis\":");
          xBeeSerial.print(myaxis);
          xBeeSerial.print(", \"mzaxis\":");
          xBeeSerial.print(mzaxis);
          xBeeSerial.print(", \"pressure\":");
          xBeeSerial.print(pressure);
          xBeeSerial.print("}");
        }
        xBeeSerial.print(" ]");
        xBeeSerial.print("\n");
        Serial.println("The data has been sent.");

      }      
      else
      {
        Serial.println("Could not match command received.");
      }
      response = "";
      responseValue = 0;
}

void readSensors()
{
  // Keep in mind, Python's JSON does NOT like leading zeros
  timestamp = millis();
  latitude = random(300000,400000);
  longitude = random(700000,800000);
  altitude = random(0,60000);
  gxaxis = random(0,300);
  gyaxis = random(0,300);
  gzaxis = random(0,300);
  axaxis = random(0,300);
  ayaxis = random(0,300);
  azaxis = random(0,300);
  mxaxis = random(0,300);
  myaxis = random(0,300);
  mzaxis = random(0,300);
  pressure = random(0,300);
}
