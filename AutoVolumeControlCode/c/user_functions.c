#include <stdio.h> /*printf*/
#include <stdlib.h> /*system*/

#include "user_functions.h"
#include "main_functions.h"

//TODO: how to read from file, without excat address?
const char *USER_FILE = "/home/myth/Desktop/my_projects/AutoVolumeControl/user_output/user_profile_1.txt";
const char *RATING_SOUND = "/home/myth/Desktop/my_projects/AutoVolumeControl/texts/rating_sounds.txt";
const int MAX_SOUND_RATE = 3;

/**
 * @ setting user hearing profile
 */
volume_level UserProfiling()
{
    while(!IsEarphonePlugged())
    {
        system("clear");
        printf("Please plug in your headphones\n");
        sleep(3);
    }
    volume_level user_profile = ReturnUserProfile();
    return 0 == user_profile ? ReturnAvgFirstTime() : user_profile;
}

void SaveUserProfile(volume_level rating)
{
    FILE *user_profile = fopen(USER_FILE, "w");
    if (NULL == user_profile)
    {
        perror("Error opening user_profile.txt");
        exit(1);
    }
    fprintf(user_profile, "%ld", rating);
    fclose(user_profile);
}

/**
 * @ get user profile data from file 
 */
volume_level ReturnUserProfile()
{
    FILE *user_profile = fopen(USER_FILE, "r");
    char *user_input = (char *)malloc(sizeof(char));
    if (NULL == user_profile)
    {
        return 0;
    }
    //
    fgets(user_input, sizeof(user_input), user_profile);
    fclose(user_profile);
    volume_level rating = atoi(user_input);
    free(user_input);
    return rating;
}

void PrintRatingSoundText()
{
    FILE *rating_sound_text = fopen(RATING_SOUND, "r");
    char rating_sound_text_buffer[BASIC_BUFFER_SIZE] = {0};
    if (NULL == rating_sound_text)
    {
        perror("Error opening rating_sound_text.txt");
        exit(1);
    }
    while(fgets(rating_sound_text_buffer, sizeof(rating_sound_text_buffer), rating_sound_text))
    {
        printf("%s", rating_sound_text_buffer);
    }
    fclose(rating_sound_text);
}

//TODO make better test
volume_level ReturnAvgFirstTime()
{
    volume_level rating = 0;
    volume_level avg_rate = 40;
    char *user_input = (char *)malloc(sizeof(char));
    printf("\n");
    /*setting volume to 40, a bit lower then 60, the db average*/
    SetAlsaMasterVolume(avg_rate);

    for(int i = 0; i < MAX_SOUND_RATE; i++)
    {
        //TODO: how to read from file, without excat address?
        system("mpg123 /home/myth/Desktop/my_projects/AutoVolumeControl/audio_samples/chirping.mp3"); //TODO: run over 5 different sounds to rate
        sleep(1);
        system("clear");
        PrintRatingSoundText();

        printf("\n");
        printf("Sound %d: ", i+1);
        printf("\n");
        printf("Please rate the sound - ");

        /*add protection for numbers between 1-5 only*/
        fgets(user_input, sizeof(rating), stdin); 
        rating += atoi(user_input);
    }
    rating = (rating / MAX_SOUND_RATE) * 10;
    SaveUserProfile(rating);
    // SaveUserProfile(avg_rate);
    free(user_input);
    return rating;
}