#ifndef GG_CLASSES_H
#define GG_CLASSES_H

#include <string>

/* Store classes */

class Ingredient
{
public:
  std::string name;
  int qty;
  double price_pp; //price per package
  std::string image;

  Ingredient(std::string, int, double, std::string);
};

class Recipe
{
public:
  std::string name;
  std::vector<Ingredient> req_ingred;

  Recipe(std::string, std::vector<Ingredient>);
};

class Shopping_List
{
public:
  std::vector <Ingredient> shop_list;
  double total_price;

  void add_list(std::string s, int q);
  void add_from_recipe(Recipe r);
};

class Store
{
public:
  std::map <std::string, Ingredient> all_ingred;
  Shopping_List list1;
  std::vector <Recipe> all_recipes;

  void read_ingredients(std::string ingred_filename); // Reads from file ingredients.txt
  void read_recipes(std::string recipe_filename);     // Reads from file recipes.txt
  void write_recipe(std::string recipe_filename, Recipe recipe_to_add);     // Appends to file recipes.txt

  Store();
};

#endif
