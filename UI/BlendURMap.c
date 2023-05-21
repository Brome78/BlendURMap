//#include "../Generation/main.h" - placeholder, make header file for main so can be called for gtk
#include <gtk/gtk.h>
#include <stdlib.h>

#include "Utils/generate.h"
#include "../Generation/Options/exec_export.h"
#include "../Generation/Utils/options_map.h"


typedef struct UserInterface
{
  GtkWindow* window;
  GtkSpinButton* width;
  GtkSpinButton* height;
  GtkSpinButton* seed;
  GtkAdjustment* w;
  GtkAdjustment* h;
  GtkAdjustment* seedix;
  GtkToggleButton *isrender3d;
  GtkToggleButton *island;
  GtkToggleButton *mindustry;
  GtkToggleButton *props;
  GtkToggleButton *river;
  GtkToggleButton *villages;
  GtkButton* render2d;
  GtkButton* render3d;
  GtkButton* generate_button;
  //GtkButton* load_button;
  // Biome Tweaks
  GtkAdjustment* beach;
  GtkAdjustment* coast;
  GtkAdjustment* deep_ocean;
  GtkAdjustment* ocean;
  GtkAdjustment* mid_mountains;
  GtkAdjustment* mountains;
  GtkAdjustment* picks;
  GtkAdjustment* plains;
  GtkAdjustment* plateau;
  GtkAdjustment* savanna;
  GtkAdjustment* snow;
  GtkAdjustment* swamp;
} UserInterface;

typedef struct App
{
    UserInterface ui;
} App;

void on_generate_button_clicked(GtkButton *button, gpointer user_data)
{

  App *app = user_data; //recover App information

  GError *err = NULL;

  int width = gtk_adjustment_get_value(app->ui.w);
  int height = gtk_adjustment_get_value(app->ui.h);

  //g_print("w : %d \nh : %d\n",width,height);

  if(width == 0 || height == 0 || height != width)
  {
    width = 1025;
    height = 1025;
  }

  struct options* opt_alt = options_alt_3d();
  struct options* opt_temp = options_temp_3d();
  struct options* opt_hum = options_alt_3d();

  opt_alt->sizex = width;
  opt_alt->sizey = height;

  opt_temp->sizex = width;
  opt_temp->sizey = height;

  opt_hum->sizex = width;
  opt_hum->range = 252;

  int seedi =  gtk_adjustment_get_value(app->ui.seedix);
  if(seedi == 0)
    seedi = -1;

  int er1 = system("rm *.OBJ *.png");
  if(er1<0)
    return;
  printf("%d\n",gtk_toggle_button_get_active(app->ui.river));

  struct threshold *t = malloc(sizeof(struct threshold));
  t->deep_ocean = gtk_adjustment_get_value(app->ui.deep_ocean);
  t->ocean = gtk_adjustment_get_value(app->ui.ocean);
  t->coast = gtk_adjustment_get_value(app->ui.coast);
  t->beach = gtk_adjustment_get_value(app->ui.beach);
  t->mid_mountains = gtk_adjustment_get_value(app->ui.mid_mountains);
  t->mountains = gtk_adjustment_get_value(app->ui.mountains);
  t->picks = gtk_adjustment_get_value(app->ui.picks);
  t->plains = gtk_adjustment_get_value(app->ui.plains);
  t->snow = gtk_adjustment_get_value(app->ui.snow);
  t->savanna = gtk_adjustment_get_value(app->ui.savanna);
  t->plateau = gtk_adjustment_get_value(app->ui.plateau);
  t->plateau2 = gtk_adjustment_get_value(app->ui.plateau) + 20;
  t->plateau3 = gtk_adjustment_get_value(app->ui.plateau) + 15;
  t->swamp = gtk_adjustment_get_value(app->ui.swamp);

  exec_ui(seedi, opt_alt, opt_temp, opt_hum, t, width, height,
            gtk_toggle_button_get_active(app->ui.island),
            gtk_toggle_button_get_active(app->ui.river),
            gtk_toggle_button_get_active(app->ui.props),
            gtk_toggle_button_get_active(app->ui.villages),
            gtk_toggle_button_get_active(app->ui.isrender3d),
            0,
            gtk_toggle_button_get_active(app->ui.mindustry));
  //if statement for 3D gen
}

void on_render_2D_clicked(GtkButton* button, gpointer user_data)
{
  int er = system("feh *.png");
  if(er<0)
    return;
}

