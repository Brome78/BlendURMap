//#include "../Generation/main.h" - placeholder, make header file for main so can be called for gtk
#include <gtk/gtk.h>
#include <stdlib.h>

#include "Utils/generate.h"
#include "../Generation/Utils/options_map.h"


typedef struct UserInterface
{
  GtkWindow* window;
  GtkImage* render2d;
  GtkSpinButton* width;
  GtkSpinButton* height;
  GtkSpinButton* seed;
  GtkToggleButton *isrender3d;
  GtkToggleButton *island;
  GtkToggleButton *props;
  GtkToggleButton *river;
  GtkToggleButton *villages;
  GtkButton* generate_button;
  //GtkButton* load_button;
} UserInterface;

typedef struct App
{
    UserInterface ui;
} App;

void on_generate_button_clicked(GtkButton *button, gpointer user_data)
{

  App *app = user_data; //recover App information

  GError *err = NULL;

  int width = gtk_spin_button_get_value_as_int(app->ui.width);
  int height =  gtk_spin_button_get_value_as_int(app->ui.height);

  if(width == 0 || height == 0)
  {
    width = 1000;
    height = 1000;
  }

  struct options* opt_alt = options_alt_3d();
  struct options* opt_temp = options_temp_3d();

  opt_alt->sizex = width;
  opt_alt->sizey = height;

  opt_temp->sizex = width;
  opt_temp->sizey = height;


  int seedi =  gtk_spin_button_get_value_as_int(app->ui.seed);
  if(seedi == 0)
    seedi = -1;

  exec_ui(seedi, opt_alt, opt_temp, opt_temp, width, height,
             gtk_toggle_button_get_active(app->ui.river),
             gtk_toggle_button_get_active(app->ui.props),
             gtk_toggle_button_get_active(app->ui.villages),
             0);

  //if statement for 3D gen
}

void on_render_2D_clicked(GtkButton* button, gpointer user_data)
{
  system("feh map.png");
}

void on_render_3D_clicked(GtkButton* button, gpointer user_data)
{
  system("f3d map.OBJ");
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

  GtkSpinButton* width = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"width"));
  GtkSpinButton* height = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"height"));
  GtkSpinButton* seed = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"seed"));

  GtkToggleButton* isrender3d = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder,"render"));
  GtkToggleButton* island = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder,"island"));
  GtkToggleButton* props = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder,"props"));
  GtkToggleButton* river = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder,"river"));
  GtkToggleButton* villages = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder,"villages"));

  GtkImage* render2d = GTK_IMAGE(gtk_builder_get_object(builder, "2D_render"));

  GtkButton* generate_button = GTK_BUTTON(gtk_builder_get_object(builder,"generate"));


  App app =
    {
        .ui =
            {
                .window = window,
                .render2d = render2d,
                .isrender3d = isrender3d,
                .island = island,
                .props = props,
                .river = river,
                .villages = villages,
                //.load_button = load_button,
                .generate_button = generate_button,
            },
    };

  g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
  //g_signal_connect(isrender3d, "toggled", G_CALLBACK(render), NULL);
  g_signal_connect(generate_button, "clicked", G_CALLBACK(on_generate_button_clicked),&app);
  //g_signal_connect(area, "draw", G_CALLBACK(on_draw), &rect);
  //g_signal_connect(area, "configure", G_CALLBACK(on_configure), &rect);

  gtk_main();

  return 0;
}
