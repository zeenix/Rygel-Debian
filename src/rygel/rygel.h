
#ifndef __RYGEL_H__
#define __RYGEL_H__

#include <glib.h>
#include <glib-object.h>
#include <gconf/gconf-client.h>
#include <stdlib.h>
#include <string.h>
#include <gee/arraylist.h>
#include <libgupnp/gupnp.h>
#include <gio/gio.h>
#include <gee/collection.h>
#include <gee/list.h>
#include <gst/gst.h>

G_BEGIN_DECLS


#define RYGEL_TYPE_CONFIGURATION (rygel_configuration_get_type ())
#define RYGEL_CONFIGURATION(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_CONFIGURATION, RygelConfiguration))
#define RYGEL_CONFIGURATION_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_CONFIGURATION, RygelConfigurationClass))
#define RYGEL_IS_CONFIGURATION(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_CONFIGURATION))
#define RYGEL_IS_CONFIGURATION_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_CONFIGURATION))
#define RYGEL_CONFIGURATION_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_CONFIGURATION, RygelConfigurationClass))

typedef struct _RygelConfiguration RygelConfiguration;
typedef struct _RygelConfigurationClass RygelConfigurationClass;
typedef struct _RygelConfigurationPrivate RygelConfigurationPrivate;

#define RYGEL_TYPE_CONTENT_DIRECTORY (rygel_content_directory_get_type ())
#define RYGEL_CONTENT_DIRECTORY(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_CONTENT_DIRECTORY, RygelContentDirectory))
#define RYGEL_CONTENT_DIRECTORY_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_CONTENT_DIRECTORY, RygelContentDirectoryClass))
#define RYGEL_IS_CONTENT_DIRECTORY(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_CONTENT_DIRECTORY))
#define RYGEL_IS_CONTENT_DIRECTORY_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_CONTENT_DIRECTORY))
#define RYGEL_CONTENT_DIRECTORY_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_CONTENT_DIRECTORY, RygelContentDirectoryClass))

typedef struct _RygelContentDirectory RygelContentDirectory;
typedef struct _RygelContentDirectoryClass RygelContentDirectoryClass;
typedef struct _RygelContentDirectoryPrivate RygelContentDirectoryPrivate;

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

#define RYGEL_TYPE_CONNECTION_MANAGER (rygel_connection_manager_get_type ())
#define RYGEL_CONNECTION_MANAGER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_CONNECTION_MANAGER, RygelConnectionManager))
#define RYGEL_CONNECTION_MANAGER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_CONNECTION_MANAGER, RygelConnectionManagerClass))
#define RYGEL_IS_CONNECTION_MANAGER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_CONNECTION_MANAGER))
#define RYGEL_IS_CONNECTION_MANAGER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_CONNECTION_MANAGER))
#define RYGEL_CONNECTION_MANAGER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_CONNECTION_MANAGER, RygelConnectionManagerClass))

typedef struct _RygelConnectionManager RygelConnectionManager;
typedef struct _RygelConnectionManagerClass RygelConnectionManagerClass;
typedef struct _RygelConnectionManagerPrivate RygelConnectionManagerPrivate;

#define RYGEL_TYPE_STATE_MACHINE (rygel_state_machine_get_type ())
#define RYGEL_STATE_MACHINE(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_STATE_MACHINE, RygelStateMachine))
#define RYGEL_IS_STATE_MACHINE(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_STATE_MACHINE))
#define RYGEL_STATE_MACHINE_GET_INTERFACE(obj) (G_TYPE_INSTANCE_GET_INTERFACE ((obj), RYGEL_TYPE_STATE_MACHINE, RygelStateMachineIface))

typedef struct _RygelStateMachine RygelStateMachine;
typedef struct _RygelStateMachineIface RygelStateMachineIface;

#define RYGEL_TYPE_RESOURCE_INFO (rygel_resource_info_get_type ())
#define RYGEL_RESOURCE_INFO(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_RESOURCE_INFO, RygelResourceInfo))
#define RYGEL_RESOURCE_INFO_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_RESOURCE_INFO, RygelResourceInfoClass))
#define RYGEL_IS_RESOURCE_INFO(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_RESOURCE_INFO))
#define RYGEL_IS_RESOURCE_INFO_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_RESOURCE_INFO))
#define RYGEL_RESOURCE_INFO_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_RESOURCE_INFO, RygelResourceInfoClass))

typedef struct _RygelResourceInfo RygelResourceInfo;
typedef struct _RygelResourceInfoClass RygelResourceInfoClass;
typedef struct _RygelResourceInfoPrivate RygelResourceInfoPrivate;

