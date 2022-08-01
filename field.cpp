#include "field.h"
#include <gtkmm.h>
#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>
#include <cstdlib>

Field::Field (){

   set_title("Game of life");
    set_default_size(1000, 1000);
    vbox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 0));

    add(*vbox);

    grid = Gtk::manage(new Gtk::Grid());

    button_n = Gtk::manage(new Gtk::Button{"Start"});
        

    button_n->override_background_color(Gdk::RGBA("red"));
    
    button_n->signal_clicked().connect(sigc::mem_fun(*this, &Field::on_start_button_clicked));
    
    grid->attach(*button_n, 1, 5);
    
    entry_s = Gtk::manage(new Gtk::Entry());

    entry_s->set_text("7");

    grid->attach(*entry_s, 1, 10);

     Gtk::ScrolledWindow* scroller_s = Gtk::manage(new Gtk::ScrolledWindow);

    scroller_s->set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_ALWAYS);


   
    scroller_s->add(*grid);

    scroller_s->set_hexpand(true);

    scroller_s->set_vexpand(true);

    vbox->add(*scroller_s);

    vbox->show_all();
    
}
void Field::on_start_button_clicked() {

    std::string nro = entry_s->get_text();

    int n = std::stoi(nro);
    makeField(n);

}
void Field::makeField(int n) {

  this-> nro = n;

  int nro_n = 0;
    for(int i=0; i<  this->nro; ++i) {

        for(int j=0; j< this->nro; ++j) {

           
            Cell cell;
            std::string nro_s = std::to_string((nro_n+1));

            Gtk::Button *button  = Gtk::manage(new Gtk::Button{nro_s});;
            
            
            button->override_background_color(Gdk::RGBA("black"),Gtk::STATE_FLAG_NORMAL);
      
            button->signal_clicked().connect(

             [this, nro_n] {this->on_button_clicked(nro_n);});

            grid->attach(*button, j +10, i +10, 1, 1);

            cell.button = button;
            cell.nabourgs_alive = 0;
            cell.alive = false;
            cells.push_back(cell);
            nro_n ++;

        }
    }
         Gtk::Button* automate = Gtk::manage(new Gtk::Button{"Start automate"});

         automate->signal_clicked().connect(

                [this] {this->on_automate_button_clicked();});



         grid->attach(*automate, nro +11, nro +11);

         Gtk::Button* iterate = Gtk::manage(new Gtk::Button{"Iterate"});

         iterate->signal_clicked().connect(

                [this] {this->on_iterate_button_clicked();});


         grid->attach(*iterate, nro+11, nro +12);

    vbox->show_all();

}



void Field::on_button_clicked(int n) {

  if(!cells[n].alive) {
    cells[n].button->override_background_color(Gdk::RGBA("green"),Gtk::STATE_FLAG_NORMAL);
    cells[n].alive = true;
    cells[n].changed = true;
  } else {
    cells[n].button->override_background_color(Gdk::RGBA("black"),Gtk::STATE_FLAG_NORMAL);
    cells[n].alive = false;
    cells[n].changed = false;
  }
}



