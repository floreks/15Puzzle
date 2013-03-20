#include <iostream>
#include <list>
#include <queue>

using namespace std;

struct State
{
    int ML;
    int MP;
    int KL;
    int KP;
    char L;
};

struct Node
{
    State s;
    list<Node*>p;
    list<Node*>n;
    bool visited;
};

bool isPossible(Node n)
{
    if(n.s.KL <= n.s.ML || n.s.ML == 0)
        if(n.s.KP <= n.s.MP || n.s.MP == 0)
            return true;
    return false;
}

typedef void (*fPtr)(Node *n);

// mozliwe operatory xK - ilosc kanibali xM - ilosc misjonarzy LP/PL - kierunek

void _1K1M_LP(Node *n)
{
    if(n->s.L != 'L')
        return;

    if(n->s.KL < 1 || n->s.ML < 1)
        return;

    Node *ptr = new Node;

    ptr->s.KL = n->s.KL - 1;
    ptr->s.ML = n->s.ML - 1;
    ptr->s.KP = n->s.KP + 1;
    ptr->s.MP = n->s.MP + 1;
    ptr->visited = 0;
    ptr->s.L = 'P';

    if(isPossible(*ptr))
    {
        ptr->p.push_back(n);
        n->n.push_back(ptr);
    }
    else
        delete ptr;
}

void _1K1M_PL(Node *n)
{
    if(n->s.L != 'P')
        return;

    if(n->s.KP < 1 || n->s.MP < 1)
        return;

    Node *ptr = new Node;

    ptr->s.KL = n->s.KL + 1;
    ptr->s.ML = n->s.ML + 1;
    ptr->s.KP = n->s.KP - 1;
    ptr->s.MP = n->s.MP - 1;
    ptr->visited = 0;
    ptr->s.L = 'L';

    if(isPossible(*ptr))
    {
        ptr->p.push_back(n);
        n->n.push_back(ptr);
    }
    else
        delete ptr;
}

void _2K_LP(Node *n)
{
    if(n->s.L != 'L')
        return;

    if(n->s.KL < 2)
        return;

    Node *ptr = new Node;

    ptr->s.KL = n->s.KL - 2;
    ptr->s.ML = n->s.ML;
    ptr->s.KP = n->s.KP + 2;
    ptr->s.MP = n->s.MP;
    ptr->visited = 0;
    ptr->s.L = 'P';

    if(isPossible(*ptr))
    {
        ptr->p.push_back(n);
        n->n.push_back(ptr);
    }
    else
        delete ptr;
}

void _2K_PL(Node *n)
{
    if(n->s.L != 'P')
        return;

    if(n->s.KP < 2)
        return;

    Node *ptr = new Node;

    ptr->s.KL = n->s.KL + 2;
    ptr->s.ML = n->s.ML;
    ptr->s.KP = n->s.KP - 2;
    ptr->s.MP = n->s.MP;
    ptr->visited = 0;
    ptr->s.L = 'L';

    if(isPossible(*ptr))
    {
        ptr->p.push_back(n);
        n->n.push_back(ptr);
    }
    else
        delete ptr;
}

void _2M_LP(Node *n)
{
    if(n->s.L != 'L')
        return;

    if(n->s.ML < 2)
        return;

    Node *ptr = new Node;

    ptr->s.KL = n->s.KL;
    ptr->s.ML = n->s.ML - 2;
    ptr->s.KP = n->s.KP;
    ptr->s.MP = n->s.MP + 2;
    ptr->visited = 0;
    ptr->s.L = 'P';

    if(isPossible(*ptr))
    {
        ptr->p.push_back(n);
        n->n.push_back(ptr);
    }
    else
        delete ptr;
}

void _2M_PL(Node *n)
{
    if(n->s.L != 'P')
        return;

    if(n->s.MP < 2)
        return;

    Node *ptr = new Node;

    ptr->s.KL = n->s.KL;
    ptr->s.ML = n->s.ML + 2;
    ptr->s.KP = n->s.KP;
    ptr->s.MP = n->s.MP - 2;
    ptr->visited = 0;
    ptr->s.L = 'L';

    if(isPossible(*ptr))
    {
        ptr->p.push_back(n);
        n->n.push_back(ptr);
    }
    else
        delete ptr;
}

ostream &operator<<(ostream &os, Node *n)
{
    os << "KL: " << n->s.KL << " ML: " << n->s.ML << " Boat: " << n->s.L << " KP: " << n->s.KP <<
          " MP: " << n->s.MP << endl;
    return os;
}

bool equals(Node *n, Node *n2)
{
    if(n->s.KL != n2->s.KL)
        return 0;
    if(n->s.KP != n2->s.KP)
        return 0;
    if(n->s.ML != n2->s.ML)
        return 0;
    if(n->s.MP != n2->s.MP)
        return 0;
    if(n->s.L != n2->s.L)
        return 0;
    return 1;
}

int main()
{
    fPtr tab[6] = { &_1K1M_LP, &_1K1M_PL, &_2K_LP, &_2K_PL, &_2M_LP, &_2M_PL };

    Node *root = new Node;
    root->s.KL = 3;
    root->s.ML = 3;
    root->s.KP = 0;
    root->s.MP = 0;
    root->s.L = 'L';
    root->visited = 0;

    Node *end = new Node;
    end->s.KL = 0;
    end->s.ML = 0;
    end->s.KP = 3;
    end->s.MP = 3;
    end->s.L = 'P';
    end->visited = 0;

    //    for(int i=0;i<6;i++)
    //        tab[i](root);

    Node *tmp;
    list<Node*>::iterator it,it2,it3;
    list<Node*>v;
    bool bEnd = 0, cmp;
    v.push_back(root);

    do
    {
        cout << 'a';
        for(it = v.begin();it!=v.end();it++)
        {
            cout << endl << 'b';
            if((*it)->visited)
                continue;
            for(int i=0;i<6;i++)
                tab[i](*it);
            for(it2 = (*it)->n.begin();it2 != (*it)->n.end();it2++)
            {
                cout << endl << 'c';
                //cout << *it2;
                if(equals(*it2,end))
                {
                    bEnd = true;
                    tmp = *it2;
                    break;
                }
                cmp = 0;
                for(it3 = v.begin();it3!=v.end();it3++)
                {
                    cout << 'd';
                    if(equals(*it3,*it2))
                            cmp = 1;
                }
                if(!cmp)
                    v.push_back(*it2);
            }
            if(bEnd)
                break;
            (*it)->visited = true;
        }
    }while(!bEnd);
    cout << endl << "Koniec...\n" << tmp;
    return 0;
}
