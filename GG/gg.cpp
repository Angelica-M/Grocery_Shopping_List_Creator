#include "gg.h"

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iomanip>

Grocery_window::Grocery_window() : ingredient_box(Gtk::ORIENTATION_VERTICAL), box_add_recipe(Gtk::ORIENTATION_VERTICAL), ingred_list_box(Gtk::ORIENTATION_VERTICAL), recipe2list_list_box(Gtk::ORIENTATION_VERTICAL), box_add_recipe2list(Gtk::ORIENTATION_VERTICAL)
{
  set_title("Grocery Gang");
  set_border_width(10);
  resize(800, 600);
  add_recipe_scroll.set_border_width(30);
  box_add_recipe.set_homogeneous(false);

  notebook.set_tab_pos(Gtk::POS_TOP);

  /* ADD RECIPE tab */
  add_recipe_name_label.set_text("Recipe name:");
  add_recipe_label.set_text("Add Recipe");
  add_recipe_name.set_max_length(50);
  Gtk::Label* empty = new Gtk::Label("");
  Gtk::Label* empty_col = new Gtk::Label("\t ");
  grid_add_recipe.attach(*empty_col, 0, 0, 1, 2); // Adds some left padding
  grid_add_recipe.attach(*empty, 1, 0, 3, 1);
  grid_add_recipe.attach(add_recipe_name_label, 1, 1, 2, 1);
  grid_add_recipe.attach(add_recipe_name, 1, 2, 5, 1);
  box_add_recipe.pack_start(grid_add_recipe, false, false, 0);

  for (std::map<std::string, Ingredient>::iterator it = s1.all_ingred.begin(); it != s1.all_ingred.end(); it++) // Create the ingredient-picker box, make pointers of each element and pack into box
  {
    Glib::RefPtr<Gtk::Adjustment> adj = Gtk::Adjustment::create(0.0, 0.0, 100.0, 1.0, 1.0, 1.0);
    Gtk::Box* b = new Gtk::Box();
    Gtk::Image* im = new Gtk::Image(it->second.image);
    Gtk::Label* empty1 = new Gtk::Label("\t"); // Adds some padding between ingr. name and SpinButtons
    Gtk::Label* la = new Gtk::Label(it->second.name);
    Gtk::Label* empty2 = new Gtk::Label("\t"); // Adds some padding between ingr. name and SpinButtons
    Gtk::SpinButton* sp = new Gtk::SpinButton(adj); // SpinButton - entry with increment/decrement buttons
    Gtk::Separator* line = new Gtk::Separator(); // Separator line between each item
    b->pack_start(*im, false, true, 10);
    b->pack_start(*empty1, true, true, 0);
    b->pack_start(*la, false, true, 20);
    b->pack_start(*empty2, true, true, 0);
    b->pack_start(*sp, false, true, 0);
    add_recipe_spin.push_back(sp); // This will add all spin buttons to a vector, index corresponds to ingredient list
    ingredient_box.pack_start(*b, false, true, 0);
    ingredient_box.pack_start(*line, false, true, 0);
  }

  add_recipe_scroll.set_shadow_type(Gtk::SHADOW_ETCHED_IN);
  add_recipe_scroll.add(ingredient_box);
  box_add_recipe.pack_start(add_recipe_scroll, true, true, 5);
  add_recipe_button.set_label("\tAdd Recipe\t");
  add_recipe_button.signal_clicked().connect(sigc::mem_fun(*this, &Grocery_window::add_recipe));
  button_box.pack_end(add_recipe_button, false, false, 30);
  box_add_recipe.pack_start(button_box, false, false, 0);
  Gtk::Label* button_pad1 = new Gtk::Label("");
  box_add_recipe.pack_start(*button_pad1, false, false, 0);


  notebook.append_page(box_add_recipe, add_recipe_label); // Adds a tab with box_add_recipe as contents to the window with tab name from add_recipe_label

  /* ADD INGREDIENT tab */
	add_ingred_scroll.set_border_width(30);
	box_add_ingred.set_homogeneous(false);

	add_ingred_name_label.set_text("\nAdd the following ingredients to shopping list:");
	add_ingred_label.set_text("Add Ingredient to List");
	Gtk::Label* empty2 = new Gtk::Label("");
	Gtk::Label* empty_col2 = new Gtk::Label("\t ");
	grid_add_ingred.attach(*empty_col2, 0, 0, 1, 2); // Adds some left padding
	grid_add_ingred.attach(*empty2, 1, 0, 3, 1);
	grid_add_ingred.attach(add_ingred_name_label, 1, 1, 2, 1);
	box_add_ingred.pack_start(grid_add_ingred, false, false, 0);

	for (std::map<std::string, Ingredient>::iterator it = s1.all_ingred.begin(); it != s1.all_ingred.end(); it++) // might be ++it // WAS for (int i = 0; i < s1.all_ingred.size(); i++) WHEN all_ingred was a vector and not a map
	{
		Glib::RefPtr<Gtk::Adjustment> adj = Gtk::Adjustment::create(0.0, 0.0, 100.0, 1.0, 1.0, 1.0);
		Gtk::Box* b = new Gtk::Box();
		Gtk::Image* im = new Gtk::Image(it->second.image); // WAS Gtk::Image* im = new Gtk::Image(s1.all_ingred[i].image); WHEN all_ingred was a vector and not a map
		Gtk::Label* empty1 = new Gtk::Label("\t"); // Adds some padding between ingr. name and SpinButtons
		Gtk::Label* la = new Gtk::Label(it->second.name); // WAS Gtk::Label* la = new Gtk::Label(s1.all_ingred[i].name); WHEN all_ingred was a vector and not a map
		Gtk::Label* empty2 = new Gtk::Label("\t"); // Adds some padding between ingr. name and SpinButtons
		Gtk::SpinButton* sp = new Gtk::SpinButton(adj); // SpinButton - entry with increment/decrement buttons
		Gtk::Separator* line = new Gtk::Separator(); // Separator line between each item
		b->pack_start(*im, false, true, 10);
		b->pack_start(*empty1, true, true, 0);
		b->pack_start(*la, false, true, 20);
		b->pack_start(*empty2, true, true, 0);
		b->pack_start(*sp, false, true, 0);
		add_ingred_spin.push_back(sp); // This will add all spin buttons to a vector, index corresponds to ingredient list
		ingred_list_box.pack_start(*b, false, true, 0);
		ingred_list_box.pack_start(*line, false, true, 0);
	}

	add_ingred_scroll.set_shadow_type(Gtk::SHADOW_ETCHED_IN);
	add_ingred_scroll.add(ingred_list_box);
	box_add_ingred.pack_start(add_ingred_scroll, true, true, 5);
	add_ingred_button.set_label("Add to Shopping List");
	add_ingred_button.signal_clicked().connect(sigc::mem_fun(*this, &Grocery_window::add_ingred));
	add_ingred_button_box.pack_end(add_ingred_button, false, false, 30);
	box_add_ingred.pack_start(add_ingred_button_box, false, false, 0);
	Gtk::Label* button_pad2 = new Gtk::Label("");
	box_add_ingred.pack_start(*button_pad2, false, false, 0);

	notebook.append_page(box_add_ingred, add_ingred_label); // Adds a tab with box_add_ingred as contents to the window with tab name from add_ingred_label

  // ADD RECIPE TO LIST
	add_recipe2list_scroll.set_border_width(30);
	box_add_recipe2list.set_homogeneous(false);
	add_recipe2list_name_label.set_text("\nAdd the recipe's ingredients to shopping the list:");
	add_recipe2list_label.set_text("Add Recipe to List");
	Gtk::Label* empty4 = new Gtk::Label("");
	Gtk::Label* empty_col4 = new Gtk::Label("\t ");
	grid_add_recipe2list.attach(*empty_col4, 0, 0, 1, 2); // Adds some left padding
	grid_add_recipe2list.attach(*empty4, 1, 0, 3, 1);
	grid_add_recipe2list.attach(add_recipe2list_name_label, 1, 1, 2, 1);
	box_add_recipe2list.pack_start(grid_add_recipe2list, false, false, 0);

	for (int i = 0; i < s1.all_recipes.size(); i++) // might be ++it // WAS for (int i = 0; i < s1.all_recipes.size(); i++) WHEN all_recipes was a vector and not a map
	{

		Glib::RefPtr<Gtk::Adjustment> portions = Gtk::Adjustment::create(0.0, 0.0, 100.0, 1.0, 1.0, 1.0);
		Gtk::Box* bb = new Gtk::Box();
		Gtk::Label* pad1 = new Gtk::Label("\t");
		Gtk::Label* la = new Gtk::Label(s1.all_recipes[i].name);
		Gtk::Label* pad2 = new Gtk::Label("\t");
		Gtk::SpinButton* spin = new Gtk::SpinButton(portions);
		Gtk::Separator* line1 = new Gtk::Separator();
		bb->pack_start(*pad1, true, true, 0);
		bb->pack_start(*la, false, true, 20);
		bb->pack_start(*pad2, true, true, 0);
		bb->pack_start(*spin, false, true, 0);
		add_recipe2list_spin.push_back(spin); // This will add all spin buttons to a vector, index corresponds to ingredient list
		recipe2list_list_box.pack_start(*bb, false, true, 0);
		recipe2list_list_box.pack_start(*line1, false, true, 0);
	}

	add_recipe2list_scroll.set_shadow_type(Gtk::SHADOW_ETCHED_IN);
	add_recipe2list_scroll.add(recipe2list_list_box);
	box_add_recipe2list.pack_start(add_recipe2list_scroll, true, true, 5);
	add_recipe2list_button.set_label("Add to Shopping List");
	add_recipe2list_button.signal_clicked().connect(sigc::mem_fun(*this, &Grocery_window::add_recipe2list));
	add_recipe2list_button_box.pack_end(add_recipe2list_button, false, false, 30);
	box_add_recipe2list.pack_start(add_recipe2list_button_box, false, false, 0);
	Gtk::Label* button_pad4 = new Gtk::Label("");
	box_add_recipe2list.pack_start(*button_pad4, false, false, 0);

	notebook.append_page(box_add_recipe2list, add_recipe2list_label);

  /* VIEW LIST tab */

  view_list_scroll.set_border_width(30);
  box_view_list.set_homogeneous(false);
	//set label and buttons texts
	tab_name_label.set_text("View Shopping List");
	vl_title_label.set_text("\nYour Grocery Gang shopping list:");
	print_list_button.set_label("Print List");
  Gtk::Label* empty_list = new Gtk::Label("");
  Gtk::Label *empty_col_list = new Gtk::Label("\t ");
  grid_view_list.attach(*empty_col_list, 0, 0, 1, 2);
  grid_view_list.attach(*empty_list, 1, 0, 3 ,1);
  grid_view_list.attach(vl_title_label, 1, 1, 2, 1);
  box_view_list.pack_start(grid_view_list, false, false, 0);

  make_list();

  view_list_scroll.set_shadow_type(Gtk::SHADOW_ETCHED_IN);
  view_list_scroll.add(list_ingred_box);

  box_view_list.pack_start(view_list_scroll, true, true, 5);

	//setting up the general layout

	grid_view_list.show_all();
	print_list_button.signal_clicked().connect(sigc::mem_fun(*this, &Grocery_window::print_list));
  total_price_entry.set_text("$0.00");
  total_price_entry.set_sensitive(false);
  total_price_label.set_text("Total Price: ");
  print_list_button_box.pack_start(total_price_label, false, false, 30);
  print_list_button_box.pack_start(total_price_entry, false, false, 30);
  print_list_button_box.pack_end(print_list_button, false, false, 30);
  box_view_list.pack_start(print_list_button_box, false, false, 0);
  Gtk::Label* button_pad3 = new Gtk::Label("");
  box_view_list.pack_start(*button_pad3, false, false, 0);

  notebook.append_page(box_view_list, tab_name_label); // Adds a tab with grid_view_list as contents to the window with tab name from tab_name_label

  add(notebook);

  set_icon_from_file("logo.png");

  show_all_children();
}

