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


#define RYGEL_TYPE_MP2_TS_PROFILE (rygel_mp2_ts_profile_get_type ())

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

#define RYGEL_TYPE_MP2_TS_TRANSCODER (rygel_mp2_ts_transcoder_get_type ())
#define RYGEL_MP2_TS_TRANSCODER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_MP2_TS_TRANSCODER, RygelMP2TSTranscoder))
#define RYGEL_MP2_TS_TRANSCODER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_MP2_TS_TRANSCODER, RygelMP2TSTranscoderClass))
#define RYGEL_IS_MP2_TS_TRANSCODER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_MP2_TS_TRANSCODER))
#define RYGEL_IS_MP2_TS_TRANSCODER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_MP2_TS_TRANSCODER))
#define RYGEL_MP2_TS_TRANSCODER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_MP2_TS_TRANSCODER, RygelMP2TSTranscoderClass))

typedef struct _RygelMP2TSTranscoder RygelMP2TSTranscoder;
typedef struct _RygelMP2TSTranscoderClass RygelMP2TSTranscoderClass;
typedef struct _RygelMP2TSTranscoderPrivate RygelMP2TSTranscoderPrivate;

#define RYGEL_TYPE_MP2_TS_TRANSCODER_BIN (rygel_mp2_ts_transcoder_bin_get_type ())
#define RYGEL_MP2_TS_TRANSCODER_BIN(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_MP2_TS_TRANSCODER_BIN, RygelMP2TSTranscoderBin))
#define RYGEL_MP2_TS_TRANSCODER_BIN_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_MP2_TS_TRANSCODER_BIN, RygelMP2TSTranscoderBinClass))
#define RYGEL_IS_MP2_TS_TRANSCODER_BIN(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_MP2_TS_TRANSCODER_BIN))
#define RYGEL_IS_MP2_TS_TRANSCODER_BIN_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_MP2_TS_TRANSCODER_BIN))
#define RYGEL_MP2_TS_TRANSCODER_BIN_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_MP2_TS_TRANSCODER_BIN, RygelMP2TSTranscoderBinClass))

typedef struct _RygelMP2TSTranscoderBin RygelMP2TSTranscoderBin;
typedef struct _RygelMP2TSTranscoderBinClass RygelMP2TSTranscoderBinClass;

typedef enum  {
	RYGEL_MP2_TS_PROFILE_SD = 0,
	RYGEL_MP2_TS_PROFILE_HD
} RygelMP2TSProfile;

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

/**
 * Transcoder for mpeg transport stream containing mpeg 2 video and mp2 audio.
 * This element uses MP2TSTrancoderBin for actual transcoding.
 */
struct _RygelMP2TSTranscoder {
	RygelTranscoder parent_instance;
	RygelMP2TSTranscoderPrivate * priv;
};

struct _RygelMP2TSTranscoderClass {
	RygelTranscoderClass parent_class;
};

struct _RygelMP2TSTranscoderPrivate {
	RygelMP2TSProfile profile;
};



