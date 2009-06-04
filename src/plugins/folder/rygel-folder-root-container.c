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
#include <gee/list.h>
#include <gio/gio.h>
#include <stdlib.h>
#include <string.h>
#include <gee/iterable.h>
#include <gee/iterator.h>
#include <gee/collection.h>


#define RYGEL_TYPE_FOLDER_ROOT_CONTAINER (rygel_folder_root_container_get_type ())
#define RYGEL_FOLDER_ROOT_CONTAINER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_FOLDER_ROOT_CONTAINER, RygelFolderRootContainer))
#define RYGEL_FOLDER_ROOT_CONTAINER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_FOLDER_ROOT_CONTAINER, RygelFolderRootContainerClass))
#define RYGEL_IS_FOLDER_ROOT_CONTAINER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_FOLDER_ROOT_CONTAINER))
#define RYGEL_IS_FOLDER_ROOT_CONTAINER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_FOLDER_ROOT_CONTAINER))
#define RYGEL_FOLDER_ROOT_CONTAINER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_FOLDER_ROOT_CONTAINER, RygelFolderRootContainerClass))

typedef struct _RygelFolderRootContainer RygelFolderRootContainer;
typedef struct _RygelFolderRootContainerClass RygelFolderRootContainerClass;
typedef struct _RygelFolderRootContainerPrivate RygelFolderRootContainerPrivate;

#define RYGEL_TYPE_FOLDER_CONTAINER (rygel_folder_container_get_type ())
#define RYGEL_FOLDER_CONTAINER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_FOLDER_CONTAINER, RygelFolderContainer))
#define RYGEL_FOLDER_CONTAINER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_FOLDER_CONTAINER, RygelFolderContainerClass))
#define RYGEL_IS_FOLDER_CONTAINER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_FOLDER_CONTAINER))
#define RYGEL_IS_FOLDER_CONTAINER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_FOLDER_CONTAINER))
#define RYGEL_FOLDER_CONTAINER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_FOLDER_CONTAINER, RygelFolderContainerClass))

typedef struct _RygelFolderContainer RygelFolderContainer;
typedef struct _RygelFolderContainerClass RygelFolderContainerClass;

/**
 * MediaContainer which exposes the contents of a directory 
 * as items
 */
struct _RygelFolderRootContainer {
	RygelMediaContainer parent_instance;
	RygelFolderRootContainerPrivate * priv;
};

struct _RygelFolderRootContainerClass {
	RygelMediaContainerClass parent_class;
};

struct _RygelFolderRootContainerPrivate {
	GeeArrayList* items;
};



GType rygel_folder_root_container_get_type (void);
GType rygel_folder_container_get_type (void);
#define RYGEL_FOLDER_ROOT_CONTAINER_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), RYGEL_TYPE_FOLDER_ROOT_CONTAINER, RygelFolderRootContainerPrivate))
enum  {
	RYGEL_FOLDER_ROOT_CONTAINER_DUMMY_PROPERTY
};
static void rygel_folder_root_container_real_get_children (RygelMediaContainer* base, guint offset, guint max_count, GCancellable* cancellable, GAsyncReadyCallback callback, void* callback_target);
static GeeList* rygel_folder_root_container_real_get_children_finish (RygelMediaContainer* base, GAsyncResult* res, GError** error);
static void rygel_folder_root_container_real_find_object (RygelMediaContainer* base, const char* id, GCancellable* cancellable, GAsyncReadyCallback callback, void* callback_target);
RygelMediaObject* rygel_folder_container_find_object_sync (RygelFolderContainer* self, const char* id);
static RygelMediaObject* rygel_folder_root_container_real_find_object_finish (RygelMediaContainer* base, GAsyncResult* res, GError** error);
RygelFolderContainer* rygel_folder_container_new (RygelMediaContainer* parent, GFile* file);
RygelFolderContainer* rygel_folder_container_construct (GType object_type, RygelMediaContainer* parent, GFile* file);
RygelFolderRootContainer* rygel_folder_root_container_new (void);
RygelFolderRootContainer* rygel_folder_root_container_construct (GType object_type);
RygelFolderRootContainer* rygel_folder_root_container_new (void);
static gpointer rygel_folder_root_container_parent_class = NULL;
static void rygel_folder_root_container_finalize (GObject* obj);
static int _vala_strcmp0 (const char * str1, const char * str2);



