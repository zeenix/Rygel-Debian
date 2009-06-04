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
#include <gst/gst.h>
#include <libgupnp-av/gupnp-av.h>
#include <stdlib.h>
#include <string.h>
#include <gee/arraylist.h>
#include <gee/collection.h>
#include <gio/gio.h>


#define RYGEL_TYPE_TRANSCODER (rygel_transcoder_get_type ())
#define RYGEL_TRANSCODER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_TRANSCODER, RygelTranscoder))
#define RYGEL_TRANSCODER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_TRANSCODER, RygelTranscoderClass))
#define RYGEL_IS_TRANSCODER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_TRANSCODER))
#define RYGEL_IS_TRANSCODER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_TRANSCODER))
#define RYGEL_TRANSCODER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_TRANSCODER, RygelTranscoderClass))

typedef struct _RygelTranscoder RygelTranscoder;
typedef struct _RygelTranscoderClass RygelTranscoderClass;
typedef struct _RygelTranscoderPrivate RygelTranscoderPrivate;

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

#define RYGEL_TYPE_TRANSCODE_MANAGER (rygel_transcode_manager_get_type ())
#define RYGEL_TRANSCODE_MANAGER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_TRANSCODE_MANAGER, RygelTranscodeManager))
#define RYGEL_TRANSCODE_MANAGER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_TRANSCODE_MANAGER, RygelTranscodeManagerClass))
#define RYGEL_IS_TRANSCODE_MANAGER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_TRANSCODE_MANAGER))
#define RYGEL_IS_TRANSCODE_MANAGER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_TRANSCODE_MANAGER))
#define RYGEL_TRANSCODE_MANAGER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_TRANSCODE_MANAGER, RygelTranscodeManagerClass))

typedef struct _RygelTranscodeManager RygelTranscodeManager;
typedef struct _RygelTranscodeManagerClass RygelTranscodeManagerClass;
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
 * The base Transcoder class. Each implementation derives from it and must
 * at least implement create_source method.
 */
struct _RygelTranscoder {
	GObject parent_instance;
	RygelTranscoderPrivate * priv;
};

struct _RygelTranscoderClass {
	GObjectClass parent_class;
	GstElement* (*create_source) (RygelTranscoder* self, GstElement* src, GError** error);
	GUPnPDIDLLiteResource (*create_resource) (RygelTranscoder* self, RygelMediaItem* item, RygelTranscodeManager* manager, GError** error);
};

