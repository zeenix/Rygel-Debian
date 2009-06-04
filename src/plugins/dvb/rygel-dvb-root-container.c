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
#include <dbus/dbus-glib-lowlevel.h>
#include <dbus/dbus-glib.h>
#include <gee/arraylist.h>
#include <stdlib.h>
#include <string.h>
#include <gee/list.h>
#include <gio/gio.h>
#include <gee/collection.h>
#include <gee/iterable.h>
#include <gee/iterator.h>


#define RYGEL_TYPE_DVB_ROOT_CONTAINER (rygel_dvb_root_container_get_type ())
#define RYGEL_DVB_ROOT_CONTAINER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_DVB_ROOT_CONTAINER, RygelDVBRootContainer))
#define RYGEL_DVB_ROOT_CONTAINER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_DVB_ROOT_CONTAINER, RygelDVBRootContainerClass))
#define RYGEL_IS_DVB_ROOT_CONTAINER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_DVB_ROOT_CONTAINER))
#define RYGEL_IS_DVB_ROOT_CONTAINER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_DVB_ROOT_CONTAINER))
#define RYGEL_DVB_ROOT_CONTAINER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_DVB_ROOT_CONTAINER, RygelDVBRootContainerClass))

typedef struct _RygelDVBRootContainer RygelDVBRootContainer;
typedef struct _RygelDVBRootContainerClass RygelDVBRootContainerClass;
typedef struct _RygelDVBRootContainerPrivate RygelDVBRootContainerPrivate;

#define RYGEL_TYPE_DVB_CHANNEL_GROUP (rygel_dvb_channel_group_get_type ())
#define RYGEL_DVB_CHANNEL_GROUP(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_DVB_CHANNEL_GROUP, RygelDVBChannelGroup))
#define RYGEL_DVB_CHANNEL_GROUP_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_DVB_CHANNEL_GROUP, RygelDVBChannelGroupClass))
#define RYGEL_IS_DVB_CHANNEL_GROUP(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_DVB_CHANNEL_GROUP))
#define RYGEL_IS_DVB_CHANNEL_GROUP_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_DVB_CHANNEL_GROUP))
#define RYGEL_DVB_CHANNEL_GROUP_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_DVB_CHANNEL_GROUP, RygelDVBChannelGroupClass))

typedef struct _RygelDVBChannelGroup RygelDVBChannelGroup;
typedef struct _RygelDVBChannelGroupClass RygelDVBChannelGroupClass;

/**
 * Represents the root container for DVB media content hierarchy.
 */
struct _RygelDVBRootContainer {
	RygelMediaContainer parent_instance;
	RygelDVBRootContainerPrivate * priv;
	DBusGProxy* manager;
};

struct _RygelDVBRootContainerClass {
	RygelMediaContainerClass parent_class;
};

struct _RygelDVBRootContainerPrivate {
	GeeArrayList* groups;
};



