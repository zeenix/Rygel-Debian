/*
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
#include <libgupnp/gupnp.h>
#include <stdlib.h>
#include <string.h>
#include <gee/arraylist.h>
#include <gee/collection.h>


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

#define RYGEL_TYPE_CONNECTION_MANAGER (rygel_connection_manager_get_type ())
#define RYGEL_CONNECTION_MANAGER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_CONNECTION_MANAGER, RygelConnectionManager))
#define RYGEL_CONNECTION_MANAGER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_CONNECTION_MANAGER, RygelConnectionManagerClass))
#define RYGEL_IS_CONNECTION_MANAGER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_CONNECTION_MANAGER))
#define RYGEL_IS_CONNECTION_MANAGER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_CONNECTION_MANAGER))
#define RYGEL_CONNECTION_MANAGER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_CONNECTION_MANAGER, RygelConnectionManagerClass))

typedef struct _RygelConnectionManager RygelConnectionManager;
typedef struct _RygelConnectionManagerClass RygelConnectionManagerClass;
typedef struct _RygelResourceInfoPrivate RygelResourceInfoPrivate;

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

struct _RygelPluginPrivate {
	gboolean _available;
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
#define RYGEL_PLUGIN_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), RYGEL_TYPE_PLUGIN, RygelPluginPrivate))
enum  {
	RYGEL_PLUGIN_DUMMY_PROPERTY,
	RYGEL_PLUGIN_AVAILABLE
};
void rygel_plugin_set_available (RygelPlugin* self, gboolean value);
#define RYGEL_CONNECTION_MANAGER_UPNP_ID "urn:upnp-org:serviceId:ConnectionManager"
#define RYGEL_CONNECTION_MANAGER_UPNP_TYPE "urn:schemas-upnp-org:service:ConnectionManager:2"
#define RYGEL_CONNECTION_MANAGER_DESCRIPTION_PATH "xml/ConnectionManager.xml"
GType rygel_connection_manager_get_type (void);
RygelResourceInfo* rygel_resource_info_new (const char* upnp_id, const char* upnp_type, const char* description_path, GType type);
RygelResourceInfo* rygel_resource_info_construct (GType object_type, const char* upnp_id, const char* upnp_type, const char* description_path, GType type);
void rygel_plugin_add_resource (RygelPlugin* self, RygelResourceInfo* resource_info);
RygelPlugin* rygel_plugin_new (const char* name, const char* title);
RygelPlugin* rygel_plugin_construct (GType object_type, const char* name, const char* title);
RygelPlugin* rygel_plugin_new (const char* name, const char* title);
void rygel_plugin_add_icon (RygelPlugin* self, RygelIconInfo* icon_info);
gboolean rygel_plugin_get_available (RygelPlugin* self);
static gpointer rygel_plugin_parent_class = NULL;
static void rygel_plugin_finalize (GObject* obj);
static void rygel_plugin_get_property (GObject * object, guint property_id, GValue * value, GParamSpec * pspec);
static void rygel_plugin_set_property (GObject * object, guint property_id, const GValue * value, GParamSpec * pspec);



RygelPlugin* rygel_plugin_construct (GType object_type, const char* name, const char* title) {
	RygelPlugin * self;
	char* _tmp1_;
	const char* _tmp0_;
	char* _tmp3_;
	const char* _tmp2_;
	GeeArrayList* _tmp6_;
	GeeArrayList* _tmp7_;
	RygelResourceInfo* resource_info;
	g_return_val_if_fail (name != NULL, NULL);
	self = g_object_newv (object_type, 0, NULL);
	_tmp1_ = NULL;
	_tmp0_ = NULL;
	self->name = (_tmp1_ = (_tmp0_ = name, (_tmp0_ == NULL) ? NULL : g_strdup (_tmp0_)), self->name = (g_free (self->name), NULL), _tmp1_);
	_tmp3_ = NULL;
	_tmp2_ = NULL;
	self->title = (_tmp3_ = (_tmp2_ = title, (_tmp2_ == NULL) ? NULL : g_strdup (_tmp2_)), self->title = (g_free (self->title), NULL), _tmp3_);
	rygel_plugin_set_available (self, TRUE);
	if (title == NULL) {
		char* _tmp5_;
		const char* _tmp4_;
		_tmp5_ = NULL;
		_tmp4_ = NULL;
		self->title = (_tmp5_ = (_tmp4_ = name, (_tmp4_ == NULL) ? NULL : g_strdup (_tmp4_)), self->title = (g_free (self->title), NULL), _tmp5_);
	}
	_tmp6_ = NULL;
	self->resource_infos = (_tmp6_ = gee_array_list_new (RYGEL_TYPE_RESOURCE_INFO, (GBoxedCopyFunc) rygel_resource_info_ref, rygel_resource_info_unref, g_direct_equal), (self->resource_infos == NULL) ? NULL : (self->resource_infos = (g_object_unref (self->resource_infos), NULL)), _tmp6_);
	_tmp7_ = NULL;
	self->icon_infos = (_tmp7_ = gee_array_list_new (RYGEL_TYPE_ICON_INFO, (GBoxedCopyFunc) rygel_icon_info_ref, rygel_icon_info_unref, g_direct_equal), (self->icon_infos == NULL) ? NULL : (self->icon_infos = (g_object_unref (self->icon_infos), NULL)), _tmp7_);
	resource_info = rygel_resource_info_new (RYGEL_CONNECTION_MANAGER_UPNP_ID, RYGEL_CONNECTION_MANAGER_UPNP_TYPE, RYGEL_CONNECTION_MANAGER_DESCRIPTION_PATH, RYGEL_TYPE_CONNECTION_MANAGER);
	rygel_plugin_add_resource (self, resource_info);
	(resource_info == NULL) ? NULL : (resource_info = (rygel_resource_info_unref (resource_info), NULL));
	return self;
}


RygelPlugin* rygel_plugin_new (const char* name, const char* title) {
	return rygel_plugin_construct (RYGEL_TYPE_PLUGIN, name, title);
}


void rygel_plugin_add_resource (RygelPlugin* self, RygelResourceInfo* resource_info) {
	g_return_if_fail (self != NULL);
	g_return_if_fail (resource_info != NULL);
	gee_collection_add ((GeeCollection*) self->resource_infos, resource_info);
	gupnp_resource_factory_register_resource_type ((GUPnPResourceFactory*) self, resource_info->upnp_type, resource_info->type);
}


void rygel_plugin_add_icon (RygelPlugin* self, RygelIconInfo* icon_info) {
	g_return_if_fail (self != NULL);
	g_return_if_fail (icon_info != NULL);
	gee_collection_add ((GeeCollection*) self->icon_infos, icon_info);
}


gboolean rygel_plugin_get_available (RygelPlugin* self) {
	g_return_val_if_fail (self != NULL, FALSE);
	return self->priv->_available;
}


void rygel_plugin_set_available (RygelPlugin* self, gboolean value) {
	g_return_if_fail (self != NULL);
	self->priv->_available = value;
	g_object_notify ((GObject *) self, "available");
}


static void rygel_plugin_class_init (RygelPluginClass * klass) {
	rygel_plugin_parent_class = g_type_class_peek_parent (klass);
	g_type_class_add_private (klass, sizeof (RygelPluginPrivate));
	G_OBJECT_CLASS (klass)->get_property = rygel_plugin_get_property;
	G_OBJECT_CLASS (klass)->set_property = rygel_plugin_set_property;
	G_OBJECT_CLASS (klass)->finalize = rygel_plugin_finalize;
	g_object_class_install_property (G_OBJECT_CLASS (klass), RYGEL_PLUGIN_AVAILABLE, g_param_spec_boolean ("available", "available", "available", FALSE, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
}


static void rygel_plugin_instance_init (RygelPlugin * self) {
	self->priv = RYGEL_PLUGIN_GET_PRIVATE (self);
}


static void rygel_plugin_finalize (GObject* obj) {
	RygelPlugin * self;
	self = RYGEL_PLUGIN (obj);
	self->name = (g_free (self->name), NULL);
	self->title = (g_free (self->title), NULL);
	(self->resource_infos == NULL) ? NULL : (self->resource_infos = (g_object_unref (self->resource_infos), NULL));
	(self->icon_infos == NULL) ? NULL : (self->icon_infos = (g_object_unref (self->icon_infos), NULL));
	G_OBJECT_CLASS (rygel_plugin_parent_class)->finalize (obj);
}


GType rygel_plugin_get_type (void) {
	static GType rygel_plugin_type_id = 0;
	if (rygel_plugin_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (RygelPluginClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) rygel_plugin_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (RygelPlugin), 0, (GInstanceInitFunc) rygel_plugin_instance_init, NULL };
		rygel_plugin_type_id = g_type_register_static (GUPNP_TYPE_RESOURCE_FACTORY, "RygelPlugin", &g_define_type_info, 0);
	}
	return rygel_plugin_type_id;
}


static void rygel_plugin_get_property (GObject * object, guint property_id, GValue * value, GParamSpec * pspec) {
	RygelPlugin * self;
	gpointer boxed;
	self = RYGEL_PLUGIN (object);
	switch (property_id) {
		case RYGEL_PLUGIN_AVAILABLE:
		g_value_set_boolean (value, rygel_plugin_get_available (self));
		break;
		default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}


static void rygel_plugin_set_property (GObject * object, guint property_id, const GValue * value, GParamSpec * pspec) {
	RygelPlugin * self;
	self = RYGEL_PLUGIN (object);
	switch (property_id) {
		case RYGEL_PLUGIN_AVAILABLE:
		rygel_plugin_set_available (self, g_value_get_boolean (value));
		break;
		default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}




