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
#include <gee/hashmap.h>
#include <stdlib.h>
#include <string.h>
#include <libgupnp/gupnp.h>
#include <gmodule.h>
#include <gio/gio.h>
#include <gee/map.h>
#include <gee/arraylist.h>
#include <gee/collection.h>


#define RYGEL_TYPE_PLUGIN_LOADER (rygel_plugin_loader_get_type ())
#define RYGEL_PLUGIN_LOADER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_PLUGIN_LOADER, RygelPluginLoader))
#define RYGEL_PLUGIN_LOADER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_PLUGIN_LOADER, RygelPluginLoaderClass))
#define RYGEL_IS_PLUGIN_LOADER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_PLUGIN_LOADER))
#define RYGEL_IS_PLUGIN_LOADER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_PLUGIN_LOADER))
#define RYGEL_PLUGIN_LOADER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_PLUGIN_LOADER, RygelPluginLoaderClass))

typedef struct _RygelPluginLoader RygelPluginLoader;
typedef struct _RygelPluginLoaderClass RygelPluginLoaderClass;
typedef struct _RygelPluginLoaderPrivate RygelPluginLoaderPrivate;

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

/**
 * Responsible for plugin loading. Probes for shared library files in a specific
 * directry and tries to grab a function with a specific name and signature,
 * calls it. The loaded module can then add plugins to Rygel by calling the
 * add_plugin method.
 */
struct _RygelPluginLoader {
	GObject parent_instance;
	RygelPluginLoaderPrivate * priv;
};

struct _RygelPluginLoaderClass {
	GObjectClass parent_class;
};

