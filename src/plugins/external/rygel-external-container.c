/*
 * Copyright (C) 2009 Zeeshan Ali (Khattak) <zeeshanak@gnome.org>.
 * Copyright (C) 2009 Nokia Corporation, all rights reserved.
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
#include <stdlib.h>
#include <string.h>
#include <gee/arraylist.h>
#include <gee/list.h>
#include <gio/gio.h>
#include <gee/iterable.h>
#include <gee/iterator.h>
#include <gee/collection.h>


#define RYGEL_TYPE_EXTERNAL_CONTAINER (rygel_external_container_get_type ())
#define RYGEL_EXTERNAL_CONTAINER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_EXTERNAL_CONTAINER, RygelExternalContainer))
#define RYGEL_EXTERNAL_CONTAINER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_EXTERNAL_CONTAINER, RygelExternalContainerClass))
#define RYGEL_IS_EXTERNAL_CONTAINER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_EXTERNAL_CONTAINER))
#define RYGEL_IS_EXTERNAL_CONTAINER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_EXTERNAL_CONTAINER))
#define RYGEL_EXTERNAL_CONTAINER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_EXTERNAL_CONTAINER, RygelExternalContainerClass))

typedef struct _RygelExternalContainer RygelExternalContainer;
typedef struct _RygelExternalContainerClass RygelExternalContainerClass;
typedef struct _RygelExternalContainerPrivate RygelExternalContainerPrivate;

#define RYGEL_TYPE_EXTERNAL_ITEM (rygel_external_item_get_type ())
#define RYGEL_EXTERNAL_ITEM(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_EXTERNAL_ITEM, RygelExternalItem))
#define RYGEL_EXTERNAL_ITEM_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_EXTERNAL_ITEM, RygelExternalItemClass))
#define RYGEL_IS_EXTERNAL_ITEM(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_EXTERNAL_ITEM))
#define RYGEL_IS_EXTERNAL_ITEM_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_EXTERNAL_ITEM))
#define RYGEL_EXTERNAL_ITEM_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_EXTERNAL_ITEM, RygelExternalItemClass))

typedef struct _RygelExternalItem RygelExternalItem;
typedef struct _RygelExternalItemClass RygelExternalItemClass;

/**
 * Represents an external container.
 */
struct _RygelExternalContainer {
	RygelMediaContainer parent_instance;
	RygelExternalContainerPrivate * priv;
	DBusGProxy* actual_container;
	DBusGProxy* props;
	char* host_ip;
	char* service_name;
};

struct _RygelExternalContainerClass {
	RygelMediaContainerClass parent_class;
};

struct _RygelExternalContainerPrivate {
	char* object_path;
	GeeArrayList* media_objects;
};



