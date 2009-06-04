/*
 * Copyright (C) 2008 Nokia Corporation, all rights reserved.
 * Copyright (C) 2008 Zeeshan Ali (Khattak) <zeeshanak@gnome.org>.
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
#include <libgupnp/gupnp.h>
#include <stdlib.h>
#include <string.h>
#include <gee/arraylist.h>
#include <libxml/tree.h>
#include <libxml/parser.h>
#include <cstuff.h>
#include <gee/iterable.h>
#include <gee/iterator.h>
#include <gee/collection.h>
#include <stdio.h>
#include <gio/gio.h>
#include <gobject/gvaluecollector.h>


#define RYGEL_TYPE_MEDIA_SERVER_FACTORY (rygel_media_server_factory_get_type ())
#define RYGEL_MEDIA_SERVER_FACTORY(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_MEDIA_SERVER_FACTORY, RygelMediaServerFactory))
#define RYGEL_MEDIA_SERVER_FACTORY_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_MEDIA_SERVER_FACTORY, RygelMediaServerFactoryClass))
#define RYGEL_IS_MEDIA_SERVER_FACTORY(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_MEDIA_SERVER_FACTORY))
#define RYGEL_IS_MEDIA_SERVER_FACTORY_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_MEDIA_SERVER_FACTORY))
#define RYGEL_MEDIA_SERVER_FACTORY_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_MEDIA_SERVER_FACTORY, RygelMediaServerFactoryClass))

typedef struct _RygelMediaServerFactory RygelMediaServerFactory;
typedef struct _RygelMediaServerFactoryClass RygelMediaServerFactoryClass;
typedef struct _RygelMediaServerFactoryPrivate RygelMediaServerFactoryPrivate;

#define RYGEL_TYPE_CONFIGURATION (rygel_configuration_get_type ())
#define RYGEL_CONFIGURATION(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_CONFIGURATION, RygelConfiguration))
#define RYGEL_CONFIGURATION_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_CONFIGURATION, RygelConfigurationClass))
#define RYGEL_IS_CONFIGURATION(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_CONFIGURATION))
#define RYGEL_IS_CONFIGURATION_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_CONFIGURATION))
#define RYGEL_CONFIGURATION_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_CONFIGURATION, RygelConfigurationClass))

typedef struct _RygelConfiguration RygelConfiguration;
typedef struct _RygelConfigurationClass RygelConfigurationClass;

#define RYGEL_TYPE_PLUGIN (rygel_plugin_get_type ())
#define RYGEL_PLUGIN(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_PLUGIN, RygelPlugin))
#define RYGEL_PLUGIN_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_PLUGIN, RygelPluginClass))
#define RYGEL_IS_PLUGIN(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_PLUGIN))
#define RYGEL_IS_PLUGIN_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_PLUGIN))
#define RYGEL_PLUGIN_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_PLUGIN, RygelPluginClass))

typedef struct _RygelPlugin RygelPlugin;
typedef struct _RygelPluginClass RygelPluginClass;
typedef struct _RygelPluginPrivate RygelPluginPrivate;

#define RYGEL_TYPE_RESOURCE_INFO (rygel_resource_info_get_type ())
#define RYGEL_RESOURCE_INFO(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_RESOURCE_INFO, RygelResourceInfo))
#define RYGEL_RESOURCE_INFO_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_RESOURCE_INFO, RygelResourceInfoClass))
#define RYGEL_IS_RESOURCE_INFO(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_RESOURCE_INFO))
#define RYGEL_IS_RESOURCE_INFO_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_RESOURCE_INFO))
#define RYGEL_RESOURCE_INFO_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_RESOURCE_INFO, RygelResourceInfoClass))

typedef struct _RygelResourceInfo RygelResourceInfo;
typedef struct _RygelResourceInfoClass RygelResourceInfoClass;

#define RYGEL_TYPE_ICON_INFO (rygel_icon_info_get_type ())
#define RYGEL_ICON_INFO(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_ICON_INFO, RygelIconInfo))
#define RYGEL_ICON_INFO_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_ICON_INFO, RygelIconInfoClass))
#define RYGEL_IS_ICON_INFO(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_ICON_INFO))
#define RYGEL_IS_ICON_INFO_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_ICON_INFO))
#define RYGEL_ICON_INFO_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_ICON_INFO, RygelIconInfoClass))

typedef struct _RygelIconInfo RygelIconInfo;
typedef struct _RygelIconInfoClass RygelIconInfoClass;

#define RYGEL_TYPE_MEDIA_SERVER (rygel_media_server_get_type ())
#define RYGEL_MEDIA_SERVER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_MEDIA_SERVER, RygelMediaServer))
#define RYGEL_MEDIA_SERVER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_MEDIA_SERVER, RygelMediaServerClass))
#define RYGEL_IS_MEDIA_SERVER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_MEDIA_SERVER))
#define RYGEL_IS_MEDIA_SERVER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_MEDIA_SERVER))
#define RYGEL_MEDIA_SERVER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_MEDIA_SERVER, RygelMediaServerClass))

typedef struct _RygelMediaServer RygelMediaServer;
typedef struct _RygelMediaServerClass RygelMediaServerClass;
typedef struct _RygelResourceInfoPrivate RygelResourceInfoPrivate;
typedef struct _RygelIconInfoPrivate RygelIconInfoPrivate;
typedef struct _RygelParamSpecMediaServerFactory RygelParamSpecMediaServerFactory;

typedef enum  {
	MEDIA_SERVER_FACTORY_ERROR_XML_PARSE,
	MEDIA_SERVER_FACTORY_ERROR_PLUGIN_DISABLED
} MediaServerFactoryError;
#define MEDIA_SERVER_FACTORY_ERROR media_server_factory_error_quark ()
/**
 * Factory for MediaServer objects. Give it a plugin and it will create a
 * MediaServer device for that.
 */
