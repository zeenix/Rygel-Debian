/*
 * Copyright (C) 2009 Nokia Corporation, all rights reserved.
 *
 * Author: Zeeshan Ali (Khattak) <zeeshanak@gnome.org>
 *                               <zeeshan.ali@nokia.com>
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
#include <stdlib.h>
#include <string.h>
#include <gee/arraylist.h>
#include <libgupnp-av/gupnp-av.h>
#include <gee/collection.h>
#include <gst/gst.h>
#include <gee/iterable.h>
#include <gee/iterator.h>
#include <libsoup/soup.h>


#define RYGEL_TYPE_TRANSCODE_MANAGER (rygel_transcode_manager_get_type ())
#define RYGEL_TRANSCODE_MANAGER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_TRANSCODE_MANAGER, RygelTranscodeManager))
#define RYGEL_TRANSCODE_MANAGER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_TRANSCODE_MANAGER, RygelTranscodeManagerClass))
#define RYGEL_IS_TRANSCODE_MANAGER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_TRANSCODE_MANAGER))
#define RYGEL_IS_TRANSCODE_MANAGER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_TRANSCODE_MANAGER))
#define RYGEL_TRANSCODE_MANAGER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_TRANSCODE_MANAGER, RygelTranscodeManagerClass))

typedef struct _RygelTranscodeManager RygelTranscodeManager;
typedef struct _RygelTranscodeManagerClass RygelTranscodeManagerClass;
typedef struct _RygelTranscodeManagerPrivate RygelTranscodeManagerPrivate;

#define RYGEL_TYPE_MEDIA_OBJECT (rygel_media_object_get_type ())
#define RYGEL_MEDIA_OBJECT(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_MEDIA_OBJECT, RygelMediaObject))
#define RYGEL_MEDIA_OBJECT_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_MEDIA_OBJECT, RygelMediaObjectClass))
#define RYGEL_IS_MEDIA_OBJECT(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_MEDIA_OBJECT))
#define RYGEL_IS_MEDIA_OBJECT_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_MEDIA_OBJECT))
#define RYGEL_MEDIA_OBJECT_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_MEDIA_OBJECT, RygelMediaObjectClass))

typedef struct _RygelMediaObject RygelMediaObject;
typedef struct _RygelMediaObjectClass RygelMediaObjectClass;

#define RYGEL_TYPE_MEDIA_ITEM (rygel_media_item_get_type ())
#define RYGEL_MEDIA_ITEM(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_MEDIA_ITEM, RygelMediaItem))
#define RYGEL_MEDIA_ITEM_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_MEDIA_ITEM, RygelMediaItemClass))
#define RYGEL_IS_MEDIA_ITEM(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_MEDIA_ITEM))
#define RYGEL_IS_MEDIA_ITEM_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_MEDIA_ITEM))
#define RYGEL_MEDIA_ITEM_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_MEDIA_ITEM, RygelMediaItemClass))

typedef struct _RygelMediaItem RygelMediaItem;
typedef struct _RygelMediaItemClass RygelMediaItemClass;

#define RYGEL_TYPE_TRANSCODER (rygel_transcoder_get_type ())
#define RYGEL_TRANSCODER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_TRANSCODER, RygelTranscoder))
#define RYGEL_TRANSCODER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_TRANSCODER, RygelTranscoderClass))
#define RYGEL_IS_TRANSCODER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_TRANSCODER))
#define RYGEL_IS_TRANSCODER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_TRANSCODER))
#define RYGEL_TRANSCODER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_TRANSCODER, RygelTranscoderClass))

typedef struct _RygelTranscoder RygelTranscoder;
typedef struct _RygelTranscoderClass RygelTranscoderClass;

#define RYGEL_TYPE_CONFIGURATION (rygel_configuration_get_type ())
#define RYGEL_CONFIGURATION(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_CONFIGURATION, RygelConfiguration))
#define RYGEL_CONFIGURATION_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_CONFIGURATION, RygelConfigurationClass))
#define RYGEL_IS_CONFIGURATION(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_CONFIGURATION))
#define RYGEL_IS_CONFIGURATION_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_CONFIGURATION))
#define RYGEL_CONFIGURATION_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_CONFIGURATION, RygelConfigurationClass))

typedef struct _RygelConfiguration RygelConfiguration;
typedef struct _RygelConfigurationClass RygelConfigurationClass;

#define TYPE_ENDIANNESS (endianness_get_type ())

#define RYGEL_TYPE_L16_TRANSCODER (rygel_l16_transcoder_get_type ())
#define RYGEL_L16_TRANSCODER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_L16_TRANSCODER, RygelL16Transcoder))
#define RYGEL_L16_TRANSCODER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_L16_TRANSCODER, RygelL16TranscoderClass))
#define RYGEL_IS_L16_TRANSCODER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_L16_TRANSCODER))
#define RYGEL_IS_L16_TRANSCODER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_L16_TRANSCODER))
#define RYGEL_L16_TRANSCODER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_L16_TRANSCODER, RygelL16TranscoderClass))

typedef struct _RygelL16Transcoder RygelL16Transcoder;
typedef struct _RygelL16TranscoderClass RygelL16TranscoderClass;

#define RYGEL_TYPE_MP3_LAYER (rygel_mp3_layer_get_type ())

#define RYGEL_TYPE_MP3_TRANSCODER (rygel_mp3_transcoder_get_type ())
#define RYGEL_MP3_TRANSCODER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_MP3_TRANSCODER, RygelMP3Transcoder))
#define RYGEL_MP3_TRANSCODER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_MP3_TRANSCODER, RygelMP3TranscoderClass))
#define RYGEL_IS_MP3_TRANSCODER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_MP3_TRANSCODER))
#define RYGEL_IS_MP3_TRANSCODER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_MP3_TRANSCODER))
#define RYGEL_MP3_TRANSCODER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_MP3_TRANSCODER, RygelMP3TranscoderClass))

typedef struct _RygelMP3Transcoder RygelMP3Transcoder;
typedef struct _RygelMP3TranscoderClass RygelMP3TranscoderClass;

#define RYGEL_TYPE_MP2_TS_PROFILE (rygel_mp2_ts_profile_get_type ())

#define RYGEL_TYPE_MP2_TS_TRANSCODER (rygel_mp2_ts_transcoder_get_type ())
#define RYGEL_MP2_TS_TRANSCODER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_MP2_TS_TRANSCODER, RygelMP2TSTranscoder))
#define RYGEL_MP2_TS_TRANSCODER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_MP2_TS_TRANSCODER, RygelMP2TSTranscoderClass))
#define RYGEL_IS_MP2_TS_TRANSCODER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_MP2_TS_TRANSCODER))
#define RYGEL_IS_MP2_TS_TRANSCODER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_MP2_TS_TRANSCODER))
#define RYGEL_MP2_TS_TRANSCODER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_MP2_TS_TRANSCODER, RygelMP2TSTranscoderClass))

typedef struct _RygelMP2TSTranscoder RygelMP2TSTranscoder;
typedef struct _RygelMP2TSTranscoderClass RygelMP2TSTranscoderClass;
typedef struct _RygelMediaObjectPrivate RygelMediaObjectPrivate;

#define RYGEL_TYPE_MEDIA_CONTAINER (rygel_media_container_get_type ())
#define RYGEL_MEDIA_CONTAINER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_MEDIA_CONTAINER, RygelMediaContainer))
#define RYGEL_MEDIA_CONTAINER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_MEDIA_CONTAINER, RygelMediaContainerClass))
#define RYGEL_IS_MEDIA_CONTAINER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_MEDIA_CONTAINER))
#define RYGEL_IS_MEDIA_CONTAINER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_MEDIA_CONTAINER))
#define RYGEL_MEDIA_CONTAINER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_MEDIA_CONTAINER, RygelMediaContainerClass))

typedef struct _RygelMediaContainer RygelMediaContainer;
typedef struct _RygelMediaContainerClass RygelMediaContainerClass;
typedef struct _RygelMediaItemPrivate RygelMediaItemPrivate;

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

struct _RygelTranscodeManagerPrivate {
	GeeArrayList* transcoders;
};

typedef enum  {
	ENDIANNESS_LITTLE = G_LITTLE_ENDIAN,
	ENDIANNESS_BIG = G_BIG_ENDIAN
} Endianness;

typedef enum  {
	RYGEL_MP3_LAYER_TWO = 1,
	RYGEL_MP3_LAYER_THREE = 2
} RygelMP3Layer;

typedef enum  {
	RYGEL_MP2_TS_PROFILE_SD = 0,
	RYGEL_MP2_TS_PROFILE_HD
} RygelMP2TSProfile;

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

typedef enum  {
	RYGEL_HTTP_REQUEST_ERROR_UNACCEPTABLE = SOUP_STATUS_NOT_ACCEPTABLE,
	RYGEL_HTTP_REQUEST_ERROR_INVALID_RANGE = SOUP_STATUS_BAD_REQUEST,
	RYGEL_HTTP_REQUEST_ERROR_OUT_OF_RANGE = SOUP_STATUS_REQUESTED_RANGE_NOT_SATISFIABLE,
	RYGEL_HTTP_REQUEST_ERROR_BAD_REQUEST = SOUP_STATUS_BAD_REQUEST,
	RYGEL_HTTP_REQUEST_ERROR_NOT_FOUND = SOUP_STATUS_NOT_FOUND
} RygelHTTPRequestError;
#define RYGEL_HTTP_REQUEST_ERROR rygel_http_request_error_quark ()


GType rygel_transcode_manager_get_type (void);
GType rygel_media_object_get_type (void);
GType rygel_media_item_get_type (void);
GType rygel_transcoder_get_type (void);
#define RYGEL_TRANSCODE_MANAGER_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), RYGEL_TYPE_TRANSCODE_MANAGER, RygelTranscodeManagerPrivate))
enum  {
	RYGEL_TRANSCODE_MANAGER_DUMMY_PROPERTY
};
GType rygel_configuration_get_type (void);
RygelConfiguration* rygel_configuration_get_default (void);
gboolean rygel_configuration_get_transcoding (RygelConfiguration* self);
gboolean rygel_configuration_get_lpcm_transcoder (RygelConfiguration* self);
GType endianness_get_type (void);
RygelL16Transcoder* rygel_l16_transcoder_new (Endianness endianness);
RygelL16Transcoder* rygel_l16_transcoder_construct (GType object_type, Endianness endianness);
GType rygel_l16_transcoder_get_type (void);
gboolean rygel_configuration_get_mp3_transcoder (RygelConfiguration* self);
GType rygel_mp3_layer_get_type (void);
RygelMP3Transcoder* rygel_mp3_transcoder_new (RygelMP3Layer layer);
RygelMP3Transcoder* rygel_mp3_transcoder_construct (GType object_type, RygelMP3Layer layer);
GType rygel_mp3_transcoder_get_type (void);
gboolean rygel_configuration_get_mp2ts_transcoder (RygelConfiguration* self);
GType rygel_mp2_ts_profile_get_type (void);
RygelMP2TSTranscoder* rygel_mp2_ts_transcoder_new (RygelMP2TSProfile profile);
RygelMP2TSTranscoder* rygel_mp2_ts_transcoder_construct (GType object_type, RygelMP2TSProfile profile);
GType rygel_mp2_ts_transcoder_get_type (void);
RygelTranscodeManager* rygel_transcode_manager_new (void);
RygelTranscodeManager* rygel_transcode_manager_construct (GType object_type);
RygelTranscodeManager* rygel_transcode_manager_new (void);
char* rygel_transcode_manager_create_uri_for_item (RygelTranscodeManager* self, RygelMediaItem* item, const char* transcode_target, char** protocol);
static char* rygel_transcode_manager_real_create_uri_for_item (RygelTranscodeManager* self, RygelMediaItem* item, const char* transcode_target, char** protocol);
GType rygel_media_container_get_type (void);
#define RYGEL_MEDIA_ITEM_IMAGE_CLASS "object.item.imageItem"
const char* rygel_transcoder_get_upnp_class (RygelTranscoder* self);
void rygel_transcoder_add_resources (RygelTranscoder* self, GeeArrayList* resources, RygelMediaItem* item, RygelTranscodeManager* manager, GError** error);
void rygel_transcode_manager_add_resources (RygelTranscodeManager* self, GeeArrayList* resources, RygelMediaItem* item, GError** error);
static void rygel_transcode_manager_real_add_resources (RygelTranscodeManager* self, GeeArrayList* resources, RygelMediaItem* item, GError** error);
gboolean rygel_transcoder_can_handle (RygelTranscoder* self, const char* target);
GQuark rygel_http_request_error_quark (void);
RygelTranscoder* rygel_transcode_manager_get_transcoder (RygelTranscodeManager* self, const char* target, GError** error);
static gpointer rygel_transcode_manager_parent_class = NULL;
static void rygel_transcode_manager_finalize (GObject* obj);



RygelTranscodeManager* rygel_transcode_manager_construct (GType object_type) {
	RygelTranscodeManager * self;
	GeeArrayList* _tmp0_;
	RygelConfiguration* config;
	self = g_object_newv (object_type, 0, NULL);
	_tmp0_ = NULL;
	self->priv->transcoders = (_tmp0_ = gee_array_list_new (RYGEL_TYPE_TRANSCODER, (GBoxedCopyFunc) g_object_ref, g_object_unref, g_direct_equal), (self->priv->transcoders == NULL) ? NULL : (self->priv->transcoders = (g_object_unref (self->priv->transcoders), NULL)), _tmp0_);
	config = rygel_configuration_get_default ();
	if (rygel_configuration_get_transcoding (config)) {
		if (rygel_configuration_get_lpcm_transcoder (config)) {
			RygelL16Transcoder* _tmp1_;
			_tmp1_ = NULL;
			gee_collection_add ((GeeCollection*) self->priv->transcoders, (RygelTranscoder*) (_tmp1_ = rygel_l16_transcoder_new (ENDIANNESS_BIG)));
			(_tmp1_ == NULL) ? NULL : (_tmp1_ = (g_object_unref (_tmp1_), NULL));
		}
		if (rygel_configuration_get_mp3_transcoder (config)) {
			RygelMP3Transcoder* _tmp2_;
			_tmp2_ = NULL;
			gee_collection_add ((GeeCollection*) self->priv->transcoders, (RygelTranscoder*) (_tmp2_ = rygel_mp3_transcoder_new (RYGEL_MP3_LAYER_THREE)));
			(_tmp2_ == NULL) ? NULL : (_tmp2_ = (g_object_unref (_tmp2_), NULL));
		}
		if (rygel_configuration_get_mp2ts_transcoder (config)) {
			RygelMP2TSTranscoder* _tmp3_;
			RygelMP2TSTranscoder* _tmp4_;
			_tmp3_ = NULL;
			gee_collection_add ((GeeCollection*) self->priv->transcoders, (RygelTranscoder*) (_tmp3_ = rygel_mp2_ts_transcoder_new (RYGEL_MP2_TS_PROFILE_SD)));
			(_tmp3_ == NULL) ? NULL : (_tmp3_ = (g_object_unref (_tmp3_), NULL));
			_tmp4_ = NULL;
			gee_collection_add ((GeeCollection*) self->priv->transcoders, (RygelTranscoder*) (_tmp4_ = rygel_mp2_ts_transcoder_new (RYGEL_MP2_TS_PROFILE_HD)));
			(_tmp4_ == NULL) ? NULL : (_tmp4_ = (g_object_unref (_tmp4_), NULL));
		}
	}
	(config == NULL) ? NULL : (config = (g_object_unref (config), NULL));
	return self;
}


RygelTranscodeManager* rygel_transcode_manager_new (void) {
	return rygel_transcode_manager_construct (RYGEL_TYPE_TRANSCODE_MANAGER);
}


static char* rygel_transcode_manager_real_create_uri_for_item (RygelTranscodeManager* self, RygelMediaItem* item, const char* transcode_target, char** protocol) {
	g_return_val_if_fail (self != NULL, NULL);
	g_critical ("Type `%s' does not implement abstract method `rygel_transcode_manager_create_uri_for_item'", g_type_name (G_TYPE_FROM_INSTANCE (self)));
	return NULL;
}


char* rygel_transcode_manager_create_uri_for_item (RygelTranscodeManager* self, RygelMediaItem* item, const char* transcode_target, char** protocol) {
	return RYGEL_TRANSCODE_MANAGER_GET_CLASS (self)->create_uri_for_item (self, item, transcode_target, protocol);
}


static void rygel_transcode_manager_real_add_resources (RygelTranscodeManager* self, GeeArrayList* resources, RygelMediaItem* item, GError** error) {
	GError * _inner_error_;
	g_return_if_fail (self != NULL);
	g_return_if_fail (resources != NULL);
	g_return_if_fail (item != NULL);
	_inner_error_ = NULL;
	if (g_str_has_prefix (item->upnp_class, RYGEL_MEDIA_ITEM_IMAGE_CLASS)) {
		/* No  transcoding for images yet :(*/
		return;
	}
	/* First add resource of the transcoders that are primarily meant for
	 the UPnP class of the item concerned*/
	{
		GeeIterator* _transcoder_it;
		/* First add resource of the transcoders that are primarily meant for
		 the UPnP class of the item concerned*/
		_transcoder_it = gee_iterable_iterator ((GeeIterable*) self->priv->transcoders);
		/* First add resource of the transcoders that are primarily meant for
		 the UPnP class of the item concerned*/
		while (gee_iterator_next (_transcoder_it)) {
			RygelTranscoder* transcoder;
			/* First add resource of the transcoders that are primarily meant for
			 the UPnP class of the item concerned*/
			transcoder = (RygelTranscoder*) gee_iterator_get (_transcoder_it);
			if (g_str_has_prefix (item->upnp_class, rygel_transcoder_get_upnp_class (transcoder))) {
				rygel_transcoder_add_resources (transcoder, resources, item, self, &_inner_error_);
				if (_inner_error_ != NULL) {
					g_propagate_error (error, _inner_error_);
					(transcoder == NULL) ? NULL : (transcoder = (g_object_unref (transcoder), NULL));
					(_transcoder_it == NULL) ? NULL : (_transcoder_it = (g_object_unref (_transcoder_it), NULL));
					return;
				}
			}
			(transcoder == NULL) ? NULL : (transcoder = (g_object_unref (transcoder), NULL));
		}
		(_transcoder_it == NULL) ? NULL : (_transcoder_it = (g_object_unref (_transcoder_it), NULL));
	}
	/* Then add resources from other transcoders*/
	{
		GeeIterator* _transcoder_it;
		/* Then add resources from other transcoders*/
		_transcoder_it = gee_iterable_iterator ((GeeIterable*) self->priv->transcoders);
		/* Then add resources from other transcoders*/
		while (gee_iterator_next (_transcoder_it)) {
			RygelTranscoder* transcoder;
			/* Then add resources from other transcoders*/
			transcoder = (RygelTranscoder*) gee_iterator_get (_transcoder_it);
			if (!g_str_has_prefix (item->upnp_class, rygel_transcoder_get_upnp_class (transcoder))) {
				rygel_transcoder_add_resources (transcoder, resources, item, self, &_inner_error_);
				if (_inner_error_ != NULL) {
					g_propagate_error (error, _inner_error_);
					(transcoder == NULL) ? NULL : (transcoder = (g_object_unref (transcoder), NULL));
					(_transcoder_it == NULL) ? NULL : (_transcoder_it = (g_object_unref (_transcoder_it), NULL));
					return;
				}
			}
			(transcoder == NULL) ? NULL : (transcoder = (g_object_unref (transcoder), NULL));
		}
		(_transcoder_it == NULL) ? NULL : (_transcoder_it = (g_object_unref (_transcoder_it), NULL));
	}
}