GType rygel_external_container_get_type (void);
#define RYGEL_EXTERNAL_CONTAINER_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), RYGEL_TYPE_EXTERNAL_CONTAINER, RygelExternalContainerPrivate))
enum  {
	RYGEL_EXTERNAL_CONTAINER_DUMMY_PROPERTY
};
static char* rygel_external_container_PROPS_IFACE;
static char* rygel_external_container_PROPS_IFACE = NULL;
#define RYGEL_EXTERNAL_CONTAINER_OBJECT_IFACE "org.gnome.UPnP.MediaObject1"
#define RYGEL_EXTERNAL_CONTAINER_CONTAINER_IFACE "org.gnome.UPnP.MediaContainer1"
#define RYGEL_EXTERNAL_CONTAINER_ITEM_IFACE "org.gnome.UPnP.MediaItem1"
void _dynamic_Get0 (DBusGProxy* self, const char* param1, const char* param2, GValue* param3, GError** error);
char* rygel_external_container_substitute_keywords (RygelExternalContainer* self, const char* title);
static void rygel_external_container_fetch_media_objects (RygelExternalContainer* self, GError** error);
static void rygel_external_container_on_container_updated (RygelExternalContainer* self, DBusGProxy* actual_container);
static void _rygel_external_container_on_container_updated_dynamic_Updated0_ (DBusGProxy* _sender, gpointer self);
void _dynamic_Updated1_connect (gpointer obj, const char * signal_name, GCallback handler, gpointer data);
RygelExternalContainer* rygel_external_container_new (const char* id, const char* service_name, const char* object_path, const char* host_ip, RygelExternalContainer* parent);
RygelExternalContainer* rygel_external_container_construct (GType object_type, const char* id, const char* service_name, const char* object_path, const char* host_ip, RygelExternalContainer* parent);
RygelExternalContainer* rygel_external_container_new (const char* id, const char* service_name, const char* object_path, const char* host_ip, RygelExternalContainer* parent);
static void rygel_external_container_real_get_children (RygelMediaContainer* base, guint offset, guint max_count, GCancellable* cancellable, GAsyncReadyCallback callback, void* callback_target);
static GeeList* rygel_external_container_real_get_children_finish (RygelMediaContainer* base, GAsyncResult* res, GError** error);
static RygelMediaObject* rygel_external_container_find_object_sync (RygelExternalContainer* self, const char* id);
static void rygel_external_container_real_find_object (RygelMediaContainer* base, const char* id, GCancellable* cancellable, GAsyncReadyCallback callback, void* callback_target);
static RygelMediaObject* rygel_external_container_real_find_object_finish (RygelMediaContainer* base, GAsyncResult* res, GError** error);
GHashTable* _dynamic_GetAll1 (DBusGProxy* self, const char* param1, GError** error);
static GValue* _g_value_dup (GValue* self);
RygelExternalItem* rygel_external_item_new (const char* object_path, RygelExternalContainer* parent, GError** error);
RygelExternalItem* rygel_external_item_construct (GType object_type, const char* object_path, RygelExternalContainer* parent, GError** error);
GType rygel_external_item_get_type (void);
static gpointer rygel_external_container_parent_class = NULL;
static void rygel_external_container_finalize (GObject* obj);
static int _vala_strcmp0 (const char * str1, const char * str2);



void _dynamic_Get0 (DBusGProxy* self, const char* param1, const char* param2, GValue* param3, GError** error) {
	dbus_g_proxy_call (self, "Get", error, G_TYPE_STRING, param1, G_TYPE_STRING, param2, G_TYPE_INVALID, G_TYPE_VALUE, param3, G_TYPE_INVALID);
	if (*error) {
		return;
	}
}


static void _rygel_external_container_on_container_updated_dynamic_Updated0_ (DBusGProxy* _sender, gpointer self) {
	rygel_external_container_on_container_updated (self, _sender);
}


void _dynamic_Updated1_connect (gpointer obj, const char * signal_name, GCallback handler, gpointer data) {
	dbus_g_object_register_marshaller (g_cclosure_marshal_VOID__VOID, G_TYPE_NONE, G_TYPE_INVALID);
	dbus_g_proxy_add_signal (obj, "Updated", G_TYPE_INVALID);
	dbus_g_proxy_connect_signal (obj, signal_name, handler, data, NULL);
}


