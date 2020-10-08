/***************************************************
//Web: http://www.buydisplay.com
EastRising Technology Co.,LTD
****************************************************/
#include "ER-EPD026-1B.h"
#include "Debug.h"


/******************************************************************************
function :	Software reset
parameter:
******************************************************************************/
static void EPD_Reset(void)
{
    DEV_Digital_Write(EPD_RST_PIN, 1);
    DEV_Delay_ms(200);
    DEV_Digital_Write(EPD_RST_PIN, 0);
    DEV_Delay_ms(200);
    DEV_Digital_Write(EPD_RST_PIN, 1);
    DEV_Delay_ms(200);
}

/******************************************************************************
function :	send command
parameter:
     Reg : Command register
******************************************************************************/
static void EPD_SendCommand(UBYTE Reg)
{
    DEV_Digital_Write(EPD_DC_PIN, 0);
    DEV_Digital_Write(EPD_CS_PIN, 0);
    DEV_SPI_WriteByte(Reg);
    DEV_Digital_Write(EPD_CS_PIN, 1);
}

/******************************************************************************
function :	send data
parameter:
    Data : Write data
******************************************************************************/
static void EPD_SendData(UBYTE Data)
{
    DEV_Digital_Write(EPD_DC_PIN, 1);
    DEV_Digital_Write(EPD_CS_PIN, 0);
    DEV_SPI_WriteByte(Data);
    DEV_Digital_Write(EPD_CS_PIN, 1);
}

/******************************************************************************
function :	Wait until the busy_pin goes LOW
parameter:
******************************************************************************/
void EPD_WaitUntilIdle(void)
{
  /*
  Debug("e-Paper busy\r\n");
    UBYTE busy;
    do {
        EPD_SendCommand(0x71);
        busy = DEV_Digital_Read(EPD_BUSY_PIN);
        busy =!(busy & 0x01);
    } while(busy);
    DEV_Delay_ms(200);
    Debug("e-Paper busy release\r\n");
 */
    Debug("e-Paper busy\r\n");
    while(DEV_Digital_Read(EPD_BUSY_PIN) == 0) {      //LOW: busy, HIGH: idle
        DEV_Delay_ms(200);
    }
    Debug("e-Paper busy release\r\n");
}


/******************************************************************************
function :	Initialize the e-Paper register
parameter:
******************************************************************************/
UBYTE EPD_Init(void)
{
    EPD_Reset();

    EPD_SendCommand(BOOSTER_SOFT_START);
    EPD_SendData(0x17);
    EPD_SendData(0x17);
    EPD_SendData(0x17);

    EPD_SendCommand(POWER_SETTING);
    EPD_SendData(0x03);
    EPD_SendData(0x00);
    EPD_SendData(0x2B);
    EPD_SendData(0x2B);
    EPD_SendData(0x09);
   
    EPD_SendCommand(POWER_ON);
    EPD_WaitUntilIdle();

    EPD_SendCommand(PANEL_SETTING);
    EPD_SendData(0xDF);

    EPD_SendCommand(TCON_RESOLUTION);
    EPD_SendData(0x98);
    EPD_SendData(0x01);
    EPD_SendData(0x28);
 
    EPD_SendCommand(VCOM_AND_DATA_INTERVAL_SETTING);
    EPD_SendData(0xF7);  

 
    
    return 0;
}

/******************************************************************************
function :	Clear screen
parameter:
******************************************************************************/
void EPD_Clear(void)
{
    UWORD Width, Height,j,i;
    Width = (EPD_WIDTH % 8 == 0)? (EPD_WIDTH / 8 ): (EPD_WIDTH / 8 + 1);
    Height = EPD_HEIGHT;
    
    EPD_SendCommand(DATA_START_TRANSMISSION_1);
    for ( j = 0; j < Height; j++) {
        for ( i = 0; i < Width; i++) {
            EPD_SendData(0XFF);
        }
    }
    
    EPD_SendCommand(DATA_START_TRANSMISSION_2);
    for (j = 0; j < Height; j++) {
        for ( i = 0; i < Width; i++) {
            EPD_SendData(0XFF);
        }
    }
    EPD_SendCommand(DISPLAY_REFRESH);
    EPD_WaitUntilIdle();
}

/******************************************************************************
function :	Sends the image buffer in RAM to e-Paper and displays
parameter:
******************************************************************************/
void EPD_Display(UBYTE *Image)
{
    UWORD Width, Height,j,i;
    Width = (EPD_WIDTH % 8 == 0)? (EPD_WIDTH / 8 ): (EPD_WIDTH / 8 + 1);
    Height = EPD_HEIGHT;
    
    EPD_SendCommand(DATA_START_TRANSMISSION_1);
    for (j = 0; j < Height; j++) {
        for (i = 0; i < Width; i++) {
            EPD_SendData(0XFF);
        }
    }
    
    EPD_SendCommand(DATA_START_TRANSMISSION_2);
    for (j = 0; j < Height; j++) {
        for (i = 0; i < Width; i++) {
            EPD_SendData(Image[i + j * Width]);
        }
    }
    EPD_SendCommand(DISPLAY_REFRESH);
    EPD_WaitUntilIdle();
}

/******************************************************************************
function :	Enter sleep mode
parameter:
******************************************************************************/
void EPD_Sleep(void)
{

    EPD_SendCommand(0X02);  	//power off
    EPD_SendCommand(DEEP_SLEEP );  	//deep sleep
    EPD_SendData(0xA5);
}
