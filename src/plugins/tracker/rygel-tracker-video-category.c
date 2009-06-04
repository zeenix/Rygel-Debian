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


#define RYGEL_TYPE_TRACKER_CATEGORY (rygel_tracker_category_get_type ())
#define RYGEL_TRACKER_CATEGORY(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_TRACKER_CATEGORY, RygelTrackerCategory))
#define RYGEL_TRACKER_CATEGORY_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_TRACKER_CATEGORY, RygelTrackerCategoryClass))
#define RYGEL_IS_TRACKER_CATEGORY(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_TRACKER_CATEGORY))
#define RYGEL_IS_TRACKER_CATEGORY_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_TRACKER_CATEGORY))
#define RYGEL_TRACKER_CATEGORY_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_TRACKER_CATEGORY, RygelTrackerCategoryClass))

typedef struct _RygelTrackerCategory RygelTrackerCategory;
typedef struct _RygelTrackerCategoryClass RygelTrackerCategoryClass;
typedef struct _RygelTrackerCategoryPrivate RygelTrackerCategoryPrivate;

#define RYGEL_TYPE_TRACKER_VIDEO_CATEGORY (rygel_tracker_video_category_get_type ())
#define RYGEL_TRACKER_VIDEO_CATEGORY(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_TRACKER_VIDEO_CATEGORY, RygelTrackerVideoCategory))
#define RYGEL_TRACKER_VIDEO_CATEGORY_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_TRACKER_VIDEO_CATEGORY, RygelTrackerVideoCategoryClass))
#define RYGEL_IS_TRACKER_VIDEO_CATEGORY(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_TRACKER_VIDEO_CATEGORY))
#define RYGEL_IS_TRACKER_VIDEO_CATEGORY_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_TRACKER_VIDEO_CATEGORY))
#define RYGEL_TRACKER_VIDEO_CATEGORY_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_TRACKER_VIDEO_CATEGORY, RygelTrackerVideoCategoryClass))

typedef struct _RygelTrackerVideoCategory RygelTrackerVideoCategory;
typedef struct _RygelTrackerVideoCategoryClass RygelTrackerVideoCategoryClass;
typedef struct _RygelTrackerVideoCategoryPrivate RygelTrackerVideoCategoryPrivate;

#define RYGEL_TYPE_TRACKER_ITEM (rygel_tracker_item_get_type ())
#define RYGEL_TRACKER_ITEM(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_TRACKER_ITEM, RygelTrackerItem))
#define RYGEL_TRACKER_ITEM_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_TRACKER_ITEM, RygelTrackerItemClass))
#define RYGEL_IS_TRACKER_ITEM(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_TRACKER_ITEM))
#define RYGEL_IS_TRACKER_ITEM_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_TRACKER_ITEM))
#define RYGEL_TRACKER_ITEM_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_TRACKER_ITEM, RygelTrackerItemClass))

typedef struct _RygelTrackerItem RygelTrackerItem;
typedef struct _RygelTrackerItemClass RygelTrackerItemClass;

#define RYGEL_TYPE_TRACKER_VIDEO_ITEM (rygel_tracker_video_item_get_type ())
#define RYGEL_TRACKER_VIDEO_ITEM(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_TRACKER_VIDEO_ITEM, RygelTrackerVideoItem))
#define RYGEL_TRACKER_VIDEO_ITEM_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_TRACKER_VIDEO_ITEM, RygelTrackerVideoItemClass))
#define RYGEL_IS_TRACKER_VIDEO_ITEM(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_TRACKER_VIDEO_ITEM))
#define RYGEL_IS_TRACKER_VIDEO_ITEM_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_TRACKER_VIDEO_ITEM))
#define RYGEL_TRACKER_VIDEO_ITEM_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_TRACKER_VIDEO_ITEM, RygelTrackerVideoItemClass))

typedef struct _RygelTrackerVideoItem RygelTrackerVideoItem;
typedef struct _RygelTrackerVideoItemClass RygelTrackerVideoItemClass;

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

/**
 * Represents Tracker Video category.
 */
struct _RygelTrackerVideoCategory {
	RygelTrackerCategory parent_instance;
	RygelTrackerVideoCategoryPrivate * priv;
};

struct _RygelTrackerVideoCategoryClass {
	RygelTrackerCategoryClass parent_class;
};



