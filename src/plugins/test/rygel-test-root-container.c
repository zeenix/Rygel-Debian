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


#define RYGEL_TYPE_TEST_ROOT_CONTAINER (rygel_test_root_container_get_type ())
#define RYGEL_TEST_ROOT_CONTAINER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_TEST_ROOT_CONTAINER, RygelTestRootContainer))
#define RYGEL_TEST_ROOT_CONTAINER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_TEST_ROOT_CONTAINER, RygelTestRootContainerClass))
#define RYGEL_IS_TEST_ROOT_CONTAINER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_TEST_ROOT_CONTAINER))
#define RYGEL_IS_TEST_ROOT_CONTAINER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_TEST_ROOT_CONTAINER))
#define RYGEL_TEST_ROOT_CONTAINER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_TEST_ROOT_CONTAINER, RygelTestRootContainerClass))

typedef struct _RygelTestRootContainer RygelTestRootContainer;
typedef struct _RygelTestRootContainerClass RygelTestRootContainerClass;
typedef struct _RygelTestRootContainerPrivate RygelTestRootContainerPrivate;

#define RYGEL_TYPE_TEST_ITEM (rygel_test_item_get_type ())
#define RYGEL_TEST_ITEM(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_TEST_ITEM, RygelTestItem))
#define RYGEL_TEST_ITEM_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_TEST_ITEM, RygelTestItemClass))
#define RYGEL_IS_TEST_ITEM(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_TEST_ITEM))
#define RYGEL_IS_TEST_ITEM_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_TEST_ITEM))
#define RYGEL_TEST_ITEM_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_TEST_ITEM, RygelTestItemClass))

typedef struct _RygelTestItem RygelTestItem;
typedef struct _RygelTestItemClass RygelTestItemClass;

#define RYGEL_TYPE_TEST_AUDIO_ITEM (rygel_test_audio_item_get_type ())
#define RYGEL_TEST_AUDIO_ITEM(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_TEST_AUDIO_ITEM, RygelTestAudioItem))
#define RYGEL_TEST_AUDIO_ITEM_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_TEST_AUDIO_ITEM, RygelTestAudioItemClass))
#define RYGEL_IS_TEST_AUDIO_ITEM(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_TEST_AUDIO_ITEM))
#define RYGEL_IS_TEST_AUDIO_ITEM_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_TEST_AUDIO_ITEM))
#define RYGEL_TEST_AUDIO_ITEM_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_TEST_AUDIO_ITEM, RygelTestAudioItemClass))

typedef struct _RygelTestAudioItem RygelTestAudioItem;
typedef struct _RygelTestAudioItemClass RygelTestAudioItemClass;

#define RYGEL_TYPE_TEST_VIDEO_ITEM (rygel_test_video_item_get_type ())
#define RYGEL_TEST_VIDEO_ITEM(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_TEST_VIDEO_ITEM, RygelTestVideoItem))
#define RYGEL_TEST_VIDEO_ITEM_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_TEST_VIDEO_ITEM, RygelTestVideoItemClass))
#define RYGEL_IS_TEST_VIDEO_ITEM(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_TEST_VIDEO_ITEM))
#define RYGEL_IS_TEST_VIDEO_ITEM_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_TEST_VIDEO_ITEM))
#define RYGEL_TEST_VIDEO_ITEM_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_TEST_VIDEO_ITEM, RygelTestVideoItemClass))

typedef struct _RygelTestVideoItem RygelTestVideoItem;
typedef struct _RygelTestVideoItemClass RygelTestVideoItemClass;

/**
 * Represents the root container for Test media content hierarchy.
 */
struct _RygelTestRootContainer {
	RygelMediaContainer parent_instance;
	RygelTestRootContainerPrivate * priv;
};

struct _RygelTestRootContainerClass {
	RygelMediaContainerClass parent_class;
};

struct _RygelTestRootContainerPrivate {
	GeeArrayList* items;
};



GType rygel_test_root_container_get_type (void);
#define RYGEL_TEST_ROOT_CONTAINER_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), RYGEL_TYPE_TEST_ROOT_CONTAINER, RygelTestRootContainerPrivate))
enum  {
	RYGEL_TEST_ROOT_CONTAINER_DUMMY_PROPERTY
};
RygelTestAudioItem* rygel_test_audio_item_new (const char* id, RygelMediaContainer* parent, const char* title);
RygelTestAudioItem* rygel_test_audio_item_construct (GType object_type, const char* id, RygelMediaContainer* parent, const char* title);
GType rygel_test_item_get_type (void);
GType rygel_test_audio_item_get_type (void);
RygelTestVideoItem* rygel_test_video_item_new (const char* id, RygelMediaContainer* parent, const char* title);
RygelTestVideoItem* rygel_test_video_item_construct (GType object_type, const char* id, RygelMediaContainer* parent, const char* title);
GType rygel_test_video_item_get_type (void);
RygelTestRootContainer* rygel_test_root_container_new (const char* title);
RygelTestRootContainer* rygel_test_root_container_construct (GType object_type, const char* title);
RygelTestRootContainer* rygel_test_root_container_new (const char* title);
static void rygel_test_root_container_real_get_children (RygelMediaContainer* base, guint offset, guint max_count, GCancellable* cancellable, GAsyncReadyCallback callback, void* callback_target);
static GeeList* rygel_test_root_container_real_get_children_finish (RygelMediaContainer* base, GAsyncResult* res, GError** error);
static void rygel_test_root_container_real_find_object (RygelMediaContainer* base, const char* id, GCancellable* cancellable, GAsyncReadyCallback callback, void* callback_target);
static RygelMediaObject* rygel_test_root_container_real_find_object_finish (RygelMediaContainer* base, GAsyncResult* res, GError** error);
static gpointer rygel_test_root_container_parent_class = NULL;
static void rygel_test_root_container_finalize (GObject* obj);
static int _vala_strcmp0 (const char * str1, const char * str2);



