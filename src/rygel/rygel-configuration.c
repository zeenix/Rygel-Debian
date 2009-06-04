/*
 * Copyright (C) 2008,2009 Nokia Corporation, all rights reserved.
 * Copyright (C) 2008,2009 Zeeshan Ali (Khattak) <zeeshanak@gnome.org>.
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
#include <gconf/gconf-client.h>
#include <stdlib.h>
#include <string.h>
#include <gee/arraylist.h>
#include <gconf/gconf.h>
#include <gee/collection.h>
#include <gee/iterable.h>
#include <gee/iterator.h>


#define RYGEL_TYPE_CONFIGURATION (rygel_configuration_get_type ())
#define RYGEL_CONFIGURATION(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_CONFIGURATION, RygelConfiguration))
#define RYGEL_CONFIGURATION_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_CONFIGURATION, RygelConfigurationClass))
#define RYGEL_IS_CONFIGURATION(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_CONFIGURATION))
#define RYGEL_IS_CONFIGURATION_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_CONFIGURATION))
#define RYGEL_CONFIGURATION_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_CONFIGURATION, RygelConfigurationClass))

typedef struct _RygelConfiguration RygelConfiguration;
typedef struct _RygelConfigurationClass RygelConfigurationClass;
typedef struct _RygelConfigurationPrivate RygelConfigurationPrivate;

/**
 * Reads the user configuration for Rygel.
 */
struct _RygelConfiguration {
	GObject parent_instance;
	RygelConfigurationPrivate * priv;
	GConfClient* gconf;
};

struct _RygelConfigurationClass {
	GObjectClass parent_class;
};

struct _RygelConfigurationPrivate {
	char* _host_ip;
};



GType rygel_configuration_get_type (void);
#define RYGEL_CONFIGURATION_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), RYGEL_TYPE_CONFIGURATION, RygelConfigurationPrivate))
enum  {
	RYGEL_CONFIGURATION_DUMMY_PROPERTY,
	RYGEL_CONFIGURATION_HOST_IP,
	RYGEL_CONFIGURATION_PORT,
	RYGEL_CONFIGURATION_TRANSCODING,
	RYGEL_CONFIGURATION_MP3_TRANSCODER,
	RYGEL_CONFIGURATION_MP2TS_TRANSCODER,
	RYGEL_CONFIGURATION_LPCM_TRANSCODER
};
static RygelConfiguration* rygel_configuration_config;
static RygelConfiguration* rygel_configuration_config = NULL;
#define RYGEL_CONFIGURATION_ROOT_GCONF_PATH "/apps/rygel/"
#define RYGEL_CONFIGURATION_IP_KEY "host-ip"
#define RYGEL_CONFIGURATION_PORT_KEY "port"
#define RYGEL_CONFIGURATION_ENABLED_KEY "enabled"
#define RYGEL_CONFIGURATION_TITLE_KEY "title"
#define RYGEL_CONFIGURATION_TRANSCODING_KEY "enable-transcoding"
#define RYGEL_CONFIGURATION_MP3_TRANSCODER_KEY "enable-mp3-transcoder"
#define RYGEL_CONFIGURATION_MP2TS_TRANSCODER_KEY "enable-mp2ts-transcoder"
#define RYGEL_CONFIGURATION_LPCM_TRANSCODER_KEY "enable-lpcm-transcoder"
RygelConfiguration* rygel_configuration_new (void);
RygelConfiguration* rygel_configuration_construct (GType object_type);
RygelConfiguration* rygel_configuration_get_default (void);
RygelConfiguration* rygel_configuration_new (void);
gboolean rygel_configuration_get_bool (RygelConfiguration* self, const char* section, const char* key, gboolean default_value);
gboolean rygel_configuration_get_enabled (RygelConfiguration* self, const char* section);
char* rygel_configuration_get_string (RygelConfiguration* self, const char* section, const char* key, const char* default_value);
char* rygel_configuration_get_title (RygelConfiguration* self, const char* section, const char* default_title);
GeeArrayList* rygel_configuration_get_string_list (RygelConfiguration* self, const char* section, const char* key);
gint rygel_configuration_get_int (RygelConfiguration* self, const char* section, const char* key, gint min, gint max, gint default_value);
GeeArrayList* rygel_configuration_get_int_list (RygelConfiguration* self, const char* section, const char* key);
void rygel_configuration_set_string (RygelConfiguration* self, const char* section, const char* key, const char* value);
static void _g_slist_free_g_free (GSList* self);
void rygel_configuration_set_string_list (RygelConfiguration* self, const char* section, const char* key, GeeArrayList* str_list);
void rygel_configuration_set_int (RygelConfiguration* self, const char* section, const char* key, gint value);
void rygel_configuration_set_bool (RygelConfiguration* self, const char* section, const char* key, gboolean value);
const char* rygel_configuration_get_host_ip (RygelConfiguration* self);
void rygel_configuration_set_host_ip (RygelConfiguration* self, const char* value);
gint rygel_configuration_get_port (RygelConfiguration* self);
void rygel_configuration_set_port (RygelConfiguration* self, gint value);
gboolean rygel_configuration_get_transcoding (RygelConfiguration* self);
void rygel_configuration_set_transcoding (RygelConfiguration* self, gboolean value);
gboolean rygel_configuration_get_mp3_transcoder (RygelConfiguration* self);
void rygel_configuration_set_mp3_transcoder (RygelConfiguration* self, gboolean value);
gboolean rygel_configuration_get_mp2ts_transcoder (RygelConfiguration* self);
void rygel_configuration_set_mp2ts_transcoder (RygelConfiguration* self, gboolean value);
gboolean rygel_configuration_get_lpcm_transcoder (RygelConfiguration* self);
void rygel_configuration_set_lpcm_transcoder (RygelConfiguration* self, gboolean value);
static gpointer rygel_configuration_parent_class = NULL;
static void rygel_configuration_finalize (GObject* obj);
static void rygel_configuration_get_property (GObject * object, guint property_id, GValue * value, GParamSpec * pspec);
static void rygel_configuration_set_property (GObject * object, guint property_id, const GValue * value, GParamSpec * pspec);
static int _vala_strcmp0 (const char * str1, const char * str2);



