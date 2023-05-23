//#include "../Generation/main.h" - placeholder, make header file for main so can be called for gtk
#include <gtk/gtk.h>
#include <stdlib.h>
#include <libintl.h>
#include <locale.h>

#include "Utils/generate.h"
#include "Utils/resize.h"
#include "../Generation/Options/exec_export.h"
#include "../Generation/Utils/options_map.h"
#include "../Generation/Utils/threshold.h"


typedef struct UserInterface
{
  GtkWindow* window;
  GtkImage* image;
  GtkSpinButton* width;
  GtkSpinButton* seed;
  GtkAdjustment* w;
  GtkAdjustment* seedix;
  GtkToggleButton *isrender3d;
  GtkToggleButton *island;
  GtkToggleButton *continent;
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
  struct available* available;
} UserInterface;

typedef struct {
    const char *id;
    const char *text;
} StringEntry;

const StringEntry strings_en[] = 
{
    {"Label1", "Generation options"},
    {"Label2", "Width"},
    {"Label3", "Height"},
    {"Label4", "Biome Tweaking"},
    {"Label5", "Display"},
    {"Label6", "Island Generation"},
    {"Label7", "Props"},
    {"Label8", "Rivers"},
    {"Label9", "Villages"},
    {"Label10", "Export to 3D"},
    {"Label11", "Exportation Mindustry"},
    {"Label12", "Height Tweaks"},
    {"Label13", "Deep ocean"},
    {"Label14", "Ocean"},
    {"Label15", "Coast"},
    {"Label16", "Beach"},
    {"Label17", "Plateau"},
    {"Label18", "Hills"},
    {"Label19", "Mountains"},
    {"Label20", "Peaks"},
    {"Label21", "Climate Tweaks"},
    {"Label22", "Snow"},
    {"Label23", "Plains"},
    {"Label24", "Savanna"},
    {"Label25", "Desert"},
    {"Label26", "Swamp"},
    {"generate", "Generate"},
    {"render_in_2D", "Render in 2D"},
    {"export_map", "Export Map"},
    {"render_in_3D", "Render in 3D"}
};

const StringEntry strings_fr[] = 
{
    {"Label1", "Options de génération"},
    {"Label2", "Largeur"},
    {"Label3", "Hauteur"},
    {"Label4", "Ajustements du biome"},
    {"Label5", "Affichage"},
    {"Label6", "Génération d'îles"},
    {"Label7", "Objets"},
    {"Label8", "Rivières"},
    {"Label9", "Villages"},
    {"Label10", "Exportation en 3D"},
    {"Label11", "Exportation Mindustry"},
    {"Label12", "Ajustement de la hauteur"},
    {"Label13", "Océan profond"},
    {"Label14", "Océan"},
    {"Label15", "Côte"},
    {"Label16", "Plage"},
    {"Label17", "Plateau"},
    {"Label18", "Collines"},
    {"Label19", "Montagnes"},
    {"Label20", "Pics enneigés"},
    {"Label21", "Ajustements du climat"},
    {"Label22", "Neige"},
    {"Label23", "Plaines"},
    {"Label24", "Savane"},
    {"Label25", "Désert"},
    {"Label26", "Marais"},
    {"generate", "Générer"},
    {"render_in_2D", "Rendu en 2D"},
    {"export_map", "Exporter la carte"},
    {"render_in_3D", "Rendu en 3D"}
};

typedef struct App
{
    UserInterface ui;
} App;

void set_image(GtkImage *image, const gchar* filename)
{

  resize(filename,"tmp/resized/resized.png",500,500);
  gtk_image_set_from_file(image,"tmp/resized/resized.png");

}

