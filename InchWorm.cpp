/**
 * @file InchWorm.cpp - Cody the Inch Worm!
 * @author Rajiv Singireddy
 * @see "Seattle University, CPSC 2430, Spring 2018"
 */

#include "InchWorm.h"
#include <iostream>
using namespace std;

InchWorm::InchWorm(int row, int col) {
  r = row;
  c = col;
  state = BUNCHED;
  heading = EAST;
}

void InchWorm:: move() {
  if(state == STRAIGHT) {
    state = BUNCHED;
  }
  else {
    state = STRAIGHT;
    if(heading == EAST) {
      c+= 2;
    }
    if(heading == WEST) {
      c-=2;
    }
    if(heading == NORTH) {
      r-= 2;
    }
    if(heading == SOUTH) {
      r+=2;
    }
  }
}

void InchWorm:: reverse() {
  if(heading == EAST) {
    heading = WEST;
  }
  else if(heading == WEST) {
    heading = EAST;
  }

  else if(heading == NORTH) {
    heading = SOUTH;
  }
  else if(heading == SOUTH) {
    heading = NORTH;
  }
}

void InchWorm:: rotate() {
  if(heading == EAST) {
    heading = SOUTH;
  }
  else if(heading == WEST) {
    heading = NORTH;
  }
  else if(heading == NORTH) {
    heading = EAST;
  }
  else if(heading == SOUTH) {
    heading = WEST;
  }
}

void InchWorm:: render(PixelMatrix &pxm) const {
  pxm.paint(r, c, RGB:: WHITE);
  RGB color;
  int rows, cols;
  pxm.getSize(rows,cols);
  if(state == STRAIGHT) {
    if(heading == EAST) {
      for(int i = 0; i <7; i++) {
        if(i%2==0) {
          pxm.paint(r,c-i,RGB::WHITE);
        }
        if(i%2!=0) {
          pxm.paint(r,c-i,RGB::GREEN);
        }
      }
    }

    if(heading == WEST) {
      for(int i = 0; i <7; i++) {
        if(i%2==0) {
          pxm.paint(r,c+i,RGB::WHITE);
        }
        if(i%2!=0) {
          pxm.paint(r,c+i,RGB::GREEN);
        }
      }
    }

    if(heading == NORTH) {
      for(int i = 0; i <7; i++) {
        if(i%2==0) {
          pxm.paint(r+i,c,RGB::WHITE);
        }
        if(i%2!=0) {
          pxm.paint(r+i,c,RGB::GREEN);
        }
      }
    }

    if(heading == SOUTH) {
      for(int i = 0; i <7; i++) {
        if(i%2==0) {
          pxm.paint(r-i,c,RGB::WHITE);
        }
        if(i%2!=0) {
          pxm.paint(r-i,c,RGB::GREEN);
        }
      }
    }

    
  } 
  else if(state == BUNCHED) {
    if(heading == EAST) {
      pxm.paint(r,c-1,RGB::GREEN);
      pxm.paint(r-1,c-1,RGB::WHITE);
      pxm.paint(r-1,c-2,RGB::GREEN);
      pxm.paint(r-1,c-3,RGB::WHITE);
      pxm.paint(r,c-3,RGB::GREEN);
      pxm.paint(r,c-4,RGB::WHITE);
    }
    else if(heading == WEST) {
      pxm.paint(r,c+1,RGB::GREEN);
      pxm.paint(r-1,c+1,RGB::WHITE);
      pxm.paint(r-1,c+2,RGB::GREEN);
      pxm.paint(r-1,c+3,RGB::WHITE);
      pxm.paint(r,c+3,RGB::GREEN);
      pxm.paint(r,c+4,RGB::WHITE);

    }
    else if(heading == NORTH) {
      pxm.paint(r+1,c,RGB::GREEN);
      pxm.paint(r+1,c-1,RGB::WHITE);
      pxm.paint(r+2,c-1,RGB::GREEN);
      pxm.paint(r+3,c-1,RGB::WHITE);
      pxm.paint(r+3,c,RGB::GREEN);
      pxm.paint(r+4,c,RGB::WHITE);
    }
    else if(heading == SOUTH) {
      pxm.paint(r-1,c,RGB::GREEN);
      pxm.paint(r-1,c-1,RGB::WHITE);
      pxm.paint(r-2,c-1,RGB::GREEN);
      pxm.paint(r-3,c-1,RGB::WHITE);
      pxm.paint(r-3,c,RGB::GREEN);
      pxm.paint(r-4,c,RGB::WHITE);


    }
  }
}

int InchWorm::sign() const {
  if (heading == EAST || heading == SOUTH)
    return +1;
  else
    return -1;
}

bool InchWorm::eastwest() const {
  return (heading == EAST || heading == WEST);
}
