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


#define TYPE_EXTERNAL_PLUGIN_FACTORY (external_plugin_factory_get_type ())
#define EXTERNAL_PLUGIN_FACTORY(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_EXTERNAL_PLUGIN_FACTORY, ExternalPluginFactory))
#define EXTERNAL_PLUGIN_FACTORY_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_EXTERNAL_PLUGIN_FACTORY, ExternalPluginFactoryClass))
#define IS_EXTERNAL_PLUGIN_FACTORY(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_EXTERNAL_PLUGIN_FACTORY))
#define IS_EXTERNAL_PLUGIN_FACTORY_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_EXTERNAL_PLUGIN_FACTORY))
#define EXTERNAL_PLUGIN_FACTORY_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_EXTERNAL_PLUGIN_FACTORY, ExternalPluginFactoryClass))

typedef struct _ExternalPluginFactory ExternalPluginFactory;
typedef struct _ExternalPluginFactoryClass ExternalPluginFactoryClass;
typedef struct _ExternalPluginFactoryPrivate ExternalPluginFactoryPrivate;

#define TYPE_EXTERNAL_PLUGIN (external_plugin_get_type ())
#define EXTERNAL_PLUGIN(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_EXTERNAL_PLUGIN, ExternalPlugin))
#define EXTERNAL_PLUGIN_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_EXTERNAL_PLUGIN, ExternalPluginClass))
#define IS_EXTERNAL_PLUGIN(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_EXTERNAL_PLUGIN))
#define IS_EXTERNAL_PLUGIN_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_EXTERNAL_PLUGIN))
#define EXTERNAL_PLUGIN_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_EXTERNAL_PLUGIN, ExternalPluginClass))

typedef struct _ExternalPlugin ExternalPlugin;
typedef struct _ExternalPluginClass ExternalPluginClass;
typedef struct _ParamSpecExternalPluginFactory ParamSpecExternalPluginFactory;

struct _ExternalPluginFactory {
	GTypeInstance parent_instance;
	volatile int ref_count;
	ExternalPluginFactoryPrivate * priv;
};

struct _ExternalPluginFactoryClass {
	GTypeClass parent_class;
	void (*finalize) (ExternalPluginFactory *self);
};

struct _ExternalPluginFactoryPrivate {
	DBusGProxy* dbus_obj;
	DBusGConnection* connection;
	RygelPluginLoader* loader;
	gboolean activatable;
};

struct _ParamSpecExternalPluginFactory {
	GParamSpec parent_instance;
};



extern ExternalPluginFactory* plugin_factory;
ExternalPluginFactory* plugin_factory = NULL;
ExternalPluginFactory* external_plugin_factory_new (RygelPluginLoader* loader, GError** error);
ExternalPluginFactory* external_plugin_factory_construct (GType object_type, RygelPluginLoader* loader, GError** error);
gpointer external_plugin_factory_ref (gpointer instance);
void external_plugin_factory_unref (gpointer instance);
GParamSpec* param_spec_external_plugin_factory (const gchar* name, const gchar* nick, const gchar* blurb, GType object_type, GParamFlags flags);
void value_set_external_plugin_factory (GValue* value, gpointer v_object);
gpointer value_get_external_plugin_factory (const GValue* value);
GType external_plugin_factory_get_type (void);
void module_init (RygelPluginLoader* loader);
#define EXTERNAL_PLUGIN_FACTORY_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), TYPE_EXTERNAL_PLUGIN_FACTORY, ExternalPluginFactoryPrivate))
enum  {
	EXTERNAL_PLUGIN_FACTORY_DUMMY_PROPERTY
};
#define EXTERNAL_PLUGIN_FACTORY_DBUS_SERVICE "org.freedesktop.DBus"
#define EXTERNAL_PLUGIN_FACTORY_DBUS_OBJECT "/org/freedesktop/DBus"
#define EXTERNAL_PLUGIN_FACTORY_DBUS_IFACE "org.freedesktop.DBus"
#define EXTERNAL_PLUGIN_FACTORY_SERVICE_PREFIX "org.gnome.UPnP.MediaServer1."
static void external_plugin_factory_list_names_cb (ExternalPluginFactory* self, char** services, int services_length1, GError* err);
void _dynamic_ListNames5 (DBusGProxy* self, gpointer param1, void* param1_target, GError** error);
ExternalPluginFactory* external_plugin_factory_new (RygelPluginLoader* loader, GError** error);
ExternalPlugin* external_plugin_new (DBusGConnection* connection, const char* service_name);
ExternalPlugin* external_plugin_construct (GType object_type, DBusGConnection* connection, const char* service_name);
GType external_plugin_get_type (void);
static void external_plugin_factory_name_owner_changed (ExternalPluginFactory* self, DBusGProxy* dbus_obj, const char* name, const char* old_owner, const char* new_owner);
static void _external_plugin_factory_name_owner_changed_dynamic_NameOwnerChanged2_ (DBusGProxy* _sender, const char* name, const char* old_owner, const char* new_owner, gpointer self);
void _dynamic_NameOwnerChanged3_connect (gpointer obj, const char * signal_name, GCallback handler, gpointer data);
void _dynamic_ListActivatableNames6 (DBusGProxy* self, gpointer param1, void* param1_target, GError** error);
static gpointer external_plugin_factory_parent_class = NULL;
static void external_plugin_factory_finalize (ExternalPluginFactory* obj);
static int _vala_strcmp0 (const char * str1, const char * str2);


