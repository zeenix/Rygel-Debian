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
#include <gst/gst.h>
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

#define RYGEL_TYPE_LIVE_RESPONSE (rygel_live_response_get_type ())
#define RYGEL_LIVE_RESPONSE(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_LIVE_RESPONSE, RygelLiveResponse))
#define RYGEL_LIVE_RESPONSE_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_LIVE_RESPONSE, RygelLiveResponseClass))
#define RYGEL_IS_LIVE_RESPONSE(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_LIVE_RESPONSE))
#define RYGEL_IS_LIVE_RESPONSE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_LIVE_RESPONSE))
#define RYGEL_LIVE_RESPONSE_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_LIVE_RESPONSE, RygelLiveResponseClass))

typedef struct _RygelLiveResponse RygelLiveResponse;
typedef struct _RygelLiveResponseClass RygelLiveResponseClass;
typedef struct _RygelLiveResponsePrivate RygelLiveResponsePrivate;

typedef enum  {
	RYGEL_LIVE_RESPONSE_ERROR_MISSING_PLUGIN,
	RYGEL_LIVE_RESPONSE_ERROR_LINK
} RygelLiveResponseError;
#define RYGEL_LIVE_RESPONSE_ERROR rygel_live_response_error_quark ()
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

struct _RygelLiveResponse {
	RygelHTTPResponse parent_instance;
	RygelLiveResponsePrivate * priv;
};

struct _RygelLiveResponseClass {
	RygelHTTPResponseClass parent_class;
};

struct _RygelLiveResponsePrivate {
	GstPipeline* pipeline;
	GAsyncQueue* buffers;
};



GQuark rygel_live_response_error_quark (void);
GType rygel_state_machine_get_type (void);
GType rygel_http_response_get_type (void);
GType rygel_live_response_get_type (void);
#define RYGEL_LIVE_RESPONSE_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), RYGEL_TYPE_LIVE_RESPONSE, RygelLiveResponsePrivate))
enum  {
	RYGEL_LIVE_RESPONSE_DUMMY_PROPERTY
};
#define RYGEL_LIVE_RESPONSE_SINK_NAME "fakesink"
RygelHTTPResponse* rygel_http_response_new (SoupServer* server, SoupMessage* msg, gboolean partial);
RygelHTTPResponse* rygel_http_response_construct (GType object_type, SoupServer* server, SoupMessage* msg, gboolean partial);
static void rygel_live_response_prepare_pipeline (RygelLiveResponse* self, const char* name, GstElement* src, GError** error);
RygelLiveResponse* rygel_live_response_new (SoupServer* server, SoupMessage* msg, const char* name, GstElement* src, GError** error);
RygelLiveResponse* rygel_live_response_construct (GType object_type, SoupServer* server, SoupMessage* msg, const char* name, GstElement* src, GError** error);
RygelLiveResponse* rygel_live_response_new (SoupServer* server, SoupMessage* msg, const char* name, GstElement* src, GError** error);
void rygel_http_response_run (RygelHTTPResponse* self, GCancellable* cancellable);
static void rygel_live_response_real_run (RygelHTTPResponse* base, GCancellable* cancellable);
void rygel_http_response_end (RygelHTTPResponse* self, gboolean aborted, guint status);
static void rygel_live_response_real_end (RygelHTTPResponse* base, gboolean aborted, guint status);
static inline void _dynamic_set_signal_handoffs1 (GstElement* obj, gboolean value);
static void rygel_live_response_on_new_buffer (RygelLiveResponse* self, GstElement* sink, GstBuffer* buffer, GstPad* pad);
static void _rygel_live_response_on_new_buffer_dynamic_handoff0_ (GstElement* _sender, GstBuffer* buffer, GstPad* pad, gpointer self);
void _dynamic_handoff1_connect (gpointer obj, const char * signal_name, GCallback handler, gpointer data);
static void rygel_live_response_src_pad_added (RygelLiveResponse* self, GstElement* src, GstPad* src_pad);
static void _rygel_live_response_src_pad_added_gst_element_pad_added (GstElement* _sender, GstPad* pad, gpointer self);
static gboolean rygel_live_response_bus_handler (RygelLiveResponse* self, GstBus* bus, GstMessage* message);
static gboolean _rygel_live_response_bus_handler_gst_bus_func (GstBus* bus, GstMessage* message, gpointer self);
static GstElement* rygel_live_response_get_rtp_depayloader (RygelLiveResponse* self, GstCaps* caps);
static gboolean rygel_live_response_need_rtp_depayloader (RygelLiveResponse* self, GstCaps* caps);
static gboolean rygel_live_response_rtp_depay_filter (RygelLiveResponse* self, GstPluginFeature* feature);
static gboolean _rygel_live_response_rtp_depay_filter_gst_plugin_feature_filter (GstPluginFeature* feature, gpointer self);
static GstElement* rygel_live_response_get_best_depay (RygelLiveResponse* self, GList* features, GstCaps* caps);
static void _g_list_free_gst_object_unref (GList* self);
static gint rygel_live_response_compare_factories (void* a, void* b);
static gint _rygel_live_response_compare_factories_gcompare_func (void* a, void* b);
static gboolean rygel_live_response_idle_handler (RygelLiveResponse* self);
static gboolean _rygel_live_response_idle_handler_gsource_func (gpointer self);
void rygel_http_response_push_data (RygelHTTPResponse* self, void* data, gsize length);
static gpointer rygel_live_response_parent_class = NULL;
static void rygel_live_response_finalize (GObject* obj);
static int _vala_strcmp0 (const char * str1, const char * str2);


