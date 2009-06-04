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
#include <stdlib.h>
#include <string.h>
#include <dbus/dbus-glib-lowlevel.h>
#include <dbus/dbus-glib.h>
#include <gee/list.h>
#include <gio/gio.h>
#include <gee/iterable.h>
#include <gee/iterator.h>
#include <gee/collection.h>


#define RYGEL_TYPE_DVB_CHANNEL_GROUP (rygel_dvb_channel_group_get_type ())
#define RYGEL_DVB_CHANNEL_GROUP(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_DVB_CHANNEL_GROUP, RygelDVBChannelGroup))
#define RYGEL_DVB_CHANNEL_GROUP_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_DVB_CHANNEL_GROUP, RygelDVBChannelGroupClass))
#define RYGEL_IS_DVB_CHANNEL_GROUP(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_DVB_CHANNEL_GROUP))
#define RYGEL_IS_DVB_CHANNEL_GROUP_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_DVB_CHANNEL_GROUP))
#define RYGEL_DVB_CHANNEL_GROUP_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_DVB_CHANNEL_GROUP, RygelDVBChannelGroupClass))

typedef struct _RygelDVBChannelGroup RygelDVBChannelGroup;
typedef struct _RygelDVBChannelGroupClass RygelDVBChannelGroupClass;
typedef struct _RygelDVBChannelGroupPrivate RygelDVBChannelGroupPrivate;

#define RYGEL_TYPE_DVB_CHANNEL (rygel_dvb_channel_get_type ())
#define RYGEL_DVB_CHANNEL(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_DVB_CHANNEL, RygelDVBChannel))
#define RYGEL_DVB_CHANNEL_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_DVB_CHANNEL, RygelDVBChannelClass))
#define RYGEL_IS_DVB_CHANNEL(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_DVB_CHANNEL))
#define RYGEL_IS_DVB_CHANNEL_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_DVB_CHANNEL))
#define RYGEL_DVB_CHANNEL_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_DVB_CHANNEL, RygelDVBChannelClass))

typedef struct _RygelDVBChannel RygelDVBChannel;
typedef struct _RygelDVBChannelClass RygelDVBChannelClass;

/**
 * Represents DVB channel group.
 */
struct _RygelDVBChannelGroup {
	RygelMediaContainer parent_instance;
	RygelDVBChannelGroupPrivate * priv;
};

struct _RygelDVBChannelGroupClass {
	RygelMediaContainerClass parent_class;
};

struct _RygelDVBChannelGroupPrivate {
	GeeArrayList* channels;
	guint gid;
};



GType rygel_dvb_channel_group_get_type (void);
GType rygel_dvb_channel_get_type (void);
#define RYGEL_DVB_CHANNEL_GROUP_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), RYGEL_TYPE_DVB_CHANNEL_GROUP, RygelDVBChannelGroupPrivate))
enum  {
	RYGEL_DVB_CHANNEL_GROUP_DUMMY_PROPERTY
};
extern DBusGProxy* rygel_dvb_channel_group_channel_list;
DBusGProxy* rygel_dvb_channel_group_channel_list = NULL;
#define RYGEL_DVB_CHANNEL_GROUP_GID_PREFIX "GroupID:"
static void rygel_dvb_channel_group_fetch_channels (RygelDVBChannelGroup* self);
RygelDVBChannelGroup* rygel_dvb_channel_group_new (guint gid, const char* title, RygelMediaContainer* parent, DBusGProxy* channel_list);
RygelDVBChannelGroup* rygel_dvb_channel_group_construct (GType object_type, guint gid, const char* title, RygelMediaContainer* parent, DBusGProxy* channel_list);
RygelDVBChannelGroup* rygel_dvb_channel_group_new (guint gid, const char* title, RygelMediaContainer* parent, DBusGProxy* channel_list);
static void rygel_dvb_channel_group_real_get_children (RygelMediaContainer* base, guint offset, guint max_count, GCancellable* cancellable, GAsyncReadyCallback callback, void* callback_target);
static GeeList* rygel_dvb_channel_group_real_get_children_finish (RygelMediaContainer* base, GAsyncResult* res, GError** error);
static void rygel_dvb_channel_group_real_find_object (RygelMediaContainer* base, const char* id, GCancellable* cancellable, GAsyncReadyCallback callback, void* callback_target);
static RygelMediaObject* rygel_dvb_channel_group_real_find_object_finish (RygelMediaContainer* base, GAsyncResult* res, GError** error);
RygelMediaObject* rygel_dvb_channel_group_find_object_sync (RygelDVBChannelGroup* self, const char* id);
guint* _dynamic_GetChannels3 (DBusGProxy* self, int* result_length1, GError** error);
RygelDVBChannel* rygel_dvb_channel_new (guint cid, RygelMediaContainer* parent, DBusGProxy* channel_list, GError** error);
RygelDVBChannel* rygel_dvb_channel_construct (GType object_type, guint cid, RygelMediaContainer* parent, DBusGProxy* channel_list, GError** error);
static gpointer rygel_dvb_channel_group_parent_class = NULL;
static void rygel_dvb_channel_group_finalize (GObject* obj);
static int _vala_strcmp0 (const char * str1, const char * str2);



