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
#include <stdlib.h>
#include <string.h>
#include <libxml/tree.h>
#include <gee/arraylist.h>
#include <gee/iterable.h>
#include <gee/iterator.h>
#include <gee/collection.h>


#define RYGEL_TYPE_MEDIATHEK_VIDEO_ITEM (rygel_mediathek_video_item_get_type ())
#define RYGEL_MEDIATHEK_VIDEO_ITEM(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_MEDIATHEK_VIDEO_ITEM, RygelMediathekVideoItem))
#define RYGEL_MEDIATHEK_VIDEO_ITEM_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_MEDIATHEK_VIDEO_ITEM, RygelMediathekVideoItemClass))
#define RYGEL_IS_MEDIATHEK_VIDEO_ITEM(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_MEDIATHEK_VIDEO_ITEM))
#define RYGEL_IS_MEDIATHEK_VIDEO_ITEM_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_MEDIATHEK_VIDEO_ITEM))
#define RYGEL_MEDIATHEK_VIDEO_ITEM_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_MEDIATHEK_VIDEO_ITEM, RygelMediathekVideoItemClass))

typedef struct _RygelMediathekVideoItem RygelMediathekVideoItem;
typedef struct _RygelMediathekVideoItemClass RygelMediathekVideoItemClass;
typedef struct _RygelMediathekVideoItemPrivate RygelMediathekVideoItemPrivate;

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
	RYGEL_MEDIATHEK_VIDEO_ITEM_ERROR_XML_PARSE_ERROR
} RygelMediathekVideoItemError;
#define RYGEL_MEDIATHEK_VIDEO_ITEM_ERROR rygel_mediathek_video_item_error_quark ()
struct _RygelMediathekVideoItem {
	RygelMediaItem parent_instance;
	RygelMediathekVideoItemPrivate * priv;
};

struct _RygelMediathekVideoItemClass {
	RygelMediaItemClass parent_class;
};

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



GQuark rygel_mediathek_video_item_error_quark (void);
GType rygel_mediathek_video_item_get_type (void);
enum  {
	RYGEL_MEDIATHEK_VIDEO_ITEM_DUMMY_PROPERTY
};
static RygelMediathekVideoItem* rygel_mediathek_video_item_new (RygelMediaContainer* parent, const char* title);
static RygelMediathekVideoItem* rygel_mediathek_video_item_construct (GType object_type, RygelMediaContainer* parent, const char* title);
static RygelMediathekVideoItem* rygel_mediathek_video_item_new (RygelMediaContainer* parent, const char* title);
static gboolean rygel_mediathek_video_item_namespace_ok (xmlNode* node);
GType rygel_mediathek_asx_playlist_get_type (void);
RygelMediathekAsxPlaylist* rygel_mediathek_asx_playlist_new (const char* uri);
RygelMediathekAsxPlaylist* rygel_mediathek_asx_playlist_construct (GType object_type, const char* uri);
GQuark rygel_mediathek_asx_playlist_error_quark (void);
void rygel_mediathek_asx_playlist_parse (RygelMediathekAsxPlaylist* self, GError** error);
RygelMediathekAsxPlaylist* rygel_mediathek_video_item_handle_content (xmlNode* group, GError** error);
RygelMediathekVideoItem* rygel_mediathek_video_item_create_from_xml (RygelMediaContainer* parent, xmlNode* item, GError** error);
static gpointer rygel_mediathek_video_item_parent_class = NULL;
static int _vala_strcmp0 (const char * str1, const char * str2);



GQuark rygel_mediathek_video_item_error_quark (void) {
	return g_quark_from_static_string ("rygel_mediathek_video_item_error-quark");
}


static RygelMediathekVideoItem* rygel_mediathek_video_item_construct (GType object_type, RygelMediaContainer* parent, const char* title) {
	RygelMediathekVideoItem * self;
	char* _tmp0_;
	char* _tmp1_;
	char* _tmp2_;
	g_return_val_if_fail (parent != NULL, NULL);
	g_return_val_if_fail (title != NULL, NULL);
	_tmp0_ = NULL;
	self = (RygelMediathekVideoItem*) rygel_media_item_construct (object_type, _tmp0_ = g_compute_checksum_for_string (G_CHECKSUM_MD5, title, -1), parent, title, RYGEL_MEDIA_ITEM_VIDEO_CLASS);
	_tmp0_ = (g_free (_tmp0_), NULL);
	_tmp1_ = NULL;
	((RygelMediaItem*) self)->mime_type = (_tmp1_ = g_strdup ("video/x-ms-asf"), ((RygelMediaItem*) self)->mime_type = (g_free (((RygelMediaItem*) self)->mime_type), NULL), _tmp1_);
	_tmp2_ = NULL;
	((RygelMediaItem*) self)->author = (_tmp2_ = g_strdup ("ZDF - Zweites Deutsches Fernsehen"), ((RygelMediaItem*) self)->author = (g_free (((RygelMediaItem*) self)->author), NULL), _tmp2_);
	return self;
}


