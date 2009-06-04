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
#include <gee/arraylist.h>
#include <gio/gio.h>
#include <gee/list.h>
#include <gee/collection.h>
#include <gee/iterable.h>
#include <gee/iterator.h>
#include <stdlib.h>
#include <string.h>


#define RYGEL_TYPE_FOLDER_CONTAINER (rygel_folder_container_get_type ())
#define RYGEL_FOLDER_CONTAINER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_FOLDER_CONTAINER, RygelFolderContainer))
#define RYGEL_FOLDER_CONTAINER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_FOLDER_CONTAINER, RygelFolderContainerClass))
#define RYGEL_IS_FOLDER_CONTAINER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_FOLDER_CONTAINER))
#define RYGEL_IS_FOLDER_CONTAINER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_FOLDER_CONTAINER))
#define RYGEL_FOLDER_CONTAINER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_FOLDER_CONTAINER, RygelFolderContainerClass))

typedef struct _RygelFolderContainer RygelFolderContainer;
typedef struct _RygelFolderContainerClass RygelFolderContainerClass;
typedef struct _RygelFolderContainerPrivate RygelFolderContainerPrivate;

#define RYGEL_TYPE_FOLDER_DIRECTORY_SEARCH_RESULT (rygel_folder_directory_search_result_get_type ())
#define RYGEL_FOLDER_DIRECTORY_SEARCH_RESULT(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_FOLDER_DIRECTORY_SEARCH_RESULT, RygelFolderDirectorySearchResult))
#define RYGEL_FOLDER_DIRECTORY_SEARCH_RESULT_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_FOLDER_DIRECTORY_SEARCH_RESULT, RygelFolderDirectorySearchResultClass))
#define RYGEL_IS_FOLDER_DIRECTORY_SEARCH_RESULT(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_FOLDER_DIRECTORY_SEARCH_RESULT))
#define RYGEL_IS_FOLDER_DIRECTORY_SEARCH_RESULT_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_FOLDER_DIRECTORY_SEARCH_RESULT))
#define RYGEL_FOLDER_DIRECTORY_SEARCH_RESULT_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_FOLDER_DIRECTORY_SEARCH_RESULT, RygelFolderDirectorySearchResultClass))

typedef struct _RygelFolderDirectorySearchResult RygelFolderDirectorySearchResult;
typedef struct _RygelFolderDirectorySearchResultClass RygelFolderDirectorySearchResultClass;

/**
 * MediaContainer which exposes the contents of a directory 
 * as items.
 *
 * The folder contents will be queried on demand and cached afterwards
 */
struct _RygelFolderContainer {
	RygelMediaContainer parent_instance;
	RygelFolderContainerPrivate * priv;
};

struct _RygelFolderContainerClass {
	RygelMediaContainerClass parent_class;
};

struct _RygelFolderContainerPrivate {
	GeeArrayList* items;
	GFile* root_dir;
	GeeList* results;
};



GType rygel_folder_container_get_type (void);
#define RYGEL_FOLDER_CONTAINER_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), RYGEL_TYPE_FOLDER_CONTAINER, RygelFolderContainerPrivate))
enum  {
	RYGEL_FOLDER_CONTAINER_DUMMY_PROPERTY
};
#define RYGEL_FOLDER_CONTAINER_MAX_CHILDREN 10
RygelFolderDirectorySearchResult* rygel_folder_directory_search_result_new (RygelMediaContainer* parent, guint offset, guint max_count, GAsyncReadyCallback callback, void* callback_target);
RygelFolderDirectorySearchResult* rygel_folder_directory_search_result_construct (GType object_type, RygelMediaContainer* parent, guint offset, guint max_count, GAsyncReadyCallback callback, void* callback_target);
GType rygel_folder_directory_search_result_get_type (void);
void rygel_folder_directory_search_result_enumerate_children_ready (RygelFolderDirectorySearchResult* self, GObject* obj, GAsyncResult* res);
static void _rygel_folder_directory_search_result_enumerate_children_ready_gasync_ready_callback (GObject* source_object, GAsyncResult* res, gpointer self);
static void rygel_folder_container_real_get_children (RygelMediaContainer* base, guint offset, guint max_count, GCancellable* cancellable, GAsyncReadyCallback callback, void* callback_target);
GeeList* rygel_folder_directory_search_result_get_children (RygelFolderDirectorySearchResult* self);
static GeeList* rygel_folder_container_real_get_children_finish (RygelMediaContainer* base, GAsyncResult* res, GError** error);
static void rygel_folder_container_real_find_object (RygelMediaContainer* base, const char* id, GCancellable* cancellable, GAsyncReadyCallback callback, void* callback_target);
RygelMediaObject* rygel_folder_container_find_object_sync (RygelFolderContainer* self, const char* id);
static RygelMediaObject* rygel_folder_container_real_find_object_finish (RygelMediaContainer* base, GAsyncResult* res, GError** error);
RygelFolderContainer* rygel_folder_container_new (RygelMediaContainer* parent, GFile* file);
RygelFolderContainer* rygel_folder_container_construct (GType object_type, RygelMediaContainer* parent, GFile* file);
RygelFolderContainer* rygel_folder_container_new (RygelMediaContainer* parent, GFile* file);
static gpointer rygel_folder_container_parent_class = NULL;
static void rygel_folder_container_finalize (GObject* obj);
static int _vala_strcmp0 (const char * str1, const char * str2);



