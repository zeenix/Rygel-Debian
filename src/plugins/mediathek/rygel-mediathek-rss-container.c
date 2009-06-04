/*
 * Copyright (C) 2009 Jens Georg
 *
 * Author: Jens Georg <mail@jensge.org>
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
#include <gee/arraylist.h>
#include <libsoup/soup.h>
#include <stdlib.h>
#include <string.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <gee/collection.h>
#include <libxml/xpath.h>
#include <gee/list.h>
#include <gio/gio.h>
#include <gee/iterable.h>
#include <gee/iterator.h>


#define RYGEL_TYPE_MEDIATHEK_RSS_CONTAINER (rygel_mediathek_rss_container_get_type ())
#define RYGEL_MEDIATHEK_RSS_CONTAINER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_MEDIATHEK_RSS_CONTAINER, RygelMediathekRssContainer))
#define RYGEL_MEDIATHEK_RSS_CONTAINER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_MEDIATHEK_RSS_CONTAINER, RygelMediathekRssContainerClass))
#define RYGEL_IS_MEDIATHEK_RSS_CONTAINER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_MEDIATHEK_RSS_CONTAINER))
#define RYGEL_IS_MEDIATHEK_RSS_CONTAINER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_MEDIATHEK_RSS_CONTAINER))
#define RYGEL_MEDIATHEK_RSS_CONTAINER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_MEDIATHEK_RSS_CONTAINER, RygelMediathekRssContainerClass))

typedef struct _RygelMediathekRssContainer RygelMediathekRssContainer;
typedef struct _RygelMediathekRssContainerClass RygelMediathekRssContainerClass;
typedef struct _RygelMediathekRssContainerPrivate RygelMediathekRssContainerPrivate;

#define RYGEL_TYPE_MEDIATHEK_VIDEO_ITEM (rygel_mediathek_video_item_get_type ())
#define RYGEL_MEDIATHEK_VIDEO_ITEM(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_MEDIATHEK_VIDEO_ITEM, RygelMediathekVideoItem))
#define RYGEL_MEDIATHEK_VIDEO_ITEM_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_MEDIATHEK_VIDEO_ITEM, RygelMediathekVideoItemClass))
#define RYGEL_IS_MEDIATHEK_VIDEO_ITEM(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_MEDIATHEK_VIDEO_ITEM))
#define RYGEL_IS_MEDIATHEK_VIDEO_ITEM_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_MEDIATHEK_VIDEO_ITEM))
#define RYGEL_MEDIATHEK_VIDEO_ITEM_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_MEDIATHEK_VIDEO_ITEM, RygelMediathekVideoItemClass))

typedef struct _RygelMediathekVideoItem RygelMediathekVideoItem;
typedef struct _RygelMediathekVideoItemClass RygelMediathekVideoItemClass;

#define RYGEL_TYPE_MEDIATHEK_ROOT_CONTAINER (rygel_mediathek_root_container_get_type ())
#define RYGEL_MEDIATHEK_ROOT_CONTAINER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_MEDIATHEK_ROOT_CONTAINER, RygelMediathekRootContainer))
#define RYGEL_MEDIATHEK_ROOT_CONTAINER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_MEDIATHEK_ROOT_CONTAINER, RygelMediathekRootContainerClass))
#define RYGEL_IS_MEDIATHEK_ROOT_CONTAINER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_MEDIATHEK_ROOT_CONTAINER))
#define RYGEL_IS_MEDIATHEK_ROOT_CONTAINER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_MEDIATHEK_ROOT_CONTAINER))
#define RYGEL_MEDIATHEK_ROOT_CONTAINER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_MEDIATHEK_ROOT_CONTAINER, RygelMediathekRootContainerClass))

typedef struct _RygelMediathekRootContainer RygelMediathekRootContainer;
typedef struct _RygelMediathekRootContainerClass RygelMediathekRootContainerClass;
typedef struct _RygelMediathekRootContainerPrivate RygelMediathekRootContainerPrivate;

struct _RygelMediathekRssContainer {
	RygelMediaContainer parent_instance;
	RygelMediathekRssContainerPrivate * priv;
};

struct _RygelMediathekRssContainerClass {
	RygelMediaContainerClass parent_class;
};

struct _RygelMediathekRssContainerPrivate {
	GeeArrayList* items;
	guint zdf_content_id;
	SoupDate* last_modified;
};

typedef enum  {
	RYGEL_MEDIATHEK_VIDEO_ITEM_ERROR_XML_PARSE_ERROR
} RygelMediathekVideoItemError;
#define RYGEL_MEDIATHEK_VIDEO_ITEM_ERROR rygel_mediathek_video_item_error_quark ()
struct _RygelMediathekRootContainer {
	RygelMediaContainer parent_instance;
	RygelMediathekRootContainerPrivate * priv;
	SoupSessionAsync* session;
};

struct _RygelMediathekRootContainerClass {
	RygelMediaContainerClass parent_class;
};



GType rygel_mediathek_rss_container_get_type (void);
#define RYGEL_MEDIATHEK_RSS_CONTAINER_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), RYGEL_TYPE_MEDIATHEK_RSS_CONTAINER, RygelMediathekRssContainerPrivate))
enum  {
	RYGEL_MEDIATHEK_RSS_CONTAINER_DUMMY_PROPERTY
};
static gboolean rygel_mediathek_rss_container_parse_response (RygelMediathekRssContainer* self, const char* data, gsize length);
static void rygel_mediathek_rss_container_on_feed_got (RygelMediathekRssContainer* self, SoupSession* session, SoupMessage* msg);
GType rygel_mediathek_video_item_get_type (void);
GQuark rygel_mediathek_video_item_error_quark (void);
RygelMediathekVideoItem* rygel_mediathek_video_item_create_from_xml (RygelMediaContainer* parent, xmlNode* item, GError** error);
static void rygel_mediathek_rss_container_real_get_children (RygelMediaContainer* base, guint offset, guint max_count, GCancellable* cancellable, GAsyncReadyCallback callback, void* callback_target);
static GeeList* rygel_mediathek_rss_container_real_get_children_finish (RygelMediaContainer* base, GAsyncResult* res, GError** error);
static void rygel_mediathek_rss_container_real_find_object (RygelMediaContainer* base, const char* id, GCancellable* cancellable, GAsyncReadyCallback callback, void* callback_target);
RygelMediaObject* rygel_mediathek_rss_container_find_object_sync (RygelMediathekRssContainer* self, const char* id);
static RygelMediaObject* rygel_mediathek_rss_container_real_find_object_finish (RygelMediaContainer* base, GAsyncResult* res, GError** error);
GType rygel_mediathek_root_container_get_type (void);
static void _rygel_mediathek_rss_container_on_feed_got_soup_session_callback (SoupSession* session, SoupMessage* msg, gpointer self);
void rygel_mediathek_rss_container_update (RygelMediathekRssContainer* self);
RygelMediathekRssContainer* rygel_mediathek_rss_container_new (RygelMediaContainer* parent, guint id);
RygelMediathekRssContainer* rygel_mediathek_rss_container_construct (GType object_type, RygelMediaContainer* parent, guint id);
RygelMediathekRssContainer* rygel_mediathek_rss_container_new (RygelMediaContainer* parent, guint id);
static gpointer rygel_mediathek_rss_container_parent_class = NULL;
static void rygel_mediathek_rss_container_finalize (GObject* obj);
static int _vala_strcmp0 (const char * str1, const char * str2);



static void rygel_mediathek_rss_container_on_feed_got (RygelMediathekRssContainer* self, SoupSession* session, SoupMessage* msg) {
	guint _tmp0_;
	g_return_if_fail (self != NULL);
	g_return_if_fail (session != NULL);
	g_return_if_fail (msg != NULL);
	switch ((g_object_get (msg, "status-code", &_tmp0_, NULL), _tmp0_)) {
		case 304:
		{
			g_message ("rygel-mediathek-rss-container.vala:36: Feed has not changed, nothing to do");
			break;
		}
		case 200:
		{
			if (rygel_mediathek_rss_container_parse_response (self, msg->response_body->data, (gsize) msg->response_body->length)) {
				SoupDate* _tmp1_;
				_tmp1_ = NULL;
				self->priv->last_modified = (_tmp1_ = soup_date_new_from_string (soup_message_headers_get (msg->response_headers, "Date")), (self->priv->last_modified == NULL) ? NULL : (self->priv->last_modified = (soup_date_free (self->priv->last_modified), NULL)), _tmp1_);
			}
			break;
		}
		default:
		{
			guint _tmp2_;
			guint _tmp3_;
			g_warning ("rygel-mediathek-rss-container.vala:47: Got unexpected response %u (%s)", (g_object_get (msg, "status-code", &_tmp2_, NULL), _tmp2_), soup_status_get_phrase ((g_object_get (msg, "status-code", &_tmp3_, NULL), _tmp3_)));
			break;
		}
	}
}


static gboolean rygel_mediathek_rss_container_parse_response (RygelMediathekRssContainer* self, const char* data, gsize length) {
	GError * _inner_error_;
	gboolean ret;
	xmlDoc* doc;
	g_return_val_if_fail (self != NULL, FALSE);
	g_return_val_if_fail (data != NULL, FALSE);
	_inner_error_ = NULL;
	ret = FALSE;
	doc = xmlParseMemory (data, (gint) length);
	if (doc != NULL) {
		xmlXPathContext* ctx;
		xmlXPathObject* xpo;
		gboolean _tmp0_;
		gee_collection_clear ((GeeCollection*) self->priv->items);
		ctx = xmlXPathNewContext (doc);
		xpo = xmlXPathEval ("/rss/channel/title", ctx);
		_tmp0_ = FALSE;
		if (xpo->type == XPATH_NODESET) {
			_tmp0_ = xmlXPathNodeSetGetLength (xpo->nodesetval) > 0;
		} else {
			_tmp0_ = FALSE;
		}
		if (_tmp0_) {
			char* _tmp1_;
			/* just use first title (there should be only one)*/
			_tmp1_ = NULL;
			((RygelMediaObject*) self)->title = (_tmp1_ = xmlNodeGetContent (xmlXPathNodeSetItem (xpo->nodesetval, 0)), ((RygelMediaObject*) self)->title = (g_free (((RygelMediaObject*) self)->title), NULL), _tmp1_);
		}
		xpo = xmlXPathEval ("/rss/channel/item", ctx);
		if (xpo->type == XPATH_NODESET) {
			{
				gint i;
				i = 0;
				for (; i < xmlXPathNodeSetGetLength (xpo->nodesetval); i++) {
					xmlNode* node;
					node = xmlXPathNodeSetItem (xpo->nodesetval, i);
					{
						RygelMediathekVideoItem* item;
						item = rygel_mediathek_video_item_create_from_xml ((RygelMediaContainer*) self, node, &_inner_error_);
						if (_inner_error_ != NULL) {
							if (_inner_error_->domain == RYGEL_MEDIATHEK_VIDEO_ITEM_ERROR) {
								goto __catch2_rygel_mediathek_video_item_error;
							}
							goto __finally2;
						}
						gee_collection_add ((GeeCollection*) self->priv->items, (RygelMediaItem*) item);
						ret = TRUE;
						(item == NULL) ? NULL : (item = (g_object_unref (item), NULL));
					}
					goto __finally2;
					__catch2_rygel_mediathek_video_item_error:
					{
						GError * _error_;
						_error_ = _inner_error_;
						_inner_error_ = NULL;
						{
							g_warning ("rygel-mediathek-rss-container.vala:79: Error creating video item: %s", _error_->message);
							(_error_ == NULL) ? NULL : (_error_ = (g_error_free (_error_), NULL));
						}
					}
					__finally2:
					if (_inner_error_ != NULL) {
						(ctx == NULL) ? NULL : (ctx = (xmlXPathFreeContext (ctx), NULL));
						g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, _inner_error_->message);
						g_clear_error (&_inner_error_);
						return FALSE;
					}
				}
			}
		} else {
			g_warning ("rygel-mediathek-rss-container.vala:85: XPath query failed");
		}
		xmlFreeDoc (doc);
		((RygelMediaContainer*) self)->child_count = (guint) gee_collection_get_size ((GeeCollection*) self->priv->items);
		rygel_media_container_updated ((RygelMediaContainer*) self);
		(ctx == NULL) ? NULL : (ctx = (xmlXPathFreeContext (ctx), NULL));
	} else {
		g_warning ("rygel-mediathek-rss-container.vala:93: Failed to parse doc");
	}
	return ret;
}


