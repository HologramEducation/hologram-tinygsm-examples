# hologram-tinygsm-examples
Examples using the TinyGSM library to connect to hologram

## Installation

Install TinyGSM Arduino libraries from "Manage Libraries" in the Arduino IDE

Install Losant MQTT following the instructions here https://github.com/Losant/losant-mqtt-arduino

## Losant Arduino Device Set-Up

1. Create a New Application in Losant
1. Create a New Standalone Device for your application
1. Generate an Access Key and Access Key Secret
1. Copy the Device ID, Key and Secret to the correct field in the Arduino sketch
1. Program the Arduino sketch, be sure to set the correct modem you're using at the top of the sketch

## Losant Workflow Set-Up

We need a flow that sends a command "toggle" to the device we set up before.

1. Create a New Cloud Workflow in your app
1. Drag the toggle.flow to the "Import Existing Flow" box in the Settings panel
1. Save and deploy

You should be able to toggle the virtual button to turn Pin 13 on and off.
