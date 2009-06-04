/*
 * Copyright (C) 2008 Zeeshan Ali <zeenix@gmail.com>.
 * Copyright (C) 2007 OpenedHand Ltd.
 *
 * Author: Zeeshan Ali <zeenix@gmail.com>
 *         Jorn Baayen <jorn@openedhand.com>
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
#include <stdlib.h>
#include <string.h>
#include <libgupnp/gupnp.h>
#include <libgupnp-av/gupnp-av.h>
#include <gee/list.h>
#include <gee/collection.h>


#define RYGEL_TYPE_STATE_MACHINE (rygel_state_machine_get_type ())
#define RYGEL_STATE_MACHINE(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_STATE_MACHINE, RygelStateMachine))
#define RYGEL_IS_STATE_MACHINE(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_STATE_MACHINE))
#define RYGEL_STATE_MACHINE_GET_INTERFACE(obj) (G_TYPE_INSTANCE_GET_INTERFACE ((obj), RYGEL_TYPE_STATE_MACHINE, RygelStateMachineIface))

typedef struct _RygelStateMachine RygelStateMachine;
typedef struct _RygelStateMachineIface RygelStateMachineIface;

#define RYGEL_TYPE_BROWSE (rygel_browse_get_type ())
#define RYGEL_BROWSE(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_BROWSE, RygelBrowse))
#define RYGEL_BROWSE_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_BROWSE, RygelBrowseClass))
#define RYGEL_IS_BROWSE(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_BROWSE))
#define RYGEL_IS_BROWSE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_BROWSE))
#define RYGEL_BROWSE_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_BROWSE, RygelBrowseClass))

typedef struct _RygelBrowse RygelBrowse;
typedef struct _RygelBrowseClass RygelBrowseClass;
typedef struct _RygelBrowsePrivate RygelBrowsePrivate;

#define RYGEL_TYPE_MEDIA_OBJECT (rygel_media_object_get_type ())
#define RYGEL_MEDIA_OBJECT(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_MEDIA_OBJECT, RygelMediaObject))
#define RYGEL_MEDIA_OBJECT_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_MEDIA_OBJECT, RygelMediaObjectClass))
#define RYGEL_IS_MEDIA_OBJECT(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_MEDIA_OBJECT))
#define RYGEL_IS_MEDIA_OBJECT_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_MEDIA_OBJECT))
#define RYGEL_MEDIA_OBJECT_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_MEDIA_OBJECT, RygelMediaObjectClass))

typedef struct _RygelMediaObject RygelMediaObject;
typedef struct _RygelMediaObjectClass RygelMediaObjectClass;

#define RYGEL_TYPE_MEDIA_CONTAINER (rygel_media_container_get_type ())
#define RYGEL_MEDIA_CONTAINER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_MEDIA_CONTAINER, RygelMediaContainer))
#define RYGEL_MEDIA_CONTAINER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_MEDIA_CONTAINER, RygelMediaContainerClass))
#define RYGEL_IS_MEDIA_CONTAINER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_MEDIA_CONTAINER))
#define RYGEL_IS_MEDIA_CONTAINER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_MEDIA_CONTAINER))
#define RYGEL_MEDIA_CONTAINER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_MEDIA_CONTAINER, RygelMediaContainerClass))

typedef struct _RygelMediaContainer RygelMediaContainer;
typedef struct _RygelMediaContainerClass RygelMediaContainerClass;

#define RYGEL_TYPE_DIDL_LITE_WRITER (rygel_didl_lite_writer_get_type ())
#define RYGEL_DIDL_LITE_WRITER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_DIDL_LITE_WRITER, RygelDIDLLiteWriter))
#define RYGEL_DIDL_LITE_WRITER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_DIDL_LITE_WRITER, RygelDIDLLiteWriterClass))
#define RYGEL_IS_DIDL_LITE_WRITER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_DIDL_LITE_WRITER))
#define RYGEL_IS_DIDL_LITE_WRITER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_DIDL_LITE_WRITER))
#define RYGEL_DIDL_LITE_WRITER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_DIDL_LITE_WRITER, RygelDIDLLiteWriterClass))

typedef struct _RygelDIDLLiteWriter RygelDIDLLiteWriter;
typedef struct _RygelDIDLLiteWriterClass RygelDIDLLiteWriterClass;

#define RYGEL_TYPE_CONTENT_DIRECTORY (rygel_content_directory_get_type ())
#define RYGEL_CONTENT_DIRECTORY(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_CONTENT_DIRECTORY, RygelContentDirectory))
#define RYGEL_CONTENT_DIRECTORY_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_CONTENT_DIRECTORY, RygelContentDirectoryClass))
#define RYGEL_IS_CONTENT_DIRECTORY(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_CONTENT_DIRECTORY))
#define RYGEL_IS_CONTENT_DIRECTORY_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_CONTENT_DIRECTORY))
#define RYGEL_CONTENT_DIRECTORY_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_CONTENT_DIRECTORY, RygelContentDirectoryClass))

typedef struct _RygelContentDirectory RygelContentDirectory;
typedef struct _RygelContentDirectoryClass RygelContentDirectoryClass;
typedef struct _RygelContentDirectoryPrivate RygelContentDirectoryPrivate;

#define RYGEL_TYPE_TRANSCODE_MANAGER (rygel_transcode_manager_get_type ())
#define RYGEL_TRANSCODE_MANAGER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_TRANSCODE_MANAGER, RygelTranscodeManager))
#define RYGEL_TRANSCODE_MANAGER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_TRANSCODE_MANAGER, RygelTranscodeManagerClass))
#define RYGEL_IS_TRANSCODE_MANAGER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_TRANSCODE_MANAGER))
#define RYGEL_IS_TRANSCODE_MANAGER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_TRANSCODE_MANAGER))
#define RYGEL_TRANSCODE_MANAGER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_TRANSCODE_MANAGER, RygelTranscodeManagerClass))

typedef struct _RygelTranscodeManager RygelTranscodeManager;
typedef struct _RygelTranscodeManagerClass RygelTranscodeManagerClass;

#define RYGEL_TYPE_HTTP_SERVER (rygel_http_server_get_type ())
#define RYGEL_HTTP_SERVER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_HTTP_SERVER, RygelHTTPServer))
#define RYGEL_HTTP_SERVER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_HTTP_SERVER, RygelHTTPServerClass))
#define RYGEL_IS_HTTP_SERVER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_HTTP_SERVER))
#define RYGEL_IS_HTTP_SERVER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_HTTP_SERVER))
#define RYGEL_HTTP_SERVER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_HTTP_SERVER, RygelHTTPServerClass))

typedef struct _RygelHTTPServer RygelHTTPServer;
typedef struct _RygelHTTPServerClass RygelHTTPServerClass;
typedef struct _RygelMediaObjectPrivate RygelMediaObjectPrivate;
typedef struct _RygelMediaContainerPrivate RygelMediaContainerPrivate;

/**
 * StateMachine interface.
 */
