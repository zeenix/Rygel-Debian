/*
 * Copyright (C) 2008 Nokia Corporation, all rights reserved.
 * Copyright (C) 2008 Zeeshan Ali (Khattak) <zeeshanak@gnome.org>.
 *
 * Author: Zeeshan Ali (Khattak) <zeeshanak@gnome.org>
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
#include <gee/arraylist.h>
#include <libgupnp/gupnp.h>
#include <glib/gi18n-lib.h>
#include <cstuff.h>
#include <gee/collection.h>
#include <stdlib.h>
#include <string.h>
#include <gee/iterable.h>
#include <gee/iterator.h>
#include <gst/gst.h>


#define RYGEL_TYPE_MAIN (rygel_main_get_type ())
#define RYGEL_MAIN(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_MAIN, RygelMain))
#define RYGEL_MAIN_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_MAIN, RygelMainClass))
#define RYGEL_IS_MAIN(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_MAIN))
#define RYGEL_IS_MAIN_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_MAIN))
#define RYGEL_MAIN_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_MAIN, RygelMainClass))

typedef struct _RygelMain RygelMain;
typedef struct _RygelMainClass RygelMainClass;
typedef struct _RygelMainPrivate RygelMainPrivate;

#define RYGEL_TYPE_PLUGIN_LOADER (rygel_plugin_loader_get_type ())
#define RYGEL_PLUGIN_LOADER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_PLUGIN_LOADER, RygelPluginLoader))
#define RYGEL_PLUGIN_LOADER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_PLUGIN_LOADER, RygelPluginLoaderClass))
#define RYGEL_IS_PLUGIN_LOADER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_PLUGIN_LOADER))
#define RYGEL_IS_PLUGIN_LOADER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_PLUGIN_LOADER))
#define RYGEL_PLUGIN_LOADER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_PLUGIN_LOADER, RygelPluginLoaderClass))

typedef struct _RygelPluginLoader RygelPluginLoader;
typedef struct _RygelPluginLoaderClass RygelPluginLoaderClass;

#define RYGEL_TYPE_MEDIA_SERVER_FACTORY (rygel_media_server_factory_get_type ())
#define RYGEL_MEDIA_SERVER_FACTORY(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_MEDIA_SERVER_FACTORY, RygelMediaServerFactory))
#define RYGEL_MEDIA_SERVER_FACTORY_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_MEDIA_SERVER_FACTORY, RygelMediaServerFactoryClass))
#define RYGEL_IS_MEDIA_SERVER_FACTORY(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_MEDIA_SERVER_FACTORY))
#define RYGEL_IS_MEDIA_SERVER_FACTORY_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_MEDIA_SERVER_FACTORY))
#define RYGEL_MEDIA_SERVER_FACTORY_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_MEDIA_SERVER_FACTORY, RygelMediaServerFactoryClass))

typedef struct _RygelMediaServerFactory RygelMediaServerFactory;
typedef struct _RygelMediaServerFactoryClass RygelMediaServerFactoryClass;

#define RYGEL_TYPE_MEDIA_SERVER (rygel_media_server_get_type ())
#define RYGEL_MEDIA_SERVER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_MEDIA_SERVER, RygelMediaServer))
#define RYGEL_MEDIA_SERVER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_MEDIA_SERVER, RygelMediaServerClass))
#define RYGEL_IS_MEDIA_SERVER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_MEDIA_SERVER))
#define RYGEL_IS_MEDIA_SERVER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_MEDIA_SERVER))
#define RYGEL_MEDIA_SERVER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_MEDIA_SERVER, RygelMediaServerClass))

typedef struct _RygelMediaServer RygelMediaServer;
typedef struct _RygelMediaServerClass RygelMediaServerClass;

#define RYGEL_TYPE_PLUGIN (rygel_plugin_get_type ())
#define RYGEL_PLUGIN(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_PLUGIN, RygelPlugin))
#define RYGEL_PLUGIN_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_PLUGIN, RygelPluginClass))
#define RYGEL_IS_PLUGIN(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_PLUGIN))
#define RYGEL_IS_PLUGIN_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_PLUGIN))
#define RYGEL_PLUGIN_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_PLUGIN, RygelPluginClass))

typedef struct _RygelPlugin RygelPlugin;
typedef struct _RygelPluginClass RygelPluginClass;
typedef struct _RygelPluginPrivate RygelPluginPrivate;

#define RYGEL_TYPE_RESOURCE_INFO (rygel_resource_info_get_type ())
#define RYGEL_RESOURCE_INFO(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_RESOURCE_INFO, RygelResourceInfo))
#define RYGEL_RESOURCE_INFO_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_RESOURCE_INFO, RygelResourceInfoClass))
#define RYGEL_IS_RESOURCE_INFO(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_RESOURCE_INFO))
#define RYGEL_IS_RESOURCE_INFO_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_RESOURCE_INFO))
#define RYGEL_RESOURCE_INFO_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_RESOURCE_INFO, RygelResourceInfoClass))

typedef struct _RygelResourceInfo RygelResourceInfo;
typedef struct _RygelResourceInfoClass RygelResourceInfoClass;

#define RYGEL_TYPE_ICON_INFO (rygel_icon_info_get_type ())
#define RYGEL_ICON_INFO(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_ICON_INFO, RygelIconInfo))
#define RYGEL_ICON_INFO_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_ICON_INFO, RygelIconInfoClass))
#define RYGEL_IS_ICON_INFO(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_ICON_INFO))
#define RYGEL_IS_ICON_INFO_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_ICON_INFO))
#define RYGEL_ICON_INFO_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_ICON_INFO, RygelIconInfoClass))

typedef struct _RygelIconInfo RygelIconInfo;
typedef struct _RygelIconInfoClass RygelIconInfoClass;

struct _RygelMain {
	GObject parent_instance;
	RygelMainPrivate * priv;
};

struct _RygelMainClass {
	GObjectClass parent_class;
};

struct _RygelMainPrivate {
	RygelPluginLoader* plugin_loader;
	RygelMediaServerFactory* ms_factory;
	GeeArrayList* media_servers;
	GMainLoop* main_loop;
	gint exit_code;
};

/**
 * Represents a Rygel plugin. Plugins are supposed to provide an object of this
 * class or a subclass.
 */
