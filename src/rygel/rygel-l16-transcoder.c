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


#define TYPE_ENDIANNESS (endianness_get_type ())

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

#define RYGEL_TYPE_L16_TRANSCODER (rygel_l16_transcoder_get_type ())
#define RYGEL_L16_TRANSCODER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_L16_TRANSCODER, RygelL16Transcoder))
#define RYGEL_L16_TRANSCODER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_L16_TRANSCODER, RygelL16TranscoderClass))
#define RYGEL_IS_L16_TRANSCODER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_L16_TRANSCODER))
#define RYGEL_IS_L16_TRANSCODER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_L16_TRANSCODER))
#define RYGEL_L16_TRANSCODER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_L16_TRANSCODER, RygelL16TranscoderClass))

typedef struct _RygelL16Transcoder RygelL16Transcoder;
typedef struct _RygelL16TranscoderClass RygelL16TranscoderClass;
typedef struct _RygelL16TranscoderPrivate RygelL16TranscoderPrivate;

#define RYGEL_TYPE_L16_TRANSCODER_BIN (rygel_l16_transcoder_bin_get_type ())
#define RYGEL_L16_TRANSCODER_BIN(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_L16_TRANSCODER_BIN, RygelL16TranscoderBin))
#define RYGEL_L16_TRANSCODER_BIN_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_L16_TRANSCODER_BIN, RygelL16TranscoderBinClass))
#define RYGEL_IS_L16_TRANSCODER_BIN(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_L16_TRANSCODER_BIN))
#define RYGEL_IS_L16_TRANSCODER_BIN_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_L16_TRANSCODER_BIN))
#define RYGEL_L16_TRANSCODER_BIN_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_L16_TRANSCODER_BIN, RygelL16TranscoderBinClass))

typedef struct _RygelL16TranscoderBin RygelL16TranscoderBin;
typedef struct _RygelL16TranscoderBinClass RygelL16TranscoderBinClass;

typedef enum  {
	ENDIANNESS_LITTLE = G_LITTLE_ENDIAN,
	ENDIANNESS_BIG = G_BIG_ENDIAN
} Endianness;

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
 * Transcoder for linear PCM audio (LPCM). This element uses L16TrancoderBin for
 * actual transcoding.
 */
struct _RygelL16Transcoder {
	RygelTranscoder parent_instance;
	RygelL16TranscoderPrivate * priv;
};

struct _RygelL16TranscoderClass {
	RygelTranscoderClass parent_class;
};

struct _RygelL16TranscoderPrivate {
	Endianness endianness;
};



GType endianness_get_type (void);
GType rygel_transcoder_get_type (void);
GType rygel_media_object_get_type (void);
GType rygel_media_item_get_type (void);
GType rygel_transcode_manager_get_type (void);
GType rygel_l16_transcoder_get_type (void);
#define RYGEL_L16_TRANSCODER_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), RYGEL_TYPE_L16_TRANSCODER, RygelL16TranscoderPrivate))
enum  {
	RYGEL_L16_TRANSCODER_DUMMY_PROPERTY
};
#define RYGEL_L16_TRANSCODER_CHANNELS 2
#define RYGEL_L16_TRANSCODER_FREQUENCY 44100
#define RYGEL_L16_TRANSCODER_WIDTH 16
#define RYGEL_L16_TRANSCODER_DEPTH 16
#define RYGEL_L16_TRANSCODER_SIGNED TRUE
#define RYGEL_L16_TRANSCODER_AUDIO_CONVERT "audioconvert"
#define RYGEL_L16_TRANSCODER_AUDIO_RESAMPLE "audioresample"
#define RYGEL_L16_TRANSCODER_AUDIO_RATE "audiorate"
#define RYGEL_L16_TRANSCODER_CAPS_FILTER "capsfilter"
#define RYGEL_MEDIA_ITEM_AUDIO_CLASS "object.item.audioItem"
RygelTranscoder* rygel_transcoder_new (const char* mime_type, const char* dlna_profile, const char* upnp_class);
RygelTranscoder* rygel_transcoder_construct (GType object_type, const char* mime_type, const char* dlna_profile, const char* upnp_class);
RygelL16Transcoder* rygel_l16_transcoder_new (Endianness endianness);
RygelL16Transcoder* rygel_l16_transcoder_construct (GType object_type, Endianness endianness);
RygelL16Transcoder* rygel_l16_transcoder_new (Endianness endianness);
RygelL16TranscoderBin* rygel_l16_transcoder_bin_new (GstElement* src, RygelL16Transcoder* transcoder, GError** error);
RygelL16TranscoderBin* rygel_l16_transcoder_bin_construct (GType object_type, GstElement* src, RygelL16Transcoder* transcoder, GError** error);
GType rygel_l16_transcoder_bin_get_type (void);
static GstElement* rygel_l16_transcoder_real_create_source (RygelTranscoder* base, GstElement* src, GError** error);
GUPnPDIDLLiteResource rygel_transcoder_create_resource (RygelTranscoder* self, RygelMediaItem* item, RygelTranscodeManager* manager, GError** error);
static GUPnPDIDLLiteResource rygel_l16_transcoder_real_create_resource (RygelTranscoder* base, RygelMediaItem* item, RygelTranscodeManager* manager, GError** error);
GstElement* rygel_gst_utils_create_element (const char* factoryname, const char* name, GError** error);
static inline void _dynamic_set_caps4 (GstElement* obj, GstCaps* value);
GstElement* rygel_l16_transcoder_create_encoder (RygelL16Transcoder* self, const char* src_pad_name, const char* sink_pad_name, GError** error);
static gpointer rygel_l16_transcoder_parent_class = NULL;
static void rygel_l16_transcoder_finalize (GObject* obj);




