char volup[5]={0xA1, 0xF1, 0x0E, 0x0E, 0x15};
char voldown[5]={0xA1, 0xF1, 0x0E, 0x0E, 0x14};
char prup[5]={0xA1, 0xF1, 0x0E, 0x0E, 0x12};
char prdown[5]={0xA1, 0xF1, 0x0E, 0x0E, 0x13};
char power[5]={0xA1, 0xF1, 0x0E, 0x0E, 0x0C};
char homee[5]={0xA1, 0xF1, 0x0E, 0x0E, 0x78};
char menu[5]={0xA1, 0xF1, 0x0E, 0x0E, 0x11};
char exite[5]={0xA1, 0xF1, 0x0E, 0x0E, 0xB5};

char command ;
void setup() {
    Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
    Serial1.begin(9600);
}

void loop() {
    if (Serial.available()>0)
  {
    command = Serial.read();
    Serial.println(command);
    if (command == '1')
      Serial1.write(volup,sizeof(volup));
  if (command =='2')
       Serial1.write(voldown,sizeof(voldown));
    // Serial1.write(volup,sizeof(volup));
     //Serial1.write(voldown,sizeof(voldown));
    // Serial1.write(prup,sizeof(prup));
    // Serial1.write(prdown);
     //Serial1.write(power,sizeof(power));
     //Serial1.write(homee,sizeof(homee));
     //Serial1.write(menu,sizeof(menu));
     //Serial1.write(exite,sizeof(exite));
  
 delay (300);            
}      
}
