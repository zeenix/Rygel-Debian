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

#define RYGEL_TYPE_MP3_TRANSCODER (rygel_mp3_transcoder_get_type ())
#define RYGEL_MP3_TRANSCODER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_MP3_TRANSCODER, RygelMP3Transcoder))
#define RYGEL_MP3_TRANSCODER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_MP3_TRANSCODER, RygelMP3TranscoderClass))
#define RYGEL_IS_MP3_TRANSCODER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_MP3_TRANSCODER))
#define RYGEL_IS_MP3_TRANSCODER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_MP3_TRANSCODER))
#define RYGEL_MP3_TRANSCODER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_MP3_TRANSCODER, RygelMP3TranscoderClass))

typedef struct _RygelMP3Transcoder RygelMP3Transcoder;
typedef struct _RygelMP3TranscoderClass RygelMP3TranscoderClass;
typedef struct _RygelMP3TranscoderPrivate RygelMP3TranscoderPrivate;

#define RYGEL_TYPE_MP3_LAYER (rygel_mp3_layer_get_type ())

#define RYGEL_TYPE_MP3_TRANSCODER_BIN (rygel_mp3_transcoder_bin_get_type ())
#define RYGEL_MP3_TRANSCODER_BIN(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_MP3_TRANSCODER_BIN, RygelMP3TranscoderBin))
#define RYGEL_MP3_TRANSCODER_BIN_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_MP3_TRANSCODER_BIN, RygelMP3TranscoderBinClass))
#define RYGEL_IS_MP3_TRANSCODER_BIN(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_MP3_TRANSCODER_BIN))
#define RYGEL_IS_MP3_TRANSCODER_BIN_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_MP3_TRANSCODER_BIN))
#define RYGEL_MP3_TRANSCODER_BIN_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_MP3_TRANSCODER_BIN, RygelMP3TranscoderBinClass))

typedef struct _RygelMP3TranscoderBin RygelMP3TranscoderBin;
typedef struct _RygelMP3TranscoderBinClass RygelMP3TranscoderBinClass;

#define TYPE_ENDIANNESS (endianness_get_type ())

#define RYGEL_TYPE_L16_TRANSCODER (rygel_l16_transcoder_get_type ())
#define RYGEL_L16_TRANSCODER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_L16_TRANSCODER, RygelL16Transcoder))
#define RYGEL_L16_TRANSCODER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_L16_TRANSCODER, RygelL16TranscoderClass))
#define RYGEL_IS_L16_TRANSCODER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_L16_TRANSCODER))
#define RYGEL_IS_L16_TRANSCODER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_L16_TRANSCODER))
#define RYGEL_L16_TRANSCODER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_L16_TRANSCODER, RygelL16TranscoderClass))

typedef struct _RygelL16Transcoder RygelL16Transcoder;
typedef struct _RygelL16TranscoderClass RygelL16TranscoderClass;

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
 * Transcoder for mpeg 1 layer 2 and 3 audio. This element uses MP3TrancoderBin
 * for actual transcoding.
 */
struct _RygelMP3Transcoder {
	RygelTranscoder parent_instance;
	RygelMP3TranscoderPrivate * priv;
};

struct _RygelMP3TranscoderClass {
	RygelTranscoderClass parent_class;
};

typedef enum  {
	RYGEL_MP3_LAYER_TWO = 1,
	RYGEL_MP3_LAYER_THREE = 2
} RygelMP3Layer;

struct _RygelMP3TranscoderPrivate {
	RygelMP3Layer layer;
};

typedef enum  {
	ENDIANNESS_LITTLE = G_LITTLE_ENDIAN,
	ENDIANNESS_BIG = G_BIG_ENDIAN
} Endianness;



