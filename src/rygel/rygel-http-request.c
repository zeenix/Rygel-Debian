/*
 * Copyright (C) 2008, 2009 Nokia Corporation, all rights reserved.
 * Copyright (C) 2006, 2007, 2008 OpenedHand Ltd.
 *
 * Author: Zeeshan Ali (Khattak) <zeeshanak@gnome.org>
 *                               <zeeshan.ali@nokia.com>
 *         Jorn Baayen <jorn.baayen@gmail.com>
 *
 * This file is part of Rygel.
 *
 * Rygel is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Rygel is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#include <glib.h>
#include <glib-object.h>
#include <libsoup/soup.h>
#include <gio/gio.h>
#include <stdlib.h>
#include <string.h>
#include <gee/arraylist.h>
#include <libgupnp-av/gupnp-av.h>
#include <gst/gst.h>
#include <gee/collection.h>
#include <gee/list.h>


#define RYGEL_TYPE_STATE_MACHINE (rygel_state_machine_get_type ())
#define RYGEL_STATE_MACHINE(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_STATE_MACHINE, RygelStateMachine))
#define RYGEL_IS_STATE_MACHINE(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_STATE_MACHINE))
#define RYGEL_STATE_MACHINE_GET_INTERFACE(obj) (G_TYPE_INSTANCE_GET_INTERFACE ((obj), RYGEL_TYPE_STATE_MACHINE, RygelStateMachineIface))

typedef struct _RygelStateMachine RygelStateMachine;
typedef struct _RygelStateMachineIface RygelStateMachineIface;

#define RYGEL_TYPE_HTTP_REQUEST (rygel_http_request_get_type ())
#define RYGEL_HTTP_REQUEST(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_HTTP_REQUEST, RygelHTTPRequest))
#define RYGEL_HTTP_REQUEST_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_HTTP_REQUEST, RygelHTTPRequestClass))
#define RYGEL_IS_HTTP_REQUEST(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_HTTP_REQUEST))
#define RYGEL_IS_HTTP_REQUEST_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_HTTP_REQUEST))
#define RYGEL_HTTP_REQUEST_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_HTTP_REQUEST, RygelHTTPRequestClass))

typedef struct _RygelHTTPRequest RygelHTTPRequest;
typedef struct _RygelHTTPRequestClass RygelHTTPRequestClass;
typedef struct _RygelHTTPRequestPrivate RygelHTTPRequestPrivate;

#define RYGEL_TYPE_TRANSCODE_MANAGER (rygel_transcode_manager_get_type ())
#define RYGEL_TRANSCODE_MANAGER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_TRANSCODE_MANAGER, RygelTranscodeManager))
#define RYGEL_TRANSCODE_MANAGER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_TRANSCODE_MANAGER, RygelTranscodeManagerClass))
#define RYGEL_IS_TRANSCODE_MANAGER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_TRANSCODE_MANAGER))
#define RYGEL_IS_TRANSCODE_MANAGER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_TRANSCODE_MANAGER))
#define RYGEL_TRANSCODE_MANAGER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_TRANSCODE_MANAGER, RygelTranscodeManagerClass))

typedef struct _RygelTranscodeManager RygelTranscodeManager;
typedef struct _RygelTranscodeManagerClass RygelTranscodeManagerClass;

#define RYGEL_TYPE_HTTP_SERVER (rygel_http_server_get_type ())
#define RYGEL_HTTP_SERVER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_HTTP_SERVER, RygelHTTPServer))
#define RYGEL_HTTP_SERVER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_HTTP_SERVER, RygelHTTPServerClass))
#define RYGEL_IS_HTTP_SERVER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_HTTP_SERVER))
#define RYGEL_IS_HTTP_SERVER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_HTTP_SERVER))
#define RYGEL_HTTP_SERVER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_HTTP_SERVER, RygelHTTPServerClass))

typedef struct _RygelHTTPServer RygelHTTPServer;
typedef struct _RygelHTTPServerClass RygelHTTPServerClass;

#define RYGEL_TYPE_MEDIA_OBJECT (rygel_media_object_get_type ())
#define RYGEL_MEDIA_OBJECT(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_MEDIA_OBJECT, RygelMediaObject))
#define RYGEL_MEDIA_OBJECT_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_MEDIA_OBJECT, RygelMediaObjectClass))
#define RYGEL_IS_MEDIA_OBJECT(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_MEDIA_OBJECT))
#define RYGEL_IS_MEDIA_OBJECT_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_MEDIA_OBJECT))
#define RYGEL_MEDIA_OBJECT_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_MEDIA_OBJECT, RygelMediaObjectClass))

typedef struct _RygelMediaObject RygelMediaObject;
typedef struct _RygelMediaObjectClass RygelMediaObjectClass;

#define RYGEL_TYPE_MEDIA_CONTAINER (rygel_media_container_get_type ())
#define RYGEL_MEDIA_CONTAINER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_MEDIA_CONTAINER, RygelMediaContainer))
#define RYGEL_MEDIA_CONTAINER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_MEDIA_CONTAINER, RygelMediaContainerClass))
#define RYGEL_IS_MEDIA_CONTAINER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_MEDIA_CONTAINER))
#define RYGEL_IS_MEDIA_CONTAINER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_MEDIA_CONTAINER))
#define RYGEL_MEDIA_CONTAINER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_MEDIA_CONTAINER, RygelMediaContainerClass))

typedef struct _RygelMediaContainer RygelMediaContainer;
typedef struct _RygelMediaContainerClass RygelMediaContainerClass;

#define RYGEL_TYPE_HTTP_RESPONSE (rygel_http_response_get_type ())
#define RYGEL_HTTP_RESPONSE(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_HTTP_RESPONSE, RygelHTTPResponse))
#define RYGEL_HTTP_RESPONSE_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_HTTP_RESPONSE, RygelHTTPResponseClass))
#define RYGEL_IS_HTTP_RESPONSE(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_HTTP_RESPONSE))
#define RYGEL_IS_HTTP_RESPONSE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_HTTP_RESPONSE))
#define RYGEL_HTTP_RESPONSE_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_HTTP_RESPONSE, RygelHTTPResponseClass))

typedef struct _RygelHTTPResponse RygelHTTPResponse;
typedef struct _RygelHTTPResponseClass RygelHTTPResponseClass;

#define RYGEL_TYPE_TRANSCODER (rygel_transcoder_get_type ())
#define RYGEL_TRANSCODER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_TRANSCODER, RygelTranscoder))
#define RYGEL_TRANSCODER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_TRANSCODER, RygelTranscoderClass))
#define RYGEL_IS_TRANSCODER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_TRANSCODER))
#define RYGEL_IS_TRANSCODER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_TRANSCODER))
#define RYGEL_TRANSCODER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_TRANSCODER, RygelTranscoderClass))

typedef struct _RygelTranscoder RygelTranscoder;
typedef struct _RygelTranscoderClass RygelTranscoderClass;

#define RYGEL_TYPE_MEDIA_ITEM (rygel_media_item_get_type ())
#define RYGEL_MEDIA_ITEM(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_MEDIA_ITEM, RygelMediaItem))
#define RYGEL_MEDIA_ITEM_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_MEDIA_ITEM, RygelMediaItemClass))
#define RYGEL_IS_MEDIA_ITEM(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_MEDIA_ITEM))
#define RYGEL_IS_MEDIA_ITEM_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_MEDIA_ITEM))
#define RYGEL_MEDIA_ITEM_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_MEDIA_ITEM, RygelMediaItemClass))

typedef struct _RygelMediaItem RygelMediaItem;
typedef struct _RygelMediaItemClass RygelMediaItemClass;

#define RYGEL_TYPE_SEEK (rygel_seek_get_type ())
#define RYGEL_SEEK(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_SEEK, RygelSeek))
#define RYGEL_SEEK_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_SEEK, RygelSeekClass))
#define RYGEL_IS_SEEK(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_SEEK))
#define RYGEL_IS_SEEK_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_SEEK))
#define RYGEL_SEEK_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_SEEK, RygelSeekClass))

typedef struct _RygelSeek RygelSeek;
typedef struct _RygelSeekClass RygelSeekClass;
typedef struct _RygelTranscodeManagerPrivate RygelTranscodeManagerPrivate;
typedef struct _RygelHTTPServerPrivate RygelHTTPServerPrivate;

#define RYGEL_TYPE_LIVE_RESPONSE (rygel_live_response_get_type ())
#define RYGEL_LIVE_RESPONSE(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_LIVE_RESPONSE, RygelLiveResponse))
#define RYGEL_LIVE_RESPONSE_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_LIVE_RESPONSE, RygelLiveResponseClass))
#define RYGEL_IS_LIVE_RESPONSE(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_LIVE_RESPONSE))
#define RYGEL_IS_LIVE_RESPONSE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_LIVE_RESPONSE))
#define RYGEL_LIVE_RESPONSE_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_LIVE_RESPONSE, RygelLiveResponseClass))

typedef struct _RygelLiveResponse RygelLiveResponse;
typedef struct _RygelLiveResponseClass RygelLiveResponseClass;

#define RYGEL_TYPE_SEEKABLE_RESPONSE (rygel_seekable_response_get_type ())
#define RYGEL_SEEKABLE_RESPONSE(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_SEEKABLE_RESPONSE, RygelSeekableResponse))
#define RYGEL_SEEKABLE_RESPONSE_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_SEEKABLE_RESPONSE, RygelSeekableResponseClass))
#define RYGEL_IS_SEEKABLE_RESPONSE(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_SEEKABLE_RESPONSE))
#define RYGEL_IS_SEEKABLE_RESPONSE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_SEEKABLE_RESPONSE))
#define RYGEL_SEEKABLE_RESPONSE_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_SEEKABLE_RESPONSE, RygelSeekableResponseClass))

typedef struct _RygelSeekableResponse RygelSeekableResponse;
typedef struct _RygelSeekableResponseClass RygelSeekableResponseClass;
typedef struct _RygelMediaObjectPrivate RygelMediaObjectPrivate;
typedef struct _RygelMediaItemPrivate RygelMediaItemPrivate;

typedef enum  {
	RYGEL_HTTP_REQUEST_ERROR_UNACCEPTABLE = SOUP_STATUS_NOT_ACCEPTABLE,
	RYGEL_HTTP_REQUEST_ERROR_INVALID_RANGE = SOUP_STATUS_BAD_REQUEST,
	RYGEL_HTTP_REQUEST_ERROR_OUT_OF_RANGE = SOUP_STATUS_REQUESTED_RANGE_NOT_SATISFIABLE,
	RYGEL_HTTP_REQUEST_ERROR_BAD_REQUEST = SOUP_STATUS_BAD_REQUEST,
	RYGEL_HTTP_REQUEST_ERROR_NOT_FOUND = SOUP_STATUS_NOT_FOUND
} RygelHTTPRequestError;
#define RYGEL_HTTP_REQUEST_ERROR rygel_http_request_error_quark ()
/**
 * StateMachine interface.
 */
