/*
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
#include <gio/gio.h>
#include <libsoup/soup.h>
#include <gst/gst.h>


#define RYGEL_TYPE_STATE_MACHINE (rygel_state_machine_get_type ())
#define RYGEL_STATE_MACHINE(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_STATE_MACHINE, RygelStateMachine))
#define RYGEL_IS_STATE_MACHINE(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_STATE_MACHINE))
#define RYGEL_STATE_MACHINE_GET_INTERFACE(obj) (G_TYPE_INSTANCE_GET_INTERFACE ((obj), RYGEL_TYPE_STATE_MACHINE, RygelStateMachineIface))

typedef struct _RygelStateMachine RygelStateMachine;
typedef struct _RygelStateMachineIface RygelStateMachineIface;

#define RYGEL_TYPE_HTTP_RESPONSE (rygel_http_response_get_type ())
#define RYGEL_HTTP_RESPONSE(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_HTTP_RESPONSE, RygelHTTPResponse))
#define RYGEL_HTTP_RESPONSE_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_HTTP_RESPONSE, RygelHTTPResponseClass))
#define RYGEL_IS_HTTP_RESPONSE(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_HTTP_RESPONSE))
#define RYGEL_IS_HTTP_RESPONSE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_HTTP_RESPONSE))
#define RYGEL_HTTP_RESPONSE_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_HTTP_RESPONSE, RygelHTTPResponseClass))

typedef struct _RygelHTTPResponse RygelHTTPResponse;
typedef struct _RygelHTTPResponseClass RygelHTTPResponseClass;
typedef struct _RygelHTTPResponsePrivate RygelHTTPResponsePrivate;

#define RYGEL_TYPE_SEEK (rygel_seek_get_type ())
#define RYGEL_SEEK(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_SEEK, RygelSeek))
#define RYGEL_SEEK_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_SEEK, RygelSeekClass))
#define RYGEL_IS_SEEK(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_SEEK))
#define RYGEL_IS_SEEK_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_SEEK))
#define RYGEL_SEEK_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_SEEK, RygelSeekClass))

typedef struct _RygelSeek RygelSeek;
typedef struct _RygelSeekClass RygelSeekClass;
typedef struct _RygelSeekPrivate RygelSeekPrivate;

/**
 * StateMachine interface.
 */
struct _RygelStateMachineIface {
	GTypeInterface parent_iface;
	void (*run) (RygelStateMachine* self, GCancellable* cancellable);
};

struct _RygelHTTPResponse {
	GObject parent_instance;
	RygelHTTPResponsePrivate * priv;
	SoupMessage* msg;
	GCancellable* cancellable;
};

struct _RygelHTTPResponseClass {
	GObjectClass parent_class;
	void (*run) (RygelHTTPResponse* self, GCancellable* cancellable);
	void (*end) (RygelHTTPResponse* self, gboolean aborted, guint status);
};

struct _RygelHTTPResponsePrivate {
	SoupServer* _server;
};

struct _RygelSeek {
	GObject parent_instance;
	RygelSeekPrivate * priv;
};

struct _RygelSeekClass {
	GObjectClass parent_class;
};

struct _RygelSeekPrivate {
	GstFormat _format;
	gint64 _start;
	gint64 _stop;
	gint64 _length;
};