struct _RygelStateMachineIface {
	GTypeInterface parent_iface;
	void (*run) (RygelStateMachine* self, GCancellable* cancellable);
};

/**
 * Browse action implementation. This class is more or less the state-machine
 * associated with the Browse action handling that exists to make asynchronous
 * handling of Browse action possible.
 */
struct _RygelBrowse {
	GObject parent_instance;
	RygelBrowsePrivate * priv;
	char* object_id;
	char* browse_flag;
	char* filter;
	guint index;
	guint requested_count;
	char* sort_criteria;
	guint number_returned;
	guint total_matches;
	guint update_id;
};

struct _RygelBrowseClass {
	GObjectClass parent_class;
};

struct _RygelBrowsePrivate {
	gboolean fetch_metadata;
	RygelMediaObject* media_object;
	RygelMediaContainer* root_container;
	guint32 system_update_id;
	GUPnPServiceAction* action;
	RygelDIDLLiteWriter* didl_writer;
	GCancellable* cancellable;
};

/**
 * Basic implementation of UPnP ContentDirectory service version 2. Most often
 * plugins will provide a child of this class. The inheriting classes should
 * override create_root_container method.
 */
struct _RygelContentDirectory {
	GUPnPService parent_instance;
	RygelContentDirectoryPrivate * priv;
	char* feature_list;
	char* search_caps;
	char* sort_caps;
	RygelHTTPServer* http_server;
	RygelMediaContainer* root_container;
	GCancellable* cancellable;
	guint32 system_update_id;
};

struct _RygelContentDirectoryClass {
	GUPnPServiceClass parent_class;
	RygelMediaContainer* (*create_root_container) (RygelContentDirectory* self);
	void (*browse_cb) (RygelContentDirectory* self, RygelContentDirectory* content_dir, GUPnPServiceAction* action);
};

