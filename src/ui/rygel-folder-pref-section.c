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
#include <gtk/gtk.h>
#include <gee/arraylist.h>
#include <gee/iterable.h>
#include <gee/iterator.h>
#include <gee/collection.h>


#define RYGEL_TYPE_PREFERENCES_SECTION (rygel_preferences_section_get_type ())
#define RYGEL_PREFERENCES_SECTION(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_PREFERENCES_SECTION, RygelPreferencesSection))
#define RYGEL_PREFERENCES_SECTION_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_PREFERENCES_SECTION, RygelPreferencesSectionClass))
#define RYGEL_IS_PREFERENCES_SECTION(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_PREFERENCES_SECTION))
#define RYGEL_IS_PREFERENCES_SECTION_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_PREFERENCES_SECTION))
#define RYGEL_PREFERENCES_SECTION_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_PREFERENCES_SECTION, RygelPreferencesSectionClass))

typedef struct _RygelPreferencesSection RygelPreferencesSection;
typedef struct _RygelPreferencesSectionClass RygelPreferencesSectionClass;
typedef struct _RygelPreferencesSectionPrivate RygelPreferencesSectionPrivate;

#define RYGEL_TYPE_PLUGIN_PREF_SECTION (rygel_plugin_pref_section_get_type ())
#define RYGEL_PLUGIN_PREF_SECTION(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_PLUGIN_PREF_SECTION, RygelPluginPrefSection))
#define RYGEL_PLUGIN_PREF_SECTION_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_PLUGIN_PREF_SECTION, RygelPluginPrefSectionClass))
#define RYGEL_IS_PLUGIN_PREF_SECTION(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_PLUGIN_PREF_SECTION))
#define RYGEL_IS_PLUGIN_PREF_SECTION_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_PLUGIN_PREF_SECTION))
#define RYGEL_PLUGIN_PREF_SECTION_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_PLUGIN_PREF_SECTION, RygelPluginPrefSectionClass))

typedef struct _RygelPluginPrefSection RygelPluginPrefSection;
typedef struct _RygelPluginPrefSectionClass RygelPluginPrefSectionClass;
typedef struct _RygelPluginPrefSectionPrivate RygelPluginPrefSectionPrivate;

#define RYGEL_TYPE_FOLDER_PREF_SECTION (rygel_folder_pref_section_get_type ())
#define RYGEL_FOLDER_PREF_SECTION(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_FOLDER_PREF_SECTION, RygelFolderPrefSection))
#define RYGEL_FOLDER_PREF_SECTION_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_FOLDER_PREF_SECTION, RygelFolderPrefSectionClass))
#define RYGEL_IS_FOLDER_PREF_SECTION(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_FOLDER_PREF_SECTION))
#define RYGEL_IS_FOLDER_PREF_SECTION_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_FOLDER_PREF_SECTION))
#define RYGEL_FOLDER_PREF_SECTION_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_FOLDER_PREF_SECTION, RygelFolderPrefSectionClass))

typedef struct _RygelFolderPrefSection RygelFolderPrefSection;
typedef struct _RygelFolderPrefSectionClass RygelFolderPrefSectionClass;
typedef struct _RygelFolderPrefSectionPrivate RygelFolderPrefSectionPrivate;

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

struct _RygelPluginPrefSection {
	RygelPreferencesSection parent_instance;
	RygelPluginPrefSectionPrivate * priv;
};

struct _RygelPluginPrefSectionClass {
	RygelPreferencesSectionClass parent_class;
	void (*on_enabled_check_toggled) (RygelPluginPrefSection* self, GtkCheckButton* enabled_check);
};

struct _RygelFolderPrefSection {
	RygelPluginPrefSection parent_instance;
	RygelFolderPrefSectionPrivate * priv;
};

struct _RygelFolderPrefSectionClass {
	RygelPluginPrefSectionClass parent_class;
};

struct _RygelFolderPrefSectionPrivate {
	GtkTextView* text_view;
	GtkTextBuffer* text_buffer;
};