#line 33 "rygel-folder-root-container.vala"
static void rygel_folder_root_container_real_get_children (RygelMediaContainer* base, guint offset, guint max_count, GCancellable* cancellable, GAsyncReadyCallback callback, void* callback_target) {
#line 99 "rygel-folder-root-container.c"
	RygelFolderRootContainer * self;
	guint stop;
	GeeList* children;
	RygelSimpleAsyncResult* res;
	GeeList* _tmp1_;
	GeeList* _tmp0_;
	self = (RygelFolderRootContainer*) base;
	stop = offset + max_count;
#line 39 "rygel-folder-root-container.vala"
	stop = CLAMP (stop, (guint) 0, ((RygelMediaContainer*) self)->child_count);
#line 110 "rygel-folder-root-container.c"
	children = gee_list_slice ((GeeList*) self->priv->items, (gint) offset, (gint) stop);
	res = rygel_simple_async_result_new (GEE_TYPE_LIST, (GBoxedCopyFunc) g_object_ref, g_object_unref, (GObject*) self, callback, callback_target);
	_tmp1_ = NULL;
#line 43 "rygel-folder-root-container.vala"
	_tmp0_ = NULL;
#line 43 "rygel-folder-root-container.vala"
	res->data = (_tmp1_ = (_tmp0_ = children, (_tmp0_ == NULL) ? NULL : g_object_ref (_tmp0_)), (res->data == NULL) ? NULL : (res->data = (g_object_unref (res->data), NULL)), _tmp1_);
#line 44 "rygel-folder-root-container.vala"
	rygel_simple_async_result_complete_in_idle (res);
#line 120 "rygel-folder-root-container.c"
	(children == NULL) ? NULL : (children = (g_object_unref (children), NULL));
	(res == NULL) ? NULL : (res = (g_object_unref (res), NULL));
}


#line 47 "rygel-folder-root-container.vala"
static GeeList* rygel_folder_root_container_real_get_children_finish (RygelMediaContainer* base, GAsyncResult* res, GError** error) {
#line 128 "rygel-folder-root-container.c"
	RygelFolderRootContainer * self;
	RygelSimpleAsyncResult* _tmp0_;
	RygelSimpleAsyncResult* simple_res;
	GeeList* _tmp1_;
	GeeList* _tmp2_;
	self = (RygelFolderRootContainer*) base;
#line 47 "rygel-folder-root-container.vala"
	g_return_val_if_fail (res != NULL, NULL);
#line 50 "rygel-folder-root-container.vala"
	_tmp0_ = NULL;
#line 139 "rygel-folder-root-container.c"
	simple_res = (_tmp0_ = RYGEL_SIMPLE_ASYNC_RESULT (res), (_tmp0_ == NULL) ? NULL : g_object_ref (_tmp0_));
#line 52 "rygel-folder-root-container.vala"
	_tmp1_ = NULL;
#line 52 "rygel-folder-root-container.vala"
	_tmp2_ = NULL;
#line 52 "rygel-folder-root-container.vala"
	return (_tmp2_ = (_tmp1_ = (GeeList*) simple_res->data, (_tmp1_ == NULL) ? NULL : g_object_ref (_tmp1_)), (simple_res == NULL) ? NULL : (simple_res = (g_object_unref (simple_res), NULL)), _tmp2_);
#line 147 "rygel-folder-root-container.c"
}


#line 55 "rygel-folder-root-container.vala"
static void rygel_folder_root_container_real_find_object (RygelMediaContainer* base, const char* id, GCancellable* cancellable, GAsyncReadyCallback callback, void* callback_target) {
#line 153 "rygel-folder-root-container.c"
	RygelFolderRootContainer * self;
	RygelSimpleAsyncResult* res;
	char* _tmp1_;
	const char* _tmp0_;
	self = (RygelFolderRootContainer*) base;
#line 55 "rygel-folder-root-container.vala"
	g_return_if_fail (id != NULL);
#line 161 "rygel-folder-root-container.c"
	res = rygel_simple_async_result_new (G_TYPE_STRING, (GBoxedCopyFunc) g_strdup, g_free, (GObject*) self, callback, callback_target);
	_tmp1_ = NULL;
#line 60 "rygel-folder-root-container.vala"
	_tmp0_ = NULL;
#line 60 "rygel-folder-root-container.vala"
	res->data = (_tmp1_ = (_tmp0_ = id, (_tmp0_ == NULL) ? NULL : g_strdup (_tmp0_)), res->data = (g_free (res->data), NULL), _tmp1_);
#line 61 "rygel-folder-root-container.vala"
	rygel_simple_async_result_complete_in_idle (res);
#line 170 "rygel-folder-root-container.c"
	(res == NULL) ? NULL : (res = (g_object_unref (res), NULL));
}