GType endianness_get_type (void) {
	static GType endianness_type_id = 0;
	if (G_UNLIKELY (endianness_type_id == 0)) {
		static const GEnumValue values[] = {{ENDIANNESS_LITTLE, "ENDIANNESS_LITTLE", "little"}, {ENDIANNESS_BIG, "ENDIANNESS_BIG", "big"}, {0, NULL, NULL}};
		endianness_type_id = g_enum_register_static ("Endianness", values);
	}
	return endianness_type_id;
}


RygelL16Transcoder* rygel_l16_transcoder_construct (GType object_type, Endianness endianness) {
	RygelL16Transcoder * self;
	char* _tmp6_;
	char* _tmp5_;
	char* _tmp4_;
	char* _tmp3_;
	char* _tmp2_;
	char* _tmp1_;
	char* _tmp0_;
	char* _tmp7_;
	char* mime_type;
	_tmp6_ = NULL;
	_tmp5_ = NULL;
	_tmp4_ = NULL;
	_tmp3_ = NULL;
	_tmp2_ = NULL;
	_tmp1_ = NULL;
	_tmp0_ = NULL;
	_tmp7_ = NULL;
	mime_type = (_tmp7_ = g_strconcat (_tmp5_ = g_strconcat (_tmp4_ = g_strconcat (_tmp2_ = g_strconcat (_tmp1_ = g_strconcat ("audio/L", _tmp0_ = g_strdup_printf ("%i", RYGEL_L16_TRANSCODER_WIDTH), NULL), ";rate=", NULL), _tmp3_ = g_strdup_printf ("%i", RYGEL_L16_TRANSCODER_FREQUENCY), NULL), ";channels=", NULL), _tmp6_ = g_strdup_printf ("%i", RYGEL_L16_TRANSCODER_CHANNELS), NULL), _tmp6_ = (g_free (_tmp6_), NULL), _tmp5_ = (g_free (_tmp5_), NULL), _tmp4_ = (g_free (_tmp4_), NULL), _tmp3_ = (g_free (_tmp3_), NULL), _tmp2_ = (g_free (_tmp2_), NULL), _tmp1_ = (g_free (_tmp1_), NULL), _tmp0_ = (g_free (_tmp0_), NULL), _tmp7_);
	self = (RygelL16Transcoder*) rygel_transcoder_construct (object_type, mime_type, "LPCM", RYGEL_MEDIA_ITEM_AUDIO_CLASS);
	self->priv->endianness = endianness;
	mime_type = (g_free (mime_type), NULL);
	return self;
}


RygelL16Transcoder* rygel_l16_transcoder_new (Endianness endianness) {
	return rygel_l16_transcoder_construct (RYGEL_TYPE_L16_TRANSCODER, endianness);
}


static GstElement* rygel_l16_transcoder_real_create_source (RygelTranscoder* base, GstElement* src, GError** error) {
	RygelL16Transcoder * self;
	GError * _inner_error_;
	self = (RygelL16Transcoder*) base;
	g_return_val_if_fail (src != NULL, NULL);
	_inner_error_ = NULL;
	return (GstElement*) rygel_l16_transcoder_bin_new (src, self, &_inner_error_);
}


