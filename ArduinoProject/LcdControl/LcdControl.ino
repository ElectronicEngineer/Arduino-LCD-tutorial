/*
  Digital Pot Control

  This example controls an Analog Devices AD5206 digital potentiometer.
  The AD5206 has 6 potentiometer channels. Each channel's pins are labeled
  A - connect this to voltage
  W - this is the pot's wiper, which changes when you set it
  B - connect this to ground.

 The AD5206 is SPI-compatible,and to command it, you send two bytes,
 one with the channel number (0 - 5) and one with the resistance value for the
 channel (0 - 255).

 The circuit:
  * All A pins  of AD5206 connected to +5V
  * All B pins of AD5206 connected to ground
  * An LED and a 220-ohm resisor in series connected from each W pin to ground
  * CS - to digital pin 10  (SS pin)
  * SDI - to digital pin 11 (MOSI pin)
  * CLK - to digital pin 13 (SCK pin)

 created 10 Aug 2010
 by Tom Igoe

 Thanks to Heather Dewey-Hagborg for the original tutorial, 2005

*/


// inslude the SPI library:
#include <SPI.h>
#include <LCD12864.h>


// set pin 10 as the slave select for the digital pot:
const int lcd_rs =    10;
const int lcd_reset = 4;
const int lcd_cs1 =   7;

#define IS_COMMAND  LOW
#define IS_DATA     HIGH
#define CHIP_SELECT LOW
#define CHIP_UNSELECT HIGH




void setup() {
  // set the slaveSelectPin as an output:
  pinMode(lcd_rs, OUTPUT);
  pinMode(lcd_reset, OUTPUT);
  pinMode(lcd_cs1, OUTPUT);
  digitalWrite(lcd_reset,HIGH);  
  // initialize SPI:
  SPI.begin();    
  initial_lcd();
  display_bk();
}

void transfer_command_lcd(int data1)
{
  digitalWrite(lcd_cs1,CHIP_SELECT);
  digitalWrite(lcd_rs,IS_COMMAND);
  SPI.transfer(data1);
  digitalWrite(lcd_cs1,CHIP_UNSELECT);
}
void transfer_data_lcd(int data1)
{
  digitalWrite(lcd_cs1,CHIP_SELECT);
  digitalWrite(lcd_rs,IS_DATA);
  SPI.transfer(data1);
  digitalWrite(lcd_cs1,CHIP_UNSELECT);
  
}
void initial_lcd()
{
  digitalWrite(lcd_reset,LOW);
  delay(100);
  digitalWrite(lcd_reset,HIGH);
  delay(100);
  transfer_command_lcd(0xe2); 

  delay(5);
  transfer_command_lcd(0x2c); 
  delay(50);
  transfer_command_lcd(0x2e);
  delay(50);
  transfer_command_lcd(0x2f);
  delay(5);
  transfer_command_lcd(0x23);
  transfer_command_lcd(0x81);
  transfer_command_lcd(0x28);
  transfer_command_lcd(0xa2);
  transfer_command_lcd(0xc8);
  transfer_command_lcd(0xa0);
  transfer_command_lcd(0x40);
  transfer_command_lcd(0xaf);
    
}
void lcd_address(int page,int column)
{
  column=column;
  transfer_command_lcd(0xb0+page); //è®¾ç½®é¡µåœ°å�€ï¼Œ
  transfer_command_lcd(0x10+(column>>4&0x0f)); //è®¾ç½®åˆ—åœ°å�€çš„é«˜4 ä½�
  transfer_command_lcd(column&0x0f); //è®¾ç½®åˆ—åœ°å�€çš„ä½Ž4 ä½�
}
void display_bk()
{
  int i,j;
  //å·¦æ¡†
 for (i =0; i< 8 ; i++)
  for (j = 0; j < 8; j++)
  {
    lcd_address(i,j);
    transfer_data_lcd(0xa0);
   
  }
}
void loop() { 




}

/*void digitalPotWrite(int address, int value) {
  // take the SS pin low to select the chip:
  digitalWrite(slaveSelectPin, LOW);
  //  send in the address and value via SPI:
  SPI.transfer(address);
  SPI.transfer(value);
  // take the SS pin high to de-select the chip:
  digitalWrite(slaveSelectPin, HIGH);
}
*/