void on_generate_button_clicked(GtkButton *button, gpointer user_data)
{

  App *app = user_data; //recover App information

  GError *err = NULL;

  int width = gtk_adjustment_get_value(app->ui.w);
  int height = gtk_adjustment_get_value(app->ui.w);

  //g_print("w : %d \nh : %d\n",width,height);

  /*if(width == 0)
  {
    width = 500;
    height = 500;
  }*/

  if(gtk_toggle_button_get_active(app->ui.mindustry) && width != 500)
  {
    GtkDialogFlags flags = GTK_DIALOG_DESTROY_WITH_PARENT;
    GtkWidget* dialog = gtk_message_dialog_new (app->ui.window,
        flags,
        GTK_MESSAGE_ERROR,
        GTK_BUTTONS_CLOSE,
        "Error...\nThe size for Mindustry Map Export must be 500px but is %dpx",
        width);
    gtk_dialog_run (GTK_DIALOG (dialog));
    gtk_widget_destroy (dialog);
    return;
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

  struct available* a = app->ui.available;
  a->map = 1;
  a->model = gtk_toggle_button_get_active(app->ui.isrender3d);
  a->props = gtk_toggle_button_get_active(app->ui.props);
  a->river = gtk_toggle_button_get_active(app->ui.river);
  a->village = gtk_toggle_button_get_active(app->ui.villages);

  struct current_map* current_map = exec_ui(seedi, opt_alt, opt_temp, opt_hum, t, width, height,
            gtk_toggle_button_get_active(app->ui.island),
            gtk_toggle_button_get_active(app->ui.continent),
            gtk_toggle_button_get_active(app->ui.river),
            gtk_toggle_button_get_active(app->ui.props),
            gtk_toggle_button_get_active(app->ui.villages),
            gtk_toggle_button_get_active(app->ui.isrender3d),
            0,
            gtk_toggle_button_get_active(app->ui.mindustry),
            app->ui.seedix);
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

  if(gtk_toggle_button_get_active(app->ui.island))
  {
    GtkDialogFlags flags = GTK_DIALOG_DESTROY_WITH_PARENT;
    GtkWidget* dialog = gtk_message_dialog_new (app->ui.window,
                                      flags,
                                      GTK_MESSAGE_ERROR,
                                      GTK_BUTTONS_CLOSE,
                                      "Error...\nYou can't modify threshold for islands preset");
    gtk_dialog_run (GTK_DIALOG (dialog));
    gtk_widget_destroy (dialog);
    return;
  }

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

void export(char* source, GtkWindow* window)
{
  GtkWidget *dialog;
  GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_SAVE;
  gint res;
  dialog = gtk_file_chooser_dialog_new ("Choose File",
          window,
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
    save_to_png(load_image(source),filename);
    gchar string[200];
    g_snprintf(string,200,"Export :\n%s\nSuccess.",filename);
    GtkWidget* loaded = gtk_message_dialog_new(
    NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK,"%s",string);
    gtk_dialog_run(GTK_DIALOG(loaded));
    gtk_widget_destroy(loaded);
  }
  gtk_widget_destroy (dialog);
  
}

void export_files(GtkWidget *widget, gpointer data)
{
  App *app = data;
  struct available* a = app->ui.available;
  if(a->map)
  {
    GtkWidget *dialog;
    GtkDialogFlags flags = GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT;
    dialog = gtk_dialog_new_with_buttons ("Would you export the classic map ?",
                                      app->ui.window,
                                      flags,
                                      ("_OK"),
                                      GTK_RESPONSE_ACCEPT,
                                      ("_Cancel"),
                                      GTK_RESPONSE_REJECT,
                                      NULL);
    gint res = gtk_dialog_run (GTK_DIALOG (dialog));
    if(res == GTK_RESPONSE_ACCEPT)
      export("tmp/map.png",app->ui.window);
    gtk_widget_destroy (dialog);
    
  }

  if(a->props || a->river || a->village)
  {
    GtkWidget *dialog;
    GtkDialogFlags flags = GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT;
    dialog = gtk_dialog_new_with_buttons ("Would you export the map with options (Props, Villages, Rivers) ?",
                                      app->ui.window,
                                      flags,
                                      ("_OK"),
                                      GTK_RESPONSE_ACCEPT,
                                      ("_Cancel"),
                                      GTK_RESPONSE_REJECT,
                                      NULL);
    gint res = gtk_dialog_run (GTK_DIALOG (dialog));
    if(res == GTK_RESPONSE_ACCEPT)
      export("tmp/options.png",app->ui.window);
    gtk_widget_destroy (dialog);
    
  }

  if(a->model)
  {
    GtkWidget *dialog;
    GtkDialogFlags flags = GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT;
    dialog = gtk_dialog_new_with_buttons ("Would you export the map in 3D?",
                                      app->ui.window,
                                      flags,
                                      ("_OK"),
                                      GTK_RESPONSE_ACCEPT,
                                      ("_Cancel"),
                                      GTK_RESPONSE_REJECT,
                                      NULL);
    gint res = gtk_dialog_run (GTK_DIALOG (dialog));
    if(res == GTK_RESPONSE_ACCEPT)
      export("tmp/map.OBJ",app->ui.window);
    gtk_widget_destroy (dialog);
    
  }
}

void refresh_preset(GtkToggleButton *button, gpointer data)
{
  App *app = data;

  if(gtk_toggle_button_get_active(app->ui.island) &&
    gtk_toggle_button_get_active(app->ui.continent))
  {
    gtk_toggle_button_set_active(button,0);
    GtkDialogFlags flags = GTK_DIALOG_DESTROY_WITH_PARENT;
    GtkWidget* dialog = gtk_message_dialog_new (app->ui.window,
                                      flags,
                                      GTK_MESSAGE_ERROR,
                                      GTK_BUTTONS_CLOSE,
                                      "Error...\nYou can't check multiple presets\nPlease uncheck the preset");
    gtk_dialog_run (GTK_DIALOG (dialog));
    gtk_widget_destroy (dialog);
  }

  if(gtk_toggle_button_get_active(app->ui.continent))
  {
    struct threshold *t2 = threshold_continent();
    gtk_adjustment_set_value(app->ui.deep_ocean,t2->deep_ocean);
    gtk_adjustment_set_value(app->ui.ocean,t2->ocean);
    gtk_adjustment_set_value(app->ui.coast,t2->coast);
    gtk_adjustment_set_value(app->ui.beach,t2->beach);
    gtk_adjustment_set_value(app->ui.mid_mountains,t2->mid_mountains);
    gtk_adjustment_set_value(app->ui.mountains,t2->mountains);
    gtk_adjustment_set_value(app->ui.picks,t2->picks);
    gtk_adjustment_set_value(app->ui.plains,t2->plains);
    gtk_adjustment_set_value(app->ui.snow,t2->snow);
    gtk_adjustment_set_value(app->ui.savanna,t2->savanna);
    gtk_adjustment_set_value(app->ui.plateau,t2->plateau);
    gtk_adjustment_set_value(app->ui.swamp,t2->swamp);
    free(t2);
  }
}

void load_css(void)
{
    GtkCssProvider *provider = gtk_css_provider_new();
    GdkDisplay *display = gdk_display_get_default();
    GdkScreen *screen=gdk_display_get_default_screen(display);
    gchar *css_style_file = "style.css";
    GFile *css_fp = g_file_new_for_path(css_style_file);
    GError *error = 0;
    gtk_style_context_add_provider_for_screen(screen,
            GTK_STYLE_PROVIDER(provider),
            GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    gtk_css_provider_load_from_file(provider,css_fp,&error);
    g_object_unref(provider);
}

void set_language(const char *locale)     // ex *locale : fr_FR, en_US, ...
{
    setlocale(LC_ALL, locale);
    textdomain("BlendURMap");
}

/*void update_language(GtkBuilder *builder, const StringEntry strings[]) 
{
    for (int i = 0; strings[i].id != NULL; i++) 
    {
        const char *id = strings[i].id;
        const char *text = strings[i].text;
        GObject *widget = gtk_builder_get_object(builder, id);
        if (GTK_IS_LABEL(widget)) 
        {
            gtk_label_set_text(GTK_LABEL(widget), text);
        } 
        else if (GTK_IS_BUTTON(widget)) 
        {
            gtk_button_set_label(GTK_BUTTON(widget), text);
        }
    }
}

void on_change_language_button(GtkButton *button, gpointer user_data) 
{
    static gboolean in_french = FALSE;
    GtkBuilder *builder = GTK_BUILDER(user_data);

    if (in_french) 
    {
        update_language(builder, strings_en);
        in_french = FALSE;
    } else 
    {
        update_language(builder, strings_fr);
        in_french = TRUE;
    }
}*/

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

  load_css();

  GtkWindow* window = GTK_WINDOW(gtk_builder_get_object(builder, "org.gtk.UI"));

  GtkImage* image = GTK_IMAGE(gtk_builder_get_object(builder,"image"));

  GtkSpinButton* width = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"width"));
  GtkSpinButton* seed = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"seed"));

  GtkAdjustment* w = GTK_ADJUSTMENT(gtk_builder_get_object(builder,"Width"));
  GtkAdjustment* seedix = GTK_ADJUSTMENT(gtk_builder_get_object(builder,"Seedi"));

  GtkToggleButton* isrender3d = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder,"render"));
  GtkToggleButton* island = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder,"island"));
  GtkToggleButton* continent = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder,"continent"));
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

  struct available* a = malloc(sizeof(struct available));
  a->map = 0;
  a->model = 0;
  a->props = 0;
  a->river = 0;
  a->village = 0;


  App app =
    {
        .ui =
            {
                .window = window,
                .image = image,
                .render2d = render2d,
                .width = width,
                .seed = seed,
                .w = w,
                .seedix = seedix,
                .isrender3d = isrender3d,
                .island = island,
                .continent = continent,
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
                .available = a,
            },
    };

  set_image(image,"tmp/map.png");


  
  g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

  //g_signal_connect(isrender3d, "toggled", G_CALLBACK(render), NULL);
  g_signal_connect(generate_button, "clicked", G_CALLBACK(on_generate_button_clicked),&app);
  g_signal_connect(render2d, "clicked", G_CALLBACK(on_render_2D_clicked),&app);
  g_signal_connect(render3d, "clicked", G_CALLBACK(on_render_3D_clicked),&app);
  g_signal_connect(export_map, "clicked", G_CALLBACK(export_files),&app);

  g_signal_connect(island, "toggled", G_CALLBACK(refresh_preset),&app);
  g_signal_connect(continent, "toggled", G_CALLBACK(refresh_preset),&app);

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

  free(a);

  return 0;
}