RygelConfiguration* rygel_configuration_get_default (void) {
	RygelConfiguration* _tmp1_;
	if (rygel_configuration_config == NULL) {
		RygelConfiguration* _tmp0_;
		_tmp0_ = NULL;
		rygel_configuration_config = (_tmp0_ = rygel_configuration_new (), (rygel_configuration_config == NULL) ? NULL : (rygel_configuration_config = (g_object_unref (rygel_configuration_config), NULL)), _tmp0_);
	}
	_tmp1_ = NULL;
	return (_tmp1_ = rygel_configuration_config, (_tmp1_ == NULL) ? NULL : g_object_ref (_tmp1_));
}


RygelConfiguration* rygel_configuration_construct (GType object_type) {
	RygelConfiguration * self;
	GConfClient* _tmp1_;
	GConfClient* _tmp0_;
	self = g_object_newv (object_type, 0, NULL);
	_tmp1_ = NULL;
	_tmp0_ = NULL;
	self->gconf = (_tmp1_ = (_tmp0_ = gconf_client_get_default (), (_tmp0_ == NULL) ? NULL : g_object_ref (_tmp0_)), (self->gconf == NULL) ? NULL : (self->gconf = (g_object_unref (self->gconf), NULL)), _tmp1_);
	return self;
}


RygelConfiguration* rygel_configuration_new (void) {
	return rygel_configuration_construct (RYGEL_TYPE_CONFIGURATION);
}


gboolean rygel_configuration_get_enabled (RygelConfiguration* self, const char* section) {
	g_return_val_if_fail (self != NULL, FALSE);
	g_return_val_if_fail (section != NULL, FALSE);
	return rygel_configuration_get_bool (self, section, RYGEL_CONFIGURATION_ENABLED_KEY, TRUE);
}


char* rygel_configuration_get_title (RygelConfiguration* self, const char* section, const char* default_title) {
	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (section != NULL, NULL);
	g_return_val_if_fail (default_title != NULL, NULL);
	return rygel_configuration_get_string (self, section, RYGEL_CONFIGURATION_TITLE_KEY, default_title);
}


