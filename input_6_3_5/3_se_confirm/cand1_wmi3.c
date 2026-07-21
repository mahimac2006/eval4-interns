#include "klee.h"
#include <assert.h>
/* WMI-3 psmouse_smbus_cleanup — SE oracle from SA rule sailor/wmi-3-arbitrary-free-stale-traversal */
int main(void){
  int attacker_controlled; klee_make_symbolic(&attacker_controlled, sizeof(attacker_controlled), "attacker_controlled");
  int authoritative; klee_make_symbolic(&authoritative, sizeof(authoritative), "authoritative");
  klee_assume(authoritative == 1);
  assert(attacker_controlled == 0);
  return 0;}
