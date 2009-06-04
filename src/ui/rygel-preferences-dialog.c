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
#include <gtk/gtk.h>
#include <gee/arraylist.h>
#include <rygel.h>
#include <gee/collection.h>
#include <stdlib.h>
#include <string.h>
#include <gdk/gdk.h>
#include <gee/iterable.h>
#include <gee/iterator.h>


#define RYGEL_TYPE_PREFERENCES_DIALOG (rygel_preferences_dialog_get_type ())
#define RYGEL_PREFERENCES_DIALOG(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_PREFERENCES_DIALOG, RygelPreferencesDialog))
#define RYGEL_PREFERENCES_DIALOG_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_PREFERENCES_DIALOG, RygelPreferencesDialogClass))
#define RYGEL_IS_PREFERENCES_DIALOG(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_PREFERENCES_DIALOG))
#define RYGEL_IS_PREFERENCES_DIALOG_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_PREFERENCES_DIALOG))
#define RYGEL_PREFERENCES_DIALOG_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_PREFERENCES_DIALOG, RygelPreferencesDialogClass))

typedef struct _RygelPreferencesDialog RygelPreferencesDialog;
typedef struct _RygelPreferencesDialogClass RygelPreferencesDialogClass;
typedef struct _RygelPreferencesDialogPrivate RygelPreferencesDialogPrivate;

#define RYGEL_TYPE_PREFERENCES_SECTION (rygel_preferences_section_get_type ())
#define RYGEL_PREFERENCES_SECTION(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_PREFERENCES_SECTION, RygelPreferencesSection))
#define RYGEL_PREFERENCES_SECTION_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_PREFERENCES_SECTION, RygelPreferencesSectionClass))
#define RYGEL_IS_PREFERENCES_SECTION(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_PREFERENCES_SECTION))
#define RYGEL_IS_PREFERENCES_SECTION_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_PREFERENCES_SECTION))
#define RYGEL_PREFERENCES_SECTION_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_PREFERENCES_SECTION, RygelPreferencesSectionClass))

typedef struct _RygelPreferencesSection RygelPreferencesSection;
typedef struct _RygelPreferencesSectionClass RygelPreferencesSectionClass;

#define RYGEL_TYPE_GENERAL_PREF_SECTION (rygel_general_pref_section_get_type ())
#define RYGEL_GENERAL_PREF_SECTION(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_GENERAL_PREF_SECTION, RygelGeneralPrefSection))
#define RYGEL_GENERAL_PREF_SECTION_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_GENERAL_PREF_SECTION, RygelGeneralPrefSectionClass))
#define RYGEL_IS_GENERAL_PREF_SECTION(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_GENERAL_PREF_SECTION))
#define RYGEL_IS_GENERAL_PREF_SECTION_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_GENERAL_PREF_SECTION))
#define RYGEL_GENERAL_PREF_SECTION_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_GENERAL_PREF_SECTION, RygelGeneralPrefSectionClass))

typedef struct _RygelGeneralPrefSection RygelGeneralPrefSection;
typedef struct _RygelGeneralPrefSectionClass RygelGeneralPrefSectionClass;

#define RYGEL_TYPE_PLUGIN_PREF_SECTION (rygel_plugin_pref_section_get_type ())
#define RYGEL_PLUGIN_PREF_SECTION(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_PLUGIN_PREF_SECTION, RygelPluginPrefSection))
#define RYGEL_PLUGIN_PREF_SECTION_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_PLUGIN_PREF_SECTION, RygelPluginPrefSectionClass))
#define RYGEL_IS_PLUGIN_PREF_SECTION(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_PLUGIN_PREF_SECTION))
#define RYGEL_IS_PLUGIN_PREF_SECTION_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_PLUGIN_PREF_SECTION))
#define RYGEL_PLUGIN_PREF_SECTION_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_PLUGIN_PREF_SECTION, RygelPluginPrefSectionClass))

typedef struct _RygelPluginPrefSection RygelPluginPrefSection;
typedef struct _RygelPluginPrefSectionClass RygelPluginPrefSectionClass;

