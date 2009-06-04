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
#include <gee/arraylist.h>
#include <gee/collection.h>
#include <stdlib.h>
#include <string.h>
#include <gee/list.h>
#include <gio/gio.h>
#include <gee/iterable.h>
#include <gee/iterator.h>


#define RYGEL_TYPE_TRACKER_ROOT_CONTAINER (rygel_tracker_root_container_get_type ())
#define RYGEL_TRACKER_ROOT_CONTAINER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_TRACKER_ROOT_CONTAINER, RygelTrackerRootContainer))
#define RYGEL_TRACKER_ROOT_CONTAINER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_TRACKER_ROOT_CONTAINER, RygelTrackerRootContainerClass))
#define RYGEL_IS_TRACKER_ROOT_CONTAINER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_TRACKER_ROOT_CONTAINER))
#define RYGEL_IS_TRACKER_ROOT_CONTAINER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_TRACKER_ROOT_CONTAINER))
#define RYGEL_TRACKER_ROOT_CONTAINER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_TRACKER_ROOT_CONTAINER, RygelTrackerRootContainerClass))

typedef struct _RygelTrackerRootContainer RygelTrackerRootContainer;
typedef struct _RygelTrackerRootContainerClass RygelTrackerRootContainerClass;
typedef struct _RygelTrackerRootContainerPrivate RygelTrackerRootContainerPrivate;

#define RYGEL_TYPE_TRACKER_CATEGORY (rygel_tracker_category_get_type ())
#define RYGEL_TRACKER_CATEGORY(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_TRACKER_CATEGORY, RygelTrackerCategory))
#define RYGEL_TRACKER_CATEGORY_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_TRACKER_CATEGORY, RygelTrackerCategoryClass))
#define RYGEL_IS_TRACKER_CATEGORY(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_TRACKER_CATEGORY))
#define RYGEL_IS_TRACKER_CATEGORY_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_TRACKER_CATEGORY))
#define RYGEL_TRACKER_CATEGORY_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_TRACKER_CATEGORY, RygelTrackerCategoryClass))

typedef struct _RygelTrackerCategory RygelTrackerCategory;
typedef struct _RygelTrackerCategoryClass RygelTrackerCategoryClass;

#define RYGEL_TYPE_TRACKER_IMAGE_CATEGORY (rygel_tracker_image_category_get_type ())
#define RYGEL_TRACKER_IMAGE_CATEGORY(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_TRACKER_IMAGE_CATEGORY, RygelTrackerImageCategory))
#define RYGEL_TRACKER_IMAGE_CATEGORY_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_TRACKER_IMAGE_CATEGORY, RygelTrackerImageCategoryClass))
#define RYGEL_IS_TRACKER_IMAGE_CATEGORY(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_TRACKER_IMAGE_CATEGORY))
#define RYGEL_IS_TRACKER_IMAGE_CATEGORY_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_TRACKER_IMAGE_CATEGORY))
#define RYGEL_TRACKER_IMAGE_CATEGORY_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_TRACKER_IMAGE_CATEGORY, RygelTrackerImageCategoryClass))

typedef struct _RygelTrackerImageCategory RygelTrackerImageCategory;
typedef struct _RygelTrackerImageCategoryClass RygelTrackerImageCategoryClass;

#define RYGEL_TYPE_TRACKER_MUSIC_CATEGORY (rygel_tracker_music_category_get_type ())
#define RYGEL_TRACKER_MUSIC_CATEGORY(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_TRACKER_MUSIC_CATEGORY, RygelTrackerMusicCategory))
#define RYGEL_TRACKER_MUSIC_CATEGORY_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_TRACKER_MUSIC_CATEGORY, RygelTrackerMusicCategoryClass))
#define RYGEL_IS_TRACKER_MUSIC_CATEGORY(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_TRACKER_MUSIC_CATEGORY))
#define RYGEL_IS_TRACKER_MUSIC_CATEGORY_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_TRACKER_MUSIC_CATEGORY))
#define RYGEL_TRACKER_MUSIC_CATEGORY_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_TRACKER_MUSIC_CATEGORY, RygelTrackerMusicCategoryClass))

typedef struct _RygelTrackerMusicCategory RygelTrackerMusicCategory;
typedef struct _RygelTrackerMusicCategoryClass RygelTrackerMusicCategoryClass;

