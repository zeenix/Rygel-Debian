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
#include <stdlib.h>
#include <string.h>
#include <dbus/dbus-glib-lowlevel.h>
#include <dbus/dbus-glib.h>


#define RYGEL_TYPE_TRACKER_ITEM (rygel_tracker_item_get_type ())
#define RYGEL_TRACKER_ITEM(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_TRACKER_ITEM, RygelTrackerItem))
#define RYGEL_TRACKER_ITEM_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_TRACKER_ITEM, RygelTrackerItemClass))
#define RYGEL_IS_TRACKER_ITEM(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_TRACKER_ITEM))
#define RYGEL_IS_TRACKER_ITEM_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_TRACKER_ITEM))
#define RYGEL_TRACKER_ITEM_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_TRACKER_ITEM, RygelTrackerItemClass))

typedef struct _RygelTrackerItem RygelTrackerItem;
typedef struct _RygelTrackerItemClass RygelTrackerItemClass;
typedef struct _RygelTrackerItemPrivate RygelTrackerItemPrivate;

#define RYGEL_TYPE_TRACKER_CATEGORY (rygel_tracker_category_get_type ())
#define RYGEL_TRACKER_CATEGORY(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_TRACKER_CATEGORY, RygelTrackerCategory))
#define RYGEL_TRACKER_CATEGORY_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_TRACKER_CATEGORY, RygelTrackerCategoryClass))
#define RYGEL_IS_TRACKER_CATEGORY(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_TRACKER_CATEGORY))
#define RYGEL_IS_TRACKER_CATEGORY_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_TRACKER_CATEGORY))
#define RYGEL_TRACKER_CATEGORY_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_TRACKER_CATEGORY, RygelTrackerCategoryClass))

typedef struct _RygelTrackerCategory RygelTrackerCategory;
typedef struct _RygelTrackerCategoryClass RygelTrackerCategoryClass;
typedef struct _RygelTrackerCategoryPrivate RygelTrackerCategoryPrivate;

/**
 * Represents Tracker item.
 */
struct _RygelTrackerItem {
	RygelMediaItem parent_instance;
	RygelTrackerItemPrivate * priv;
	char* path;
};

struct _RygelTrackerItemClass {
	RygelMediaItemClass parent_class;
	void (*init_from_metadata) (RygelTrackerItem* self, char** values, int values_length1);
};

/**
 * Represents Tracker category.
 */
struct _RygelTrackerCategory {
	RygelMediaContainer parent_instance;
	RygelTrackerCategoryPrivate * priv;
	DBusGProxy* metadata;
	DBusGProxy* search;
	DBusGProxy* tracker;
	char* category;
	char* child_class;
};

struct _RygelTrackerCategoryClass {
	RygelMediaContainerClass parent_class;
	char** (*get_metadata_keys) (RygelTrackerCategory* self, int* result_length1);
	RygelMediaItem* (*create_item) (RygelTrackerCategory* self, const char* path, char** metadata, int metadata_length1);
};



GType rygel_tracker_item_get_type (void);
enum  {
	RYGEL_TRACKER_ITEM_DUMMY_PROPERTY
};
GType rygel_tracker_category_get_type (void);
void rygel_tracker_item_init_from_metadata (RygelTrackerItem* self, char** values, int values_length1);
RygelTrackerItem* rygel_tracker_item_new (const char* id, const char* path, RygelTrackerCategory* parent, char** metadata, int metadata_length1);
RygelTrackerItem* rygel_tracker_item_construct (GType object_type, const char* id, const char* path, RygelTrackerCategory* parent, char** metadata, int metadata_length1);
RygelTrackerItem* rygel_tracker_item_new (const char* id, const char* path, RygelTrackerCategory* parent, char** metadata, int metadata_length1);
char* rygel_tracker_item_seconds_to_iso8601 (RygelTrackerItem* self, const char* seconds);
static void rygel_tracker_item_real_init_from_metadata (RygelTrackerItem* self, char** values, int values_length1);
static gpointer rygel_tracker_item_parent_class = NULL;
static void rygel_tracker_item_finalize (GObject* obj);
static int _vala_strcmp0 (const char * str1, const char * str2);



