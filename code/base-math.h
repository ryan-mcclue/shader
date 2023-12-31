// SPDX-License-Identifier: zlib-acknowledgement
#if !defined(BASE_MATH_H)
#define BASE_MATH_H

// TODO(Ryan): sse_mathfun.h

#include <math.h>

#define SQUARE(x) ((x) * (x))

// TODO(Ryan): Investigate using SIMD, e.g: 
//   _mm_cvtss_f32(_mm_sqrt_ss(_mm_set1_ps(x)));
INTERNAL f32
sqrt_f32(f32 x)
{
  return sqrtf(x);
}

INTERNAL f32
sin_f32(f32 x)
{
  return sinf(x);
}

INTERNAL f32
cos_f32(f32 x)
{
  return cosf(x);
}

INTERNAL f32
tan_f32(f32 x)
{
  return tanf(x);
}

INTERNAL f32
atan2_f32(f32 x, f32 y)
{
  return atan2f(x, y);
}

INTERNAL f32
ln_f32(f32 x)
{
  return logf(x);
}

INTERNAL f64
sqrt_f64(f64 x)
{
  return sqrt(x);
}

INTERNAL f64
sin_f64(f64 x)
{
  return sin(x);
}

INTERNAL f64
cos_f64(f64 x)
{
  return cos(x);
}

INTERNAL f64
tan_f64(f64 x)
{
  return tan(x);
}

INTERNAL f64
ln_f64(f64 x)
{
  return log(x);
}

INTERNAL f32
lerp_f32(f32 a, f32 b, f32 t)
{
  f32 result = 0.0f;
  result = ((b - a) * t) + a; 

  return result;
}

INTERNAL f32
move_toward_f32(f32 current, f32 target, f32 dt, f32 rate)
{
  f32 result = current;

  if (current > target)
  {
    result -= dt * rate;
    if (result < target) result = target; 
  }
  else if (current < target)
  {
    result += dt * rate;
    if (result > target) result = target; 
  }

  return result;
}

INTERNAL u32
round_f32_to_u32(f32 real32)
{
  u32 result = 0;

  result = (u32)roundf(real32);

  return result;
}

INTERNAL i32
round_f32_to_i32(f32 real32)
{
  i32 result = 0;

  result = (i32)roundf(real32);

  return result;
}

INTERNAL i32
floor_f32_to_i32(f32 real32)
{
  i32 result = 0;

  result = (i32)floorf(real32);

  return result;
}

INTERNAL u32
ceil_f32_to_u32(f32 real32)
{
  u32 result = 0;

  result = (u32)ceilf(real32);

  return result;
}

INTERNAL i32
ceil_f32_to_i32(f32 real32)
{
  i32 result = 0;

  result = (i32)ceilf(real32);

  return result;
}

INTERNAL u64
round_to_nearest(u64 val, u64 near)
{
  u64 result = val;

  result += near - 1;
  result -= result % near;
  
  return result;
}

INTERNAL u32 
rand_u32(u32 *seed)
{
  u32 x = *seed;
  x ^= x << 13;
  x ^= x >> 17;
  x ^= x << 5;
  *seed = x;

  return *seed;
}

INTERNAL f32 
rand_unilateral_f32(u32 *seed)
{
  u32 exponent = 127;
  u32 mantissa = rand_u32(seed) >> 9;
  u32 bits = (exponent << 23) | mantissa;
  f32 result = *(f32 *)&bits - 1.0f;

  return result;
}

INTERNAL f32 
rand_bilateral_f32(u32 *seed)
{
  return -1.0f + (2.0f * rand_unilateral_f32(seed));
}

INTERNAL u32 
rand_range_u32(u32 *seed, u32 range)
{
  u32 result = rand_u32(seed) % range;

  return result;
}

INTERNAL i32
rand_range_i32(u32 *seed, i32 min, i32 max)
{
  if (max < min)
  {
    max = min;
  }

  i32 result = min + (i32)rand_u32(seed) % (max - min + 1);

  return result;
}

INTERNAL f32 
rand_range_f32(u32 *seed, f32 min, f32 max)
{
  f32 range = rand_unilateral_f32(seed);
  f32 result = min + range * (max - min);

  return result;
}

INTERNAL f32
map_to_range_f32(f32 start, f32 a, f32 end)
{
  f32 result = 0.0f;

  a = CLAMP(start, a, end);

  result = (end - a) / (end - start);

  return result;
}