void Grocery_window::make_list() // DEPRECATED : DO NOT USE THIS FUNCTION, CAUSES REDUNDANCY
{
  /*
  for (int i = 0; i < s1.list1.shop_list.size(); i++)
  {
    Gtk::Box* b = new Gtk::Box();
    Gtk::Image* im = new Gtk::Image(s1.list1.shop_list[i].image);
    Gtk::Label* empty1 = new Gtk::Label("\t");
    Gtk::Label* la = new Gtk::Label(s1.list1.shop_list[i].name);
    Gtk::Label* empty2 = new Gtk::Label("\t");
    Gtk::Separator* line = new Gtk::Separator(); // Separator line between each item
    b->pack_start(*im, false, true, 10);
    b->pack_start(*empty1, true, true, 0);
    b->pack_start(*la, false, true, 20);
    b->pack_start(*empty2, true, true, 0);

    list_ingred_box.pack_start(*b, false, true, 0);
    list_ingred_box.pack_start(*line, false, true, 0);
  }
  */
}

void Grocery_window::update_list(Ingredient ing_to_add)
{
  std::ostringstream out;
  std::string qty_string;
  out << ing_to_add.qty;
  qty_string = out.str();

  Gtk::Box* b = new Gtk::Box();
  Gtk::Image* im = new Gtk::Image(ing_to_add.image);
  Gtk::Label* empty1 = new Gtk::Label("\t");
  Gtk::Label* la = new Gtk::Label(ing_to_add.name);
  Gtk::Label* empty2 = new Gtk::Label("\t");
  Gtk::Label* qty = new Gtk::Label(qty_string);
  Gtk::Separator* line = new Gtk::Separator(); // Separator line between each item
  b->pack_start(*im, false, true, 10);
  b->pack_start(*empty1, true, true, 0);
  b->pack_start(*la, false, true, 20);
  b->pack_start(*empty2, true, true, 0);
  b->pack_start(*qty, false, true, 40);
  list_ingred_box.pack_start(*b, false, true, 0);
  list_ingred_box.pack_start(*line, false, true, 0);

  list_ingred_box.show_all_children();

  // Update the total price
  double total_cost = 0;
  double curr_qty;
  double curr_price_pp;
  for (int i = 0; i < s1.list1.shop_list.size(); i++)
  {
    curr_qty = (double) s1.list1.shop_list[i].qty;
    curr_price_pp = s1.list1.shop_list[i].price_pp;
    total_cost += curr_qty * curr_price_pp;
  }
  s1.list1.total_price = total_cost;

  // Update the Entry in GUI
  std::ostringstream out_cost;
  std::string cost_string;
  out_cost << "$" << std::fixed << std::setprecision(2) << total_cost;
  cost_string = out_cost.str();

  total_price_entry.set_text(cost_string);
}