RygelTrackerItem* rygel_tracker_item_construct (GType object_type, const char* id, const char* path, RygelTrackerCategory* parent, char** metadata, int metadata_length1) {
	RygelTrackerItem * self;
	char* _tmp1_;
	const char* _tmp0_;
	g_return_val_if_fail (id != NULL, NULL);
	g_return_val_if_fail (path != NULL, NULL);
	g_return_val_if_fail (parent != NULL, NULL);
	self = (RygelTrackerItem*) rygel_media_item_construct (object_type, id, (RygelMediaContainer*) parent, "", parent->child_class);
	_tmp1_ = NULL;
	_tmp0_ = NULL;
	self->path = (_tmp1_ = (_tmp0_ = path, (_tmp0_ == NULL) ? NULL : g_strdup (_tmp0_)), self->path = (g_free (self->path), NULL), _tmp1_);
	rygel_tracker_item_init_from_metadata (self, metadata, metadata_length1);
	return self;
}


RygelTrackerItem* rygel_tracker_item_new (const char* id, const char* path, RygelTrackerCategory* parent, char** metadata, int metadata_length1) {
	return rygel_tracker_item_construct (RYGEL_TYPE_TRACKER_ITEM, id, path, parent, metadata, metadata_length1);
}


char* rygel_tracker_item_seconds_to_iso8601 (RygelTrackerItem* self, const char* seconds) {
	char* date;
	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (seconds != NULL, NULL);
	date = NULL;
	if (_vala_strcmp0 (seconds, "") != 0) {
		GTimeVal _tmp0_ = {0};
		GTimeVal tv;
		char* _tmp1_;
		tv = (g_get_current_time (&_tmp0_), _tmp0_);
		tv.tv_sec = (glong) atoi (seconds);
		tv.tv_usec = (glong) 0;
		_tmp1_ = NULL;
		date = (_tmp1_ = g_time_val_to_iso8601 (&tv), date = (g_free (date), NULL), _tmp1_);
	} else {
		char* _tmp2_;
		_tmp2_ = NULL;
		date = (_tmp2_ = g_strdup (""), date = (g_free (date), NULL), _tmp2_);
	}
	return date;
}


static void rygel_tracker_item_real_init_from_metadata (RygelTrackerItem* self, char** values, int values_length1) {
	g_return_if_fail (self != NULL);
	g_critical ("Type `%s' does not implement abstract method `rygel_tracker_item_init_from_metadata'", g_type_name (G_TYPE_FROM_INSTANCE (self)));
	return;
}


void rygel_tracker_item_init_from_metadata (RygelTrackerItem* self, char** values, int values_length1) {
	RYGEL_TRACKER_ITEM_GET_CLASS (self)->init_from_metadata (self, values, values_length1);
}


static void rygel_tracker_item_class_init (RygelTrackerItemClass * klass) {
	rygel_tracker_item_parent_class = g_type_class_peek_parent (klass);
	RYGEL_TRACKER_ITEM_CLASS (klass)->init_from_metadata = rygel_tracker_item_real_init_from_metadata;
	G_OBJECT_CLASS (klass)->finalize = rygel_tracker_item_finalize;
}


static void rygel_tracker_item_instance_init (RygelTrackerItem * self) {
}


static void rygel_tracker_item_finalize (GObject* obj) {
	RygelTrackerItem * self;
	self = RYGEL_TRACKER_ITEM (obj);
	self->path = (g_free (self->path), NULL);
	G_OBJECT_CLASS (rygel_tracker_item_parent_class)->finalize (obj);
}


GType rygel_tracker_item_get_type (void) {
	static GType rygel_tracker_item_type_id = 0;
	if (rygel_tracker_item_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (RygelTrackerItemClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) rygel_tracker_item_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (RygelTrackerItem), 0, (GInstanceInitFunc) rygel_tracker_item_instance_init, NULL };
		rygel_tracker_item_type_id = g_type_register_static (RYGEL_TYPE_MEDIA_ITEM, "RygelTrackerItem", &g_define_type_info, G_TYPE_FLAG_ABSTRACT);
	}
	return rygel_tracker_item_type_id;
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