struct _RygelPlugin {
	GUPnPResourceFactory parent_instance;
	RygelPluginPrivate * priv;
	char* name;
	char* title;
	GeeArrayList* resource_infos;
	GeeArrayList* icon_infos;
};

struct _RygelPluginClass {
	GUPnPResourceFactoryClass parent_class;
};



GType rygel_main_get_type (void);
GType rygel_plugin_loader_get_type (void);
gpointer rygel_media_server_factory_ref (gpointer instance);
void rygel_media_server_factory_unref (gpointer instance);
GParamSpec* rygel_param_spec_media_server_factory (const gchar* name, const gchar* nick, const gchar* blurb, GType object_type, GParamFlags flags);
void rygel_value_set_media_server_factory (GValue* value, gpointer v_object);
gpointer rygel_value_get_media_server_factory (const GValue* value);
GType rygel_media_server_factory_get_type (void);
GType rygel_media_server_get_type (void);
#define RYGEL_MAIN_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), RYGEL_TYPE_MAIN, RygelMainPrivate))
enum  {
	RYGEL_MAIN_DUMMY_PROPERTY
};
RygelPluginLoader* rygel_plugin_loader_new (void);
RygelPluginLoader* rygel_plugin_loader_construct (GType object_type);
RygelMediaServerFactory* rygel_media_server_factory_new (GError** error);
RygelMediaServerFactory* rygel_media_server_factory_construct (GType object_type, GError** error);
GType rygel_plugin_get_type (void);
static void rygel_main_on_plugin_loaded (RygelMain* self, RygelPluginLoader* plugin_loader, RygelPlugin* plugin);
static void _rygel_main_on_plugin_loaded_rygel_plugin_loader_plugin_available (RygelPluginLoader* _sender, RygelPlugin* plugin, gpointer self);
static void rygel_main_application_exit_cb (RygelMain* self);
static void _rygel_main_application_exit_cb_cstuff_utils_application_exit_cb (gpointer self);
RygelMain* rygel_main_new (GError** error);
RygelMain* rygel_main_construct (GType object_type, GError** error);
RygelMain* rygel_main_new (GError** error);
void rygel_plugin_loader_load_plugins (RygelPluginLoader* self);
gint rygel_main_run (RygelMain* self);
void rygel_main_exit (RygelMain* self, gint exit_code);
RygelMediaServer* rygel_media_server_factory_create_media_server (RygelMediaServerFactory* self, RygelPlugin* plugin, GError** error);
gboolean rygel_plugin_get_available (RygelPlugin* self);
static void rygel_main_on_plugin_notify (RygelMain* self, RygelPlugin* plugin, GParamSpec* spec);
static void _rygel_main_on_plugin_notify_g_object_notify (RygelPlugin* _sender, GParamSpec* pspec, gpointer self);
gpointer rygel_resource_info_ref (gpointer instance);
void rygel_resource_info_unref (gpointer instance);
GParamSpec* rygel_param_spec_resource_info (const gchar* name, const gchar* nick, const gchar* blurb, GType object_type, GParamFlags flags);
void rygel_value_set_resource_info (GValue* value, gpointer v_object);
gpointer rygel_value_get_resource_info (const GValue* value);
GType rygel_resource_info_get_type (void);
gpointer rygel_icon_info_ref (gpointer instance);
void rygel_icon_info_unref (gpointer instance);
GParamSpec* rygel_param_spec_icon_info (const gchar* name, const gchar* nick, const gchar* blurb, GType object_type, GParamFlags flags);
void rygel_value_set_icon_info (GValue* value, gpointer v_object);
gpointer rygel_value_get_icon_info (const GValue* value);
GType rygel_icon_info_get_type (void);
gint rygel_main_main (char** args, int args_length1);
static gpointer rygel_main_parent_class = NULL;
static void rygel_main_finalize (GObject* obj);



