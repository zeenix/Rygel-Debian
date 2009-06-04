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
#include <libgupnp/gupnp.h>
#include <stdlib.h>
#include <string.h>


#define RYGEL_TYPE_EXTERNAL_CONTENT_DIR (rygel_external_content_dir_get_type ())
#define RYGEL_EXTERNAL_CONTENT_DIR(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_EXTERNAL_CONTENT_DIR, RygelExternalContentDir))
#define RYGEL_EXTERNAL_CONTENT_DIR_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_EXTERNAL_CONTENT_DIR, RygelExternalContentDirClass))
#define RYGEL_IS_EXTERNAL_CONTENT_DIR(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_EXTERNAL_CONTENT_DIR))
#define RYGEL_IS_EXTERNAL_CONTENT_DIR_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_EXTERNAL_CONTENT_DIR))
#define RYGEL_EXTERNAL_CONTENT_DIR_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_EXTERNAL_CONTENT_DIR, RygelExternalContentDirClass))

typedef struct _RygelExternalContentDir RygelExternalContentDir;
typedef struct _RygelExternalContentDirClass RygelExternalContentDirClass;
typedef struct _RygelExternalContentDirPrivate RygelExternalContentDirPrivate;

#define TYPE_EXTERNAL_PLUGIN (external_plugin_get_type ())
#define EXTERNAL_PLUGIN(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_EXTERNAL_PLUGIN, ExternalPlugin))
#define EXTERNAL_PLUGIN_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_EXTERNAL_PLUGIN, ExternalPluginClass))
#define IS_EXTERNAL_PLUGIN(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_EXTERNAL_PLUGIN))
#define IS_EXTERNAL_PLUGIN_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_EXTERNAL_PLUGIN))
#define EXTERNAL_PLUGIN_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_EXTERNAL_PLUGIN, ExternalPluginClass))

typedef struct _ExternalPlugin ExternalPlugin;
typedef struct _ExternalPluginClass ExternalPluginClass;
typedef struct _ExternalPluginPrivate ExternalPluginPrivate;

#define RYGEL_TYPE_EXTERNAL_CONTAINER (rygel_external_container_get_type ())
#define RYGEL_EXTERNAL_CONTAINER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_EXTERNAL_CONTAINER, RygelExternalContainer))
#define RYGEL_EXTERNAL_CONTAINER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_EXTERNAL_CONTAINER, RygelExternalContainerClass))
#define RYGEL_IS_EXTERNAL_CONTAINER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_EXTERNAL_CONTAINER))
#define RYGEL_IS_EXTERNAL_CONTAINER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_EXTERNAL_CONTAINER))
#define RYGEL_EXTERNAL_CONTAINER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_EXTERNAL_CONTAINER, RygelExternalContainerClass))

typedef struct _RygelExternalContainer RygelExternalContainer;
typedef struct _RygelExternalContainerClass RygelExternalContainerClass;

/**
 * Implementation of External ContentDirectory service.
 */
struct _RygelExternalContentDir {
	RygelContentDirectory parent_instance;
	RygelExternalContentDirPrivate * priv;
};

struct _RygelExternalContentDirClass {
	RygelContentDirectoryClass parent_class;
};

struct _ExternalPlugin {
	RygelPlugin parent_instance;
	ExternalPluginPrivate * priv;
	char* service_name;
	char* root_object;
};

struct _ExternalPluginClass {
	RygelPluginClass parent_class;
};



GType rygel_external_content_dir_get_type (void);
enum  {
	RYGEL_EXTERNAL_CONTENT_DIR_DUMMY_PROPERTY
};
GType external_plugin_get_type (void);
GType rygel_external_container_get_type (void);
RygelExternalContainer* rygel_external_container_new (const char* id, const char* service_name, const char* object_path, const char* host_ip, RygelExternalContainer* parent);
RygelExternalContainer* rygel_external_container_construct (GType object_type, const char* id, const char* service_name, const char* object_path, const char* host_ip, RygelExternalContainer* parent);
static RygelMediaContainer* rygel_external_content_dir_real_create_root_container (RygelContentDirectory* base);
RygelExternalContentDir* rygel_external_content_dir_new (void);
RygelExternalContentDir* rygel_external_content_dir_construct (GType object_type);
RygelExternalContentDir* rygel_external_content_dir_new (void);
static gpointer rygel_external_content_dir_parent_class = NULL;



/* Pubic methods*/
static RygelMediaContainer* rygel_external_content_dir_real_create_root_container (RygelContentDirectory* base) {
	RygelExternalContentDir * self;
	ExternalPlugin* _tmp2_;
	GUPnPRootDevice* _tmp1_;
	GUPnPRootDevice* _tmp0_;
	ExternalPlugin* _tmp3_;
	ExternalPlugin* plugin;
	RygelMediaContainer* _tmp4_;
	self = (RygelExternalContentDir*) base;
	_tmp2_ = NULL;
	_tmp1_ = NULL;
	_tmp0_ = NULL;
	_tmp3_ = NULL;
	plugin = (_tmp3_ = (_tmp2_ = EXTERNAL_PLUGIN (gupnp_device_info_get_resource_factory ((GUPnPDeviceInfo*) (_tmp1_ = (g_object_get ((GUPnPService*) self, "root-device", &_tmp0_, NULL), _tmp0_)))), (_tmp2_ == NULL) ? NULL : g_object_ref (_tmp2_)), (_tmp1_ == NULL) ? NULL : (_tmp1_ = (g_object_unref (_tmp1_), NULL)), _tmp3_);
	_tmp4_ = NULL;
	return (_tmp4_ = (RygelMediaContainer*) rygel_external_container_new ("0", plugin->service_name, plugin->root_object, gupnp_context_get_host_ip (gupnp_service_info_get_context ((GUPnPServiceInfo*) self)), NULL), (plugin == NULL) ? NULL : (plugin = (g_object_unref (plugin), NULL)), _tmp4_);
}


/**
 * Implementation of External ContentDirectory service.
 */
RygelExternalContentDir* rygel_external_content_dir_construct (GType object_type) {
	RygelExternalContentDir * self;
	self = (RygelExternalContentDir*) rygel_content_directory_construct (object_type);
	return self;
}


RygelExternalContentDir* rygel_external_content_dir_new (void) {
	return rygel_external_content_dir_construct (RYGEL_TYPE_EXTERNAL_CONTENT_DIR);
}


static void rygel_external_content_dir_class_init (RygelExternalContentDirClass * klass) {
	rygel_external_content_dir_parent_class = g_type_class_peek_parent (klass);
	RYGEL_CONTENT_DIRECTORY_CLASS (klass)->create_root_container = rygel_external_content_dir_real_create_root_container;
}


static void rygel_external_content_dir_instance_init (RygelExternalContentDir * self) {
}


GType rygel_external_content_dir_get_type (void) {
	static GType rygel_external_content_dir_type_id = 0;
	if (rygel_external_content_dir_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (RygelExternalContentDirClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) rygel_external_content_dir_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (RygelExternalContentDir), 0, (GInstanceInitFunc) rygel_external_content_dir_instance_init, NULL };
		rygel_external_content_dir_type_id = g_type_register_static (RYGEL_TYPE_CONTENT_DIRECTORY, "RygelExternalContentDir", &g_define_type_info, 0);
	}
	return rygel_external_content_dir_type_id;
}




