#ifndef GRAPH_H
#define GRAPH_H

#include "Node3.h"
#include <QObject>
#include "QThread"
#include <QDebug>

typedef void (*fPtr)(Node3 & , vector<Node3*> &);

class Graph : public QObject
{
    Q_OBJECT
private:
    vector<Node3*> nodes;
    Node3 *endNode;
    Node3 *startNode;
    fPtr operators[4];
    void explore(Node3 *n);
    int *tab;
public:
    Graph(QObject *parent=0);
    void create(int tab[9]);
    vector<Node3*> getPath();
signals:
    void update(int);
};

#endif // GRAPH_H