struct _RygelMediaServerFactory {
	GTypeInstance parent_instance;
	volatile int ref_count;
	RygelMediaServerFactoryPrivate * priv;
};

struct _RygelMediaServerFactoryClass {
	GTypeClass parent_class;
	void (*finalize) (RygelMediaServerFactory *self);
};

struct _RygelMediaServerFactoryPrivate {
	RygelConfiguration* config;
	GUPnPContext* context;
};

/**
 * Represents a Rygel plugin. Plugins are supposed to provide an object of this
 * class or a subclass.
 */
struct _RygelPlugin {
	GUPnPResourceFactory parent_instance;
	RygelPluginPrivate * priv;
	char* name;
	char* title;
	GeeArrayList* resource_infos;
	GeeArrayList* icon_infos;
};

struct _RygelPluginClass {
	GUPnPResourceFactoryClass parent_class;
};

/**
 * Holds information about a particular resource (device and service)
 * implementation.
 */
struct _RygelResourceInfo {
	GTypeInstance parent_instance;
	volatile int ref_count;
	RygelResourceInfoPrivate * priv;
	char* upnp_type;
	char* upnp_id;
	char* description_path;
	GType type;
};

struct _RygelResourceInfoClass {
	GTypeClass parent_class;
	void (*finalize) (RygelResourceInfo *self);
};

/**
 * Holds information about an icon.
 */
struct _RygelIconInfo {
	GTypeInstance parent_instance;
	volatile int ref_count;
	RygelIconInfoPrivate * priv;
	char* mimetype;
	guint width;
	guint height;
	guint depth;
	char* path;
};

struct _RygelIconInfoClass {
	GTypeClass parent_class;
	void (*finalize) (RygelIconInfo *self);
};

struct _RygelParamSpecMediaServerFactory {
	GParamSpec parent_instance;
};



GQuark media_server_factory_error_quark (void);
gpointer rygel_media_server_factory_ref (gpointer instance);
void rygel_media_server_factory_unref (gpointer instance);
GParamSpec* rygel_param_spec_media_server_factory (const gchar* name, const gchar* nick, const gchar* blurb, GType object_type, GParamFlags flags);
void rygel_value_set_media_server_factory (GValue* value, gpointer v_object);
gpointer rygel_value_get_media_server_factory (const GValue* value);
GType rygel_media_server_factory_get_type (void);
GType rygel_configuration_get_type (void);
#define RYGEL_MEDIA_SERVER_FACTORY_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), RYGEL_TYPE_MEDIA_SERVER_FACTORY, RygelMediaServerFactoryPrivate))
enum  {
	RYGEL_MEDIA_SERVER_FACTORY_DUMMY_PROPERTY
};
#define RYGEL_MEDIA_SERVER_FACTORY_DESC_DOC "xml/description.xml"
#define RYGEL_MEDIA_SERVER_FACTORY_DESC_PREFIX "Rygel"
RygelConfiguration* rygel_configuration_get_default (void);
static GUPnPContext* rygel_media_server_factory_create_upnp_context (RygelMediaServerFactory* self, GError** error);
RygelMediaServerFactory* rygel_media_server_factory_new (GError** error);
RygelMediaServerFactory* rygel_media_server_factory_construct (GType object_type, GError** error);
RygelMediaServerFactory* rygel_media_server_factory_new (GError** error);
gboolean rygel_configuration_get_enabled (RygelConfiguration* self, const char* section);
GType rygel_plugin_get_type (void);
gpointer rygel_resource_info_ref (gpointer instance);
void rygel_resource_info_unref (gpointer instance);
GParamSpec* rygel_param_spec_resource_info (const gchar* name, const gchar* nick, const gchar* blurb, GType object_type, GParamFlags flags);
void rygel_value_set_resource_info (GValue* value, gpointer v_object);
gpointer rygel_value_get_resource_info (const GValue* value);
GType rygel_resource_info_get_type (void);
gpointer rygel_icon_info_ref (gpointer instance);
void rygel_icon_info_unref (gpointer instance);
GParamSpec* rygel_param_spec_icon_info (const gchar* name, const gchar* nick, const gchar* blurb, GType object_type, GParamFlags flags);
void rygel_value_set_icon_info (GValue* value, gpointer v_object);
gpointer rygel_value_get_icon_info (const GValue* value);
GType rygel_icon_info_get_type (void);
static xmlDoc* rygel_media_server_factory_create_desc (RygelMediaServerFactory* self, RygelPlugin* plugin, const char* desc_path, GError** error);
RygelMediaServer* rygel_media_server_new (GUPnPContext* context, RygelPlugin* plugin, xmlDoc* description_doc, const char* relative_location);
RygelMediaServer* rygel_media_server_construct (GType object_type, GUPnPContext* context, RygelPlugin* plugin, xmlDoc* description_doc, const char* relative_location);
GType rygel_media_server_get_type (void);
RygelMediaServer* rygel_media_server_factory_create_media_server (RygelMediaServerFactory* self, RygelPlugin* plugin, GError** error);
static gboolean rygel_media_server_factory_check_path_exist (RygelMediaServerFactory* self, const char* path);
static void rygel_media_server_factory_prepare_desc_for_plugin (RygelMediaServerFactory* self, xmlDoc* doc, RygelPlugin* plugin);
static void rygel_media_server_factory_save_modified_desc (RygelMediaServerFactory* self, xmlDoc* doc, const char* desc_path, GError** error);
const char* rygel_configuration_get_host_ip (RygelConfiguration* self);
gint rygel_configuration_get_port (RygelConfiguration* self);
static void rygel_media_server_factory_set_friendly_name_and_udn (RygelMediaServerFactory* self, xmlNode* device_element, const char* plugin_name, const char* plugin_title);
static void rygel_media_server_factory_add_icons_to_desc (RygelMediaServerFactory* self, xmlNode* device_element, RygelPlugin* plugin);
static void rygel_media_server_factory_add_services_to_desc (RygelMediaServerFactory* self, xmlNode* device_element, RygelPlugin* plugin);
char* rygel_configuration_get_title (RygelConfiguration* self, const char* section, const char* default_title);
static void rygel_media_server_factory_add_service_to_desc (RygelMediaServerFactory* self, xmlNode* service_list_node, const char* plugin_name, RygelResourceInfo* resource_info);
static void rygel_media_server_factory_add_icon_to_desc (RygelMediaServerFactory* self, xmlNode* icon_list_node, RygelIconInfo* icon_info, RygelPlugin* plugin);
static gpointer rygel_media_server_factory_parent_class = NULL;
static void rygel_media_server_factory_finalize (RygelMediaServerFactory* obj);
static int _vala_strcmp0 (const char * str1, const char * str2);