struct _RygelPluginLoaderPrivate {
	GeeHashMap* plugin_hash;
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

typedef void (*RygelPluginLoaderModuleInitFunc) (RygelPluginLoader* loader, void* user_data);


GType rygel_plugin_loader_get_type (void);
GType rygel_plugin_get_type (void);
#define RYGEL_PLUGIN_LOADER_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), RYGEL_TYPE_PLUGIN_LOADER, RygelPluginLoaderPrivate))
enum  {
	RYGEL_PLUGIN_LOADER_DUMMY_PROPERTY
};
RygelPluginLoader* rygel_plugin_loader_new (void);
RygelPluginLoader* rygel_plugin_loader_construct (GType object_type);
RygelPluginLoader* rygel_plugin_loader_new (void);
static gboolean rygel_plugin_loader_is_dir (GFile* file);
static void rygel_plugin_loader_load_modules_from_dir (RygelPluginLoader* self, GFile* dir);
void rygel_plugin_loader_load_plugins (RygelPluginLoader* self);
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
void rygel_plugin_loader_add_plugin (RygelPluginLoader* self, RygelPlugin* plugin);
RygelPlugin* rygel_plugin_loader_get_plugin_by_name (RygelPluginLoader* self, const char* name);
GeeCollection* rygel_plugin_loader_list_plugins (RygelPluginLoader* self);
static void rygel_plugin_loader_on_children_enumerated (RygelPluginLoader* self, GObject* source_object, GAsyncResult* res);
static void _rygel_plugin_loader_on_children_enumerated_gasync_ready_callback (GObject* source_object, GAsyncResult* res, gpointer self);
static void rygel_plugin_loader_on_next_files_enumerated (RygelPluginLoader* self, GObject* source_object, GAsyncResult* res);
static void _rygel_plugin_loader_on_next_files_enumerated_gasync_ready_callback (GObject* source_object, GAsyncResult* res, gpointer self);
static void _g_list_free_g_object_unref (GList* self);
static void rygel_plugin_loader_load_module_from_file (RygelPluginLoader* self, const char* file_path);
static gpointer rygel_plugin_loader_parent_class = NULL;
static void rygel_plugin_loader_finalize (GObject* obj);
static int _vala_strcmp0 (const char * str1, const char * str2);



RygelPluginLoader* rygel_plugin_loader_construct (GType object_type) {
	RygelPluginLoader * self;
	GeeHashMap* _tmp0_;
	self = g_object_newv (object_type, 0, NULL);
	_tmp0_ = NULL;
	self->priv->plugin_hash = (_tmp0_ = gee_hash_map_new (G_TYPE_STRING, (GBoxedCopyFunc) g_strdup, g_free, RYGEL_TYPE_PLUGIN, (GBoxedCopyFunc) g_object_ref, g_object_unref, g_str_hash, g_str_equal, g_direct_equal), (self->priv->plugin_hash == NULL) ? NULL : (self->priv->plugin_hash = (g_object_unref (self->priv->plugin_hash), NULL)), _tmp0_);
	return self;
}


RygelPluginLoader* rygel_plugin_loader_new (void) {
	return rygel_plugin_loader_construct (RYGEL_TYPE_PLUGIN_LOADER);
}


/* Plugin loading functions*/
void rygel_plugin_loader_load_plugins (RygelPluginLoader* self) {
	GFile* dir;
	gboolean _tmp0_;
	g_return_if_fail (self != NULL);
	g_assert (g_module_supported ());
	dir = g_file_new_for_path (PLUGIN_DIR);
	_tmp0_ = FALSE;
	if (dir != NULL) {
		_tmp0_ = rygel_plugin_loader_is_dir (dir);
	} else {
		_tmp0_ = FALSE;
	}
	g_assert (_tmp0_);
	rygel_plugin_loader_load_modules_from_dir (self, dir);
	(dir == NULL) ? NULL : (dir = (g_object_unref (dir), NULL));
}


void rygel_plugin_loader_add_plugin (RygelPluginLoader* self, RygelPlugin* plugin) {
	g_return_if_fail (self != NULL);
	g_return_if_fail (plugin != NULL);
	gee_map_set ((GeeMap*) self->priv->plugin_hash, plugin->name, plugin);
	g_debug ("rygel-plugin-loader.vala:59: New plugin '%s' available", plugin->name);
	g_signal_emit_by_name (self, "plugin-available", plugin);
}


RygelPlugin* rygel_plugin_loader_get_plugin_by_name (RygelPluginLoader* self, const char* name) {
	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (name != NULL, NULL);
	return (RygelPlugin*) gee_map_get ((GeeMap*) self->priv->plugin_hash, name);
}


GeeCollection* rygel_plugin_loader_list_plugins (RygelPluginLoader* self) {
	g_return_val_if_fail (self != NULL, NULL);
	return gee_map_get_values ((GeeMap*) self->priv->plugin_hash);
}


static void _rygel_plugin_loader_on_children_enumerated_gasync_ready_callback (GObject* source_object, GAsyncResult* res, gpointer self) {
	rygel_plugin_loader_on_children_enumerated (self, source_object, res);
}


static void rygel_plugin_loader_load_modules_from_dir (RygelPluginLoader* self, GFile* dir) {
	char* attributes;
	g_return_if_fail (self != NULL);
	g_return_if_fail (dir != NULL);
	attributes = g_strdup (G_FILE_ATTRIBUTE_STANDARD_NAME "," G_FILE_ATTRIBUTE_STANDARD_TYPE "," G_FILE_ATTRIBUTE_STANDARD_CONTENT_TYPE);
	g_file_enumerate_children_async (dir, attributes, G_FILE_QUERY_INFO_NONE, G_PRIORITY_DEFAULT, NULL, _rygel_plugin_loader_on_children_enumerated_gasync_ready_callback, self);
	attributes = (g_free (attributes), NULL);
}


static void _rygel_plugin_loader_on_next_files_enumerated_gasync_ready_callback (GObject* source_object, GAsyncResult* res, gpointer self) {
	rygel_plugin_loader_on_next_files_enumerated (self, source_object, res);
}


static void rygel_plugin_loader_on_children_enumerated (RygelPluginLoader* self, GObject* source_object, GAsyncResult* res) {
	GError * _inner_error_;
	GFile* _tmp0_;
	GFile* dir;
	GFileEnumerator* enumerator;
	g_return_if_fail (self != NULL);
	g_return_if_fail (source_object != NULL);
	g_return_if_fail (res != NULL);
	_inner_error_ = NULL;
	_tmp0_ = NULL;
	dir = (_tmp0_ = G_FILE (source_object), (_tmp0_ == NULL) ? NULL : g_object_ref (_tmp0_));
	enumerator = NULL;
	{
		GFileEnumerator* _tmp1_;
		GFileEnumerator* _tmp2_;
		_tmp1_ = g_file_enumerate_children_finish (dir, res, &_inner_error_);
		if (_inner_error_ != NULL) {
			goto __catch16_g_error;
			goto __finally16;
		}
		_tmp2_ = NULL;
		enumerator = (_tmp2_ = _tmp1_, (enumerator == NULL) ? NULL : (enumerator = (g_object_unref (enumerator), NULL)), _tmp2_);
	}
	goto __finally16;
	__catch16_g_error:
	{
		GError * _error_;
		_error_ = _inner_error_;
		_inner_error_ = NULL;
		{
			char* _tmp3_;
			_tmp3_ = NULL;
			g_critical ("rygel-plugin-loader.vala:91: Error listing contents of directory '%s': %s\n", _tmp3_ = g_file_get_path (dir), _error_->message);
			_tmp3_ = (g_free (_tmp3_), NULL);
			(_error_ == NULL) ? NULL : (_error_ = (g_error_free (_error_), NULL));
			(dir == NULL) ? NULL : (dir = (g_object_unref (dir), NULL));
			(enumerator == NULL) ? NULL : (enumerator = (g_object_unref (enumerator), NULL));
			return;
		}
	}
	__finally16:
	if (_inner_error_ != NULL) {
		(dir == NULL) ? NULL : (dir = (g_object_unref (dir), NULL));
		(enumerator == NULL) ? NULL : (enumerator = (g_object_unref (enumerator), NULL));
		g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, _inner_error_->message);
		g_clear_error (&_inner_error_);
		return;
	}
	g_file_enumerator_next_files_async (enumerator, G_MAXINT, G_PRIORITY_DEFAULT, NULL, _rygel_plugin_loader_on_next_files_enumerated_gasync_ready_callback, self);
	(dir == NULL) ? NULL : (dir = (g_object_unref (dir), NULL));
	(enumerator == NULL) ? NULL : (enumerator = (g_object_unref (enumerator), NULL));
}


