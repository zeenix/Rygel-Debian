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
#include <libgupnp-av/gupnp-av.h>
#include <stdlib.h>
#include <string.h>
#include <gst/gst.h>
#include <gee/arraylist.h>
#include <gee/iterable.h>
#include <gee/iterator.h>
#include <gio/gio.h>
#include <gee/list.h>
#include <gee/collection.h>


#define RYGEL_TYPE_DIDL_LITE_WRITER (rygel_didl_lite_writer_get_type ())
#define RYGEL_DIDL_LITE_WRITER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_DIDL_LITE_WRITER, RygelDIDLLiteWriter))
#define RYGEL_DIDL_LITE_WRITER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_DIDL_LITE_WRITER, RygelDIDLLiteWriterClass))
#define RYGEL_IS_DIDL_LITE_WRITER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_DIDL_LITE_WRITER))
#define RYGEL_IS_DIDL_LITE_WRITER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_DIDL_LITE_WRITER))
#define RYGEL_DIDL_LITE_WRITER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_DIDL_LITE_WRITER, RygelDIDLLiteWriterClass))

typedef struct _RygelDIDLLiteWriter RygelDIDLLiteWriter;
typedef struct _RygelDIDLLiteWriterClass RygelDIDLLiteWriterClass;
typedef struct _RygelDIDLLiteWriterPrivate RygelDIDLLiteWriterPrivate;

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

#define RYGEL_TYPE_MEDIA_ITEM (rygel_media_item_get_type ())
#define RYGEL_MEDIA_ITEM(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_MEDIA_ITEM, RygelMediaItem))
#define RYGEL_MEDIA_ITEM_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_MEDIA_ITEM, RygelMediaItemClass))
#define RYGEL_IS_MEDIA_ITEM(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_MEDIA_ITEM))
#define RYGEL_IS_MEDIA_ITEM_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_MEDIA_ITEM))
#define RYGEL_MEDIA_ITEM_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_MEDIA_ITEM, RygelMediaItemClass))

typedef struct _RygelMediaItem RygelMediaItem;
typedef struct _RygelMediaItemClass RygelMediaItemClass;

#define RYGEL_TYPE_MEDIA_CONTAINER (rygel_media_container_get_type ())
#define RYGEL_MEDIA_CONTAINER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_MEDIA_CONTAINER, RygelMediaContainer))
#define RYGEL_MEDIA_CONTAINER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_MEDIA_CONTAINER, RygelMediaContainerClass))
#define RYGEL_IS_MEDIA_CONTAINER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_MEDIA_CONTAINER))
#define RYGEL_IS_MEDIA_CONTAINER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_MEDIA_CONTAINER))
#define RYGEL_MEDIA_CONTAINER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_MEDIA_CONTAINER, RygelMediaContainerClass))

typedef struct _RygelMediaContainer RygelMediaContainer;
typedef struct _RygelMediaContainerClass RygelMediaContainerClass;
typedef struct _RygelMediaObjectPrivate RygelMediaObjectPrivate;
typedef struct _RygelMediaItemPrivate RygelMediaItemPrivate;
typedef struct _RygelMediaContainerPrivate RygelMediaContainerPrivate;

typedef enum  {
	RYGEL_DIDL_LITE_WRITER_ERROR_UNSUPPORTED_OBJECT
} RygelDIDLLiteWriterError;
#define RYGEL_DIDL_LITE_WRITER_ERROR rygel_didl_lite_writer_error_quark ()
/**
 * Responsible for serializing media objects.
 */
struct _RygelDIDLLiteWriter {
	GUPnPDIDLLiteWriter parent_instance;
	RygelDIDLLiteWriterPrivate * priv;
};

struct _RygelDIDLLiteWriterClass {
	GUPnPDIDLLiteWriterClass parent_class;
};

