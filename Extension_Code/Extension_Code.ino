
/*<------------------------------ - Arduino_Extension.h - -----------------------------
 
  Librería que permite expandir la candidad de pines de entrada y salida que se disponen 
  en el Arduino, utiliza CI CD4094 y CD4021. Esta versión solo está habilitada para dos
  CD4094 y dos CD4021, por lo tanto 16 nuevos pines de entrada y 16 nuevos de salida.

  *Los dos CD4094 brindan 16 pines de salida nuevos, que van del 0 al 15.
     Ejemplo:
       newOut(3, HIGH); //Pone el pin Q4 del primer CD4094 en <<HIGH>> 

  Creado por: German A. Ureña Araya, 17 diciembre 2018
  Liberado para el dominio público.
  
---------------------------------------------------------------- Versión 1 --------->*/


int STR = 10;       // Pin 10 del Arduino conectado a los pines <<STROBE>> de los CD4094
int DATA_OUT = 11;  // Pin 11 del Arduino conectado al pin <<DATA>> del primer CD4094
int CLK = 12;       // Pin 12 del Arduino conectado a los pines de <<CLOCK>> de ambos integrados

int a = 0x00;       // Byte de datos a
int b = 0x00;       // Byte de datos b

void setup(){

  //-------------> Se declaran los pines de salida
  pinMode(STR, OUTPUT);
  pinMode(CLK, OUTPUT);
  pinMode(DATA_OUT, OUTPUT);
  
}

/*----------------> Función: newOut
 *
 *  ->Establece el estado lógico en algún de los pines de los CD4094,  
 *    según sea recibido en los parámetros.
 *  ->Recibe como primer parámetro el pin al que se le coloca el estado 
 *    que se establece en el segundo.
 * 
 *-------------------------------------------------------------------->*/

void newOut(int, int);

/*----------------> Función: outByte
 *
 *  ->Envía dos bytes a los CD4094, que establecen el estado de las salidas de los pines
 *    en ambos circuitos integrados.
 *  ->Recibe como parámetros dos bytes (a, b).
 * 
 *-------------------------------------------------------------------->*/
 
void outByte(int, int);

int tmp = 100;

void loop() {

  for(int a = 0; a <= 7; a++){
    newOut(a, HIGH);
    for(int d = 8; d <= 15; d++){
      newOut(d, HIGH);
      delay(20);
      newOut(d, LOW);
    }
    newOut(a, LOW);
  }

  //newOut(0,HIGH);
  //newOut(8,HIGH);

}

void newOut(int pin, int std){

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
  outByte(a, b);
  
}

void outByte(int a, int b){
    digitalWrite(STR, LOW);
    shiftOut(DATA_OUT, CLK, MSBFIRST, b);
    shiftOut(DATA_OUT, CLK, MSBFIRST, a);  
    digitalWrite(STR, HIGH);
}