static void g_cclosure_user_marshal_VOID__POINTER_OBJECT (GClosure * closure, GValue * return_value, guint n_param_values, const GValue * param_values, gpointer invocation_hint, gpointer marshal_data);

GQuark rygel_live_response_error_quark (void) {
	return g_quark_from_static_string ("rygel_live_response_error-quark");
}


RygelLiveResponse* rygel_live_response_construct (GType object_type, SoupServer* server, SoupMessage* msg, const char* name, GstElement* src, GError** error) {
	GError * _inner_error_;
	RygelLiveResponse * self;
	GAsyncQueue* _tmp0_;
	g_return_val_if_fail (server != NULL, NULL);
	g_return_val_if_fail (msg != NULL, NULL);
	g_return_val_if_fail (name != NULL, NULL);
	g_return_val_if_fail (src != NULL, NULL);
	_inner_error_ = NULL;
	self = (RygelLiveResponse*) rygel_http_response_construct (object_type, server, msg, FALSE);
	soup_message_headers_set_encoding (((RygelHTTPResponse*) self)->msg->response_headers, SOUP_ENCODING_EOF);
	_tmp0_ = NULL;
	self->priv->buffers = (_tmp0_ = g_async_queue_new (), (self->priv->buffers == NULL) ? NULL : (self->priv->buffers = (g_async_queue_unref (self->priv->buffers), NULL)), _tmp0_);
	rygel_live_response_prepare_pipeline (self, name, src, &_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		return;
	}
	return self;
}


RygelLiveResponse* rygel_live_response_new (SoupServer* server, SoupMessage* msg, const char* name, GstElement* src, GError** error) {
	return rygel_live_response_construct (RYGEL_TYPE_LIVE_RESPONSE, server, msg, name, src, error);
}


static void rygel_live_response_real_run (RygelHTTPResponse* base, GCancellable* cancellable) {
	RygelLiveResponse * self;
	self = (RygelLiveResponse*) base;
	RYGEL_HTTP_RESPONSE_CLASS (rygel_live_response_parent_class)->run (RYGEL_HTTP_RESPONSE (self), cancellable);
	/* Go to PAUSED first*/
	gst_element_set_state ((GstElement*) self->priv->pipeline, GST_STATE_PLAYING);
}