static void _rygel_main_on_plugin_loaded_rygel_plugin_loader_plugin_available (RygelPluginLoader* _sender, RygelPlugin* plugin, gpointer self) {
	rygel_main_on_plugin_loaded (self, _sender, plugin);
}


static void _rygel_main_application_exit_cb_cstuff_utils_application_exit_cb (gpointer self) {
	rygel_main_application_exit_cb (self);
}


RygelMain* rygel_main_construct (GType object_type, GError** error) {
	GError * _inner_error_;
	RygelMain * self;
	GeeArrayList* _tmp0_;
	RygelPluginLoader* _tmp1_;
	RygelMediaServerFactory* _tmp2_;
	GMainLoop* _tmp3_;
	_inner_error_ = NULL;
	self = g_object_newv (object_type, 0, NULL);
	g_set_application_name (_ (PACKAGE_NAME));
	_tmp0_ = NULL;
	self->priv->media_servers = (_tmp0_ = gee_array_list_new (RYGEL_TYPE_MEDIA_SERVER, (GBoxedCopyFunc) g_object_ref, g_object_unref, g_direct_equal), (self->priv->media_servers == NULL) ? NULL : (self->priv->media_servers = (g_object_unref (self->priv->media_servers), NULL)), _tmp0_);
	_tmp1_ = NULL;
	self->priv->plugin_loader = (_tmp1_ = rygel_plugin_loader_new (), (self->priv->plugin_loader == NULL) ? NULL : (self->priv->plugin_loader = (g_object_unref (self->priv->plugin_loader), NULL)), _tmp1_);
	_tmp2_ = NULL;
	self->priv->ms_factory = (_tmp2_ = rygel_media_server_factory_new (&_inner_error_), (self->priv->ms_factory == NULL) ? NULL : (self->priv->ms_factory = (rygel_media_server_factory_unref (self->priv->ms_factory), NULL)), _tmp2_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		return;
	}
	_tmp3_ = NULL;
	self->priv->main_loop = (_tmp3_ = g_main_loop_new (NULL, FALSE), (self->priv->main_loop == NULL) ? NULL : (self->priv->main_loop = (g_main_loop_unref (self->priv->main_loop), NULL)), _tmp3_);
	self->priv->exit_code = 0;
	g_signal_connect_object (self->priv->plugin_loader, "plugin-available", (GCallback) _rygel_main_on_plugin_loaded_rygel_plugin_loader_plugin_available, self, 0);
	on_application_exit (_rygel_main_application_exit_cb_cstuff_utils_application_exit_cb, self);
	return self;
}


