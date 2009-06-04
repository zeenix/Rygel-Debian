/*
 * Copyright (C) 2008 Zeeshan Ali <zeenix@gmail.com>.
 * Copyright (C) 2008 Nokia Corporation, all rights reserved.
 *
 * Author: Zeeshan Ali <zeenix@gmail.com>
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
#include <dbus/dbus-glib-lowlevel.h>
#include <dbus/dbus-glib.h>
#include <gee/list.h>
#include <gio/gio.h>
#include <gee/arraylist.h>
#include <gee/collection.h>


#define RYGEL_TYPE_TRACKER_CATEGORY (rygel_tracker_category_get_type ())
#define RYGEL_TRACKER_CATEGORY(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_TRACKER_CATEGORY, RygelTrackerCategory))
#define RYGEL_TRACKER_CATEGORY_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_TRACKER_CATEGORY, RygelTrackerCategoryClass))
#define RYGEL_IS_TRACKER_CATEGORY(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_TRACKER_CATEGORY))
#define RYGEL_IS_TRACKER_CATEGORY_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_TRACKER_CATEGORY))
#define RYGEL_TRACKER_CATEGORY_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_TRACKER_CATEGORY, RygelTrackerCategoryClass))

typedef struct _RygelTrackerCategory RygelTrackerCategory;
typedef struct _RygelTrackerCategoryClass RygelTrackerCategoryClass;
typedef struct _RygelTrackerCategoryPrivate RygelTrackerCategoryPrivate;

#define RYGEL_TYPE_TRACKER_SEARCH_RESULT (rygel_tracker_search_result_get_type ())
#define RYGEL_TRACKER_SEARCH_RESULT(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_TRACKER_SEARCH_RESULT, RygelTrackerSearchResult))
#define RYGEL_TRACKER_SEARCH_RESULT_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_TRACKER_SEARCH_RESULT, RygelTrackerSearchResultClass))
#define RYGEL_IS_TRACKER_SEARCH_RESULT(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_TRACKER_SEARCH_RESULT))
#define RYGEL_IS_TRACKER_SEARCH_RESULT_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_TRACKER_SEARCH_RESULT))
#define RYGEL_TRACKER_SEARCH_RESULT_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_TRACKER_SEARCH_RESULT, RygelTrackerSearchResultClass))

typedef struct _RygelTrackerSearchResult RygelTrackerSearchResult;
typedef struct _RygelTrackerSearchResultClass RygelTrackerSearchResultClass;

#define RYGEL_TYPE_TRACKER_GET_METADATA_RESULT (rygel_tracker_get_metadata_result_get_type ())
#define RYGEL_TRACKER_GET_METADATA_RESULT(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_TRACKER_GET_METADATA_RESULT, RygelTrackerGetMetadataResult))
#define RYGEL_TRACKER_GET_METADATA_RESULT_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_TRACKER_GET_METADATA_RESULT, RygelTrackerGetMetadataResultClass))
#define RYGEL_IS_TRACKER_GET_METADATA_RESULT(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_TRACKER_GET_METADATA_RESULT))
#define RYGEL_IS_TRACKER_GET_METADATA_RESULT_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_TRACKER_GET_METADATA_RESULT))
#define RYGEL_TRACKER_GET_METADATA_RESULT_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_TRACKER_GET_METADATA_RESULT, RygelTrackerGetMetadataResultClass))

typedef struct _RygelTrackerGetMetadataResult RygelTrackerGetMetadataResult;
typedef struct _RygelTrackerGetMetadataResultClass RygelTrackerGetMetadataResultClass;

/**
 * Represents Tracker category.
 */
struct _RygelTrackerCategory {
	RygelMediaContainer parent_instance;
	RygelTrackerCategoryPrivate * priv;
	DBusGProxy* metadata;
	DBusGProxy* search;
	DBusGProxy* tracker;
	char* category;
	char* child_class;
};

struct _RygelTrackerCategoryClass {
	RygelMediaContainerClass parent_class;
	char** (*get_metadata_keys) (RygelTrackerCategory* self, int* result_length1);
	RygelMediaItem* (*create_item) (RygelTrackerCategory* self, const char* path, char** metadata, int metadata_length1);
};

struct _RygelTrackerCategoryPrivate {
	GeeList* results;
};