#define RYGEL_TYPE_FOLDER_PREF_SECTION (rygel_folder_pref_section_get_type ())
#define RYGEL_FOLDER_PREF_SECTION(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_FOLDER_PREF_SECTION, RygelFolderPrefSection))
#define RYGEL_FOLDER_PREF_SECTION_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_FOLDER_PREF_SECTION, RygelFolderPrefSectionClass))
#define RYGEL_IS_FOLDER_PREF_SECTION(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_FOLDER_PREF_SECTION))
#define RYGEL_IS_FOLDER_PREF_SECTION_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_FOLDER_PREF_SECTION))
#define RYGEL_FOLDER_PREF_SECTION_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_FOLDER_PREF_SECTION, RygelFolderPrefSectionClass))

typedef struct _RygelFolderPrefSection RygelFolderPrefSection;
typedef struct _RygelFolderPrefSectionClass RygelFolderPrefSectionClass;

struct _RygelPreferencesDialog {
	GObject parent_instance;
	RygelPreferencesDialogPrivate * priv;
};

struct _RygelPreferencesDialogClass {
	GObjectClass parent_class;
};

struct _RygelPreferencesDialogPrivate {
	GtkBuilder* builder;
	GtkDialog* dialog;
	GeeArrayList* sections;
};



GType rygel_preferences_dialog_get_type (void);
GType rygel_preferences_section_get_type (void);
#define RYGEL_PREFERENCES_DIALOG_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), RYGEL_TYPE_PREFERENCES_DIALOG, RygelPreferencesDialogPrivate))
enum  {
	RYGEL_PREFERENCES_DIALOG_DUMMY_PROPERTY
};
#define RYGEL_PREFERENCES_DIALOG_UI_FILE DATA_DIR "/rygel-preferences.ui"
#define RYGEL_PREFERENCES_DIALOG_DIALOG "preferences-dialog"
RygelGeneralPrefSection* rygel_general_pref_section_new (GtkBuilder* builder, RygelConfiguration* config, GError** error);
RygelGeneralPrefSection* rygel_general_pref_section_construct (GType object_type, GtkBuilder* builder, RygelConfiguration* config, GError** error);
GType rygel_general_pref_section_get_type (void);
RygelPluginPrefSection* rygel_plugin_pref_section_new (GtkBuilder* builder, RygelConfiguration* config, const char* name);
RygelPluginPrefSection* rygel_plugin_pref_section_construct (GType object_type, GtkBuilder* builder, RygelConfiguration* config, const char* name);
GType rygel_plugin_pref_section_get_type (void);
RygelFolderPrefSection* rygel_folder_pref_section_new (GtkBuilder* builder, RygelConfiguration* config);
RygelFolderPrefSection* rygel_folder_pref_section_construct (GType object_type, GtkBuilder* builder, RygelConfiguration* config);
GType rygel_folder_pref_section_get_type (void);
static void rygel_preferences_dialog_on_response (RygelPreferencesDialog* self, GtkDialog* dialog, gint response_id);
static void _rygel_preferences_dialog_on_response_gtk_dialog_response (GtkDialog* _sender, gint response_id, gpointer self);
static gboolean _lambda0_ (GtkDialog* dialog, GdkEvent* event, RygelPreferencesDialog* self);
static gboolean __lambda0__gtk_widget_delete_event (GtkDialog* _sender, GdkEvent* event, gpointer self);
RygelPreferencesDialog* rygel_preferences_dialog_new (GError** error);
RygelPreferencesDialog* rygel_preferences_dialog_construct (GType object_type, GError** error);
RygelPreferencesDialog* rygel_preferences_dialog_new (GError** error);
static void rygel_preferences_dialog_apply_settings (RygelPreferencesDialog* self);
void rygel_preferences_section_save (RygelPreferencesSection* self);
void rygel_preferences_dialog_run (RygelPreferencesDialog* self);
gint rygel_preferences_dialog_main (char** args, int args_length1);
static gpointer rygel_preferences_dialog_parent_class = NULL;
static void rygel_preferences_dialog_finalize (GObject* obj);



static void _rygel_preferences_dialog_on_response_gtk_dialog_response (GtkDialog* _sender, gint response_id, gpointer self) {
	rygel_preferences_dialog_on_response (self, _sender, response_id);
}


static gboolean _lambda0_ (GtkDialog* dialog, GdkEvent* event, RygelPreferencesDialog* self) {
	g_return_val_if_fail (dialog != NULL, FALSE);
	g_return_val_if_fail (event != NULL, FALSE);
	gtk_main_quit ();
	return FALSE;
}


static gboolean __lambda0__gtk_widget_delete_event (GtkDialog* _sender, GdkEvent* event, gpointer self) {
	return _lambda0_ (_sender, event, self);
}


