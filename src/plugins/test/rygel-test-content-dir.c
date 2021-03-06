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
#include <libgupnp/gupnp.h>
#include <stdlib.h>
#include <string.h>


#define RYGEL_TYPE_TEST_CONTENT_DIR (rygel_test_content_dir_get_type ())
#define RYGEL_TEST_CONTENT_DIR(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_TEST_CONTENT_DIR, RygelTestContentDir))
#define RYGEL_TEST_CONTENT_DIR_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_TEST_CONTENT_DIR, RygelTestContentDirClass))
#define RYGEL_IS_TEST_CONTENT_DIR(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_TEST_CONTENT_DIR))
#define RYGEL_IS_TEST_CONTENT_DIR_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_TEST_CONTENT_DIR))
#define RYGEL_TEST_CONTENT_DIR_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_TEST_CONTENT_DIR, RygelTestContentDirClass))

typedef struct _RygelTestContentDir RygelTestContentDir;
typedef struct _RygelTestContentDirClass RygelTestContentDirClass;
typedef struct _RygelTestContentDirPrivate RygelTestContentDirPrivate;

#define RYGEL_TYPE_TEST_ROOT_CONTAINER (rygel_test_root_container_get_type ())
#define RYGEL_TEST_ROOT_CONTAINER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_TEST_ROOT_CONTAINER, RygelTestRootContainer))
#define RYGEL_TEST_ROOT_CONTAINER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_TEST_ROOT_CONTAINER, RygelTestRootContainerClass))
#define RYGEL_IS_TEST_ROOT_CONTAINER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_TEST_ROOT_CONTAINER))
#define RYGEL_IS_TEST_ROOT_CONTAINER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_TEST_ROOT_CONTAINER))
#define RYGEL_TEST_ROOT_CONTAINER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_TEST_ROOT_CONTAINER, RygelTestRootContainerClass))

typedef struct _RygelTestRootContainer RygelTestRootContainer;
typedef struct _RygelTestRootContainerClass RygelTestRootContainerClass;

/**
 * Implementation of ContentDirectory service, meant for testing purposes only.
 */
struct _RygelTestContentDir {
	RygelContentDirectory parent_instance;
	RygelTestContentDirPrivate * priv;
};

struct _RygelTestContentDirClass {
	RygelContentDirectoryClass parent_class;
};



GType rygel_test_content_dir_get_type (void);
enum  {
	RYGEL_TEST_CONTENT_DIR_DUMMY_PROPERTY
};
RygelTestRootContainer* rygel_test_root_container_new (const char* title);
RygelTestRootContainer* rygel_test_root_container_construct (GType object_type, const char* title);
GType rygel_test_root_container_get_type (void);
static RygelMediaContainer* rygel_test_content_dir_real_create_root_container (RygelContentDirectory* base);
RygelTestContentDir* rygel_test_content_dir_new (void);
RygelTestContentDir* rygel_test_content_dir_construct (GType object_type);
RygelTestContentDir* rygel_test_content_dir_new (void);
static gpointer rygel_test_content_dir_parent_class = NULL;



/* Pubic methods */
static RygelMediaContainer* rygel_test_content_dir_real_create_root_container (RygelContentDirectory* base) {
	RygelTestContentDir * self;
	GUPnPRootDevice* _tmp1_;
	GUPnPRootDevice* _tmp0_;
	char* _tmp2_;
	char* friendly_name;
	RygelMediaContainer* _tmp3_;
	self = (RygelTestContentDir*) base;
	_tmp1_ = NULL;
	_tmp0_ = NULL;
	_tmp2_ = NULL;
	friendly_name = (_tmp2_ = gupnp_device_info_get_friendly_name ((GUPnPDeviceInfo*) (_tmp1_ = (g_object_get ((GUPnPService*) self, "root-device", &_tmp0_, NULL), _tmp0_))), (_tmp1_ == NULL) ? NULL : (_tmp1_ = (g_object_unref (_tmp1_), NULL)), _tmp2_);
	_tmp3_ = NULL;
	return (_tmp3_ = (RygelMediaContainer*) rygel_test_root_container_new (friendly_name), friendly_name = (g_free (friendly_name), NULL), _tmp3_);
}


/**
 * Implementation of ContentDirectory service, meant for testing purposes only.
 */
RygelTestContentDir* rygel_test_content_dir_construct (GType object_type) {
	RygelTestContentDir * self;
	self = (RygelTestContentDir*) rygel_content_directory_construct (object_type);
	return self;
}


RygelTestContentDir* rygel_test_content_dir_new (void) {
	return rygel_test_content_dir_construct (RYGEL_TYPE_TEST_CONTENT_DIR);
}


static void rygel_test_content_dir_class_init (RygelTestContentDirClass * klass) {
	rygel_test_content_dir_parent_class = g_type_class_peek_parent (klass);
	RYGEL_CONTENT_DIRECTORY_CLASS (klass)->create_root_container = rygel_test_content_dir_real_create_root_container;
}


static void rygel_test_content_dir_instance_init (RygelTestContentDir * self) {
}


GType rygel_test_content_dir_get_type (void) {
	static GType rygel_test_content_dir_type_id = 0;
	if (rygel_test_content_dir_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (RygelTestContentDirClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) rygel_test_content_dir_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (RygelTestContentDir), 0, (GInstanceInitFunc) rygel_test_content_dir_instance_init, NULL };
		rygel_test_content_dir_type_id = g_type_register_static (RYGEL_TYPE_CONTENT_DIRECTORY, "RygelTestContentDir", &g_define_type_info, 0);
	}
	return rygel_test_content_dir_type_id;
}




