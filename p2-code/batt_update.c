#include <stdio.h>
#include "batt.h"

int set_batt_from_ports(batt_t *batt){
    if(BATT_VOLTAGE_PORT < 0){
        return 1;                                   //  error: invalid negative voltage reading, return 1
    }
    batt->mlvolts = BATT_VOLTAGE_PORT >> 1;         //  mlvolts is initialized to half of the microcontroller reading
    if(batt->mlvolts < 3000){
        batt->percent = 0;                          //  anything less than 3V will not have any battery percentage
    }
    else if((batt->mlvolts - 3000) >> 3 < 100){     //  battery percentage = (mlvolts - 3000) / 8 if less than 100%
        batt->percent = (batt->mlvolts - 3000) >> 3;
    }
    else{
        batt->percent = 100;                        //  maximum battery percentage is 100% regardless of voltage
    }
    if(BATT_STATUS_PORT & 1 << 4){
        batt->mode = 1;                             //  checks 4th bit on BATT_STATUS_PORT, truthy bit turns on percentage mode
    }
    else{
        batt->mode = 2;                             //  checks 4th bit on BATT_STATUS_PORT, falsey bit turns on voltage mode
    }
    return 0;
}

int set_display_from_batt(batt_t batt, int *display){
    int bits = 0;                                   //  bits is the temporary bitstring representation of display
    int digits[10] = {0b0111111, 0b0000110, 0b1011011,
        0b1001111, 0b1100110, 0b1101101, 0b1111101,
        0b0000111, 0b1111111, 0b1101111};           //  digits array of bitstrings for each digit 0-9
    int volts = batt.mlvolts;                       //  local volts variable retrieved from batt struct
    int percent = batt.percent;                     //  local percent variable retrieved from batt struct
    if(percent >= 90) bits |= 0b11111;
    else if(percent >= 70) bits |= 0b1111;
    else if(percent >= 50) bits |= 0b111;           //  if/else if/else uses bitwise or to fill battery meter
    else if(percent >= 30) bits |= 0b11;
    else if(percent >= 5) bits |= 0b1;              //  battery meter works in fifths; >=90 appears full, while <5 appears empty
    bits = bits << 7;                               //  bitwise shift by 7 to first digit on display
    if(batt.mode == 1){                             //  percentage mode on
        int ones = percent % 10;
        percent /= 10;                              //  division operator changes percent variable from ones to tens
        int tens = percent % 10;                    //  modulus operator used frequently to get value in ones place
        percent /= 10;                              //  percent changes to either zero or one, used in conditional on next line
        if(percent != 0) bits |= digits[percent];
        bits = bits << 7;                           //  bitwise shift by 7 to second digit on display
        if(tens != 0 || percent != 0) bits |= digits[tens];
        bits = bits << 7;                           //  bitwise shift by 7 to third digit on display
        bits = (bits | digits[ones]) << 3;          //  all percentages display at least a third digit to the display
        bits |= 0b001;                              //  indices 1 and 2 are falsey in percentage mode, index 0 is truthy 
    }
    if(batt.mode == 2){                             //  voltage mode on
        int thousandths = volts % 10;               //  thousandths are not displayed but used for rounding
        volts /= 10;
        if(thousandths >= 5) volts++;               //  round voltage up by one hundredth if thousandths is >= 5
        int hundredths = volts % 10;                //  modulus and division to retrieve digits as used in percentage mode
        volts /= 10;
        int tenths = volts % 10;                    //  all voltage readings display three digits regardless of value
        volts /= 10;
        bits = (bits | digits[volts]) << 7;         //  bitwise or to update ones value combined with a bitwise shift for next digit
        bits = (bits | digits[tenths]) << 7;        //  bitwise or to update tenths value combined with a bitwise shift for next digit
        bits = (bits | digits[hundredths]) << 3;    //  bitwise or to update hundredths value combined with a bitwise shift of 3
        bits |= 0b110;                              //  indices 1 and 2 are truthy in voltage mode, index 0 is falsey
    }
    *display = bits;                                //  memory address parameter points to the display bitstring representation
    return 0;
}

int batt_update(){
    batt_t batt;                                    //  battery struct initialized
    if(set_batt_from_ports(&batt)){                 //  set instance variables of battery struct
        return 1;                                   //  truthy value returned from set_batt_from_ports; invalid voltage reading
    }
    int display = 0;                                //  initialize display variable to zero
    set_display_from_batt(batt, &display);          //  pass in display pointer and battery struct to set_display_from_batt
    BATT_DISPLAY_PORT = display;                    //  global variable on microcontroller set to bitstring representation
    return 0;                                       //  return 0 when no errors occur
}