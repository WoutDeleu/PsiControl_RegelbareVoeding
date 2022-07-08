// const unsigned int DEFAULT_CHANNEL = 0;
// const unsigned int DEFAULT_COUNT = 1500;
// const double DEFAULT_GAIN = 1;
// const int DEFAULT_DELAY_MS = 2;
// MeasRange DEFAULT_BOARD_RANGE = MeasRange::Bi30;

// unsigned int channel = DEFAULT_CHANNEL;
// unsigned int count = DEFAULT_COUNT;
// double gain = DEFAULT_GAIN;
// double average = 0;
// double rms = 0;     // rms calculation does not substract average
// double truerms = 0; // truerms calculation substracts average -> AC rms value
// double max = 0;
// double min = 0;
// double pk2pk = 0;
// int DelayMs = DEFAULT_DELAY_MS;
// // Dynamisch lengte??? !!!
// double samples[4];
// bool trigger = false;
// MeasRange boardrange = DEFAULT_BOARD_RANGE;

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
        delay(RELAY_ON_SETTLING);
    }
}

// Daq.measure
double measure()
{
}
// void selectChannel(int channel, bool status)
// {
//     if (status)
//     {
//         if (channel <= 8)
//         {
//             // voltage is connected with the AD input
//             measureStatus = 0x28 | (channel - 1);
//         }
//         else
//         {
//             // voltage is connected with the AD input
//             measureStatus = 0x30 | (channel - 9);
//         }
//     }
//     else
//     {
//         measureStatus &= 0x80;
//     }
//     writeData(Register::MEASURE, measureStatus, boardNumber);
//     if (status)
//     {
//         delay(RELAY_ON_SETTLING);
//     }
// }
// void selectMeasRange()
// {
//     int rangeStatusCopy = rangeStatus;
//     switch (boardRange)
//     {
//     case MeasRange::Bi10:
//         rangeStatusCopy = (rangeStatusCopy & 0x3F) | 0x40;
//         break;
//     case MeasRange::Bi120:
//         rangeStatusCopy = (rangeStatusCopy & 0x3F) | 0x80;
//         break;
//     default:
//         rangeStatusCopy &= 0x3F;
//         break;
//     }
//     if (rangeStatus != rangeStatusCopy)
//     {
//         rangeStatus = rangeStatusCopy;
//         writeData(Register::RANGE, rangeStatusCopy, boardNumber);
//         delay(RELAY_ON_SETTLING);
//     }
// }

// // Daq.measure
// double measure()
// {
// }

// // SetTrigger?

// // RANGE???
