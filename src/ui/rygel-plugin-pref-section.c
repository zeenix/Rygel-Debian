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

struct _RygelPluginPrefSectionPrivate {
	GtkCheckButton* enabled_check;
	GtkEntry* title_entry;
};



GType rygel_preferences_section_get_type (void);
GType rygel_plugin_pref_section_get_type (void);
#define RYGEL_PLUGIN_PREF_SECTION_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), RYGEL_TYPE_PLUGIN_PREF_SECTION, RygelPluginPrefSectionPrivate))
enum  {
	RYGEL_PLUGIN_PREF_SECTION_DUMMY_PROPERTY
};
#define RYGEL_PLUGIN_PREF_SECTION_ENABLED_CHECK "-enabled-checkbutton"
#define RYGEL_PLUGIN_PREF_SECTION_TITLE_ENTRY "-title-entry"
RygelPreferencesSection* rygel_preferences_section_new (RygelConfiguration* config, const char* name);
RygelPreferencesSection* rygel_preferences_section_construct (GType object_type, RygelConfiguration* config, const char* name);
void rygel_plugin_pref_section_on_enabled_check_toggled (RygelPluginPrefSection* self, GtkCheckButton* enabled_check);
static void _rygel_plugin_pref_section_on_enabled_check_toggled_gtk_toggle_button_toggled (GtkCheckButton* _sender, gpointer self);
RygelPluginPrefSection* rygel_plugin_pref_section_new (GtkBuilder* builder, RygelConfiguration* config, const char* name);
RygelPluginPrefSection* rygel_plugin_pref_section_construct (GType object_type, GtkBuilder* builder, RygelConfiguration* config, const char* name);
RygelPluginPrefSection* rygel_plugin_pref_section_new (GtkBuilder* builder, RygelConfiguration* config, const char* name);
static void rygel_plugin_pref_section_real_save (RygelPreferencesSection* base);
static void rygel_plugin_pref_section_real_on_enabled_check_toggled (RygelPluginPrefSection* self, GtkCheckButton* enabled_check);
static gpointer rygel_plugin_pref_section_parent_class = NULL;
static void rygel_plugin_pref_section_finalize (GObject* obj);



static char* string_replace (const char* self, const char* old, const char* replacement) {
	GError * _inner_error_;
	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (old != NULL, NULL);
	g_return_val_if_fail (replacement != NULL, NULL);
	_inner_error_ = NULL;
	{
		char* _tmp0_;
		GRegex* _tmp1_;
		GRegex* regex;
		char* _tmp2_;
		char* _tmp3_;
		_tmp0_ = NULL;
		_tmp1_ = NULL;
		regex = (_tmp1_ = g_regex_new (_tmp0_ = g_regex_escape_string (old, -1), 0, 0, &_inner_error_), _tmp0_ = (g_free (_tmp0_), NULL), _tmp1_);
		if (_inner_error_ != NULL) {
			if (_inner_error_->domain == G_REGEX_ERROR) {
				goto __catch1_g_regex_error;
			}
			goto __finally1;
		}
		_tmp2_ = g_regex_replace_literal (regex, self, (glong) (-1), 0, replacement, 0, &_inner_error_);
		if (_inner_error_ != NULL) {
			(regex == NULL) ? NULL : (regex = (g_regex_unref (regex), NULL));
			if (_inner_error_->domain == G_REGEX_ERROR) {
				goto __catch1_g_regex_error;
			}
			goto __finally1;
		}
		_tmp3_ = NULL;
		return (_tmp3_ = _tmp2_, (regex == NULL) ? NULL : (regex = (g_regex_unref (regex), NULL)), _tmp3_);
	}
	goto __finally1;
	__catch1_g_regex_error:
	{
		GError * e;
		e = _inner_error_;
		_inner_error_ = NULL;
		{
			g_assert_not_reached ();
			(e == NULL) ? NULL : (e = (g_error_free (e), NULL));
		}
	}
	__finally1:
	if (_inner_error_ != NULL) {
		g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, _inner_error_->message);
		g_clear_error (&_inner_error_);
		return NULL;
	}
}


