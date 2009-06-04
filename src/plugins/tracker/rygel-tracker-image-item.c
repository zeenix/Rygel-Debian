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
#include <gee/collection.h>


#define RYGEL_TYPE_TRACKER_ITEM (rygel_tracker_item_get_type ())
#define RYGEL_TRACKER_ITEM(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_TRACKER_ITEM, RygelTrackerItem))
#define RYGEL_TRACKER_ITEM_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_TRACKER_ITEM, RygelTrackerItemClass))
#define RYGEL_IS_TRACKER_ITEM(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_TRACKER_ITEM))
#define RYGEL_IS_TRACKER_ITEM_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_TRACKER_ITEM))
#define RYGEL_TRACKER_ITEM_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_TRACKER_ITEM, RygelTrackerItemClass))

typedef struct _RygelTrackerItem RygelTrackerItem;
typedef struct _RygelTrackerItemClass RygelTrackerItemClass;
typedef struct _RygelTrackerItemPrivate RygelTrackerItemPrivate;

#define RYGEL_TYPE_TRACKER_IMAGE_ITEM (rygel_tracker_image_item_get_type ())
#define RYGEL_TRACKER_IMAGE_ITEM(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_TRACKER_IMAGE_ITEM, RygelTrackerImageItem))
#define RYGEL_TRACKER_IMAGE_ITEM_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_TRACKER_IMAGE_ITEM, RygelTrackerImageItemClass))
#define RYGEL_IS_TRACKER_IMAGE_ITEM(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_TRACKER_IMAGE_ITEM))
#define RYGEL_IS_TRACKER_IMAGE_ITEM_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_TRACKER_IMAGE_ITEM))
#define RYGEL_TRACKER_IMAGE_ITEM_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_TRACKER_IMAGE_ITEM, RygelTrackerImageItemClass))

typedef struct _RygelTrackerImageItem RygelTrackerImageItem;
typedef struct _RygelTrackerImageItemClass RygelTrackerImageItemClass;
typedef struct _RygelTrackerImageItemPrivate RygelTrackerImageItemPrivate;

#define RYGEL_TRACKER_IMAGE_ITEM_TYPE_METADATA (rygel_tracker_image_item_metadata_get_type ())

#define RYGEL_TYPE_TRACKER_CATEGORY (rygel_tracker_category_get_type ())
#define RYGEL_TRACKER_CATEGORY(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_TRACKER_CATEGORY, RygelTrackerCategory))
#define RYGEL_TRACKER_CATEGORY_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_TRACKER_CATEGORY, RygelTrackerCategoryClass))
#define RYGEL_IS_TRACKER_CATEGORY(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_TRACKER_CATEGORY))
#define RYGEL_IS_TRACKER_CATEGORY_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_TRACKER_CATEGORY))
#define RYGEL_TRACKER_CATEGORY_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_TRACKER_CATEGORY, RygelTrackerCategoryClass))

typedef struct _RygelTrackerCategory RygelTrackerCategory;
typedef struct _RygelTrackerCategoryClass RygelTrackerCategoryClass;

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
 * Represents Tracker image item.
 */
struct _RygelTrackerImageItem {
	RygelTrackerItem parent_instance;
	RygelTrackerImageItemPrivate * priv;
};

struct _RygelTrackerImageItemClass {
	RygelTrackerItemClass parent_class;
};

typedef enum  {
	RYGEL_TRACKER_IMAGE_ITEM_METADATA_FILE_NAME,
	RYGEL_TRACKER_IMAGE_ITEM_METADATA_MIME,
	RYGEL_TRACKER_IMAGE_ITEM_METADATA_SIZE,
	RYGEL_TRACKER_IMAGE_ITEM_METADATA_TITLE,
	RYGEL_TRACKER_IMAGE_ITEM_METADATA_CREATOR,
	RYGEL_TRACKER_IMAGE_ITEM_METADATA_WIDTH,
	RYGEL_TRACKER_IMAGE_ITEM_METADATA_HEIGHT,
	RYGEL_TRACKER_IMAGE_ITEM_METADATA_ALBUM,
	RYGEL_TRACKER_IMAGE_ITEM_METADATA_IMAGE_DATE,
	RYGEL_TRACKER_IMAGE_ITEM_METADATA_DATE,
	RYGEL_TRACKER_IMAGE_ITEM_METADATA_LAST_KEY
} RygelTrackerImageItemMetadata;



