
// Pins used as address lines
#define ADDR_0                7
#define ADDR_1                8
#define ADDR_2                12
#define ADDR_3                13

// Pins used as data output
//#define PIN_0                9
//#define PIN_1                10
//#define PIN_2                11
//#define PIN_3                3
//#define PIN_4                5
//#define PIN_5                6

// Pins used as command input
#define CMD_CALIBRATE        A0
#define CMD_START            A1

//******************************************************************************
// Begin of data created via automated code generation

#define INVERT_DATA           1
#define NUM_LINES             32
#define NUM_COLS              6
#define NUM_PIXELS            576
unsigned char img_data[NUM_PIXELS] = {
/*  1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,
  1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,
  1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,
  1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,
  1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,
  1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,
  */
255,0,0 ,0,255,0 ,0,0,255 ,255,0,0 ,0,255,0 ,0,0,255 ,255,0,0 ,0,255,0 ,0,0,255 ,255,0,0 ,0,255,0 ,0,0,255 ,255,0,0 ,0,255,0 ,0,0,255 ,255,0,0 ,0,255,0 ,0,0,255 ,255,0,0 ,0,255,0 ,0,0,255 ,255,0,0 ,0,255,0 ,0,0,255 ,255,0,0 ,0,255,0 ,0,0,255 ,255,0,0 ,0,255,0 ,0,0,255 ,255,0,0 ,0,255,0 
//015,015,0 ,0,015,015 ,015,0,015 ,255,0,0 ,0,255,0 ,0,0,255 ,255,0,0 ,0,255,0 ,0,0,255 ,255,0,0 ,0,255,0 ,0,0,255 ,255,0,0 ,0,255,0 ,0,0,255 ,255,0,0 ,0,255,0 ,0,0,255 ,255,0,0 ,0,255,0 ,0,0,255 ,255,0,0 ,0,255,0 ,0,0,255 ,255,0,0 ,0,255,0 ,0,0,255 ,255,0,0 ,0,255,0 ,0,0,255 ,255,0,0 ,0,255,0 
    ,0,0,255 ,255,0,0 ,0,255,0 ,0,0,255 ,255,0,0 ,0,255,0 ,0,0,255 ,255,0,0 ,0,255,0 ,0,0,255 ,255,0,0 ,0,255,0 ,0,0,255 ,255,0,0 ,0,255,0 ,0,0,255 ,255,0,0 ,0,255,0 ,0,0,255 ,255,0,0 ,0,255,0 ,0,0,255 ,255,0,0 ,0,255,0 ,0,0,255 ,255,0,0 ,0,255,0 ,0,0,255 ,255,0,0 ,0,255,0 ,0,0,255 ,255,0,0 
    ,0,255,0 ,0,0,255 ,255,0,0 ,0,255,0 ,0,0,255 ,255,0,0 ,0,255,0 ,0,0,255 ,255,0,0 ,0,255,0 ,0,0,255 ,255,0,0 ,0,255,0 ,0,0,255 ,255,0,0 ,0,255,0 ,0,0,255 ,255,0,0 ,0,255,0 ,0,0,255 ,255,0,0 ,0,255,0 ,0,0,255 ,255,0,0 ,0,255,0 ,0,0,255 ,255,0,0 ,0,255,0 ,0,0,255 ,255,0,0 ,0,255,0 ,0,0,255 
    ,255,255,0 ,255,255,0 ,255,255,0 ,255,255,0 ,255,255,0 ,255,255,0 ,255,255,0 ,255,255,0 ,255,255,0 ,255,255,0 ,255,255,0 ,255,255,0 ,255,255,0 ,255,255,0 ,255,255,0 ,255,255,0 ,255,255,0 ,255,255,0 ,255,255,0 ,255,255,0 ,255,255,0 ,255,255,0 ,255,255,0 ,255,255,0 ,255,255,0 ,255,255,0 ,255,255,0 ,255,255,0 ,255,255,0 ,255,255,0 ,255,255,0 ,255,255,0 
    ,0,255,255 ,0,255,255 ,0,255,255 ,0,255,255 ,0,255,255 ,0,255,255 ,0,255,255 ,0,255,255 ,0,255,255 ,0,255,255 ,0,255,255 ,0,255,255 ,0,255,255 ,0,255,255 ,0,255,255 ,0,255,255 ,0,255,255 ,0,255,255 ,0,255,255 ,0,255,255 ,0,255,255 ,0,255,255 ,0,255,255 ,0,255,255 ,0,255,255 ,0,255,255 ,0,255,255 ,0,255,255 ,0,255,255 ,0,255,255 ,0,255,255 ,0,255,255 
    ,255,0,255 ,255,0,255 ,255,0,255 ,255,0,255 ,255,0,255 ,255,0,255 ,255,0,255 ,255,0,255 ,255,0,255 ,255,0,255 ,255,0,255 ,255,0,255 ,255,0,255 ,255,0,255 ,255,0,255 ,255,0,255 ,255,0,255 ,255,0,255 ,255,0,255 ,255,0,255 ,255,0,255 ,255,0,255 ,255,0,255 ,255,0,255 ,255,0,255 ,255,0,255 ,255,0,255 ,255,0,255 ,255,0,255 ,255,0,255 ,255,0,255 ,255,0,255 
    };

// End of data created via automated code generation

/*  1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,
  1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,
  1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,
  1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,
  1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,
  1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,
  */
  
//******************************************************************************

//unsigned char color_pins[6] = {3, 5, 6, 9, 10, 11};
unsigned char color_pins[6] = {9, 10, 11, 3, 5, 6};
int current_line = 0;
int data_idx = 0;

//******************************************************************************

void writeColorValue(unsigned char pin, unsigned char value)
{
    if (INVERT_DATA) {
        analogWrite(color_pins[pin], 255 - value);
        //char txt[100];
      //  sprintf(txt, "aw (%d, %d)\n", color_pins[pin], value);
        //Serial.print(txt);
    } else {
        analogWrite(color_pins[pin], value);
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

  //  char txt[100];
//    sprintf(txt, "addr %d, %d, %d, %d\n", addr_bit[3], addr_bit[2], addr_bit[1], addr_bit[0]);
  //  Serial.print(txt);
}

//******************************************************************************

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
    
    for (int i=0; i < 6; i++) {
        writeColorValue(0, 0);
    }

    Serial.begin(9600);
    
    //analogWrite(colorPin[0], 255);
}

//******************************************************************************

bool b1 = false;

void loop() {  
    //Serial.println(current_line);
    setMuxAddress(current_line);

    for (unsigned char i=0; i < 6; i++) {
        writeColorValue(i, img_data[data_idx * (NUM_LINES)  + current_line + i * 16]);    
        //writeColorValue(i, 128);
    }    
    
    current_line++;
    if (current_line >= 16) {
        current_line = 0;
    }
    
    int t = analogRead(A0);
    bool b = t < 512;
    
    if ((b1 == true) && (b == false)) {
        Serial.println("Apertou");
        data_idx++;
        if (data_idx == NUM_COLS) {
            data_idx = 0;
        }
    }
    
    b1 = b;
 //   delay(4000);
  //  Serial.println("----------------");
    //Serial.println(" ");
}