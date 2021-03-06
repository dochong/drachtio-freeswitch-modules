#ifndef __MOD_FORK_H__
#define __MOD_FORK_H__

#include <switch.h>
#include <libwebsockets.h>
#include <speex/speex_resampler.h>

#include <unistd.h>

#define MY_BUG_NAME "audio_fork"
#define MAX_SESSION_ID (256)
#define MAX_WS_URL_LEN (512)
#define MAX_PATH_LEN (128)

enum {
	LWS_CLIENT_IDLE,
	LWS_CLIENT_CONNECTING,
	LWS_CLIENT_CONNECTED,
	LWS_CLIENT_FAILED,
	LWS_CLIENT_DISCONNECTING,
	LWS_CLIENT_DISCONNECTED
};

struct lws_per_vhost_data {
  struct lws_context *context;
  struct lws_vhost *vhost;
  const struct lws_protocols *protocol;
};

struct cap_cb {
	switch_mutex_t *mutex;
  switch_thread_cond_t *cond;
	char sessionId[MAX_SESSION_ID];
	char *base;
  SpeexResamplerState *resampler;
  int state;
  char host[MAX_WS_URL_LEN];
  unsigned int port;
  char path[MAX_PATH_LEN];
  uint8_t *metadata;
  size_t metadata_length;
  int sslFlags;
  int sampling;
  struct lws *wsi;
  uint8_t audio_buffer[LWS_PRE + (SWITCH_RECOMMENDED_BUFFER_SIZE << 1)];
  uint8_t* buf_head;
  struct lws_per_vhost_data* vhd;
};

#endif
