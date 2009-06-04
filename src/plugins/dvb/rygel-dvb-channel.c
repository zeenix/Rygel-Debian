/*
 * Copyright (C) 2008 Zeeshan Ali (Khattak) <zeeshanak@gnome.org>.
 * Copyright (C) 2008 Nokia Corporation, all rights reserved.
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
#include <dbus/dbus-glib-lowlevel.h>
#include <dbus/dbus-glib.h>
#include <gee/collection.h>


#define RYGEL_TYPE_DVB_CHANNEL (rygel_dvb_channel_get_type ())
#define RYGEL_DVB_CHANNEL(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_DVB_CHANNEL, RygelDVBChannel))
#define RYGEL_DVB_CHANNEL_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_DVB_CHANNEL, RygelDVBChannelClass))
#define RYGEL_IS_DVB_CHANNEL(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_DVB_CHANNEL))
#define RYGEL_IS_DVB_CHANNEL_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_DVB_CHANNEL))
#define RYGEL_DVB_CHANNEL_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_DVB_CHANNEL, RygelDVBChannelClass))

typedef struct _RygelDVBChannel RygelDVBChannel;
typedef struct _RygelDVBChannelClass RygelDVBChannelClass;
typedef struct _RygelDVBChannelPrivate RygelDVBChannelPrivate;

/**
 * Represents DVB item.
 */
struct _RygelDVBChannel {
	RygelMediaItem parent_instance;
	RygelDVBChannelPrivate * priv;
};

struct _RygelDVBChannelClass {
	RygelMediaItemClass parent_class;
};

struct _RygelDVBChannelPrivate {
	guint cid;
};



GType rygel_dvb_channel_get_type (void);
#define RYGEL_DVB_CHANNEL_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), RYGEL_TYPE_DVB_CHANNEL, RygelDVBChannelPrivate))
enum  {
	RYGEL_DVB_CHANNEL_DUMMY_PROPERTY
};
extern DBusGProxy* rygel_dvb_channel_channel_list;
DBusGProxy* rygel_dvb_channel_channel_list = NULL;
void rygel_dvb_channel_fetch_metadata (RygelDVBChannel* self, GError** error);
RygelDVBChannel* rygel_dvb_channel_new (guint cid, RygelMediaContainer* parent, DBusGProxy* channel_list, GError** error);
RygelDVBChannel* rygel_dvb_channel_construct (GType object_type, guint cid, RygelMediaContainer* parent, DBusGProxy* channel_list, GError** error);
RygelDVBChannel* rygel_dvb_channel_new (guint cid, RygelMediaContainer* parent, DBusGProxy* channel_list, GError** error);
char* _dynamic_GetChannelName4 (DBusGProxy* self, guint param1, GError** error);
gboolean _dynamic_IsRadioChannel5 (DBusGProxy* self, guint param1, GError** error);
char* _dynamic_GetChannelURL6 (DBusGProxy* self, guint param1, GError** error);
static gpointer rygel_dvb_channel_parent_class = NULL;
static void rygel_dvb_channel_finalize (GObject* obj);



/* The DVB Daemon Channel ID */
RygelDVBChannel* rygel_dvb_channel_construct (GType object_type, guint cid, RygelMediaContainer* parent, DBusGProxy* channel_list, GError** error) {
	GError * _inner_error_;
	RygelDVBChannel * self;
	char* _tmp1_;
	char* _tmp0_;
	char* _tmp2_;
	char* id;
	DBusGProxy* _tmp4_;
	DBusGProxy* _tmp3_;
	g_return_val_if_fail (parent != NULL, NULL);
	g_return_val_if_fail (channel_list != NULL, NULL);
	_inner_error_ = NULL;
	_tmp1_ = NULL;
	_tmp0_ = NULL;
	_tmp2_ = NULL;
	id = (_tmp2_ = g_strconcat (_tmp0_ = g_strconcat (((RygelMediaObject*) parent)->id, ":", NULL), _tmp1_ = g_strdup_printf ("%u", cid), NULL), _tmp1_ = (g_free (_tmp1_), NULL), _tmp0_ = (g_free (_tmp0_), NULL), _tmp2_);
	self = (RygelDVBChannel*) rygel_media_item_construct (object_type, id, parent, "Unknown", "Unknown");
	self->priv->cid = cid;
	_tmp4_ = NULL;
	_tmp3_ = NULL;
	rygel_dvb_channel_channel_list = (_tmp4_ = (_tmp3_ = channel_list, (_tmp3_ == NULL) ? NULL : g_object_ref (_tmp3_)), (rygel_dvb_channel_channel_list == NULL) ? NULL : (rygel_dvb_channel_channel_list = (g_object_unref (rygel_dvb_channel_channel_list), NULL)), _tmp4_);
	rygel_dvb_channel_fetch_metadata (self, &_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		id = (g_free (id), NULL);
		return;
	}
	id = (g_free (id), NULL);
	return self;
}