static void _g_list_free_g_object_unref (GList* self) {
	g_list_foreach (self, (GFunc) g_object_unref, NULL);
	g_list_free (self);
}


static void rygel_plugin_loader_on_next_files_enumerated (RygelPluginLoader* self, GObject* source_object, GAsyncResult* res) {
	GError * _inner_error_;
	GFileEnumerator* _tmp0_;
	GFileEnumerator* enumerator;
	GFile* _tmp1_;
	GFile* dir;
	GList* infos;
	g_return_if_fail (self != NULL);
	g_return_if_fail (source_object != NULL);
	g_return_if_fail (res != NULL);
	_inner_error_ = NULL;
	_tmp0_ = NULL;
	enumerator = (_tmp0_ = G_FILE_ENUMERATOR (source_object), (_tmp0_ == NULL) ? NULL : g_object_ref (_tmp0_));
	_tmp1_ = NULL;
	dir = (_tmp1_ = G_FILE (g_file_enumerator_get_container (enumerator)), (_tmp1_ == NULL) ? NULL : g_object_ref (_tmp1_));
	infos = NULL;
	{
		GList* _tmp2_;
		GList* _tmp3_;
		_tmp2_ = g_file_enumerator_next_files_finish (enumerator, res, &_inner_error_);
		if (_inner_error_ != NULL) {
			goto __catch17_g_error;
			goto __finally17;
		}
		_tmp3_ = NULL;
		infos = (_tmp3_ = _tmp2_, (infos == NULL) ? NULL : (infos = (_g_list_free_g_object_unref (infos), NULL)), _tmp3_);
	}
	goto __finally17;
	__catch17_g_error:
	{
		GError * _error_;
		_error_ = _inner_error_;
		_inner_error_ = NULL;
		{
			char* _tmp4_;
			_tmp4_ = NULL;
			g_critical ("rygel-plugin-loader.vala:113: Error listing contents of directory '%s': %s\n", _tmp4_ = g_file_get_path (dir), _error_->message);
			_tmp4_ = (g_free (_tmp4_), NULL);
			(_error_ == NULL) ? NULL : (_error_ = (g_error_free (_error_), NULL));
			(enumerator == NULL) ? NULL : (enumerator = (g_object_unref (enumerator), NULL));
			(dir == NULL) ? NULL : (dir = (g_object_unref (dir), NULL));
			(infos == NULL) ? NULL : (infos = (_g_list_free_g_object_unref (infos), NULL));
			return;
		}
	}
	__finally17:
	if (_inner_error_ != NULL) {
		(enumerator == NULL) ? NULL : (enumerator = (g_object_unref (enumerator), NULL));
		(dir == NULL) ? NULL : (dir = (g_object_unref (dir), NULL));
		(infos == NULL) ? NULL : (infos = (_g_list_free_g_object_unref (infos), NULL));
		g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, _inner_error_->message);
		g_clear_error (&_inner_error_);
		return;
	}
	{
		GList* info_collection;
		GList* info_it;
		info_collection = infos;
		for (info_it = info_collection; info_it != NULL; info_it = info_it->next) {
			GFileInfo* _tmp9_;
			GFileInfo* info;
			_tmp9_ = NULL;
			info = (_tmp9_ = (GFileInfo*) info_it->data, (_tmp9_ == NULL) ? NULL : g_object_ref (_tmp9_));
			{
				const char* _tmp5_;
				char* file_name;
				char* _tmp6_;
				char* _tmp7_;
				char* file_path;
				GFile* file;
				GFileType file_type;
				const char* _tmp8_;
				char* content_type;
				const char* mime;
				_tmp5_ = NULL;
				file_name = (_tmp5_ = g_file_info_get_name (info), (_tmp5_ == NULL) ? NULL : g_strdup (_tmp5_));
				_tmp6_ = NULL;
				_tmp7_ = NULL;
				file_path = (_tmp7_ = g_build_filename (_tmp6_ = g_file_get_path (dir), file_name, NULL), _tmp6_ = (g_free (_tmp6_), NULL), _tmp7_);
				file = g_file_new_for_path (file_path);
				file_type = g_file_info_get_file_type (info);
				_tmp8_ = NULL;
				content_type = (_tmp8_ = g_file_info_get_content_type (info), (_tmp8_ == NULL) ? NULL : g_strdup (_tmp8_));
				mime = g_content_type_get_mime_type (content_type);
				if (file_type == G_FILE_TYPE_DIRECTORY) {
					/* Recurse into directories*/
					rygel_plugin_loader_load_modules_from_dir (self, file);
				} else {
					if (_vala_strcmp0 (mime, "application/x-sharedlib") == 0) {
						/* Seems like we found a module*/
						rygel_plugin_loader_load_module_from_file (self, file_path);
					}
				}
				(info == NULL) ? NULL : (info = (g_object_unref (info), NULL));
				file_name = (g_free (file_name), NULL);
				file_path = (g_free (file_path), NULL);
				(file == NULL) ? NULL : (file = (g_object_unref (file), NULL));
				content_type = (g_free (content_type), NULL);
			}
		}
	}
	(enumerator == NULL) ? NULL : (enumerator = (g_object_unref (enumerator), NULL));
	(dir == NULL) ? NULL : (dir = (g_object_unref (dir), NULL));
	(infos == NULL) ? NULL : (infos = (_g_list_free_g_object_unref (infos), NULL));
}


