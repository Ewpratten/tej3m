/**
 * PWM LED control
 * By: Evan Pratten
 * 
 * ## Light level ramping ##
 * The light level ramping follows this equation, where "m" is the LED's maximum output:
 * 
 * c(i) = abs(m · sin(((i2) / m) · π))
 * f(x) = {(mod(x,2m) > m): c(m − (mod(x,2m) − m)), c(mod(x, 2m))}
 */

// Definitions
#define led_pin 9
#define max_output 255

// Locals
int output = 0;

void setup()
{
    // Configure and disable LED
    pinMode(led_pin, OUTPUT);
    digitalWrite(led_pin, LOW);

    // Print program header
    Serial.begin(9600);
    Serial.write("Program by: Evan Pratten <ewpratten@retrylife.ca>\n");
}

double curve(double i)
{
    return abs(max_output * sin(((i * 2) / max_output) * PI));
}

void loop()
{
    // Determine LED output
    int led_signal = (int)(output <= max_output) ? curve(output) : curve(max_output - (output - max_output));

    // Write LED brightness
    analogWrite(led_pin, led_signal);

    // Incr the output
    output++;
    output %= max_output * 2;

    // Pause
    delay(8);
}