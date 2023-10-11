//Tour builds the tsp path and makes a linkedList of all the nodes.

#include <iostream>
#include "Tour.h"
#include "Node.h"
#include "Point.h"

Tour::Tour(Point a, Point b, Point c, Point d)
{
    Node* nodeA = new Node(a);
    Node* nodeB = new Node(b);
    Node* nodeC = new Node(c);
    Node* nodeD = new Node(d);

    nodeA->next = nodeB;
    nodeB->next = nodeC;
    nodeC->next = nodeD;
    nodeD->next = nodeA;

    node = nodeA;
}

Tour::Tour()
{
    node = nullptr;
}

Tour::~Tour()
{
    if(node == nullptr){
        return;
    }
    Node* currentNode = node;
    Node* nextNode;

    do{
        nextNode = currentNode->next;
        delete currentNode;
        currentNode = nextNode;
    }while(currentNode != node);

}

void Tour::show()
{
    // If there are no Nodes we don't print
    if(node == nullptr) return;

    Node* currentNode = node;
    do
    {
        cout << currentNode->point.toString() << endl;
        currentNode = currentNode->next;

    }while(currentNode != node);

}

void Tour::draw(QGraphicsScene *scene)
{
    // If there are no Nodes we don't draw
    if(node == nullptr) return;


    // Iterate trough the nodes (First node will be a Node next node
    // may be a nullptr then we just draw the point
    Node* currentNode = node;
    do
    {
        currentNode->point.drawTo(currentNode->next->point, scene);

        currentNode = currentNode->next;

    }while(currentNode != node);
}

int Tour::size()
{
    int count = 0;

    if(node == nullptr) return count;

    // Itererate trough the nodes until we reach the startnode
    // or reach a nullptr
    Node* currentNode = node;
    do
    {
        count++;
        currentNode = currentNode->next;
    }while(currentNode != node);
    return count;
}

double Tour::distance()
{
    double tourLength = 0;

    // If there are no Nodes we don't draw
    if(node == nullptr || node->next == nullptr)
    {
        return tourLength;
    }

    // Iterate trough the nodes (First node will be a Node next node
    // may be a nullptr then we stop
    Node* currentNode = node;
    do
    {
        tourLength += currentNode->point.distanceTo(currentNode->next->point);
        currentNode = currentNode->next;

    }while(currentNode != node);
    return tourLength;
}

void Tour::insertNearest(Point p)
{
    //catches the first instance where there are no nodes
    //currently added to the tour.
    if(node == nullptr){
        node = new Node(p);
        node->next = node;
        return;
    }
    // Itererate trough the nodes until we reach the startnode.
    double shortestDistance = node->point.distanceTo(p);
    Node* nearestNode = node;
    Node* currentNode = node;
    do
    {
        double currentDistance = currentNode->point.distanceTo(p);
        if(shortestDistance > currentDistance)
        {
            shortestDistance = currentDistance;
            nearestNode = currentNode;

        }
        //iterator tool for continuing the loop.
        currentNode = currentNode->next;
    }while(currentNode != node);

    nearestNode->next = new Node(p,nearestNode->next);

}


void Tour::insertSmallest(Point p)
{
    //catches the first instance where there are no nodes
    //currently added to the tour.
    if(node == nullptr){
        node = new Node(p);
        node->next = node;
        return;

    //Catches the case when there is no next node in starting node
    }else if(node->next == nullptr){
        node->next = new Node(p);
        node->next->next = node;
        return;
    }

    // Variables for making comparisons and storingthe smallest increase
    Node* nearestNode = node;
    Node* currentNode = node;

    double currentDiff;

    double previousDistance = currentNode->point.distanceTo(currentNode->next->point);
    double newDistance = currentNode->point.distanceTo(p) + p.distanceTo(currentNode->next->point);
    double shortestDiff = newDistance - previousDistance;

    //Loop trough all nodes until we reach the starting node again
    do
    {
        //Calculate the difference in distance if we try to insert the point between two
        //existing points
        previousDistance = currentNode->point.distanceTo(currentNode->next->point);
        newDistance = currentNode->point.distanceTo(p) + p.distanceTo(currentNode->next->point);
        currentDiff = newDistance - previousDistance;

        // Compare the shortests difference we have found until this point
        // and replace it if the current difference is shorter
        if(currentDiff < shortestDiff)
        {
            shortestDiff = currentDiff;
            nearestNode = currentNode;
        }
        currentNode = currentNode->next;

    }while(currentNode != node);

    // insert the new node where it makes the smallest
    // increse to the tour length
    nearestNode->next = new Node(p,nearestNode->next);

}