GType rygel_transcoder_get_type (void);
GType rygel_media_object_get_type (void);
GType rygel_media_item_get_type (void);
GType rygel_transcode_manager_get_type (void);
GType rygel_mp3_transcoder_get_type (void);
GType rygel_mp3_layer_get_type (void);
#define RYGEL_MP3_TRANSCODER_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), RYGEL_TYPE_MP3_TRANSCODER, RygelMP3TranscoderPrivate))
enum  {
	RYGEL_MP3_TRANSCODER_DUMMY_PROPERTY
};
#define RYGEL_MP3_TRANSCODER_BITRATE 256
#define RYGEL_MP3_TRANSCODER_AUDIO_PARSER "mp3parse"
#define RYGEL_MP3_TRANSCODER_CONVERT_SINK_PAD "convert-sink-pad"
#define RYGEL_MEDIA_ITEM_AUDIO_CLASS "object.item.audioItem"
RygelTranscoder* rygel_transcoder_new (const char* mime_type, const char* dlna_profile, const char* upnp_class);
RygelTranscoder* rygel_transcoder_construct (GType object_type, const char* mime_type, const char* dlna_profile, const char* upnp_class);
RygelMP3Transcoder* rygel_mp3_transcoder_new (RygelMP3Layer layer);
RygelMP3Transcoder* rygel_mp3_transcoder_construct (GType object_type, RygelMP3Layer layer);
RygelMP3Transcoder* rygel_mp3_transcoder_new (RygelMP3Layer layer);
RygelMP3TranscoderBin* rygel_mp3_transcoder_bin_new (GstElement* src, RygelMP3Transcoder* transcoder, GError** error);
RygelMP3TranscoderBin* rygel_mp3_transcoder_bin_construct (GType object_type, GstElement* src, RygelMP3Transcoder* transcoder, GError** error);
GType rygel_mp3_transcoder_bin_get_type (void);
static GstElement* rygel_mp3_transcoder_real_create_source (RygelTranscoder* base, GstElement* src, GError** error);
GUPnPDIDLLiteResource rygel_transcoder_create_resource (RygelTranscoder* self, RygelMediaItem* item, RygelTranscodeManager* manager, GError** error);
static GUPnPDIDLLiteResource rygel_mp3_transcoder_real_create_resource (RygelTranscoder* base, RygelMediaItem* item, RygelTranscodeManager* manager, GError** error);
GType endianness_get_type (void);
RygelL16Transcoder* rygel_l16_transcoder_new (Endianness endianness);
RygelL16Transcoder* rygel_l16_transcoder_construct (GType object_type, Endianness endianness);
GType rygel_l16_transcoder_get_type (void);
GstElement* rygel_l16_transcoder_create_encoder (RygelL16Transcoder* self, const char* src_pad_name, const char* sink_pad_name, GError** error);
GstElement* rygel_gst_utils_create_element (const char* factoryname, const char* name, GError** error);
static inline void _dynamic_set_quality2 (GstElement* obj, gint value);
static inline void _dynamic_set_bitrate3 (GstElement* obj, gint value);
GstElement* rygel_mp3_transcoder_create_encoder (RygelMP3Transcoder* self, const char* src_pad_name, const char* sink_pad_name, GError** error);
static gpointer rygel_mp3_transcoder_parent_class = NULL;
static void rygel_mp3_transcoder_finalize (GObject* obj);

static const char* RYGEL_MP3_TRANSCODER_AUDIO_ENCODER[] = {NULL, "twolame", "lame"};


RygelMP3Transcoder* rygel_mp3_transcoder_construct (GType object_type, RygelMP3Layer layer) {
	RygelMP3Transcoder * self;
	self = (RygelMP3Transcoder*) rygel_transcoder_construct (object_type, "audio/mpeg", "MP3", RYGEL_MEDIA_ITEM_AUDIO_CLASS);
	self->priv->layer = layer;
	return self;
}


RygelMP3Transcoder* rygel_mp3_transcoder_new (RygelMP3Layer layer) {
	return rygel_mp3_transcoder_construct (RYGEL_TYPE_MP3_TRANSCODER, layer);
}


