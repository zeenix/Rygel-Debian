/*
 * Copyright (C) 2008 Zeeshan Ali <zeenix@gmail.com>.
 *
 * Author: Zeeshan Ali <zeenix@gmail.com>
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
#include <gst/gst.h>
#include <gee/arraylist.h>
#include <libgupnp-av/gupnp-av.h>


#define RYGEL_TYPE_MEDIA_OBJECT (rygel_media_object_get_type ())
#define RYGEL_MEDIA_OBJECT(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_MEDIA_OBJECT, RygelMediaObject))
#define RYGEL_MEDIA_OBJECT_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_MEDIA_OBJECT, RygelMediaObjectClass))
#define RYGEL_IS_MEDIA_OBJECT(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_MEDIA_OBJECT))
#define RYGEL_IS_MEDIA_OBJECT_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_MEDIA_OBJECT))
#define RYGEL_MEDIA_OBJECT_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_MEDIA_OBJECT, RygelMediaObjectClass))

typedef struct _RygelMediaObject RygelMediaObject;
typedef struct _RygelMediaObjectClass RygelMediaObjectClass;
typedef struct _RygelMediaObjectPrivate RygelMediaObjectPrivate;

#define RYGEL_TYPE_MEDIA_CONTAINER (rygel_media_container_get_type ())
#define RYGEL_MEDIA_CONTAINER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_MEDIA_CONTAINER, RygelMediaContainer))
#define RYGEL_MEDIA_CONTAINER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_MEDIA_CONTAINER, RygelMediaContainerClass))
#define RYGEL_IS_MEDIA_CONTAINER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_MEDIA_CONTAINER))
#define RYGEL_IS_MEDIA_CONTAINER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_MEDIA_CONTAINER))
#define RYGEL_MEDIA_CONTAINER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_MEDIA_CONTAINER, RygelMediaContainerClass))

typedef struct _RygelMediaContainer RygelMediaContainer;
typedef struct _RygelMediaContainerClass RygelMediaContainerClass;

#define RYGEL_TYPE_MEDIA_ITEM (rygel_media_item_get_type ())
#define RYGEL_MEDIA_ITEM(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_MEDIA_ITEM, RygelMediaItem))
#define RYGEL_MEDIA_ITEM_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_MEDIA_ITEM, RygelMediaItemClass))
#define RYGEL_IS_MEDIA_ITEM(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_MEDIA_ITEM))
#define RYGEL_IS_MEDIA_ITEM_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_MEDIA_ITEM))
#define RYGEL_MEDIA_ITEM_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_MEDIA_ITEM, RygelMediaItemClass))

typedef struct _RygelMediaItem RygelMediaItem;
typedef struct _RygelMediaItemClass RygelMediaItemClass;
typedef struct _RygelMediaItemPrivate RygelMediaItemPrivate;

typedef enum  {
	RYGEL_MEDIA_ITEM_ERROR_BAD_URI
} RygelMediaItemError;
#define RYGEL_MEDIA_ITEM_ERROR rygel_media_item_error_quark ()
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



GQuark rygel_media_item_error_quark (void);
GType rygel_media_object_get_type (void);
GType rygel_media_container_get_type (void);
GType rygel_media_item_get_type (void);
enum  {
	RYGEL_MEDIA_ITEM_DUMMY_PROPERTY
};
#define RYGEL_MEDIA_ITEM_IMAGE_CLASS "object.item.imageItem"
#define RYGEL_MEDIA_ITEM_VIDEO_CLASS "object.item.videoItem"
#define RYGEL_MEDIA_ITEM_AUDIO_CLASS "object.item.audioItem"
#define RYGEL_MEDIA_ITEM_MUSIC_CLASS "object.item.audioItem.musicTrack"
RygelMediaItem* rygel_media_item_new (const char* id, RygelMediaContainer* parent, const char* title, const char* upnp_class);
RygelMediaItem* rygel_media_item_construct (GType object_type, const char* id, RygelMediaContainer* parent, const char* title, const char* upnp_class);
RygelMediaItem* rygel_media_item_new (const char* id, RygelMediaContainer* parent, const char* title, const char* upnp_class);
GstElement* rygel_media_item_create_stream_source (RygelMediaItem* self);
static GstElement* rygel_media_item_real_create_stream_source (RygelMediaItem* self);
static char* rygel_media_item_get_protocol_for_uri (RygelMediaItem* self, const char* uri, GError** error);
GUPnPDIDLLiteResource rygel_media_item_create_res (RygelMediaItem* self, const char* uri, GError** error);
static gpointer rygel_media_item_parent_class = NULL;
static void rygel_media_item_finalize (GObject* obj);
static void _vala_array_destroy (gpointer array, gint array_length, GDestroyNotify destroy_func);
static void _vala_array_free (gpointer array, gint array_length, GDestroyNotify destroy_func);
static gint _vala_array_length (gpointer array);



GQuark rygel_media_item_error_quark (void) {
	return g_quark_from_static_string ("rygel_media_item_error-quark");
}


RygelMediaItem* rygel_media_item_construct (GType object_type, const char* id, RygelMediaContainer* parent, const char* title, const char* upnp_class) {
	RygelMediaItem * self;
	char* _tmp1_;
	const char* _tmp0_;
	char* _tmp3_;
	const char* _tmp2_;
	char* _tmp5_;
	const char* _tmp4_;
	GeeArrayList* _tmp6_;
	g_return_val_if_fail (id != NULL, NULL);
	g_return_val_if_fail (parent != NULL, NULL);
	g_return_val_if_fail (title != NULL, NULL);
	g_return_val_if_fail (upnp_class != NULL, NULL);
	self = g_object_newv (object_type, 0, NULL);
	_tmp1_ = NULL;
	_tmp0_ = NULL;
	((RygelMediaObject*) self)->id = (_tmp1_ = (_tmp0_ = id, (_tmp0_ == NULL) ? NULL : g_strdup (_tmp0_)), ((RygelMediaObject*) self)->id = (g_free (((RygelMediaObject*) self)->id), NULL), _tmp1_);
	((RygelMediaObject*) self)->parent = parent;
	_tmp3_ = NULL;
	_tmp2_ = NULL;
	((RygelMediaObject*) self)->title = (_tmp3_ = (_tmp2_ = title, (_tmp2_ == NULL) ? NULL : g_strdup (_tmp2_)), ((RygelMediaObject*) self)->title = (g_free (((RygelMediaObject*) self)->title), NULL), _tmp3_);
	_tmp5_ = NULL;
	_tmp4_ = NULL;
	self->upnp_class = (_tmp5_ = (_tmp4_ = upnp_class, (_tmp4_ == NULL) ? NULL : g_strdup (_tmp4_)), self->upnp_class = (g_free (self->upnp_class), NULL), _tmp5_);
	_tmp6_ = NULL;
	self->uris = (_tmp6_ = gee_array_list_new (G_TYPE_STRING, (GBoxedCopyFunc) g_strdup, g_free, g_direct_equal), (self->uris == NULL) ? NULL : (self->uris = (g_object_unref (self->uris), NULL)), _tmp6_);
	return self;
}


RygelMediaItem* rygel_media_item_new (const char* id, RygelMediaContainer* parent, const char* title, const char* upnp_class) {
	return rygel_media_item_construct (RYGEL_TYPE_MEDIA_ITEM, id, parent, title, upnp_class);
}


/* Live media items need to provide a nice working implementation of this
 method if they can/do no provide a valid URI*/
