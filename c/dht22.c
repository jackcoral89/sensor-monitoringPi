#include <wiringPi.h> // https://github.com/WiringPi/WiringPi
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define MAX_TIMINGS 85
#define DHT_PIN 7 // usa il numero di pin di wiringPi (GPIO 4)

// Array per memorizzare i dati
int data[5] = {0, 0, 0, 0, 0};

void read_dht_data()
{
	uint8_t laststate = HIGH;
	uint8_t counter = 0, j = 0;
	int i;

	// Inizializza array dati
	for (i = 0; i < 5; i++)
	{
		data[i] = 0;
	}

	// Invio del segnale di start: pin basso per 18 ms
	pinMode(DHT_PIN, OUTPUT);
	digitalWrite(DHT_PIN, LOW);
	delay(18);

	// Prepara alla lettura dei dati
	pinMode(DHT_PIN, INPUT);

	// Leggi il bus, rilevando i segnali temporizzati
	for (i = 0; i < MAX_TIMINGS; i++)
	{
		counter = 0;
		while (digitalRead(DHT_PIN) == laststate)
		{
			counter++;
			delayMicroseconds(1);
			if (counter == 255)
				break;
		}
		laststate = digitalRead(DHT_PIN);
		if (counter == 255)
			break;

		// Salta i primi 3 cambiamenti di stato
		if ((i >= 4) && (i % 2 == 0))
		{
			data[j / 8] <<= 1;
			if (counter > 16)
				data[j / 8] |= 1;
			j++;
		}
	}

	// Convalida checksum e stampa i valori
	if ((j >= 40) && (data[4] == ((data[0] + data[1] + data[2] + data[3]) & 0xFF)))
	{
		float h = ((data[0] << 8) + data[1]) / 10.0;

		if (h > 100)
		{
			h = data[0]; // fallback DHT11
		}

		float c = (((data[2] & 0x7F) << 8) + data[3]) / 10.0;

		if (c > 125)
		{
			c = data[2]; // fallback DHT11
		}

		if (data[2] & 0x80)
		{
			c = -c;
		}

		printf("Humidity = %.1f %% Temperature = %.1f °C\n", h, c);
	}
	else
	{
		printf("Data not good, skip\n");
	}
}

int main(void)
{
	printf("Raspberry Pi DHT22 temperature/humidity test\n");
	if (wiringPiSetup() == -1)
	{
		exit(1);
	}

	while (1)
	{
		read_dht_data();
		delay(2000); // attendi 2 secondi tra le letture
	}
	return 0;
}