static void rygel_live_response_real_end (RygelHTTPResponse* base, gboolean aborted, guint status) {
	RygelLiveResponse * self;
	GstBuffer* buffer;
	self = (RygelLiveResponse*) base;
	gst_element_set_state ((GstElement*) self->priv->pipeline, GST_STATE_NULL);
	/* Flush the queue of buffers*/
	buffer = NULL;
	do {
		GstBuffer* _tmp0_;
		_tmp0_ = NULL;
		buffer = (_tmp0_ = (GstBuffer*) g_async_queue_try_pop (self->priv->buffers), (buffer == NULL) ? NULL : (buffer = (gst_buffer_unref (buffer), NULL)), _tmp0_);
	} while (buffer != NULL);
	if (!aborted) {
		soup_message_body_complete (((RygelHTTPResponse*) self)->msg->response_body);
	}
	RYGEL_HTTP_RESPONSE_CLASS (rygel_live_response_parent_class)->end (RYGEL_HTTP_RESPONSE (self), aborted, status);
	(buffer == NULL) ? NULL : (buffer = (gst_buffer_unref (buffer), NULL));
}


static inline void _dynamic_set_signal_handoffs1 (GstElement* obj, gboolean value) {
	g_object_set (obj, "signal-handoffs", value, NULL);
}


static void _rygel_live_response_on_new_buffer_dynamic_handoff0_ (GstElement* _sender, GstBuffer* buffer, GstPad* pad, gpointer self) {
	rygel_live_response_on_new_buffer (self, _sender, buffer, pad);
}


void _dynamic_handoff1_connect (gpointer obj, const char * signal_name, GCallback handler, gpointer data) {
	g_signal_connect_object (obj, signal_name, handler, data, 0);
}


static void _rygel_live_response_src_pad_added_gst_element_pad_added (GstElement* _sender, GstPad* pad, gpointer self) {
	rygel_live_response_src_pad_added (self, _sender, pad);
}


static gboolean _rygel_live_response_bus_handler_gst_bus_func (GstBus* bus, GstMessage* message, gpointer self) {
	return rygel_live_response_bus_handler (self, bus, message);
}


static void rygel_live_response_prepare_pipeline (RygelLiveResponse* self, const char* name, GstElement* src, GError** error) {
	GError * _inner_error_;
	GstElement* sink;
	GstPipeline* _tmp0_;
	GstElement* _tmp2_;
	GstElement* _tmp1_;
	GstBus* bus;
	g_return_if_fail (self != NULL);
	g_return_if_fail (name != NULL);
	g_return_if_fail (src != NULL);
	_inner_error_ = NULL;
	sink = gst_element_factory_make ("fakesink", RYGEL_LIVE_RESPONSE_SINK_NAME);
	if (sink == NULL) {
		_inner_error_ = g_error_new_literal (RYGEL_LIVE_RESPONSE_ERROR, RYGEL_LIVE_RESPONSE_ERROR_MISSING_PLUGIN, "Required plugin 'fakesink' missing");
		if (_inner_error_ != NULL) {
			g_propagate_error (error, _inner_error_);
			(sink == NULL) ? NULL : (sink = (gst_object_unref (sink), NULL));
			return;
		}
	}
	_dynamic_set_signal_handoffs1 (sink, TRUE);
	_dynamic_handoff1_connect (sink, "handoff", (GCallback) _rygel_live_response_on_new_buffer_dynamic_handoff0_, self);
	_tmp0_ = NULL;
	self->priv->pipeline = (_tmp0_ = (GstPipeline*) gst_pipeline_new (name), (self->priv->pipeline == NULL) ? NULL : (self->priv->pipeline = (gst_object_unref (self->priv->pipeline), NULL)), _tmp0_);
	g_assert (self->priv->pipeline != NULL);
	_tmp2_ = NULL;
	_tmp1_ = NULL;
	gst_bin_add_many ((GstBin*) self->priv->pipeline, (_tmp1_ = src, (_tmp1_ == NULL) ? NULL : gst_object_ref (_tmp1_)), (_tmp2_ = sink, (_tmp2_ == NULL) ? NULL : gst_object_ref (_tmp2_)), NULL);
	if (src->numpads == 0) {
		/* Seems source uses dynamic pads, link when pad available*/
		g_signal_connect_object (src, "pad-added", (GCallback) _rygel_live_response_src_pad_added_gst_element_pad_added, self, 0);
	} else {
		/* static pads? easy!*/
		if (!gst_element_link (src, sink)) {
			_inner_error_ = g_error_new (RYGEL_LIVE_RESPONSE_ERROR, RYGEL_LIVE_RESPONSE_ERROR_LINK, "Failed to link %s to %s", gst_object_get_name ((GstObject*) src), gst_object_get_name ((GstObject*) sink));
			if (_inner_error_ != NULL) {
				g_propagate_error (error, _inner_error_);
				(sink == NULL) ? NULL : (sink = (gst_object_unref (sink), NULL));
				return;
			}
		}
	}
	/* Bus handler*/
	bus = gst_pipeline_get_bus (self->priv->pipeline);
	gst_bus_add_watch (bus, _rygel_live_response_bus_handler_gst_bus_func, self);
	(sink == NULL) ? NULL : (sink = (gst_object_unref (sink), NULL));
	(bus == NULL) ? NULL : (bus = (gst_object_unref (bus), NULL));
}


