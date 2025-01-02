#include "MyIotReader.h"
#include <Arduino.h>

IotReader::IotReader(Executable* executor) {
  this->executor = executor;
}

void IotReader::readPackage() {
  while(Serial.available() > 0) {
    Serial.print("Reading: ");
    Serial.print(Serial.available());
    Serial.println(" Bytes!");
    
    this->package = Serial.readStringUntil('\n');
    this->package.trim();

    Serial.print("Read: ");
    Serial.println(this->package);
  }    
}

void IotReader::requestPackage() {
  Serial.println("Requesting package");
}

void IotReader::parserCommand() {
    int firstSpace = this->package.indexOf(' ');

    if (firstSpace == -1) {
      this->command.name = this->package;  
      this->command.x = 0;
      this->command.y = 0;
  
      return;
    }

    this->command.name = this->package.substring(0, firstSpace);
    
    String args = this->package.substring(firstSpace + 1);

    int secondSpace = args.indexOf(' ');
    
    command.x = args.substring(0, secondSpace).toInt();
    command.y = args.substring(secondSpace + 1).toInt();
}
  
void IotReader::processCommand() {
  if (this->package.equals("PENUP")) {
    this->executor->PENUP();
  }

  if (this->package.equals("PENDOWN")) {
    this->executor->PENDOWN();  
  }

  if (this->package.equals("GOTO")) {
    this->executor->GOTO(
      this->command.x,
      this->command.y
    ); 
  }

  this->package = "";
  
}

void IotReader::readLine() {

  this->readPackage();

  this->parserCommand();

  this->processCommand();
  
  this->requestPackage();
  
}