void Grocery_window::update_recipes(Recipe recipe_to_add)
{
  Glib::RefPtr<Gtk::Adjustment> portions = Gtk::Adjustment::create(0.0, 0.0, 100.0, 1.0, 1.0, 1.0);
  Gtk::Box* bb = new Gtk::Box();
  Gtk::Label* pad1 = new Gtk::Label("\t");
  Gtk::Label* la = new Gtk::Label(recipe_to_add.name);
  Gtk::Label* pad2 = new Gtk::Label("\t");
  Gtk::SpinButton* spin = new Gtk::SpinButton(portions);
  Gtk::Separator* line1 = new Gtk::Separator();
  bb->pack_start(*pad1, true, true, 0);
  bb->pack_start(*la, false, true, 20);
  bb->pack_start(*pad2, true, true, 0);
  bb->pack_start(*spin, false, true, 0);
  add_recipe2list_spin.push_back(spin); // This will add all spin buttons to a vector, index corresponds to ingredient list
  recipe2list_list_box.pack_start(*bb, false, true, 0);
  recipe2list_list_box.pack_start(*line1, false, true, 0);

  recipe2list_list_box.show_all_children();
}

void Grocery_window::add_recipe()
{
  //Create a recipe object using non-zero ingredients from add_recipe_spin, name from add_recipe_name.get_text()
  //This will append to recipe file the new recipe, open a dialog box confirming the recipe was added, and reset all spin buttons and entry

  //Check if recipe name is empty. If it is, error: recipe name cannot be empty and return
  if (add_recipe_name.get_text().compare("") == 0)
  {
    Gtk::MessageDialog dialog(*this, "Error: Could not add recipe",false,Gtk::MESSAGE_ERROR);
    dialog.set_secondary_text("Recipe name cannot be blank.");
    dialog.run();
    return;
  }

  //Create object and check if ingredients is empty, if it is, error: ingredient list cannot be empty and return
  bool list_not_empty = false;
  for (int i = 0; i < add_recipe_spin.size(); i++)
  {
    if (add_recipe_spin.at(i)->get_value() != 0.0)
      list_not_empty = true;
  }

  if (!list_not_empty)
  {
    Gtk::MessageDialog dialog(*this, "Error: Could not add recipe",false,Gtk::MESSAGE_ERROR);
    dialog.set_secondary_text("You must add at least one ingredient to the recipe.");
    dialog.run();
    return;
  }
  //If the above 2 conditions false, append to file
  std::vector<Ingredient> all_current_ingredients;
  int ing_qty;
  int it_count = 0;
  for (std::map<std::string, Ingredient>::iterator it1 = s1.all_ingred.begin(); it1 != s1.all_ingred.end(); it1++)
  {
    if (add_recipe_spin.at(it_count)->get_value() != 0.0)
    {
      ing_qty = (int) add_recipe_spin.at(it_count)->get_value();
      Ingredient current_ingredient(it1->second.name, ing_qty, it1->second.price_pp, it1->second.image);
      all_current_ingredients.push_back(current_ingredient);
    }
    it_count++;
  }
  Recipe add_from_ing(add_recipe_name.get_text(), all_current_ingredients);
  s1.write_recipe("recipes.txt", add_from_ing);
  s1.all_recipes.clear();           // Resets the recipe vector
  s1.read_recipes("recipes.txt");   // Reads from recipe again to update

  update_recipes(add_from_ing);

  /* ############# Add code to update your window elements here ############# */
  /* ############# Add code to update your window elements here ############# */
  /* ############# Add code to update your window elements here ############# */

  // Confirmation dialog
  std::ostringstream out;
  std::string output;
  out << add_recipe_name.get_text() << " was added to the list of recipes.";
  output = out.str();
  Gtk::MessageDialog dialog(*this, "Recipe Added",false,Gtk::MESSAGE_INFO);
  dialog.set_secondary_text(output);
  dialog.run();

  //Reset spin buttons & entry
  for (int i = 0; i < add_recipe_spin.size(); i++)
  {
    add_recipe_spin.at(i)->set_value(0.0);
  }

  add_recipe_name.set_text("");
}

