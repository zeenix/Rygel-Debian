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

#define RYGEL_TYPE_GENERAL_PREF_SECTION (rygel_general_pref_section_get_type ())
#define RYGEL_GENERAL_PREF_SECTION(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_GENERAL_PREF_SECTION, RygelGeneralPrefSection))
#define RYGEL_GENERAL_PREF_SECTION_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_GENERAL_PREF_SECTION, RygelGeneralPrefSectionClass))
#define RYGEL_IS_GENERAL_PREF_SECTION(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_GENERAL_PREF_SECTION))
#define RYGEL_IS_GENERAL_PREF_SECTION_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_GENERAL_PREF_SECTION))
#define RYGEL_GENERAL_PREF_SECTION_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_GENERAL_PREF_SECTION, RygelGeneralPrefSectionClass))

typedef struct _RygelGeneralPrefSection RygelGeneralPrefSection;
typedef struct _RygelGeneralPrefSectionClass RygelGeneralPrefSectionClass;
typedef struct _RygelGeneralPrefSectionPrivate RygelGeneralPrefSectionPrivate;

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

struct _RygelGeneralPrefSection {
	RygelPreferencesSection parent_instance;
	RygelGeneralPrefSectionPrivate * priv;
};

struct _RygelGeneralPrefSectionClass {
	RygelPreferencesSectionClass parent_class;
};

struct _RygelGeneralPrefSectionPrivate {
	GtkEntry* ip_entry;
	GtkSpinButton* port_spin;
	GtkCheckButton* trans_check;
	GtkCheckButton* mp3_check;
	GtkCheckButton* mp2ts_check;
	GtkCheckButton* lpcm_check;
};



GType rygel_preferences_section_get_type (void);
GType rygel_general_pref_section_get_type (void);
#define RYGEL_GENERAL_PREF_SECTION_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), RYGEL_TYPE_GENERAL_PREF_SECTION, RygelGeneralPrefSectionPrivate))
enum  {
	RYGEL_GENERAL_PREF_SECTION_DUMMY_PROPERTY
};
#define RYGEL_GENERAL_PREF_SECTION_IP_ENTRY "ip-entry"
#define RYGEL_GENERAL_PREF_SECTION_PORT_SPINBUTTON "port-spinbutton"
#define RYGEL_GENERAL_PREF_SECTION_TRANS_CHECKBUTTON "transcoding-checkbutton"
#define RYGEL_GENERAL_PREF_SECTION_MP3_CHECKBUTTON "mp3-checkbutton"
#define RYGEL_GENERAL_PREF_SECTION_MP2TS_CHECKBUTTON "mp2ts-checkbutton"
#define RYGEL_GENERAL_PREF_SECTION_LPCM_CHECKBUTTON "lpcm-checkbutton"
RygelPreferencesSection* rygel_preferences_section_new (RygelConfiguration* config, const char* name);
RygelPreferencesSection* rygel_preferences_section_construct (GType object_type, RygelConfiguration* config, const char* name);
static void rygel_general_pref_section_on_trans_check_toggled (RygelGeneralPrefSection* self, GtkCheckButton* trans_check);
static void _rygel_general_pref_section_on_trans_check_toggled_gtk_toggle_button_toggled (GtkCheckButton* _sender, gpointer self);
RygelGeneralPrefSection* rygel_general_pref_section_new (GtkBuilder* builder, RygelConfiguration* config, GError** error);
RygelGeneralPrefSection* rygel_general_pref_section_construct (GType object_type, GtkBuilder* builder, RygelConfiguration* config, GError** error);
RygelGeneralPrefSection* rygel_general_pref_section_new (GtkBuilder* builder, RygelConfiguration* config, GError** error);
static void rygel_general_pref_section_real_save (RygelPreferencesSection* base);
static gpointer rygel_general_pref_section_parent_class = NULL;
static void rygel_general_pref_section_finalize (GObject* obj);



static void _rygel_general_pref_section_on_trans_check_toggled_gtk_toggle_button_toggled (GtkCheckButton* _sender, gpointer self) {
	rygel_general_pref_section_on_trans_check_toggled (self, _sender);
}


