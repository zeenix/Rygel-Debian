/*
 * Copyright (C) 2009 Nokia Corporation, all rights reserved.
 *
 * Author: Zeeshan Ali (Khattak) <zeeshanak@gnome.org>
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
#include <gio/gio.h>


#define RYGEL_TYPE_TRACKER_GET_METADATA_RESULT (rygel_tracker_get_metadata_result_get_type ())
#define RYGEL_TRACKER_GET_METADATA_RESULT(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_TRACKER_GET_METADATA_RESULT, RygelTrackerGetMetadataResult))
#define RYGEL_TRACKER_GET_METADATA_RESULT_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_TRACKER_GET_METADATA_RESULT, RygelTrackerGetMetadataResultClass))
#define RYGEL_IS_TRACKER_GET_METADATA_RESULT(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_TRACKER_GET_METADATA_RESULT))
#define RYGEL_IS_TRACKER_GET_METADATA_RESULT_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_TRACKER_GET_METADATA_RESULT))
#define RYGEL_TRACKER_GET_METADATA_RESULT_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_TRACKER_GET_METADATA_RESULT, RygelTrackerGetMetadataResultClass))

typedef struct _RygelTrackerGetMetadataResult RygelTrackerGetMetadataResult;
typedef struct _RygelTrackerGetMetadataResultClass RygelTrackerGetMetadataResultClass;
typedef struct _RygelTrackerGetMetadataResultPrivate RygelTrackerGetMetadataResultPrivate;

#define RYGEL_TYPE_TRACKER_CATEGORY (rygel_tracker_category_get_type ())
#define RYGEL_TRACKER_CATEGORY(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_TRACKER_CATEGORY, RygelTrackerCategory))
#define RYGEL_TRACKER_CATEGORY_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_TRACKER_CATEGORY, RygelTrackerCategoryClass))
#define RYGEL_IS_TRACKER_CATEGORY(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_TRACKER_CATEGORY))
#define RYGEL_IS_TRACKER_CATEGORY_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_TRACKER_CATEGORY))
#define RYGEL_TRACKER_CATEGORY_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_TRACKER_CATEGORY, RygelTrackerCategoryClass))

typedef struct _RygelTrackerCategory RygelTrackerCategory;
typedef struct _RygelTrackerCategoryClass RygelTrackerCategoryClass;

/**
 * Handles Tracker Metadata.Get method results.
 *
 */
struct _RygelTrackerGetMetadataResult {
	RygelSimpleAsyncResult parent_instance;
	RygelTrackerGetMetadataResultPrivate * priv;
	char* item_id;
};

struct _RygelTrackerGetMetadataResultClass {
	RygelSimpleAsyncResultClass parent_class;
};



GType rygel_tracker_get_metadata_result_get_type (void);
enum  {
	RYGEL_TRACKER_GET_METADATA_RESULT_DUMMY_PROPERTY
};
GType rygel_tracker_category_get_type (void);
RygelTrackerGetMetadataResult* rygel_tracker_get_metadata_result_new (RygelTrackerCategory* category, GAsyncReadyCallback callback, void* callback_target, const char* item_id);
RygelTrackerGetMetadataResult* rygel_tracker_get_metadata_result_construct (GType object_type, RygelTrackerCategory* category, GAsyncReadyCallback callback, void* callback_target, const char* item_id);
RygelTrackerGetMetadataResult* rygel_tracker_get_metadata_result_new (RygelTrackerCategory* category, GAsyncReadyCallback callback, void* callback_target, const char* item_id);
char* rygel_tracker_category_get_item_path (RygelTrackerCategory* self, const char* item_id);
RygelMediaItem* rygel_tracker_category_create_item (RygelTrackerCategory* self, const char* path, char** metadata, int metadata_length1);
void rygel_tracker_get_metadata_result_ready (RygelTrackerGetMetadataResult* self, char** metadata, int metadata_length1, GError* _error_);
static gpointer rygel_tracker_get_metadata_result_parent_class = NULL;
static void rygel_tracker_get_metadata_result_finalize (GObject* obj);