GType rygel_tracker_category_get_type (void);
#define RYGEL_TRACKER_CATEGORY_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), RYGEL_TYPE_TRACKER_CATEGORY, RygelTrackerCategoryPrivate))
enum  {
	RYGEL_TRACKER_CATEGORY_DUMMY_PROPERTY
};
#define RYGEL_TRACKER_CATEGORY_TRACKER_SERVICE "org.freedesktop.Tracker"
#define RYGEL_TRACKER_CATEGORY_TRACKER_PATH "/org/freedesktop/Tracker"
#define RYGEL_TRACKER_CATEGORY_TRACKER_IFACE "org.freedesktop.Tracker"
#define RYGEL_TRACKER_CATEGORY_SEARCH_PATH "/org/freedesktop/Tracker/Search"
#define RYGEL_TRACKER_CATEGORY_SEARCH_IFACE "org.freedesktop.Tracker.Search"
#define RYGEL_TRACKER_CATEGORY_METADATA_PATH "/org/freedesktop/Tracker/Metadata"
#define RYGEL_TRACKER_CATEGORY_METADATA_IFACE "org.freedesktop.Tracker.Metadata"
static void rygel_tracker_category_create_proxies (RygelTrackerCategory* self, GError** error);
static void rygel_tracker_category_get_children_count (RygelTrackerCategory* self);
RygelTrackerCategory* rygel_tracker_category_new (const char* id, RygelMediaContainer* parent, const char* title, const char* category, const char* child_class);
RygelTrackerCategory* rygel_tracker_category_construct (GType object_type, const char* id, RygelMediaContainer* parent, const char* title, const char* category, const char* child_class);
RygelTrackerCategory* rygel_tracker_category_new (const char* id, RygelMediaContainer* parent, const char* title, const char* category, const char* child_class);
static void rygel_tracker_category_on_search_query_cb (RygelTrackerCategory* self, char*** search_result, int search_result_length1, GError* _error_);
void _dynamic_Query0 (DBusGProxy* self, gint param1, const char* param2, char** param3, int param3_length1, const char* param4, char** param5, int param5_length1, const char* param6, gboolean param7, char** param8, int param8_length1, gboolean param9, gint param10, gint param11, gpointer param12, void* param12_target, GError** error);
RygelTrackerSearchResult* rygel_tracker_search_result_new (RygelTrackerCategory* category, GAsyncReadyCallback callback, void* callback_target);
RygelTrackerSearchResult* rygel_tracker_search_result_construct (GType object_type, RygelTrackerCategory* category, GAsyncReadyCallback callback, void* callback_target);
GType rygel_tracker_search_result_get_type (void);
char** rygel_tracker_category_get_metadata_keys (RygelTrackerCategory* self, int* result_length1);
void rygel_tracker_search_result_ready (RygelTrackerSearchResult* self, char*** search_result, int search_result_length1, GError* _error_);
void _dynamic_Query1 (DBusGProxy* self, gint param1, const char* param2, char** param3, int param3_length1, const char* param4, char** param5, int param5_length1, const char* param6, gboolean param7, char** param8, int param8_length1, gboolean param9, gint param10, gint param11, gpointer param12, void* param12_target, GError** error);
static void rygel_tracker_category_real_get_children (RygelMediaContainer* base, guint offset, guint max_count, GCancellable* cancellable, GAsyncReadyCallback callback, void* callback_target);
static GeeList* rygel_tracker_category_real_get_children_finish (RygelMediaContainer* base, GAsyncResult* res, GError** error);
RygelTrackerGetMetadataResult* rygel_tracker_get_metadata_result_new (RygelTrackerCategory* category, GAsyncReadyCallback callback, void* callback_target, const char* item_id);
RygelTrackerGetMetadataResult* rygel_tracker_get_metadata_result_construct (GType object_type, RygelTrackerCategory* category, GAsyncReadyCallback callback, void* callback_target, const char* item_id);
GType rygel_tracker_get_metadata_result_get_type (void);
char* rygel_tracker_category_get_item_path (RygelTrackerCategory* self, const char* item_id);
void rygel_tracker_get_metadata_result_ready (RygelTrackerGetMetadataResult* self, char** metadata, int metadata_length1, GError* _error_);
void _dynamic_Get2 (DBusGProxy* self, const char* param1, const char* param2, char** param3, int param3_length1, gpointer param4, void* param4_target, GError** error);
static void rygel_tracker_category_real_find_object (RygelMediaContainer* base, const char* id, GCancellable* cancellable, GAsyncReadyCallback callback, void* callback_target);
static RygelMediaObject* rygel_tracker_category_real_find_object_finish (RygelMediaContainer* base, GAsyncResult* res, GError** error);
static char* rygel_tracker_category_get_item_parent_id (RygelTrackerCategory* self, const char* item_id);
gboolean rygel_tracker_category_is_thy_child (RygelTrackerCategory* self, const char* item_id);
static char** rygel_tracker_category_real_get_metadata_keys (RygelTrackerCategory* self, int* result_length1);
RygelMediaItem* rygel_tracker_category_create_item (RygelTrackerCategory* self, const char* path, char** metadata, int metadata_length1);
static RygelMediaItem* rygel_tracker_category_real_create_item (RygelTrackerCategory* self, const char* path, char** metadata, int metadata_length1);
static gpointer rygel_tracker_category_parent_class = NULL;
static void rygel_tracker_category_finalize (GObject* obj);
static void _vala_array_destroy (gpointer array, gint array_length, GDestroyNotify destroy_func);
static void _vala_array_free (gpointer array, gint array_length, GDestroyNotify destroy_func);
static gint _vala_array_length (gpointer array);
static int _vala_strcmp0 (const char * str1, const char * str2);