#line 94 "rygel-folder-directory-search-result.vala"
static void _rygel_folder_directory_search_result_enumerate_children_ready_gasync_ready_callback (GObject* source_object, GAsyncResult* res, gpointer self) {
#line 107 "rygel-folder-container.c"
	rygel_folder_directory_search_result_enumerate_children_ready (self, source_object, res);
}


/* methods overridden from MediaContainer*/
#line 51 "rygel-folder-container.vala"
static void rygel_folder_container_real_get_children (RygelMediaContainer* base, guint offset, guint max_count, GCancellable* cancellable, GAsyncReadyCallback callback, void* callback_target) {
#line 115 "rygel-folder-container.c"
	RygelFolderContainer * self;
	self = (RygelFolderContainer*) base;
	/* if the cache is empty, fill it*/
#line 56 "rygel-folder-container.vala"
	if (gee_collection_get_size ((GeeCollection*) self->priv->items) == 0) {
#line 121 "rygel-folder-container.c"
		RygelFolderDirectorySearchResult* res;
		res = rygel_folder_directory_search_result_new ((RygelMediaContainer*) self, offset, max_count, callback, callback_target);
#line 62 "rygel-folder-container.vala"
		g_file_enumerate_children_async (self->priv->root_dir, G_FILE_ATTRIBUTE_STANDARD_CONTENT_TYPE "," G_FILE_ATTRIBUTE_STANDARD_DISPLAY_NAME "," G_FILE_ATTRIBUTE_STANDARD_TYPE "," G_FILE_ATTRIBUTE_STANDARD_NAME, G_FILE_QUERY_INFO_NONE, G_PRIORITY_DEFAULT, NULL, _rygel_folder_directory_search_result_enumerate_children_ready_gasync_ready_callback, res);
#line 71 "rygel-folder-container.vala"
		gee_collection_add ((GeeCollection*) self->priv->results, (GAsyncResult*) res);
#line 128 "rygel-folder-container.c"
		(res == NULL) ? NULL : (res = (g_object_unref (res), NULL));
	} else {
		guint stop;
		GeeList* children;
		RygelSimpleAsyncResult* res;
		GeeList* _tmp1_;
		GeeList* _tmp0_;
		stop = offset + max_count;
#line 74 "rygel-folder-container.vala"
		stop = CLAMP (stop, (guint) 0, ((RygelMediaContainer*) self)->child_count);
#line 139 "rygel-folder-container.c"
		children = gee_list_slice ((GeeList*) self->priv->items, (gint) offset, (gint) stop);
		res = rygel_simple_async_result_new (GEE_TYPE_LIST, (GBoxedCopyFunc) g_object_ref, g_object_unref, (GObject*) self, callback, callback_target);
		_tmp1_ = NULL;
#line 80 "rygel-folder-container.vala"
		_tmp0_ = NULL;
#line 80 "rygel-folder-container.vala"
		res->data = (_tmp1_ = (_tmp0_ = children, (_tmp0_ == NULL) ? NULL : g_object_ref (_tmp0_)), (res->data == NULL) ? NULL : (res->data = (g_object_unref (res->data), NULL)), _tmp1_);
#line 81 "rygel-folder-container.vala"
		rygel_simple_async_result_complete_in_idle (res);
#line 149 "rygel-folder-container.c"
		(children == NULL) ? NULL : (children = (g_object_unref (children), NULL));
		(res == NULL) ? NULL : (res = (g_object_unref (res), NULL));
	}
}


