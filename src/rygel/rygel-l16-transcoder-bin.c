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
#include <stdlib.h>
#include <string.h>


#define RYGEL_TYPE_L16_TRANSCODER_BIN (rygel_l16_transcoder_bin_get_type ())
#define RYGEL_L16_TRANSCODER_BIN(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_L16_TRANSCODER_BIN, RygelL16TranscoderBin))
#define RYGEL_L16_TRANSCODER_BIN_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_L16_TRANSCODER_BIN, RygelL16TranscoderBinClass))
#define RYGEL_IS_L16_TRANSCODER_BIN(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_L16_TRANSCODER_BIN))
#define RYGEL_IS_L16_TRANSCODER_BIN_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_L16_TRANSCODER_BIN))
#define RYGEL_L16_TRANSCODER_BIN_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_L16_TRANSCODER_BIN, RygelL16TranscoderBinClass))

typedef struct _RygelL16TranscoderBin RygelL16TranscoderBin;
typedef struct _RygelL16TranscoderBinClass RygelL16TranscoderBinClass;
typedef struct _RygelL16TranscoderBinPrivate RygelL16TranscoderBinPrivate;

#define RYGEL_TYPE_TRANSCODER (rygel_transcoder_get_type ())
#define RYGEL_TRANSCODER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_TRANSCODER, RygelTranscoder))
#define RYGEL_TRANSCODER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_TRANSCODER, RygelTranscoderClass))
#define RYGEL_IS_TRANSCODER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_TRANSCODER))
#define RYGEL_IS_TRANSCODER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_TRANSCODER))
#define RYGEL_TRANSCODER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_TRANSCODER, RygelTranscoderClass))

typedef struct _RygelTranscoder RygelTranscoder;
typedef struct _RygelTranscoderClass RygelTranscoderClass;

#define RYGEL_TYPE_L16_TRANSCODER (rygel_l16_transcoder_get_type ())
#define RYGEL_L16_TRANSCODER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_L16_TRANSCODER, RygelL16Transcoder))
#define RYGEL_L16_TRANSCODER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_L16_TRANSCODER, RygelL16TranscoderClass))
#define RYGEL_IS_L16_TRANSCODER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_L16_TRANSCODER))
#define RYGEL_IS_L16_TRANSCODER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_L16_TRANSCODER))
#define RYGEL_L16_TRANSCODER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_L16_TRANSCODER, RygelL16TranscoderClass))

typedef struct _RygelL16Transcoder RygelL16Transcoder;
typedef struct _RygelL16TranscoderClass RygelL16TranscoderClass;

/**
 * A Gst.Bin derivative that implements transcoding of any type of media (using
 * decodebin2) to linear PCM audio.
 */
struct _RygelL16TranscoderBin {
	GstBin parent_instance;
	RygelL16TranscoderBinPrivate * priv;
};

struct _RygelL16TranscoderBinClass {
	GstBinClass parent_class;
};

struct _RygelL16TranscoderBinPrivate {
	GstElement* audio_enc;
};

typedef enum  {
	RYGEL_LIVE_RESPONSE_ERROR_MISSING_PLUGIN,
	RYGEL_LIVE_RESPONSE_ERROR_LINK
} RygelLiveResponseError;
#define RYGEL_LIVE_RESPONSE_ERROR rygel_live_response_error_quark ()


