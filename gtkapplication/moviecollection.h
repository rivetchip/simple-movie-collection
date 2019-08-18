#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <math.h>

#include <glib.h>
#include <gtk/gtk.h>
#include <gio/gio.h>
#include <json-glib/json-glib.h>

#include "macros.h"
#include "vector.h"

#ifdef  __cplusplus
    extern "C" {
#endif


// type definition
struct _MovieApplication {
    GtkApplication parent_instance;

};

typedef struct _MovieApplication MovieApplication;
typedef GtkApplicationClass MovieApplicationClass;

G_DEFINE_TYPE(MovieApplication, movie_application, GTK_TYPE_APPLICATION);

// public api
GType movie_application_get_type(void) G_GNUC_CONST;

// macro function G_DECLARE_FINAL_TYPE
inline MovieApplication *MOVIE_APPLICATION(gpointer ptr) {
    return G_TYPE_CHECK_INSTANCE_CAST(ptr, movie_application_get_type(), MovieApplication);
}

////////////////////

// type definition
struct _MovieWindow {
    GtkApplicationWindow parent_instance;

    // window state
    int win_height;
    int win_width;
    bool is_maximized;
    bool is_fullscreen;

    // widgets
    int paned_position;
};

typedef struct _MovieWindow MovieWindow;
typedef GtkApplicationWindowClass MovieWindowClass;

G_DEFINE_TYPE(MovieWindow, movie_window, GTK_TYPE_APPLICATION_WINDOW);

// public api
GType movie_window_get_type(void) G_GNUC_CONST;
#define MOVIE_TYPE_WINDOW (gedit_window_get_type())

// macro function G_DECLARE_FINAL_TYPE
inline MovieWindow *MOVIE_WINDOW(gpointer ptr) {
    return G_TYPE_CHECK_INSTANCE_CAST(ptr, movie_window_get_type(), MovieWindow);
}


////////////////////

struct MoviesMetadata {
    int version;
    char *created;
    char *imported;
    char *source;
};

struct Movie {
    char *title;
    bool favorite;
    int rating; // /100
    char *tagline;
    char *originalTitle;
    int ratingPress;
    int duration; // minutes
    char *dateReleased;
    char *dateCreated;
    char *dateModified;
    char *poster;
    char *description;
    char *comment;
    char *director;
    char **countries; // array
    char *genres; // array
    char **actors; // array[][2]
    char *serie;
    char **companies; // array
    char *keywords; // array
    char *source;
    int sourceId;
    char *webPage;
};

struct MoviesStorage {
    size_t size;
    struct MoviesMetadata *metadata;
    vector *movies; // array[Movie]
};

////////////////////

struct WidgetHeaderbar {
    GtkWidget *headerbar; // container
    GtkWidget *button_close;
    GtkWidget *button_minimize;
    GtkWidget *button_maximize;
};

struct WidgetToolbar {
    GtkWidget *toolbar; // container
    GtkWidget *button_open;
    GtkWidget *button_save;
    GtkWidget *button_new;
    GtkWidget *providers;
};

struct WidgetSidebar {
    GtkWidget *sidebar; // container
    GtkWidget *search_box;
    GtkWidget *search_entry;
    GtkWidget *list_items; // movies
};

struct WidgetSidebarItem {
    GtkWidget *list_row; // container
    GtkWidget *label;
    GtkWidget *favorite_icon;
};

////////////////////

struct WidgetPanels {
    GtkWidget *panels; // container
    GtkWidget *panel_welcome;
    GtkWidget *panel_preview;
    GtkWidget *panel_edition;
};

struct WidgetPanelWelcome {
    GtkWidget *panel; // container

};

struct WidgetPanelPreview {
    GtkWidget *panel; // container
    struct WidgetStarRating *widget_starrating;

};

struct WidgetPanelEdition {
    GtkWidget *panel; // container
    struct WidgetStarRating *widget_starrating;

};

struct WidgetStatusbar {
    GtkWidget *statusbar; // container
    GtkWidget *label;
};

////////////////////

struct WidgetStarRating {
    GtkWidget *starrating; // container
    bool interactive; // can be clickable
    int rating;
    GtkWidget *gtkstars[5]; //buttons
};

////////////////////


#ifdef  __cplusplus
    } // extern c
#endif