#line 64 "rygel-folder-root-container.vala"
static RygelMediaObject* rygel_folder_root_container_real_find_object_finish (RygelMediaContainer* base, GAsyncResult* res, GError** error) {
#line 177 "rygel-folder-root-container.c"
	RygelFolderRootContainer * self;
	RygelMediaObject* item;
	const char* _tmp0_;
	char* id;
	RygelMediaObject* _tmp5_;
	self = (RygelFolderRootContainer*) base;
#line 64 "rygel-folder-root-container.vala"
	g_return_val_if_fail (res != NULL, NULL);
#line 186 "rygel-folder-root-container.c"
	item = NULL;
#line 67 "rygel-folder-root-container.vala"
	_tmp0_ = NULL;
#line 190 "rygel-folder-root-container.c"
	id = (_tmp0_ = (const char*) RYGEL_SIMPLE_ASYNC_RESULT (res)->data, (_tmp0_ == NULL) ? NULL : g_strdup (_tmp0_));
	{
		GeeIterator* _tmp_it;
		_tmp_it = gee_iterable_iterator ((GeeIterable*) self->priv->items);
#line 69 "rygel-folder-root-container.vala"
		while (gee_iterator_next (_tmp_it)) {
#line 197 "rygel-folder-root-container.c"
			RygelFolderContainer* tmp;
			tmp = (RygelFolderContainer*) gee_iterator_get (_tmp_it);
#line 70 "rygel-folder-root-container.vala"
			if (_vala_strcmp0 (id, ((RygelMediaObject*) tmp)->id) == 0) {
#line 202 "rygel-folder-root-container.c"
				RygelMediaObject* _tmp2_;
				RygelMediaObject* _tmp1_;
				_tmp2_ = NULL;
#line 71 "rygel-folder-root-container.vala"
				_tmp1_ = NULL;
#line 71 "rygel-folder-root-container.vala"
				item = (_tmp2_ = (_tmp1_ = (RygelMediaObject*) tmp, (_tmp1_ == NULL) ? NULL : g_object_ref (_tmp1_)), (item == NULL) ? NULL : (item = (g_object_unref (item), NULL)), _tmp2_);
#line 210 "rygel-folder-root-container.c"
				(tmp == NULL) ? NULL : (tmp = (g_object_unref (tmp), NULL));
#line 72 "rygel-folder-root-container.vala"
				break;
#line 214 "rygel-folder-root-container.c"
			}
			(tmp == NULL) ? NULL : (tmp = (g_object_unref (tmp), NULL));
		}
		(_tmp_it == NULL) ? NULL : (_tmp_it = (g_object_unref (_tmp_it), NULL));
	}
#line 76 "rygel-folder-root-container.vala"
	if (item == NULL) {
#line 222 "rygel-folder-root-container.c"
		{
			GeeIterator* _tmp_it;
			_tmp_it = gee_iterable_iterator ((GeeIterable*) self->priv->items);
#line 77 "rygel-folder-root-container.vala"
			while (gee_iterator_next (_tmp_it)) {
#line 228 "rygel-folder-root-container.c"
				RygelFolderContainer* tmp;
				tmp = (RygelFolderContainer*) gee_iterator_get (_tmp_it);
#line 78 "rygel-folder-root-container.vala"
				if (RYGEL_IS_FOLDER_CONTAINER (tmp)) {
#line 233 "rygel-folder-root-container.c"
					RygelFolderContainer* _tmp3_;
					RygelFolderContainer* folder;
					RygelMediaObject* _tmp4_;
#line 79 "rygel-folder-root-container.vala"
					_tmp3_ = NULL;
#line 239 "rygel-folder-root-container.c"
					folder = (_tmp3_ = RYGEL_FOLDER_CONTAINER (tmp), (_tmp3_ == NULL) ? NULL : g_object_ref (_tmp3_));
					_tmp4_ = NULL;
#line 80 "rygel-folder-root-container.vala"
					item = (_tmp4_ = rygel_folder_container_find_object_sync (folder, id), (item == NULL) ? NULL : (item = (g_object_unref (item), NULL)), _tmp4_);
#line 81 "rygel-folder-root-container.vala"
					if (item != NULL) {
#line 246 "rygel-folder-root-container.c"
						(folder == NULL) ? NULL : (folder = (g_object_unref (folder), NULL));
						(tmp == NULL) ? NULL : (tmp = (g_object_unref (tmp), NULL));
#line 82 "rygel-folder-root-container.vala"
						break;
#line 251 "rygel-folder-root-container.c"
					}
					(folder == NULL) ? NULL : (folder = (g_object_unref (folder), NULL));
				}
				(tmp == NULL) ? NULL : (tmp = (g_object_unref (tmp), NULL));
			}
			(_tmp_it == NULL) ? NULL : (_tmp_it = (g_object_unref (_tmp_it), NULL));
		}
	}
#line 88 "rygel-folder-root-container.vala"
	_tmp5_ = NULL;
#line 88 "rygel-folder-root-container.vala"
	return (_tmp5_ = item, id = (g_free (id), NULL), _tmp5_);
#line 264 "rygel-folder-root-container.c"
}