void rygel_transcode_manager_add_resources (RygelTranscodeManager* self, GeeArrayList* resources, RygelMediaItem* item, GError** error) {
	RYGEL_TRANSCODE_MANAGER_GET_CLASS (self)->add_resources (self, resources, item, error);
}


RygelTranscoder* rygel_transcode_manager_get_transcoder (RygelTranscodeManager* self, const char* target, GError** error) {
	GError * _inner_error_;
	RygelTranscoder* transcoder;
	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (target != NULL, NULL);
	_inner_error_ = NULL;
	transcoder = NULL;
	{
		GeeIterator* _iter_it;
		_iter_it = gee_iterable_iterator ((GeeIterable*) self->priv->transcoders);
		while (gee_iterator_next (_iter_it)) {
			RygelTranscoder* iter;
			iter = (RygelTranscoder*) gee_iterator_get (_iter_it);
			if (rygel_transcoder_can_handle (iter, target)) {
				RygelTranscoder* _tmp1_;
				RygelTranscoder* _tmp0_;
				_tmp1_ = NULL;
				_tmp0_ = NULL;
				transcoder = (_tmp1_ = (_tmp0_ = iter, (_tmp0_ == NULL) ? NULL : g_object_ref (_tmp0_)), (transcoder == NULL) ? NULL : (transcoder = (g_object_unref (transcoder), NULL)), _tmp1_);
			}
			(iter == NULL) ? NULL : (iter = (g_object_unref (iter), NULL));
		}
		(_iter_it == NULL) ? NULL : (_iter_it = (g_object_unref (_iter_it), NULL));
	}
	if (transcoder == NULL) {
		_inner_error_ = g_error_new (RYGEL_HTTP_REQUEST_ERROR, RYGEL_HTTP_REQUEST_ERROR_NOT_FOUND, "No transcoder available for target format '%s'", target);
		if (_inner_error_ != NULL) {
			g_propagate_error (error, _inner_error_);
			(transcoder == NULL) ? NULL : (transcoder = (g_object_unref (transcoder), NULL));
			return NULL;
		}
	}
	return transcoder;
}


