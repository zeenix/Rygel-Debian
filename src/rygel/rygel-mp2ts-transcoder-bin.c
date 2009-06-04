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


#define RYGEL_TYPE_MP2_TS_TRANSCODER_BIN (rygel_mp2_ts_transcoder_bin_get_type ())
#define RYGEL_MP2_TS_TRANSCODER_BIN(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_MP2_TS_TRANSCODER_BIN, RygelMP2TSTranscoderBin))
#define RYGEL_MP2_TS_TRANSCODER_BIN_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_MP2_TS_TRANSCODER_BIN, RygelMP2TSTranscoderBinClass))
#define RYGEL_IS_MP2_TS_TRANSCODER_BIN(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_MP2_TS_TRANSCODER_BIN))
#define RYGEL_IS_MP2_TS_TRANSCODER_BIN_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_MP2_TS_TRANSCODER_BIN))
#define RYGEL_MP2_TS_TRANSCODER_BIN_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_MP2_TS_TRANSCODER_BIN, RygelMP2TSTranscoderBinClass))

typedef struct _RygelMP2TSTranscoderBin RygelMP2TSTranscoderBin;
typedef struct _RygelMP2TSTranscoderBinClass RygelMP2TSTranscoderBinClass;
typedef struct _RygelMP2TSTranscoderBinPrivate RygelMP2TSTranscoderBinPrivate;

#define RYGEL_TYPE_MP3_LAYER (rygel_mp3_layer_get_type ())

#define RYGEL_TYPE_TRANSCODER (rygel_transcoder_get_type ())
#define RYGEL_TRANSCODER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_TRANSCODER, RygelTranscoder))
#define RYGEL_TRANSCODER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_TRANSCODER, RygelTranscoderClass))
#define RYGEL_IS_TRANSCODER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_TRANSCODER))
#define RYGEL_IS_TRANSCODER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_TRANSCODER))
#define RYGEL_TRANSCODER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_TRANSCODER, RygelTranscoderClass))

typedef struct _RygelTranscoder RygelTranscoder;
typedef struct _RygelTranscoderClass RygelTranscoderClass;

#define RYGEL_TYPE_MP3_TRANSCODER (rygel_mp3_transcoder_get_type ())
#define RYGEL_MP3_TRANSCODER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_MP3_TRANSCODER, RygelMP3Transcoder))
#define RYGEL_MP3_TRANSCODER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_MP3_TRANSCODER, RygelMP3TranscoderClass))
#define RYGEL_IS_MP3_TRANSCODER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_MP3_TRANSCODER))
#define RYGEL_IS_MP3_TRANSCODER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_MP3_TRANSCODER))
#define RYGEL_MP3_TRANSCODER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_MP3_TRANSCODER, RygelMP3TranscoderClass))

typedef struct _RygelMP3Transcoder RygelMP3Transcoder;
typedef struct _RygelMP3TranscoderClass RygelMP3TranscoderClass;

#define RYGEL_TYPE_MP2_TS_TRANSCODER (rygel_mp2_ts_transcoder_get_type ())
#define RYGEL_MP2_TS_TRANSCODER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_MP2_TS_TRANSCODER, RygelMP2TSTranscoder))
#define RYGEL_MP2_TS_TRANSCODER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_MP2_TS_TRANSCODER, RygelMP2TSTranscoderClass))
#define RYGEL_IS_MP2_TS_TRANSCODER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_MP2_TS_TRANSCODER))
#define RYGEL_IS_MP2_TS_TRANSCODER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_MP2_TS_TRANSCODER))
#define RYGEL_MP2_TS_TRANSCODER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_MP2_TS_TRANSCODER, RygelMP2TSTranscoderClass))

typedef struct _RygelMP2TSTranscoder RygelMP2TSTranscoder;
typedef struct _RygelMP2TSTranscoderClass RygelMP2TSTranscoderClass;

/**
 * A Gst.Bin derivative that implements transcoding of any type of media (using
 * decodebin2) to mpeg transport stream containing mpeg 2 video and mp2 audio.
 */
struct _RygelMP2TSTranscoderBin {
	GstBin parent_instance;
	RygelMP2TSTranscoderBinPrivate * priv;
};

struct _RygelMP2TSTranscoderBinClass {
	GstBinClass parent_class;
};

