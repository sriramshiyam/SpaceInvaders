#pragma once

typedef struct Spring
{
    int restLength;
    float damping;
    float velocity;
    float force;
    float k;
} Spring;