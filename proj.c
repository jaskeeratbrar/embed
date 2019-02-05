#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>


struct ntuple {
  uint8_t core;
  uint8_t mask;
  int8_t shift;
};

const struct ntuple inputs[] = {
  { 0x01, 0x0f, 3 },
  { 0x42, 0xf0, -2 },
  { 0x03, 0xaa, 0 },
  { 0xff, 0xf0, -7 },
  { 0xe3, 0xbc, 7 },
  { 0x7d, 0x00, -2 },
  { 0x88, 0x00, 8 },
  { 0xaa, 0x00, 2 },
  { 0x01, 0xaa, 3 },
  { 0x01, 0xcc, 3 },
  { 0xbb, 0xff, 2 },
  { 0xcc, 0x67, 4 },
  { 0x00, 0x32, 2 }  
};

/* Take a value x and reverse the order of the bits. */
uint8_t reverse(uint8_t x) {
    uint8_t revNum = 0;
    for(int i =0 ; i < 8; ++i){
        if((x & (1 <<i))) {
            revNum |= 1 << ((8-1) - i);
        }
    }
    return revNum;
}

/* For all of the one bits in mv, clear the corresponding bits in val and
 * returns the result. */
uint8_t clearbits(uint8_t val, uint8_t mv) {

    uint8_t bit = 0;

    for(int i = 0; i < 8; i++){
        if((mv & (1 << i))){
            bit |= 0;
        }
        else{
            bit|= (val & (1 << i));
        }

    }

    return bit;
}

/* Shift val the number of bits provided by sv.  If sv is positive, shifts left.
 * If sv is negative, logically shifts right the absolute value. */
uint8_t shift(uint8_t val, int8_t sv) {
    if(sv > 0){
        return val << sv;
    }
    else{
        return val >> abs(sv);
    }
}

/* Prints out the value val in string form to standard output.
 */
void binaryPrint(uint8_t val) {

    const unsigned bits = 8;

    unsigned mask = 1 << (bits-1);

    while (mask){
        printf("%d", (mask & val) != 0);
        mask >>= 1;
    }


}

/* Calculates and returns the number of test values in the input array.
 */
int getTestCount() {

    int size = *(&inputs +1) - inputs;

    return size;
}

int main(int argc, char **argv) {
  int n = getTestCount();

  printf("size is %d\n", n);

  for (int i=0; i < n; i++) {
    printf("%02x: ", inputs[i].core);
    binaryPrint(inputs[i].core);
    printf(" ");
    binaryPrint(reverse(inputs[i].core));
    printf(" ");
    binaryPrint(clearbits(inputs[i].core, inputs[i].mask));
    printf(" ");
    binaryPrint(shift(inputs[i].core, inputs[i].shift));
    printf("\n");
  }
  return 0;
}