struct _RygelMP2TSTranscoderBinPrivate {
	GstElement* audio_enc;
	GstElement* video_enc;
	GstElement* muxer;
};

typedef enum  {
	RYGEL_MP3_LAYER_TWO = 1,
	RYGEL_MP3_LAYER_THREE = 2
} RygelMP3Layer;

typedef enum  {
	RYGEL_LIVE_RESPONSE_ERROR_MISSING_PLUGIN,
	RYGEL_LIVE_RESPONSE_ERROR_LINK
} RygelLiveResponseError;
#define RYGEL_LIVE_RESPONSE_ERROR rygel_live_response_error_quark ()


GType rygel_mp2_ts_transcoder_bin_get_type (void);
#define RYGEL_MP2_TS_TRANSCODER_BIN_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), RYGEL_TYPE_MP2_TS_TRANSCODER_BIN, RygelMP2TSTranscoderBinPrivate))
enum  {
	RYGEL_MP2_TS_TRANSCODER_BIN_DUMMY_PROPERTY
};
#define RYGEL_MP2_TS_TRANSCODER_BIN_DECODEBIN "decodebin2"
#define RYGEL_MP2_TS_TRANSCODER_BIN_MUXER "mpegtsmux"
#define RYGEL_MP2_TS_TRANSCODER_BIN_AUDIO_ENC_SINK "audio-enc-sink-pad"
#define RYGEL_MP2_TS_TRANSCODER_BIN_VIDEO_ENC_SINK "sink"
GstElement* rygel_gst_utils_create_element (const char* factoryname, const char* name, GError** error);
GType rygel_mp3_layer_get_type (void);
RygelMP3Transcoder* rygel_mp3_transcoder_new (RygelMP3Layer layer);
RygelMP3Transcoder* rygel_mp3_transcoder_construct (GType object_type, RygelMP3Layer layer);
GType rygel_transcoder_get_type (void);
GType rygel_mp3_transcoder_get_type (void);
GstElement* rygel_mp3_transcoder_create_encoder (RygelMP3Transcoder* self, const char* src_pad_name, const char* sink_pad_name, GError** error);
GType rygel_mp2_ts_transcoder_get_type (void);
GstElement* rygel_mp2_ts_transcoder_create_encoder (RygelMP2TSTranscoder* self, const char* src_pad_name, const char* sink_pad_name, GError** error);
static void rygel_mp2_ts_transcoder_bin_decodebin_pad_added (RygelMP2TSTranscoderBin* self, GstElement* decodebin, GstPad* new_pad);
static void _rygel_mp2_ts_transcoder_bin_decodebin_pad_added_gst_element_pad_added (GstElement* _sender, GstPad* pad, gpointer self);
RygelMP2TSTranscoderBin* rygel_mp2_ts_transcoder_bin_new (GstElement* src, RygelMP2TSTranscoder* transcoder, GError** error);
RygelMP2TSTranscoderBin* rygel_mp2_ts_transcoder_bin_construct (GType object_type, GstElement* src, RygelMP2TSTranscoder* transcoder, GError** error);
RygelMP2TSTranscoderBin* rygel_mp2_ts_transcoder_bin_new (GstElement* src, RygelMP2TSTranscoder* transcoder, GError** error);
void rygel_gst_utils_post_error (GstElement* dest, GError* _error_);
GQuark rygel_live_response_error_quark (void);
static gpointer rygel_mp2_ts_transcoder_bin_parent_class = NULL;
static void rygel_mp2_ts_transcoder_bin_finalize (GObject* obj);



static void _rygel_mp2_ts_transcoder_bin_decodebin_pad_added_gst_element_pad_added (GstElement* _sender, GstPad* pad, gpointer self) {
	rygel_mp2_ts_transcoder_bin_decodebin_pad_added (self, _sender, pad);
}