GType rygel_tracker_category_get_type (void);
GType rygel_tracker_video_category_get_type (void);
enum  {
	RYGEL_TRACKER_VIDEO_CATEGORY_DUMMY_PROPERTY
};
RygelTrackerCategory* rygel_tracker_category_new (const char* id, RygelMediaContainer* parent, const char* title, const char* category, const char* child_class);
RygelTrackerCategory* rygel_tracker_category_construct (GType object_type, const char* id, RygelMediaContainer* parent, const char* title, const char* category, const char* child_class);
RygelTrackerVideoCategory* rygel_tracker_video_category_new (const char* id, RygelMediaContainer* parent, const char* title);
RygelTrackerVideoCategory* rygel_tracker_video_category_construct (GType object_type, const char* id, RygelMediaContainer* parent, const char* title);
RygelTrackerVideoCategory* rygel_tracker_video_category_new (const char* id, RygelMediaContainer* parent, const char* title);
char** rygel_tracker_video_item_get_metadata_keys (int* result_length1);
static char** rygel_tracker_video_category_real_get_metadata_keys (RygelTrackerCategory* base, int* result_length1);
RygelTrackerVideoItem* rygel_tracker_video_item_new (const char* id, const char* path, RygelTrackerCategory* parent, char** metadata, int metadata_length1);
RygelTrackerVideoItem* rygel_tracker_video_item_construct (GType object_type, const char* id, const char* path, RygelTrackerCategory* parent, char** metadata, int metadata_length1);
GType rygel_tracker_item_get_type (void);
GType rygel_tracker_video_item_get_type (void);
static RygelMediaItem* rygel_tracker_video_category_real_create_item (RygelTrackerCategory* base, const char* path, char** metadata, int metadata_length1);
static gpointer rygel_tracker_video_category_parent_class = NULL;



RygelTrackerVideoCategory* rygel_tracker_video_category_construct (GType object_type, const char* id, RygelMediaContainer* parent, const char* title) {
	RygelTrackerVideoCategory * self;
	g_return_val_if_fail (id != NULL, NULL);
	g_return_val_if_fail (parent != NULL, NULL);
	g_return_val_if_fail (title != NULL, NULL);
	self = (RygelTrackerVideoCategory*) rygel_tracker_category_construct (object_type, id, parent, title, "Videos", RYGEL_MEDIA_ITEM_VIDEO_CLASS);
	return self;
}


RygelTrackerVideoCategory* rygel_tracker_video_category_new (const char* id, RygelMediaContainer* parent, const char* title) {
	return rygel_tracker_video_category_construct (RYGEL_TYPE_TRACKER_VIDEO_CATEGORY, id, parent, title);
}


static char** rygel_tracker_video_category_real_get_metadata_keys (RygelTrackerCategory* base, int* result_length1) {
	RygelTrackerVideoCategory * self;
	gint _tmp0_;
	char** _tmp1_;
	self = (RygelTrackerVideoCategory*) base;
	_tmp1_ = NULL;
	return (_tmp1_ = rygel_tracker_video_item_get_metadata_keys (&_tmp0_), *result_length1 = _tmp0_, _tmp1_);
}


static RygelMediaItem* rygel_tracker_video_category_real_create_item (RygelTrackerCategory* base, const char* path, char** metadata, int metadata_length1) {
	RygelTrackerVideoCategory * self;
	char* _tmp1_;
	char* _tmp0_;
	RygelMediaItem* _tmp2_;
	self = (RygelTrackerVideoCategory*) base;
	g_return_val_if_fail (path != NULL, NULL);
	_tmp1_ = NULL;
	_tmp0_ = NULL;
	_tmp2_ = NULL;
	return (_tmp2_ = (RygelMediaItem*) rygel_tracker_video_item_new (_tmp1_ = g_strconcat (_tmp0_ = g_strconcat (((RygelMediaObject*) self)->id, ":", NULL), path, NULL), path, (RygelTrackerCategory*) self, metadata, metadata_length1), _tmp1_ = (g_free (_tmp1_), NULL), _tmp0_ = (g_free (_tmp0_), NULL), _tmp2_);
}


static void rygel_tracker_video_category_class_init (RygelTrackerVideoCategoryClass * klass) {
	rygel_tracker_video_category_parent_class = g_type_class_peek_parent (klass);
	RYGEL_TRACKER_CATEGORY_CLASS (klass)->get_metadata_keys = rygel_tracker_video_category_real_get_metadata_keys;
	RYGEL_TRACKER_CATEGORY_CLASS (klass)->create_item = rygel_tracker_video_category_real_create_item;
}


static void rygel_tracker_video_category_instance_init (RygelTrackerVideoCategory * self) {
}


GType rygel_tracker_video_category_get_type (void) {
	static GType rygel_tracker_video_category_type_id = 0;
	if (rygel_tracker_video_category_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (RygelTrackerVideoCategoryClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) rygel_tracker_video_category_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (RygelTrackerVideoCategory), 0, (GInstanceInitFunc) rygel_tracker_video_category_instance_init, NULL };
		rygel_tracker_video_category_type_id = g_type_register_static (RYGEL_TYPE_TRACKER_CATEGORY, "RygelTrackerVideoCategory", &g_define_type_info, 0);
	}
	return rygel_tracker_video_category_type_id;
}




