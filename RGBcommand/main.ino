/**
 * TEJ3M
 * By: Evan Pratten
 */

#define beep boop

// Pinouts. NOTE: These must support PWM
#define r_pin 11
#define g_pin 10
#define b_pin 9

String command = "";

// Write PWM data to each RGB output
void setPWMOutput(int r, int g, int b)
{
    analogWrite(r_pin, r);
    analogWrite(g_pin, g);
    analogWrite(b_pin, b);
}

int strsegToInt(char a, char b)
{
    return ((a - '0') * 10) + (b - '0');
}

void setup()
{

    // Set up, and clear each pin
    pinMode(r_pin, OUTPUT);
    digitalWrite(r_pin, LOW);
    pinMode(g_pin, OUTPUT);
    digitalWrite(g_pin, LOW);
    pinMode(b_pin, OUTPUT);
    digitalWrite(b_pin, LOW);

    // Start a serial conn
    Serial.begin(9600);
}

void loop()
{
    // Read a string from input

    if (Serial.available() > 0)
    {
        command = "";
        while (Serial.available() > 0)
        {
            command += char(Serial.read());
            delay(2);
        }

        Serial.println(command);
    }

    // Handle RAW RGB data
    if (command[0] == '(')
    {

        // Set and map RGB colors from encdec
        int r = map(strsegToInt(command[1], command[2]), 0, 99, 0, 255);
        int g = map(strsegToInt(command[3], command[4]), 0, 99, 0, 255);
        int b = map(strsegToInt(command[5], command[6]), 0, 99, 0, 255);

        // Set the PWM outputs
        setPWMOutput(r, g, b);

        return;
    }

    // Uppercase the command
    command.toUpperCase();

    // Handle colours
    if (command == "BLUE")
    {
        setPWMOutput(0, 0, 255);
    }
    else if (command == "GREEN")
    {
        setPWMOutput(0, 255, 0);
    }
    else if (command == "RED")
    {
        setPWMOutput(255, 0, 0);
    }
}