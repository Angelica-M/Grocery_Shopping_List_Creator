#include "gg.h"
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char **argv)
{
  Gtk::Main app(argc, argv);
  Grocery_window w;
  Gtk::Main::run(w);
  return 0;
}