RygelMP2TSTranscoderBin* rygel_mp2_ts_transcoder_bin_construct (GType object_type, GstElement* src, RygelMP2TSTranscoder* transcoder, GError** error) {
	GError * _inner_error_;
	RygelMP2TSTranscoderBin * self;
	GstElement* decodebin;
	RygelMP3Transcoder* mp3_transcoder;
	GstElement* _tmp0_;
	GstElement* _tmp1_;
	GstElement* _tmp2_;
	GstElement* _tmp3_;
	GstElement* _tmp4_;
	GstElement* _tmp5_;
	GstElement* _tmp10_;
	GstElement* _tmp9_;
	GstElement* _tmp8_;
	GstElement* _tmp7_;
	GstElement* _tmp6_;
	GstPad* src_pad;
	GstGhostPad* ghost;
	GstPad* _tmp11_;
	g_return_val_if_fail (src != NULL, NULL);
	g_return_val_if_fail (transcoder != NULL, NULL);
	_inner_error_ = NULL;
	self = g_object_newv (object_type, 0, NULL);
	decodebin = rygel_gst_utils_create_element (RYGEL_MP2_TS_TRANSCODER_BIN_DECODEBIN, RYGEL_MP2_TS_TRANSCODER_BIN_DECODEBIN, &_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		return;
	}
	mp3_transcoder = rygel_mp3_transcoder_new (RYGEL_MP3_LAYER_TWO);
	_tmp0_ = rygel_mp3_transcoder_create_encoder (mp3_transcoder, NULL, RYGEL_MP2_TS_TRANSCODER_BIN_AUDIO_ENC_SINK, &_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		(decodebin == NULL) ? NULL : (decodebin = (gst_object_unref (decodebin), NULL));
		(mp3_transcoder == NULL) ? NULL : (mp3_transcoder = (g_object_unref (mp3_transcoder), NULL));
		return;
	}
	_tmp1_ = NULL;
	self->priv->audio_enc = (_tmp1_ = _tmp0_, (self->priv->audio_enc == NULL) ? NULL : (self->priv->audio_enc = (gst_object_unref (self->priv->audio_enc), NULL)), _tmp1_);
	_tmp2_ = rygel_mp2_ts_transcoder_create_encoder (transcoder, NULL, RYGEL_MP2_TS_TRANSCODER_BIN_VIDEO_ENC_SINK, &_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		(decodebin == NULL) ? NULL : (decodebin = (gst_object_unref (decodebin), NULL));
		(mp3_transcoder == NULL) ? NULL : (mp3_transcoder = (g_object_unref (mp3_transcoder), NULL));
		return;
	}
	_tmp3_ = NULL;
	self->priv->video_enc = (_tmp3_ = _tmp2_, (self->priv->video_enc == NULL) ? NULL : (self->priv->video_enc = (gst_object_unref (self->priv->video_enc), NULL)), _tmp3_);
	_tmp4_ = rygel_gst_utils_create_element (RYGEL_MP2_TS_TRANSCODER_BIN_MUXER, RYGEL_MP2_TS_TRANSCODER_BIN_MUXER, &_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		(decodebin == NULL) ? NULL : (decodebin = (gst_object_unref (decodebin), NULL));
		(mp3_transcoder == NULL) ? NULL : (mp3_transcoder = (g_object_unref (mp3_transcoder), NULL));
		return;
	}
	_tmp5_ = NULL;
	self->priv->muxer = (_tmp5_ = _tmp4_, (self->priv->muxer == NULL) ? NULL : (self->priv->muxer = (gst_object_unref (self->priv->muxer), NULL)), _tmp5_);
	_tmp10_ = NULL;
	_tmp9_ = NULL;
	_tmp8_ = NULL;
	_tmp7_ = NULL;
	_tmp6_ = NULL;
	gst_bin_add_many ((GstBin*) self, (_tmp6_ = src, (_tmp6_ == NULL) ? NULL : gst_object_ref (_tmp6_)), (_tmp7_ = decodebin, (_tmp7_ == NULL) ? NULL : gst_object_ref (_tmp7_)), (_tmp8_ = self->priv->audio_enc, (_tmp8_ == NULL) ? NULL : gst_object_ref (_tmp8_)), (_tmp9_ = self->priv->video_enc, (_tmp9_ == NULL) ? NULL : gst_object_ref (_tmp9_)), (_tmp10_ = self->priv->muxer, (_tmp10_ == NULL) ? NULL : gst_object_ref (_tmp10_)), NULL);
	gst_element_link (src, decodebin);
	src_pad = gst_element_get_static_pad (self->priv->muxer, "src");
	ghost = (GstGhostPad*) gst_ghost_pad_new (NULL, src_pad);
	_tmp11_ = NULL;
	gst_element_add_pad ((GstElement*) self, (_tmp11_ = (GstPad*) ghost, (_tmp11_ == NULL) ? NULL : gst_object_ref (_tmp11_)));
	g_signal_connect_object (decodebin, "pad-added", (GCallback) _rygel_mp2_ts_transcoder_bin_decodebin_pad_added_gst_element_pad_added, self, 0);
	(decodebin == NULL) ? NULL : (decodebin = (gst_object_unref (decodebin), NULL));
	(mp3_transcoder == NULL) ? NULL : (mp3_transcoder = (g_object_unref (mp3_transcoder), NULL));
	(src_pad == NULL) ? NULL : (src_pad = (gst_object_unref (src_pad), NULL));
	(ghost == NULL) ? NULL : (ghost = (gst_object_unref (ghost), NULL));
	return self;
}


