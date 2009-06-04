/*
 * Copyright (C) 2008-2009 Jens Georg <mail@jensge.org>.
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


#define RYGEL_TYPE_FOLDER_CONTENT_DIR (rygel_folder_content_dir_get_type ())
#define RYGEL_FOLDER_CONTENT_DIR(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_FOLDER_CONTENT_DIR, RygelFolderContentDir))
#define RYGEL_FOLDER_CONTENT_DIR_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_FOLDER_CONTENT_DIR, RygelFolderContentDirClass))
#define RYGEL_IS_FOLDER_CONTENT_DIR(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_FOLDER_CONTENT_DIR))
#define RYGEL_IS_FOLDER_CONTENT_DIR_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_FOLDER_CONTENT_DIR))
#define RYGEL_FOLDER_CONTENT_DIR_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_FOLDER_CONTENT_DIR, RygelFolderContentDirClass))

typedef struct _RygelFolderContentDir RygelFolderContentDir;
typedef struct _RygelFolderContentDirClass RygelFolderContentDirClass;
typedef struct _RygelFolderContentDirPrivate RygelFolderContentDirPrivate;

#define RYGEL_TYPE_FOLDER_ROOT_CONTAINER (rygel_folder_root_container_get_type ())
#define RYGEL_FOLDER_ROOT_CONTAINER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_FOLDER_ROOT_CONTAINER, RygelFolderRootContainer))
#define RYGEL_FOLDER_ROOT_CONTAINER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_FOLDER_ROOT_CONTAINER, RygelFolderRootContainerClass))
#define RYGEL_IS_FOLDER_ROOT_CONTAINER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_FOLDER_ROOT_CONTAINER))
#define RYGEL_IS_FOLDER_ROOT_CONTAINER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_FOLDER_ROOT_CONTAINER))
#define RYGEL_FOLDER_ROOT_CONTAINER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_FOLDER_ROOT_CONTAINER, RygelFolderRootContainerClass))

typedef struct _RygelFolderRootContainer RygelFolderRootContainer;
typedef struct _RygelFolderRootContainerClass RygelFolderRootContainerClass;

struct _RygelFolderContentDir {
	RygelContentDirectory parent_instance;
	RygelFolderContentDirPrivate * priv;
};

struct _RygelFolderContentDirClass {
	RygelContentDirectoryClass parent_class;
};



GType rygel_folder_content_dir_get_type (void);
void module_init (RygelPluginLoader* loader);
enum  {
	RYGEL_FOLDER_CONTENT_DIR_DUMMY_PROPERTY
};
RygelFolderRootContainer* rygel_folder_root_container_new (void);
RygelFolderRootContainer* rygel_folder_root_container_construct (GType object_type);
GType rygel_folder_root_container_get_type (void);
static RygelMediaContainer* rygel_folder_content_dir_real_create_root_container (RygelContentDirectory* base);
RygelFolderContentDir* rygel_folder_content_dir_new (void);
RygelFolderContentDir* rygel_folder_content_dir_construct (GType object_type);
RygelFolderContentDir* rygel_folder_content_dir_new (void);
static gpointer rygel_folder_content_dir_parent_class = NULL;



/**
 * Simple plugin which exposes the media contents of a directory via UPnP.
 * 
 * This plugin is currently meant for testing purposes only. It has several 
 * drawbacks like:
 *
 * * No sorting
 * * flat hierarchy
 * * no metadata extraction apart from content type
 * * no monitoring
 */
#line 38 "rygel-folder-plugin.vala"
void module_init (RygelPluginLoader* loader) {
#line 88 "rygel-folder-plugin.c"
	RygelPlugin* plugin;
	RygelResourceInfo* resource_info;
#line 38 "rygel-folder-plugin.vala"
	g_return_if_fail (loader != NULL);
#line 93 "rygel-folder-plugin.c"
	plugin = rygel_plugin_new ("Folder", "@REALNAME@'s media");
	resource_info = rygel_resource_info_new (RYGEL_CONTENT_DIRECTORY_UPNP_ID, RYGEL_CONTENT_DIRECTORY_UPNP_TYPE, RYGEL_CONTENT_DIRECTORY_DESCRIPTION_PATH, RYGEL_TYPE_FOLDER_CONTENT_DIR);
#line 46 "rygel-folder-plugin.vala"
	rygel_plugin_add_resource (plugin, resource_info);
#line 48 "rygel-folder-plugin.vala"
	rygel_plugin_loader_add_plugin (loader, plugin);
#line 100 "rygel-folder-plugin.c"
	(plugin == NULL) ? NULL : (plugin = (g_object_unref (plugin), NULL));
	(resource_info == NULL) ? NULL : (resource_info = (rygel_resource_info_unref (resource_info), NULL));
}


#line 52 "rygel-folder-plugin.vala"
static RygelMediaContainer* rygel_folder_content_dir_real_create_root_container (RygelContentDirectory* base) {
#line 108 "rygel-folder-plugin.c"
	RygelFolderContentDir * self;
	self = (RygelFolderContentDir*) base;
#line 53 "rygel-folder-plugin.vala"
	return (RygelMediaContainer*) rygel_folder_root_container_new ();
#line 113 "rygel-folder-plugin.c"
}


#line 51 "rygel-folder-plugin.vala"
RygelFolderContentDir* rygel_folder_content_dir_construct (GType object_type) {
#line 119 "rygel-folder-plugin.c"
	RygelFolderContentDir * self;
	self = (RygelFolderContentDir*) rygel_content_directory_construct (object_type);
	return self;
}


#line 51 "rygel-folder-plugin.vala"
RygelFolderContentDir* rygel_folder_content_dir_new (void) {
#line 51 "rygel-folder-plugin.vala"
	return rygel_folder_content_dir_construct (RYGEL_TYPE_FOLDER_CONTENT_DIR);
#line 130 "rygel-folder-plugin.c"
}


static void rygel_folder_content_dir_class_init (RygelFolderContentDirClass * klass) {
	rygel_folder_content_dir_parent_class = g_type_class_peek_parent (klass);
	RYGEL_CONTENT_DIRECTORY_CLASS (klass)->create_root_container = rygel_folder_content_dir_real_create_root_container;
}


static void rygel_folder_content_dir_instance_init (RygelFolderContentDir * self) {
}


GType rygel_folder_content_dir_get_type (void) {
	static GType rygel_folder_content_dir_type_id = 0;
	if (rygel_folder_content_dir_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (RygelFolderContentDirClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) rygel_folder_content_dir_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (RygelFolderContentDir), 0, (GInstanceInitFunc) rygel_folder_content_dir_instance_init, NULL };
		rygel_folder_content_dir_type_id = g_type_register_static (RYGEL_TYPE_CONTENT_DIRECTORY, "RygelFolderContentDir", &g_define_type_info, 0);
	}
	return rygel_folder_content_dir_type_id;
}




