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


#define RYGEL_TYPE_MEDIATHEK_CONTENT_DIR (rygel_mediathek_content_dir_get_type ())
#define RYGEL_MEDIATHEK_CONTENT_DIR(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_MEDIATHEK_CONTENT_DIR, RygelMediathekContentDir))
#define RYGEL_MEDIATHEK_CONTENT_DIR_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_MEDIATHEK_CONTENT_DIR, RygelMediathekContentDirClass))
#define RYGEL_IS_MEDIATHEK_CONTENT_DIR(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_MEDIATHEK_CONTENT_DIR))
#define RYGEL_IS_MEDIATHEK_CONTENT_DIR_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_MEDIATHEK_CONTENT_DIR))
#define RYGEL_MEDIATHEK_CONTENT_DIR_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_MEDIATHEK_CONTENT_DIR, RygelMediathekContentDirClass))

typedef struct _RygelMediathekContentDir RygelMediathekContentDir;
typedef struct _RygelMediathekContentDirClass RygelMediathekContentDirClass;
typedef struct _RygelMediathekContentDirPrivate RygelMediathekContentDirPrivate;

#define RYGEL_TYPE_MEDIATHEK_ROOT_CONTAINER (rygel_mediathek_root_container_get_type ())
#define RYGEL_MEDIATHEK_ROOT_CONTAINER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_MEDIATHEK_ROOT_CONTAINER, RygelMediathekRootContainer))
#define RYGEL_MEDIATHEK_ROOT_CONTAINER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_MEDIATHEK_ROOT_CONTAINER, RygelMediathekRootContainerClass))
#define RYGEL_IS_MEDIATHEK_ROOT_CONTAINER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_MEDIATHEK_ROOT_CONTAINER))
#define RYGEL_IS_MEDIATHEK_ROOT_CONTAINER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_MEDIATHEK_ROOT_CONTAINER))
#define RYGEL_MEDIATHEK_ROOT_CONTAINER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_MEDIATHEK_ROOT_CONTAINER, RygelMediathekRootContainerClass))

typedef struct _RygelMediathekRootContainer RygelMediathekRootContainer;
typedef struct _RygelMediathekRootContainerClass RygelMediathekRootContainerClass;

struct _RygelMediathekContentDir {
	RygelContentDirectory parent_instance;
	RygelMediathekContentDirPrivate * priv;
};

struct _RygelMediathekContentDirClass {
	RygelContentDirectoryClass parent_class;
};



GType rygel_mediathek_content_dir_get_type (void);
void module_init (RygelPluginLoader* loader);
enum  {
	RYGEL_MEDIATHEK_CONTENT_DIR_DUMMY_PROPERTY
};
RygelMediathekRootContainer* rygel_mediathek_root_container_new (void);
RygelMediathekRootContainer* rygel_mediathek_root_container_construct (GType object_type);
GType rygel_mediathek_root_container_get_type (void);
static RygelMediaContainer* rygel_mediathek_content_dir_real_create_root_container (RygelContentDirectory* base);
RygelMediathekContentDir* rygel_mediathek_content_dir_new (void);
RygelMediathekContentDir* rygel_mediathek_content_dir_construct (GType object_type);
RygelMediathekContentDir* rygel_mediathek_content_dir_new (void);
static gpointer rygel_mediathek_content_dir_parent_class = NULL;



void module_init (RygelPluginLoader* loader) {
	RygelPlugin* plugin;
	RygelResourceInfo* resource_info;
	g_return_if_fail (loader != NULL);
	plugin = rygel_plugin_new ("ZDFMediathek", "ZDF Mediathek");
	resource_info = rygel_resource_info_new (RYGEL_CONTENT_DIRECTORY_UPNP_ID, RYGEL_CONTENT_DIRECTORY_UPNP_TYPE, RYGEL_CONTENT_DIRECTORY_DESCRIPTION_PATH, RYGEL_TYPE_MEDIATHEK_CONTENT_DIR);
	rygel_plugin_add_resource (plugin, resource_info);
	rygel_plugin_loader_add_plugin (loader, plugin);
	(plugin == NULL) ? NULL : (plugin = (g_object_unref (plugin), NULL));
	(resource_info == NULL) ? NULL : (resource_info = (rygel_resource_info_unref (resource_info), NULL));
}


static RygelMediaContainer* rygel_mediathek_content_dir_real_create_root_container (RygelContentDirectory* base) {
	RygelMediathekContentDir * self;
	self = (RygelMediathekContentDir*) base;
	return (RygelMediaContainer*) rygel_mediathek_root_container_new ();
}


RygelMediathekContentDir* rygel_mediathek_content_dir_construct (GType object_type) {
	RygelMediathekContentDir * self;
	self = (RygelMediathekContentDir*) rygel_content_directory_construct (object_type);
	return self;
}


RygelMediathekContentDir* rygel_mediathek_content_dir_new (void) {
	return rygel_mediathek_content_dir_construct (RYGEL_TYPE_MEDIATHEK_CONTENT_DIR);
}


static void rygel_mediathek_content_dir_class_init (RygelMediathekContentDirClass * klass) {
	rygel_mediathek_content_dir_parent_class = g_type_class_peek_parent (klass);
	RYGEL_CONTENT_DIRECTORY_CLASS (klass)->create_root_container = rygel_mediathek_content_dir_real_create_root_container;
}


static void rygel_mediathek_content_dir_instance_init (RygelMediathekContentDir * self) {
}


GType rygel_mediathek_content_dir_get_type (void) {
	static GType rygel_mediathek_content_dir_type_id = 0;
	if (rygel_mediathek_content_dir_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (RygelMediathekContentDirClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) rygel_mediathek_content_dir_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (RygelMediathekContentDir), 0, (GInstanceInitFunc) rygel_mediathek_content_dir_instance_init, NULL };
		rygel_mediathek_content_dir_type_id = g_type_register_static (RYGEL_TYPE_CONTENT_DIRECTORY, "RygelMediathekContentDir", &g_define_type_info, 0);
	}
	return rygel_mediathek_content_dir_type_id;
}




