#ifndef __MOD_GOOGLE_TRANSCRIBE_H__
#define __MOD_GOOGLE_TRANSCRIBE_H__

#include <switch.h>
#include <speex/speex_resampler.h>

#include <unistd.h>

#define MY_BUG_NAME "google_transcribe"
#define TRANSCRIBE_EVENT_RESULTS "google_transcribe::transcription"


// simply write a wave file
//#define DEBUG_TRANSCRIBE 0


#ifdef DEBUG_TRANSCRIBE

/* per-channel data */
struct cap_cb {
	switch_buffer_t *buffer;
	switch_mutex_t *mutex;
	char *base;
    SpeexResamplerState *resampler;
    FILE* fp;
};
#else
/* per-channel data */
typedef void (*responseHandler_t)(switch_core_session_t* session, char* json);

struct cap_cb {
	switch_mutex_t *mutex;
    switch_core_session_t *session;
	char *base;
    SpeexResamplerState *resampler;
	void* streamer;
	responseHandler_t responseHandler;
	switch_thread_t* thread;
};
#endif

#endif