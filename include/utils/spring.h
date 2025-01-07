#pragma once

typedef struct Spring
{
    int restLength;
    double damping;
    double velocity;
    double force;
    double k;
} Spring;