static RygelMediathekVideoItem* rygel_mediathek_video_item_new (RygelMediaContainer* parent, const char* title) {
	return rygel_mediathek_video_item_construct (RYGEL_TYPE_MEDIATHEK_VIDEO_ITEM, parent, title);
}


static gboolean rygel_mediathek_video_item_namespace_ok (xmlNode* node) {
	gboolean _tmp0_;
	_tmp0_ = FALSE;
	if (node->ns != NULL) {
		_tmp0_ = _vala_strcmp0 (node->ns->prefix, "media") == 0;
	} else {
		_tmp0_ = FALSE;
	}
	return _tmp0_;
}


RygelMediathekAsxPlaylist* rygel_mediathek_video_item_handle_content (xmlNode* group, GError** error) {
	GError * _inner_error_;
	RygelMediathekAsxPlaylist* asx;
	_inner_error_ = NULL;
	asx = NULL;
	if (rygel_mediathek_video_item_namespace_ok (group)) {
		xmlAttr* attr;
		attr = xmlHasProp (group, "url");
		if (attr != NULL) {
			const char* _tmp0_;
			char* url;
			_tmp0_ = NULL;
			url = (_tmp0_ = attr->children->content, (_tmp0_ == NULL) ? NULL : g_strdup (_tmp0_));
			if (g_str_has_suffix (url, ".asx")) {
				{
					RygelMediathekAsxPlaylist* _tmp1_;
					_tmp1_ = NULL;
					asx = (_tmp1_ = rygel_mediathek_asx_playlist_new (url), (asx == NULL) ? NULL : (asx = (g_object_unref (asx), NULL)), _tmp1_);
					rygel_mediathek_asx_playlist_parse (asx, &_inner_error_);
					if (_inner_error_ != NULL) {
						if (_inner_error_->domain == RYGEL_MEDIATHEK_ASX_PLAYLIST_ERROR) {
							goto __catch1_rygel_mediathek_asx_playlist_error;
						}
						goto __finally1;
					}
				}
				goto __finally1;
				__catch1_rygel_mediathek_asx_playlist_error:
				{
					GError * _error_;
					_error_ = _inner_error_;
					_inner_error_ = NULL;
					{
						RygelMediathekAsxPlaylist* _tmp2_;
						_tmp2_ = NULL;
						asx = (_tmp2_ = NULL, (asx == NULL) ? NULL : (asx = (g_object_unref (asx), NULL)), _tmp2_);
						(_error_ == NULL) ? NULL : (_error_ = (g_error_free (_error_), NULL));
					}
				}
				__finally1:
				if (_inner_error_ != NULL) {
					if (_inner_error_->domain == RYGEL_MEDIATHEK_VIDEO_ITEM_ERROR) {
						g_propagate_error (error, _inner_error_);
						url = (g_free (url), NULL);
						(asx == NULL) ? NULL : (asx = (g_object_unref (asx), NULL));
						return NULL;
					} else {
						url = (g_free (url), NULL);
						(asx == NULL) ? NULL : (asx = (g_object_unref (asx), NULL));
						g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, _inner_error_->message);
						g_clear_error (&_inner_error_);
						return NULL;
					}
				}
			}
			url = (g_free (url), NULL);
		} else {
			_inner_error_ = g_error_new_literal (RYGEL_MEDIATHEK_VIDEO_ITEM_ERROR, RYGEL_MEDIATHEK_VIDEO_ITEM_ERROR_XML_PARSE_ERROR, "group node has url property");
			if (_inner_error_ != NULL) {
				if (_inner_error_->domain == RYGEL_MEDIATHEK_VIDEO_ITEM_ERROR) {
					g_propagate_error (error, _inner_error_);
					(asx == NULL) ? NULL : (asx = (g_object_unref (asx), NULL));
					return NULL;
				} else {
					(asx == NULL) ? NULL : (asx = (g_object_unref (asx), NULL));
					g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, _inner_error_->message);
					g_clear_error (&_inner_error_);
					return NULL;
				}
			}
		}
	} else {
		_inner_error_ = g_error_new_literal (RYGEL_MEDIATHEK_VIDEO_ITEM_ERROR, RYGEL_MEDIATHEK_VIDEO_ITEM_ERROR_XML_PARSE_ERROR, "invalid or no namespace");
		if (_inner_error_ != NULL) {
			if (_inner_error_->domain == RYGEL_MEDIATHEK_VIDEO_ITEM_ERROR) {
				g_propagate_error (error, _inner_error_);
				(asx == NULL) ? NULL : (asx = (g_object_unref (asx), NULL));
				return NULL;
			} else {
				(asx == NULL) ? NULL : (asx = (g_object_unref (asx), NULL));
				g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, _inner_error_->message);
				g_clear_error (&_inner_error_);
				return NULL;
			}
		}
	}
	return asx;
}


