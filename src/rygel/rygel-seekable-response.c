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
#include <gio/gio.h>
#include <libsoup/soup.h>
#include <stdlib.h>
#include <string.h>


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

#define RYGEL_TYPE_SEEKABLE_RESPONSE (rygel_seekable_response_get_type ())
#define RYGEL_SEEKABLE_RESPONSE(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_SEEKABLE_RESPONSE, RygelSeekableResponse))
#define RYGEL_SEEKABLE_RESPONSE_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_SEEKABLE_RESPONSE, RygelSeekableResponseClass))
#define RYGEL_IS_SEEKABLE_RESPONSE(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_SEEKABLE_RESPONSE))
#define RYGEL_IS_SEEKABLE_RESPONSE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_SEEKABLE_RESPONSE))
#define RYGEL_SEEKABLE_RESPONSE_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_SEEKABLE_RESPONSE, RygelSeekableResponseClass))

typedef struct _RygelSeekableResponse RygelSeekableResponse;
typedef struct _RygelSeekableResponseClass RygelSeekableResponseClass;
typedef struct _RygelSeekableResponsePrivate RygelSeekableResponsePrivate;

#define RYGEL_TYPE_SEEK (rygel_seek_get_type ())
#define RYGEL_SEEK(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_SEEK, RygelSeek))
#define RYGEL_SEEK_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_SEEK, RygelSeekClass))
#define RYGEL_IS_SEEK(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_SEEK))
#define RYGEL_IS_SEEK_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_SEEK))
#define RYGEL_SEEK_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_SEEK, RygelSeekClass))

typedef struct _RygelSeek RygelSeek;
typedef struct _RygelSeekClass RygelSeekClass;

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

struct _RygelSeekableResponse {
	RygelHTTPResponse parent_instance;
	RygelSeekableResponsePrivate * priv;
};

struct _RygelSeekableResponseClass {
	RygelHTTPResponseClass parent_class;
};

struct _RygelSeekableResponsePrivate {
	RygelSeek* seek;
	GFile* file;
	GFileInputStream* input_stream;
	gchar* buffer;
	gint buffer_length1;
	gint buffer_size;
	gsize total_length;
	gint priority;
};



GType rygel_state_machine_get_type (void);
GType rygel_http_response_get_type (void);
GType rygel_seekable_response_get_type (void);
GType rygel_seek_get_type (void);
#define RYGEL_SEEKABLE_RESPONSE_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), RYGEL_TYPE_SEEKABLE_RESPONSE, RygelSeekableResponsePrivate))
enum  {
	RYGEL_SEEKABLE_RESPONSE_DUMMY_PROPERTY
};
#define RYGEL_SEEKABLE_RESPONSE_BUFFER_LENGTH (gsize) 4096
RygelHTTPResponse* rygel_http_response_new (SoupServer* server, SoupMessage* msg, gboolean partial);
RygelHTTPResponse* rygel_http_response_construct (GType object_type, SoupServer* server, SoupMessage* msg, gboolean partial);
static gint rygel_seekable_response_get_requested_priority (RygelSeekableResponse* self);
gint64 rygel_seek_get_length (RygelSeek* self);
static void rygel_seekable_response_on_wrote_chunk (RygelSeekableResponse* self, SoupMessage* msg);
static void _rygel_seekable_response_on_wrote_chunk_soup_message_wrote_chunk (SoupMessage* _sender, gpointer self);
RygelSeekableResponse* rygel_seekable_response_new (SoupServer* server, SoupMessage* msg, const char* uri, RygelSeek* seek, gsize file_length);
RygelSeekableResponse* rygel_seekable_response_construct (GType object_type, SoupServer* server, SoupMessage* msg, const char* uri, RygelSeek* seek, gsize file_length);
RygelSeekableResponse* rygel_seekable_response_new (SoupServer* server, SoupMessage* msg, const char* uri, RygelSeek* seek, gsize file_length);
static void rygel_seekable_response_on_file_read (RygelSeekableResponse* self, GObject* source_object, GAsyncResult* _result_);
static void _rygel_seekable_response_on_file_read_gasync_ready_callback (GObject* source_object, GAsyncResult* res, gpointer self);
static void rygel_seekable_response_real_run (RygelHTTPResponse* base, GCancellable* cancellable);
void rygel_http_response_end (RygelHTTPResponse* self, gboolean aborted, guint status);
gint64 rygel_seek_get_start (RygelSeek* self);
gint64 rygel_seek_get_stop (RygelSeek* self);
static void rygel_seekable_response_on_contents_read (RygelSeekableResponse* self, GObject* source_object, GAsyncResult* _result_);
static void _rygel_seekable_response_on_contents_read_gasync_ready_callback (GObject* source_object, GAsyncResult* res, gpointer self);
void rygel_http_response_push_data (RygelHTTPResponse* self, void* data, gsize length);
static void rygel_seekable_response_on_input_stream_closed (RygelSeekableResponse* self, GObject* source_object, GAsyncResult* _result_);
static void _rygel_seekable_response_on_input_stream_closed_gasync_ready_callback (GObject* source_object, GAsyncResult* res, gpointer self);
static gpointer rygel_seekable_response_parent_class = NULL;
static void rygel_seekable_response_finalize (GObject* obj);
static int _vala_strcmp0 (const char * str1, const char * str2);



