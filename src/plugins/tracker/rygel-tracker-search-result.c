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
#include <gee/arraylist.h>
#include <gio/gio.h>
#include <stdlib.h>
#include <string.h>
#include <gee/collection.h>


#define RYGEL_TYPE_TRACKER_SEARCH_RESULT (rygel_tracker_search_result_get_type ())
#define RYGEL_TRACKER_SEARCH_RESULT(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_TRACKER_SEARCH_RESULT, RygelTrackerSearchResult))
#define RYGEL_TRACKER_SEARCH_RESULT_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_TRACKER_SEARCH_RESULT, RygelTrackerSearchResultClass))
#define RYGEL_IS_TRACKER_SEARCH_RESULT(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_TRACKER_SEARCH_RESULT))
#define RYGEL_IS_TRACKER_SEARCH_RESULT_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_TRACKER_SEARCH_RESULT))
#define RYGEL_TRACKER_SEARCH_RESULT_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_TRACKER_SEARCH_RESULT, RygelTrackerSearchResultClass))

typedef struct _RygelTrackerSearchResult RygelTrackerSearchResult;
typedef struct _RygelTrackerSearchResultClass RygelTrackerSearchResultClass;
typedef struct _RygelTrackerSearchResultPrivate RygelTrackerSearchResultPrivate;

#define RYGEL_TYPE_TRACKER_CATEGORY (rygel_tracker_category_get_type ())
#define RYGEL_TRACKER_CATEGORY(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_TRACKER_CATEGORY, RygelTrackerCategory))
#define RYGEL_TRACKER_CATEGORY_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_TRACKER_CATEGORY, RygelTrackerCategoryClass))
#define RYGEL_IS_TRACKER_CATEGORY(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_TRACKER_CATEGORY))
#define RYGEL_IS_TRACKER_CATEGORY_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_TRACKER_CATEGORY))
#define RYGEL_TRACKER_CATEGORY_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_TRACKER_CATEGORY, RygelTrackerCategoryClass))

typedef struct _RygelTrackerCategory RygelTrackerCategory;
typedef struct _RygelTrackerCategoryClass RygelTrackerCategoryClass;

/**
 * Handles Tracker Search.Query method results.
 *
 */
struct _RygelTrackerSearchResult {
	RygelSimpleAsyncResult parent_instance;
	RygelTrackerSearchResultPrivate * priv;
};

struct _RygelTrackerSearchResultClass {
	RygelSimpleAsyncResultClass parent_class;
};



GType rygel_tracker_search_result_get_type (void);
enum  {
	RYGEL_TRACKER_SEARCH_RESULT_DUMMY_PROPERTY
};
GType rygel_tracker_category_get_type (void);
RygelTrackerSearchResult* rygel_tracker_search_result_new (RygelTrackerCategory* category, GAsyncReadyCallback callback, void* callback_target);
RygelTrackerSearchResult* rygel_tracker_search_result_construct (GType object_type, RygelTrackerCategory* category, GAsyncReadyCallback callback, void* callback_target);
RygelTrackerSearchResult* rygel_tracker_search_result_new (RygelTrackerCategory* category, GAsyncReadyCallback callback, void* callback_target);
static char** rygel_tracker_search_result_slice_strv_tail (RygelTrackerSearchResult* self, char** strv, int strv_length1, gint index, int* result_length1);
RygelMediaItem* rygel_tracker_category_create_item (RygelTrackerCategory* self, const char* path, char** metadata, int metadata_length1);
void rygel_tracker_search_result_ready (RygelTrackerSearchResult* self, char*** search_result, int search_result_length1, GError* _error_);
static gint rygel_tracker_search_result_get_strv_length (RygelTrackerSearchResult* self, char** strv, int strv_length1);
static gpointer rygel_tracker_search_result_parent_class = NULL;
static void _vala_array_destroy (gpointer array, gint array_length, GDestroyNotify destroy_func);
static void _vala_array_free (gpointer array, gint array_length, GDestroyNotify destroy_func);



RygelTrackerSearchResult* rygel_tracker_search_result_construct (GType object_type, RygelTrackerCategory* category, GAsyncReadyCallback callback, void* callback_target) {
	RygelTrackerSearchResult * self;
	GeeList* _tmp0_;
	g_return_val_if_fail (category != NULL, NULL);
	self = (RygelTrackerSearchResult*) rygel_simple_async_result_construct (object_type, GEE_TYPE_LIST, (GBoxedCopyFunc) g_object_ref, g_object_unref, (GObject*) category, callback, callback_target);
	_tmp0_ = NULL;
	((RygelSimpleAsyncResult*) self)->data = (_tmp0_ = (GeeList*) gee_array_list_new (RYGEL_TYPE_MEDIA_OBJECT, (GBoxedCopyFunc) g_object_ref, g_object_unref, g_direct_equal), (((RygelSimpleAsyncResult*) self)->data == NULL) ? NULL : (((RygelSimpleAsyncResult*) self)->data = (g_object_unref (((RygelSimpleAsyncResult*) self)->data), NULL)), _tmp0_);
	return self;
}


RygelTrackerSearchResult* rygel_tracker_search_result_new (RygelTrackerCategory* category, GAsyncReadyCallback callback, void* callback_target) {
	return rygel_tracker_search_result_construct (RYGEL_TYPE_TRACKER_SEARCH_RESULT, category, callback, callback_target);
}