static GUPnPDIDLLiteResource rygel_l16_transcoder_real_create_resource (RygelTranscoder* base, RygelMediaItem* item, RygelTranscodeManager* manager, GError** error) {
	RygelL16Transcoder * self;
	GError * _inner_error_;
	GUPnPDIDLLiteResource res;
	self = (RygelL16Transcoder*) base;
	_inner_error_ = NULL;
	res = RYGEL_TRANSCODER_CLASS (rygel_l16_transcoder_parent_class)->create_resource (RYGEL_TRANSCODER (self), item, manager, &_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		return;
	}
	res.sample_freq = RYGEL_L16_TRANSCODER_FREQUENCY;
	res.n_audio_channels = RYGEL_L16_TRANSCODER_CHANNELS;
	res.bits_per_sample = RYGEL_L16_TRANSCODER_WIDTH;
	return res;
}


static inline void _dynamic_set_caps4 (GstElement* obj, GstCaps* value) {
	g_object_set (obj, "caps", value, NULL);
}


GstElement* rygel_l16_transcoder_create_encoder (RygelL16Transcoder* self, const char* src_pad_name, const char* sink_pad_name, GError** error) {
	GError * _inner_error_;
	GstElement* convert1;
	GstElement* resample;
	GstElement* audiorate;
	GstElement* convert2;
	GstElement* capsfilter;
	GstBin* bin;
	GstElement* _tmp4_;
	GstElement* _tmp3_;
	GstElement* _tmp2_;
	GstElement* _tmp1_;
	GstElement* _tmp0_;
	GstCaps* _tmp5_;
	GstPad* pad;
	GstGhostPad* ghost;
	GstPad* _tmp6_;
	GstPad* _tmp7_;
	GstGhostPad* _tmp8_;
	GstPad* _tmp9_;
	GstElement* _tmp10_;
	g_return_val_if_fail (self != NULL, NULL);
	_inner_error_ = NULL;
	convert1 = rygel_gst_utils_create_element (RYGEL_L16_TRANSCODER_AUDIO_CONVERT, NULL, &_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		return NULL;
	}
	resample = rygel_gst_utils_create_element (RYGEL_L16_TRANSCODER_AUDIO_RESAMPLE, RYGEL_L16_TRANSCODER_AUDIO_RESAMPLE, &_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		(convert1 == NULL) ? NULL : (convert1 = (gst_object_unref (convert1), NULL));
		return NULL;
	}
	audiorate = rygel_gst_utils_create_element (RYGEL_L16_TRANSCODER_AUDIO_RATE, NULL, &_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		(convert1 == NULL) ? NULL : (convert1 = (gst_object_unref (convert1), NULL));
		(resample == NULL) ? NULL : (resample = (gst_object_unref (resample), NULL));
		return NULL;
	}
	convert2 = rygel_gst_utils_create_element (RYGEL_L16_TRANSCODER_AUDIO_CONVERT, NULL, &_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		(convert1 == NULL) ? NULL : (convert1 = (gst_object_unref (convert1), NULL));
		(resample == NULL) ? NULL : (resample = (gst_object_unref (resample), NULL));
		(audiorate == NULL) ? NULL : (audiorate = (gst_object_unref (audiorate), NULL));
		return NULL;
	}
	capsfilter = rygel_gst_utils_create_element (RYGEL_L16_TRANSCODER_CAPS_FILTER, RYGEL_L16_TRANSCODER_CAPS_FILTER, &_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		(convert1 == NULL) ? NULL : (convert1 = (gst_object_unref (convert1), NULL));
		(resample == NULL) ? NULL : (resample = (gst_object_unref (resample), NULL));
		(audiorate == NULL) ? NULL : (audiorate = (gst_object_unref (audiorate), NULL));
		(convert2 == NULL) ? NULL : (convert2 = (gst_object_unref (convert2), NULL));
		return NULL;
	}
	bin = (GstBin*) gst_bin_new ("l16-encoder-bin");
	_tmp4_ = NULL;
	_tmp3_ = NULL;
	_tmp2_ = NULL;
	_tmp1_ = NULL;
	_tmp0_ = NULL;
	gst_bin_add_many (bin, (_tmp0_ = convert1, (_tmp0_ == NULL) ? NULL : gst_object_ref (_tmp0_)), (_tmp1_ = resample, (_tmp1_ == NULL) ? NULL : gst_object_ref (_tmp1_)), (_tmp2_ = audiorate, (_tmp2_ == NULL) ? NULL : gst_object_ref (_tmp2_)), (_tmp3_ = convert2, (_tmp3_ == NULL) ? NULL : gst_object_ref (_tmp3_)), (_tmp4_ = capsfilter, (_tmp4_ == NULL) ? NULL : gst_object_ref (_tmp4_)), NULL);
	_tmp5_ = NULL;
	_dynamic_set_caps4 (capsfilter, _tmp5_ = gst_caps_new_simple ("audio/x-raw-int", "channels", G_TYPE_INT, RYGEL_L16_TRANSCODER_CHANNELS, "rate", G_TYPE_INT, RYGEL_L16_TRANSCODER_FREQUENCY, "width", G_TYPE_INT, RYGEL_L16_TRANSCODER_WIDTH, "depth", G_TYPE_INT, RYGEL_L16_TRANSCODER_DEPTH, "signed", G_TYPE_BOOLEAN, RYGEL_L16_TRANSCODER_SIGNED, "endianness", G_TYPE_INT, self->priv->endianness, NULL));
	(_tmp5_ == NULL) ? NULL : (_tmp5_ = (gst_caps_unref (_tmp5_), NULL));
	gst_element_link_many (convert1, resample, audiorate, convert2, capsfilter, NULL);
	pad = gst_element_get_static_pad (convert1, "sink");
	ghost = (GstGhostPad*) gst_ghost_pad_new (sink_pad_name, pad);
	_tmp6_ = NULL;
	gst_element_add_pad ((GstElement*) bin, (_tmp6_ = (GstPad*) ghost, (_tmp6_ == NULL) ? NULL : gst_object_ref (_tmp6_)));
	_tmp7_ = NULL;
	pad = (_tmp7_ = gst_element_get_static_pad (capsfilter, "src"), (pad == NULL) ? NULL : (pad = (gst_object_unref (pad), NULL)), _tmp7_);
	_tmp8_ = NULL;
	ghost = (_tmp8_ = (GstGhostPad*) gst_ghost_pad_new (src_pad_name, pad), (ghost == NULL) ? NULL : (ghost = (gst_object_unref (ghost), NULL)), _tmp8_);
	_tmp9_ = NULL;
	gst_element_add_pad ((GstElement*) bin, (_tmp9_ = (GstPad*) ghost, (_tmp9_ == NULL) ? NULL : gst_object_ref (_tmp9_)));
	_tmp10_ = NULL;
	return (_tmp10_ = (GstElement*) bin, (convert1 == NULL) ? NULL : (convert1 = (gst_object_unref (convert1), NULL)), (resample == NULL) ? NULL : (resample = (gst_object_unref (resample), NULL)), (audiorate == NULL) ? NULL : (audiorate = (gst_object_unref (audiorate), NULL)), (convert2 == NULL) ? NULL : (convert2 = (gst_object_unref (convert2), NULL)), (capsfilter == NULL) ? NULL : (capsfilter = (gst_object_unref (capsfilter), NULL)), (pad == NULL) ? NULL : (pad = (gst_object_unref (pad), NULL)), (ghost == NULL) ? NULL : (ghost = (gst_object_unref (ghost), NULL)), _tmp10_);
}


