/*******************************************************************************************

Purpurina code
Author: Alex Rocha Porto

Info: This is the main code for Purpurina, a light-painting device created by Alex Porto
for an event called Virada Hacker (Hacker Overnight) in Garoa Hackerspace, Sao Paulo, Brazil

Purpurina is intended to be a cheap and easy-to-reproduce device, so it only uses 3 
electronic components. The PCBs can be easily made using the "laser printer technique"

For more info, check http://dalpix.com/purpurina

Instructions: 
- This code needs the file "purpurina_image.h" to compile. 
- "purpurina_image.h" is automatically generated at htpp://dalpix.com/purpurina or 
  using the html file included in source-code
- Use your image on the address above to generate the file "purpurina_image.h", add its
  content to this sketch and program it on your Arduino
- Make sure your Purpurina set is working
- Enjoy your pictures

History: 
2012-05-06: Started controlling changes history
 - Added color compression: Expanded image maximum size to about 48000
   pixels (aprox. 160 x 300)

*******************************************************************************************/

#include <avr/pgmspace.h>
#include "purpurina_image.h"

// Pins used as address lines
#define ADDR_0                13 //7
#define ADDR_1                12 //8
#define ADDR_2                8 //12
#define ADDR_3                7 //13

// Pins used as module selector
#define MODULE_0              6
#define MODULE_1              5
#define MODULE_2              4
#define MODULE_3              3

// Pins used as command input
#define CMD_CALIBRATE        A0
#define CMD_START            A1
#define CMD_BRIGHTNESS       A3
#define MOD_SELECTOR_ENABLE  2  

// States of the main loop
#define STATE_NONE           0
#define STATE_TEST           1
#define STATE_PRINTING       2
#define STATE_CALIBRATING    3

#define MAX_LINE_SIZE    768 /* 16 pixels * 16 modules * 3 bytes per pixels = 768 */
unsigned char img_line[MAX_LINE_SIZE];
unsigned char color_pins[3] = {
  11, 10, 9};
unsigned int current_line = 0;
unsigned int data_idx = 0;
bool button1[2];
bool button2[2];
unsigned char state = STATE_NONE;
unsigned long time1;
unsigned long calib_time = 9000000;
unsigned int test_counter = 0;
unsigned int brightness;

const unsigned char compressed_colors[8][3] = {
         {0x00, 0x00, 0x00}, // black
         {0xFF, 0x00, 0x00}, // red
         {0x00, 0xFF, 0x00}, // green
         {0x00, 0x00, 0xFF}, // blue
         {0xFF, 0xFF, 0x00}, // yellow
         {0xFF, 0x00, 0xFF}, // magenta
         {0x00, 0xFF, 0xFF}, // cyan
         {0xFF, 0xFF, 0xFF} // white
};

//******************************************************************************

void getImageLine(unsigned int line);
void clearLeds(void);

//******************************************************************************

//bool p = true;

void setup() {               
  pinMode(ADDR_0, OUTPUT); 
  pinMode(ADDR_1, OUTPUT);    
  pinMode(ADDR_2, OUTPUT);    
  pinMode(ADDR_3, OUTPUT);    
  digitalWrite(ADDR_0, LOW);
  digitalWrite(ADDR_1, LOW);
  digitalWrite(ADDR_2, LOW);
  digitalWrite(ADDR_3, LOW);

  pinMode(MODULE_0, OUTPUT); 
  pinMode(MODULE_1, OUTPUT);    
  pinMode(MODULE_2, OUTPUT);    
  pinMode(MODULE_3, OUTPUT);    
  digitalWrite(MODULE_0, LOW);
  digitalWrite(MODULE_1, LOW);
  digitalWrite(MODULE_2, LOW);
  digitalWrite(MODULE_3, LOW);

  pinMode(MOD_SELECTOR_ENABLE, OUTPUT);    
  digitalWrite(MOD_SELECTOR_ENABLE, LOW); 

  for (unsigned int i=0; i < 3; i++) {
    pinMode(color_pins[i], OUTPUT);    
  }

  clearLeds();

  Serial.begin(9600);
  
  memset(img_line, 0, MAX_LINE_SIZE);
  getImageLine(0);

  memset(button1, 0, sizeof(button1));
  memset(button2, 0, sizeof(button2));
}

//******************************************************************************

