/*
 * Copyright (C) 2008 OpenedHand Ltd.
 * Copyright (C) 2008 Zeeshan Ali <zeenix@gmail.com>.
 *
 * Author: Jorn Baayen <jorn@openedhand.com>
 *         Zeeshan Ali <zeenix@gmail.com>
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
#include <libgupnp/gupnp.h>
#include <stdlib.h>
#include <string.h>


#define RYGEL_TYPE_CONNECTION_MANAGER (rygel_connection_manager_get_type ())
#define RYGEL_CONNECTION_MANAGER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_CONNECTION_MANAGER, RygelConnectionManager))
#define RYGEL_CONNECTION_MANAGER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_CONNECTION_MANAGER, RygelConnectionManagerClass))
#define RYGEL_IS_CONNECTION_MANAGER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_CONNECTION_MANAGER))
#define RYGEL_IS_CONNECTION_MANAGER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_CONNECTION_MANAGER))
#define RYGEL_CONNECTION_MANAGER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_CONNECTION_MANAGER, RygelConnectionManagerClass))

typedef struct _RygelConnectionManager RygelConnectionManager;
typedef struct _RygelConnectionManagerClass RygelConnectionManagerClass;
typedef struct _RygelConnectionManagerPrivate RygelConnectionManagerPrivate;

/**
 * Basic implementation of UPnP ConnectionManager service version 2.
 */
struct _RygelConnectionManager {
	GUPnPService parent_instance;
	RygelConnectionManagerPrivate * priv;
	char* source_protocol_info;
	char* sink_protocol_info;
	char* connection_ids;
};

struct _RygelConnectionManagerClass {
	GUPnPServiceClass parent_class;
};



GType rygel_connection_manager_get_type (void);
enum  {
	RYGEL_CONNECTION_MANAGER_DUMMY_PROPERTY
};
#define RYGEL_CONNECTION_MANAGER_UPNP_ID "urn:upnp-org:serviceId:ConnectionManager"
#define RYGEL_CONNECTION_MANAGER_UPNP_TYPE "urn:schemas-upnp-org:service:ConnectionManager:2"
#define RYGEL_CONNECTION_MANAGER_DESCRIPTION_PATH "xml/ConnectionManager.xml"
static void rygel_connection_manager_query_source_protocol_info_cb (RygelConnectionManager* self, RygelConnectionManager* cm, const char* var, GValue* val);
static void _rygel_connection_manager_query_source_protocol_info_cb_gupnp_service_query_variable (RygelConnectionManager* _sender, const char* variable, GValue* value, gpointer self);
static void rygel_connection_manager_query_sink_protocol_info_cb (RygelConnectionManager* self, RygelConnectionManager* cm, const char* var, GValue* val);
static void _rygel_connection_manager_query_sink_protocol_info_cb_gupnp_service_query_variable (RygelConnectionManager* _sender, const char* variable, GValue* value, gpointer self);
static void rygel_connection_manager_query_current_connection_ids_cb (RygelConnectionManager* self, RygelConnectionManager* cm, const char* var, GValue* val);
static void _rygel_connection_manager_query_current_connection_ids_cb_gupnp_service_query_variable (RygelConnectionManager* _sender, const char* variable, GValue* value, gpointer self);
static void rygel_connection_manager_get_protocol_info_cb (RygelConnectionManager* self, RygelConnectionManager* cm, GUPnPServiceAction* action);
static void _rygel_connection_manager_get_protocol_info_cb_gupnp_service_action_invoked (RygelConnectionManager* _sender, GUPnPServiceAction* action, gpointer self);
static void rygel_connection_manager_get_current_connection_ids_cb (RygelConnectionManager* self, RygelConnectionManager* cm, GUPnPServiceAction* action);
static void _rygel_connection_manager_get_current_connection_ids_cb_gupnp_service_action_invoked (RygelConnectionManager* _sender, GUPnPServiceAction* action, gpointer self);
static void rygel_connection_manager_get_current_connection_info_cb (RygelConnectionManager* self, RygelConnectionManager* cm, GUPnPServiceAction* action);
static void _rygel_connection_manager_get_current_connection_info_cb_gupnp_service_action_invoked (RygelConnectionManager* _sender, GUPnPServiceAction* action, gpointer self);
static void rygel_connection_manager_real_constructed (GObject* base);
RygelConnectionManager* rygel_connection_manager_new (void);
RygelConnectionManager* rygel_connection_manager_construct (GType object_type);
RygelConnectionManager* rygel_connection_manager_new (void);
static gpointer rygel_connection_manager_parent_class = NULL;
static void rygel_connection_manager_finalize (GObject* obj);