RygelTrackerCategory* rygel_tracker_category_construct (GType object_type, const char* id, RygelMediaContainer* parent, const char* title, const char* category, const char* child_class) {
	GError * _inner_error_;
	RygelTrackerCategory * self;
	char* _tmp1_;
	const char* _tmp0_;
	char* _tmp3_;
	const char* _tmp2_;
	g_return_val_if_fail (id != NULL, NULL);
	g_return_val_if_fail (parent != NULL, NULL);
	g_return_val_if_fail (title != NULL, NULL);
	g_return_val_if_fail (category != NULL, NULL);
	g_return_val_if_fail (child_class != NULL, NULL);
	_inner_error_ = NULL;
	self = (RygelTrackerCategory*) rygel_media_container_construct (object_type, id, parent, title, (guint) 0);
	_tmp1_ = NULL;
	_tmp0_ = NULL;
	self->category = (_tmp1_ = (_tmp0_ = category, (_tmp0_ == NULL) ? NULL : g_strdup (_tmp0_)), self->category = (g_free (self->category), NULL), _tmp1_);
	_tmp3_ = NULL;
	_tmp2_ = NULL;
	self->child_class = (_tmp3_ = (_tmp2_ = child_class, (_tmp2_ == NULL) ? NULL : g_strdup (_tmp2_)), self->child_class = (g_free (self->child_class), NULL), _tmp3_);
	{
		GeeList* _tmp4_;
		rygel_tracker_category_create_proxies (self, &_inner_error_);
		if (_inner_error_ != NULL) {
			if (_inner_error_->domain == DBUS_GERROR) {
				goto __catch0_dbus_gerror;
			}
			goto __finally0;
		}
		/* FIXME: We need to hook to some tracker signals to keep
		             *        this field up2date at all times
		             */
		rygel_tracker_category_get_children_count (self);
		_tmp4_ = NULL;
		self->priv->results = (_tmp4_ = (GeeList*) gee_array_list_new (G_TYPE_ASYNC_RESULT, (GBoxedCopyFunc) g_object_ref, g_object_unref, g_direct_equal), (self->priv->results == NULL) ? NULL : (self->priv->results = (g_object_unref (self->priv->results), NULL)), _tmp4_);
	}
	goto __finally0;
	__catch0_dbus_gerror:
	{
		GError * _error_;
		_error_ = _inner_error_;
		_inner_error_ = NULL;
		{
			g_critical ("rygel-tracker-category.vala:73: Failed to create to Session bus: %s\n", _error_->message);
			(_error_ == NULL) ? NULL : (_error_ = (g_error_free (_error_), NULL));
		}
	}
	__finally0:
	if (_inner_error_ != NULL) {
		g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, _inner_error_->message);
		g_clear_error (&_inner_error_);
		return NULL;
	}
	return self;
}


RygelTrackerCategory* rygel_tracker_category_new (const char* id, RygelMediaContainer* parent, const char* title, const char* category, const char* child_class) {
	return rygel_tracker_category_construct (RYGEL_TYPE_TRACKER_CATEGORY, id, parent, title, category, child_class);
}


static void _rygel_tracker_category_on_search_query_cb_cb (DBusGProxy* proxy, DBusGProxyCall* call, void* user_data) {
	GError* error;
	GPtrArray* search_result;
	error = NULL;
	dbus_g_proxy_end_call (proxy, call, &error, dbus_g_type_get_collection ("GPtrArray", G_TYPE_STRV), &search_result, G_TYPE_INVALID);
	rygel_tracker_category_on_search_query_cb (user_data, search_result->pdata, search_result->len, error);
}


void _dynamic_Query0 (DBusGProxy* self, gint param1, const char* param2, char** param3, int param3_length1, const char* param4, char** param5, int param5_length1, const char* param6, gboolean param7, char** param8, int param8_length1, gboolean param9, gint param10, gint param11, gpointer param12, void* param12_target, GError** error) {
	dbus_g_proxy_begin_call (self, "Query", _rygel_tracker_category_on_search_query_cb_cb, param12_target, NULL, G_TYPE_INT, param1, G_TYPE_STRING, param2, G_TYPE_STRV, param3, G_TYPE_STRING, param4, G_TYPE_STRV, param5, G_TYPE_STRING, param6, G_TYPE_BOOLEAN, param7, G_TYPE_STRV, param8, G_TYPE_BOOLEAN, param9, G_TYPE_INT, param10, G_TYPE_INT, param11, G_TYPE_INVALID, G_TYPE_INVALID);
	if (*error) {
		return;
	}
}