static void _rygel_seekable_response_on_wrote_chunk_soup_message_wrote_chunk (SoupMessage* _sender, gpointer self) {
	rygel_seekable_response_on_wrote_chunk (self, _sender);
}


RygelSeekableResponse* rygel_seekable_response_construct (GType object_type, SoupServer* server, SoupMessage* msg, const char* uri, RygelSeek* seek, gsize file_length) {
	RygelSeekableResponse * self;
	RygelSeek* _tmp1_;
	RygelSeek* _tmp0_;
	gchar* _tmp2_;
	GFile* _tmp3_;
	g_return_val_if_fail (server != NULL, NULL);
	g_return_val_if_fail (msg != NULL, NULL);
	g_return_val_if_fail (uri != NULL, NULL);
	self = (RygelSeekableResponse*) rygel_http_response_construct (object_type, server, msg, seek != NULL);
	_tmp1_ = NULL;
	_tmp0_ = NULL;
	self->priv->seek = (_tmp1_ = (_tmp0_ = seek, (_tmp0_ == NULL) ? NULL : g_object_ref (_tmp0_)), (self->priv->seek == NULL) ? NULL : (self->priv->seek = (g_object_unref (self->priv->seek), NULL)), _tmp1_);
	self->priv->total_length = file_length;
	self->priv->priority = rygel_seekable_response_get_requested_priority (self);
	if (seek != NULL) {
		self->priv->total_length = (gsize) rygel_seek_get_length (seek);
	} else {
		self->priv->total_length = file_length;
	}
	g_signal_connect_object (msg, "wrote-chunk", (GCallback) _rygel_seekable_response_on_wrote_chunk_soup_message_wrote_chunk, self, 0);
	_tmp2_ = NULL;
	self->priv->buffer = (_tmp2_ = g_new0 (gchar, RYGEL_SEEKABLE_RESPONSE_BUFFER_LENGTH), self->priv->buffer = (g_free (self->priv->buffer), NULL), self->priv->buffer_length1 = RYGEL_SEEKABLE_RESPONSE_BUFFER_LENGTH, self->priv->buffer_size = self->priv->buffer_length1, _tmp2_);
	_tmp3_ = NULL;
	self->priv->file = (_tmp3_ = g_file_new_for_uri (uri), (self->priv->file == NULL) ? NULL : (self->priv->file = (g_object_unref (self->priv->file), NULL)), _tmp3_);
	return self;
}


RygelSeekableResponse* rygel_seekable_response_new (SoupServer* server, SoupMessage* msg, const char* uri, RygelSeek* seek, gsize file_length) {
	return rygel_seekable_response_construct (RYGEL_TYPE_SEEKABLE_RESPONSE, server, msg, uri, seek, file_length);
}


static void _rygel_seekable_response_on_file_read_gasync_ready_callback (GObject* source_object, GAsyncResult* res, gpointer self) {
	rygel_seekable_response_on_file_read (self, source_object, res);
}


static void rygel_seekable_response_real_run (RygelHTTPResponse* base, GCancellable* cancellable) {
	RygelSeekableResponse * self;
	GCancellable* _tmp1_;
	GCancellable* _tmp0_;
	self = (RygelSeekableResponse*) base;
	_tmp1_ = NULL;
	_tmp0_ = NULL;
	((RygelHTTPResponse*) self)->cancellable = (_tmp1_ = (_tmp0_ = cancellable, (_tmp0_ == NULL) ? NULL : g_object_ref (_tmp0_)), (((RygelHTTPResponse*) self)->cancellable == NULL) ? NULL : (((RygelHTTPResponse*) self)->cancellable = (g_object_unref (((RygelHTTPResponse*) self)->cancellable), NULL)), _tmp1_);
	g_file_read_async (self->priv->file, self->priv->priority, cancellable, _rygel_seekable_response_on_file_read_gasync_ready_callback, self);
}


