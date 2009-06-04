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
#include <gee/collection.h>


#define RYGEL_TYPE_EXTERNAL_ITEM (rygel_external_item_get_type ())
#define RYGEL_EXTERNAL_ITEM(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_EXTERNAL_ITEM, RygelExternalItem))
#define RYGEL_EXTERNAL_ITEM_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_EXTERNAL_ITEM, RygelExternalItemClass))
#define RYGEL_IS_EXTERNAL_ITEM(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_EXTERNAL_ITEM))
#define RYGEL_IS_EXTERNAL_ITEM_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_EXTERNAL_ITEM))
#define RYGEL_EXTERNAL_ITEM_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_EXTERNAL_ITEM, RygelExternalItemClass))

typedef struct _RygelExternalItem RygelExternalItem;
typedef struct _RygelExternalItemClass RygelExternalItemClass;
typedef struct _RygelExternalItemPrivate RygelExternalItemPrivate;

#define RYGEL_TYPE_EXTERNAL_CONTAINER (rygel_external_container_get_type ())
#define RYGEL_EXTERNAL_CONTAINER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_EXTERNAL_CONTAINER, RygelExternalContainer))
#define RYGEL_EXTERNAL_CONTAINER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_EXTERNAL_CONTAINER, RygelExternalContainerClass))
#define RYGEL_IS_EXTERNAL_CONTAINER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_EXTERNAL_CONTAINER))
#define RYGEL_IS_EXTERNAL_CONTAINER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_EXTERNAL_CONTAINER))
#define RYGEL_EXTERNAL_CONTAINER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_EXTERNAL_CONTAINER, RygelExternalContainerClass))

typedef struct _RygelExternalContainer RygelExternalContainer;
typedef struct _RygelExternalContainerClass RygelExternalContainerClass;
typedef struct _RygelExternalContainerPrivate RygelExternalContainerPrivate;

/**
 * Represents External item.
 */
struct _RygelExternalItem {
	RygelMediaItem parent_instance;
	RygelExternalItemPrivate * priv;
};

struct _RygelExternalItemClass {
	RygelMediaItemClass parent_class;
};

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



GType rygel_external_item_get_type (void);
enum  {
	RYGEL_EXTERNAL_ITEM_DUMMY_PROPERTY
};
static char* rygel_external_item_PROPS_IFACE;
static char* rygel_external_item_PROPS_IFACE = NULL;
static char* rygel_external_item_OBJECT_IFACE;
static char* rygel_external_item_OBJECT_IFACE = NULL;
static char* rygel_external_item_ITEM_IFACE;
static char* rygel_external_item_ITEM_IFACE = NULL;
GType rygel_external_container_get_type (void);
GHashTable* _dynamic_GetAll2 (DBusGProxy* self, const char* param1, GError** error);
static GValue* _g_value_dup (GValue* self);
char* rygel_external_container_substitute_keywords (RygelExternalContainer* self, const char* title);
void _dynamic_GetAll3 (DBusGProxy* self, const char* param1, GHashTable** param2, GError** error);
RygelExternalItem* rygel_external_item_new (const char* object_path, RygelExternalContainer* parent, GError** error);
RygelExternalItem* rygel_external_item_construct (GType object_type, const char* object_path, RygelExternalContainer* parent, GError** error);
RygelExternalItem* rygel_external_item_new (const char* object_path, RygelExternalContainer* parent, GError** error);
static gpointer rygel_external_item_parent_class = NULL;
static void rygel_external_item_finalize (GObject* obj);
static int _vala_strcmp0 (const char * str1, const char * str2);



GHashTable* _dynamic_GetAll2 (DBusGProxy* self, const char* param1, GError** error) {
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


void _dynamic_GetAll3 (DBusGProxy* self, const char* param1, GHashTable** param2, GError** error) {
	dbus_g_proxy_call (self, "GetAll", error, G_TYPE_STRING, param1, G_TYPE_INVALID, dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE), param2, G_TYPE_INVALID);
	if (*error) {
		return;
	}
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
				goto __catch3_g_regex_error;
			}
			goto __finally3;
		}
		_tmp2_ = g_regex_replace_literal (regex, self, (glong) (-1), 0, replacement, 0, &_inner_error_);
		if (_inner_error_ != NULL) {
			(regex == NULL) ? NULL : (regex = (g_regex_unref (regex), NULL));
			if (_inner_error_->domain == G_REGEX_ERROR) {
				goto __catch3_g_regex_error;
			}
			goto __finally3;
		}
		_tmp3_ = NULL;
		return (_tmp3_ = _tmp2_, (regex == NULL) ? NULL : (regex = (g_regex_unref (regex), NULL)), _tmp3_);
	}
	goto __finally3;
	__catch3_g_regex_error:
	{
		GError * e;
		e = _inner_error_;
		_inner_error_ = NULL;
		{
			g_assert_not_reached ();
			(e == NULL) ? NULL : (e = (g_error_free (e), NULL));
		}
	}
	__finally3:
	if (_inner_error_ != NULL) {
		g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, _inner_error_->message);
		g_clear_error (&_inner_error_);
		return NULL;
	}
}


