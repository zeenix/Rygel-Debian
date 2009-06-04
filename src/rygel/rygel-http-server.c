/*
 * Copyright (C) 2008, 2009 Nokia Corporation, all rights reserved.
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
#include <stdlib.h>
#include <string.h>
#include <gee/arraylist.h>
#include <libgupnp-av/gupnp-av.h>
#include <gio/gio.h>
#include <libgupnp/gupnp.h>
#include <libsoup/soup.h>
#include <gee/list.h>
#include <gee/iterable.h>
#include <gee/iterator.h>
#include <gee/collection.h>


#define RYGEL_TYPE_TRANSCODE_MANAGER (rygel_transcode_manager_get_type ())
#define RYGEL_TRANSCODE_MANAGER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_TRANSCODE_MANAGER, RygelTranscodeManager))
#define RYGEL_TRANSCODE_MANAGER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_TRANSCODE_MANAGER, RygelTranscodeManagerClass))
#define RYGEL_IS_TRANSCODE_MANAGER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_TRANSCODE_MANAGER))
#define RYGEL_IS_TRANSCODE_MANAGER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_TRANSCODE_MANAGER))
#define RYGEL_TRANSCODE_MANAGER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_TRANSCODE_MANAGER, RygelTranscodeManagerClass))

typedef struct _RygelTranscodeManager RygelTranscodeManager;
typedef struct _RygelTranscodeManagerClass RygelTranscodeManagerClass;
typedef struct _RygelTranscodeManagerPrivate RygelTranscodeManagerPrivate;

#define RYGEL_TYPE_MEDIA_OBJECT (rygel_media_object_get_type ())
#define RYGEL_MEDIA_OBJECT(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_MEDIA_OBJECT, RygelMediaObject))
#define RYGEL_MEDIA_OBJECT_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_MEDIA_OBJECT, RygelMediaObjectClass))
#define RYGEL_IS_MEDIA_OBJECT(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_MEDIA_OBJECT))
#define RYGEL_IS_MEDIA_OBJECT_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_MEDIA_OBJECT))
#define RYGEL_MEDIA_OBJECT_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_MEDIA_OBJECT, RygelMediaObjectClass))

typedef struct _RygelMediaObject RygelMediaObject;
typedef struct _RygelMediaObjectClass RygelMediaObjectClass;

#define RYGEL_TYPE_MEDIA_ITEM (rygel_media_item_get_type ())
#define RYGEL_MEDIA_ITEM(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_MEDIA_ITEM, RygelMediaItem))
#define RYGEL_MEDIA_ITEM_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_MEDIA_ITEM, RygelMediaItemClass))
#define RYGEL_IS_MEDIA_ITEM(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_MEDIA_ITEM))
#define RYGEL_IS_MEDIA_ITEM_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_MEDIA_ITEM))
#define RYGEL_MEDIA_ITEM_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_MEDIA_ITEM, RygelMediaItemClass))

typedef struct _RygelMediaItem RygelMediaItem;
typedef struct _RygelMediaItemClass RygelMediaItemClass;

#define RYGEL_TYPE_STATE_MACHINE (rygel_state_machine_get_type ())
#define RYGEL_STATE_MACHINE(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_STATE_MACHINE, RygelStateMachine))
#define RYGEL_IS_STATE_MACHINE(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_STATE_MACHINE))
#define RYGEL_STATE_MACHINE_GET_INTERFACE(obj) (G_TYPE_INSTANCE_GET_INTERFACE ((obj), RYGEL_TYPE_STATE_MACHINE, RygelStateMachineIface))

typedef struct _RygelStateMachine RygelStateMachine;
typedef struct _RygelStateMachineIface RygelStateMachineIface;

#define RYGEL_TYPE_HTTP_SERVER (rygel_http_server_get_type ())
#define RYGEL_HTTP_SERVER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_HTTP_SERVER, RygelHTTPServer))
#define RYGEL_HTTP_SERVER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_HTTP_SERVER, RygelHTTPServerClass))
#define RYGEL_IS_HTTP_SERVER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_HTTP_SERVER))
#define RYGEL_IS_HTTP_SERVER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_HTTP_SERVER))
#define RYGEL_HTTP_SERVER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_HTTP_SERVER, RygelHTTPServerClass))

typedef struct _RygelHTTPServer RygelHTTPServer;
typedef struct _RygelHTTPServerClass RygelHTTPServerClass;
typedef struct _RygelHTTPServerPrivate RygelHTTPServerPrivate;

#define RYGEL_TYPE_MEDIA_CONTAINER (rygel_media_container_get_type ())
#define RYGEL_MEDIA_CONTAINER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_MEDIA_CONTAINER, RygelMediaContainer))
#define RYGEL_MEDIA_CONTAINER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_MEDIA_CONTAINER, RygelMediaContainerClass))
#define RYGEL_IS_MEDIA_CONTAINER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_MEDIA_CONTAINER))
#define RYGEL_IS_MEDIA_CONTAINER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_MEDIA_CONTAINER))
#define RYGEL_MEDIA_CONTAINER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_MEDIA_CONTAINER, RygelMediaContainerClass))

typedef struct _RygelMediaContainer RygelMediaContainer;
typedef struct _RygelMediaContainerClass RygelMediaContainerClass;

#define RYGEL_TYPE_HTTP_REQUEST (rygel_http_request_get_type ())
#define RYGEL_HTTP_REQUEST(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_HTTP_REQUEST, RygelHTTPRequest))
#define RYGEL_HTTP_REQUEST_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_HTTP_REQUEST, RygelHTTPRequestClass))
#define RYGEL_IS_HTTP_REQUEST(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_HTTP_REQUEST))
#define RYGEL_IS_HTTP_REQUEST_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_HTTP_REQUEST))
#define RYGEL_HTTP_REQUEST_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_HTTP_REQUEST, RygelHTTPRequestClass))

typedef struct _RygelHTTPRequest RygelHTTPRequest;
typedef struct _RygelHTTPRequestClass RygelHTTPRequestClass;

#define RYGEL_TYPE_CONTENT_DIRECTORY (rygel_content_directory_get_type ())
#define RYGEL_CONTENT_DIRECTORY(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_CONTENT_DIRECTORY, RygelContentDirectory))
#define RYGEL_CONTENT_DIRECTORY_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_CONTENT_DIRECTORY, RygelContentDirectoryClass))
#define RYGEL_IS_CONTENT_DIRECTORY(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_CONTENT_DIRECTORY))
#define RYGEL_IS_CONTENT_DIRECTORY_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_CONTENT_DIRECTORY))
#define RYGEL_CONTENT_DIRECTORY_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_CONTENT_DIRECTORY, RygelContentDirectoryClass))

typedef struct _RygelContentDirectory RygelContentDirectory;
typedef struct _RygelContentDirectoryClass RygelContentDirectoryClass;
typedef struct _RygelContentDirectoryPrivate RygelContentDirectoryPrivate;
typedef struct _RygelMediaObjectPrivate RygelMediaObjectPrivate;

/**
 * Responsible for management of all transcoders:
 *    - gets the appropriate transcoder given a transcoding target.
 *    - provide all possible transcoding resources for items.
 */