/**
 * Errors used by ContentDirectory and deriving classes.
 */
typedef enum  {
	RYGEL_CONTENT_DIRECTORY_ERROR_NO_SUCH_OBJECT = 701,
	RYGEL_CONTENT_DIRECTORY_ERROR_INVALID_ARGS = 402
} RygelContentDirectoryError;
#define RYGEL_CONTENT_DIRECTORY_ERROR rygel_content_directory_error_quark ()
/**
 * Represents a media object (container and item).
 */
struct _RygelMediaObject {
	GObject parent_instance;
	RygelMediaObjectPrivate * priv;
	char* id;
	char* title;
	RygelMediaContainer* parent;
};

struct _RygelMediaObjectClass {
	GObjectClass parent_class;
};

/**
 * Represents a container (folder) for media items and containers. Provides
 * basic serialization (to DIDLLiteWriter) implementation. Deriving classes
 * are supposed to provide working implementations of get_children and
 * find_object.
 */
struct _RygelMediaContainer {
	RygelMediaObject parent_instance;
	RygelMediaContainerPrivate * priv;
	guint child_count;
	guint32 update_id;
};

struct _RygelMediaContainerClass {
	RygelMediaObjectClass parent_class;
	void (*get_children) (RygelMediaContainer* self, guint offset, guint max_count, GCancellable* cancellable, GAsyncReadyCallback callback, void* callback_target);
	GeeList* (*get_children_finish) (RygelMediaContainer* self, GAsyncResult* res, GError** error);
	void (*find_object) (RygelMediaContainer* self, const char* id, GCancellable* cancellable, GAsyncReadyCallback callback, void* callback_target);
	RygelMediaObject* (*find_object_finish) (RygelMediaContainer* self, GAsyncResult* res, GError** error);
};



GType rygel_state_machine_get_type (void);
GType rygel_browse_get_type (void);
GType rygel_media_object_get_type (void);
GType rygel_media_container_get_type (void);
GType rygel_didl_lite_writer_get_type (void);
#define RYGEL_BROWSE_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), RYGEL_TYPE_BROWSE, RygelBrowsePrivate))
enum  {
	RYGEL_BROWSE_DUMMY_PROPERTY
};
GType rygel_content_directory_get_type (void);
GType rygel_transcode_manager_get_type (void);
GType rygel_http_server_get_type (void);
RygelDIDLLiteWriter* rygel_didl_lite_writer_new (RygelHTTPServer* http_server);
RygelDIDLLiteWriter* rygel_didl_lite_writer_construct (GType object_type, RygelHTTPServer* http_server);
RygelBrowse* rygel_browse_new (RygelContentDirectory* content_dir, GUPnPServiceAction* action);
RygelBrowse* rygel_browse_construct (GType object_type, RygelContentDirectory* content_dir, GUPnPServiceAction* action);
RygelBrowse* rygel_browse_new (RygelContentDirectory* content_dir, GUPnPServiceAction* action);
static void rygel_browse_parse_args (RygelBrowse* self);
static void rygel_browse_real_run (RygelStateMachine* base, GCancellable* cancellable);
static void rygel_browse_handle_error (RygelBrowse* self, GError* _error_);
GQuark rygel_content_directory_error_quark (void);
static void rygel_browse_handle_metadata_request (RygelBrowse* self);
static void rygel_browse_handle_children_request (RygelBrowse* self);
static void rygel_browse_got_media_object (RygelBrowse* self);
void rygel_media_container_find_object (RygelMediaContainer* self, const char* id, GCancellable* cancellable, GAsyncReadyCallback callback, void* callback_target);
static void rygel_browse_on_media_object_found (RygelBrowse* self, GObject* source_object, GAsyncResult* res);
static void _rygel_browse_on_media_object_found_gasync_ready_callback (GObject* source_object, GAsyncResult* res, gpointer self);
static void rygel_browse_fetch_media_object (RygelBrowse* self);
RygelMediaObject* rygel_media_container_find_object_finish (RygelMediaContainer* self, GAsyncResult* res, GError** error);
void rygel_didl_lite_writer_serialize (RygelDIDLLiteWriter* self, RygelMediaObject* media_object, GError** error);
static void rygel_browse_conclude (RygelBrowse* self);
static void rygel_browse_fetch_children (RygelBrowse* self);
static void rygel_browse_serialize_children (RygelBrowse* self, GeeList* children);
void rygel_media_container_get_children (RygelMediaContainer* self, guint offset, guint max_count, GCancellable* cancellable, GAsyncReadyCallback callback, void* callback_target);
static void rygel_browse_on_children_fetched (RygelBrowse* self, GObject* source_object, GAsyncResult* res);
static void _rygel_browse_on_children_fetched_gasync_ready_callback (GObject* source_object, GAsyncResult* res, gpointer self);
GeeList* rygel_media_container_get_children_finish (RygelMediaContainer* self, GAsyncResult* res, GError** error);
static gpointer rygel_browse_parent_class = NULL;
static RygelStateMachineIface* rygel_browse_rygel_state_machine_parent_iface = NULL;
static void rygel_browse_finalize (GObject* obj);
static int _vala_strcmp0 (const char * str1, const char * str2);



