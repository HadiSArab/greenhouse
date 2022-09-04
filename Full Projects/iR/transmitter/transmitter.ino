uint8_t my_serial_bytes[5]={0xA1, 0xF1, 0x0E, 0x0E, 0x15};

void setup() {
        Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
//Serial1.begin(9600);
}

void loop() {
  
  
Serial.write(my_serial_bytes,sizeof(my_serial_bytes));


delay(5000);        // delay 5sec
                
        
}
