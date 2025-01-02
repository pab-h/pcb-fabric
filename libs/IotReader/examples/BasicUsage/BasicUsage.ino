#include "Executable.h"
#include <Arduino.h>

class EchoExec: public Executable {
  public:
    void PENUP();
    void PENDOWN();
    void GOTO(int x, int y);
};

void EchoExec::PENUP() {
  Serial.println(" [Executor] Processing... PENUP");  
}

void EchoExec::PENDOWN() {
  Serial.println(" [Executor] Processing... PENDOWN"); 
}

void EchoExec::GOTO(int x, int y) {
  Serial.print(" [Executor] Processing... GOTO on "); 
  Serial.print("x = ");
  Serial.print(x);
  Serial.print(", ");
  Serial.print("y = ");
  Serial.println(y);
}

EchoExec echo;
IotReader reader(&echo);

void setup() {

  Serial.begin(9600);

}

void loop() {
  reader.readLine();
  
  delay(2000);
}
