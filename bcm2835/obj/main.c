﻿/***************************************************
//Web: http://www.buydisplay.com
EastRising Technology Co.,LTD
Examples for ER-EPD026-1B 
Display is Hardward SPI 4-Wire SPI Interface 
Tested and worked with: 
Works with Raspberry pi
****************************************************/

#include <stdlib.h>     //exit()
#include <signal.h>     //signal()
#include <time.h>
#include "GUI_Paint.h"
#include "GUI_BMPfile.h"
#include "ImageData.h"
#include "ER-EPD026-1B.h"

void  Handler(int signo)
{
    //System Exit
    printf("\r\nHandler:Goto Sleep mode\r\n");
    EPD_Sleep();
    DEV_ModuleExit();

    exit(0);
}

int main(void)
{
    DEV_ModuleInit();

    // Exception handling:ctrl + c
    signal(SIGINT, Handler);

    if(EPD_Init() != 0) {
        printf("e-Paper init failed\r\n");
    }
    printf("clear...\r\n");
    EPD_Clear();
    DEV_Delay_ms(500);

    //Create a new image cache
    UBYTE *BlackImage;
    UWORD Imagesize = ((EPD_WIDTH % 8 == 0)? (EPD_WIDTH / 8 ): (EPD_WIDTH / 8 + 1)) * EPD_HEIGHT;
    if((BlackImage = (UBYTE *)malloc(Imagesize)) == NULL) {
        printf("Failed to apply for black memory...\r\n");
        exit(0);
    }
    printf("Paint_NewImage\r\n");
    Paint_NewImage(BlackImage, EPD_WIDTH, EPD_HEIGHT, 0, WHITE);
    Paint_SelectImage(BlackImage);
    Paint_Clear(WHITE);


    // 2.Drawing on the image
    printf("Writing to screen...\r\n");
    Paint_DrawString_EN(10, 20, "Failed to", &Font12, WHITE, BLACK);
	Paint_DrawString_EN(10,34, "	Connect", &Font12, WHITE, BLACK);

	Paint_DrawString_EN(10,64, "Rebooting...", &Font12, WHITE, BLACK);
	
    EPD_Display(BlackImage);
    DEV_Delay_ms(500);


    printf("Goto Sleep mode...\r\n");
    EPD_Sleep();
    free(BlackImage);
    BlackImage = NULL;

    return 0;
}