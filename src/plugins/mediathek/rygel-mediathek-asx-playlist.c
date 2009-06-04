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
#include <gee/arraylist.h>
#include <stdlib.h>
#include <string.h>
#include <libsoup/soup.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xpath.h>
#include <gee/collection.h>


#define RYGEL_TYPE_MEDIATHEK_ASX_PLAYLIST (rygel_mediathek_asx_playlist_get_type ())
#define RYGEL_MEDIATHEK_ASX_PLAYLIST(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_MEDIATHEK_ASX_PLAYLIST, RygelMediathekAsxPlaylist))
#define RYGEL_MEDIATHEK_ASX_PLAYLIST_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_MEDIATHEK_ASX_PLAYLIST, RygelMediathekAsxPlaylistClass))
#define RYGEL_IS_MEDIATHEK_ASX_PLAYLIST(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_MEDIATHEK_ASX_PLAYLIST))
#define RYGEL_IS_MEDIATHEK_ASX_PLAYLIST_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_MEDIATHEK_ASX_PLAYLIST))
#define RYGEL_MEDIATHEK_ASX_PLAYLIST_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_MEDIATHEK_ASX_PLAYLIST, RygelMediathekAsxPlaylistClass))

typedef struct _RygelMediathekAsxPlaylist RygelMediathekAsxPlaylist;
typedef struct _RygelMediathekAsxPlaylistClass RygelMediathekAsxPlaylistClass;
typedef struct _RygelMediathekAsxPlaylistPrivate RygelMediathekAsxPlaylistPrivate;

typedef enum  {
	RYGEL_MEDIATHEK_ASX_PLAYLIST_ERROR_XML_ERROR,
	RYGEL_MEDIATHEK_ASX_PLAYLIST_ERROR_NETWORK_ERROR
} RygelMediathekAsxPlaylistError;
#define RYGEL_MEDIATHEK_ASX_PLAYLIST_ERROR rygel_mediathek_asx_playlist_error_quark ()
/**
 * This class is a simple ASX playlist parser
 * 
 * It does nothing but extracting all href tags from an ASX
 * and ignore all of the other information that may be in it
 * 
 * This parser is //only// intended to work with the simple 
 * ASX files presented by the ZDF Mediathek streaming server
 */
struct _RygelMediathekAsxPlaylist {
	GObject parent_instance;
	RygelMediathekAsxPlaylistPrivate * priv;
	GeeArrayList* uris;
};

struct _RygelMediathekAsxPlaylistClass {
	GObjectClass parent_class;
};

struct _RygelMediathekAsxPlaylistPrivate {
	char* uri;
};



GQuark rygel_mediathek_asx_playlist_error_quark (void);
GType rygel_mediathek_asx_playlist_get_type (void);
#define RYGEL_MEDIATHEK_ASX_PLAYLIST_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), RYGEL_TYPE_MEDIATHEK_ASX_PLAYLIST, RygelMediathekAsxPlaylistPrivate))
enum  {
	RYGEL_MEDIATHEK_ASX_PLAYLIST_DUMMY_PROPERTY
};
RygelMediathekAsxPlaylist* rygel_mediathek_asx_playlist_new (const char* uri);
RygelMediathekAsxPlaylist* rygel_mediathek_asx_playlist_construct (GType object_type, const char* uri);
RygelMediathekAsxPlaylist* rygel_mediathek_asx_playlist_new (const char* uri);
void rygel_mediathek_asx_playlist_parse (RygelMediathekAsxPlaylist* self, GError** error);
static gpointer rygel_mediathek_asx_playlist_parent_class = NULL;
static void rygel_mediathek_asx_playlist_finalize (GObject* obj);



GQuark rygel_mediathek_asx_playlist_error_quark (void) {
	return g_quark_from_static_string ("rygel_mediathek_asx_playlist_error-quark");
}


RygelMediathekAsxPlaylist* rygel_mediathek_asx_playlist_construct (GType object_type, const char* uri) {
	RygelMediathekAsxPlaylist * self;
	GeeArrayList* _tmp0_;
	char* _tmp2_;
	const char* _tmp1_;
	g_return_val_if_fail (uri != NULL, NULL);
	self = g_object_newv (object_type, 0, NULL);
	_tmp0_ = NULL;
	self->uris = (_tmp0_ = gee_array_list_new (G_TYPE_STRING, (GBoxedCopyFunc) g_strdup, g_free, g_direct_equal), (self->uris == NULL) ? NULL : (self->uris = (g_object_unref (self->uris), NULL)), _tmp0_);
	_tmp2_ = NULL;
	_tmp1_ = NULL;
	self->priv->uri = (_tmp2_ = (_tmp1_ = uri, (_tmp1_ == NULL) ? NULL : g_strdup (_tmp1_)), self->priv->uri = (g_free (self->priv->uri), NULL), _tmp2_);
	return self;
}