RygelMediathekVideoItem* rygel_mediathek_video_item_create_from_xml (RygelMediaContainer* parent, xmlNode* item, GError** error) {
	GError * _inner_error_;
	char* title;
	RygelMediathekVideoItem* video_item;
	RygelMediathekAsxPlaylist* asx;
	RygelMediathekVideoItem* _tmp5_;
	RygelMediathekVideoItem* _tmp6_;
	g_return_val_if_fail (parent != NULL, NULL);
	_inner_error_ = NULL;
	title = NULL;
	video_item = NULL;
	asx = NULL;
	{
		xmlNode* item_child;
		item_child = item->children;
		for (; item_child != NULL; item_child = item_child->next) {
			GQuark _tmp4_;
			const char* _tmp3_;
			_tmp3_ = NULL;
			static GQuark _tmp4__label0 = 0;
			static GQuark _tmp4__label1 = 0;
			_tmp3_ = item_child->name;
			_tmp4_ = (NULL == _tmp3_) ? 0 : g_quark_from_string (_tmp3_);
			if (_tmp4_ == ((0 != _tmp4__label0) ? _tmp4__label0 : (_tmp4__label0 = g_quark_from_static_string ("title"))))
			do {
				char* _tmp0_;
				_tmp0_ = NULL;
				title = (_tmp0_ = xmlNodeGetContent (item_child), title = (g_free (title), NULL), _tmp0_);
				break;
			} while (0); else if (_tmp4_ == ((0 != _tmp4__label1) ? _tmp4__label1 : (_tmp4__label1 = g_quark_from_static_string ("group"))))
			do {
				if (rygel_mediathek_video_item_namespace_ok (item_child)) {
					{
						xmlNode* group;
						group = item_child->children;
						for (; group != NULL; group = group->next) {
							if (_vala_strcmp0 (group->name, "content") == 0) {
								RygelMediathekAsxPlaylist* _tmp1_;
								RygelMediathekAsxPlaylist* _tmp2_;
								_tmp1_ = rygel_mediathek_video_item_handle_content (group, &_inner_error_);
								if (_inner_error_ != NULL) {
									if (_inner_error_->domain == RYGEL_MEDIATHEK_VIDEO_ITEM_ERROR) {
										g_propagate_error (error, _inner_error_);
										title = (g_free (title), NULL);
										(video_item == NULL) ? NULL : (video_item = (g_object_unref (video_item), NULL));
										(asx == NULL) ? NULL : (asx = (g_object_unref (asx), NULL));
										return NULL;
									} else {
										title = (g_free (title), NULL);
										(video_item == NULL) ? NULL : (video_item = (g_object_unref (video_item), NULL));
										(asx == NULL) ? NULL : (asx = (g_object_unref (asx), NULL));
										g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, _inner_error_->message);
										g_clear_error (&_inner_error_);
										return NULL;
									}
								}
								_tmp2_ = NULL;
								asx = (_tmp2_ = _tmp1_, (asx == NULL) ? NULL : (asx = (g_object_unref (asx), NULL)), _tmp2_);
							}
						}
					}
				} else {
					_inner_error_ = g_error_new_literal (RYGEL_MEDIATHEK_VIDEO_ITEM_ERROR, RYGEL_MEDIATHEK_VIDEO_ITEM_ERROR_XML_PARSE_ERROR, "invalid or no namespace on group node");
					if (_inner_error_ != NULL) {
						if (_inner_error_->domain == RYGEL_MEDIATHEK_VIDEO_ITEM_ERROR) {
							g_propagate_error (error, _inner_error_);
							title = (g_free (title), NULL);
							(video_item == NULL) ? NULL : (video_item = (g_object_unref (video_item), NULL));
							(asx == NULL) ? NULL : (asx = (g_object_unref (asx), NULL));
							return NULL;
						} else {
							title = (g_free (title), NULL);
							(video_item == NULL) ? NULL : (video_item = (g_object_unref (video_item), NULL));
							(asx == NULL) ? NULL : (asx = (g_object_unref (asx), NULL));
							g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, _inner_error_->message);
							g_clear_error (&_inner_error_);
							return NULL;
						}
					}
				}
				break;
			} while (0); else
			do {
				break;
			} while (0);
		}
	}
	if (title == NULL) {
		_inner_error_ = g_error_new_literal (RYGEL_MEDIATHEK_VIDEO_ITEM_ERROR, RYGEL_MEDIATHEK_VIDEO_ITEM_ERROR_XML_PARSE_ERROR, "Could not find title");
		if (_inner_error_ != NULL) {
			if (_inner_error_->domain == RYGEL_MEDIATHEK_VIDEO_ITEM_ERROR) {
				g_propagate_error (error, _inner_error_);
				title = (g_free (title), NULL);
				(video_item == NULL) ? NULL : (video_item = (g_object_unref (video_item), NULL));
				(asx == NULL) ? NULL : (asx = (g_object_unref (asx), NULL));
				return NULL;
			} else {
				title = (g_free (title), NULL);
				(video_item == NULL) ? NULL : (video_item = (g_object_unref (video_item), NULL));
				(asx == NULL) ? NULL : (asx = (g_object_unref (asx), NULL));
				g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, _inner_error_->message);
				g_clear_error (&_inner_error_);
				return NULL;
			}
		}
	}
	if (asx == NULL) {
		_inner_error_ = g_error_new_literal (RYGEL_MEDIATHEK_VIDEO_ITEM_ERROR, RYGEL_MEDIATHEK_VIDEO_ITEM_ERROR_XML_PARSE_ERROR, "Could not find uris");
		if (_inner_error_ != NULL) {
			if (_inner_error_->domain == RYGEL_MEDIATHEK_VIDEO_ITEM_ERROR) {
				g_propagate_error (error, _inner_error_);
				title = (g_free (title), NULL);
				(video_item == NULL) ? NULL : (video_item = (g_object_unref (video_item), NULL));
				(asx == NULL) ? NULL : (asx = (g_object_unref (asx), NULL));
				return NULL;
			} else {
				title = (g_free (title), NULL);
				(video_item == NULL) ? NULL : (video_item = (g_object_unref (video_item), NULL));
				(asx == NULL) ? NULL : (asx = (g_object_unref (asx), NULL));
				g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, _inner_error_->message);
				g_clear_error (&_inner_error_);
				return NULL;
			}
		}
	}
	_tmp5_ = NULL;
	video_item = (_tmp5_ = rygel_mediathek_video_item_new (parent, title), (video_item == NULL) ? NULL : (video_item = (g_object_unref (video_item), NULL)), _tmp5_);
	{
		GeeIterator* _uri_it;
		_uri_it = gee_iterable_iterator ((GeeIterable*) asx->uris);
		while (gee_iterator_next (_uri_it)) {
			char* uri;
			uri = (char*) gee_iterator_get (_uri_it);
			gee_collection_add ((GeeCollection*) ((RygelMediaItem*) video_item)->uris, uri);
			uri = (g_free (uri), NULL);
		}
		(_uri_it == NULL) ? NULL : (_uri_it = (g_object_unref (_uri_it), NULL));
	}
	_tmp6_ = NULL;
	return (_tmp6_ = video_item, title = (g_free (title), NULL), (asx == NULL) ? NULL : (asx = (g_object_unref (asx), NULL)), _tmp6_);
}


static void rygel_mediathek_video_item_class_init (RygelMediathekVideoItemClass * klass) {
	rygel_mediathek_video_item_parent_class = g_type_class_peek_parent (klass);
}


static void rygel_mediathek_video_item_instance_init (RygelMediathekVideoItem * self) {
}


GType rygel_mediathek_video_item_get_type (void) {
	static GType rygel_mediathek_video_item_type_id = 0;
	if (rygel_mediathek_video_item_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (RygelMediathekVideoItemClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) rygel_mediathek_video_item_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (RygelMediathekVideoItem), 0, (GInstanceInitFunc) rygel_mediathek_video_item_instance_init, NULL };
		rygel_mediathek_video_item_type_id = g_type_register_static (RYGEL_TYPE_MEDIA_ITEM, "RygelMediathekVideoItem", &g_define_type_info, 0);
	}
	return rygel_mediathek_video_item_type_id;
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




