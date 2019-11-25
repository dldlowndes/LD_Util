#include "rs232_wrap.h"

int main(){
    RS232_Wrap my_Comport("ttyS0", 9600, "8n1");

    return 0;
}