static void rygel_l16_transcoder_class_init (RygelL16TranscoderClass * klass) {
	rygel_l16_transcoder_parent_class = g_type_class_peek_parent (klass);
	g_type_class_add_private (klass, sizeof (RygelL16TranscoderPrivate));
	RYGEL_TRANSCODER_CLASS (klass)->create_source = rygel_l16_transcoder_real_create_source;
	RYGEL_TRANSCODER_CLASS (klass)->create_resource = rygel_l16_transcoder_real_create_resource;
	G_OBJECT_CLASS (klass)->finalize = rygel_l16_transcoder_finalize;
}


static void rygel_l16_transcoder_instance_init (RygelL16Transcoder * self) {
	self->priv = RYGEL_L16_TRANSCODER_GET_PRIVATE (self);
}


static void rygel_l16_transcoder_finalize (GObject* obj) {
	RygelL16Transcoder * self;
	self = RYGEL_L16_TRANSCODER (obj);
	G_OBJECT_CLASS (rygel_l16_transcoder_parent_class)->finalize (obj);
}


GType rygel_l16_transcoder_get_type (void) {
	static GType rygel_l16_transcoder_type_id = 0;
	if (rygel_l16_transcoder_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (RygelL16TranscoderClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) rygel_l16_transcoder_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (RygelL16Transcoder), 0, (GInstanceInitFunc) rygel_l16_transcoder_instance_init, NULL };
		rygel_l16_transcoder_type_id = g_type_register_static (RYGEL_TYPE_TRANSCODER, "RygelL16Transcoder", &g_define_type_info, 0);
	}
	return rygel_l16_transcoder_type_id;
}




