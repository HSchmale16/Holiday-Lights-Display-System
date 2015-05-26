/*
 * XMAS_LIGHTS_CLIENT.ino
 * 
 * Copyright 2015 Henry Schmale <hschmale16@gmail.com>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */

#include <SPI.h>
#include <Ethernet.h>

// Macro to say that we're debugging right now
#define DEBUG_MODE

// constants
const int NUM_OUTPUTS = 8;		// must be a multiple of 8
const int BYTES_PER_INSTRUCTION = 8;	// How many bytes are in each instruction
const int NUM_FORBIDDEN = 7;		// Number of Forbiden Pins
const int forbiddenPins[NUM_FORBIDDEN] = {0, 1, 4, 10, 11, 12, 13};
// How many milliseconds to wait between write-outs
const int LIGHTS_UPDATE_T_PERIOD = 100;

// Networking stuff
byte mac[] =
{
	0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip(192,168, 0, 6);

// Initialize the Ethernet server library
// with the IP address and port you want to use
// (port 80 is default for HTTP):
EthernetServer server(80);

void setup()
{
	// Open serial communications and wait for port to open:
#ifdef DEBUG_MODE
	Serial.begin(9600);
#endif
	
	// init pins
	int outs = 0;
	int p = -1;	// start at -1 because I increment it first
	while(outs < NUM_OUTPUTS)
	{
		while(checkForbidden(p++));
		pinMode(p, OUTPUT);
        digitalWrite(p, LOW);
		outs++;
#ifdef DEBUG_MODE
		Serial.print("Output: ");
		Serial.println(p);
#endif
	}

	// start the Ethernet connection and the server:
	Ethernet.begin(mac, ip);
	server.begin();
#ifdef DEBUG_MODE
	Serial.print("server is at ");
	Serial.println(Ethernet.localIP());
#endif
}

String songData;
void loop()
{
	// listen for incoming clients
	EthernetClient client = server.available();
	if (client)
	{
		while (client.connected())
		{
			// clear the song data for this run
			songData = "";
			// get the song data
			while(client.available())
			{
				char c = client.read();
				songData += c;
				if(songData.length() % BYTES_PER_INSTRUCTION == 0)
				{
					execute();
					songData = "";
				}
			}
			// close the connection:
			client.stop();
		}
		
	} // if (client) closed
}

// integer exponetion. Very standard
int powi(int m, int n)
{
	int j = m;
	m = 1;
	for(int i = 0; i < n; i++)
	{
		m *= j;
	}
	return m;
}

/** Checks if a pin is on the forbidden list. If it is it returns true.
 *  else it returns false.
 */
bool checkForbidden(int pin)
{
	for(int i = 0; i < NUM_FORBIDDEN; i++){
		if(pin == forbiddenPins[i])
			return true;
	}
	return false;
}

void execute()
{
#ifdef DEBUG_MODE
	Serial.println(songData);	// print out current song data
#endif
	for(int i = 0; i < (songData.length() / BYTES_PER_INSTRUCTION); i += BYTES_PER_INSTRUCTION)
	{
		int pin = 0;
		String dat = songData.substring(i, i + BYTES_PER_INSTRUCTION);
		for(int j = 0; j < BYTES_PER_INSTRUCTION - 2; j++)
		{
			char c = dat[j];
			for(int k = 0; k < 8; k++)
			{
				if((c & powi(2, k)) == powi(2, k))
				{
					digitalWrite(pin, HIGH);
				}
				else
				{
					digitalWrite(pin, LOW);
				}
				Serial.println(pin);
				while(checkForbidden(++pin));
			}
		}
		delay(LIGHTS_UPDATE_T_PERIOD);
	}
}
