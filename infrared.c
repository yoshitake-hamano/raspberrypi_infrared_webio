#include <wiringPi.h>

#include <iostream>
#include <vector>
using namespace std;

#define INFRARED_LED 4

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

static void flushInfrared(const vector<int>& data)
{
    for (int i=0; i<data.size(); i++) {
        if ((i % 2) == 0) {
            digitalWrite(INFRARED_LED, 1);
        } else {
            digitalWrite(INFRARED_LED, 0);
        }
        delayMicroseconds(i / 2);
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