struct _RygelTranscoderPrivate {
	char* _mime_type;
	char* _dlna_profile;
	char* _upnp_class;
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



GType rygel_transcoder_get_type (void);
GType rygel_media_object_get_type (void);
GType rygel_media_item_get_type (void);
GType rygel_transcode_manager_get_type (void);
#define RYGEL_TRANSCODER_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), RYGEL_TYPE_TRANSCODER, RygelTranscoderPrivate))
enum  {
	RYGEL_TRANSCODER_DUMMY_PROPERTY,
	RYGEL_TRANSCODER_MIME_TYPE,
	RYGEL_TRANSCODER_DLNA_PROFILE,
	RYGEL_TRANSCODER_UPNP_CLASS
};
void rygel_transcoder_set_mime_type (RygelTranscoder* self, const char* value);
void rygel_transcoder_set_dlna_profile (RygelTranscoder* self, const char* value);
void rygel_transcoder_set_upnp_class (RygelTranscoder* self, const char* value);
RygelTranscoder* rygel_transcoder_new (const char* mime_type, const char* dlna_profile, const char* upnp_class);
RygelTranscoder* rygel_transcoder_construct (GType object_type, const char* mime_type, const char* dlna_profile, const char* upnp_class);
RygelTranscoder* rygel_transcoder_new (const char* mime_type, const char* dlna_profile, const char* upnp_class);
GstElement* rygel_transcoder_create_source (RygelTranscoder* self, GstElement* src, GError** error);
static GstElement* rygel_transcoder_real_create_source (RygelTranscoder* self, GstElement* src, GError** error);
gboolean rygel_transcoder_mime_type_is_a (RygelTranscoder* self, const char* mime_type1, const char* mime_type2);
GType rygel_media_container_get_type (void);
const char* rygel_transcoder_get_mime_type (RygelTranscoder* self);
GUPnPDIDLLiteResource rygel_transcoder_create_resource (RygelTranscoder* self, RygelMediaItem* item, RygelTranscodeManager* manager, GError** error);
void rygel_transcoder_add_resources (RygelTranscoder* self, GeeArrayList* resources, RygelMediaItem* item, RygelTranscodeManager* manager, GError** error);
char* rygel_transcode_manager_create_uri_for_item (RygelTranscodeManager* self, RygelMediaItem* item, const char* transcode_target, char** protocol);
const char* rygel_transcoder_get_dlna_profile (RygelTranscoder* self);
GUPnPDIDLLiteResource rygel_media_item_create_res (RygelMediaItem* self, const char* uri, GError** error);
static GUPnPDIDLLiteResource rygel_transcoder_real_create_resource (RygelTranscoder* self, RygelMediaItem* item, RygelTranscodeManager* manager, GError** error);
gboolean rygel_transcoder_can_handle (RygelTranscoder* self, const char* target);
const char* rygel_transcoder_get_upnp_class (RygelTranscoder* self);
static gpointer rygel_transcoder_parent_class = NULL;
static void rygel_transcoder_finalize (GObject* obj);
static void rygel_transcoder_get_property (GObject * object, guint property_id, GValue * value, GParamSpec * pspec);
static void rygel_transcoder_set_property (GObject * object, guint property_id, const GValue * value, GParamSpec * pspec);
static int _vala_strcmp0 (const char * str1, const char * str2);



RygelTranscoder* rygel_transcoder_construct (GType object_type, const char* mime_type, const char* dlna_profile, const char* upnp_class) {
	RygelTranscoder * self;
	g_return_val_if_fail (mime_type != NULL, NULL);
	g_return_val_if_fail (dlna_profile != NULL, NULL);
	g_return_val_if_fail (upnp_class != NULL, NULL);
	self = g_object_newv (object_type, 0, NULL);
	rygel_transcoder_set_mime_type (self, mime_type);
	rygel_transcoder_set_dlna_profile (self, dlna_profile);
	rygel_transcoder_set_upnp_class (self, upnp_class);
	return self;
}


RygelTranscoder* rygel_transcoder_new (const char* mime_type, const char* dlna_profile, const char* upnp_class) {
	return rygel_transcoder_construct (RYGEL_TYPE_TRANSCODER, mime_type, dlna_profile, upnp_class);
}


static GstElement* rygel_transcoder_real_create_source (RygelTranscoder* self, GstElement* src, GError** error) {
	g_return_val_if_fail (self != NULL, NULL);
	g_critical ("Type `%s' does not implement abstract method `rygel_transcoder_create_source'", g_type_name (G_TYPE_FROM_INSTANCE (self)));
	return NULL;
}


/**
     * Creates a transcoding source.
     *
     * @param src the original (non-transcoding) source
     *
     * @return      the new transcoding source
     */
GstElement* rygel_transcoder_create_source (RygelTranscoder* self, GstElement* src, GError** error) {
	return RYGEL_TRANSCODER_GET_CLASS (self)->create_source (self, src, error);
}


void rygel_transcoder_add_resources (RygelTranscoder* self, GeeArrayList* resources, RygelMediaItem* item, RygelTranscodeManager* manager, GError** error) {
	GError * _inner_error_;
	GUPnPDIDLLiteResource _tmp0_;
	GUPnPDIDLLiteResource _tmp2_ = {0};
	GUPnPDIDLLiteResource _tmp1_ = {0};
	g_return_if_fail (self != NULL);
	g_return_if_fail (resources != NULL);
	g_return_if_fail (item != NULL);
	g_return_if_fail (manager != NULL);
	_inner_error_ = NULL;
	if (rygel_transcoder_mime_type_is_a (self, item->mime_type, self->priv->_mime_type)) {
		return;
	}
	_tmp0_ = rygel_transcoder_create_resource (self, item, manager, &_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		return;
	}
	gee_collection_add ((GeeCollection*) resources, (_tmp2_ = _tmp1_ = _tmp0_, &_tmp2_));
	gupnp_didl_lite_resource_destroy (&_tmp1_);
}


static GUPnPDIDLLiteResource rygel_transcoder_real_create_resource (RygelTranscoder* self, RygelMediaItem* item, RygelTranscodeManager* manager, GError** error) {
	GError * _inner_error_;
	char* protocol;
	char* _tmp2_;
	char* _tmp1_;
	char* _tmp0_;
	char* uri;
	GUPnPDIDLLiteResource res;
	char* _tmp4_;
	const char* _tmp3_;
	char* _tmp6_;
	const char* _tmp5_;
	char* _tmp8_;
	const char* _tmp7_;
	GUPnPDIDLLiteResource _tmp9_ = {0};
	_inner_error_ = NULL;
	protocol = NULL;
	_tmp2_ = NULL;
	_tmp1_ = NULL;
	_tmp0_ = NULL;
	uri = (_tmp1_ = rygel_transcode_manager_create_uri_for_item (manager, item, self->priv->_dlna_profile, &_tmp0_), protocol = (_tmp2_ = _tmp0_, protocol = (g_free (protocol), NULL), _tmp2_), _tmp1_);
	res = rygel_media_item_create_res (item, uri, &_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		protocol = (g_free (protocol), NULL);
		uri = (g_free (uri), NULL);
		return;
	}
	_tmp4_ = NULL;
	_tmp3_ = NULL;
	res.mime_type = (_tmp4_ = (_tmp3_ = self->priv->_mime_type, (_tmp3_ == NULL) ? NULL : g_strdup (_tmp3_)), res.mime_type = (g_free (res.mime_type), NULL), _tmp4_);
	_tmp6_ = NULL;
	_tmp5_ = NULL;
	res.protocol = (_tmp6_ = (_tmp5_ = protocol, (_tmp5_ == NULL) ? NULL : g_strdup (_tmp5_)), res.protocol = (g_free (res.protocol), NULL), _tmp6_);
	_tmp8_ = NULL;
	_tmp7_ = NULL;
	res.dlna_profile = (_tmp8_ = (_tmp7_ = self->priv->_dlna_profile, (_tmp7_ == NULL) ? NULL : g_strdup (_tmp7_)), res.dlna_profile = (g_free (res.dlna_profile), NULL), _tmp8_);
	res.dlna_conversion = GUPNP_DLNA_CONVERSION_TRANSCODED;
	res.dlna_flags = GUPNP_DLNA_FLAG_STREAMING_TRANSFER_MODE;
	res.dlna_operation = GUPNP_DLNA_OPERATION_NONE;
	res.size = (glong) (-1);
	return (_tmp9_ = res, protocol = (g_free (protocol), NULL), uri = (g_free (uri), NULL), _tmp9_);
}


GUPnPDIDLLiteResource rygel_transcoder_create_resource (RygelTranscoder* self, RygelMediaItem* item, RygelTranscodeManager* manager, GError** error) {
	return RYGEL_TRANSCODER_GET_CLASS (self)->create_resource (self, item, manager, error);
}


gboolean rygel_transcoder_can_handle (RygelTranscoder* self, const char* target) {
	g_return_val_if_fail (self != NULL, FALSE);
	g_return_val_if_fail (target != NULL, FALSE);
	return _vala_strcmp0 (target, self->priv->_dlna_profile) == 0;
}


gboolean rygel_transcoder_mime_type_is_a (RygelTranscoder* self, const char* mime_type1, const char* mime_type2) {
	const char* _tmp0_;
	char* content_type1;
	const char* _tmp1_;
	char* content_type2;
	gboolean _tmp2_;
	g_return_val_if_fail (self != NULL, FALSE);
	g_return_val_if_fail (mime_type1 != NULL, FALSE);
	g_return_val_if_fail (mime_type2 != NULL, FALSE);
	_tmp0_ = NULL;
	content_type1 = (_tmp0_ = g_content_type_from_mime_type (mime_type1), (_tmp0_ == NULL) ? NULL : g_strdup (_tmp0_));
	_tmp1_ = NULL;
	content_type2 = (_tmp1_ = g_content_type_from_mime_type (mime_type2), (_tmp1_ == NULL) ? NULL : g_strdup (_tmp1_));
	return (_tmp2_ = g_content_type_is_a (content_type1, content_type2), content_type1 = (g_free (content_type1), NULL), content_type2 = (g_free (content_type2), NULL), _tmp2_);
}


const char* rygel_transcoder_get_mime_type (RygelTranscoder* self) {
	g_return_val_if_fail (self != NULL, NULL);
	return self->priv->_mime_type;
}


void rygel_transcoder_set_mime_type (RygelTranscoder* self, const char* value) {
	char* _tmp2_;
	const char* _tmp1_;
	g_return_if_fail (self != NULL);
	_tmp2_ = NULL;
	_tmp1_ = NULL;
	self->priv->_mime_type = (_tmp2_ = (_tmp1_ = value, (_tmp1_ == NULL) ? NULL : g_strdup (_tmp1_)), self->priv->_mime_type = (g_free (self->priv->_mime_type), NULL), _tmp2_);
	g_object_notify ((GObject *) self, "mime-type");
}


const char* rygel_transcoder_get_dlna_profile (RygelTranscoder* self) {
	g_return_val_if_fail (self != NULL, NULL);
	return self->priv->_dlna_profile;
}


void rygel_transcoder_set_dlna_profile (RygelTranscoder* self, const char* value) {
	char* _tmp2_;
	const char* _tmp1_;
	g_return_if_fail (self != NULL);
	_tmp2_ = NULL;
	_tmp1_ = NULL;
	self->priv->_dlna_profile = (_tmp2_ = (_tmp1_ = value, (_tmp1_ == NULL) ? NULL : g_strdup (_tmp1_)), self->priv->_dlna_profile = (g_free (self->priv->_dlna_profile), NULL), _tmp2_);
	g_object_notify ((GObject *) self, "dlna-profile");
}


const char* rygel_transcoder_get_upnp_class (RygelTranscoder* self) {
	g_return_val_if_fail (self != NULL, NULL);
	return self->priv->_upnp_class;
}


void rygel_transcoder_set_upnp_class (RygelTranscoder* self, const char* value) {
	char* _tmp2_;
	const char* _tmp1_;
	g_return_if_fail (self != NULL);
	_tmp2_ = NULL;
	_tmp1_ = NULL;
	self->priv->_upnp_class = (_tmp2_ = (_tmp1_ = value, (_tmp1_ == NULL) ? NULL : g_strdup (_tmp1_)), self->priv->_upnp_class = (g_free (self->priv->_upnp_class), NULL), _tmp2_);
	g_object_notify ((GObject *) self, "upnp-class");
}


static void rygel_transcoder_class_init (RygelTranscoderClass * klass) {
	rygel_transcoder_parent_class = g_type_class_peek_parent (klass);
	g_type_class_add_private (klass, sizeof (RygelTranscoderPrivate));
	RYGEL_TRANSCODER_CLASS (klass)->create_source = rygel_transcoder_real_create_source;
	RYGEL_TRANSCODER_CLASS (klass)->create_resource = rygel_transcoder_real_create_resource;
	G_OBJECT_CLASS (klass)->get_property = rygel_transcoder_get_property;
	G_OBJECT_CLASS (klass)->set_property = rygel_transcoder_set_property;
	G_OBJECT_CLASS (klass)->finalize = rygel_transcoder_finalize;
	g_object_class_install_property (G_OBJECT_CLASS (klass), RYGEL_TRANSCODER_MIME_TYPE, g_param_spec_string ("mime-type", "mime-type", "mime-type", NULL, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
	g_object_class_install_property (G_OBJECT_CLASS (klass), RYGEL_TRANSCODER_DLNA_PROFILE, g_param_spec_string ("dlna-profile", "dlna-profile", "dlna-profile", NULL, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
	g_object_class_install_property (G_OBJECT_CLASS (klass), RYGEL_TRANSCODER_UPNP_CLASS, g_param_spec_string ("upnp-class", "upnp-class", "upnp-class", NULL, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
}


static void rygel_transcoder_instance_init (RygelTranscoder * self) {
	self->priv = RYGEL_TRANSCODER_GET_PRIVATE (self);
}


static void rygel_transcoder_finalize (GObject* obj) {
	RygelTranscoder * self;
	self = RYGEL_TRANSCODER (obj);
	self->priv->_mime_type = (g_free (self->priv->_mime_type), NULL);
	self->priv->_dlna_profile = (g_free (self->priv->_dlna_profile), NULL);
	self->priv->_upnp_class = (g_free (self->priv->_upnp_class), NULL);
	G_OBJECT_CLASS (rygel_transcoder_parent_class)->finalize (obj);
}


GType rygel_transcoder_get_type (void) {
	static GType rygel_transcoder_type_id = 0;
	if (rygel_transcoder_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (RygelTranscoderClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) rygel_transcoder_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (RygelTranscoder), 0, (GInstanceInitFunc) rygel_transcoder_instance_init, NULL };
		rygel_transcoder_type_id = g_type_register_static (G_TYPE_OBJECT, "RygelTranscoder", &g_define_type_info, G_TYPE_FLAG_ABSTRACT);
	}
	return rygel_transcoder_type_id;
}


static void rygel_transcoder_get_property (GObject * object, guint property_id, GValue * value, GParamSpec * pspec) {
	RygelTranscoder * self;
	gpointer boxed;
	self = RYGEL_TRANSCODER (object);
	switch (property_id) {
		case RYGEL_TRANSCODER_MIME_TYPE:
		g_value_set_string (value, rygel_transcoder_get_mime_type (self));
		break;
		case RYGEL_TRANSCODER_DLNA_PROFILE:
		g_value_set_string (value, rygel_transcoder_get_dlna_profile (self));
		break;
		case RYGEL_TRANSCODER_UPNP_CLASS:
		g_value_set_string (value, rygel_transcoder_get_upnp_class (self));
		break;
		default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}


static void rygel_transcoder_set_property (GObject * object, guint property_id, const GValue * value, GParamSpec * pspec) {
	RygelTranscoder * self;
	self = RYGEL_TRANSCODER (object);
	switch (property_id) {
		case RYGEL_TRANSCODER_MIME_TYPE:
		rygel_transcoder_set_mime_type (self, g_value_get_string (value));
		break;
		case RYGEL_TRANSCODER_DLNA_PROFILE:
		rygel_transcoder_set_dlna_profile (self, g_value_get_string (value));
		break;
		case RYGEL_TRANSCODER_UPNP_CLASS:
		rygel_transcoder_set_upnp_class (self, g_value_get_string (value));
		break;
		default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
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




