const unsigned int DEFAULT_CHANNEL = 0;
const unsigned int DEFAULT_COUNT = 1500;
const int DEFAULT_DELAY_MS = 2;
const unsigned long DEFAULT_RATE = 100000;

unsigned long rate = DEFAULT_RATE;
unsigned int channel = DEFAULT_CHANNEL;
unsigned int count = DEFAULT_COUNT;
double average = 0;
double rms = 0;     // rms calculation does not substract average
double truerms = 0; // truerms calculation substracts average -> AC rms value
double max = 0;
double min = 0;
double pk2pk = 0;
int DelayMs = DEFAULT_DELAY_MS;
// bool trigger = false;

void selectChannel(int channel, bool status)
{
    if (status)
    {
        if (channel <= 8)
        {
            // voltage is connected with the AD input
            measureStatus = 0x28 | (channel - 1);
        }
        else
        {
            // voltage is connected with the AD input
            measureStatus = 0x30 | (channel - 9);
        }
    }
    else
    {
        measureStatus &= 0x80;
    }
    writeData(Register::MEASURE, measureStatus, boardNumber);
    if (status)
    {
        delay(RELAY_ON_SETTLING);
    }
}
void selectMeasRange(MeasRange range)
{
    int rangeStatusCopy = rangeStatus;
    switch (range)
    {
    case MeasRange::Bi10:
        rangeStatusCopy = (rangeStatusCopy & 0x3F) | 0x40;
        break;
    case MeasRange::Bi120:
        rangeStatusCopy = (rangeStatusCopy & 0x3F) | 0x80;
        break;
    default:
        rangeStatusCopy &= 0x3F;
        break;
    }
    if (rangeStatus != rangeStatusCopy)
    {
        rangeStatus = rangeStatusCopy;
        writeData(Register::RANGE, rangeStatusCopy, boardNumber);
        // settling time for the measure path.
        delay(RELAY_ON_SETTLING);
    }
}
double measureRaw()
{
    double measuredValue = analogRead(AD0);
    Serial.println("Measured Value = " + String(measuredValue));
    double measuredVoltage = ((double)3 / (double)1023) * measuredValue;
    return measuredVoltage;
}