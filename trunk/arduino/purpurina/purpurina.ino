
#include <avr/pgmspace.h>
#include "purpurina_image.h"

// Pins used as address lines
#define ADDR_0                7
#define ADDR_1                8
#define ADDR_2                12
#define ADDR_3                13

// Pins used as command input
#define CMD_CALIBRATE        A0
#define CMD_START            A1

// States of the main loop
#define STATE_NONE           0
#define STATE_PRINTING       1
#define STATE_CALIBRATING    2

bool p = true;

unsigned char img_line[LINE_SIZE];
unsigned char color_pins[6] = {9, 10, 11, 3, 5, 6};
unsigned int current_line = 0;
unsigned int data_idx = 0;
bool button1[2];
bool button2[2];
unsigned char state = STATE_NONE;
unsigned long time1;
unsigned long calibTime = 9000000;

//******************************************************************************

void getImageLine(unsigned int line);
void clearLeds(void);

//******************************************************************************

//bool p = true;

void setup() {               
    //memset (imageLine, 0, sizeof(imageLine));
    pinMode(ADDR_0, OUTPUT); 
    pinMode(ADDR_1, OUTPUT);    
    pinMode(ADDR_2, OUTPUT);    
    pinMode(ADDR_3, OUTPUT);    
  
    digitalWrite(ADDR_0, LOW);
    digitalWrite(ADDR_0, LOW);
    digitalWrite(ADDR_0, LOW);
    digitalWrite(ADDR_0, LOW);
    
    for (unsigned int i=0; i < 6; i++) {
        pinMode(color_pins[i], OUTPUT);    
    }
    
    clearLeds();

    Serial.begin(9600);
    
    getImageLine(0);
    
    memset(button1, 0, sizeof(button1));
    memset(button2, 0, sizeof(button2));
}

//******************************************************************************

void writeColorValue(unsigned char pin, unsigned char value)
{
    if (INVERT_DATA) {      
        analogWrite(color_pins[pin], 255 - value);
        /*if (value > 0) {
            digitalWrite(color_pins[pin], LOW);
            //if (p && (pin == 0)) Serial.println("0");
        } else {
            digitalWrite(color_pins[pin], HIGH);
            //if (p && (pin == 0)) Serial.println("1");
        }*/
    } else {
        analogWrite(color_pins[pin], value);
    }
}

//******************************************************************************

void getImageLine(unsigned int line)
{
    for (unsigned int i=0; i < LINE_SIZE; i++) {        
        img_line[i] =  pgm_read_byte_near(img_data + line * (LINE_SIZE) + i); 
    }
}
 
//******************************************************************************
 
 void setMuxAddress(unsigned char addr) {
    unsigned char addr_bit[4] = {0, 0, 0, 0};
    addr_bit[0] = (addr & 1) == 1;
    addr_bit[1] = (addr & 2) == 2;
    addr_bit[2] = (addr & 4) == 4;
    addr_bit[3] = (addr & 8) == 8;

    digitalWrite(ADDR_0, addr_bit[0]);
    digitalWrite(ADDR_1, addr_bit[1]);
    digitalWrite(ADDR_2, addr_bit[2]);
    digitalWrite(ADDR_3, addr_bit[3]);
    
    //unsigned int c = addr;
    //if (p) {Serial.print(c, DEC); Serial.print(":");}

//    char txt[100];
//    sprintf(txt, "addr %d, %d, %d, %d\n", addr_bit[3], addr_bit[2], addr_bit[1], addr_bit[0]);
  //  Serial.print(txt);
}

//******************************************************************************

void clearLeds(void)
{
    for (unsigned char i=0; i < 6; i++) {
        writeColorValue(i, 0);    
    }
}

//******************************************************************************

void modePrintImage(void)
{
    // Blank all other leds before setting the current led color.
    clearLeds();
    setMuxAddress(current_line);
    
    for (unsigned char i=0; i < 6; i++) {
        unsigned int ptr = current_line + i * 16;
        writeColorValue(i, img_line[ptr]);    
      //  if (p) { Serial.print(i);Serial.print("=");Serial.println(ptr);}
        //writeColorValue(i, 128);
    }    
    // Force Arduino to wait until the muxes finish their switching (rising time, etc)
    // This will avoid color "leaking" to nearby pixels/leds
    delayMicroseconds(1) ;
    
    current_line++;
    if (current_line >= 16) {
        current_line = 0;
        //if (p) {Serial.println("*");}
        p = false;        
    }
}

//******************************************************************************

void goNextLine(void)
{
    p = true;
    if (data_idx < NUM_COLS - 1) {
        data_idx++;
        current_line = 0;
        getImageLine(data_idx);        
    } else {
        if (STEP_BY_STEP_OH_BABY) {
            data_idx = 0;
            current_line = 0;
            getImageLine(data_idx);
        } else {
            state = STATE_NONE; 
            analogWrite(13, 128);
            clearLeds();
        }
    }
}

//******************************************************************************

void loop() {  
    button1[0] = analogRead(A0) > 512;
    button2[0] = analogRead(A1) > 512;
    if (button2[0] && (button2[0] != button2[1])) {
        state = STATE_CALIBRATING;
        time1 = micros();
        analogWrite(13, 255);
    //    Serial.println("start calib");
    }    
    if (!button2[0] && (button2[0] != button2[1])) {
        state = STATE_NONE;
        //time2 = micros();
        unsigned long c = micros() - time1;
        if (c > 1000000) {
            calibTime = c;
        }
        analogWrite(13, 0);
//        Serial.print("end calib ");
  //      Serial.println(movementTotalCounter);
    }
    if (button1[0] && (button1[0] != button1[1])) {
        state = STATE_PRINTING;        
        analogWrite(13, 0);        
        if (STEP_BY_STEP_OH_BABY) {
            goNextLine();
        } else {
            data_idx = 0;
            time1 = micros();
        }
      //  Serial.println("start");
    }
    if (button1[1] && (button1[0] != button1[1])) {
        if (STEP_BY_STEP_OH_BABY == 0) {
            state = STATE_NONE;   
            analogWrite(13, 0);
        }
//      Serial.println("end");  
    }
    button1[1] = button1[0];
    button2[1] = button2[0];
    
    if (state == STATE_PRINTING) {
        modePrintImage();
        if (STEP_BY_STEP_OH_BABY == 0) {
            if (micros() - time1 > calibTime / (NUM_COLS)) {            
                goNextLine();                
                time1 = micros();
            }            
        }        
    } else {
        if (state != STATE_CALIBRATING) {
          clearLeds();            
       }
   }
}

//******************************************************************************
// Begin of data created via automated code generation
// End of data created via automated code generation

/*  1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,
  1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,
  1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,
  1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,
  1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,
  1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,
  */
  
//******************************************************************************