static void rygel_mediathek_rss_container_real_get_children (RygelMediaContainer* base, guint offset, guint max_count, GCancellable* cancellable, GAsyncReadyCallback callback, void* callback_target) {
	RygelMediathekRssContainer * self;
	guint stop;
	GeeList* children;
	RygelSimpleAsyncResult* res;
	GeeList* _tmp1_;
	GeeList* _tmp0_;
	self = (RygelMediathekRssContainer*) base;
	stop = offset + max_count;
	stop = CLAMP (stop, (guint) 0, ((RygelMediaContainer*) self)->child_count);
	children = gee_list_slice ((GeeList*) self->priv->items, (gint) offset, (gint) stop);
	res = rygel_simple_async_result_new (GEE_TYPE_LIST, (GBoxedCopyFunc) g_object_ref, g_object_unref, (GObject*) self, callback, callback_target);
	_tmp1_ = NULL;
	_tmp0_ = NULL;
	res->data = (_tmp1_ = (_tmp0_ = children, (_tmp0_ == NULL) ? NULL : g_object_ref (_tmp0_)), (res->data == NULL) ? NULL : (res->data = (g_object_unref (res->data), NULL)), _tmp1_);
	rygel_simple_async_result_complete_in_idle (res);
	(children == NULL) ? NULL : (children = (g_object_unref (children), NULL));
	(res == NULL) ? NULL : (res = (g_object_unref (res), NULL));
}