#if defined(COMPILER_GCC) && defined(ARCH_X86_64)
  #include <x86intrin.h>

  INTERNAL f32 
  pow_f32(f32 x, f32 y)
  {
    return __builtin_powf(x, y); 
  }

  INTERNAL f32 
  fmodf_f32(f32 x, f32 y)
  {
    return __builtin_fmodf(x, y); 
  }

  INTERNAL f32 
  acos_f32(f32 x)
  {
    return __builtin_acosf(x); 
  }

  INTERNAL f32 
  powi_f32(f32 x, i32 y)
  {
    return __builtin_powif(x, y); 
  }

  INTERNAL u32 
  count_bits_set_u32(u32 val)
  {
    return (u32)__builtin_popcount(val);
  }

  // NOTE(Ryan): This is from most significant bits
  INTERNAL u32 
  count_leading_zeroes_u32(u32 val)
  {
    return (u32)__builtin_clz(val);
  }

  INTERNAL u32 
  count_trailing_zeroes_u32(u32 val)
  {
    return (u32)__builtin_ctz(val);
  }

  INTERNAL u32 
  get_parity_u32(u32 val)
  {
    return (u32)__builtin_parity(val);
  }

  INTERNAL u16 
  endianness_swap_u16(u16 val)
  {
    return __builtin_bswap16(val);
  }

  INTERNAL u32 
  endianness_swap_u32(u32 val)
  {
    return __builtin_bswap32(val);
  }

  INTERNAL u64 
  endianness_swap_u64(u64 val)
  {
    return __builtin_bswap64(val);
  }
#endif



// NOTE(Ryan): To allow for anonymous structs
IGNORE_WARNING_PEDANTIC()
typedef union Vec2F32 Vec2F32;
union Vec2F32
{
  struct
  {
    f32 x, y;
  };
  struct
  {
    f32 w, h;
  };

  f32 elements[2];
  f32 v[2];
};

typedef union Vec2I32 Vec2I32;
union Vec2I32
{
  struct
  {
    i32 x, y;
  };

  struct
  {
    i32 w, h;
  };

  i32 elements[2];
  i32 v[2];
};

typedef union Vec2I64 Vec2I64;
union Vec2I64
{
  struct
  {
    i64 x, y;
  };

  i64 elements[2];
  i64 v[2];
};

typedef union Vec3F32 Vec3F32;
union Vec3F32
{
  struct
  {
    f32 x, y, z;
  };

  struct
  {
    f32 r, g, b;
  };

  struct
  {
    Vec2F32 xy;
    f32 z1;
  };

  struct
  {
    f32 x1;
    Vec2F32 yz;
  };

  f32 elements[3];
  f32 v[3];
};

typedef union Vec3I32 Vec3I32;
union Vec3I32
{
  struct
  {
    i32 x, y, z;
  };

  struct
  {
    i32 r, g, b;
  };

  i32 elements[3];
  i32 v[3];
};

typedef union Vec3I64 Vec3I64;
union Vec3I64
{
  struct
  {
    i64 x, y, z;
  };

  struct
  {
    i64 r, g, b;
  };

  i64 elements[3];
  i64 v[3];
};


typedef union Vec4F32 Vec4F32;
union Vec4F32
{
  struct
  {
    f32 x, y, z, w;
  };

  struct
  {
    Vec2F32 xy, zw;
  };

  struct
  {
    Vec3F32 xyz;
    f32 w1;
  };

  struct
  {
    f32 x1;
    Vec3F32 yzw;
  };

  struct
  {
    f32 r, g, b, a;
  };

  struct
  {
    Vec3F32 rgb;
    f32 a1;
  };

  struct
  {
    f32 r1;
    Vec3F32 gba;
  };

  f32 elements[4];
  f32 v[4];
};

typedef union Vec4I32 Vec4I32;
union Vec4I32
{
  struct
  {
    i32 x, y, z, w;
  };

  struct
  {
    Vec2I32 xy, zw;
  };

  struct
  {
    Vec3I32 xyz;
    i32 w1;
  };

  struct
  {
    i32 x1;
    Vec3I32 yzw;
  };

  struct
  {
    i32 r, g, b, a;
  };

  struct
  {
    Vec3I32 rgb;
    i32 a1;
  };

  struct
  {
    i32 r1;
    Vec3I32 gba;
  };

  i32 elements[4];
  i32 v[4];
};

typedef union Vec4I64 Vec4I64;
union Vec4I64
{
  struct
  {
    i64 x, y, z, w;
  };

  struct
  {
    Vec2I64 xy, zw;
  };

  struct
  {
    Vec3I64 xyz;
    i64 w1;
  };

  struct
  {
    i64 x1;
    Vec3I64 yzw;
  };