static void rygel_tracker_category_get_children_count (RygelTrackerCategory* self) {
	GError * _inner_error_;
	g_return_if_fail (self != NULL);
	_inner_error_ = NULL;
	{
		gint _tmp2__length1;
		char** _tmp2_;
		gint _tmp1__length1;
		char** _tmp1_;
		gint _tmp0__length1;
		char** _tmp0_;
		/* We are performing actual search (though an optimized one) to get
		 the hitcount rather than GetHitCount because GetHitCount only
		 allows us to get hit count for Text searches.*/
		_tmp2_ = NULL;
		_tmp1_ = NULL;
		_tmp0_ = NULL;
		_dynamic_Query0 (self->search, 0, self->category, (_tmp0_ = g_new0 (char*, 0 + 1), _tmp0__length1 = 0, _tmp0_), 0, "", (_tmp1_ = g_new0 (char*, 0 + 1), _tmp1__length1 = 0, _tmp1_), 0, "", FALSE, (_tmp2_ = g_new0 (char*, 0 + 1), _tmp2__length1 = 0, _tmp2_), 0, FALSE, 0, -1, rygel_tracker_category_on_search_query_cb, self, &_inner_error_);
		if (_inner_error_ != NULL) {
			goto __catch1_g_error;
			goto __finally1;
		}
		_tmp2_ = (_vala_array_free (_tmp2_, _tmp2__length1, (GDestroyNotify) g_free), NULL);
		_tmp1_ = (_vala_array_free (_tmp1_, _tmp1__length1, (GDestroyNotify) g_free), NULL);
		_tmp0_ = (_vala_array_free (_tmp0_, _tmp0__length1, (GDestroyNotify) g_free), NULL);
	}
	goto __finally1;
	__catch1_g_error:
	{
		GError * _error_;
		_error_ = _inner_error_;
		_inner_error_ = NULL;
		{
			g_critical ("rygel-tracker-category.vala:96: error getting items under category '%s': %s", self->category, _error_->message);
			(_error_ == NULL) ? NULL : (_error_ = (g_error_free (_error_), NULL));
			return;
		}
	}
	__finally1:
	if (_inner_error_ != NULL) {
		g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, _inner_error_->message);
		g_clear_error (&_inner_error_);
		return;
	}
}


static void rygel_tracker_category_on_search_query_cb (RygelTrackerCategory* self, char*** search_result, int search_result_length1, GError* _error_) {
	g_return_if_fail (self != NULL);
	if (_error_ != NULL) {
		g_critical ("rygel-tracker-category.vala:107: error getting items under category '%s': %s", self->category, _error_->message);
		return;
	}
	((RygelMediaContainer*) self)->child_count = (guint) search_result_length1;
	rygel_media_container_updated ((RygelMediaContainer*) self);
}


static void _rygel_tracker_search_result_ready_cb (DBusGProxy* proxy, DBusGProxyCall* call, void* user_data) {
	GError* error;
	GPtrArray* search_result;
	error = NULL;
	dbus_g_proxy_end_call (proxy, call, &error, dbus_g_type_get_collection ("GPtrArray", G_TYPE_STRV), &search_result, G_TYPE_INVALID);
	rygel_tracker_search_result_ready (user_data, search_result->pdata, search_result->len, error);
}


void _dynamic_Query1 (DBusGProxy* self, gint param1, const char* param2, char** param3, int param3_length1, const char* param4, char** param5, int param5_length1, const char* param6, gboolean param7, char** param8, int param8_length1, gboolean param9, gint param10, gint param11, gpointer param12, void* param12_target, GError** error) {
	dbus_g_proxy_begin_call (self, "Query", _rygel_tracker_search_result_ready_cb, param12_target, NULL, G_TYPE_INT, param1, G_TYPE_STRING, param2, G_TYPE_STRV, param3, G_TYPE_STRING, param4, G_TYPE_STRV, param5, G_TYPE_STRING, param6, G_TYPE_BOOLEAN, param7, G_TYPE_STRV, param8, G_TYPE_BOOLEAN, param9, G_TYPE_INT, param10, G_TYPE_INT, param11, G_TYPE_INVALID, G_TYPE_INVALID);
	if (*error) {
		return;
	}
}


