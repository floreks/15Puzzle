#include "node.h"

bool Node::equals(Node n)
{
    return equal(state.begin(),state.end(),n.getNode().begin());
}