GType rygel_preferences_section_get_type (void);
GType rygel_plugin_pref_section_get_type (void);
GType rygel_folder_pref_section_get_type (void);
#define RYGEL_FOLDER_PREF_SECTION_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), RYGEL_TYPE_FOLDER_PREF_SECTION, RygelFolderPrefSectionPrivate))
enum  {
	RYGEL_FOLDER_PREF_SECTION_DUMMY_PROPERTY
};
#define RYGEL_FOLDER_PREF_SECTION_NAME "Folder"
#define RYGEL_FOLDER_PREF_SECTION_FOLDERS_KEY "folders"
#define RYGEL_FOLDER_PREF_SECTION_FOLDERS_TEXTVIEW RYGEL_FOLDER_PREF_SECTION_FOLDERS_KEY "-textview"
#define RYGEL_FOLDER_PREF_SECTION_FOLDERS_TEXTBUFFER RYGEL_FOLDER_PREF_SECTION_FOLDERS_KEY "-textbuffer"
RygelPluginPrefSection* rygel_plugin_pref_section_new (GtkBuilder* builder, RygelConfiguration* config, const char* name);
RygelPluginPrefSection* rygel_plugin_pref_section_construct (GType object_type, GtkBuilder* builder, RygelConfiguration* config, const char* name);
RygelFolderPrefSection* rygel_folder_pref_section_new (GtkBuilder* builder, RygelConfiguration* config);
RygelFolderPrefSection* rygel_folder_pref_section_construct (GType object_type, GtkBuilder* builder, RygelConfiguration* config);
RygelFolderPrefSection* rygel_folder_pref_section_new (GtkBuilder* builder, RygelConfiguration* config);
static void rygel_folder_pref_section_real_save (RygelPreferencesSection* base);
void rygel_plugin_pref_section_on_enabled_check_toggled (RygelPluginPrefSection* self, GtkCheckButton* enabled_check);
static void rygel_folder_pref_section_real_on_enabled_check_toggled (RygelPluginPrefSection* base, GtkCheckButton* enabled_check);
static gpointer rygel_folder_pref_section_parent_class = NULL;
static void rygel_folder_pref_section_finalize (GObject* obj);
static void _vala_array_destroy (gpointer array, gint array_length, GDestroyNotify destroy_func);
static void _vala_array_free (gpointer array, gint array_length, GDestroyNotify destroy_func);
static gint _vala_array_length (gpointer array);



RygelFolderPrefSection* rygel_folder_pref_section_construct (GType object_type, GtkBuilder* builder, RygelConfiguration* config) {
	RygelFolderPrefSection * self;
	GtkTextView* _tmp1_;
	GtkTextView* _tmp0_;
	GtkTextBuffer* _tmp3_;
	GtkTextBuffer* _tmp2_;
	GeeArrayList* folders;
	char* text;
	g_return_val_if_fail (builder != NULL, NULL);
	g_return_val_if_fail (config != NULL, NULL);
	self = (RygelFolderPrefSection*) rygel_plugin_pref_section_construct (object_type, builder, config, RYGEL_FOLDER_PREF_SECTION_NAME);
	_tmp1_ = NULL;
	_tmp0_ = NULL;
	self->priv->text_view = (_tmp1_ = (_tmp0_ = GTK_TEXT_VIEW (gtk_builder_get_object (builder, RYGEL_FOLDER_PREF_SECTION_FOLDERS_TEXTVIEW)), (_tmp0_ == NULL) ? NULL : g_object_ref (_tmp0_)), (self->priv->text_view == NULL) ? NULL : (self->priv->text_view = (g_object_unref (self->priv->text_view), NULL)), _tmp1_);
	g_assert (self->priv->text_view != NULL);
	_tmp3_ = NULL;
	_tmp2_ = NULL;
	self->priv->text_buffer = (_tmp3_ = (_tmp2_ = GTK_TEXT_BUFFER (gtk_builder_get_object (builder, RYGEL_FOLDER_PREF_SECTION_FOLDERS_TEXTBUFFER)), (_tmp2_ == NULL) ? NULL : g_object_ref (_tmp2_)), (self->priv->text_buffer == NULL) ? NULL : (self->priv->text_buffer = (g_object_unref (self->priv->text_buffer), NULL)), _tmp3_);
	g_assert (self->priv->text_buffer != NULL);
	folders = rygel_configuration_get_string_list (config, ((RygelPreferencesSection*) self)->name, RYGEL_FOLDER_PREF_SECTION_FOLDERS_KEY);
	text = g_strdup ("");
	{
		GeeIterator* _folder_it;
		_folder_it = gee_iterable_iterator ((GeeIterable*) folders);
		while (gee_iterator_next (_folder_it)) {
			char* folder;
			char* _tmp5_;
			char* _tmp4_;
			folder = (char*) gee_iterator_get (_folder_it);
			_tmp5_ = NULL;
			_tmp4_ = NULL;
			text = (_tmp5_ = g_strconcat (text, _tmp4_ = g_strconcat (folder, "\n", NULL), NULL), text = (g_free (text), NULL), _tmp5_);
			_tmp4_ = (g_free (_tmp4_), NULL);
			folder = (g_free (folder), NULL);
		}
		(_folder_it == NULL) ? NULL : (_folder_it = (g_object_unref (_folder_it), NULL));
	}
	gtk_text_buffer_set_text (self->priv->text_buffer, text, -1);
	(folders == NULL) ? NULL : (folders = (g_object_unref (folders), NULL));
	text = (g_free (text), NULL);
	return self;
}


RygelFolderPrefSection* rygel_folder_pref_section_new (GtkBuilder* builder, RygelConfiguration* config) {
	return rygel_folder_pref_section_construct (RYGEL_TYPE_FOLDER_PREF_SECTION, builder, config);
}