void writeColorValue(unsigned char pin, unsigned char value)
{
  value = value;
  if (INVERT_DATA) {      
    analogWrite(color_pins[pin], 255 - value);
  } 
  else {
    analogWrite(color_pins[pin], value);
  }
}

//******************************************************************************

void getImageLine(unsigned int line)
{
    unsigned int idx = 0;
    for (unsigned int i=0; i < LINE_SIZE; i++) {        
        unsigned char compressed = pgm_read_byte_near(img_data + line * (LINE_SIZE) + i);
        unsigned char c1 = compressed & 0xF;
        unsigned char c2 = (compressed & 0xF0) >> 4;      

        if (c1 > 7) c1 = 0;
        if (c2 > 7) c2 = 0;
        
        /*Serial.print(i);
        Serial.print("=");
        Serial.print(compressed);
        Serial.print(" :: ");
        Serial.print(c1);
        Serial.print(",");
        Serial.println(c2);
        */
        
        for (unsigned ci=0; ci < 3; ci++) {
            img_line[idx + ci] = compressed_colors[c1][ci];
            img_line[idx + ci + 3] = compressed_colors[c2][ci];
        }
        idx += 6; // get 2 RGB colors each time, so we jump 6 bytes on each iteraction
        //img_line[i] =  pgm_read_byte_near(img_data + line * (LINE_SIZE) + i); 
    }
  
//    char str[100];
//  sprintf(str, "%d: %d, %d, %d, %d, %d, %d\n", line, img_line[0], img_line[1], img_line[2], img_line[3], img_line[4], img_line[5]);
//  Serial.print(str);      
}

//******************************************************************************

void setMuxAddress(unsigned char addr) 
{
  unsigned char addr_bit[4] = {
    0, 0, 0, 0  };
  addr_bit[0] = (addr & 1) == 1;
  addr_bit[1] = (addr & 2) == 2;
  addr_bit[2] = (addr & 4) == 4;
  addr_bit[3] = (addr & 8) == 8;

  digitalWrite(ADDR_0, addr_bit[0]);
  digitalWrite(ADDR_1, addr_bit[1]);
  digitalWrite(ADDR_2, addr_bit[2]);
  digitalWrite(ADDR_3, addr_bit[3]);
}

//******************************************************************************

void selectModule(unsigned char id) 
{
  unsigned char addr_bit[4] = {
    0, 0, 0, 0  };
  addr_bit[0] = (id & 1) == 1;
  addr_bit[1] = (id & 2) == 2;
  addr_bit[2] = (id & 4) == 4;
  addr_bit[3] = (id & 8) == 8;

  digitalWrite(MODULE_0, addr_bit[0]);
  digitalWrite(MODULE_1, addr_bit[1]);
  digitalWrite(MODULE_2, addr_bit[2]);
  digitalWrite(MODULE_3, addr_bit[3]);
}

//******************************************************************************

void clearLeds(void)
{
  for (unsigned char i=0; i < 3; i++) {
    writeColorValue(i, 0);    
  }
}

//******************************************************************************

void modePrintImage(void)
{
    for (unsigned int mod = 0; mod < 16; mod++) {
        clearLeds();
        delayMicroseconds(1);
        selectModule(mod);    
        for (unsigned int line = 0; line < 16; line++) {
            clearLeds();
            setMuxAddress(line);
            for (unsigned char c=0; c < 3; c++) {
                unsigned int ptr = line + c * 16  + 48 * mod;
                writeColorValue(c, img_line[ptr]);    
                //char str[100];
                //sprintf(str, "%d: %d = %d / %d", mod, line, ptr, img_line[ptr]);
                //Serial.println(str);                
            }
            //delay(1);                
            delayMicroseconds(1);
        }
    }
    
/*  // Blank all other leds before setting the current led color.
  setMuxAddress(current_line);
  unsigned char mod_count = 2;
  for (unsigned char mod=0; mod < mod_count; mod++) {    
    clearLeds();
    selectModule(mod);    
    delayMicroseconds(1) ;
    
    for (unsigned char i=0; i < 3; i++) {
      unsigned int ptr = current_line + i * 16  + 48 * mod;
      writeColorValue(i, img_line[ptr]);    
      char str[100];
      sprintf(str, "%d: %d = %d / %d", current_line, mod, ptr, img_line[ptr]);
  //    Serial.println(str);
    }    
    //Serial.println(" ");
    // Force Arduino to wait until the muxes finish their switching (rising time, etc)
    // This will avoid color "leaking" to nearby pixels/leds
    delayMicroseconds(1) ;
  }

  current_line++;
  if (current_line >= 16) {
    current_line = 0;
    //delay(10000);
  }
  */
  
  
  
  // Blank all other leds before setting the current led color.
  /*clearLeds();
   setMuxAddress(current_line);
   selectModule(0);
   
   for (unsigned char i=0; i < 3; i++) {
   unsigned int ptr = current_line + i * 16;
   writeColorValue(i, img_line[ptr]);    
   }    
   // Force Arduino to wait until the muxes finish their switching (rising time, etc)
   // This will avoid color "leaking" to nearby pixels/leds
   delayMicroseconds(1) ;
   
   current_line++;
   if (current_line >= 16) {
   current_line = 0;
   }*/
}