static void _rygel_seekable_response_on_contents_read_gasync_ready_callback (GObject* source_object, GAsyncResult* res, gpointer self) {
	rygel_seekable_response_on_contents_read (self, source_object, res);
}


static void rygel_seekable_response_on_file_read (RygelSeekableResponse* self, GObject* source_object, GAsyncResult* _result_) {
	GError * _inner_error_;
	g_return_if_fail (self != NULL);
	g_return_if_fail (source_object != NULL);
	g_return_if_fail (_result_ != NULL);
	_inner_error_ = NULL;
	{
		GFileInputStream* _tmp0_;
		GFileInputStream* _tmp1_;
		_tmp0_ = g_file_read_finish (self->priv->file, _result_, &_inner_error_);
		if (_inner_error_ != NULL) {
			goto __catch12_g_error;
			goto __finally12;
		}
		_tmp1_ = NULL;
		self->priv->input_stream = (_tmp1_ = _tmp0_, (self->priv->input_stream == NULL) ? NULL : (self->priv->input_stream = (g_object_unref (self->priv->input_stream), NULL)), _tmp1_);
	}
	goto __finally12;
	__catch12_g_error:
	{
		GError * err;
		err = _inner_error_;
		_inner_error_ = NULL;
		{
			char* _tmp2_;
			_tmp2_ = NULL;
			g_warning ("rygel-seekable-response.vala:74: Failed to read from URI: %s: %s\n", _tmp2_ = g_file_get_uri (self->priv->file), err->message);
			_tmp2_ = (g_free (_tmp2_), NULL);
			rygel_http_response_end ((RygelHTTPResponse*) self, FALSE, (guint) SOUP_STATUS_NOT_FOUND);
			(err == NULL) ? NULL : (err = (g_error_free (err), NULL));
			return;
		}
	}
	__finally12:
	if (_inner_error_ != NULL) {
		g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, _inner_error_->message);
		g_clear_error (&_inner_error_);
		return;
	}
	if (self->priv->seek != NULL) {
		{
			G_FILE_INPUT_STREAM_GET_CLASS (self->priv->input_stream)->seek (self->priv->input_stream, rygel_seek_get_start (self->priv->seek), G_SEEK_SET, ((RygelHTTPResponse*) self)->cancellable, &_inner_error_);
			if (_inner_error_ != NULL) {
				goto __catch13_g_error;
				goto __finally13;
			}
		}
		goto __finally13;
		__catch13_g_error:
		{
			GError * err;
			err = _inner_error_;
			_inner_error_ = NULL;
			{
				char* _tmp5_;
				char* _tmp4_;
				char* _tmp3_;
				_tmp5_ = NULL;
				_tmp4_ = NULL;
				_tmp3_ = NULL;
				g_warning ("rygel-seekable-response.vala:87: Failed to seek to %s-%s on URI %s: %s\n", _tmp3_ = g_strdup_printf ("%lli", rygel_seek_get_start (self->priv->seek)), _tmp4_ = g_strdup_printf ("%lli", rygel_seek_get_stop (self->priv->seek)), _tmp5_ = g_file_get_uri (self->priv->file), err->message);
				_tmp5_ = (g_free (_tmp5_), NULL);
				_tmp4_ = (g_free (_tmp4_), NULL);
				_tmp3_ = (g_free (_tmp3_), NULL);
				rygel_http_response_end ((RygelHTTPResponse*) self, FALSE, (guint) SOUP_STATUS_REQUESTED_RANGE_NOT_SATISFIABLE);
				(err == NULL) ? NULL : (err = (g_error_free (err), NULL));
				return;
			}
		}
		__finally13:
		if (_inner_error_ != NULL) {
			g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, _inner_error_->message);
			g_clear_error (&_inner_error_);
			return;
		}
	}
	g_input_stream_read_async ((GInputStream*) self->priv->input_stream, self->priv->buffer, RYGEL_SEEKABLE_RESPONSE_BUFFER_LENGTH, self->priv->priority, ((RygelHTTPResponse*) self)->cancellable, _rygel_seekable_response_on_contents_read_gasync_ready_callback, self);
}


