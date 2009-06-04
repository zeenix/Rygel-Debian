/*
 * Copyright (C) 2009 Jens Georg <mail@jensge.org>.
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
#include <gio/gio.h>
#include <gee/arraylist.h>
#include <gee/collection.h>
#include <gee/list.h>
#include <stdlib.h>
#include <string.h>


#define RYGEL_TYPE_FOLDER_DIRECTORY_SEARCH_RESULT (rygel_folder_directory_search_result_get_type ())
#define RYGEL_FOLDER_DIRECTORY_SEARCH_RESULT(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_FOLDER_DIRECTORY_SEARCH_RESULT, RygelFolderDirectorySearchResult))
#define RYGEL_FOLDER_DIRECTORY_SEARCH_RESULT_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_FOLDER_DIRECTORY_SEARCH_RESULT, RygelFolderDirectorySearchResultClass))
#define RYGEL_IS_FOLDER_DIRECTORY_SEARCH_RESULT(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_FOLDER_DIRECTORY_SEARCH_RESULT))
#define RYGEL_IS_FOLDER_DIRECTORY_SEARCH_RESULT_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_FOLDER_DIRECTORY_SEARCH_RESULT))
#define RYGEL_FOLDER_DIRECTORY_SEARCH_RESULT_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_FOLDER_DIRECTORY_SEARCH_RESULT, RygelFolderDirectorySearchResultClass))

typedef struct _RygelFolderDirectorySearchResult RygelFolderDirectorySearchResult;
typedef struct _RygelFolderDirectorySearchResultClass RygelFolderDirectorySearchResultClass;
typedef struct _RygelFolderDirectorySearchResultPrivate RygelFolderDirectorySearchResultPrivate;

#define RYGEL_TYPE_FOLDER_CONTAINER (rygel_folder_container_get_type ())
#define RYGEL_FOLDER_CONTAINER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_FOLDER_CONTAINER, RygelFolderContainer))
#define RYGEL_FOLDER_CONTAINER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_FOLDER_CONTAINER, RygelFolderContainerClass))
#define RYGEL_IS_FOLDER_CONTAINER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_FOLDER_CONTAINER))
#define RYGEL_IS_FOLDER_CONTAINER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_FOLDER_CONTAINER))
#define RYGEL_FOLDER_CONTAINER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_FOLDER_CONTAINER, RygelFolderContainerClass))

typedef struct _RygelFolderContainer RygelFolderContainer;
typedef struct _RygelFolderContainerClass RygelFolderContainerClass;

struct _RygelFolderDirectorySearchResult {
	RygelSimpleAsyncResult parent_instance;
	RygelFolderDirectorySearchResultPrivate * priv;
};

struct _RygelFolderDirectorySearchResultClass {
	RygelSimpleAsyncResultClass parent_class;
};

struct _RygelFolderDirectorySearchResultPrivate {
	guint max_count;
	guint offset;
	GFile* file;
};



GType rygel_folder_directory_search_result_get_type (void);
#define RYGEL_FOLDER_DIRECTORY_SEARCH_RESULT_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), RYGEL_TYPE_FOLDER_DIRECTORY_SEARCH_RESULT, RygelFolderDirectorySearchResultPrivate))
enum  {
	RYGEL_FOLDER_DIRECTORY_SEARCH_RESULT_DUMMY_PROPERTY
};
#define RYGEL_FOLDER_DIRECTORY_SEARCH_RESULT_MAX_CHILDREN 10
RygelFolderDirectorySearchResult* rygel_folder_directory_search_result_new (RygelMediaContainer* parent, guint offset, guint max_count, GAsyncReadyCallback callback, void* callback_target);
RygelFolderDirectorySearchResult* rygel_folder_directory_search_result_construct (GType object_type, RygelMediaContainer* parent, guint offset, guint max_count, GAsyncReadyCallback callback, void* callback_target);
RygelFolderDirectorySearchResult* rygel_folder_directory_search_result_new (RygelMediaContainer* parent, guint offset, guint max_count, GAsyncReadyCallback callback, void* callback_target);
void rygel_folder_directory_search_result_enumerator_closed (RygelFolderDirectorySearchResult* self, GObject* obj, GAsyncResult* res);
RygelFolderContainer* rygel_folder_container_new (RygelMediaContainer* parent, GFile* file);
RygelFolderContainer* rygel_folder_container_construct (GType object_type, RygelMediaContainer* parent, GFile* file);
GType rygel_folder_container_get_type (void);
static RygelMediaItem* rygel_folder_directory_search_result_get_media_item (RygelFolderDirectorySearchResult* self, RygelMediaContainer* parent, GFile* file, GFileInfo* info);
void rygel_folder_directory_search_result_enumerate_next_ready (RygelFolderDirectorySearchResult* self, GObject* obj, GAsyncResult* res);
static void _rygel_folder_directory_search_result_enumerate_next_ready_gasync_ready_callback (GObject* source_object, GAsyncResult* res, gpointer self);
static void _rygel_folder_directory_search_result_enumerator_closed_gasync_ready_callback (GObject* source_object, GAsyncResult* res, gpointer self);
static void _g_list_free_g_object_unref (GList* self);
void rygel_folder_directory_search_result_enumerate_children_ready (RygelFolderDirectorySearchResult* self, GObject* obj, GAsyncResult* res);
GeeList* rygel_folder_directory_search_result_get_children (RygelFolderDirectorySearchResult* self);
static gpointer rygel_folder_directory_search_result_parent_class = NULL;
static void rygel_folder_directory_search_result_finalize (GObject* obj);



#line 33 "rygel-folder-directory-search-result.vala"
RygelFolderDirectorySearchResult* rygel_folder_directory_search_result_construct (GType object_type, RygelMediaContainer* parent, guint offset, guint max_count, GAsyncReadyCallback callback, void* callback_target) {
#line 98 "rygel-folder-directory-search-result.c"
	RygelFolderDirectorySearchResult * self;
	GeeList* _tmp0_;
#line 33 "rygel-folder-directory-search-result.vala"
	g_return_val_if_fail (parent != NULL, NULL);
#line 37 "rygel-folder-directory-search-result.vala"
	self = (RygelFolderDirectorySearchResult*) rygel_simple_async_result_construct (object_type, GEE_TYPE_LIST, (GBoxedCopyFunc) g_object_ref, g_object_unref, (GObject*) parent, callback, callback_target);
#line 105 "rygel-folder-directory-search-result.c"
	_tmp0_ = NULL;
#line 39 "rygel-folder-directory-search-result.vala"
	((RygelSimpleAsyncResult*) self)->data = (_tmp0_ = (GeeList*) gee_array_list_new (RYGEL_TYPE_MEDIA_OBJECT, (GBoxedCopyFunc) g_object_ref, g_object_unref, g_direct_equal), (((RygelSimpleAsyncResult*) self)->data == NULL) ? NULL : (((RygelSimpleAsyncResult*) self)->data = (g_object_unref (((RygelSimpleAsyncResult*) self)->data), NULL)), _tmp0_);
#line 40 "rygel-folder-directory-search-result.vala"
	self->priv->offset = offset;
#line 41 "rygel-folder-directory-search-result.vala"
	self->priv->max_count = max_count;
#line 113 "rygel-folder-directory-search-result.c"
	return self;
}


#line 33 "rygel-folder-directory-search-result.vala"
RygelFolderDirectorySearchResult* rygel_folder_directory_search_result_new (RygelMediaContainer* parent, guint offset, guint max_count, GAsyncReadyCallback callback, void* callback_target) {
#line 33 "rygel-folder-directory-search-result.vala"
	return rygel_folder_directory_search_result_construct (RYGEL_TYPE_FOLDER_DIRECTORY_SEARCH_RESULT, parent, offset, max_count, callback, callback_target);
#line 122 "rygel-folder-directory-search-result.c"
}


#line 44 "rygel-folder-directory-search-result.vala"
void rygel_folder_directory_search_result_enumerator_closed (RygelFolderDirectorySearchResult* self, GObject* obj, GAsyncResult* res) {
#line 128 "rygel-folder-directory-search-result.c"
	GError * _inner_error_;
	GFileEnumerator* _tmp0_;
	GFileEnumerator* enumerator;
#line 44 "rygel-folder-directory-search-result.vala"
	g_return_if_fail (self != NULL);
#line 44 "rygel-folder-directory-search-result.vala"
	g_return_if_fail (obj != NULL);
#line 44 "rygel-folder-directory-search-result.vala"
	g_return_if_fail (res != NULL);
#line 138 "rygel-folder-directory-search-result.c"
	_inner_error_ = NULL;
#line 45 "rygel-folder-directory-search-result.vala"
	_tmp0_ = NULL;
#line 142 "rygel-folder-directory-search-result.c"
	enumerator = (_tmp0_ = G_FILE_ENUMERATOR (obj), (_tmp0_ == NULL) ? NULL : g_object_ref (_tmp0_));
	{
#line 48 "rygel-folder-directory-search-result.vala"
		g_file_enumerator_close_finish (enumerator, res, &_inner_error_);
#line 147 "rygel-folder-directory-search-result.c"
		if (_inner_error_ != NULL) {
			goto __catch0_g_error;
			goto __finally0;
		}
	}
	goto __finally0;
	__catch0_g_error:
	{
		GError * e;
		e = _inner_error_;
		_inner_error_ = NULL;
		{
			GError* _tmp2_;
			GError* _tmp1_;
			_tmp2_ = NULL;
#line 50 "rygel-folder-directory-search-result.vala"
			_tmp1_ = NULL;
#line 50 "rygel-folder-directory-search-result.vala"
			((RygelSimpleAsyncResult*) self)->error = (_tmp2_ = (_tmp1_ = e, (_tmp1_ == NULL) ? ((gpointer) _tmp1_) : g_error_copy (_tmp1_)), (((RygelSimpleAsyncResult*) self)->error == NULL) ? NULL : (((RygelSimpleAsyncResult*) self)->error = (g_error_free (((RygelSimpleAsyncResult*) self)->error), NULL)), _tmp2_);
#line 167 "rygel-folder-directory-search-result.c"
			(e == NULL) ? NULL : (e = (g_error_free (e), NULL));
		}
	}
	__finally0:
	if (_inner_error_ != NULL) {
		(enumerator == NULL) ? NULL : (enumerator = (g_object_unref (enumerator), NULL));
		g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, _inner_error_->message);
		g_clear_error (&_inner_error_);
		return;
	}
#line 53 "rygel-folder-directory-search-result.vala"
	rygel_simple_async_result_complete ((RygelSimpleAsyncResult*) self);
#line 180 "rygel-folder-directory-search-result.c"
	(enumerator == NULL) ? NULL : (enumerator = (g_object_unref (enumerator), NULL));
}


#line 56 "rygel-folder-directory-search-result.vala"
static void _rygel_folder_directory_search_result_enumerate_next_ready_gasync_ready_callback (GObject* source_object, GAsyncResult* res, gpointer self) {
#line 187 "rygel-folder-directory-search-result.c"
	rygel_folder_directory_search_result_enumerate_next_ready (self, source_object, res);
}


#line 44 "rygel-folder-directory-search-result.vala"
static void _rygel_folder_directory_search_result_enumerator_closed_gasync_ready_callback (GObject* source_object, GAsyncResult* res, gpointer self) {
#line 194 "rygel-folder-directory-search-result.c"
	rygel_folder_directory_search_result_enumerator_closed (self, source_object, res);
}


static void _g_list_free_g_object_unref (GList* self) {
	g_list_foreach (self, (GFunc) g_object_unref, NULL);
	g_list_free (self);
}


#line 56 "rygel-folder-directory-search-result.vala"
void rygel_folder_directory_search_result_enumerate_next_ready (RygelFolderDirectorySearchResult* self, GObject* obj, GAsyncResult* res) {
#line 207 "rygel-folder-directory-search-result.c"
	GError * _inner_error_;
	GFileEnumerator* _tmp0_;
	GFileEnumerator* enumerator;
#line 56 "rygel-folder-directory-search-result.vala"
	g_return_if_fail (self != NULL);
#line 56 "rygel-folder-directory-search-result.vala"
	g_return_if_fail (obj != NULL);
#line 56 "rygel-folder-directory-search-result.vala"
	g_return_if_fail (res != NULL);
#line 217 "rygel-folder-directory-search-result.c"
	_inner_error_ = NULL;
#line 57 "rygel-folder-directory-search-result.vala"
	_tmp0_ = NULL;
#line 221 "rygel-folder-directory-search-result.c"
	enumerator = (_tmp0_ = G_FILE_ENUMERATOR (obj), (_tmp0_ == NULL) ? NULL : g_object_ref (_tmp0_));
	{
		GList* list;
		list = g_file_enumerator_next_files_finish (enumerator, res, &_inner_error_);
		if (_inner_error_ != NULL) {
			goto __catch1_g_error;
			goto __finally1;
		}
#line 60 "rygel-folder-directory-search-result.vala"
		if (list != NULL) {
#line 232 "rygel-folder-directory-search-result.c"
			{
				GList* file_info_collection;
				GList* file_info_it;
#line 61 "rygel-folder-directory-search-result.vala"
				file_info_collection = list;
#line 238 "rygel-folder-directory-search-result.c"
				for (file_info_it = file_info_collection; file_info_it != NULL; file_info_it = file_info_it->next) {
					GFileInfo* _tmp3_;
					GFileInfo* file_info;
#line 165 "gio-2.0.vapi"
					_tmp3_ = NULL;
#line 61 "rygel-folder-directory-search-result.vala"
					file_info = (_tmp3_ = (GFileInfo*) file_info_it->data, (_tmp3_ == NULL) ? NULL : g_object_ref (_tmp3_));
#line 246 "rygel-folder-directory-search-result.c"
					{
						GFile* f;
						RygelMediaObject* item;
						f = g_file_get_child (self->priv->file, g_file_info_get_name (file_info));
						item = NULL;
#line 64 "rygel-folder-directory-search-result.vala"
						if (g_file_info_get_file_type (file_info) == G_FILE_TYPE_DIRECTORY) {
#line 254 "rygel-folder-directory-search-result.c"
							RygelMediaObject* _tmp1_;
							_tmp1_ = NULL;
#line 65 "rygel-folder-directory-search-result.vala"
							item = (_tmp1_ = (RygelMediaObject*) rygel_folder_container_new (RYGEL_MEDIA_CONTAINER (((RygelSimpleAsyncResult*) self)->source_object), f), (item == NULL) ? NULL : (item = (g_object_unref (item), NULL)), _tmp1_);
#line 259 "rygel-folder-directory-search-result.c"
						} else {
							RygelMediaObject* _tmp2_;
							_tmp2_ = NULL;
#line 70 "rygel-folder-directory-search-result.vala"
							item = (_tmp2_ = (RygelMediaObject*) rygel_folder_directory_search_result_get_media_item (self, RYGEL_MEDIA_CONTAINER (((RygelSimpleAsyncResult*) self)->source_object), f, file_info), (item == NULL) ? NULL : (item = (g_object_unref (item), NULL)), _tmp2_);
#line 265 "rygel-folder-directory-search-result.c"
						}
#line 75 "rygel-folder-directory-search-result.vala"
						if (item != NULL) {
#line 76 "rygel-folder-directory-search-result.vala"
							gee_collection_add ((GeeCollection*) ((GeeList*) ((RygelSimpleAsyncResult*) self)->data), item);
#line 271 "rygel-folder-directory-search-result.c"
						}
						(file_info == NULL) ? NULL : (file_info = (g_object_unref (file_info), NULL));
						(f == NULL) ? NULL : (f = (g_object_unref (f), NULL));
						(item == NULL) ? NULL : (item = (g_object_unref (item), NULL));
					}
				}
			}
#line 80 "rygel-folder-directory-search-result.vala"
			g_file_enumerator_next_files_async (enumerator, RYGEL_FOLDER_DIRECTORY_SEARCH_RESULT_MAX_CHILDREN, G_PRIORITY_DEFAULT, NULL, _rygel_folder_directory_search_result_enumerate_next_ready_gasync_ready_callback, self);
#line 281 "rygel-folder-directory-search-result.c"
		} else {
#line 84 "rygel-folder-directory-search-result.vala"
			g_file_enumerator_close_async (enumerator, G_PRIORITY_DEFAULT, NULL, _rygel_folder_directory_search_result_enumerator_closed_gasync_ready_callback, self);
#line 285 "rygel-folder-directory-search-result.c"
		}
		(list == NULL) ? NULL : (list = (_g_list_free_g_object_unref (list), NULL));
	}
	goto __finally1;
	__catch1_g_error:
	{
		GError * e;
		e = _inner_error_;
		_inner_error_ = NULL;
		{
			GError* _tmp5_;
			GError* _tmp4_;
			_tmp5_ = NULL;
#line 89 "rygel-folder-directory-search-result.vala"
			_tmp4_ = NULL;
#line 89 "rygel-folder-directory-search-result.vala"
			((RygelSimpleAsyncResult*) self)->error = (_tmp5_ = (_tmp4_ = e, (_tmp4_ == NULL) ? ((gpointer) _tmp4_) : g_error_copy (_tmp4_)), (((RygelSimpleAsyncResult*) self)->error == NULL) ? NULL : (((RygelSimpleAsyncResult*) self)->error = (g_error_free (((RygelSimpleAsyncResult*) self)->error), NULL)), _tmp5_);
#line 90 "rygel-folder-directory-search-result.vala"
			rygel_simple_async_result_complete ((RygelSimpleAsyncResult*) self);
#line 305 "rygel-folder-directory-search-result.c"
			(e == NULL) ? NULL : (e = (g_error_free (e), NULL));
		}
	}
	__finally1:
	if (_inner_error_ != NULL) {
		(enumerator == NULL) ? NULL : (enumerator = (g_object_unref (enumerator), NULL));
		g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, _inner_error_->message);
		g_clear_error (&_inner_error_);
		return;
	}
	(enumerator == NULL) ? NULL : (enumerator = (g_object_unref (enumerator), NULL));
}


#line 94 "rygel-folder-directory-search-result.vala"
void rygel_folder_directory_search_result_enumerate_children_ready (RygelFolderDirectorySearchResult* self, GObject* obj, GAsyncResult* res) {
#line 322 "rygel-folder-directory-search-result.c"
	GError * _inner_error_;
	GFile* _tmp1_;
	GFile* _tmp0_;
#line 94 "rygel-folder-directory-search-result.vala"
	g_return_if_fail (self != NULL);
#line 94 "rygel-folder-directory-search-result.vala"
	g_return_if_fail (obj != NULL);
#line 94 "rygel-folder-directory-search-result.vala"
	g_return_if_fail (res != NULL);
#line 332 "rygel-folder-directory-search-result.c"
	_inner_error_ = NULL;
	_tmp1_ = NULL;
#line 95 "rygel-folder-directory-search-result.vala"
	_tmp0_ = NULL;
#line 95 "rygel-folder-directory-search-result.vala"
	self->priv->file = (_tmp1_ = (_tmp0_ = G_FILE (obj), (_tmp0_ == NULL) ? NULL : g_object_ref (_tmp0_)), (self->priv->file == NULL) ? NULL : (self->priv->file = (g_object_unref (self->priv->file), NULL)), _tmp1_);
#line 339 "rygel-folder-directory-search-result.c"
	{
		GFileEnumerator* enumerator;
		enumerator = g_file_enumerate_children_finish (self->priv->file, res, &_inner_error_);
		if (_inner_error_ != NULL) {
			goto __catch2_g_error;
			goto __finally2;
		}
#line 100 "rygel-folder-directory-search-result.vala"
		g_file_enumerator_next_files_async (enumerator, RYGEL_FOLDER_DIRECTORY_SEARCH_RESULT_MAX_CHILDREN, G_PRIORITY_DEFAULT, NULL, _rygel_folder_directory_search_result_enumerate_next_ready_gasync_ready_callback, self);
#line 349 "rygel-folder-directory-search-result.c"
		(enumerator == NULL) ? NULL : (enumerator = (g_object_unref (enumerator), NULL));
	}
	goto __finally2;
	__catch2_g_error:
	{
		GError * _error_;
		_error_ = _inner_error_;
		_inner_error_ = NULL;
		{
			GError* _tmp3_;
			GError* _tmp2_;
			_tmp3_ = NULL;
#line 105 "rygel-folder-directory-search-result.vala"
			_tmp2_ = NULL;
#line 105 "rygel-folder-directory-search-result.vala"
			((RygelSimpleAsyncResult*) self)->error = (_tmp3_ = (_tmp2_ = _error_, (_tmp2_ == NULL) ? ((gpointer) _tmp2_) : g_error_copy (_tmp2_)), (((RygelSimpleAsyncResult*) self)->error == NULL) ? NULL : (((RygelSimpleAsyncResult*) self)->error = (g_error_free (((RygelSimpleAsyncResult*) self)->error), NULL)), _tmp3_);
#line 106 "rygel-folder-directory-search-result.vala"
			rygel_simple_async_result_complete ((RygelSimpleAsyncResult*) self);
#line 368 "rygel-folder-directory-search-result.c"
			(_error_ == NULL) ? NULL : (_error_ = (g_error_free (_error_), NULL));
		}
	}
	__finally2:
	if (_inner_error_ != NULL) {
		g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, _inner_error_->message);
		g_clear_error (&_inner_error_);
		return;
	}
}


#line 110 "rygel-folder-directory-search-result.vala"
GeeList* rygel_folder_directory_search_result_get_children (RygelFolderDirectorySearchResult* self) {
#line 383 "rygel-folder-directory-search-result.c"
	guint stop;
	GeeList* children;
#line 110 "rygel-folder-directory-search-result.vala"
	g_return_val_if_fail (self != NULL, NULL);
#line 388 "rygel-folder-directory-search-result.c"
	stop = self->priv->offset + self->priv->max_count;
#line 112 "rygel-folder-directory-search-result.vala"
	stop = CLAMP (stop, (guint) 0, (guint) gee_collection_get_size ((GeeCollection*) ((GeeList*) ((RygelSimpleAsyncResult*) self)->data)));
#line 392 "rygel-folder-directory-search-result.c"
	children = gee_list_slice ((GeeList*) ((RygelSimpleAsyncResult*) self)->data, (gint) self->priv->offset, (gint) stop);
#line 115 "rygel-folder-directory-search-result.vala"
	return children;
#line 396 "rygel-folder-directory-search-result.c"
}


#line 118 "rygel-folder-directory-search-result.vala"
static RygelMediaItem* rygel_folder_directory_search_result_get_media_item (RygelFolderDirectorySearchResult* self, RygelMediaContainer* parent, GFile* file, GFileInfo* info) {
#line 402 "rygel-folder-directory-search-result.c"
	const char* _tmp0_;
	char* content_type;
	char* item_class;
	char* id;
	RygelMediaItem* item;
	char* _tmp6_;
	const char* _tmp5_;
	char* _tmp8_;
	char* _tmp7_;
	RygelMediaItem* _tmp9_;
#line 118 "rygel-folder-directory-search-result.vala"
	g_return_val_if_fail (self != NULL, NULL);
#line 118 "rygel-folder-directory-search-result.vala"
	g_return_val_if_fail (parent != NULL, NULL);
#line 118 "rygel-folder-directory-search-result.vala"
	g_return_val_if_fail (file != NULL, NULL);
#line 118 "rygel-folder-directory-search-result.vala"
	g_return_val_if_fail (info != NULL, NULL);
#line 121 "rygel-folder-directory-search-result.vala"
	_tmp0_ = NULL;
#line 423 "rygel-folder-directory-search-result.c"
	content_type = (_tmp0_ = g_file_info_get_content_type (info), (_tmp0_ == NULL) ? NULL : g_strdup (_tmp0_));
	item_class = NULL;
	id = g_compute_checksum_for_string (G_CHECKSUM_MD5, g_file_info_get_name (info), -1);
	/* use heuristics based on content type; will use MediaHarvester
	 when it's ready*/