void Field::setNabourgs(){

  // int n = 0;
    for(int i = 0; i < nro; i++) {
        for(int j = 0; j <nro; j++) {
          
           //std::cout <<n << ":"<< cells[n].nabourgs_alive << std::endl;
            if(i > 0 && i < nro-1 && j>0 && j < nro-1) {
              
                if(cells[j + (i * nro)].alive==true  && cells[j + (i * nro)].changed==true) {
                    cells[j + (i * nro)-nro-1].nabourgs_alive++;
                    cells[j + (i * nro)-nro].nabourgs_alive++;
                    cells[j + (i * nro)-nro+1].nabourgs_alive++;
                    cells[j + (i * nro)+1].nabourgs_alive++;
                    cells[j + (i * nro)+nro+1].nabourgs_alive++;
                    cells[j + (i * nro)+nro].nabourgs_alive++;
                    cells[j + (i * nro)+nro-1].nabourgs_alive++;
                    cells[j + (i * nro)-1].nabourgs_alive++;
                } else if(cells[j + (i * nro)].alive==false && cells[j + (i * nro)].changed==true) {
                    cells[j + (i * nro)-nro-1].nabourgs_alive--;
                    cells[j + (i * nro)-nro].nabourgs_alive--;
                    cells[j + (i * nro)-nro+1].nabourgs_alive--;
                    cells[j + (i * nro)+1].nabourgs_alive--;
                    cells[j + (i * nro)+nro+1].nabourgs_alive--;
                    cells[j + (i * nro)+nro].nabourgs_alive--;
                    cells[j + (i * nro)+nro-1].nabourgs_alive--;
                    cells[j + (i * nro)-1].nabourgs_alive--;
                }
              } 
              if(i == 0 && j == 0) {
                  if(cells[j + i*nro].alive==true&& cells[j+ i*nro].changed==true) {
                    cells[j+ i*nro +1].nabourgs_alive++;
                    cells[j+ i*nro+nro].nabourgs_alive++;
                    cells[j+ i*nro+nro+1].nabourgs_alive++;
                  } else if(cells[j+ i*nro].alive==false&& cells[j+ i*nro].changed==true) {
                    cells[j+ i*nro+1].nabourgs_alive--;
                    cells[j+ i*nro+nro].nabourgs_alive--;
                    cells[j+ i*nro+nro+1].nabourgs_alive--;
                  }
                } 
                if(i==nro-1 && j == nro-1) {
                  if(cells[j+ i*nro].alive==true &&  cells[j+ i*nro].changed==true) {
                     cells[j+ i*nro-nro].nabourgs_alive++;
                     cells[j+ i*nro-nro-1].nabourgs_alive++;
                     cells[j+ i*nro-1].nabourgs_alive++;
                  } else if(cells[j+ i*nro].alive==false&& cells[j+ i*nro].changed==true ) {
                     cells[j+ i*nro-nro].nabourgs_alive--;
                     cells[j+ i*nro-nro-1].nabourgs_alive--;
                     cells[j+ i*nro-1].nabourgs_alive--;
                  }
                } 
                if(i == 0 && j == nro-1 ) {
                  if(cells[j+ i*nro].alive==true && cells[j+ i*nro].changed==true) {
                     cells[j+ i*nro+nro].nabourgs_alive++;
                     cells[j+ i*nro+nro-1].nabourgs_alive++;
                      cells[j+ i*nro-1].nabourgs_alive++;
                  } else if(cells[j+ i*nro].alive==false && cells[j+ i*nro].changed==true) {
                     cells[j+ i*nro+nro].nabourgs_alive--;
                     cells[j+ i*nro+nro-1].nabourgs_alive--;
                      cells[j+ i*nro-1].nabourgs_alive--;
                  }
                }
                if (i == nro -1 && j == 0) {
                  if(cells[j+ i*nro].alive==true && cells[j+ i*nro].changed==true) {
                    cells[j+ i*nro+1].nabourgs_alive++;
                     cells[j+ i*nro-nro+1].nabourgs_alive++;
                      cells[j+ i*nro-nro].nabourgs_alive++;
                  } else  if(cells[j+ i*nro].alive==false && cells[j+ i*nro].changed==true) {
                    cells[j+ i*nro+1].nabourgs_alive--;
                     cells[j+ i*nro-nro+1].nabourgs_alive--;
                      cells[j+ i*nro-nro].nabourgs_alive--;
                  }
                } 
                if(i == 0 && (j > 0 && j < nro-1)) {
                  if(cells[j+ i*nro].alive==true && cells[j+ i*nro].changed==true) {
                       cells[j+ i*nro-1].nabourgs_alive++;
                        cells[j+ i*nro+1].nabourgs_alive++;
                         cells[j+ i*nro+nro-1].nabourgs_alive++;
                        cells[j+ i*nro+nro].nabourgs_alive++; 
                    cells[j+ i*nro+nro+1].nabourgs_alive++;
                  } else if(cells[j+ i*nro].alive==false && cells[j+ i*nro].changed==true) {
                       cells[j+ i*nro-1].nabourgs_alive--;
                        cells[j+ i*nro+1].nabourgs_alive--;
                         cells[j+ i*nro+nro-1].nabourgs_alive--;
                        cells[j+ i*nro+nro].nabourgs_alive--; 
                    cells[j+ i*nro + nro+1].nabourgs_alive--;
                  }
                }
                if ((i >0 && i <nro-1 ) && j == 0) {
                  if(cells[j+ i*nro].alive==true && cells[j+ i*nro].changed==true) {
                    cells[j+ i*nro-nro].nabourgs_alive++;
                     cells[j+ i*nro-nro+1].nabourgs_alive++;
                     cells[j+ i*nro+1].nabourgs_alive++;
                     cells[j+ i*nro+nro].nabourgs_alive++;
                    cells[j+ i*nro+nro+1].nabourgs_alive++;
                  } else if(cells[j+ i*nro].alive==false && cells[j+ i*nro].changed==true) {
                    cells[j+ i*nro-nro].nabourgs_alive--;
                     cells[j+ i*nro-nro+1].nabourgs_alive--;
                     cells[j+ i*nro+1].nabourgs_alive--;
                     cells[j+ i*nro+nro].nabourgs_alive--;
                    cells[j+ i*nro+nro+1].nabourgs_alive--;
                  }
                }
                if(i == nro-1 && (j > 0 && j < nro-1)) {
                  if(cells[j+ i*nro].alive==true && cells[j+ i*nro].changed==true) {
                    cells[j+ i*nro-nro-1].nabourgs_alive++;
                     cells[j+ i*nro-nro].nabourgs_alive++;
                       cells[j+ i*nro-nro+1].nabourgs_alive++;
                        cells[j+ i*nro -1].nabourgs_alive++;
                        cells[j+ i*nro +1].nabourgs_alive++;
                  } else if(cells[j+ i*nro].alive==false && cells[j+ i*nro].changed==true) {
                    cells[j+ i*nro-nro-1].nabourgs_alive--;
                     cells[j+ i*nro-nro].nabourgs_alive--;
                       cells[j+ i*nro-nro+1].nabourgs_alive--;
                        cells[j+ i*nro -1].nabourgs_alive--;
                        cells[j+ i*nro+1].nabourgs_alive--;
                  }
                } 
                if ((i >0 && i <nro-1 ) && j == nro-1){
                  if(cells[j+ i*nro].alive==true  && cells[j+ i*nro].changed==true) {
                      cells[j+ i*nro-nro-1].nabourgs_alive++;
                       cells[j+ i*nro-nro].nabourgs_alive++;
                       cells[j+ i*nro-1].nabourgs_alive++;
                       cells[j+ i*nro+nro-1].nabourgs_alive++;
                       cells[j+ i*nro+nro].nabourgs_alive++;
                  } else if(cells[j+ i*nro].alive==false  && cells[j+ i*nro].changed==true) {
                      cells[j+ i*nro-nro-1].nabourgs_alive--;
                       cells[j+ i*nro-nro].nabourgs_alive--;
                       cells[j+ i*nro-1].nabourgs_alive--;
                       cells[j+ i*nro+nro-1].nabourgs_alive--;
                       cells[j+ i*nro+nro].nabourgs_alive--;
                  }
                }
            // n++;
            }
        }
}

           
            void Field::checkAlive() {

  int n = 0;
    for(int i = 0; i < this->nro; i++) {
      for(int j = 0; j < this->nro; j++) {
          if(cells[n].isALive()==true) {
             cells[n].button->set_sensitive(true);
             cells[n].button->override_background_color(Gdk::RGBA("green"),Gtk::STATE_FLAG_NORMAL);
             cells[n].button->set_sensitive(false);
          } else {
              cells[n].button->set_sensitive(true);
              cells[n].button->override_background_color(Gdk::RGBA("black"),Gtk::STATE_FLAG_NORMAL);
              cells[n].button->set_sensitive(false);
     
          }
          n++;
      }
    }

}


