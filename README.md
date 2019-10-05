# Programmable Airsoft Trigger - an STM32F030C8T6 based project
## Short Brief
Programmable Airsoft Trigger - designed to replace traditional electromechanical switch present in airsoft replica to control gearbox opeartion.
## Project's status:
**In development**
### List of things left to do:
* Implement fire selector switch ,,on fly" programming, to let user decide burst cycles, semi only etc.
* An OLED I2C display to show the player how many shots were shot
* Minor hardware update
## The Problem
As the usual circuitry closes and lets the current flow, just a moment before contacts meet each other a spark is present between these contacts.
After a longer usage it leads to oxydation of metal and creating a layer of carbon, which leads to higher resistance, therefore heat is generated and switch gets damaged.
Here's some quick maths:

For an `11,1V` LiPo battery with `20C/40C` at burst and at `t=0` a DC motor acts as a short circuit, thus resulting in a full current burst from the battery, 
which is roughly **30A** at `t=0`. Following this thinking, let's say the resistance of a damaged trigger switch is 1 Ohm - that's not really that much, huh?

Power dissipated on contacts may be calulated with a simple equation: `R * I^2` . As the current is squared, it's easily seen how dramatically power raises to 900W ! If it would work for a couple of seconds, the airsoft replica would be like a portable microwave :)
## The Solution
A transistor has been used as a switch ever since it has been developed. If we consider large currents like in this application, a field transistor suits our needs.
A P-channel MOSFET transistor STL42P6LLF6 has it's drain-source resistance at typically 0,023 Ohm, so for a moment maximal power dissipated on a junction is less then 21W.
## Technologies used
For this project following technologies, programs and hardware were used:
* C (embedded C11)
* Altium Designer 18.1.7
* Eclipse IDE with GCC compiler
* ST-Link V2.1 programmer/debugger
* STM32F030C8T6 ARM architecture based microcontroller
* Custom hardware
## Setup
### Software Setup
This project was designed to be out-ouf-package ready to work with, no software setup is needed.
### Memory Flashing
Use SWD connector presented onboard to flash the board with an external ST-Link programmer. Pinouts are available in this repository. Next, connect your hardware programmer and flash the `.elf` file (how to do that depends on IDE or software flashing software used - please refer to tutarials specific to your setup)
## Inspiration
As an airsoft player I found it frustrating to fight with my own setup in a longer game as my battery would eventually die after a couple of magazines shot. Also, trigger response wasn't acceptable.
Inspired by airsoft forums I decided to use an N-MOSFET as a switch. Results were fascinating, as my battery life doubled, and trigger felt gentle as a feather.
Later I found out that there were commercial programable triggers that had fancy funcionality like 3-shot bursts, low battery warnings etc.
I bought one eventually, but I couldn't see why these cost about 100 euros (there are even 180 euros price tag ones). Then I got an idea - why can't I make one by myself?
After a couple of years I learned more and more about hardware design, started studying at technical university and got into C coding. It was about that time I decided to give that project a try.
Books I always find usefull:
* Tomasz Francuz ,,C language for AVR microcontrollers"
* Robert C. Martin ,,Clean Code"
* James Grenning ,,Test-Driven Development for Embedded C"
## Contact
Created by Paweł Klisz @ pawelochojec@gmail.com- feel free to contact me!