void rygel_tracker_search_result_ready (RygelTrackerSearchResult* self, char*** search_result, int search_result_length1, GError* _error_) {
	RygelTrackerCategory* _tmp2_;
	RygelTrackerCategory* category;
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
	{
		guint i;
		/* Iterate through all items */
		i = (guint) 0;
		for (; i < search_result_length1; i++) {
			const char* _tmp3_;
			char* child_path;
			char** _tmp5_;
			gint metadata_size;
			gint metadata_length1;
			gint _tmp4_;
			char** metadata;
			RygelMediaItem* item;
			_tmp3_ = NULL;
			child_path = (_tmp3_ = search_result[i][0], (_tmp3_ == NULL) ? NULL : g_strdup (_tmp3_));
			_tmp5_ = NULL;
			metadata = (_tmp5_ = rygel_tracker_search_result_slice_strv_tail (self, search_result[i], -1, 2, &_tmp4_), metadata_length1 = _tmp4_, metadata_size = metadata_length1, _tmp5_);
			item = rygel_tracker_category_create_item (category, child_path, metadata, metadata_length1);
			gee_collection_add ((GeeCollection*) ((GeeList*) ((RygelSimpleAsyncResult*) self)->data), (RygelMediaObject*) item);
			child_path = (g_free (child_path), NULL);
			metadata = (_vala_array_free (metadata, metadata_length1, (GDestroyNotify) g_free), NULL);
			(item == NULL) ? NULL : (item = (g_object_unref (item), NULL));
		}
	}
	rygel_simple_async_result_complete ((RygelSimpleAsyncResult*) self);
	(category == NULL) ? NULL : (category = (g_object_unref (category), NULL));
}


/**
     * Chops the tail of a string array.
     *
     * param strv the string to chop the tail of.
     * param index index of the first element in the tail.
     *
     * FIXME: Stop using it once vala supports array[N:M] syntax.
     */
static char** rygel_tracker_search_result_slice_strv_tail (RygelTrackerSearchResult* self, char** strv, int strv_length1, gint index, int* result_length1) {
	gint strv_length;
	char** _tmp1_;
	gint slice_size;
	gint slice_length1;
	gint _tmp0_;
	char** slice;
	char** _tmp4_;
	g_return_val_if_fail (self != NULL, NULL);
	strv_length = rygel_tracker_search_result_get_strv_length (self, strv, strv_length1);
	_tmp1_ = NULL;
	slice = (_tmp1_ = g_new0 (char*, (_tmp0_ = strv_length - index) + 1), slice_length1 = _tmp0_, slice_size = slice_length1, _tmp1_);
	{
		gint i;
		i = 0;
		for (; i < slice_length1; i++) {
			char* _tmp3_;
			const char* _tmp2_;
			_tmp3_ = NULL;
			_tmp2_ = NULL;
			slice[i] = (_tmp3_ = (_tmp2_ = strv[i + index], (_tmp2_ == NULL) ? NULL : g_strdup (_tmp2_)), slice[i] = (g_free (slice[i]), NULL), _tmp3_);
		}
	}
	_tmp4_ = NULL;
	return (_tmp4_ = slice, *result_length1 = slice_length1, _tmp4_);
}


/**
     * Gets the length of a null-terminated string array
     *
     * param strv the string to compute length of
     *
     * FIXME: Temporary hack, don't use once bug#571322 is fixed
     */
static gint rygel_tracker_search_result_get_strv_length (RygelTrackerSearchResult* self, char** strv, int strv_length1) {
	gint i;
	g_return_val_if_fail (self != NULL, 0);
	i = 0;
	for (i = 0; strv[i] != NULL; i++) {
		;
	}
	return i + 1;
}


static void rygel_tracker_search_result_class_init (RygelTrackerSearchResultClass * klass) {
	rygel_tracker_search_result_parent_class = g_type_class_peek_parent (klass);
}


static void rygel_tracker_search_result_instance_init (RygelTrackerSearchResult * self) {
}


GType rygel_tracker_search_result_get_type (void) {
	static GType rygel_tracker_search_result_type_id = 0;
	if (rygel_tracker_search_result_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (RygelTrackerSearchResultClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) rygel_tracker_search_result_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (RygelTrackerSearchResult), 0, (GInstanceInitFunc) rygel_tracker_search_result_instance_init, NULL };
		rygel_tracker_search_result_type_id = g_type_register_static (RYGEL_TYPE_SIMPLE_ASYNC_RESULT, "RygelTrackerSearchResult", &g_define_type_info, 0);
	}
	return rygel_tracker_search_result_type_id;
}


static void _vala_array_destroy (gpointer array, gint array_length, GDestroyNotify destroy_func) {
	if ((array != NULL) && (destroy_func != NULL)) {
		int i;
		for (i = 0; i < array_length; i = i + 1) {
			if (((gpointer*) array)[i] != NULL) {
				destroy_func (((gpointer*) array)[i]);
			}
		}
	}
}


static void _vala_array_free (gpointer array, gint array_length, GDestroyNotify destroy_func) {
	_vala_array_destroy (array, array_length, destroy_func);
	g_free (array);
}