static void _rygel_seekable_response_on_input_stream_closed_gasync_ready_callback (GObject* source_object, GAsyncResult* res, gpointer self) {
	rygel_seekable_response_on_input_stream_closed (self, source_object, res);
}


static void rygel_seekable_response_on_contents_read (RygelSeekableResponse* self, GObject* source_object, GAsyncResult* _result_) {
	GError * _inner_error_;
	GFileInputStream* _tmp0_;
	GFileInputStream* input_stream;
	gssize bytes_read;
	g_return_if_fail (self != NULL);
	g_return_if_fail (source_object != NULL);
	g_return_if_fail (_result_ != NULL);
	_inner_error_ = NULL;
	_tmp0_ = NULL;
	input_stream = (_tmp0_ = G_FILE_INPUT_STREAM (source_object), (_tmp0_ == NULL) ? NULL : g_object_ref (_tmp0_));
	bytes_read = 0L;
	{
		gssize _tmp1_;
		_tmp1_ = g_input_stream_read_finish ((GInputStream*) input_stream, _result_, &_inner_error_);
		if (_inner_error_ != NULL) {
			goto __catch14_g_error;
			goto __finally14;
		}
		bytes_read = _tmp1_;
	}
	goto __finally14;
	__catch14_g_error:
	{
		GError * err;
		err = _inner_error_;
		_inner_error_ = NULL;
		{
			char* _tmp2_;
			_tmp2_ = NULL;
			g_warning ("rygel-seekable-response.vala:113: Failed to read contents from URI: %s: %s\n", _tmp2_ = g_file_get_uri (self->priv->file), err->message);
			_tmp2_ = (g_free (_tmp2_), NULL);
			rygel_http_response_end ((RygelHTTPResponse*) self, FALSE, (guint) SOUP_STATUS_NOT_FOUND);
			(err == NULL) ? NULL : (err = (g_error_free (err), NULL));
			(input_stream == NULL) ? NULL : (input_stream = (g_object_unref (input_stream), NULL));
			return;
		}
	}
	__finally14:
	if (_inner_error_ != NULL) {
		(input_stream == NULL) ? NULL : (input_stream = (g_object_unref (input_stream), NULL));
		g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, _inner_error_->message);
		g_clear_error (&_inner_error_);
		return;
	}
	if (bytes_read > 0) {
		rygel_http_response_push_data ((RygelHTTPResponse*) self, self->priv->buffer, (gsize) bytes_read);
	} else {
		g_input_stream_close_async ((GInputStream*) input_stream, self->priv->priority, ((RygelHTTPResponse*) self)->cancellable, _rygel_seekable_response_on_input_stream_closed_gasync_ready_callback, self);
	}
	(input_stream == NULL) ? NULL : (input_stream = (g_object_unref (input_stream), NULL));
}


static void rygel_seekable_response_on_input_stream_closed (RygelSeekableResponse* self, GObject* source_object, GAsyncResult* _result_) {
	GError * _inner_error_;
	GFileInputStream* _tmp0_;
	GFileInputStream* input_stream;
	g_return_if_fail (self != NULL);
	g_return_if_fail (source_object != NULL);
	g_return_if_fail (_result_ != NULL);
	_inner_error_ = NULL;
	_tmp0_ = NULL;
	input_stream = (_tmp0_ = G_FILE_INPUT_STREAM (source_object), (_tmp0_ == NULL) ? NULL : g_object_ref (_tmp0_));
	{
		g_input_stream_close_finish ((GInputStream*) input_stream, _result_, &_inner_error_);
		if (_inner_error_ != NULL) {
			goto __catch15_g_error;
			goto __finally15;
		}
	}
	goto __finally15;
	__catch15_g_error:
	{
		GError * err;
		err = _inner_error_;
		_inner_error_ = NULL;
		{
			char* _tmp1_;
			_tmp1_ = NULL;
			g_warning ("rygel-seekable-response.vala:136: Failed to close stream to URI %s: %s\n", _tmp1_ = g_file_get_uri (self->priv->file), err->message);
			_tmp1_ = (g_free (_tmp1_), NULL);
			(err == NULL) ? NULL : (err = (g_error_free (err), NULL));
		}
	}
	__finally15:
	if (_inner_error_ != NULL) {
		(input_stream == NULL) ? NULL : (input_stream = (g_object_unref (input_stream), NULL));
		g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, _inner_error_->message);
		g_clear_error (&_inner_error_);
		return;
	}
	rygel_http_response_end ((RygelHTTPResponse*) self, FALSE, (guint) SOUP_STATUS_NONE);
	(input_stream == NULL) ? NULL : (input_stream = (g_object_unref (input_stream), NULL));
}