static GeeList* rygel_mediathek_rss_container_real_get_children_finish (RygelMediaContainer* base, GAsyncResult* res, GError** error) {
	RygelMediathekRssContainer * self;
	RygelSimpleAsyncResult* _tmp0_;
	RygelSimpleAsyncResult* simple_res;
	GeeList* _tmp1_;
	GeeList* _tmp2_;
	self = (RygelMediathekRssContainer*) base;
	g_return_val_if_fail (res != NULL, NULL);
	_tmp0_ = NULL;
	simple_res = (_tmp0_ = RYGEL_SIMPLE_ASYNC_RESULT (res), (_tmp0_ == NULL) ? NULL : g_object_ref (_tmp0_));
	_tmp1_ = NULL;
	_tmp2_ = NULL;
	return (_tmp2_ = (_tmp1_ = (GeeList*) simple_res->data, (_tmp1_ == NULL) ? NULL : g_object_ref (_tmp1_)), (simple_res == NULL) ? NULL : (simple_res = (g_object_unref (simple_res), NULL)), _tmp2_);
}


static void rygel_mediathek_rss_container_real_find_object (RygelMediaContainer* base, const char* id, GCancellable* cancellable, GAsyncReadyCallback callback, void* callback_target) {
	RygelMediathekRssContainer * self;
	RygelSimpleAsyncResult* res;
	char* _tmp1_;
	const char* _tmp0_;
	self = (RygelMediathekRssContainer*) base;
	g_return_if_fail (id != NULL);
	res = rygel_simple_async_result_new (G_TYPE_STRING, (GBoxedCopyFunc) g_strdup, g_free, (GObject*) self, callback, callback_target);
	_tmp1_ = NULL;
	_tmp0_ = NULL;
	res->data = (_tmp1_ = (_tmp0_ = id, (_tmp0_ == NULL) ? NULL : g_strdup (_tmp0_)), res->data = (g_free (res->data), NULL), _tmp1_);
	rygel_simple_async_result_complete_in_idle (res);
	(res == NULL) ? NULL : (res = (g_object_unref (res), NULL));
}