RygelExternalContainer* rygel_external_container_construct (GType object_type, const char* id, const char* service_name, const char* object_path, const char* host_ip, RygelExternalContainer* parent) {
	GError * _inner_error_;
	RygelExternalContainer * self;
	char* _tmp1_;
	const char* _tmp0_;
	char* _tmp3_;
	const char* _tmp2_;
	char* _tmp5_;
	const char* _tmp4_;
	GeeArrayList* _tmp6_;
	g_return_val_if_fail (id != NULL, NULL);
	g_return_val_if_fail (service_name != NULL, NULL);
	g_return_val_if_fail (object_path != NULL, NULL);
	g_return_val_if_fail (host_ip != NULL, NULL);
	_inner_error_ = NULL;
	self = (RygelExternalContainer*) rygel_media_container_construct (object_type, id, (RygelMediaContainer*) parent, "Uknown", (guint) 0);
	_tmp1_ = NULL;
	_tmp0_ = NULL;
	self->service_name = (_tmp1_ = (_tmp0_ = service_name, (_tmp0_ == NULL) ? NULL : g_strdup (_tmp0_)), self->service_name = (g_free (self->service_name), NULL), _tmp1_);
	_tmp3_ = NULL;
	_tmp2_ = NULL;
	self->priv->object_path = (_tmp3_ = (_tmp2_ = object_path, (_tmp2_ == NULL) ? NULL : g_strdup (_tmp2_)), self->priv->object_path = (g_free (self->priv->object_path), NULL), _tmp3_);
	_tmp5_ = NULL;
	_tmp4_ = NULL;
	self->host_ip = (_tmp5_ = (_tmp4_ = host_ip, (_tmp4_ == NULL) ? NULL : g_strdup (_tmp4_)), self->host_ip = (g_free (self->host_ip), NULL), _tmp5_);
	_tmp6_ = NULL;
	self->priv->media_objects = (_tmp6_ = gee_array_list_new (RYGEL_TYPE_MEDIA_OBJECT, (GBoxedCopyFunc) g_object_ref, g_object_unref, g_direct_equal), (self->priv->media_objects == NULL) ? NULL : (self->priv->media_objects = (g_object_unref (self->priv->media_objects), NULL)), _tmp6_);
	{
		DBusGConnection* connection;
		DBusGProxy* _tmp7_;
		GValue value = {0};
		GValue _tmp9_ = {0};
		GValue _tmp8_ = {0};
		char* _tmp10_;
		DBusGProxy* _tmp11_;
		connection = dbus_g_bus_get (DBUS_BUS_SESSION, &_inner_error_);
		if (_inner_error_ != NULL) {
			if (_inner_error_->domain == DBUS_GERROR) {
				goto __catch0_dbus_gerror;
			}
			goto __finally0;
		}
		/* Create proxy to MediaObject iface to get the display name through*/
		_tmp7_ = NULL;
		self->props = (_tmp7_ = dbus_g_proxy_new_for_name (connection, service_name, object_path, rygel_external_container_PROPS_IFACE), (self->props == NULL) ? NULL : (self->props = (g_object_unref (self->props), NULL)), _tmp7_);
		_dynamic_Get0 (self->props, RYGEL_EXTERNAL_CONTAINER_OBJECT_IFACE, "DisplayName", &_tmp8_, &_inner_error_);
		value = (_tmp9_ = _tmp8_, G_IS_VALUE (&value) ? (g_value_unset (&value), NULL) : NULL, _tmp9_);
		if (_inner_error_ != NULL) {
			(connection == NULL) ? NULL : (connection = (dbus_g_connection_unref (connection), NULL));
			G_IS_VALUE (&value) ? (g_value_unset (&value), NULL) : NULL;
			if (_inner_error_->domain == DBUS_GERROR) {
				goto __catch0_dbus_gerror;
			}
			goto __finally0;
		}
		_tmp10_ = NULL;
		((RygelMediaObject*) self)->title = (_tmp10_ = rygel_external_container_substitute_keywords (self, g_value_get_string (&value)), ((RygelMediaObject*) self)->title = (g_free (((RygelMediaObject*) self)->title), NULL), _tmp10_);
		/* Now proxy to MediaContainer iface for the rest of the stuff*/
		_tmp11_ = NULL;
		self->actual_container = (_tmp11_ = dbus_g_proxy_new_for_name (connection, service_name, object_path, RYGEL_EXTERNAL_CONTAINER_CONTAINER_IFACE), (self->actual_container == NULL) ? NULL : (self->actual_container = (g_object_unref (self->actual_container), NULL)), _tmp11_);
		rygel_external_container_fetch_media_objects (self, &_inner_error_);
		if (_inner_error_ != NULL) {
			(connection == NULL) ? NULL : (connection = (dbus_g_connection_unref (connection), NULL));
			G_IS_VALUE (&value) ? (g_value_unset (&value), NULL) : NULL;
			if (_inner_error_->domain == DBUS_GERROR) {
				goto __catch0_dbus_gerror;
			}
			goto __finally0;
		}
		_dynamic_Updated1_connect (self->actual_container, "Updated", (GCallback) _rygel_external_container_on_container_updated_dynamic_Updated0_, self);
		(connection == NULL) ? NULL : (connection = (dbus_g_connection_unref (connection), NULL));
		G_IS_VALUE (&value) ? (g_value_unset (&value), NULL) : NULL;
	}
	goto __finally0;
	__catch0_dbus_gerror:
	{
		GError * _error_;
		_error_ = _inner_error_;
		_inner_error_ = NULL;
		{
			g_critical ("rygel-external-container.vala:83: Failed to fetch root media objects: %s\n", _error_->message);
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


RygelExternalContainer* rygel_external_container_new (const char* id, const char* service_name, const char* object_path, const char* host_ip, RygelExternalContainer* parent) {
	return rygel_external_container_construct (RYGEL_TYPE_EXTERNAL_CONTAINER, id, service_name, object_path, host_ip, parent);
}


static void rygel_external_container_real_get_children (RygelMediaContainer* base, guint offset, guint max_count, GCancellable* cancellable, GAsyncReadyCallback callback, void* callback_target) {
	RygelExternalContainer * self;
	guint stop;
	GeeList* containers;
	RygelSimpleAsyncResult* res;
	GeeList* _tmp1_;
	GeeList* _tmp0_;
	self = (RygelExternalContainer*) base;
	stop = offset + max_count;
	stop = CLAMP (stop, (guint) 0, ((RygelMediaContainer*) self)->child_count);
	containers = gee_list_slice ((GeeList*) self->priv->media_objects, (gint) offset, (gint) stop);
	res = rygel_simple_async_result_new (GEE_TYPE_LIST, (GBoxedCopyFunc) g_object_ref, g_object_unref, (GObject*) self, callback, callback_target);
	_tmp1_ = NULL;
	_tmp0_ = NULL;
	res->data = (_tmp1_ = (_tmp0_ = containers, (_tmp0_ == NULL) ? NULL : g_object_ref (_tmp0_)), (res->data == NULL) ? NULL : (res->data = (g_object_unref (res->data), NULL)), _tmp1_);
	rygel_simple_async_result_complete_in_idle (res);
	(containers == NULL) ? NULL : (containers = (g_object_unref (containers), NULL));
	(res == NULL) ? NULL : (res = (g_object_unref (res), NULL));
}


static GeeList* rygel_external_container_real_get_children_finish (RygelMediaContainer* base, GAsyncResult* res, GError** error) {
	RygelExternalContainer * self;
	RygelSimpleAsyncResult* _tmp0_;
	RygelSimpleAsyncResult* simple_res;
	GeeList* _tmp1_;
	GeeList* _tmp2_;
	self = (RygelExternalContainer*) base;
	g_return_val_if_fail (res != NULL, NULL);
	_tmp0_ = NULL;
	simple_res = (_tmp0_ = RYGEL_SIMPLE_ASYNC_RESULT (res), (_tmp0_ == NULL) ? NULL : g_object_ref (_tmp0_));
	_tmp1_ = NULL;
	_tmp2_ = NULL;
	return (_tmp2_ = (_tmp1_ = (GeeList*) simple_res->data, (_tmp1_ == NULL) ? NULL : g_object_ref (_tmp1_)), (simple_res == NULL) ? NULL : (simple_res = (g_object_unref (simple_res), NULL)), _tmp2_);
}


static void rygel_external_container_real_find_object (RygelMediaContainer* base, const char* id, GCancellable* cancellable, GAsyncReadyCallback callback, void* callback_target) {
	RygelExternalContainer * self;
	RygelMediaObject* media_object;
	RygelSimpleAsyncResult* res;
	RygelMediaObject* _tmp1_;
	RygelMediaObject* _tmp0_;
	self = (RygelExternalContainer*) base;
	g_return_if_fail (id != NULL);
	media_object = rygel_external_container_find_object_sync (self, id);
	res = rygel_simple_async_result_new (RYGEL_TYPE_MEDIA_OBJECT, (GBoxedCopyFunc) g_object_ref, g_object_unref, (GObject*) self, callback, callback_target);
	_tmp1_ = NULL;
	_tmp0_ = NULL;
	res->data = (_tmp1_ = (_tmp0_ = media_object, (_tmp0_ == NULL) ? NULL : g_object_ref (_tmp0_)), (res->data == NULL) ? NULL : (res->data = (g_object_unref (res->data), NULL)), _tmp1_);
	rygel_simple_async_result_complete_in_idle (res);
	(media_object == NULL) ? NULL : (media_object = (g_object_unref (media_object), NULL));
	(res == NULL) ? NULL : (res = (g_object_unref (res), NULL));
}


static RygelMediaObject* rygel_external_container_real_find_object_finish (RygelMediaContainer* base, GAsyncResult* res, GError** error) {
	RygelExternalContainer * self;
	RygelSimpleAsyncResult* _tmp0_;
	RygelSimpleAsyncResult* simple_res;
	RygelMediaObject* _tmp1_;
	RygelMediaObject* _tmp2_;
	self = (RygelExternalContainer*) base;
	g_return_val_if_fail (res != NULL, NULL);
	_tmp0_ = NULL;
	simple_res = (_tmp0_ = RYGEL_SIMPLE_ASYNC_RESULT (res), (_tmp0_ == NULL) ? NULL : g_object_ref (_tmp0_));
	_tmp1_ = NULL;
	_tmp2_ = NULL;
	return (_tmp2_ = (_tmp1_ = (RygelMediaObject*) simple_res->data, (_tmp1_ == NULL) ? NULL : g_object_ref (_tmp1_)), (simple_res == NULL) ? NULL : (simple_res = (g_object_unref (simple_res), NULL)), _tmp2_);
}


static char* string_replace (const char* self, const char* old, const char* replacement) {
	GError * _inner_error_;
	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (old != NULL, NULL);
	g_return_val_if_fail (replacement != NULL, NULL);
	_inner_error_ = NULL;
	{
		char* _tmp0_;
		GRegex* _tmp1_;
		GRegex* regex;
		char* _tmp2_;
		char* _tmp3_;
		_tmp0_ = NULL;
		_tmp1_ = NULL;
		regex = (_tmp1_ = g_regex_new (_tmp0_ = g_regex_escape_string (old, -1), 0, 0, &_inner_error_), _tmp0_ = (g_free (_tmp0_), NULL), _tmp1_);
		if (_inner_error_ != NULL) {
			if (_inner_error_->domain == G_REGEX_ERROR) {
				goto __catch1_g_regex_error;
			}
			goto __finally1;
		}
		_tmp2_ = g_regex_replace_literal (regex, self, (glong) (-1), 0, replacement, 0, &_inner_error_);
		if (_inner_error_ != NULL) {
			(regex == NULL) ? NULL : (regex = (g_regex_unref (regex), NULL));
			if (_inner_error_->domain == G_REGEX_ERROR) {
				goto __catch1_g_regex_error;
			}
			goto __finally1;
		}
		_tmp3_ = NULL;
		return (_tmp3_ = _tmp2_, (regex == NULL) ? NULL : (regex = (g_regex_unref (regex), NULL)), _tmp3_);
	}
	goto __finally1;
	__catch1_g_regex_error:
	{
		GError * e;
		e = _inner_error_;
		_inner_error_ = NULL;
		{
			g_assert_not_reached ();
			(e == NULL) ? NULL : (e = (g_error_free (e), NULL));
		}
	}
	__finally1:
	if (_inner_error_ != NULL) {
		g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, _inner_error_->message);
		g_clear_error (&_inner_error_);
		return NULL;
	}
}


char* rygel_external_container_substitute_keywords (RygelExternalContainer* self, const char* title) {
	char* new_title;
	char* _tmp0_;
	char* _tmp1_;
	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (title != NULL, NULL);
	new_title = string_replace (title, "@REALNAME@", g_get_real_name ());
	_tmp0_ = NULL;
	new_title = (_tmp0_ = string_replace (new_title, "@USERNAME@", g_get_user_name ()), new_title = (g_free (new_title), NULL), _tmp0_);
	_tmp1_ = NULL;
	new_title = (_tmp1_ = string_replace (new_title, "@HOSTNAME@", g_get_host_name ()), new_title = (g_free (new_title), NULL), _tmp1_);
	return new_title;
}


/* Private methods*/
static RygelMediaObject* rygel_external_container_find_object_sync (RygelExternalContainer* self, const char* id) {
	RygelMediaObject* obj;
	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (id != NULL, NULL);
	obj = NULL;
	{
		GeeIterator* _tmp_it;
		_tmp_it = gee_iterable_iterator ((GeeIterable*) self->priv->media_objects);
		while (gee_iterator_next (_tmp_it)) {
			RygelMediaObject* tmp;
			tmp = (RygelMediaObject*) gee_iterator_get (_tmp_it);
			if (_vala_strcmp0 (id, tmp->id) == 0) {
				RygelMediaObject* _tmp1_;
				RygelMediaObject* _tmp0_;
				_tmp1_ = NULL;
				_tmp0_ = NULL;
				obj = (_tmp1_ = (_tmp0_ = tmp, (_tmp0_ == NULL) ? NULL : g_object_ref (_tmp0_)), (obj == NULL) ? NULL : (obj = (g_object_unref (obj), NULL)), _tmp1_);
			} else {
				if (RYGEL_IS_EXTERNAL_CONTAINER (tmp)) {
					RygelExternalContainer* _tmp2_;
					RygelExternalContainer* container;
					RygelMediaObject* _tmp3_;
					/* Check it's children*/
					_tmp2_ = NULL;
					container = (_tmp2_ = RYGEL_EXTERNAL_CONTAINER (tmp), (_tmp2_ == NULL) ? NULL : g_object_ref (_tmp2_));
					_tmp3_ = NULL;
					obj = (_tmp3_ = rygel_external_container_find_object_sync (container, id), (obj == NULL) ? NULL : (obj = (g_object_unref (obj), NULL)), _tmp3_);
					(container == NULL) ? NULL : (container = (g_object_unref (container), NULL));
				}
			}
			if (obj != NULL) {
				(tmp == NULL) ? NULL : (tmp = (g_object_unref (tmp), NULL));
				break;
			}
			(tmp == NULL) ? NULL : (tmp = (g_object_unref (tmp), NULL));
		}
		(_tmp_it == NULL) ? NULL : (_tmp_it = (g_object_unref (_tmp_it), NULL));
	}
	return obj;
}


GHashTable* _dynamic_GetAll1 (DBusGProxy* self, const char* param1, GError** error) {
	GHashTable* result;
	dbus_g_proxy_call (self, "GetAll", error, G_TYPE_STRING, param1, G_TYPE_INVALID, dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE), &result, G_TYPE_INVALID);
	if (*error) {
		return NULL;
	}
	return result;
}


static GValue* _g_value_dup (GValue* self) {
	return g_boxed_copy (G_TYPE_VALUE, self);
}


static void rygel_external_container_fetch_media_objects (RygelExternalContainer* self, GError** error) {
	GError * _inner_error_;
	GHashTable* all_props;
	GValue* _tmp0_;
	GValue* value;
	GPtrArray* obj_paths;
	GValue* _tmp3_;
	GValue* _tmp2_;
	g_return_if_fail (self != NULL);
	_inner_error_ = NULL;
	all_props = _dynamic_GetAll1 (self->props, RYGEL_EXTERNAL_CONTAINER_CONTAINER_IFACE, &_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		return;
	}
	_tmp0_ = NULL;
	value = (_tmp0_ = (GValue*) g_hash_table_lookup (all_props, "Containers"), (_tmp0_ == NULL) ? NULL : _g_value_dup (_tmp0_));
	obj_paths = (GPtrArray*) g_value_get_boxed (value);
	if (obj_paths->len > 0) {
		{
			gint i;
			i = 0;
			for (; i < obj_paths->len; i++) {
				const char* _tmp1_;
				char* obj_path;
				RygelExternalContainer* container;
				_tmp1_ = NULL;
				obj_path = (_tmp1_ = (const char*) obj_paths->pdata[i], (_tmp1_ == NULL) ? NULL : g_strdup (_tmp1_));
				container = rygel_external_container_new (obj_path, self->service_name, obj_path, self->host_ip, self);
				gee_collection_add ((GeeCollection*) self->priv->media_objects, (RygelMediaObject*) container);
				obj_path = (g_free (obj_path), NULL);
				(container == NULL) ? NULL : (container = (g_object_unref (container), NULL));
			}
		}
	}
	_tmp3_ = NULL;
	_tmp2_ = NULL;
	value = (_tmp3_ = (_tmp2_ = (GValue*) g_hash_table_lookup (all_props, "Items"), (_tmp2_ == NULL) ? NULL : _g_value_dup (_tmp2_)), (value == NULL) ? NULL : (value = (g_free (value), NULL)), _tmp3_);
	obj_paths = (GPtrArray*) g_value_get_boxed (value);
	if (obj_paths->len > 0) {
		{
			gint i;
			i = 0;
			for (; i < obj_paths->len; i++) {
				const char* _tmp4_;
				char* obj_path;
				RygelExternalItem* _tmp5_;
				_tmp4_ = NULL;
				obj_path = (_tmp4_ = (const char*) obj_paths->pdata[i], (_tmp4_ == NULL) ? NULL : g_strdup (_tmp4_));
				_tmp5_ = NULL;
				gee_collection_add ((GeeCollection*) self->priv->media_objects, (RygelMediaObject*) (_tmp5_ = rygel_external_item_new (obj_path, self, &_inner_error_)));
				(_tmp5_ == NULL) ? NULL : (_tmp5_ = (g_object_unref (_tmp5_), NULL));
				obj_path = (g_free (obj_path), NULL);
			}
		}
	}
	((RygelMediaContainer*) self)->child_count = (guint) gee_collection_get_size ((GeeCollection*) self->priv->media_objects);
	(all_props == NULL) ? NULL : (all_props = (g_hash_table_unref (all_props), NULL));
	(value == NULL) ? NULL : (value = (g_free (value), NULL));
}


static void rygel_external_container_on_container_updated (RygelExternalContainer* self, DBusGProxy* actual_container) {
	GError * _inner_error_;
	g_return_if_fail (self != NULL);
	g_return_if_fail (actual_container != NULL);
	_inner_error_ = NULL;
	/* Re-fetch the objects*/
	gee_collection_clear ((GeeCollection*) self->priv->media_objects);
	{
		rygel_external_container_fetch_media_objects (self, &_inner_error_);
		if (_inner_error_ != NULL) {
			goto __catch2_g_error;
			goto __finally2;
		}
	}
	goto __finally2;
	__catch2_g_error:
	{
		GError * err;
		err = _inner_error_;
		_inner_error_ = NULL;
		{
			g_warning ("rygel-external-container.vala:197: Failed to re-fetch media objects: %s\n", err->message);
			(err == NULL) ? NULL : (err = (g_error_free (err), NULL));
		}
	}
	__finally2:
	if (_inner_error_ != NULL) {
		g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, _inner_error_->message);
		g_clear_error (&_inner_error_);
		return;
	}
	/* and signal the clients*/
	rygel_media_container_updated ((RygelMediaContainer*) self);
}