static void rygel_live_response_src_pad_added (RygelLiveResponse* self, GstElement* src, GstPad* src_pad) {
	GstCaps* caps;
	GstElement* sink;
	GstPad* sink_pad;
	GstElement* depay;
	g_return_if_fail (self != NULL);
	g_return_if_fail (src != NULL);
	g_return_if_fail (src_pad != NULL);
	caps = gst_pad_get_caps (src_pad);
	sink = gst_bin_get_by_name ((GstBin*) self->priv->pipeline, RYGEL_LIVE_RESPONSE_SINK_NAME);
	sink_pad = NULL;
	depay = rygel_live_response_get_rtp_depayloader (self, caps);
	if (depay != NULL) {
		GstElement* _tmp0_;
		GstPad* _tmp2_;
		GstPad* _tmp1_;
		_tmp0_ = NULL;
		gst_bin_add ((GstBin*) self->priv->pipeline, (_tmp0_ = depay, (_tmp0_ == NULL) ? NULL : gst_object_ref (_tmp0_)));
		if (!gst_element_link (depay, sink)) {
			g_critical ("rygel-live-response.vala:122: Failed to link %s to %s", gst_object_get_name ((GstObject*) depay), gst_object_get_name ((GstObject*) sink));
			rygel_http_response_end ((RygelHTTPResponse*) self, FALSE, (guint) SOUP_STATUS_NONE);
			(caps == NULL) ? NULL : (caps = (gst_caps_unref (caps), NULL));
			(sink == NULL) ? NULL : (sink = (gst_object_unref (sink), NULL));
			(sink_pad == NULL) ? NULL : (sink_pad = (gst_object_unref (sink_pad), NULL));
			(depay == NULL) ? NULL : (depay = (gst_object_unref (depay), NULL));
			return;
		}
		_tmp2_ = NULL;
		_tmp1_ = NULL;
		sink_pad = (_tmp2_ = (_tmp1_ = gst_element_get_compatible_pad (depay, src_pad, caps), (_tmp1_ == NULL) ? NULL : gst_object_ref (_tmp1_)), (sink_pad == NULL) ? NULL : (sink_pad = (gst_object_unref (sink_pad), NULL)), _tmp2_);
	} else {
		GstPad* _tmp4_;
		GstPad* _tmp3_;
		_tmp4_ = NULL;
		_tmp3_ = NULL;
		sink_pad = (_tmp4_ = (_tmp3_ = gst_element_get_compatible_pad (sink, src_pad, caps), (_tmp3_ == NULL) ? NULL : gst_object_ref (_tmp3_)), (sink_pad == NULL) ? NULL : (sink_pad = (gst_object_unref (sink_pad), NULL)), _tmp4_);
	}
	if (gst_pad_link (src_pad, sink_pad) != GST_PAD_LINK_OK) {
		g_critical ("rygel-live-response.vala:135: Failed to link pad %s to %s", gst_object_get_name ((GstObject*) src_pad), gst_object_get_name ((GstObject*) sink_pad));
		rygel_http_response_end ((RygelHTTPResponse*) self, FALSE, (guint) SOUP_STATUS_NONE);
		(caps == NULL) ? NULL : (caps = (gst_caps_unref (caps), NULL));
		(sink == NULL) ? NULL : (sink = (gst_object_unref (sink), NULL));
		(sink_pad == NULL) ? NULL : (sink_pad = (gst_object_unref (sink_pad), NULL));
		(depay == NULL) ? NULL : (depay = (gst_object_unref (depay), NULL));
		return;
	}
	if (depay != NULL) {
		gst_element_sync_state_with_parent (depay);
	}
	(caps == NULL) ? NULL : (caps = (gst_caps_unref (caps), NULL));
	(sink == NULL) ? NULL : (sink = (gst_object_unref (sink), NULL));
	(sink_pad == NULL) ? NULL : (sink_pad = (gst_object_unref (sink_pad), NULL));
	(depay == NULL) ? NULL : (depay = (gst_object_unref (depay), NULL));
}


