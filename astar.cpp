#include "astar.h"
#include <cmath>
#include <ctime>
#include <set>

Astar::Astar(double HW, bool BT)
{
    hweight = HW;
    breakingties = BT;
}

SearchResult Astar::startSearch(ILogger *Logger, const Map &map, const EnvironmentOptions &options)
{
    bool pathfound;
    float pathlength;
    std::list<Node> lppath;
    std::list<Node> hppath;
    unsigned int nodescreated; //|OPEN| + |CLOSE| = total number of nodes saved in memory during search process.
    unsigned int numberofsteps; //number of iterations (expansions) made by algorithm to find a solution

    const clock_t begin_time = std::clock();

    std::set<Node> closedSet = std::set<Node>();

    /*
    int s_i = map.get_start_i();
    int s_j = map.get_start_j();
     */
    int g_i = map.get_goal_i();
    int g_j = map.get_goal_j();
    Node start = Node(map.get_start_i(), map.get_start_j()
            , computeHFromCellToCell(map.get_start_i(), map.get_start_j(), g_i, g_j, options));
    Node goal = Node(g_i, g_j, 0);

    // The set of currently discovered nodes that are not evaluated yet.
    // Initially, only the start node is known.
    std::set<Node> openSet = std::set<Node>();
    openSet.insert(start);

    Node current = start;
    Node neighbor = start;
    bool isobstacle1 = false, isobstacle2 =false;
    while (!openSet.empty()) {
        current = *openSet.begin();
        if (current == goal) {
            break;
        }

        openSet.erase(openSet.begin());
        closedSet.insert(current);

        //for each neighbor of current if neighbor in closedSet
        //    continue;        // Ignore the neighbor which is already evaluated.

        for (int k = 0; k < 9; ++k) {

            openSet.insert(neighbor);

            // The distance from start to a neighbor
            tentative_gScore := gScore[current] + dist_between(current, neighbor)
            if tentative_gScore >= gScore[neighbor]
            continue        // This is not a better path.

            // This path is the best until now. Record it!
            cameFrom[neighbor] := current
                    gScore[neighbor] : = tentative_gScore
            fScore[neighbor] := gScore[neighbor] + heuristic_cost_estimate(neighbor, goal)
        }
    }
    if (sresult.pathfound = (current == goal)) {
        sresult.hppath = &hppath; //Here is a constant pointer
        sresult.lppath = &lppath;
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
