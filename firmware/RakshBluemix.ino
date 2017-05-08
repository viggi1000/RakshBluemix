
/*
Raksh: The earworn multisensory pneumonia monitor for children.
Raksh is a wearable sensor to track progression of child pneumonia in developing countries. It monitors the Blood Oxygenation, HR, Respiration Rate
For SpO2, HR the MAX30100 sensor was used, For respiration sensing a nasal IR temperature sensor was used. LM35 for Body Temperature.
Connections: 
Connect SDA, SCL of MAX30100&MLX90614 to D0,D1 respectively and Vin,Gnd to 3.3V and Gnd in the Particle Photon.

Create a IoT boilerplate app on the IBM bluemix service and add a custom MQTT device and connect up your Photon board, Follow the below tutorial.
(http://www.kevinhoyt.com/2016/04/27/particle-photon-on-watson-iot/).

DISCLAIMER **While I aim to make this more safe, accurate it this is experimental software (and pre-beta) at that.
It is not suitable for any particular purpose. No life-critical devices should be based on this software.**

Port of the Oxullo Interscans library for Particle Photon/Electron.
Work by Vignesh Ravichandran (hello@rvignesh.xyz)
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <MQTT.h>
#include "Adafruit_MLX90614.h"
#include "MAX30100_PulseOximeter.h"
#include "application.h"
#define REPORTING_PERIOD_MS     1000
#define slaveAddress 0x5A

#define POLL_PERIOD_US                      1E06 / 100
#define SAMPLING_RATE                       MAX30100_SAMPRATE_100HZ

// The LEDs currents must be set to a level that avoids clipping and maximises the
// dynamic range
#define IR_LED_CURRENT                      MAX30100_LED_CURR_50MA
#define RED_LED_CURRENT                     MAX30100_LED_CURR_27_1MA

// The pulse width of the LEDs driving determines the resolution of
// the ADC (which is a Sigma-Delta).
// set HIGHRES_MODE to true only when setting PULSE_WIDTH to MAX30100_SPC_PW_1600US_16BITS
#define PULSE_WIDTH                         MAX30100_SPC_PW_1600US_16BITS
#define HIGHRES_MODE                        true

// PulseOximeter is the higher level interface to the sensor
// it offers:
//  * beat detection reporting
//  * heart rate calculation
//  * SpO2 (oxidation level) calculation
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
unsigned long t, period_respiration;
uint32_t tsLastReport1 = 0;
int f;
float peakValue = 0;
PulseOximeter pox;
int BPM,sp;
float t;
uint32_t tsLastReport = 0;
uint32_t tsLastReport1 = 0;
char *IOT_CLIENT = "Client ID";  
char *IOT_HOST = "Your Host name";  
char *IOT_PASSWORD = "Your key";  
char *IOT_PUBLISH = "Publish ID";  
char *IOT_USERNAME = "use-token-auth";
int count = 0;

MQTT client( IOT_HOST, 1883, callback );

// Callback (registered below) fired when a pulse is detected

void setup()
{

    Serial.begin(115200);
    // Initialize the PulseOximeter instance and register a beat-detected callback
    pox.begin();
	mlx.begin();
    client.connect( 
    IOT_CLIENT, 
    IOT_USERNAME, 
    IOT_PASSWORD 
  );
  if( client.isConnected() ) {
    Serial.println( "Connected." );
    Particle.publish("Connected. ");
    // client.subscribe( IOT_SUBSCRIBE );
  }

}

void loop()
{
pox.update();
BPM=pox.getHeartRate();
sp=pox.getSpO2();
float sensorValue=mlx.readObjectTempC();
float threshold=mlx.readAmbientTempC();	
int i = 0;
int sensorValue = mlx.readObjectTempC();
  //  vals[i] = sensorValue;
if (sensorValue > peakValue) 
  {
     t=millis();
    peakValue = sensorValue;
   // tot++;
  }

  if (sensorValue <= threshold) 
  {
    if (peakValue > threshold) {
      // you have a peak value:
     signed long currentTime = millis();
      period_respiration = currentTime-t;
      Serial.println(peakValue);
      p = (float)period_respiration*6;
      f=60000/p;
    }
  }   
//Serial.print("Heart rate:");
//Serial.print(BPM);
//Serial.print("bpm / SpO2:");
//Serial.print(sp);
//    "{\"BPM\": " + BPM + "\"sp\": " + sp + "\"rr\": " + BPM/4 + "}" 
if (millis() - tsLastReport1 > 2000) {
Particle.publish("BPM", String(BPM));
Particle.publish("spo2", String(sp));
Particle.publish("temp", String(36));
String data = "{";
  data+="\"BPM\": ";
  data+=(int)BPM;
  data+= ",";
  data+="\n";
  data+="\"sp\": ";
  data+=(int)sp;
  data+= ",";
  data+="\n";
  data+="\"RR\": ";
  data+=(int)f;
  data+="\n";
  data+="}";
client.loop();

client.publish(IOT_PUBLISH,data);            
tsLastReport1 = millis();
}

}
void callback( char* topic, byte* payload, unsigned int length ) {  
  char p[length + 1];

  memcpy( p, payload, length );
  p[length] = NULL;

  String message( p );
}