GQuark media_server_factory_error_quark (void) {
	return g_quark_from_static_string ("media_server_factory_error-quark");
}


RygelMediaServerFactory* rygel_media_server_factory_construct (GType object_type, GError** error) {
	GError * _inner_error_;
	RygelMediaServerFactory* self;
	RygelConfiguration* _tmp0_;
	GUPnPContext* _tmp1_;
	GUPnPContext* _tmp2_;
	_inner_error_ = NULL;
	self = (RygelMediaServerFactory*) g_type_create_instance (object_type);
	_tmp0_ = NULL;
	self->priv->config = (_tmp0_ = rygel_configuration_get_default (), (self->priv->config == NULL) ? NULL : (self->priv->config = (g_object_unref (self->priv->config), NULL)), _tmp0_);
	_tmp1_ = rygel_media_server_factory_create_upnp_context (self, &_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		return;
	}
	/* Set up GUPnP context */
	_tmp2_ = NULL;
	self->priv->context = (_tmp2_ = _tmp1_, (self->priv->context == NULL) ? NULL : (self->priv->context = (g_object_unref (self->priv->context), NULL)), _tmp2_);
	return self;
}


RygelMediaServerFactory* rygel_media_server_factory_new (GError** error) {
	return rygel_media_server_factory_construct (RYGEL_TYPE_MEDIA_SERVER_FACTORY, error);
}


RygelMediaServer* rygel_media_server_factory_create_media_server (RygelMediaServerFactory* self, RygelPlugin* plugin, GError** error) {
	GError * _inner_error_;
	char* _tmp0_;
	char* _tmp1_;
	char* modified_desc;
	char* desc_path;
	xmlDoc* doc;
	char* _tmp2_;
	RygelMediaServer* _tmp3_;
	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (plugin != NULL, NULL);
	_inner_error_ = NULL;
	if (!rygel_configuration_get_enabled (self->priv->config, plugin->name)) {
		_inner_error_ = g_error_new_literal (MEDIA_SERVER_FACTORY_ERROR, MEDIA_SERVER_FACTORY_ERROR_PLUGIN_DISABLED, "Plugin disabled in user configuration.");
		if (_inner_error_ != NULL) {
			g_propagate_error (error, _inner_error_);
			return NULL;
		}
	}
	_tmp0_ = NULL;
	_tmp1_ = NULL;
	modified_desc = (_tmp1_ = g_strconcat (_tmp0_ = g_strconcat (RYGEL_MEDIA_SERVER_FACTORY_DESC_PREFIX "-", plugin->name, NULL), ".xml", NULL), _tmp0_ = (g_free (_tmp0_), NULL), _tmp1_);
	/* We store a modified description.xml in the user's config dir */
	desc_path = g_build_filename (g_get_user_config_dir (), modified_desc, NULL);
	/* Create the description xml */
	doc = rygel_media_server_factory_create_desc (self, plugin, desc_path, &_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		modified_desc = (g_free (modified_desc), NULL);
		desc_path = (g_free (desc_path), NULL);
		return NULL;
	}
	/* Host our modified file */
	_tmp2_ = NULL;
	gupnp_context_host_path (self->priv->context, desc_path, _tmp2_ = g_strconcat ("/", modified_desc, NULL));
	_tmp2_ = (g_free (_tmp2_), NULL);
	_tmp3_ = NULL;
	return (_tmp3_ = rygel_media_server_new (self->priv->context, plugin, doc, modified_desc), modified_desc = (g_free (modified_desc), NULL), desc_path = (g_free (desc_path), NULL), _tmp3_);
}