char* rygel_configuration_get_string (RygelConfiguration* self, const char* section, const char* key, const char* default_value) {
	GError * _inner_error_;
	char* val;
	char* _tmp1_;
	char* _tmp0_;
	char* _tmp2_;
	char* path;
	gboolean _tmp7_;
	char* _tmp10_;
	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (section != NULL, NULL);
	g_return_val_if_fail (key != NULL, NULL);
	_inner_error_ = NULL;
	val = NULL;
	_tmp1_ = NULL;
	_tmp0_ = NULL;
	_tmp2_ = NULL;
	path = (_tmp2_ = g_strconcat (_tmp1_ = g_strconcat (_tmp0_ = g_strconcat (RYGEL_CONFIGURATION_ROOT_GCONF_PATH, section, NULL), "/", NULL), key, NULL), _tmp1_ = (g_free (_tmp1_), NULL), _tmp0_ = (g_free (_tmp0_), NULL), _tmp2_);
	{
		const char* _tmp3_;
		char* _tmp5_;
		const char* _tmp4_;
		_tmp3_ = gconf_client_get_string (self->gconf, path, &_inner_error_);
		if (_inner_error_ != NULL) {
			goto __catch0_g_error;
			goto __finally0;
		}
		_tmp5_ = NULL;
		_tmp4_ = NULL;
		val = (_tmp5_ = (_tmp4_ = _tmp3_, (_tmp4_ == NULL) ? NULL : g_strdup (_tmp4_)), val = (g_free (val), NULL), _tmp5_);
	}
	goto __finally0;
	__catch0_g_error:
	{
		GError * _error_;
		_error_ = _inner_error_;
		_inner_error_ = NULL;
		{
			char* _tmp6_;
			_tmp6_ = NULL;
			val = (_tmp6_ = NULL, val = (g_free (val), NULL), _tmp6_);
			(_error_ == NULL) ? NULL : (_error_ = (g_error_free (_error_), NULL));
		}
	}
	__finally0:
	if (_inner_error_ != NULL) {
		val = (g_free (val), NULL);
		path = (g_free (path), NULL);
		g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, _inner_error_->message);
		g_clear_error (&_inner_error_);
		return NULL;
	}
	_tmp7_ = FALSE;
	if (val == NULL) {
		_tmp7_ = TRUE;
	} else {
		_tmp7_ = _vala_strcmp0 (val, "") == 0;
	}
	if (_tmp7_) {
		char* _tmp9_;
		const char* _tmp8_;
		_tmp9_ = NULL;
		_tmp8_ = NULL;
		val = (_tmp9_ = (_tmp8_ = default_value, (_tmp8_ == NULL) ? NULL : g_strdup (_tmp8_)), val = (g_free (val), NULL), _tmp9_);
	}
	_tmp10_ = NULL;
	return (_tmp10_ = val, path = (g_free (path), NULL), _tmp10_);
}


GeeArrayList* rygel_configuration_get_string_list (RygelConfiguration* self, const char* section, const char* key) {
	GError * _inner_error_;
	GeeArrayList* str_list;
	char* _tmp1_;
	char* _tmp0_;
	char* _tmp2_;
	char* path;
	GeeArrayList* _tmp4_;
	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (section != NULL, NULL);
	g_return_val_if_fail (key != NULL, NULL);
	_inner_error_ = NULL;
	str_list = gee_array_list_new (G_TYPE_STRING, (GBoxedCopyFunc) g_strdup, g_free, g_direct_equal);
	_tmp1_ = NULL;
	_tmp0_ = NULL;
	_tmp2_ = NULL;
	path = (_tmp2_ = g_strconcat (_tmp1_ = g_strconcat (_tmp0_ = g_strconcat (RYGEL_CONFIGURATION_ROOT_GCONF_PATH, section, NULL), "/", NULL), key, NULL), _tmp1_ = (g_free (_tmp1_), NULL), _tmp0_ = (g_free (_tmp0_), NULL), _tmp2_);
	{
		GSList* strings;
		strings = gconf_client_get_list (self->gconf, path, GCONF_VALUE_STRING, &_inner_error_);
		if (_inner_error_ != NULL) {
			goto __catch1_g_error;
			goto __finally1;
		}
		if (strings != NULL) {
			{
				GSList* str_collection;
				GSList* str_it;
				str_collection = strings;
				for (str_it = str_collection; str_it != NULL; str_it = str_it->next) {
					const char* _tmp3_;
					char* str;
					_tmp3_ = NULL;
					str = (_tmp3_ = (const char*) str_it->data, (_tmp3_ == NULL) ? NULL : g_strdup (_tmp3_));
					{
						gee_collection_add ((GeeCollection*) str_list, str);
						str = (g_free (str), NULL);
					}
				}
			}
		}
	}
	goto __finally1;
	__catch1_g_error:
	{
		GError * _error_;
		_error_ = _inner_error_;
		_inner_error_ = NULL;
		{
			g_warning ("rygel-configuration.vala:163: Failed to get value for key: %s\n", path);
			(_error_ == NULL) ? NULL : (_error_ = (g_error_free (_error_), NULL));
		}
	}
	__finally1:
	if (_inner_error_ != NULL) {
		(str_list == NULL) ? NULL : (str_list = (g_object_unref (str_list), NULL));
		path = (g_free (path), NULL);
		g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, _inner_error_->message);
		g_clear_error (&_inner_error_);
		return NULL;
	}
	_tmp4_ = NULL;
	return (_tmp4_ = str_list, path = (g_free (path), NULL), _tmp4_);
}


