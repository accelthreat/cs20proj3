#include <math.h>
//VS CODE BLOCK to block syntax errors
//Comment out when compiling
// #define INPUT 1
// #define OUTPUT 0
// #define HIGH 1
// #define LOW 0
// #define A0 14
// void pinMode(int pin, int mode);
// void setup();
// void loop();
// int digitalRead(int pin);
// void digitalWrite(int pin, int val);
// float analogRead(int pin);
// void analogWrite(int pin, float val);
// int constrain(int a, int b, int c);
// unsigned long millis();
// void tone(int pin, unsigned int hertz);
//END BLOCK

void setMode();
void runMode();
void evaluate(int num, int mode);
int compute_real_value(int tens, int ones);
int mod10(int a);

#define SET 1
#define RUN 0
#define TEN 10
#define ONE 1

const int TEN_TACT_UP = 30;
const int TEN_TACT_DOWN = 31;
const int ONE_TACT_UP = 2;
const int ONE_TACT_DOWN = 3;
const int SET_RUN = 4;
const int PIEZZO = 5;
const int TEN_A = 6;
const int TEN_B = 7;
const int TEN_C = 8;
const int TEN_D = 9;
const int TEN_E = 10;
const int TEN_F = 11;
const int TEN_G = 12;
const int ONE_A = 23;
const int ONE_B = 24;
const int ONE_C = 25;
const int ONE_D = 26;
const int ONE_E = 27;
const int ONE_F = 28;
const int ONE_G = 29;
const int LDR = A0;

int increaseTenPrev = LOW;
int decreaseTenPrev = LOW;
int increaseOnePrev = LOW;
int decreaseOnePrev = LOW;

int tenValue = 0;
int oneValue = 0;

unsigned long currentTime = 0;
unsigned long previousTime = 0;
unsigned long delayTime = 1000;

void setup() {
    pinMode(TEN_TACT_UP, INPUT);
    pinMode(TEN_TACT_DOWN, INPUT);
    pinMode(ONE_TACT_UP, INPUT);
    pinMode(ONE_TACT_DOWN, INPUT);
    pinMode(SET_RUN, INPUT);
    pinMode(LDR, INPUT);
    pinMode(PIEZZO, OUTPUT);

    for (int i = TEN_A; i < TEN_G + 1; i++) {
        pinMode(i, INPUT);
    }
    for (int i = ONE_A; i < ONE_G + 1; i++) {
        pinMode(i, INPUT);
    }
}

void loop() {
    int mode = digitalRead(SET_RUN);

    if (mode == SET) {
        setMode();
    } else if (mode == RUN) {
        runMode();
    }
}

void setMode() {
    previousTime = 0;
    currentTime = 0;

    int increaseTen = digitalRead(TEN_TACT_UP);
    int decreaseTen = digitalRead(TEN_TACT_DOWN);
    int increaseOne = digitalRead(ONE_TACT_UP);
    int decreaseOne = digitalRead(ONE_TACT_DOWN);

    if (increaseTen == HIGH && increaseTenPrev == LOW) {
        tenValue = constrain(tenValue + increaseTen, 0, 9);
        increaseTenPrev = increaseTen;
    }

    if (decreaseTen == HIGH && decreaseTenPrev == LOW) {
        tenValue = constrain(tenValue - decreaseTen, 0, 9);
        decreaseTenPrev = decreaseTen;
    }

    if (increaseOne == HIGH && increaseOnePrev == LOW) {
        oneValue = constrain(oneValue + increaseOne, 0, 9);
        increaseOnePrev = increaseOne;
    }

    if (decreaseOne == HIGH && decreaseOnePrev == LOW) {
        oneValue = constrain(oneValue - decreaseOne, 0, 9);
        decreaseOnePrev = decreaseOne;
    }

    evaluate(tenValue, TEN);
    evaluate(oneValue, ONE);
}