static void g_cclosure_user_marshal_VOID__STRING_STRING_STRING (GClosure * closure, GValue * return_value, guint n_param_values, const GValue * param_values, gpointer invocation_hint, gpointer marshal_data);

void module_init (RygelPluginLoader* loader) {
	GError * _inner_error_;
	g_return_if_fail (loader != NULL);
	_inner_error_ = NULL;
	{
		ExternalPluginFactory* _tmp0_;
		_tmp0_ = NULL;
		plugin_factory = (_tmp0_ = external_plugin_factory_new (loader, &_inner_error_), (plugin_factory == NULL) ? NULL : (plugin_factory = (external_plugin_factory_unref (plugin_factory), NULL)), _tmp0_);
		if (_inner_error_ != NULL) {
			if (_inner_error_->domain == DBUS_GERROR) {
				goto __catch5_dbus_gerror;
			}
			goto __finally5;
		}
	}
	goto __finally5;
	__catch5_dbus_gerror:
	{
		GError * _error_;
		_error_ = _inner_error_;
		_inner_error_ = NULL;
		{
			g_critical ("rygel-external-plugin-factory.vala:36: Failed to fetch list of external services: %s\n", _error_->message);
			(_error_ == NULL) ? NULL : (_error_ = (g_error_free (_error_), NULL));
		}
	}
	__finally5:
	if (_inner_error_ != NULL) {
		g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, _inner_error_->message);
		g_clear_error (&_inner_error_);
		return;
	}
}


static void _external_plugin_factory_list_names_cb_cb (DBusGProxy* proxy, DBusGProxyCall* call, void* user_data) {
	GError* error;
	char** services;
	error = NULL;
	dbus_g_proxy_end_call (proxy, call, &error, G_TYPE_STRV, &services, G_TYPE_INVALID);
	external_plugin_factory_list_names_cb (user_data, services, g_strv_length (services), error);
}


void _dynamic_ListNames5 (DBusGProxy* self, gpointer param1, void* param1_target, GError** error) {
	dbus_g_proxy_begin_call (self, "ListNames", _external_plugin_factory_list_names_cb_cb, param1_target, NULL, G_TYPE_INVALID, G_TYPE_INVALID);
	if (*error) {
		return;
	}
}


