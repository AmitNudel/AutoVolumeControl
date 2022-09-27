#include <stdio.h>
#include "main_functions.h"
#include "tests.h"
#include "math.h"


void SoundTest()
{
    //play sound 1 -> chck pcm 
    //play sound 2 -> chck pcm
    //play sound 3 -> chck pcm
    //what ar th diffrncs btwn th pcm rsults? chck again, agftr chnaginc th bar to hight/lowr 
    
}


void AmplitudeTest()
{
    float amplitude = GetAmplitudeLevel();
    printf("%f\n", amplitude);
    int dB = AmpTodB(amplitude);
    printf("dB: %i\n", dB);

    dB = AmpTodB(1000.0);
    printf("dB: %i\n", dB);

    amplitude = dBToAmp(60);
    printf("%f\n", amplitude);

    amplitude = dBToAmp(89);
    printf("%f\n", amplitude);
}

void Tests()
{
    AmplitudeTest();
}