GType rygel_mp2_ts_profile_get_type (void);
GType rygel_transcoder_get_type (void);
GType rygel_media_object_get_type (void);
GType rygel_media_item_get_type (void);
GType rygel_transcode_manager_get_type (void);
GType rygel_mp2_ts_transcoder_get_type (void);
#define RYGEL_MP2_TS_TRANSCODER_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), RYGEL_TYPE_MP2_TS_TRANSCODER, RygelMP2TSTranscoderPrivate))
enum  {
	RYGEL_MP2_TS_TRANSCODER_DUMMY_PROPERTY
};
#define RYGEL_MP2_TS_TRANSCODER_VIDEO_ENCODER "ffenc_mpeg2video"
#define RYGEL_MP2_TS_TRANSCODER_COLORSPACE_CONVERT "ffmpegcolorspace"
#define RYGEL_MP2_TS_TRANSCODER_VIDEO_RATE "videorate"
#define RYGEL_MP2_TS_TRANSCODER_VIDEO_SCALE "videoscale"
#define RYGEL_MEDIA_ITEM_VIDEO_CLASS "object.item.videoItem"
RygelTranscoder* rygel_transcoder_new (const char* mime_type, const char* dlna_profile, const char* upnp_class);
RygelTranscoder* rygel_transcoder_construct (GType object_type, const char* mime_type, const char* dlna_profile, const char* upnp_class);
RygelMP2TSTranscoder* rygel_mp2_ts_transcoder_new (RygelMP2TSProfile profile);
RygelMP2TSTranscoder* rygel_mp2_ts_transcoder_construct (GType object_type, RygelMP2TSProfile profile);
RygelMP2TSTranscoder* rygel_mp2_ts_transcoder_new (RygelMP2TSProfile profile);
RygelMP2TSTranscoderBin* rygel_mp2_ts_transcoder_bin_new (GstElement* src, RygelMP2TSTranscoder* transcoder, GError** error);
RygelMP2TSTranscoderBin* rygel_mp2_ts_transcoder_bin_construct (GType object_type, GstElement* src, RygelMP2TSTranscoder* transcoder, GError** error);
GType rygel_mp2_ts_transcoder_bin_get_type (void);
static GstElement* rygel_mp2_ts_transcoder_real_create_source (RygelTranscoder* base, GstElement* src, GError** error);
GUPnPDIDLLiteResource rygel_transcoder_create_resource (RygelTranscoder* self, RygelMediaItem* item, RygelTranscodeManager* manager, GError** error);
static GUPnPDIDLLiteResource rygel_mp2_ts_transcoder_real_create_resource (RygelTranscoder* base, RygelMediaItem* item, RygelTranscodeManager* manager, GError** error);
GstElement* rygel_gst_utils_create_element (const char* factoryname, const char* name, GError** error);
GstElement* rygel_mp2_ts_transcoder_create_encoder (RygelMP2TSTranscoder* self, const char* src_pad_name, const char* sink_pad_name, GError** error);
static gpointer rygel_mp2_ts_transcoder_parent_class = NULL;
static void rygel_mp2_ts_transcoder_finalize (GObject* obj);

static const gint RYGEL_MP2_TS_TRANSCODER_WIDTH[] = {640, 1920};
static const gint RYGEL_MP2_TS_TRANSCODER_HEIGHT[] = {480, 1080};
static const char* RYGEL_MP2_TS_TRANSCODER_PROFILES[] = {"MPEG_TS_SD_US", "MPEG_TS_HD_US"};



GType rygel_mp2_ts_profile_get_type (void) {
	static GType rygel_mp2_ts_profile_type_id = 0;
	if (G_UNLIKELY (rygel_mp2_ts_profile_type_id == 0)) {
		static const GEnumValue values[] = {{RYGEL_MP2_TS_PROFILE_SD, "RYGEL_MP2_TS_PROFILE_SD", "sd"}, {RYGEL_MP2_TS_PROFILE_HD, "RYGEL_MP2_TS_PROFILE_HD", "hd"}, {0, NULL, NULL}};
		rygel_mp2_ts_profile_type_id = g_enum_register_static ("RygelMP2TSProfile", values);
	}
	return rygel_mp2_ts_profile_type_id;
}


RygelMP2TSTranscoder* rygel_mp2_ts_transcoder_construct (GType object_type, RygelMP2TSProfile profile) {
	RygelMP2TSTranscoder * self;
	self = (RygelMP2TSTranscoder*) rygel_transcoder_construct (object_type, "video/mpeg", RYGEL_MP2_TS_TRANSCODER_PROFILES[profile], RYGEL_MEDIA_ITEM_VIDEO_CLASS);
	self->priv->profile = profile;
	return self;
}


RygelMP2TSTranscoder* rygel_mp2_ts_transcoder_new (RygelMP2TSProfile profile) {
	return rygel_mp2_ts_transcoder_construct (RYGEL_TYPE_MP2_TS_TRANSCODER, profile);
}


static GstElement* rygel_mp2_ts_transcoder_real_create_source (RygelTranscoder* base, GstElement* src, GError** error) {
	RygelMP2TSTranscoder * self;
	GError * _inner_error_;
	self = (RygelMP2TSTranscoder*) base;
	g_return_val_if_fail (src != NULL, NULL);
	_inner_error_ = NULL;
	return (GstElement*) rygel_mp2_ts_transcoder_bin_new (src, self, &_inner_error_);
}