/* Indicated if we have listed activatable services yet*/
ExternalPluginFactory* external_plugin_factory_construct (GType object_type, RygelPluginLoader* loader, GError** error) {
	GError * _inner_error_;
	ExternalPluginFactory* self;
	DBusGConnection* _tmp0_;
	DBusGConnection* _tmp1_;
	DBusGProxy* _tmp2_;
	RygelPluginLoader* _tmp4_;
	RygelPluginLoader* _tmp3_;
	g_return_val_if_fail (loader != NULL, NULL);
	_inner_error_ = NULL;
	self = (ExternalPluginFactory*) g_type_create_instance (object_type);
	_tmp0_ = dbus_g_bus_get (DBUS_BUS_SESSION, &_inner_error_);
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
	_tmp1_ = NULL;
	self->priv->connection = (_tmp1_ = _tmp0_, (self->priv->connection == NULL) ? NULL : (self->priv->connection = (dbus_g_connection_unref (self->priv->connection), NULL)), _tmp1_);
	_tmp2_ = NULL;
	self->priv->dbus_obj = (_tmp2_ = dbus_g_proxy_new_for_name (self->priv->connection, EXTERNAL_PLUGIN_FACTORY_DBUS_SERVICE, EXTERNAL_PLUGIN_FACTORY_DBUS_OBJECT, EXTERNAL_PLUGIN_FACTORY_DBUS_IFACE), (self->priv->dbus_obj == NULL) ? NULL : (self->priv->dbus_obj = (g_object_unref (self->priv->dbus_obj), NULL)), _tmp2_);
	_tmp4_ = NULL;
	_tmp3_ = NULL;
	self->priv->loader = (_tmp4_ = (_tmp3_ = loader, (_tmp3_ == NULL) ? NULL : g_object_ref (_tmp3_)), (self->priv->loader == NULL) ? NULL : (self->priv->loader = (g_object_unref (self->priv->loader), NULL)), _tmp4_);
	self->priv->activatable = FALSE;
	_dynamic_ListNames5 (self->priv->dbus_obj, external_plugin_factory_list_names_cb, self, &_inner_error_);
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
	return self;
}


ExternalPluginFactory* external_plugin_factory_new (RygelPluginLoader* loader, GError** error) {
	return external_plugin_factory_construct (TYPE_EXTERNAL_PLUGIN_FACTORY, loader, error);
}


static void _external_plugin_factory_name_owner_changed_dynamic_NameOwnerChanged2_ (DBusGProxy* _sender, const char* name, const char* old_owner, const char* new_owner, gpointer self) {
	external_plugin_factory_name_owner_changed (self, _sender, name, old_owner, new_owner);
}


void _dynamic_NameOwnerChanged3_connect (gpointer obj, const char * signal_name, GCallback handler, gpointer data) {
	dbus_g_object_register_marshaller (g_cclosure_user_marshal_VOID__STRING_STRING_STRING, G_TYPE_NONE, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INVALID);
	dbus_g_proxy_add_signal (obj, "NameOwnerChanged", G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INVALID);
	dbus_g_proxy_connect_signal (obj, signal_name, handler, data, NULL);
}


void _dynamic_ListActivatableNames6 (DBusGProxy* self, gpointer param1, void* param1_target, GError** error) {
	dbus_g_proxy_begin_call (self, "ListActivatableNames", _external_plugin_factory_list_names_cb_cb, param1_target, NULL, G_TYPE_INVALID, G_TYPE_INVALID);
	if (*error) {
		return;
	}
}