#line 85 "rygel-folder-container.vala"
static GeeList* rygel_folder_container_real_get_children_finish (RygelMediaContainer* base, GAsyncResult* res, GError** error) {
#line 158 "rygel-folder-container.c"
	RygelFolderContainer * self;
	self = (RygelFolderContainer*) base;
#line 85 "rygel-folder-container.vala"
	g_return_val_if_fail (res != NULL, NULL);
#line 88 "rygel-folder-container.vala"
	if (RYGEL_IS_FOLDER_DIRECTORY_SEARCH_RESULT (res)) {
#line 165 "rygel-folder-container.c"
		RygelFolderDirectorySearchResult* _tmp0_;
		RygelFolderDirectorySearchResult* dsr;
		GeeList* _tmp1_;
#line 89 "rygel-folder-container.vala"
		_tmp0_ = NULL;
#line 171 "rygel-folder-container.c"
		dsr = (_tmp0_ = RYGEL_FOLDER_DIRECTORY_SEARCH_RESULT (res), (_tmp0_ == NULL) ? NULL : g_object_ref (_tmp0_));
		{
			GeeIterator* _item_it;
			_item_it = gee_iterable_iterator ((GeeIterable*) ((GeeList*) ((RygelSimpleAsyncResult*) dsr)->data));
#line 91 "rygel-folder-container.vala"
			while (gee_iterator_next (_item_it)) {
#line 178 "rygel-folder-container.c"
				RygelMediaObject* item;
				item = (RygelMediaObject*) gee_iterator_get (_item_it);
#line 92 "rygel-folder-container.vala"
				gee_collection_add ((GeeCollection*) self->priv->items, item);
#line 183 "rygel-folder-container.c"
				(item == NULL) ? NULL : (item = (g_object_unref (item), NULL));
			}
			(_item_it == NULL) ? NULL : (_item_it = (g_object_unref (_item_it), NULL));
		}
#line 95 "rygel-folder-container.vala"
		((RygelMediaContainer*) self)->child_count = (guint) gee_collection_get_size ((GeeCollection*) self->priv->items);
#line 96 "rygel-folder-container.vala"
		gee_collection_remove ((GeeCollection*) self->priv->results, res);
#line 97 "rygel-folder-container.vala"
		_tmp1_ = NULL;
#line 97 "rygel-folder-container.vala"
		return (_tmp1_ = rygel_folder_directory_search_result_get_children (dsr), (dsr == NULL) ? NULL : (dsr = (g_object_unref (dsr), NULL)), _tmp1_);
#line 196 "rygel-folder-container.c"
	} else {
		RygelSimpleAsyncResult* _tmp2_;
		RygelSimpleAsyncResult* simple_res;
		GeeList* _tmp3_;
		GeeList* _tmp4_;
#line 99 "rygel-folder-container.vala"
		_tmp2_ = NULL;
#line 204 "rygel-folder-container.c"
		simple_res = (_tmp2_ = RYGEL_SIMPLE_ASYNC_RESULT (res), (_tmp2_ == NULL) ? NULL : g_object_ref (_tmp2_));
#line 101 "rygel-folder-container.vala"
		_tmp3_ = NULL;
#line 101 "rygel-folder-container.vala"
		_tmp4_ = NULL;
#line 101 "rygel-folder-container.vala"
		return (_tmp4_ = (_tmp3_ = (GeeList*) simple_res->data, (_tmp3_ == NULL) ? NULL : g_object_ref (_tmp3_)), (simple_res == NULL) ? NULL : (simple_res = (g_object_unref (simple_res), NULL)), _tmp4_);
#line 212 "rygel-folder-container.c"
	}
}