gint rygel_configuration_get_int (RygelConfiguration* self, const char* section, const char* key, gint min, gint max, gint default_value) {
	GError * _inner_error_;
	gint val;
	char* _tmp1_;
	char* _tmp0_;
	char* _tmp2_;
	char* path;
	gboolean _tmp4_;
	gint _tmp5_;
	g_return_val_if_fail (self != NULL, 0);
	g_return_val_if_fail (section != NULL, 0);
	g_return_val_if_fail (key != NULL, 0);
	_inner_error_ = NULL;
	val = 0;
	_tmp1_ = NULL;
	_tmp0_ = NULL;
	_tmp2_ = NULL;
	path = (_tmp2_ = g_strconcat (_tmp1_ = g_strconcat (_tmp0_ = g_strconcat (RYGEL_CONFIGURATION_ROOT_GCONF_PATH, section, NULL), "/", NULL), key, NULL), _tmp1_ = (g_free (_tmp1_), NULL), _tmp0_ = (g_free (_tmp0_), NULL), _tmp2_);
	{
		gint _tmp3_;
		_tmp3_ = gconf_client_get_int (self->gconf, path, &_inner_error_);
		if (_inner_error_ != NULL) {
			goto __catch2_g_error;
			goto __finally2;
		}
		val = _tmp3_;
	}
	goto __finally2;
	__catch2_g_error:
	{
		GError * _error_;
		_error_ = _inner_error_;
		_inner_error_ = NULL;
		{
			val = default_value;
			(_error_ == NULL) ? NULL : (_error_ = (g_error_free (_error_), NULL));
		}
	}
	__finally2:
	if (_inner_error_ != NULL) {
		path = (g_free (path), NULL);
		g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, _inner_error_->message);
		g_clear_error (&_inner_error_);
		return 0;
	}
	_tmp4_ = FALSE;
	if (val < min) {
		_tmp4_ = TRUE;
	} else {
		_tmp4_ = val > max;
	}
	if (_tmp4_) {
		val = default_value;
	}
	return (_tmp5_ = val, path = (g_free (path), NULL), _tmp5_);
}


GeeArrayList* rygel_configuration_get_int_list (RygelConfiguration* self, const char* section, const char* key) {
	GError * _inner_error_;
	GeeArrayList* int_list;
	char* _tmp1_;
	char* _tmp0_;
	char* _tmp2_;
	char* path;
	GeeArrayList* _tmp3_;
	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (section != NULL, NULL);
	g_return_val_if_fail (key != NULL, NULL);
	_inner_error_ = NULL;
	int_list = gee_array_list_new (G_TYPE_INT, NULL, NULL, g_direct_equal);
	_tmp1_ = NULL;
	_tmp0_ = NULL;
	_tmp2_ = NULL;
	path = (_tmp2_ = g_strconcat (_tmp1_ = g_strconcat (_tmp0_ = g_strconcat (RYGEL_CONFIGURATION_ROOT_GCONF_PATH, section, NULL), "/", NULL), key, NULL), _tmp1_ = (g_free (_tmp1_), NULL), _tmp0_ = (g_free (_tmp0_), NULL), _tmp2_);
	{
		GSList* ints;
		ints = gconf_client_get_list (self->gconf, path, GCONF_VALUE_INT, &_inner_error_);
		if (_inner_error_ != NULL) {
			goto __catch3_g_error;
			goto __finally3;
		}
		if (ints != NULL) {
			{
				GSList* num_collection;
				GSList* num_it;
				num_collection = ints;
				for (num_it = num_collection; num_it != NULL; num_it = num_it->next) {
					gint num;
					num = GPOINTER_TO_INT (num_it->data);
					{
						gee_collection_add ((GeeCollection*) int_list, GINT_TO_POINTER (num));
					}
				}
			}
		}
	}
	goto __finally3;
	__catch3_g_error:
	{
		GError * _error_;
		_error_ = _inner_error_;
		_inner_error_ = NULL;
		{
			g_warning ("rygel-configuration.vala:205: Failed to get value for key: %s", path);
			(_error_ == NULL) ? NULL : (_error_ = (g_error_free (_error_), NULL));
		}
	}
	__finally3:
	if (_inner_error_ != NULL) {
		(int_list == NULL) ? NULL : (int_list = (g_object_unref (int_list), NULL));
		path = (g_free (path), NULL);
		g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, _inner_error_->message);
		g_clear_error (&_inner_error_);
		return NULL;
	}
	_tmp3_ = NULL;
	return (_tmp3_ = int_list, path = (g_free (path), NULL), _tmp3_);
}


