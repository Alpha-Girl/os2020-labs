/* IO operations */
unsigned char inb(unsigned short int port_from){
    unsigned char _in_value;

    /* something for __asm__
    %w1: w=word
    read a byte from port %w1 to %0
    "=a": read-only, get value from eax/ax/al
    "d": set value to edx/da/dl
    */
    __asm__ __volatile__ ("inb %w1,%0":"=a"(_in_value):"Nd"(port_from));

    return _in_value;
}