static GstElement* rygel_media_item_real_create_stream_source (RygelMediaItem* self) {
	g_return_val_if_fail (self != NULL, NULL);
	return NULL;
}


GstElement* rygel_media_item_create_stream_source (RygelMediaItem* self) {
	return RYGEL_MEDIA_ITEM_GET_CLASS (self)->create_stream_source (self);
}


GUPnPDIDLLiteResource rygel_media_item_create_res (RygelMediaItem* self, const char* uri, GError** error) {
	GError * _inner_error_;
	GUPnPDIDLLiteResource _tmp0_ = {0};
	GUPnPDIDLLiteResource res;
	char* _tmp2_;
	const char* _tmp1_;
	char* _tmp4_;
	const char* _tmp3_;
	_inner_error_ = NULL;
	res = (memset (&_tmp0_, 0, sizeof (GUPnPDIDLLiteResource)), _tmp0_);
	gupnp_didl_lite_resource_reset (&res);
	_tmp2_ = NULL;
	_tmp1_ = NULL;
	res.uri = (_tmp2_ = (_tmp1_ = uri, (_tmp1_ == NULL) ? NULL : g_strdup (_tmp1_)), res.uri = (g_free (res.uri), NULL), _tmp2_);
	_tmp4_ = NULL;
	_tmp3_ = NULL;
	res.mime_type = (_tmp4_ = (_tmp3_ = self->mime_type, (_tmp3_ == NULL) ? NULL : g_strdup (_tmp3_)), res.mime_type = (g_free (res.mime_type), NULL), _tmp4_);
	res.size = self->size;
	res.duration = self->duration;
	res.bitrate = self->bitrate;
	res.sample_freq = self->sample_freq;
	res.bits_per_sample = self->bits_per_sample;
	res.n_audio_channels = self->n_audio_channels;
	res.width = self->width;
	res.height = self->height;
	res.color_depth = self->color_depth;
	/* Protocol info */
	if (res.uri != NULL) {
		char* protocol;
		char* _tmp6_;
		const char* _tmp5_;
		protocol = rygel_media_item_get_protocol_for_uri (self, res.uri, &_inner_error_);
		if (_inner_error_ != NULL) {
			g_propagate_error (error, _inner_error_);
			gupnp_didl_lite_resource_destroy (&res);
			return;
		}
		_tmp6_ = NULL;
		_tmp5_ = NULL;
		res.protocol = (_tmp6_ = (_tmp5_ = protocol, (_tmp5_ == NULL) ? NULL : g_strdup (_tmp5_)), res.protocol = (g_free (res.protocol), NULL), _tmp6_);
		protocol = (g_free (protocol), NULL);
	}
	if (g_str_has_prefix (self->upnp_class, RYGEL_MEDIA_ITEM_IMAGE_CLASS)) {
		res.dlna_flags = res.dlna_flags | GUPNP_DLNA_FLAG_INTERACTIVE_TRANSFER_MODE;
	} else {
		res.dlna_flags = res.dlna_flags | GUPNP_DLNA_FLAG_STREAMING_TRANSFER_MODE;
	}
	if (res.size > 0) {
		res.dlna_operation = GUPNP_DLNA_OPERATION_RANGE;
		res.dlna_flags = res.dlna_flags | GUPNP_DLNA_FLAG_BACKGROUND_TRANSFER_MODE;
	}
	return res;
}


