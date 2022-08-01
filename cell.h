#include <gtkmm.h>

class Cell {

    public:
        Cell();
        virtual ~Cell() {};

        bool isALive();
        bool alive;
        bool changed;
        int nabourgs_alive;
        Gtk::Button *button;
       
};