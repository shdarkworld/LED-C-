#include<iostream>
#include<stdio.h>
#include<cstring>
#include<unistd.h>
using namespace std;

#define LED3 "/sys/class/leds/beaglebone:green:usr3" //Path

// Prototype Functios
void WriteLED(char filename[], char value[]);
void RemoveTrigger();

char trig[9] = "/trigger";
char non[5] = "none";
char bright[12] = "/brightness";
char uno[2] = "1";
char cero[2] = "0";
char fifty[3] = "50";
char d_on[10] = "/delay_on";
char d_off[11] = "/delay_off";
char tim[6] = "timer";


int main(int argc, char* argv[])
{
	if(argc != 2)
	{
		//Checks if number of arguments are rigth
		cout << "Error wrong number of arguments" << endl;
		return 2;
	}
	cout << "Starting the script..." << endl;
	// Comparing argument
	if(strcmp(argv[1], "on") == 0)
	{
		// Turns on LED3
		cout << "LED on" << endl;
		RemoveTrigger();
		WriteLED(bright,uno);
	}
	else
	{
		if(strcmp(argv[1], "off") == 0)
		{
			// Turns off LED3
			cout << "LED off" << endl;
			RemoveTrigger();
			WriteLED(bright, cero);
		}
		else
		{
			if (strcmp(argv[1], "flash") == 0)
			{
				// LED3 starts flashing 50ms on, 50ms off (needs sudo)
				cout << "LED flashing" << endl;
				WriteLED(trig,tim);
				WriteLED(d_on,fifty);
				WriteLED(d_off,fifty);
			}
			else
				cout << "Wrong arguments" << endl;
		}
	}
	cout << "Script Done" << endl;

	return 0;
}

// Complete Functions
void WriteLED(char filename[], char value[])
{
	// Writes the passed value to the file in the path
	FILE *fp;
	char fullFile[100];
	sprintf(fullFile, LED3 "%s", filename);
	fp = fopen(fullFile, "w+");
	fprintf(fp, "%s", value);
	fclose(fp);
	
	
}

void RemoveTrigger()
{
	//Writes "none" in trigger
	WriteLED(trig, non);
}