/* The DVB Daemon Device Group ID */
RygelDVBChannelGroup* rygel_dvb_channel_group_construct (GType object_type, guint gid, const char* title, RygelMediaContainer* parent, DBusGProxy* channel_list) {
	RygelDVBChannelGroup * self;
	char* _tmp1_;
	char* _tmp0_;
	DBusGProxy* _tmp3_;
	DBusGProxy* _tmp2_;
	g_return_val_if_fail (title != NULL, NULL);
	g_return_val_if_fail (parent != NULL, NULL);
	g_return_val_if_fail (channel_list != NULL, NULL);
	_tmp1_ = NULL;
	_tmp0_ = NULL;
	self = (RygelDVBChannelGroup*) rygel_media_container_construct (object_type, _tmp1_ = g_strconcat (RYGEL_DVB_CHANNEL_GROUP_GID_PREFIX, _tmp0_ = g_strdup_printf ("%u", gid), NULL), parent, title, (guint) 0);
	_tmp1_ = (g_free (_tmp1_), NULL);
	_tmp0_ = (g_free (_tmp0_), NULL);
	self->priv->gid = gid;
	_tmp3_ = NULL;
	_tmp2_ = NULL;
	rygel_dvb_channel_group_channel_list = (_tmp3_ = (_tmp2_ = channel_list, (_tmp2_ == NULL) ? NULL : g_object_ref (_tmp2_)), (rygel_dvb_channel_group_channel_list == NULL) ? NULL : (rygel_dvb_channel_group_channel_list = (g_object_unref (rygel_dvb_channel_group_channel_list), NULL)), _tmp3_);
	rygel_dvb_channel_group_fetch_channels (self);
	return self;
}


RygelDVBChannelGroup* rygel_dvb_channel_group_new (guint gid, const char* title, RygelMediaContainer* parent, DBusGProxy* channel_list) {
	return rygel_dvb_channel_group_construct (RYGEL_TYPE_DVB_CHANNEL_GROUP, gid, title, parent, channel_list);
}