static gboolean rygel_live_response_need_rtp_depayloader (RygelLiveResponse* self, GstCaps* caps) {
	const GstStructure* _tmp0_;
	GstStructure* structure;
	gboolean _tmp1_;
	g_return_val_if_fail (self != NULL, FALSE);
	g_return_val_if_fail (caps != NULL, FALSE);
	_tmp0_ = NULL;
	structure = (_tmp0_ = gst_caps_get_structure (caps, (guint) 0), (_tmp0_ == NULL) ? NULL : gst_structure_copy (_tmp0_));
	return (_tmp1_ = _vala_strcmp0 (gst_structure_get_name (structure), "application/x-rtp") == 0, (structure == NULL) ? NULL : (structure = (gst_structure_free (structure), NULL)), _tmp1_);
}


static gboolean _rygel_live_response_rtp_depay_filter_gst_plugin_feature_filter (GstPluginFeature* feature, gpointer self) {
	return rygel_live_response_rtp_depay_filter (self, feature);
}


static void _g_list_free_gst_object_unref (GList* self) {
	g_list_foreach (self, (GFunc) gst_object_unref, NULL);
	g_list_free (self);
}


static GstElement* rygel_live_response_get_rtp_depayloader (RygelLiveResponse* self, GstCaps* caps) {
	GstRegistry* registry;
	GList* features;
	GstElement* _tmp1_;
	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (caps != NULL, NULL);
	if (!rygel_live_response_need_rtp_depayloader (self, caps)) {
		return NULL;
	}
	registry = gst_registry_get_default ();
	features = gst_registry_feature_filter (registry, _rygel_live_response_rtp_depay_filter_gst_plugin_feature_filter, FALSE, self);
	_tmp1_ = NULL;
	return (_tmp1_ = rygel_live_response_get_best_depay (self, features, caps), (features == NULL) ? NULL : (features = (_g_list_free_gst_object_unref (features), NULL)), _tmp1_);
}


static gint _rygel_live_response_compare_factories_gcompare_func (void* a, void* b) {
	return rygel_live_response_compare_factories (a, b);
}


