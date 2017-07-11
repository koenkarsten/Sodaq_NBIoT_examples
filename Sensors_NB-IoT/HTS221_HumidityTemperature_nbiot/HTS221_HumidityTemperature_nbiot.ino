/***************************************************************************
	This is a library for the HTS221 Humidity Temperature Sensor
		Originally written by speirano for SmartEverything
		Adjusted by Gregory Knauff of SODAQ for the NB-IoT shield
    Adjusted by Jan van Loenen to work on Sodaq Explorer and Arduino Leonardo

	Standard I2C-address is 0x5F.

***************************************************************************/

#include <Wire.h>
#include <Arduino.h>
#include "Sodaq_nbIOT.h"
#include "Sodaq_HTS221.h"

#if defined(ARDUINO_AVR_LEONARDO)
#define MODEM_STREAM Serial1

#elif defined(ARDUINO_SODAQ_EXPLORER)
#define MODEM_STREAM Serial

#elif defined(ARDUINO_AVR_UNO)
#define MODEM_STREAM Serial

#else
#error "Please select a Sodaq ExpLoRer, Arduino Leonardo or add your board."
#endif

Sodaq_nbIOT nbiot;

void setup()
{
  delay(500);
  MODEM_STREAM.begin(nbiot.getDefaultBaudrate());

  nbiot.init(MODEM_STREAM, 7);

  delay(2000);

  if (!nbiot.connect("oceanconnect.t-mobile.nl", "172.16.14.20", "20416")) {
    return;
  }

  if (hts221.begin() == false)
  {
    while (1);
  }
}


void loop()
{
  // Create the message
  String message = String(hts221.readTemperature()) + "C" +
                   ",  " + String(hts221.readHumidity()) + "%";

  // Send the message
  nbiot.sendMessage(message);

  // Wait some time between messages
  delay(60000); // 1000 = 1 sec
}
