#include <wiringPi.h>

#include <iostream>
#include <vector>
using namespace std;

#define INFRARED_LED       4
#define INFRARED_DUTY_HIGH 9
#define INFRARED_DUTY_LOW  17

static bool initializePio()
{
    if(wiringPiSetupGpio() == -1) return false;
    pinMode(INFRARED_LED, OUTPUT);
    return true;
}

static void readData(vector<int>& data)
{
    int i;
    while (cin >> i) {
        data.push_back(i);
    }
}

static void flushHigh(int us)
{
    int count = us / (INFRARED_DUTY_HIGH + INFRARED_DUTY_LOW);
    for (int i=0; i<count; i++) {
        digitalWrite(INFRARED_LED, 1);
        delayMicroseconds(INFRARED_DUTY_HIGH);
        digitalWrite(INFRARED_LED, 0);
        delayMicroseconds(INFRARED_DUTY_LOW);
    }
}

static void flushLow(int us)
{
    digitalWrite(INFRARED_LED, 0);
    delayMicroseconds(us);
}


static void flushInfrared(const vector<int>& data)
{
    for (int i=0; i<data.size(); i++) {
        if ((i % 2) == 0) {
            flushHigh(i);
        } else {
            flushLow(i);
        }
    }
}

int main(int argc, char *argv[])
{
    if (!initializePio()) {
        return 1;
    }

    vector<int> data;
    readData(data);
    flushInfrared(data);
}

