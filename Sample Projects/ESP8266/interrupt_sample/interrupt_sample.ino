void setup()
{
  Serial.begin(9600);
  Serial1.begin(9600);
}

void loop()
{
int a=0;

   if (Serial1.available()>0)
   {  
      a = Serial1.read();
      Serial.print(a); 
      Serial.println();
       
   }
}