static GstElement* rygel_live_response_get_best_depay (RygelLiveResponse* self, GList* features, GstCaps* caps) {
	GList* relevant_factories;
	GstElementFactory* _tmp4_;
	GstElementFactory* factory;
	GstElement* _tmp5_;
	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (caps != NULL, NULL);
	relevant_factories = NULL;
	/* First construct a list of relevant factories*/
	{
		GList* feature_collection;
		GList* feature_it;
		feature_collection = features;
		for (feature_it = feature_collection; feature_it != NULL; feature_it = feature_it->next) {
			GstPluginFeature* _tmp2_;
			GstPluginFeature* feature;
			_tmp2_ = NULL;
			feature = (_tmp2_ = (GstPluginFeature*) feature_it->data, (_tmp2_ == NULL) ? NULL : gst_object_ref (_tmp2_));
			{
				GstElementFactory* _tmp0_;
				GstElementFactory* factory;
				_tmp0_ = NULL;
				factory = (_tmp0_ = GST_ELEMENT_FACTORY (feature), (_tmp0_ == NULL) ? NULL : gst_object_ref (_tmp0_));
				if (gst_element_factory_can_sink_caps (factory, caps)) {
					GstElementFactory* _tmp1_;
					_tmp1_ = NULL;
					relevant_factories = g_list_append (relevant_factories, (_tmp1_ = factory, (_tmp1_ == NULL) ? NULL : gst_object_ref (_tmp1_)));
				}
				(feature == NULL) ? NULL : (feature = (gst_object_unref (feature), NULL));
				(factory == NULL) ? NULL : (factory = (gst_object_unref (factory), NULL));
			}
		}
	}
	if (g_list_length (relevant_factories) == 0) {
		GstElement* _tmp3_;
		/* No relevant factory available, hence no depayloader*/
		_tmp3_ = NULL;
		return (_tmp3_ = NULL, (relevant_factories == NULL) ? NULL : (relevant_factories = (_g_list_free_gst_object_unref (relevant_factories), NULL)), _tmp3_);
	}
	/* Then sort the list through their ranks*/
	relevant_factories = g_list_sort (relevant_factories, _rygel_live_response_compare_factories_gcompare_func);
	/* create an element of the top ranking factory and return it*/
	_tmp4_ = NULL;
	factory = (_tmp4_ = (GstElementFactory*) relevant_factories->data, (_tmp4_ == NULL) ? NULL : gst_object_ref (_tmp4_));
	_tmp5_ = NULL;
	return (_tmp5_ = gst_element_factory_make (gst_plugin_feature_get_name ((GstPluginFeature*) factory), NULL), (relevant_factories == NULL) ? NULL : (relevant_factories = (_g_list_free_gst_object_unref (relevant_factories), NULL)), (factory == NULL) ? NULL : (factory = (gst_object_unref (factory), NULL)), _tmp5_);
}


static gboolean string_contains (const char* self, const char* needle) {
	g_return_val_if_fail (self != NULL, FALSE);
	g_return_val_if_fail (needle != NULL, FALSE);
	return strstr (self, needle) != NULL;
}


static gboolean rygel_live_response_rtp_depay_filter (RygelLiveResponse* self, GstPluginFeature* feature) {
	GstElementFactory* _tmp1_;
	GstElementFactory* factory;
	gboolean _tmp2_;
	g_return_val_if_fail (self != NULL, FALSE);
	g_return_val_if_fail (feature != NULL, FALSE);
	if (!g_type_is_a (G_TYPE_FROM_INSTANCE ((GObject*) feature), GST_TYPE_ELEMENT_FACTORY)) {
		return FALSE;
	}
	_tmp1_ = NULL;
	factory = (_tmp1_ = GST_ELEMENT_FACTORY (feature), (_tmp1_ == NULL) ? NULL : gst_object_ref (_tmp1_));
	return (_tmp2_ = string_contains (gst_element_factory_get_klass (factory), "Depayloader"), (factory == NULL) ? NULL : (factory = (gst_object_unref (factory), NULL)), _tmp2_);
}