RygelDVBChannel* rygel_dvb_channel_new (guint cid, RygelMediaContainer* parent, DBusGProxy* channel_list, GError** error) {
	return rygel_dvb_channel_construct (RYGEL_TYPE_DVB_CHANNEL, cid, parent, channel_list, error);
}


char* _dynamic_GetChannelName4 (DBusGProxy* self, guint param1, GError** error) {
	char* result;
	dbus_g_proxy_call (self, "GetChannelName", error, G_TYPE_UINT, param1, G_TYPE_INVALID, G_TYPE_STRING, &result, G_TYPE_INVALID);
	if (*error) {
		return NULL;
	}
	return result;
}


gboolean _dynamic_IsRadioChannel5 (DBusGProxy* self, guint param1, GError** error) {
	gboolean result;
	dbus_g_proxy_call (self, "IsRadioChannel", error, G_TYPE_UINT, param1, G_TYPE_INVALID, G_TYPE_BOOLEAN, &result, G_TYPE_INVALID);
	if (*error) {
		return FALSE;
	}
	return result;
}


char* _dynamic_GetChannelURL6 (DBusGProxy* self, guint param1, GError** error) {
	char* result;
	dbus_g_proxy_call (self, "GetChannelURL", error, G_TYPE_UINT, param1, G_TYPE_INVALID, G_TYPE_STRING, &result, G_TYPE_INVALID);
	if (*error) {
		return NULL;
	}
	return result;
}


void rygel_dvb_channel_fetch_metadata (RygelDVBChannel* self, GError** error) {
	GError * _inner_error_;
	char* _tmp0_;
	char* _tmp1_;
	gboolean is_radio;
	char* _tmp4_;
	char* uri;
	g_return_if_fail (self != NULL);
	_inner_error_ = NULL;
	_tmp0_ = _dynamic_GetChannelName4 (rygel_dvb_channel_channel_list, self->priv->cid, &_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		return;
	}
	/* TODO: make this async */
	_tmp1_ = NULL;
	((RygelMediaObject*) self)->title = (_tmp1_ = _tmp0_, ((RygelMediaObject*) self)->title = (g_free (((RygelMediaObject*) self)->title), NULL), _tmp1_);
	is_radio = _dynamic_IsRadioChannel5 (rygel_dvb_channel_channel_list, self->priv->cid, &_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		return;
	}
	if (is_radio) {
		char* _tmp2_;
		_tmp2_ = NULL;
		((RygelMediaItem*) self)->upnp_class = (_tmp2_ = g_strdup ("object.item.audioItem.audioBroadcast"), ((RygelMediaItem*) self)->upnp_class = (g_free (((RygelMediaItem*) self)->upnp_class), NULL), _tmp2_);
	} else {
		char* _tmp3_;
		_tmp3_ = NULL;
		((RygelMediaItem*) self)->upnp_class = (_tmp3_ = g_strdup ("object.item.videoItem.videoBroadcast"), ((RygelMediaItem*) self)->upnp_class = (g_free (((RygelMediaItem*) self)->upnp_class), NULL), _tmp3_);
	}
	_tmp4_ = NULL;
	((RygelMediaItem*) self)->mime_type = (_tmp4_ = g_strdup ("video/mpeg"), ((RygelMediaItem*) self)->mime_type = (g_free (((RygelMediaItem*) self)->mime_type), NULL), _tmp4_);
	uri = _dynamic_GetChannelURL6 (rygel_dvb_channel_channel_list, self->priv->cid, &_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		return;
	}
	gee_collection_add ((GeeCollection*) ((RygelMediaItem*) self)->uris, uri);
	uri = (g_free (uri), NULL);
}


static void rygel_dvb_channel_class_init (RygelDVBChannelClass * klass) {
	rygel_dvb_channel_parent_class = g_type_class_peek_parent (klass);
	g_type_class_add_private (klass, sizeof (RygelDVBChannelPrivate));
	G_OBJECT_CLASS (klass)->finalize = rygel_dvb_channel_finalize;
}


static void rygel_dvb_channel_instance_init (RygelDVBChannel * self) {
	self->priv = RYGEL_DVB_CHANNEL_GET_PRIVATE (self);
}


static void rygel_dvb_channel_finalize (GObject* obj) {
	RygelDVBChannel * self;
	self = RYGEL_DVB_CHANNEL (obj);
	G_OBJECT_CLASS (rygel_dvb_channel_parent_class)->finalize (obj);
}


GType rygel_dvb_channel_get_type (void) {
	static GType rygel_dvb_channel_type_id = 0;
	if (rygel_dvb_channel_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (RygelDVBChannelClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) rygel_dvb_channel_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (RygelDVBChannel), 0, (GInstanceInitFunc) rygel_dvb_channel_instance_init, NULL };
		rygel_dvb_channel_type_id = g_type_register_static (RYGEL_TYPE_MEDIA_ITEM, "RygelDVBChannel", &g_define_type_info, 0);
	}
	return rygel_dvb_channel_type_id;
}




