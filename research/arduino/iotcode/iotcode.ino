class Executable {
  public:
    virtual void PENUP();
    virtual void PENDOWN();
    virtual void GOTO(int x, int y);
  
};

class Command {
  public:
    String name;
    unsigned int x;
    unsigned int y;

    Command();
};

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

Command::Command() {
  this->name = "";
  this->x = 0;
  this->y = 0;

}

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