/**
     * Create a new root container.
     */
#line 94 "rygel-folder-root-container.vala"
RygelFolderRootContainer* rygel_folder_root_container_construct (GType object_type) {
#line 273 "rygel-folder-root-container.c"
	RygelFolderRootContainer * self;
	GeeArrayList* _tmp0_;
	RygelConfiguration* config;
	GeeArrayList* dirs;
#line 95 "rygel-folder-root-container.vala"
	self = (RygelFolderRootContainer*) rygel_media_container_construct_root (object_type, "FolderRoot", (guint) 0);
#line 280 "rygel-folder-root-container.c"
	_tmp0_ = NULL;
#line 97 "rygel-folder-root-container.vala"
	self->priv->items = (_tmp0_ = gee_array_list_new (RYGEL_TYPE_FOLDER_CONTAINER, (GBoxedCopyFunc) g_object_ref, g_object_unref, g_direct_equal), (self->priv->items == NULL) ? NULL : (self->priv->items = (g_object_unref (self->priv->items), NULL)), _tmp0_);
#line 284 "rygel-folder-root-container.c"
	config = rygel_configuration_get_default ();
	dirs = rygel_configuration_get_string_list (config, "Folder", "folders");
#line 103 "rygel-folder-root-container.vala"
	if (gee_collection_get_size ((GeeCollection*) dirs) == 0) {
#line 289 "rygel-folder-root-container.c"
		const char* _tmp1_;
		char* dir;
		char* _tmp3_;
		const char* _tmp2_;
		char* _tmp5_;
		const char* _tmp4_;
#line 104 "rygel-folder-root-container.vala"
		_tmp1_ = NULL;
#line 298 "rygel-folder-root-container.c"
		dir = (_tmp1_ = g_get_user_special_dir (G_USER_DIRECTORY_MUSIC), (_tmp1_ == NULL) ? NULL : g_strdup (_tmp1_));
#line 105 "rygel-folder-root-container.vala"
		if (dir != NULL) {
#line 106 "rygel-folder-root-container.vala"
			gee_collection_add ((GeeCollection*) dirs, dir);
#line 304 "rygel-folder-root-container.c"
		}
		_tmp3_ = NULL;
#line 108 "rygel-folder-root-container.vala"
		_tmp2_ = NULL;
#line 108 "rygel-folder-root-container.vala"
		dir = (_tmp3_ = (_tmp2_ = g_get_user_special_dir (G_USER_DIRECTORY_PICTURES), (_tmp2_ == NULL) ? NULL : g_strdup (_tmp2_)), dir = (g_free (dir), NULL), _tmp3_);
#line 109 "rygel-folder-root-container.vala"
		if (dir != NULL) {
#line 110 "rygel-folder-root-container.vala"
			gee_collection_add ((GeeCollection*) dirs, dir);
#line 315 "rygel-folder-root-container.c"
		}
		_tmp5_ = NULL;
#line 112 "rygel-folder-root-container.vala"
		_tmp4_ = NULL;
#line 112 "rygel-folder-root-container.vala"
		dir = (_tmp5_ = (_tmp4_ = g_get_user_special_dir (G_USER_DIRECTORY_VIDEOS), (_tmp4_ == NULL) ? NULL : g_strdup (_tmp4_)), dir = (g_free (dir), NULL), _tmp5_);
#line 113 "rygel-folder-root-container.vala"
		if (dir != NULL) {
#line 114 "rygel-folder-root-container.vala"
			gee_collection_add ((GeeCollection*) dirs, dir);
#line 326 "rygel-folder-root-container.c"
		}
		dir = (g_free (dir), NULL);
	}
	{
		GeeIterator* _dir_it;
		_dir_it = gee_iterable_iterator ((GeeIterable*) dirs);
#line 117 "rygel-folder-root-container.vala"
		while (gee_iterator_next (_dir_it)) {
#line 335 "rygel-folder-root-container.c"
			char* dir;
			GFile* f;
			dir = (char*) gee_iterator_get (_dir_it);
			f = g_file_new_for_commandline_arg (dir);
#line 119 "rygel-folder-root-container.vala"
			if (g_file_query_exists (f, NULL)) {
#line 342 "rygel-folder-root-container.c"
				RygelFolderContainer* _tmp6_;
				_tmp6_ = NULL;
#line 120 "rygel-folder-root-container.vala"
				gee_collection_add ((GeeCollection*) self->priv->items, _tmp6_ = rygel_folder_container_new ((RygelMediaContainer*) self, f));
#line 347 "rygel-folder-root-container.c"
				(_tmp6_ == NULL) ? NULL : (_tmp6_ = (g_object_unref (_tmp6_), NULL));
			}
			dir = (g_free (dir), NULL);
			(f == NULL) ? NULL : (f = (g_object_unref (f), NULL));
		}
		(_dir_it == NULL) ? NULL : (_dir_it = (g_object_unref (_dir_it), NULL));
	}
#line 124 "rygel-folder-root-container.vala"
	((RygelMediaContainer*) self)->child_count = (guint) gee_collection_get_size ((GeeCollection*) self->priv->items);
#line 357 "rygel-folder-root-container.c"
	(config == NULL) ? NULL : (config = (g_object_unref (config), NULL));
	(dirs == NULL) ? NULL : (dirs = (g_object_unref (dirs), NULL));
	return self;
}