struct _RygelStateMachineIface {
	GTypeInterface parent_iface;
	void (*run) (RygelStateMachine* self, GCancellable* cancellable);
};

/**
 * Responsible for handling HTTP client requests.
 */
struct _RygelHTTPRequest {
	GObject parent_instance;
	RygelHTTPRequestPrivate * priv;
};

struct _RygelHTTPRequestClass {
	GObjectClass parent_class;
};

struct _RygelHTTPRequestPrivate {
	RygelHTTPServer* http_server;
	RygelMediaContainer* root_container;
	SoupServer* server;
	SoupMessage* msg;
	GHashTable* query;
	RygelHTTPResponse* response;
	char* item_id;
	RygelTranscoder* transcoder;
	RygelMediaItem* item;
	RygelSeek* seek;
	GCancellable* cancellable;
};

/**
 * Responsible for management of all transcoders:
 *    - gets the appropriate transcoder given a transcoding target.
 *    - provide all possible transcoding resources for items.
 */
struct _RygelTranscodeManager {
	GObject parent_instance;
	RygelTranscodeManagerPrivate * priv;
};

struct _RygelTranscodeManagerClass {
	GObjectClass parent_class;
	char* (*create_uri_for_item) (RygelTranscodeManager* self, RygelMediaItem* item, const char* transcode_target, char** protocol);
	void (*add_resources) (RygelTranscodeManager* self, GeeArrayList* resources, RygelMediaItem* item, GError** error);
};

struct _RygelHTTPServer {
	RygelTranscodeManager parent_instance;
	RygelHTTPServerPrivate * priv;
	RygelMediaContainer* root_container;
};

struct _RygelHTTPServerClass {
	RygelTranscodeManagerClass parent_class;
};

/**
 * Represents a media object (container and item).
 */
struct _RygelMediaObject {
	GObject parent_instance;
	RygelMediaObjectPrivate * priv;
	char* id;
	char* title;
	RygelMediaContainer* parent;
};

struct _RygelMediaObjectClass {
	GObjectClass parent_class;
};

/**
 * Represents a media (Music, Video and Image) item.
 */
struct _RygelMediaItem {
	RygelMediaObject parent_instance;
	RygelMediaItemPrivate * priv;
	char* author;
	char* album;
	char* date;
	char* upnp_class;
	GeeArrayList* uris;
	char* mime_type;
	glong size;
	glong duration;
	gint bitrate;
	gint sample_freq;
	gint bits_per_sample;
	gint n_audio_channels;
	gint track_number;
	gint width;
	gint height;
	gint color_depth;
};

struct _RygelMediaItemClass {
	RygelMediaObjectClass parent_class;
	GstElement* (*create_stream_source) (RygelMediaItem* self);
};



