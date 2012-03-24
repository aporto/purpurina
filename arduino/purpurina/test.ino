int pin = 1;
char bits[16];

// Pins used as address lines
#define ADDR_0    2
#define ADDR_1    4
#define ADDR_2    7
#define ADDR_3    8

unsigned char addBit[4] = {0,0,0,0};
int pos = 0;
unsigned char imageLine[32];
unsigned char colorPin[6] = {3,5,6,9,10,11};

void setup() {               
    memset (imageLine, 0, sizeof(imageLine));
    pinMode(ADDR_0, OUTPUT);    
    pinMode(ADDR_1, OUTPUT);    
    pinMode(ADDR_2, OUTPUT);    
    pinMode(ADDR_3, OUTPUT);    
  
    digitalWrite(ADDR_0, LOW);
    digitalWrite(ADDR_0, LOW);
    digitalWrite(ADDR_0, LOW);
    digitalWrite(ADDR_0, LOW);

    Serial.begin(9600);
    
    analogWrite(colorPin[0], 255);
    

}

void getImageLine(void)
{
    unsigned char colorOutput[6] = {0, 0, 0, 0};

    imageLine[0] = 255;
    imageLine[1] = 0;
    imageLine[2] = 0;
    
    imageLine[3] = 0;
    imageLine[4] = 255;
    imageLine[5] = 0;
    
    imageLine[6] = 0;
    imageLine[7] = 0;
    imageLine[8] = 255;
    
    imageLine[9] = 0;    
    imageLine[10] = 255;
    imageLine[11] = 255;
}

void loop() {
    getImageLine();   
    pos++;
    if (pos == 16) { pos = 0; }
    
  unsigned char colorOutput[6] = {0, 0, 0, 0};
  
    unsigned char addrBit[4] = {0, 0, 0, 0};
    addrBit[0] = (pos & 1) == 1;
    addrBit[1] = (pos & 2) == 2;
    addrBit[2] = (pos & 4) == 4;
    addrBit[3] = (pos & 8) == 8;
    digitalWrite(ADDR_0, addrBit[0]);
    digitalWrite(ADDR_1, addrBit[1]);
    digitalWrite(ADDR_2, addrBit[2]);
    digitalWrite(ADDR_3, addrBit[3]);
    
    for (int i=0; i < 6; i++) {
        int color = imageLine[pos];
        analogWrite(colorPin[i], 255 - color);        
    } 
    
    //char txt[100];
   // sprintf(txt, "%d: %d, %d, %d, %d\n", pos, addrBit[0], addrBit[1], addrBit[2], addrBit[3]);
   // Serial.print(txt);
   // delay(1000);
}
