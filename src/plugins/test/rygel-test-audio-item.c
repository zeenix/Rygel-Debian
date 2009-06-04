/*
 * Copyright (C) 2008 Zeeshan Ali (Khattak) <zeeshanak@gnome.org>.
 * Copyright (C) 2008 Nokia Corporation, all rights reserved.
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
#include <rygel.h>
#include <stdlib.h>
#include <string.h>
#include <gst/gst.h>


#define RYGEL_TYPE_TEST_ITEM (rygel_test_item_get_type ())
#define RYGEL_TEST_ITEM(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_TEST_ITEM, RygelTestItem))
#define RYGEL_TEST_ITEM_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_TEST_ITEM, RygelTestItemClass))
#define RYGEL_IS_TEST_ITEM(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_TEST_ITEM))
#define RYGEL_IS_TEST_ITEM_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_TEST_ITEM))
#define RYGEL_TEST_ITEM_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_TEST_ITEM, RygelTestItemClass))

typedef struct _RygelTestItem RygelTestItem;
typedef struct _RygelTestItemClass RygelTestItemClass;
typedef struct _RygelTestItemPrivate RygelTestItemPrivate;

#define RYGEL_TYPE_TEST_AUDIO_ITEM (rygel_test_audio_item_get_type ())
#define RYGEL_TEST_AUDIO_ITEM(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_TEST_AUDIO_ITEM, RygelTestAudioItem))
#define RYGEL_TEST_AUDIO_ITEM_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_TEST_AUDIO_ITEM, RygelTestAudioItemClass))
#define RYGEL_IS_TEST_AUDIO_ITEM(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_TEST_AUDIO_ITEM))
#define RYGEL_IS_TEST_AUDIO_ITEM_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_TEST_AUDIO_ITEM))
#define RYGEL_TEST_AUDIO_ITEM_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_TEST_AUDIO_ITEM, RygelTestAudioItemClass))

typedef struct _RygelTestAudioItem RygelTestAudioItem;
typedef struct _RygelTestAudioItemClass RygelTestAudioItemClass;
typedef struct _RygelTestAudioItemPrivate RygelTestAudioItemPrivate;

/**
 * Represents Test item.
 */
struct _RygelTestItem {
	RygelMediaItem parent_instance;
	RygelTestItemPrivate * priv;
};

struct _RygelTestItemClass {
	RygelMediaItemClass parent_class;
};

/**
 * Represents Test audio item.
 */
struct _RygelTestAudioItem {
	RygelTestItem parent_instance;
	RygelTestAudioItemPrivate * priv;
};

struct _RygelTestAudioItemClass {
	RygelTestItemClass parent_class;
};



GType rygel_test_item_get_type (void);
GType rygel_test_audio_item_get_type (void);
enum  {
	RYGEL_TEST_AUDIO_ITEM_DUMMY_PROPERTY
};
#define RYGEL_TEST_AUDIO_ITEM_TEST_MIMETYPE "audio/x-wav"
RygelTestItem* rygel_test_item_new (const char* id, RygelMediaContainer* parent, const char* title, const char* mime, const char* upnp_class);
RygelTestItem* rygel_test_item_construct (GType object_type, const char* id, RygelMediaContainer* parent, const char* title, const char* mime, const char* upnp_class);
RygelTestAudioItem* rygel_test_audio_item_new (const char* id, RygelMediaContainer* parent, const char* title);
RygelTestAudioItem* rygel_test_audio_item_construct (GType object_type, const char* id, RygelMediaContainer* parent, const char* title);
RygelTestAudioItem* rygel_test_audio_item_new (const char* id, RygelMediaContainer* parent, const char* title);
static inline void _dynamic_set_is_live0 (GstElement* obj, gboolean value);
static GstElement* rygel_test_audio_item_real_create_stream_source (RygelMediaItem* base);
static gpointer rygel_test_audio_item_parent_class = NULL;



RygelTestAudioItem* rygel_test_audio_item_construct (GType object_type, const char* id, RygelMediaContainer* parent, const char* title) {
	RygelTestAudioItem * self;
	g_return_val_if_fail (id != NULL, NULL);
	g_return_val_if_fail (parent != NULL, NULL);
	g_return_val_if_fail (title != NULL, NULL);
	self = (RygelTestAudioItem*) rygel_test_item_construct (object_type, id, parent, title, RYGEL_TEST_AUDIO_ITEM_TEST_MIMETYPE, RYGEL_MEDIA_ITEM_AUDIO_CLASS);
	return self;
}


RygelTestAudioItem* rygel_test_audio_item_new (const char* id, RygelMediaContainer* parent, const char* title) {
	return rygel_test_audio_item_construct (RYGEL_TYPE_TEST_AUDIO_ITEM, id, parent, title);
}


