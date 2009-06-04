/*
 * Copyright (C) 2008 Nokia Corporation, all rights reserved.
 * Copyright (C) 2008 Zeeshan Ali (Khattak) <zeeshanak@gnome.org>.
 *
 * Author: Zeeshan Ali (Khattak) <zeeshanak@gnome.org>
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
#include <gee/arraylist.h>
#include <libxml/tree.h>
#include <libxml/parser.h>
#include <stdlib.h>
#include <string.h>
#include <gee/iterable.h>
#include <gee/iterator.h>
#include <gee/collection.h>


#define RYGEL_TYPE_MEDIA_SERVER (rygel_media_server_get_type ())
#define RYGEL_MEDIA_SERVER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_MEDIA_SERVER, RygelMediaServer))
#define RYGEL_MEDIA_SERVER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_MEDIA_SERVER, RygelMediaServerClass))
#define RYGEL_IS_MEDIA_SERVER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_MEDIA_SERVER))
#define RYGEL_IS_MEDIA_SERVER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_MEDIA_SERVER))
#define RYGEL_MEDIA_SERVER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_MEDIA_SERVER, RygelMediaServerClass))

typedef struct _RygelMediaServer RygelMediaServer;
typedef struct _RygelMediaServerClass RygelMediaServerClass;
typedef struct _RygelMediaServerPrivate RygelMediaServerPrivate;

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
typedef struct _RygelResourceInfoPrivate RygelResourceInfoPrivate;

/**
 * Represents a MediaServer device.
 */
struct _RygelMediaServer {
	GUPnPRootDevice parent_instance;
	RygelMediaServerPrivate * priv;
};

struct _RygelMediaServerClass {
	GUPnPRootDeviceClass parent_class;
};