#define RYGEL_TYPE_TRACKER_VIDEO_CATEGORY (rygel_tracker_video_category_get_type ())
#define RYGEL_TRACKER_VIDEO_CATEGORY(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_TRACKER_VIDEO_CATEGORY, RygelTrackerVideoCategory))
#define RYGEL_TRACKER_VIDEO_CATEGORY_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_TRACKER_VIDEO_CATEGORY, RygelTrackerVideoCategoryClass))
#define RYGEL_IS_TRACKER_VIDEO_CATEGORY(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_TRACKER_VIDEO_CATEGORY))
#define RYGEL_IS_TRACKER_VIDEO_CATEGORY_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_TRACKER_VIDEO_CATEGORY))
#define RYGEL_TRACKER_VIDEO_CATEGORY_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_TRACKER_VIDEO_CATEGORY, RygelTrackerVideoCategoryClass))

typedef struct _RygelTrackerVideoCategory RygelTrackerVideoCategory;
typedef struct _RygelTrackerVideoCategoryClass RygelTrackerVideoCategoryClass;

/**
 * Represents the root container for Tracker media content hierarchy.
 */
struct _RygelTrackerRootContainer {
	RygelMediaContainer parent_instance;
	RygelTrackerRootContainerPrivate * priv;
};

struct _RygelTrackerRootContainerClass {
	RygelMediaContainerClass parent_class;
};

struct _RygelTrackerRootContainerPrivate {
	GeeArrayList* categories;
};



GType rygel_tracker_root_container_get_type (void);
GType rygel_tracker_category_get_type (void);
#define RYGEL_TRACKER_ROOT_CONTAINER_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), RYGEL_TYPE_TRACKER_ROOT_CONTAINER, RygelTrackerRootContainerPrivate))
enum  {
	RYGEL_TRACKER_ROOT_CONTAINER_DUMMY_PROPERTY
};
RygelTrackerImageCategory* rygel_tracker_image_category_new (const char* id, RygelMediaContainer* parent, const char* title);
RygelTrackerImageCategory* rygel_tracker_image_category_construct (GType object_type, const char* id, RygelMediaContainer* parent, const char* title);
GType rygel_tracker_image_category_get_type (void);
RygelTrackerMusicCategory* rygel_tracker_music_category_new (const char* id, RygelMediaContainer* parent, const char* title);
RygelTrackerMusicCategory* rygel_tracker_music_category_construct (GType object_type, const char* id, RygelMediaContainer* parent, const char* title);
GType rygel_tracker_music_category_get_type (void);
RygelTrackerVideoCategory* rygel_tracker_video_category_new (const char* id, RygelMediaContainer* parent, const char* title);
RygelTrackerVideoCategory* rygel_tracker_video_category_construct (GType object_type, const char* id, RygelMediaContainer* parent, const char* title);
GType rygel_tracker_video_category_get_type (void);
RygelTrackerRootContainer* rygel_tracker_root_container_new (const char* title);
RygelTrackerRootContainer* rygel_tracker_root_container_construct (GType object_type, const char* title);
RygelTrackerRootContainer* rygel_tracker_root_container_new (const char* title);
static void rygel_tracker_root_container_real_get_children (RygelMediaContainer* base, guint offset, guint max_count, GCancellable* cancellable, GAsyncReadyCallback callback, void* callback_target);
static GeeList* rygel_tracker_root_container_real_get_children_finish (RygelMediaContainer* base, GAsyncResult* res, GError** error);
static RygelTrackerCategory* rygel_tracker_root_container_find_category_by_id (RygelTrackerRootContainer* self, const char* category_id);
static RygelTrackerCategory* rygel_tracker_root_container_get_item_category (RygelTrackerRootContainer* self, const char* item_id);
static void rygel_tracker_root_container_real_find_object (RygelMediaContainer* base, const char* id, GCancellable* cancellable, GAsyncReadyCallback callback, void* callback_target);
static RygelMediaObject* rygel_tracker_root_container_real_find_object_finish (RygelMediaContainer* base, GAsyncResult* res, GError** error);
gboolean rygel_tracker_category_is_thy_child (RygelTrackerCategory* self, const char* item_id);
static gpointer rygel_tracker_root_container_parent_class = NULL;
static void rygel_tracker_root_container_finalize (GObject* obj);
static int _vala_strcmp0 (const char * str1, const char * str2);



