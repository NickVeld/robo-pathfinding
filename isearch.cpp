#include "isearch.h"

ISearch::ISearch()
{
    hweight = 1;
    breakingties = CN_SP_BT_GMAX;
}

ISearch::~ISearch(void) {}


SearchResult ISearch::startSearch(ILogger *Logger, const Map &map, const EnvironmentOptions &options)
{
    //need to implement

    /*sresult.pathfound = ;
    sresult.nodescreated =  ;
    sresult.numberofsteps = ;
    sresult.time = ;
    sresult.hppath = &hppath; //Here is a constant pointer
    sresult.lppath = &lppath;*/
    return sresult;
}

/*
std::list<Node> ISearch::findSuccessors(Node curNode, const Map &map, const EnvironmentOptions &options)
{
    std::list<Node> successors;
    //need to implement
    return successors;
}
*/

std::list<Node>* ISearch::makePrimaryPath(Node curNode)
{
    std::list<Node>* path;
    //need to implement
    return path;
}

std::list<Node>* ISearch::makeSecondaryPath(Node curNode)
{
    std::list<Node>* path;
    //need to implement
    return path;
}