struct _RygelMediaServerPrivate {
	GeeArrayList* services;
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



GType rygel_media_server_get_type (void);
#define RYGEL_MEDIA_SERVER_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), RYGEL_TYPE_MEDIA_SERVER, RygelMediaServerPrivate))
enum  {
	RYGEL_MEDIA_SERVER_DUMMY_PROPERTY
};
static void rygel_media_server_xml_doc_free (xmlDoc* doc, RygelMediaServer* server);
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
RygelMediaServer* rygel_media_server_new (GUPnPContext* context, RygelPlugin* plugin, xmlDoc* description_doc, const char* relative_location);
RygelMediaServer* rygel_media_server_construct (GType object_type, GUPnPContext* context, RygelPlugin* plugin, xmlDoc* description_doc, const char* relative_location);
RygelMediaServer* rygel_media_server_new (GUPnPContext* context, RygelPlugin* plugin, xmlDoc* description_doc, const char* relative_location);
static gpointer rygel_media_server_parent_class = NULL;
static void rygel_media_server_finalize (GObject* obj);



/* Services we implement */
RygelMediaServer* rygel_media_server_construct (GType object_type, GUPnPContext* context, RygelPlugin* plugin, xmlDoc* description_doc, const char* relative_location) {
	GParameter * __params;
	GParameter * __params_it;
	RygelMediaServer * self;
	GeeArrayList* _tmp0_;
	g_return_val_if_fail (context != NULL, NULL);
	g_return_val_if_fail (plugin != NULL, NULL);
	g_return_val_if_fail (relative_location != NULL, NULL);
	__params = g_new0 (GParameter, 5);
	__params_it = __params;
	__params_it->name = "resource-factory";
	g_value_init (&__params_it->value, GUPNP_TYPE_RESOURCE_FACTORY);
	g_value_set_object (&__params_it->value, (GUPnPResourceFactory*) plugin);
	__params_it++;
	__params_it->name = "root-device";
	g_value_init (&__params_it->value, GUPNP_TYPE_ROOT_DEVICE);
	g_value_set_object (&__params_it->value, NULL);
	__params_it++;
	__params_it->name = "context";
	g_value_init (&__params_it->value, GUPNP_TYPE_CONTEXT);
	g_value_set_object (&__params_it->value, context);
	__params_it++;
	__params_it->name = "description-doc";
	g_value_init (&__params_it->value, G_TYPE_POINTER);
	g_value_set_pointer (&__params_it->value, description_doc);
	__params_it++;
	__params_it->name = "relative-location";
	g_value_init (&__params_it->value, G_TYPE_STRING);
	g_value_set_string (&__params_it->value, relative_location);
	__params_it++;
	self = g_object_newv (object_type, __params_it - __params, __params);
	g_object_weak_ref ((GObject*) self, (GWeakNotify) rygel_media_server_xml_doc_free, description_doc);
	_tmp0_ = NULL;
	self->priv->services = (_tmp0_ = gee_array_list_new (GUPNP_TYPE_SERVICE_INFO, (GBoxedCopyFunc) g_object_ref, g_object_unref, g_direct_equal), (self->priv->services == NULL) ? NULL : (self->priv->services = (g_object_unref (self->priv->services), NULL)), _tmp0_);
	{
		GeeIterator* _info_it;
		/* Now create the sevice objects*/
		_info_it = gee_iterable_iterator ((GeeIterable*) plugin->resource_infos);
		/* Now create the sevice objects*/
		while (gee_iterator_next (_info_it)) {
			RygelResourceInfo* info;
			/* Now create the sevice objects*/
			info = (RygelResourceInfo*) gee_iterator_get (_info_it);
			/* FIXME: We only support plugable services for now*/
			if (g_type_is_a (info->type, GUPNP_TYPE_SERVICE)) {
				GUPnPServiceInfo* service;
				service = gupnp_device_info_get_service ((GUPnPDeviceInfo*) self, info->upnp_type);
				gee_collection_add ((GeeCollection*) self->priv->services, service);
				(service == NULL) ? NULL : (service = (g_object_unref (service), NULL));
			}
			(info == NULL) ? NULL : (info = (rygel_resource_info_unref (info), NULL));
		}
		(_info_it == NULL) ? NULL : (_info_it = (g_object_unref (_info_it), NULL));
	}
	while (__params_it > __params) {
		--__params_it;
		g_value_unset (&__params_it->value);
	}
	g_free (__params);
	return self;
}


RygelMediaServer* rygel_media_server_new (GUPnPContext* context, RygelPlugin* plugin, xmlDoc* description_doc, const char* relative_location) {
	return rygel_media_server_construct (RYGEL_TYPE_MEDIA_SERVER, context, plugin, description_doc, relative_location);
}


static void rygel_media_server_xml_doc_free (xmlDoc* doc, RygelMediaServer* server) {
	g_return_if_fail (server != NULL);
	xmlFreeDoc (doc);
}


static void rygel_media_server_class_init (RygelMediaServerClass * klass) {
	rygel_media_server_parent_class = g_type_class_peek_parent (klass);
	g_type_class_add_private (klass, sizeof (RygelMediaServerPrivate));
	G_OBJECT_CLASS (klass)->finalize = rygel_media_server_finalize;
}


static void rygel_media_server_instance_init (RygelMediaServer * self) {
	self->priv = RYGEL_MEDIA_SERVER_GET_PRIVATE (self);
}


static void rygel_media_server_finalize (GObject* obj) {
	RygelMediaServer * self;
	self = RYGEL_MEDIA_SERVER (obj);
	(self->priv->services == NULL) ? NULL : (self->priv->services = (g_object_unref (self->priv->services), NULL));
	G_OBJECT_CLASS (rygel_media_server_parent_class)->finalize (obj);
}


GType rygel_media_server_get_type (void) {
	static GType rygel_media_server_type_id = 0;
	if (rygel_media_server_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (RygelMediaServerClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) rygel_media_server_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (RygelMediaServer), 0, (GInstanceInitFunc) rygel_media_server_instance_init, NULL };
		rygel_media_server_type_id = g_type_register_static (GUPNP_TYPE_ROOT_DEVICE, "RygelMediaServer", &g_define_type_info, 0);
	}
	return rygel_media_server_type_id;
}




