//#include "../Generation/main.h" - placeholder, make header file for main so can be called for gtk
#include <gtk/gtk.h>
#include "resize.h"

#include <stdlib.h>²
#include "../Generation/Options/exec_perso.h"

typedef struct UserInterface
{
  GtkWindow* window;
  GtkImage* render2d;
  GtkButton* generate_button;
  GtkButton* load_button;
} UserInterface;

typedef struct App
{
    UserInterface ui;
} App;

void on_generate_button_clicked(GtkButton *button, gpointer user_data)
{

  App *app = user_data; //recover App information

  GError *err = NULL;

  system("feh map.png");


  //resize("map.png","tmp.png",400,400);
  //GdkPixbuf* pxbuf = gdk_pixbuf_new_from_file("tmp.png",&err);
  //gtk_image_set_from_pixbuf(app->ui.render2d,pxbuf); //sets the image on the window
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
  GtkButton* load_button = GTK_BUTTON(gtk_builder_get_object(builder,"load"));


  App app =
    {
        .ui =
            {
                .window = window,
                .render2d = render2d,
                .load_button = load_button,
                .generate_button = generate_button,
            },
    };

  g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
  //g_signal_connect(render2d, "render2d", G_CALLBACK(render), NULL);
  g_signal_connect(generate_button, "clicked", G_CALLBACK(on_generate_button_clicked),&app);
  //g_signal_connect(area, "draw", G_CALLBACK(on_draw), &rect);
  //g_signal_connect(area, "configure", G_CALLBACK(on_configure), &rect);

  gtk_main();

  return 0;
}