struct _RygelDIDLLiteWriterPrivate {
	RygelHTTPServer* http_server;
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

/**
 * Represents a container (folder) for media items and containers. Provides
 * basic serialization (to DIDLLiteWriter) implementation. Deriving classes
 * are supposed to provide working implementations of get_children and
 * find_object.
 */
struct _RygelMediaContainer {
	RygelMediaObject parent_instance;
	RygelMediaContainerPrivate * priv;
	guint child_count;
	guint32 update_id;
};

struct _RygelMediaContainerClass {
	RygelMediaObjectClass parent_class;
	void (*get_children) (RygelMediaContainer* self, guint offset, guint max_count, GCancellable* cancellable, GAsyncReadyCallback callback, void* callback_target);
	GeeList* (*get_children_finish) (RygelMediaContainer* self, GAsyncResult* res, GError** error);
	void (*find_object) (RygelMediaContainer* self, const char* id, GCancellable* cancellable, GAsyncReadyCallback callback, void* callback_target);
	RygelMediaObject* (*find_object_finish) (RygelMediaContainer* self, GAsyncResult* res, GError** error);
};



GQuark rygel_didl_lite_writer_error_quark (void);
GType rygel_didl_lite_writer_get_type (void);
GType rygel_transcode_manager_get_type (void);
GType rygel_http_server_get_type (void);
#define RYGEL_DIDL_LITE_WRITER_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), RYGEL_TYPE_DIDL_LITE_WRITER, RygelDIDLLiteWriterPrivate))
enum  {
	RYGEL_DIDL_LITE_WRITER_DUMMY_PROPERTY
};
RygelDIDLLiteWriter* rygel_didl_lite_writer_new (RygelHTTPServer* http_server);
RygelDIDLLiteWriter* rygel_didl_lite_writer_construct (GType object_type, RygelHTTPServer* http_server);
RygelDIDLLiteWriter* rygel_didl_lite_writer_new (RygelHTTPServer* http_server);
GType rygel_media_object_get_type (void);
GType rygel_media_item_get_type (void);
static void rygel_didl_lite_writer_serialize_item (RygelDIDLLiteWriter* self, RygelMediaItem* item, GError** error);
GType rygel_media_container_get_type (void);
static void rygel_didl_lite_writer_serialize_container (RygelDIDLLiteWriter* self, RygelMediaContainer* container, GError** error);
void rygel_didl_lite_writer_serialize (RygelDIDLLiteWriter* self, RygelMediaObject* media_object, GError** error);
#define RYGEL_MEDIA_ITEM_VIDEO_CLASS "object.item.videoItem"
#define RYGEL_MEDIA_ITEM_MUSIC_CLASS "object.item.audioItem.musicTrack"
static GeeArrayList* rygel_didl_lite_writer_get_original_resources (RygelDIDLLiteWriter* self, RygelMediaItem* item, GError** error);
void rygel_transcode_manager_add_resources (RygelTranscodeManager* self, GeeArrayList* resources, RygelMediaItem* item, GError** error);
static GUPnPDIDLLiteResource* _gupnp_didl_lite_resource_dup (GUPnPDIDLLiteResource* self);
GUPnPDIDLLiteResource rygel_media_item_create_res (RygelMediaItem* self, const char* uri, GError** error);
static gpointer rygel_didl_lite_writer_parent_class = NULL;
static void rygel_didl_lite_writer_finalize (GObject* obj);
static int _vala_strcmp0 (const char * str1, const char * str2);



GQuark rygel_didl_lite_writer_error_quark (void) {
	return g_quark_from_static_string ("rygel_didl_lite_writer_error-quark");
}


RygelDIDLLiteWriter* rygel_didl_lite_writer_construct (GType object_type, RygelHTTPServer* http_server) {
	RygelDIDLLiteWriter * self;
	RygelHTTPServer* _tmp1_;
	RygelHTTPServer* _tmp0_;
	g_return_val_if_fail (http_server != NULL, NULL);
	self = g_object_newv (object_type, 0, NULL);
	_tmp1_ = NULL;
	_tmp0_ = NULL;
	self->priv->http_server = (_tmp1_ = (_tmp0_ = http_server, (_tmp0_ == NULL) ? NULL : g_object_ref (_tmp0_)), (self->priv->http_server == NULL) ? NULL : (self->priv->http_server = (g_object_unref (self->priv->http_server), NULL)), _tmp1_);
	return self;
}


RygelDIDLLiteWriter* rygel_didl_lite_writer_new (RygelHTTPServer* http_server) {
	return rygel_didl_lite_writer_construct (RYGEL_TYPE_DIDL_LITE_WRITER, http_server);
}


void rygel_didl_lite_writer_serialize (RygelDIDLLiteWriter* self, RygelMediaObject* media_object, GError** error) {
	GError * _inner_error_;
	g_return_if_fail (self != NULL);
	g_return_if_fail (media_object != NULL);
	_inner_error_ = NULL;
	if (RYGEL_IS_MEDIA_ITEM (media_object)) {
		rygel_didl_lite_writer_serialize_item (self, RYGEL_MEDIA_ITEM (media_object), &_inner_error_);
		if (_inner_error_ != NULL) {
			g_propagate_error (error, _inner_error_);
			return;
		}
	} else {
		if (RYGEL_IS_MEDIA_CONTAINER (media_object)) {
			rygel_didl_lite_writer_serialize_container (self, RYGEL_MEDIA_CONTAINER (media_object), &_inner_error_);
			if (_inner_error_ != NULL) {
				g_propagate_error (error, _inner_error_);
				return;
			}
		} else {
			_inner_error_ = g_error_new_literal (RYGEL_DIDL_LITE_WRITER_ERROR, RYGEL_DIDL_LITE_WRITER_ERROR_UNSUPPORTED_OBJECT, "Unable to serialize unsupported object");
			if (_inner_error_ != NULL) {
				g_propagate_error (error, _inner_error_);
				return;
			}
		}
	}
}


static void rygel_didl_lite_writer_serialize_item (RygelDIDLLiteWriter* self, RygelMediaItem* item, GError** error) {
	GError * _inner_error_;
	gboolean _tmp0_;
	gboolean _tmp1_;
	gboolean _tmp2_;
	GeeArrayList* resources;
	g_return_if_fail (self != NULL);
	g_return_if_fail (item != NULL);
	_inner_error_ = NULL;
	gupnp_didl_lite_writer_start_item ((GUPnPDIDLLiteWriter*) self, ((RygelMediaObject*) item)->id, ((RygelMediaObject*) ((RygelMediaObject*) item)->parent)->id, NULL, FALSE);
	/* Add fields */
	gupnp_didl_lite_writer_add_string ((GUPnPDIDLLiteWriter*) self, "title", GUPNP_DIDL_LITE_WRITER_NAMESPACE_DC, NULL, ((RygelMediaObject*) item)->title);
	gupnp_didl_lite_writer_add_string ((GUPnPDIDLLiteWriter*) self, "class", GUPNP_DIDL_LITE_WRITER_NAMESPACE_UPNP, NULL, item->upnp_class);
	_tmp0_ = FALSE;
	if (item->author != NULL) {
		_tmp0_ = _vala_strcmp0 (item->author, "") != 0;
	} else {
		_tmp0_ = FALSE;
	}
	if (_tmp0_) {
		gupnp_didl_lite_writer_add_string ((GUPnPDIDLLiteWriter*) self, "creator", GUPNP_DIDL_LITE_WRITER_NAMESPACE_DC, NULL, item->author);
		if (g_str_has_prefix (item->upnp_class, RYGEL_MEDIA_ITEM_VIDEO_CLASS)) {
			gupnp_didl_lite_writer_add_string ((GUPnPDIDLLiteWriter*) self, "author", GUPNP_DIDL_LITE_WRITER_NAMESPACE_UPNP, NULL, item->author);
		} else {
			if (g_str_has_prefix (item->upnp_class, RYGEL_MEDIA_ITEM_MUSIC_CLASS)) {
				gupnp_didl_lite_writer_add_string ((GUPnPDIDLLiteWriter*) self, "artist", GUPNP_DIDL_LITE_WRITER_NAMESPACE_UPNP, NULL, item->author);
			}
		}
	}
	if (item->track_number >= 0) {
		gupnp_didl_lite_writer_add_int ((GUPnPDIDLLiteWriter*) self, "originalTrackNumber", GUPNP_DIDL_LITE_WRITER_NAMESPACE_UPNP, NULL, item->track_number);
	}
	_tmp1_ = FALSE;
	if (item->album != NULL) {
		_tmp1_ = _vala_strcmp0 (item->album, "") != 0;
	} else {
		_tmp1_ = FALSE;
	}
	if (_tmp1_) {
		gupnp_didl_lite_writer_add_string ((GUPnPDIDLLiteWriter*) self, "album", GUPNP_DIDL_LITE_WRITER_NAMESPACE_UPNP, NULL, item->album);
	}
	_tmp2_ = FALSE;
	if (item->date != NULL) {
		_tmp2_ = _vala_strcmp0 (item->date, "") != 0;
	} else {
		_tmp2_ = FALSE;
	}
	if (_tmp2_) {
		gupnp_didl_lite_writer_add_string ((GUPnPDIDLLiteWriter*) self, "date", GUPNP_DIDL_LITE_WRITER_NAMESPACE_DC, NULL, item->date);
	}
	/* Add resource data */
	resources = rygel_didl_lite_writer_get_original_resources (self, item, &_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		return;
	}
	/* Now get the transcoded/proxy URIs */
	rygel_transcode_manager_add_resources ((RygelTranscodeManager*) self->priv->http_server, resources, item, &_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		(resources == NULL) ? NULL : (resources = (g_object_unref (resources), NULL));
		return;
	}
	{
		GeeIterator* _res_it;
		_res_it = gee_iterable_iterator ((GeeIterable*) resources);
		while (gee_iterator_next (_res_it)) {
			GUPnPDIDLLiteResource _tmp4_ = {0};
			GUPnPDIDLLiteResource* _tmp3_;
			GUPnPDIDLLiteResource _tmp5_ = {0};
			GUPnPDIDLLiteResource res;
			_tmp3_ = NULL;
			res = (_tmp5_ = (gupnp_didl_lite_resource_copy (&(*(_tmp3_ = (GUPnPDIDLLiteResource*) gee_iterator_get (_res_it))), &_tmp4_), _tmp4_), (_tmp3_ == NULL) ? NULL : (_tmp3_ = (g_free (_tmp3_), NULL)), _tmp5_);
			gupnp_didl_lite_writer_add_res ((GUPnPDIDLLiteWriter*) self, &res);
			gupnp_didl_lite_resource_destroy (&res);
		}
		(_res_it == NULL) ? NULL : (_res_it = (g_object_unref (_res_it), NULL));
	}
	/* End of item */
	gupnp_didl_lite_writer_end_item ((GUPnPDIDLLiteWriter*) self);
	(resources == NULL) ? NULL : (resources = (g_object_unref (resources), NULL));
}


static void rygel_didl_lite_writer_serialize_container (RygelDIDLLiteWriter* self, RygelMediaContainer* container, GError** error) {
	char* parent_id;
	g_return_if_fail (self != NULL);
	g_return_if_fail (container != NULL);
	parent_id = NULL;
	if (((RygelMediaObject*) container)->parent != NULL) {
		char* _tmp1_;
		const char* _tmp0_;
		_tmp1_ = NULL;
		_tmp0_ = NULL;
		parent_id = (_tmp1_ = (_tmp0_ = ((RygelMediaObject*) ((RygelMediaObject*) container)->parent)->id, (_tmp0_ == NULL) ? NULL : g_strdup (_tmp0_)), parent_id = (g_free (parent_id), NULL), _tmp1_);
	} else {
		char* _tmp2_;
		_tmp2_ = NULL;
		parent_id = (_tmp2_ = g_strdup ("-1"), parent_id = (g_free (parent_id), NULL), _tmp2_);
	}
	gupnp_didl_lite_writer_start_container ((GUPnPDIDLLiteWriter*) self, ((RygelMediaObject*) container)->id, parent_id, (gint) container->child_count, FALSE, FALSE);
	gupnp_didl_lite_writer_add_string ((GUPnPDIDLLiteWriter*) self, "class", GUPNP_DIDL_LITE_WRITER_NAMESPACE_UPNP, NULL, "object.container.storageFolder");
	gupnp_didl_lite_writer_add_string ((GUPnPDIDLLiteWriter*) self, "title", GUPNP_DIDL_LITE_WRITER_NAMESPACE_DC, NULL, ((RygelMediaObject*) container)->title);
	/* End of Container */
	gupnp_didl_lite_writer_end_container ((GUPnPDIDLLiteWriter*) self);
	parent_id = (g_free (parent_id), NULL);
}


static GUPnPDIDLLiteResource* _gupnp_didl_lite_resource_dup (GUPnPDIDLLiteResource* self) {
	GUPnPDIDLLiteResource* dup;
	dup = g_new0 (GUPnPDIDLLiteResource, 1);
	gupnp_didl_lite_resource_copy (self, dup);
	return dup;
}


static GeeArrayList* rygel_didl_lite_writer_get_original_resources (RygelDIDLLiteWriter* self, RygelMediaItem* item, GError** error) {
	GError * _inner_error_;
	GeeArrayList* resources;
	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (item != NULL, NULL);
	_inner_error_ = NULL;
	resources = gee_array_list_new (GUPNP_TYPE_DIDL_LITE_RESOURCE, (GBoxedCopyFunc) _gupnp_didl_lite_resource_dup, g_free, g_direct_equal);
	{
		GeeIterator* _uri_it;
		_uri_it = gee_iterable_iterator ((GeeIterable*) item->uris);
		while (gee_iterator_next (_uri_it)) {
			char* uri;
			GUPnPDIDLLiteResource res;
			uri = (char*) gee_iterator_get (_uri_it);
			res = rygel_media_item_create_res (item, uri, &_inner_error_);
			if (_inner_error_ != NULL) {
				g_propagate_error (error, _inner_error_);
				uri = (g_free (uri), NULL);
				(_uri_it == NULL) ? NULL : (_uri_it = (g_object_unref (_uri_it), NULL));
				(resources == NULL) ? NULL : (resources = (g_object_unref (resources), NULL));
				return NULL;
			}
			gee_collection_add ((GeeCollection*) resources, &res);
			uri = (g_free (uri), NULL);
			gupnp_didl_lite_resource_destroy (&res);
		}
		(_uri_it == NULL) ? NULL : (_uri_it = (g_object_unref (_uri_it), NULL));
	}
	return resources;
}


static void rygel_didl_lite_writer_class_init (RygelDIDLLiteWriterClass * klass) {
	rygel_didl_lite_writer_parent_class = g_type_class_peek_parent (klass);
	g_type_class_add_private (klass, sizeof (RygelDIDLLiteWriterPrivate));
	G_OBJECT_CLASS (klass)->finalize = rygel_didl_lite_writer_finalize;
}


static void rygel_didl_lite_writer_instance_init (RygelDIDLLiteWriter * self) {
	self->priv = RYGEL_DIDL_LITE_WRITER_GET_PRIVATE (self);
}


static void rygel_didl_lite_writer_finalize (GObject* obj) {
	RygelDIDLLiteWriter * self;
	self = RYGEL_DIDL_LITE_WRITER (obj);
	(self->priv->http_server == NULL) ? NULL : (self->priv->http_server = (g_object_unref (self->priv->http_server), NULL));
	G_OBJECT_CLASS (rygel_didl_lite_writer_parent_class)->finalize (obj);
}


GType rygel_didl_lite_writer_get_type (void) {
	static GType rygel_didl_lite_writer_type_id = 0;
	if (rygel_didl_lite_writer_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (RygelDIDLLiteWriterClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) rygel_didl_lite_writer_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (RygelDIDLLiteWriter), 0, (GInstanceInitFunc) rygel_didl_lite_writer_instance_init, NULL };
		rygel_didl_lite_writer_type_id = g_type_register_static (GUPNP_TYPE_DIDL_LITE_WRITER, "RygelDIDLLiteWriter", &g_define_type_info, 0);
	}
	return rygel_didl_lite_writer_type_id;
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