  struct
  {
    i64 r, g, b, a;
  };

  struct
  {
    i64 r1;
    Vec3I64 gba;
  };

  struct
  {
    Vec3I64 rgb;
    i64 a1;
  };

  i64 elements[4];
  i64 v[4];
};
IGNORE_WARNING_POP()

#define vec2_f32_dup(a) vec2_f32((a), (a))
#define vec3_f32_dup(a) vec3_f32((a), (a), (a))

INTERNAL Vec2F32
vec2_f32(f32 x, f32 y)
{
  Vec2F32 result = {x, y};
  return result;
}

INTERNAL Vec2F32 
vec2_f32_add(Vec2F32 a, Vec2F32 b) 
{ 
  return vec2_f32(a.x + b.x, a.y + b.y);
}

INTERNAL Vec2F32 
vec2_f32_sub(Vec2F32 a, Vec2F32 b) 
{ 
  return vec2_f32(a.x - b.x, a.y - b.y); 
}

INTERNAL Vec2F32 
vec2_f32_neg(Vec2F32 a) 
{ 
  return vec2_f32(-a.x, -a.y);
}


INTERNAL Vec2F32 
vec2_f32_hadamard(Vec2F32 a, Vec2F32 b) 
{ 
  return vec2_f32(a.x * b.x, a.y * b.y); 
}

INTERNAL Vec2F32 
vec2_f32_mul(Vec2F32 a, f32 b) 
{ 
  return vec2_f32(a.x * b, a.y * b); 
}

INTERNAL Vec2F32 
vec2_f32_div(Vec2F32 a, Vec2F32 b) 
{ 
  return vec2_f32(a.x / b.x, a.y / b.y); 
}

INTERNAL Vec2F32 
vec2_f32_arm(f32 angle) 
{ 
  return vec2_f32(cos_f32(angle), sin_f32(angle)); 
}

INTERNAL Vec2F32
vec2_f32_perp(Vec2F32 a)
{
  return vec2_f32(-a.y, a.x);
}

INTERNAL f32
vec2_f32_angle(Vec2F32 a)
{
  return atan2_f32(a.y, a.x);
}

INTERNAL f32 
vec2_f32_dot(Vec2F32 a, Vec2F32 b) 
{ 
  return (a.x * b.x + a.y * b.y); 
}

INTERNAL f32 
vec2_f32_lengthsq(Vec2F32 v) 
{ 
  return vec2_f32_dot(v, v); 
}

INTERNAL f32 
vec2_f32_length(Vec2F32 v) 
{ 
  return sqrt_f32(vec2_f32_lengthsq(v)); 
}

INTERNAL Vec2F32 
vec2_f32_normalise(Vec2F32 v) 
{ 
  return vec2_f32_mul(v, 1.0f / vec2_f32_length(v)); 
}

INTERNAL Vec2F32 
vec2_f32_lerp(Vec2F32 a, Vec2F32 b, f32 t) 
{ 
  return vec2_f32(a.x * (1 - t) + (b.x * t), a.y * (1 - t) + (b.y * t)); 
}


#if defined(LANG_CPP)
INTERNAL Vec2F32
operator*(f32 s, Vec2F32 a)
{
  return vec2_f32_mul(a, s);
}

INTERNAL Vec2F32
operator*(Vec2F32 a, f32 s)
{
  return vec2_f32_mul(a, s);
}

INTERNAL Vec2F32 &
operator*=(Vec2F32 &a, f32 s)
{
  a = a * s;

  return a;
}

INTERNAL Vec2F32
operator+(Vec2F32 a, Vec2F32 b)
{
  return vec2_f32_add(a, b);
}

INTERNAL Vec2F32 &
operator+=(Vec2F32 &a, Vec2F32 b)
{
  a = a + b;

  return a;
}

INTERNAL Vec2F32
operator-(Vec2F32 a, Vec2F32 b)
{
  return vec2_f32_sub(a, b);
}

INTERNAL Vec2F32 &
operator-=(Vec2F32 &a, Vec2F32 b)
{
  a = a - b;

  return a;
}

INTERNAL Vec2F32
operator-(Vec2F32 a)
{
  return vec2_f32_neg(a);
}
#endif
// TODO(Ryan): Add gcc vector extensions here

INTERNAL Vec2F32
vec2_f32_reflect(Vec2F32 incident, Vec2F32 normal)
{
  Vec2F32 result = ZERO_STRUCT;

  Vec2F32 normal_unit = vec2_f32_normalise(normal);

  result = -2.0f * (vec2_f32_dot(incident, normal_unit)) * normal_unit;

  return result;
}


