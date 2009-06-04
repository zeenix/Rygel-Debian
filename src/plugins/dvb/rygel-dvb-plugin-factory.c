/*
 * Copyright (C) 2009 Zeeshan Ali (Khattak) <zeeshanak@gnome.org>.
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
#include <dbus/dbus-glib-lowlevel.h>
#include <dbus/dbus-glib.h>
#include <stdlib.h>
#include <string.h>
#include <gobject/gvaluecollector.h>


#define TYPE_DVB_PLUGIN_FACTORY (dvb_plugin_factory_get_type ())
#define DVB_PLUGIN_FACTORY(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_DVB_PLUGIN_FACTORY, DVBPluginFactory))
#define DVB_PLUGIN_FACTORY_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_DVB_PLUGIN_FACTORY, DVBPluginFactoryClass))
#define IS_DVB_PLUGIN_FACTORY(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_DVB_PLUGIN_FACTORY))
#define IS_DVB_PLUGIN_FACTORY_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_DVB_PLUGIN_FACTORY))
#define DVB_PLUGIN_FACTORY_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_DVB_PLUGIN_FACTORY, DVBPluginFactoryClass))

typedef struct _DVBPluginFactory DVBPluginFactory;
typedef struct _DVBPluginFactoryClass DVBPluginFactoryClass;
typedef struct _DVBPluginFactoryPrivate DVBPluginFactoryPrivate;

#define TYPE_DVB_PLUGIN (dvb_plugin_get_type ())
#define DVB_PLUGIN(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_DVB_PLUGIN, DVBPlugin))
#define DVB_PLUGIN_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_DVB_PLUGIN, DVBPluginClass))
#define IS_DVB_PLUGIN(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_DVB_PLUGIN))
#define IS_DVB_PLUGIN_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_DVB_PLUGIN))
#define DVB_PLUGIN_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_DVB_PLUGIN, DVBPluginClass))

typedef struct _DVBPlugin DVBPlugin;
typedef struct _DVBPluginClass DVBPluginClass;
typedef struct _ParamSpecDVBPluginFactory ParamSpecDVBPluginFactory;

struct _DVBPluginFactory {
	GTypeInstance parent_instance;
	volatile int ref_count;
	DVBPluginFactoryPrivate * priv;
};

struct _DVBPluginFactoryClass {
	GTypeClass parent_class;
	void (*finalize) (DVBPluginFactory *self);
};

struct _DVBPluginFactoryPrivate {
	DBusGProxy* dbus_obj;
	RygelPluginLoader* loader;
};

struct _ParamSpecDVBPluginFactory {
	GParamSpec parent_instance;
};



extern DVBPluginFactory* plugin_factory;
DVBPluginFactory* plugin_factory = NULL;
DVBPluginFactory* dvb_plugin_factory_new (RygelPluginLoader* loader, GError** error);
DVBPluginFactory* dvb_plugin_factory_construct (GType object_type, RygelPluginLoader* loader, GError** error);
gpointer dvb_plugin_factory_ref (gpointer instance);
void dvb_plugin_factory_unref (gpointer instance);
GParamSpec* param_spec_dvb_plugin_factory (const gchar* name, const gchar* nick, const gchar* blurb, GType object_type, GParamFlags flags);
void value_set_dvb_plugin_factory (GValue* value, gpointer v_object);
gpointer value_get_dvb_plugin_factory (const GValue* value);
GType dvb_plugin_factory_get_type (void);
void module_init (RygelPluginLoader* loader);
#define DVB_PLUGIN_FACTORY_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), TYPE_DVB_PLUGIN_FACTORY, DVBPluginFactoryPrivate))
enum  {
	DVB_PLUGIN_FACTORY_DUMMY_PROPERTY
};
#define DVB_PLUGIN_FACTORY_DBUS_SERVICE "org.freedesktop.DBus"
#define DVB_PLUGIN_FACTORY_DBUS_OBJECT "/org/freedesktop/DBus"
#define DVB_PLUGIN_FACTORY_DBUS_IFACE "org.freedesktop.DBus"
#define DVB_PLUGIN_FACTORY_TRACKER_SERVICE "org.gnome.DVB"
static void dvb_plugin_factory_start_service_cb (DVBPluginFactory* self, guint32 status, GError* err);
void _dynamic_StartServiceByName7 (DBusGProxy* self, const char* param1, guint32 param2, gpointer param3, void* param3_target, GError** error);
DVBPluginFactory* dvb_plugin_factory_new (RygelPluginLoader* loader, GError** error);
DVBPlugin* dvb_plugin_new (void);
DVBPlugin* dvb_plugin_construct (GType object_type);
GType dvb_plugin_get_type (void);
static gpointer dvb_plugin_factory_parent_class = NULL;
static void dvb_plugin_factory_finalize (DVBPluginFactory* obj);



void module_init (RygelPluginLoader* loader) {
	GError * _inner_error_;
	g_return_if_fail (loader != NULL);
	_inner_error_ = NULL;
	{
		DVBPluginFactory* _tmp0_;
		_tmp0_ = NULL;
		plugin_factory = (_tmp0_ = dvb_plugin_factory_new (loader, &_inner_error_), (plugin_factory == NULL) ? NULL : (plugin_factory = (dvb_plugin_factory_unref (plugin_factory), NULL)), _tmp0_);
		if (_inner_error_ != NULL) {
			if (_inner_error_->domain == DBUS_GERROR) {
				goto __catch4_dbus_gerror;
			}
			goto __finally4;
		}
	}
	goto __finally4;
	__catch4_dbus_gerror:
	{
		GError * _error_;
		_error_ = _inner_error_;
		_inner_error_ = NULL;
		{
			g_critical ("rygel-dvb-plugin-factory.vala:36: Failed to fetch list of external services: %s\n", _error_->message);
			(_error_ == NULL) ? NULL : (_error_ = (g_error_free (_error_), NULL));
		}
	}
	__finally4:
	if (_inner_error_ != NULL) {
		g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, _inner_error_->message);
		g_clear_error (&_inner_error_);
		return;
	}
}


static void _dvb_plugin_factory_start_service_cb_cb (DBusGProxy* proxy, DBusGProxyCall* call, void* user_data) {
	GError* error;
	guint32 status;
	error = NULL;
	dbus_g_proxy_end_call (proxy, call, &error, G_TYPE_UINT, &status, G_TYPE_INVALID);
	dvb_plugin_factory_start_service_cb (user_data, status, error);
}


void _dynamic_StartServiceByName7 (DBusGProxy* self, const char* param1, guint32 param2, gpointer param3, void* param3_target, GError** error) {
	dbus_g_proxy_begin_call (self, "StartServiceByName", _dvb_plugin_factory_start_service_cb_cb, param3_target, NULL, G_TYPE_STRING, param1, G_TYPE_UINT, param2, G_TYPE_INVALID, G_TYPE_INVALID);
	if (*error) {
		return;
	}
}


DVBPluginFactory* dvb_plugin_factory_construct (GType object_type, RygelPluginLoader* loader, GError** error) {
	GError * _inner_error_;
	DVBPluginFactory* self;
	DBusGConnection* connection;
	DBusGProxy* _tmp0_;
	RygelPluginLoader* _tmp2_;
	RygelPluginLoader* _tmp1_;
	g_return_val_if_fail (loader != NULL, NULL);
	_inner_error_ = NULL;
	self = (DVBPluginFactory*) g_type_create_instance (object_type);
	connection = dbus_g_bus_get (DBUS_BUS_SESSION, &_inner_error_);
	if (_inner_error_ != NULL) {
		if (_inner_error_->domain == DBUS_GERROR) {
			g_propagate_error (error, _inner_error_);
			return;
		} else {
			g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, _inner_error_->message);
			g_clear_error (&_inner_error_);
			return NULL;
		}
	}
	_tmp0_ = NULL;
	self->priv->dbus_obj = (_tmp0_ = dbus_g_proxy_new_for_name (connection, DVB_PLUGIN_FACTORY_DBUS_SERVICE, DVB_PLUGIN_FACTORY_DBUS_OBJECT, DVB_PLUGIN_FACTORY_DBUS_IFACE), (self->priv->dbus_obj == NULL) ? NULL : (self->priv->dbus_obj = (g_object_unref (self->priv->dbus_obj), NULL)), _tmp0_);
	_tmp2_ = NULL;
	_tmp1_ = NULL;
	self->priv->loader = (_tmp2_ = (_tmp1_ = loader, (_tmp1_ == NULL) ? NULL : g_object_ref (_tmp1_)), (self->priv->loader == NULL) ? NULL : (self->priv->loader = (g_object_unref (self->priv->loader), NULL)), _tmp2_);
	_dynamic_StartServiceByName7 (self->priv->dbus_obj, DVB_PLUGIN_FACTORY_TRACKER_SERVICE, (guint32) 0, dvb_plugin_factory_start_service_cb, self, &_inner_error_);
	if (_inner_error_ != NULL) {
		if (_inner_error_->domain == DBUS_GERROR) {
			g_propagate_error (error, _inner_error_);
			(connection == NULL) ? NULL : (connection = (dbus_g_connection_unref (connection), NULL));
			return;
		} else {
			(connection == NULL) ? NULL : (connection = (dbus_g_connection_unref (connection), NULL));
			g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, _inner_error_->message);
			g_clear_error (&_inner_error_);
			return NULL;
		}
	}
	(connection == NULL) ? NULL : (connection = (dbus_g_connection_unref (connection), NULL));
	return self;
}


DVBPluginFactory* dvb_plugin_factory_new (RygelPluginLoader* loader, GError** error) {
	return dvb_plugin_factory_construct (TYPE_DVB_PLUGIN_FACTORY, loader, error);
}


static void dvb_plugin_factory_start_service_cb (DVBPluginFactory* self, guint32 status, GError* err) {
	DVBPlugin* _tmp0_;
	g_return_if_fail (self != NULL);
	if (err != NULL) {
		g_warning ("rygel-dvb-plugin-factory.vala:66: Failed to start DVB service: %s\n", err->message);
		g_warning ("rygel-dvb-plugin-factory.vala:68: DVB plugin disabled.\n");
		return;
	}
	_tmp0_ = NULL;
	rygel_plugin_loader_add_plugin (self->priv->loader, (RygelPlugin*) (_tmp0_ = dvb_plugin_new ()));
	(_tmp0_ == NULL) ? NULL : (_tmp0_ = (g_object_unref (_tmp0_), NULL));
}


static void value_dvb_plugin_factory_init (GValue* value) {
	value->data[0].v_pointer = NULL;
}


static void value_dvb_plugin_factory_free_value (GValue* value) {
	if (value->data[0].v_pointer) {
		dvb_plugin_factory_unref (value->data[0].v_pointer);
	}
}


static void value_dvb_plugin_factory_copy_value (const GValue* src_value, GValue* dest_value) {
	if (src_value->data[0].v_pointer) {
		dest_value->data[0].v_pointer = dvb_plugin_factory_ref (src_value->data[0].v_pointer);
	} else {
		dest_value->data[0].v_pointer = NULL;
	}
}


static gpointer value_dvb_plugin_factory_peek_pointer (const GValue* value) {
	return value->data[0].v_pointer;
}


static gchar* value_dvb_plugin_factory_collect_value (GValue* value, guint n_collect_values, GTypeCValue* collect_values, guint collect_flags) {
	if (collect_values[0].v_pointer) {
		DVBPluginFactory* object;
		object = collect_values[0].v_pointer;
		if (object->parent_instance.g_class == NULL) {
			return g_strconcat ("invalid unclassed object pointer for value type `", G_VALUE_TYPE_NAME (value), "'", NULL);
		} else if (!g_value_type_compatible (G_TYPE_FROM_INSTANCE (object), G_VALUE_TYPE (value))) {
			return g_strconcat ("invalid object type `", g_type_name (G_TYPE_FROM_INSTANCE (object)), "' for value type `", G_VALUE_TYPE_NAME (value), "'", NULL);
		}
		value->data[0].v_pointer = dvb_plugin_factory_ref (object);
	} else {
		value->data[0].v_pointer = NULL;
	}
	return NULL;
}


static gchar* value_dvb_plugin_factory_lcopy_value (const GValue* value, guint n_collect_values, GTypeCValue* collect_values, guint collect_flags) {
	DVBPluginFactory** object_p;
	object_p = collect_values[0].v_pointer;
	if (!object_p) {
		return g_strdup_printf ("value location for `%s' passed as NULL", G_VALUE_TYPE_NAME (value));
	}
	if (!value->data[0].v_pointer) {
		*object_p = NULL;
	} else if (collect_flags && G_VALUE_NOCOPY_CONTENTS) {
		*object_p = value->data[0].v_pointer;
	} else {
		*object_p = dvb_plugin_factory_ref (value->data[0].v_pointer);
	}
	return NULL;
}


GParamSpec* param_spec_dvb_plugin_factory (const gchar* name, const gchar* nick, const gchar* blurb, GType object_type, GParamFlags flags) {
	ParamSpecDVBPluginFactory* spec;
	g_return_val_if_fail (g_type_is_a (object_type, TYPE_DVB_PLUGIN_FACTORY), NULL);
	spec = g_param_spec_internal (G_TYPE_PARAM_OBJECT, name, nick, blurb, flags);
	G_PARAM_SPEC (spec)->value_type = object_type;
	return G_PARAM_SPEC (spec);
}


gpointer value_get_dvb_plugin_factory (const GValue* value) {
	g_return_val_if_fail (G_TYPE_CHECK_VALUE_TYPE (value, TYPE_DVB_PLUGIN_FACTORY), NULL);
	return value->data[0].v_pointer;
}


void value_set_dvb_plugin_factory (GValue* value, gpointer v_object) {
	DVBPluginFactory* old;
	g_return_if_fail (G_TYPE_CHECK_VALUE_TYPE (value, TYPE_DVB_PLUGIN_FACTORY));
	old = value->data[0].v_pointer;
	if (v_object) {
		g_return_if_fail (G_TYPE_CHECK_INSTANCE_TYPE (v_object, TYPE_DVB_PLUGIN_FACTORY));
		g_return_if_fail (g_value_type_compatible (G_TYPE_FROM_INSTANCE (v_object), G_VALUE_TYPE (value)));
		value->data[0].v_pointer = v_object;
		dvb_plugin_factory_ref (value->data[0].v_pointer);
	} else {
		value->data[0].v_pointer = NULL;
	}
	if (old) {
		dvb_plugin_factory_unref (old);
	}
}


static void dvb_plugin_factory_class_init (DVBPluginFactoryClass * klass) {
	dvb_plugin_factory_parent_class = g_type_class_peek_parent (klass);
	DVB_PLUGIN_FACTORY_CLASS (klass)->finalize = dvb_plugin_factory_finalize;
	g_type_class_add_private (klass, sizeof (DVBPluginFactoryPrivate));
}


static void dvb_plugin_factory_instance_init (DVBPluginFactory * self) {
	self->priv = DVB_PLUGIN_FACTORY_GET_PRIVATE (self);
	self->ref_count = 1;
}


static void dvb_plugin_factory_finalize (DVBPluginFactory* obj) {
	DVBPluginFactory * self;
	self = DVB_PLUGIN_FACTORY (obj);
	(self->priv->dbus_obj == NULL) ? NULL : (self->priv->dbus_obj = (g_object_unref (self->priv->dbus_obj), NULL));
	(self->priv->loader == NULL) ? NULL : (self->priv->loader = (g_object_unref (self->priv->loader), NULL));
}


GType dvb_plugin_factory_get_type (void) {
	static GType dvb_plugin_factory_type_id = 0;
	if (dvb_plugin_factory_type_id == 0) {
		static const GTypeValueTable g_define_type_value_table = { value_dvb_plugin_factory_init, value_dvb_plugin_factory_free_value, value_dvb_plugin_factory_copy_value, value_dvb_plugin_factory_peek_pointer, "p", value_dvb_plugin_factory_collect_value, "p", value_dvb_plugin_factory_lcopy_value };
		static const GTypeInfo g_define_type_info = { sizeof (DVBPluginFactoryClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) dvb_plugin_factory_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (DVBPluginFactory), 0, (GInstanceInitFunc) dvb_plugin_factory_instance_init, &g_define_type_value_table };
		static const GTypeFundamentalInfo g_define_type_fundamental_info = { (G_TYPE_FLAG_CLASSED | G_TYPE_FLAG_INSTANTIATABLE | G_TYPE_FLAG_DERIVABLE | G_TYPE_FLAG_DEEP_DERIVABLE) };
		dvb_plugin_factory_type_id = g_type_register_fundamental (g_type_fundamental_next (), "DVBPluginFactory", &g_define_type_info, &g_define_type_fundamental_info, 0);
	}
	return dvb_plugin_factory_type_id;
}


gpointer dvb_plugin_factory_ref (gpointer instance) {
	DVBPluginFactory* self;
	self = instance;
	g_atomic_int_inc (&self->ref_count);
	return instance;
}


void dvb_plugin_factory_unref (gpointer instance) {
	DVBPluginFactory* self;
	self = instance;
	if (g_atomic_int_dec_and_test (&self->ref_count)) {
		DVB_PLUGIN_FACTORY_GET_CLASS (self)->finalize (self);
		g_type_free_instance ((GTypeInstance *) self);
	}
}