static gint rygel_live_response_compare_factories (void* a, void* b) {
	GstElementFactory* _tmp0_;
	GstElementFactory* factory_a;
	GstElementFactory* _tmp1_;
	GstElementFactory* factory_b;
	gint _tmp2_;
	_tmp0_ = NULL;
	factory_a = (_tmp0_ = GST_ELEMENT_FACTORY (a), (_tmp0_ == NULL) ? NULL : gst_object_ref (_tmp0_));
	_tmp1_ = NULL;
	factory_b = (_tmp1_ = GST_ELEMENT_FACTORY (b), (_tmp1_ == NULL) ? NULL : gst_object_ref (_tmp1_));
	return (_tmp2_ = (gint) (gst_plugin_feature_get_rank ((GstPluginFeature*) factory_b) - gst_plugin_feature_get_rank ((GstPluginFeature*) factory_a)), (factory_a == NULL) ? NULL : (factory_a = (gst_object_unref (factory_a), NULL)), (factory_b == NULL) ? NULL : (factory_b = (gst_object_unref (factory_b), NULL)), _tmp2_);
}


static gboolean _rygel_live_response_idle_handler_gsource_func (gpointer self) {
	return rygel_live_response_idle_handler (self);
}


static void rygel_live_response_on_new_buffer (RygelLiveResponse* self, GstElement* sink, GstBuffer* buffer, GstPad* pad) {
	GstBuffer* _tmp0_;
	g_return_if_fail (self != NULL);
	g_return_if_fail (sink != NULL);
	g_return_if_fail (buffer != NULL);
	g_return_if_fail (pad != NULL);
	_tmp0_ = NULL;
	g_async_queue_push (self->priv->buffers, (_tmp0_ = buffer, (_tmp0_ == NULL) ? NULL : gst_buffer_ref (_tmp0_)));
	g_idle_add_full (G_PRIORITY_HIGH_IDLE, _rygel_live_response_idle_handler_gsource_func, g_object_ref (self), g_object_unref);
}


static gboolean rygel_live_response_idle_handler (RygelLiveResponse* self) {
	GstBuffer* buffer;
	gboolean _tmp0_;
	g_return_val_if_fail (self != NULL, FALSE);
	buffer = (GstBuffer*) g_async_queue_try_pop (self->priv->buffers);
	if (buffer != NULL) {
		rygel_http_response_push_data ((RygelHTTPResponse*) self, buffer->data, (gsize) buffer->size);
	}
	return (_tmp0_ = FALSE, (buffer == NULL) ? NULL : (buffer = (gst_buffer_unref (buffer), NULL)), _tmp0_);
}


static gboolean rygel_live_response_bus_handler (RygelLiveResponse* self, GstBus* bus, GstMessage* message) {
	gboolean ret;
	g_return_val_if_fail (self != NULL, FALSE);
	g_return_val_if_fail (bus != NULL, FALSE);
	g_return_val_if_fail (message != NULL, FALSE);
	ret = TRUE;
	if (message->type == GST_MESSAGE_EOS) {
		ret = FALSE;
	} else {
		GError* err;
		char* err_msg;
		err = NULL;
		err_msg = NULL;
		if (message->type == GST_MESSAGE_ERROR) {
			char* _tmp3_;
			char* _tmp2_;
			GError* _tmp1_;
			GError* _tmp0_;
			_tmp3_ = NULL;
			_tmp2_ = NULL;
			_tmp1_ = NULL;
			_tmp0_ = NULL;
			(gst_message_parse_error (message, &_tmp0_, &_tmp2_), err = (_tmp1_ = _tmp0_, (err == NULL) ? NULL : (err = (g_error_free (err), NULL)), _tmp1_));
			err_msg = (_tmp3_ = _tmp2_, err_msg = (g_free (err_msg), NULL), _tmp3_);
			g_critical ("rygel-live-response.vala:235: Error from pipeline %s:%s", gst_object_get_name ((GstObject*) self->priv->pipeline), err_msg);
			ret = FALSE;
		} else {
			if (message->type == GST_MESSAGE_WARNING) {
				char* _tmp7_;
				char* _tmp6_;
				GError* _tmp5_;
				GError* _tmp4_;
				_tmp7_ = NULL;
				_tmp6_ = NULL;
				_tmp5_ = NULL;
				_tmp4_ = NULL;
				(gst_message_parse_warning (message, &_tmp4_, &_tmp6_), err = (_tmp5_ = _tmp4_, (err == NULL) ? NULL : (err = (g_error_free (err), NULL)), _tmp5_));
				err_msg = (_tmp7_ = _tmp6_, err_msg = (g_free (err_msg), NULL), _tmp7_);
				g_warning ("rygel-live-response.vala:242: Warning from pipeline %s:%s", gst_object_get_name ((GstObject*) self->priv->pipeline), err_msg);
			}
		}
		(err == NULL) ? NULL : (err = (g_error_free (err), NULL));
		err_msg = (g_free (err_msg), NULL);
	}
	if (!ret) {
		rygel_http_response_end ((RygelHTTPResponse*) self, FALSE, (guint) SOUP_STATUS_NONE);
	}
	return ret;
}