static GstElement* rygel_mp3_transcoder_real_create_source (RygelTranscoder* base, GstElement* src, GError** error) {
	RygelMP3Transcoder * self;
	GError * _inner_error_;
	self = (RygelMP3Transcoder*) base;
	g_return_val_if_fail (src != NULL, NULL);
	_inner_error_ = NULL;
	return (GstElement*) rygel_mp3_transcoder_bin_new (src, self, &_inner_error_);
}


static GUPnPDIDLLiteResource rygel_mp3_transcoder_real_create_resource (RygelTranscoder* base, RygelMediaItem* item, RygelTranscodeManager* manager, GError** error) {
	RygelMP3Transcoder * self;
	GError * _inner_error_;
	GUPnPDIDLLiteResource res;
	self = (RygelMP3Transcoder*) base;
	_inner_error_ = NULL;
	res = RYGEL_TRANSCODER_CLASS (rygel_mp3_transcoder_parent_class)->create_resource (RYGEL_TRANSCODER (self), item, manager, &_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		return;
	}
	res.bitrate = RYGEL_MP3_TRANSCODER_BITRATE;
	return res;
}


static inline void _dynamic_set_quality2 (GstElement* obj, gint value) {
	g_object_set (obj, "quality", value, NULL);
}


static inline void _dynamic_set_bitrate3 (GstElement* obj, gint value) {
	g_object_set (obj, "bitrate", value, NULL);
}


GstElement* rygel_mp3_transcoder_create_encoder (RygelMP3Transcoder* self, const char* src_pad_name, const char* sink_pad_name, GError** error) {
	GError * _inner_error_;
	RygelL16Transcoder* l16_transcoder;
	GstElement* convert;
	GstElement* encoder;
	GstElement* parser;
	GstBin* bin;
	GstElement* _tmp2_;
	GstElement* _tmp1_;
	GstElement* _tmp0_;
	GstPad* pad;
	GstGhostPad* ghost;
	GstPad* _tmp3_;
	GstPad* _tmp4_;
	GstGhostPad* _tmp5_;
	GstPad* _tmp6_;
	GstElement* _tmp7_;
	g_return_val_if_fail (self != NULL, NULL);
	_inner_error_ = NULL;
	l16_transcoder = rygel_l16_transcoder_new (ENDIANNESS_LITTLE);
	convert = rygel_l16_transcoder_create_encoder (l16_transcoder, NULL, RYGEL_MP3_TRANSCODER_CONVERT_SINK_PAD, &_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		(l16_transcoder == NULL) ? NULL : (l16_transcoder = (g_object_unref (l16_transcoder), NULL));
		return NULL;
	}
	encoder = rygel_gst_utils_create_element (RYGEL_MP3_TRANSCODER_AUDIO_ENCODER[self->priv->layer], RYGEL_MP3_TRANSCODER_AUDIO_ENCODER[self->priv->layer], &_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		(l16_transcoder == NULL) ? NULL : (l16_transcoder = (g_object_unref (l16_transcoder), NULL));
		(convert == NULL) ? NULL : (convert = (gst_object_unref (convert), NULL));
		return NULL;
	}
	parser = rygel_gst_utils_create_element (RYGEL_MP3_TRANSCODER_AUDIO_PARSER, RYGEL_MP3_TRANSCODER_AUDIO_PARSER, &_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		(l16_transcoder == NULL) ? NULL : (l16_transcoder = (g_object_unref (l16_transcoder), NULL));
		(convert == NULL) ? NULL : (convert = (gst_object_unref (convert), NULL));
		(encoder == NULL) ? NULL : (encoder = (gst_object_unref (encoder), NULL));
		return NULL;
	}
	if (self->priv->layer == RYGEL_MP3_LAYER_THREE) {
		/* Best quality*/
		_dynamic_set_quality2 (encoder, 0);
	}
	_dynamic_set_bitrate3 (encoder, RYGEL_MP3_TRANSCODER_BITRATE);
	bin = (GstBin*) gst_bin_new ("mp3-encoder-bin");
	_tmp2_ = NULL;
	_tmp1_ = NULL;
	_tmp0_ = NULL;
	gst_bin_add_many (bin, (_tmp0_ = convert, (_tmp0_ == NULL) ? NULL : gst_object_ref (_tmp0_)), (_tmp1_ = encoder, (_tmp1_ == NULL) ? NULL : gst_object_ref (_tmp1_)), (_tmp2_ = parser, (_tmp2_ == NULL) ? NULL : gst_object_ref (_tmp2_)), NULL);
	gst_element_link_many (convert, encoder, parser, NULL);
	pad = gst_element_get_static_pad (convert, RYGEL_MP3_TRANSCODER_CONVERT_SINK_PAD);
	ghost = (GstGhostPad*) gst_ghost_pad_new (sink_pad_name, pad);
	_tmp3_ = NULL;
	gst_element_add_pad ((GstElement*) bin, (_tmp3_ = (GstPad*) ghost, (_tmp3_ == NULL) ? NULL : gst_object_ref (_tmp3_)));
	_tmp4_ = NULL;
	pad = (_tmp4_ = gst_element_get_static_pad (parser, "src"), (pad == NULL) ? NULL : (pad = (gst_object_unref (pad), NULL)), _tmp4_);
	_tmp5_ = NULL;
	ghost = (_tmp5_ = (GstGhostPad*) gst_ghost_pad_new (src_pad_name, pad), (ghost == NULL) ? NULL : (ghost = (gst_object_unref (ghost), NULL)), _tmp5_);
	_tmp6_ = NULL;
	gst_element_add_pad ((GstElement*) bin, (_tmp6_ = (GstPad*) ghost, (_tmp6_ == NULL) ? NULL : gst_object_ref (_tmp6_)));
	_tmp7_ = NULL;
	return (_tmp7_ = (GstElement*) bin, (l16_transcoder == NULL) ? NULL : (l16_transcoder = (g_object_unref (l16_transcoder), NULL)), (convert == NULL) ? NULL : (convert = (gst_object_unref (convert), NULL)), (encoder == NULL) ? NULL : (encoder = (gst_object_unref (encoder), NULL)), (parser == NULL) ? NULL : (parser = (gst_object_unref (parser), NULL)), (pad == NULL) ? NULL : (pad = (gst_object_unref (pad), NULL)), (ghost == NULL) ? NULL : (ghost = (gst_object_unref (ghost), NULL)), _tmp7_);
}