static void rygel_plugin_loader_load_module_from_file (RygelPluginLoader* self, const char* file_path) {
	GModule* module;
	void* function;
	RygelPluginLoaderModuleInitFunc _tmp0_;
	void* module_init_target;
	RygelPluginLoaderModuleInitFunc module_init;
	g_return_if_fail (self != NULL);
	g_return_if_fail (file_path != NULL);
	module = g_module_open (file_path, G_MODULE_BIND_LOCAL);
	if (module == NULL) {
		g_warning ("rygel-plugin-loader.vala:142: Failed to load module from path '%s' : %s\n", file_path, g_module_error ());
		(module == NULL) ? NULL : (module = (g_module_close (module), NULL));
		return;
	}
	function = NULL;
	if (!g_module_symbol (module, "module_init", &function)) {
		g_warning ("Failed to find entry point function 'module_init'" " in module loaded from path '%s': %s\n", file_path, g_module_error ());
		(module == NULL) ? NULL : (module = (g_module_close (module), NULL));
		return;
	}
	module_init_target = NULL;
	module_init = (_tmp0_ = (RygelPluginLoaderModuleInitFunc) function, module_init_target = NULL, _tmp0_);
	g_assert (module_init != NULL);
	/* We don't want our modules to ever unload*/
	g_module_make_resident (module);
	module_init (self, module_init_target);
	g_debug ("rygel-plugin-loader.vala:168: Loaded module source: '%s'\n", g_module_name (module));
	(module == NULL) ? NULL : (module = (g_module_close (module), NULL));
}


