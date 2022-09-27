#include <math.h> /*log, pow*/
#include <unistd.h>

#include "main_functions.h"
#include "user_functions.h"

        //TODO: how to read from file, without excat address?
const char *JACK_INFO_FILE = "/home/myth/Desktop/my_projects/AutoVolumeControl/texts/jack_info.txt";


amplitude_level dBToAmp(int db)
{
    return (float)pow(10.0 ,((double)db / 20.0));
}


volume_level AmpTodB(amplitude_level num_amplitude_level)
{
    return (volume_level)log10(num_amplitude_level) * 20;
}

/**
 * @ set computer audio volume to wanted value
 */
void SetAlsaMasterVolume(long volume)
{
    long min = 0;
    long max = 0;
    snd_mixer_t *handle = NULL;
    snd_mixer_selem_id_t *sid = NULL;
    const char *card = "default";
    const char *selem_name = "Master";

    /*handling the mixer handler and initializing it*/
    snd_mixer_open(&handle, 0);
    snd_mixer_attach(handle, card);
    snd_mixer_selem_register(handle, NULL, NULL);
    snd_mixer_load(handle);
    
    /*getting id of mixer and setting name*/
    snd_mixer_selem_id_alloca(&sid);
    snd_mixer_selem_id_set_index(sid, 0);
    snd_mixer_selem_id_set_name(sid, selem_name);
    snd_mixer_elem_t* elem = snd_mixer_find_selem(handle, sid);
    
    /*getting volume range and setting to wanted volume*/
    snd_mixer_selem_get_playback_volume_range(elem, &min, &max);
    snd_mixer_selem_set_playback_volume_all(elem, volume * max / 100);

    snd_mixer_close(handle);
    handle = NULL; 
}

amplitude_level GetAmplitudeLevel(void)
{
    amplitude_level result = 0.0f;
    /*audio stream source*/
    snd_pcm_t* waveform = NULL;
    short current_samples_buffer[BASIC_BUFFER_SIZE] = {0};
 
    /*Open and intialize waveform*/
    if (0 != snd_pcm_open(&waveform, "default",
        SND_PCM_STREAM_PLAYBACK, 0)) 
    {
        perror("Failed to open and initialize waveform\n");
        return result;
    }

    /*Set the hardware parameters*/
    if (!snd_pcm_set_params (waveform, SND_PCM_FORMAT_S16_LE,
        SND_PCM_ACCESS_RW_INTERLEAVED, 2, 44100, 1, 0) &&
        128 == snd_pcm_readi(waveform, current_samples_buffer, 128))
    { 
        /*Compute the maximum peak value*/
        for (int i = 0; i < BASIC_BUFFER_SIZE; ++i)
        {
            // amplitude_level sound = current_samples_buffer[i] / 32768.0f;
            amplitude_level sound = current_samples_buffer[i];
            if (sound < 0) 
            {
                sound *= -1;
            }

            if (result < sound) 
            {
                result = sound;
            }
        }
        
    }
    snd_pcm_close(waveform);
    return result;
}

amplitude_level AmplitudeAverage()
{
    amplitude_level amp_level = 0.0;
    for(int i = 0; i < 50; i++)
    {
        amp_level += GetAmplitudeLevel();
        printf("%f", amp_level);
    }
    return (amp_level / 50.0F);

}

int IsEarphonePlugged()
{
    /*exact sentence needed*/
    char wanted_input[] = 
    "analog-output-headphones: Headphones (priority 9900, latency offset 0 usec, available: yes)";

    char output_from_alsa[BASIC_BUFFER_SIZE] = {0}; 
    int result = 0;

    system("pacmd list-cards > /home/myth/Desktop/my_projects/AutoVolumeControl/texts/jack_info.txt");

    FILE *jack_info_file = fopen(JACK_INFO_FILE, "r");

    if (NULL == jack_info_file)
    {
        fclose(jack_info_file);
        perror("Error opening jack_info.txt");
    }

    /*jack info file, looking foe the wanted sentece*/
    while(fgets(output_from_alsa, sizeof(output_from_alsa), jack_info_file))
    {
        if (strstr(output_from_alsa, wanted_input))
        {
            result = 1;
        }
    }
    
    fclose(jack_info_file);
    return result;
}


void ProgramRun()
{
    /*get rating from user*/
    long user_volume = UserProfiling();
    
    system("clear");
    printf("Running...\n");

    SetAlsaMasterVolume(user_volume);
    
    while(1)
    {
        /*adjusting volume*/

        amplitude_level current_level = AmplitudeAverage();
        // current_level > user_volume ? SetAlsaMasterVolume(AmpTodB(current_level - user_volume)) : SetAlsaMasterVolume(AmpTodB(current_level + user_volume));
        if (current_level > user_volume)
        {
            amplitude_level fix = current_level - user_volume; 
            // printf("%ld", fix);
            SetAlsaMasterVolume(AmpTodB(user_volume - fix));
        }
        else if (current_level < user_volume)
        {
            amplitude_level fix = user_volume - current_level;
            // printf("%ld", fix); 
            SetAlsaMasterVolume(AmpTodB(user_volume + fix));
        }
        else
        {
            SetAlsaMasterVolume(user_volume);
        }
       
        // amplitude_level gap = current_level - user_volume;
        // gap > user_volume ? SetAlsaMasterVolume(AmpTodB(gap - user_volume)) : SetAlsaMasterVolume(AmpTodB(gap + user_volume));
  
    }
}