static void rygel_dvb_channel_group_real_get_children (RygelMediaContainer* base, guint offset, guint max_count, GCancellable* cancellable, GAsyncReadyCallback callback, void* callback_target) {
	RygelDVBChannelGroup * self;
	guint stop;
	GeeList* channels;
	RygelSimpleAsyncResult* res;
	GeeList* _tmp1_;
	GeeList* _tmp0_;
	self = (RygelDVBChannelGroup*) base;
	stop = offset + max_count;
	stop = CLAMP (stop, (guint) 0, ((RygelMediaContainer*) self)->child_count);
	channels = gee_list_slice ((GeeList*) self->priv->channels, (gint) offset, (gint) stop);
	res = rygel_simple_async_result_new (GEE_TYPE_LIST, (GBoxedCopyFunc) g_object_ref, g_object_unref, (GObject*) self, callback, callback_target);
	_tmp1_ = NULL;
	_tmp0_ = NULL;
	res->data = (_tmp1_ = (_tmp0_ = channels, (_tmp0_ == NULL) ? NULL : g_object_ref (_tmp0_)), (res->data == NULL) ? NULL : (res->data = (g_object_unref (res->data), NULL)), _tmp1_);
	rygel_simple_async_result_complete_in_idle (res);
	(channels == NULL) ? NULL : (channels = (g_object_unref (channels), NULL));
	(res == NULL) ? NULL : (res = (g_object_unref (res), NULL));
}


static GeeList* rygel_dvb_channel_group_real_get_children_finish (RygelMediaContainer* base, GAsyncResult* res, GError** error) {
	RygelDVBChannelGroup * self;
	RygelSimpleAsyncResult* _tmp0_;
	RygelSimpleAsyncResult* simple_res;
	GeeList* _tmp1_;
	GeeList* _tmp2_;
	self = (RygelDVBChannelGroup*) base;
	g_return_val_if_fail (res != NULL, NULL);
	_tmp0_ = NULL;
	simple_res = (_tmp0_ = RYGEL_SIMPLE_ASYNC_RESULT (res), (_tmp0_ == NULL) ? NULL : g_object_ref (_tmp0_));
	_tmp1_ = NULL;
	_tmp2_ = NULL;
	return (_tmp2_ = (_tmp1_ = (GeeList*) simple_res->data, (_tmp1_ == NULL) ? NULL : g_object_ref (_tmp1_)), (simple_res == NULL) ? NULL : (simple_res = (g_object_unref (simple_res), NULL)), _tmp2_);
}


static void rygel_dvb_channel_group_real_find_object (RygelMediaContainer* base, const char* id, GCancellable* cancellable, GAsyncReadyCallback callback, void* callback_target) {
	RygelDVBChannelGroup * self;
	RygelMediaObject* channel;
	RygelSimpleAsyncResult* res;
	RygelMediaObject* _tmp3_;
	RygelMediaObject* _tmp2_;
	self = (RygelDVBChannelGroup*) base;
	g_return_if_fail (id != NULL);
	channel = NULL;
	{
		GeeIterator* _tmp_it;
		_tmp_it = gee_iterable_iterator ((GeeIterable*) self->priv->channels);
		while (gee_iterator_next (_tmp_it)) {
			RygelDVBChannel* tmp;
			tmp = (RygelDVBChannel*) gee_iterator_get (_tmp_it);
			if (_vala_strcmp0 (((RygelMediaObject*) tmp)->id, id) == 0) {
				RygelMediaObject* _tmp1_;
				RygelMediaObject* _tmp0_;
				_tmp1_ = NULL;
				_tmp0_ = NULL;
				channel = (_tmp1_ = (_tmp0_ = (RygelMediaObject*) tmp, (_tmp0_ == NULL) ? NULL : g_object_ref (_tmp0_)), (channel == NULL) ? NULL : (channel = (g_object_unref (channel), NULL)), _tmp1_);
				(tmp == NULL) ? NULL : (tmp = (g_object_unref (tmp), NULL));
				break;
			}
			(tmp == NULL) ? NULL : (tmp = (g_object_unref (tmp), NULL));
		}
		(_tmp_it == NULL) ? NULL : (_tmp_it = (g_object_unref (_tmp_it), NULL));
	}
	res = rygel_simple_async_result_new (RYGEL_TYPE_MEDIA_OBJECT, (GBoxedCopyFunc) g_object_ref, g_object_unref, (GObject*) self, callback, callback_target);
	_tmp3_ = NULL;
	_tmp2_ = NULL;
	res->data = (_tmp3_ = (_tmp2_ = channel, (_tmp2_ == NULL) ? NULL : g_object_ref (_tmp2_)), (res->data == NULL) ? NULL : (res->data = (g_object_unref (res->data), NULL)), _tmp3_);
	rygel_simple_async_result_complete_in_idle (res);
	(channel == NULL) ? NULL : (channel = (g_object_unref (channel), NULL));
	(res == NULL) ? NULL : (res = (g_object_unref (res), NULL));
}


