#include "klee.h"
#include <assert.h>
/* WMI-3 mousedev_create — SE oracle from SA rule CodeQL WMI-3 + RbSA WMI-3 aggregated oracle */
int main(void){
  int attacker_controlled; klee_make_symbolic(&attacker_controlled, sizeof(attacker_controlled), "attacker_controlled");
  int authoritative; klee_make_symbolic(&authoritative, sizeof(authoritative), "authoritative");
  klee_assume(authoritative == 1);
  assert(attacker_controlled == 0);
  return 0;}
