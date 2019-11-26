#ifndef CARDINAL_DIRECTION_H
#define CARDINAL_DIRECTION_H

enum CardinalDirection {
    North = 0,
    East = 1,
    South = 2,
    West = 3,
};

CardinalDirection fromNumber(const int num);
#endif // CARDINAL_DIRECTION_H
