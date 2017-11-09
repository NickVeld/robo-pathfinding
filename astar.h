#ifndef ASTAR_H
#define ASTAR_H
#include "isearch.h"
#include <cmath>
#include <ctime>
#include <set>
#include <unordered_map>

//A* search.
class Astar : public ISearch
{
    public:
        Astar(double HW, bool BT);
        SearchResult startSearch(ILogger *Logger, const Map &map, const EnvironmentOptions &options);
        static double computeHFromCellToCell(int i1, int j1, int i2, int j2, const EnvironmentOptions &options);
protected:
        virtual void pushNextSuccessor(Node *curNode, const Map &map, const EnvironmentOptions &options
                                        , int i, int j, std::list<Node*> &ss);
        virtual std::list<Node*> findSuccessors(Node *curNode, const Map &map, const EnvironmentOptions &options);

        virtual bool lineOfSight(int i1, int j1, int i2, int j2, const Map &map, const EnvironmentOptions &options)
        {return false;}

        virtual std::list<Node>* makePrimaryPath(Node curNode, const Map &map, const EnvironmentOptions &options);//Makes path using back pointers
        virtual std::list<Node>* makeSecondaryPath(Node curNode);//Makes another type of path(sections or points)

        std::set<std::pair<double, Node*>> openSet;
        std::unordered_map<unsigned long long int, Node*> closedSet;
        std::list<Node> created;
        std::unordered_map<unsigned long long int, Node*> pcreated;
        int g_i = -1, g_j = -1;
        unsigned long long int map_shift;

};

#endif
