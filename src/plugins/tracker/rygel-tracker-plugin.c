/*
 * Copyright (C) 2008 Zeeshan Ali <zeenix@gmail.com>.
 *
 * Author: Zeeshan Ali <zeenix@gmail.com>
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


#define TYPE_TRACKER_PLUGIN (tracker_plugin_get_type ())
#define TRACKER_PLUGIN(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_TRACKER_PLUGIN, TrackerPlugin))
#define TRACKER_PLUGIN_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_TRACKER_PLUGIN, TrackerPluginClass))
#define IS_TRACKER_PLUGIN(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_TRACKER_PLUGIN))
#define IS_TRACKER_PLUGIN_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_TRACKER_PLUGIN))
#define TRACKER_PLUGIN_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_TRACKER_PLUGIN, TrackerPluginClass))

typedef struct _TrackerPlugin TrackerPlugin;
typedef struct _TrackerPluginClass TrackerPluginClass;
typedef struct _TrackerPluginPrivate TrackerPluginPrivate;

#define RYGEL_TYPE_MEDIA_TRACKER (rygel_media_tracker_get_type ())
#define RYGEL_MEDIA_TRACKER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_MEDIA_TRACKER, RygelMediaTracker))
#define RYGEL_MEDIA_TRACKER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_MEDIA_TRACKER, RygelMediaTrackerClass))
#define RYGEL_IS_MEDIA_TRACKER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_MEDIA_TRACKER))
#define RYGEL_IS_MEDIA_TRACKER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_MEDIA_TRACKER))
#define RYGEL_MEDIA_TRACKER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_MEDIA_TRACKER, RygelMediaTrackerClass))

typedef struct _RygelMediaTracker RygelMediaTracker;
typedef struct _RygelMediaTrackerClass RygelMediaTrackerClass;

struct _TrackerPlugin {
	RygelPlugin parent_instance;
	TrackerPluginPrivate * priv;
};

struct _TrackerPluginClass {
	RygelPluginClass parent_class;
};



GType tracker_plugin_get_type (void);
enum  {
	TRACKER_PLUGIN_DUMMY_PROPERTY
};
#define TRACKER_PLUGIN_ICON DATA_DIR "/icons/hicolor/48x48/apps/tracker.png"
GType rygel_media_tracker_get_type (void);
TrackerPlugin* tracker_plugin_new (void);
TrackerPlugin* tracker_plugin_construct (GType object_type);
TrackerPlugin* tracker_plugin_new (void);
static gpointer tracker_plugin_parent_class = NULL;



/* Path*/
TrackerPlugin* tracker_plugin_construct (GType object_type) {
	TrackerPlugin * self;
	RygelResourceInfo* resource_info;
	RygelIconInfo* icon_info;
	self = (TrackerPlugin*) rygel_plugin_construct (object_type, "Tracker", "@REALNAME@'s media");
	resource_info = rygel_resource_info_new (RYGEL_CONTENT_DIRECTORY_UPNP_ID, RYGEL_CONTENT_DIRECTORY_UPNP_TYPE, RYGEL_CONTENT_DIRECTORY_DESCRIPTION_PATH, RYGEL_TYPE_MEDIA_TRACKER);
	rygel_plugin_add_resource ((RygelPlugin*) self, resource_info);
	icon_info = rygel_icon_info_new ("image/png", (guint) 48, (guint) 48, (guint) 24, TRACKER_PLUGIN_ICON);
	rygel_plugin_add_icon ((RygelPlugin*) self, icon_info);
	(resource_info == NULL) ? NULL : (resource_info = (rygel_resource_info_unref (resource_info), NULL));
	(icon_info == NULL) ? NULL : (icon_info = (rygel_icon_info_unref (icon_info), NULL));
	return self;
}


TrackerPlugin* tracker_plugin_new (void) {
	return tracker_plugin_construct (TYPE_TRACKER_PLUGIN);
}


static void tracker_plugin_class_init (TrackerPluginClass * klass) {
	tracker_plugin_parent_class = g_type_class_peek_parent (klass);
}


static void tracker_plugin_instance_init (TrackerPlugin * self) {
}


GType tracker_plugin_get_type (void) {
	static GType tracker_plugin_type_id = 0;
	if (tracker_plugin_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (TrackerPluginClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) tracker_plugin_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (TrackerPlugin), 0, (GInstanceInitFunc) tracker_plugin_instance_init, NULL };
		tracker_plugin_type_id = g_type_register_static (RYGEL_TYPE_PLUGIN, "TrackerPlugin", &g_define_type_info, 0);
	}
	return tracker_plugin_type_id;
}