GQuark rygel_http_request_error_quark (void);
GType rygel_state_machine_get_type (void);
GType rygel_http_request_get_type (void);
GType rygel_transcode_manager_get_type (void);
GType rygel_http_server_get_type (void);
GType rygel_media_object_get_type (void);
GType rygel_media_container_get_type (void);
GType rygel_http_response_get_type (void);
GType rygel_transcoder_get_type (void);
GType rygel_media_item_get_type (void);
GType rygel_seek_get_type (void);
#define RYGEL_HTTP_REQUEST_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), RYGEL_TYPE_HTTP_REQUEST, RygelHTTPRequestPrivate))
enum  {
	RYGEL_HTTP_REQUEST_DUMMY_PROPERTY
};
RygelHTTPRequest* rygel_http_request_new (RygelHTTPServer* http_server, SoupServer* server, SoupMessage* msg, GHashTable* query);
RygelHTTPRequest* rygel_http_request_construct (GType object_type, RygelHTTPServer* http_server, SoupServer* server, SoupMessage* msg, GHashTable* query);
RygelHTTPRequest* rygel_http_request_new (RygelHTTPServer* http_server, SoupServer* server, SoupMessage* msg, GHashTable* query);
static void rygel_http_request_handle_error (RygelHTTPRequest* self, GError* _error_);
RygelTranscoder* rygel_transcode_manager_get_transcoder (RygelTranscodeManager* self, const char* target, GError** error);
void rygel_media_container_find_object (RygelMediaContainer* self, const char* id, GCancellable* cancellable, GAsyncReadyCallback callback, void* callback_target);
static void rygel_http_request_on_item_found (RygelHTTPRequest* self, GObject* source_object, GAsyncResult* res);
static void _rygel_http_request_on_item_found_gasync_ready_callback (GObject* source_object, GAsyncResult* res, gpointer self);
static void rygel_http_request_real_run (RygelStateMachine* base, GCancellable* cancellable);
RygelLiveResponse* rygel_live_response_new (SoupServer* server, SoupMessage* msg, const char* name, GstElement* src, GError** error);
RygelLiveResponse* rygel_live_response_construct (GType object_type, SoupServer* server, SoupMessage* msg, const char* name, GstElement* src, GError** error);
GType rygel_live_response_get_type (void);
static void rygel_http_request_on_response_completed (RygelHTTPRequest* self, RygelHTTPResponse* response);
static void _rygel_http_request_on_response_completed_rygel_state_machine_completed (RygelLiveResponse* _sender, gpointer self);
void rygel_http_response_run (RygelHTTPResponse* self, GCancellable* cancellable);
static void rygel_http_request_stream_from_gst_source (RygelHTTPRequest* self, GstElement* src, GError** error);
RygelSeekableResponse* rygel_seekable_response_new (SoupServer* server, SoupMessage* msg, const char* uri, RygelSeek* seek, gsize file_length);
RygelSeekableResponse* rygel_seekable_response_construct (GType object_type, SoupServer* server, SoupMessage* msg, const char* uri, RygelSeek* seek, gsize file_length);
GType rygel_seekable_response_get_type (void);
static void rygel_http_request_serve_uri (RygelHTTPRequest* self, const char* uri, gsize size);
void rygel_http_request_end (RygelHTTPRequest* self, guint status);
static void rygel_http_request_parse_range (RygelHTTPRequest* self, GError** error);
static void rygel_http_request_add_item_headers (RygelHTTPRequest* self);
static void rygel_http_request_handle_interactive_item (RygelHTTPRequest* self, const char* uri);
static void rygel_http_request_handle_streaming_item (RygelHTTPRequest* self, const char* uri);
static void rygel_http_request_handle_item_request (RygelHTTPRequest* self);
const char* rygel_transcoder_get_mime_type (RygelTranscoder* self);
gint64 rygel_seek_get_start (RygelSeek* self);
gint64 rygel_seek_get_stop (RygelSeek* self);
GstElement* rygel_media_item_create_stream_source (RygelMediaItem* self);
static inline void _dynamic_set_tcp_timeout0 (GstElement* obj, gint64 value);
GstElement* rygel_transcoder_create_source (RygelTranscoder* self, GstElement* src, GError** error);
RygelSeek* rygel_seek_new (GstFormat format, gint64 start, gint64 stop);
RygelSeek* rygel_seek_construct (GType object_type, GstFormat format, gint64 start, gint64 stop);
void rygel_seek_set_start (RygelSeek* self, gint64 value);
void rygel_seek_set_stop (RygelSeek* self, gint64 value);
gint64 rygel_seek_get_length (RygelSeek* self);
RygelMediaObject* rygel_media_container_find_object_finish (RygelMediaContainer* self, GAsyncResult* res, GError** error);
static gpointer rygel_http_request_parent_class = NULL;
static RygelStateMachineIface* rygel_http_request_rygel_state_machine_parent_iface = NULL;
static void rygel_http_request_finalize (GObject* obj);
static void _vala_array_destroy (gpointer array, gint array_length, GDestroyNotify destroy_func);
static void _vala_array_free (gpointer array, gint array_length, GDestroyNotify destroy_func);
static gint _vala_array_length (gpointer array);
static int _vala_strcmp0 (const char * str1, const char * str2);



GQuark rygel_http_request_error_quark (void) {
	return g_quark_from_static_string ("rygel_http_request_error-quark");
}


RygelHTTPRequest* rygel_http_request_construct (GType object_type, RygelHTTPServer* http_server, SoupServer* server, SoupMessage* msg, GHashTable* query) {
	RygelHTTPRequest * self;
	RygelMediaContainer* _tmp1_;
	RygelMediaContainer* _tmp0_;
	SoupServer* _tmp3_;
	SoupServer* _tmp2_;
	SoupMessage* _tmp5_;
	SoupMessage* _tmp4_;
	GHashTable* _tmp7_;
	GHashTable* _tmp6_;
	g_return_val_if_fail (http_server != NULL, NULL);
	g_return_val_if_fail (server != NULL, NULL);
	g_return_val_if_fail (msg != NULL, NULL);
	self = g_object_newv (object_type, 0, NULL);
	self->priv->http_server = http_server;
	_tmp1_ = NULL;
	_tmp0_ = NULL;
	self->priv->root_container = (_tmp1_ = (_tmp0_ = http_server->root_container, (_tmp0_ == NULL) ? NULL : g_object_ref (_tmp0_)), (self->priv->root_container == NULL) ? NULL : (self->priv->root_container = (g_object_unref (self->priv->root_container), NULL)), _tmp1_);
	_tmp3_ = NULL;
	_tmp2_ = NULL;
	self->priv->server = (_tmp3_ = (_tmp2_ = server, (_tmp2_ == NULL) ? NULL : g_object_ref (_tmp2_)), (self->priv->server == NULL) ? NULL : (self->priv->server = (g_object_unref (self->priv->server), NULL)), _tmp3_);
	_tmp5_ = NULL;
	_tmp4_ = NULL;
	self->priv->msg = (_tmp5_ = (_tmp4_ = msg, (_tmp4_ == NULL) ? NULL : g_object_ref (_tmp4_)), (self->priv->msg == NULL) ? NULL : (self->priv->msg = (g_object_unref (self->priv->msg), NULL)), _tmp5_);
	_tmp7_ = NULL;
	_tmp6_ = NULL;
	self->priv->query = (_tmp7_ = (_tmp6_ = query, (_tmp6_ == NULL) ? NULL : g_hash_table_ref (_tmp6_)), (self->priv->query == NULL) ? NULL : (self->priv->query = (g_hash_table_unref (self->priv->query), NULL)), _tmp7_);
	soup_server_pause_message (self->priv->server, self->priv->msg);
	return self;
}


RygelHTTPRequest* rygel_http_request_new (RygelHTTPServer* http_server, SoupServer* server, SoupMessage* msg, GHashTable* query) {
	return rygel_http_request_construct (RYGEL_TYPE_HTTP_REQUEST, http_server, server, msg, query);
}


static void _rygel_http_request_on_item_found_gasync_ready_callback (GObject* source_object, GAsyncResult* res, gpointer self) {
	rygel_http_request_on_item_found (self, source_object, res);
}


