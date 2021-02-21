#ifndef GG_H
#define GG_H

#include <gtkmm.h>
#include <string>
#include "gg_classes.h"

/* Class for main window */
class Grocery_window: public Gtk::Window
{
public:
  Grocery_window();
  virtual ~Grocery_window();

  Store s1; // Store object is stored in the main window class
protected:

  /* Base */
  Gtk::Notebook notebook;

  /* Add Recipe */
  std::vector<Gtk::SpinButton*> add_recipe_spin;

  Gtk::ScrolledWindow add_recipe_scroll;
  Gtk::Grid grid_add_recipe;
  Gtk::VBox box_add_recipe;
  Gtk::Label add_recipe_label;
  Gtk::Label add_recipe_name_label;
  Gtk::Entry add_recipe_name;
  Gtk::Box ingredient_box;
  Gtk::Box button_box;
  Gtk::Button add_recipe_button;

  /* Add Ingredient */
  std::vector<Gtk::SpinButton*> add_ingred_spin;

  Gtk::ScrolledWindow add_ingred_scroll;
  Gtk::Grid grid_add_ingred;
  Gtk::VBox box_add_ingred;
  Gtk::Label add_ingred_label;
  Gtk::Label add_ingred_name_label;
  Gtk::Box ingred_list_box;
  Gtk::Box add_ingred_button_box;
  Gtk::Button add_ingred_button;

  /* View List */
  Gtk::VBox main_box;
  Gtk::VBox box_view_list;
  Gtk::VBox list_ingred_box;
  Gtk::ScrolledWindow view_list_scroll; //
  Gtk::Grid grid_view_list; // grid
  Gtk::Box print_list_button_box;
  Gtk::Label total_price_label;
  Gtk::Entry total_price_entry;

  Gtk::Label vl_title_label; // lbltitle
  Gtk::Button print_list_button; // btnPrintList
  Gtk::Image image; // logo
  Gtk::Label tab_name_label;

  std::vector <Gtk::Label*> all_ingred_lbl;
  std::vector <Gtk::Label*> all_amt_lbl;
  Gtk::VBox vbox_c1; // column1
  Gtk::VBox vbox_c2; // column2
  Gtk::Box box_top; // top
  Gtk::HBox hbox_view_list; // hbox

  /* Add recipe2list */

  std::vector<Gtk::SpinButton*> add_recipe2list_spin;
  Gtk::ScrolledWindow add_recipe2list_scroll;
  Gtk::Grid grid_add_recipe2list;
  Gtk::VBox box_add_recipe2list;
  Gtk::Label add_recipe2list_label;
  Gtk::Label add_recipe2list_name_label;
  Gtk::Box recipe2list_list_box;
  Gtk::Box add_recipe2list_button_box;
  Gtk::Button add_recipe2list_button;

  void add_recipe2list();

  void add_ingred();
  void write_list();
  void update_list(Ingredient);
  void update_recipes(Recipe);
  void add_recipe();
  void make_list();
  void print_list();

};




#endif