static void rygel_seekable_response_on_wrote_chunk (RygelSeekableResponse* self, SoupMessage* msg) {
	g_return_if_fail (self != NULL);
	g_return_if_fail (msg != NULL);
	g_input_stream_read_async ((GInputStream*) self->priv->input_stream, self->priv->buffer, RYGEL_SEEKABLE_RESPONSE_BUFFER_LENGTH, self->priv->priority, ((RygelHTTPResponse*) self)->cancellable, _rygel_seekable_response_on_contents_read_gasync_ready_callback, self);
}


static gint rygel_seekable_response_get_requested_priority (RygelSeekableResponse* self) {
	const char* _tmp0_;
	char* mode;
	gboolean _tmp1_;
	g_return_val_if_fail (self != NULL, 0);
	_tmp0_ = NULL;
	mode = (_tmp0_ = soup_message_headers_get (((RygelHTTPResponse*) self)->msg->request_headers, "transferMode.dlna.org"), (_tmp0_ == NULL) ? NULL : g_strdup (_tmp0_));
	_tmp1_ = FALSE;
	if (mode == NULL) {
		_tmp1_ = TRUE;
	} else {
		_tmp1_ = _vala_strcmp0 (mode, "Interactive") == 0;
	}
	if (_tmp1_) {
		gint _tmp2_;
		return (_tmp2_ = G_PRIORITY_DEFAULT, mode = (g_free (mode), NULL), _tmp2_);
	} else {
		if (_vala_strcmp0 (mode, "Streaming") == 0) {
			gint _tmp3_;
			return (_tmp3_ = G_PRIORITY_HIGH, mode = (g_free (mode), NULL), _tmp3_);
		} else {
			if (_vala_strcmp0 (mode, "Background") == 0) {
				gint _tmp4_;
				return (_tmp4_ = G_PRIORITY_LOW, mode = (g_free (mode), NULL), _tmp4_);
			} else {
				gint _tmp5_;
				return (_tmp5_ = G_PRIORITY_DEFAULT, mode = (g_free (mode), NULL), _tmp5_);
			}
		}
	}
	mode = (g_free (mode), NULL);
}


static void rygel_seekable_response_class_init (RygelSeekableResponseClass * klass) {
	rygel_seekable_response_parent_class = g_type_class_peek_parent (klass);
	g_type_class_add_private (klass, sizeof (RygelSeekableResponsePrivate));
	RYGEL_HTTP_RESPONSE_CLASS (klass)->run = rygel_seekable_response_real_run;
	G_OBJECT_CLASS (klass)->finalize = rygel_seekable_response_finalize;
}


static void rygel_seekable_response_instance_init (RygelSeekableResponse * self) {
	self->priv = RYGEL_SEEKABLE_RESPONSE_GET_PRIVATE (self);
}


static void rygel_seekable_response_finalize (GObject* obj) {
	RygelSeekableResponse * self;
	self = RYGEL_SEEKABLE_RESPONSE (obj);
	(self->priv->seek == NULL) ? NULL : (self->priv->seek = (g_object_unref (self->priv->seek), NULL));
	(self->priv->file == NULL) ? NULL : (self->priv->file = (g_object_unref (self->priv->file), NULL));
	(self->priv->input_stream == NULL) ? NULL : (self->priv->input_stream = (g_object_unref (self->priv->input_stream), NULL));
	self->priv->buffer = (g_free (self->priv->buffer), NULL);
	G_OBJECT_CLASS (rygel_seekable_response_parent_class)->finalize (obj);
}


GType rygel_seekable_response_get_type (void) {
	static GType rygel_seekable_response_type_id = 0;
	if (rygel_seekable_response_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (RygelSeekableResponseClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) rygel_seekable_response_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (RygelSeekableResponse), 0, (GInstanceInitFunc) rygel_seekable_response_instance_init, NULL };
		rygel_seekable_response_type_id = g_type_register_static (RYGEL_TYPE_HTTP_RESPONSE, "RygelSeekableResponse", &g_define_type_info, 0);
	}
	return rygel_seekable_response_type_id;
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




