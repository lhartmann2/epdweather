#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include <cweather.h>

#include "GUI_Paint.h"
#include "GUI_BMPfile.h"
#include "ImageData.h"
#include "ER-EPD026-1B.h"

//Handler
void Handler(int signo)
{
	printf("\r\nHandler: Sleep mode\r\n");
	EPD_Sleep();
	DEV_ModuleExit();
	
	exit(0);
}

//Get center x position of a given icon
int get_icon_x_position(const char* icon)
{
	int value = 0;
	
	if((strcmp(icon, "01d") == 0) || (strcmp(icon, "01n") == 0))
		value = 39;
	else if((strcmp(icon, "02d") == 0) || (strcmp(icon, "02n") == 0))
		value = 28.5;
	else if((strcmp(icon, "03d") == 0) || (strcmp(icon, "03n") == 0))
		value = 32;
	else if((strcmp(icon, "04d") == 0) || (strcmp(icon, "04n") == 0))
		value = 24;
	else if((strcmp(icon, "09d") == 0) || (strcmp(icon, "09n") == 0))
		value = 34;
	else if((strcmp(icon, "10d") == 0) || (strcmp(icon, "10n") == 0))
		value = 37;
	else if((strcmp(icon, "11d") == 0) || (strcmp(icon, "11n") == 0))
		value = 27;
	else if((strcmp(icon, "13d") == 0) || (strcmp(icon, "13n") == 0))
		value = 48;
	else if((strcmp(icon, "50d") == 0) || (strcmp(icon, "50d") == 0))
		value = 36;
	
	return value;
}

//Get correct y position of a given icon
int get_icon_y_position(const char* icon)
{
	int value = 0;
	
	if((strcmp(icon, "01d") == 0) || (strcmp(icon, "01n") == 0))
		value = 27;
	else if((strcmp(icon, "02d") == 0) || (strcmp(icon, "02n") == 0))
		value = 25;
	else if((strcmp(icon, "03d") == 0) || (strcmp(icon, "03n") == 0))
		value = 38;
	else if((strcmp(icon, "04d") == 0) || (strcmp(icon, "04n") == 0))
		value = 28;
	else if((strcmp(icon, "09d") == 0) || (strcmp(icon, "09n") == 0))
		value = 27;
	else if((strcmp(icon, "10d") == 0) || (strcmp(icon, "10n") == 0))
		value = 27;
	else if((strcmp(icon, "11d") == 0) || (strcmp(icon, "11n") == 0))
		value = 22;
	else if((strcmp(icon, "13d") == 0) || (strcmp(icon, "13n") == 0))
		value = 32;
	else if((strcmp(icon, "50d") == 0) || (strcmp(icon, "50d") == 0))
		value = 38;
	
	return value;
}

//Draw conditions icon
//@param const char icon (wdata->icon)
void draw_icon(const char* icon)
{
	char path[100];
	strcpy(path, "./pic/");
	strcat(path, icon);
	strcat(path, ".bmp");

	GUI_ReadBmp(path, get_icon_x_position(icon), get_icon_y_position(icon));
}

