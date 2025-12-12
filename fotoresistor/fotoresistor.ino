int odczytanaWartosc = 0;//Odczytana wartość z ADC

float napiecie = 0;//Wartość przeliczona na napięcie w V

void setup() {

  Serial.begin(9600);//Uruchomienie komunikacji przez USART
  pinMode(8, OUTPUT);

}

void loop() {

  odczytanaWartosc = analogRead(A5);//Odczytujemy wartość napięcia

  napiecie = odczytanaWartosc; //Przeliczenie wartości na napięcie

  Serial.println(napiecie);//Wysyłamy zmierzone napięcie
  if (napiecie < 100) {

     digitalWrite(8, HIGH);//Włączenie diody    

  } else {

     digitalWrite(8, LOW);//Wyłączenie diody      

  }

  delay(200);//Czekamy, aby wygodniej odczytywać wyniki  

}