RygelPreferencesDialog* rygel_preferences_dialog_construct (GType object_type, GError** error) {
	GError * _inner_error_;
	RygelPreferencesDialog * self;
	RygelConfiguration* config;
	GtkBuilder* _tmp0_;
	GtkDialog* _tmp2_;
	GtkDialog* _tmp1_;
	GeeArrayList* _tmp3_;
	RygelGeneralPrefSection* _tmp4_;
	RygelPluginPrefSection* _tmp5_;
	RygelPluginPrefSection* _tmp6_;
	RygelFolderPrefSection* _tmp7_;
	_inner_error_ = NULL;
	self = g_object_newv (object_type, 0, NULL);
	config = rygel_configuration_get_default ();
	_tmp0_ = NULL;
	self->priv->builder = (_tmp0_ = gtk_builder_new (), (self->priv->builder == NULL) ? NULL : (self->priv->builder = (g_object_unref (self->priv->builder), NULL)), _tmp0_);
	gtk_builder_add_from_file (self->priv->builder, RYGEL_PREFERENCES_DIALOG_UI_FILE, &_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		(config == NULL) ? NULL : (config = (g_object_unref (config), NULL));
		return;
	}
	_tmp2_ = NULL;
	_tmp1_ = NULL;
	self->priv->dialog = (_tmp2_ = (_tmp1_ = GTK_DIALOG (gtk_builder_get_object (self->priv->builder, RYGEL_PREFERENCES_DIALOG_DIALOG)), (_tmp1_ == NULL) ? NULL : g_object_ref (_tmp1_)), (self->priv->dialog == NULL) ? NULL : (self->priv->dialog = (g_object_unref (self->priv->dialog), NULL)), _tmp2_);
	g_assert (self->priv->dialog != NULL);
	_tmp3_ = NULL;
	self->priv->sections = (_tmp3_ = gee_array_list_new (RYGEL_TYPE_PREFERENCES_SECTION, (GBoxedCopyFunc) g_object_ref, g_object_unref, g_direct_equal), (self->priv->sections == NULL) ? NULL : (self->priv->sections = (g_object_unref (self->priv->sections), NULL)), _tmp3_);
	_tmp4_ = NULL;
	gee_collection_add ((GeeCollection*) self->priv->sections, (RygelPreferencesSection*) (_tmp4_ = rygel_general_pref_section_new (self->priv->builder, config, &_inner_error_)));
	(_tmp4_ == NULL) ? NULL : (_tmp4_ = (g_object_unref (_tmp4_), NULL));
	_tmp5_ = NULL;
	gee_collection_add ((GeeCollection*) self->priv->sections, (RygelPreferencesSection*) (_tmp5_ = rygel_plugin_pref_section_new (self->priv->builder, config, "Tracker")));
	(_tmp5_ == NULL) ? NULL : (_tmp5_ = (g_object_unref (_tmp5_), NULL));
	_tmp6_ = NULL;
	gee_collection_add ((GeeCollection*) self->priv->sections, (RygelPreferencesSection*) (_tmp6_ = rygel_plugin_pref_section_new (self->priv->builder, config, "DVB")));
	(_tmp6_ == NULL) ? NULL : (_tmp6_ = (g_object_unref (_tmp6_), NULL));
	_tmp7_ = NULL;
	gee_collection_add ((GeeCollection*) self->priv->sections, (RygelPreferencesSection*) (_tmp7_ = rygel_folder_pref_section_new (self->priv->builder, config)));
	(_tmp7_ == NULL) ? NULL : (_tmp7_ = (g_object_unref (_tmp7_), NULL));
	g_signal_connect_object (self->priv->dialog, "response", (GCallback) _rygel_preferences_dialog_on_response_gtk_dialog_response, self, 0);
	g_signal_connect ((GtkWidget*) self->priv->dialog, "delete-event", (GCallback) __lambda0__gtk_widget_delete_event, self);
	gtk_widget_show_all ((GtkWidget*) self->priv->dialog);
	(config == NULL) ? NULL : (config = (g_object_unref (config), NULL));
	return self;
}


RygelPreferencesDialog* rygel_preferences_dialog_new (GError** error) {
	return rygel_preferences_dialog_construct (RYGEL_TYPE_PREFERENCES_DIALOG, error);
}