static char* rygel_media_item_get_protocol_for_uri (RygelMediaItem* self, const char* uri, GError** error) {
	GError * _inner_error_;
	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (uri != NULL, NULL);
	_inner_error_ = NULL;
	if (g_str_has_prefix (uri, "http")) {
		return g_strdup ("http-get");
	} else {
		if (g_str_has_prefix (uri, "file")) {
			return g_strdup ("internal");
		} else {
			if (g_str_has_prefix (uri, "rtsp")) {
				/* FIXME: Assuming that RTSP is always accompanied with RTP over UDP*/
				return g_strdup ("rtsp-rtp-udp");
			} else {
				char** _tmp4_;
				gint tokens_size;
				gint tokens_length1;
				char** _tmp3_;
				char** tokens;
				const char* _tmp5_;
				char* _tmp6_;
				g_warning ("rygel-media-item.vala:129: Failed to probe protocol for URI %s", uri);
				/* Assume the protocol to be the scheme of the URI*/
				_tmp4_ = NULL;
				_tmp3_ = NULL;
				tokens = (_tmp4_ = _tmp3_ = g_strsplit (uri, ":", 2), tokens_length1 = _vala_array_length (_tmp3_), tokens_size = tokens_length1, _tmp4_);
				if (tokens[0] == NULL) {
					_inner_error_ = g_error_new (RYGEL_MEDIA_ITEM_ERROR, RYGEL_MEDIA_ITEM_ERROR_BAD_URI, "Bad URI: %s", uri);
					if (_inner_error_ != NULL) {
						g_propagate_error (error, _inner_error_);
						tokens = (_vala_array_free (tokens, tokens_length1, (GDestroyNotify) g_free), NULL);
						return NULL;
					}
				}
				_tmp5_ = NULL;
				_tmp6_ = NULL;
				return (_tmp6_ = (_tmp5_ = tokens[0], (_tmp5_ == NULL) ? NULL : g_strdup (_tmp5_)), tokens = (_vala_array_free (tokens, tokens_length1, (GDestroyNotify) g_free), NULL), _tmp6_);
			}
		}
	}
}


static void rygel_media_item_class_init (RygelMediaItemClass * klass) {
	rygel_media_item_parent_class = g_type_class_peek_parent (klass);
	RYGEL_MEDIA_ITEM_CLASS (klass)->create_stream_source = rygel_media_item_real_create_stream_source;
	G_OBJECT_CLASS (klass)->finalize = rygel_media_item_finalize;
}


static void rygel_media_item_instance_init (RygelMediaItem * self) {
	self->size = (glong) (-1);
	self->duration = (glong) (-1);
	self->bitrate = -1;
	self->sample_freq = -1;
	self->bits_per_sample = -1;
	self->n_audio_channels = -1;
	self->track_number = -1;
	self->width = -1;
	self->height = -1;
	self->color_depth = -1;
}


static void rygel_media_item_finalize (GObject* obj) {
	RygelMediaItem * self;
	self = RYGEL_MEDIA_ITEM (obj);
	self->author = (g_free (self->author), NULL);
	self->album = (g_free (self->album), NULL);
	self->date = (g_free (self->date), NULL);
	self->upnp_class = (g_free (self->upnp_class), NULL);
	(self->uris == NULL) ? NULL : (self->uris = (g_object_unref (self->uris), NULL));
	self->mime_type = (g_free (self->mime_type), NULL);
	G_OBJECT_CLASS (rygel_media_item_parent_class)->finalize (obj);
}


GType rygel_media_item_get_type (void) {
	static GType rygel_media_item_type_id = 0;
	if (rygel_media_item_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (RygelMediaItemClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) rygel_media_item_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (RygelMediaItem), 0, (GInstanceInitFunc) rygel_media_item_instance_init, NULL };
		rygel_media_item_type_id = g_type_register_static (RYGEL_TYPE_MEDIA_OBJECT, "RygelMediaItem", &g_define_type_info, 0);
	}
	return rygel_media_item_type_id;
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