static void external_plugin_factory_list_names_cb (ExternalPluginFactory* self, char** services, int services_length1, GError* err) {
	GError * _inner_error_;
	g_return_if_fail (self != NULL);
	_inner_error_ = NULL;
	if (err != NULL) {
		g_critical ("rygel-external-plugin-factory.vala:69: Failed to fetch list of external services: %s\n", err->message);
		return;
	}
	{
		char** service_collection;
		int service_collection_length1;
		int service_it;
		service_collection = services;
		service_collection_length1 = services_length1;
		for (service_it = 0; service_it < services_length1; service_it = service_it + 1) {
			const char* _tmp1_;
			char* service;
			_tmp1_ = NULL;
			service = (_tmp1_ = service_collection[service_it], (_tmp1_ == NULL) ? NULL : g_strdup (_tmp1_));
			{
				if (g_str_has_prefix (service, EXTERNAL_PLUGIN_FACTORY_SERVICE_PREFIX)) {
					ExternalPlugin* _tmp0_;
					_tmp0_ = NULL;
					rygel_plugin_loader_add_plugin (self->priv->loader, (RygelPlugin*) (_tmp0_ = external_plugin_new (self->priv->connection, service)));
					(_tmp0_ == NULL) ? NULL : (_tmp0_ = (g_object_unref (_tmp0_), NULL));
				}
				service = (g_free (service), NULL);
			}
		}
	}
	if (self->priv->activatable) {
		/* Activatable services are already taken-care of, now we can
		 just relax but keep a watch on bus for plugins coming and
		 going away on the fly.*/
		_dynamic_NameOwnerChanged3_connect (self->priv->dbus_obj, "NameOwnerChanged", (GCallback) _external_plugin_factory_name_owner_changed_dynamic_NameOwnerChanged2_, self);
	} else {
		_dynamic_ListActivatableNames6 (self->priv->dbus_obj, external_plugin_factory_list_names_cb, self, &_inner_error_);
		if (_inner_error_ != NULL) {
			g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, _inner_error_->message);
			g_clear_error (&_inner_error_);
			return;
		}
		self->priv->activatable = TRUE;
	}
}


static void external_plugin_factory_name_owner_changed (ExternalPluginFactory* self, DBusGProxy* dbus_obj, const char* name, const char* old_owner, const char* new_owner) {
	RygelPlugin* plugin;
	g_return_if_fail (self != NULL);
	g_return_if_fail (dbus_obj != NULL);
	g_return_if_fail (name != NULL);
	g_return_if_fail (old_owner != NULL);
	g_return_if_fail (new_owner != NULL);
	plugin = rygel_plugin_loader_get_plugin_by_name (self->priv->loader, name);
	if (plugin != NULL) {
		gboolean _tmp0_;
		_tmp0_ = FALSE;
		if (_vala_strcmp0 (old_owner, "") != 0) {
			_tmp0_ = _vala_strcmp0 (new_owner, "") == 0;
		} else {
			_tmp0_ = FALSE;
		}
		if (_tmp0_) {
			g_debug ("rygel-external-plugin-factory.vala:101: Service '%s' going down, marking it as unavailable", name);
			rygel_plugin_set_available (plugin, FALSE);
		} else {
			gboolean _tmp1_;
			_tmp1_ = FALSE;
			if (_vala_strcmp0 (old_owner, "") == 0) {
				_tmp1_ = _vala_strcmp0 (new_owner, "") != 0;
			} else {
				_tmp1_ = FALSE;
			}
			if (_tmp1_) {
				g_debug ("rygel-external-plugin-factory.vala:105: Service '%s' up again, marking it as available", name);
				rygel_plugin_set_available (plugin, TRUE);
			}
		}
	} else {
		if (g_str_has_prefix (name, EXTERNAL_PLUGIN_FACTORY_SERVICE_PREFIX)) {
			ExternalPlugin* _tmp2_;
			/* Ah, new plugin available, lets use it*/
			_tmp2_ = NULL;
			rygel_plugin_loader_add_plugin (self->priv->loader, (RygelPlugin*) (_tmp2_ = external_plugin_new (self->priv->connection, name)));
			(_tmp2_ == NULL) ? NULL : (_tmp2_ = (g_object_unref (_tmp2_), NULL));
		}
	}
	(plugin == NULL) ? NULL : (plugin = (g_object_unref (plugin), NULL));
}


static void value_external_plugin_factory_init (GValue* value) {
	value->data[0].v_pointer = NULL;
}


static void value_external_plugin_factory_free_value (GValue* value) {
	if (value->data[0].v_pointer) {
		external_plugin_factory_unref (value->data[0].v_pointer);
	}
}