RygelMain* rygel_main_new (GError** error) {
	return rygel_main_construct (RYGEL_TYPE_MAIN, error);
}


gint rygel_main_run (RygelMain* self) {
	g_return_val_if_fail (self != NULL, 0);
	rygel_plugin_loader_load_plugins (self->priv->plugin_loader);
	g_main_loop_run (self->priv->main_loop);
	return self->priv->exit_code;
}


void rygel_main_exit (RygelMain* self, gint exit_code) {
	g_return_if_fail (self != NULL);
	self->priv->exit_code = exit_code;
	g_main_loop_quit (self->priv->main_loop);
}


static void rygel_main_application_exit_cb (RygelMain* self) {
	g_return_if_fail (self != NULL);
	rygel_main_exit (self, 0);
}


static void _rygel_main_on_plugin_notify_g_object_notify (RygelPlugin* _sender, GParamSpec* pspec, gpointer self) {
	rygel_main_on_plugin_notify (self, _sender, pspec);
}


static void rygel_main_on_plugin_loaded (RygelMain* self, RygelPluginLoader* plugin_loader, RygelPlugin* plugin) {
	GError * _inner_error_;
	g_return_if_fail (self != NULL);
	g_return_if_fail (plugin_loader != NULL);
	g_return_if_fail (plugin != NULL);
	_inner_error_ = NULL;
	{
		RygelMediaServer* server;
		server = rygel_media_server_factory_create_media_server (self->priv->ms_factory, plugin, &_inner_error_);
		if (_inner_error_ != NULL) {
			goto __catch24_g_error;
			goto __finally24;
		}
		gupnp_root_device_set_available ((GUPnPRootDevice*) server, rygel_plugin_get_available (plugin));
		gee_collection_add ((GeeCollection*) self->priv->media_servers, server);
		g_signal_connect_object ((GObject*) plugin, "notify::available", (GCallback) _rygel_main_on_plugin_notify_g_object_notify, self, 0);
		(server == NULL) ? NULL : (server = (g_object_unref (server), NULL));
	}
	goto __finally24;
	__catch24_g_error:
	{
		GError * _error_;
		_error_ = _inner_error_;
		_inner_error_ = NULL;
		{
			g_warning ("rygel-main.vala:81: Failed to create MediaServer for %s. Reason: %s\n", plugin->name, _error_->message);
			(_error_ == NULL) ? NULL : (_error_ = (g_error_free (_error_), NULL));
		}
	}
	__finally24:
	if (_inner_error_ != NULL) {
		g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, _inner_error_->message);
		g_clear_error (&_inner_error_);
		return;
	}
}