static RygelMediaObject* rygel_mediathek_rss_container_real_find_object_finish (RygelMediaContainer* base, GAsyncResult* res, GError** error) {
	RygelMediathekRssContainer * self;
	const char* _tmp0_;
	char* id;
	RygelMediaObject* _tmp1_;
	self = (RygelMediathekRssContainer*) base;
	g_return_val_if_fail (res != NULL, NULL);
	_tmp0_ = NULL;
	id = (_tmp0_ = (const char*) RYGEL_SIMPLE_ASYNC_RESULT (res)->data, (_tmp0_ == NULL) ? NULL : g_strdup (_tmp0_));
	_tmp1_ = NULL;
	return (_tmp1_ = rygel_mediathek_rss_container_find_object_sync (self, id), id = (g_free (id), NULL), _tmp1_);
}


RygelMediaObject* rygel_mediathek_rss_container_find_object_sync (RygelMediathekRssContainer* self, const char* id) {
	RygelMediaItem* item;
	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (id != NULL, NULL);
	item = NULL;
	{
		GeeIterator* _tmp_it;
		_tmp_it = gee_iterable_iterator ((GeeIterable*) self->priv->items);
		while (gee_iterator_next (_tmp_it)) {
			RygelMediaItem* tmp;
			tmp = (RygelMediaItem*) gee_iterator_get (_tmp_it);
			if (_vala_strcmp0 (id, ((RygelMediaObject*) tmp)->id) == 0) {
				RygelMediaItem* _tmp1_;
				RygelMediaItem* _tmp0_;
				_tmp1_ = NULL;
				_tmp0_ = NULL;
				item = (_tmp1_ = (_tmp0_ = tmp, (_tmp0_ == NULL) ? NULL : g_object_ref (_tmp0_)), (item == NULL) ? NULL : (item = (g_object_unref (item), NULL)), _tmp1_);
				(tmp == NULL) ? NULL : (tmp = (g_object_unref (tmp), NULL));
				break;
			}
			(tmp == NULL) ? NULL : (tmp = (g_object_unref (tmp), NULL));
		}
		(_tmp_it == NULL) ? NULL : (_tmp_it = (g_object_unref (_tmp_it), NULL));
	}
	return (RygelMediaObject*) item;
}


