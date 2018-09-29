/**
 * @file Menagerie.cpp - Menagerie game
 * @author Rajiv Singireddy
 * @see "Seattle University, CPSC 2430, Spring 2018"
 */
#include <iostream>
#include <fstream>
#include "ListA.h"
#include "adt/Display.h"
#include "adt/Critter.h"
#include "QueueL.h"
#include "Menagerie.h"
#include "Cannon.h"
#include "Cannonball.h"
#include "Terminal.h"
#include "InchWorm.h"
#include "Snake.h"
#include "Snake.cpp"
#include "Snake2.cpp"

using namespace std;

void Menagerie::resetGame() {
  clear();
  cannonballs = 0;
  int row,col;
  display.getSize(row,col);
  Cannon* c = new Cannon((int)row-2,(int)col/2);
  critters.append(c);

  InchWorm *worm = new InchWorm(10,10);
  int cody = this->critters.append(worm);
  this->events.enqueue(Event(MOVE, cody));

  InchWorm *worm2 = new InchWorm(15,15);
  int cody2 = this->critters.append(worm2);
  this->events.enqueue(Event(MOVE, cody2));

  Snake *snake = new Snake(20,20);
  int cody3 = this->critters.append(snake);
  this->events.enqueue(Event(MOVE, cody3));
  

}


void Menagerie::processCollisions() {
  /**
   * Look for and process each collision.
   * A collision is where pxms.get(i).get(r,c) and pxms.get(j).get(r,c)
   * are both not transparent.
   *
   * For any collision, we kill both colliding critters with killCritter.
   */
  int row,cols;
  display.getSize(row,cols);

  for(int i = 0; i < pxms.size()-1; i++) {
    for(int j = i+1; j < pxms.size(); j++) {
      for(int r = 0; r < row; r++) {
        for(int c = 0; c < cols; c++) {
          if(!(pxms.get(i).get(r,c).transparent) && !(pxms.get(j).get(r,c).transparent)) {
            killCritter(i);
            killCritter(j);
          }
        }
      }
    }
  }
}

bool Menagerie::compositeScene() {
  int r,c;
  display.getSize(r,c);
  scene = PixelMatrix(r,c,RGB::BLACK);
  PixelMatrix old = scene;
  for(int i = 0; i < pxms.size(); i++) {
    scene.overlay(pxms.get(i));
  }
  refreshDisplay();

  if (scene != old)
    lastMovement = eventCount;
  else {
    log("no movement");
    eventCount++;
  }
  return eventCount - lastMovement <= NO_MOVEMENT;
}

bool Menagerie::processEvent() {
  Event e = this->events.peek();
  if(e.type == MOVE) {
    for(int i = 1; i < critters.size(); i++) {
      if(critters.get(i) !=nullptr) {
        critters.get(i)->move();
      }
    }
    events.enqueue(Event(MOVE));
  }
  else if(e.data == 'q') {
    return false;
  }
  else if(e.data == 'h') {
    critters.get(0)->move();
  }
  else if(e.data == 'g') {
    critters.get(0)->reverse();
  }
  else if(e.data == 'i') {
    shoot();
  }
  this->events.dequeue();
  return true;
}

void Menagerie:: shoot() {
  int row;
  int col;
  display.getSize(row,col);
  col = critters.get(0)->getColumn();
  if(cannonballs < CANNON_BALLS) {
    Cannonball *c2 = new Cannonball(row-4,col);
    int ball = this->critters.append(c2);
    this->events.enqueue(Event(MOVE, ball));
    cannonballs++;
  }
}