RygelMediathekAsxPlaylist* rygel_mediathek_asx_playlist_new (const char* uri) {
	return rygel_mediathek_asx_playlist_construct (RYGEL_TYPE_MEDIATHEK_ASX_PLAYLIST, uri);
}


static glong string_get_length (const char* self) {
	g_return_val_if_fail (self != NULL, 0L);
	return g_utf8_strlen (self, -1);
}


/** 
     * Get and parse the ASX file.
     *
     * This will fetch the ASX file represented by an uri
     * using a synchronous soup session. As ASX seems to be
     * a bit inconsistent wrt tag case all the tags are
     * converted to lowercase. A XPath query is then used
     * to extract all of the href attributes for every entry
     * in the file
     */
void rygel_mediathek_asx_playlist_parse (RygelMediathekAsxPlaylist* self, GError** error) {
	GError * _inner_error_;
	SoupSessionSync* session;
	SoupMessage* message;
	guint _tmp0_;
	g_return_if_fail (self != NULL);
	_inner_error_ = NULL;
	/* FIXME make async using global soup session*/
	session = (SoupSessionSync*) soup_session_sync_new ();
	message = soup_message_new ("GET", self->priv->uri);
	soup_session_send_message ((SoupSession*) session, message);
	if ((g_object_get (message, "status-code", &_tmp0_, NULL), _tmp0_) == 200) {
		{
			GRegex* normalizer;
			char* normalized_content;
			xmlDoc* doc;
			/* lowercase all tags using regex and \L\E syntax*/
			normalizer = g_regex_new ("(<[/]?)([a-zA-Z:]+)", 0, 0, &_inner_error_);
			if (_inner_error_ != NULL) {
				if (_inner_error_->domain == G_REGEX_ERROR) {
					goto __catch0_g_regex_error;
				}
				goto __finally0;
			}
			normalized_content = g_regex_replace (normalizer, message->response_body->data, (glong) message->response_body->length, 0, "\\1\\L\\2\\E", 0, &_inner_error_);
			if (_inner_error_ != NULL) {
				(normalizer == NULL) ? NULL : (normalizer = (g_regex_unref (normalizer), NULL));
				if (_inner_error_->domain == G_REGEX_ERROR) {
					goto __catch0_g_regex_error;
				}
				goto __finally0;
			}
			doc = xmlParseMemory (normalized_content, (gint) string_get_length (normalized_content));
			if (doc != NULL) {
				xmlXPathContext* ctx;
				xmlXPathObject* xpo;
				ctx = xmlXPathNewContext (doc);
				xpo = xmlXPathEval ("/asx/entry/ref/@href", ctx);
				if (xpo->type == XPATH_NODESET) {
					{
						gint i;
						i = 0;
						for (; i < xmlXPathNodeSetGetLength (xpo->nodesetval); i++) {
							xmlNode* item;
							item = xmlXPathNodeSetItem (xpo->nodesetval, i);
							gee_collection_add ((GeeCollection*) self->uris, item->children->content);
						}
					}
				}
				(ctx == NULL) ? NULL : (ctx = (xmlXPathFreeContext (ctx), NULL));
			} else {
				_inner_error_ = g_error_new_literal (RYGEL_MEDIATHEK_ASX_PLAYLIST_ERROR, RYGEL_MEDIATHEK_ASX_PLAYLIST_ERROR_XML_ERROR, "Could not received XML");
				if (_inner_error_ != NULL) {
					(normalizer == NULL) ? NULL : (normalizer = (g_regex_unref (normalizer), NULL));
					normalized_content = (g_free (normalized_content), NULL);
					if (_inner_error_->domain == G_REGEX_ERROR) {
						goto __catch0_g_regex_error;
					}
					goto __finally0;
				}
			}
			(normalizer == NULL) ? NULL : (normalizer = (g_regex_unref (normalizer), NULL));
			normalized_content = (g_free (normalized_content), NULL);
		}
		goto __finally0;
		__catch0_g_regex_error:
		{
			GError * _error_;
			_error_ = _inner_error_;
			_inner_error_ = NULL;
			{
				(_error_ == NULL) ? NULL : (_error_ = (g_error_free (_error_), NULL));
			}
		}
		__finally0:
		if (_inner_error_ != NULL) {
			if (_inner_error_->domain == RYGEL_MEDIATHEK_ASX_PLAYLIST_ERROR) {
				g_propagate_error (error, _inner_error_);
				(session == NULL) ? NULL : (session = (g_object_unref (session), NULL));
				(message == NULL) ? NULL : (message = (g_object_unref (message), NULL));
				return;
			} else {
				(session == NULL) ? NULL : (session = (g_object_unref (session), NULL));
				(message == NULL) ? NULL : (message = (g_object_unref (message), NULL));
				g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, _inner_error_->message);
				g_clear_error (&_inner_error_);
				return;
			}
		}
	} else {
		char* _tmp3_;
		guint _tmp1_;
		guint _tmp2_;
		GError* _tmp4_;
		_tmp3_ = NULL;
		_tmp4_ = NULL;
		_inner_error_ = (_tmp4_ = g_error_new_literal (RYGEL_MEDIATHEK_ASX_PLAYLIST_ERROR, RYGEL_MEDIATHEK_ASX_PLAYLIST_ERROR_NETWORK_ERROR, _tmp3_ = g_strdup_printf ("Could not download playlist, error code was %u (%s)", (g_object_get (message, "status-code", &_tmp1_, NULL), _tmp1_), soup_status_get_phrase ((g_object_get (message, "status-code", &_tmp2_, NULL), _tmp2_)))), _tmp3_ = (g_free (_tmp3_), NULL), _tmp4_);
		if (_inner_error_ != NULL) {
			if (_inner_error_->domain == RYGEL_MEDIATHEK_ASX_PLAYLIST_ERROR) {
				g_propagate_error (error, _inner_error_);
				(session == NULL) ? NULL : (session = (g_object_unref (session), NULL));
				(message == NULL) ? NULL : (message = (g_object_unref (message), NULL));
				return;
			} else {
				(session == NULL) ? NULL : (session = (g_object_unref (session), NULL));
				(message == NULL) ? NULL : (message = (g_object_unref (message), NULL));
				g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, _inner_error_->message);
				g_clear_error (&_inner_error_);
				return;
			}
		}
	}
	(session == NULL) ? NULL : (session = (g_object_unref (session), NULL));
	(message == NULL) ? NULL : (message = (g_object_unref (message), NULL));
}


