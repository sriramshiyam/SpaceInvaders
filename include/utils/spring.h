#pragma once

typedef struct Spring
{
    double restLength;
    double damping;
    double velocity;
    double force;
    double k;
} Spring;