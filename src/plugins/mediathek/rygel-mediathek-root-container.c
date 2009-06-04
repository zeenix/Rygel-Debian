/*
 * Copyright (C) 2009 Jens Georg
 *
 * Author: Jens Georg <mail@jensge.org>
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
#include <libsoup/soup.h>
#include <gee/arraylist.h>
#include <gee/list.h>
#include <gio/gio.h>
#include <stdlib.h>
#include <string.h>
#include <gee/iterable.h>
#include <gee/iterator.h>
#include <gee/collection.h>


#define RYGEL_TYPE_MEDIATHEK_ROOT_CONTAINER (rygel_mediathek_root_container_get_type ())
#define RYGEL_MEDIATHEK_ROOT_CONTAINER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_MEDIATHEK_ROOT_CONTAINER, RygelMediathekRootContainer))
#define RYGEL_MEDIATHEK_ROOT_CONTAINER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_MEDIATHEK_ROOT_CONTAINER, RygelMediathekRootContainerClass))
#define RYGEL_IS_MEDIATHEK_ROOT_CONTAINER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_MEDIATHEK_ROOT_CONTAINER))
#define RYGEL_IS_MEDIATHEK_ROOT_CONTAINER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_MEDIATHEK_ROOT_CONTAINER))
#define RYGEL_MEDIATHEK_ROOT_CONTAINER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_MEDIATHEK_ROOT_CONTAINER, RygelMediathekRootContainerClass))

typedef struct _RygelMediathekRootContainer RygelMediathekRootContainer;
typedef struct _RygelMediathekRootContainerClass RygelMediathekRootContainerClass;
typedef struct _RygelMediathekRootContainerPrivate RygelMediathekRootContainerPrivate;

#define RYGEL_TYPE_MEDIATHEK_RSS_CONTAINER (rygel_mediathek_rss_container_get_type ())
#define RYGEL_MEDIATHEK_RSS_CONTAINER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_MEDIATHEK_RSS_CONTAINER, RygelMediathekRssContainer))
#define RYGEL_MEDIATHEK_RSS_CONTAINER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_MEDIATHEK_RSS_CONTAINER, RygelMediathekRssContainerClass))
#define RYGEL_IS_MEDIATHEK_RSS_CONTAINER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_MEDIATHEK_RSS_CONTAINER))
#define RYGEL_IS_MEDIATHEK_RSS_CONTAINER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_MEDIATHEK_RSS_CONTAINER))
#define RYGEL_MEDIATHEK_RSS_CONTAINER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_MEDIATHEK_RSS_CONTAINER, RygelMediathekRssContainerClass))

typedef struct _RygelMediathekRssContainer RygelMediathekRssContainer;
typedef struct _RygelMediathekRssContainerClass RygelMediathekRssContainerClass;

struct _RygelMediathekRootContainer {
	RygelMediaContainer parent_instance;
	RygelMediathekRootContainerPrivate * priv;
	SoupSessionAsync* session;
};

struct _RygelMediathekRootContainerClass {
	RygelMediaContainerClass parent_class;
};

struct _RygelMediathekRootContainerPrivate {
	GeeArrayList* items;
};



GType rygel_mediathek_root_container_get_type (void);
GType rygel_mediathek_rss_container_get_type (void);
#define RYGEL_MEDIATHEK_ROOT_CONTAINER_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), RYGEL_TYPE_MEDIATHEK_ROOT_CONTAINER, RygelMediathekRootContainerPrivate))
enum  {
	RYGEL_MEDIATHEK_ROOT_CONTAINER_DUMMY_PROPERTY
};
static void rygel_mediathek_root_container_real_get_children (RygelMediaContainer* base, guint offset, guint max_count, GCancellable* cancellable, GAsyncReadyCallback callback, void* callback_target);
static GeeList* rygel_mediathek_root_container_real_get_children_finish (RygelMediaContainer* base, GAsyncResult* res, GError** error);
static void rygel_mediathek_root_container_real_find_object (RygelMediaContainer* base, const char* id, GCancellable* cancellable, GAsyncReadyCallback callback, void* callback_target);
RygelMediaObject* rygel_mediathek_rss_container_find_object_sync (RygelMediathekRssContainer* self, const char* id);
static RygelMediaObject* rygel_mediathek_root_container_real_find_object_finish (RygelMediaContainer* base, GAsyncResult* res, GError** error);
void rygel_mediathek_rss_container_update (RygelMediathekRssContainer* self);
static gboolean rygel_mediathek_root_container_on_schedule_update (RygelMediathekRootContainer* self);
RygelMediathekRssContainer* rygel_mediathek_rss_container_new (RygelMediaContainer* parent, guint id);
RygelMediathekRssContainer* rygel_mediathek_rss_container_construct (GType object_type, RygelMediaContainer* parent, guint id);
static gboolean _rygel_mediathek_root_container_on_schedule_update_gsource_func (gpointer self);
RygelMediathekRootContainer* rygel_mediathek_root_container_new (void);
RygelMediathekRootContainer* rygel_mediathek_root_container_construct (GType object_type);
RygelMediathekRootContainer* rygel_mediathek_root_container_new (void);
static gpointer rygel_mediathek_root_container_parent_class = NULL;
static void rygel_mediathek_root_container_finalize (GObject* obj);
static int _vala_strcmp0 (const char * str1, const char * str2);



static void rygel_mediathek_root_container_real_get_children (RygelMediaContainer* base, guint offset, guint max_count, GCancellable* cancellable, GAsyncReadyCallback callback, void* callback_target) {
	RygelMediathekRootContainer * self;
	guint stop;
	GeeList* children;
	RygelSimpleAsyncResult* res;
	GeeList* _tmp1_;
	GeeList* _tmp0_;
	self = (RygelMediathekRootContainer*) base;
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


static GeeList* rygel_mediathek_root_container_real_get_children_finish (RygelMediaContainer* base, GAsyncResult* res, GError** error) {
	RygelMediathekRootContainer * self;
	RygelSimpleAsyncResult* _tmp0_;
	RygelSimpleAsyncResult* simple_res;
	GeeList* _tmp1_;
	GeeList* _tmp2_;
	self = (RygelMediathekRootContainer*) base;
	g_return_val_if_fail (res != NULL, NULL);
	_tmp0_ = NULL;
	simple_res = (_tmp0_ = RYGEL_SIMPLE_ASYNC_RESULT (res), (_tmp0_ == NULL) ? NULL : g_object_ref (_tmp0_));
	_tmp1_ = NULL;
	_tmp2_ = NULL;
	return (_tmp2_ = (_tmp1_ = (GeeList*) simple_res->data, (_tmp1_ == NULL) ? NULL : g_object_ref (_tmp1_)), (simple_res == NULL) ? NULL : (simple_res = (g_object_unref (simple_res), NULL)), _tmp2_);
}


static void rygel_mediathek_root_container_real_find_object (RygelMediaContainer* base, const char* id, GCancellable* cancellable, GAsyncReadyCallback callback, void* callback_target) {
	RygelMediathekRootContainer * self;
	RygelSimpleAsyncResult* res;
	char* _tmp1_;
	const char* _tmp0_;
	self = (RygelMediathekRootContainer*) base;
	g_return_if_fail (id != NULL);
	res = rygel_simple_async_result_new (G_TYPE_STRING, (GBoxedCopyFunc) g_strdup, g_free, (GObject*) self, callback, callback_target);
	_tmp1_ = NULL;
	_tmp0_ = NULL;
	res->data = (_tmp1_ = (_tmp0_ = id, (_tmp0_ == NULL) ? NULL : g_strdup (_tmp0_)), res->data = (g_free (res->data), NULL), _tmp1_);
	rygel_simple_async_result_complete_in_idle (res);
	(res == NULL) ? NULL : (res = (g_object_unref (res), NULL));
}


static RygelMediaObject* rygel_mediathek_root_container_real_find_object_finish (RygelMediaContainer* base, GAsyncResult* res, GError** error) {
	RygelMediathekRootContainer * self;
	RygelMediaObject* item;
	const char* _tmp0_;
	char* id;
	RygelMediaObject* _tmp4_;
	self = (RygelMediathekRootContainer*) base;
	g_return_val_if_fail (res != NULL, NULL);
	item = NULL;
	_tmp0_ = NULL;
	id = (_tmp0_ = (const char*) RYGEL_SIMPLE_ASYNC_RESULT (res)->data, (_tmp0_ == NULL) ? NULL : g_strdup (_tmp0_));
	{
		GeeIterator* _tmp_it;
		_tmp_it = gee_iterable_iterator ((GeeIterable*) self->priv->items);
		while (gee_iterator_next (_tmp_it)) {
			RygelMediathekRssContainer* tmp;
			tmp = (RygelMediathekRssContainer*) gee_iterator_get (_tmp_it);
			if (_vala_strcmp0 (id, ((RygelMediaObject*) tmp)->id) == 0) {
				RygelMediaObject* _tmp2_;
				RygelMediaObject* _tmp1_;
				_tmp2_ = NULL;
				_tmp1_ = NULL;
				item = (_tmp2_ = (_tmp1_ = (RygelMediaObject*) tmp, (_tmp1_ == NULL) ? NULL : g_object_ref (_tmp1_)), (item == NULL) ? NULL : (item = (g_object_unref (item), NULL)), _tmp2_);
				(tmp == NULL) ? NULL : (tmp = (g_object_unref (tmp), NULL));
				break;
			}
			(tmp == NULL) ? NULL : (tmp = (g_object_unref (tmp), NULL));
		}
		(_tmp_it == NULL) ? NULL : (_tmp_it = (g_object_unref (_tmp_it), NULL));
	}
	if (item == NULL) {
		{
			GeeIterator* _container_it;
			_container_it = gee_iterable_iterator ((GeeIterable*) self->priv->items);
			while (gee_iterator_next (_container_it)) {
				RygelMediathekRssContainer* container;
				RygelMediaObject* _tmp3_;
				container = (RygelMediathekRssContainer*) gee_iterator_get (_container_it);
				_tmp3_ = NULL;
				item = (_tmp3_ = rygel_mediathek_rss_container_find_object_sync (container, id), (item == NULL) ? NULL : (item = (g_object_unref (item), NULL)), _tmp3_);
				if (item != NULL) {
					(container == NULL) ? NULL : (container = (g_object_unref (container), NULL));
					break;
				}
				(container == NULL) ? NULL : (container = (g_object_unref (container), NULL));
			}
			(_container_it == NULL) ? NULL : (_container_it = (g_object_unref (_container_it), NULL));
		}
	}
	_tmp4_ = NULL;
	return (_tmp4_ = item, id = (g_free (id), NULL), _tmp4_);
}


static gboolean rygel_mediathek_root_container_on_schedule_update (RygelMediathekRootContainer* self) {
	g_return_val_if_fail (self != NULL, FALSE);
	g_message ("rygel-mediathek-root-container.vala:90: Scheduling update for all feeds....");
	{
		GeeIterator* _container_it;
		_container_it = gee_iterable_iterator ((GeeIterable*) self->priv->items);
		while (gee_iterator_next (_container_it)) {
			RygelMediathekRssContainer* container;
			container = (RygelMediathekRssContainer*) gee_iterator_get (_container_it);
			rygel_mediathek_rss_container_update (container);
			(container == NULL) ? NULL : (container = (g_object_unref (container), NULL));
		}
		(_container_it == NULL) ? NULL : (_container_it = (g_object_unref (_container_it), NULL));
	}
	return TRUE;
}


static gboolean _rygel_mediathek_root_container_on_schedule_update_gsource_func (gpointer self) {
	return rygel_mediathek_root_container_on_schedule_update (self);
}


RygelMediathekRootContainer* rygel_mediathek_root_container_construct (GType object_type) {
	RygelMediathekRootContainer * self;
	SoupSessionAsync* _tmp0_;
	GeeArrayList* _tmp1_;
	RygelConfiguration* config;
	GeeArrayList* feeds;
	self = (RygelMediathekRootContainer*) rygel_media_container_construct_root (object_type, "ZDF Mediathek", (guint) 0);
	_tmp0_ = NULL;
	self->session = (_tmp0_ = (SoupSessionAsync*) soup_session_async_new (), (self->session == NULL) ? NULL : (self->session = (g_object_unref (self->session), NULL)), _tmp0_);
	_tmp1_ = NULL;
	self->priv->items = (_tmp1_ = gee_array_list_new (RYGEL_TYPE_MEDIATHEK_RSS_CONTAINER, (GBoxedCopyFunc) g_object_ref, g_object_unref, g_direct_equal), (self->priv->items == NULL) ? NULL : (self->priv->items = (g_object_unref (self->priv->items), NULL)), _tmp1_);
	config = rygel_configuration_get_default ();
	feeds = rygel_configuration_get_int_list (config, "ZDFMediathek", "rss");
	if (gee_collection_get_size ((GeeCollection*) feeds) == 0) {
		g_message ("rygel-mediathek-root-container.vala:107: Could not get RSS items from GConf, using defaults");
		gee_collection_add ((GeeCollection*) feeds, GINT_TO_POINTER (508));
	}
	{
		GeeIterator* _id_it;
		_id_it = gee_iterable_iterator ((GeeIterable*) feeds);
		while (gee_iterator_next (_id_it)) {
			gint id;
			RygelMediathekRssContainer* _tmp2_;
			id = GPOINTER_TO_INT (gee_iterator_get (_id_it));
			_tmp2_ = NULL;
			gee_collection_add ((GeeCollection*) self->priv->items, _tmp2_ = rygel_mediathek_rss_container_new ((RygelMediaContainer*) self, (guint) id));
			(_tmp2_ == NULL) ? NULL : (_tmp2_ = (g_object_unref (_tmp2_), NULL));
		}
		(_id_it == NULL) ? NULL : (_id_it = (g_object_unref (_id_it), NULL));
	}
	((RygelMediaContainer*) self)->child_count = (guint) gee_collection_get_size ((GeeCollection*) self->priv->items);
	g_timeout_add_seconds ((guint) 1800, _rygel_mediathek_root_container_on_schedule_update_gsource_func, self);
	(config == NULL) ? NULL : (config = (g_object_unref (config), NULL));
	(feeds == NULL) ? NULL : (feeds = (g_object_unref (feeds), NULL));
	return self;
}


RygelMediathekRootContainer* rygel_mediathek_root_container_new (void) {
	return rygel_mediathek_root_container_construct (RYGEL_TYPE_MEDIATHEK_ROOT_CONTAINER);
}


static void rygel_mediathek_root_container_class_init (RygelMediathekRootContainerClass * klass) {
	rygel_mediathek_root_container_parent_class = g_type_class_peek_parent (klass);
	g_type_class_add_private (klass, sizeof (RygelMediathekRootContainerPrivate));
	RYGEL_MEDIA_CONTAINER_CLASS (klass)->get_children = rygel_mediathek_root_container_real_get_children;
	RYGEL_MEDIA_CONTAINER_CLASS (klass)->get_children_finish = rygel_mediathek_root_container_real_get_children_finish;
	RYGEL_MEDIA_CONTAINER_CLASS (klass)->find_object = rygel_mediathek_root_container_real_find_object;
	RYGEL_MEDIA_CONTAINER_CLASS (klass)->find_object_finish = rygel_mediathek_root_container_real_find_object_finish;
	G_OBJECT_CLASS (klass)->finalize = rygel_mediathek_root_container_finalize;
}


static void rygel_mediathek_root_container_instance_init (RygelMediathekRootContainer * self) {
	self->priv = RYGEL_MEDIATHEK_ROOT_CONTAINER_GET_PRIVATE (self);
}


static void rygel_mediathek_root_container_finalize (GObject* obj) {
	RygelMediathekRootContainer * self;
	self = RYGEL_MEDIATHEK_ROOT_CONTAINER (obj);
	(self->priv->items == NULL) ? NULL : (self->priv->items = (g_object_unref (self->priv->items), NULL));
	(self->session == NULL) ? NULL : (self->session = (g_object_unref (self->session), NULL));
	G_OBJECT_CLASS (rygel_mediathek_root_container_parent_class)->finalize (obj);
}


GType rygel_mediathek_root_container_get_type (void) {
	static GType rygel_mediathek_root_container_type_id = 0;
	if (rygel_mediathek_root_container_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (RygelMediathekRootContainerClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) rygel_mediathek_root_container_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (RygelMediathekRootContainer), 0, (GInstanceInitFunc) rygel_mediathek_root_container_instance_init, NULL };
		rygel_mediathek_root_container_type_id = g_type_register_static (RYGEL_TYPE_MEDIA_CONTAINER, "RygelMediathekRootContainer", &g_define_type_info, 0);
	}
	return rygel_mediathek_root_container_type_id;
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




