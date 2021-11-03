#pragma once


struct particle
{
  const double mass;
  const double num; //int is OK but temporary I use double
  const double num_z;
};

typedef struct particle Mass;

extern Mass *main_beam;
extern Mass *main_target;
extern Mass *sub_beam;
extern Mass *sub_target;