static GUPnPDIDLLiteResource rygel_mp2_ts_transcoder_real_create_resource (RygelTranscoder* base, RygelMediaItem* item, RygelTranscodeManager* manager, GError** error) {
	RygelMP2TSTranscoder * self;
	GError * _inner_error_;
	GUPnPDIDLLiteResource res;
	self = (RygelMP2TSTranscoder*) base;
	_inner_error_ = NULL;
	res = RYGEL_TRANSCODER_CLASS (rygel_mp2_ts_transcoder_parent_class)->create_resource (RYGEL_TRANSCODER (self), item, manager, &_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		return;
	}
	res.width = RYGEL_MP2_TS_TRANSCODER_WIDTH[self->priv->profile];
	res.height = RYGEL_MP2_TS_TRANSCODER_HEIGHT[self->priv->profile];
	return res;
}


GstElement* rygel_mp2_ts_transcoder_create_encoder (RygelMP2TSTranscoder* self, const char* src_pad_name, const char* sink_pad_name, GError** error) {
	GError * _inner_error_;
	GstElement* videorate;
	GstElement* videoscale;
	GstElement* convert;
	GstElement* encoder;
	GstBin* bin;
	GstElement* _tmp3_;
	GstElement* _tmp2_;
	GstElement* _tmp1_;
	GstElement* _tmp0_;
	GstCaps* caps;
	GstPad* pad;
	GstGhostPad* ghost;
	GstPad* _tmp4_;
	GstPad* _tmp5_;
	GstGhostPad* _tmp6_;
	GstPad* _tmp7_;
	GstElement* _tmp8_;
	g_return_val_if_fail (self != NULL, NULL);
	_inner_error_ = NULL;
	videorate = rygel_gst_utils_create_element (RYGEL_MP2_TS_TRANSCODER_VIDEO_RATE, RYGEL_MP2_TS_TRANSCODER_VIDEO_RATE, &_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		return NULL;
	}
	videoscale = rygel_gst_utils_create_element (RYGEL_MP2_TS_TRANSCODER_VIDEO_SCALE, RYGEL_MP2_TS_TRANSCODER_VIDEO_SCALE, &_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		(videorate == NULL) ? NULL : (videorate = (gst_object_unref (videorate), NULL));
		return NULL;
	}
	convert = rygel_gst_utils_create_element (RYGEL_MP2_TS_TRANSCODER_COLORSPACE_CONVERT, RYGEL_MP2_TS_TRANSCODER_COLORSPACE_CONVERT, &_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		(videorate == NULL) ? NULL : (videorate = (gst_object_unref (videorate), NULL));
		(videoscale == NULL) ? NULL : (videoscale = (gst_object_unref (videoscale), NULL));
		return NULL;
	}
	encoder = rygel_gst_utils_create_element (RYGEL_MP2_TS_TRANSCODER_VIDEO_ENCODER, RYGEL_MP2_TS_TRANSCODER_VIDEO_ENCODER, &_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		(videorate == NULL) ? NULL : (videorate = (gst_object_unref (videorate), NULL));
		(videoscale == NULL) ? NULL : (videoscale = (gst_object_unref (videoscale), NULL));
		(convert == NULL) ? NULL : (convert = (gst_object_unref (convert), NULL));
		return NULL;
	}
	bin = (GstBin*) gst_bin_new ("video-encoder-bin");
	_tmp3_ = NULL;
	_tmp2_ = NULL;
	_tmp1_ = NULL;
	_tmp0_ = NULL;
	gst_bin_add_many (bin, (_tmp0_ = videorate, (_tmp0_ == NULL) ? NULL : gst_object_ref (_tmp0_)), (_tmp1_ = videoscale, (_tmp1_ == NULL) ? NULL : gst_object_ref (_tmp1_)), (_tmp2_ = convert, (_tmp2_ == NULL) ? NULL : gst_object_ref (_tmp2_)), (_tmp3_ = encoder, (_tmp3_ == NULL) ? NULL : gst_object_ref (_tmp3_)), NULL);
	gst_element_link_many (convert, videoscale, videorate, NULL);
	caps = gst_caps_new_simple ("video/x-raw-yuv", "width", G_TYPE_INT, RYGEL_MP2_TS_TRANSCODER_WIDTH[self->priv->profile], "height", G_TYPE_INT, RYGEL_MP2_TS_TRANSCODER_HEIGHT[self->priv->profile], "framerate", GST_TYPE_FRACTION, 30, 1, "pixel-aspect-ratio", GST_TYPE_FRACTION, 1, 1, NULL);
	gst_element_link_filtered (videorate, encoder, caps);
	pad = gst_element_get_static_pad (convert, "sink");
	ghost = (GstGhostPad*) gst_ghost_pad_new (sink_pad_name, pad);
	_tmp4_ = NULL;
	gst_element_add_pad ((GstElement*) bin, (_tmp4_ = (GstPad*) ghost, (_tmp4_ == NULL) ? NULL : gst_object_ref (_tmp4_)));
	_tmp5_ = NULL;
	pad = (_tmp5_ = gst_element_get_static_pad (encoder, "src"), (pad == NULL) ? NULL : (pad = (gst_object_unref (pad), NULL)), _tmp5_);
	_tmp6_ = NULL;
	ghost = (_tmp6_ = (GstGhostPad*) gst_ghost_pad_new (src_pad_name, pad), (ghost == NULL) ? NULL : (ghost = (gst_object_unref (ghost), NULL)), _tmp6_);
	_tmp7_ = NULL;
	gst_element_add_pad ((GstElement*) bin, (_tmp7_ = (GstPad*) ghost, (_tmp7_ == NULL) ? NULL : gst_object_ref (_tmp7_)));
	_tmp8_ = NULL;
	return (_tmp8_ = (GstElement*) bin, (videorate == NULL) ? NULL : (videorate = (gst_object_unref (videorate), NULL)), (videoscale == NULL) ? NULL : (videoscale = (gst_object_unref (videoscale), NULL)), (convert == NULL) ? NULL : (convert = (gst_object_unref (convert), NULL)), (encoder == NULL) ? NULL : (encoder = (gst_object_unref (encoder), NULL)), (caps == NULL) ? NULL : (caps = (gst_caps_unref (caps), NULL)), (pad == NULL) ? NULL : (pad = (gst_object_unref (pad), NULL)), (ghost == NULL) ? NULL : (ghost = (gst_object_unref (ghost), NULL)), _tmp8_);
}