static xmlDoc* rygel_media_server_factory_create_desc (RygelMediaServerFactory* self, RygelPlugin* plugin, const char* desc_path, GError** error) {
	GError * _inner_error_;
	char* path;
	xmlDoc* doc;
	xmlDoc* _tmp3_;
	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (plugin != NULL, NULL);
	g_return_val_if_fail (desc_path != NULL, NULL);
	_inner_error_ = NULL;
	path = NULL;
	if (rygel_media_server_factory_check_path_exist (self, desc_path)) {
		char* _tmp1_;
		const char* _tmp0_;
		_tmp1_ = NULL;
		_tmp0_ = NULL;
		path = (_tmp1_ = (_tmp0_ = desc_path, (_tmp0_ == NULL) ? NULL : g_strdup (_tmp0_)), path = (g_free (path), NULL), _tmp1_);
	} else {
		char* _tmp2_;
		/* Use the template */
		_tmp2_ = NULL;
		path = (_tmp2_ = g_build_filename (DATA_DIR, RYGEL_MEDIA_SERVER_FACTORY_DESC_DOC, NULL), path = (g_free (path), NULL), _tmp2_);
	}
	doc = xmlParseFile (path);
	if (doc == NULL) {
		char* message;
		message = g_strdup_printf ("Failed to parse %s", path);
		_inner_error_ = g_error_new_literal (MEDIA_SERVER_FACTORY_ERROR, MEDIA_SERVER_FACTORY_ERROR_XML_PARSE, message);
		if (_inner_error_ != NULL) {
			g_propagate_error (error, _inner_error_);
			message = (g_free (message), NULL);
			path = (g_free (path), NULL);
			return NULL;
		}
		message = (g_free (message), NULL);
	}
	/* Modify description to include Plugin-specific stuff */
	rygel_media_server_factory_prepare_desc_for_plugin (self, doc, plugin);
	rygel_media_server_factory_save_modified_desc (self, doc, desc_path, &_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		path = (g_free (path), NULL);
		return NULL;
	}
	_tmp3_ = NULL;
	return (_tmp3_ = doc, path = (g_free (path), NULL), _tmp3_);
}


static GUPnPContext* rygel_media_server_factory_create_upnp_context (RygelMediaServerFactory* self, GError** error) {
	GError * _inner_error_;
	GUPnPContext* context;
	g_return_val_if_fail (self != NULL, NULL);
	_inner_error_ = NULL;
	context = gupnp_context_new (NULL, rygel_configuration_get_host_ip (self->priv->config), (guint) rygel_configuration_get_port (self->priv->config), &_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		return NULL;
	}
	/* Host UPnP dir */
	gupnp_context_host_path (context, DATA_DIR, "");
	return context;
}


static void rygel_media_server_factory_prepare_desc_for_plugin (RygelMediaServerFactory* self, xmlDoc* doc, RygelPlugin* plugin) {
	xmlNode* device_element;
	g_return_if_fail (self != NULL);
	g_return_if_fail (doc != NULL);
	g_return_if_fail (plugin != NULL);
	device_element = NULL;
	device_element = get_xml_element ((xmlNode*) doc, "root", "device", NULL, NULL);
	if (device_element == NULL) {
		g_warning ("rygel-media-server-factory.vala:122: Element /root/device not found.");
		return;
	}
	/* First, set the Friendly name and UDN */
	rygel_media_server_factory_set_friendly_name_and_udn (self, device_element, plugin->name, plugin->title);
	/* Then list each icon */
	rygel_media_server_factory_add_icons_to_desc (self, device_element, plugin);
	/* Then list each service */
	rygel_media_server_factory_add_services_to_desc (self, device_element, plugin);
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
				goto __catch23_g_regex_error;
			}
			goto __finally23;
		}
		_tmp2_ = g_regex_replace_literal (regex, self, (glong) (-1), 0, replacement, 0, &_inner_error_);
		if (_inner_error_ != NULL) {
			(regex == NULL) ? NULL : (regex = (g_regex_unref (regex), NULL));
			if (_inner_error_->domain == G_REGEX_ERROR) {
				goto __catch23_g_regex_error;
			}
			goto __finally23;
		}
		_tmp3_ = NULL;
		return (_tmp3_ = _tmp2_, (regex == NULL) ? NULL : (regex = (g_regex_unref (regex), NULL)), _tmp3_);
	}
	goto __finally23;
	__catch23_g_regex_error:
	{
		GError * e;
		e = _inner_error_;
		_inner_error_ = NULL;
		{
			g_assert_not_reached ();
			(e == NULL) ? NULL : (e = (g_error_free (e), NULL));
		}
	}
	__finally23:
	if (_inner_error_ != NULL) {
		g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, _inner_error_->message);
		g_clear_error (&_inner_error_);
		return NULL;
	}
}


