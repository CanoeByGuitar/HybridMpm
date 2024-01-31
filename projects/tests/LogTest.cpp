//
// Created by chenhui on 24-1-15.
//

#include <util/Log.h>

void f(){
  int i = 0;
  MPM_ASSERT(i > 0, "i has to be bigger than zero!");
}
void g(){
  f();
}

int main(){
  g();
}