static inline void _dynamic_set_is_live0 (GstElement* obj, gboolean value) {
	g_object_set (obj, "is-live", value, NULL);
}


static GstElement* rygel_test_audio_item_real_create_stream_source (RygelMediaItem* base) {
	RygelTestAudioItem * self;
	GstBin* bin;
	GstElement* src;
	GstElement* encoder;
	gboolean _tmp0_;
	GstElement* _tmp3_;
	GstElement* _tmp2_;
	GstPad* pad;
	char* _tmp5_;
	char* _tmp4_;
	GstGhostPad* _tmp6_;
	GstGhostPad* ghost;
	GstPad* _tmp7_;
	GstElement* _tmp8_;
	self = (RygelTestAudioItem*) base;
	bin = (GstBin*) gst_bin_new (((RygelMediaObject*) self)->title);
	src = gst_element_factory_make ("audiotestsrc", NULL);
	encoder = gst_element_factory_make ("wavenc", NULL);
	_tmp0_ = FALSE;
	if (src == NULL) {
		_tmp0_ = TRUE;
	} else {
		_tmp0_ = encoder == NULL;
	}
	if (_tmp0_) {
		GstElement* _tmp1_;
		g_warning ("rygel-test-audio-item.vala:53: Required plugin missing");
		_tmp1_ = NULL;
		return (_tmp1_ = NULL, (bin == NULL) ? NULL : (bin = (gst_object_unref (bin), NULL)), (src == NULL) ? NULL : (src = (gst_object_unref (src), NULL)), (encoder == NULL) ? NULL : (encoder = (gst_object_unref (encoder), NULL)), _tmp1_);
	}
	/* Tell the source to behave like a live source*/
	_dynamic_set_is_live0 (src, TRUE);
	/* Add elements to our source bin*/
	_tmp3_ = NULL;
	_tmp2_ = NULL;
	gst_bin_add_many (bin, (_tmp2_ = src, (_tmp2_ == NULL) ? NULL : gst_object_ref (_tmp2_)), (_tmp3_ = encoder, (_tmp3_ == NULL) ? NULL : gst_object_ref (_tmp3_)), NULL);
	/* Link them*/
	gst_element_link (src, encoder);
	/* Now add the encoder's src pad to the bin*/
	pad = gst_element_get_static_pad (encoder, "src");
	_tmp5_ = NULL;
	_tmp4_ = NULL;
	_tmp6_ = NULL;
	ghost = (_tmp6_ = (GstGhostPad*) gst_ghost_pad_new (_tmp5_ = g_strconcat (_tmp4_ = g_strconcat (gst_object_get_name ((GstObject*) bin), ".", NULL), gst_object_get_name ((GstObject*) pad), NULL), pad), _tmp5_ = (g_free (_tmp5_), NULL), _tmp4_ = (g_free (_tmp4_), NULL), _tmp6_);
	_tmp7_ = NULL;
	gst_element_add_pad ((GstElement*) bin, (_tmp7_ = (GstPad*) ghost, (_tmp7_ == NULL) ? NULL : gst_object_ref (_tmp7_)));
	_tmp8_ = NULL;
	return (_tmp8_ = (GstElement*) bin, (src == NULL) ? NULL : (src = (gst_object_unref (src), NULL)), (encoder == NULL) ? NULL : (encoder = (gst_object_unref (encoder), NULL)), (pad == NULL) ? NULL : (pad = (gst_object_unref (pad), NULL)), (ghost == NULL) ? NULL : (ghost = (gst_object_unref (ghost), NULL)), _tmp8_);
}


static void rygel_test_audio_item_class_init (RygelTestAudioItemClass * klass) {
	rygel_test_audio_item_parent_class = g_type_class_peek_parent (klass);
	RYGEL_MEDIA_ITEM_CLASS (klass)->create_stream_source = rygel_test_audio_item_real_create_stream_source;
}


static void rygel_test_audio_item_instance_init (RygelTestAudioItem * self) {
}


GType rygel_test_audio_item_get_type (void) {
	static GType rygel_test_audio_item_type_id = 0;
	if (rygel_test_audio_item_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (RygelTestAudioItemClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) rygel_test_audio_item_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (RygelTestAudioItem), 0, (GInstanceInitFunc) rygel_test_audio_item_instance_init, NULL };
		rygel_test_audio_item_type_id = g_type_register_static (RYGEL_TYPE_TEST_ITEM, "RygelTestAudioItem", &g_define_type_info, 0);
	}
	return rygel_test_audio_item_type_id;
}




