# GameOfLife

This is my version of game of life simulation
It was done in five days after 3,5 month break in coding.
[wikipedia] (https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life)

##Instrucitons

You need to have Gtk installed on computer, I used Linux computer. I'm not sure that does it work on other computers or not.
[link to instllation instructions[]](https://www.gtk.org/docs/installations/linux)

To compile ja run the project load the src file, have Gtk on computer and use the following command

- g++ cell.h cell.cpp  field.h field.cpp main.cpp -o GOL `pkg-config --cflags --libs gtkmm-3.0`
- ./GOL
- have fun!