static void _rygel_plugin_pref_section_on_enabled_check_toggled_gtk_toggle_button_toggled (GtkCheckButton* _sender, gpointer self) {
	rygel_plugin_pref_section_on_enabled_check_toggled (self, _sender);
}


RygelPluginPrefSection* rygel_plugin_pref_section_construct (GType object_type, GtkBuilder* builder, RygelConfiguration* config, const char* name) {
	RygelPluginPrefSection * self;
	GtkCheckButton* _tmp3_;
	GtkCheckButton* _tmp2_;
	char* _tmp1_;
	char* _tmp0_;
	GtkEntry* _tmp7_;
	GtkEntry* _tmp6_;
	char* _tmp5_;
	char* _tmp4_;
	char* _tmp8_;
	char* _tmp9_;
	char* title;
	char* _tmp10_;
	char* _tmp11_;
	g_return_val_if_fail (builder != NULL, NULL);
	g_return_val_if_fail (config != NULL, NULL);
	g_return_val_if_fail (name != NULL, NULL);
	self = (RygelPluginPrefSection*) rygel_preferences_section_construct (object_type, config, name);
	_tmp3_ = NULL;
	_tmp2_ = NULL;
	_tmp1_ = NULL;
	_tmp0_ = NULL;
	self->priv->enabled_check = (_tmp3_ = (_tmp2_ = GTK_CHECK_BUTTON (gtk_builder_get_object (builder, _tmp1_ = g_strconcat (_tmp0_ = g_utf8_strdown (name, -1), RYGEL_PLUGIN_PREF_SECTION_ENABLED_CHECK, NULL))), (_tmp2_ == NULL) ? NULL : g_object_ref (_tmp2_)), (self->priv->enabled_check == NULL) ? NULL : (self->priv->enabled_check = (g_object_unref (self->priv->enabled_check), NULL)), _tmp3_);
	_tmp1_ = (g_free (_tmp1_), NULL);
	_tmp0_ = (g_free (_tmp0_), NULL);
	g_assert (self->priv->enabled_check != NULL);
	_tmp7_ = NULL;
	_tmp6_ = NULL;
	_tmp5_ = NULL;
	_tmp4_ = NULL;
	self->priv->title_entry = (_tmp7_ = (_tmp6_ = GTK_ENTRY (gtk_builder_get_object (builder, _tmp5_ = g_strconcat (_tmp4_ = g_utf8_strdown (name, -1), RYGEL_PLUGIN_PREF_SECTION_TITLE_ENTRY, NULL))), (_tmp6_ == NULL) ? NULL : g_object_ref (_tmp6_)), (self->priv->title_entry == NULL) ? NULL : (self->priv->title_entry = (g_object_unref (self->priv->title_entry), NULL)), _tmp7_);
	_tmp5_ = (g_free (_tmp5_), NULL);
	_tmp4_ = (g_free (_tmp4_), NULL);
	g_assert (self->priv->title_entry != NULL);
	gtk_toggle_button_set_active ((GtkToggleButton*) self->priv->enabled_check, rygel_configuration_get_enabled (config, name));
	_tmp8_ = NULL;
	_tmp9_ = NULL;
	title = (_tmp9_ = string_replace (_tmp8_ = rygel_configuration_get_title (config, name, name), "@REALNAME@", "%n"), _tmp8_ = (g_free (_tmp8_), NULL), _tmp9_);
	_tmp10_ = NULL;
	title = (_tmp10_ = string_replace (title, "@USERNAME@", "%u"), title = (g_free (title), NULL), _tmp10_);
	_tmp11_ = NULL;
	title = (_tmp11_ = string_replace (title, "@HOSTNAME@", "%h"), title = (g_free (title), NULL), _tmp11_);
	gtk_entry_set_text (self->priv->title_entry, title);
	g_signal_connect_object ((GtkToggleButton*) self->priv->enabled_check, "toggled", (GCallback) _rygel_plugin_pref_section_on_enabled_check_toggled_gtk_toggle_button_toggled, self, 0);
	title = (g_free (title), NULL);
	return self;
}


RygelPluginPrefSection* rygel_plugin_pref_section_new (GtkBuilder* builder, RygelConfiguration* config, const char* name) {
	return rygel_plugin_pref_section_construct (RYGEL_TYPE_PLUGIN_PREF_SECTION, builder, config, name);
}


