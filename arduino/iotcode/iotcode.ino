#define MAX_PACKAGE_LEN 1024

class IotReader {
  private:
    int packageIndex;
    char inByte;
    char package[MAX_PACKAGE_LEN];

  public:
    void readPackage();
    void requestPackage();
  
};

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

IotReader reader;

void setup() {

  Serial.begin(9600);

}

void loop() {
  reader.readPackage();
  
  delay(2000); // simulate plotter process
  
  reader.requestPackage();
  
}
