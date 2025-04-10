# SPI Controller in VHDL

## Description

This is a repository that contains complete working SPI Controllers 
described in VHDL. The first one is an SPI Master and the second is
an SPI Slave. 

![photo1 overall design](images/spi_slave_in_fpga.jpg)

Each of these two SPI controllers have been tested. Each of the two tests
involve two main components: (1) an FPGA board; I used DE1-SoC board
and (2) a microcontroller board; I used an Arduino Uno. Here, you
all files needed to replicate the two tests that verify the correct
operation of teh two SPI controllers.
Complete Quartus II projects are provided in subfolders called "fpga".
Complete Arduino sketches are located in subfolders called "arduino",
for each test circuit.
You will also find folders called "docs" that include concise descriptions
of teh two tests and diagrams that show the connections you need to make 
between the FPGA board and the Arduino Uno board.

## Video description

A short video description can be found on my youtube channel.

https://www.youtube.com/@eigenpi

## Credits

The SPI Controller Master is adapted from the wonderful book of Pong P. Chu
(I highly reccommend reading the book for further details):
[1] Pong P. Chu, FPGA Prototyping by VHDL Examples: Xilinx MicroBlaze 
    MCS SoC, Wiley, 2nd edition, October 23, 2017.
