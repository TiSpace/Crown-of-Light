#define PIN      6
#define VOLTAGEMONITOR 0
#define NUMPIXELS   27
#define Button_1 7 //D7
#define Button_2 8 //D8
#define Buzzer 9 //D9

#define numbersMode 7 // Anzahl der LED Modi (0...n)
#define waitButton 40 //wie viele Durchgänge der Touchbutton gedrückt sein muss
#define waitButtonBrightness 10 //wie viele Durchgänge der Touchbutton gedrückt sein muss
#define VoltageCorrection  0.0097387173396675 // Korrektur ADC wegen Spannungsteile
#define userBaudRate 38400

byte BrightnessValue = 64;
byte ButtonPressed[2] = {0,0}; //zäjlt ie lange der Button aktiviert ist

bool exit_func = false;     // Global helper variable to get out of the color modes when mode changes


// List of all color modes
enum MODE { SIMPLERUN, WIPE, RAINBOW, RAINBOWCYCLE, THEATERCHASE, THEATERCHASERAINBOW,POLISH, CHAOS };

MODE mode = WIPE;
//MODE mode = RAINBOWCYCLE;   // Standard mode that is active when software starts



Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