struct _RygelTranscodeManager {
	GObject parent_instance;
	RygelTranscodeManagerPrivate * priv;
};

struct _RygelTranscodeManagerClass {
	GObjectClass parent_class;
	char* (*create_uri_for_item) (RygelTranscodeManager* self, RygelMediaItem* item, const char* transcode_target, char** protocol);
	void (*add_resources) (RygelTranscodeManager* self, GeeArrayList* resources, RygelMediaItem* item, GError** error);
};

/**
 * StateMachine interface.
 */
struct _RygelStateMachineIface {
	GTypeInterface parent_iface;
	void (*run) (RygelStateMachine* self, GCancellable* cancellable);
};

struct _RygelHTTPServer {
	RygelTranscodeManager parent_instance;
	RygelHTTPServerPrivate * priv;
	RygelMediaContainer* root_container;
};

struct _RygelHTTPServerClass {
	RygelTranscodeManagerClass parent_class;
};

struct _RygelHTTPServerPrivate {
	char* path_root;
	GUPnPContext* context;
	GeeArrayList* requests;
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



GType rygel_transcode_manager_get_type (void);
GType rygel_media_object_get_type (void);
GType rygel_media_item_get_type (void);
GType rygel_state_machine_get_type (void);
GType rygel_http_server_get_type (void);
GType rygel_media_container_get_type (void);
GType rygel_http_request_get_type (void);
#define RYGEL_HTTP_SERVER_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), RYGEL_TYPE_HTTP_SERVER, RygelHTTPServerPrivate))
enum  {
	RYGEL_HTTP_SERVER_DUMMY_PROPERTY
};
#define RYGEL_HTTP_SERVER_SERVER_PATH_PREFIX "/RygelHTTPServer"
RygelTranscodeManager* rygel_transcode_manager_new (void);
RygelTranscodeManager* rygel_transcode_manager_construct (GType object_type);
GType rygel_content_directory_get_type (void);
RygelHTTPServer* rygel_http_server_new (RygelContentDirectory* content_dir, const char* name);
RygelHTTPServer* rygel_http_server_construct (GType object_type, RygelContentDirectory* content_dir, const char* name);
RygelHTTPServer* rygel_http_server_new (RygelContentDirectory* content_dir, const char* name);
static void rygel_http_server_server_handler (RygelHTTPServer* self, SoupServer* server, SoupMessage* msg, const char* server_path, GHashTable* query, SoupClientContext* soup_client);
static void _rygel_http_server_server_handler_soup_server_callback (SoupServer* server, SoupMessage* msg, const char* path, GHashTable* query, SoupClientContext* client, gpointer self);
static void rygel_http_server_on_cancelled (RygelHTTPServer* self, GCancellable* cancellable);
static void _rygel_http_server_on_cancelled_g_cancellable_cancelled (GCancellable* _sender, gpointer self);
static void rygel_http_server_real_run (RygelStateMachine* base, GCancellable* cancellable);
char* rygel_transcode_manager_create_uri_for_item (RygelTranscodeManager* self, RygelMediaItem* item, const char* transcode_target, char** protocol);
GUPnPDIDLLiteResource rygel_media_item_create_res (RygelMediaItem* self, const char* uri, GError** error);
static gboolean rygel_http_server_http_res_present (RygelHTTPServer* self, GeeArrayList* res_list);
void rygel_transcode_manager_add_resources (RygelTranscodeManager* self, GeeArrayList* resources, RygelMediaItem* item, GError** error);
static void rygel_http_server_real_add_resources (RygelTranscodeManager* base, GeeArrayList* resources, RygelMediaItem* item, GError** error);
static char* rygel_http_server_create_uri_for_path (RygelHTTPServer* self, const char* path);
static char* rygel_http_server_real_create_uri_for_item (RygelTranscodeManager* base, RygelMediaItem* item, const char* transcode_target, char** protocol);
static void rygel_http_server_on_request_completed (RygelHTTPServer* self, RygelHTTPRequest* request);
RygelHTTPRequest* rygel_http_request_new (RygelHTTPServer* http_server, SoupServer* server, SoupMessage* msg, GHashTable* query);
RygelHTTPRequest* rygel_http_request_construct (GType object_type, RygelHTTPServer* http_server, SoupServer* server, SoupMessage* msg, GHashTable* query);
static void _rygel_http_server_on_request_completed_rygel_state_machine_completed (RygelHTTPRequest* _sender, gpointer self);
void rygel_state_machine_run (RygelStateMachine* self, GCancellable* cancellable);
static gpointer rygel_http_server_parent_class = NULL;
static RygelStateMachineIface* rygel_http_server_rygel_state_machine_parent_iface = NULL;
static void rygel_http_server_finalize (GObject* obj);
static int _vala_strcmp0 (const char * str1, const char * str2);



RygelHTTPServer* rygel_http_server_construct (GType object_type, RygelContentDirectory* content_dir, const char* name) {
	RygelHTTPServer * self;
	RygelMediaContainer* _tmp1_;
	RygelMediaContainer* _tmp0_;
	GUPnPContext* _tmp3_;
	GUPnPContext* _tmp2_;
	GeeArrayList* _tmp4_;
	char* _tmp5_;
	g_return_val_if_fail (content_dir != NULL, NULL);
	g_return_val_if_fail (name != NULL, NULL);
	self = (RygelHTTPServer*) rygel_transcode_manager_construct (object_type);
	_tmp1_ = NULL;
	_tmp0_ = NULL;
	self->root_container = (_tmp1_ = (_tmp0_ = content_dir->root_container, (_tmp0_ == NULL) ? NULL : g_object_ref (_tmp0_)), (self->root_container == NULL) ? NULL : (self->root_container = (g_object_unref (self->root_container), NULL)), _tmp1_);
	_tmp3_ = NULL;
	_tmp2_ = NULL;
	self->priv->context = (_tmp3_ = (_tmp2_ = gupnp_service_info_get_context ((GUPnPServiceInfo*) content_dir), (_tmp2_ == NULL) ? NULL : g_object_ref (_tmp2_)), (self->priv->context == NULL) ? NULL : (self->priv->context = (g_object_unref (self->priv->context), NULL)), _tmp3_);
	_tmp4_ = NULL;
	self->priv->requests = (_tmp4_ = gee_array_list_new (RYGEL_TYPE_HTTP_REQUEST, (GBoxedCopyFunc) g_object_ref, g_object_unref, g_direct_equal), (self->priv->requests == NULL) ? NULL : (self->priv->requests = (g_object_unref (self->priv->requests), NULL)), _tmp4_);
	_tmp5_ = NULL;
	self->priv->path_root = (_tmp5_ = g_strconcat (RYGEL_HTTP_SERVER_SERVER_PATH_PREFIX "/", name, NULL), self->priv->path_root = (g_free (self->priv->path_root), NULL), _tmp5_);
	return self;
}


RygelHTTPServer* rygel_http_server_new (RygelContentDirectory* content_dir, const char* name) {
	return rygel_http_server_construct (RYGEL_TYPE_HTTP_SERVER, content_dir, name);
}


static void _rygel_http_server_server_handler_soup_server_callback (SoupServer* server, SoupMessage* msg, const char* path, GHashTable* query, SoupClientContext* client, gpointer self) {
	rygel_http_server_server_handler (self, server, msg, path, query, client);
}


static void _rygel_http_server_on_cancelled_g_cancellable_cancelled (GCancellable* _sender, gpointer self) {
	rygel_http_server_on_cancelled (self, _sender);
}


static void rygel_http_server_real_run (RygelStateMachine* base, GCancellable* cancellable) {
	RygelHTTPServer * self;
	self = (RygelHTTPServer*) base;
	soup_server_add_handler (gupnp_context_get_server (self->priv->context), self->priv->path_root, _rygel_http_server_server_handler_soup_server_callback, g_object_ref (self), g_object_unref);
	if (cancellable != NULL) {
		GCancellable* _tmp1_;
		GCancellable* _tmp0_;
		_tmp1_ = NULL;
		_tmp0_ = NULL;
		self->priv->cancellable = (_tmp1_ = (_tmp0_ = cancellable, (_tmp0_ == NULL) ? NULL : g_object_ref (_tmp0_)), (self->priv->cancellable == NULL) ? NULL : (self->priv->cancellable = (g_object_unref (self->priv->cancellable), NULL)), _tmp1_);
		g_signal_connect_object (self->priv->cancellable, "cancelled", (GCallback) _rygel_http_server_on_cancelled_g_cancellable_cancelled, self, 0);
	}
}


/* We prepend these resources into the original resource list instead of
     * appending them because some crappy MediaRenderer/ControlPoint
     * implemenation out there just choose the first one in the list instead of
     * the one they can handle.
     */
static void rygel_http_server_real_add_resources (RygelTranscodeManager* base, GeeArrayList* resources, RygelMediaItem* item, GError** error) {
	RygelHTTPServer * self;
	GError * _inner_error_;
	char* protocol;
	char* _tmp2_;
	char* _tmp1_;
	char* _tmp0_;
	char* uri;
	GUPnPDIDLLiteResource res;
	char* _tmp4_;
	const char* _tmp3_;
	self = (RygelHTTPServer*) base;
	g_return_if_fail (resources != NULL);
	g_return_if_fail (item != NULL);
	_inner_error_ = NULL;
	/* Create the HTTP proxy URI*/
	protocol = NULL;
	_tmp2_ = NULL;
	_tmp1_ = NULL;
	_tmp0_ = NULL;
	uri = (_tmp1_ = rygel_transcode_manager_create_uri_for_item ((RygelTranscodeManager*) self, item, NULL, &_tmp0_), protocol = (_tmp2_ = _tmp0_, protocol = (g_free (protocol), NULL), _tmp2_), _tmp1_);
	res = rygel_media_item_create_res (item, uri, &_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		protocol = (g_free (protocol), NULL);
		uri = (g_free (uri), NULL);
		return;
	}
	_tmp4_ = NULL;
	_tmp3_ = NULL;
	res.protocol = (_tmp4_ = (_tmp3_ = protocol, (_tmp3_ == NULL) ? NULL : g_strdup (_tmp3_)), res.protocol = (g_free (res.protocol), NULL), _tmp4_);
	if (!rygel_http_server_http_res_present (self, resources)) {
		gee_list_insert ((GeeList*) resources, 0, &res);
	}
	RYGEL_TRANSCODE_MANAGER_CLASS (rygel_http_server_parent_class)->add_resources (RYGEL_TRANSCODE_MANAGER (self), resources, item, &_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		protocol = (g_free (protocol), NULL);
		uri = (g_free (uri), NULL);
		gupnp_didl_lite_resource_destroy (&res);
		return;
	}
	protocol = (g_free (protocol), NULL);
	uri = (g_free (uri), NULL);
	gupnp_didl_lite_resource_destroy (&res);
}


static gboolean rygel_http_server_http_res_present (RygelHTTPServer* self, GeeArrayList* res_list) {
	gboolean present;
	g_return_val_if_fail (self != NULL, FALSE);
	g_return_val_if_fail (res_list != NULL, FALSE);
	present = FALSE;
	{
		GeeIterator* _res_it;
		_res_it = gee_iterable_iterator ((GeeIterable*) res_list);
		while (gee_iterator_next (_res_it)) {
			GUPnPDIDLLiteResource* res;
			res = (GUPnPDIDLLiteResource*) gee_iterator_get (_res_it);
			if (_vala_strcmp0 ((*res).protocol, "http-get") == 0) {
				present = TRUE;
				(res == NULL) ? NULL : (res = (g_free (res), NULL));
				break;
			}
			(res == NULL) ? NULL : (res = (g_free (res), NULL));
		}
		(_res_it == NULL) ? NULL : (_res_it = (g_object_unref (_res_it), NULL));
	}
	return present;
}


static void rygel_http_server_on_cancelled (RygelHTTPServer* self, GCancellable* cancellable) {
	g_return_if_fail (self != NULL);
	g_return_if_fail (cancellable != NULL);
	/* Cancel all state machines*/
	g_cancellable_cancel (self->priv->cancellable);
	soup_server_remove_handler (gupnp_context_get_server (self->priv->context), self->priv->path_root);
	g_signal_emit_by_name ((RygelStateMachine*) self, "completed");
}


static char* rygel_http_server_create_uri_for_path (RygelHTTPServer* self, const char* path) {
	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (path != NULL, NULL);
	return g_strdup_printf ("http://%s:%u%s%s", gupnp_context_get_host_ip (self->priv->context), gupnp_context_get_port (self->priv->context), self->priv->path_root, path);
}


static char* rygel_http_server_real_create_uri_for_item (RygelTranscodeManager* base, RygelMediaItem* item, const char* transcode_target, char** protocol) {
	RygelHTTPServer * self;
	char* escaped;
	char* query;
	char* _tmp3_;
	char* _tmp4_;
	self = (RygelHTTPServer*) base;
	g_return_val_if_fail (item != NULL, NULL);
	if (protocol != NULL) {
		*protocol = NULL;
	}
	escaped = g_uri_escape_string (((RygelMediaObject*) item)->id, "", TRUE);
	query = g_strconcat ("?itemid=", escaped, NULL);
	if (transcode_target != NULL) {
		char* _tmp0_;
		char* _tmp2_;
		char* _tmp1_;
		_tmp0_ = NULL;
		escaped = (_tmp0_ = g_uri_escape_string (transcode_target, "", TRUE), escaped = (g_free (escaped), NULL), _tmp0_);
		_tmp2_ = NULL;
		_tmp1_ = NULL;
		query = (_tmp2_ = g_strconcat (query, _tmp1_ = g_strconcat ("&transcode=", escaped, NULL), NULL), query = (g_free (query), NULL), _tmp2_);
		_tmp1_ = (g_free (_tmp1_), NULL);
	}
	_tmp3_ = NULL;
	(*protocol) = (_tmp3_ = g_strdup ("http-get"), (*protocol) = (g_free ((*protocol)), NULL), _tmp3_);
	_tmp4_ = NULL;
	return (_tmp4_ = rygel_http_server_create_uri_for_path (self, query), escaped = (g_free (escaped), NULL), query = (g_free (query), NULL), _tmp4_);
}


static void rygel_http_server_on_request_completed (RygelHTTPServer* self, RygelHTTPRequest* request) {
	g_return_if_fail (self != NULL);
	g_return_if_fail (request != NULL);
	/* Remove the request from our list. */
	gee_collection_remove ((GeeCollection*) self->priv->requests, request);
}


static void _rygel_http_server_on_request_completed_rygel_state_machine_completed (RygelHTTPRequest* _sender, gpointer self) {
	rygel_http_server_on_request_completed (self, _sender);
}


static void rygel_http_server_server_handler (RygelHTTPServer* self, SoupServer* server, SoupMessage* msg, const char* server_path, GHashTable* query, SoupClientContext* soup_client) {
	char* _tmp2_;
	char* _tmp1_;
	char* _tmp0_;
	RygelHTTPRequest* request;
	g_return_if_fail (self != NULL);
	g_return_if_fail (server != NULL);
	g_return_if_fail (msg != NULL);
	g_return_if_fail (server_path != NULL);
	g_return_if_fail (soup_client != NULL);
	_tmp2_ = NULL;
	_tmp1_ = NULL;
	_tmp0_ = NULL;
	g_debug ("rygel-http-server.vala:137: HTTP %s request for URI: %s", _tmp1_ = (g_object_get (msg, "method", &_tmp0_, NULL), _tmp0_), _tmp2_ = soup_uri_to_string (soup_message_get_uri (msg), FALSE));
	_tmp2_ = (g_free (_tmp2_), NULL);
	_tmp1_ = (g_free (_tmp1_), NULL);
	request = rygel_http_request_new (self, server, msg, query);
	g_signal_connect_object ((RygelStateMachine*) request, "completed", (GCallback) _rygel_http_server_on_request_completed_rygel_state_machine_completed, self, 0);
	gee_collection_add ((GeeCollection*) self->priv->requests, request);
	rygel_state_machine_run ((RygelStateMachine*) request, self->priv->cancellable);
	(request == NULL) ? NULL : (request = (g_object_unref (request), NULL));
}


static void rygel_http_server_class_init (RygelHTTPServerClass * klass) {
	rygel_http_server_parent_class = g_type_class_peek_parent (klass);
	g_type_class_add_private (klass, sizeof (RygelHTTPServerPrivate));
	RYGEL_TRANSCODE_MANAGER_CLASS (klass)->add_resources = rygel_http_server_real_add_resources;
	RYGEL_TRANSCODE_MANAGER_CLASS (klass)->create_uri_for_item = rygel_http_server_real_create_uri_for_item;
	G_OBJECT_CLASS (klass)->finalize = rygel_http_server_finalize;
}


static void rygel_http_server_rygel_state_machine_interface_init (RygelStateMachineIface * iface) {
	rygel_http_server_rygel_state_machine_parent_iface = g_type_interface_peek_parent (iface);
	iface->run = rygel_http_server_real_run;
}


static void rygel_http_server_instance_init (RygelHTTPServer * self) {
	self->priv = RYGEL_HTTP_SERVER_GET_PRIVATE (self);
}


static void rygel_http_server_finalize (GObject* obj) {
	RygelHTTPServer * self;
	self = RYGEL_HTTP_SERVER (obj);
	self->priv->path_root = (g_free (self->priv->path_root), NULL);
	(self->root_container == NULL) ? NULL : (self->root_container = (g_object_unref (self->root_container), NULL));
	(self->priv->context == NULL) ? NULL : (self->priv->context = (g_object_unref (self->priv->context), NULL));
	(self->priv->requests == NULL) ? NULL : (self->priv->requests = (g_object_unref (self->priv->requests), NULL));
	(self->priv->cancellable == NULL) ? NULL : (self->priv->cancellable = (g_object_unref (self->priv->cancellable), NULL));
	G_OBJECT_CLASS (rygel_http_server_parent_class)->finalize (obj);
}


GType rygel_http_server_get_type (void) {
	static GType rygel_http_server_type_id = 0;
	if (rygel_http_server_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (RygelHTTPServerClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) rygel_http_server_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (RygelHTTPServer), 0, (GInstanceInitFunc) rygel_http_server_instance_init, NULL };
		static const GInterfaceInfo rygel_state_machine_info = { (GInterfaceInitFunc) rygel_http_server_rygel_state_machine_interface_init, (GInterfaceFinalizeFunc) NULL, NULL};
		rygel_http_server_type_id = g_type_register_static (RYGEL_TYPE_TRANSCODE_MANAGER, "RygelHTTPServer", &g_define_type_info, 0);
		g_type_add_interface_static (rygel_http_server_type_id, RYGEL_TYPE_STATE_MACHINE, &rygel_state_machine_info);
	}
	return rygel_http_server_type_id;
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




