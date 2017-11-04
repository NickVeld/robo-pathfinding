#include "astar.h"

Astar::Astar(double HW, bool BT)
{
    hweight = HW;
    breakingties = BT;
    openSet = std::set<Node>();
    closedSet = std::set<Node>();
}

SearchResult Astar::startSearch(ILogger *Logger, const Map &map, const EnvironmentOptions &options)
{
    unsigned long long int numberofsteps = 0; //number of iterations (expansions) made by algorithm to find a solution

    const clock_t begin_time = std::clock();

    /*
    int s_i = map.get_start_i();
    int s_j = map.get_start_j();
     */
    int g_i = map.get_goal_i();
    int g_j = map.get_goal_j();
    Node start = Node(map.get_start_i(), map.get_start_j()
            , hweight * computeHFromCellToCell(map.get_start_i(), map.get_start_j(), g_i, g_j, options));
    Node goal = Node(g_i, g_j, 0);

    // The set of currently discovered nodes that are not evaluated yet.
    // Initially, only the start node is known.
    openSet.insert(start);

    Node current = start;
    Node neighbor = start;
    std::list<Node> neighbors;
    double tentative_gScore = 0;
    while (!openSet.empty()) {
        numberofsteps++;
        current = *openSet.begin();
        if (current == goal) {
            break;
        }

        openSet.erase(openSet.begin());
        closedSet.insert(current);

       neighbors = findSuccessors(current, map, options);
        for (auto it = neighbors.begin(); it != neighbors.end(); ++it) {
            neighbor = *it;
            openSet.insert(neighbor);

            tentative_gScore = current.g
                               + computeHFromCellToCell(current.i, current.j, neighbor.i, neighbor.j, options);
            if (tentative_gScore >= neighbor.g)
                continue;        // This is not a better path.

            neighbor.set_g_and_parent(tentative_gScore, &current);
        }
    }
    if (sresult.pathfound = (current == goal)) {
        std::list<Node> lppath = makePrimaryPath(current);
        std::list<Node> hppath = makeSecondaryPath(current);
        sresult.lppath = &lppath; //Ошибка!
        sresult.hppath = &hppath; //Here is a constant pointer
    }
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

std::list<Node> Astar::findSuccessors(Node curNode, const Map &map, const EnvironmentOptions &options)
{

}

std::list<Node> Astar::makePrimaryPath(Node curNode)
{
    std::list<Node> path;
    //need to implement
    return path;
}

std::list<Node> Astar::makeSecondaryPath(Node curNode)
{
    std::list<Node> path;
    //need to implement
    return path;
}