/**
     * Fills the description doc @doc with a friendly name, and UDN from gconf.
     * If these keys are not present in gconf, they are set with default values.
     */
static void rygel_media_server_factory_set_friendly_name_and_udn (RygelMediaServerFactory* self, xmlNode* device_element, const char* plugin_name, const char* plugin_title) {
	xmlNode* element;
	char* title;
	char* _tmp0_;
	char* _tmp1_;
	char* _tmp2_;
	char* udn;
	gboolean _tmp3_;
	g_return_if_fail (self != NULL);
	g_return_if_fail (plugin_name != NULL);
	g_return_if_fail (plugin_title != NULL);
	/* friendlyName */
	element = get_xml_element (device_element, "friendlyName", NULL, NULL);
	if (element == NULL) {
		g_warning ("rygel-media-server-factory.vala:151: Element /root/device/friendlyName not found.");
		return;
	}
	title = rygel_configuration_get_title (self->priv->config, plugin_name, plugin_title);
	_tmp0_ = NULL;
	title = (_tmp0_ = string_replace (title, "@REALNAME@", g_get_real_name ()), title = (g_free (title), NULL), _tmp0_);
	_tmp1_ = NULL;
	title = (_tmp1_ = string_replace (title, "@USERNAME@", g_get_user_name ()), title = (g_free (title), NULL), _tmp1_);
	_tmp2_ = NULL;
	title = (_tmp2_ = string_replace (title, "@HOSTNAME@", g_get_host_name ()), title = (g_free (title), NULL), _tmp2_);
	xmlNodeSetContent (element, title);
	/* UDN */
	element = get_xml_element (device_element, "UDN", NULL);
	if (element == NULL) {
		g_warning ("rygel-media-server-factory.vala:166: Element /root/device/UDN not found.");
		title = (g_free (title), NULL);
		return;
	}
	udn = xmlNodeGetContent (element);
	_tmp3_ = FALSE;
	if (udn == NULL) {
		_tmp3_ = TRUE;
	} else {
		_tmp3_ = _vala_strcmp0 (udn, "") == 0;
	}
	if (_tmp3_) {
		char* _tmp4_;
		_tmp4_ = NULL;
		udn = (_tmp4_ = generate_random_udn (), udn = (g_free (udn), NULL), _tmp4_);
		xmlNodeSetContent (element, udn);
	}
	title = (g_free (title), NULL);
	udn = (g_free (udn), NULL);
}


static void rygel_media_server_factory_add_services_to_desc (RygelMediaServerFactory* self, xmlNode* device_element, RygelPlugin* plugin) {
	xmlNode* service_list_node;
	g_return_if_fail (self != NULL);
	g_return_if_fail (plugin != NULL);
	service_list_node = get_xml_element (device_element, "serviceList", NULL, NULL);
	if (service_list_node == NULL) {
		g_warning ("rygel-media-server-factory.vala:185: Element /root/device/serviceList not found.");
		return;
	}
	{
		GeeIterator* _resource_info_it;
		_resource_info_it = gee_iterable_iterator ((GeeIterable*) plugin->resource_infos);
		while (gee_iterator_next (_resource_info_it)) {
			RygelResourceInfo* resource_info;
			resource_info = (RygelResourceInfo*) gee_iterator_get (_resource_info_it);
			/* FIXME: We only support plugable services for now*/
			if (g_type_is_a (resource_info->type, GUPNP_TYPE_SERVICE)) {
				rygel_media_server_factory_add_service_to_desc (self, service_list_node, plugin->name, resource_info);
			}
			(resource_info == NULL) ? NULL : (resource_info = (rygel_resource_info_unref (resource_info), NULL));
		}
		(_resource_info_it == NULL) ? NULL : (_resource_info_it = (g_object_unref (_resource_info_it), NULL));
	}
}


