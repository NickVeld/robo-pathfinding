#include "theta.h"
Theta::~Theta()
{
}

bool Theta::lineOfSight(int i1, int j1, int i2, int j2, const Map &map, const EnvironmentOptions &options )
{
    bool transposed = false;
    if (std::abs(j2-j1) > std::abs(i2-i1)) {
        std::swap(i1, j1);
        std::swap(i2, j2);
        transposed = true;
    }
    if (i1 > i2) {
        std::swap(i1, i2);
        std::swap(j1, j2);
    }
    auto f = [i1,j1,i2,j2](int x){return (double(x)-i1)*(j2-j1)/(i2-i1) + j1 + 0.5;};
    int lastj = j1;
    int j;
    for (int i = i1 + 1; i < i2; ++i) {
        j = int(f(i));
        if (!map.MoveIsAvaiable(transposed ? j : i, transposed ? i : j
                                , transposed  ? lastj : i-1, transposed ? i-1 : lastj, options)) {
            return false;
        }
    }
    return true;
}

Node Theta::resetParent(Node current, Node parent, const Map &map, const EnvironmentOptions &options )
{
    //need to implement
    return current;
}

std::list<Node>* Theta::makeSecondaryPath(Node curNode) {
    auto path = new std::list<Node>();
    const Node * tmp = &curNode;
    do {
        path->push_front(*tmp);
    }
    while ((tmp = tmp->parent) != nullptr);
    return path;
}

void Theta::getLineOfSight(Node * to, const Map &map, const EnvironmentOptions &options, std::list<Node>* path)
{
    int i1 = to->parent->i, j1 = to->parent->j, i2 = to->i, j2 = to->j;
    bool transposed = false;
    if (std::abs(j2-j1) > std::abs(i2-i1)) {
        std::swap(i1, j1);
        std::swap(i2, j2);
        transposed = true;
    }
    if (i1 > i2) {
        std::swap(i1, i2);
        std::swap(j1, j2);
    }
    auto f = [i1,j1,i2,j2](int x){return (double(x)-i1)*(j2-j1)/(i2-i1) + j1 + 0.5;};
    double hw;
    int g_ia = g_i, g_ja = g_j;
    /*auto g = [map, options, path, hw, g_ia, g_ja](int i, int j, int from_i, int from_j, Node * current, Node * parent) {
        Node * tmp;
        if (!(from_i == i || from_j == j || options.allowdiagonal)) {
            if (map.CellIsObstacle(i, from_j)) {
                path->emplace_front(Node(from_i, j
                            , hw * Astar::computeHFromCellToCell(from_i, j, g_ia, g_ja, options)
                            , parent->g + Astar::computeHFromCellToCell(from_i, from_j, from_i, j, options)));
            } else {
                path->emplace_front(Node(i, from_j
                            , hw * Astar::computeHFromCellToCell(i, from_j, g_ia, g_ja, options)
                            , parent->g + Astar::computeHFromCellToCell(from_i, from_j, i, from_j, options)));
            }
        }
        path->push_front(*current);
    };*/
    int lastj = j1;
    int j;
    for (int i = i1 + 1; i < i2; ++i) {
        j = int(f(i));
        //g(transposed ? j : i, transposed ? i : j
        //        , transposed  ? lastj : i-1, transposed ? i-1 : lastj, to, to->parent);
        path->emplace_front(Node(transposed ? j : i, transposed ? i : j
                , hweight * computeHFromCellToCell(transposed ? j : i, transposed ? i : j, g_ia, g_ja, options)
                , to->parent->g + computeHFromCellToCell(transposed  ? lastj : i-1, transposed ? i-1 : lastj
                        , transposed ? j : i, transposed ? i : j, options)));
    }
}

std::list<Node>* Theta::makePrimaryPath(Node curNode, const Map &map, const EnvironmentOptions &options)
{
    auto path = new std::list<Node>();
    Node * tmp = &curNode;
    do {
        path->push_front(*tmp);
        getLineOfSight(tmp, map, options, path);
        tmp = tmp->parent;
    }
    while (tmp->parent != nullptr);
    return path;
}

