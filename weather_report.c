#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define WEATHER_REPORT_FILENAME "weatherReport.dat"

char* get_temperature()
{
	FILE* fp_weather_report = fopen(WEATHER_REPORT_FILENAME, "r");
	char* temperature;
	char weather_report[1000];
	fread(weather_report, sizeof(weather_report), 1, fp_weather_report);
	char* token = strtok(weather_report, "{,\":");
	while(token != NULL)
	{
		char is_temperature_found = 'n';
		if(strcmp(token, "temp") == 0)
		{
			is_temperature_found = 'y';
			temperature = token;
			break;
		}
	}
	fclose(fp_weather_report);
	return temperature;
}

void load_weather_report(char* location, char* file_name)
{
	char cmd[100];
	sprintf(cmd, "curl \"http://api.openweathermap.org/data/2.5/weather?q=London&appid=f9874839570cbe4c58c6266950c788f6\" > %s", location, file_name);
	system(cmd);
}

void display_temperature_of_location()
{
	char city[30];
	printf("Enter city: ");
	scanf("%s", city);
	load_weather_report(city, WEATHER_REPORT_FILENAME);
	char* temperature = get_temperature(WEATHER_REPORT_FILENAME);
	printf("The temperature in %s is %s", city,temperature);;
}

int main(int argc, char const *argv[])
{
	display_temperature_of_location();
	return 0;
}