RygelBrowse* rygel_browse_construct (GType object_type, RygelContentDirectory* content_dir, GUPnPServiceAction* action) {
	RygelBrowse * self;
	RygelMediaContainer* _tmp1_;
	RygelMediaContainer* _tmp0_;
	GUPnPServiceAction* _tmp2_;
	RygelDIDLLiteWriter* _tmp3_;
	g_return_val_if_fail (content_dir != NULL, NULL);
	g_return_val_if_fail (action != NULL, NULL);
	self = g_object_newv (object_type, 0, NULL);
	_tmp1_ = NULL;
	_tmp0_ = NULL;
	self->priv->root_container = (_tmp1_ = (_tmp0_ = content_dir->root_container, (_tmp0_ == NULL) ? NULL : g_object_ref (_tmp0_)), (self->priv->root_container == NULL) ? NULL : (self->priv->root_container = (g_object_unref (self->priv->root_container), NULL)), _tmp1_);
	self->priv->system_update_id = content_dir->system_update_id;
	_tmp2_ = NULL;
	self->priv->action = (_tmp2_ = action, action = NULL, _tmp2_);
	_tmp3_ = NULL;
	self->priv->didl_writer = (_tmp3_ = rygel_didl_lite_writer_new (content_dir->http_server), (self->priv->didl_writer == NULL) ? NULL : (self->priv->didl_writer = (g_object_unref (self->priv->didl_writer), NULL)), _tmp3_);
	return self;
}


RygelBrowse* rygel_browse_new (RygelContentDirectory* content_dir, GUPnPServiceAction* action) {
	return rygel_browse_construct (RYGEL_TYPE_BROWSE, content_dir, action);
}


static void rygel_browse_real_run (RygelStateMachine* base, GCancellable* cancellable) {
	RygelBrowse * self;
	GCancellable* _tmp1_;
	GCancellable* _tmp0_;
	self = (RygelBrowse*) base;
	_tmp1_ = NULL;
	_tmp0_ = NULL;
	self->priv->cancellable = (_tmp1_ = (_tmp0_ = cancellable, (_tmp0_ == NULL) ? NULL : g_object_ref (_tmp0_)), (self->priv->cancellable == NULL) ? NULL : (self->priv->cancellable = (g_object_unref (self->priv->cancellable), NULL)), _tmp1_);
	/* Start DIDL-Lite fragment */
	gupnp_didl_lite_writer_start_didl_lite ((GUPnPDIDLLiteWriter*) self->priv->didl_writer, NULL, NULL, TRUE);
	/* Start by parsing the 'in' arguments */
	rygel_browse_parse_args (self);
}


static void rygel_browse_got_media_object (RygelBrowse* self) {
	g_return_if_fail (self != NULL);
	if (self->priv->media_object == NULL) {
		GError* _tmp0_;
		_tmp0_ = NULL;
		rygel_browse_handle_error (self, _tmp0_ = g_error_new_literal (RYGEL_CONTENT_DIRECTORY_ERROR, RYGEL_CONTENT_DIRECTORY_ERROR_NO_SUCH_OBJECT, "No such object"));
		(_tmp0_ == NULL) ? NULL : (_tmp0_ = (g_error_free (_tmp0_), NULL));
		return;
	}
	if (self->priv->fetch_metadata) {
		/* BrowseMetadata*/
		rygel_browse_handle_metadata_request (self);
	} else {
		/* BrowseDirectChildren*/
		rygel_browse_handle_children_request (self);
	}
}