static void rygel_mediathek_asx_playlist_class_init (RygelMediathekAsxPlaylistClass * klass) {
	rygel_mediathek_asx_playlist_parent_class = g_type_class_peek_parent (klass);
	g_type_class_add_private (klass, sizeof (RygelMediathekAsxPlaylistPrivate));
	G_OBJECT_CLASS (klass)->finalize = rygel_mediathek_asx_playlist_finalize;
}


static void rygel_mediathek_asx_playlist_instance_init (RygelMediathekAsxPlaylist * self) {
	self->priv = RYGEL_MEDIATHEK_ASX_PLAYLIST_GET_PRIVATE (self);
}


static void rygel_mediathek_asx_playlist_finalize (GObject* obj) {
	RygelMediathekAsxPlaylist * self;
	self = RYGEL_MEDIATHEK_ASX_PLAYLIST (obj);
	(self->uris == NULL) ? NULL : (self->uris = (g_object_unref (self->uris), NULL));
	self->priv->uri = (g_free (self->priv->uri), NULL);
	G_OBJECT_CLASS (rygel_mediathek_asx_playlist_parent_class)->finalize (obj);
}


GType rygel_mediathek_asx_playlist_get_type (void) {
	static GType rygel_mediathek_asx_playlist_type_id = 0;
	if (rygel_mediathek_asx_playlist_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (RygelMediathekAsxPlaylistClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) rygel_mediathek_asx_playlist_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (RygelMediathekAsxPlaylist), 0, (GInstanceInitFunc) rygel_mediathek_asx_playlist_instance_init, NULL };
		rygel_mediathek_asx_playlist_type_id = g_type_register_static (G_TYPE_OBJECT, "RygelMediathekAsxPlaylist", &g_define_type_info, 0);
	}
	return rygel_mediathek_asx_playlist_type_id;
}