static void rygel_mp2_ts_transcoder_class_init (RygelMP2TSTranscoderClass * klass) {
	rygel_mp2_ts_transcoder_parent_class = g_type_class_peek_parent (klass);
	g_type_class_add_private (klass, sizeof (RygelMP2TSTranscoderPrivate));
	RYGEL_TRANSCODER_CLASS (klass)->create_source = rygel_mp2_ts_transcoder_real_create_source;
	RYGEL_TRANSCODER_CLASS (klass)->create_resource = rygel_mp2_ts_transcoder_real_create_resource;
	G_OBJECT_CLASS (klass)->finalize = rygel_mp2_ts_transcoder_finalize;
}


static void rygel_mp2_ts_transcoder_instance_init (RygelMP2TSTranscoder * self) {
	self->priv = RYGEL_MP2_TS_TRANSCODER_GET_PRIVATE (self);
}


static void rygel_mp2_ts_transcoder_finalize (GObject* obj) {
	RygelMP2TSTranscoder * self;
	self = RYGEL_MP2_TS_TRANSCODER (obj);
	G_OBJECT_CLASS (rygel_mp2_ts_transcoder_parent_class)->finalize (obj);
}


GType rygel_mp2_ts_transcoder_get_type (void) {
	static GType rygel_mp2_ts_transcoder_type_id = 0;
	if (rygel_mp2_ts_transcoder_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (RygelMP2TSTranscoderClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) rygel_mp2_ts_transcoder_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (RygelMP2TSTranscoder), 0, (GInstanceInitFunc) rygel_mp2_ts_transcoder_instance_init, NULL };
		rygel_mp2_ts_transcoder_type_id = g_type_register_static (RYGEL_TYPE_TRANSCODER, "RygelMP2TSTranscoder", &g_define_type_info, 0);
	}
	return rygel_mp2_ts_transcoder_type_id;
}




