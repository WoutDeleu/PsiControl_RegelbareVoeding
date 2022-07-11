const int DEFAULT_DELAY_MS = 2;

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
    // Range lowers voltage send to measure channel depending on the range
    // e.g. voltage = 15, Bi30 -> voltage to measuring channel = 5
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
double measureRaw(MeasRange range)
{
    double measuredValue = analogRead(AD0);
    // Convert from analog value to correct voltage
    // 10 bits -> 1023 values
    // Default 5, needs to be multiplied with ranges
    double measuredVoltage = ((double)(range)*5 / (double)1023) * measuredValue;
    return measuredVoltage;
}