static void _rygel_browse_on_media_object_found_gasync_ready_callback (GObject* source_object, GAsyncResult* res, gpointer self) {
	rygel_browse_on_media_object_found (self, source_object, res);
}


static void rygel_browse_fetch_media_object (RygelBrowse* self) {
	g_return_if_fail (self != NULL);
	if (_vala_strcmp0 (self->object_id, ((RygelMediaObject*) self->priv->root_container)->id) == 0) {
		RygelMediaObject* _tmp1_;
		RygelMediaObject* _tmp0_;
		_tmp1_ = NULL;
		_tmp0_ = NULL;
		self->priv->media_object = (_tmp1_ = (_tmp0_ = (RygelMediaObject*) self->priv->root_container, (_tmp0_ == NULL) ? NULL : g_object_ref (_tmp0_)), (self->priv->media_object == NULL) ? NULL : (self->priv->media_object = (g_object_unref (self->priv->media_object), NULL)), _tmp1_);
		rygel_browse_got_media_object (self);
		return;
	}
	rygel_media_container_find_object (self->priv->root_container, self->object_id, self->priv->cancellable, _rygel_browse_on_media_object_found_gasync_ready_callback, self);
}


static void rygel_browse_on_media_object_found (RygelBrowse* self, GObject* source_object, GAsyncResult* res) {
	GError * _inner_error_;
	RygelMediaContainer* _tmp0_;
	RygelMediaContainer* container;
	g_return_if_fail (self != NULL);
	g_return_if_fail (source_object != NULL);
	g_return_if_fail (res != NULL);
	_inner_error_ = NULL;
	_tmp0_ = NULL;
	container = (_tmp0_ = RYGEL_MEDIA_CONTAINER (source_object), (_tmp0_ == NULL) ? NULL : g_object_ref (_tmp0_));
	{
		RygelMediaObject* _tmp1_;
		RygelMediaObject* _tmp2_;
		_tmp1_ = rygel_media_container_find_object_finish (container, res, &_inner_error_);
		if (_inner_error_ != NULL) {
			goto __catch19_g_error;
			goto __finally19;
		}
		_tmp2_ = NULL;
		self->priv->media_object = (_tmp2_ = _tmp1_, (self->priv->media_object == NULL) ? NULL : (self->priv->media_object = (g_object_unref (self->priv->media_object), NULL)), _tmp2_);
	}
	goto __finally19;
	__catch19_g_error:
	{
		GError * err;
		err = _inner_error_;
		_inner_error_ = NULL;
		{
			rygel_browse_handle_error (self, err);
			(err == NULL) ? NULL : (err = (g_error_free (err), NULL));
			(container == NULL) ? NULL : (container = (g_object_unref (container), NULL));
			return;
		}
	}
	__finally19:
	if (_inner_error_ != NULL) {
		(container == NULL) ? NULL : (container = (g_object_unref (container), NULL));
		g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, _inner_error_->message);
		g_clear_error (&_inner_error_);
		return;
	}
	rygel_browse_got_media_object (self);
	(container == NULL) ? NULL : (container = (g_object_unref (container), NULL));
}


static void rygel_browse_handle_metadata_request (RygelBrowse* self) {
	GError * _inner_error_;
	g_return_if_fail (self != NULL);
	_inner_error_ = NULL;
	if (RYGEL_IS_MEDIA_CONTAINER (self->priv->media_object)) {
		self->update_id = (guint) RYGEL_MEDIA_CONTAINER (self->priv->media_object)->update_id;
	} else {
		self->update_id = (guint) G_MAXUINT32;
	}
	{
		rygel_didl_lite_writer_serialize (self->priv->didl_writer, self->priv->media_object, &_inner_error_);
		if (_inner_error_ != NULL) {
			goto __catch20_g_error;
			goto __finally20;
		}
	}
	goto __finally20;
	__catch20_g_error:
	{
		GError * err;
		err = _inner_error_;
		_inner_error_ = NULL;
		{
			rygel_browse_handle_error (self, err);
			(err == NULL) ? NULL : (err = (g_error_free (err), NULL));
			return;
		}
	}
	__finally20:
	if (_inner_error_ != NULL) {
		g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, _inner_error_->message);
		g_clear_error (&_inner_error_);
		return;
	}
	self->number_returned = (guint) 1;
	self->total_matches = (guint) 1;
	/* Conclude the successful Browse action*/
	rygel_browse_conclude (self);
}