static void rygel_http_request_real_run (RygelStateMachine* base, GCancellable* cancellable) {
	RygelHTTPRequest * self;
	GError * _inner_error_;
	GCancellable* _tmp1_;
	GCancellable* _tmp0_;
	gboolean _tmp2_;
	char* _tmp4_;
	char* _tmp3_;
	gboolean _tmp5_;
	self = (RygelHTTPRequest*) base;
	_inner_error_ = NULL;
	_tmp1_ = NULL;
	_tmp0_ = NULL;
	self->priv->cancellable = (_tmp1_ = (_tmp0_ = cancellable, (_tmp0_ == NULL) ? NULL : g_object_ref (_tmp0_)), (self->priv->cancellable == NULL) ? NULL : (self->priv->cancellable = (g_object_unref (self->priv->cancellable), NULL)), _tmp1_);
	_tmp2_ = FALSE;
	_tmp4_ = NULL;
	_tmp3_ = NULL;
	if ((_tmp5_ = _vala_strcmp0 (_tmp4_ = (g_object_get (self->priv->msg, "method", &_tmp3_, NULL), _tmp3_), "HEAD") != 0, _tmp4_ = (g_free (_tmp4_), NULL), _tmp5_)) {
		char* _tmp7_;
		char* _tmp6_;
		_tmp7_ = NULL;
		_tmp6_ = NULL;
		_tmp2_ = _vala_strcmp0 (_tmp7_ = (g_object_get (self->priv->msg, "method", &_tmp6_, NULL), _tmp6_), "GET") != 0;
		_tmp7_ = (g_free (_tmp7_), NULL);
	} else {
		_tmp2_ = FALSE;
	}
	if (_tmp2_) {
		GError* _tmp8_;
		/* We only entertain 'HEAD' and 'GET' requests */
		_tmp8_ = NULL;
		rygel_http_request_handle_error (self, _tmp8_ = g_error_new_literal (RYGEL_HTTP_REQUEST_ERROR, RYGEL_HTTP_REQUEST_ERROR_BAD_REQUEST, "Invalid Request"));
		(_tmp8_ == NULL) ? NULL : (_tmp8_ = (g_error_free (_tmp8_), NULL));
		return;
	}
	if (self->priv->query != NULL) {
		char* _tmp10_;
		const char* _tmp9_;
		const char* _tmp11_;
		char* transcode_target;
		_tmp10_ = NULL;
		_tmp9_ = NULL;
		self->priv->item_id = (_tmp10_ = (_tmp9_ = (const char*) g_hash_table_lookup (self->priv->query, "itemid"), (_tmp9_ == NULL) ? NULL : g_strdup (_tmp9_)), self->priv->item_id = (g_free (self->priv->item_id), NULL), _tmp10_);
		_tmp11_ = NULL;
		transcode_target = (_tmp11_ = (const char*) g_hash_table_lookup (self->priv->query, "transcode"), (_tmp11_ == NULL) ? NULL : g_strdup (_tmp11_));
		if (transcode_target != NULL) {
			RygelTranscoder* _tmp12_;
			RygelTranscoder* _tmp13_;
			_tmp12_ = rygel_transcode_manager_get_transcoder ((RygelTranscodeManager*) self->priv->http_server, transcode_target, &_inner_error_);
			if (_inner_error_ != NULL) {
				transcode_target = (g_free (transcode_target), NULL);
				g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, _inner_error_->message);
				g_clear_error (&_inner_error_);
				return;
			}
			_tmp13_ = NULL;
			self->priv->transcoder = (_tmp13_ = _tmp12_, (self->priv->transcoder == NULL) ? NULL : (self->priv->transcoder = (g_object_unref (self->priv->transcoder), NULL)), _tmp13_);
		}
		transcode_target = (g_free (transcode_target), NULL);
	}
	if (self->priv->item_id == NULL) {
		GError* _tmp14_;
		_tmp14_ = NULL;
		rygel_http_request_handle_error (self, _tmp14_ = g_error_new_literal (RYGEL_HTTP_REQUEST_ERROR, RYGEL_HTTP_REQUEST_ERROR_NOT_FOUND, "Not Found"));
		(_tmp14_ == NULL) ? NULL : (_tmp14_ = (g_error_free (_tmp14_), NULL));
		return;
	}
	/* Fetch the requested item*/
	rygel_media_container_find_object (self->priv->root_container, self->priv->item_id, NULL, _rygel_http_request_on_item_found_gasync_ready_callback, self);
}


static void _rygel_http_request_on_response_completed_rygel_state_machine_completed (RygelLiveResponse* _sender, gpointer self) {
	rygel_http_request_on_response_completed (self, _sender);
}


static void rygel_http_request_stream_from_gst_source (RygelHTTPRequest* self, GstElement* src, GError** error) {
	GError * _inner_error_;
	RygelLiveResponse* response;
	RygelHTTPResponse* _tmp1_;
	RygelHTTPResponse* _tmp0_;
	g_return_if_fail (self != NULL);
	g_return_if_fail (src != NULL);
	_inner_error_ = NULL;
	response = rygel_live_response_new (self->priv->server, self->priv->msg, "RygelLiveResponse", src, &_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		(src == NULL) ? NULL : (src = (gst_object_unref (src), NULL));
		return;
	}
	_tmp1_ = NULL;
	_tmp0_ = NULL;
	self->priv->response = (_tmp1_ = (_tmp0_ = (RygelHTTPResponse*) response, (_tmp0_ == NULL) ? NULL : g_object_ref (_tmp0_)), (self->priv->response == NULL) ? NULL : (self->priv->response = (g_object_unref (self->priv->response), NULL)), _tmp1_);
	g_signal_connect_object ((RygelStateMachine*) response, "completed", (GCallback) _rygel_http_request_on_response_completed_rygel_state_machine_completed, self, 0);
	rygel_http_response_run ((RygelHTTPResponse*) response, self->priv->cancellable);
	(response == NULL) ? NULL : (response = (g_object_unref (response), NULL));
	(src == NULL) ? NULL : (src = (gst_object_unref (src), NULL));
}


static void rygel_http_request_serve_uri (RygelHTTPRequest* self, const char* uri, gsize size) {
	RygelSeekableResponse* response;
	RygelHTTPResponse* _tmp1_;
	RygelHTTPResponse* _tmp0_;
	g_return_if_fail (self != NULL);
	g_return_if_fail (uri != NULL);
	response = rygel_seekable_response_new (self->priv->server, self->priv->msg, uri, self->priv->seek, size);
	_tmp1_ = NULL;
	_tmp0_ = NULL;
	self->priv->response = (_tmp1_ = (_tmp0_ = (RygelHTTPResponse*) response, (_tmp0_ == NULL) ? NULL : g_object_ref (_tmp0_)), (self->priv->response == NULL) ? NULL : (self->priv->response = (g_object_unref (self->priv->response), NULL)), _tmp1_);
	g_signal_connect_object ((RygelStateMachine*) response, "completed", (GCallback) _rygel_http_request_on_response_completed_rygel_state_machine_completed, self, 0);
	rygel_http_response_run ((RygelHTTPResponse*) response, self->priv->cancellable);
	(response == NULL) ? NULL : (response = (g_object_unref (response), NULL));
}