GType rygel_state_machine_get_type (void);
GType rygel_http_response_get_type (void);
#define RYGEL_HTTP_RESPONSE_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), RYGEL_TYPE_HTTP_RESPONSE, RygelHTTPResponsePrivate))
enum  {
	RYGEL_HTTP_RESPONSE_DUMMY_PROPERTY,
	RYGEL_HTTP_RESPONSE_SERVER
};
static void rygel_http_response_set_server (RygelHTTPResponse* self, SoupServer* value);
static void rygel_http_response_on_request_aborted (RygelHTTPResponse* self, SoupServer* server, SoupMessage* msg, SoupClientContext* client);
static void _rygel_http_response_on_request_aborted_soup_server_request_aborted (SoupServer* _sender, SoupMessage* msg, SoupClientContext* client, gpointer self);
SoupServer* rygel_http_response_get_server (RygelHTTPResponse* self);
RygelHTTPResponse* rygel_http_response_new (SoupServer* server, SoupMessage* msg, gboolean partial);
RygelHTTPResponse* rygel_http_response_construct (GType object_type, SoupServer* server, SoupMessage* msg, gboolean partial);
RygelHTTPResponse* rygel_http_response_new (SoupServer* server, SoupMessage* msg, gboolean partial);
static void rygel_http_response_on_cancelled (RygelHTTPResponse* self, GCancellable* cancellable);
static void _rygel_http_response_on_cancelled_g_cancellable_cancelled (GCancellable* _sender, gpointer self);
void rygel_http_response_run (RygelHTTPResponse* self, GCancellable* cancellable);
static void rygel_http_response_real_run (RygelHTTPResponse* self, GCancellable* cancellable);
void rygel_http_response_end (RygelHTTPResponse* self, gboolean aborted, guint status);
void rygel_http_response_push_data (RygelHTTPResponse* self, void* data, gsize length);
static void rygel_http_response_real_end (RygelHTTPResponse* self, gboolean aborted, guint status);
static gpointer rygel_http_response_parent_class = NULL;
static RygelStateMachineIface* rygel_http_response_rygel_state_machine_parent_iface = NULL;
static void rygel_http_response_finalize (GObject* obj);
static void rygel_http_response_get_property (GObject * object, guint property_id, GValue * value, GParamSpec * pspec);
static void rygel_http_response_set_property (GObject * object, guint property_id, const GValue * value, GParamSpec * pspec);
GType rygel_seek_get_type (void);
#define RYGEL_SEEK_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), RYGEL_TYPE_SEEK, RygelSeekPrivate))
enum  {
	RYGEL_SEEK_DUMMY_PROPERTY,
	RYGEL_SEEK_FORMAT,
	RYGEL_SEEK_START,
	RYGEL_SEEK_STOP,
	RYGEL_SEEK_LENGTH
};
static void rygel_seek_set_format (RygelSeek* self, GstFormat value);
void rygel_seek_set_start (RygelSeek* self, gint64 value);
void rygel_seek_set_stop (RygelSeek* self, gint64 value);
RygelSeek* rygel_seek_new (GstFormat format, gint64 start, gint64 stop);
RygelSeek* rygel_seek_construct (GType object_type, GstFormat format, gint64 start, gint64 stop);
RygelSeek* rygel_seek_new (GstFormat format, gint64 start, gint64 stop);
GstFormat rygel_seek_get_format (RygelSeek* self);
gint64 rygel_seek_get_start (RygelSeek* self);
gint64 rygel_seek_get_stop (RygelSeek* self);
static void rygel_seek_set_length (RygelSeek* self, gint64 value);
gint64 rygel_seek_get_length (RygelSeek* self);
static gpointer rygel_seek_parent_class = NULL;
static void rygel_seek_finalize (GObject* obj);
static void rygel_seek_get_property (GObject * object, guint property_id, GValue * value, GParamSpec * pspec);
static void rygel_seek_set_property (GObject * object, guint property_id, const GValue * value, GParamSpec * pspec);



static void _rygel_http_response_on_request_aborted_soup_server_request_aborted (SoupServer* _sender, SoupMessage* msg, SoupClientContext* client, gpointer self) {
	rygel_http_response_on_request_aborted (self, _sender, msg, client);
}


RygelHTTPResponse* rygel_http_response_construct (GType object_type, SoupServer* server, SoupMessage* msg, gboolean partial) {
	RygelHTTPResponse * self;
	SoupMessage* _tmp1_;
	SoupMessage* _tmp0_;
	g_return_val_if_fail (server != NULL, NULL);
	g_return_val_if_fail (msg != NULL, NULL);
	self = g_object_newv (object_type, 0, NULL);
	rygel_http_response_set_server (self, server);
	_tmp1_ = NULL;
	_tmp0_ = NULL;
	self->msg = (_tmp1_ = (_tmp0_ = msg, (_tmp0_ == NULL) ? NULL : g_object_ref (_tmp0_)), (self->msg == NULL) ? NULL : (self->msg = (g_object_unref (self->msg), NULL)), _tmp1_);
	if (partial) {
		soup_message_set_status (self->msg, (guint) SOUP_STATUS_PARTIAL_CONTENT);
	} else {
		soup_message_set_status (self->msg, (guint) SOUP_STATUS_OK);
	}
	soup_message_body_set_accumulate (self->msg->response_body, FALSE);
	g_signal_connect_object (self->priv->_server, "request-aborted", (GCallback) _rygel_http_response_on_request_aborted_soup_server_request_aborted, self, 0);
	return self;
}


