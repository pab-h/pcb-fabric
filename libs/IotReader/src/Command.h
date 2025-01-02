#ifndef COMMAND_IOTREADER_H

#define COMMAND_IOTREADER_H

#include<Arduino.h>

class Command {
  public:
    String name;
    unsigned int x;
    unsigned int y;

    Command();
};

#endif