#define RYGEL_TYPE_ICON_INFO (rygel_icon_info_get_type ())
#define RYGEL_ICON_INFO(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_ICON_INFO, RygelIconInfo))
#define RYGEL_ICON_INFO_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_ICON_INFO, RygelIconInfoClass))
#define RYGEL_IS_ICON_INFO(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_ICON_INFO))
#define RYGEL_IS_ICON_INFO_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_ICON_INFO))
#define RYGEL_ICON_INFO_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_ICON_INFO, RygelIconInfoClass))

typedef struct _RygelIconInfo RygelIconInfo;
typedef struct _RygelIconInfoClass RygelIconInfoClass;
typedef struct _RygelIconInfoPrivate RygelIconInfoPrivate;

#define RYGEL_TYPE_PLUGIN (rygel_plugin_get_type ())
#define RYGEL_PLUGIN(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_PLUGIN, RygelPlugin))
#define RYGEL_PLUGIN_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_PLUGIN, RygelPluginClass))
#define RYGEL_IS_PLUGIN(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_PLUGIN))
#define RYGEL_IS_PLUGIN_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_PLUGIN))
#define RYGEL_PLUGIN_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_PLUGIN, RygelPluginClass))

typedef struct _RygelPlugin RygelPlugin;
typedef struct _RygelPluginClass RygelPluginClass;
typedef struct _RygelPluginPrivate RygelPluginPrivate;

#define RYGEL_TYPE_PLUGIN_LOADER (rygel_plugin_loader_get_type ())
#define RYGEL_PLUGIN_LOADER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_PLUGIN_LOADER, RygelPluginLoader))
#define RYGEL_PLUGIN_LOADER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_PLUGIN_LOADER, RygelPluginLoaderClass))
#define RYGEL_IS_PLUGIN_LOADER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_PLUGIN_LOADER))
#define RYGEL_IS_PLUGIN_LOADER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_PLUGIN_LOADER))
#define RYGEL_PLUGIN_LOADER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_PLUGIN_LOADER, RygelPluginLoaderClass))

typedef struct _RygelPluginLoader RygelPluginLoader;
typedef struct _RygelPluginLoaderClass RygelPluginLoaderClass;
typedef struct _RygelPluginLoaderPrivate RygelPluginLoaderPrivate;
typedef struct _RygelMediaObjectPrivate RygelMediaObjectPrivate;
typedef struct _RygelMediaContainerPrivate RygelMediaContainerPrivate;

#define RYGEL_TYPE_SIMPLE_ASYNC_RESULT (rygel_simple_async_result_get_type ())
#define RYGEL_SIMPLE_ASYNC_RESULT(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_SIMPLE_ASYNC_RESULT, RygelSimpleAsyncResult))
#define RYGEL_SIMPLE_ASYNC_RESULT_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_SIMPLE_ASYNC_RESULT, RygelSimpleAsyncResultClass))
#define RYGEL_IS_SIMPLE_ASYNC_RESULT(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_SIMPLE_ASYNC_RESULT))
#define RYGEL_IS_SIMPLE_ASYNC_RESULT_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_SIMPLE_ASYNC_RESULT))
#define RYGEL_SIMPLE_ASYNC_RESULT_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_SIMPLE_ASYNC_RESULT, RygelSimpleAsyncResultClass))

typedef struct _RygelSimpleAsyncResult RygelSimpleAsyncResult;
typedef struct _RygelSimpleAsyncResultClass RygelSimpleAsyncResultClass;
typedef struct _RygelSimpleAsyncResultPrivate RygelSimpleAsyncResultPrivate;

#define RYGEL_TYPE_MEDIA_ITEM (rygel_media_item_get_type ())
#define RYGEL_MEDIA_ITEM(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_MEDIA_ITEM, RygelMediaItem))
#define RYGEL_MEDIA_ITEM_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_MEDIA_ITEM, RygelMediaItemClass))
#define RYGEL_IS_MEDIA_ITEM(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_MEDIA_ITEM))
#define RYGEL_IS_MEDIA_ITEM_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_MEDIA_ITEM))
#define RYGEL_MEDIA_ITEM_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_MEDIA_ITEM, RygelMediaItemClass))

typedef struct _RygelMediaItem RygelMediaItem;
typedef struct _RygelMediaItemClass RygelMediaItemClass;
typedef struct _RygelMediaItemPrivate RygelMediaItemPrivate;

/**
 * Reads the user configuration for Rygel.
 */
