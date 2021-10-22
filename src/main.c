#include <Arduino.h>0

// light one
int red1 = 13;
int yellow1 = 14;
int green1 = 15;
// light two
int red2 = 13;
int yellow2 = 12;
int green2 = 11;

int button = 0; // switch is on pin 12


void setup()
{
    pinMode(3, OUTPUT );

    pinMode(red1, OUTPUT);
    pinMode(yellow1, OUTPUT);
    pinMode(green1, OUTPUT);

    // pinMode(red2, OUTPUT);
    // pinMode(yellow2, OUTPUT);
    // pinMode(green2, OUTPUT);

    // pinMode(button, INPUT);
}

void loop() 
{
#if 0
    /* strobe 3 colours in paralelle  */
    digitalWrite( red1, LOW );
    digitalWrite( yellow1, LOW );
    digitalWrite( green1, LOW );
    digitalWrite( 3, LOW );
    delay(250);
    digitalWrite( red1, HIGH );
    digitalWrite( yellow1, HIGH );
    digitalWrite( green1, HIGH );
    digitalWrite( 3, HIGH );
    delay(250);

//     digitalWrite( red1, LOW );
//     digitalWrite( yellow1, LOW );
//     digitalWrite( green1, LOW );
//     digitalWrite( red2, LOW );
//     digitalWrite( yellow2, LOW );
//     digitalWrite( green2, LOW );

//     delay(250);

//     digitalWrite( red1, HIGH );
//     digitalWrite( yellow1, HIGH );
//     digitalWrite( green1, HIGH );
//     digitalWrite( red2, HIGH );
//     digitalWrite( yellow2, HIGH );
//     digitalWrite( green2, HIGH );
//     delay(250);

#elif 0
    /* strobe 3 colours sequentially */
    digitalWrite( red1,     HIGH );
    digitalWrite( yellow1,  LOW );
    digitalWrite( green1,   LOW );
    delay(250);   

    digitalWrite( red1,     LOW );
    digitalWrite( yellow1,  HIGH );
    digitalWrite( green1,   LOW );
    delay(250);

    digitalWrite( red1,     LOW );
    digitalWrite( yellow1,  LOW );
    digitalWrite( green1,   HIGH );
    delay(250);


#elif 1

    static int state = 0;

    if (digitalRead(button) == LOW)
    {
        delay(15);                  // software debounce
        if (digitalRead(button) == LOW) 
        {
            // if the switch is LOW, ie. pushed down - change state
            ++state;
        }
    }

    switch(state)
    {
        case 0:
            digitalWrite( red1,     HIGH );
            digitalWrite( yellow1,  LOW );
            digitalWrite( green1,   LOW );
            break;
        case 1:
            digitalWrite( red1,     LOW );
            digitalWrite( yellow1,  HIGH );
            digitalWrite( green1,   LOW );
            break;

        case 2:
            digitalWrite( red1,     LOW );
            digitalWrite( yellow1,  LOW );
            digitalWrite( green1,   HIGH );
            break;

        case 3:
            digitalWrite( red1,     LOW );
            digitalWrite( yellow1,  HIGH );
            digitalWrite( green1,   LOW );
            break;

        case 4:
            state = 0;

        default:
            digitalWrite( red1,     HIGH );
            digitalWrite( yellow1,  LOW );
            digitalWrite( green1,   LOW );
    }
    
    delay(500);

#endif
}

void changeLights()
{
    // turn both yellows on
    digitalWrite(green1, LOW);
    digitalWrite(yellow1, HIGH);
    digitalWrite(yellow2, HIGH);
    delay(5000);
    // turn both yellows off, and opposite green and red
    digitalWrite(yellow1, LOW);
    digitalWrite(red1, HIGH);
    digitalWrite(yellow2, LOW);
    digitalWrite(red2, LOW);
    digitalWrite(green2, HIGH);
    delay(5000);
    // both yellows on again
    digitalWrite(yellow1, HIGH);
    digitalWrite(yellow2, HIGH);
    digitalWrite(green2, LOW);
    delay(3000);
    // turn both yellows off, and opposite green and red
    digitalWrite(green1, HIGH);
    digitalWrite(yellow1, LOW);
    digitalWrite(red1, LOW);
    digitalWrite(yellow2, LOW);
    digitalWrite(red2, HIGH);
    delay(5000);
}
