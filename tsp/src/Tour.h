//Tour builds the tsp path and makes a linkedList of all the nodes.

#ifndef TOUR_H
#define TOUR_H

#include "Node.h"
#include "Point.h"

class Tour {
public:
    /**
     * @brief Tour this is a constructor for a short tour we used for testing
     * in the early stages of the development.
     */
    Tour(Point a, Point b, Point c, Point d);

    /**
     * @brief Tour is our default constructor for the whole class.
     */
    Tour();

    /**
      This is our default destructor for the class.
      */
    ~Tour();

    /**
     * @brief Tour::show prints the coordinates of the node and the order of the tour.
     */
    void show();

    /**
     * @brief draw, draws the lines between the nodes.
     * @param scene
     */
    void draw(QGraphicsScene* scene);

    /**
     * @brief size The function returns the amount of nodes used in the tour.
     */
    int size();

    /**
     * @brief distance Returns the length of the whole tour.
     * @return Adds the distance between each node.
     */
    double distance();

    /**
     * @brief Tour::insertNearest is a method which allows the point to be placed in the path
     * which connects to the nearest point.
     *
     * @param p is the new point which we construct a node from. This node(p)
     * is the node which we will place in the tour.
     */
    void insertNearest(Point p);

    /**
     * @brief Tour::insertSmallest function leads the nodes through the path
     * where each added node travels the path which adds the shortest distance
     * to the total distance.
     * @param p is the new point which we construct a node from. This node(p)
     * is the node which we will place in the tour.
     */
    void insertSmallest(Point p);

private:
    Node* node = nullptr;

};

#endif // TOUR_H
