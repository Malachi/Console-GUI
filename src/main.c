#include <stdlib.h>
#include "video.h"
#include "audio.h"

/**
 * Application Entry Point (EOP)
 * It calls a function that initializes the audio device and starts 
 * playing a song(Defined: audio.h | Implemented: audio.c). 
 * Then, it schedules a call to the function in charge of closing the
 * audio device so that this function is run when the program exits.
 * Finally, it calls a function that will initialize the video mode 
 * and take care of the rendering of the screen and event handling 
 * (Defined: video.h | audio.c).
 * 
 * @author Marcos Di Pietro
 */
int main() {
	

	audio_initialize("share/sound/music.wav");
	atexit(audio_close);

	video_initialize();
	
	
	
	return 0;
	
}