static void _rygel_connection_manager_query_source_protocol_info_cb_gupnp_service_query_variable (RygelConnectionManager* _sender, const char* variable, GValue* value, gpointer self) {
	rygel_connection_manager_query_source_protocol_info_cb (self, _sender, variable, value);
}


static void _rygel_connection_manager_query_sink_protocol_info_cb_gupnp_service_query_variable (RygelConnectionManager* _sender, const char* variable, GValue* value, gpointer self) {
	rygel_connection_manager_query_sink_protocol_info_cb (self, _sender, variable, value);
}


static void _rygel_connection_manager_query_current_connection_ids_cb_gupnp_service_query_variable (RygelConnectionManager* _sender, const char* variable, GValue* value, gpointer self) {
	rygel_connection_manager_query_current_connection_ids_cb (self, _sender, variable, value);
}


static void _rygel_connection_manager_get_protocol_info_cb_gupnp_service_action_invoked (RygelConnectionManager* _sender, GUPnPServiceAction* action, gpointer self) {
	rygel_connection_manager_get_protocol_info_cb (self, _sender, action);
}


static void _rygel_connection_manager_get_current_connection_ids_cb_gupnp_service_action_invoked (RygelConnectionManager* _sender, GUPnPServiceAction* action, gpointer self) {
	rygel_connection_manager_get_current_connection_ids_cb (self, _sender, action);
}


static void _rygel_connection_manager_get_current_connection_info_cb_gupnp_service_action_invoked (RygelConnectionManager* _sender, GUPnPServiceAction* action, gpointer self) {
	rygel_connection_manager_get_current_connection_info_cb (self, _sender, action);
}


static void rygel_connection_manager_real_constructed (GObject* base) {
	RygelConnectionManager * self;
	char* _tmp0_;
	char* _tmp1_;
	char* _tmp2_;
	self = (RygelConnectionManager*) base;
	_tmp0_ = NULL;
	self->sink_protocol_info = (_tmp0_ = g_strdup (""), self->sink_protocol_info = (g_free (self->sink_protocol_info), NULL), _tmp0_);
	_tmp1_ = NULL;
	self->connection_ids = (_tmp1_ = g_strdup ("0"), self->connection_ids = (g_free (self->connection_ids), NULL), _tmp1_);
	_tmp2_ = NULL;
	self->source_protocol_info = (_tmp2_ = g_strdup ("http-get:*:*:*"), self->source_protocol_info = (g_free (self->source_protocol_info), NULL), _tmp2_);
	g_signal_connect_object ((GUPnPService*) self, "query-variable::SourceProtocolInfo", (GCallback) _rygel_connection_manager_query_source_protocol_info_cb_gupnp_service_query_variable, self, 0);
	g_signal_connect_object ((GUPnPService*) self, "query-variable::SinkProtocolInfo", (GCallback) _rygel_connection_manager_query_sink_protocol_info_cb_gupnp_service_query_variable, self, 0);
	g_signal_connect_object ((GUPnPService*) self, "query-variable::CurrentConnectionIDs", (GCallback) _rygel_connection_manager_query_current_connection_ids_cb_gupnp_service_query_variable, self, 0);
	g_signal_connect_object ((GUPnPService*) self, "action-invoked::GetProtocolInfo", (GCallback) _rygel_connection_manager_get_protocol_info_cb_gupnp_service_action_invoked, self, 0);
	g_signal_connect_object ((GUPnPService*) self, "action-invoked::GetCurrentConnectionIDs", (GCallback) _rygel_connection_manager_get_current_connection_ids_cb_gupnp_service_action_invoked, self, 0);
	g_signal_connect_object ((GUPnPService*) self, "action-invoked::GetCurrentConnectionInfo", (GCallback) _rygel_connection_manager_get_current_connection_info_cb_gupnp_service_action_invoked, self, 0);
}


static void rygel_connection_manager_query_source_protocol_info_cb (RygelConnectionManager* self, RygelConnectionManager* cm, const char* var, GValue* val) {
	g_return_if_fail (self != NULL);
	g_return_if_fail (cm != NULL);
	g_return_if_fail (var != NULL);
	g_value_init (&(*val), G_TYPE_STRING);
	g_value_set_string (&(*val), self->source_protocol_info);
}


static void rygel_connection_manager_query_sink_protocol_info_cb (RygelConnectionManager* self, RygelConnectionManager* cm, const char* var, GValue* val) {
	g_return_if_fail (self != NULL);
	g_return_if_fail (cm != NULL);
	g_return_if_fail (var != NULL);
	g_value_init (&(*val), G_TYPE_STRING);
	g_value_set_string (&(*val), self->sink_protocol_info);
}