GType rygel_tracker_item_get_type (void);
GType rygel_tracker_image_item_get_type (void);
enum  {
	RYGEL_TRACKER_IMAGE_ITEM_DUMMY_PROPERTY
};
static GType rygel_tracker_image_item_metadata_get_type (void);
GType rygel_tracker_category_get_type (void);
RygelTrackerItem* rygel_tracker_item_new (const char* id, const char* path, RygelTrackerCategory* parent, char** metadata, int metadata_length1);
RygelTrackerItem* rygel_tracker_item_construct (GType object_type, const char* id, const char* path, RygelTrackerCategory* parent, char** metadata, int metadata_length1);
RygelTrackerImageItem* rygel_tracker_image_item_new (const char* id, const char* path, RygelTrackerCategory* parent, char** metadata, int metadata_length1);
RygelTrackerImageItem* rygel_tracker_image_item_construct (GType object_type, const char* id, const char* path, RygelTrackerCategory* parent, char** metadata, int metadata_length1);
RygelTrackerImageItem* rygel_tracker_image_item_new (const char* id, const char* path, RygelTrackerCategory* parent, char** metadata, int metadata_length1);
char** rygel_tracker_image_item_get_metadata_keys (int* result_length1);
char* rygel_tracker_item_seconds_to_iso8601 (RygelTrackerItem* self, const char* seconds);
static void rygel_tracker_image_item_real_init_from_metadata (RygelTrackerItem* base, char** values, int values_length1);
static gpointer rygel_tracker_image_item_parent_class = NULL;
static void _vala_array_destroy (gpointer array, gint array_length, GDestroyNotify destroy_func);
static void _vala_array_free (gpointer array, gint array_length, GDestroyNotify destroy_func);
static int _vala_strcmp0 (const char * str1, const char * str2);




static GType rygel_tracker_image_item_metadata_get_type (void) {
	static GType rygel_tracker_image_item_metadata_type_id = 0;
	if (G_UNLIKELY (rygel_tracker_image_item_metadata_type_id == 0)) {
		static const GEnumValue values[] = {{RYGEL_TRACKER_IMAGE_ITEM_METADATA_FILE_NAME, "RYGEL_TRACKER_IMAGE_ITEM_METADATA_FILE_NAME", "file-name"}, {RYGEL_TRACKER_IMAGE_ITEM_METADATA_MIME, "RYGEL_TRACKER_IMAGE_ITEM_METADATA_MIME", "mime"}, {RYGEL_TRACKER_IMAGE_ITEM_METADATA_SIZE, "RYGEL_TRACKER_IMAGE_ITEM_METADATA_SIZE", "size"}, {RYGEL_TRACKER_IMAGE_ITEM_METADATA_TITLE, "RYGEL_TRACKER_IMAGE_ITEM_METADATA_TITLE", "title"}, {RYGEL_TRACKER_IMAGE_ITEM_METADATA_CREATOR, "RYGEL_TRACKER_IMAGE_ITEM_METADATA_CREATOR", "creator"}, {RYGEL_TRACKER_IMAGE_ITEM_METADATA_WIDTH, "RYGEL_TRACKER_IMAGE_ITEM_METADATA_WIDTH", "width"}, {RYGEL_TRACKER_IMAGE_ITEM_METADATA_HEIGHT, "RYGEL_TRACKER_IMAGE_ITEM_METADATA_HEIGHT", "height"}, {RYGEL_TRACKER_IMAGE_ITEM_METADATA_ALBUM, "RYGEL_TRACKER_IMAGE_ITEM_METADATA_ALBUM", "album"}, {RYGEL_TRACKER_IMAGE_ITEM_METADATA_IMAGE_DATE, "RYGEL_TRACKER_IMAGE_ITEM_METADATA_IMAGE_DATE", "image-date"}, {RYGEL_TRACKER_IMAGE_ITEM_METADATA_DATE, "RYGEL_TRACKER_IMAGE_ITEM_METADATA_DATE", "date"}, {RYGEL_TRACKER_IMAGE_ITEM_METADATA_LAST_KEY, "RYGEL_TRACKER_IMAGE_ITEM_METADATA_LAST_KEY", "last-key"}, {0, NULL, NULL}};
		rygel_tracker_image_item_metadata_type_id = g_enum_register_static ("RygelTrackerImageItemMetadata", values);
	}
	return rygel_tracker_image_item_metadata_type_id;
}


