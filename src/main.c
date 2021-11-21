/*
 *    include path for stm8...
 *    "/home/xxxxx/.platformio/packages/toolchain-sdcc/share/sdcc/include"
 *    Also the IAR #include <intrinsics.h> so commenting it out removes any 
 *    warning squiggles...
 */
#include <Arduino.h>

/*
 * Macros
 */
// #define DEBUG_MODE      (1)

/* 
 * Prototypes 
 */
static void TLOne_red( void );
static void TLOne_yellow( void );
static void TLOne_green( void );
static void TLTwo_red( void );
static void TLTwo_yellow( void );
static void TLTwo_green( void );

static void changeLightsEveryAuto( void );
static void OnOffFlasher( void );
static void strober( void );

/* 
 * Globals 
 */
#if defined STM8S_BLUE
const int pinDebug = 2; // solely for debugging software

const int pinButton = 0;

/* traffic Light one */
const int pinRed1      = 13;
const int pinYellow1   = 14;
const int pinGreen1    = 15;

/* traffic Light two */
const int pinRed2      = 10;
const int pinYellow2   = 11;
const int pinGreen2    = 12;

/* traffic Light three */
// const int red3      = 0; // no used by push button
// const int yellow3   = 1;
// const int green3    = 2;

// typedef struct 
// {
//     /* data */
// };

#else
#   error You need to define your hardware pins.
#endif

/* https://learn.adafruit.com/make-it-switch/debouncing */

int state = 0;              // traffic light state
int buttonState;             // the current reading from the input pin
int lastButtonState = HIGH;  // the previous reading from the input pin

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime =  0;  // the last time the output pin was toggled
unsigned long debounceDelay    = 50;    // the debounce time; increase if the output flickers


void setup( )
{
#if DEBUG_MODE
    pinMode( pinDebug, OUTPUT );
    digitalWrite( pinDebug, HIGH );
#endif /* DEBUG_MODE */

    // traffic Light one
    pinMode( pinRed1,    OUTPUT );
    pinMode( pinYellow1, OUTPUT );
    pinMode( pinGreen1,  OUTPUT );

    // traffic Light one
    pinMode( pinRed2,    OUTPUT );
    pinMode( pinYellow2, OUTPUT );
    pinMode( pinGreen2,  OUTPUT );

    //Init all leds off...
    digitalWrite( pinRed1,     LOW );
    digitalWrite( pinYellow1,  LOW );
    digitalWrite( pinGreen1,   LOW );

    digitalWrite( pinRed2,     LOW );
    digitalWrite( pinYellow2,  LOW );
    digitalWrite( pinGreen2,   LOW );

    // pinMode( buttonPin, INPUT );
    pinMode( pinButton, INPUT_PULLUP ); // does it have pullups ??  pressing buttin made the circuit go low so i think so
}

void loop( ) 
{
    delay(1000); 
    // read the state of the switch into a local variable:
    int reading = digitalRead( pinButton );

    // check to see if you just pressed the button
    // (i.e. the input went from LOW to HIGH), and you've waited long enough
    // since the last press to ignore any noise:

    // If the switch changed, due to noise or pressing:
    if( reading != lastButtonState ) 
    {
        // reset the debouncing timer
        lastDebounceTime = millis( );
    }

    if( (millis( ) - lastDebounceTime) > debounceDelay ) 
    {

        // whatever the reading is at, it's been there for longer than the debounce
        // delay, so take it as the actual current state:
        // if the button state has changed:
        if( reading != buttonState ) 
        {
            buttonState = reading;

            // only toggle the LED if the new button state is HIGH
            if( buttonState == HIGH ) 
            {
#if DEBUG_MODE
        digitalWrite( pinDebug, LOW );
#endif /* DEBUG_MODE */
                ++state;
            }
        }
    }

    switch( state )
    {
        case 0:
            /* two is green */
            TLOne_red( );
            TLTwo_green( );
            break;
        case 1:
            TLOne_red( );
            TLTwo_yellow( );
            break;
        case 2:
            /* both stopped */
            TLOne_red( );
            TLTwo_red( );
            break;
        case 3:
            // TLOne_yellow( );
            TLOne_redYellow( );
            TLTwo_red( );
            break;
        case 4:
            /* one is green */
            TLOne_green( );
            TLTwo_red( );
            break;
        case 5:
            TLOne_yellow( );
            TLTwo_red( );
            break;
        case 6:
            /* both stopped */
            TLOne_red( );
            TLTwo_red( );
            break;
        case 7:
            TLOne_red( );
            // TLTwo_yellow( );
            TLTwo_redYellow( );
            break;
        case 8:
            state = 0;
        default:
            /* two is green */
            TLOne_red( );
            TLTwo_green( );
    }
    
    // save the reading. Next time through the loop, it'll be the lastButtonState:
    lastButtonState = reading;
}


