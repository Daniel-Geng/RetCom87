const int RESET_PIN = 8;
const int BC1_PIN = 10;
const int BDIR_PIN = 11;

void set_mode_inactive()
{
  digitalWrite(BC1_PIN, LOW);
  digitalWrite(BDIR_PIN, LOW);
}

void set_mode_latch()
{
  digitalWrite(BC1_PIN, HIGH);
  digitalWrite(BDIR_PIN, HIGH);
}

void set_mode_write()
{
  digitalWrite(BC1_PIN, LOW);
  digitalWrite(BDIR_PIN, HIGH);
}

void write_register(int reg, int value)
{
  //Use pins 0 to 8 as date line
  const byte numPins = 8;
  byte pins[] = {0, 1, 2, 3, 4, 5, 6, 7};

  //Register Select
  set_mode_latch();  
  Serial.println("Latch");
  for (byte i=0; i<numPins; i++) {
    byte state = bitRead(reg, i);
    digitalWrite(pins[i], state);
    Serial.print(state);
  }
  Serial.println();
  set_mode_inactive(); 
  Serial.println("Inactive"); 

  //Data Write
  set_mode_write();  
  Serial.println("Write");
  for (byte i=0; i<numPins; i++) {
    byte state = bitRead(value, i);
    digitalWrite(pins[i], state);
    Serial.print(state);
  }
  Serial.println();
  set_mode_inactive();
  Serial.println("Inactive");
}

void setup() {
  Serial.begin(9600);
  
  //Create 2MHz Clock
  TCCR1A = bit (COM1A0);
  TCCR1B = bit (WGM12) | bit (CS10);
  OCR1A =  3; 

  //Set pins as output
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(RESET_PIN, OUTPUT);
  pinMode(BC1_PIN, OUTPUT);
  pinMode(BDIR_PIN, OUTPUT);

  //Reset Chip
  digitalWrite(RESET_PIN, LOW);
  delay(1);
  digitalWrite(RESET_PIN, HIGH);

  // Enable channel A tone generator
  write_register(7, 62);

  //Set volume to max
  write_register(8, 15);


}

void loop() {
  //Set volume to max
  write_register(8, 15);

  //E5
  write_register(0, 190);
  write_register(1, 0);

  delay(250);

  //E5
  write_register(0, 190);
  write_register(1, 0);

  delay(500);

  //E5
  write_register(0, 190);
  write_register(1, 0);

  delay(500);

  //C5
  write_register(0, 239);
  write_register(1, 0);

  delay(250);

  //E5
  write_register(0, 190);
  write_register(1, 0);

  delay(250);

  //G5
  write_register(0, 159);
  write_register(1, 0);

  delay(1000);

  //E4
  write_register(0, 63);
  write_register(1, 1);

  delay(500);

  //Volume to 0
  write_register(8, 0);

  delay(5000);


  

}