#line 105 "rygel-folder-container.vala"
static void rygel_folder_container_real_find_object (RygelMediaContainer* base, const char* id, GCancellable* cancellable, GAsyncReadyCallback callback, void* callback_target) {
#line 219 "rygel-folder-container.c"
	RygelFolderContainer * self;
	RygelSimpleAsyncResult* res;
	char* _tmp1_;
	const char* _tmp0_;
	self = (RygelFolderContainer*) base;
#line 105 "rygel-folder-container.vala"
	g_return_if_fail (id != NULL);
#line 227 "rygel-folder-container.c"
	res = rygel_simple_async_result_new (G_TYPE_STRING, (GBoxedCopyFunc) g_strdup, g_free, (GObject*) self, callback, callback_target);
	_tmp1_ = NULL;
#line 110 "rygel-folder-container.vala"
	_tmp0_ = NULL;
#line 110 "rygel-folder-container.vala"
	res->data = (_tmp1_ = (_tmp0_ = id, (_tmp0_ == NULL) ? NULL : g_strdup (_tmp0_)), res->data = (g_free (res->data), NULL), _tmp1_);
#line 111 "rygel-folder-container.vala"
	rygel_simple_async_result_complete_in_idle (res);
#line 236 "rygel-folder-container.c"
	(res == NULL) ? NULL : (res = (g_object_unref (res), NULL));
}


#line 114 "rygel-folder-container.vala"
static RygelMediaObject* rygel_folder_container_real_find_object_finish (RygelMediaContainer* base, GAsyncResult* res, GError** error) {
#line 243 "rygel-folder-container.c"
	RygelFolderContainer * self;
	const char* _tmp0_;
	char* id;
	RygelMediaObject* _tmp1_;
	self = (RygelFolderContainer*) base;
#line 114 "rygel-folder-container.vala"
	g_return_val_if_fail (res != NULL, NULL);
#line 116 "rygel-folder-container.vala"
	_tmp0_ = NULL;
#line 253 "rygel-folder-container.c"
	id = (_tmp0_ = (const char*) RYGEL_SIMPLE_ASYNC_RESULT (res)->data, (_tmp0_ == NULL) ? NULL : g_strdup (_tmp0_));
#line 118 "rygel-folder-container.vala"
	_tmp1_ = NULL;
#line 118 "rygel-folder-container.vala"
	return (_tmp1_ = rygel_folder_container_find_object_sync (self, id), id = (g_free (id), NULL), _tmp1_);
#line 259 "rygel-folder-container.c"
}