void Grocery_window::add_recipe2list()
{
  bool list_not_empty = false;
  for (int i = 0; i < add_recipe2list_spin.size(); i++)
  {
    if (add_recipe2list_spin.at(i)->get_value() != 0.0)
      list_not_empty = true;
  }

  if (!list_not_empty)
  {
    Gtk::MessageDialog dialog(*this, "Error: Could not add to list",false,Gtk::MESSAGE_ERROR);
    dialog.set_secondary_text("You must select at least one recipe to add.");
    dialog.run();
    return;
  }

  for (int i = 0; i < add_recipe2list_spin.size(); i++)
  {
    if (add_recipe2list_spin[i]->get_value() != 0.0)
    {
      int portion = add_recipe2list_spin[i]->get_value();
      Recipe curr_recipe = s1.all_recipes[i];
      for (int j = 0; j < curr_recipe.req_ingred.size(); j++)
      {
        Ingredient curr_ingredient = curr_recipe.req_ingred[j];
        // Multiply by portion size
        curr_ingredient.qty *= portion;
        s1.list1.shop_list.push_back(curr_ingredient);
        update_list(curr_ingredient); // Updates the GUI
      }
    }
  }

  Gtk::MessageDialog dialog(*this, "Recipe added to list",false,Gtk::MESSAGE_INFO);
  dialog.set_secondary_text("Selected recipe ingredients have been added to your shopping list");
  dialog.run();

  // Reset the spin buttons
  for (int i = 0; i < add_recipe2list_spin.size(); i++)
  {
      add_recipe2list_spin.at(i)->set_value(0.0);
  }
}