RygelTrackerRootContainer* rygel_tracker_root_container_construct (GType object_type, const char* title) {
	RygelTrackerRootContainer * self;
	GeeArrayList* _tmp0_;
	RygelTrackerImageCategory* _tmp1_;
	RygelTrackerMusicCategory* _tmp2_;
	RygelTrackerVideoCategory* _tmp3_;
	g_return_val_if_fail (title != NULL, NULL);
	self = (RygelTrackerRootContainer*) rygel_media_container_construct_root (object_type, title, (guint) 0);
	_tmp0_ = NULL;
	self->priv->categories = (_tmp0_ = gee_array_list_new (RYGEL_TYPE_TRACKER_CATEGORY, (GBoxedCopyFunc) g_object_ref, g_object_unref, g_direct_equal), (self->priv->categories == NULL) ? NULL : (self->priv->categories = (g_object_unref (self->priv->categories), NULL)), _tmp0_);
	_tmp1_ = NULL;
	gee_collection_add ((GeeCollection*) self->priv->categories, (RygelTrackerCategory*) (_tmp1_ = rygel_tracker_image_category_new ("16", (RygelMediaContainer*) self, "All Images")));
	(_tmp1_ == NULL) ? NULL : (_tmp1_ = (g_object_unref (_tmp1_), NULL));
	_tmp2_ = NULL;
	gee_collection_add ((GeeCollection*) self->priv->categories, (RygelTrackerCategory*) (_tmp2_ = rygel_tracker_music_category_new ("14", (RygelMediaContainer*) self, "All Music")));
	(_tmp2_ == NULL) ? NULL : (_tmp2_ = (g_object_unref (_tmp2_), NULL));
	_tmp3_ = NULL;
	gee_collection_add ((GeeCollection*) self->priv->categories, (RygelTrackerCategory*) (_tmp3_ = rygel_tracker_video_category_new ("15", (RygelMediaContainer*) self, "All Videos")));
	(_tmp3_ == NULL) ? NULL : (_tmp3_ = (g_object_unref (_tmp3_), NULL));
	((RygelMediaContainer*) self)->child_count = (guint) gee_collection_get_size ((GeeCollection*) self->priv->categories);
	return self;
}


RygelTrackerRootContainer* rygel_tracker_root_container_new (const char* title) {
	return rygel_tracker_root_container_construct (RYGEL_TYPE_TRACKER_ROOT_CONTAINER, title);
}


static void rygel_tracker_root_container_real_get_children (RygelMediaContainer* base, guint offset, guint max_count, GCancellable* cancellable, GAsyncReadyCallback callback, void* callback_target) {
	RygelTrackerRootContainer * self;
	guint stop;
	GeeList* children;
	RygelSimpleAsyncResult* res;
	GeeList* _tmp1_;
	GeeList* _tmp0_;
	self = (RygelTrackerRootContainer*) base;
	stop = offset + max_count;
	stop = CLAMP (stop, (guint) 0, ((RygelMediaContainer*) self)->child_count);
	children = gee_list_slice ((GeeList*) self->priv->categories, (gint) offset, (gint) stop);
	res = rygel_simple_async_result_new (GEE_TYPE_LIST, (GBoxedCopyFunc) g_object_ref, g_object_unref, (GObject*) self, callback, callback_target);
	_tmp1_ = NULL;
	_tmp0_ = NULL;
	res->data = (_tmp1_ = (_tmp0_ = children, (_tmp0_ == NULL) ? NULL : g_object_ref (_tmp0_)), (res->data == NULL) ? NULL : (res->data = (g_object_unref (res->data), NULL)), _tmp1_);
	rygel_simple_async_result_complete_in_idle (res);
	(children == NULL) ? NULL : (children = (g_object_unref (children), NULL));
	(res == NULL) ? NULL : (res = (g_object_unref (res), NULL));
}


static GeeList* rygel_tracker_root_container_real_get_children_finish (RygelMediaContainer* base, GAsyncResult* res, GError** error) {
	RygelTrackerRootContainer * self;
	RygelSimpleAsyncResult* _tmp0_;
	RygelSimpleAsyncResult* simple_res;
	GeeList* _tmp1_;
	GeeList* _tmp2_;
	self = (RygelTrackerRootContainer*) base;
	g_return_val_if_fail (res != NULL, NULL);
	_tmp0_ = NULL;
	simple_res = (_tmp0_ = RYGEL_SIMPLE_ASYNC_RESULT (res), (_tmp0_ == NULL) ? NULL : g_object_ref (_tmp0_));
	_tmp1_ = NULL;
	_tmp2_ = NULL;
	return (_tmp2_ = (_tmp1_ = (GeeList*) simple_res->data, (_tmp1_ == NULL) ? NULL : g_object_ref (_tmp1_)), (simple_res == NULL) ? NULL : (simple_res = (g_object_unref (simple_res), NULL)), _tmp2_);
}


