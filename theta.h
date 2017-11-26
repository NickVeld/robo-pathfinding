#ifndef THETA_H
#define THETA_H
#include "astar.h"

class Theta: public Astar
{
    public:
        Theta(double hweight, bool breakingties):Astar(hweight, breakingties){}
        ~Theta(void);

    private:
        bool lineOfSight(int i1, int j1, int i2, int j2, const Map &map, const EnvironmentOptions &options );
        Node resetParent(Node current, Node parent, const Map &map, const EnvironmentOptions &options);

        void getLineOfSight(Node * to, const Map &map, const EnvironmentOptions &options, std::list<Node>* path);

        virtual std::list<Node>* makePrimaryPath(Node curNode, const Map &map, const EnvironmentOptions &options);//Makes path using back pointers
        virtual std::list<Node>* makeSecondaryPath(Node curNode);//Makes another type of path(sections or points)

};


#endif // THETA_H
