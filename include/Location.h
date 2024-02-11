#pragma once

struct Location
{
    int row =0;
    int col=0;

    Location() = default;
    Location(int y, int x) : row(y), col(x) {}
};