static gboolean rygel_plugin_loader_is_dir (GFile* file) {
	GError * _inner_error_;
	GFileInfo* file_info;
	gboolean _tmp4_;
	g_return_val_if_fail (file != NULL, FALSE);
	_inner_error_ = NULL;
	file_info = NULL;
	{
		GFileInfo* _tmp0_;
		GFileInfo* _tmp1_;
		_tmp0_ = g_file_query_info (file, G_FILE_ATTRIBUTE_STANDARD_TYPE, G_FILE_QUERY_INFO_NONE, NULL, &_inner_error_);
		if (_inner_error_ != NULL) {
			goto __catch18_g_error;
			goto __finally18;
		}
		_tmp1_ = NULL;
		file_info = (_tmp1_ = _tmp0_, (file_info == NULL) ? NULL : (file_info = (g_object_unref (file_info), NULL)), _tmp1_);
	}
	goto __finally18;
	__catch18_g_error:
	{
		GError * _error_;
		_error_ = _inner_error_;
		_inner_error_ = NULL;
		{
			char* _tmp2_;
			gboolean _tmp3_;
			_tmp2_ = NULL;
			g_critical ("rygel-plugin-loader.vala:179: Failed to query content type for '%s'\n", _tmp2_ = g_file_get_path (file));
			_tmp2_ = (g_free (_tmp2_), NULL);
			return (_tmp3_ = FALSE, (_error_ == NULL) ? NULL : (_error_ = (g_error_free (_error_), NULL)), (file_info == NULL) ? NULL : (file_info = (g_object_unref (file_info), NULL)), _tmp3_);
		}
	}
	__finally18:
	if (_inner_error_ != NULL) {
		(file_info == NULL) ? NULL : (file_info = (g_object_unref (file_info), NULL));
		g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, _inner_error_->message);
		g_clear_error (&_inner_error_);
		return FALSE;
	}
	return (_tmp4_ = g_file_info_get_file_type (file_info) == G_FILE_TYPE_DIRECTORY, (file_info == NULL) ? NULL : (file_info = (g_object_unref (file_info), NULL)), _tmp4_);
}


static void rygel_plugin_loader_class_init (RygelPluginLoaderClass * klass) {
	rygel_plugin_loader_parent_class = g_type_class_peek_parent (klass);
	g_type_class_add_private (klass, sizeof (RygelPluginLoaderPrivate));
	G_OBJECT_CLASS (klass)->finalize = rygel_plugin_loader_finalize;
	g_signal_new ("plugin_available", RYGEL_TYPE_PLUGIN_LOADER, G_SIGNAL_RUN_LAST, 0, NULL, NULL, g_cclosure_marshal_VOID__OBJECT, G_TYPE_NONE, 1, RYGEL_TYPE_PLUGIN);
}


static void rygel_plugin_loader_instance_init (RygelPluginLoader * self) {
	self->priv = RYGEL_PLUGIN_LOADER_GET_PRIVATE (self);
}


static void rygel_plugin_loader_finalize (GObject* obj) {
	RygelPluginLoader * self;
	self = RYGEL_PLUGIN_LOADER (obj);
	(self->priv->plugin_hash == NULL) ? NULL : (self->priv->plugin_hash = (g_object_unref (self->priv->plugin_hash), NULL));
	G_OBJECT_CLASS (rygel_plugin_loader_parent_class)->finalize (obj);
}


GType rygel_plugin_loader_get_type (void) {
	static GType rygel_plugin_loader_type_id = 0;
	if (rygel_plugin_loader_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (RygelPluginLoaderClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) rygel_plugin_loader_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (RygelPluginLoader), 0, (GInstanceInitFunc) rygel_plugin_loader_instance_init, NULL };
		rygel_plugin_loader_type_id = g_type_register_static (G_TYPE_OBJECT, "RygelPluginLoader", &g_define_type_info, 0);
	}
	return rygel_plugin_loader_type_id;
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




