#pragma once

class Maze;

bool RecursiveDivision(Maze &);

/*struct RecursiveDivision
{
    bool operator()(Maze &maze);
private:
    struct Area
    {
        Area();
        Area(int t, int l, int r, int c);
        bool canBeSplit();

        int top, left, rows, cols;
    };
    void initialize(Maze &maze);
    void verticalSplit(const Area &area, Maze &maze);
    void horizontalSplit(const Area &area, Maze &maze);
};*/
