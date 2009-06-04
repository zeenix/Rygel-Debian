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
#include <stdlib.h>
#include <string.h>
#include <dbus/dbus-glib-lowlevel.h>
#include <dbus/dbus-glib.h>


#define TYPE_EXTERNAL_PLUGIN (external_plugin_get_type ())
#define EXTERNAL_PLUGIN(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_EXTERNAL_PLUGIN, ExternalPlugin))
#define EXTERNAL_PLUGIN_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_EXTERNAL_PLUGIN, ExternalPluginClass))
#define IS_EXTERNAL_PLUGIN(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_EXTERNAL_PLUGIN))
#define IS_EXTERNAL_PLUGIN_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_EXTERNAL_PLUGIN))
#define EXTERNAL_PLUGIN_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_EXTERNAL_PLUGIN, ExternalPluginClass))

typedef struct _ExternalPlugin ExternalPlugin;
typedef struct _ExternalPluginClass ExternalPluginClass;
typedef struct _ExternalPluginPrivate ExternalPluginPrivate;

#define RYGEL_TYPE_EXTERNAL_CONTENT_DIR (rygel_external_content_dir_get_type ())
#define RYGEL_EXTERNAL_CONTENT_DIR(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_EXTERNAL_CONTENT_DIR, RygelExternalContentDir))
#define RYGEL_EXTERNAL_CONTENT_DIR_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_EXTERNAL_CONTENT_DIR, RygelExternalContentDirClass))
#define RYGEL_IS_EXTERNAL_CONTENT_DIR(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_EXTERNAL_CONTENT_DIR))
#define RYGEL_IS_EXTERNAL_CONTENT_DIR_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_EXTERNAL_CONTENT_DIR))
#define RYGEL_EXTERNAL_CONTENT_DIR_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_EXTERNAL_CONTENT_DIR, RygelExternalContentDirClass))

typedef struct _RygelExternalContentDir RygelExternalContentDir;
typedef struct _RygelExternalContentDirClass RygelExternalContentDirClass;

struct _ExternalPlugin {
	RygelPlugin parent_instance;
	ExternalPluginPrivate * priv;
	char* service_name;
	char* root_object;
};

struct _ExternalPluginClass {
	RygelPluginClass parent_class;
};



GType external_plugin_get_type (void);
enum  {
	EXTERNAL_PLUGIN_DUMMY_PROPERTY
};
#define EXTERNAL_PLUGIN_PROPS_IFACE "org.freedesktop.DBus.Properties"
#define EXTERNAL_PLUGIN_OBJECT_IFACE "org.gnome.UPnP.MediaObject1"
void _dynamic_Get4 (DBusGProxy* self, const char* param1, const char* param2, GValue* param3, GError** error);
GType rygel_external_content_dir_get_type (void);
ExternalPlugin* external_plugin_new (DBusGConnection* connection, const char* service_name);
ExternalPlugin* external_plugin_construct (GType object_type, DBusGConnection* connection, const char* service_name);
ExternalPlugin* external_plugin_new (DBusGConnection* connection, const char* service_name);
static gpointer external_plugin_parent_class = NULL;
static void external_plugin_finalize (GObject* obj);



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
				goto __catch4_g_regex_error;
			}
			goto __finally4;
		}
		_tmp2_ = g_regex_replace_literal (regex, self, (glong) (-1), 0, replacement, 0, &_inner_error_);
		if (_inner_error_ != NULL) {
			(regex == NULL) ? NULL : (regex = (g_regex_unref (regex), NULL));
			if (_inner_error_->domain == G_REGEX_ERROR) {
				goto __catch4_g_regex_error;
			}
			goto __finally4;
		}
		_tmp3_ = NULL;
		return (_tmp3_ = _tmp2_, (regex == NULL) ? NULL : (regex = (g_regex_unref (regex), NULL)), _tmp3_);
	}
	goto __finally4;
	__catch4_g_regex_error:
	{
		GError * e;
		e = _inner_error_;
		_inner_error_ = NULL;
		{
			g_assert_not_reached ();
			(e == NULL) ? NULL : (e = (g_error_free (e), NULL));
		}
	}
	__finally4:
	if (_inner_error_ != NULL) {
		g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, _inner_error_->message);
		g_clear_error (&_inner_error_);
		return NULL;
	}
}


void _dynamic_Get4 (DBusGProxy* self, const char* param1, const char* param2, GValue* param3, GError** error) {
	dbus_g_proxy_call (self, "Get", error, G_TYPE_STRING, param1, G_TYPE_STRING, param2, G_TYPE_INVALID, G_TYPE_VALUE, param3, G_TYPE_INVALID);
	if (*error) {
		return;
	}
}


