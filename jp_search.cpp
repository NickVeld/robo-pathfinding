#include "jp_search.h"

JP_Search::~JP_Search()
{
}

unsigned long long int JP_Search::findJp(int i, int j, const Map &map, const EnvironmentOptions &options
                                  , int to_i, int to_j, std::list<Node*> &ss)
{
    if (!map.MoveIsAvaiable(to_i, to_j, i, j, options)) {
        return map_shift * i + j;
    }
    if (to_i == g_i && to_j == g_j) {
        return map_shift*to_i + to_j;
    }

    if (to_i - i > 0) {
        //if ()
        return findJp(i, j, map, options, i + 1, j, ss);
    }
    if (to_j - j > 0) {
        return findJp(i, j, map, options, i, j + 1, ss);
    }
    if (to_i - i < 0) {
        return findJp(i, j, map, options, i - 1, j, ss);
    }
    if (to_j - j < 0) {
        return findJp(i, j, map, options, i, j - 1, ss);
    }
    if(options.allowdiagonal) {
        if (to_i - i > 0 && to_j - j < 0) findJp(i, j, map, options, i + 1, j - 1, ss);
        if (to_i - i > 0 && to_j - j > 0) findJp(i, j, map, options, i + 1, j + 1, ss);
        if (to_i - i < 0 && to_j - j > 0) findJp(i, j, map, options, i - 1, j + 1, ss);
        if (to_i - i < 0 && to_j - j < 0) findJp(i, j, map, options, i - 1, j - 1, ss);
    }
    return true;
}

std::list<Node*> JP_Search::findSuccessors(Node* curNode, const Map &map, const EnvironmentOptions &options)
{
    std::list<Node*> ss;
    findJp(curNode->i, curNode->j, map, options, curNode->i + 1, curNode->j, ss);
    findJp(curNode->i, curNode->j, map, options, curNode->i, curNode->j + 1, ss);
    findJp(curNode->i, curNode->j, map, options, curNode->i - 1, curNode->j, ss);
    findJp(curNode->i, curNode->j, map, options, curNode->i, curNode->j - 1, ss);
    if(options.allowdiagonal) {
        findJp(curNode->i, curNode->j, map, options, curNode->i + 1, curNode->j - 1, ss);
        findJp(curNode->i, curNode->j, map, options, curNode->i + 1, curNode->j + 1, ss);
        findJp(curNode->i, curNode->j, map, options, curNode->i - 1, curNode->j + 1, ss);
        findJp(curNode->i, curNode->j, map, options, curNode->i - 1, curNode->j - 1, ss);
    }
    return ss;
}
/*
std::list<Node> JP_Search::makePrimaryPath(Node curNode)
{
    //need to implement
}

std::list<Node> JP_Search::makeSecondaryPath(Node curNode)
{
    //need to implement
}
*/