RygelExternalItem* rygel_external_item_construct (GType object_type, const char* object_path, RygelExternalContainer* parent, GError** error) {
	GError * _inner_error_;
	RygelExternalItem * self;
	DBusGConnection* connection;
	DBusGProxy* props;
	GHashTable* object_props;
	GValue* _tmp0_;
	GValue* value;
	char* _tmp1_;
	GHashTable* item_props;
	GHashTable* _tmp3_;
	GHashTable* _tmp2_;
	GValue* _tmp5_;
	GValue* _tmp4_;
	const char* _tmp6_;
	char* type;
	GValue* _tmp12_;
	GValue* _tmp11_;
	char* _tmp14_;
	const char* _tmp13_;
	GValue* _tmp16_;
	GValue* _tmp15_;
	char** _tmp17_;
	gint uris_size;
	gint uris_length1;
	char** uris;
	g_return_val_if_fail (object_path != NULL, NULL);
	g_return_val_if_fail (parent != NULL, NULL);
	_inner_error_ = NULL;
	self = (RygelExternalItem*) rygel_media_item_construct (object_type, object_path, (RygelMediaContainer*) parent, "Unknown", "Unknown");
	connection = dbus_g_bus_get (DBUS_BUS_SESSION, &_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		return;
	}
	props = dbus_g_proxy_new_for_name (connection, parent->service_name, object_path, rygel_external_item_PROPS_IFACE);
	object_props = _dynamic_GetAll2 (props, rygel_external_item_OBJECT_IFACE, &_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		(connection == NULL) ? NULL : (connection = (dbus_g_connection_unref (connection), NULL));
		(props == NULL) ? NULL : (props = (g_object_unref (props), NULL));
		return;
	}
	_tmp0_ = NULL;
	value = (_tmp0_ = (GValue*) g_hash_table_lookup (object_props, "DisplayName"), (_tmp0_ == NULL) ? NULL : _g_value_dup (_tmp0_));
	_tmp1_ = NULL;
	((RygelMediaObject*) self)->title = (_tmp1_ = rygel_external_container_substitute_keywords (parent, g_value_get_string (value)), ((RygelMediaObject*) self)->title = (g_free (((RygelMediaObject*) self)->title), NULL), _tmp1_);
	item_props = NULL;
	_tmp3_ = NULL;
	_tmp2_ = NULL;
	_dynamic_GetAll3 (props, rygel_external_item_ITEM_IFACE, &_tmp2_, &_inner_error_);
	item_props = (_tmp3_ = _tmp2_, (item_props == NULL) ? NULL : (item_props = (g_hash_table_unref (item_props), NULL)), _tmp3_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		(connection == NULL) ? NULL : (connection = (dbus_g_connection_unref (connection), NULL));
		(props == NULL) ? NULL : (props = (g_object_unref (props), NULL));
		(object_props == NULL) ? NULL : (object_props = (g_hash_table_unref (object_props), NULL));
		(value == NULL) ? NULL : (value = (g_free (value), NULL));
		(item_props == NULL) ? NULL : (item_props = (g_hash_table_unref (item_props), NULL));
		return;
	}
	_tmp5_ = NULL;
	_tmp4_ = NULL;
	value = (_tmp5_ = (_tmp4_ = (GValue*) g_hash_table_lookup (item_props, "Type"), (_tmp4_ == NULL) ? NULL : _g_value_dup (_tmp4_)), (value == NULL) ? NULL : (value = (g_free (value), NULL)), _tmp5_);
	_tmp6_ = NULL;
	type = (_tmp6_ = g_value_get_string (value), (_tmp6_ == NULL) ? NULL : g_strdup (_tmp6_));
	if (_vala_strcmp0 (type, "audio") == 0) {
		char* _tmp7_;
		_tmp7_ = NULL;
		((RygelMediaItem*) self)->upnp_class = (_tmp7_ = g_strdup (RYGEL_MEDIA_ITEM_AUDIO_CLASS), ((RygelMediaItem*) self)->upnp_class = (g_free (((RygelMediaItem*) self)->upnp_class), NULL), _tmp7_);
	} else {
		if (_vala_strcmp0 (type, "music") == 0) {
			char* _tmp8_;
			_tmp8_ = NULL;
			((RygelMediaItem*) self)->upnp_class = (_tmp8_ = g_strdup (RYGEL_MEDIA_ITEM_MUSIC_CLASS), ((RygelMediaItem*) self)->upnp_class = (g_free (((RygelMediaItem*) self)->upnp_class), NULL), _tmp8_);
		} else {
			if (_vala_strcmp0 (type, "video") == 0) {
				char* _tmp9_;
				_tmp9_ = NULL;
				((RygelMediaItem*) self)->upnp_class = (_tmp9_ = g_strdup (RYGEL_MEDIA_ITEM_VIDEO_CLASS), ((RygelMediaItem*) self)->upnp_class = (g_free (((RygelMediaItem*) self)->upnp_class), NULL), _tmp9_);
			} else {
				char* _tmp10_;
				_tmp10_ = NULL;
				((RygelMediaItem*) self)->upnp_class = (_tmp10_ = g_strdup (RYGEL_MEDIA_ITEM_IMAGE_CLASS), ((RygelMediaItem*) self)->upnp_class = (g_free (((RygelMediaItem*) self)->upnp_class), NULL), _tmp10_);
			}
		}
	}
	_tmp12_ = NULL;
	_tmp11_ = NULL;
	value = (_tmp12_ = (_tmp11_ = (GValue*) g_hash_table_lookup (item_props, "MIMEType"), (_tmp11_ == NULL) ? NULL : _g_value_dup (_tmp11_)), (value == NULL) ? NULL : (value = (g_free (value), NULL)), _tmp12_);
	_tmp14_ = NULL;
	_tmp13_ = NULL;
	((RygelMediaItem*) self)->mime_type = (_tmp14_ = (_tmp13_ = g_value_get_string (value), (_tmp13_ == NULL) ? NULL : g_strdup (_tmp13_)), ((RygelMediaItem*) self)->mime_type = (g_free (((RygelMediaItem*) self)->mime_type), NULL), _tmp14_);
	_tmp16_ = NULL;
	_tmp15_ = NULL;
	value = (_tmp16_ = (_tmp15_ = (GValue*) g_hash_table_lookup (item_props, "URLs"), (_tmp15_ == NULL) ? NULL : _g_value_dup (_tmp15_)), (value == NULL) ? NULL : (value = (g_free (value), NULL)), _tmp16_);
	_tmp17_ = NULL;
	uris = (_tmp17_ = (char**) g_value_get_boxed (value), uris_length1 = -1, uris_size = uris_length1, _tmp17_);
	{
		gint i;
		i = 0;
		for (; uris[i] != NULL; i++) {
			char* tmp;
			tmp = string_replace (uris[i], "@ADDRESS@", parent->host_ip);
			gee_collection_add ((GeeCollection*) ((RygelMediaItem*) self)->uris, tmp);
			tmp = (g_free (tmp), NULL);
		}
	}
	(connection == NULL) ? NULL : (connection = (dbus_g_connection_unref (connection), NULL));
	(props == NULL) ? NULL : (props = (g_object_unref (props), NULL));
	(object_props == NULL) ? NULL : (object_props = (g_hash_table_unref (object_props), NULL));
	(value == NULL) ? NULL : (value = (g_free (value), NULL));
	(item_props == NULL) ? NULL : (item_props = (g_hash_table_unref (item_props), NULL));
	type = (g_free (type), NULL);
	return self;
}


