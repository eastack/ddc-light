#include <gtk/gtk.h>
#include <ddcutil_c_api.h>
#include "ddc.h"

bool scale_pressed = false;

static gboolean
scale_press() {
    scale_pressed = true;
    return FALSE;
}

static void
value_changed(GtkRange *range,
              DDCA_Display_Handle *dh) {
    if (!scale_pressed) {
        gdouble pos = gtk_range_get_value(range);
        set_display_brightness(dh, (int) pos);
    }
}

static void
scale_release(GtkRange *range,
              GdkEventButton *event,
              DDCA_Display_Handle *dh) {
    gdouble pos = gtk_range_get_value(range);
    set_display_brightness(dh, (int) pos);
    scale_pressed = false;
}

static void
activate(GtkApplication *app,
         DDCA_Display_Handle *dh) {
    // window
    GtkWidget *window;
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW (window), "ddc-light");
    gtk_window_set_default_size(GTK_WINDOW (window), 150, 50);

    // scale
    GtkWidget *scale = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 0, 100, 1);
    int brightness = get_display_brightness(dh);
    gtk_range_set_value(GTK_RANGE(scale), brightness);
    gtk_widget_set_hexpand(scale, TRUE);
    gtk_widget_set_valign(scale, GTK_ALIGN_START);

    g_signal_connect (scale,
                      "button-press-event",
                      G_CALLBACK(scale_press),
                      NULL);

    g_signal_connect (scale,
                      "value-changed",
                      G_CALLBACK(value_changed),
                      dh);

    g_signal_connect (scale,
                      "button-release-event",
                      G_CALLBACK(scale_release),
                      dh);

    // grid
    GtkWidget *grid;
    grid = gtk_grid_new();
    gtk_grid_set_column_spacing(GTK_GRID (grid), 1);
    gtk_grid_set_column_homogeneous(GTK_GRID (grid), TRUE);
    gtk_grid_attach(GTK_GRID (grid), scale, 0, 0, 1, 1);

    // assembly
    gtk_container_add(GTK_CONTAINER (window), grid);

    // display
    gtk_widget_show_all(window);
}

int
main(int argc,
     char **argv) {
    // ddcutil
    DDCA_Display_Handle *dh = open_display_by_dispno(1);
    GtkApplication *app = gtk_application_new("me.eastack.ddc-light", G_APPLICATION_FLAGS_NONE);
    g_signal_connect (app, "activate", G_CALLBACK(activate), dh);

    int status = g_application_run(G_APPLICATION (app), argc, argv);

    g_object_unref(app);
    ddca_close_display(dh);

    return status;
}