gboolean rygel_configuration_get_bool (RygelConfiguration* self, const char* section, const char* key, gboolean default_value) {
	GError * _inner_error_;
	gboolean val;
	char* _tmp1_;
	char* _tmp0_;
	char* _tmp2_;
	char* path;
	gboolean _tmp3_;
	g_return_val_if_fail (self != NULL, FALSE);
	g_return_val_if_fail (section != NULL, FALSE);
	g_return_val_if_fail (key != NULL, FALSE);
	_inner_error_ = NULL;
	val = FALSE;
	_tmp1_ = NULL;
	_tmp0_ = NULL;
	_tmp2_ = NULL;
	path = (_tmp2_ = g_strconcat (_tmp1_ = g_strconcat (_tmp0_ = g_strconcat (RYGEL_CONFIGURATION_ROOT_GCONF_PATH, section, NULL), "/", NULL), key, NULL), _tmp1_ = (g_free (_tmp1_), NULL), _tmp0_ = (g_free (_tmp0_), NULL), _tmp2_);
	{
		GConfValue* value;
		value = gconf_client_get (self->gconf, path, &_inner_error_);
		if (_inner_error_ != NULL) {
			goto __catch4_g_error;
			goto __finally4;
		}
		if (value != NULL) {
			val = gconf_value_get_bool (value);
		} else {
			val = default_value;
		}
	}
	goto __finally4;
	__catch4_g_error:
	{
		GError * _error_;
		_error_ = _inner_error_;
		_inner_error_ = NULL;
		{
			val = default_value;
			(_error_ == NULL) ? NULL : (_error_ = (g_error_free (_error_), NULL));
		}
	}
	__finally4:
	if (_inner_error_ != NULL) {
		path = (g_free (path), NULL);
		g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, _inner_error_->message);
		g_clear_error (&_inner_error_);
		return FALSE;
	}
	return (_tmp3_ = val, path = (g_free (path), NULL), _tmp3_);
}


void rygel_configuration_set_string (RygelConfiguration* self, const char* section, const char* key, const char* value) {
	GError * _inner_error_;
	char* _tmp1_;
	char* _tmp0_;
	char* _tmp2_;
	char* path;
	g_return_if_fail (self != NULL);
	g_return_if_fail (section != NULL);
	g_return_if_fail (key != NULL);
	g_return_if_fail (value != NULL);
	_inner_error_ = NULL;
	_tmp1_ = NULL;
	_tmp0_ = NULL;
	_tmp2_ = NULL;
	path = (_tmp2_ = g_strconcat (_tmp1_ = g_strconcat (_tmp0_ = g_strconcat (RYGEL_CONFIGURATION_ROOT_GCONF_PATH, section, NULL), "/", NULL), key, NULL), _tmp1_ = (g_free (_tmp1_), NULL), _tmp0_ = (g_free (_tmp0_), NULL), _tmp2_);
	{
		gconf_client_set_string (self->gconf, path, value, &_inner_error_);
		if (_inner_error_ != NULL) {
			goto __catch5_g_error;
			goto __finally5;
		}
	}
	goto __finally5;
	__catch5_g_error:
	{
		GError * _error_;
		_error_ = _inner_error_;
		_inner_error_ = NULL;
		{
			(_error_ == NULL) ? NULL : (_error_ = (g_error_free (_error_), NULL));
		}
	}
	__finally5:
	if (_inner_error_ != NULL) {
		path = (g_free (path), NULL);
		g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, _inner_error_->message);
		g_clear_error (&_inner_error_);
		return;
	}
	path = (g_free (path), NULL);
}


static void _g_slist_free_g_free (GSList* self) {
	g_slist_foreach (self, (GFunc) g_free, NULL);
	g_slist_free (self);
}


