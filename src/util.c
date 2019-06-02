#include "header/util.h"

size_t get_own_id_length(void) {
    size_t len = 1;
    if(_b2b_own_id > 9) {
        if(_b2b_own_id > 99) {
            len = 3;
        } else {
            len = 2;
        }
    } else {
        len = 1;
    }
    return len;
}