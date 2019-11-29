#define beep boop

const int pins[] = {2, 3, 4, 5, 6, 7, 8};
const int pin_count = sizeof(pins) / sizeof(pins[0]);

// Mapping of each digit to its pins
const int digits[][7] = {
    {0, 1, 2, 3, 4, 5},
    {0, 5, -1, -1, -1, -1},
    {0, 1, 3, 4, 6, -1, -1},
    {1, 2, 3, 4, 6, -1, -1},
    {2, 3, 5, 6, -1, -1, -1},
    {1, 2, 4, 5, 6, -1, -1},
    {0, 1, 2, 4, 5, 6, -1},
    {2, 3, 4, -1, -1, -1, -1},
    {0, 1, 2, 3, 4, 5, 6},
    {1, 2, 3, 4, 5, 6, -1},
    {0, 2, 3, 4, 5, 6, -1},
    {0, 1, 2, 5, 6, -1, -1},
    {0, 1, 4, 5, -1, -1, -1},
    {0, 1, 2, 3, -1, 6, -1},
    {0, 1, 4, 5, 6, -1, -1},
    {0, 4, 5, 6, -1, -1, -1}};
const int digit_count = sizeof(digits) / sizeof(digits[0]);

int counter = 0;

void setup()
{
    // Init and clear all pins
    for (int i = 0; i < pin_count; i++)
    {
        pinMode(pins[i], OUTPUT);
        digitalWrite(pins[i], LOW);
    }
}

void writeHexDig(int num)
{
    // Clear all pins
    for (int i = 0; i < pin_count; i++)
    {
        digitalWrite(pins[i], LOW);
    }

    // Iter each pin mapping in digits
    for (int i = 0; i < 7; i++)
    {
        int pin_index = digits[num][i];

        if (pin_index != -1)
        {
            digitalWrite(pins[pin_index], HIGH);
        }
    }
}

void loop()
{
    writeHexDig(counter);
    counter++;
    counter %= digit_count;

    delay(400);
}