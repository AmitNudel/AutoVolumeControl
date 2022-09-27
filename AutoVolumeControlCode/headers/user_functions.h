#ifndef _USER__
#define _USER__

typedef long volume_level;

volume_level UserPrompt();
volume_level UserProfiling();
void SaveUserProfile(volume_level rating);
volume_level ReturnUserProfile();
void RatingSoundText();
volume_level ReturnAvgFirstTime();

const int BASIC_BUFFER_SIZE = 256;

#endif /* _USER_ */