#line 94 "rygel-folder-root-container.vala"
RygelFolderRootContainer* rygel_folder_root_container_new (void) {
#line 94 "rygel-folder-root-container.vala"
	return rygel_folder_root_container_construct (RYGEL_TYPE_FOLDER_ROOT_CONTAINER);
#line 368 "rygel-folder-root-container.c"
}


static void rygel_folder_root_container_class_init (RygelFolderRootContainerClass * klass) {
	rygel_folder_root_container_parent_class = g_type_class_peek_parent (klass);
	g_type_class_add_private (klass, sizeof (RygelFolderRootContainerPrivate));
	RYGEL_MEDIA_CONTAINER_CLASS (klass)->get_children = rygel_folder_root_container_real_get_children;
	RYGEL_MEDIA_CONTAINER_CLASS (klass)->get_children_finish = rygel_folder_root_container_real_get_children_finish;
	RYGEL_MEDIA_CONTAINER_CLASS (klass)->find_object = rygel_folder_root_container_real_find_object;
	RYGEL_MEDIA_CONTAINER_CLASS (klass)->find_object_finish = rygel_folder_root_container_real_find_object_finish;
	G_OBJECT_CLASS (klass)->finalize = rygel_folder_root_container_finalize;
}


static void rygel_folder_root_container_instance_init (RygelFolderRootContainer * self) {
	self->priv = RYGEL_FOLDER_ROOT_CONTAINER_GET_PRIVATE (self);
}


static void rygel_folder_root_container_finalize (GObject* obj) {
	RygelFolderRootContainer * self;
	self = RYGEL_FOLDER_ROOT_CONTAINER (obj);
	(self->priv->items == NULL) ? NULL : (self->priv->items = (g_object_unref (self->priv->items), NULL));
	G_OBJECT_CLASS (rygel_folder_root_container_parent_class)->finalize (obj);
}


GType rygel_folder_root_container_get_type (void) {
	static GType rygel_folder_root_container_type_id = 0;
	if (rygel_folder_root_container_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (RygelFolderRootContainerClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) rygel_folder_root_container_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (RygelFolderRootContainer), 0, (GInstanceInitFunc) rygel_folder_root_container_instance_init, NULL };
		rygel_folder_root_container_type_id = g_type_register_static (RYGEL_TYPE_MEDIA_CONTAINER, "RygelFolderRootContainer", &g_define_type_info, 0);
	}
	return rygel_folder_root_container_type_id;
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




