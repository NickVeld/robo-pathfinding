#ifndef JP_SEARCH_H
#define JP_SEARCH_H
#include "astar.h"

class JP_Search:public Astar
{
public:
    JP_Search(float hweight, bool breakingties):Astar(hweight, breakingties){}
    ~JP_Search();

private:
    std::list<Node> findSuccessors(Node curNode, const Map &map, const EnvironmentOptions &options);
    //std::list<Node> makePrimaryPath(Node curNode);
    //std::list<Node> makeSecondaryPath(Node curNode);
};

#endif // JP_SEARCH_H
