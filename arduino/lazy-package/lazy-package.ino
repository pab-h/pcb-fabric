const unsigned int MAX_PACKAGE_LEN = 1024;
char package[MAX_PACKAGE_LEN];

int packageIndex = 0;
char inByte = 0;

void readPackage() {
  while (Serial.available() > 0) {
    inByte = Serial.read();
    
    if (inByte != '\n' && (packageIndex < MAX_PACKAGE_LEN - 1)) {
      package[packageIndex] = inByte;
      packageIndex++;
    } else {
      package[packageIndex] = '\0'; 
      packageIndex = 0;
    }
  }
}

void processPackage() {
  delay(1000);
}

void setup() {
  Serial.begin(9600);
}

void loop() {

  readPackage();

  processPackage();

  Serial.println("READY");

}
