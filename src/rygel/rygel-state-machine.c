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
#include <gio/gio.h>


#define RYGEL_TYPE_STATE_MACHINE (rygel_state_machine_get_type ())
#define RYGEL_STATE_MACHINE(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_STATE_MACHINE, RygelStateMachine))
#define RYGEL_IS_STATE_MACHINE(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_STATE_MACHINE))
#define RYGEL_STATE_MACHINE_GET_INTERFACE(obj) (G_TYPE_INSTANCE_GET_INTERFACE ((obj), RYGEL_TYPE_STATE_MACHINE, RygelStateMachineIface))

typedef struct _RygelStateMachine RygelStateMachine;
typedef struct _RygelStateMachineIface RygelStateMachineIface;

/**
 * StateMachine interface.
 */
struct _RygelStateMachineIface {
	GTypeInterface parent_iface;
	void (*run) (RygelStateMachine* self, GCancellable* cancellable);
};



GType rygel_state_machine_get_type (void);
void rygel_state_machine_run (RygelStateMachine* self, GCancellable* cancellable);



void rygel_state_machine_run (RygelStateMachine* self, GCancellable* cancellable) {
	RYGEL_STATE_MACHINE_GET_INTERFACE (self)->run (self, cancellable);
}


static void rygel_state_machine_base_init (RygelStateMachineIface * iface) {
	static gboolean initialized = FALSE;
	if (!initialized) {
		initialized = TRUE;
		g_signal_new ("completed", RYGEL_TYPE_STATE_MACHINE, G_SIGNAL_RUN_LAST, 0, NULL, NULL, g_cclosure_marshal_VOID__VOID, G_TYPE_NONE, 0);
	}
}


GType rygel_state_machine_get_type (void) {
	static GType rygel_state_machine_type_id = 0;
	if (rygel_state_machine_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (RygelStateMachineIface), (GBaseInitFunc) rygel_state_machine_base_init, (GBaseFinalizeFunc) NULL, (GClassInitFunc) NULL, (GClassFinalizeFunc) NULL, NULL, 0, 0, (GInstanceInitFunc) NULL, NULL };
		rygel_state_machine_type_id = g_type_register_static (G_TYPE_INTERFACE, "RygelStateMachine", &g_define_type_info, 0);
		g_type_interface_add_prerequisite (rygel_state_machine_type_id, G_TYPE_OBJECT);
	}
	return rygel_state_machine_type_id;
}




