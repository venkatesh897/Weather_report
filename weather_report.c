#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define WEATHER_REPORT_FILE "weather_report.dat"

char* get_temperature_of_city(char* file_name)
{
	char weather_report[1000];
	char* temperature;
 	FILE* fp_weather_report = fopen(WEATHER_REPORT_FILE, "r");
 	fread(weather_report, sizeof(weather_report), 1, fp_weather_report);
 	char* weather_report_token = strtok(weather_report, "{,\":");
 	while(weather_report_token !=  NULL)
 	{
 		char is_temperature_found = 'n';
 		if(strcmp(weather_report_token, "temp") == 0)
 		{
 			is_temperature_found = 'y';
 		}
 		weather_report_token = strtok(NULL, "{,\":");
 		if(is_temperature_found == 'y')
 		{
 			temperature = weather_report_token;
 			break;
 		}
 	}
 	fclose(fp_weather_report);
 	return temperature;
}

void display_temperature()
{
	char cmd[100];
	char city_name[30];
	printf("Enter city: ");
	scanf("%s", city_name);
	sprintf(cmd, "curl \"http://api.openweathermap.org/data/2.5/weather?q=%s&appid=f9ba15284b25d77cf2aae3a2733bb72a&units=metric\" > %s", city_name, WEATHER_REPORT_FILE);
	system(cmd);
	char* temperature = get_temperature_of_city(WEATHER_REPORT_FILE);
	printf("Temperature in %s is %s %cC", city_name, temperature, 248);
}

int main()
{
	display_temperature();
	return 0;
}





