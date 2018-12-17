
int STR = 10;
int DATA = 11;
int CLK = 12;

int a = 0x00; // firts byte  00000000
int b = 0x00; // second byte 00000000

void setup() {
  //set pins to output because they are addressed in the main loop
  pinMode(STR, OUTPUT);
  pinMode(CLK, OUTPUT);
  pinMode(DATA, OUTPUT);
}

void Output(int, int);
void Output_Byte(int, int);

void loop() {

  Output(1, HIGH);
  delay(100);
  Output(1, LOW);
  delay(100);
  
}

void Output(int pin,int std){

  int i = 0;
  for(int p = 0; p <= 7; p++){
    if(pin == p){
      if(std == 1){a = a | (1 << p);}
      if(std == 0){a = a ^ (1 << p);}    
    }
  }
  
  for(int s = 8; s <= 15 ; s++){
    if(pin == s){
      if(std == 1){b = b | (1 << i);}
      if(std == 0){b = b ^ (1 << i);}
    }    
    i++;
  }
  Output_Byte(a, b);
  
}

void Output_Byte(int a, int b){
    digitalWrite(STR, LOW);
    shiftOut(DATA, CLK, MSBFIRST, b);
    shiftOut(DATA, CLK, MSBFIRST, a);  
    digitalWrite(STR, HIGH);
}