static void rygel_connection_manager_query_current_connection_ids_cb (RygelConnectionManager* self, RygelConnectionManager* cm, const char* var, GValue* val) {
	g_return_if_fail (self != NULL);
	g_return_if_fail (cm != NULL);
	g_return_if_fail (var != NULL);
	g_value_init (&(*val), G_TYPE_STRING);
	g_value_set_string (&(*val), self->connection_ids);
}


static void rygel_connection_manager_get_protocol_info_cb (RygelConnectionManager* self, RygelConnectionManager* cm, GUPnPServiceAction* action) {
	g_return_if_fail (self != NULL);
	g_return_if_fail (cm != NULL);
	g_return_if_fail (action != NULL);
	gupnp_service_action_set (action, "Source", G_TYPE_STRING, self->source_protocol_info, "Sink", G_TYPE_STRING, self->sink_protocol_info, NULL);
	gupnp_service_action_return (action);
}


static void rygel_connection_manager_get_current_connection_ids_cb (RygelConnectionManager* self, RygelConnectionManager* cm, GUPnPServiceAction* action) {
	g_return_if_fail (self != NULL);
	g_return_if_fail (cm != NULL);
	g_return_if_fail (action != NULL);
	gupnp_service_action_set (action, "ConnectionIDs", G_TYPE_STRING, self->connection_ids, NULL);
	gupnp_service_action_return (action);
}


static void rygel_connection_manager_get_current_connection_info_cb (RygelConnectionManager* self, RygelConnectionManager* cm, GUPnPServiceAction* action) {
	gint connection_id;
	g_return_if_fail (self != NULL);
	g_return_if_fail (cm != NULL);
	g_return_if_fail (action != NULL);
	connection_id = 0;
	gupnp_service_action_get (action, "ConnectionID", G_TYPE_INT, &connection_id, NULL);
	if (connection_id != 0) {
		gupnp_service_action_return_error (action, (guint) 706, "Invalid connection reference");
		return;
	}
	gupnp_service_action_set (action, "ResID", G_TYPE_INT, -1, "AVTransportID", G_TYPE_INT, -1, "ProtocolInfo", G_TYPE_STRING, "", "PeerConnectionManager", G_TYPE_STRING, "", "PeerConnectionID", G_TYPE_INT, -1, "Direction", G_TYPE_STRING, "Input", "Status", G_TYPE_STRING, "Unknown", NULL);
	gupnp_service_action_return (action);
}


/**
 * Basic implementation of UPnP ConnectionManager service version 2.
 */
RygelConnectionManager* rygel_connection_manager_construct (GType object_type) {
	RygelConnectionManager * self;
	self = g_object_newv (object_type, 0, NULL);
	return self;
}


RygelConnectionManager* rygel_connection_manager_new (void) {
	return rygel_connection_manager_construct (RYGEL_TYPE_CONNECTION_MANAGER);
}


static void rygel_connection_manager_class_init (RygelConnectionManagerClass * klass) {
	rygel_connection_manager_parent_class = g_type_class_peek_parent (klass);
	G_OBJECT_CLASS (klass)->constructed = rygel_connection_manager_real_constructed;
	G_OBJECT_CLASS (klass)->finalize = rygel_connection_manager_finalize;
}


static void rygel_connection_manager_instance_init (RygelConnectionManager * self) {
}


static void rygel_connection_manager_finalize (GObject* obj) {
	RygelConnectionManager * self;
	self = RYGEL_CONNECTION_MANAGER (obj);
	self->source_protocol_info = (g_free (self->source_protocol_info), NULL);
	self->sink_protocol_info = (g_free (self->sink_protocol_info), NULL);
	self->connection_ids = (g_free (self->connection_ids), NULL);
	G_OBJECT_CLASS (rygel_connection_manager_parent_class)->finalize (obj);
}


GType rygel_connection_manager_get_type (void) {
	static GType rygel_connection_manager_type_id = 0;
	if (rygel_connection_manager_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (RygelConnectionManagerClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) rygel_connection_manager_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (RygelConnectionManager), 0, (GInstanceInitFunc) rygel_connection_manager_instance_init, NULL };
		rygel_connection_manager_type_id = g_type_register_static (GUPNP_TYPE_SERVICE, "RygelConnectionManager", &g_define_type_info, 0);
	}
	return rygel_connection_manager_type_id;
}




