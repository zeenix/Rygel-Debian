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


#define RYGEL_TYPE_TEST_CONTENT_DIR (rygel_test_content_dir_get_type ())
#define RYGEL_TEST_CONTENT_DIR(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_TEST_CONTENT_DIR, RygelTestContentDir))
#define RYGEL_TEST_CONTENT_DIR_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_TEST_CONTENT_DIR, RygelTestContentDirClass))
#define RYGEL_IS_TEST_CONTENT_DIR(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_TEST_CONTENT_DIR))
#define RYGEL_IS_TEST_CONTENT_DIR_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_TEST_CONTENT_DIR))
#define RYGEL_TEST_CONTENT_DIR_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_TEST_CONTENT_DIR, RygelTestContentDirClass))

typedef struct _RygelTestContentDir RygelTestContentDir;
typedef struct _RygelTestContentDirClass RygelTestContentDirClass;



GType rygel_test_content_dir_get_type (void);
void module_init (RygelPluginLoader* loader);



void module_init (RygelPluginLoader* loader) {
	RygelPlugin* plugin;
	RygelResourceInfo* resource_info;
	g_return_if_fail (loader != NULL);
	plugin = rygel_plugin_new ("Test", "Test Streams");
	/* We only implement a ContentDirectory service*/
	resource_info = rygel_resource_info_new (RYGEL_CONTENT_DIRECTORY_UPNP_ID, RYGEL_CONTENT_DIRECTORY_UPNP_TYPE, RYGEL_CONTENT_DIRECTORY_DESCRIPTION_PATH, RYGEL_TYPE_TEST_CONTENT_DIR);
	rygel_plugin_add_resource (plugin, resource_info);
	rygel_plugin_loader_add_plugin (loader, plugin);
	(plugin == NULL) ? NULL : (plugin = (g_object_unref (plugin), NULL));
	(resource_info == NULL) ? NULL : (resource_info = (rygel_resource_info_unref (resource_info), NULL));
}