RygelMP2TSTranscoderBin* rygel_mp2_ts_transcoder_bin_new (GstElement* src, RygelMP2TSTranscoder* transcoder, GError** error) {
	return rygel_mp2_ts_transcoder_bin_construct (RYGEL_TYPE_MP2_TS_TRANSCODER_BIN, src, transcoder, error);
}


static void rygel_mp2_ts_transcoder_bin_decodebin_pad_added (RygelMP2TSTranscoderBin* self, GstElement* decodebin, GstPad* new_pad) {
	GstElement* encoder;
	GstPad* enc_pad;
	GstPad* _tmp0_;
	GstPad* audio_enc_pad;
	GstPad* _tmp1_;
	GstPad* video_enc_pad;
	g_return_if_fail (self != NULL);
	g_return_if_fail (decodebin != NULL);
	g_return_if_fail (new_pad != NULL);
	encoder = NULL;
	enc_pad = NULL;
	_tmp0_ = NULL;
	audio_enc_pad = (_tmp0_ = gst_element_get_pad (self->priv->audio_enc, RYGEL_MP2_TS_TRANSCODER_BIN_AUDIO_ENC_SINK), (_tmp0_ == NULL) ? NULL : gst_object_ref (_tmp0_));
	_tmp1_ = NULL;
	video_enc_pad = (_tmp1_ = gst_element_get_pad (self->priv->video_enc, RYGEL_MP2_TS_TRANSCODER_BIN_VIDEO_ENC_SINK), (_tmp1_ == NULL) ? NULL : gst_object_ref (_tmp1_));
	/* Check which encoder to use*/
	if (gst_pad_can_link (new_pad, audio_enc_pad)) {
		GstElement* _tmp3_;
		GstElement* _tmp2_;
		GstPad* _tmp5_;
		GstPad* _tmp4_;
		_tmp3_ = NULL;
		_tmp2_ = NULL;
		encoder = (_tmp3_ = (_tmp2_ = self->priv->audio_enc, (_tmp2_ == NULL) ? NULL : gst_object_ref (_tmp2_)), (encoder == NULL) ? NULL : (encoder = (gst_object_unref (encoder), NULL)), _tmp3_);
		_tmp5_ = NULL;
		_tmp4_ = NULL;
		enc_pad = (_tmp5_ = (_tmp4_ = audio_enc_pad, (_tmp4_ == NULL) ? NULL : gst_object_ref (_tmp4_)), (enc_pad == NULL) ? NULL : (enc_pad = (gst_object_unref (enc_pad), NULL)), _tmp5_);
	} else {
		if (gst_pad_can_link (new_pad, video_enc_pad)) {
			GstElement* _tmp7_;
			GstElement* _tmp6_;
			GstPad* _tmp9_;
			GstPad* _tmp8_;
			_tmp7_ = NULL;
			_tmp6_ = NULL;
			encoder = (_tmp7_ = (_tmp6_ = self->priv->video_enc, (_tmp6_ == NULL) ? NULL : gst_object_ref (_tmp6_)), (encoder == NULL) ? NULL : (encoder = (gst_object_unref (encoder), NULL)), _tmp7_);
			_tmp9_ = NULL;
			_tmp8_ = NULL;
			enc_pad = (_tmp9_ = (_tmp8_ = video_enc_pad, (_tmp8_ == NULL) ? NULL : gst_object_ref (_tmp8_)), (enc_pad == NULL) ? NULL : (enc_pad = (gst_object_unref (enc_pad), NULL)), _tmp9_);
		} else {
			(encoder == NULL) ? NULL : (encoder = (gst_object_unref (encoder), NULL));
			(enc_pad == NULL) ? NULL : (enc_pad = (gst_object_unref (enc_pad), NULL));
			(audio_enc_pad == NULL) ? NULL : (audio_enc_pad = (gst_object_unref (audio_enc_pad), NULL));
			(video_enc_pad == NULL) ? NULL : (video_enc_pad = (gst_object_unref (video_enc_pad), NULL));
			return;
		}
	}
	gst_element_link (encoder, self->priv->muxer);
	if (gst_pad_link (new_pad, enc_pad) != GST_PAD_LINK_OK) {
		GError* _tmp10_;
		_tmp10_ = NULL;
		rygel_gst_utils_post_error ((GstElement*) self, _tmp10_ = g_error_new (RYGEL_LIVE_RESPONSE_ERROR, RYGEL_LIVE_RESPONSE_ERROR_LINK, "Failed to link pad %s to %s", gst_object_get_name ((GstObject*) new_pad), gst_object_get_name ((GstObject*) enc_pad)));
		(_tmp10_ == NULL) ? NULL : (_tmp10_ = (g_error_free (_tmp10_), NULL));
		(encoder == NULL) ? NULL : (encoder = (gst_object_unref (encoder), NULL));
		(enc_pad == NULL) ? NULL : (enc_pad = (gst_object_unref (enc_pad), NULL));
		(audio_enc_pad == NULL) ? NULL : (audio_enc_pad = (gst_object_unref (audio_enc_pad), NULL));
		(video_enc_pad == NULL) ? NULL : (video_enc_pad = (gst_object_unref (video_enc_pad), NULL));
		return;
	}
	(encoder == NULL) ? NULL : (encoder = (gst_object_unref (encoder), NULL));
	(enc_pad == NULL) ? NULL : (enc_pad = (gst_object_unref (enc_pad), NULL));
	(audio_enc_pad == NULL) ? NULL : (audio_enc_pad = (gst_object_unref (audio_enc_pad), NULL));
	(video_enc_pad == NULL) ? NULL : (video_enc_pad = (gst_object_unref (video_enc_pad), NULL));
}


