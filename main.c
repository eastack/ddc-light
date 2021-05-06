#include <gtk/gtk.h>
#include <ddcutil_c_api.h>

#define DDC_ERRMSG(function_name, status_code)\
    printf("(%s) %s() returned %d (%s): %s\n",\
    __func__, function_name, status_code,\
    ddca_rc_name(status_code),\
    ddca_rc_desc(status_code))\


/* This is the callback function.
 * It is a handler function which reacts to the signal.
 * In this case, it will notify the user the value of their scale as a label.
 */
static void
scale_moved(GtkRange *range,
            gpointer user_data) {
    GtkWidget *label = user_data;

    /* Get the value of the range, and convert it into a string which will be
     * used as a new label for the horizontal scale.
     * %.0f - stands for a double that will have 0 decimal places.
     */
    gdouble pos = gtk_range_get_value(range);
    /* Note: Using g_strdup_printf returns a string that must be freed.
     * (In which is done below)
     */
    gchar *str = g_strdup_printf("Horizontal scale is %.0f", pos);
    gtk_label_set_text(GTK_LABEL (label), str);

    g_free(str);
}


static void
activate(GtkApplication *app,
         gpointer user_data) {
    GtkWidget *window;
    GtkWidget *label;
    label = gtk_label_new("Move the scale handle...");
//    GtkWidget *button;
//    GtkWidget *button_box;


    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW (window), "ddc-light");
    gtk_window_set_default_size(GTK_WINDOW (window), 200, 200);

//    button_box = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
//    gtk_container_add(GTK_CONTAINER (window), button_box);
//
//    button = gtk_button_new_with_label("exit");
//    g_signal_connect (button, "clicked", G_CALLBACK(print_hello), NULL);
//    g_signal_connect_swapped (button, "clicked", G_CALLBACK(gtk_widget_destroy), window);
//    gtk_container_add(GTK_CONTAINER (button_box), button);

    // my scale
    GtkWidget *scale;
    scale = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 0, 100, 1);
    gtk_scale_set_digits(GTK_SCALE (scale), 0);
    gtk_widget_set_hexpand(scale, TRUE);
    gtk_widget_set_valign(scale, GTK_ALIGN_START);

    g_signal_connect (scale,
                      "value-changed",
                      G_CALLBACK(scale_moved),
                      label);

    // grid
    GtkWidget *grid;
    grid = gtk_grid_new();
    gtk_grid_set_column_spacing(GTK_GRID (grid), 2);
    gtk_grid_set_column_homogeneous(GTK_GRID (grid), TRUE);
    gtk_grid_attach(GTK_GRID(grid), scale, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID (grid), label, 0, 1, 1, 1);

    gtk_container_add(GTK_CONTAINER (window), grid);

    gtk_widget_show_all(window);
}

DDCA_Display_Handle *open_first_display_by_dispno() {
    printf("Opening display 1...\n");
    DDCA_Display_Identifier did;
    DDCA_Display_Ref dref;
    DDCA_Display_Handle dh = NULL;

    ddca_create_dispno_display_identifier(1, &did);
    DDCA_Status rc = ddca_get_display_ref(did, &dref);
    if (rc != 0) {
        DDC_ERRMSG("ddca_create_display_ref", rc);
    } else {
        rc = ddca_open_display2(dref, false, &dh);
        if (rc != 0) {
            DDC_ERRMSG("ddca_open_display", rc);
        } else {
            printf("Opened display handle: %s\n", ddca_dh_repr(dh));
        }
    }
}

void get_capabilities() {
    DDCA_Display_Handle dh = open_first_display_by_dispno();
    if (!dh)
        goto bye;

    DDCA_Status rc = 0;

    bye:
    return;
}

int
main(int argc,
     char **argv) {
    GtkApplication *app;
    int status;
    open_first_display_by_dispno();

    app = gtk_application_new("me.eastack.ddc-light", G_APPLICATION_FLAGS_NONE);
    g_signal_connect (app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION (app), argc, argv);
    g_object_unref(app);

    return status;
}

