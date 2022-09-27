#ifndef _AutoVolumeControl_Amit_Nudel__
#define _AutoVolumeControl_Amit_Nudel__


#include <alsa/asoundlib.h> /*alsa*/
#include <sys/types.h>

typedef float amplitude_level;
typedef long volume_level;

void ProgramRun();
amplitude_level AmplitudeAverage();
void SetAlsaMasterVolume(long volume);
amplitude_level GetAmplitudeLevel(void);
amplitude_level dBToAmp(int db);
volume_level AmpTodB(amplitude_level num_amplitude_level);
int IsEarphonePlugged();

#endif /* _AutoVolumeControl_Amit_Nudel_ */