/* No big deal*/
void rygel_configuration_set_string_list (RygelConfiguration* self, const char* section, const char* key, GeeArrayList* str_list) {
	GError * _inner_error_;
	char* _tmp1_;
	char* _tmp0_;
	char* _tmp2_;
	char* path;
	GSList* slist;
	g_return_if_fail (self != NULL);
	g_return_if_fail (section != NULL);
	g_return_if_fail (key != NULL);
	g_return_if_fail (str_list != NULL);
	_inner_error_ = NULL;
	_tmp1_ = NULL;
	_tmp0_ = NULL;
	_tmp2_ = NULL;
	path = (_tmp2_ = g_strconcat (_tmp1_ = g_strconcat (_tmp0_ = g_strconcat (RYGEL_CONFIGURATION_ROOT_GCONF_PATH, section, NULL), "/", NULL), key, NULL), _tmp1_ = (g_free (_tmp1_), NULL), _tmp0_ = (g_free (_tmp0_), NULL), _tmp2_);
	/* GConf requires us to provide it GLib.SList*/
	slist = NULL;
	{
		GeeIterator* _str_it;
		_str_it = gee_iterable_iterator ((GeeIterable*) str_list);
		while (gee_iterator_next (_str_it)) {
			char* str;
			str = (char*) gee_iterator_get (_str_it);
			if (_vala_strcmp0 (str, "") != 0) {
				const char* _tmp3_;
				_tmp3_ = NULL;
				slist = g_slist_append (slist, (_tmp3_ = str, (_tmp3_ == NULL) ? NULL : g_strdup (_tmp3_)));
			}
			str = (g_free (str), NULL);
		}
		(_str_it == NULL) ? NULL : (_str_it = (g_object_unref (_str_it), NULL));
	}
	{
		gconf_client_set_list (self->gconf, path, GCONF_VALUE_STRING, slist, &_inner_error_);
		if (_inner_error_ != NULL) {
			goto __catch6_g_error;
			goto __finally6;
		}
	}
	goto __finally6;
	__catch6_g_error:
	{
		GError * _error_;
		_error_ = _inner_error_;
		_inner_error_ = NULL;
		{
			(_error_ == NULL) ? NULL : (_error_ = (g_error_free (_error_), NULL));
		}
	}
	__finally6:
	if (_inner_error_ != NULL) {
		path = (g_free (path), NULL);
		(slist == NULL) ? NULL : (slist = (_g_slist_free_g_free (slist), NULL));
		g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, _inner_error_->message);
		g_clear_error (&_inner_error_);
		return;
	}
	path = (g_free (path), NULL);
	(slist == NULL) ? NULL : (slist = (_g_slist_free_g_free (slist), NULL));
}


/* No big deal*/
void rygel_configuration_set_int (RygelConfiguration* self, const char* section, const char* key, gint value) {
	GError * _inner_error_;
	char* _tmp1_;
	char* _tmp0_;
	char* _tmp2_;
	char* path;
	g_return_if_fail (self != NULL);
	g_return_if_fail (section != NULL);
	g_return_if_fail (key != NULL);
	_inner_error_ = NULL;
	_tmp1_ = NULL;
	_tmp0_ = NULL;
	_tmp2_ = NULL;
	path = (_tmp2_ = g_strconcat (_tmp1_ = g_strconcat (_tmp0_ = g_strconcat (RYGEL_CONFIGURATION_ROOT_GCONF_PATH, section, NULL), "/", NULL), key, NULL), _tmp1_ = (g_free (_tmp1_), NULL), _tmp0_ = (g_free (_tmp0_), NULL), _tmp2_);
	{
		gconf_client_set_int (self->gconf, path, value, &_inner_error_);
		if (_inner_error_ != NULL) {
			goto __catch7_g_error;
			goto __finally7;
		}
	}
	goto __finally7;
	__catch7_g_error:
	{
		GError * _error_;
		_error_ = _inner_error_;
		_inner_error_ = NULL;
		{
			(_error_ == NULL) ? NULL : (_error_ = (g_error_free (_error_), NULL));
		}
	}
	__finally7:
	if (_inner_error_ != NULL) {
		path = (g_free (path), NULL);
		g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, _inner_error_->message);
		g_clear_error (&_inner_error_);
		return;
	}
	path = (g_free (path), NULL);
}


/* No big deal*/
void rygel_configuration_set_bool (RygelConfiguration* self, const char* section, const char* key, gboolean value) {
	GError * _inner_error_;
	char* _tmp1_;
	char* _tmp0_;
	char* _tmp2_;
	char* path;
	g_return_if_fail (self != NULL);
	g_return_if_fail (section != NULL);
	g_return_if_fail (key != NULL);
	_inner_error_ = NULL;
	_tmp1_ = NULL;
	_tmp0_ = NULL;
	_tmp2_ = NULL;
	path = (_tmp2_ = g_strconcat (_tmp1_ = g_strconcat (_tmp0_ = g_strconcat (RYGEL_CONFIGURATION_ROOT_GCONF_PATH, section, NULL), "/", NULL), key, NULL), _tmp1_ = (g_free (_tmp1_), NULL), _tmp0_ = (g_free (_tmp0_), NULL), _tmp2_);
	{
		gconf_client_set_bool (self->gconf, path, value, &_inner_error_);
		if (_inner_error_ != NULL) {
			goto __catch8_g_error;
			goto __finally8;
		}
	}
	goto __finally8;
	__catch8_g_error:
	{
		GError * _error_;
		_error_ = _inner_error_;
		_inner_error_ = NULL;
		{
			(_error_ == NULL) ? NULL : (_error_ = (g_error_free (_error_), NULL));
		}
	}
	__finally8:
	if (_inner_error_ != NULL) {
		path = (g_free (path), NULL);
		g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, _inner_error_->message);
		g_clear_error (&_inner_error_);
		return;
	}
	path = (g_free (path), NULL);
}