RygelTrackerImageItem* rygel_tracker_image_item_construct (GType object_type, const char* id, const char* path, RygelTrackerCategory* parent, char** metadata, int metadata_length1) {
	RygelTrackerImageItem * self;
	g_return_val_if_fail (id != NULL, NULL);
	g_return_val_if_fail (path != NULL, NULL);
	g_return_val_if_fail (parent != NULL, NULL);
	self = (RygelTrackerImageItem*) rygel_tracker_item_construct (object_type, id, path, parent, metadata, metadata_length1);
	return self;
}


RygelTrackerImageItem* rygel_tracker_image_item_new (const char* id, const char* path, RygelTrackerCategory* parent, char** metadata, int metadata_length1) {
	return rygel_tracker_image_item_construct (RYGEL_TYPE_TRACKER_IMAGE_ITEM, id, path, parent, metadata, metadata_length1);
}


char** rygel_tracker_image_item_get_metadata_keys (int* result_length1) {
	char** _tmp0_;
	gint keys_size;
	gint keys_length1;
	char** keys;
	char* _tmp1_;
	char* _tmp2_;
	char* _tmp3_;
	char* _tmp4_;
	char* _tmp5_;
	char* _tmp6_;
	char* _tmp7_;
	char* _tmp8_;
	char* _tmp9_;
	char* _tmp10_;
	char** _tmp11_;
	_tmp0_ = NULL;
	keys = (_tmp0_ = g_new0 (char*, RYGEL_TRACKER_IMAGE_ITEM_METADATA_LAST_KEY + 1), keys_length1 = RYGEL_TRACKER_IMAGE_ITEM_METADATA_LAST_KEY, keys_size = keys_length1, _tmp0_);
	_tmp1_ = NULL;
	keys[RYGEL_TRACKER_IMAGE_ITEM_METADATA_FILE_NAME] = (_tmp1_ = g_strdup ("File:Name"), keys[RYGEL_TRACKER_IMAGE_ITEM_METADATA_FILE_NAME] = (g_free (keys[RYGEL_TRACKER_IMAGE_ITEM_METADATA_FILE_NAME]), NULL), _tmp1_);
	_tmp2_ = NULL;
	keys[RYGEL_TRACKER_IMAGE_ITEM_METADATA_MIME] = (_tmp2_ = g_strdup ("File:Mime"), keys[RYGEL_TRACKER_IMAGE_ITEM_METADATA_MIME] = (g_free (keys[RYGEL_TRACKER_IMAGE_ITEM_METADATA_MIME]), NULL), _tmp2_);
	_tmp3_ = NULL;
	keys[RYGEL_TRACKER_IMAGE_ITEM_METADATA_SIZE] = (_tmp3_ = g_strdup ("File:Size"), keys[RYGEL_TRACKER_IMAGE_ITEM_METADATA_SIZE] = (g_free (keys[RYGEL_TRACKER_IMAGE_ITEM_METADATA_SIZE]), NULL), _tmp3_);
	_tmp4_ = NULL;
	keys[RYGEL_TRACKER_IMAGE_ITEM_METADATA_TITLE] = (_tmp4_ = g_strdup ("Video:Title"), keys[RYGEL_TRACKER_IMAGE_ITEM_METADATA_TITLE] = (g_free (keys[RYGEL_TRACKER_IMAGE_ITEM_METADATA_TITLE]), NULL), _tmp4_);
	_tmp5_ = NULL;
	keys[RYGEL_TRACKER_IMAGE_ITEM_METADATA_CREATOR] = (_tmp5_ = g_strdup ("Image:Creator"), keys[RYGEL_TRACKER_IMAGE_ITEM_METADATA_CREATOR] = (g_free (keys[RYGEL_TRACKER_IMAGE_ITEM_METADATA_CREATOR]), NULL), _tmp5_);
	_tmp6_ = NULL;
	keys[RYGEL_TRACKER_IMAGE_ITEM_METADATA_WIDTH] = (_tmp6_ = g_strdup ("Image:Width"), keys[RYGEL_TRACKER_IMAGE_ITEM_METADATA_WIDTH] = (g_free (keys[RYGEL_TRACKER_IMAGE_ITEM_METADATA_WIDTH]), NULL), _tmp6_);
	_tmp7_ = NULL;
	keys[RYGEL_TRACKER_IMAGE_ITEM_METADATA_HEIGHT] = (_tmp7_ = g_strdup ("Image:Height"), keys[RYGEL_TRACKER_IMAGE_ITEM_METADATA_HEIGHT] = (g_free (keys[RYGEL_TRACKER_IMAGE_ITEM_METADATA_HEIGHT]), NULL), _tmp7_);
	_tmp8_ = NULL;
	keys[RYGEL_TRACKER_IMAGE_ITEM_METADATA_ALBUM] = (_tmp8_ = g_strdup ("Image:Album"), keys[RYGEL_TRACKER_IMAGE_ITEM_METADATA_ALBUM] = (g_free (keys[RYGEL_TRACKER_IMAGE_ITEM_METADATA_ALBUM]), NULL), _tmp8_);
	_tmp9_ = NULL;
	keys[RYGEL_TRACKER_IMAGE_ITEM_METADATA_IMAGE_DATE] = (_tmp9_ = g_strdup ("Image:Date"), keys[RYGEL_TRACKER_IMAGE_ITEM_METADATA_IMAGE_DATE] = (g_free (keys[RYGEL_TRACKER_IMAGE_ITEM_METADATA_IMAGE_DATE]), NULL), _tmp9_);
	_tmp10_ = NULL;
	keys[RYGEL_TRACKER_IMAGE_ITEM_METADATA_DATE] = (_tmp10_ = g_strdup ("DC:Date"), keys[RYGEL_TRACKER_IMAGE_ITEM_METADATA_DATE] = (g_free (keys[RYGEL_TRACKER_IMAGE_ITEM_METADATA_DATE]), NULL), _tmp10_);
	_tmp11_ = NULL;
	return (_tmp11_ = keys, *result_length1 = keys_length1, _tmp11_);
}