RygelGeneralPrefSection* rygel_general_pref_section_construct (GType object_type, GtkBuilder* builder, RygelConfiguration* config, GError** error) {
	RygelGeneralPrefSection * self;
	GtkEntry* _tmp1_;
	GtkEntry* _tmp0_;
	GtkSpinButton* _tmp3_;
	GtkSpinButton* _tmp2_;
	GtkCheckButton* _tmp5_;
	GtkCheckButton* _tmp4_;
	GtkCheckButton* _tmp7_;
	GtkCheckButton* _tmp6_;
	GtkCheckButton* _tmp9_;
	GtkCheckButton* _tmp8_;
	GtkCheckButton* _tmp11_;
	GtkCheckButton* _tmp10_;
	g_return_val_if_fail (builder != NULL, NULL);
	g_return_val_if_fail (config != NULL, NULL);
	self = (RygelGeneralPrefSection*) rygel_preferences_section_construct (object_type, config, "general");
	_tmp1_ = NULL;
	_tmp0_ = NULL;
	self->priv->ip_entry = (_tmp1_ = (_tmp0_ = GTK_ENTRY (gtk_builder_get_object (builder, RYGEL_GENERAL_PREF_SECTION_IP_ENTRY)), (_tmp0_ == NULL) ? NULL : g_object_ref (_tmp0_)), (self->priv->ip_entry == NULL) ? NULL : (self->priv->ip_entry = (g_object_unref (self->priv->ip_entry), NULL)), _tmp1_);
	g_assert (self->priv->ip_entry != NULL);
	_tmp3_ = NULL;
	_tmp2_ = NULL;
	self->priv->port_spin = (_tmp3_ = (_tmp2_ = GTK_SPIN_BUTTON (gtk_builder_get_object (builder, RYGEL_GENERAL_PREF_SECTION_PORT_SPINBUTTON)), (_tmp2_ == NULL) ? NULL : g_object_ref (_tmp2_)), (self->priv->port_spin == NULL) ? NULL : (self->priv->port_spin = (g_object_unref (self->priv->port_spin), NULL)), _tmp3_);
	g_assert (self->priv->port_spin != NULL);
	_tmp5_ = NULL;
	_tmp4_ = NULL;
	self->priv->trans_check = (_tmp5_ = (_tmp4_ = GTK_CHECK_BUTTON (gtk_builder_get_object (builder, RYGEL_GENERAL_PREF_SECTION_TRANS_CHECKBUTTON)), (_tmp4_ == NULL) ? NULL : g_object_ref (_tmp4_)), (self->priv->trans_check == NULL) ? NULL : (self->priv->trans_check = (g_object_unref (self->priv->trans_check), NULL)), _tmp5_);
	g_assert (self->priv->trans_check != NULL);
	_tmp7_ = NULL;
	_tmp6_ = NULL;
	self->priv->mp3_check = (_tmp7_ = (_tmp6_ = GTK_CHECK_BUTTON (gtk_builder_get_object (builder, RYGEL_GENERAL_PREF_SECTION_MP3_CHECKBUTTON)), (_tmp6_ == NULL) ? NULL : g_object_ref (_tmp6_)), (self->priv->mp3_check == NULL) ? NULL : (self->priv->mp3_check = (g_object_unref (self->priv->mp3_check), NULL)), _tmp7_);
	g_assert (self->priv->mp3_check != NULL);
	_tmp9_ = NULL;
	_tmp8_ = NULL;
	self->priv->mp2ts_check = (_tmp9_ = (_tmp8_ = GTK_CHECK_BUTTON (gtk_builder_get_object (builder, RYGEL_GENERAL_PREF_SECTION_MP2TS_CHECKBUTTON)), (_tmp8_ == NULL) ? NULL : g_object_ref (_tmp8_)), (self->priv->mp2ts_check == NULL) ? NULL : (self->priv->mp2ts_check = (g_object_unref (self->priv->mp2ts_check), NULL)), _tmp9_);
	g_assert (self->priv->mp2ts_check != NULL);
	_tmp11_ = NULL;
	_tmp10_ = NULL;
	self->priv->lpcm_check = (_tmp11_ = (_tmp10_ = GTK_CHECK_BUTTON (gtk_builder_get_object (builder, RYGEL_GENERAL_PREF_SECTION_LPCM_CHECKBUTTON)), (_tmp10_ == NULL) ? NULL : g_object_ref (_tmp10_)), (self->priv->lpcm_check == NULL) ? NULL : (self->priv->lpcm_check = (g_object_unref (self->priv->lpcm_check), NULL)), _tmp11_);
	g_assert (self->priv->lpcm_check != NULL);
	if (rygel_configuration_get_host_ip (config) != NULL) {
		gtk_entry_set_text (self->priv->ip_entry, rygel_configuration_get_host_ip (config));
	}
	gtk_spin_button_set_value (self->priv->port_spin, (double) rygel_configuration_get_port (config));
	gtk_toggle_button_set_active ((GtkToggleButton*) self->priv->trans_check, rygel_configuration_get_transcoding (((RygelPreferencesSection*) self)->config));
	gtk_toggle_button_set_active ((GtkToggleButton*) self->priv->mp3_check, rygel_configuration_get_mp3_transcoder (((RygelPreferencesSection*) self)->config));
	gtk_toggle_button_set_active ((GtkToggleButton*) self->priv->mp2ts_check, rygel_configuration_get_mp2ts_transcoder (((RygelPreferencesSection*) self)->config));
	gtk_toggle_button_set_active ((GtkToggleButton*) self->priv->lpcm_check, rygel_configuration_get_lpcm_transcoder (((RygelPreferencesSection*) self)->config));
	g_signal_connect_object ((GtkToggleButton*) self->priv->trans_check, "toggled", (GCallback) _rygel_general_pref_section_on_trans_check_toggled_gtk_toggle_button_toggled, self, 0);
	return self;
}


