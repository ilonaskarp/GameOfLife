 #include "cell.h"
 
Cell::Cell() {


}

bool Cell::isALive() {
    bool former = this->alive;

    if (nabourgs_alive == 3 || (nabourgs_alive == 2 && this->alive == true)) {
        this->alive = true;
    } else {
        this->alive = false;
    }
    if(former != this->alive) {
        changed = true;
    } else {
        changed = false;
    }
    return this->alive;
}