static void rygel_main_on_plugin_notify (RygelMain* self, RygelPlugin* plugin, GParamSpec* spec) {
	g_return_if_fail (self != NULL);
	g_return_if_fail (plugin != NULL);
	g_return_if_fail (spec != NULL);
	{
		GeeIterator* _server_it;
		_server_it = gee_iterable_iterator ((GeeIterable*) self->priv->media_servers);
		while (gee_iterator_next (_server_it)) {
			RygelMediaServer* server;
			server = (RygelMediaServer*) gee_iterator_get (_server_it);
			if (gupnp_device_info_get_resource_factory ((GUPnPDeviceInfo*) server) == GUPNP_RESOURCE_FACTORY (plugin)) {
				gupnp_root_device_set_available ((GUPnPRootDevice*) server, rygel_plugin_get_available (plugin));
			}
			(server == NULL) ? NULL : (server = (g_object_unref (server), NULL));
		}
		(_server_it == NULL) ? NULL : (_server_it = (g_object_unref (_server_it), NULL));
	}
}


gint rygel_main_main (char** args, int args_length1) {
	GError * _inner_error_;
	RygelMain* main;
	gint exit_code;
	gint _tmp2_;
	_inner_error_ = NULL;
	main = NULL;
	/* initialize gstreamer*/
	gst_init (&args_length1, &args);
	{
		RygelMain* _tmp0_;
		_tmp0_ = NULL;
		main = (_tmp0_ = rygel_main_new (&_inner_error_), (main == NULL) ? NULL : (main = (g_object_unref (main), NULL)), _tmp0_);
		if (_inner_error_ != NULL) {
			goto __catch25_g_error;
			goto __finally25;
		}
	}
	goto __finally25;
	__catch25_g_error:
	{
		GError * err;
		err = _inner_error_;
		_inner_error_ = NULL;
		{
			gint _tmp1_;
			g_error ("rygel-main.vala:105: %s", err->message);
			return (_tmp1_ = -1, (err == NULL) ? NULL : (err = (g_error_free (err), NULL)), (main == NULL) ? NULL : (main = (g_object_unref (main), NULL)), _tmp1_);
		}
	}
	__finally25:
	if (_inner_error_ != NULL) {
		(main == NULL) ? NULL : (main = (g_object_unref (main), NULL));
		g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, _inner_error_->message);
		g_clear_error (&_inner_error_);
		return 0;
	}
	exit_code = rygel_main_run (main);
	return (_tmp2_ = exit_code, (main == NULL) ? NULL : (main = (g_object_unref (main), NULL)), _tmp2_);
}


int main (int argc, char ** argv) {
	g_type_init ();
	return rygel_main_main (argv, argc);
}


static void rygel_main_class_init (RygelMainClass * klass) {
	rygel_main_parent_class = g_type_class_peek_parent (klass);
	g_type_class_add_private (klass, sizeof (RygelMainPrivate));
	G_OBJECT_CLASS (klass)->finalize = rygel_main_finalize;
}


static void rygel_main_instance_init (RygelMain * self) {
	self->priv = RYGEL_MAIN_GET_PRIVATE (self);
}


static void rygel_main_finalize (GObject* obj) {
	RygelMain * self;
	self = RYGEL_MAIN (obj);
	(self->priv->plugin_loader == NULL) ? NULL : (self->priv->plugin_loader = (g_object_unref (self->priv->plugin_loader), NULL));
	(self->priv->ms_factory == NULL) ? NULL : (self->priv->ms_factory = (rygel_media_server_factory_unref (self->priv->ms_factory), NULL));
	(self->priv->media_servers == NULL) ? NULL : (self->priv->media_servers = (g_object_unref (self->priv->media_servers), NULL));
	(self->priv->main_loop == NULL) ? NULL : (self->priv->main_loop = (g_main_loop_unref (self->priv->main_loop), NULL));
	G_OBJECT_CLASS (rygel_main_parent_class)->finalize (obj);
}


GType rygel_main_get_type (void) {
	static GType rygel_main_type_id = 0;
	if (rygel_main_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (RygelMainClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) rygel_main_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (RygelMain), 0, (GInstanceInitFunc) rygel_main_instance_init, NULL };
		rygel_main_type_id = g_type_register_static (G_TYPE_OBJECT, "RygelMain", &g_define_type_info, 0);
	}
	return rygel_main_type_id;
}