//Draw centered string @ font 8
//@param x
//@param y
//@param const char str (ex., (wdata->description))
void draw_string_8(int y, const char* str)
{
	char outStr[60];
	switch(strlen(str))
	{
		case 3:
			strcpy(outStr, "             ");
			break;
		case 4:
			strcpy(outStr, "            ");
			break;
		case 5:
			strcpy(outStr, "            ");
			break;
		case 7:
			strcpy(outStr, "           ");
			break;
		case 9:
			strcpy(outStr, "          ");
			break;
		case 10:
			strcpy(outStr, "          ");
			break;
		case 11:
			strcpy(outStr, "         ");
			break;
		case 12:
			strcpy(outStr, "         ");
			break;
		case 13:
			strcpy(outStr, "        ");
			break;
		case 14:
			strcpy(outStr, "        ");
			break;
		case 15:
			strcpy(outStr, "       ");
			break;
		case 16:
			strcpy(outStr, "       ");
			break;
		case 17:
			strcpy(outStr, "       ");
			break;
		case 18:
			strcpy(outStr, "      ");
			break;
		case 19:
			strcpy(outStr, "     ");
			break;
		case 20:
			strcpy(outStr, "     ");
			break;
		case 22:
			strcpy(outStr, "    ");
			break;
		case 23:
			strcpy(outStr, "    ");
			break;
		case 25:
			strcpy(outStr,"   ");
			break;
		case 27:
			strcpy(outStr,"  ");
			break;
		case 28:
			strcpy(outStr," ");
			break;
		case 29:
			strcpy(outStr," ");
			break;
		case 31:
			if(strcmp(str, "thunderstorm with light drizzle") == 0)
				strcpy(outStr, "      thunderstorm with               light drizzle");
			else if(strcmp(str, "thunderstorm with heavy drizzle") == 0)
				strcpy(outStr, "      thunderstorm with               heavy drizzle");
			else
				strcpy(outStr,"error in case 31");
			break;
		default:
			strcpy(outStr, "");
			break;
	}
	if((strcmp(str, "thunderstorm with light drizzle") != 0) &&
		(strcmp(str, "thunderstorm with heavy drizzle") != 0))
		{
			strcat(outStr, str);
		}
	
	Paint_DrawString_EN(0, y, outStr, &Font8, WHITE, BLACK);
}

//Draw centered string @ font 16
//@param y
//@param const char str (ex., (wdata->conditions))
void draw_string_16(int y, const char* str)
{
	char outStr[14];
	int x = 0;
	switch(strlen(str))
	{
		case 1:
			strcpy(outStr, "      ");
			break;
		case 2:
			strcpy(outStr, "     ");
			break;
		case 3:
			strcpy(outStr, "     ");
			x = 3;
			break;
		case 4:
			strcpy(outStr, "     ");
			break;
		case 5:
			strcpy(outStr, "    ");
			x = 3;
			break;
		case 6:
			strcpy(outStr, "    ");
			break;
		case 7:
			strcpy(outStr, "   ");
			x = 3;
			break;
		case 8:
			strcpy(outStr, "   ");
			break;
		case 9:
			strcpy(outStr, "  ");
			break;
		case 10:
			strcpy(outStr, "  ");
			break;
		case 11:
			strcpy(outStr, " ");
			break;
		case 12:
			strcpy(outStr, " ");
			x = 0;
			break;
		default:
			strcpy(outStr,"");
			break;
	}
	
	strcat(outStr, str);
	
	Paint_DrawString_EN(x, y, outStr, &Font16, WHITE, BLACK);
}

//Draw main temperature
//@param y
//@param const char str (wdata->temp)
void draw_temp(int y, const char* str)
{
	float temp = strtof(str, NULL);
	int temp_i = round(temp);
	char outStr[10];
	sprintf(outStr, "%d", temp_i);
	
	switch(strlen(outStr))
	{
		case 1:
			Paint_DrawCircle(74, y+2, 2, BLACK, DRAW_FILL_EMPTY, DOT_PIXEL_1X1);
			strcat(outStr,"F");
			Paint_DrawString_EN(58, y, outStr, &Font24, WHITE, BLACK);
			break;
		case 2:
			Paint_DrawCircle(82, y+2, 2, BLACK, DRAW_FILL_EMPTY, DOT_PIXEL_1X1);
			strcat(outStr,"F");
			Paint_DrawString_EN(49, y, outStr, &Font24, WHITE, BLACK);
			break;
		case 3:
			Paint_DrawCircle(92, y+2, 2, BLACK, DRAW_FILL_EMPTY, DOT_PIXEL_1X1);
			strcat(outStr,"F");
			Paint_DrawString_EN(42, y, outStr, &Font24, WHITE, BLACK);
			break;
		default:
			Paint_DrawString_EN(50, y, "error in draw_temp", &Font16, WHITE, BLACK);
			break;
	}
}