static void rygel_tracker_category_real_get_children (RygelMediaContainer* base, guint offset, guint max_count, GCancellable* cancellable, GAsyncReadyCallback callback, void* callback_target) {
	RygelTrackerCategory * self;
	GError * _inner_error_;
	RygelTrackerSearchResult* res;
	self = (RygelTrackerCategory*) base;
	_inner_error_ = NULL;
	res = rygel_tracker_search_result_new (self, callback, callback_target);
	gee_collection_add ((GeeCollection*) self->priv->results, (GAsyncResult*) res);
	{
		char** _tmp4_;
		gint _tmp3__length1;
		char** _tmp3_;
		gint _tmp2__length1;
		char** _tmp2_;
		gint _tmp1__length1;
		char** _tmp1_;
		gint _tmp0_;
		_tmp4_ = NULL;
		_tmp3_ = NULL;
		_tmp2_ = NULL;
		_tmp1_ = NULL;
		_tmp4_ = (_tmp1_ = rygel_tracker_category_get_metadata_keys (self, &_tmp0_), _tmp1__length1 = _tmp0_, _tmp1_);
		_dynamic_Query1 (self->search, 0, self->category, _tmp4_, _tmp0_, "", (_tmp2_ = g_new0 (char*, 0 + 1), _tmp2__length1 = 0, _tmp2_), 0, "", FALSE, (_tmp3_ = g_new0 (char*, 0 + 1), _tmp3__length1 = 0, _tmp3_), 0, FALSE, (gint) offset, (gint) max_count, rygel_tracker_search_result_ready, res, &_inner_error_);
		if (_inner_error_ != NULL) {
			goto __catch2_g_error;
			goto __finally2;
		}
		_tmp3_ = (_vala_array_free (_tmp3_, _tmp3__length1, (GDestroyNotify) g_free), NULL);
		_tmp2_ = (_vala_array_free (_tmp2_, _tmp2__length1, (GDestroyNotify) g_free), NULL);
		_tmp1_ = (_vala_array_free (_tmp1_, _tmp1__length1, (GDestroyNotify) g_free), NULL);
	}
	goto __finally2;
	__catch2_g_error:
	{
		GError * _error_;
		_error_ = _inner_error_;
		_inner_error_ = NULL;
		{
			GError* _tmp6_;
			GError* _tmp5_;
			_tmp6_ = NULL;
			_tmp5_ = NULL;
			((RygelSimpleAsyncResult*) res)->error = (_tmp6_ = (_tmp5_ = _error_, (_tmp5_ == NULL) ? ((gpointer) _tmp5_) : g_error_copy (_tmp5_)), (((RygelSimpleAsyncResult*) res)->error == NULL) ? NULL : (((RygelSimpleAsyncResult*) res)->error = (g_error_free (((RygelSimpleAsyncResult*) res)->error), NULL)), _tmp6_);
			rygel_simple_async_result_complete_in_idle ((RygelSimpleAsyncResult*) res);
			(_error_ == NULL) ? NULL : (_error_ = (g_error_free (_error_), NULL));
		}
	}
	__finally2:
	if (_inner_error_ != NULL) {
		(res == NULL) ? NULL : (res = (g_object_unref (res), NULL));
		g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, _inner_error_->message);
		g_clear_error (&_inner_error_);
		return;
	}
	(res == NULL) ? NULL : (res = (g_object_unref (res), NULL));
}


static GeeList* rygel_tracker_category_real_get_children_finish (RygelMediaContainer* base, GAsyncResult* res, GError** error) {
	RygelTrackerCategory * self;
	GError * _inner_error_;
	RygelTrackerSearchResult* _tmp0_;
	RygelTrackerSearchResult* search_res;
	self = (RygelTrackerCategory*) base;
	g_return_val_if_fail (res != NULL, NULL);
	_inner_error_ = NULL;
	_tmp0_ = NULL;
	search_res = (_tmp0_ = RYGEL_TRACKER_SEARCH_RESULT (res), (_tmp0_ == NULL) ? NULL : g_object_ref (_tmp0_));
	gee_collection_remove ((GeeCollection*) self->priv->results, (GAsyncResult*) search_res);
	if (((RygelSimpleAsyncResult*) search_res)->error != NULL) {
		GError* _tmp1_;
		_tmp1_ = NULL;
		_inner_error_ = (_tmp1_ = ((RygelSimpleAsyncResult*) search_res)->error, (_tmp1_ == NULL) ? ((gpointer) _tmp1_) : g_error_copy (_tmp1_));
		if (_inner_error_ != NULL) {
			g_propagate_error (error, _inner_error_);
			(search_res == NULL) ? NULL : (search_res = (g_object_unref (search_res), NULL));
			return NULL;
		}
	} else {
		GeeList* _tmp2_;
		GeeList* _tmp3_;
		_tmp2_ = NULL;
		_tmp3_ = NULL;
		return (_tmp3_ = (_tmp2_ = (GeeList*) ((RygelSimpleAsyncResult*) search_res)->data, (_tmp2_ == NULL) ? NULL : g_object_ref (_tmp2_)), (search_res == NULL) ? NULL : (search_res = (g_object_unref (search_res), NULL)), _tmp3_);
	}
	(search_res == NULL) ? NULL : (search_res = (g_object_unref (search_res), NULL));
}


static void _rygel_tracker_get_metadata_result_ready_cb (DBusGProxy* proxy, DBusGProxyCall* call, void* user_data) {
	GError* error;
	char** metadata;
	error = NULL;
	dbus_g_proxy_end_call (proxy, call, &error, G_TYPE_STRV, &metadata, G_TYPE_INVALID);
	rygel_tracker_get_metadata_result_ready (user_data, metadata, g_strv_length (metadata), error);
}


void _dynamic_Get2 (DBusGProxy* self, const char* param1, const char* param2, char** param3, int param3_length1, gpointer param4, void* param4_target, GError** error) {
	dbus_g_proxy_begin_call (self, "Get", _rygel_tracker_get_metadata_result_ready_cb, param4_target, NULL, G_TYPE_STRING, param1, G_TYPE_STRING, param2, G_TYPE_STRV, param3, G_TYPE_INVALID, G_TYPE_INVALID);
	if (*error) {
		return;
	}
}


