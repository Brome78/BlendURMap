#include "../Generation/Utils/utils.h"
#include <gtk/gtk.h>


static gboolean render(GtkImage *image, GdkGLContext *context)
{
  // inside this function it's safe to use GL; the given
  // GdkGLContext has been made current to the drawable
  // surface used by the `GtkGLArea` and the viewport has
  // already been set to be the size of the allocation
  GError *err = NULL;
  GdkPixbuf* pxbuf = gdk_pixbuf_new_from_file("map.png",&err);
  gtk_image_set_from_pixbuf(image,pxbuf);

  // draw your object
  // draw_an_object ();

  // we completed our drawing; the draw commands will be
  // flushed at the end of the signal emission chain, and
  // the buffers will be drawn on the window
  return TRUE;
}

int main()
{
  //Nothing to see yet !
  gtk_init(NULL,NULL);
  // Constructs a GtkBuilder instance.
  GtkBuilder* builder = gtk_builder_new();

  // Loads the UI description.
  // (Exits if an error occurs.)
  GError* error = NULL;
  if (gtk_builder_add_from_file(builder, "NewApp.glade", &error) == 0)
  {
    g_printerr("Error loading file: %s\n", error->message);
    g_clear_error(&error);
    return 1;
  }

  GtkWindow* window = GTK_WINDOW(gtk_builder_get_object(builder, "org.gtk.NewApp"));
  //GtkGLArea* render3d = GTK_GL_AREA(gtk_builder_get_object(builder,"3D_window"));
  //GtkButton* start_button = GTK_BUTTON(gtk_builder_get_object(builder, "start_button"));
  GtkImage* render2d = GTK_IMAGE(gtk_builder_get_object(builder, "2D_render"));
  GtkButton* generate_button = GTK_BUTTON(gtk_builder_get_object(builder,"generate"));

  // Connects signal handlers.
  g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
  g_signal_connect(render2d, "render2d", G_CALLBACK(render), NULL);
  //g_signal_connect(generate, "generate", G_CALLBACK(render),NULL);
  //g_signal_connect(area, "draw", G_CALLBACK(on_draw), &rect);
  //g_signal_connect(area, "configure", G_CALLBACK(on_configure), &rect);
  gtk_main();
  return 0;
}