//Draw current min temperature
//@param const char str (wdata->low)
void draw_low_temp(const char* str)
{
	float temp = strtof(str, NULL);
	int temp_i = round(temp);
	char outStr[10];
	sprintf(outStr, "%d", temp_i);
	
	Paint_DrawString_EN(15, 160, "MIN", &Font8, WHITE, BLACK);
	
	switch(strlen(outStr))
	{
		case 1:
			Paint_DrawCircle(22, 174, 1, BLACK, DRAW_FILL_EMPTY, DOT_PIXEL_1X1);
			strcat(outStr,"F");
			Paint_DrawString_EN(11, 172, outStr, &Font16, WHITE, BLACK);
			break;
		case 2:
			Paint_DrawCircle(28, 174, 1, BLACK, DRAW_FILL_EMPTY, DOT_PIXEL_1X1);
			strcat(outStr,"F");
			Paint_DrawString_EN(6, 172, outStr, &Font16, WHITE, BLACK);
			break;
		case 3:
			Paint_DrawCircle(33, 174, 1, BLACK, DRAW_FILL_EMPTY, DOT_PIXEL_1X1);
			strcat(outStr,"F");
			Paint_DrawString_EN(0, 172, outStr, &Font16, WHITE, BLACK);
			break;
		default:
			Paint_DrawString_EN(15, 180, "error in draw_low_temp", &Font8, WHITE, BLACK);
			break;
	}
}

//Draw feels-like temperature
//@param const char str (wdata->feelsLike)
void draw_feels_like_temp(const char* str)
{
	float temp = strtof(str, NULL);
	int temp_i = round(temp);
	char outStr[10];
	sprintf(outStr, "%d", temp_i);
	
	Paint_DrawString_EN(50, 160, "FEELS LIKE", &Font8, WHITE, BLACK);
	
	switch(strlen(outStr))
	{
		case 1:
			Paint_DrawCircle(74, 174, 1, BLACK, DRAW_FILL_EMPTY, DOT_PIXEL_1X1);
			strcat(outStr,"F");
			Paint_DrawString_EN(63, 172, outStr, &Font16, WHITE, BLACK);
			break;
		case 2:
			Paint_DrawCircle(80, 174, 1, BLACK, DRAW_FILL_EMPTY, DOT_PIXEL_1X1);
			strcat(outStr,"F");
			Paint_DrawString_EN(58, 172, outStr, &Font16, WHITE, BLACK);
			break;
		case 3:
			Paint_DrawCircle(85, 174, 1, BLACK, DRAW_FILL_EMPTY, DOT_PIXEL_1X1);
			strcat(outStr,"F");
			Paint_DrawString_EN(52, 172, outStr, &Font16, WHITE, BLACK);
			break;
		default:
			Paint_DrawString_EN(50, 180, "error in draw_feels_like_temp", &Font8, WHITE, BLACK);
			break;
	}
}

//Draw current max temperature
//@param const char str (wdata->high)
void draw_high_temp(const char* str)
{
	float temp = strtof(str, NULL);
	int temp_i = round(temp);
	char outStr[10];
	sprintf(outStr, "%d", temp_i);
	
	Paint_DrawString_EN(119, 160, "MAX", &Font8, WHITE, BLACK);
	
	switch(strlen(outStr))
	{
		case 1:
			Paint_DrawCircle(126, 174, 1, BLACK, DRAW_FILL_EMPTY, DOT_PIXEL_1X1);
			strcat(outStr,"F");
			Paint_DrawString_EN(115, 172, outStr, &Font16, WHITE, BLACK);
			break;
		case 2:
			Paint_DrawCircle(132, 174, 1, BLACK, DRAW_FILL_EMPTY, DOT_PIXEL_1X1);
			strcat(outStr,"F");
			Paint_DrawString_EN(110, 172, outStr, &Font16, WHITE, BLACK);
			break;
		case 3:
			Paint_DrawCircle(137, 174, 1, BLACK, DRAW_FILL_EMPTY, DOT_PIXEL_1X1);
			strcat(outStr,"F");
			Paint_DrawString_EN(104, 172, outStr, &Font16, WHITE, BLACK);
			break;
		default:
			Paint_DrawString_EN(50, 180, "error in draw_high_temp", &Font8, WHITE, BLACK);
			break;
	}
}

