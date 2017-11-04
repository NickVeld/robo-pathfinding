#ifndef ASTAR_H
#define ASTAR_H
#include "isearch.h"
#include <cmath>
#include <ctime>
#include <set>

//A* search.
class Astar : public ISearch
{
    public:
        Astar(double HW, bool BT);
        SearchResult startSearch(ILogger *Logger, const Map &map, const EnvironmentOptions &options);
    protected:
    virtual double computeHFromCellToCell(int i1, int j1, int i2, int j2, const EnvironmentOptions &options) {return 0;}
    virtual std::list<Node> findSuccessors(Node curNode, const Map &map, const EnvironmentOptions &options);
    virtual std::list<Node> makePrimaryPath(Node curNode);//Makes path using back pointers
    virtual std::list<Node> makeSecondaryPath(Node curNode);//Makes another type of path(sections or points)
    std::set<Node> openSet;
    std::set<Node> closedSet;
};

#endif
