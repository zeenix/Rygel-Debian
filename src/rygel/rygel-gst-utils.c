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
#include <gst/gst.h>
#include <stdlib.h>
#include <string.h>
#include <gobject/gvaluecollector.h>


#define RYGEL_TYPE_GST_UTILS (rygel_gst_utils_get_type ())
#define RYGEL_GST_UTILS(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_GST_UTILS, RygelGstUtils))
#define RYGEL_GST_UTILS_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_GST_UTILS, RygelGstUtilsClass))
#define RYGEL_IS_GST_UTILS(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_GST_UTILS))
#define RYGEL_IS_GST_UTILS_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_GST_UTILS))
#define RYGEL_GST_UTILS_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_GST_UTILS, RygelGstUtilsClass))

typedef struct _RygelGstUtils RygelGstUtils;
typedef struct _RygelGstUtilsClass RygelGstUtilsClass;
typedef struct _RygelGstUtilsPrivate RygelGstUtilsPrivate;
typedef struct _RygelParamSpecGstUtils RygelParamSpecGstUtils;

struct _RygelGstUtils {
	GTypeInstance parent_instance;
	volatile int ref_count;
	RygelGstUtilsPrivate * priv;
};

struct _RygelGstUtilsClass {
	GTypeClass parent_class;
	void (*finalize) (RygelGstUtils *self);
};

typedef enum  {
	RYGEL_LIVE_RESPONSE_ERROR_MISSING_PLUGIN,
	RYGEL_LIVE_RESPONSE_ERROR_LINK
} RygelLiveResponseError;
#define RYGEL_LIVE_RESPONSE_ERROR rygel_live_response_error_quark ()
struct _RygelParamSpecGstUtils {
	GParamSpec parent_instance;
};



gpointer rygel_gst_utils_ref (gpointer instance);
void rygel_gst_utils_unref (gpointer instance);
GParamSpec* rygel_param_spec_gst_utils (const gchar* name, const gchar* nick, const gchar* blurb, GType object_type, GParamFlags flags);
void rygel_value_set_gst_utils (GValue* value, gpointer v_object);
gpointer rygel_value_get_gst_utils (const GValue* value);
GType rygel_gst_utils_get_type (void);
enum  {
	RYGEL_GST_UTILS_DUMMY_PROPERTY
};
GQuark rygel_live_response_error_quark (void);
GstElement* rygel_gst_utils_create_element (const char* factoryname, const char* name, GError** error);
void rygel_gst_utils_post_error (GstElement* dest, GError* _error_);
static gpointer rygel_gst_utils_parent_class = NULL;
static void rygel_gst_utils_finalize (RygelGstUtils* obj);



GstElement* rygel_gst_utils_create_element (const char* factoryname, const char* name, GError** error) {
	GError * _inner_error_;
	GstElement* element;
	g_return_val_if_fail (factoryname != NULL, NULL);
	_inner_error_ = NULL;
	element = gst_element_factory_make (factoryname, name);
	if (element == NULL) {
		_inner_error_ = g_error_new (RYGEL_LIVE_RESPONSE_ERROR, RYGEL_LIVE_RESPONSE_ERROR_MISSING_PLUGIN, "Required element factory '%s' missing", factoryname);
		if (_inner_error_ != NULL) {
			g_propagate_error (error, _inner_error_);
			(element == NULL) ? NULL : (element = (gst_object_unref (element), NULL));
			return NULL;
		}
	}
	return element;
}


void rygel_gst_utils_post_error (GstElement* dest, GError* _error_) {
	GstMessage* msg;
	GstMessage* _tmp0_;
	g_return_if_fail (dest != NULL);
	msg = gst_message_new_error ((GstObject*) dest, _error_, _error_->message);
	_tmp0_ = NULL;
	gst_element_post_message (dest, (_tmp0_ = msg, (_tmp0_ == NULL) ? NULL : gst_message_ref (_tmp0_)));
	(msg == NULL) ? NULL : (msg = (gst_message_unref (msg), NULL));
}


static void rygel_value_gst_utils_init (GValue* value) {
	value->data[0].v_pointer = NULL;
}


static void rygel_value_gst_utils_free_value (GValue* value) {
	if (value->data[0].v_pointer) {
		rygel_gst_utils_unref (value->data[0].v_pointer);
	}
}


static void rygel_value_gst_utils_copy_value (const GValue* src_value, GValue* dest_value) {
	if (src_value->data[0].v_pointer) {
		dest_value->data[0].v_pointer = rygel_gst_utils_ref (src_value->data[0].v_pointer);
	} else {
		dest_value->data[0].v_pointer = NULL;
	}
}


static gpointer rygel_value_gst_utils_peek_pointer (const GValue* value) {
	return value->data[0].v_pointer;
}


static gchar* rygel_value_gst_utils_collect_value (GValue* value, guint n_collect_values, GTypeCValue* collect_values, guint collect_flags) {
	if (collect_values[0].v_pointer) {
		RygelGstUtils* object;
		object = collect_values[0].v_pointer;
		if (object->parent_instance.g_class == NULL) {
			return g_strconcat ("invalid unclassed object pointer for value type `", G_VALUE_TYPE_NAME (value), "'", NULL);
		} else if (!g_value_type_compatible (G_TYPE_FROM_INSTANCE (object), G_VALUE_TYPE (value))) {
			return g_strconcat ("invalid object type `", g_type_name (G_TYPE_FROM_INSTANCE (object)), "' for value type `", G_VALUE_TYPE_NAME (value), "'", NULL);
		}
		value->data[0].v_pointer = rygel_gst_utils_ref (object);
	} else {
		value->data[0].v_pointer = NULL;
	}
	return NULL;
}