static void rygel_mp3_transcoder_class_init (RygelMP3TranscoderClass * klass) {
	rygel_mp3_transcoder_parent_class = g_type_class_peek_parent (klass);
	g_type_class_add_private (klass, sizeof (RygelMP3TranscoderPrivate));
	RYGEL_TRANSCODER_CLASS (klass)->create_source = rygel_mp3_transcoder_real_create_source;
	RYGEL_TRANSCODER_CLASS (klass)->create_resource = rygel_mp3_transcoder_real_create_resource;
	G_OBJECT_CLASS (klass)->finalize = rygel_mp3_transcoder_finalize;
}


static void rygel_mp3_transcoder_instance_init (RygelMP3Transcoder * self) {
	self->priv = RYGEL_MP3_TRANSCODER_GET_PRIVATE (self);
}


static void rygel_mp3_transcoder_finalize (GObject* obj) {
	RygelMP3Transcoder * self;
	self = RYGEL_MP3_TRANSCODER (obj);
	G_OBJECT_CLASS (rygel_mp3_transcoder_parent_class)->finalize (obj);
}


GType rygel_mp3_transcoder_get_type (void) {
	static GType rygel_mp3_transcoder_type_id = 0;
	if (rygel_mp3_transcoder_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (RygelMP3TranscoderClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) rygel_mp3_transcoder_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (RygelMP3Transcoder), 0, (GInstanceInitFunc) rygel_mp3_transcoder_instance_init, NULL };
		rygel_mp3_transcoder_type_id = g_type_register_static (RYGEL_TYPE_TRANSCODER, "RygelMP3Transcoder", &g_define_type_info, 0);
	}
	return rygel_mp3_transcoder_type_id;
}