GType rygel_l16_transcoder_bin_get_type (void);
#define RYGEL_L16_TRANSCODER_BIN_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), RYGEL_TYPE_L16_TRANSCODER_BIN, RygelL16TranscoderBinPrivate))
enum  {
	RYGEL_L16_TRANSCODER_BIN_DUMMY_PROPERTY
};
#define RYGEL_L16_TRANSCODER_BIN_DECODEBIN "decodebin2"
#define RYGEL_L16_TRANSCODER_BIN_AUDIO_SRC_PAD "audio-src-pad"
#define RYGEL_L16_TRANSCODER_BIN_AUDIO_SINK_PAD "audio-sink-pad"
GstElement* rygel_gst_utils_create_element (const char* factoryname, const char* name, GError** error);
GType rygel_transcoder_get_type (void);
GType rygel_l16_transcoder_get_type (void);
GstElement* rygel_l16_transcoder_create_encoder (RygelL16Transcoder* self, const char* src_pad_name, const char* sink_pad_name, GError** error);
static void rygel_l16_transcoder_bin_decodebin_pad_added (RygelL16TranscoderBin* self, GstElement* decodebin, GstPad* new_pad);
static void _rygel_l16_transcoder_bin_decodebin_pad_added_gst_element_pad_added (GstElement* _sender, GstPad* pad, gpointer self);
RygelL16TranscoderBin* rygel_l16_transcoder_bin_new (GstElement* src, RygelL16Transcoder* transcoder, GError** error);
RygelL16TranscoderBin* rygel_l16_transcoder_bin_construct (GType object_type, GstElement* src, RygelL16Transcoder* transcoder, GError** error);
RygelL16TranscoderBin* rygel_l16_transcoder_bin_new (GstElement* src, RygelL16Transcoder* transcoder, GError** error);
void rygel_gst_utils_post_error (GstElement* dest, GError* _error_);
GQuark rygel_live_response_error_quark (void);
static gpointer rygel_l16_transcoder_bin_parent_class = NULL;
static void rygel_l16_transcoder_bin_finalize (GObject* obj);



static void _rygel_l16_transcoder_bin_decodebin_pad_added_gst_element_pad_added (GstElement* _sender, GstPad* pad, gpointer self) {
	rygel_l16_transcoder_bin_decodebin_pad_added (self, _sender, pad);
}


RygelL16TranscoderBin* rygel_l16_transcoder_bin_construct (GType object_type, GstElement* src, RygelL16Transcoder* transcoder, GError** error) {
	GError * _inner_error_;
	RygelL16TranscoderBin * self;
	GstElement* decodebin;
	GstElement* _tmp0_;
	GstElement* _tmp1_;
	GstElement* _tmp4_;
	GstElement* _tmp3_;
	GstElement* _tmp2_;
	GstPad* src_pad;
	GstGhostPad* ghost;
	GstPad* _tmp5_;
	g_return_val_if_fail (src != NULL, NULL);
	g_return_val_if_fail (transcoder != NULL, NULL);
	_inner_error_ = NULL;
	self = g_object_newv (object_type, 0, NULL);
	decodebin = rygel_gst_utils_create_element (RYGEL_L16_TRANSCODER_BIN_DECODEBIN, RYGEL_L16_TRANSCODER_BIN_DECODEBIN, &_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		return;
	}
	_tmp0_ = rygel_l16_transcoder_create_encoder (transcoder, RYGEL_L16_TRANSCODER_BIN_AUDIO_SRC_PAD, RYGEL_L16_TRANSCODER_BIN_AUDIO_SINK_PAD, &_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		(decodebin == NULL) ? NULL : (decodebin = (gst_object_unref (decodebin), NULL));
		return;
	}
	_tmp1_ = NULL;
	self->priv->audio_enc = (_tmp1_ = _tmp0_, (self->priv->audio_enc == NULL) ? NULL : (self->priv->audio_enc = (gst_object_unref (self->priv->audio_enc), NULL)), _tmp1_);
	_tmp4_ = NULL;
	_tmp3_ = NULL;
	_tmp2_ = NULL;
	gst_bin_add_many ((GstBin*) self, (_tmp2_ = src, (_tmp2_ == NULL) ? NULL : gst_object_ref (_tmp2_)), (_tmp3_ = decodebin, (_tmp3_ == NULL) ? NULL : gst_object_ref (_tmp3_)), (_tmp4_ = self->priv->audio_enc, (_tmp4_ == NULL) ? NULL : gst_object_ref (_tmp4_)), NULL);
	gst_element_link (src, decodebin);
	src_pad = gst_element_get_static_pad (self->priv->audio_enc, RYGEL_L16_TRANSCODER_BIN_AUDIO_SRC_PAD);
	ghost = (GstGhostPad*) gst_ghost_pad_new (NULL, src_pad);
	_tmp5_ = NULL;
	gst_element_add_pad ((GstElement*) self, (_tmp5_ = (GstPad*) ghost, (_tmp5_ == NULL) ? NULL : gst_object_ref (_tmp5_)));
	g_signal_connect_object (decodebin, "pad-added", (GCallback) _rygel_l16_transcoder_bin_decodebin_pad_added_gst_element_pad_added, self, 0);
	(decodebin == NULL) ? NULL : (decodebin = (gst_object_unref (decodebin), NULL));
	(src_pad == NULL) ? NULL : (src_pad = (gst_object_unref (src_pad), NULL));
	(ghost == NULL) ? NULL : (ghost = (gst_object_unref (ghost), NULL));
	return self;
}