RygelExternalItem* rygel_external_item_new (const char* object_path, RygelExternalContainer* parent, GError** error) {
	return rygel_external_item_construct (RYGEL_TYPE_EXTERNAL_ITEM, object_path, parent, error);
}


static void rygel_external_item_class_init (RygelExternalItemClass * klass) {
	rygel_external_item_parent_class = g_type_class_peek_parent (klass);
	G_OBJECT_CLASS (klass)->finalize = rygel_external_item_finalize;
	rygel_external_item_PROPS_IFACE = g_strdup ("org.freedesktop.DBus.Properties");
	rygel_external_item_OBJECT_IFACE = g_strdup ("org.gnome.UPnP.MediaObject1");
	rygel_external_item_ITEM_IFACE = g_strdup ("org.gnome.UPnP.MediaItem1");
}


static void rygel_external_item_instance_init (RygelExternalItem * self) {
}


static void rygel_external_item_finalize (GObject* obj) {
	RygelExternalItem * self;
	self = RYGEL_EXTERNAL_ITEM (obj);
	G_OBJECT_CLASS (rygel_external_item_parent_class)->finalize (obj);
}


GType rygel_external_item_get_type (void) {
	static GType rygel_external_item_type_id = 0;
	if (rygel_external_item_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (RygelExternalItemClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) rygel_external_item_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (RygelExternalItem), 0, (GInstanceInitFunc) rygel_external_item_instance_init, NULL };
		rygel_external_item_type_id = g_type_register_static (RYGEL_TYPE_MEDIA_ITEM, "RygelExternalItem", &g_define_type_info, 0);
	}
	return rygel_external_item_type_id;
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