//Draw current humidity
//@param const char str (wdata->humidity)
void draw_humidity(const char* str)
{
	char outStr[10];
	strcpy(outStr, str);
	strcat(outStr, "%");
	
	Paint_DrawString_EN(17, 196, "HUMIDITY", &Font8, WHITE, BLACK);
	
	switch(strlen(str))
	{
		case 1:
			Paint_DrawString_EN(28, 208, outStr, &Font16, WHITE, BLACK);
			break;
		case 2:
			Paint_DrawString_EN(22, 208, outStr, &Font16, WHITE, BLACK);
			break;
		case 3:
			Paint_DrawString_EN(15, 208, outStr, &Font16, WHITE, BLACK);
			break;
		default:
			Paint_DrawString_EN(17, 208, "error in draw_humidity", &Font8, WHITE, BLACK);
			break;
	}
}

//Draw current pressure converted from hpa to inHg
//@param const char str (wdata->pressure)
void draw_pressure(const char* str)
{
	float hpa = strtof(str, NULL);
	int inhg = round(hpa*0.02953);
	char outStr[10];
	sprintf(outStr, "%d", inhg);
	
	Paint_DrawString_EN(92, 196, "PRESSURE", &Font8, WHITE, BLACK);
	
	switch(strlen(outStr))
	{
		case 1:
			Paint_DrawString_EN(98, 208, outStr, &Font16, WHITE, BLACK);
			Paint_DrawString_EN(108, 212, "inHg", &Font8, WHITE, BLACK);
			break;
		case 2:
			Paint_DrawString_EN(91, 208, outStr, &Font16, WHITE, BLACK);
			Paint_DrawString_EN(113, 212, "inHg", &Font8, WHITE, BLACK);
			break;
		case 3:
			Paint_DrawString_EN(84, 208, outStr, &Font16, WHITE, BLACK);
			Paint_DrawString_EN(118, 212, "inHg", &Font8, WHITE, BLACK);
			break;
		default:
			Paint_DrawString_EN(17, 208, "error in draw_humidity", &Font8, WHITE, BLACK);
			break;
	}
}

//Draw current wind speed in mph
//@param const char str (wdata->speed)
void draw_wind_speed(const char* str)
{
	char outStr[10];
	strcpy(outStr, str);
	
	Paint_DrawString_EN(13, 233, "WIND SPEED", &Font8, WHITE, BLACK);
	
	switch(strlen(str))
	{
		case 1:
			Paint_DrawString_EN(24, 245, outStr, &Font16, WHITE, BLACK);
			Paint_DrawString_EN(36, 250, "MPH", &Font8, WHITE, BLACK);
			break;
		case 2:
			Paint_DrawString_EN(19, 245, outStr, &Font16, WHITE, BLACK);
			Paint_DrawString_EN(42, 250, "MPH", &Font8, WHITE, BLACK);
			break;
		case 3:
			Paint_DrawString_EN(12, 245, outStr, &Font16, WHITE, BLACK);
			Paint_DrawString_EN(46, 250, "MPH", &Font8, WHITE, BLACK);
			break;
		case 4:
			Paint_DrawString_EN(7, 245, outStr, &Font16, WHITE, BLACK);
			Paint_DrawString_EN(52, 250, "MPH", &Font8, WHITE, BLACK);
			break;
		case 5:
			Paint_DrawString_EN(2, 245, outStr, &Font16, WHITE, BLACK);
			Paint_DrawString_EN(60, 250, "MPH", &Font8, WHITE, BLACK);
			break;
		default:
			Paint_DrawString_EN(17, 250, "error in draw_wind_speed", &Font8, WHITE, BLACK);
			break;
	}
}

