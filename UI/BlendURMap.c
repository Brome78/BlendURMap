//#include "../Generation/main.h" - placeholder, make header file for main so can be called for gtk
#include <gtk/gtk.h>
#include <stdlib.h>

#include "Utils/generate.h"
#include "Utils/resize.h"
#include "../Generation/Options/exec_export.h"
#include "../Generation/Utils/options_map.h"


typedef struct UserInterface
{
  GtkWindow* window;
  GtkImage* image;
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
  GtkButton* export_map;
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

  GtkSpinButton* spb_beach;
  GtkSpinButton* spb_coast;
  GtkSpinButton* spb_deep_ocean;
  GtkSpinButton* spb_ocean;
  GtkSpinButton* spb_mid_mountains;
  GtkSpinButton* spb_mountains;
  GtkSpinButton* spb_picks;
  GtkSpinButton* spb_plains;
  GtkSpinButton* spb_plateau;
  GtkSpinButton* spb_savanna;
  GtkSpinButton* spb_snow;
  GtkSpinButton* spb_swamp;

  struct current_map* current_map;
} UserInterface;

typedef struct App
{
    UserInterface ui;
} App;

void set_image(GtkImage *image, const gchar* filename)
{

  resize(filename,"tmp/resized.png",500,500);
  gtk_image_set_from_file(image,"tmp/resized.png");

}

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

  struct current_map* current_map = exec_ui(seedi, opt_alt, opt_temp, opt_hum, t, width, height,
            gtk_toggle_button_get_active(app->ui.island),
            gtk_toggle_button_get_active(app->ui.river),
            gtk_toggle_button_get_active(app->ui.props),
            gtk_toggle_button_get_active(app->ui.villages),
            gtk_toggle_button_get_active(app->ui.isrender3d),
            0,
            gtk_toggle_button_get_active(app->ui.mindustry));
  set_image(app->ui.image,"tmp/map.png");
  app->ui.current_map = current_map;
  //if statement for 3D gen
}

void on_render_2D_clicked(GtkButton* button, gpointer user_data)
{
  int er = system("feh tmp/*.png");
  if(er<0)
    return;
}

void on_render_3D_clicked(GtkButton* button, gpointer user_data)
{
  int er = system("f3d tmp/map.OBJ");
  if(er<0)
    return;
}

void refresh(GtkButton *button, gpointer user_data)
{

  App *app = user_data; //recover App information

  if(app->ui.current_map == NULL)
    return;
  
  GError *err = NULL;

  struct current_map* cur = app->ui.current_map;

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

  SDL_Surface *map = apply_biome(cur->perlin, cur->simplex,cur->ds,
            cur->opt_alt,cur->opt_hum,t,
            gtk_toggle_button_get_active(app->ui.mindustry));
  save_to_png(map,"tmp/map.png");
  
  set_image(app->ui.image,"tmp/map.png");
  //if statement for 3D gen
}

void export_map_file(GtkWidget *widget, gpointer data)
{
    App *ui = data;
    GtkWidget *dialog;
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_SAVE;
    gint res;

    dialog = gtk_file_chooser_dialog_new ("Choose File",
            ui->ui.window,
            action,
            ("_Cancel"),
            GTK_RESPONSE_CANCEL,
            ("_Save"),
            GTK_RESPONSE_ACCEPT,
            NULL);

    res = gtk_dialog_run (GTK_DIALOG (dialog));
    char *filename = "default.png";
    if (res == GTK_RESPONSE_ACCEPT)
    {

        GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);
        filename = gtk_file_chooser_get_filename (chooser);
    }

    gtk_widget_destroy (dialog);

    save_image(load_image("tmp/map.png"),filename);

    gchar string[200];
    g_snprintf(string,200,"Export :\n%s\nSuccess.",filename);
    GtkWidget* loaded = gtk_message_dialog_new(
        NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK,"%s",string);


    gtk_dialog_run(GTK_DIALOG(loaded));
    gtk_widget_destroy(loaded);
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

  GtkImage* image = GTK_IMAGE(gtk_builder_get_object(builder,"image"));

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
  GtkButton* export_map = GTK_BUTTON(gtk_builder_get_object(builder,"export_map"));


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

  GtkSpinButton* spb_beach = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"beach"));
  GtkSpinButton* spb_coast = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"coast"));
  GtkSpinButton* spb_deep_ocean = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"deep_ocean"));
  GtkSpinButton* spb_ocean =      GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"ocean"));
  GtkSpinButton* spb_mid_mountains = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"mid_mountains"));
  GtkSpinButton* spb_mountains = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"mountains"));
  GtkSpinButton* spb_picks = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"picks"));
  GtkSpinButton* spb_plains = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"plains"));
  GtkSpinButton* spb_plateau = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"plateau"));
  GtkSpinButton* spb_savanna = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"savanna"));
  GtkSpinButton* spb_snow = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"snow"));
  GtkSpinButton* spb_swamp = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"swamp"));



  App app =
    {
        .ui =
            {
                .window = window,
                .image = image,
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
                .export_map = export_map,

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

                .spb_beach = spb_beach,
                .spb_coast = spb_coast,
                .spb_deep_ocean = spb_deep_ocean,
                .spb_ocean = spb_ocean,
                .spb_mid_mountains = spb_mid_mountains,
                .spb_mountains = spb_mountains,
                .spb_picks = spb_picks,
                .spb_plains = spb_plains,
                .spb_plateau = spb_plateau,
                .spb_savanna = spb_savanna,
                .spb_snow = spb_snow,
                .spb_swamp = spb_swamp,

                .current_map = NULL,
            },
    };

  set_image(image,"tmp/map.png");


  
  g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

  //g_signal_connect(isrender3d, "toggled", G_CALLBACK(render), NULL);
  g_signal_connect(generate_button, "clicked", G_CALLBACK(on_generate_button_clicked),&app);
  g_signal_connect(render2d, "clicked", G_CALLBACK(on_render_2D_clicked),&app);
  g_signal_connect(render3d, "clicked", G_CALLBACK(on_render_3D_clicked),&app);
  g_signal_connect(export_map, "clicked", G_CALLBACK(export_map_file),&app);

  g_signal_connect(spb_beach, "value_changed", G_CALLBACK(refresh),&app);
  g_signal_connect(spb_coast, "value_changed", G_CALLBACK(refresh),&app);
  g_signal_connect(spb_deep_ocean, "value_changed", G_CALLBACK(refresh),&app);
  g_signal_connect(spb_ocean, "value_changed", G_CALLBACK(refresh),&app);
  g_signal_connect(spb_mid_mountains, "value_changed", G_CALLBACK(refresh),&app);
  g_signal_connect(spb_mountains, "value_changed", G_CALLBACK(refresh),&app);
  g_signal_connect(spb_picks, "value_changed", G_CALLBACK(refresh),&app);
  g_signal_connect(spb_plains, "value_changed", G_CALLBACK(refresh),&app);
  g_signal_connect(spb_plateau, "value_changed", G_CALLBACK(refresh),&app);
  g_signal_connect(spb_savanna, "value_changed", G_CALLBACK(refresh),&app);
  g_signal_connect(spb_snow, "value_changed", G_CALLBACK(refresh),&app);
  g_signal_connect(spb_swamp, "value_changed", G_CALLBACK(refresh),&app);

  //g_signal_connect(area, "draw", G_CALLBACK(on_draw), &rect);
  //g_signal_connect(area, "configure", G_CALLBACK(on_configure), &rect);

  gtk_main();

  return 0;
}
