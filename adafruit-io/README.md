# Hologram + TinyGSM + Adafruit IO
This example uses TinyGSM and PubSubClient to connect to Adafruit.io to send and receive messages and log data!

## Installation

Install TinyGSM and PubSubClient Arduino libraries from "Manage Libraries" in the Arduino IDE

## Adafruit IO Set Up

1. Create an account at adafruit.io
1. Login and grab you AIO KEY from "View AIO Key", stash this
1. Go to "Feeds" and create a Group, lets call it "hologram"
1. Click on you hologram group, from there use "Actions" to create two feeds called "to" and "from"
1. Go to Dashboards and create a new one
1. Add a toggle widget, select hologram > from for the feed.

## Arduino Set Up

1. Wire up your GSM Module, this example is set for SIM800 by default
1. In the Arduino sketch included in this folder fill in the blanks for the MQTT details. Add in your adafruit.io username and your AIO_KEY.
1. Program the sketch

## Test it out!

Open the serial monitor in the Arduino IDE

Toggling the switch in the Adafruit.io dashboard should cause Pin 13 on your Arduino turn on and off. You should also see the payload and topic in the Serial monitor.

If you go to the hologram > to feed we set up earlier, you'll see the current LED status logged.

Now make something cool and tweet at us or post your project on hackster.io/hologram