static void rygel_http_request_on_response_completed (RygelHTTPRequest* self, RygelHTTPResponse* response) {
	g_return_if_fail (self != NULL);
	g_return_if_fail (response != NULL);
	rygel_http_request_end (self, (guint) SOUP_STATUS_NONE);
}


static void rygel_http_request_handle_item_request (RygelHTTPRequest* self) {
	GError * _inner_error_;
	char* _tmp1_;
	char* _tmp0_;
	gboolean _tmp2_;
	char* uri;
	gboolean _tmp4_;
	g_return_if_fail (self != NULL);
	_inner_error_ = NULL;
	{
		rygel_http_request_parse_range (self, &_inner_error_);
		if (_inner_error_ != NULL) {
			goto __catch9_g_error;
			goto __finally9;
		}
	}
	goto __finally9;
	__catch9_g_error:
	{
		GError * _error_;
		_error_ = _inner_error_;
		_inner_error_ = NULL;
		{
			rygel_http_request_handle_error (self, _error_);
			(_error_ == NULL) ? NULL : (_error_ = (g_error_free (_error_), NULL));
			return;
		}
	}
	__finally9:
	if (_inner_error_ != NULL) {
		g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, _inner_error_->message);
		g_clear_error (&_inner_error_);
		return;
	}
	/* Add headers*/
	rygel_http_request_add_item_headers (self);
	_tmp1_ = NULL;
	_tmp0_ = NULL;
	if ((_tmp2_ = _vala_strcmp0 (_tmp1_ = (g_object_get (self->priv->msg, "method", &_tmp0_, NULL), _tmp0_), "HEAD") == 0, _tmp1_ = (g_free (_tmp1_), NULL), _tmp2_)) {
		/* Only headers requested, no need to send contents*/
		rygel_http_request_end (self, (guint) SOUP_STATUS_OK);
		return;
	}
	/* Just use the first URI available*/
	uri = NULL;
	if (gee_collection_get_size ((GeeCollection*) self->priv->item->uris) != 0) {
		char* _tmp3_;
		_tmp3_ = NULL;
		uri = (_tmp3_ = (char*) gee_list_get ((GeeList*) self->priv->item->uris, 0), uri = (g_free (uri), NULL), _tmp3_);
	}
	_tmp4_ = FALSE;
	if (self->priv->item->size > 0) {
		_tmp4_ = self->priv->transcoder == NULL;
	} else {
		_tmp4_ = FALSE;
	}
	if (_tmp4_) {
		rygel_http_request_handle_interactive_item (self, uri);
	} else {
		rygel_http_request_handle_streaming_item (self, uri);
	}
	uri = (g_free (uri), NULL);
}


static void rygel_http_request_add_item_headers (RygelHTTPRequest* self) {
	g_return_if_fail (self != NULL);
	if (self->priv->transcoder != NULL) {
		soup_message_headers_append (self->priv->msg->response_headers, "Content-Type", rygel_transcoder_get_mime_type (self->priv->transcoder));
		return;
	}
	if (self->priv->item->mime_type != NULL) {
		soup_message_headers_append (self->priv->msg->response_headers, "Content-Type", self->priv->item->mime_type);
	}
	if (self->priv->item->size >= 0) {
		soup_message_headers_set_content_length (self->priv->msg->response_headers, (gint64) self->priv->item->size);
	}
	if (self->priv->item->size > 0) {
		gint64 first_byte;
		gint64 last_byte;
		char* _tmp6_;
		char* _tmp5_;
		char* _tmp4_;
		char* _tmp3_;
		char* _tmp2_;
		char* _tmp1_;
		char* _tmp0_;
		char* _tmp7_;
		char* content_range;
		first_byte = 0LL;
		last_byte = 0LL;
		if (self->priv->seek != NULL) {
			first_byte = rygel_seek_get_start (self->priv->seek);
			last_byte = rygel_seek_get_stop (self->priv->seek);
		} else {
			first_byte = (gint64) 0;
			last_byte = (gint64) (self->priv->item->size - 1);
		}
		/* Content-Range: bytes START_BYTE-STOP_BYTE/TOTAL_LENGTH*/
		_tmp6_ = NULL;
		_tmp5_ = NULL;
		_tmp4_ = NULL;
		_tmp3_ = NULL;
		_tmp2_ = NULL;
		_tmp1_ = NULL;
		_tmp0_ = NULL;
		_tmp7_ = NULL;
		content_range = (_tmp7_ = g_strconcat (_tmp5_ = g_strconcat (_tmp4_ = g_strconcat (_tmp2_ = g_strconcat (_tmp1_ = g_strconcat ("bytes ", _tmp0_ = g_strdup_printf ("%lli", first_byte), NULL), "-", NULL), _tmp3_ = g_strdup_printf ("%lli", last_byte), NULL), "/", NULL), _tmp6_ = g_strdup_printf ("%li", self->priv->item->size), NULL), _tmp6_ = (g_free (_tmp6_), NULL), _tmp5_ = (g_free (_tmp5_), NULL), _tmp4_ = (g_free (_tmp4_), NULL), _tmp3_ = (g_free (_tmp3_), NULL), _tmp2_ = (g_free (_tmp2_), NULL), _tmp1_ = (g_free (_tmp1_), NULL), _tmp0_ = (g_free (_tmp0_), NULL), _tmp7_);
		soup_message_headers_append (self->priv->msg->response_headers, "Content-Range", content_range);
		soup_message_headers_append (self->priv->msg->response_headers, "Accept-Ranges", "bytes");
		content_range = (g_free (content_range), NULL);
	}
}


static inline void _dynamic_set_tcp_timeout0 (GstElement* obj, gint64 value) {
	g_object_set (obj, "tcp-timeout", value, NULL);
}


static void rygel_http_request_handle_streaming_item (RygelHTTPRequest* self, const char* uri) {
	GError * _inner_error_;
	GstElement* src;
	g_return_if_fail (self != NULL);
	_inner_error_ = NULL;
	src = NULL;
	if (uri != NULL) {
		GstElement* _tmp0_;
		/* URI provided, try to create source element from it*/
		_tmp0_ = NULL;
		src = (_tmp0_ = gst_element_make_from_uri (GST_URI_SRC, uri, NULL), (src == NULL) ? NULL : (src = (gst_object_unref (src), NULL)), _tmp0_);
	} else {
		GstElement* _tmp1_;
		/* No URI provided, ask for source element*/
		_tmp1_ = NULL;
		src = (_tmp1_ = rygel_media_item_create_stream_source (self->priv->item), (src == NULL) ? NULL : (src = (gst_object_unref (src), NULL)), _tmp1_);
	}
	if (src == NULL) {
		GError* _tmp2_;
		_tmp2_ = NULL;
		rygel_http_request_handle_error (self, _tmp2_ = g_error_new_literal (RYGEL_HTTP_REQUEST_ERROR, RYGEL_HTTP_REQUEST_ERROR_NOT_FOUND, "Not Found"));
		(_tmp2_ == NULL) ? NULL : (_tmp2_ = (g_error_free (_tmp2_), NULL));
		(src == NULL) ? NULL : (src = (gst_object_unref (src), NULL));
		return;
	}
	/* For rtspsrc since some RTSP sources takes a while to start
	 transmitting*/
	_dynamic_set_tcp_timeout0 (src, (gint64) 60000000);
	{
		GstElement* _tmp5_;
		if (self->priv->transcoder != NULL) {
			GstElement* _tmp3_;
			GstElement* _tmp4_;
			_tmp3_ = rygel_transcoder_create_source (self->priv->transcoder, src, &_inner_error_);
			if (_inner_error_ != NULL) {
				goto __catch10_g_error;
				goto __finally10;
			}
			_tmp4_ = NULL;
			src = (_tmp4_ = _tmp3_, (src == NULL) ? NULL : (src = (gst_object_unref (src), NULL)), _tmp4_);
		}
		/* Then start the gst stream*/
		_tmp5_ = NULL;
		rygel_http_request_stream_from_gst_source (self, (_tmp5_ = src, (_tmp5_ == NULL) ? NULL : gst_object_ref (_tmp5_)), &_inner_error_);
		if (_inner_error_ != NULL) {
			goto __catch10_g_error;
			goto __finally10;
		}
	}
	goto __finally10;
	__catch10_g_error:
	{
		GError * _error_;
		_error_ = _inner_error_;
		_inner_error_ = NULL;
		{
			rygel_http_request_handle_error (self, _error_);
			(_error_ == NULL) ? NULL : (_error_ = (g_error_free (_error_), NULL));
			(src == NULL) ? NULL : (src = (gst_object_unref (src), NULL));
			return;
		}
	}
	__finally10:
	if (_inner_error_ != NULL) {
		(src == NULL) ? NULL : (src = (gst_object_unref (src), NULL));
		g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, _inner_error_->message);
		g_clear_error (&_inner_error_);
		return;
	}
	(src == NULL) ? NULL : (src = (gst_object_unref (src), NULL));
}