static void _rygel_mediathek_rss_container_on_feed_got_soup_session_callback (SoupSession* session, SoupMessage* msg, gpointer self) {
	rygel_mediathek_rss_container_on_feed_got (self, session, msg);
}


void rygel_mediathek_rss_container_update (RygelMediathekRssContainer* self) {
	char* _tmp0_;
	SoupMessage* _tmp1_;
	SoupMessage* message;
	SoupMessage* _tmp2_;
	g_return_if_fail (self != NULL);
	_tmp0_ = NULL;
	_tmp1_ = NULL;
	message = (_tmp1_ = soup_message_new ("GET", _tmp0_ = g_strdup_printf ("http://www.zdf.de/ZDFmediathek/content/%u?view=rss", self->priv->zdf_content_id)), _tmp0_ = (g_free (_tmp0_), NULL), _tmp1_);
	if (self->priv->last_modified != NULL) {
		g_debug ("rygel-mediathek-rss-container.vala:154: Requesting change since %s", soup_date_to_string (self->priv->last_modified, SOUP_DATE_HTTP));
		soup_message_headers_append (message->request_headers, "If-Modified-Since", soup_date_to_string (self->priv->last_modified, SOUP_DATE_HTTP));
	}
	_tmp2_ = NULL;
	soup_session_queue_message ((SoupSession*) RYGEL_MEDIATHEK_ROOT_CONTAINER (((RygelMediaObject*) self)->parent)->session, (_tmp2_ = message, (_tmp2_ == NULL) ? NULL : g_object_ref (_tmp2_)), _rygel_mediathek_rss_container_on_feed_got_soup_session_callback, self);
	(message == NULL) ? NULL : (message = (g_object_unref (message), NULL));
}


