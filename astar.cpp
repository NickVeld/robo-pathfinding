#include "astar.h"

Astar::Astar(double HW, bool BT)
{
    hweight = HW;
    breakingties = BT;
    openSet = std::set<Node>();
    closedSet = std::unordered_map<unsigned long long int, Node>();
}

SearchResult Astar::startSearch(ILogger *Logger, const Map &map, const EnvironmentOptions &options)
{
    unsigned long long int numberofsteps = 0; //number of iterations (expansions) made by algorithm to find a solution

    const clock_t begin_time = std::clock();

    /*
    int s_i = map.get_start_i();
    int s_j = map.get_start_j();
     */
    g_i = map.get_goal_i();
    g_j = map.get_goal_j();
    map_shift = map.getMapWidth();

    Node start = Node(map.get_start_i(), map.get_start_j()
            , hweight * computeHFromCellToCell(map.get_start_i(), map.get_start_j(), g_i, g_j, options),
            0, NULL);
    Node goal = Node(g_i, g_j, 0);

    // The set of currently discovered nodes that are not evaluated yet.
    // Initially, only the start node is known.
    openSet.insert(start);

    Node current = start;
    std::list<Node> neighbors;
    double tentative_gScore = 0;
    while (!openSet.empty()) {
        numberofsteps++;
        current = *openSet.begin();
        if (current == goal) {
            break;
        }

        openSet.erase(openSet.begin());
        closedSet.insert({map_shift * current.i + current.j, current});

       neighbors = findSuccessors(current, map, options);
        for (Node neighbor : neighbors) {

            tentative_gScore = current.g
                               + computeHFromCellToCell(current.i, current.j, neighbor.i, neighbor.j, options);
            if (tentative_gScore < neighbor.g) {
                neighbor.set_g_and_parent(tentative_gScore
                        , &((*(closedSet.find(map_shift * current.i + current.j))).second));
                openSet.erase(neighbor);
            }
            openSet.insert(neighbor);
        }
    }
    if ((sresult.pathfound = (current == goal)) || true) {
        std::list<Node> lppath = makePrimaryPath(current);
        //std::list<Node> hppath = makeSecondaryPath(current);
        //sresult.lppath = &lppath; //Ошибка!
        //Что это такое???
        //5. Implement A* with 2k neighbors (up to 32).
        //6. Implement A* with heading turns.
        //sresult.hppath = &hppath; //Here is a constant pointer
    }
    sresult.pathlength = current.g;
    sresult.nodescreated = openSet.size() + closedSet.size();
    sresult.numberofsteps = numberofsteps;
    sresult.time = double(std::clock() - begin_time) /  CLOCKS_PER_SEC;
    return sresult;
}

double Astar::computeHFromCellToCell(int i1, int j1, int i2, int j2, const EnvironmentOptions &options)
{
    if (options.metrictype == CN_SP_MT_EUCL) {
        return std::sqrt(std::pow(i1-i2, 2) + std::pow(j1-j2, 2));
    }
    unsigned int di = std::abs(i1 - i2);
    unsigned int dj = std::abs(j1 - j2);
    if (options.metrictype == CN_SP_MT_MANH) {
        return di + dj;
    }
    if (options.metrictype == CN_SP_MT_CHEB) {
        return (di < dj) ? dj : di;
    }
    if (options.metrictype == CN_SP_MT_DIAG) {
        unsigned int D = 1; // weight of up, down, left, right movement
        unsigned int D2 = 1; // weight of diagonal movement
        //if D == D2, Diagonal distance equivalent to Chebyshev distance
        return D * (di + dj) + (D2 - 2 * D) * ((di < dj) ? di : dj);
    }
    return 0;
}

void Astar::pushNextSuccessor(Node curNode, const Map &map, const EnvironmentOptions &options
                                , int i, int j, std::list<Node> &ss)
{
    Node tmp = curNode;
    if (map.MoveIsAvaiable(i, j, curNode.i, curNode.j, options)) {
        /*if (i == 11 && j == 8) {
            std::cout << closedSet.size() << std::endl << (closedSet.find(tmp) == closedSet.end()) << std::endl;
            closedSet.insert(tmp);
            std::cout << closedSet.size() << std::endl;
            closedSet.erase(tmp);
            std::cout << closedSet.size() << std::endl << std::endl;
        }*/
        if (!closedSet.count(map_shift * i + j)) {
            tmp = Node(i, j
                    , computeHFromCellToCell(i, j, g_i, g_j, options));
            ss.push_back(tmp);
        }
    }
}

std::list<Node> Astar::findSuccessors(Node curNode, const Map &map, const EnvironmentOptions &options) {
    std::list<Node> ss;
    pushNextSuccessor(curNode, map, options, curNode.i + 1, curNode.j, ss);
    pushNextSuccessor(curNode, map, options, curNode.i, curNode.j + 1, ss);
    pushNextSuccessor(curNode, map, options, curNode.i - 1, curNode.j, ss);
    pushNextSuccessor(curNode, map, options, curNode.i, curNode.j - 1, ss);
    if(options.allowdiagonal) {
        pushNextSuccessor(curNode, map, options, curNode.i + 1, curNode.j - 1, ss);
        pushNextSuccessor(curNode, map, options, curNode.i + 1, curNode.j + 1, ss);
        pushNextSuccessor(curNode, map, options, curNode.i - 1, curNode.j + 1, ss);
        pushNextSuccessor(curNode, map, options, curNode.i - 1, curNode.j - 1, ss);
    }
    return ss;
}

std::list<Node> Astar::makePrimaryPath(Node curNode)
{
    std::list<Node> path;
    const Node * tmp = &curNode;
    do {
        path.push_front(*tmp);
    }
    while ((tmp = tmp->parent) != NULL);
    return path;
}

std::list<Node> Astar::makeSecondaryPath(Node curNode)
{
    std::list<Node> path;
    //need to implement
    return path;
}