RygelTestRootContainer* rygel_test_root_container_construct (GType object_type, const char* title) {
	RygelTestRootContainer * self;
	GeeArrayList* _tmp0_;
	RygelTestAudioItem* _tmp1_;
	RygelTestVideoItem* _tmp2_;
	g_return_val_if_fail (title != NULL, NULL);
	self = (RygelTestRootContainer*) rygel_media_container_construct_root (object_type, title, (guint) 0);
	_tmp0_ = NULL;
	self->priv->items = (_tmp0_ = gee_array_list_new (RYGEL_TYPE_MEDIA_ITEM, (GBoxedCopyFunc) g_object_ref, g_object_unref, g_direct_equal), (self->priv->items == NULL) ? NULL : (self->priv->items = (g_object_unref (self->priv->items), NULL)), _tmp0_);
	_tmp1_ = NULL;
	gee_collection_add ((GeeCollection*) self->priv->items, (RygelMediaItem*) (_tmp1_ = rygel_test_audio_item_new ("sinewave", (RygelMediaContainer*) self, "Sine Wave")));
	(_tmp1_ == NULL) ? NULL : (_tmp1_ = (g_object_unref (_tmp1_), NULL));
	_tmp2_ = NULL;
	gee_collection_add ((GeeCollection*) self->priv->items, (RygelMediaItem*) (_tmp2_ = rygel_test_video_item_new ("smtpe", (RygelMediaContainer*) self, "SMTPE")));
	(_tmp2_ == NULL) ? NULL : (_tmp2_ = (g_object_unref (_tmp2_), NULL));
	((RygelMediaContainer*) self)->child_count = (guint) gee_collection_get_size ((GeeCollection*) self->priv->items);
	return self;
}


RygelTestRootContainer* rygel_test_root_container_new (const char* title) {
	return rygel_test_root_container_construct (RYGEL_TYPE_TEST_ROOT_CONTAINER, title);
}


static void rygel_test_root_container_real_get_children (RygelMediaContainer* base, guint offset, guint max_count, GCancellable* cancellable, GAsyncReadyCallback callback, void* callback_target) {
	RygelTestRootContainer * self;
	guint stop;
	GeeList* children;
	RygelSimpleAsyncResult* res;
	GeeList* _tmp1_;
	GeeList* _tmp0_;
	self = (RygelTestRootContainer*) base;
	stop = offset + max_count;
	stop = CLAMP (stop, (guint) 0, ((RygelMediaContainer*) self)->child_count);
	children = gee_list_slice ((GeeList*) self->priv->items, (gint) offset, (gint) stop);
	res = rygel_simple_async_result_new (GEE_TYPE_LIST, (GBoxedCopyFunc) g_object_ref, g_object_unref, (GObject*) self, callback, callback_target);
	_tmp1_ = NULL;
	_tmp0_ = NULL;
	res->data = (_tmp1_ = (_tmp0_ = children, (_tmp0_ == NULL) ? NULL : g_object_ref (_tmp0_)), (res->data == NULL) ? NULL : (res->data = (g_object_unref (res->data), NULL)), _tmp1_);
	rygel_simple_async_result_complete_in_idle (res);
	(children == NULL) ? NULL : (children = (g_object_unref (children), NULL));
	(res == NULL) ? NULL : (res = (g_object_unref (res), NULL));
}


static GeeList* rygel_test_root_container_real_get_children_finish (RygelMediaContainer* base, GAsyncResult* res, GError** error) {
	RygelTestRootContainer * self;
	RygelSimpleAsyncResult* _tmp0_;
	RygelSimpleAsyncResult* simple_res;
	GeeList* _tmp1_;
	GeeList* _tmp2_;
	self = (RygelTestRootContainer*) base;
	g_return_val_if_fail (res != NULL, NULL);
	_tmp0_ = NULL;
	simple_res = (_tmp0_ = RYGEL_SIMPLE_ASYNC_RESULT (res), (_tmp0_ == NULL) ? NULL : g_object_ref (_tmp0_));
	_tmp1_ = NULL;
	_tmp2_ = NULL;
	return (_tmp2_ = (_tmp1_ = (GeeList*) simple_res->data, (_tmp1_ == NULL) ? NULL : g_object_ref (_tmp1_)), (simple_res == NULL) ? NULL : (simple_res = (g_object_unref (simple_res), NULL)), _tmp2_);
}


