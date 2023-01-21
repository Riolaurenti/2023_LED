#include <Wire.h>
#include <PJONSoftwareBitBang.h> 
// PJON stuff //

uint8_t bus_id[] = {0, 0, 1, 53}; // Ancs unique ID
PJON<SoftwareBitBang> bus(bus_id, 20); // Choose Bus ID
int packet; // Holder for our packet
String string = ""; // holder for our Pjon Message