//void Grocery_window::add_recipe() {} // Angelica's code
void Grocery_window::add_ingred()
{
  bool list_not_empty = false;
  for (int i = 0; i < add_ingred_spin.size(); i++)
  {
    if (add_ingred_spin.at(i)->get_value() != 0.0)
      list_not_empty = true;
  }

  if (!list_not_empty)
  {
    Gtk::MessageDialog dialog(*this, "Error: Could not add to list",false,Gtk::MESSAGE_ERROR);
    dialog.set_secondary_text("You must indicate at least one ingredient to add.");
    dialog.run();
    return;
  }

  int ing_qty;
	int it_count = 0; // ERROR: it_count was not declared
	for (std::map<std::string, Ingredient>::iterator it1 = s1.all_ingred.begin(); it1 != s1.all_ingred.end(); it1++)
	{
		if (add_ingred_spin.at(it_count)->get_value() != 0.0)
		{
			ing_qty = (int) add_ingred_spin.at(it_count)->get_value();
			Ingredient current_ingredient(it1->second.name, ing_qty, it1->second.price_pp, it1->second.image);
			s1.list1.shop_list.push_back(current_ingredient);
      update_list(current_ingredient);
		}
		it_count++;
	}

  //UPDATE THE List

  make_list();

  Gtk::MessageDialog dialog(*this, "Ingredients Added",false,Gtk::MESSAGE_INFO);
  dialog.set_secondary_text("Selected ingredients were added to shopping list");
  dialog.run();

  // Reset the spin buttons
  for (int i = 0; i < add_ingred_spin.size(); i++)
  {
    add_ingred_spin.at(i)->set_value(0.0);
  }
}

