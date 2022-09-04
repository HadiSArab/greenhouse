
char buffer[2];
int lenght;
void setup()
{
  Serial.begin(9600);
 
}
 
 
void loop()
{
  if (Serial.available() > 0)
  {
    lenght = Serial.readBytes(buffer , 2);
    for (int i = 0 ; i <= lenght- 1 ; i++)
    {
      Serial.print(buffer[i]);
    }
    Serial.println();
  }
}