static void rygel_folder_pref_section_real_save (RygelPreferencesSection* base) {
	RygelFolderPrefSection * self;
	GtkTextIter start = {0};
	GtkTextIter end = {0};
	const char* _tmp0_;
	char* text;
	char** _tmp2_;
	gint folders_size;
	gint folders_length1;
	char** _tmp1_;
	char** folders;
	GeeArrayList* folder_list;
	self = (RygelFolderPrefSection*) base;
	gtk_text_buffer_get_start_iter (self->priv->text_buffer, &start);
	gtk_text_buffer_get_end_iter (self->priv->text_buffer, &end);
	_tmp0_ = NULL;
	text = (_tmp0_ = gtk_text_buffer_get_text (self->priv->text_buffer, &start, &end, FALSE), (_tmp0_ == NULL) ? NULL : g_strdup (_tmp0_));
	_tmp2_ = NULL;
	_tmp1_ = NULL;
	folders = (_tmp2_ = _tmp1_ = g_strsplit (text, "\n", -1), folders_length1 = _vala_array_length (_tmp1_), folders_size = folders_length1, _tmp2_);
	folder_list = gee_array_list_new (G_TYPE_STRING, (GBoxedCopyFunc) g_strdup, g_free, g_direct_equal);
	{
		char** folder_collection;
		int folder_collection_length1;
		int folder_it;
		folder_collection = folders;
		folder_collection_length1 = folders_length1;
		for (folder_it = 0; folder_it < folders_length1; folder_it = folder_it + 1) {
			const char* _tmp3_;
			char* folder;
			_tmp3_ = NULL;
			folder = (_tmp3_ = folder_collection[folder_it], (_tmp3_ == NULL) ? NULL : g_strdup (_tmp3_));
			{
				gee_collection_add ((GeeCollection*) folder_list, folder);
				folder = (g_free (folder), NULL);
			}
		}
	}
	rygel_configuration_set_string_list (((RygelPreferencesSection*) self)->config, ((RygelPreferencesSection*) self)->name, RYGEL_FOLDER_PREF_SECTION_FOLDERS_KEY, folder_list);
	text = (g_free (text), NULL);
	folders = (_vala_array_free (folders, folders_length1, (GDestroyNotify) g_free), NULL);
	(folder_list == NULL) ? NULL : (folder_list = (g_object_unref (folder_list), NULL));
}


static void rygel_folder_pref_section_real_on_enabled_check_toggled (RygelPluginPrefSection* base, GtkCheckButton* enabled_check) {
	RygelFolderPrefSection * self;
	self = (RygelFolderPrefSection*) base;
	g_return_if_fail (enabled_check != NULL);
	RYGEL_PLUGIN_PREF_SECTION_CLASS (rygel_folder_pref_section_parent_class)->on_enabled_check_toggled (RYGEL_PLUGIN_PREF_SECTION (self), enabled_check);
	g_object_set ((GtkWidget*) self->priv->text_view, "sensitive", gtk_toggle_button_get_active ((GtkToggleButton*) enabled_check), NULL);
}


static void rygel_folder_pref_section_class_init (RygelFolderPrefSectionClass * klass) {
	rygel_folder_pref_section_parent_class = g_type_class_peek_parent (klass);
	g_type_class_add_private (klass, sizeof (RygelFolderPrefSectionPrivate));
	RYGEL_PREFERENCES_SECTION_CLASS (klass)->save = rygel_folder_pref_section_real_save;
	RYGEL_PLUGIN_PREF_SECTION_CLASS (klass)->on_enabled_check_toggled = rygel_folder_pref_section_real_on_enabled_check_toggled;
	G_OBJECT_CLASS (klass)->finalize = rygel_folder_pref_section_finalize;
}


static void rygel_folder_pref_section_instance_init (RygelFolderPrefSection * self) {
	self->priv = RYGEL_FOLDER_PREF_SECTION_GET_PRIVATE (self);
}


static void rygel_folder_pref_section_finalize (GObject* obj) {
	RygelFolderPrefSection * self;
	self = RYGEL_FOLDER_PREF_SECTION (obj);
	(self->priv->text_view == NULL) ? NULL : (self->priv->text_view = (g_object_unref (self->priv->text_view), NULL));
	(self->priv->text_buffer == NULL) ? NULL : (self->priv->text_buffer = (g_object_unref (self->priv->text_buffer), NULL));
	G_OBJECT_CLASS (rygel_folder_pref_section_parent_class)->finalize (obj);
}


GType rygel_folder_pref_section_get_type (void) {
	static GType rygel_folder_pref_section_type_id = 0;
	if (rygel_folder_pref_section_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (RygelFolderPrefSectionClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) rygel_folder_pref_section_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (RygelFolderPrefSection), 0, (GInstanceInitFunc) rygel_folder_pref_section_instance_init, NULL };
		rygel_folder_pref_section_type_id = g_type_register_static (RYGEL_TYPE_PLUGIN_PREF_SECTION, "RygelFolderPrefSection", &g_define_type_info, 0);
	}
	return rygel_folder_pref_section_type_id;
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


static gint _vala_array_length (gpointer array) {
	int length;
	length = 0;
	if (array) {
		while (((gpointer*) array)[length]) {
			length++;
		}
	}
	return length;
}