static void rygel_http_request_handle_interactive_item (RygelHTTPRequest* self, const char* uri) {
	g_return_if_fail (self != NULL);
	if (uri == NULL) {
		GError* _error_;
		_error_ = g_error_new (RYGEL_HTTP_REQUEST_ERROR, RYGEL_HTTP_REQUEST_ERROR_NOT_FOUND, "Requested item '%s' didn't provide a URI\n", ((RygelMediaObject*) self->priv->item)->id);
		rygel_http_request_handle_error (self, _error_);
		(_error_ == NULL) ? NULL : (_error_ = (g_error_free (_error_), NULL));
		return;
	}
	rygel_http_request_serve_uri (self, uri, (gsize) self->priv->item->size);
}


static void rygel_http_request_parse_range (RygelHTTPRequest* self, GError** error) {
	GError * _inner_error_;
	char* range;
	gint range_tokens_size;
	gint range_tokens_length1;
	char** range_tokens;
	char* _tmp1_;
	const char* _tmp0_;
	char** _tmp3_;
	char** _tmp2_;
	gboolean _tmp4_;
	RygelSeek* _tmp5_;
	const char* _tmp6_;
	char* first_byte;
	const char* _tmp7_;
	char* last_byte;
	g_return_if_fail (self != NULL);
	_inner_error_ = NULL;
	range = NULL;
	range_tokens = (range_tokens_length1 = 0, NULL);
	_tmp1_ = NULL;
	_tmp0_ = NULL;
	range = (_tmp1_ = (_tmp0_ = soup_message_headers_get (self->priv->msg->request_headers, "Range"), (_tmp0_ == NULL) ? NULL : g_strdup (_tmp0_)), range = (g_free (range), NULL), _tmp1_);
	if (range == NULL) {
		range = (g_free (range), NULL);
		range_tokens = (_vala_array_free (range_tokens, range_tokens_length1, (GDestroyNotify) g_free), NULL);
		return;
	}
	/* We have a Range header. Parse.*/
	if (!g_str_has_prefix (range, "bytes=")) {
		_inner_error_ = g_error_new (RYGEL_HTTP_REQUEST_ERROR, RYGEL_HTTP_REQUEST_ERROR_INVALID_RANGE, "Invalid Range '%s'", range);
		if (_inner_error_ != NULL) {
			if (_inner_error_->domain == RYGEL_HTTP_REQUEST_ERROR) {
				g_propagate_error (error, _inner_error_);
				range = (g_free (range), NULL);
				range_tokens = (_vala_array_free (range_tokens, range_tokens_length1, (GDestroyNotify) g_free), NULL);
				return;
			} else {
				range = (g_free (range), NULL);
				range_tokens = (_vala_array_free (range_tokens, range_tokens_length1, (GDestroyNotify) g_free), NULL);
				g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, _inner_error_->message);
				g_clear_error (&_inner_error_);
				return;
			}
		}
	}
	_tmp3_ = NULL;
	_tmp2_ = NULL;
	range_tokens = (_tmp3_ = _tmp2_ = g_strsplit (g_utf8_offset_to_pointer (range, (glong) 6), "-", 2), range_tokens = (_vala_array_free (range_tokens, range_tokens_length1, (GDestroyNotify) g_free), NULL), range_tokens_length1 = _vala_array_length (_tmp2_), range_tokens_size = range_tokens_length1, _tmp3_);
	_tmp4_ = FALSE;
	if (range_tokens[0] == NULL) {
		_tmp4_ = TRUE;
	} else {
		_tmp4_ = range_tokens[1] == NULL;
	}
	if (_tmp4_) {
		_inner_error_ = g_error_new (RYGEL_HTTP_REQUEST_ERROR, RYGEL_HTTP_REQUEST_ERROR_INVALID_RANGE, "Invalid Range '%s'", range);
		if (_inner_error_ != NULL) {
			if (_inner_error_->domain == RYGEL_HTTP_REQUEST_ERROR) {
				g_propagate_error (error, _inner_error_);
				range = (g_free (range), NULL);
				range_tokens = (_vala_array_free (range_tokens, range_tokens_length1, (GDestroyNotify) g_free), NULL);
				return;
			} else {
				range = (g_free (range), NULL);
				range_tokens = (_vala_array_free (range_tokens, range_tokens_length1, (GDestroyNotify) g_free), NULL);
				g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, _inner_error_->message);
				g_clear_error (&_inner_error_);
				return;
			}
		}
	}
	_tmp5_ = NULL;
	self->priv->seek = (_tmp5_ = rygel_seek_new (GST_FORMAT_BYTES, (gint64) 0, (gint64) (self->priv->item->size - 1)), (self->priv->seek == NULL) ? NULL : (self->priv->seek = (g_object_unref (self->priv->seek), NULL)), _tmp5_);
	/* Get first byte position*/
	_tmp6_ = NULL;
	first_byte = (_tmp6_ = range_tokens[0], (_tmp6_ == NULL) ? NULL : g_strdup (_tmp6_));
	if (g_unichar_isdigit (g_utf8_get_char (g_utf8_offset_to_pointer (first_byte, 0)))) {
		rygel_seek_set_start (self->priv->seek, g_ascii_strtoll (first_byte, NULL, 0));
	} else {
		if (_vala_strcmp0 (first_byte, "") != 0) {
			_inner_error_ = g_error_new (RYGEL_HTTP_REQUEST_ERROR, RYGEL_HTTP_REQUEST_ERROR_INVALID_RANGE, "Invalid Range '%s'", range);
			if (_inner_error_ != NULL) {
				if (_inner_error_->domain == RYGEL_HTTP_REQUEST_ERROR) {
					g_propagate_error (error, _inner_error_);
					range = (g_free (range), NULL);
					range_tokens = (_vala_array_free (range_tokens, range_tokens_length1, (GDestroyNotify) g_free), NULL);
					first_byte = (g_free (first_byte), NULL);
					return;
				} else {
					range = (g_free (range), NULL);
					range_tokens = (_vala_array_free (range_tokens, range_tokens_length1, (GDestroyNotify) g_free), NULL);
					first_byte = (g_free (first_byte), NULL);
					g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, _inner_error_->message);
					g_clear_error (&_inner_error_);
					return;
				}
			}
		}
	}
	/* Get last byte position if specified*/
	_tmp7_ = NULL;
	last_byte = (_tmp7_ = range_tokens[1], (_tmp7_ == NULL) ? NULL : g_strdup (_tmp7_));
	if (g_unichar_isdigit (g_utf8_get_char (g_utf8_offset_to_pointer (last_byte, 0)))) {
		rygel_seek_set_stop (self->priv->seek, g_ascii_strtoll (last_byte, NULL, 0));
	} else {
		if (_vala_strcmp0 (last_byte, "") != 0) {
			_inner_error_ = g_error_new (RYGEL_HTTP_REQUEST_ERROR, RYGEL_HTTP_REQUEST_ERROR_INVALID_RANGE, "Invalid Range '%s'", range);
			if (_inner_error_ != NULL) {
				if (_inner_error_->domain == RYGEL_HTTP_REQUEST_ERROR) {
					g_propagate_error (error, _inner_error_);
					range = (g_free (range), NULL);
					range_tokens = (_vala_array_free (range_tokens, range_tokens_length1, (GDestroyNotify) g_free), NULL);
					first_byte = (g_free (first_byte), NULL);
					last_byte = (g_free (last_byte), NULL);
					return;
				} else {
					range = (g_free (range), NULL);
					range_tokens = (_vala_array_free (range_tokens, range_tokens_length1, (GDestroyNotify) g_free), NULL);
					first_byte = (g_free (first_byte), NULL);
					last_byte = (g_free (last_byte), NULL);
					g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, _inner_error_->message);
					g_clear_error (&_inner_error_);
					return;
				}
			}
		}
	}
	if (self->priv->item->size > 0) {
		gboolean _tmp8_;
		gboolean _tmp9_;
		_tmp8_ = FALSE;
		if (rygel_seek_get_start (self->priv->seek) > self->priv->item->size) {
			_tmp8_ = TRUE;
		} else {
			_tmp8_ = rygel_seek_get_length (self->priv->seek) > self->priv->item->size;
		}
		/* shouldn't go beyond actual length of media*/
		if (_tmp8_) {
			_inner_error_ = g_error_new (RYGEL_HTTP_REQUEST_ERROR, RYGEL_HTTP_REQUEST_ERROR_OUT_OF_RANGE, "Range '%s' not setsifiable", range);
			if (_inner_error_ != NULL) {
				if (_inner_error_->domain == RYGEL_HTTP_REQUEST_ERROR) {
					g_propagate_error (error, _inner_error_);
					range = (g_free (range), NULL);
					range_tokens = (_vala_array_free (range_tokens, range_tokens_length1, (GDestroyNotify) g_free), NULL);
					first_byte = (g_free (first_byte), NULL);
					last_byte = (g_free (last_byte), NULL);
					return;
				} else {
					range = (g_free (range), NULL);
					range_tokens = (_vala_array_free (range_tokens, range_tokens_length1, (GDestroyNotify) g_free), NULL);
					first_byte = (g_free (first_byte), NULL);
					last_byte = (g_free (last_byte), NULL);
					g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, _inner_error_->message);
					g_clear_error (&_inner_error_);
					return;
				}
			}
		}
		_tmp9_ = FALSE;
		if (rygel_seek_get_start (self->priv->seek) == 0) {
			_tmp9_ = rygel_seek_get_length (self->priv->seek) == self->priv->item->size;
		} else {
			_tmp9_ = FALSE;
		}
		/* No need to seek if whole stream is requested*/
		if (_tmp9_) {
			self->priv->seek == NULL;
			range = (g_free (range), NULL);
			range_tokens = (_vala_array_free (range_tokens, range_tokens_length1, (GDestroyNotify) g_free), NULL);
			first_byte = (g_free (first_byte), NULL);
			last_byte = (g_free (last_byte), NULL);
			return;
		}
	} else {
		if (rygel_seek_get_start (self->priv->seek) == 0) {
			/* Might be an attempt to get the size, in which case it's not
			 an error. Just don't seek.*/
			self->priv->seek == NULL;
			range = (g_free (range), NULL);
			range_tokens = (_vala_array_free (range_tokens, range_tokens_length1, (GDestroyNotify) g_free), NULL);
			first_byte = (g_free (first_byte), NULL);
			last_byte = (g_free (last_byte), NULL);
			return;
		} else {
			_inner_error_ = g_error_new (RYGEL_HTTP_REQUEST_ERROR, RYGEL_HTTP_REQUEST_ERROR_UNACCEPTABLE, "Partial download not applicable for item %s", ((RygelMediaObject*) self->priv->item)->id);
			if (_inner_error_ != NULL) {
				if (_inner_error_->domain == RYGEL_HTTP_REQUEST_ERROR) {
					g_propagate_error (error, _inner_error_);
					range = (g_free (range), NULL);
					range_tokens = (_vala_array_free (range_tokens, range_tokens_length1, (GDestroyNotify) g_free), NULL);
					first_byte = (g_free (first_byte), NULL);
					last_byte = (g_free (last_byte), NULL);
					return;
				} else {
					range = (g_free (range), NULL);
					range_tokens = (_vala_array_free (range_tokens, range_tokens_length1, (GDestroyNotify) g_free), NULL);
					first_byte = (g_free (first_byte), NULL);
					last_byte = (g_free (last_byte), NULL);
					g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, _inner_error_->message);
					g_clear_error (&_inner_error_);
					return;
				}
			}
		}
	}
	range = (g_free (range), NULL);
	range_tokens = (_vala_array_free (range_tokens, range_tokens_length1, (GDestroyNotify) g_free), NULL);
	first_byte = (g_free (first_byte), NULL);
	last_byte = (g_free (last_byte), NULL);
}


