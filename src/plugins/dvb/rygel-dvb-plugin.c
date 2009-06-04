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


#define TYPE_DVB_PLUGIN (dvb_plugin_get_type ())
#define DVB_PLUGIN(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_DVB_PLUGIN, DVBPlugin))
#define DVB_PLUGIN_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_DVB_PLUGIN, DVBPluginClass))
#define IS_DVB_PLUGIN(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_DVB_PLUGIN))
#define IS_DVB_PLUGIN_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_DVB_PLUGIN))
#define DVB_PLUGIN_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_DVB_PLUGIN, DVBPluginClass))

typedef struct _DVBPlugin DVBPlugin;
typedef struct _DVBPluginClass DVBPluginClass;
typedef struct _DVBPluginPrivate DVBPluginPrivate;

#define RYGEL_TYPE_DVB_CONTENT_DIR (rygel_dvb_content_dir_get_type ())
#define RYGEL_DVB_CONTENT_DIR(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_DVB_CONTENT_DIR, RygelDVBContentDir))
#define RYGEL_DVB_CONTENT_DIR_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_DVB_CONTENT_DIR, RygelDVBContentDirClass))
#define RYGEL_IS_DVB_CONTENT_DIR(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_DVB_CONTENT_DIR))
#define RYGEL_IS_DVB_CONTENT_DIR_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_DVB_CONTENT_DIR))
#define RYGEL_DVB_CONTENT_DIR_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_DVB_CONTENT_DIR, RygelDVBContentDirClass))

typedef struct _RygelDVBContentDir RygelDVBContentDir;
typedef struct _RygelDVBContentDirClass RygelDVBContentDirClass;

/* Implementation of DVB related services, based on DVBDaemon. */
struct _DVBPlugin {
	RygelPlugin parent_instance;
	DVBPluginPrivate * priv;
};

struct _DVBPluginClass {
	RygelPluginClass parent_class;
};



GType dvb_plugin_get_type (void);
enum  {
	DVB_PLUGIN_DUMMY_PROPERTY
};
GType rygel_dvb_content_dir_get_type (void);
DVBPlugin* dvb_plugin_new (void);
DVBPlugin* dvb_plugin_construct (GType object_type);
DVBPlugin* dvb_plugin_new (void);
static gpointer dvb_plugin_parent_class = NULL;



DVBPlugin* dvb_plugin_construct (GType object_type) {
	DVBPlugin * self;
	RygelResourceInfo* resource_info;
	self = (DVBPlugin*) rygel_plugin_construct (object_type, "DVB", "Digital TV");
	resource_info = rygel_resource_info_new (RYGEL_CONTENT_DIRECTORY_UPNP_ID, RYGEL_CONTENT_DIRECTORY_UPNP_TYPE, RYGEL_CONTENT_DIRECTORY_DESCRIPTION_PATH, RYGEL_TYPE_DVB_CONTENT_DIR);
	rygel_plugin_add_resource ((RygelPlugin*) self, resource_info);
	(resource_info == NULL) ? NULL : (resource_info = (rygel_resource_info_unref (resource_info), NULL));
	return self;
}


DVBPlugin* dvb_plugin_new (void) {
	return dvb_plugin_construct (TYPE_DVB_PLUGIN);
}


static void dvb_plugin_class_init (DVBPluginClass * klass) {
	dvb_plugin_parent_class = g_type_class_peek_parent (klass);
}


static void dvb_plugin_instance_init (DVBPlugin * self) {
}


GType dvb_plugin_get_type (void) {
	static GType dvb_plugin_type_id = 0;
	if (dvb_plugin_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (DVBPluginClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) dvb_plugin_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (DVBPlugin), 0, (GInstanceInitFunc) dvb_plugin_instance_init, NULL };
		dvb_plugin_type_id = g_type_register_static (RYGEL_TYPE_PLUGIN, "DVBPlugin", &g_define_type_info, 0);
	}
	return dvb_plugin_type_id;
}