static void rygel_media_server_factory_add_service_to_desc (RygelMediaServerFactory* self, xmlNode* service_list_node, const char* plugin_name, RygelResourceInfo* resource_info) {
	xmlNode* service_node;
	const char* _tmp0_;
	char* url;
	char* _tmp3_;
	char* _tmp2_;
	char* _tmp1_;
	char* _tmp6_;
	char* _tmp5_;
	char* _tmp4_;
	g_return_if_fail (self != NULL);
	g_return_if_fail (plugin_name != NULL);
	g_return_if_fail (resource_info != NULL);
	/* Clear the existing service list first*/
	xmlNodeSetContent (service_list_node, "");
	/* Now create the service node*/
	service_node = xmlNewChild (service_list_node, NULL, "service", NULL);
	xmlNewChild (service_node, NULL, "serviceType", resource_info->upnp_type);
	xmlNewChild (service_node, NULL, "serviceId", resource_info->upnp_id);
	/* Now the relative (to base URL) URLs*/
	_tmp0_ = NULL;
	url = (_tmp0_ = resource_info->description_path, (_tmp0_ == NULL) ? NULL : g_strdup (_tmp0_));
	xmlNewChild (service_node, NULL, "SCPDURL", url);
	_tmp3_ = NULL;
	_tmp2_ = NULL;
	_tmp1_ = NULL;
	url = (_tmp3_ = g_strconcat (_tmp2_ = g_strconcat (_tmp1_ = g_strconcat (plugin_name, "/", NULL), g_type_name (resource_info->type), NULL), "/Event", NULL), url = (g_free (url), NULL), _tmp3_);
	_tmp2_ = (g_free (_tmp2_), NULL);
	_tmp1_ = (g_free (_tmp1_), NULL);
	xmlNewChild (service_node, NULL, "eventSubURL", url);
	_tmp6_ = NULL;
	_tmp5_ = NULL;
	_tmp4_ = NULL;
	url = (_tmp6_ = g_strconcat (_tmp5_ = g_strconcat (_tmp4_ = g_strconcat (plugin_name, "/", NULL), g_type_name (resource_info->type), NULL), "/Control", NULL), url = (g_free (url), NULL), _tmp6_);
	_tmp5_ = (g_free (_tmp5_), NULL);
	_tmp4_ = (g_free (_tmp4_), NULL);
	xmlNewChild (service_node, NULL, "controlURL", url);
	url = (g_free (url), NULL);
}


static void rygel_media_server_factory_add_icons_to_desc (RygelMediaServerFactory* self, xmlNode* device_element, RygelPlugin* plugin) {
	gboolean _tmp0_;
	xmlNode* icon_list_node;
	g_return_if_fail (self != NULL);
	g_return_if_fail (plugin != NULL);
	_tmp0_ = FALSE;
	if (plugin->icon_infos == NULL) {
		_tmp0_ = TRUE;
	} else {
		_tmp0_ = gee_collection_get_size ((GeeCollection*) plugin->icon_infos) == 0;
	}
	if (_tmp0_) {
		g_debug ("rygel-media-server-factory.vala:226: No icon provided by %s.", plugin->name);
		return;
	}
	icon_list_node = xmlNewChild (device_element, NULL, "iconList", NULL);
	{
		GeeIterator* _icon_info_it;
		_icon_info_it = gee_iterable_iterator ((GeeIterable*) plugin->icon_infos);
		while (gee_iterator_next (_icon_info_it)) {
			RygelIconInfo* icon_info;
			icon_info = (RygelIconInfo*) gee_iterator_get (_icon_info_it);
			rygel_media_server_factory_add_icon_to_desc (self, icon_list_node, icon_info, plugin);
			(icon_info == NULL) ? NULL : (icon_info = (rygel_icon_info_unref (icon_info), NULL));
		}
		(_icon_info_it == NULL) ? NULL : (_icon_info_it = (g_object_unref (_icon_info_it), NULL));
	}
}


static void rygel_media_server_factory_add_icon_to_desc (RygelMediaServerFactory* self, xmlNode* icon_list_node, RygelIconInfo* icon_info, RygelPlugin* plugin) {
	xmlNode* icon_node;
	char* width;
	char* height;
	char* depth;
	char* _tmp5_;
	char* _tmp4_;
	char* _tmp3_;
	char* _tmp2_;
	char* _tmp1_;
	char* _tmp0_;
	char* _tmp6_;
	char* url;
	char* _tmp7_;
	g_return_if_fail (self != NULL);
	g_return_if_fail (icon_info != NULL);
	g_return_if_fail (plugin != NULL);
	/* Create the service node*/
	icon_node = xmlNewChild (icon_list_node, NULL, "icon", NULL);
	width = g_strdup_printf ("%u", icon_info->width);
	height = g_strdup_printf ("%u", icon_info->height);
	depth = g_strdup_printf ("%u", icon_info->depth);
	xmlNewChild (icon_node, NULL, "mimetype", icon_info->mimetype);
	xmlNewChild (icon_node, NULL, "width", width);
	xmlNewChild (icon_node, NULL, "height", height);
	xmlNewChild (icon_node, NULL, "depth", depth);
	/* PLUGIN_NAME-WIDTHxHEIGHTxDEPTH.png*/
	_tmp5_ = NULL;
	_tmp4_ = NULL;
	_tmp3_ = NULL;
	_tmp2_ = NULL;
	_tmp1_ = NULL;
	_tmp0_ = NULL;
	_tmp6_ = NULL;
	url = (_tmp6_ = g_strconcat (_tmp5_ = g_strconcat (_tmp4_ = g_strconcat (_tmp3_ = g_strconcat (_tmp2_ = g_strconcat (_tmp1_ = g_strconcat (_tmp0_ = g_strconcat (plugin->name, "-", NULL), width, NULL), "x", NULL), height, NULL), "x", NULL), depth, NULL), ".png", NULL), _tmp5_ = (g_free (_tmp5_), NULL), _tmp4_ = (g_free (_tmp4_), NULL), _tmp3_ = (g_free (_tmp3_), NULL), _tmp2_ = (g_free (_tmp2_), NULL), _tmp1_ = (g_free (_tmp1_), NULL), _tmp0_ = (g_free (_tmp0_), NULL), _tmp6_);
	_tmp7_ = NULL;
	gupnp_context_host_path (self->priv->context, icon_info->path, _tmp7_ = g_strconcat ("/", url, NULL));
	_tmp7_ = (g_free (_tmp7_), NULL);
	xmlNewChild (icon_node, NULL, "url", url);
	width = (g_free (width), NULL);
	height = (g_free (height), NULL);
	depth = (g_free (depth), NULL);
	url = (g_free (url), NULL);
}