static void rygel_plugin_pref_section_real_save (RygelPreferencesSection* base) {
	RygelPluginPrefSection * self;
	char* title;
	char* _tmp0_;
	char* _tmp1_;
	self = (RygelPluginPrefSection*) base;
	rygel_configuration_set_bool (((RygelPreferencesSection*) self)->config, ((RygelPreferencesSection*) self)->name, RYGEL_CONFIGURATION_ENABLED_KEY, gtk_toggle_button_get_active ((GtkToggleButton*) self->priv->enabled_check));
	title = string_replace (gtk_entry_get_text (self->priv->title_entry), "%n", "@REALNAME@");
	_tmp0_ = NULL;
	title = (_tmp0_ = string_replace (title, "%u", "@USERNAME@"), title = (g_free (title), NULL), _tmp0_);
	_tmp1_ = NULL;
	title = (_tmp1_ = string_replace (title, "%h", "@HOSTNAME@"), title = (g_free (title), NULL), _tmp1_);
	rygel_configuration_set_string (((RygelPreferencesSection*) self)->config, ((RygelPreferencesSection*) self)->name, RYGEL_CONFIGURATION_TITLE_KEY, title);
	title = (g_free (title), NULL);
}


static void rygel_plugin_pref_section_real_on_enabled_check_toggled (RygelPluginPrefSection* self, GtkCheckButton* enabled_check) {
	g_return_if_fail (self != NULL);
	g_return_if_fail (enabled_check != NULL);
	g_object_set ((GtkWidget*) self->priv->title_entry, "sensitive", gtk_toggle_button_get_active ((GtkToggleButton*) enabled_check), NULL);
}


void rygel_plugin_pref_section_on_enabled_check_toggled (RygelPluginPrefSection* self, GtkCheckButton* enabled_check) {
	RYGEL_PLUGIN_PREF_SECTION_GET_CLASS (self)->on_enabled_check_toggled (self, enabled_check);
}


static void rygel_plugin_pref_section_class_init (RygelPluginPrefSectionClass * klass) {
	rygel_plugin_pref_section_parent_class = g_type_class_peek_parent (klass);
	g_type_class_add_private (klass, sizeof (RygelPluginPrefSectionPrivate));
	RYGEL_PREFERENCES_SECTION_CLASS (klass)->save = rygel_plugin_pref_section_real_save;
	RYGEL_PLUGIN_PREF_SECTION_CLASS (klass)->on_enabled_check_toggled = rygel_plugin_pref_section_real_on_enabled_check_toggled;
	G_OBJECT_CLASS (klass)->finalize = rygel_plugin_pref_section_finalize;
}


static void rygel_plugin_pref_section_instance_init (RygelPluginPrefSection * self) {
	self->priv = RYGEL_PLUGIN_PREF_SECTION_GET_PRIVATE (self);
}


static void rygel_plugin_pref_section_finalize (GObject* obj) {
	RygelPluginPrefSection * self;
	self = RYGEL_PLUGIN_PREF_SECTION (obj);
	(self->priv->enabled_check == NULL) ? NULL : (self->priv->enabled_check = (g_object_unref (self->priv->enabled_check), NULL));
	(self->priv->title_entry == NULL) ? NULL : (self->priv->title_entry = (g_object_unref (self->priv->title_entry), NULL));
	G_OBJECT_CLASS (rygel_plugin_pref_section_parent_class)->finalize (obj);
}


GType rygel_plugin_pref_section_get_type (void) {
	static GType rygel_plugin_pref_section_type_id = 0;
	if (rygel_plugin_pref_section_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (RygelPluginPrefSectionClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) rygel_plugin_pref_section_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (RygelPluginPrefSection), 0, (GInstanceInitFunc) rygel_plugin_pref_section_instance_init, NULL };
		rygel_plugin_pref_section_type_id = g_type_register_static (RYGEL_TYPE_PREFERENCES_SECTION, "RygelPluginPrefSection", &g_define_type_info, 0);
	}
	return rygel_plugin_pref_section_type_id;
}