static void rygel_transcode_manager_class_init (RygelTranscodeManagerClass * klass) {
	rygel_transcode_manager_parent_class = g_type_class_peek_parent (klass);
	g_type_class_add_private (klass, sizeof (RygelTranscodeManagerPrivate));
	RYGEL_TRANSCODE_MANAGER_CLASS (klass)->create_uri_for_item = rygel_transcode_manager_real_create_uri_for_item;
	RYGEL_TRANSCODE_MANAGER_CLASS (klass)->add_resources = rygel_transcode_manager_real_add_resources;
	G_OBJECT_CLASS (klass)->finalize = rygel_transcode_manager_finalize;
}


static void rygel_transcode_manager_instance_init (RygelTranscodeManager * self) {
	self->priv = RYGEL_TRANSCODE_MANAGER_GET_PRIVATE (self);
}


static void rygel_transcode_manager_finalize (GObject* obj) {
	RygelTranscodeManager * self;
	self = RYGEL_TRANSCODE_MANAGER (obj);
	(self->priv->transcoders == NULL) ? NULL : (self->priv->transcoders = (g_object_unref (self->priv->transcoders), NULL));
	G_OBJECT_CLASS (rygel_transcode_manager_parent_class)->finalize (obj);
}


GType rygel_transcode_manager_get_type (void) {
	static GType rygel_transcode_manager_type_id = 0;
	if (rygel_transcode_manager_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (RygelTranscodeManagerClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) rygel_transcode_manager_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (RygelTranscodeManager), 0, (GInstanceInitFunc) rygel_transcode_manager_instance_init, NULL };
		rygel_transcode_manager_type_id = g_type_register_static (G_TYPE_OBJECT, "RygelTranscodeManager", &g_define_type_info, G_TYPE_FLAG_ABSTRACT);
	}
	return rygel_transcode_manager_type_id;
}




