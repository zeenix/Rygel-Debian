/*
 * Copyright (C) 2009 Nokia Corporation, all rights reserved.
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


#define RYGEL_TYPE_PREFERENCES_SECTION (rygel_preferences_section_get_type ())
#define RYGEL_PREFERENCES_SECTION(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_PREFERENCES_SECTION, RygelPreferencesSection))
#define RYGEL_PREFERENCES_SECTION_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_PREFERENCES_SECTION, RygelPreferencesSectionClass))
#define RYGEL_IS_PREFERENCES_SECTION(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_PREFERENCES_SECTION))
#define RYGEL_IS_PREFERENCES_SECTION_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_PREFERENCES_SECTION))
#define RYGEL_PREFERENCES_SECTION_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_PREFERENCES_SECTION, RygelPreferencesSectionClass))

typedef struct _RygelPreferencesSection RygelPreferencesSection;
typedef struct _RygelPreferencesSectionClass RygelPreferencesSectionClass;
typedef struct _RygelPreferencesSectionPrivate RygelPreferencesSectionPrivate;

struct _RygelPreferencesSection {
	GObject parent_instance;
	RygelPreferencesSectionPrivate * priv;
	RygelConfiguration* config;
	char* name;
};

struct _RygelPreferencesSectionClass {
	GObjectClass parent_class;
	void (*save) (RygelPreferencesSection* self);
};



GType rygel_preferences_section_get_type (void);
enum  {
	RYGEL_PREFERENCES_SECTION_DUMMY_PROPERTY
};
RygelPreferencesSection* rygel_preferences_section_new (RygelConfiguration* config, const char* name);
RygelPreferencesSection* rygel_preferences_section_construct (GType object_type, RygelConfiguration* config, const char* name);
RygelPreferencesSection* rygel_preferences_section_new (RygelConfiguration* config, const char* name);
void rygel_preferences_section_save (RygelPreferencesSection* self);
static void rygel_preferences_section_real_save (RygelPreferencesSection* self);
static gpointer rygel_preferences_section_parent_class = NULL;
static void rygel_preferences_section_finalize (GObject* obj);



RygelPreferencesSection* rygel_preferences_section_construct (GType object_type, RygelConfiguration* config, const char* name) {
	RygelPreferencesSection * self;
	char* _tmp1_;
	const char* _tmp0_;
	RygelConfiguration* _tmp3_;
	RygelConfiguration* _tmp2_;
	g_return_val_if_fail (config != NULL, NULL);
	g_return_val_if_fail (name != NULL, NULL);
	self = g_object_newv (object_type, 0, NULL);
	_tmp1_ = NULL;
	_tmp0_ = NULL;
	self->name = (_tmp1_ = (_tmp0_ = name, (_tmp0_ == NULL) ? NULL : g_strdup (_tmp0_)), self->name = (g_free (self->name), NULL), _tmp1_);
	_tmp3_ = NULL;
	_tmp2_ = NULL;
	self->config = (_tmp3_ = (_tmp2_ = config, (_tmp2_ == NULL) ? NULL : g_object_ref (_tmp2_)), (self->config == NULL) ? NULL : (self->config = (g_object_unref (self->config), NULL)), _tmp3_);
	return self;
}


RygelPreferencesSection* rygel_preferences_section_new (RygelConfiguration* config, const char* name) {
	return rygel_preferences_section_construct (RYGEL_TYPE_PREFERENCES_SECTION, config, name);
}


static void rygel_preferences_section_real_save (RygelPreferencesSection* self) {
	g_return_if_fail (self != NULL);
	g_critical ("Type `%s' does not implement abstract method `rygel_preferences_section_save'", g_type_name (G_TYPE_FROM_INSTANCE (self)));
	return;
}


void rygel_preferences_section_save (RygelPreferencesSection* self) {
	RYGEL_PREFERENCES_SECTION_GET_CLASS (self)->save (self);
}


static void rygel_preferences_section_class_init (RygelPreferencesSectionClass * klass) {
	rygel_preferences_section_parent_class = g_type_class_peek_parent (klass);
	RYGEL_PREFERENCES_SECTION_CLASS (klass)->save = rygel_preferences_section_real_save;
	G_OBJECT_CLASS (klass)->finalize = rygel_preferences_section_finalize;
}


static void rygel_preferences_section_instance_init (RygelPreferencesSection * self) {
}


static void rygel_preferences_section_finalize (GObject* obj) {
	RygelPreferencesSection * self;
	self = RYGEL_PREFERENCES_SECTION (obj);
	(self->config == NULL) ? NULL : (self->config = (g_object_unref (self->config), NULL));
	self->name = (g_free (self->name), NULL);
	G_OBJECT_CLASS (rygel_preferences_section_parent_class)->finalize (obj);
}


GType rygel_preferences_section_get_type (void) {
	static GType rygel_preferences_section_type_id = 0;
	if (rygel_preferences_section_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (RygelPreferencesSectionClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) rygel_preferences_section_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (RygelPreferencesSection), 0, (GInstanceInitFunc) rygel_preferences_section_instance_init, NULL };
		rygel_preferences_section_type_id = g_type_register_static (G_TYPE_OBJECT, "RygelPreferencesSection", &g_define_type_info, G_TYPE_FLAG_ABSTRACT);
	}
	return rygel_preferences_section_type_id;
}