RygelMediathekRssContainer* rygel_mediathek_rss_container_construct (GType object_type, RygelMediaContainer* parent, guint id) {
	RygelMediathekRssContainer * self;
	char* _tmp1_;
	char* _tmp0_;
	GeeArrayList* _tmp2_;
	g_return_val_if_fail (parent != NULL, NULL);
	_tmp1_ = NULL;
	_tmp0_ = NULL;
	self = (RygelMediathekRssContainer*) rygel_media_container_construct (object_type, _tmp0_ = g_strdup_printf ("GroupId:%u", id), parent, _tmp1_ = g_strdup_printf ("ZDF Mediathek RSS feed %u", id), (guint) 0);
	_tmp1_ = (g_free (_tmp1_), NULL);
	_tmp0_ = (g_free (_tmp0_), NULL);
	_tmp2_ = NULL;
	self->priv->items = (_tmp2_ = gee_array_list_new (RYGEL_TYPE_MEDIA_ITEM, (GBoxedCopyFunc) g_object_ref, g_object_unref, g_direct_equal), (self->priv->items == NULL) ? NULL : (self->priv->items = (g_object_unref (self->priv->items), NULL)), _tmp2_);
	((RygelMediaContainer*) self)->child_count = (guint) 0;
	self->priv->zdf_content_id = id;
	rygel_mediathek_rss_container_update (self);
	return self;
}


RygelMediathekRssContainer* rygel_mediathek_rss_container_new (RygelMediaContainer* parent, guint id) {
	return rygel_mediathek_rss_container_construct (RYGEL_TYPE_MEDIATHEK_RSS_CONTAINER, parent, id);
}


static void rygel_mediathek_rss_container_class_init (RygelMediathekRssContainerClass * klass) {
	rygel_mediathek_rss_container_parent_class = g_type_class_peek_parent (klass);
	g_type_class_add_private (klass, sizeof (RygelMediathekRssContainerPrivate));
	RYGEL_MEDIA_CONTAINER_CLASS (klass)->get_children = rygel_mediathek_rss_container_real_get_children;
	RYGEL_MEDIA_CONTAINER_CLASS (klass)->get_children_finish = rygel_mediathek_rss_container_real_get_children_finish;
	RYGEL_MEDIA_CONTAINER_CLASS (klass)->find_object = rygel_mediathek_rss_container_real_find_object;
	RYGEL_MEDIA_CONTAINER_CLASS (klass)->find_object_finish = rygel_mediathek_rss_container_real_find_object_finish;
	G_OBJECT_CLASS (klass)->finalize = rygel_mediathek_rss_container_finalize;
}


static void rygel_mediathek_rss_container_instance_init (RygelMediathekRssContainer * self) {
	self->priv = RYGEL_MEDIATHEK_RSS_CONTAINER_GET_PRIVATE (self);
	self->priv->last_modified = NULL;
}


static void rygel_mediathek_rss_container_finalize (GObject* obj) {
	RygelMediathekRssContainer * self;
	self = RYGEL_MEDIATHEK_RSS_CONTAINER (obj);
	(self->priv->items == NULL) ? NULL : (self->priv->items = (g_object_unref (self->priv->items), NULL));
	(self->priv->last_modified == NULL) ? NULL : (self->priv->last_modified = (soup_date_free (self->priv->last_modified), NULL));
	G_OBJECT_CLASS (rygel_mediathek_rss_container_parent_class)->finalize (obj);
}


GType rygel_mediathek_rss_container_get_type (void) {
	static GType rygel_mediathek_rss_container_type_id = 0;
	if (rygel_mediathek_rss_container_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (RygelMediathekRssContainerClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) rygel_mediathek_rss_container_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (RygelMediathekRssContainer), 0, (GInstanceInitFunc) rygel_mediathek_rss_container_instance_init, NULL };
		rygel_mediathek_rss_container_type_id = g_type_register_static (RYGEL_TYPE_MEDIA_CONTAINER, "RygelMediathekRssContainer", &g_define_type_info, 0);
	}
	return rygel_mediathek_rss_container_type_id;
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