static void rygel_tracker_category_real_find_object (RygelMediaContainer* base, const char* id, GCancellable* cancellable, GAsyncReadyCallback callback, void* callback_target) {
	RygelTrackerCategory * self;
	GError * _inner_error_;
	RygelTrackerGetMetadataResult* res;
	self = (RygelTrackerCategory*) base;
	g_return_if_fail (id != NULL);
	_inner_error_ = NULL;
	res = rygel_tracker_get_metadata_result_new (self, callback, callback_target, id);
	gee_collection_add ((GeeCollection*) self->priv->results, (GAsyncResult*) res);
	{
		char* path;
		char** _tmp1_;
		gint keys_size;
		gint keys_length1;
		gint _tmp0_;
		char** keys;
		path = rygel_tracker_category_get_item_path (self, id);
		if (path == NULL) {
			_inner_error_ = g_error_new_literal (RYGEL_CONTENT_DIRECTORY_ERROR, RYGEL_CONTENT_DIRECTORY_ERROR_NO_SUCH_OBJECT, "No such object");
			if (_inner_error_ != NULL) {
				path = (g_free (path), NULL);
				goto __catch3_g_error;
				goto __finally3;
			}
		}
		_tmp1_ = NULL;
		keys = (_tmp1_ = rygel_tracker_category_get_metadata_keys (self, &_tmp0_), keys_length1 = _tmp0_, keys_size = keys_length1, _tmp1_);
		_dynamic_Get2 (self->metadata, self->category, path, keys, keys_length1, rygel_tracker_get_metadata_result_ready, res, &_inner_error_);
		if (_inner_error_ != NULL) {
			path = (g_free (path), NULL);
			keys = (_vala_array_free (keys, keys_length1, (GDestroyNotify) g_free), NULL);
			goto __catch3_g_error;
			goto __finally3;
		}
		path = (g_free (path), NULL);
		keys = (_vala_array_free (keys, keys_length1, (GDestroyNotify) g_free), NULL);
	}
	goto __finally3;
	__catch3_g_error:
	{
		GError * _error_;
		_error_ = _inner_error_;
		_inner_error_ = NULL;
		{
			GError* _tmp3_;
			GError* _tmp2_;
			_tmp3_ = NULL;
			_tmp2_ = NULL;
			((RygelSimpleAsyncResult*) res)->error = (_tmp3_ = (_tmp2_ = _error_, (_tmp2_ == NULL) ? ((gpointer) _tmp2_) : g_error_copy (_tmp2_)), (((RygelSimpleAsyncResult*) res)->error == NULL) ? NULL : (((RygelSimpleAsyncResult*) res)->error = (g_error_free (((RygelSimpleAsyncResult*) res)->error), NULL)), _tmp3_);
			rygel_simple_async_result_complete_in_idle ((RygelSimpleAsyncResult*) res);
			(_error_ == NULL) ? NULL : (_error_ = (g_error_free (_error_), NULL));
		}
	}
	__finally3:
	if (_inner_error_ != NULL) {
		(res == NULL) ? NULL : (res = (g_object_unref (res), NULL));
		g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, _inner_error_->message);
		g_clear_error (&_inner_error_);
		return;
	}
	(res == NULL) ? NULL : (res = (g_object_unref (res), NULL));
}


static RygelMediaObject* rygel_tracker_category_real_find_object_finish (RygelMediaContainer* base, GAsyncResult* res, GError** error) {
	RygelTrackerCategory * self;
	GError * _inner_error_;
	RygelTrackerGetMetadataResult* _tmp0_;
	RygelTrackerGetMetadataResult* metadata_res;
	self = (RygelTrackerCategory*) base;
	g_return_val_if_fail (res != NULL, NULL);
	_inner_error_ = NULL;
	_tmp0_ = NULL;
	metadata_res = (_tmp0_ = RYGEL_TRACKER_GET_METADATA_RESULT (res), (_tmp0_ == NULL) ? NULL : g_object_ref (_tmp0_));
	if (((RygelSimpleAsyncResult*) metadata_res)->error != NULL) {
		GError* _tmp1_;
		_tmp1_ = NULL;
		_inner_error_ = (_tmp1_ = ((RygelSimpleAsyncResult*) metadata_res)->error, (_tmp1_ == NULL) ? ((gpointer) _tmp1_) : g_error_copy (_tmp1_));
		if (_inner_error_ != NULL) {
			g_propagate_error (error, _inner_error_);
			(metadata_res == NULL) ? NULL : (metadata_res = (g_object_unref (metadata_res), NULL));
			return NULL;
		}
	} else {
		RygelMediaObject* _tmp2_;
		RygelMediaObject* _tmp3_;
		_tmp2_ = NULL;
		_tmp3_ = NULL;
		return (_tmp3_ = (_tmp2_ = (RygelMediaObject*) ((RygelSimpleAsyncResult*) metadata_res)->data, (_tmp2_ == NULL) ? NULL : g_object_ref (_tmp2_)), (metadata_res == NULL) ? NULL : (metadata_res = (g_object_unref (metadata_res), NULL)), _tmp3_);
	}
	(metadata_res == NULL) ? NULL : (metadata_res = (g_object_unref (metadata_res), NULL));
}