static void rygel_tracker_image_item_real_init_from_metadata (RygelTrackerItem* base, char** values, int values_length1) {
	RygelTrackerImageItem * self;
	GError * _inner_error_;
	char* _tmp7_;
	const char* _tmp6_;
	char* _tmp9_;
	const char* _tmp8_;
	char* _tmp11_;
	const char* _tmp10_;
	char* _tmp12_;
	char* _tmp13_;
	self = (RygelTrackerImageItem*) base;
	_inner_error_ = NULL;
	if (_vala_strcmp0 (values[RYGEL_TRACKER_IMAGE_ITEM_METADATA_TITLE], "") != 0) {
		char* _tmp1_;
		const char* _tmp0_;
		_tmp1_ = NULL;
		_tmp0_ = NULL;
		((RygelMediaObject*) self)->title = (_tmp1_ = (_tmp0_ = values[RYGEL_TRACKER_IMAGE_ITEM_METADATA_TITLE], (_tmp0_ == NULL) ? NULL : g_strdup (_tmp0_)), ((RygelMediaObject*) self)->title = (g_free (((RygelMediaObject*) self)->title), NULL), _tmp1_);
	} else {
		char* _tmp3_;
		const char* _tmp2_;
		_tmp3_ = NULL;
		_tmp2_ = NULL;
		((RygelMediaObject*) self)->title = (_tmp3_ = (_tmp2_ = values[RYGEL_TRACKER_IMAGE_ITEM_METADATA_FILE_NAME], (_tmp2_ == NULL) ? NULL : g_strdup (_tmp2_)), ((RygelMediaObject*) self)->title = (g_free (((RygelMediaObject*) self)->title), NULL), _tmp3_);
	}
	if (_vala_strcmp0 (values[RYGEL_TRACKER_IMAGE_ITEM_METADATA_SIZE], "") != 0) {
		((RygelMediaItem*) self)->size = (glong) atoi (values[RYGEL_TRACKER_IMAGE_ITEM_METADATA_SIZE]);
	}
	if (_vala_strcmp0 (values[RYGEL_TRACKER_IMAGE_ITEM_METADATA_WIDTH], "") != 0) {
		((RygelMediaItem*) self)->width = atoi (values[RYGEL_TRACKER_IMAGE_ITEM_METADATA_WIDTH]);
	}
	if (_vala_strcmp0 (values[RYGEL_TRACKER_IMAGE_ITEM_METADATA_HEIGHT], "") != 0) {
		((RygelMediaItem*) self)->height = atoi (values[RYGEL_TRACKER_IMAGE_ITEM_METADATA_HEIGHT]);
	}
	if (_vala_strcmp0 (values[RYGEL_TRACKER_IMAGE_ITEM_METADATA_SIZE], "") != 0) {
		((RygelMediaItem*) self)->size = (glong) atoi (values[RYGEL_TRACKER_IMAGE_ITEM_METADATA_SIZE]);
	}
	if (_vala_strcmp0 (values[RYGEL_TRACKER_IMAGE_ITEM_METADATA_DATE], "") != 0) {
		char* _tmp4_;
		_tmp4_ = NULL;
		((RygelMediaItem*) self)->date = (_tmp4_ = rygel_tracker_item_seconds_to_iso8601 ((RygelTrackerItem*) self, values[RYGEL_TRACKER_IMAGE_ITEM_METADATA_DATE]), ((RygelMediaItem*) self)->date = (g_free (((RygelMediaItem*) self)->date), NULL), _tmp4_);
	} else {
		char* _tmp5_;
		_tmp5_ = NULL;
		((RygelMediaItem*) self)->date = (_tmp5_ = rygel_tracker_item_seconds_to_iso8601 ((RygelTrackerItem*) self, values[RYGEL_TRACKER_IMAGE_ITEM_METADATA_IMAGE_DATE]), ((RygelMediaItem*) self)->date = (g_free (((RygelMediaItem*) self)->date), NULL), _tmp5_);
	}
	_tmp7_ = NULL;
	_tmp6_ = NULL;
	((RygelMediaItem*) self)->mime_type = (_tmp7_ = (_tmp6_ = values[RYGEL_TRACKER_IMAGE_ITEM_METADATA_MIME], (_tmp6_ == NULL) ? NULL : g_strdup (_tmp6_)), ((RygelMediaItem*) self)->mime_type = (g_free (((RygelMediaItem*) self)->mime_type), NULL), _tmp7_);
	_tmp9_ = NULL;
	_tmp8_ = NULL;
	((RygelMediaItem*) self)->author = (_tmp9_ = (_tmp8_ = values[RYGEL_TRACKER_IMAGE_ITEM_METADATA_CREATOR], (_tmp8_ == NULL) ? NULL : g_strdup (_tmp8_)), ((RygelMediaItem*) self)->author = (g_free (((RygelMediaItem*) self)->author), NULL), _tmp9_);
	_tmp11_ = NULL;
	_tmp10_ = NULL;
	((RygelMediaItem*) self)->album = (_tmp11_ = (_tmp10_ = values[RYGEL_TRACKER_IMAGE_ITEM_METADATA_ALBUM], (_tmp10_ == NULL) ? NULL : g_strdup (_tmp10_)), ((RygelMediaItem*) self)->album = (g_free (((RygelMediaItem*) self)->album), NULL), _tmp11_);
	_tmp12_ = g_filename_to_uri (((RygelTrackerItem*) self)->path, NULL, &_inner_error_);
	if (_inner_error_ != NULL) {
		g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, _inner_error_->message);
		g_clear_error (&_inner_error_);
		return;
	}
	_tmp13_ = NULL;
	gee_collection_add ((GeeCollection*) ((RygelMediaItem*) self)->uris, _tmp13_ = _tmp12_);
	_tmp13_ = (g_free (_tmp13_), NULL);
}