static RygelMediaObject* rygel_dvb_channel_group_real_find_object_finish (RygelMediaContainer* base, GAsyncResult* res, GError** error) {
	RygelDVBChannelGroup * self;
	RygelSimpleAsyncResult* _tmp0_;
	RygelSimpleAsyncResult* simple_res;
	RygelMediaObject* _tmp1_;
	RygelMediaObject* _tmp2_;
	self = (RygelDVBChannelGroup*) base;
	g_return_val_if_fail (res != NULL, NULL);
	_tmp0_ = NULL;
	simple_res = (_tmp0_ = RYGEL_SIMPLE_ASYNC_RESULT (res), (_tmp0_ == NULL) ? NULL : g_object_ref (_tmp0_));
	_tmp1_ = NULL;
	_tmp2_ = NULL;
	return (_tmp2_ = (_tmp1_ = (RygelMediaObject*) simple_res->data, (_tmp1_ == NULL) ? NULL : g_object_ref (_tmp1_)), (simple_res == NULL) ? NULL : (simple_res = (g_object_unref (simple_res), NULL)), _tmp2_);
}


RygelMediaObject* rygel_dvb_channel_group_find_object_sync (RygelDVBChannelGroup* self, const char* id) {
	RygelMediaObject* channel;
	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (id != NULL, NULL);
	channel = NULL;
	{
		GeeIterator* _tmp_it;
		_tmp_it = gee_iterable_iterator ((GeeIterable*) self->priv->channels);
		while (gee_iterator_next (_tmp_it)) {
			RygelDVBChannel* tmp;
			tmp = (RygelDVBChannel*) gee_iterator_get (_tmp_it);
			if (_vala_strcmp0 (((RygelMediaObject*) tmp)->id, id) == 0) {
				RygelMediaObject* _tmp1_;
				RygelMediaObject* _tmp0_;
				_tmp1_ = NULL;
				_tmp0_ = NULL;
				channel = (_tmp1_ = (_tmp0_ = (RygelMediaObject*) tmp, (_tmp0_ == NULL) ? NULL : g_object_ref (_tmp0_)), (channel == NULL) ? NULL : (channel = (g_object_unref (channel), NULL)), _tmp1_);
				(tmp == NULL) ? NULL : (tmp = (g_object_unref (tmp), NULL));
				break;
			}
			(tmp == NULL) ? NULL : (tmp = (g_object_unref (tmp), NULL));
		}
		(_tmp_it == NULL) ? NULL : (_tmp_it = (g_object_unref (_tmp_it), NULL));
	}
	return channel;
}


guint* _dynamic_GetChannels3 (DBusGProxy* self, int* result_length1, GError** error) {
	GArray* result;
	dbus_g_proxy_call (self, "GetChannels", error, G_TYPE_INVALID, dbus_g_type_get_collection ("GArray", G_TYPE_UINT), &result, G_TYPE_INVALID);
	if (*error) {
		return NULL;
	}
	*result_length1 = result->len;
	return (guint*) result->data;
}