void Grocery_window::write_list()
{}


Grocery_window::~Grocery_window(){}

Ingredient::Ingredient(std::string n, int q, double p, std::string i)
{
  this->name = n;
  this->qty = q;
  this->price_pp = p;
  this->image = i;
}

Recipe::Recipe(std::string n, std::vector<Ingredient> all_ingred)
{
  this->name = n;
  this->req_ingred = all_ingred;
}

// Default constructor for store class
Store::Store()
{
  read_ingredients("ingredients.txt");
  read_recipes("recipes.txt");
}

void Store::write_recipe(std::string filename, Recipe recipe_to_add)
{
    std::ofstream file_out;
    std::ostringstream out;
    std::string output;

    out << recipe_to_add.name << "/"; // Write name of recipe
    for (int i = 0; i < recipe_to_add.req_ingred.size() - 1; i++)
    {
      out << recipe_to_add.req_ingred.at(i).name << "." << recipe_to_add.req_ingred.at(i).qty << ",";
    }

    out << recipe_to_add.req_ingred.at(recipe_to_add.req_ingred.size() - 1).name << "." << recipe_to_add.req_ingred.at(recipe_to_add.req_ingred.size() - 1).qty;
    out << std::endl;

    output = out.str();
    file_out.open(filename, std::ios_base::app);
    file_out << output;
}