struct _RygelConfiguration {
	GObject parent_instance;
	RygelConfigurationPrivate * priv;
	GConfClient* gconf;
};

struct _RygelConfigurationClass {
	GObjectClass parent_class;
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

/**
 * StateMachine interface.
 */
struct _RygelStateMachineIface {
	GTypeInterface parent_iface;
	void (*run) (RygelStateMachine* self, GCancellable* cancellable);
};

/**
 * Holds information about a particular resource (device and service)
 * implementation.
 */
struct _RygelResourceInfo {
	GTypeInstance parent_instance;
	volatile int ref_count;
	RygelResourceInfoPrivate * priv;
	char* upnp_type;
	char* upnp_id;
	char* description_path;
	GType type;
};

struct _RygelResourceInfoClass {
	GTypeClass parent_class;
	void (*finalize) (RygelResourceInfo *self);
};

/**
 * Holds information about an icon.
 */
struct _RygelIconInfo {
	GTypeInstance parent_instance;
	volatile int ref_count;
	RygelIconInfoPrivate * priv;
	char* mimetype;
	guint width;
	guint height;
	guint depth;
	char* path;
};

struct _RygelIconInfoClass {
	GTypeClass parent_class;
	void (*finalize) (RygelIconInfo *self);
};

/**
 * Represents a Rygel plugin. Plugins are supposed to provide an object of this
 * class or a subclass.
 */
struct _RygelPlugin {
	GUPnPResourceFactory parent_instance;
	RygelPluginPrivate * priv;
	char* name;
	char* title;
	GeeArrayList* resource_infos;
	GeeArrayList* icon_infos;
};

struct _RygelPluginClass {
	GUPnPResourceFactoryClass parent_class;
};

/**
 * Responsible for plugin loading. Probes for shared library files in a specific
 * directry and tries to grab a function with a specific name and signature,
 * calls it. The loaded module can then add plugins to Rygel by calling the
 * add_plugin method.
 */
struct _RygelPluginLoader {
	GObject parent_instance;
	RygelPluginLoaderPrivate * priv;
};

struct _RygelPluginLoaderClass {
	GObjectClass parent_class;
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

/**
 * A simple implementation of GLib.AsyncResult, very similar to
 * GLib.SimpleAsyncResult that provides holders for generic and error
 * reference/values.
 */
struct _RygelSimpleAsyncResult {
	GObject parent_instance;
	RygelSimpleAsyncResultPrivate * priv;
	GObject* source_object;
	GAsyncReadyCallback callback;
	gpointer callback_target;
	gpointer data;
	GError* error;
};

struct _RygelSimpleAsyncResultClass {
	GObjectClass parent_class;
};

/**
 * Represents a media (Music, Video and Image) item.
 */
struct _RygelMediaItem {
	RygelMediaObject parent_instance;
	RygelMediaItemPrivate * priv;
	char* author;
	char* album;
	char* date;
	char* upnp_class;
	GeeArrayList* uris;
	char* mime_type;
	glong size;
	glong duration;
	gint bitrate;
	gint sample_freq;
	gint bits_per_sample;
	gint n_audio_channels;
	gint track_number;
	gint width;
	gint height;
	gint color_depth;
};

struct _RygelMediaItemClass {
	RygelMediaObjectClass parent_class;
	GstElement* (*create_stream_source) (RygelMediaItem* self);
};


GType rygel_configuration_get_type (void);
#define RYGEL_CONFIGURATION_ROOT_GCONF_PATH "/apps/rygel/"
#define RYGEL_CONFIGURATION_IP_KEY "host-ip"
#define RYGEL_CONFIGURATION_PORT_KEY "port"
#define RYGEL_CONFIGURATION_ENABLED_KEY "enabled"
#define RYGEL_CONFIGURATION_TITLE_KEY "title"
#define RYGEL_CONFIGURATION_TRANSCODING_KEY "enable-transcoding"
#define RYGEL_CONFIGURATION_MP3_TRANSCODER_KEY "enable-mp3-transcoder"
#define RYGEL_CONFIGURATION_MP2TS_TRANSCODER_KEY "enable-mp2ts-transcoder"
#define RYGEL_CONFIGURATION_LPCM_TRANSCODER_KEY "enable-lpcm-transcoder"
RygelConfiguration* rygel_configuration_get_default (void);
RygelConfiguration* rygel_configuration_new (void);
RygelConfiguration* rygel_configuration_construct (GType object_type);
gboolean rygel_configuration_get_enabled (RygelConfiguration* self, const char* section);
char* rygel_configuration_get_title (RygelConfiguration* self, const char* section, const char* default_title);
char* rygel_configuration_get_string (RygelConfiguration* self, const char* section, const char* key, const char* default_value);
GeeArrayList* rygel_configuration_get_string_list (RygelConfiguration* self, const char* section, const char* key);
gint rygel_configuration_get_int (RygelConfiguration* self, const char* section, const char* key, gint min, gint max, gint default_value);
GeeArrayList* rygel_configuration_get_int_list (RygelConfiguration* self, const char* section, const char* key);
gboolean rygel_configuration_get_bool (RygelConfiguration* self, const char* section, const char* key, gboolean default_value);
void rygel_configuration_set_string (RygelConfiguration* self, const char* section, const char* key, const char* value);
void rygel_configuration_set_string_list (RygelConfiguration* self, const char* section, const char* key, GeeArrayList* str_list);
void rygel_configuration_set_int (RygelConfiguration* self, const char* section, const char* key, gint value);
void rygel_configuration_set_bool (RygelConfiguration* self, const char* section, const char* key, gboolean value);
const char* rygel_configuration_get_host_ip (RygelConfiguration* self);
void rygel_configuration_set_host_ip (RygelConfiguration* self, const char* value);
gint rygel_configuration_get_port (RygelConfiguration* self);
void rygel_configuration_set_port (RygelConfiguration* self, gint value);
gboolean rygel_configuration_get_transcoding (RygelConfiguration* self);
void rygel_configuration_set_transcoding (RygelConfiguration* self, gboolean value);
gboolean rygel_configuration_get_mp3_transcoder (RygelConfiguration* self);
void rygel_configuration_set_mp3_transcoder (RygelConfiguration* self, gboolean value);
gboolean rygel_configuration_get_mp2ts_transcoder (RygelConfiguration* self);
void rygel_configuration_set_mp2ts_transcoder (RygelConfiguration* self, gboolean value);
gboolean rygel_configuration_get_lpcm_transcoder (RygelConfiguration* self);
void rygel_configuration_set_lpcm_transcoder (RygelConfiguration* self, gboolean value);
GQuark rygel_content_directory_error_quark (void);
GType rygel_content_directory_get_type (void);
GType rygel_media_object_get_type (void);
GType rygel_media_container_get_type (void);
GType rygel_transcode_manager_get_type (void);
GType rygel_http_server_get_type (void);
#define RYGEL_CONTENT_DIRECTORY_UPNP_ID "urn:upnp-org:serviceId:ContentDirectory"
#define RYGEL_CONTENT_DIRECTORY_UPNP_TYPE "urn:schemas-upnp-org:service:ContentDirectory:2"
#define RYGEL_CONTENT_DIRECTORY_DESCRIPTION_PATH "xml/ContentDirectory.xml"
RygelMediaContainer* rygel_content_directory_create_root_container (RygelContentDirectory* self);
RygelContentDirectory* rygel_content_directory_new (void);
RygelContentDirectory* rygel_content_directory_construct (GType object_type);
GType rygel_connection_manager_get_type (void);
#define RYGEL_CONNECTION_MANAGER_UPNP_ID "urn:upnp-org:serviceId:ConnectionManager"
#define RYGEL_CONNECTION_MANAGER_UPNP_TYPE "urn:schemas-upnp-org:service:ConnectionManager:2"
#define RYGEL_CONNECTION_MANAGER_DESCRIPTION_PATH "xml/ConnectionManager.xml"
RygelConnectionManager* rygel_connection_manager_new (void);
RygelConnectionManager* rygel_connection_manager_construct (GType object_type);
GType rygel_state_machine_get_type (void);
void rygel_state_machine_run (RygelStateMachine* self, GCancellable* cancellable);
gpointer rygel_resource_info_ref (gpointer instance);
void rygel_resource_info_unref (gpointer instance);
GParamSpec* rygel_param_spec_resource_info (const gchar* name, const gchar* nick, const gchar* blurb, GType object_type, GParamFlags flags);
void rygel_value_set_resource_info (GValue* value, gpointer v_object);
gpointer rygel_value_get_resource_info (const GValue* value);
GType rygel_resource_info_get_type (void);
RygelResourceInfo* rygel_resource_info_new (const char* upnp_id, const char* upnp_type, const char* description_path, GType type);
RygelResourceInfo* rygel_resource_info_construct (GType object_type, const char* upnp_id, const char* upnp_type, const char* description_path, GType type);
gpointer rygel_icon_info_ref (gpointer instance);
void rygel_icon_info_unref (gpointer instance);
GParamSpec* rygel_param_spec_icon_info (const gchar* name, const gchar* nick, const gchar* blurb, GType object_type, GParamFlags flags);
void rygel_value_set_icon_info (GValue* value, gpointer v_object);
gpointer rygel_value_get_icon_info (const GValue* value);
GType rygel_icon_info_get_type (void);
RygelIconInfo* rygel_icon_info_new (const char* mimetype, guint width, guint height, guint depth, const char* path);
RygelIconInfo* rygel_icon_info_construct (GType object_type, const char* mimetype, guint width, guint height, guint depth, const char* path);
GType rygel_plugin_get_type (void);
RygelPlugin* rygel_plugin_new (const char* name, const char* title);
RygelPlugin* rygel_plugin_construct (GType object_type, const char* name, const char* title);
void rygel_plugin_add_resource (RygelPlugin* self, RygelResourceInfo* resource_info);
void rygel_plugin_add_icon (RygelPlugin* self, RygelIconInfo* icon_info);
gboolean rygel_plugin_get_available (RygelPlugin* self);
void rygel_plugin_set_available (RygelPlugin* self, gboolean value);
GType rygel_plugin_loader_get_type (void);
RygelPluginLoader* rygel_plugin_loader_new (void);
RygelPluginLoader* rygel_plugin_loader_construct (GType object_type);
void rygel_plugin_loader_load_plugins (RygelPluginLoader* self);
void rygel_plugin_loader_add_plugin (RygelPluginLoader* self, RygelPlugin* plugin);
RygelPlugin* rygel_plugin_loader_get_plugin_by_name (RygelPluginLoader* self, const char* name);
GeeCollection* rygel_plugin_loader_list_plugins (RygelPluginLoader* self);
RygelMediaContainer* rygel_media_container_new (const char* id, RygelMediaContainer* parent, const char* title, guint child_count);
RygelMediaContainer* rygel_media_container_construct (GType object_type, const char* id, RygelMediaContainer* parent, const char* title, guint child_count);
RygelMediaContainer* rygel_media_container_new_root (const char* title, guint child_count);
RygelMediaContainer* rygel_media_container_construct_root (GType object_type, const char* title, guint child_count);
void rygel_media_container_get_children (RygelMediaContainer* self, guint offset, guint max_count, GCancellable* cancellable, GAsyncReadyCallback callback, void* callback_target);
GeeList* rygel_media_container_get_children_finish (RygelMediaContainer* self, GAsyncResult* res, GError** error);
void rygel_media_container_find_object (RygelMediaContainer* self, const char* id, GCancellable* cancellable, GAsyncReadyCallback callback, void* callback_target);
RygelMediaObject* rygel_media_container_find_object_finish (RygelMediaContainer* self, GAsyncResult* res, GError** error);
void rygel_media_container_updated (RygelMediaContainer* self);
GType rygel_simple_async_result_get_type (void);
RygelSimpleAsyncResult* rygel_simple_async_result_new (GType g_type, GBoxedCopyFunc g_dup_func, GDestroyNotify g_destroy_func, GObject* source_object, GAsyncReadyCallback callback, void* callback_target);
RygelSimpleAsyncResult* rygel_simple_async_result_construct (GType object_type, GType g_type, GBoxedCopyFunc g_dup_func, GDestroyNotify g_destroy_func, GObject* source_object, GAsyncReadyCallback callback, void* callback_target);
void rygel_simple_async_result_complete (RygelSimpleAsyncResult* self);
void rygel_simple_async_result_complete_in_idle (RygelSimpleAsyncResult* self);
GType rygel_media_item_get_type (void);
#define RYGEL_MEDIA_ITEM_IMAGE_CLASS "object.item.imageItem"
#define RYGEL_MEDIA_ITEM_VIDEO_CLASS "object.item.videoItem"
#define RYGEL_MEDIA_ITEM_AUDIO_CLASS "object.item.audioItem"
#define RYGEL_MEDIA_ITEM_MUSIC_CLASS "object.item.audioItem.musicTrack"
RygelMediaItem* rygel_media_item_new (const char* id, RygelMediaContainer* parent, const char* title, const char* upnp_class);
RygelMediaItem* rygel_media_item_construct (GType object_type, const char* id, RygelMediaContainer* parent, const char* title, const char* upnp_class);
GstElement* rygel_media_item_create_stream_source (RygelMediaItem* self);


G_END_DECLS

#endif