INTERNAL Vec3F32
vec3_f32(f32 x, f32 y, f32 z)
{
  Vec3F32 result = {x, y, z};
  return result;
}

INTERNAL Vec3F32 
vec3_f32_add(Vec3F32 a, Vec3F32 b) 
{ 
  return vec3_f32(a.x + b.x, a.y + b.y, a.z + b.z); 
}

INTERNAL Vec3F32 
vec3_f32_sub(Vec3F32 a, Vec3F32 b) 
{ 
  return vec3_f32(a.x - b.x, a.y - b.y, a.z - b.z);
}

INTERNAL Vec3F32 
vec3_f32_hadamard(Vec3F32 a, Vec3F32 b) 
{ 
  return vec3_f32(a.x * b.x, a.y * b.y, a.z * b.z); 
}

INTERNAL Vec3F32 
vec3_f32_div(Vec3F32 a, Vec3F32 b) 
{ 
  return vec3_f32(a.x / b.x, a.y / b.y, a.z / b.z); 
}

INTERNAL Vec3F32 
vec3_f32_mul(Vec3F32 a, f32 scale) 
{ 
  return vec3_f32(a.x * scale, a.y * scale, a.z * scale);
}

INTERNAL f32 
vec3_f32_dot(Vec3F32 a, Vec3F32 b) 
{ 
  return (a.x * b.x + a.y * b.y + a.z * b.z); 
}

INTERNAL f32 
vec3_f32_lengthsq(Vec3F32 v) 
{ 
  return vec3_f32_dot(v, v); 
}

INTERNAL f32 
vec3_f32_length(Vec3F32 v) 
{ 
  return sqrt_f32(vec3_f32_lengthsq(v));
}

INTERNAL Vec3F32 
vec3_f32_normalise(Vec3F32 v) 
{ 
  return vec3_f32_mul(v, 1.0f / vec3_f32_length(v));
}

INTERNAL Vec3F32 
vec3_f32_lerp(Vec3F32 a, Vec3F32 b, f32 t) 
{ 
  return vec3_f32(a.x * (1 - t) + (b.x * t), a.y * (1 - t) + (b.y * t), a.z * (1 - t) + (b.z * t)); 
}

INTERNAL Vec3F32 
vec3_f32_cross(Vec3F32 a, Vec3F32 b) 
{ 
  return vec3_f32(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x); 
}


INTERNAL Vec4F32
vec4_f32(f32 x, f32 y, f32 z, f32 w)
{
  Vec4F32 result = {x, y, z, w};
  return result;
}