RygelHTTPResponse* rygel_http_response_new (SoupServer* server, SoupMessage* msg, gboolean partial) {
	return rygel_http_response_construct (RYGEL_TYPE_HTTP_RESPONSE, server, msg, partial);
}


static void _rygel_http_response_on_cancelled_g_cancellable_cancelled (GCancellable* _sender, gpointer self) {
	rygel_http_response_on_cancelled (self, _sender);
}


static void rygel_http_response_real_run (RygelHTTPResponse* self, GCancellable* cancellable) {
	g_return_if_fail (self != NULL);
	if (cancellable != NULL) {
		GCancellable* _tmp1_;
		GCancellable* _tmp0_;
		_tmp1_ = NULL;
		_tmp0_ = NULL;
		self->cancellable = (_tmp1_ = (_tmp0_ = cancellable, (_tmp0_ == NULL) ? NULL : g_object_ref (_tmp0_)), (self->cancellable == NULL) ? NULL : (self->cancellable = (g_object_unref (self->cancellable), NULL)), _tmp1_);
		g_signal_connect_object (cancellable, "cancelled", (GCallback) _rygel_http_response_on_cancelled_g_cancellable_cancelled, self, 0);
	}
}


void rygel_http_response_run (RygelHTTPResponse* self, GCancellable* cancellable) {
	RYGEL_HTTP_RESPONSE_GET_CLASS (self)->run (self, cancellable);
}


static void rygel_http_response_on_cancelled (RygelHTTPResponse* self, GCancellable* cancellable) {
	g_return_if_fail (self != NULL);
	g_return_if_fail (cancellable != NULL);
	rygel_http_response_end (self, TRUE, (guint) SOUP_STATUS_CANCELLED);
}


static void rygel_http_response_on_request_aborted (RygelHTTPResponse* self, SoupServer* server, SoupMessage* msg, SoupClientContext* client) {
	g_return_if_fail (self != NULL);
	g_return_if_fail (server != NULL);
	g_return_if_fail (msg != NULL);
	g_return_if_fail (client != NULL);
	/* Ignore if message isn't ours*/
	if (msg == self->msg) {
		rygel_http_response_end (self, TRUE, (guint) SOUP_STATUS_NONE);
	}
}


void rygel_http_response_push_data (RygelHTTPResponse* self, void* data, gsize length) {
	g_return_if_fail (self != NULL);
	soup_message_body_append (self->msg->response_body, SOUP_MEMORY_COPY, data, length);
	soup_server_unpause_message (self->priv->_server, self->msg);
}


static void rygel_http_response_real_end (RygelHTTPResponse* self, gboolean aborted, guint status) {
	g_return_if_fail (self != NULL);
	if (status != SOUP_STATUS_NONE) {
		soup_message_set_status (self->msg, status);
	}
	g_signal_emit_by_name ((RygelStateMachine*) self, "completed");
}


void rygel_http_response_end (RygelHTTPResponse* self, gboolean aborted, guint status) {
	RYGEL_HTTP_RESPONSE_GET_CLASS (self)->end (self, aborted, status);
}


SoupServer* rygel_http_response_get_server (RygelHTTPResponse* self) {
	g_return_val_if_fail (self != NULL, NULL);
	return self->priv->_server;
}


static void rygel_http_response_set_server (RygelHTTPResponse* self, SoupServer* value) {
	SoupServer* _tmp2_;
	SoupServer* _tmp1_;
	g_return_if_fail (self != NULL);
	_tmp2_ = NULL;
	_tmp1_ = NULL;
	self->priv->_server = (_tmp2_ = (_tmp1_ = value, (_tmp1_ == NULL) ? NULL : g_object_ref (_tmp1_)), (self->priv->_server == NULL) ? NULL : (self->priv->_server = (g_object_unref (self->priv->_server), NULL)), _tmp2_);
	g_object_notify ((GObject *) self, "server");
}


