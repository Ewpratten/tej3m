/*
 * Arduino LED toggle
 * By: Evan Pratten
 * 
 * ## Goal ##
 * Use an external button to toggle the builtin LED on an Arduino UNO R3 (pin 13)
 * 
 * ## Program design ##
 * Read button state to an input buffer that will only count as "on" if the 
 * entire buffer had the same state. This is a simple method of denouncing 
 * the button. Larger buffers will increase reaction time, but decrease bouncing.
 * 
 * This state is then compared with the last to control a flip-flop, which then 
 * is read to determine the desired output of the LED
*/

// Definitions
#define sense_pin A0
#define led_pin 13
#define voltage_thresh 200
#define debounce_buffer 5

// Array to track avg button states
bool states[debounce_buffer];
int state_ticker = 0;

// Button toggling
bool last_button_state = false;
bool led_flip_flop = false;

// Setup the program
void setup()
{

    // Set Pin modes
    pinMode(sense_pin, INPUT);
    pinMode(led_pin, OUTPUT);

    // Turn off LED
    digitalWrite(led_pin, LOW);

    // Write header
    Serial.begin(9600);
    Serial.write("Program by: Evan Pratten <ewpratten@retrylife.ca>");
}

// Debounce the button
bool getDebounced(bool button_state)
{
    // Feed the debouncer
    states[state_ticker] = button_state;

    // Incr the state_ticker
    state_ticker++;
    state_ticker %= debounce_buffer;

    // Iter each button reading
    for (int i = 0; i < debounce_buffer; i++)
    {
        // Too bouncy
        if (!states[i])
        {
            return false;
        }
    }

    return true;
}

void loop()
{
    // Read the button
    bool button_state = getDebounced(analogRead(sense_pin) > 200);

    // Set the flip-flop
    led_flip_flop = (button_state == true && button_state != last_button_state) ? !led_flip_flop : led_flip_flop;
    last_button_state = button_state;

    // Write the LED state
    digitalWrite(led_pin, (led_flip_flop) ? HIGH : LOW);
}