GType rygel_dvb_root_container_get_type (void);
GType rygel_dvb_channel_group_get_type (void);
#define RYGEL_DVB_ROOT_CONTAINER_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), RYGEL_TYPE_DVB_ROOT_CONTAINER, RygelDVBRootContainerPrivate))
enum  {
	RYGEL_DVB_ROOT_CONTAINER_DUMMY_PROPERTY
};
#define RYGEL_DVB_ROOT_CONTAINER_DVB_SERVICE "org.gnome.DVB"
#define RYGEL_DVB_ROOT_CONTAINER_MANAGER_PATH "/org/gnome/DVB/Manager"
#define RYGEL_DVB_ROOT_CONTAINER_MANAGER_IFACE "org.gnome.DVB.Manager"
#define RYGEL_DVB_ROOT_CONTAINER_CHANNEL_LIST_IFACE "org.gnome.DVB.ChannelList"
static void rygel_dvb_root_container_fetch_device_groups (RygelDVBRootContainer* self, DBusGConnection* connection, GError** error);
RygelDVBRootContainer* rygel_dvb_root_container_new (const char* title);
RygelDVBRootContainer* rygel_dvb_root_container_construct (GType object_type, const char* title);
RygelDVBRootContainer* rygel_dvb_root_container_new (const char* title);
static void rygel_dvb_root_container_real_get_children (RygelMediaContainer* base, guint offset, guint max_count, GCancellable* cancellable, GAsyncReadyCallback callback, void* callback_target);
static GeeList* rygel_dvb_root_container_real_get_children_finish (RygelMediaContainer* base, GAsyncResult* res, GError** error);
static RygelDVBChannelGroup* rygel_dvb_root_container_find_group_by_id (RygelDVBRootContainer* self, const char* id);
static RygelMediaObject* rygel_dvb_root_container_find_channel_by_id (RygelDVBRootContainer* self, const char* id, GError** error);
static void rygel_dvb_root_container_real_find_object (RygelMediaContainer* base, const char* id, GCancellable* cancellable, GAsyncReadyCallback callback, void* callback_target);
static RygelMediaObject* rygel_dvb_root_container_real_find_object_finish (RygelMediaContainer* base, GAsyncResult* res, GError** error);
guint* _dynamic_GetRegisteredDeviceGroups0 (DBusGProxy* self, int* result_length1, GError** error);
char* _dynamic_GetChannelList1 (DBusGProxy* self, guint param1, GError** error);
char* _dynamic_GetDeviceGroupName2 (DBusGProxy* self, guint param1, GError** error);
RygelDVBChannelGroup* rygel_dvb_channel_group_new (guint gid, const char* title, RygelMediaContainer* parent, DBusGProxy* channel_list);
RygelDVBChannelGroup* rygel_dvb_channel_group_construct (GType object_type, guint gid, const char* title, RygelMediaContainer* parent, DBusGProxy* channel_list);
RygelMediaObject* rygel_dvb_channel_group_find_object_sync (RygelDVBChannelGroup* self, const char* id);
static gpointer rygel_dvb_root_container_parent_class = NULL;
static void rygel_dvb_root_container_finalize (GObject* obj);
static int _vala_strcmp0 (const char * str1, const char * str2);



