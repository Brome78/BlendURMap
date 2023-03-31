#include "../Generation/Utils/utils.h"
#include <gtk/gtk.h>

int main()
{
  //Nothing to see yet !
  gtk_init(NULL,NULL);
  // Constructs a GtkBuilder instance.
  GtkBuilder* builder = gtk_builder_new ();

  // Loads the UI description.
  // (Exits if an error occurs.)
  GError* error = NULL;
  if (gtk_builder_add_from_file(builder, "NewApp.glade", &error) == 0)
  {
    g_printerr("Error loading file: %s\n", error->message);
    g_clear_error(&error);
    return 1;
  }
  //GtkWindow* window = GTK_WINDOW(gtk_builder_get_object(builder, "org.gtk.NewApp"));
  //GtkButton* start_button = GTK_BUTTON(gtk_builder_get_object(builder, "start_button"));
  //GtkDrawingArea* area = GTK_DRAWING_AREA(gtk_builder_get_object(builder, "area"));

  // Connects signal handlers.
  //g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
  //g_signal_connect(start_button, "clicked", G_CALLBACK(on_start), NULL);
  //g_signal_connect(area, "draw", G_CALLBACK(on_draw), &rect);
  //g_signal_connect(area, "configure", G_CALLBACK(on_configure), &rect);
  gtk_main();
  return 0;
}