static void value_external_plugin_factory_copy_value (const GValue* src_value, GValue* dest_value) {
	if (src_value->data[0].v_pointer) {
		dest_value->data[0].v_pointer = external_plugin_factory_ref (src_value->data[0].v_pointer);
	} else {
		dest_value->data[0].v_pointer = NULL;
	}
}


static gpointer value_external_plugin_factory_peek_pointer (const GValue* value) {
	return value->data[0].v_pointer;
}


static gchar* value_external_plugin_factory_collect_value (GValue* value, guint n_collect_values, GTypeCValue* collect_values, guint collect_flags) {
	if (collect_values[0].v_pointer) {
		ExternalPluginFactory* object;
		object = collect_values[0].v_pointer;
		if (object->parent_instance.g_class == NULL) {
			return g_strconcat ("invalid unclassed object pointer for value type `", G_VALUE_TYPE_NAME (value), "'", NULL);
		} else if (!g_value_type_compatible (G_TYPE_FROM_INSTANCE (object), G_VALUE_TYPE (value))) {
			return g_strconcat ("invalid object type `", g_type_name (G_TYPE_FROM_INSTANCE (object)), "' for value type `", G_VALUE_TYPE_NAME (value), "'", NULL);
		}
		value->data[0].v_pointer = external_plugin_factory_ref (object);
	} else {
		value->data[0].v_pointer = NULL;
	}
	return NULL;
}


static gchar* value_external_plugin_factory_lcopy_value (const GValue* value, guint n_collect_values, GTypeCValue* collect_values, guint collect_flags) {
	ExternalPluginFactory** object_p;
	object_p = collect_values[0].v_pointer;
	if (!object_p) {
		return g_strdup_printf ("value location for `%s' passed as NULL", G_VALUE_TYPE_NAME (value));
	}
	if (!value->data[0].v_pointer) {
		*object_p = NULL;
	} else if (collect_flags && G_VALUE_NOCOPY_CONTENTS) {
		*object_p = value->data[0].v_pointer;
	} else {
		*object_p = external_plugin_factory_ref (value->data[0].v_pointer);
	}
	return NULL;
}


GParamSpec* param_spec_external_plugin_factory (const gchar* name, const gchar* nick, const gchar* blurb, GType object_type, GParamFlags flags) {
	ParamSpecExternalPluginFactory* spec;
	g_return_val_if_fail (g_type_is_a (object_type, TYPE_EXTERNAL_PLUGIN_FACTORY), NULL);
	spec = g_param_spec_internal (G_TYPE_PARAM_OBJECT, name, nick, blurb, flags);
	G_PARAM_SPEC (spec)->value_type = object_type;
	return G_PARAM_SPEC (spec);
}


gpointer value_get_external_plugin_factory (const GValue* value) {
	g_return_val_if_fail (G_TYPE_CHECK_VALUE_TYPE (value, TYPE_EXTERNAL_PLUGIN_FACTORY), NULL);
	return value->data[0].v_pointer;
}


void value_set_external_plugin_factory (GValue* value, gpointer v_object) {
	ExternalPluginFactory* old;
	g_return_if_fail (G_TYPE_CHECK_VALUE_TYPE (value, TYPE_EXTERNAL_PLUGIN_FACTORY));
	old = value->data[0].v_pointer;
	if (v_object) {
		g_return_if_fail (G_TYPE_CHECK_INSTANCE_TYPE (v_object, TYPE_EXTERNAL_PLUGIN_FACTORY));
		g_return_if_fail (g_value_type_compatible (G_TYPE_FROM_INSTANCE (v_object), G_VALUE_TYPE (value)));
		value->data[0].v_pointer = v_object;
		external_plugin_factory_ref (value->data[0].v_pointer);
	} else {
		value->data[0].v_pointer = NULL;
	}
	if (old) {
		external_plugin_factory_unref (old);
	}
}


