#ifndef EXECUTABLE_IOTREADER_H

#define EXECUTABLE_IOTREADER_H

class Executable {
  public:
    virtual void PENUP();
    virtual void PENDOWN();
    virtual void GOTO(int x, int y);
  
};

#endif