static void rygel_browse_handle_children_request (RygelBrowse* self) {
	RygelMediaContainer* _tmp1_;
	RygelMediaContainer* container;
	g_return_if_fail (self != NULL);
	if (!RYGEL_IS_MEDIA_CONTAINER (self->priv->media_object)) {
		GError* _tmp0_;
		_tmp0_ = NULL;
		rygel_browse_handle_error (self, _tmp0_ = g_error_new_literal (RYGEL_CONTENT_DIRECTORY_ERROR, RYGEL_CONTENT_DIRECTORY_ERROR_NO_SUCH_OBJECT, "No such object"));
		(_tmp0_ == NULL) ? NULL : (_tmp0_ = (g_error_free (_tmp0_), NULL));
		return;
	}
	_tmp1_ = NULL;
	container = (_tmp1_ = RYGEL_MEDIA_CONTAINER (self->priv->media_object), (_tmp1_ == NULL) ? NULL : g_object_ref (_tmp1_));
	self->total_matches = container->child_count;
	self->update_id = (guint) container->update_id;
	if (self->requested_count == 0) {
		/* No max count requested, try to fetch all children*/
		self->requested_count = self->total_matches;
	}
	rygel_browse_fetch_children (self);
	(container == NULL) ? NULL : (container = (g_object_unref (container), NULL));
}


static void rygel_browse_parse_args (RygelBrowse* self) {
	gboolean _tmp0_;
	g_return_if_fail (self != NULL);
	gupnp_service_action_get (self->priv->action, "ObjectID", G_TYPE_STRING, &self->object_id, "BrowseFlag", G_TYPE_STRING, &self->browse_flag, "Filter", G_TYPE_STRING, &self->filter, "StartingIndex", G_TYPE_UINT, &self->index, "RequestedCount", G_TYPE_UINT, &self->requested_count, "SortCriteria", G_TYPE_STRING, &self->sort_criteria, NULL);
	_tmp0_ = FALSE;
	if (self->browse_flag != NULL) {
		_tmp0_ = _vala_strcmp0 (self->browse_flag, "BrowseDirectChildren") == 0;
	} else {
		_tmp0_ = FALSE;
	}
	/* BrowseFlag */
	if (_tmp0_) {
		self->priv->fetch_metadata = FALSE;
	} else {
		gboolean _tmp1_;
		_tmp1_ = FALSE;
		if (self->browse_flag != NULL) {
			_tmp1_ = _vala_strcmp0 (self->browse_flag, "BrowseMetadata") == 0;
		} else {
			_tmp1_ = FALSE;
		}
		if (_tmp1_) {
			self->priv->fetch_metadata = TRUE;
		} else {
			GError* _tmp2_;
			self->priv->fetch_metadata = FALSE;
			_tmp2_ = NULL;
			rygel_browse_handle_error (self, _tmp2_ = g_error_new_literal (RYGEL_CONTENT_DIRECTORY_ERROR, RYGEL_CONTENT_DIRECTORY_ERROR_INVALID_ARGS, "Invalid Args"));
			(_tmp2_ == NULL) ? NULL : (_tmp2_ = (g_error_free (_tmp2_), NULL));
			return;
		}
	}
	/* ObjectID */
	if (self->object_id == NULL) {
		/* Stupid Xbox */
		gupnp_service_action_get (self->priv->action, "ContainerID", G_TYPE_STRING, &self->object_id, NULL);
	}
	if (self->object_id == NULL) {
		GError* _tmp3_;
		/* Sorry we can't do anything without ObjectID*/
		_tmp3_ = NULL;
		rygel_browse_handle_error (self, _tmp3_ = g_error_new_literal (RYGEL_CONTENT_DIRECTORY_ERROR, RYGEL_CONTENT_DIRECTORY_ERROR_NO_SUCH_OBJECT, "No such object"));
		(_tmp3_ == NULL) ? NULL : (_tmp3_ = (g_error_free (_tmp3_), NULL));
		return;
	}
	rygel_browse_fetch_media_object (self);
}