static void rygel_http_response_class_init (RygelHTTPResponseClass * klass) {
	rygel_http_response_parent_class = g_type_class_peek_parent (klass);
	g_type_class_add_private (klass, sizeof (RygelHTTPResponsePrivate));
	RYGEL_HTTP_RESPONSE_CLASS (klass)->run = rygel_http_response_real_run;
	RYGEL_HTTP_RESPONSE_CLASS (klass)->end = rygel_http_response_real_end;
	G_OBJECT_CLASS (klass)->get_property = rygel_http_response_get_property;
	G_OBJECT_CLASS (klass)->set_property = rygel_http_response_set_property;
	G_OBJECT_CLASS (klass)->finalize = rygel_http_response_finalize;
	g_object_class_install_property (G_OBJECT_CLASS (klass), RYGEL_HTTP_RESPONSE_SERVER, g_param_spec_object ("server", "server", "server", SOUP_TYPE_SERVER, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
}


static void rygel_http_response_rygel_state_machine_interface_init (RygelStateMachineIface * iface) {
	rygel_http_response_rygel_state_machine_parent_iface = g_type_interface_peek_parent (iface);
	iface->run = (void (*)(RygelStateMachine* ,GCancellable*)) rygel_http_response_run;
}


static void rygel_http_response_instance_init (RygelHTTPResponse * self) {
	self->priv = RYGEL_HTTP_RESPONSE_GET_PRIVATE (self);
}


static void rygel_http_response_finalize (GObject* obj) {
	RygelHTTPResponse * self;
	self = RYGEL_HTTP_RESPONSE (obj);
	(self->priv->_server == NULL) ? NULL : (self->priv->_server = (g_object_unref (self->priv->_server), NULL));
	(self->msg == NULL) ? NULL : (self->msg = (g_object_unref (self->msg), NULL));
	(self->cancellable == NULL) ? NULL : (self->cancellable = (g_object_unref (self->cancellable), NULL));
	G_OBJECT_CLASS (rygel_http_response_parent_class)->finalize (obj);
}


GType rygel_http_response_get_type (void) {
	static GType rygel_http_response_type_id = 0;
	if (rygel_http_response_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (RygelHTTPResponseClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) rygel_http_response_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (RygelHTTPResponse), 0, (GInstanceInitFunc) rygel_http_response_instance_init, NULL };
		static const GInterfaceInfo rygel_state_machine_info = { (GInterfaceInitFunc) rygel_http_response_rygel_state_machine_interface_init, (GInterfaceFinalizeFunc) NULL, NULL};
		rygel_http_response_type_id = g_type_register_static (G_TYPE_OBJECT, "RygelHTTPResponse", &g_define_type_info, G_TYPE_FLAG_ABSTRACT);
		g_type_add_interface_static (rygel_http_response_type_id, RYGEL_TYPE_STATE_MACHINE, &rygel_state_machine_info);
	}
	return rygel_http_response_type_id;
}


static void rygel_http_response_get_property (GObject * object, guint property_id, GValue * value, GParamSpec * pspec) {
	RygelHTTPResponse * self;
	gpointer boxed;
	self = RYGEL_HTTP_RESPONSE (object);
	switch (property_id) {
		case RYGEL_HTTP_RESPONSE_SERVER:
		g_value_set_object (value, rygel_http_response_get_server (self));
		break;
		default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}


static void rygel_http_response_set_property (GObject * object, guint property_id, const GValue * value, GParamSpec * pspec) {
	RygelHTTPResponse * self;
	self = RYGEL_HTTP_RESPONSE (object);
	switch (property_id) {
		case RYGEL_HTTP_RESPONSE_SERVER:
		rygel_http_response_set_server (self, g_value_get_object (value));
		break;
		default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}


RygelSeek* rygel_seek_construct (GType object_type, GstFormat format, gint64 start, gint64 stop) {
	RygelSeek * self;
	self = g_object_newv (object_type, 0, NULL);
	rygel_seek_set_format (self, format);
	rygel_seek_set_start (self, start);
	rygel_seek_set_stop (self, stop);
	return self;
}


RygelSeek* rygel_seek_new (GstFormat format, gint64 start, gint64 stop) {
	return rygel_seek_construct (RYGEL_TYPE_SEEK, format, start, stop);
}


GstFormat rygel_seek_get_format (RygelSeek* self) {
	g_return_val_if_fail (self != NULL, 0);
	return self->priv->_format;
}


static void rygel_seek_set_format (RygelSeek* self, GstFormat value) {
	g_return_if_fail (self != NULL);
	self->priv->_format = value;
	g_object_notify ((GObject *) self, "format");
}


gint64 rygel_seek_get_start (RygelSeek* self) {
	g_return_val_if_fail (self != NULL, 0LL);
	return self->priv->_start;
}


void rygel_seek_set_start (RygelSeek* self, gint64 value) {
	g_return_if_fail (self != NULL);
	self->priv->_start = value;
	rygel_seek_set_length (self, (rygel_seek_get_stop (self) - rygel_seek_get_start (self)) + 1);
	g_object_notify ((GObject *) self, "start");
}


gint64 rygel_seek_get_stop (RygelSeek* self) {
	g_return_val_if_fail (self != NULL, 0LL);
	return self->priv->_stop;
}


void rygel_seek_set_stop (RygelSeek* self, gint64 value) {
	g_return_if_fail (self != NULL);
	self->priv->_stop = value;
	rygel_seek_set_length (self, (rygel_seek_get_stop (self) - rygel_seek_get_start (self)) + 1);
	g_object_notify ((GObject *) self, "stop");
}


gint64 rygel_seek_get_length (RygelSeek* self) {
	g_return_val_if_fail (self != NULL, 0LL);
	return self->priv->_length;
}


static void rygel_seek_set_length (RygelSeek* self, gint64 value) {
	g_return_if_fail (self != NULL);
	self->priv->_length = value;
	g_object_notify ((GObject *) self, "length");
}


static void rygel_seek_class_init (RygelSeekClass * klass) {
	rygel_seek_parent_class = g_type_class_peek_parent (klass);
	g_type_class_add_private (klass, sizeof (RygelSeekPrivate));
	G_OBJECT_CLASS (klass)->get_property = rygel_seek_get_property;
	G_OBJECT_CLASS (klass)->set_property = rygel_seek_set_property;
	G_OBJECT_CLASS (klass)->finalize = rygel_seek_finalize;
	g_object_class_install_property (G_OBJECT_CLASS (klass), RYGEL_SEEK_FORMAT, g_param_spec_enum ("format", "format", "format", GST_TYPE_FORMAT, 0, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
	g_object_class_install_property (G_OBJECT_CLASS (klass), RYGEL_SEEK_START, g_param_spec_int64 ("start", "start", "start", G_MININT64, G_MAXINT64, 0, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
	g_object_class_install_property (G_OBJECT_CLASS (klass), RYGEL_SEEK_STOP, g_param_spec_int64 ("stop", "stop", "stop", G_MININT64, G_MAXINT64, 0, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
	g_object_class_install_property (G_OBJECT_CLASS (klass), RYGEL_SEEK_LENGTH, g_param_spec_int64 ("length", "length", "length", G_MININT64, G_MAXINT64, 0, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
}


static void rygel_seek_instance_init (RygelSeek * self) {
	self->priv = RYGEL_SEEK_GET_PRIVATE (self);
}


static void rygel_seek_finalize (GObject* obj) {
	RygelSeek * self;
	self = RYGEL_SEEK (obj);
	G_OBJECT_CLASS (rygel_seek_parent_class)->finalize (obj);
}


GType rygel_seek_get_type (void) {
	static GType rygel_seek_type_id = 0;
	if (rygel_seek_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (RygelSeekClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) rygel_seek_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (RygelSeek), 0, (GInstanceInitFunc) rygel_seek_instance_init, NULL };
		rygel_seek_type_id = g_type_register_static (G_TYPE_OBJECT, "RygelSeek", &g_define_type_info, 0);
	}
	return rygel_seek_type_id;
}


static void rygel_seek_get_property (GObject * object, guint property_id, GValue * value, GParamSpec * pspec) {
	RygelSeek * self;
	gpointer boxed;
	self = RYGEL_SEEK (object);
	switch (property_id) {
		case RYGEL_SEEK_FORMAT:
		g_value_set_enum (value, rygel_seek_get_format (self));
		break;
		case RYGEL_SEEK_START:
		g_value_set_int64 (value, rygel_seek_get_start (self));
		break;
		case RYGEL_SEEK_STOP:
		g_value_set_int64 (value, rygel_seek_get_stop (self));
		break;
		case RYGEL_SEEK_LENGTH:
		g_value_set_int64 (value, rygel_seek_get_length (self));
		break;
		default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}


static void rygel_seek_set_property (GObject * object, guint property_id, const GValue * value, GParamSpec * pspec) {
	RygelSeek * self;
	self = RYGEL_SEEK (object);
	switch (property_id) {
		case RYGEL_SEEK_FORMAT:
		rygel_seek_set_format (self, g_value_get_enum (value));
		break;
		case RYGEL_SEEK_START:
		rygel_seek_set_start (self, g_value_get_int64 (value));
		break;
		case RYGEL_SEEK_STOP:
		rygel_seek_set_stop (self, g_value_get_int64 (value));
		break;
		case RYGEL_SEEK_LENGTH:
		rygel_seek_set_length (self, g_value_get_int64 (value));
		break;
		default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}