#line 129 "rygel-folder-directory-search-result.vala"
	if (g_str_has_prefix (content_type, "video/")) {
#line 431 "rygel-folder-directory-search-result.c"
		char* _tmp1_;
		_tmp1_ = NULL;
#line 130 "rygel-folder-directory-search-result.vala"
		item_class = (_tmp1_ = g_strdup (RYGEL_MEDIA_ITEM_VIDEO_CLASS), item_class = (g_free (item_class), NULL), _tmp1_);
#line 436 "rygel-folder-directory-search-result.c"
	} else {
#line 131 "rygel-folder-directory-search-result.vala"
		if (g_str_has_prefix (content_type, "audio/")) {
#line 440 "rygel-folder-directory-search-result.c"
			char* _tmp2_;
			_tmp2_ = NULL;
#line 132 "rygel-folder-directory-search-result.vala"
			item_class = (_tmp2_ = g_strdup (RYGEL_MEDIA_ITEM_AUDIO_CLASS), item_class = (g_free (item_class), NULL), _tmp2_);
#line 445 "rygel-folder-directory-search-result.c"
		} else {
#line 133 "rygel-folder-directory-search-result.vala"
			if (g_str_has_prefix (content_type, "image/")) {
#line 449 "rygel-folder-directory-search-result.c"
				char* _tmp3_;
				_tmp3_ = NULL;
#line 134 "rygel-folder-directory-search-result.vala"
				item_class = (_tmp3_ = g_strdup (RYGEL_MEDIA_ITEM_IMAGE_CLASS), item_class = (g_free (item_class), NULL), _tmp3_);
#line 454 "rygel-folder-directory-search-result.c"
			}
		}
	}