static void rygel_external_container_class_init (RygelExternalContainerClass * klass) {
	rygel_external_container_parent_class = g_type_class_peek_parent (klass);
	g_type_class_add_private (klass, sizeof (RygelExternalContainerPrivate));
	RYGEL_MEDIA_CONTAINER_CLASS (klass)->get_children = rygel_external_container_real_get_children;
	RYGEL_MEDIA_CONTAINER_CLASS (klass)->get_children_finish = rygel_external_container_real_get_children_finish;
	RYGEL_MEDIA_CONTAINER_CLASS (klass)->find_object = rygel_external_container_real_find_object;
	RYGEL_MEDIA_CONTAINER_CLASS (klass)->find_object_finish = rygel_external_container_real_find_object_finish;
	G_OBJECT_CLASS (klass)->finalize = rygel_external_container_finalize;
	rygel_external_container_PROPS_IFACE = g_strdup ("org.freedesktop.DBus.Properties");
}


static void rygel_external_container_instance_init (RygelExternalContainer * self) {
	self->priv = RYGEL_EXTERNAL_CONTAINER_GET_PRIVATE (self);
}


static void rygel_external_container_finalize (GObject* obj) {
	RygelExternalContainer * self;
	self = RYGEL_EXTERNAL_CONTAINER (obj);
	(self->actual_container == NULL) ? NULL : (self->actual_container = (g_object_unref (self->actual_container), NULL));
	(self->props == NULL) ? NULL : (self->props = (g_object_unref (self->props), NULL));
	self->host_ip = (g_free (self->host_ip), NULL);
	self->service_name = (g_free (self->service_name), NULL);
	self->priv->object_path = (g_free (self->priv->object_path), NULL);
	(self->priv->media_objects == NULL) ? NULL : (self->priv->media_objects = (g_object_unref (self->priv->media_objects), NULL));
	G_OBJECT_CLASS (rygel_external_container_parent_class)->finalize (obj);
}


GType rygel_external_container_get_type (void) {
	static GType rygel_external_container_type_id = 0;
	if (rygel_external_container_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (RygelExternalContainerClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) rygel_external_container_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (RygelExternalContainer), 0, (GInstanceInitFunc) rygel_external_container_instance_init, NULL };
		rygel_external_container_type_id = g_type_register_static (RYGEL_TYPE_MEDIA_CONTAINER, "RygelExternalContainer", &g_define_type_info, 0);
	}
	return rygel_external_container_type_id;
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