const char* rygel_configuration_get_host_ip (RygelConfiguration* self) {
	char* _tmp0_;
	g_return_val_if_fail (self != NULL, NULL);
	_tmp0_ = NULL;
	self->priv->_host_ip = (_tmp0_ = rygel_configuration_get_string (self, "general", RYGEL_CONFIGURATION_IP_KEY, NULL), self->priv->_host_ip = (g_free (self->priv->_host_ip), NULL), _tmp0_);
	return self->priv->_host_ip;
}


void rygel_configuration_set_host_ip (RygelConfiguration* self, const char* value) {
	g_return_if_fail (self != NULL);
	rygel_configuration_set_string (self, "general", RYGEL_CONFIGURATION_IP_KEY, value);
	g_object_notify ((GObject *) self, "host-ip");
}


gint rygel_configuration_get_port (RygelConfiguration* self) {
	g_return_val_if_fail (self != NULL, 0);
	return rygel_configuration_get_int (self, "general", RYGEL_CONFIGURATION_PORT_KEY, (gint) 0U, (gint) G_MAXUINT16, 0);
}


void rygel_configuration_set_port (RygelConfiguration* self, gint value) {
	g_return_if_fail (self != NULL);
	rygel_configuration_set_int (self, "general", RYGEL_CONFIGURATION_PORT_KEY, value);
	g_object_notify ((GObject *) self, "port");
}


gboolean rygel_configuration_get_transcoding (RygelConfiguration* self) {
	g_return_val_if_fail (self != NULL, FALSE);
	return rygel_configuration_get_bool (self, "general", RYGEL_CONFIGURATION_TRANSCODING_KEY, TRUE);
}


void rygel_configuration_set_transcoding (RygelConfiguration* self, gboolean value) {
	g_return_if_fail (self != NULL);
	rygel_configuration_set_bool (self, "general", RYGEL_CONFIGURATION_TRANSCODING_KEY, value);
	g_object_notify ((GObject *) self, "transcoding");
}


gboolean rygel_configuration_get_mp3_transcoder (RygelConfiguration* self) {
	g_return_val_if_fail (self != NULL, FALSE);
	return rygel_configuration_get_bool (self, "general", RYGEL_CONFIGURATION_MP3_TRANSCODER_KEY, TRUE);
}


void rygel_configuration_set_mp3_transcoder (RygelConfiguration* self, gboolean value) {
	g_return_if_fail (self != NULL);
	rygel_configuration_set_bool (self, "general", RYGEL_CONFIGURATION_MP3_TRANSCODER_KEY, value);
	g_object_notify ((GObject *) self, "mp3-transcoder");
}


gboolean rygel_configuration_get_mp2ts_transcoder (RygelConfiguration* self) {
	g_return_val_if_fail (self != NULL, FALSE);
	return rygel_configuration_get_bool (self, "general", RYGEL_CONFIGURATION_MP2TS_TRANSCODER_KEY, TRUE);
}


void rygel_configuration_set_mp2ts_transcoder (RygelConfiguration* self, gboolean value) {
	g_return_if_fail (self != NULL);
	rygel_configuration_set_bool (self, "general", RYGEL_CONFIGURATION_MP2TS_TRANSCODER_KEY, value);
	g_object_notify ((GObject *) self, "mp2ts-transcoder");
}


gboolean rygel_configuration_get_lpcm_transcoder (RygelConfiguration* self) {
	g_return_val_if_fail (self != NULL, FALSE);
	return rygel_configuration_get_bool (self, "general", RYGEL_CONFIGURATION_LPCM_TRANSCODER_KEY, TRUE);
}


void rygel_configuration_set_lpcm_transcoder (RygelConfiguration* self, gboolean value) {
	g_return_if_fail (self != NULL);
	rygel_configuration_set_bool (self, "general", RYGEL_CONFIGURATION_LPCM_TRANSCODER_KEY, value);
	g_object_notify ((GObject *) self, "lpcm-transcoder");
}