//Draw current wind speed converted from degrees to cardinal direction
//@param const char str (wdata->dir)
void draw_wind_direction(const char* str)
{
	char outStr[4];
	float deg = strtof(str, NULL);
	
	if((deg >= 0) && (deg < 11.25))
		strcpy(outStr, "N");
	else if((deg >= 11.25) && (deg < 33.75))
		strcpy(outStr, "NNE");
	else if((deg >= 33.75) && (deg < 56.25))
		strcpy(outStr, "NE");
	else if((deg >= 56.25) && (deg < 78.75))
		strcpy(outStr, "ENE");
	else if((deg >= 78.75) && (deg < 101.25))
		strcpy(outStr, "E");
	else if((deg >= 101.25) && (deg < 123.75))
		strcpy(outStr, "ESE");
	else if((deg >= 123.75) && (deg < 146.25))
		strcpy(outStr, "SE");
	else if((deg >= 146.25) && (deg < 168.75))
		strcpy(outStr, "SSE");
	else if((deg >= 168.75) && (deg < 191.25))
		strcpy(outStr, "S");
	else if((deg >= 191.25) && (deg < 213.75))
		strcpy(outStr, "SSW");
	else if((deg >= 213.75) && (deg < 236.25))
		strcpy(outStr, "SW");
	else if((deg >= 236.25) && (deg < 258.75))
		strcpy(outStr, "WSW");
	else if((deg >= 258.75) && (deg < 281.25))
		strcpy(outStr, "W");
	else if((deg >= 281.25) && (deg < 303.75))
		strcpy(outStr, "WNW");
	else if((deg >= 303.75) && (deg < 326.25))
		strcpy(outStr, "NW");
	else if((deg >= 326.25) && (deg < 348.75))
		strcpy(outStr, "NNW");
	else if((deg >= 348.75) && (deg < 360))
		strcpy(outStr, "N");
	
	Paint_DrawString_EN(91, 235, "WIND DIR", &Font8, WHITE, BLACK);
	
	switch(strlen(outStr))
	{
		case 1:
			Paint_DrawString_EN(106, 245, outStr, &Font16, WHITE, BLACK);
			break;
		case 2:
			Paint_DrawString_EN(100, 245, outStr, &Font16, WHITE, BLACK);
			break;
		case 3:
			Paint_DrawString_EN(95, 245, outStr, &Font16, WHITE, BLACK);
			break;
		default:
			Paint_DrawString_EN(90, 260, "error in draw_wind_speed", &Font8, WHITE, BLACK);
			break;
	}
	
}

//draws the current date
//@param m - Current month+1
//@param d - Current day
//@param y - Current year+1900
void draw_date(int m, int d, int y)
{
	char outStr[12];	
	
	if(m < 10)
	{
		if(d < 10)
		{
			sprintf(outStr, "0%d/0%d/%d", m, d, y);
		} else {
			sprintf(outStr, "0%d/%d/%d", m, d, y);
		}
	} else {
		if(d < 10)
		{
			sprintf(outStr, "%d/0%d/%d", m, d, y);
		} else {
			sprintf(outStr, "%d/%d/%d", m, d, y);
		}
	}
	
	//Paint_DrawString_EN(27, 270, "DATE", &Font8, WHITE, BLACK);
	Paint_DrawString_EN(6, 282, outStr, &Font12, WHITE, BLACK);
}

