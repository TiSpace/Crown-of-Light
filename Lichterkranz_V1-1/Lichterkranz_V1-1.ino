#include <Adafruit_NeoPixel.h>
#include "settings.h"
#include "scenario.h"

long Farbe;

void setup()
{

  pinMode(Button_1, INPUT);
  pinMode(Button_2, INPUT);
  pinMode(Buzzer, OUTPUT);

  Serial.begin(userBaudRate);
  Serial.println ("---------------------------");
  Serial.println ("Lichterkranz Version 1.1");
  Serial.println("    © tr 2017");
  Serial.println("");
  Serial.println ("---------------------------");



  pixels.begin();

  // Batteriespannung lesen und ausgeben
  int BatterieSpannung  = 0;
  BatterieSpannung = analogRead(VOLTAGEMONITOR);

  Serial.print("Spannung: ");
  Serial.println(BatterieSpannung * VoltageCorrection);
  digitalWrite(Buzzer, LOW); // Buzzer einschalten
  delay(50);
  digitalWrite(Buzzer, HIGH); // Buzzer ausschalten

  pixels.clear();
  for (int i = 0; i < 7; i++)
  {
    //pixels.setPixelColor(i, pixels.Color(0, 0,32));
    pixels.setPixelColor(i, 0, 0, 32);

  }

  pixels.setBrightness(BrightnessValue);

  // Spannung messen und anhand von 7 Segementen zwischen 6..8,4V aufteilen
  if (BatterieSpannung < 616)   {
    pixels.setPixelColor(6, 32, 0, 0);
  }
  if (BatterieSpannung < 663)   {
    pixels.setPixelColor(5, 32, 0, 0);
  }
  if (BatterieSpannung < 710)   {
    pixels.setPixelColor(4,  32, 0, 0);
  }
  if (BatterieSpannung < 757)   {
    pixels.setPixelColor(3,  32, 0, 0);
  }
  if (BatterieSpannung < 804)   {
    pixels.setPixelColor(2, 32, 0, 0);
  }
  if (BatterieSpannung < 815)   {
    pixels.setPixelColor(1,  32, 0, 0);
  }
  if (BatterieSpannung < 900)   {
    pixels.setPixelColor(0,  32, 0, 0);
  }

  pixels.show();
  //if (BatterieSpannung
  delay(2000);
}
void loop()


{

  // eine der vordefinierten Lichterszenarien einstellen
  // mode ändert sich bei Tastendruck

  // SIMPLERUN, WIPE, RAINBOW, RAINBOWCYCLE, THEATERCHASE, THEATERCHASERAINBOW
  switch (mode) {
    case SIMPLERUN:
      simpleRun(10);
      break;
    case WIPE:
      //randomSeed(analogRead(1));
      Farbe = random(0, 0xffffff);

      //Serial.println(String(Farbe, HEX));
      colorWipe(Farbe , 10);
      break;
    case RAINBOW:
      rainbow(10);
      break;
    case RAINBOWCYCLE:
      rainbowCycle(10);
      break;
    case THEATERCHASE:
      Farbe = random(0, 0xffffff);
      theaterChase(Farbe, 10);
      break;
    case THEATERCHASERAINBOW:
      theaterChaseRainbow(10);
      break;
    case POLISH:
      polishLight(50);
      break;
    case CHAOS:
      chaos(20);
      break;
  }



}