void evaluate(int num, int mode) {
    const int a = mode == TEN ? TEN_A : ONE_A;
    const int b = mode == TEN ? TEN_B : ONE_B;
    const int c = mode == TEN ? TEN_C : ONE_C;
    const int d = mode == TEN ? TEN_D : ONE_D;
    const int e = mode == TEN ? TEN_E : ONE_E;
    const int f = mode == TEN ? TEN_F : ONE_F;
    const int g = mode == TEN ? TEN_G : ONE_G;

    switch (num) {
        case 0:
            digitalWrite(a, HIGH);
            digitalWrite(b, HIGH);
            digitalWrite(c, HIGH);
            digitalWrite(d, HIGH);
            digitalWrite(e, HIGH);
            digitalWrite(f, HIGH);
            digitalWrite(g, LOW);
            break;
        case 1:
            digitalWrite(a, LOW);
            digitalWrite(b, HIGH);
            digitalWrite(c, HIGH);
            digitalWrite(d, LOW);
            digitalWrite(e, LOW);
            digitalWrite(f, LOW);
            digitalWrite(g, LOW);
            break;
        case 2:
            digitalWrite(a, HIGH);
            digitalWrite(b, HIGH);
            digitalWrite(c, LOW);
            digitalWrite(d, HIGH);
            digitalWrite(e, HIGH);
            digitalWrite(f, LOW);
            digitalWrite(g, HIGH);
            break;
        case 3:
            digitalWrite(a, HIGH);
            digitalWrite(b, HIGH);
            digitalWrite(c, HIGH);
            digitalWrite(d, HIGH);
            digitalWrite(e, LOW);
            digitalWrite(f, LOW);
            digitalWrite(g, HIGH);
            break;
        case 4:
            digitalWrite(a, LOW);
            digitalWrite(b, HIGH);
            digitalWrite(c, HIGH);
            digitalWrite(d, LOW);
            digitalWrite(e, LOW);
            digitalWrite(f, HIGH);
            digitalWrite(g, HIGH);
            break;
        case 5:
            digitalWrite(a, HIGH);
            digitalWrite(b, LOW);
            digitalWrite(c, HIGH);
            digitalWrite(d, HIGH);
            digitalWrite(e, LOW);
            digitalWrite(f, HIGH);
            digitalWrite(g, HIGH);
            break;
        case 6:
            digitalWrite(a, HIGH);
            digitalWrite(b, LOW);
            digitalWrite(c, HIGH);
            digitalWrite(d, HIGH);
            digitalWrite(e, HIGH);
            digitalWrite(f, HIGH);
            digitalWrite(g, HIGH);
            break;
        case 7:
            digitalWrite(a, HIGH);
            digitalWrite(b, HIGH);
            digitalWrite(c, HIGH);
            digitalWrite(d, LOW);
            digitalWrite(e, LOW);
            digitalWrite(f, LOW);
            digitalWrite(g, LOW);
            break;
        case 8:
            digitalWrite(a, HIGH);
            digitalWrite(b, HIGH);
            digitalWrite(c, HIGH);
            digitalWrite(d, HIGH);
            digitalWrite(e, HIGH);
            digitalWrite(f, HIGH);
            digitalWrite(g, HIGH);
            break;
        case 9:
            digitalWrite(a, HIGH);
            digitalWrite(b, HIGH);
            digitalWrite(c, HIGH);
            digitalWrite(d, HIGH);
            digitalWrite(e, LOW);
            digitalWrite(f, HIGH);
            digitalWrite(g, HIGH);
            break;
    }
}

void runMode() {
    if (tenValue == 0 && oneValue == 0) {
        tone(PIEZZO, 500);
    } else {
        float ldrValue = analogRead(LDR);
        currentTime = millis();
        if (ldrValue == 0) {
            if (currentTime - previousTime > delayTime) {
                decrease_real_value();
                previousTime = currentTime;
            }
        } else {
            previousTime = currentTime;
        }
    }
}

void decrease_real_value() {
    int oldOneValue = oneValue;
    oneValue = mod10(oneValue - 1);
    if (oneValue != oldOneValue - 1) {
        tenValue = mod10(tenValue - 1);
    }
}

int mod10(int a) {
    a = a - (10 * floor(a / 10.0));
    return a;
}