static void rygel_browse_conclude (RygelBrowse* self) {
	const char* _tmp0_;
	char* didl;
	g_return_if_fail (self != NULL);
	/* End DIDL-Lite fragment */
	gupnp_didl_lite_writer_end_didl_lite ((GUPnPDIDLLiteWriter*) self->priv->didl_writer);
	/* Retrieve generated string */
	_tmp0_ = NULL;
	didl = (_tmp0_ = gupnp_didl_lite_writer_get_string ((GUPnPDIDLLiteWriter*) self->priv->didl_writer), (_tmp0_ == NULL) ? NULL : g_strdup (_tmp0_));
	if (self->update_id == G_MAXUINT32) {
		self->update_id = (guint) self->priv->system_update_id;
	}
	/* Set action return arguments */
	gupnp_service_action_set (self->priv->action, "Result", G_TYPE_STRING, didl, "NumberReturned", G_TYPE_UINT, self->number_returned, "TotalMatches", G_TYPE_UINT, self->total_matches, "UpdateID", G_TYPE_UINT, self->update_id, NULL);
	gupnp_service_action_return (self->priv->action);
	g_signal_emit_by_name ((RygelStateMachine*) self, "completed");
	didl = (g_free (didl), NULL);
}


static void rygel_browse_handle_error (RygelBrowse* self, GError* _error_) {
	g_return_if_fail (self != NULL);
	if (_error_->domain == RYGEL_CONTENT_DIRECTORY_ERROR) {
		g_warning ("rygel-browse.vala:226: Failed to browse '%s': %s\n", self->object_id, _error_->message);
		gupnp_service_action_return_error (self->priv->action, (guint) _error_->code, _error_->message);
	} else {
		g_warning ("rygel-browse.vala:231: Failed to browse '%s': %s\n", self->object_id, _error_->message);
		gupnp_service_action_return_error (self->priv->action, (guint) 701, _error_->message);
	}
	g_signal_emit_by_name ((RygelStateMachine*) self, "completed");
}


static void rygel_browse_serialize_children (RygelBrowse* self, GeeList* children) {
	GError * _inner_error_;
	g_return_if_fail (self != NULL);
	_inner_error_ = NULL;
	if (children == NULL) {
		GError* _tmp0_;
		_tmp0_ = NULL;
		rygel_browse_handle_error (self, _tmp0_ = g_error_new_literal (RYGEL_CONTENT_DIRECTORY_ERROR, RYGEL_CONTENT_DIRECTORY_ERROR_NO_SUCH_OBJECT, "No such object"));
		(_tmp0_ == NULL) ? NULL : (_tmp0_ = (g_error_free (_tmp0_), NULL));
		return;
	}
	{
		gint i;
		/* serialize all children */
		i = 0;
		for (; i < gee_collection_get_size ((GeeCollection*) children); i++) {
			{
				RygelMediaObject* _tmp1_;
				_tmp1_ = NULL;
				rygel_didl_lite_writer_serialize (self->priv->didl_writer, _tmp1_ = (RygelMediaObject*) gee_list_get (children, i), &_inner_error_);
				if (_inner_error_ != NULL) {
					goto __catch21_g_error;
					goto __finally21;
				}
				(_tmp1_ == NULL) ? NULL : (_tmp1_ = (g_object_unref (_tmp1_), NULL));
			}
			goto __finally21;
			__catch21_g_error:
			{
				GError * err;
				err = _inner_error_;
				_inner_error_ = NULL;
				{
					rygel_browse_handle_error (self, err);
					(err == NULL) ? NULL : (err = (g_error_free (err), NULL));
					return;
				}
			}
			__finally21:
			if (_inner_error_ != NULL) {
				g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, _inner_error_->message);
				g_clear_error (&_inner_error_);
				return;
			}
		}
	}
	/* Conclude the successful Browse action*/
	rygel_browse_conclude (self);
}


static void _rygel_browse_on_children_fetched_gasync_ready_callback (GObject* source_object, GAsyncResult* res, gpointer self) {
	rygel_browse_on_children_fetched (self, source_object, res);
}


static void rygel_browse_fetch_children (RygelBrowse* self) {
	RygelMediaContainer* _tmp0_;
	RygelMediaContainer* container;
	g_return_if_fail (self != NULL);
	_tmp0_ = NULL;
	container = (_tmp0_ = RYGEL_MEDIA_CONTAINER (self->priv->media_object), (_tmp0_ == NULL) ? NULL : g_object_ref (_tmp0_));
	rygel_media_container_get_children (container, self->index, self->requested_count, self->priv->cancellable, _rygel_browse_on_children_fetched_gasync_ready_callback, self);
	(container == NULL) ? NULL : (container = (g_object_unref (container), NULL));
}


