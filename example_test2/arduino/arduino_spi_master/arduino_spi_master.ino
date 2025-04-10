// cristinel ababei
//
// this is a sketch to have an Arduino Uno board use its SPI as Master;
// SPI Master sends data item 0x1234 to SPI Slave;
// the SPI Slave is inside the FPGA on the DE1-SoC board;
//
// credit:
// https://forum.arduino.cc/t/spi-slave-mode-example-code/66617/5
//
///////////////////////////////////////////////////////////////////////////////
// 
// inclusion of SPI library and the call to SPI.begin() will have as effect:
//
// (1) DPin-10 takes over the symbolic name SS (Slave Select) and gets configures 
//   as output line with value logic-high; to select the Slave, the Master must 
//   assert logic-low (LL) on the SS/-pin;
//
//(2) DPin-11 takes over the symbolic name MOSI (Master Out Slave In) and gets 
//   configured as output line with value logic-low;
//
// (3) DPin-12 takes over the symbolic name MISO (Master In Slave Out) and gets 
//   configured as input line.
//
// (4) DPin-13 takes over the symbolic name SCK (Serial Clock) configured as 
//   output line with value logic-low (Mode-1 operation: CPOL = LOW, CPHA = FALLING).
//
// (5) The default data transfer speed is 4 MBits/sec; the speed can be changed 
// using this code: SPI.setClockDivider();

#include<SPI.h>

unsigned short x = 0x8F33; // a random number;

///////////////////////////////////////////////////////////////////////////////
// 
// setup
//
///////////////////////////////////////////////////////////////////////////////

void setup()
{
  Serial.begin(115200);
  SPI.begin();
  // NOTE: we can configure the bit rate (i.e., sclk) by using setClockDivider(),
  // to divide the Arduino's clock (16 MHz on most Arduinos) down to a frequency 
  // between 8 MHz (/2) and 125 kHz (/128);
  // for example, dividing by 128 gives us the slowest bit rate = 16 MHz/128 = 125 kbit/sec;
  SPI.setClockDivider(SPI_CLOCK_DIV128);
  // set mode of operation as Mode 0, because that is how I set
  // set it also inside the SPI Slave inside the FPGA;
  SPI.setBitOrder(MSBFIRST); 
  SPI.setDataMode(SPI_MODE0);
  // start with slave select signal high, i.e., slave unselected; 
  // it will be set low/high right before/after each transaction later;
  digitalWrite(SS, HIGH);
}

///////////////////////////////////////////////////////////////////////////////
// 
// main
//
///////////////////////////////////////////////////////////////////////////////

void loop()
{
  // NOTE: I confirmed with the scope that I Do Need to pull down and then
  // back up the SS signal; otherwise, SS stays high and the SPI Slave
  // on FPGA will not read anything; also, noticed that SPI.beginTransaction()
  // and SPI.endTransaction() will not do that; that is why, I use 
  // digitalWrite(SS, LOW/HIGH) before and after each transfer;
  digitalWrite(SS, LOW);
  byte returned_byte = SPI.transfer(highByte(x));
  digitalWrite(SS, HIGH);
  // print what we sent and what was returned at the same time;
  Serial.print(highByte(x), HEX);
  Serial.print(" ");
  Serial.print(returned_byte, HEX);
  Serial.println(" ");
  delay(10);

  // digitalWrite(SS, LOW);
  // returned_byte = SPI.transfer(lowByte(x));
  // digitalWrite(SS, HIGH);
  // // print what we sent and what was returned at the same time;
  // Serial.print(lowByte(x), HEX);
  // Serial.print(" ");
  // Serial.print(returned_byte, HEX);
  // Serial.println(" ");
  // delay(20);
}