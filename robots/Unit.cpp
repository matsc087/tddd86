/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 */

#include "Unit.h"
#include "constants.h"
#include "utilities.h"
#include <cstdlib>
#include <cmath>

Unit::Unit() {
    teleport();
}

Unit::Unit(const Point& p) {
    x = p.x;
    y = p.y;
}

Point Unit::asPoint() const {
    return Point{x, y};
}

bool Unit::at(const Unit& u) const {
    return (x == u.x && y == u.y);
}



void Unit::moveTowards(const Point& p) {
    if (x > p.x) x--;
    if (x < p.x) x++;
    if (y > p.y) y--;
    if (y < p.y) y++;
    checkBounds();
}

void Unit::teleport() {
    x = rand_int (MIN_X, MAX_X);
    y = rand_int (MIN_Y, MAX_Y);
}

double Unit::distanceTo(const Unit& u) const {
    double dx = u.x - x;
    double dy = u.y - y;
    return sqrt(dx * dx + dy * dy);
}

/*
 * Put this unit inside playing field if outside
 */
void Unit::checkBounds() {
    if (x < MIN_X) x = MIN_X;
    if (x > MAX_X) x = MAX_X;
    if (y < MIN_Y) y = MIN_Y;
    if (y > MAX_Y) y = MAX_Y;
}

void Unit::draw(QGraphicsScene *scene) const {
    Point corner = asPoint();
    if(toBeJunked){
        scene->addEllipse(QRectF(corner.x * UNIT_WIDTH, corner.y * UNIT_HEIGHT,
                                 JUNK_RADIUS, JUNK_RADIUS), QPen(), QBrush(JUNK_COLOR));
    }else{
        scene->addEllipse(QRectF(corner.x * UNIT_WIDTH, corner.y * UNIT_HEIGHT,
                                 JUNK_RADIUS, JUNK_RADIUS), QPen(), QBrush(ROBOT_COLOR));
    }
}

bool Unit::isAlive(){
    return !toBeJunked;
}

bool Unit::isToBeJunked(){
    return toBeJunked;
}

void Unit::doCrash(){
    toBeJunked = true;
    return;
}

void Unit::moveTowards(){
    return;
}

bool Unit::isDestroyed(){
    return !destroyed;
}