RygelL16TranscoderBin* rygel_l16_transcoder_bin_new (GstElement* src, RygelL16Transcoder* transcoder, GError** error) {
	return rygel_l16_transcoder_bin_construct (RYGEL_TYPE_L16_TRANSCODER_BIN, src, transcoder, error);
}


static void rygel_l16_transcoder_bin_decodebin_pad_added (RygelL16TranscoderBin* self, GstElement* decodebin, GstPad* new_pad) {
	GstPad* _tmp0_;
	GstPad* enc_pad;
	g_return_if_fail (self != NULL);
	g_return_if_fail (decodebin != NULL);
	g_return_if_fail (new_pad != NULL);
	_tmp0_ = NULL;
	enc_pad = (_tmp0_ = gst_element_get_pad (self->priv->audio_enc, RYGEL_L16_TRANSCODER_BIN_AUDIO_SINK_PAD), (_tmp0_ == NULL) ? NULL : gst_object_ref (_tmp0_));
	if (!gst_pad_can_link (new_pad, enc_pad)) {
		(enc_pad == NULL) ? NULL : (enc_pad = (gst_object_unref (enc_pad), NULL));
		return;
	}
	if (gst_pad_link (new_pad, enc_pad) != GST_PAD_LINK_OK) {
		GError* _tmp1_;
		_tmp1_ = NULL;
		rygel_gst_utils_post_error ((GstElement*) self, _tmp1_ = g_error_new (RYGEL_LIVE_RESPONSE_ERROR, RYGEL_LIVE_RESPONSE_ERROR_LINK, "Failed to link pad %s to %s", gst_object_get_name ((GstObject*) new_pad), gst_object_get_name ((GstObject*) enc_pad)));
		(_tmp1_ == NULL) ? NULL : (_tmp1_ = (g_error_free (_tmp1_), NULL));
		(enc_pad == NULL) ? NULL : (enc_pad = (gst_object_unref (enc_pad), NULL));
		return;
	}
	(enc_pad == NULL) ? NULL : (enc_pad = (gst_object_unref (enc_pad), NULL));
}


static void rygel_l16_transcoder_bin_class_init (RygelL16TranscoderBinClass * klass) {
	rygel_l16_transcoder_bin_parent_class = g_type_class_peek_parent (klass);
	g_type_class_add_private (klass, sizeof (RygelL16TranscoderBinPrivate));
	G_OBJECT_CLASS (klass)->finalize = rygel_l16_transcoder_bin_finalize;
}


static void rygel_l16_transcoder_bin_instance_init (RygelL16TranscoderBin * self) {
	self->priv = RYGEL_L16_TRANSCODER_BIN_GET_PRIVATE (self);
}


static void rygel_l16_transcoder_bin_finalize (GObject* obj) {
	RygelL16TranscoderBin * self;
	self = RYGEL_L16_TRANSCODER_BIN (obj);
	(self->priv->audio_enc == NULL) ? NULL : (self->priv->audio_enc = (gst_object_unref (self->priv->audio_enc), NULL));
	G_OBJECT_CLASS (rygel_l16_transcoder_bin_parent_class)->finalize (obj);
}


GType rygel_l16_transcoder_bin_get_type (void) {
	static GType rygel_l16_transcoder_bin_type_id = 0;
	if (rygel_l16_transcoder_bin_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (RygelL16TranscoderBinClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) rygel_l16_transcoder_bin_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (RygelL16TranscoderBin), 0, (GInstanceInitFunc) rygel_l16_transcoder_bin_instance_init, NULL };
		rygel_l16_transcoder_bin_type_id = g_type_register_static (GST_TYPE_BIN, "RygelL16TranscoderBin", &g_define_type_info, 0);
	}
	return rygel_l16_transcoder_bin_type_id;
}




