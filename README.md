# [Raksh](https://hackaday.io/project/13345-rakshthe-25-earworn-child-pneumonia-monitor) Bluemix application

Raksh, named after the Sanskrit word “safeguard,” is a low cost wifi-based, ear-worn multi-parameter monitoring platform to primarily monitor child pneumonia.
Raksh, continuously monitor parameters like Respiration Rate, Heart Rate, Blood Oxygenation (SpO2) and Body Temperature in a noninvasive and nonobtrusive manner behind the ear. 
The data is streamed using MQTT to an IBM Bluemix server. This project also explores the opportunities for presenting patient vital signs from such a device to the remote health care workers and doctors. 

### Raksh Dashboard view
<img width="772" alt="screenshot1" src="https://cloud.githubusercontent.com/assets/1295467/25814388/f857bb24-343a-11e7-8361-c951c5acf781.png">


## Getting Started
Raksh was designed to be simple to develop and the components are modular through the use of the i2c bus
### Hardware Prerequisites

```
	1. Particle Photon (Wifi MCU)
	2. MAX30100 (SpO2, Heart Rate IC)
	3. MLX90614 (I2C Noncontact Temperature sensor)
	4. LIR2560 battery
	5. 5V Boost regulator
```
Connections: 
Connect SDA, SCL of MAX30100&MLX90614 to D0,D1 respectively and Vin,Gnd to 3.3V and Gnd in the Particle Photon.


### Software Prerequisites

```
	1. IBM Bluemix
	2. Create a Internet of Things Platform Starter boilerplate app on Bluemix
	3. Add a custom device to the Watson IoT platform using "Add Device"
	4. Note the API Keys and other credentials as soon the Device is added
	5. Add the firmware to Particle Photon Cloud IDE or Particle Desktop and replace relavent details 
	6. Import the package.JSON file into Node-Red to create the application
	7. Generate API keys in the Apps section of the Watson IoT platform and edit the Node-Red device input
```
Visualize the data on the Node-Red dashboard.

### Node-Red Application
The Node-Red application is used to split various sensor values from JSON format and display using charts and dials. Alerts are also configurable and currently email is used to convey patient alerts but in future iterations a phone alarm might be triggered.

<img width="504" alt="noderedflow" src="https://cloud.githubusercontent.com/assets/1295467/25814454/2d770314-343b-11e7-9e5b-fb60995f7756.PNG">


## Built With

* [Watson IoT](https://www.ibm.com/internet-of-things/platform/watson-iot-platform/) - IoT backend
* [Node-Red](https://nodered.org/) - NodeJS based IoT tool
* [IBM Bluemix](https://www.ibm.com/cloud-computing/bluemix/) - Cloud platform service
* [Particle](https://www.particle.io/) - Wifi MCU


## Authors

* **Vignesh Ravichandran** - [viggi1000](https://github.com/viggi1000)

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

## Acknowledgments

* Thanks to [oxullo](https://github.com/oxullo/Arduino-MAX30100) for the amazing MAX30100 lib
* IBM & Node-Red team for providing such amazing tools!
* Dad for funding my offshoot ideas as always.


