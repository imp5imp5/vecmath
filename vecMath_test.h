/*
 * Dagor Engine 5
 * Copyright (C) 2003-2022  Gaijin Entertainment.  All rights reserved
 *
 * (for conditions of distribution and use, see License)
*/

#ifndef _DAGOR_PUBLIC_MATH_VECMATH_TEST_H_
#define _DAGOR_PUBLIC_MATH_VECMATH_TEST_H_
#pragma once

#include <vecmath/dag_vecMath.h>
#include <string.h>
#include <memory.h>

#ifndef G_ASSERT
#include <assert.h>
#define G_ASSERT assert
#endif

namespace mathtest
{

struct TestIntVec
{
  uint32_t x, y, z, w;
  void set(uint32_t x_, uint32_t y_, uint32_t z_, uint32_t w_)
  {
    x = x_;
    y = y_;
    z = z_;
    w = w_;
  }
};

struct TestFloatVec
{
  float x, y, z, w;
  void set(float x_, float y_, float z_, float w_)
  {
    x = x_;
    y = y_;
    z = z_;
    w = w_;
  }
};

void advanced_test()
{
  TestIntVec iv;
  TestFloatVec fv;
  TestFloatVec fv2;
  vec4f a, b;
  float pos_inf = expf(1e20f);
  float neg_inf = -pos_inf;
  float nan = cosf(pos_inf);

  fv.set(-0.0f, -1e-30f, 1e-30f, (1 << 23));
  fv2.set(0, 0, 1, (1 << 23));
  a = v_ceil(v_ldu(&fv.x));
  G_ASSERT(memcmp(&a, &fv2, sizeof(a)) == 0);
}


void base_test()
{
  TestIntVec iv;
  TestFloatVec fv;
  TestFloatVec fv2;
  vec4f a, b;
  float pos_inf = expf(1e20f);
  float neg_inf = -pos_inf;
  float nan = cosf(pos_inf);

  G_ASSERT(sizeof(a) == sizeof(iv));
  G_ASSERT(sizeof(a) == sizeof(fv));

  a = v_zero();
  iv.set(0, 0, 0, 0);
  G_ASSERT(memcmp(&a, &iv, sizeof(a)) == 0);

  a = v_msbit();
  iv.set(0x80000000u, 0x80000000u, 0x80000000u, 0x80000000u);
  G_ASSERT(memcmp(&a, &iv, sizeof(a)) == 0);

  fv.set(1.0f, 2.0f, 3.0f, 4.0f);
  a = v_ldu(&fv.x);
  G_ASSERT(memcmp(&a, &fv, sizeof(a)) == 0);

  fv.set(1.0f, 2.0f, 3.0f, 4.0f);
  a = v_ldu(&fv.x);
  a = v_add(a, a);
  fv2.set(2.0f, 4.0f, 6.0f, 8.0f);
  v_stu(&fv, a);
  G_ASSERT(memcmp(&fv, &fv2, sizeof(fv)) == 0);

  fv.set(1.0f, 2.0f, 3.0f, 4.0f);
  a = v_ldu(&fv.x);
  a = v_mul(a, a);
  fv2.set(1.0f, 4.0f, 9.0f, 16.0f);
  v_stu(&fv, a);
  G_ASSERT(memcmp(&fv, &fv2, sizeof(fv)) == 0);

  fv.set(1.0f, 2.0f, 3.0f, 4.0f);
  a = v_ldu(&fv.x);
  a = v_div(a, a);
  fv2.set(1.0f, 1.0f, 1.0f, 1.0f);
  v_stu(&fv, a);
  G_ASSERT(memcmp(&fv, &fv2, sizeof(fv)) == 0);

  fv.set(-1.0f, -0.0f, -1e-30f, -1e30f);
  fv2.set(1.0f, 0.0f, 1e-30f, 1e30f);
  a = v_abs(v_ldu(&fv.x));
  G_ASSERT(memcmp(&a, &fv2, sizeof(a)) == 0);

  fv.set(neg_inf, neg_inf, neg_inf, pos_inf);
  fv2.set(pos_inf, pos_inf, pos_inf, pos_inf);
  a = v_abs(v_ldu(&fv.x));
  G_ASSERT(memcmp(&a, &fv2, sizeof(a)) == 0);

  fv.set(neg_inf, neg_inf, neg_inf, pos_inf);
  fv2.set(1e30f, 1e-30f, -1e30f, -1e-30f);
  a = v_add(v_ldu(&fv.x), v_ldu(&fv2.x));
  G_ASSERT(memcmp(&a, &fv, sizeof(a)) == 0);

  fv.set(neg_inf, neg_inf, neg_inf, pos_inf);
  fv2.set(1e30f, 1e-30f, -1e30f, -1e-30f);
  a = v_sub(v_ldu(&fv.x), v_ldu(&fv2.x));
  G_ASSERT(memcmp(&a, &fv, sizeof(a)) == 0);

  fv.set(neg_inf, pos_inf, neg_inf, pos_inf);
  fv2.set(1e30f, 1e-30f, 1e30f, 1e-30f);
  a = v_mul(v_ldu(&fv.x), v_ldu(&fv2.x));
  G_ASSERT(memcmp(&a, &fv, sizeof(a)) == 0);

  fv.set(neg_inf, neg_inf, neg_inf, pos_inf);
  fv2.set(0.0f, -0.0f, 1e30f, 1e-300f);
  a = v_mul(v_ldu(&fv.x), v_ldu(&fv2.x));
  fv.set(nan, nan, neg_inf, nan);
  G_ASSERT(memcmp(&a, &fv, sizeof(a)) == 0);

  fv.set(1.25f, -2.1f, 0.f, -234.0f);
  fv2.set(1, -3, 0, -234);
  a = v_floor(v_ldu(&fv.x));
  G_ASSERT(memcmp(&a, &fv2, sizeof(a)) == 0);

  fv.set(-0.0f, -1e-30f, 1e-30f, -(1 << 23));
  fv2.set(0, -1, 0, -(1 << 23));
  a = v_floor(v_ldu(&fv.x));
  G_ASSERT(memcmp(&a, &fv2, sizeof(a)) == 0);

  fv.set(1.25f, -2.1f, 0.f, -234.0f);
  fv2.set(2, -2, 0, -234);
  a = v_ceil(v_ldu(&fv.x));
  G_ASSERT(memcmp(&a, &fv2, sizeof(a)) == 0);

  fv.set(-0.0f, -1e-6f, 1e-6f, -(1 << 23));
  fv2.set(0, 0, 1, -(1 << 23));
  a = v_ceil(v_ldu(&fv.x));
  G_ASSERT(memcmp(&a, &fv2, sizeof(a)) == 0);

  fv.set(1.0f, -2.0f, 3.0f, -4.0f);
  fv2.set(0.1f, 0.1f, 0.1f, 0.1f);
  a = v_ldu(&fv.x);
  b = v_ldu(&fv2.x);
  fv2.set(1.0f, 1.0f, 1.0f, 1.0f);
  for (int i = 0; i < 18; i++)
  {
    vec4f c = v_safediv(a, a);
    a = v_mul(a, b);
    G_ASSERT(memcmp(&c, &fv2, sizeof(a)) == 0);
  }

  fv.set(1.0f, -2.0f, 0.0f, -4.0f);
  fv2.set(0.0, -0.0, 0.0, 0.0);
  a = v_ldu(&fv.x);
  b = v_ldu(&fv2.x);
  vec4f c = v_safediv(a, b);
  G_ASSERT(isfinite(c.m128_f32[0]));
  G_ASSERT(isfinite(c.m128_f32[1]));
  G_ASSERT(isfinite(c.m128_f32[2]));
  G_ASSERT(isfinite(c.m128_f32[3]));


  vec3f pa;
  pa.m128_f32[0] = 1;
  pa.m128_f32[1] = 1;
  pa.m128_f32[2] = 1;
  vec3f pb = pa;
  vec3f pp = pa;
  pp.m128_f32[1] = 2.0f;

  vec3f res = closest_point_on_segment(pa, pb, pp);
  G_ASSERT(res.m128_f32[0] == 1.0f && res.m128_f32[1] == 1.0f && res.m128_f32[2] == 1.0f);

  {
    vec4f invalid;  // (0, 1, 0, 1) (0, 1, 1e-15, 2) (1e-15, 1, 0, 3)
    plane3f p0;
    p0.m128_f32[0] = 0;
    p0.m128_f32[1] = 1;
    p0.m128_f32[2] = 0;
    p0.m128_f32[3] = 1;
    plane3f p1;
    p1.m128_f32[0] = 0;
    p1.m128_f32[1] = 1;
    p1.m128_f32[2] = 1e-15;
    p1.m128_f32[3] = 2;
    plane3f p2;
    p2.m128_f32[0] = 1e-15;
    p2.m128_f32[1] = 1;
    p2.m128_f32[2] = 0;
    p2.m128_f32[3] = 3;
    vec3f w = three_plane_intersection(p0, p1, p2, invalid);
    G_ASSERT(isfinite(w.m128_f32[0]) || invalid.m128_f32[0]);
  }

  {
    vec3f start;
    start.m128_f32[0] = 0;
    start.m128_f32[1] = -0.5f;
    start.m128_f32[2] = 0;
    vec3f dir;
    dir.m128_f32[0] = -1e-38;
    dir.m128_f32[1] = 1;
    dir.m128_f32[2] = 1e-38;

    bbox3f box;
    box.bmax.m128_f32[0] = 1;
    box.bmax.m128_f32[1] = 1;
    box.bmax.m128_f32[2] = 1;
    box.bmin.m128_f32[0] = -1;
    box.bmin.m128_f32[1] = -1;
    box.bmin.m128_f32[2] = -1;

    G_ASSERT(v_test_segment_box_intersection_dir(start, dir, box) == 1);
  }
}

} // namespace mathtest

#endif