static void rygel_http_request_on_item_found (RygelHTTPRequest* self, GObject* source_object, GAsyncResult* res) {
	GError * _inner_error_;
	RygelMediaContainer* _tmp0_;
	RygelMediaContainer* container;
	RygelMediaObject* media_object;
	gboolean _tmp3_;
	RygelMediaItem* _tmp6_;
	RygelMediaItem* _tmp5_;
	g_return_if_fail (self != NULL);
	g_return_if_fail (source_object != NULL);
	g_return_if_fail (res != NULL);
	_inner_error_ = NULL;
	_tmp0_ = NULL;
	container = (_tmp0_ = RYGEL_MEDIA_CONTAINER (source_object), (_tmp0_ == NULL) ? NULL : g_object_ref (_tmp0_));
	media_object = NULL;
	{
		RygelMediaObject* _tmp1_;
		RygelMediaObject* _tmp2_;
		_tmp1_ = rygel_media_container_find_object_finish (container, res, &_inner_error_);
		if (_inner_error_ != NULL) {
			goto __catch11_g_error;
			goto __finally11;
		}
		_tmp2_ = NULL;
		media_object = (_tmp2_ = _tmp1_, (media_object == NULL) ? NULL : (media_object = (g_object_unref (media_object), NULL)), _tmp2_);
	}
	goto __finally11;
	__catch11_g_error:
	{
		GError * err;
		err = _inner_error_;
		_inner_error_ = NULL;
		{
			rygel_http_request_handle_error (self, err);
			(err == NULL) ? NULL : (err = (g_error_free (err), NULL));
			(container == NULL) ? NULL : (container = (g_object_unref (container), NULL));
			(media_object == NULL) ? NULL : (media_object = (g_object_unref (media_object), NULL));
			return;
		}
	}
	__finally11:
	if (_inner_error_ != NULL) {
		(container == NULL) ? NULL : (container = (g_object_unref (container), NULL));
		(media_object == NULL) ? NULL : (media_object = (g_object_unref (media_object), NULL));
		g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, _inner_error_->message);
		g_clear_error (&_inner_error_);
		return;
	}
	_tmp3_ = FALSE;
	if (media_object == NULL) {
		_tmp3_ = TRUE;
	} else {
		_tmp3_ = !RYGEL_IS_MEDIA_ITEM (media_object);
	}
	if (_tmp3_) {
		GError* _tmp4_;
		_tmp4_ = NULL;
		rygel_http_request_handle_error (self, _tmp4_ = g_error_new (RYGEL_HTTP_REQUEST_ERROR, RYGEL_HTTP_REQUEST_ERROR_NOT_FOUND, "requested item '%s' not found", self->priv->item_id));
		(_tmp4_ == NULL) ? NULL : (_tmp4_ = (g_error_free (_tmp4_), NULL));
		(container == NULL) ? NULL : (container = (g_object_unref (container), NULL));
		(media_object == NULL) ? NULL : (media_object = (g_object_unref (media_object), NULL));
		return;
	}
	_tmp6_ = NULL;
	_tmp5_ = NULL;
	self->priv->item = (_tmp6_ = (_tmp5_ = RYGEL_MEDIA_ITEM (media_object), (_tmp5_ == NULL) ? NULL : g_object_ref (_tmp5_)), (self->priv->item == NULL) ? NULL : (self->priv->item = (g_object_unref (self->priv->item), NULL)), _tmp6_);
	rygel_http_request_handle_item_request (self);
	(container == NULL) ? NULL : (container = (g_object_unref (container), NULL));
	(media_object == NULL) ? NULL : (media_object = (g_object_unref (media_object), NULL));
}