static void rygel_browse_on_children_fetched (RygelBrowse* self, GObject* source_object, GAsyncResult* res) {
	GError * _inner_error_;
	RygelMediaContainer* _tmp0_;
	RygelMediaContainer* container;
	g_return_if_fail (self != NULL);
	g_return_if_fail (source_object != NULL);
	g_return_if_fail (res != NULL);
	_inner_error_ = NULL;
	_tmp0_ = NULL;
	container = (_tmp0_ = RYGEL_MEDIA_CONTAINER (source_object), (_tmp0_ == NULL) ? NULL : g_object_ref (_tmp0_));
	{
		GeeList* children;
		children = rygel_media_container_get_children_finish (container, res, &_inner_error_);
		if (_inner_error_ != NULL) {
			goto __catch22_g_error;
			goto __finally22;
		}
		self->number_returned = (guint) gee_collection_get_size ((GeeCollection*) children);
		rygel_browse_serialize_children (self, children);
		(children == NULL) ? NULL : (children = (g_object_unref (children), NULL));
	}
	goto __finally22;
	__catch22_g_error:
	{
		GError * err;
		err = _inner_error_;
		_inner_error_ = NULL;
		{
			rygel_browse_handle_error (self, err);
			(err == NULL) ? NULL : (err = (g_error_free (err), NULL));
		}
	}
	__finally22:
	if (_inner_error_ != NULL) {
		(container == NULL) ? NULL : (container = (g_object_unref (container), NULL));
		g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, _inner_error_->message);
		g_clear_error (&_inner_error_);
		return;
	}
	(container == NULL) ? NULL : (container = (g_object_unref (container), NULL));
}


static void rygel_browse_class_init (RygelBrowseClass * klass) {
	rygel_browse_parent_class = g_type_class_peek_parent (klass);
	g_type_class_add_private (klass, sizeof (RygelBrowsePrivate));
	G_OBJECT_CLASS (klass)->finalize = rygel_browse_finalize;
}


static void rygel_browse_rygel_state_machine_interface_init (RygelStateMachineIface * iface) {
	rygel_browse_rygel_state_machine_parent_iface = g_type_interface_peek_parent (iface);
	iface->run = rygel_browse_real_run;
}


static void rygel_browse_instance_init (RygelBrowse * self) {
	self->priv = RYGEL_BROWSE_GET_PRIVATE (self);
}


static void rygel_browse_finalize (GObject* obj) {
	RygelBrowse * self;
	self = RYGEL_BROWSE (obj);
	self->object_id = (g_free (self->object_id), NULL);
	self->browse_flag = (g_free (self->browse_flag), NULL);
	self->filter = (g_free (self->filter), NULL);
	self->sort_criteria = (g_free (self->sort_criteria), NULL);
	(self->priv->media_object == NULL) ? NULL : (self->priv->media_object = (g_object_unref (self->priv->media_object), NULL));
	(self->priv->root_container == NULL) ? NULL : (self->priv->root_container = (g_object_unref (self->priv->root_container), NULL));
	(self->priv->didl_writer == NULL) ? NULL : (self->priv->didl_writer = (g_object_unref (self->priv->didl_writer), NULL));
	(self->priv->cancellable == NULL) ? NULL : (self->priv->cancellable = (g_object_unref (self->priv->cancellable), NULL));
	G_OBJECT_CLASS (rygel_browse_parent_class)->finalize (obj);
}


GType rygel_browse_get_type (void) {
	static GType rygel_browse_type_id = 0;
	if (rygel_browse_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (RygelBrowseClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) rygel_browse_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (RygelBrowse), 0, (GInstanceInitFunc) rygel_browse_instance_init, NULL };
		static const GInterfaceInfo rygel_state_machine_info = { (GInterfaceInitFunc) rygel_browse_rygel_state_machine_interface_init, (GInterfaceFinalizeFunc) NULL, NULL};
		rygel_browse_type_id = g_type_register_static (G_TYPE_OBJECT, "RygelBrowse", &g_define_type_info, 0);
		g_type_add_interface_static (rygel_browse_type_id, RYGEL_TYPE_STATE_MACHINE, &rygel_state_machine_info);
	}
	return rygel_browse_type_id;
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