static void rygel_test_root_container_real_find_object (RygelMediaContainer* base, const char* id, GCancellable* cancellable, GAsyncReadyCallback callback, void* callback_target) {
	RygelTestRootContainer * self;
	RygelSimpleAsyncResult* res;
	char* _tmp1_;
	const char* _tmp0_;
	self = (RygelTestRootContainer*) base;
	g_return_if_fail (id != NULL);
	res = rygel_simple_async_result_new (G_TYPE_STRING, (GBoxedCopyFunc) g_strdup, g_free, (GObject*) self, callback, callback_target);
	_tmp1_ = NULL;
	_tmp0_ = NULL;
	res->data = (_tmp1_ = (_tmp0_ = id, (_tmp0_ == NULL) ? NULL : g_strdup (_tmp0_)), res->data = (g_free (res->data), NULL), _tmp1_);
	rygel_simple_async_result_complete_in_idle (res);
	(res == NULL) ? NULL : (res = (g_object_unref (res), NULL));
}


static RygelMediaObject* rygel_test_root_container_real_find_object_finish (RygelMediaContainer* base, GAsyncResult* res, GError** error) {
	RygelTestRootContainer * self;
	RygelMediaItem* item;
	const char* _tmp0_;
	char* id;
	RygelMediaObject* _tmp3_;
	self = (RygelTestRootContainer*) base;
	g_return_val_if_fail (res != NULL, NULL);
	item = NULL;
	_tmp0_ = NULL;
	id = (_tmp0_ = (const char*) RYGEL_SIMPLE_ASYNC_RESULT (res)->data, (_tmp0_ == NULL) ? NULL : g_strdup (_tmp0_));
	{
		GeeIterator* _tmp_it;
		_tmp_it = gee_iterable_iterator ((GeeIterable*) self->priv->items);
		while (gee_iterator_next (_tmp_it)) {
			RygelMediaItem* tmp;
			tmp = (RygelMediaItem*) gee_iterator_get (_tmp_it);
			if (_vala_strcmp0 (id, ((RygelMediaObject*) tmp)->id) == 0) {
				RygelMediaItem* _tmp2_;
				RygelMediaItem* _tmp1_;
				_tmp2_ = NULL;
				_tmp1_ = NULL;
				item = (_tmp2_ = (_tmp1_ = tmp, (_tmp1_ == NULL) ? NULL : g_object_ref (_tmp1_)), (item == NULL) ? NULL : (item = (g_object_unref (item), NULL)), _tmp2_);
				(tmp == NULL) ? NULL : (tmp = (g_object_unref (tmp), NULL));
				break;
			}
			(tmp == NULL) ? NULL : (tmp = (g_object_unref (tmp), NULL));
		}
		(_tmp_it == NULL) ? NULL : (_tmp_it = (g_object_unref (_tmp_it), NULL));
	}
	_tmp3_ = NULL;
	return (_tmp3_ = (RygelMediaObject*) item, id = (g_free (id), NULL), _tmp3_);
}


static void rygel_test_root_container_class_init (RygelTestRootContainerClass * klass) {
	rygel_test_root_container_parent_class = g_type_class_peek_parent (klass);
	g_type_class_add_private (klass, sizeof (RygelTestRootContainerPrivate));
	RYGEL_MEDIA_CONTAINER_CLASS (klass)->get_children = rygel_test_root_container_real_get_children;
	RYGEL_MEDIA_CONTAINER_CLASS (klass)->get_children_finish = rygel_test_root_container_real_get_children_finish;
	RYGEL_MEDIA_CONTAINER_CLASS (klass)->find_object = rygel_test_root_container_real_find_object;
	RYGEL_MEDIA_CONTAINER_CLASS (klass)->find_object_finish = rygel_test_root_container_real_find_object_finish;
	G_OBJECT_CLASS (klass)->finalize = rygel_test_root_container_finalize;
}


static void rygel_test_root_container_instance_init (RygelTestRootContainer * self) {
	self->priv = RYGEL_TEST_ROOT_CONTAINER_GET_PRIVATE (self);
}


static void rygel_test_root_container_finalize (GObject* obj) {
	RygelTestRootContainer * self;
	self = RYGEL_TEST_ROOT_CONTAINER (obj);
	(self->priv->items == NULL) ? NULL : (self->priv->items = (g_object_unref (self->priv->items), NULL));
	G_OBJECT_CLASS (rygel_test_root_container_parent_class)->finalize (obj);
}


GType rygel_test_root_container_get_type (void) {
	static GType rygel_test_root_container_type_id = 0;
	if (rygel_test_root_container_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (RygelTestRootContainerClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) rygel_test_root_container_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (RygelTestRootContainer), 0, (GInstanceInitFunc) rygel_test_root_container_instance_init, NULL };
		rygel_test_root_container_type_id = g_type_register_static (RYGEL_TYPE_MEDIA_CONTAINER, "RygelTestRootContainer", &g_define_type_info, 0);
	}
	return rygel_test_root_container_type_id;
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