RygelDVBRootContainer* rygel_dvb_root_container_construct (GType object_type, const char* title) {
	GError * _inner_error_;
	RygelDVBRootContainer * self;
	GeeArrayList* _tmp0_;
	g_return_val_if_fail (title != NULL, NULL);
	_inner_error_ = NULL;
	self = (RygelDVBRootContainer*) rygel_media_container_construct_root (object_type, title, (guint) 0);
	_tmp0_ = NULL;
	self->priv->groups = (_tmp0_ = gee_array_list_new (RYGEL_TYPE_DVB_CHANNEL_GROUP, (GBoxedCopyFunc) g_object_ref, g_object_unref, g_direct_equal), (self->priv->groups == NULL) ? NULL : (self->priv->groups = (g_object_unref (self->priv->groups), NULL)), _tmp0_);
	{
		DBusGConnection* connection;
		DBusGProxy* _tmp1_;
		connection = dbus_g_bus_get (DBUS_BUS_SESSION, &_inner_error_);
		if (_inner_error_ != NULL) {
			if (_inner_error_->domain == DBUS_GERROR) {
				goto __catch0_dbus_gerror;
			}
			goto __finally0;
		}
		/* Get a proxy to DVB Manager object*/
		_tmp1_ = NULL;
		self->manager = (_tmp1_ = dbus_g_proxy_new_for_name (connection, RYGEL_DVB_ROOT_CONTAINER_DVB_SERVICE, RYGEL_DVB_ROOT_CONTAINER_MANAGER_PATH, RYGEL_DVB_ROOT_CONTAINER_MANAGER_IFACE), (self->manager == NULL) ? NULL : (self->manager = (g_object_unref (self->manager), NULL)), _tmp1_);
		rygel_dvb_root_container_fetch_device_groups (self, connection, &_inner_error_);
		if (_inner_error_ != NULL) {
			(connection == NULL) ? NULL : (connection = (dbus_g_connection_unref (connection), NULL));
			if (_inner_error_->domain == DBUS_GERROR) {
				goto __catch0_dbus_gerror;
			}
			goto __finally0;
		}
		(connection == NULL) ? NULL : (connection = (dbus_g_connection_unref (connection), NULL));
	}
	goto __finally0;
	__catch0_dbus_gerror:
	{
		GError * _error_;
		_error_ = _inner_error_;
		_inner_error_ = NULL;
		{
			g_critical ("rygel-dvb-root-container.vala:60: Failed to fetch device groups: %s\n", _error_->message);
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


RygelDVBRootContainer* rygel_dvb_root_container_new (const char* title) {
	return rygel_dvb_root_container_construct (RYGEL_TYPE_DVB_ROOT_CONTAINER, title);
}


static void rygel_dvb_root_container_real_get_children (RygelMediaContainer* base, guint offset, guint max_count, GCancellable* cancellable, GAsyncReadyCallback callback, void* callback_target) {
	RygelDVBRootContainer * self;
	guint stop;
	GeeList* groups;
	RygelSimpleAsyncResult* res;
	GeeList* _tmp1_;
	GeeList* _tmp0_;
	self = (RygelDVBRootContainer*) base;
	stop = offset + max_count;
	stop = CLAMP (stop, (guint) 0, ((RygelMediaContainer*) self)->child_count);
	groups = gee_list_slice ((GeeList*) self->priv->groups, (gint) offset, (gint) stop);
	res = rygel_simple_async_result_new (GEE_TYPE_LIST, (GBoxedCopyFunc) g_object_ref, g_object_unref, (GObject*) self, callback, callback_target);
	_tmp1_ = NULL;
	_tmp0_ = NULL;
	res->data = (_tmp1_ = (_tmp0_ = groups, (_tmp0_ == NULL) ? NULL : g_object_ref (_tmp0_)), (res->data == NULL) ? NULL : (res->data = (g_object_unref (res->data), NULL)), _tmp1_);
	rygel_simple_async_result_complete_in_idle (res);
	(groups == NULL) ? NULL : (groups = (g_object_unref (groups), NULL));
	(res == NULL) ? NULL : (res = (g_object_unref (res), NULL));
}


static GeeList* rygel_dvb_root_container_real_get_children_finish (RygelMediaContainer* base, GAsyncResult* res, GError** error) {
	RygelDVBRootContainer * self;
	RygelSimpleAsyncResult* _tmp0_;
	RygelSimpleAsyncResult* simple_res;
	GeeList* _tmp1_;
	GeeList* _tmp2_;
	self = (RygelDVBRootContainer*) base;
	g_return_val_if_fail (res != NULL, NULL);
	_tmp0_ = NULL;
	simple_res = (_tmp0_ = RYGEL_SIMPLE_ASYNC_RESULT (res), (_tmp0_ == NULL) ? NULL : g_object_ref (_tmp0_));
	_tmp1_ = NULL;
	_tmp2_ = NULL;
	return (_tmp2_ = (_tmp1_ = (GeeList*) simple_res->data, (_tmp1_ == NULL) ? NULL : g_object_ref (_tmp1_)), (simple_res == NULL) ? NULL : (simple_res = (g_object_unref (simple_res), NULL)), _tmp2_);
}


static void rygel_dvb_root_container_real_find_object (RygelMediaContainer* base, const char* id, GCancellable* cancellable, GAsyncReadyCallback callback, void* callback_target) {
	RygelDVBRootContainer * self;
	GError * _inner_error_;
	RygelMediaObject* media_object;
	RygelSimpleAsyncResult* res;
	RygelMediaObject* _tmp3_;
	RygelMediaObject* _tmp2_;
	self = (RygelDVBRootContainer*) base;
	g_return_if_fail (id != NULL);
	_inner_error_ = NULL;
	/* First try groups*/
	media_object = (RygelMediaObject*) rygel_dvb_root_container_find_group_by_id (self, id);
	if (media_object == NULL) {
		RygelMediaObject* _tmp0_;
		RygelMediaObject* _tmp1_;
		_tmp0_ = rygel_dvb_root_container_find_channel_by_id (self, id, &_inner_error_);
		if (_inner_error_ != NULL) {
			(media_object == NULL) ? NULL : (media_object = (g_object_unref (media_object), NULL));
			g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, _inner_error_->message);
			g_clear_error (&_inner_error_);
			return;
		}
		_tmp1_ = NULL;
		media_object = (_tmp1_ = _tmp0_, (media_object == NULL) ? NULL : (media_object = (g_object_unref (media_object), NULL)), _tmp1_);
	}
	res = rygel_simple_async_result_new (RYGEL_TYPE_MEDIA_OBJECT, (GBoxedCopyFunc) g_object_ref, g_object_unref, (GObject*) self, callback, callback_target);
	_tmp3_ = NULL;
	_tmp2_ = NULL;
	res->data = (_tmp3_ = (_tmp2_ = media_object, (_tmp2_ == NULL) ? NULL : g_object_ref (_tmp2_)), (res->data == NULL) ? NULL : (res->data = (g_object_unref (res->data), NULL)), _tmp3_);
	rygel_simple_async_result_complete_in_idle (res);
	(media_object == NULL) ? NULL : (media_object = (g_object_unref (media_object), NULL));
	(res == NULL) ? NULL : (res = (g_object_unref (res), NULL));
}


static RygelMediaObject* rygel_dvb_root_container_real_find_object_finish (RygelMediaContainer* base, GAsyncResult* res, GError** error) {
	RygelDVBRootContainer * self;
	RygelSimpleAsyncResult* _tmp0_;
	RygelSimpleAsyncResult* simple_res;
	RygelMediaObject* _tmp1_;
	RygelMediaObject* _tmp2_;
	self = (RygelDVBRootContainer*) base;
	g_return_val_if_fail (res != NULL, NULL);
	_tmp0_ = NULL;
	simple_res = (_tmp0_ = RYGEL_SIMPLE_ASYNC_RESULT (res), (_tmp0_ == NULL) ? NULL : g_object_ref (_tmp0_));
	_tmp1_ = NULL;
	_tmp2_ = NULL;
	return (_tmp2_ = (_tmp1_ = (RygelMediaObject*) simple_res->data, (_tmp1_ == NULL) ? NULL : g_object_ref (_tmp1_)), (simple_res == NULL) ? NULL : (simple_res = (g_object_unref (simple_res), NULL)), _tmp2_);
}


guint* _dynamic_GetRegisteredDeviceGroups0 (DBusGProxy* self, int* result_length1, GError** error) {
	GArray* result;
	dbus_g_proxy_call (self, "GetRegisteredDeviceGroups", error, G_TYPE_INVALID, dbus_g_type_get_collection ("GArray", G_TYPE_UINT), &result, G_TYPE_INVALID);
	if (*error) {
		return NULL;
	}
	*result_length1 = result->len;
	return (guint*) result->data;
}


char* _dynamic_GetChannelList1 (DBusGProxy* self, guint param1, GError** error) {
	char* result;
	dbus_g_proxy_call (self, "GetChannelList", error, G_TYPE_UINT, param1, G_TYPE_INVALID, G_TYPE_STRING, &result, G_TYPE_INVALID);
	if (*error) {
		return NULL;
	}
	return result;
}


char* _dynamic_GetDeviceGroupName2 (DBusGProxy* self, guint param1, GError** error) {
	char* result;
	dbus_g_proxy_call (self, "GetDeviceGroupName", error, G_TYPE_UINT, param1, G_TYPE_INVALID, G_TYPE_STRING, &result, G_TYPE_INVALID);
	if (*error) {
		return NULL;
	}
	return result;
}


/* Private methods*/
static void rygel_dvb_root_container_fetch_device_groups (RygelDVBRootContainer* self, DBusGConnection* connection, GError** error) {
	GError * _inner_error_;
	guint* _tmp0_;
	gint dev_groups_size;
	gint dev_groups_length1;
	guint* dev_groups;
	guint* _tmp3_;
	gint _tmp2__size;
	gint _tmp2__length1;
	gint _tmp1_;
	guint* _tmp2_;
	guint* _tmp4_;
	g_return_if_fail (self != NULL);
	g_return_if_fail (connection != NULL);
	_inner_error_ = NULL;
	_tmp0_ = NULL;
	dev_groups = (_tmp0_ = NULL, dev_groups_length1 = 0, dev_groups_size = dev_groups_length1, _tmp0_);
	_tmp3_ = NULL;
	_tmp2_ = (_tmp3_ = _dynamic_GetRegisteredDeviceGroups0 (self->manager, &_tmp1_, &_inner_error_), _tmp2__length1 = _tmp1_, _tmp2__size = _tmp2__length1, _tmp3_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		dev_groups = (g_free (dev_groups), NULL);
		return;
	}
	_tmp4_ = NULL;
	dev_groups = (_tmp4_ = _tmp2_, dev_groups = (g_free (dev_groups), NULL), dev_groups_length1 = _tmp2__length1, dev_groups_size = dev_groups_length1, _tmp4_);
	{
		guint* group_id_collection;
		int group_id_collection_length1;
		int group_id_it;
		group_id_collection = dev_groups;
		group_id_collection_length1 = dev_groups_length1;
		for (group_id_it = 0; group_id_it < dev_groups_length1; group_id_it = group_id_it + 1) {
			guint group_id;
			group_id = group_id_collection[group_id_it];
			{
				char* channel_list_path;
				char* group_name;
				char* _tmp5_;
				char* _tmp6_;
				char* _tmp7_;
				char* _tmp8_;
				DBusGProxy* channel_list;
				RygelDVBChannelGroup* _tmp9_;
				channel_list_path = NULL;
				group_name = NULL;
				_tmp5_ = _dynamic_GetChannelList1 (self->manager, group_id, &_inner_error_);
				if (_inner_error_ != NULL) {
					g_propagate_error (error, _inner_error_);
					channel_list_path = (g_free (channel_list_path), NULL);
					group_name = (g_free (group_name), NULL);
					dev_groups = (g_free (dev_groups), NULL);
					return;
				}
				_tmp6_ = NULL;
				channel_list_path = (_tmp6_ = _tmp5_, channel_list_path = (g_free (channel_list_path), NULL), _tmp6_);
				_tmp7_ = _dynamic_GetDeviceGroupName2 (self->manager, group_id, &_inner_error_);
				if (_inner_error_ != NULL) {
					g_propagate_error (error, _inner_error_);
					channel_list_path = (g_free (channel_list_path), NULL);
					group_name = (g_free (group_name), NULL);
					dev_groups = (g_free (dev_groups), NULL);
					return;
				}
				/* Get the name of the group*/
				_tmp8_ = NULL;
				group_name = (_tmp8_ = _tmp7_, group_name = (g_free (group_name), NULL), _tmp8_);
				/* Get a proxy to DVB ChannelList object*/
				channel_list = dbus_g_proxy_new_for_name (connection, RYGEL_DVB_ROOT_CONTAINER_DVB_SERVICE, channel_list_path, RYGEL_DVB_ROOT_CONTAINER_CHANNEL_LIST_IFACE);
				/* Create ChannelGroup for each registered device group*/
				_tmp9_ = NULL;
				gee_collection_add ((GeeCollection*) self->priv->groups, _tmp9_ = rygel_dvb_channel_group_new (group_id, group_name, (RygelMediaContainer*) self, channel_list));
				(_tmp9_ == NULL) ? NULL : (_tmp9_ = (g_object_unref (_tmp9_), NULL));
				channel_list_path = (g_free (channel_list_path), NULL);
				group_name = (g_free (group_name), NULL);
				(channel_list == NULL) ? NULL : (channel_list = (g_object_unref (channel_list), NULL));
			}
		}
	}
	((RygelMediaContainer*) self)->child_count = (guint) gee_collection_get_size ((GeeCollection*) self->priv->groups);
	dev_groups = (g_free (dev_groups), NULL);
}


static RygelDVBChannelGroup* rygel_dvb_root_container_find_group_by_id (RygelDVBRootContainer* self, const char* id) {
	RygelDVBChannelGroup* group;
	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (id != NULL, NULL);
	group = NULL;
	{
		GeeIterator* _tmp_it;
		_tmp_it = gee_iterable_iterator ((GeeIterable*) self->priv->groups);
		while (gee_iterator_next (_tmp_it)) {
			RygelDVBChannelGroup* tmp;
			tmp = (RygelDVBChannelGroup*) gee_iterator_get (_tmp_it);
			if (_vala_strcmp0 (id, ((RygelMediaObject*) tmp)->id) == 0) {
				RygelDVBChannelGroup* _tmp1_;
				RygelDVBChannelGroup* _tmp0_;
				_tmp1_ = NULL;
				_tmp0_ = NULL;
				group = (_tmp1_ = (_tmp0_ = tmp, (_tmp0_ == NULL) ? NULL : g_object_ref (_tmp0_)), (group == NULL) ? NULL : (group = (g_object_unref (group), NULL)), _tmp1_);
				(tmp == NULL) ? NULL : (tmp = (g_object_unref (tmp), NULL));
				break;
			}
			(tmp == NULL) ? NULL : (tmp = (g_object_unref (tmp), NULL));
		}
		(_tmp_it == NULL) ? NULL : (_tmp_it = (g_object_unref (_tmp_it), NULL));
	}
	return group;
}


static RygelMediaObject* rygel_dvb_root_container_find_channel_by_id (RygelDVBRootContainer* self, const char* id, GError** error) {
	RygelMediaObject* channel;
	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (id != NULL, NULL);
	channel = NULL;
	{
		GeeIterator* _group_it;
		_group_it = gee_iterable_iterator ((GeeIterable*) self->priv->groups);
		while (gee_iterator_next (_group_it)) {
			RygelDVBChannelGroup* group;
			RygelMediaObject* _tmp0_;
			group = (RygelDVBChannelGroup*) gee_iterator_get (_group_it);
			_tmp0_ = NULL;
			channel = (_tmp0_ = rygel_dvb_channel_group_find_object_sync (group, id), (channel == NULL) ? NULL : (channel = (g_object_unref (channel), NULL)), _tmp0_);
			if (channel != NULL) {
				(group == NULL) ? NULL : (group = (g_object_unref (group), NULL));
				break;
			}
			(group == NULL) ? NULL : (group = (g_object_unref (group), NULL));
		}
		(_group_it == NULL) ? NULL : (_group_it = (g_object_unref (_group_it), NULL));
	}
	return channel;
}


static void rygel_dvb_root_container_class_init (RygelDVBRootContainerClass * klass) {
	rygel_dvb_root_container_parent_class = g_type_class_peek_parent (klass);
	g_type_class_add_private (klass, sizeof (RygelDVBRootContainerPrivate));
	RYGEL_MEDIA_CONTAINER_CLASS (klass)->get_children = rygel_dvb_root_container_real_get_children;
	RYGEL_MEDIA_CONTAINER_CLASS (klass)->get_children_finish = rygel_dvb_root_container_real_get_children_finish;
	RYGEL_MEDIA_CONTAINER_CLASS (klass)->find_object = rygel_dvb_root_container_real_find_object;
	RYGEL_MEDIA_CONTAINER_CLASS (klass)->find_object_finish = rygel_dvb_root_container_real_find_object_finish;
	G_OBJECT_CLASS (klass)->finalize = rygel_dvb_root_container_finalize;
}


static void rygel_dvb_root_container_instance_init (RygelDVBRootContainer * self) {
	self->priv = RYGEL_DVB_ROOT_CONTAINER_GET_PRIVATE (self);
}


static void rygel_dvb_root_container_finalize (GObject* obj) {
	RygelDVBRootContainer * self;
	self = RYGEL_DVB_ROOT_CONTAINER (obj);
	(self->manager == NULL) ? NULL : (self->manager = (g_object_unref (self->manager), NULL));
	(self->priv->groups == NULL) ? NULL : (self->priv->groups = (g_object_unref (self->priv->groups), NULL));
	G_OBJECT_CLASS (rygel_dvb_root_container_parent_class)->finalize (obj);
}


GType rygel_dvb_root_container_get_type (void) {
	static GType rygel_dvb_root_container_type_id = 0;
	if (rygel_dvb_root_container_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (RygelDVBRootContainerClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) rygel_dvb_root_container_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (RygelDVBRootContainer), 0, (GInstanceInitFunc) rygel_dvb_root_container_instance_init, NULL };
		rygel_dvb_root_container_type_id = g_type_register_static (RYGEL_TYPE_MEDIA_CONTAINER, "RygelDVBRootContainer", &g_define_type_info, 0);
	}
	return rygel_dvb_root_container_type_id;
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