static void rygel_dvb_channel_group_fetch_channels (RygelDVBChannelGroup* self) {
	GError * _inner_error_;
	GeeArrayList* _tmp0_;
	DBusGConnection* connection;
	guint* _tmp3_;
	gint channel_ids_size;
	gint channel_ids_length1;
	guint* channel_ids;
	g_return_if_fail (self != NULL);
	_inner_error_ = NULL;
	_tmp0_ = NULL;
	self->priv->channels = (_tmp0_ = gee_array_list_new (RYGEL_TYPE_DVB_CHANNEL, (GBoxedCopyFunc) g_object_ref, g_object_unref, g_direct_equal), (self->priv->channels == NULL) ? NULL : (self->priv->channels = (g_object_unref (self->priv->channels), NULL)), _tmp0_);
	connection = NULL;
	{
		DBusGConnection* _tmp1_;
		DBusGConnection* _tmp2_;
		_tmp1_ = dbus_g_bus_get (DBUS_BUS_SESSION, &_inner_error_);
		if (_inner_error_ != NULL) {
			if (_inner_error_->domain == DBUS_GERROR) {
				goto __catch1_dbus_gerror;
			}
			goto __finally1;
		}
		_tmp2_ = NULL;
		connection = (_tmp2_ = _tmp1_, (connection == NULL) ? NULL : (connection = (dbus_g_connection_unref (connection), NULL)), _tmp2_);
	}
	goto __finally1;
	__catch1_dbus_gerror:
	{
		GError * _error_;
		_error_ = _inner_error_;
		_inner_error_ = NULL;
		{
			g_critical ("rygel-dvb-channel-group.vala:123: Failed to connect to Session bus: %s\n", _error_->message);
			(_error_ == NULL) ? NULL : (_error_ = (g_error_free (_error_), NULL));
			(connection == NULL) ? NULL : (connection = (dbus_g_connection_unref (connection), NULL));
			return;
		}
	}
	__finally1:
	if (_inner_error_ != NULL) {
		(connection == NULL) ? NULL : (connection = (dbus_g_connection_unref (connection), NULL));
		g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, _inner_error_->message);
		g_clear_error (&_inner_error_);
		return;
	}
	_tmp3_ = NULL;
	channel_ids = (_tmp3_ = NULL, channel_ids_length1 = 0, channel_ids_size = channel_ids_length1, _tmp3_);
	{
		guint* _tmp6_;
		gint _tmp5__size;
		gint _tmp5__length1;
		gint _tmp4_;
		guint* _tmp5_;
		guint* _tmp7_;
		_tmp6_ = NULL;
		_tmp5_ = (_tmp6_ = _dynamic_GetChannels3 (rygel_dvb_channel_group_channel_list, &_tmp4_, &_inner_error_), _tmp5__length1 = _tmp4_, _tmp5__size = _tmp5__length1, _tmp6_);
		if (_inner_error_ != NULL) {
			goto __catch2_g_error;
			goto __finally2;
		}
		_tmp7_ = NULL;
		channel_ids = (_tmp7_ = _tmp5_, channel_ids = (g_free (channel_ids), NULL), channel_ids_length1 = _tmp5__length1, channel_ids_size = channel_ids_length1, _tmp7_);
	}
	goto __finally2;
	__catch2_g_error:
	{
		GError * _error_;
		_error_ = _inner_error_;
		_inner_error_ = NULL;
		{
			g_critical ("rygel-dvb-channel-group.vala:133: error: %s", _error_->message);
			(_error_ == NULL) ? NULL : (_error_ = (g_error_free (_error_), NULL));
			(connection == NULL) ? NULL : (connection = (dbus_g_connection_unref (connection), NULL));
			channel_ids = (g_free (channel_ids), NULL);
			return;
		}
	}
	__finally2:
	if (_inner_error_ != NULL) {
		(connection == NULL) ? NULL : (connection = (dbus_g_connection_unref (connection), NULL));
		channel_ids = (g_free (channel_ids), NULL);
		g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, _inner_error_->message);
		g_clear_error (&_inner_error_);
		return;
	}
	{
		guint* channel_id_collection;
		int channel_id_collection_length1;
		int channel_id_it;
		channel_id_collection = channel_ids;
		channel_id_collection_length1 = channel_ids_length1;
		for (channel_id_it = 0; channel_id_it < channel_ids_length1; channel_id_it = channel_id_it + 1) {
			guint channel_id;
			channel_id = channel_id_collection[channel_id_it];
			{
				{
					RygelDVBChannel* channel;
					channel = rygel_dvb_channel_new (channel_id, (RygelMediaContainer*) self, rygel_dvb_channel_group_channel_list, &_inner_error_);
					if (_inner_error_ != NULL) {
						goto __catch3_g_error;
						goto __finally3;
					}
					gee_collection_add ((GeeCollection*) self->priv->channels, channel);
					(channel == NULL) ? NULL : (channel = (g_object_unref (channel), NULL));
				}
				goto __finally3;
				__catch3_g_error:
				{
					GError * _error_;
					_error_ = _inner_error_;
					_inner_error_ = NULL;
					{
						g_critical ("rygel-dvb-channel-group.vala:145: Failed to create DVB Channel object: %s", _error_->message);
						(_error_ == NULL) ? NULL : (_error_ = (g_error_free (_error_), NULL));
					}
				}
				__finally3:
				if (_inner_error_ != NULL) {
					(connection == NULL) ? NULL : (connection = (dbus_g_connection_unref (connection), NULL));
					channel_ids = (g_free (channel_ids), NULL);
					g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, _inner_error_->message);
					g_clear_error (&_inner_error_);
					return;
				}
			}
		}
	}
	((RygelMediaContainer*) self)->child_count = (guint) gee_collection_get_size ((GeeCollection*) self->priv->channels);
	(connection == NULL) ? NULL : (connection = (dbus_g_connection_unref (connection), NULL));
	channel_ids = (g_free (channel_ids), NULL);
}


