//
// BME280 oneshoot read
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include "bme280.h"

// delay between samples in microseconds

int main(int argc, char *argv[])
{

	int bme280;
	int T, P, H; // calibrated values
	int i2cBus,i2cDev;

	if (argc > 1){
		i2cDev = atoi(argv[1]);
	}else{
		i2cDev = 0x76;
	}


	if (argc > 0){
		i2cBus = atoi(argv[0]);
	}else{
		i2cBus = 0x76;
	}

	bme280 = bme280Init(i2cBus, i2cDev);
	if (bme280 != 0)
	{
		return -1; // problem - quit
	}

	//printf("BME280 device successfully opened.\n");

	//TODO : trouver comment attendre moins longtemps
	usleep(1000000); // wait for data to settle for first read


	bme280ReadValues(&T, &P, &H);
	T -= 150; // for some reason, the sensor reports temperatures too high
	printf("{data:{temp:{value:%3.2f,unit:\"C\"},pres:{value:%6.2f,unit:\"Pa\"},humi:{value:%2.2f,unit:\"%%\"}}}\n", (float)T/100.0, (float)P/256.0, (float)H/1024.0);
	return 0;

} /* main() */