//Draws the time of the last update
//@param h - hour of last update
//@param m - minute of last update
void draw_last_update(int h, int m)
{
	char outStr[12];
	int am;
	if(h<12)
		am=1;
	else
		am=0;
	
	if(am==1)
	{
		if(h==0)
		{
			if(m<10)
			{
				sprintf(outStr, "12:0%dAM", m);
			} else {
				sprintf(outStr, "12:%dAM", m);
			}
		} else if(h<10)
		{
			if(m<10)
			{
				sprintf(outStr, "0%d:0%dAM", h, m);
			} else {
				sprintf(outStr, "0%d:%dAM", h, m);
			}
		} else {
			if(m<10)
			{
				sprintf(outStr, "%d:0%dAM", h, m);
			} else {
				sprintf(outStr, "%d:%dAM", h, m);
			}
		}
	} else {
		if((h-12)<10)
		{
			if(m<10)
			{
				sprintf(outStr, "0%d:0%dPM", h-12, m);
			} else {
				sprintf(outStr, "0%d:%dPM", h-12, m);
			}
		} else {
			if(m<10)
			{
				sprintf(outStr, "%d:0%dPM", h-12, m);
			} else {
				sprintf(outStr, "%d:%dPM", h-12, m);
			}
		}
	}
	
	Paint_DrawString_EN(45, 272, "LAST UPDATE", &Font8, WHITE, BLACK);
	Paint_DrawString_EN(94, 282, outStr, &Font12, WHITE, BLACK);
}


int main(void)
{
	DEV_ModuleInit();
	struct c_weather_data *wdata;
	
	signal(SIGINT, Handler);
	
	if(EPD_Init() != 0) {
		printf("EPD init failed.\r\n");
	}
	
	EPD_Clear();
	
	//Create Image cache
	UBYTE *BlackImage;
	UWORD Imagesize = ((EPD_WIDTH % 8 == 0)? (EPD_WIDTH / 8): (EPD_WIDTH / 8 + 1)) * EPD_HEIGHT;
	if((BlackImage = (UBYTE *)malloc(Imagesize)) == NULL) {
		printf("Failed to allocated memory for image cache\r\n");
		exit(0);
	}
	
	
	
	Paint_NewImage(BlackImage, EPD_WIDTH, EPD_HEIGHT, 0, BLACK);
	Paint_SelectImage(BlackImage);
	Paint_Clear(WHITE);
	
	while(1)
	{
		wdata = c_weather_get_data();
		Paint_Clear(WHITE);
		if (!wdata) {
			Paint_DrawString_EN(2, 2, "Failed to get weather data Retrying in 2 minutes...", &Font16, WHITE, BLACK);
		} else {
			//Main draw routine
			
			//TOP
			draw_string_16(4, wdata->conditions); //Main condition text
			draw_icon(wdata->icon); //Icon
			draw_string_8(108, wdata->description); //condition description text
			
			//TEMPS
			draw_temp(129, wdata->temp);
			draw_low_temp(wdata->low);
			draw_feels_like_temp(wdata->feelsLike);
			draw_high_temp(wdata->high);
			
			//OTHER
			draw_humidity(wdata->humidity);
			draw_pressure(wdata->pressure);
			
			//WIND
			draw_wind_speed(wdata->speed);
			draw_wind_direction(wdata->deg);
			
			//DATE/TIME
			time_t t = time(NULL);
			struct tm tm = *localtime(&t);
			draw_date(tm.tm_mon+1, tm.tm_mday, tm.tm_year+1900);
			draw_last_update(tm.tm_hour, tm.tm_min);
		}

		//Draw to display
		EPD_Display(BlackImage);
		
		//Wait 2 minutes
		sleep(90);
		
		//Reset weather vars
		c_weather_free(wdata);
	}
	
	//DEV_Delay_ms(500);
	
	c_weather_free(wdata);
	EPD_Sleep();
	DEV_ModuleExit();
	free(BlackImage);
	BlackImage = NULL;
	
	return 0;
}
