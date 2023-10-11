/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 * Updated for TDDD86, 2021.
 */

#include "GameState.h"
#include "utilities.h"
#include "constants.h"
#include <iostream>


GameState::GameState(int numberOfRobots) {
    if(!units.empty())
    {
        for(Unit* unit : units)
        {
            delete unit;
        }
    }

    for (int i = 0; i < numberOfRobots; i++) {
        Unit* unit = new Unit();
        units.push_back(unit);
   }
    teleportHero();
}

void GameState::draw(QGraphicsScene *scene) const {

    scene->clear();
    hero.draw(scene);
    for(const Unit* unit: units){
        unit->draw(scene);
    }
}

void GameState::teleportHero() {
    do hero.teleport();
    while (!isEmpty(hero));
}

void GameState::moveRobots() {
    for(Unit* unit: units){
        if(unit->isAlive()){
            unit->moveTowards(hero.asPoint());
        }
    }
    /*
    for(Robot& robot: robots)
        robot.moveTowards(hero.asPoint());
        */
}


void GameState::updateCrashes() {

    for(unsigned i=0; i < units.size(); i++){
        for(unsigned j=i+1; j < units.size(); j++){

            if(units[i]->at(*units[j])){
                units[i]->doCrash();
                units[j]->doCrash();
            }
        }
    }

/**
    for(unsigned i=0; i < robots.size(); ++i){
        for(unsigned j=0; j < junks.size(); ++j){
            if(robots[i].at(junks[j])){
                robots[i].doCrash();
            }
        }
        for(unsigned o=i+1; o < robots.size(); ++o){
            if(robots[i].at(robots[o])){
                robots[i].doCrash();
                robots[o].doCrash();
            }
        }
    }
    **/
}

int GameState::countToBeJunked()const{
    int numberDestroyed =0;
    for(unsigned i=0; i < units.size(); ++i)
        if(units[i]->isToBeJunked())
        {
            numberDestroyed++;
        }
    return numberDestroyed;
}

void GameState::junkTheCrashed(){
    for(unsigned i=0; i < units.size(); i++){
        if(units[i]->isToBeJunked()){
            units[i]->toBeJunked = true;
        }
    }
/*
    for(unsigned i=0; i < robots.size(); ++i){
        if (robots[i].isToBeJunked()) {
            junks.push_back(Junk(robots[i].asPoint()));
            robots[i] = robots[robots.size()-1];
            robots.pop_back();
        }
    }
    */
}

bool GameState::someRobotsAlive() const {
    for(unsigned i=0; i < units.size(); ++i)
        if(units[i]->isAlive())
            return true;
    return false;
}


bool GameState::heroDead() const {
    for(const Unit* unit: units){
        if(hero.at(*unit)){
            return true;
        }
    }
    return false;
}


void GameState::moveHeroTowards(const Point& dir) {
    hero.moveTowards(dir);
}

Point GameState::getHeroAsPoint() const {
    return hero.asPoint();
}

/*
 * Free of robots and junk
 */
bool GameState::isEmpty(const Unit& unit) const {
    for(const Unit* currentUnit: units){
        if(currentUnit->at(unit)){
            return false;
        }
    }
    return true;
}

