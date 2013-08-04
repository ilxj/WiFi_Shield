#include <Arduino.h>
#include <SoftwareSerial.h>
#include "WiFly.h"

//WiFly wifly(TX, RX);
WiFly wifly(2, 3);

void setup() {
	Serial.begin(9600);

	// wait for initilization of wifly
	delay(3000);

	Serial.println("--------- started --------");
}

void loop() {
	while (wifly.available()) {
		Serial.write(wifly.read());
	}

	while (Serial.available()) {
		wifly.write(Serial.read());
	}

	delay(1000);
}