static void rygel_media_server_factory_save_modified_desc (RygelMediaServerFactory* self, xmlDoc* doc, const char* desc_path, GError** error) {
	GError * _inner_error_;
	FILE* f;
	gint res;
	gboolean _tmp0_;
	g_return_if_fail (self != NULL);
	g_return_if_fail (desc_path != NULL);
	_inner_error_ = NULL;
	f = fopen (desc_path, "w+");
	res = -1;
	if (f != NULL) {
		res = xmlDocDump (f, doc);
	}
	_tmp0_ = FALSE;
	if (f == NULL) {
		_tmp0_ = TRUE;
	} else {
		_tmp0_ = res == (-1);
	}
	if (_tmp0_) {
		char* _tmp1_;
		char* _tmp2_;
		char* message;
		_tmp1_ = NULL;
		_tmp2_ = NULL;
		message = (_tmp2_ = g_strconcat ("Failed to write modified description", _tmp1_ = g_strdup_printf (" to %s.\n", desc_path), NULL), _tmp1_ = (g_free (_tmp1_), NULL), _tmp2_);
		xmlFreeDoc (doc);
		_inner_error_ = g_error_new_literal (G_IO_ERROR, G_IO_ERROR_FAILED, message);
		if (_inner_error_ != NULL) {
			g_propagate_error (error, _inner_error_);
			message = (g_free (message), NULL);
			(f == NULL) ? NULL : (f = (fclose (f), NULL));
			return;
		}
		message = (g_free (message), NULL);
	}
	(f == NULL) ? NULL : (f = (fclose (f), NULL));
}


static gboolean rygel_media_server_factory_check_path_exist (RygelMediaServerFactory* self, const char* path) {
	GFile* file;
	gboolean _tmp0_;
	g_return_val_if_fail (self != NULL, FALSE);
	g_return_val_if_fail (path != NULL, FALSE);
	file = g_file_new_for_path (path);
	return (_tmp0_ = g_file_query_exists (file, NULL), (file == NULL) ? NULL : (file = (g_object_unref (file), NULL)), _tmp0_);
}


static void rygel_value_media_server_factory_init (GValue* value) {
	value->data[0].v_pointer = NULL;
}


static void rygel_value_media_server_factory_free_value (GValue* value) {
	if (value->data[0].v_pointer) {
		rygel_media_server_factory_unref (value->data[0].v_pointer);
	}
}


static void rygel_value_media_server_factory_copy_value (const GValue* src_value, GValue* dest_value) {
	if (src_value->data[0].v_pointer) {
		dest_value->data[0].v_pointer = rygel_media_server_factory_ref (src_value->data[0].v_pointer);
	} else {
		dest_value->data[0].v_pointer = NULL;
	}
}


static gpointer rygel_value_media_server_factory_peek_pointer (const GValue* value) {
	return value->data[0].v_pointer;
}


static gchar* rygel_value_media_server_factory_collect_value (GValue* value, guint n_collect_values, GTypeCValue* collect_values, guint collect_flags) {
	if (collect_values[0].v_pointer) {
		RygelMediaServerFactory* object;
		object = collect_values[0].v_pointer;
		if (object->parent_instance.g_class == NULL) {
			return g_strconcat ("invalid unclassed object pointer for value type `", G_VALUE_TYPE_NAME (value), "'", NULL);
		} else if (!g_value_type_compatible (G_TYPE_FROM_INSTANCE (object), G_VALUE_TYPE (value))) {
			return g_strconcat ("invalid object type `", g_type_name (G_TYPE_FROM_INSTANCE (object)), "' for value type `", G_VALUE_TYPE_NAME (value), "'", NULL);
		}
		value->data[0].v_pointer = rygel_media_server_factory_ref (object);
	} else {
		value->data[0].v_pointer = NULL;
	}
	return NULL;
}


static gchar* rygel_value_media_server_factory_lcopy_value (const GValue* value, guint n_collect_values, GTypeCValue* collect_values, guint collect_flags) {
	RygelMediaServerFactory** object_p;
	object_p = collect_values[0].v_pointer;
	if (!object_p) {
		return g_strdup_printf ("value location for `%s' passed as NULL", G_VALUE_TYPE_NAME (value));
	}
	if (!value->data[0].v_pointer) {
		*object_p = NULL;
	} else if (collect_flags && G_VALUE_NOCOPY_CONTENTS) {
		*object_p = value->data[0].v_pointer;
	} else {
		*object_p = rygel_media_server_factory_ref (value->data[0].v_pointer);
	}
	return NULL;
}