void Field::setButtonsOff() {
  int n = 0;
  for(int i = 0; i < this->nro; i++) {
    for(int j = 0; j < this->nro; j++) {
      cells[n].button->set_sensitive(false);
      n++;
    }
  }
  button_n->hide();
  entry_s -> hide();

}

bool Field::hasChanged() {
  int n = 0;
  bool hasChanged = false;
  for(int i = 0; i < this->nro; i++) {
    for(int j = 0; j < this->nro; j++) {
      if(cells[n].changed == true) {
        hasChanged = true;
        break;
      }
      n++;
    }
  }
  return hasChanged;
}
void Field::iteration() {

   if(hasChanged()==true) {
      setNabourgs();
      checkAlive();
    }

}
 void Field::on_iterate_button_clicked() {
  
    setButtonsOff();
    iteration();
    
} 

bool Field::on_timeout(int m_timer_number)
{
 
 
  if (hasChanged() == false)
  {
    
    return false;
  }
  m_timer_number++;
  iteration();
  return true;
}
 
 void Field::on_automate_button_clicked ()
{       setButtonsOff();
        
        sigc::slot<bool()> my_slot = sigc::bind(sigc::mem_fun(*this,
              &Field::on_timeout), 0);

    auto conn = Glib::signal_timeout().connect(my_slot,
          timeout_value);

           m_timers[m_timer_number] = conn;

  // Initialize timer count:
  m_counters[m_timer_number] = count_value + 1;

}




    
    
    



     