ExternalPlugin* external_plugin_construct (GType object_type, DBusGConnection* connection, const char* service_name) {
	GError * _inner_error_;
	ExternalPlugin * self;
	char* _tmp0_;
	char* _tmp1_;
	char* root_object;
	DBusGProxy* props;
	GValue value = {0};
	GValue _tmp3_ = {0};
	GValue _tmp2_ = {0};
	const char* _tmp4_;
	char* title;
	char* _tmp6_;
	const char* _tmp5_;
	char* _tmp8_;
	const char* _tmp7_;
	RygelResourceInfo* resource_info;
	g_return_val_if_fail (connection != NULL, NULL);
	g_return_val_if_fail (service_name != NULL, NULL);
	_inner_error_ = NULL;
	_tmp0_ = NULL;
	_tmp1_ = NULL;
	root_object = (_tmp1_ = g_strconcat ("/", _tmp0_ = string_replace (service_name, ".", "/"), NULL), _tmp0_ = (g_free (_tmp0_), NULL), _tmp1_);
	props = dbus_g_proxy_new_for_name (connection, service_name, root_object, EXTERNAL_PLUGIN_PROPS_IFACE);
	_dynamic_Get4 (props, EXTERNAL_PLUGIN_OBJECT_IFACE, "DisplayName", &_tmp2_, &_inner_error_);
	value = (_tmp3_ = _tmp2_, G_IS_VALUE (&value) ? (g_value_unset (&value), NULL) : NULL, _tmp3_);
	if (_inner_error_ != NULL) {
		root_object = (g_free (root_object), NULL);
		(props == NULL) ? NULL : (props = (g_object_unref (props), NULL));
		G_IS_VALUE (&value) ? (g_value_unset (&value), NULL) : NULL;
		g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, _inner_error_->message);
		g_clear_error (&_inner_error_);
		return NULL;
	}
	_tmp4_ = NULL;
	title = (_tmp4_ = g_value_get_string (&value), (_tmp4_ == NULL) ? NULL : g_strdup (_tmp4_));
	self = (ExternalPlugin*) rygel_plugin_construct (object_type, service_name, title);
	_tmp6_ = NULL;
	_tmp5_ = NULL;
	self->service_name = (_tmp6_ = (_tmp5_ = service_name, (_tmp5_ == NULL) ? NULL : g_strdup (_tmp5_)), self->service_name = (g_free (self->service_name), NULL), _tmp6_);
	_tmp8_ = NULL;
	_tmp7_ = NULL;
	self->root_object = (_tmp8_ = (_tmp7_ = root_object, (_tmp7_ == NULL) ? NULL : g_strdup (_tmp7_)), self->root_object = (g_free (self->root_object), NULL), _tmp8_);
	resource_info = rygel_resource_info_new (RYGEL_CONTENT_DIRECTORY_UPNP_ID, RYGEL_CONTENT_DIRECTORY_UPNP_TYPE, RYGEL_CONTENT_DIRECTORY_DESCRIPTION_PATH, RYGEL_TYPE_EXTERNAL_CONTENT_DIR);
	rygel_plugin_add_resource ((RygelPlugin*) self, resource_info);
	root_object = (g_free (root_object), NULL);
	(props == NULL) ? NULL : (props = (g_object_unref (props), NULL));
	G_IS_VALUE (&value) ? (g_value_unset (&value), NULL) : NULL;
	title = (g_free (title), NULL);
	(resource_info == NULL) ? NULL : (resource_info = (rygel_resource_info_unref (resource_info), NULL));
	return self;
}


ExternalPlugin* external_plugin_new (DBusGConnection* connection, const char* service_name) {
	return external_plugin_construct (TYPE_EXTERNAL_PLUGIN, connection, service_name);
}


static void external_plugin_class_init (ExternalPluginClass * klass) {
	external_plugin_parent_class = g_type_class_peek_parent (klass);
	G_OBJECT_CLASS (klass)->finalize = external_plugin_finalize;
}


static void external_plugin_instance_init (ExternalPlugin * self) {
}


static void external_plugin_finalize (GObject* obj) {
	ExternalPlugin * self;
	self = EXTERNAL_PLUGIN (obj);
	self->service_name = (g_free (self->service_name), NULL);
	self->root_object = (g_free (self->root_object), NULL);
	G_OBJECT_CLASS (external_plugin_parent_class)->finalize (obj);
}


GType external_plugin_get_type (void) {
	static GType external_plugin_type_id = 0;
	if (external_plugin_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (ExternalPluginClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) external_plugin_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (ExternalPlugin), 0, (GInstanceInitFunc) external_plugin_instance_init, NULL };
		external_plugin_type_id = g_type_register_static (RYGEL_TYPE_PLUGIN, "ExternalPlugin", &g_define_type_info, 0);
	}
	return external_plugin_type_id;
}