static void rygel_live_response_class_init (RygelLiveResponseClass * klass) {
	rygel_live_response_parent_class = g_type_class_peek_parent (klass);
	g_type_class_add_private (klass, sizeof (RygelLiveResponsePrivate));
	RYGEL_HTTP_RESPONSE_CLASS (klass)->run = rygel_live_response_real_run;
	RYGEL_HTTP_RESPONSE_CLASS (klass)->end = rygel_live_response_real_end;
	G_OBJECT_CLASS (klass)->finalize = rygel_live_response_finalize;
}


static void rygel_live_response_instance_init (RygelLiveResponse * self) {
	self->priv = RYGEL_LIVE_RESPONSE_GET_PRIVATE (self);
}


static void rygel_live_response_finalize (GObject* obj) {
	RygelLiveResponse * self;
	self = RYGEL_LIVE_RESPONSE (obj);
	(self->priv->pipeline == NULL) ? NULL : (self->priv->pipeline = (gst_object_unref (self->priv->pipeline), NULL));
	(self->priv->buffers == NULL) ? NULL : (self->priv->buffers = (g_async_queue_unref (self->priv->buffers), NULL));
	G_OBJECT_CLASS (rygel_live_response_parent_class)->finalize (obj);
}


GType rygel_live_response_get_type (void) {
	static GType rygel_live_response_type_id = 0;
	if (rygel_live_response_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (RygelLiveResponseClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) rygel_live_response_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (RygelLiveResponse), 0, (GInstanceInitFunc) rygel_live_response_instance_init, NULL };
		rygel_live_response_type_id = g_type_register_static (RYGEL_TYPE_HTTP_RESPONSE, "RygelLiveResponse", &g_define_type_info, 0);
	}
	return rygel_live_response_type_id;
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



static void g_cclosure_user_marshal_VOID__POINTER_OBJECT (GClosure * closure, GValue * return_value, guint n_param_values, const GValue * param_values, gpointer invocation_hint, gpointer marshal_data) {
	typedef void (*GMarshalFunc_VOID__POINTER_OBJECT) (gpointer data1, gpointer arg_1, gpointer arg_2, gpointer data2);
	register GMarshalFunc_VOID__POINTER_OBJECT callback;
	register GCClosure * cc;
	register gpointer data1, data2;
	cc = (GCClosure *) closure;
	g_return_if_fail (n_param_values == 3);
	if (G_CCLOSURE_SWAP_DATA (closure)) {
		data1 = closure->data;
		data2 = param_values->data[0].v_pointer;
	} else {
		data1 = param_values->data[0].v_pointer;
		data2 = closure->data;
	}
	callback = (GMarshalFunc_VOID__POINTER_OBJECT) (marshal_data ? marshal_data : cc->callback);
	callback (data1, gst_value_get_mini_object (param_values + 1), g_value_get_object (param_values + 2), data2);
}



