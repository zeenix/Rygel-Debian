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
#include <stdlib.h>
#include <string.h>


#define RYGEL_TYPE_TEST_ITEM (rygel_test_item_get_type ())
#define RYGEL_TEST_ITEM(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_TEST_ITEM, RygelTestItem))
#define RYGEL_TEST_ITEM_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_TEST_ITEM, RygelTestItemClass))
#define RYGEL_IS_TEST_ITEM(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_TEST_ITEM))
#define RYGEL_IS_TEST_ITEM_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_TEST_ITEM))
#define RYGEL_TEST_ITEM_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_TEST_ITEM, RygelTestItemClass))

typedef struct _RygelTestItem RygelTestItem;
typedef struct _RygelTestItemClass RygelTestItemClass;
typedef struct _RygelTestItemPrivate RygelTestItemPrivate;

/**
 * Represents Test item.
 */
struct _RygelTestItem {
	RygelMediaItem parent_instance;
	RygelTestItemPrivate * priv;
};

struct _RygelTestItemClass {
	RygelMediaItemClass parent_class;
};



GType rygel_test_item_get_type (void);
enum  {
	RYGEL_TEST_ITEM_DUMMY_PROPERTY
};
#define RYGEL_TEST_ITEM_TEST_AUTHOR "Zeeshan Ali (Khattak)"
RygelTestItem* rygel_test_item_new (const char* id, RygelMediaContainer* parent, const char* title, const char* mime, const char* upnp_class);
RygelTestItem* rygel_test_item_construct (GType object_type, const char* id, RygelMediaContainer* parent, const char* title, const char* mime, const char* upnp_class);
RygelTestItem* rygel_test_item_new (const char* id, RygelMediaContainer* parent, const char* title, const char* mime, const char* upnp_class);
static gpointer rygel_test_item_parent_class = NULL;



RygelTestItem* rygel_test_item_construct (GType object_type, const char* id, RygelMediaContainer* parent, const char* title, const char* mime, const char* upnp_class) {
	RygelTestItem * self;
	char* _tmp1_;
	const char* _tmp0_;
	char* _tmp2_;
	g_return_val_if_fail (id != NULL, NULL);
	g_return_val_if_fail (parent != NULL, NULL);
	g_return_val_if_fail (title != NULL, NULL);
	g_return_val_if_fail (mime != NULL, NULL);
	g_return_val_if_fail (upnp_class != NULL, NULL);
	self = (RygelTestItem*) rygel_media_item_construct (object_type, id, parent, title, upnp_class);
	_tmp1_ = NULL;
	_tmp0_ = NULL;
	((RygelMediaItem*) self)->mime_type = (_tmp1_ = (_tmp0_ = mime, (_tmp0_ == NULL) ? NULL : g_strdup (_tmp0_)), ((RygelMediaItem*) self)->mime_type = (g_free (((RygelMediaItem*) self)->mime_type), NULL), _tmp1_);
	_tmp2_ = NULL;
	((RygelMediaItem*) self)->author = (_tmp2_ = g_strdup (RYGEL_TEST_ITEM_TEST_AUTHOR), ((RygelMediaItem*) self)->author = (g_free (((RygelMediaItem*) self)->author), NULL), _tmp2_);
	return self;
}


RygelTestItem* rygel_test_item_new (const char* id, RygelMediaContainer* parent, const char* title, const char* mime, const char* upnp_class) {
	return rygel_test_item_construct (RYGEL_TYPE_TEST_ITEM, id, parent, title, mime, upnp_class);
}


static void rygel_test_item_class_init (RygelTestItemClass * klass) {
	rygel_test_item_parent_class = g_type_class_peek_parent (klass);
}


static void rygel_test_item_instance_init (RygelTestItem * self) {
}


GType rygel_test_item_get_type (void) {
	static GType rygel_test_item_type_id = 0;
	if (rygel_test_item_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (RygelTestItemClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) rygel_test_item_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (RygelTestItem), 0, (GInstanceInitFunc) rygel_test_item_instance_init, NULL };
		rygel_test_item_type_id = g_type_register_static (RYGEL_TYPE_MEDIA_ITEM, "RygelTestItem", &g_define_type_info, G_TYPE_FLAG_ABSTRACT);
	}
	return rygel_test_item_type_id;
}




