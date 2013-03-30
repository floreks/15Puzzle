#ifndef GUIMOVE_H
#define GUIMOVE_H

bool up(int tab[9], int &index)
{
    if(index > 5)
        return 0;

    int tmp = tab[index+3];
    tab[index+3] = 0;
    tab[index] = tmp;
    index = index+3;
    return 1;
}

bool down(int tab[9], int &index)
{
    if(index < 3)
        return 0;

    int tmp = tab[index-3];
    tab[index-3] = 0;
    tab[index] = tmp;
    index = index-3;
    return 1;
}

bool left(int tab[9], int &index)
{
    if(index%3 == 2)
        return 0;

    int tmp = tab[index+1];
    tab[index+1] = 0;
    tab[index] = tmp;
    index++;
    return 1;
}


bool right(int tab[9], int &index)
{
    if(index%3 == 0)
        return 0;

    int tmp = tab[index-1];
    tab[index-1] = 0;
    tab[index] = tmp;
    index--;
    return 1;
}
#endif // GUIMOVE_H