void Grocery_window::print_list()
{
  std::ofstream ggList;
  ggList.open("SL.txt");
  ggList<<"~~~Shopping List by GG~~~\n\n";

  ggList<<"Amount\tIngredient\n";

  for(int i=0; i<s1.list1.shop_list.size(); i++)
  {
   ggList<<std::to_string(s1.list1.shop_list.at(i).qty)<<"\t"<<s1.list1.shop_list.at(i).name << std::endl;
  }

  ggList<<std::endl<<std::endl<< "Total Price: $" << s1.list1.total_price;
  ggList.close();

  Gtk::MessageDialog dialog(*this, "Shopping List Printed",false,Gtk::MESSAGE_INFO);
  dialog.set_secondary_text("Shopping list printed to file.");
  dialog.run();

  // Reset the shopping list GUI
  std::vector<Widget*> all_children = list_ingred_box.get_children();
  for (int i = 0; i < all_children.size(); i++)
  {
    list_ingred_box.remove(*all_children[i]);
  }

  // Reset the shopping list vector
  s1.list1.shop_list.clear();

  // Reset the total price and GUI Entry
  s1.list1.total_price = 0.0;
  total_price_entry.set_text("$0.00");


}

void Store::read_ingredients(std::string filename)
{
  std::ifstream file_in;
  std::string line, name, price_string, image;
  double price;

  file_in.open(filename);

  if (!file_in.is_open())
  {
    std::cout << "Error: Ingredients file could not be opened" << std::endl;
    exit(1);
  }

  while (!file_in.eof())
  {
    std::getline(file_in, line);
    if (!line.empty())
    {
      std::stringstream token(line);
      std::getline(token, name, ',');
      std::getline(token, price_string, ',');
      std::getline(token, image); //','

      if (image[image.length()-1] == '\r' || image[image.length()-1] == '\n')
      {
        image.erase(image.length()-1); // Remove the return carriage character
      }

      image = "./images/" + image;  // Ingredient images stored in 'images' folder

      price = stof(price_string);
      Ingredient curr_ing(name, 1, price, image); // Default quantity is 1
      all_ingred.insert(std::pair<std::string, Ingredient>(name, curr_ing));
    }
  }
}

void Store::read_recipes(std::string filename)
{
  std::ifstream file_in;
  std::string line, name, all_ing_string, curr_ing, curr_name, quantity_string;
  int quantity;

  file_in.open(filename);

  if (!file_in.is_open())
  {
    std::cout << "Error: Recipes file could not be opened" << std::endl;
    exit(1);
  }

  while (!file_in.eof())
  {
    std::getline(file_in, line);
    if (!line.empty())
    {
      std::vector<std::string> ing_strings;
      std::vector<Ingredient> curr_recipe_ing;
      std::stringstream token(line);
      std::getline(token, name, '/');   //  Apple Pie

      std::getline(token, all_ing_string);

      std::stringstream ing_stream(all_ing_string);

      while(ing_stream.good()) // bool good - Check whether state of stream is good
      {
        std::string substr;
        getline(ing_stream, substr, ','); // apple.3
        ing_strings.push_back(substr);
      }

      for (int i = 0; i < ing_strings.size(); i++)
      {
        std::stringstream vector_tok(ing_strings[i]);
        std::getline(vector_tok, curr_name, '.');  // apple
        std::getline(vector_tok, quantity_string); // 3
        quantity = stoi(quantity_string);

        Ingredient curr_ing = all_ingred.at(curr_name);
        curr_ing.qty = quantity;

        curr_recipe_ing.push_back(curr_ing);
      }

      Recipe curr_recipe(name, curr_recipe_ing);
      all_recipes.push_back(curr_recipe);

    }
  }
}