static void rygel_preferences_dialog_on_response (RygelPreferencesDialog* self, GtkDialog* dialog, gint response_id) {
	g_return_if_fail (self != NULL);
	g_return_if_fail (dialog != NULL);
	switch (response_id) {
		case GTK_RESPONSE_CANCEL:
		{
			gtk_main_quit ();
			break;
		}
		case GTK_RESPONSE_OK:
		{
			rygel_preferences_dialog_apply_settings (self);
			gtk_main_quit ();
			break;
		}
		case GTK_RESPONSE_APPLY:
		{
			rygel_preferences_dialog_apply_settings (self);
			break;
		}
	}
}


static void rygel_preferences_dialog_apply_settings (RygelPreferencesDialog* self) {
	g_return_if_fail (self != NULL);
	{
		GeeIterator* _section_it;
		_section_it = gee_iterable_iterator ((GeeIterable*) self->priv->sections);
		while (gee_iterator_next (_section_it)) {
			RygelPreferencesSection* section;
			section = (RygelPreferencesSection*) gee_iterator_get (_section_it);
			rygel_preferences_section_save (section);
			(section == NULL) ? NULL : (section = (g_object_unref (section), NULL));
		}
		(_section_it == NULL) ? NULL : (_section_it = (g_object_unref (_section_it), NULL));
	}
}


void rygel_preferences_dialog_run (RygelPreferencesDialog* self) {
	g_return_if_fail (self != NULL);
	gtk_main ();
}


gint rygel_preferences_dialog_main (char** args, int args_length1) {
	GError * _inner_error_;
	_inner_error_ = NULL;
	gtk_init (&args_length1, &args);
	{
		RygelPreferencesDialog* dialog;
		dialog = rygel_preferences_dialog_new (&_inner_error_);
		if (_inner_error_ != NULL) {
			goto __catch0_g_error;
			goto __finally0;
		}
		rygel_preferences_dialog_run (dialog);
		(dialog == NULL) ? NULL : (dialog = (g_object_unref (dialog), NULL));
	}
	goto __finally0;
	__catch0_g_error:
	{
		GError * err;
		err = _inner_error_;
		_inner_error_ = NULL;
		{
			g_error ("rygel-preferences-dialog.vala:99: Failed to create preferences dialog: %s\n", err->message);
			(err == NULL) ? NULL : (err = (g_error_free (err), NULL));
		}
	}
	__finally0:
	if (_inner_error_ != NULL) {
		g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, _inner_error_->message);
		g_clear_error (&_inner_error_);
		return 0;
	}
	return 0;
}


int main (int argc, char ** argv) {
	g_type_init ();
	return rygel_preferences_dialog_main (argv, argc);
}


static void rygel_preferences_dialog_class_init (RygelPreferencesDialogClass * klass) {
	rygel_preferences_dialog_parent_class = g_type_class_peek_parent (klass);
	g_type_class_add_private (klass, sizeof (RygelPreferencesDialogPrivate));
	G_OBJECT_CLASS (klass)->finalize = rygel_preferences_dialog_finalize;
}


static void rygel_preferences_dialog_instance_init (RygelPreferencesDialog * self) {
	self->priv = RYGEL_PREFERENCES_DIALOG_GET_PRIVATE (self);
}


static void rygel_preferences_dialog_finalize (GObject* obj) {
	RygelPreferencesDialog * self;
	self = RYGEL_PREFERENCES_DIALOG (obj);
	(self->priv->builder == NULL) ? NULL : (self->priv->builder = (g_object_unref (self->priv->builder), NULL));
	(self->priv->dialog == NULL) ? NULL : (self->priv->dialog = (g_object_unref (self->priv->dialog), NULL));
	(self->priv->sections == NULL) ? NULL : (self->priv->sections = (g_object_unref (self->priv->sections), NULL));
	G_OBJECT_CLASS (rygel_preferences_dialog_parent_class)->finalize (obj);
}


GType rygel_preferences_dialog_get_type (void) {
	static GType rygel_preferences_dialog_type_id = 0;
	if (rygel_preferences_dialog_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (RygelPreferencesDialogClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) rygel_preferences_dialog_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (RygelPreferencesDialog), 0, (GInstanceInitFunc) rygel_preferences_dialog_instance_init, NULL };
		rygel_preferences_dialog_type_id = g_type_register_static (G_TYPE_OBJECT, "RygelPreferencesDialog", &g_define_type_info, 0);
	}
	return rygel_preferences_dialog_type_id;
}