#line 137 "rygel-folder-directory-search-result.vala"
	if (NULL == item_class) {
#line 460 "rygel-folder-directory-search-result.c"
		RygelMediaItem* _tmp4_;
#line 138 "rygel-folder-directory-search-result.vala"
		_tmp4_ = NULL;
#line 138 "rygel-folder-directory-search-result.vala"
		return (_tmp4_ = NULL, content_type = (g_free (content_type), NULL), item_class = (g_free (item_class), NULL), id = (g_free (id), NULL), _tmp4_);
#line 466 "rygel-folder-directory-search-result.c"
	}
	item = rygel_media_item_new (id, parent, g_file_info_get_name (info), item_class);
	_tmp6_ = NULL;
#line 145 "rygel-folder-directory-search-result.vala"
	_tmp5_ = NULL;
#line 145 "rygel-folder-directory-search-result.vala"
	item->mime_type = (_tmp6_ = (_tmp5_ = content_type, (_tmp5_ == NULL) ? NULL : g_strdup (_tmp5_)), item->mime_type = (g_free (item->mime_type), NULL), _tmp6_);
#line 2716 "glib-2.0.vapi"
	_tmp8_ = NULL;
#line 720 "gio-2.0.vapi"
	_tmp7_ = NULL;
#line 146 "rygel-folder-directory-search-result.vala"
	gee_collection_add ((GeeCollection*) item->uris, _tmp8_ = g_markup_escape_text (_tmp7_ = g_file_get_uri (file), -1));