INTERNAL Vec4F32 
vec4_f32_add(Vec4F32 a, Vec4F32 b) 
{ 
  return vec4_f32(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
}

INTERNAL Vec4F32 
vec4_f32_sub(Vec4F32 a, Vec4F32 b) 
{ 
  return vec4_f32(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w); 
}

INTERNAL Vec4F32 
vec4_f32_hadamard(Vec4F32 a, Vec4F32 b) 
{ 
  return vec4_f32(a.x * b.x, a.y * b.y, a.z * b.z, a.z * b.z); 
}

INTERNAL Vec4F32 
vec4_f32_div(Vec4F32 a, Vec4F32 b) 
{ 
  return vec4_f32(a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w); 
}

INTERNAL Vec4F32 
vec4_f32_mul(Vec4F32 a, f32 scale) 
{ 
  return vec4_f32(a.x * scale, a.y * scale, a.z * scale, a.w * scale); 
}

INTERNAL Vec4F32 
vec4_f32_neg(Vec4F32 a) 
{ 
  return vec4_f32(-a.x, -a.y, -a.z, -a.w);
}

INTERNAL f32 
vec4_f32_dot(Vec4F32 a, Vec4F32 b) 
{ 
  return (a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w); 
}

INTERNAL f32 
vec4_f32_lengthsq(Vec4F32 v) 
{ 
  return vec4_f32_dot(v, v); 
}

INTERNAL f32
vec4_f32_length(Vec4F32 v) 
{ 
  return sqrt_f32(vec4_f32_lengthsq(v)); 
}

INTERNAL Vec4F32 
vec4_f32_normalise(Vec4F32 v) 
{ 
  return vec4_f32_mul(v, 1.0f / vec4_f32_length(v)); 
}

INTERNAL Vec4F32 
vec4_f32_lerp(Vec4F32 a, Vec4F32 b, f32 t)
{ 
  return vec4_f32(a.x * (1 - t) + (b.x * t), a.y * (1 - t) + (b.y * t), a.z * (1 - t) + (b.z * t), a.w * (1 - t) + (b.w * t)); 
}

INTERNAL Vec4F32
whiten(Vec4F32 colour, f32 amount)
{
  Vec4F32 result = ZERO_STRUCT;

  result.r = lerp_f32(colour.r, 1.0f, amount);
  result.g = lerp_f32(colour.g, 1.0f, amount);
  result.b = lerp_f32(colour.b, 1.0f, amount);

  result.a = 1.0f;

  return result;
}

INTERNAL Vec4F32
darken(Vec4F32 colour, f32 amount)
{
  Vec4F32 result = ZERO_STRUCT;

  result.r = lerp_f32(colour.r, 0.0f, amount);
  result.g = lerp_f32(colour.g, 0.0f, amount);
  result.b = lerp_f32(colour.b, 0.0f, amount);

  result.a = 1.0f;

  return result;
}


#if defined(LANG_CPP)
INTERNAL Vec4F32
operator*(f32 s, Vec4F32 a)
{
  return vec4_f32_mul(a, s);
}

INTERNAL Vec4F32
operator*(Vec4F32 a, f32 s)
{
  return vec4_f32_mul(a, s);
}

INTERNAL Vec4F32 &
operator*=(Vec4F32 &a, f32 s)
{
  a = a * s;

  return a;
}

INTERNAL Vec4F32
operator+(Vec4F32 a, Vec4F32 b)
{
  return vec4_f32_add(a, b);
}

INTERNAL Vec4F32 &
operator+=(Vec4F32 &a, Vec4F32 b)
{
  a = a + b;

  return a;
}

INTERNAL Vec4F32
operator-(Vec4F32 a, Vec4F32 b)
{
  return vec4_f32_sub(a, b);
}

INTERNAL Vec4F32 &
operator-=(Vec4F32 &a, Vec4F32 b)
{
  a = a - b;

  return a;
}

INTERNAL Vec4F32
operator-(Vec4F32 a)
{
  return vec4_f32_neg(a);
}
#endif
// TODO(Ryan): Add gcc vector extensions here


INTERNAL Vec2I32
vec2_i32(i32 x, i32 y)
{
  Vec2I32 result = {x, y};
  return result;
}

INTERNAL Vec2I64
vec2_i64(i64 x, i64 y)
{
  Vec2I64 result = {x, y};
  return result;
}

INTERNAL u32
pack_u32_4x8(Vec4F32 val)
{
  u32 result = 0;

  result = (round_f32_to_u32(val.x) << 24 |
            round_f32_to_u32(val.y) << 16 & 0xFF0000 |
            round_f32_to_u32(val.z) << 8 & 0xFF00 |
            round_f32_to_u32(val.w) & 0xFF);

  return result;
}

// TODO(Ryan): Rename to rect
IGNORE_WARNING_PEDANTIC()
typedef union Range2F32 Range2F32;
union Range2F32
{
  struct
  {
    Vec2F32 min, max;
  };

  struct
  {
    Vec2F32 p0, p1;
  };

  struct
  {
    f32 x0, y0, x1, y1;
  };
};
IGNORE_WARNING_POP()

INTERNAL Range2F32
range2_f32(Vec2F32 min, Vec2F32 max)
{
  Range2F32 result = {min, max};
  return result;
}

INTERNAL Range2F32 
range2_f32_shift(Range2F32 r, Vec2F32 v) 
{ 
  r.x0 += v.x; 
  r.y0 += v.y; 
  r.x1 += v.x; 
  r.y1 += v.y; 

  return r; 
}

INTERNAL Range2F32 
range2_f32_pad(Range2F32 r, f32 x) 
{ 
  Vec2F32 min = vec2_f32_sub(r.min, vec2_f32(x, x));
  Vec2F32 max = vec2_f32_add(r.max, vec2_f32(x, x));

  return range2_f32(min, max); 
}

INTERNAL Vec2F32 
range2_f32_centre(Range2F32 r) 
{ 
  return vec2_f32((r.min.x + r.max.x)/2, (r.min.y + r.max.y)/2); 
}

INTERNAL b32 
range2_f32_contains(Range2F32 r, Vec2F32 v) 
{ 
  return (r.min.x <= v.x && v.x <= r.max.x) && (r.min.y <= v.y && v.y <= r.max.y); 
}

INTERNAL Vec2F32 
range2_f32_dim(Range2F32 r) 
{ 
  return vec2_f32(abs_f32(r.max.x - r.min.x), abs_f32(r.max.y - r.min.y)); 
}

#endif
