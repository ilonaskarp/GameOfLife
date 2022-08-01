#include <gtkmm/main.h>
#include "field.h"
//#include "field.h"
#include <gtkmm/application.h>
#include <gtkmm.h>
#include <iostream>
int main (int argc, char *argv[])
{

  auto app = Gtk::Application::create(argc, argv, "start");

  Field s;
  app->run(s);

  return 0;

}