#line 480 "rygel-folder-directory-search-result.c"
	_tmp8_ = (g_free (_tmp8_), NULL);
	_tmp7_ = (g_free (_tmp7_), NULL);
#line 148 "rygel-folder-directory-search-result.vala"
	_tmp9_ = NULL;
#line 148 "rygel-folder-directory-search-result.vala"
	return (_tmp9_ = item, content_type = (g_free (content_type), NULL), item_class = (g_free (item_class), NULL), id = (g_free (id), NULL), _tmp9_);
#line 487 "rygel-folder-directory-search-result.c"
}


static void rygel_folder_directory_search_result_class_init (RygelFolderDirectorySearchResultClass * klass) {
	rygel_folder_directory_search_result_parent_class = g_type_class_peek_parent (klass);
	g_type_class_add_private (klass, sizeof (RygelFolderDirectorySearchResultPrivate));
	G_OBJECT_CLASS (klass)->finalize = rygel_folder_directory_search_result_finalize;
}


static void rygel_folder_directory_search_result_instance_init (RygelFolderDirectorySearchResult * self) {
	self->priv = RYGEL_FOLDER_DIRECTORY_SEARCH_RESULT_GET_PRIVATE (self);
}


static void rygel_folder_directory_search_result_finalize (GObject* obj) {
	RygelFolderDirectorySearchResult * self;
	self = RYGEL_FOLDER_DIRECTORY_SEARCH_RESULT (obj);
	(self->priv->file == NULL) ? NULL : (self->priv->file = (g_object_unref (self->priv->file), NULL));
	G_OBJECT_CLASS (rygel_folder_directory_search_result_parent_class)->finalize (obj);
}


GType rygel_folder_directory_search_result_get_type (void) {
	static GType rygel_folder_directory_search_result_type_id = 0;
	if (rygel_folder_directory_search_result_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (RygelFolderDirectorySearchResultClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) rygel_folder_directory_search_result_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (RygelFolderDirectorySearchResult), 0, (GInstanceInitFunc) rygel_folder_directory_search_result_instance_init, NULL };
		rygel_folder_directory_search_result_type_id = g_type_register_static (RYGEL_TYPE_SIMPLE_ASYNC_RESULT, "RygelFolderDirectorySearchResult", &g_define_type_info, 0);
	}
	return rygel_folder_directory_search_result_type_id;
}