static void rygel_http_request_handle_error (RygelHTTPRequest* self, GError* _error_) {
	guint status;
	g_return_if_fail (self != NULL);
	g_warning ("rygel-http-request.vala:332: %s", _error_->message);
	status = 0U;
	if (_error_->domain == RYGEL_HTTP_REQUEST_ERROR) {
		status = (guint) _error_->code;
	} else {
		status = (guint) SOUP_STATUS_NOT_FOUND;
	}
	rygel_http_request_end (self, status);
}


void rygel_http_request_end (RygelHTTPRequest* self, guint status) {
	g_return_if_fail (self != NULL);
	if (status != SOUP_STATUS_NONE) {
		soup_message_set_status (self->priv->msg, status);
	}
	g_signal_emit_by_name ((RygelStateMachine*) self, "completed");
}


static void rygel_http_request_class_init (RygelHTTPRequestClass * klass) {
	rygel_http_request_parent_class = g_type_class_peek_parent (klass);
	g_type_class_add_private (klass, sizeof (RygelHTTPRequestPrivate));
	G_OBJECT_CLASS (klass)->finalize = rygel_http_request_finalize;
}


static void rygel_http_request_rygel_state_machine_interface_init (RygelStateMachineIface * iface) {
	rygel_http_request_rygel_state_machine_parent_iface = g_type_interface_peek_parent (iface);
	iface->run = rygel_http_request_real_run;
}


static void rygel_http_request_instance_init (RygelHTTPRequest * self) {
	self->priv = RYGEL_HTTP_REQUEST_GET_PRIVATE (self);
}


static void rygel_http_request_finalize (GObject* obj) {
	RygelHTTPRequest * self;
	self = RYGEL_HTTP_REQUEST (obj);
	(self->priv->root_container == NULL) ? NULL : (self->priv->root_container = (g_object_unref (self->priv->root_container), NULL));
	(self->priv->server == NULL) ? NULL : (self->priv->server = (g_object_unref (self->priv->server), NULL));
	(self->priv->msg == NULL) ? NULL : (self->priv->msg = (g_object_unref (self->priv->msg), NULL));
	(self->priv->query == NULL) ? NULL : (self->priv->query = (g_hash_table_unref (self->priv->query), NULL));
	(self->priv->response == NULL) ? NULL : (self->priv->response = (g_object_unref (self->priv->response), NULL));
	self->priv->item_id = (g_free (self->priv->item_id), NULL);
	(self->priv->transcoder == NULL) ? NULL : (self->priv->transcoder = (g_object_unref (self->priv->transcoder), NULL));
	(self->priv->item == NULL) ? NULL : (self->priv->item = (g_object_unref (self->priv->item), NULL));
	(self->priv->seek == NULL) ? NULL : (self->priv->seek = (g_object_unref (self->priv->seek), NULL));
	(self->priv->cancellable == NULL) ? NULL : (self->priv->cancellable = (g_object_unref (self->priv->cancellable), NULL));
	G_OBJECT_CLASS (rygel_http_request_parent_class)->finalize (obj);
}


GType rygel_http_request_get_type (void) {
	static GType rygel_http_request_type_id = 0;
	if (rygel_http_request_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (RygelHTTPRequestClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) rygel_http_request_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (RygelHTTPRequest), 0, (GInstanceInitFunc) rygel_http_request_instance_init, NULL };
		static const GInterfaceInfo rygel_state_machine_info = { (GInterfaceInitFunc) rygel_http_request_rygel_state_machine_interface_init, (GInterfaceFinalizeFunc) NULL, NULL};
		rygel_http_request_type_id = g_type_register_static (G_TYPE_OBJECT, "RygelHTTPRequest", &g_define_type_info, 0);
		g_type_add_interface_static (rygel_http_request_type_id, RYGEL_TYPE_STATE_MACHINE, &rygel_state_machine_info);
	}
	return rygel_http_request_type_id;
}


static void _vala_array_destroy (gpointer array, gint array_length, GDestroyNotify destroy_func) {
	if ((array != NULL) && (destroy_func != NULL)) {
		int i;
		for (i = 0; i < array_length; i = i + 1) {
			if (((gpointer*) array)[i] != NULL) {
				destroy_func (((gpointer*) array)[i]);
			}
		}
	}
}


static void _vala_array_free (gpointer array, gint array_length, GDestroyNotify destroy_func) {
	_vala_array_destroy (array, array_length, destroy_func);
	g_free (array);
}


static gint _vala_array_length (gpointer array) {
	int length;
	length = 0;
	if (array) {
		while (((gpointer*) array)[length]) {
			length++;
		}
	}
	return length;
}


static int _vala_strcmp0 (const char * str1, const char * str2) {
	if (str1 == NULL) {
		return -(str1 != str2);
	}
	if (str2 == NULL) {
		return str1 != str2;
	}
	return strcmp (str1, str2);
}




