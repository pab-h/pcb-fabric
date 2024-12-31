#define MAX_PACKAGE_LEN 256
#define MAX_COMMAND_LEN 16
#define MAX_POSITION_DIGITS 4

class Executable {
  public:
    virtual void PENUP();
    virtual void PENDOWN();
    virtual void GOTO(int x, int y);
  
};

class Command {
  public:
    char name[MAX_COMMAND_LEN];
    int x;
    int y;
};

class IotReader {
  private:
    Command command;
    Executable* executor;
    
    int packageIndex;
    char inByte;
    char package[MAX_PACKAGE_LEN];

    void readPackage();
    void requestPackage();
    void parserCommand();
    void processCommand();

  public:
    void readLine();

    IotReader(Executable* executor);
    
  
};

IotReader::IotReader(Executable* executor) {
  this->executor = executor;
}

void IotReader::readPackage() {
  while(Serial.available() > 0) {
    this->inByte = Serial.read();
    
    if (this->inByte != '\n' && (this->packageIndex < MAX_PACKAGE_LEN - 1)) {
      this->package[packageIndex] = this->inByte;
      this->packageIndex++;

      Serial.print("Reading: ");
      Serial.println(this->inByte);
      
    } else {
      this->package[this->packageIndex] = '\0'; 
      this->packageIndex = 0;

      Serial.print("Read: ");
      Serial.println(this->package);

    }
  }
}

void IotReader::requestPackage() {
  Serial.println("Requesting package");
}

void IotReader::parserCommand() {
    int i = 0;
    int j = 0;
    
    char xStr[MAX_POSITION_DIGITS] = {0};
    char yStr[MAX_POSITION_DIGITS] = {0};

    while (this->package[i] != '\0' && this->package[i] != ' ' && j < MAX_COMMAND_LEN - 1) {
        this->command.name[j++] = this->package[i++];
    }
    
    this->command.name[j] = '\0';
    i++;
    j = 0;

    if (this->package[i] == '\0') {
      this->command.x = -1;
      this->command.y = -1;
      return;
    }

    while (this->package[i] != '\0' && this->package[i] != ' ' && j < MAX_POSITION_DIGITS - 1) {
        xStr[j++] = this->package[i++];
    }
    
    xStr[j] = '\0';
    this->command.x = atoi(xStr);
    i++;
    j = 0;

    while (this->package[i] != '\0' && this->package[i] != ' ' && j < MAX_POSITION_DIGITS - 1) {
        yStr[j++] = this->package[i++];
    }
    
    yStr[j] = '\0';
    this->command.y = atoi(yStr);
}

void IotReader::processCommand() {
  if (strcmp(this->command.name, "PENUP") == 0) {
    this->executor->PENUP();
  }

  if (strcmp(this->command.name, "PENDOWN") == 0) {
    this->executor->PENDOWN();  
  }

  if (strcmp(this->command.name, "GOTO") == 0) {
    this->executor->GOTO(
      this->command.x,
      this->command.y
    ); 
  }
  
}

void IotReader::readLine() {

  this->readPackage();

  this->parserCommand();

  this->processCommand();
  
  this->requestPackage();
  
}

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