static void rygel_tracker_image_item_class_init (RygelTrackerImageItemClass * klass) {
	rygel_tracker_image_item_parent_class = g_type_class_peek_parent (klass);
	RYGEL_TRACKER_ITEM_CLASS (klass)->init_from_metadata = rygel_tracker_image_item_real_init_from_metadata;
}


static void rygel_tracker_image_item_instance_init (RygelTrackerImageItem * self) {
}


GType rygel_tracker_image_item_get_type (void) {
	static GType rygel_tracker_image_item_type_id = 0;
	if (rygel_tracker_image_item_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (RygelTrackerImageItemClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) rygel_tracker_image_item_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (RygelTrackerImageItem), 0, (GInstanceInitFunc) rygel_tracker_image_item_instance_init, NULL };
		rygel_tracker_image_item_type_id = g_type_register_static (RYGEL_TYPE_TRACKER_ITEM, "RygelTrackerImageItem", &g_define_type_info, 0);
	}
	return rygel_tracker_image_item_type_id;
}


static void _vala_array_destroy (gpointer array, gint array_length, GDestroyNotify destroy_func) {
	if ((array != NULL) && (destroy_func != NULL)) {
		int i;
		for (i = 0; i < array_length; i = i + 1) {
			if (((gpointer*) array)[i] != NULL) {
				destroy_func (((gpointer*) array)[i]);
			}
		}
	}
}


static void _vala_array_free (gpointer array, gint array_length, GDestroyNotify destroy_func) {
	_vala_array_destroy (array, array_length, destroy_func);
	g_free (array);
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




