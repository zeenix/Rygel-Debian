/*
 * Copyright (C) 2008 Zeeshan Ali <zeenix@gmail.com>.
 * Copyright (C) 2008 Nokia Corporation, all rights reserved.
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
#include <libgupnp/gupnp.h>
#include <stdlib.h>
#include <string.h>


#define RYGEL_TYPE_MEDIA_TRACKER (rygel_media_tracker_get_type ())
#define RYGEL_MEDIA_TRACKER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_MEDIA_TRACKER, RygelMediaTracker))
#define RYGEL_MEDIA_TRACKER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_MEDIA_TRACKER, RygelMediaTrackerClass))
#define RYGEL_IS_MEDIA_TRACKER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_MEDIA_TRACKER))
#define RYGEL_IS_MEDIA_TRACKER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_MEDIA_TRACKER))
#define RYGEL_MEDIA_TRACKER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_MEDIA_TRACKER, RygelMediaTrackerClass))

typedef struct _RygelMediaTracker RygelMediaTracker;
typedef struct _RygelMediaTrackerClass RygelMediaTrackerClass;
typedef struct _RygelMediaTrackerPrivate RygelMediaTrackerPrivate;

#define RYGEL_TYPE_TRACKER_ROOT_CONTAINER (rygel_tracker_root_container_get_type ())
#define RYGEL_TRACKER_ROOT_CONTAINER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_TRACKER_ROOT_CONTAINER, RygelTrackerRootContainer))
#define RYGEL_TRACKER_ROOT_CONTAINER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_TRACKER_ROOT_CONTAINER, RygelTrackerRootContainerClass))
#define RYGEL_IS_TRACKER_ROOT_CONTAINER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_TRACKER_ROOT_CONTAINER))
#define RYGEL_IS_TRACKER_ROOT_CONTAINER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_TRACKER_ROOT_CONTAINER))
#define RYGEL_TRACKER_ROOT_CONTAINER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_TRACKER_ROOT_CONTAINER, RygelTrackerRootContainerClass))

typedef struct _RygelTrackerRootContainer RygelTrackerRootContainer;
typedef struct _RygelTrackerRootContainerClass RygelTrackerRootContainerClass;

/**
 * Implementation of Tracker-based ContentDirectory service.
 */
struct _RygelMediaTracker {
	RygelContentDirectory parent_instance;
	RygelMediaTrackerPrivate * priv;
};

struct _RygelMediaTrackerClass {
	RygelContentDirectoryClass parent_class;
};



GType rygel_media_tracker_get_type (void);
enum  {
	RYGEL_MEDIA_TRACKER_DUMMY_PROPERTY
};
RygelTrackerRootContainer* rygel_tracker_root_container_new (const char* title);
RygelTrackerRootContainer* rygel_tracker_root_container_construct (GType object_type, const char* title);
GType rygel_tracker_root_container_get_type (void);
static RygelMediaContainer* rygel_media_tracker_real_create_root_container (RygelContentDirectory* base);
RygelMediaTracker* rygel_media_tracker_new (void);
RygelMediaTracker* rygel_media_tracker_construct (GType object_type);
RygelMediaTracker* rygel_media_tracker_new (void);
static gpointer rygel_media_tracker_parent_class = NULL;



/* Pubic methods */
static RygelMediaContainer* rygel_media_tracker_real_create_root_container (RygelContentDirectory* base) {
	RygelMediaTracker * self;
	GUPnPRootDevice* _tmp1_;
	GUPnPRootDevice* _tmp0_;
	char* _tmp2_;
	char* friendly_name;
	RygelMediaContainer* _tmp3_;
	self = (RygelMediaTracker*) base;
	_tmp1_ = NULL;
	_tmp0_ = NULL;
	_tmp2_ = NULL;
	friendly_name = (_tmp2_ = gupnp_device_info_get_friendly_name ((GUPnPDeviceInfo*) (_tmp1_ = (g_object_get ((GUPnPService*) self, "root-device", &_tmp0_, NULL), _tmp0_))), (_tmp1_ == NULL) ? NULL : (_tmp1_ = (g_object_unref (_tmp1_), NULL)), _tmp2_);
	_tmp3_ = NULL;
	return (_tmp3_ = (RygelMediaContainer*) rygel_tracker_root_container_new (friendly_name), friendly_name = (g_free (friendly_name), NULL), _tmp3_);
}


/**
 * Implementation of Tracker-based ContentDirectory service.
 */
RygelMediaTracker* rygel_media_tracker_construct (GType object_type) {
	RygelMediaTracker * self;
	self = (RygelMediaTracker*) rygel_content_directory_construct (object_type);
	return self;
}


RygelMediaTracker* rygel_media_tracker_new (void) {
	return rygel_media_tracker_construct (RYGEL_TYPE_MEDIA_TRACKER);
}


static void rygel_media_tracker_class_init (RygelMediaTrackerClass * klass) {
	rygel_media_tracker_parent_class = g_type_class_peek_parent (klass);
	RYGEL_CONTENT_DIRECTORY_CLASS (klass)->create_root_container = rygel_media_tracker_real_create_root_container;
}


static void rygel_media_tracker_instance_init (RygelMediaTracker * self) {
}


GType rygel_media_tracker_get_type (void) {
	static GType rygel_media_tracker_type_id = 0;
	if (rygel_media_tracker_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (RygelMediaTrackerClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) rygel_media_tracker_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (RygelMediaTracker), 0, (GInstanceInitFunc) rygel_media_tracker_instance_init, NULL };
		rygel_media_tracker_type_id = g_type_register_static (RYGEL_TYPE_CONTENT_DIRECTORY, "RygelMediaTracker", &g_define_type_info, 0);
	}
	return rygel_media_tracker_type_id;
}