static void rygel_dvb_channel_group_class_init (RygelDVBChannelGroupClass * klass) {
	rygel_dvb_channel_group_parent_class = g_type_class_peek_parent (klass);
	g_type_class_add_private (klass, sizeof (RygelDVBChannelGroupPrivate));
	RYGEL_MEDIA_CONTAINER_CLASS (klass)->get_children = rygel_dvb_channel_group_real_get_children;
	RYGEL_MEDIA_CONTAINER_CLASS (klass)->get_children_finish = rygel_dvb_channel_group_real_get_children_finish;
	RYGEL_MEDIA_CONTAINER_CLASS (klass)->find_object = rygel_dvb_channel_group_real_find_object;
	RYGEL_MEDIA_CONTAINER_CLASS (klass)->find_object_finish = rygel_dvb_channel_group_real_find_object_finish;
	G_OBJECT_CLASS (klass)->finalize = rygel_dvb_channel_group_finalize;
}


static void rygel_dvb_channel_group_instance_init (RygelDVBChannelGroup * self) {
	self->priv = RYGEL_DVB_CHANNEL_GROUP_GET_PRIVATE (self);
}


static void rygel_dvb_channel_group_finalize (GObject* obj) {
	RygelDVBChannelGroup * self;
	self = RYGEL_DVB_CHANNEL_GROUP (obj);
	(self->priv->channels == NULL) ? NULL : (self->priv->channels = (g_object_unref (self->priv->channels), NULL));
	G_OBJECT_CLASS (rygel_dvb_channel_group_parent_class)->finalize (obj);
}


GType rygel_dvb_channel_group_get_type (void) {
	static GType rygel_dvb_channel_group_type_id = 0;
	if (rygel_dvb_channel_group_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (RygelDVBChannelGroupClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) rygel_dvb_channel_group_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (RygelDVBChannelGroup), 0, (GInstanceInitFunc) rygel_dvb_channel_group_instance_init, NULL };
		rygel_dvb_channel_group_type_id = g_type_register_static (RYGEL_TYPE_MEDIA_CONTAINER, "RygelDVBChannelGroup", &g_define_type_info, 0);
	}
	return rygel_dvb_channel_group_type_id;
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