#line 121 "rygel-folder-container.vala"
RygelMediaObject* rygel_folder_container_find_object_sync (RygelFolderContainer* self, const char* id) {
#line 265 "rygel-folder-container.c"
	RygelMediaObject* item;
#line 121 "rygel-folder-container.vala"
	g_return_val_if_fail (self != NULL, NULL);
#line 121 "rygel-folder-container.vala"
	g_return_val_if_fail (id != NULL, NULL);
#line 271 "rygel-folder-container.c"
	item = NULL;
	/* check if the searched item is in our cache*/
	{
		GeeIterator* _tmp_it;
		/* check if the searched item is in our cache*/
		_tmp_it = gee_iterable_iterator ((GeeIterable*) self->priv->items);
		/* check if the searched item is in our cache*/
#line 125 "rygel-folder-container.vala"
		while (gee_iterator_next (_tmp_it)) {
#line 281 "rygel-folder-container.c"
			RygelMediaObject* tmp;
			/* check if the searched item is in our cache*/
			tmp = (RygelMediaObject*) gee_iterator_get (_tmp_it);
#line 126 "rygel-folder-container.vala"
			if (_vala_strcmp0 (id, tmp->id) == 0) {
#line 287 "rygel-folder-container.c"
				RygelMediaObject* _tmp1_;
				RygelMediaObject* _tmp0_;
				_tmp1_ = NULL;
#line 127 "rygel-folder-container.vala"
				_tmp0_ = NULL;
#line 127 "rygel-folder-container.vala"
				item = (_tmp1_ = (_tmp0_ = tmp, (_tmp0_ == NULL) ? NULL : g_object_ref (_tmp0_)), (item == NULL) ? NULL : (item = (g_object_unref (item), NULL)), _tmp1_);
#line 295 "rygel-folder-container.c"
				(tmp == NULL) ? NULL : (tmp = (g_object_unref (tmp), NULL));
#line 128 "rygel-folder-container.vala"
				break;
#line 299 "rygel-folder-container.c"
			}
			(tmp == NULL) ? NULL : (tmp = (g_object_unref (tmp), NULL));
		}
		(_tmp_it == NULL) ? NULL : (_tmp_it = (g_object_unref (_tmp_it), NULL));
	}
	/* if not found, do a depth-first search on the child 
	 folders*/
#line 134 "rygel-folder-container.vala"
	if (item == NULL) {
#line 309 "rygel-folder-container.c"
		{
			GeeIterator* _tmp_it;
			_tmp_it = gee_iterable_iterator ((GeeIterable*) self->priv->items);
#line 135 "rygel-folder-container.vala"
			while (gee_iterator_next (_tmp_it)) {
#line 315 "rygel-folder-container.c"
				RygelMediaObject* tmp;
				tmp = (RygelMediaObject*) gee_iterator_get (_tmp_it);
#line 136 "rygel-folder-container.vala"
				if (RYGEL_IS_FOLDER_CONTAINER (tmp)) {
#line 320 "rygel-folder-container.c"
					RygelFolderContainer* _tmp2_;
					RygelFolderContainer* folder;
					RygelMediaObject* _tmp3_;
#line 137 "rygel-folder-container.vala"
					_tmp2_ = NULL;
#line 326 "rygel-folder-container.c"
					folder = (_tmp2_ = RYGEL_FOLDER_CONTAINER (tmp), (_tmp2_ == NULL) ? NULL : g_object_ref (_tmp2_));
					_tmp3_ = NULL;
#line 138 "rygel-folder-container.vala"
					item = (_tmp3_ = rygel_folder_container_find_object_sync (folder, id), (item == NULL) ? NULL : (item = (g_object_unref (item), NULL)), _tmp3_);
#line 139 "rygel-folder-container.vala"
					if (item != NULL) {
#line 333 "rygel-folder-container.c"
						(folder == NULL) ? NULL : (folder = (g_object_unref (folder), NULL));
						(tmp == NULL) ? NULL : (tmp = (g_object_unref (tmp), NULL));
#line 140 "rygel-folder-container.vala"
						break;
#line 338 "rygel-folder-container.c"
					}
					(folder == NULL) ? NULL : (folder = (g_object_unref (folder), NULL));
				}
				(tmp == NULL) ? NULL : (tmp = (g_object_unref (tmp), NULL));
			}
			(_tmp_it == NULL) ? NULL : (_tmp_it = (g_object_unref (_tmp_it), NULL));
		}
	}
#line 146 "rygel-folder-container.vala"
	return item;
#line 349 "rygel-folder-container.c"
}


/**
     * Create a new root container.
     * 
     * @parameter parent, parent container
     * @parameter file, directory you want to expose
     * @parameter full, show full path in title
     */