RygelGeneralPrefSection* rygel_general_pref_section_new (GtkBuilder* builder, RygelConfiguration* config, GError** error) {
	return rygel_general_pref_section_construct (RYGEL_TYPE_GENERAL_PREF_SECTION, builder, config, error);
}


static void rygel_general_pref_section_real_save (RygelPreferencesSection* base) {
	RygelGeneralPrefSection * self;
	self = (RygelGeneralPrefSection*) base;
	rygel_configuration_set_host_ip (((RygelPreferencesSection*) self)->config, gtk_entry_get_text (self->priv->ip_entry));
	rygel_configuration_set_port (((RygelPreferencesSection*) self)->config, (gint) gtk_spin_button_get_value (self->priv->port_spin));
	rygel_configuration_set_transcoding (((RygelPreferencesSection*) self)->config, gtk_toggle_button_get_active ((GtkToggleButton*) self->priv->trans_check));
	rygel_configuration_set_mp3_transcoder (((RygelPreferencesSection*) self)->config, gtk_toggle_button_get_active ((GtkToggleButton*) self->priv->mp3_check));
	rygel_configuration_set_mp2ts_transcoder (((RygelPreferencesSection*) self)->config, gtk_toggle_button_get_active ((GtkToggleButton*) self->priv->mp2ts_check));
	rygel_configuration_set_lpcm_transcoder (((RygelPreferencesSection*) self)->config, gtk_toggle_button_get_active ((GtkToggleButton*) self->priv->lpcm_check));
}


static void rygel_general_pref_section_on_trans_check_toggled (RygelGeneralPrefSection* self, GtkCheckButton* trans_check) {
	gboolean _tmp0_;
	gboolean _tmp1_;
	g_return_if_fail (self != NULL);
	g_return_if_fail (trans_check != NULL);
	g_object_set ((GtkWidget*) self->priv->mp3_check, "sensitive", (g_object_set ((GtkWidget*) self->priv->mp2ts_check, "sensitive", (g_object_set ((GtkWidget*) self->priv->lpcm_check, "sensitive", gtk_toggle_button_get_active ((GtkToggleButton*) trans_check), NULL), (g_object_get ((GtkWidget*) self->priv->lpcm_check, "sensitive", &_tmp0_, NULL), _tmp0_)), NULL), (g_object_get ((GtkWidget*) self->priv->mp2ts_check, "sensitive", &_tmp1_, NULL), _tmp1_)), NULL);
}


static void rygel_general_pref_section_class_init (RygelGeneralPrefSectionClass * klass) {
	rygel_general_pref_section_parent_class = g_type_class_peek_parent (klass);
	g_type_class_add_private (klass, sizeof (RygelGeneralPrefSectionPrivate));
	RYGEL_PREFERENCES_SECTION_CLASS (klass)->save = rygel_general_pref_section_real_save;
	G_OBJECT_CLASS (klass)->finalize = rygel_general_pref_section_finalize;
}


static void rygel_general_pref_section_instance_init (RygelGeneralPrefSection * self) {
	self->priv = RYGEL_GENERAL_PREF_SECTION_GET_PRIVATE (self);
}


static void rygel_general_pref_section_finalize (GObject* obj) {
	RygelGeneralPrefSection * self;
	self = RYGEL_GENERAL_PREF_SECTION (obj);
	(self->priv->ip_entry == NULL) ? NULL : (self->priv->ip_entry = (g_object_unref (self->priv->ip_entry), NULL));
	(self->priv->port_spin == NULL) ? NULL : (self->priv->port_spin = (g_object_unref (self->priv->port_spin), NULL));
	(self->priv->trans_check == NULL) ? NULL : (self->priv->trans_check = (g_object_unref (self->priv->trans_check), NULL));
	(self->priv->mp3_check == NULL) ? NULL : (self->priv->mp3_check = (g_object_unref (self->priv->mp3_check), NULL));
	(self->priv->mp2ts_check == NULL) ? NULL : (self->priv->mp2ts_check = (g_object_unref (self->priv->mp2ts_check), NULL));
	(self->priv->lpcm_check == NULL) ? NULL : (self->priv->lpcm_check = (g_object_unref (self->priv->lpcm_check), NULL));
	G_OBJECT_CLASS (rygel_general_pref_section_parent_class)->finalize (obj);
}


GType rygel_general_pref_section_get_type (void) {
	static GType rygel_general_pref_section_type_id = 0;
	if (rygel_general_pref_section_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (RygelGeneralPrefSectionClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) rygel_general_pref_section_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (RygelGeneralPrefSection), 0, (GInstanceInitFunc) rygel_general_pref_section_instance_init, NULL };
		rygel_general_pref_section_type_id = g_type_register_static (RYGEL_TYPE_PREFERENCES_SECTION, "RygelGeneralPrefSection", &g_define_type_info, 0);
	}
	return rygel_general_pref_section_type_id;
}