static void external_plugin_factory_class_init (ExternalPluginFactoryClass * klass) {
	external_plugin_factory_parent_class = g_type_class_peek_parent (klass);
	EXTERNAL_PLUGIN_FACTORY_CLASS (klass)->finalize = external_plugin_factory_finalize;
	g_type_class_add_private (klass, sizeof (ExternalPluginFactoryPrivate));
}


static void external_plugin_factory_instance_init (ExternalPluginFactory * self) {
	self->priv = EXTERNAL_PLUGIN_FACTORY_GET_PRIVATE (self);
	self->ref_count = 1;
}


static void external_plugin_factory_finalize (ExternalPluginFactory* obj) {
	ExternalPluginFactory * self;
	self = EXTERNAL_PLUGIN_FACTORY (obj);
	(self->priv->dbus_obj == NULL) ? NULL : (self->priv->dbus_obj = (g_object_unref (self->priv->dbus_obj), NULL));
	(self->priv->connection == NULL) ? NULL : (self->priv->connection = (dbus_g_connection_unref (self->priv->connection), NULL));
	(self->priv->loader == NULL) ? NULL : (self->priv->loader = (g_object_unref (self->priv->loader), NULL));
}


GType external_plugin_factory_get_type (void) {
	static GType external_plugin_factory_type_id = 0;
	if (external_plugin_factory_type_id == 0) {
		static const GTypeValueTable g_define_type_value_table = { value_external_plugin_factory_init, value_external_plugin_factory_free_value, value_external_plugin_factory_copy_value, value_external_plugin_factory_peek_pointer, "p", value_external_plugin_factory_collect_value, "p", value_external_plugin_factory_lcopy_value };
		static const GTypeInfo g_define_type_info = { sizeof (ExternalPluginFactoryClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) external_plugin_factory_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (ExternalPluginFactory), 0, (GInstanceInitFunc) external_plugin_factory_instance_init, &g_define_type_value_table };
		static const GTypeFundamentalInfo g_define_type_fundamental_info = { (G_TYPE_FLAG_CLASSED | G_TYPE_FLAG_INSTANTIATABLE | G_TYPE_FLAG_DERIVABLE | G_TYPE_FLAG_DEEP_DERIVABLE) };
		external_plugin_factory_type_id = g_type_register_fundamental (g_type_fundamental_next (), "ExternalPluginFactory", &g_define_type_info, &g_define_type_fundamental_info, 0);
	}
	return external_plugin_factory_type_id;
}


gpointer external_plugin_factory_ref (gpointer instance) {
	ExternalPluginFactory* self;
	self = instance;
	g_atomic_int_inc (&self->ref_count);
	return instance;
}


void external_plugin_factory_unref (gpointer instance) {
	ExternalPluginFactory* self;
	self = instance;
	if (g_atomic_int_dec_and_test (&self->ref_count)) {
		EXTERNAL_PLUGIN_FACTORY_GET_CLASS (self)->finalize (self);
		g_type_free_instance ((GTypeInstance *) self);
	}
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



static void g_cclosure_user_marshal_VOID__STRING_STRING_STRING (GClosure * closure, GValue * return_value, guint n_param_values, const GValue * param_values, gpointer invocation_hint, gpointer marshal_data) {
	typedef void (*GMarshalFunc_VOID__STRING_STRING_STRING) (gpointer data1, const char* arg_1, const char* arg_2, const char* arg_3, gpointer data2);
	register GMarshalFunc_VOID__STRING_STRING_STRING callback;
	register GCClosure * cc;
	register gpointer data1, data2;
	cc = (GCClosure *) closure;
	g_return_if_fail (n_param_values == 4);
	if (G_CCLOSURE_SWAP_DATA (closure)) {
		data1 = closure->data;
		data2 = param_values->data[0].v_pointer;
	} else {
		data1 = param_values->data[0].v_pointer;
		data2 = closure->data;
	}
	callback = (GMarshalFunc_VOID__STRING_STRING_STRING) (marshal_data ? marshal_data : cc->callback);
	callback (data1, g_value_get_string (param_values + 1), g_value_get_string (param_values + 2), g_value_get_string (param_values + 3), data2);
}