RygelTrackerGetMetadataResult* rygel_tracker_get_metadata_result_construct (GType object_type, RygelTrackerCategory* category, GAsyncReadyCallback callback, void* callback_target, const char* item_id) {
	RygelTrackerGetMetadataResult * self;
	char* _tmp1_;
	const char* _tmp0_;
	g_return_val_if_fail (category != NULL, NULL);
	g_return_val_if_fail (item_id != NULL, NULL);
	self = (RygelTrackerGetMetadataResult*) rygel_simple_async_result_construct (object_type, RYGEL_TYPE_MEDIA_OBJECT, (GBoxedCopyFunc) g_object_ref, g_object_unref, (GObject*) category, callback, callback_target);
	_tmp1_ = NULL;
	_tmp0_ = NULL;
	self->item_id = (_tmp1_ = (_tmp0_ = item_id, (_tmp0_ == NULL) ? NULL : g_strdup (_tmp0_)), self->item_id = (g_free (self->item_id), NULL), _tmp1_);
	return self;
}


RygelTrackerGetMetadataResult* rygel_tracker_get_metadata_result_new (RygelTrackerCategory* category, GAsyncReadyCallback callback, void* callback_target, const char* item_id) {
	return rygel_tracker_get_metadata_result_construct (RYGEL_TYPE_TRACKER_GET_METADATA_RESULT, category, callback, callback_target, item_id);
}


void rygel_tracker_get_metadata_result_ready (RygelTrackerGetMetadataResult* self, char** metadata, int metadata_length1, GError* _error_) {
	RygelTrackerCategory* _tmp2_;
	RygelTrackerCategory* category;
	char* path;
	RygelMediaObject* _tmp3_;
	g_return_if_fail (self != NULL);
	if (_error_ != NULL) {
		GError* _tmp1_;
		GError* _tmp0_;
		_tmp1_ = NULL;
		_tmp0_ = NULL;
		((RygelSimpleAsyncResult*) self)->error = (_tmp1_ = (_tmp0_ = _error_, (_tmp0_ == NULL) ? ((gpointer) _tmp0_) : g_error_copy (_tmp0_)), (((RygelSimpleAsyncResult*) self)->error == NULL) ? NULL : (((RygelSimpleAsyncResult*) self)->error = (g_error_free (((RygelSimpleAsyncResult*) self)->error), NULL)), _tmp1_);
		rygel_simple_async_result_complete ((RygelSimpleAsyncResult*) self);
		return;
	}
	_tmp2_ = NULL;
	category = (_tmp2_ = RYGEL_TRACKER_CATEGORY (((RygelSimpleAsyncResult*) self)->source_object), (_tmp2_ == NULL) ? NULL : g_object_ref (_tmp2_));
	path = rygel_tracker_category_get_item_path (category, self->item_id);
	_tmp3_ = NULL;
	((RygelSimpleAsyncResult*) self)->data = (_tmp3_ = (RygelMediaObject*) rygel_tracker_category_create_item (category, path, metadata, metadata_length1), (((RygelSimpleAsyncResult*) self)->data == NULL) ? NULL : (((RygelSimpleAsyncResult*) self)->data = (g_object_unref (((RygelSimpleAsyncResult*) self)->data), NULL)), _tmp3_);
	rygel_simple_async_result_complete ((RygelSimpleAsyncResult*) self);
	(category == NULL) ? NULL : (category = (g_object_unref (category), NULL));
	path = (g_free (path), NULL);
}


static void rygel_tracker_get_metadata_result_class_init (RygelTrackerGetMetadataResultClass * klass) {
	rygel_tracker_get_metadata_result_parent_class = g_type_class_peek_parent (klass);
	G_OBJECT_CLASS (klass)->finalize = rygel_tracker_get_metadata_result_finalize;
}


static void rygel_tracker_get_metadata_result_instance_init (RygelTrackerGetMetadataResult * self) {
}


static void rygel_tracker_get_metadata_result_finalize (GObject* obj) {
	RygelTrackerGetMetadataResult * self;
	self = RYGEL_TRACKER_GET_METADATA_RESULT (obj);
	self->item_id = (g_free (self->item_id), NULL);
	G_OBJECT_CLASS (rygel_tracker_get_metadata_result_parent_class)->finalize (obj);
}


GType rygel_tracker_get_metadata_result_get_type (void) {
	static GType rygel_tracker_get_metadata_result_type_id = 0;
	if (rygel_tracker_get_metadata_result_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (RygelTrackerGetMetadataResultClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) rygel_tracker_get_metadata_result_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (RygelTrackerGetMetadataResult), 0, (GInstanceInitFunc) rygel_tracker_get_metadata_result_instance_init, NULL };
		rygel_tracker_get_metadata_result_type_id = g_type_register_static (RYGEL_TYPE_SIMPLE_ASYNC_RESULT, "RygelTrackerGetMetadataResult", &g_define_type_info, 0);
	}
	return rygel_tracker_get_metadata_result_type_id;
}