static gchar* rygel_value_gst_utils_lcopy_value (const GValue* value, guint n_collect_values, GTypeCValue* collect_values, guint collect_flags) {
	RygelGstUtils** object_p;
	object_p = collect_values[0].v_pointer;
	if (!object_p) {
		return g_strdup_printf ("value location for `%s' passed as NULL", G_VALUE_TYPE_NAME (value));
	}
	if (!value->data[0].v_pointer) {
		*object_p = NULL;
	} else if (collect_flags && G_VALUE_NOCOPY_CONTENTS) {
		*object_p = value->data[0].v_pointer;
	} else {
		*object_p = rygel_gst_utils_ref (value->data[0].v_pointer);
	}
	return NULL;
}


GParamSpec* rygel_param_spec_gst_utils (const gchar* name, const gchar* nick, const gchar* blurb, GType object_type, GParamFlags flags) {
	RygelParamSpecGstUtils* spec;
	g_return_val_if_fail (g_type_is_a (object_type, RYGEL_TYPE_GST_UTILS), NULL);
	spec = g_param_spec_internal (G_TYPE_PARAM_OBJECT, name, nick, blurb, flags);
	G_PARAM_SPEC (spec)->value_type = object_type;
	return G_PARAM_SPEC (spec);
}


gpointer rygel_value_get_gst_utils (const GValue* value) {
	g_return_val_if_fail (G_TYPE_CHECK_VALUE_TYPE (value, RYGEL_TYPE_GST_UTILS), NULL);
	return value->data[0].v_pointer;
}


void rygel_value_set_gst_utils (GValue* value, gpointer v_object) {
	RygelGstUtils* old;
	g_return_if_fail (G_TYPE_CHECK_VALUE_TYPE (value, RYGEL_TYPE_GST_UTILS));
	old = value->data[0].v_pointer;
	if (v_object) {
		g_return_if_fail (G_TYPE_CHECK_INSTANCE_TYPE (v_object, RYGEL_TYPE_GST_UTILS));
		g_return_if_fail (g_value_type_compatible (G_TYPE_FROM_INSTANCE (v_object), G_VALUE_TYPE (value)));
		value->data[0].v_pointer = v_object;
		rygel_gst_utils_ref (value->data[0].v_pointer);
	} else {
		value->data[0].v_pointer = NULL;
	}
	if (old) {
		rygel_gst_utils_unref (old);
	}
}


static void rygel_gst_utils_class_init (RygelGstUtilsClass * klass) {
	rygel_gst_utils_parent_class = g_type_class_peek_parent (klass);
	RYGEL_GST_UTILS_CLASS (klass)->finalize = rygel_gst_utils_finalize;
}


static void rygel_gst_utils_instance_init (RygelGstUtils * self) {
	self->ref_count = 1;
}


static void rygel_gst_utils_finalize (RygelGstUtils* obj) {
	RygelGstUtils * self;
	self = RYGEL_GST_UTILS (obj);
}


GType rygel_gst_utils_get_type (void) {
	static GType rygel_gst_utils_type_id = 0;
	if (rygel_gst_utils_type_id == 0) {
		static const GTypeValueTable g_define_type_value_table = { rygel_value_gst_utils_init, rygel_value_gst_utils_free_value, rygel_value_gst_utils_copy_value, rygel_value_gst_utils_peek_pointer, "p", rygel_value_gst_utils_collect_value, "p", rygel_value_gst_utils_lcopy_value };
		static const GTypeInfo g_define_type_info = { sizeof (RygelGstUtilsClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) rygel_gst_utils_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (RygelGstUtils), 0, (GInstanceInitFunc) rygel_gst_utils_instance_init, &g_define_type_value_table };
		static const GTypeFundamentalInfo g_define_type_fundamental_info = { (G_TYPE_FLAG_CLASSED | G_TYPE_FLAG_INSTANTIATABLE | G_TYPE_FLAG_DERIVABLE | G_TYPE_FLAG_DEEP_DERIVABLE) };
		rygel_gst_utils_type_id = g_type_register_fundamental (g_type_fundamental_next (), "RygelGstUtils", &g_define_type_info, &g_define_type_fundamental_info, G_TYPE_FLAG_ABSTRACT);
	}
	return rygel_gst_utils_type_id;
}


gpointer rygel_gst_utils_ref (gpointer instance) {
	RygelGstUtils* self;
	self = instance;
	g_atomic_int_inc (&self->ref_count);
	return instance;
}


void rygel_gst_utils_unref (gpointer instance) {
	RygelGstUtils* self;
	self = instance;
	if (g_atomic_int_dec_and_test (&self->ref_count)) {
		RYGEL_GST_UTILS_GET_CLASS (self)->finalize (self);
		g_type_free_instance ((GTypeInstance *) self);
	}
}