GParamSpec* rygel_param_spec_media_server_factory (const gchar* name, const gchar* nick, const gchar* blurb, GType object_type, GParamFlags flags) {
	RygelParamSpecMediaServerFactory* spec;
	g_return_val_if_fail (g_type_is_a (object_type, RYGEL_TYPE_MEDIA_SERVER_FACTORY), NULL);
	spec = g_param_spec_internal (G_TYPE_PARAM_OBJECT, name, nick, blurb, flags);
	G_PARAM_SPEC (spec)->value_type = object_type;
	return G_PARAM_SPEC (spec);
}


gpointer rygel_value_get_media_server_factory (const GValue* value) {
	g_return_val_if_fail (G_TYPE_CHECK_VALUE_TYPE (value, RYGEL_TYPE_MEDIA_SERVER_FACTORY), NULL);
	return value->data[0].v_pointer;
}


void rygel_value_set_media_server_factory (GValue* value, gpointer v_object) {
	RygelMediaServerFactory* old;
	g_return_if_fail (G_TYPE_CHECK_VALUE_TYPE (value, RYGEL_TYPE_MEDIA_SERVER_FACTORY));
	old = value->data[0].v_pointer;
	if (v_object) {
		g_return_if_fail (G_TYPE_CHECK_INSTANCE_TYPE (v_object, RYGEL_TYPE_MEDIA_SERVER_FACTORY));
		g_return_if_fail (g_value_type_compatible (G_TYPE_FROM_INSTANCE (v_object), G_VALUE_TYPE (value)));
		value->data[0].v_pointer = v_object;
		rygel_media_server_factory_ref (value->data[0].v_pointer);
	} else {
		value->data[0].v_pointer = NULL;
	}
	if (old) {
		rygel_media_server_factory_unref (old);
	}
}


static void rygel_media_server_factory_class_init (RygelMediaServerFactoryClass * klass) {
	rygel_media_server_factory_parent_class = g_type_class_peek_parent (klass);
	RYGEL_MEDIA_SERVER_FACTORY_CLASS (klass)->finalize = rygel_media_server_factory_finalize;
	g_type_class_add_private (klass, sizeof (RygelMediaServerFactoryPrivate));
}


static void rygel_media_server_factory_instance_init (RygelMediaServerFactory * self) {
	self->priv = RYGEL_MEDIA_SERVER_FACTORY_GET_PRIVATE (self);
	self->ref_count = 1;
}


static void rygel_media_server_factory_finalize (RygelMediaServerFactory* obj) {
	RygelMediaServerFactory * self;
	self = RYGEL_MEDIA_SERVER_FACTORY (obj);
	(self->priv->config == NULL) ? NULL : (self->priv->config = (g_object_unref (self->priv->config), NULL));
	(self->priv->context == NULL) ? NULL : (self->priv->context = (g_object_unref (self->priv->context), NULL));
}


GType rygel_media_server_factory_get_type (void) {
	static GType rygel_media_server_factory_type_id = 0;
	if (rygel_media_server_factory_type_id == 0) {
		static const GTypeValueTable g_define_type_value_table = { rygel_value_media_server_factory_init, rygel_value_media_server_factory_free_value, rygel_value_media_server_factory_copy_value, rygel_value_media_server_factory_peek_pointer, "p", rygel_value_media_server_factory_collect_value, "p", rygel_value_media_server_factory_lcopy_value };
		static const GTypeInfo g_define_type_info = { sizeof (RygelMediaServerFactoryClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) rygel_media_server_factory_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (RygelMediaServerFactory), 0, (GInstanceInitFunc) rygel_media_server_factory_instance_init, &g_define_type_value_table };
		static const GTypeFundamentalInfo g_define_type_fundamental_info = { (G_TYPE_FLAG_CLASSED | G_TYPE_FLAG_INSTANTIATABLE | G_TYPE_FLAG_DERIVABLE | G_TYPE_FLAG_DEEP_DERIVABLE) };
		rygel_media_server_factory_type_id = g_type_register_fundamental (g_type_fundamental_next (), "RygelMediaServerFactory", &g_define_type_info, &g_define_type_fundamental_info, 0);
	}
	return rygel_media_server_factory_type_id;
}


gpointer rygel_media_server_factory_ref (gpointer instance) {
	RygelMediaServerFactory* self;
	self = instance;
	g_atomic_int_inc (&self->ref_count);
	return instance;
}


void rygel_media_server_factory_unref (gpointer instance) {
	RygelMediaServerFactory* self;
	self = instance;
	if (g_atomic_int_dec_and_test (&self->ref_count)) {
		RYGEL_MEDIA_SERVER_FACTORY_GET_CLASS (self)->finalize (self);
		g_type_free_instance ((GTypeInstance *) self);
	}
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