static void rygel_configuration_class_init (RygelConfigurationClass * klass) {
	rygel_configuration_parent_class = g_type_class_peek_parent (klass);
	g_type_class_add_private (klass, sizeof (RygelConfigurationPrivate));
	G_OBJECT_CLASS (klass)->get_property = rygel_configuration_get_property;
	G_OBJECT_CLASS (klass)->set_property = rygel_configuration_set_property;
	G_OBJECT_CLASS (klass)->finalize = rygel_configuration_finalize;
	g_object_class_install_property (G_OBJECT_CLASS (klass), RYGEL_CONFIGURATION_HOST_IP, g_param_spec_string ("host-ip", "host-ip", "host-ip", NULL, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
	g_object_class_install_property (G_OBJECT_CLASS (klass), RYGEL_CONFIGURATION_PORT, g_param_spec_int ("port", "port", "port", G_MININT, G_MAXINT, 0, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
	g_object_class_install_property (G_OBJECT_CLASS (klass), RYGEL_CONFIGURATION_TRANSCODING, g_param_spec_boolean ("transcoding", "transcoding", "transcoding", FALSE, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
	g_object_class_install_property (G_OBJECT_CLASS (klass), RYGEL_CONFIGURATION_MP3_TRANSCODER, g_param_spec_boolean ("mp3-transcoder", "mp3-transcoder", "mp3-transcoder", FALSE, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
	g_object_class_install_property (G_OBJECT_CLASS (klass), RYGEL_CONFIGURATION_MP2TS_TRANSCODER, g_param_spec_boolean ("mp2ts-transcoder", "mp2ts-transcoder", "mp2ts-transcoder", FALSE, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
	g_object_class_install_property (G_OBJECT_CLASS (klass), RYGEL_CONFIGURATION_LPCM_TRANSCODER, g_param_spec_boolean ("lpcm-transcoder", "lpcm-transcoder", "lpcm-transcoder", FALSE, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
}


static void rygel_configuration_instance_init (RygelConfiguration * self) {
	self->priv = RYGEL_CONFIGURATION_GET_PRIVATE (self);
}


static void rygel_configuration_finalize (GObject* obj) {
	RygelConfiguration * self;
	self = RYGEL_CONFIGURATION (obj);
	(self->gconf == NULL) ? NULL : (self->gconf = (g_object_unref (self->gconf), NULL));
	self->priv->_host_ip = (g_free (self->priv->_host_ip), NULL);
	G_OBJECT_CLASS (rygel_configuration_parent_class)->finalize (obj);
}


GType rygel_configuration_get_type (void) {
	static GType rygel_configuration_type_id = 0;
	if (rygel_configuration_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (RygelConfigurationClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) rygel_configuration_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (RygelConfiguration), 0, (GInstanceInitFunc) rygel_configuration_instance_init, NULL };
		rygel_configuration_type_id = g_type_register_static (G_TYPE_OBJECT, "RygelConfiguration", &g_define_type_info, 0);
	}
	return rygel_configuration_type_id;
}


static void rygel_configuration_get_property (GObject * object, guint property_id, GValue * value, GParamSpec * pspec) {
	RygelConfiguration * self;
	gpointer boxed;
	self = RYGEL_CONFIGURATION (object);
	switch (property_id) {
		case RYGEL_CONFIGURATION_HOST_IP:
		g_value_set_string (value, rygel_configuration_get_host_ip (self));
		break;
		case RYGEL_CONFIGURATION_PORT:
		g_value_set_int (value, rygel_configuration_get_port (self));
		break;
		case RYGEL_CONFIGURATION_TRANSCODING:
		g_value_set_boolean (value, rygel_configuration_get_transcoding (self));
		break;
		case RYGEL_CONFIGURATION_MP3_TRANSCODER:
		g_value_set_boolean (value, rygel_configuration_get_mp3_transcoder (self));
		break;
		case RYGEL_CONFIGURATION_MP2TS_TRANSCODER:
		g_value_set_boolean (value, rygel_configuration_get_mp2ts_transcoder (self));
		break;
		case RYGEL_CONFIGURATION_LPCM_TRANSCODER:
		g_value_set_boolean (value, rygel_configuration_get_lpcm_transcoder (self));
		break;
		default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}


static void rygel_configuration_set_property (GObject * object, guint property_id, const GValue * value, GParamSpec * pspec) {
	RygelConfiguration * self;
	self = RYGEL_CONFIGURATION (object);
	switch (property_id) {
		case RYGEL_CONFIGURATION_HOST_IP:
		rygel_configuration_set_host_ip (self, g_value_get_string (value));
		break;
		case RYGEL_CONFIGURATION_PORT:
		rygel_configuration_set_port (self, g_value_get_int (value));
		break;
		case RYGEL_CONFIGURATION_TRANSCODING:
		rygel_configuration_set_transcoding (self, g_value_get_boolean (value));
		break;
		case RYGEL_CONFIGURATION_MP3_TRANSCODER:
		rygel_configuration_set_mp3_transcoder (self, g_value_get_boolean (value));
		break;
		case RYGEL_CONFIGURATION_MP2TS_TRANSCODER:
		rygel_configuration_set_mp2ts_transcoder (self, g_value_get_boolean (value));
		break;
		case RYGEL_CONFIGURATION_LPCM_TRANSCODER:
		rygel_configuration_set_lpcm_transcoder (self, g_value_get_boolean (value));
		break;
		default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
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