//******************************************************************************

void goNextLine(void)
{  
  if (data_idx < NUM_COLS - 1) {
    data_idx++;
    current_line = 0;
    getImageLine(data_idx);        
  } 
  else {
    if (STEP_BY_STEP_OH_BABY) {
      data_idx = 0;
      current_line = 0;
      getImageLine(data_idx);
    } 
    else {
      state = STATE_NONE; 
      analogWrite(13, 128);
      clearLeds();
    }
  }
}

//******************************************************************************

void runTestFrame(void)
{  
  unsigned char value;        
  for (unsigned int repeat=0; repeat < 40; repeat++) {
    for (unsigned char mod=0; mod < 16; mod++) {      
      selectModule(mod);              
      for (unsigned int addr=0; addr<16; addr++) {                  
        clearLeds();
        setMuxAddress(addr);
        for (unsigned char ci=0; ci < 3; ci++) {
          if ((addr + ci) % 3 == test_counter) {
            value = 50;
          } 
          else {
            value = 0;
          }
          writeColorValue(ci, value);  
        }
        delayMicroseconds(1) ; 
      }
    }
  }

  test_counter++;
  if (test_counter == 3) {
    test_counter = 0;
  }    

}

//******************************************************************************

void loop() { 
/*   selectModule(0);              
   setMuxAddress(2);
    for (unsigned char ci=0; ci < 3; ci++) {
       writeColorValue(ci, 100);
    }  

}  
*/

  button1[0] = analogRead(CMD_CALIBRATE) > 512;
  button2[0] = analogRead(CMD_START) > 512;
  //brightness = constrain(analogRead(CMD_BRIGHTNESS) / 4 - 220, 0, 20);
  
  if (button1[0] && button2[0]) {
    state = STATE_TEST;
  } 
  else {
    if (button2[0] && (button2[0] != button2[1])) {
      state = STATE_CALIBRATING;
      time1 = micros();
      analogWrite(13, 255);
      Serial.println("Start calibrating");
    }    
    if (!button2[0] && (button2[0] != button2[1])) {
      state = STATE_NONE;
      unsigned long c = micros() - time1;
      if (c > 1000000) {
        calib_time = c;
      }
      analogWrite(13, 0);
      Serial.print("End calibrating: ");
      Serial.print(float(calib_time) / 1000.0);
      Serial.println(" [ms]");
    }
    if (button1[0] && (button1[0] != button1[1])) {
      state = STATE_PRINTING;        
      analogWrite(13, 0);        
      if (STEP_BY_STEP_OH_BABY) {
        goNextLine();
      } 
      else {
        data_idx = 0;
        time1 = micros();
      }
    }
    if (button1[1] && (button1[0] != button1[1])) {
      if (STEP_BY_STEP_OH_BABY == 0) {
        state = STATE_NONE;   
        analogWrite(13, 0);
      }
    }        
  }
  
 //  state = STATE_TEST;

  button1[1] = button1[0];
  button2[1] = button2[0];

  if (state == STATE_PRINTING) {
    modePrintImage();
    if (STEP_BY_STEP_OH_BABY == 0) {
      if (micros() - time1 > calib_time / (NUM_COLS)) {            
        goNextLine();                
        time1 = micros();
      }            
    }        
  } 
  else {
    if (state == STATE_CALIBRATING) {
    } 
    else {
      if (state == STATE_TEST) {
        runTestFrame();
      } 
      else {
        test_counter = 0;
        clearLeds();            
      }
    }          
  }   
}

//******************************************************************************


