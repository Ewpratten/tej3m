/**
 * 
 * 
 */

// Definitions
#define sense_pin A0

// LED pin definitions
const int led_pins[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
const int pin_count = (sizeof(led_pins) / sizeof(led_pins[0]));

// LED cycle counter
long active_led = 0;

// LED cycle delay time
unsigned int delay_time;
unsigned long last_time = 0;

void setup()
{

    // Init and clear each LED
    for (int i = 0; i < pin_count; i++)
    {
        pinMode(led_pins[i], OUTPUT);
        digitalWrite(led_pins[i], LOW);
    }

    // Init sense pin
    pinMode(sense_pin, INPUT);
}

int getNextLED()
{
    // Cycle to next LED
    active_led++;

    // Return the next ID
    return led_pins[round(((active_led % (2 * pin_count) >= pin_count) ? pin_count - (active_led % pin_count - pin_count) : active_led % pin_count) % pin_count)];
}

void loop()
{

    // Get the next LED ID to address
    int led_id = getNextLED();

    // Set the LED high
    digitalWrite(led_id, HIGH);

    // Wait the selected time
    do
    {
        // Determine delay time from analog input
        delay_time = map(pow((double)analogRead(sense_pin), 2), 0, 1048576, 0, 1024);

    } while ((millis() - last_time) < delay_time);

    // Set the last time
    last_time = millis();

    // Set the LED LOW
    digitalWrite(led_id, LOW);
}