gboolean rygel_tracker_category_is_thy_child (RygelTrackerCategory* self, const char* item_id) {
	char* parent_id;
	gboolean _tmp0_;
	g_return_val_if_fail (self != NULL, FALSE);
	g_return_val_if_fail (item_id != NULL, FALSE);
	parent_id = rygel_tracker_category_get_item_parent_id (self, item_id);
	_tmp0_ = FALSE;
	if (parent_id != NULL) {
		_tmp0_ = _vala_strcmp0 (parent_id, ((RygelMediaObject*) self)->id) == 0;
	} else {
		_tmp0_ = FALSE;
	}
	if (_tmp0_) {
		gboolean _tmp1_;
		return (_tmp1_ = TRUE, parent_id = (g_free (parent_id), NULL), _tmp1_);
	} else {
		gboolean _tmp2_;
		return (_tmp2_ = FALSE, parent_id = (g_free (parent_id), NULL), _tmp2_);
	}
	parent_id = (g_free (parent_id), NULL);
}


char* rygel_tracker_category_get_item_path (RygelTrackerCategory* self, const char* item_id) {
	char** _tmp1_;
	gint tokens_size;
	gint tokens_length1;
	char** _tmp0_;
	char** tokens;
	gboolean _tmp2_;
	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (item_id != NULL, NULL);
	_tmp1_ = NULL;
	_tmp0_ = NULL;
	tokens = (_tmp1_ = _tmp0_ = g_strsplit (item_id, ":", 2), tokens_length1 = _vala_array_length (_tmp0_), tokens_size = tokens_length1, _tmp1_);
	_tmp2_ = FALSE;
	if (tokens[0] != NULL) {
		_tmp2_ = tokens[1] != NULL;
	} else {
		_tmp2_ = FALSE;
	}
	if (_tmp2_) {
		const char* _tmp3_;
		char* _tmp4_;
		_tmp3_ = NULL;
		_tmp4_ = NULL;
		return (_tmp4_ = (_tmp3_ = tokens[1], (_tmp3_ == NULL) ? NULL : g_strdup (_tmp3_)), tokens = (_vala_array_free (tokens, tokens_length1, (GDestroyNotify) g_free), NULL), _tmp4_);
	} else {
		char* _tmp5_;
		_tmp5_ = NULL;
		return (_tmp5_ = NULL, tokens = (_vala_array_free (tokens, tokens_length1, (GDestroyNotify) g_free), NULL), _tmp5_);
	}
	tokens = (_vala_array_free (tokens, tokens_length1, (GDestroyNotify) g_free), NULL);
}


static void rygel_tracker_category_create_proxies (RygelTrackerCategory* self, GError** error) {
	GError * _inner_error_;
	DBusGConnection* connection;
	DBusGProxy* _tmp0_;
	DBusGProxy* _tmp1_;
	DBusGProxy* _tmp2_;
	g_return_if_fail (self != NULL);
	_inner_error_ = NULL;
	connection = dbus_g_bus_get (DBUS_BUS_SESSION, &_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		return;
	}
	_tmp0_ = NULL;
	self->metadata = (_tmp0_ = dbus_g_proxy_new_for_name (connection, RYGEL_TRACKER_CATEGORY_TRACKER_SERVICE, RYGEL_TRACKER_CATEGORY_METADATA_PATH, RYGEL_TRACKER_CATEGORY_METADATA_IFACE), (self->metadata == NULL) ? NULL : (self->metadata = (g_object_unref (self->metadata), NULL)), _tmp0_);
	_tmp1_ = NULL;
	self->search = (_tmp1_ = dbus_g_proxy_new_for_name (connection, RYGEL_TRACKER_CATEGORY_TRACKER_SERVICE, RYGEL_TRACKER_CATEGORY_SEARCH_PATH, RYGEL_TRACKER_CATEGORY_SEARCH_IFACE), (self->search == NULL) ? NULL : (self->search = (g_object_unref (self->search), NULL)), _tmp1_);
	_tmp2_ = NULL;
	self->tracker = (_tmp2_ = dbus_g_proxy_new_for_name (connection, RYGEL_TRACKER_CATEGORY_TRACKER_SERVICE, RYGEL_TRACKER_CATEGORY_TRACKER_PATH, RYGEL_TRACKER_CATEGORY_TRACKER_IFACE), (self->tracker == NULL) ? NULL : (self->tracker = (g_object_unref (self->tracker), NULL)), _tmp2_);
	(connection == NULL) ? NULL : (connection = (dbus_g_connection_unref (connection), NULL));
}


