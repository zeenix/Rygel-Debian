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

#define RYGEL_TYPE_TEST_VIDEO_ITEM (rygel_test_video_item_get_type ())
#define RYGEL_TEST_VIDEO_ITEM(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_TEST_VIDEO_ITEM, RygelTestVideoItem))
#define RYGEL_TEST_VIDEO_ITEM_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_TEST_VIDEO_ITEM, RygelTestVideoItemClass))
#define RYGEL_IS_TEST_VIDEO_ITEM(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_TEST_VIDEO_ITEM))
#define RYGEL_IS_TEST_VIDEO_ITEM_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_TEST_VIDEO_ITEM))
#define RYGEL_TEST_VIDEO_ITEM_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_TEST_VIDEO_ITEM, RygelTestVideoItemClass))

typedef struct _RygelTestVideoItem RygelTestVideoItem;
typedef struct _RygelTestVideoItemClass RygelTestVideoItemClass;
typedef struct _RygelTestVideoItemPrivate RygelTestVideoItemPrivate;

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
 * Represents Test video item.
 */
struct _RygelTestVideoItem {
	RygelTestItem parent_instance;
	RygelTestVideoItemPrivate * priv;
};

struct _RygelTestVideoItemClass {
	RygelTestItemClass parent_class;
};



GType rygel_test_item_get_type (void);
GType rygel_test_video_item_get_type (void);
enum  {
	RYGEL_TEST_VIDEO_ITEM_DUMMY_PROPERTY
};
#define RYGEL_TEST_VIDEO_ITEM_TEST_MIMETYPE "video/mpeg"
RygelTestItem* rygel_test_item_new (const char* id, RygelMediaContainer* parent, const char* title, const char* mime, const char* upnp_class);
RygelTestItem* rygel_test_item_construct (GType object_type, const char* id, RygelMediaContainer* parent, const char* title, const char* mime, const char* upnp_class);
RygelTestVideoItem* rygel_test_video_item_new (const char* id, RygelMediaContainer* parent, const char* title);
RygelTestVideoItem* rygel_test_video_item_construct (GType object_type, const char* id, RygelMediaContainer* parent, const char* title);
RygelTestVideoItem* rygel_test_video_item_new (const char* id, RygelMediaContainer* parent, const char* title);
static inline void _dynamic_set_is_live1 (GstElement* obj, gboolean value);
static GstElement* rygel_test_video_item_real_create_stream_source (RygelMediaItem* base);
static gpointer rygel_test_video_item_parent_class = NULL;



RygelTestVideoItem* rygel_test_video_item_construct (GType object_type, const char* id, RygelMediaContainer* parent, const char* title) {
	RygelTestVideoItem * self;
	g_return_val_if_fail (id != NULL, NULL);
	g_return_val_if_fail (parent != NULL, NULL);
	g_return_val_if_fail (title != NULL, NULL);
	self = (RygelTestVideoItem*) rygel_test_item_construct (object_type, id, parent, title, RYGEL_TEST_VIDEO_ITEM_TEST_MIMETYPE, RYGEL_MEDIA_ITEM_VIDEO_CLASS);
	return self;
}


RygelTestVideoItem* rygel_test_video_item_new (const char* id, RygelMediaContainer* parent, const char* title) {
	return rygel_test_video_item_construct (RYGEL_TYPE_TEST_VIDEO_ITEM, id, parent, title);
}


static inline void _dynamic_set_is_live1 (GstElement* obj, gboolean value) {
	g_object_set (obj, "is-live", value, NULL);
}