static void TLOne_red( void )
{
    digitalWrite( pinRed1,     HIGH );
    digitalWrite( pinYellow1,  LOW );
    digitalWrite( pinGreen1,   LOW );
}

static void TLOne_redYellow( void )
{
    digitalWrite( pinRed1,     HIGH );
    digitalWrite( pinYellow1,  HIGH );
    digitalWrite( pinGreen1,   LOW );
}

static void TLOne_green( void )
{
    digitalWrite( pinRed1,     LOW );
    digitalWrite( pinYellow1,  LOW );
    digitalWrite( pinGreen1,   HIGH );
}

static void TLOne_yellow( void )
{
    digitalWrite( pinRed1,     LOW );
    digitalWrite( pinYellow1,  HIGH );
    digitalWrite( pinGreen1,   LOW );
}

static void TLTwo_red( void )
{
    digitalWrite( pinRed2,     HIGH );
    digitalWrite( pinYellow2,  LOW );
    digitalWrite( pinGreen2,   LOW );
}

static void TLTwo_redYellow( void )
{
    digitalWrite( pinRed2,     HIGH );
    digitalWrite( pinYellow2,  HIGH );
    digitalWrite( pinGreen2,   LOW );
}

static void TLTwo_green( void )
{
    digitalWrite( pinRed2,     LOW );
    digitalWrite( pinYellow2,  LOW );
    digitalWrite( pinGreen2,   HIGH );
}

static void TLTwo_yellow( void )
{
    digitalWrite( pinRed2,     LOW );
    digitalWrite( pinYellow2,  HIGH );
    digitalWrite( pinGreen2,   LOW );
}


/*  
 */
static void changeLightsEveryAuto( void )
{
    const int delayLength = 5000;

    // turn both yellows on
    digitalWrite( pinGreen1,  LOW );
    digitalWrite( pinYellow1, HIGH );
    digitalWrite( pinYellow2, HIGH );
    delay( delayLength );

    // turn both yellows off, and opposite green and red
    digitalWrite( pinYellow1, LOW );
    digitalWrite( pinRed1,    HIGH );
    digitalWrite( pinYellow2, LOW );
    digitalWrite( pinRed2,    LOW );
    digitalWrite( pinGreen2,  HIGH );
    delay( delayLength );

    // both yellows on again
    digitalWrite( pinYellow1, HIGH );
    digitalWrite( pinYellow2, HIGH );
    digitalWrite( pinGreen2,  LOW );
    delay( delayLength );

    // turn both yellows off, and opposite green and red
    digitalWrite( pinGreen1,  HIGH );
    digitalWrite( pinYellow1, LOW );
    digitalWrite( pinRed1,    LOW );
    digitalWrite( pinYellow2, LOW );
    digitalWrite( pinRed2,    HIGH );
    delay( delayLength );
}

/**/
static void strober( void )
{
    const int delayLengthStrobe = 250;

    /* strobe 3 colours sequentially */
    digitalWrite( pinRed1,     HIGH );
    digitalWrite( pinYellow1,  LOW );
    digitalWrite( pinGreen1,   LOW );
    delay( delayLengthStrobe );   

    digitalWrite( pinRed1,     LOW );
    digitalWrite( pinYellow1,  HIGH );
    digitalWrite( pinGreen1,   LOW );
    delay( delayLengthStrobe );

    digitalWrite( pinRed1,     LOW );
    digitalWrite( pinYellow1,  LOW );
    digitalWrite( pinGreen1,   HIGH );
    delay( delayLengthStrobe );
}

/**/
static void OnOffFlasher( void )
{
    const int delayLengthFlasher = 250;

    /*  */
    digitalWrite( pinRed1,    LOW );
    digitalWrite( pinYellow1, LOW );
    digitalWrite( pinGreen1,  LOW );
    digitalWrite( pinRed2,    LOW );
    digitalWrite( pinYellow2, LOW );
    digitalWrite( pinGreen2,  LOW );
    delay( delayLengthFlasher );

    digitalWrite( pinRed1,    HIGH );
    digitalWrite( pinYellow1, HIGH );
    digitalWrite( pinGreen1,  HIGH );
    digitalWrite( pinRed2,    HIGH );
    digitalWrite( pinYellow2, HIGH );
    digitalWrite( pinGreen2,  HIGH );
    delay( delayLengthFlasher );
}