static void rygel_tracker_root_container_real_find_object (RygelMediaContainer* base, const char* id, GCancellable* cancellable, GAsyncReadyCallback callback, void* callback_target) {
	RygelTrackerRootContainer * self;
	RygelMediaObject* media_object;
	RygelSimpleAsyncResult* res;
	RygelMediaObject* _tmp1_;
	RygelMediaObject* _tmp0_;
	self = (RygelTrackerRootContainer*) base;
	g_return_if_fail (id != NULL);
	/* First try containers */
	media_object = (RygelMediaObject*) rygel_tracker_root_container_find_category_by_id (self, id);
	if (media_object == NULL) {
		RygelTrackerCategory* category;
		/* Now try items */
		category = rygel_tracker_root_container_get_item_category (self, id);
		if (category != NULL) {
			rygel_media_container_find_object ((RygelMediaContainer*) category, id, cancellable, callback, callback_target);
			(category == NULL) ? NULL : (category = (g_object_unref (category), NULL));
			(media_object == NULL) ? NULL : (media_object = (g_object_unref (media_object), NULL));
			return;
		}
		(category == NULL) ? NULL : (category = (g_object_unref (category), NULL));
	}
	res = rygel_simple_async_result_new (RYGEL_TYPE_MEDIA_OBJECT, (GBoxedCopyFunc) g_object_ref, g_object_unref, (GObject*) self, callback, callback_target);
	_tmp1_ = NULL;
	_tmp0_ = NULL;
	res->data = (_tmp1_ = (_tmp0_ = media_object, (_tmp0_ == NULL) ? NULL : g_object_ref (_tmp0_)), (res->data == NULL) ? NULL : (res->data = (g_object_unref (res->data), NULL)), _tmp1_);
	rygel_simple_async_result_complete_in_idle (res);
	(media_object == NULL) ? NULL : (media_object = (g_object_unref (media_object), NULL));
	(res == NULL) ? NULL : (res = (g_object_unref (res), NULL));
}


static RygelMediaObject* rygel_tracker_root_container_real_find_object_finish (RygelMediaContainer* base, GAsyncResult* res, GError** error) {
	RygelTrackerRootContainer * self;
	RygelSimpleAsyncResult* _tmp0_;
	RygelSimpleAsyncResult* simple_res;
	RygelMediaObject* _tmp1_;
	RygelMediaObject* _tmp2_;
	self = (RygelTrackerRootContainer*) base;
	g_return_val_if_fail (res != NULL, NULL);
	_tmp0_ = NULL;
	simple_res = (_tmp0_ = RYGEL_SIMPLE_ASYNC_RESULT (res), (_tmp0_ == NULL) ? NULL : g_object_ref (_tmp0_));
	_tmp1_ = NULL;
	_tmp2_ = NULL;
	return (_tmp2_ = (_tmp1_ = (RygelMediaObject*) simple_res->data, (_tmp1_ == NULL) ? NULL : g_object_ref (_tmp1_)), (simple_res == NULL) ? NULL : (simple_res = (g_object_unref (simple_res), NULL)), _tmp2_);
}


/* Private methods */
static RygelTrackerCategory* rygel_tracker_root_container_find_category_by_id (RygelTrackerRootContainer* self, const char* category_id) {
	RygelTrackerCategory* category;
	RygelTrackerCategory* _tmp0_;
	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (category_id != NULL, NULL);
	category = NULL;
	_tmp0_ = NULL;
	category = (_tmp0_ = NULL, (category == NULL) ? NULL : (category = (g_object_unref (category), NULL)), _tmp0_);
	{
		GeeIterator* _tmp_it;
		_tmp_it = gee_iterable_iterator ((GeeIterable*) self->priv->categories);
		while (gee_iterator_next (_tmp_it)) {
			RygelTrackerCategory* tmp;
			tmp = (RygelTrackerCategory*) gee_iterator_get (_tmp_it);
			if (_vala_strcmp0 (category_id, ((RygelMediaObject*) tmp)->id) == 0) {
				RygelTrackerCategory* _tmp2_;
				RygelTrackerCategory* _tmp1_;
				_tmp2_ = NULL;
				_tmp1_ = NULL;
				category = (_tmp2_ = (_tmp1_ = tmp, (_tmp1_ == NULL) ? NULL : g_object_ref (_tmp1_)), (category == NULL) ? NULL : (category = (g_object_unref (category), NULL)), _tmp2_);
				(tmp == NULL) ? NULL : (tmp = (g_object_unref (tmp), NULL));
				break;
			}
			(tmp == NULL) ? NULL : (tmp = (g_object_unref (tmp), NULL));
		}
		(_tmp_it == NULL) ? NULL : (_tmp_it = (g_object_unref (_tmp_it), NULL));
	}
	return category;
}