static GstElement* rygel_test_video_item_real_create_stream_source (RygelMediaItem* base) {
	RygelTestVideoItem * self;
	GstBin* bin;
	GstElement* src;
	GstElement* encoder;
	GstElement* muxer;
	gboolean _tmp0_;
	gboolean _tmp1_;
	GstElement* _tmp5_;
	GstElement* _tmp4_;
	GstElement* _tmp3_;
	GstPad* pad;
	char* _tmp7_;
	char* _tmp6_;
	GstGhostPad* _tmp8_;
	GstGhostPad* ghost;
	GstPad* _tmp9_;
	GstElement* _tmp10_;
	self = (RygelTestVideoItem*) base;
	bin = (GstBin*) gst_bin_new (((RygelMediaObject*) self)->title);
	src = gst_element_factory_make ("videotestsrc", NULL);
	encoder = gst_element_factory_make ("ffenc_mpeg2video", NULL);
	muxer = gst_element_factory_make ("mpegtsmux", NULL);
	_tmp0_ = FALSE;
	_tmp1_ = FALSE;
	if (src == NULL) {
		_tmp1_ = TRUE;
	} else {
		_tmp1_ = muxer == NULL;
	}
	if (_tmp1_) {
		_tmp0_ = TRUE;
	} else {
		_tmp0_ = encoder == NULL;
	}
	if (_tmp0_) {
		GstElement* _tmp2_;
		g_warning ("rygel-test-video-item.vala:54: Required plugin missing");
		_tmp2_ = NULL;
		return (_tmp2_ = NULL, (bin == NULL) ? NULL : (bin = (gst_object_unref (bin), NULL)), (src == NULL) ? NULL : (src = (gst_object_unref (src), NULL)), (encoder == NULL) ? NULL : (encoder = (gst_object_unref (encoder), NULL)), (muxer == NULL) ? NULL : (muxer = (gst_object_unref (muxer), NULL)), _tmp2_);
	}
	/* Tell the source to behave like a live source*/
	_dynamic_set_is_live1 (src, TRUE);
	/* Add elements to our source bin*/
	_tmp5_ = NULL;
	_tmp4_ = NULL;
	_tmp3_ = NULL;
	gst_bin_add_many (bin, (_tmp3_ = src, (_tmp3_ == NULL) ? NULL : gst_object_ref (_tmp3_)), (_tmp4_ = encoder, (_tmp4_ == NULL) ? NULL : gst_object_ref (_tmp4_)), (_tmp5_ = muxer, (_tmp5_ == NULL) ? NULL : gst_object_ref (_tmp5_)), NULL);
	/* Link them*/
	gst_element_link_many (src, encoder, muxer, NULL);
	/* Now add the encoder's src pad to the bin*/
	pad = gst_element_get_static_pad (muxer, "src");
	_tmp7_ = NULL;
	_tmp6_ = NULL;
	_tmp8_ = NULL;
	ghost = (_tmp8_ = (GstGhostPad*) gst_ghost_pad_new (_tmp7_ = g_strconcat (_tmp6_ = g_strconcat (gst_object_get_name ((GstObject*) bin), ".", NULL), gst_object_get_name ((GstObject*) pad), NULL), pad), _tmp7_ = (g_free (_tmp7_), NULL), _tmp6_ = (g_free (_tmp6_), NULL), _tmp8_);
	_tmp9_ = NULL;
	gst_element_add_pad ((GstElement*) bin, (_tmp9_ = (GstPad*) ghost, (_tmp9_ == NULL) ? NULL : gst_object_ref (_tmp9_)));
	_tmp10_ = NULL;
	return (_tmp10_ = (GstElement*) bin, (src == NULL) ? NULL : (src = (gst_object_unref (src), NULL)), (encoder == NULL) ? NULL : (encoder = (gst_object_unref (encoder), NULL)), (muxer == NULL) ? NULL : (muxer = (gst_object_unref (muxer), NULL)), (pad == NULL) ? NULL : (pad = (gst_object_unref (pad), NULL)), (ghost == NULL) ? NULL : (ghost = (gst_object_unref (ghost), NULL)), _tmp10_);
}


static void rygel_test_video_item_class_init (RygelTestVideoItemClass * klass) {
	rygel_test_video_item_parent_class = g_type_class_peek_parent (klass);
	RYGEL_MEDIA_ITEM_CLASS (klass)->create_stream_source = rygel_test_video_item_real_create_stream_source;
}


static void rygel_test_video_item_instance_init (RygelTestVideoItem * self) {
}


GType rygel_test_video_item_get_type (void) {
	static GType rygel_test_video_item_type_id = 0;
	if (rygel_test_video_item_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (RygelTestVideoItemClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) rygel_test_video_item_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (RygelTestVideoItem), 0, (GInstanceInitFunc) rygel_test_video_item_instance_init, NULL };
		rygel_test_video_item_type_id = g_type_register_static (RYGEL_TYPE_TEST_ITEM, "RygelTestVideoItem", &g_define_type_info, 0);
	}
	return rygel_test_video_item_type_id;
}




