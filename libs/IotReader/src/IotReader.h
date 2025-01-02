#ifndef IOTREADER_IOTREADER_H

#define IOTREADER_IOTREADER_H

#include <Arduino.h>
#include "Executable.h"
#include "Command.h"

class IotReader {
  private:
    Command command;
    Executable* executor;
    
    String package;

    void readPackage();
    void requestPackage();
    void parserCommand();
    void processCommand();
  
  public:
    void readLine();

    IotReader(Executable* executor);
  
};

#endif