static char* rygel_tracker_category_get_item_parent_id (RygelTrackerCategory* self, const char* item_id) {
	char** _tmp1_;
	gint tokens_size;
	gint tokens_length1;
	char** _tmp0_;
	char** tokens;
	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (item_id != NULL, NULL);
	_tmp1_ = NULL;
	_tmp0_ = NULL;
	tokens = (_tmp1_ = _tmp0_ = g_strsplit (item_id, ":", 2), tokens_length1 = _vala_array_length (_tmp0_), tokens_size = tokens_length1, _tmp1_);
	if (tokens[0] != NULL) {
		const char* _tmp2_;
		char* _tmp3_;
		_tmp2_ = NULL;
		_tmp3_ = NULL;
		return (_tmp3_ = (_tmp2_ = tokens[0], (_tmp2_ == NULL) ? NULL : g_strdup (_tmp2_)), tokens = (_vala_array_free (tokens, tokens_length1, (GDestroyNotify) g_free), NULL), _tmp3_);
	} else {
		char* _tmp4_;
		_tmp4_ = NULL;
		return (_tmp4_ = NULL, tokens = (_vala_array_free (tokens, tokens_length1, (GDestroyNotify) g_free), NULL), _tmp4_);
	}
	tokens = (_vala_array_free (tokens, tokens_length1, (GDestroyNotify) g_free), NULL);
}


static char** rygel_tracker_category_real_get_metadata_keys (RygelTrackerCategory* self, int* result_length1) {
	g_return_val_if_fail (self != NULL, NULL);
	g_critical ("Type `%s' does not implement abstract method `rygel_tracker_category_get_metadata_keys'", g_type_name (G_TYPE_FROM_INSTANCE (self)));
	return NULL;
}


char** rygel_tracker_category_get_metadata_keys (RygelTrackerCategory* self, int* result_length1) {
	return RYGEL_TRACKER_CATEGORY_GET_CLASS (self)->get_metadata_keys (self, result_length1);
}


static RygelMediaItem* rygel_tracker_category_real_create_item (RygelTrackerCategory* self, const char* path, char** metadata, int metadata_length1) {
	g_return_val_if_fail (self != NULL, NULL);
	g_critical ("Type `%s' does not implement abstract method `rygel_tracker_category_create_item'", g_type_name (G_TYPE_FROM_INSTANCE (self)));
	return NULL;
}


RygelMediaItem* rygel_tracker_category_create_item (RygelTrackerCategory* self, const char* path, char** metadata, int metadata_length1) {
	return RYGEL_TRACKER_CATEGORY_GET_CLASS (self)->create_item (self, path, metadata, metadata_length1);
}


static void rygel_tracker_category_class_init (RygelTrackerCategoryClass * klass) {
	rygel_tracker_category_parent_class = g_type_class_peek_parent (klass);
	g_type_class_add_private (klass, sizeof (RygelTrackerCategoryPrivate));
	RYGEL_MEDIA_CONTAINER_CLASS (klass)->get_children = rygel_tracker_category_real_get_children;
	RYGEL_MEDIA_CONTAINER_CLASS (klass)->get_children_finish = rygel_tracker_category_real_get_children_finish;
	RYGEL_MEDIA_CONTAINER_CLASS (klass)->find_object = rygel_tracker_category_real_find_object;
	RYGEL_MEDIA_CONTAINER_CLASS (klass)->find_object_finish = rygel_tracker_category_real_find_object_finish;
	RYGEL_TRACKER_CATEGORY_CLASS (klass)->get_metadata_keys = rygel_tracker_category_real_get_metadata_keys;
	RYGEL_TRACKER_CATEGORY_CLASS (klass)->create_item = rygel_tracker_category_real_create_item;
	G_OBJECT_CLASS (klass)->finalize = rygel_tracker_category_finalize;
}


static void rygel_tracker_category_instance_init (RygelTrackerCategory * self) {
	self->priv = RYGEL_TRACKER_CATEGORY_GET_PRIVATE (self);
}


static void rygel_tracker_category_finalize (GObject* obj) {
	RygelTrackerCategory * self;
	self = RYGEL_TRACKER_CATEGORY (obj);
	(self->metadata == NULL) ? NULL : (self->metadata = (g_object_unref (self->metadata), NULL));
	(self->search == NULL) ? NULL : (self->search = (g_object_unref (self->search), NULL));
	(self->tracker == NULL) ? NULL : (self->tracker = (g_object_unref (self->tracker), NULL));
	self->category = (g_free (self->category), NULL);
	self->child_class = (g_free (self->child_class), NULL);
	(self->priv->results == NULL) ? NULL : (self->priv->results = (g_object_unref (self->priv->results), NULL));
	G_OBJECT_CLASS (rygel_tracker_category_parent_class)->finalize (obj);
}


GType rygel_tracker_category_get_type (void) {
	static GType rygel_tracker_category_type_id = 0;
	if (rygel_tracker_category_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (RygelTrackerCategoryClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) rygel_tracker_category_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (RygelTrackerCategory), 0, (GInstanceInitFunc) rygel_tracker_category_instance_init, NULL };
		rygel_tracker_category_type_id = g_type_register_static (RYGEL_TYPE_MEDIA_CONTAINER, "RygelTrackerCategory", &g_define_type_info, G_TYPE_FLAG_ABSTRACT);
	}
	return rygel_tracker_category_type_id;
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


static gint _vala_array_length (gpointer array) {
	int length;
	length = 0;
	if (array) {
		while (((gpointer*) array)[length]) {
			length++;
		}
	}
	return length;
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