static RygelTrackerCategory* rygel_tracker_root_container_get_item_category (RygelTrackerRootContainer* self, const char* item_id) {
	RygelTrackerCategory* category;
	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (item_id != NULL, NULL);
	category = NULL;
	{
		GeeIterator* _tmp_it;
		_tmp_it = gee_iterable_iterator ((GeeIterable*) self->priv->categories);
		while (gee_iterator_next (_tmp_it)) {
			RygelTrackerCategory* tmp;
			tmp = (RygelTrackerCategory*) gee_iterator_get (_tmp_it);
			if (rygel_tracker_category_is_thy_child (tmp, item_id)) {
				RygelTrackerCategory* _tmp1_;
				RygelTrackerCategory* _tmp0_;
				_tmp1_ = NULL;
				_tmp0_ = NULL;
				category = (_tmp1_ = (_tmp0_ = tmp, (_tmp0_ == NULL) ? NULL : g_object_ref (_tmp0_)), (category == NULL) ? NULL : (category = (g_object_unref (category), NULL)), _tmp1_);
				(tmp == NULL) ? NULL : (tmp = (g_object_unref (tmp), NULL));
				break;
			}
			(tmp == NULL) ? NULL : (tmp = (g_object_unref (tmp), NULL));
		}
		(_tmp_it == NULL) ? NULL : (_tmp_it = (g_object_unref (_tmp_it), NULL));
	}
	return category;
}


static void rygel_tracker_root_container_class_init (RygelTrackerRootContainerClass * klass) {
	rygel_tracker_root_container_parent_class = g_type_class_peek_parent (klass);
	g_type_class_add_private (klass, sizeof (RygelTrackerRootContainerPrivate));
	RYGEL_MEDIA_CONTAINER_CLASS (klass)->get_children = rygel_tracker_root_container_real_get_children;
	RYGEL_MEDIA_CONTAINER_CLASS (klass)->get_children_finish = rygel_tracker_root_container_real_get_children_finish;
	RYGEL_MEDIA_CONTAINER_CLASS (klass)->find_object = rygel_tracker_root_container_real_find_object;
	RYGEL_MEDIA_CONTAINER_CLASS (klass)->find_object_finish = rygel_tracker_root_container_real_find_object_finish;
	G_OBJECT_CLASS (klass)->finalize = rygel_tracker_root_container_finalize;
}


static void rygel_tracker_root_container_instance_init (RygelTrackerRootContainer * self) {
	self->priv = RYGEL_TRACKER_ROOT_CONTAINER_GET_PRIVATE (self);
}


static void rygel_tracker_root_container_finalize (GObject* obj) {
	RygelTrackerRootContainer * self;
	self = RYGEL_TRACKER_ROOT_CONTAINER (obj);
	(self->priv->categories == NULL) ? NULL : (self->priv->categories = (g_object_unref (self->priv->categories), NULL));
	G_OBJECT_CLASS (rygel_tracker_root_container_parent_class)->finalize (obj);
}


GType rygel_tracker_root_container_get_type (void) {
	static GType rygel_tracker_root_container_type_id = 0;
	if (rygel_tracker_root_container_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (RygelTrackerRootContainerClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) rygel_tracker_root_container_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (RygelTrackerRootContainer), 0, (GInstanceInitFunc) rygel_tracker_root_container_instance_init, NULL };
		rygel_tracker_root_container_type_id = g_type_register_static (RYGEL_TYPE_MEDIA_CONTAINER, "RygelTrackerRootContainer", &g_define_type_info, 0);
	}
	return rygel_tracker_root_container_type_id;
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