#line 156 "rygel-folder-container.vala"
RygelFolderContainer* rygel_folder_container_construct (GType object_type, RygelMediaContainer* parent, GFile* file) {
#line 362 "rygel-folder-container.c"
	RygelFolderContainer * self;
	char* _tmp0_;
	char* _tmp1_;
	char* id;
	char* _tmp2_;
	GFile* _tmp4_;
	GFile* _tmp3_;
	GeeArrayList* _tmp5_;
	GeeList* _tmp6_;
#line 156 "rygel-folder-container.vala"
	g_return_val_if_fail (parent != NULL, NULL);
#line 156 "rygel-folder-container.vala"
	g_return_val_if_fail (file != NULL, NULL);
#line 720 "gio-2.0.vapi"
	_tmp0_ = NULL;
#line 157 "rygel-folder-container.vala"
	_tmp1_ = NULL;
#line 380 "rygel-folder-container.c"
	id = (_tmp1_ = g_compute_checksum_for_string (G_CHECKSUM_MD5, _tmp0_ = g_file_get_uri (file), -1), _tmp0_ = (g_free (_tmp0_), NULL), _tmp1_);
#line 713 "gio-2.0.vapi"
	_tmp2_ = NULL;
#line 160 "rygel-folder-container.vala"
	self = (RygelFolderContainer*) rygel_media_container_construct (object_type, id, parent, _tmp2_ = g_file_get_basename (file), (guint) 0);
#line 386 "rygel-folder-container.c"
	_tmp2_ = (g_free (_tmp2_), NULL);
	_tmp4_ = NULL;
#line 161 "rygel-folder-container.vala"
	_tmp3_ = NULL;
#line 161 "rygel-folder-container.vala"
	self->priv->root_dir = (_tmp4_ = (_tmp3_ = file, (_tmp3_ == NULL) ? NULL : g_object_ref (_tmp3_)), (self->priv->root_dir == NULL) ? NULL : (self->priv->root_dir = (g_object_unref (self->priv->root_dir), NULL)), _tmp4_);
#line 393 "rygel-folder-container.c"
	_tmp5_ = NULL;
#line 163 "rygel-folder-container.vala"
	self->priv->items = (_tmp5_ = gee_array_list_new (RYGEL_TYPE_MEDIA_OBJECT, (GBoxedCopyFunc) g_object_ref, g_object_unref, g_direct_equal), (self->priv->items == NULL) ? NULL : (self->priv->items = (g_object_unref (self->priv->items), NULL)), _tmp5_);
#line 164 "rygel-folder-container.vala"
	((RygelMediaContainer*) self)->child_count = (guint) 0;
#line 399 "rygel-folder-container.c"
	_tmp6_ = NULL;
#line 165 "rygel-folder-container.vala"
	self->priv->results = (_tmp6_ = (GeeList*) gee_array_list_new (G_TYPE_ASYNC_RESULT, (GBoxedCopyFunc) g_object_ref, g_object_unref, g_direct_equal), (self->priv->results == NULL) ? NULL : (self->priv->results = (g_object_unref (self->priv->results), NULL)), _tmp6_);
#line 403 "rygel-folder-container.c"
	id = (g_free (id), NULL);
	return self;
}


#line 156 "rygel-folder-container.vala"
RygelFolderContainer* rygel_folder_container_new (RygelMediaContainer* parent, GFile* file) {
#line 156 "rygel-folder-container.vala"
	return rygel_folder_container_construct (RYGEL_TYPE_FOLDER_CONTAINER, parent, file);
#line 413 "rygel-folder-container.c"
}


static void rygel_folder_container_class_init (RygelFolderContainerClass * klass) {
	rygel_folder_container_parent_class = g_type_class_peek_parent (klass);
	g_type_class_add_private (klass, sizeof (RygelFolderContainerPrivate));
	RYGEL_MEDIA_CONTAINER_CLASS (klass)->get_children = rygel_folder_container_real_get_children;
	RYGEL_MEDIA_CONTAINER_CLASS (klass)->get_children_finish = rygel_folder_container_real_get_children_finish;
	RYGEL_MEDIA_CONTAINER_CLASS (klass)->find_object = rygel_folder_container_real_find_object;
	RYGEL_MEDIA_CONTAINER_CLASS (klass)->find_object_finish = rygel_folder_container_real_find_object_finish;
	G_OBJECT_CLASS (klass)->finalize = rygel_folder_container_finalize;
}


static void rygel_folder_container_instance_init (RygelFolderContainer * self) {
	self->priv = RYGEL_FOLDER_CONTAINER_GET_PRIVATE (self);
}


static void rygel_folder_container_finalize (GObject* obj) {
	RygelFolderContainer * self;
	self = RYGEL_FOLDER_CONTAINER (obj);
	(self->priv->items == NULL) ? NULL : (self->priv->items = (g_object_unref (self->priv->items), NULL));
	(self->priv->root_dir == NULL) ? NULL : (self->priv->root_dir = (g_object_unref (self->priv->root_dir), NULL));
	(self->priv->results == NULL) ? NULL : (self->priv->results = (g_object_unref (self->priv->results), NULL));
	G_OBJECT_CLASS (rygel_folder_container_parent_class)->finalize (obj);
}


GType rygel_folder_container_get_type (void) {
	static GType rygel_folder_container_type_id = 0;
	if (rygel_folder_container_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (RygelFolderContainerClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) rygel_folder_container_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (RygelFolderContainer), 0, (GInstanceInitFunc) rygel_folder_container_instance_init, NULL };
		rygel_folder_container_type_id = g_type_register_static (RYGEL_TYPE_MEDIA_CONTAINER, "RygelFolderContainer", &g_define_type_info, 0);
	}
	return rygel_folder_container_type_id;
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




