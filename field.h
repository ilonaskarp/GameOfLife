#include <gtkmm.h>
#include <stdio.h>
#include <glib/gi18n.h>
#include <gtkmm/button.h>
#include <gtkmm/window.h>
#include <gtkmm/label.h>
#include <gtkmm/entry.h>
#include <gtkmm/widget.h>
#include <gtkmm/box.h>
#include <gtkmm/grid.h>
#include <vector>
#include "cell.h"

class Field : public Gtk::Window
{

public:
  Field();
  ~Field(){};

protected:
  int nro;
  std::vector<Cell> cells;
  int m_timer_number;
  const int count_value = 100;
  const int timeout_value = 2000;
  std::map<int, sigc::connection> m_timers;
  std::map<int, int> m_counters;
  void makeField(int n);
  void on_start_button_clicked();
  void on_button_clicked(int n);
  bool on_timeout(int m_timer_number);
  void setNabourgs();
  void checkAlive();
  void setButtonsOff();
  bool hasChanged();
  void iteration();
  void on_iterate_button_clicked();
  void on_automate_button_clicked();
  Gtk::Box *vbox_s;
  Gtk::Box *vbox;
  Gtk::Grid *grid; 
  Gtk::Button *button_n;
  Gtk::ScrolledWindow *scroller;
  Gtk::Entry *entry_s;
  Gtk::Button start_auto;
  Gtk::Button iterate;
  



};