static void rygel_mp2_ts_transcoder_bin_class_init (RygelMP2TSTranscoderBinClass * klass) {
	rygel_mp2_ts_transcoder_bin_parent_class = g_type_class_peek_parent (klass);
	g_type_class_add_private (klass, sizeof (RygelMP2TSTranscoderBinPrivate));
	G_OBJECT_CLASS (klass)->finalize = rygel_mp2_ts_transcoder_bin_finalize;
}


static void rygel_mp2_ts_transcoder_bin_instance_init (RygelMP2TSTranscoderBin * self) {
	self->priv = RYGEL_MP2_TS_TRANSCODER_BIN_GET_PRIVATE (self);
}


static void rygel_mp2_ts_transcoder_bin_finalize (GObject* obj) {
	RygelMP2TSTranscoderBin * self;
	self = RYGEL_MP2_TS_TRANSCODER_BIN (obj);
	(self->priv->audio_enc == NULL) ? NULL : (self->priv->audio_enc = (gst_object_unref (self->priv->audio_enc), NULL));
	(self->priv->video_enc == NULL) ? NULL : (self->priv->video_enc = (gst_object_unref (self->priv->video_enc), NULL));
	(self->priv->muxer == NULL) ? NULL : (self->priv->muxer = (gst_object_unref (self->priv->muxer), NULL));
	G_OBJECT_CLASS (rygel_mp2_ts_transcoder_bin_parent_class)->finalize (obj);
}


GType rygel_mp2_ts_transcoder_bin_get_type (void) {
	static GType rygel_mp2_ts_transcoder_bin_type_id = 0;
	if (rygel_mp2_ts_transcoder_bin_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (RygelMP2TSTranscoderBinClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) rygel_mp2_ts_transcoder_bin_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (RygelMP2TSTranscoderBin), 0, (GInstanceInitFunc) rygel_mp2_ts_transcoder_bin_instance_init, NULL };
		rygel_mp2_ts_transcoder_bin_type_id = g_type_register_static (GST_TYPE_BIN, "RygelMP2TSTranscoderBin", &g_define_type_info, 0);
	}
	return rygel_mp2_ts_transcoder_bin_type_id;
}