void on_render_3D_clicked(GtkButton* button, gpointer user_data)
{
  int er = system("f3d map.OBJ");
  if(er<0)
    return;
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
  if (gtk_builder_add_from_file(builder, "UI.glade", &error) == 0)
  {
    g_printerr("Error loading file: %s\n", error->message);
    g_clear_error(&error);
    return 1;
  }



  GtkWindow* window = GTK_WINDOW(gtk_builder_get_object(builder, "org.gtk.UI"));

  GtkSpinButton* width = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"width"));
  GtkSpinButton* height = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"height"));
  GtkSpinButton* seed = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"seed"));

  GtkAdjustment* w = GTK_ADJUSTMENT(gtk_builder_get_object(builder,"Width"));
  GtkAdjustment* h = GTK_ADJUSTMENT(gtk_builder_get_object(builder,"Height"));
  GtkAdjustment* seedix = GTK_ADJUSTMENT(gtk_builder_get_object(builder,"Seedi"));

  GtkToggleButton* isrender3d = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder,"render"));
  GtkToggleButton* island = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder,"island"));
  GtkToggleButton* props = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder,"props"));
  GtkToggleButton* river = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder,"rivers"));
  GtkToggleButton* villages = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder,"villages"));
  GtkToggleButton* mindustry = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder,"mindustry"));

  GtkButton* render2d = GTK_BUTTON(gtk_builder_get_object(builder, "render_in_2D"));
  GtkButton* render3d = GTK_BUTTON(gtk_builder_get_object(builder, "render_in_3D"));
  GtkButton* generate_button = GTK_BUTTON(gtk_builder_get_object(builder,"generate"));


  GtkAdjustment* beach = GTK_ADJUSTMENT(gtk_builder_get_object(builder,"Beach"));
  GtkAdjustment* coast = GTK_ADJUSTMENT(gtk_builder_get_object(builder,"Coast"));
  GtkAdjustment* deep_ocean = GTK_ADJUSTMENT(gtk_builder_get_object(builder,"Deep_Ocean"));
  GtkAdjustment* ocean = GTK_ADJUSTMENT(gtk_builder_get_object(builder,"Ocean"));
  GtkAdjustment* mid_mountains = GTK_ADJUSTMENT(gtk_builder_get_object(builder,"Mid_Mountains"));
  GtkAdjustment* mountains = GTK_ADJUSTMENT(gtk_builder_get_object(builder,"Mountains"));
  GtkAdjustment* picks = GTK_ADJUSTMENT(gtk_builder_get_object(builder,"Picks"));
  GtkAdjustment* plains = GTK_ADJUSTMENT(gtk_builder_get_object(builder,"Plains"));
  GtkAdjustment* plateau = GTK_ADJUSTMENT(gtk_builder_get_object(builder,"Plateau"));
  GtkAdjustment* savanna = GTK_ADJUSTMENT(gtk_builder_get_object(builder,"Savanna"));
  GtkAdjustment* snow = GTK_ADJUSTMENT(gtk_builder_get_object(builder,"Snow"));
  GtkAdjustment* swamp = GTK_ADJUSTMENT(gtk_builder_get_object(builder,"Swamp"));



  App app =
    {
        .ui =
            {
                .window = window,
                .render2d = render2d,
                .width = width,
                .height = height,
                .seed = seed,
                .w = w,
                .h = h,
                .seedix = seedix,
                .isrender3d = isrender3d,
                .island = island,
                .props = props,
                .river = river,
                .villages = villages,
                .mindustry = mindustry,
                .render2d = render2d,
                .render3d = render3d,
                .generate_button = generate_button,

                .beach = beach,
                .coast = coast,
                .deep_ocean = deep_ocean,
                .ocean = ocean,
                .mid_mountains = mid_mountains,
                .mountains = mountains,
                .picks = picks,
                .plains = plains,
                .plateau = plateau,
                .savanna = savanna,
                .snow = snow,
                .swamp = swamp,
            },
    };
  
  g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
  //g_signal_connect(isrender3d, "toggled", G_CALLBACK(render), NULL);
  g_signal_connect(generate_button, "clicked", G_CALLBACK(on_generate_button_clicked),&app);
  g_signal_connect(render2d, "clicked", G_CALLBACK(on_render_2D_clicked),&app);
  g_signal_connect(render3d, "clicked", G_CALLBACK(on_render_3D_clicked),&app);

  //g_signal_connect(area, "draw", G_CALLBACK(on_draw), &rect);
  //g_signal_connect(area, "configure", G_CALLBACK(on_configure), &rect);

  gtk_main();

  return 0;
}
