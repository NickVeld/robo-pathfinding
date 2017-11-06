#ifndef NODE_H
#define NODE_H

#include <limits>

//That's the data structure for storing a single search node.
//Although one might realize A* pathfinder relying only on g-value,
//it's a good idea to store f- and h-values explicitly for the sake of simplicity
//(and either h- or f-value is definetely needed for realizing different tie-breaking strategies).
//Backpointer is obligatory for any-angle algorithms, e.g. Theta*, and it makes sense to utilize it
//in A*-like algorithms as well for reconstructing path (after the main search phase is finished).

//So, in the end of the day, we have a sort of "universal" search-node structure
//compatable with various types of grid pathfinders (Dijkstra, A*, Jump Point Search, Theta* etc.)
//which means - that's all you need for that project.

struct Node
{
    int     i, j; //grid cell coordinates
    double  F, g, H; //f-, g- and h-values of the search node
    const Node    *parent; //backpointer to the predecessor node (e.g. the node which g-value was used to set the g-velue of the current node)

    Node(int i, int j, double H=0, double g=std::numeric_limits<double>::max(), Node *parent=NULL)
            : i(i), j(j), H(H), parent(parent), g(g)
    {
        F=g+H;
    }

    double set_g_and_parent(double g, const Node *parent=NULL) {
        this->g = g;
        this->parent = parent;
        F=g+H;
        return F;
    }

    double setH(double H) {
        this->H = H;
        F=g+H;
        return F;
    }

    bool operator== (const Node &other) const {
        return i == other.i && j == other.j;
    }

    bool operator!= (const Node &other) const {
        return !(*this == other);
    }

    bool operator< (const Node &other) const {
        /*
        if (i == other.i && j == other.j) {
            return false;
        }
        return ((F == other.F)
                ? ((H == other.H)
                   ? ((i == other.i) ? (j < other.j) : (i < other.i))
                   : (H < other.H))
                : (F < other.F));
         */
        return (i == other.i) ? (j < other.j) : (i < other.i);
    }
};
#endif
