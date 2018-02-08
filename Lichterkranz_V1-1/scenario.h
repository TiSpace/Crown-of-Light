


// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
// ------------------------------------------------------------------------------------
void checkUserInteraction()
{
  // check if buttons pressed and some change shall be applied
  byte incrementValue = 10;
  if (digitalRead(Button_1) == 1)
  {
    ButtonPressed[1]++;
    if (ButtonPressed[1] > waitButtonBrightness) {

      BrightnessValue = BrightnessValue + 10;
      Serial.print("Helligkeit ");
      Serial.println(BrightnessValue);
      pixels.setBrightness(BrightnessValue);
      digitalWrite(Buzzer, LOW); // Buzzer einschalten
      delay(1);
      digitalWrite(Buzzer, HIGH); // Buzzer ausschalten

      ButtonPressed[1] = 0; //reset Button Counter
    }

  }
  else
  {
    ButtonPressed[1] = 0;
  }


  // by pressing th button change to next visualization mode
  if (digitalRead(Button_2) == 1)
  {

    ButtonPressed[0]++;
    if (ButtonPressed[0] > waitButton) {
      digitalWrite(Buzzer, LOW); // Buzzer einschalten
      mode = mode + 1;
      if (mode > numbersMode) {
        mode = 0;

      }
      ButtonPressed[0] = 0; //reset Button Counter
      exit_func = true;
      Serial.print("aktuelle Mode:");
      Serial.println(mode);
      delay(100);
      digitalWrite(Buzzer, HIGH); // Buzzer ausschalten
    }
  }
  else
  {

    ButtonPressed[0] = 0;
  }
}

// ------------------------------------------------------------------------------------
void simpleRun(uint8_t wait)
{
  int j;
  for (int i = 0; i < NUMPIXELS * 2; i++)
  {
    pixels.clear();

    pixels.setPixelColor(i / 2, 0, 255, 0); //grün
    pixels.setPixelColor((i / 2 + NUMPIXELS / 3) % NUMPIXELS, 255, 0, 0); //rot
    pixels.setPixelColor(NUMPIXELS - ((i + NUMPIXELS / 3 * 2) % NUMPIXELS), 0, 0, 255); //blau

    pixels.show();

    checkUserInteraction();
    if (exit_func) {
      exit_func = false;
      return;
    }
    delay(wait * 3);
  }
}
// ------------------------------------------------------------------------------------
void rainbow(uint8_t wait) {
  uint16_t i, j;

  for (j = 0; j < 256; j++) {
    for (i = 0; i < pixels.numPixels(); i++) {
      pixels.setPixelColor(i, Wheel((i + j) & 255));
    }
    pixels.show();

    checkUserInteraction();
    if (exit_func) {
      exit_func = false;
      return;
    }

    delay(wait);
  }
}

// ------------------------------------------------------------------------------------
// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for (j = 0; j < 256; j++) { // 1 cycle of all colors on wheel
    for (i = 0; i < pixels.numPixels(); i++) {
      pixels.setPixelColor(i, Wheel(((i * 256 / pixels.numPixels()) + j) & 255));
    }
    pixels.show();


    checkUserInteraction();
    if (exit_func) {
      exit_func = false;
      return;
    }
    delay(wait);
  }
}
// ------------------------------------------------------------------------------------
// Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int q = 0; q < 3; q++) {
    for (int i = 0; i < pixels.numPixels(); i = i + 3) {
      pixels.setPixelColor(i + q, c);  //turn every third pixel on
    }
    pixels.show();

    checkUserInteraction();
    if (exit_func) {
      exit_func = false;
      return;
    }
    delay(wait);

    for (int i = 0; i < pixels.numPixels(); i = i + 3) {
      pixels.setPixelColor(i + q, 0);      //turn every third pixel off
    }
  }
}
// ------------------------------------------------------------------------------------
// Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j = 0; j < 256; j++) {   // cycle all 256 colors in the wheel
    for (int q = 0; q < 3; q++) {
      for (int i = 0; i < pixels.numPixels(); i = i + 3) {
        pixels.setPixelColor(i + q, Wheel( (i + j) % 255)); //turn every third pixel on
      }
      pixels.show();

      checkUserInteraction();
      if (exit_func) {
        exit_func = false;
        return;
      }
      delay(wait);

      for (int i = 0; i < pixels.numPixels(); i = i + 3) {
        pixels.setPixelColor(i + q, 0);      //turn every third pixel off
      }
    }
  }
}
// ------------------------------------------------------------------------------------
// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  uint16_t i;

  for (i = 0; i < pixels.numPixels(); i++) {
    pixels.setPixelColor(i, 0, 0, 0);
  }
  pixels.show();

  for (uint16_t i = 0; i < pixels.numPixels(); i++) {
    pixels.setPixelColor(i, c);
    pixels.show();

    checkUserInteraction();
    if (exit_func) {
      exit_func = false;
      return;
    }
    delay(wait * 3);
  }

  for (uint16_t i = 0; i < pixels.numPixels(); i++) {
    pixels.setPixelColor(i, 0);
    pixels.show();

    checkUserInteraction();
    if (exit_func) {
      exit_func = false;
      return;
    }
    delay(wait * 3);
  }

}

void polishLight(uint8_t wait) {

  for (int i = 0; i < NUMPIXELS; i++)
  {
    pixels.clear();
    pixels.setPixelColor(i, pixels.Color(0, 255, 0));
    pixels.setPixelColor(NUMPIXELS - i, pixels.Color(0, 0, 255));
    if (i < 12)
    {
      pixels.setPixelColor(NUMPIXELS / 2 + i, pixels.Color(255, 0, 0));
    }
    else
    {
      pixels.setPixelColor(i - NUMPIXELS / 2, pixels.Color(255, 0, 0));
    }
    pixels.show();

    checkUserInteraction();
    if (exit_func) {
      exit_func = false;
      return;
    }
    delay(wait);
  }
}

void chaos(uint8_t wait) {
  for (int i = 0; i < NUMPIXELS; i++)
  {
    pixels.setPixelColor(i, random(0, 0xffffff));
    pixels.show();

    checkUserInteraction();
    if (exit_func) {
      exit_func = false;
      return;
    }
    delay(wait);
  }
}

