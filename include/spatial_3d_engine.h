#pragma once
#include <Arduino.h>
#include <math.h>
#define LGFX_USE_V1
#include <LovyanGFX.hpp>

// ============================================================================
// 3D SPATIAL & PROCEDURAL SHADER ARCHITECTURE FOR DIGITAL KEYCHAIN
// High-Performance 3D Isometric Math, Bevel Shading & Dynamic Light Reflection
// Designed for ESP32 240MHz (LovyanGFX DMA Engine) & Canvas 2D Parity
// ============================================================================

namespace Spatial3D {

// 1. Core 3D Linear Algebra Structures
struct Vec3 {
  float x, y, z;

  constexpr Vec3() : x(0.0f), y(0.0f), z(0.0f) {}
  constexpr Vec3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}

  inline Vec3 operator+(const Vec3& b) const { return Vec3(x + b.x, y + b.y, z + b.z); }
  inline Vec3 operator-(const Vec3& b) const { return Vec3(x - b.x, y - b.y, z - b.z); }
  inline Vec3 operator*(float s) const { return Vec3(x * s, y * s, z * s); }
};

struct Point2D {
  int16_t x, y;
};

// 2. Fast Euler 3D Transformation (Pitch, Yaw, Roll)
static inline Vec3 rotate3D(const Vec3& v, float pitch, float yaw, float roll = 0.0f) {
  // Pitch around X axis
  float cp = cosf(pitch), sp = sinf(pitch);
  float y1 = v.y * cp - v.z * sp;
  float z1 = v.y * sp + v.z * cp;

  // Yaw around Y axis
  float cy = cosf(yaw), sy = sinf(yaw);
  float x2 = v.x * cy + z1 * sy;
  float z2 = -v.x * sy + z1 * cy;

  // Roll around Z axis
  if (fabsf(roll) > 0.001f) {
    float cr = cosf(roll), sr = sinf(roll);
    float x3 = x2 * cr - y1 * sr;
    float y3 = x2 * sr + y1 * cr;
    return Vec3(x3, y3, z2);
  }
  return Vec3(x2, y1, z2);
}

// 3. Isometric Axonometric Projection with Depth Perspective Scaling
static inline Point2D projectIso(const Vec3& v, int cx, int cy, float scale = 1.0f) {
  // Isometric Dimetric Projection:
  // Axonometric factor: X_screen = X - Z * cos(30°), Y_screen = Y + Z * sin(30°)
  // Enhanced with subtle focal perspective depth (D = 180)
  float depth = 180.0f / (180.0f + v.z);
  int16_t sx = (int16_t)(cx + (v.x - v.z * 0.38f) * depth * scale);
  int16_t sy = (int16_t)(cy + (v.y + v.z * 0.22f) * depth * scale);
  return Point2D{ sx, sy };
}

// 4. Facet Normal & Dynamic Lighting Reflection Model
// Calculates Lambertian Diffuse + Blinn-Phong Specular + Fresnel Edge Rim
static inline float calculateFacetLight(const Vec3& v0, const Vec3& v1, const Vec3& v2, const Vec3& lightDir) {
  Vec3 e1 = v1 - v0;
  Vec3 e2 = v2 - v0;
  // Cross product
  float nx = e1.y * e2.z - e1.z * e2.y;
  float ny = e1.z * e2.x - e1.x * e2.z;
  float nz = e1.x * e2.y - e1.y * e2.x;
  float len = sqrtf(nx * nx + ny * ny + nz * nz);
  if (len < 0.0001f) return 0.5f;
  nx /= len; ny /= len; nz /= len;

  // Diffuse: N · L
  float diff = nx * lightDir.x + ny * lightDir.y + nz * lightDir.z;
  if (diff < 0.0f) diff = 0.0f;

  // Specular Blinn-Phong: Half vector H = normalize(L + V), V = (0, 0, 1)
  Vec3 H(lightDir.x, lightDir.y, lightDir.z + 1.0f);
  float hLen = sqrtf(H.x * H.x + H.y * H.y + H.z * H.z);
  float spec = 0.0f;
  if (hLen > 0.0001f) {
    H.x /= hLen; H.y /= hLen; H.z /= hLen;
    float nDotH = nx * H.x + ny * H.y + nz * H.z;
    if (nDotH > 0.0f) {
      spec = powf(nDotH, 12.0f);
    }
  }

  // Fresnel rim glow: (1 - |Nz|)^2
  float fresnel = (1.0f - fabsf(nz)) * 0.25f;

  float intensity = 0.18f + diff * 0.62f + spec * 0.40f + fresnel;
  if (intensity > 1.0f) intensity = 1.0f;
  if (intensity < 0.12f) intensity = 0.12f;
  return intensity;
}

// 5. High-Performance 16-bit RGB565 Color Manipulators
static inline uint16_t colorScale(uint16_t color, float factor) {
  if (factor <= 0.0f) return 0;
  if (factor > 1.0f) factor = 1.0f;
  uint8_t r = (uint8_t)(((color >> 11) & 0x1F) * factor);
  uint8_t g = (uint8_t)(((color >> 5) & 0x3F) * factor);
  uint8_t b = (uint8_t)((color & 0x1F) * factor);
  return (uint16_t)((r << 11) | (g << 5) | b);
}

static inline uint16_t colorBlend(uint16_t c1, uint16_t c2, float t) {
  if (t <= 0.0f) return c1;
  if (t >= 1.0f) return c2;
  uint8_t r1 = (c1 >> 11) & 0x1F, g1 = (c1 >> 5) & 0x3F, b1 = c1 & 0x1F;
  uint8_t r2 = (c2 >> 11) & 0x1F, g2 = (c2 >> 5) & 0x3F, b2 = c2 & 0x1F;
  uint8_t r = (uint8_t)(r1 + (r2 - r1) * t);
  uint8_t g = (uint8_t)(g1 + (g2 - g1) * t);
  uint8_t b = (uint8_t)(b1 + (b2 - b1) * t);
  return (uint16_t)((r << 11) | (g << 5) | b);
}

// Quad fill using 2 triangles
static inline void fillQuad(LGFX_Sprite* spr, const Point2D& p0, const Point2D& p1, const Point2D& p2, const Point2D& p3, uint16_t color) {
  spr->fillTriangle(p0.x, p0.y, p1.x, p1.y, p2.x, p2.y, color);
  spr->fillTriangle(p0.x, p0.y, p2.x, p2.y, p3.x, p3.y, color);
}

// Static Normalized Key Light Source Vector (-0.55, -0.65, 0.52)
static const Vec3 KEY_LIGHT = Vec3(-0.577f, -0.577f, 0.577f);

// ============================================================================
// PART A: THE 10 CYBER WEAPONS (CASES 12 .. 21)
// ============================================================================

// Case 12: Cyber Greatsword (Faceted buster blade with light & dark bevels + glowing core)
static inline void drawCyberGreatsword(LGFX_Sprite* spr, int cx, int cy, float breath, float angle) {
  float pitch = sinf(angle * 1.5f) * 0.18f;
  float yaw   = cosf(angle * 1.8f) * 0.32f;
  float roll  = -0.15f + sinf(angle * 0.9f) * 0.08f;

  // Define 3D Vertices in Model Space
  Vec3 tip(0, -60, 0);
  Vec3 ridgeTop(0, -50, 4);
  Vec3 ridgeMid(0, -5, 5);
  Vec3 ridgeBase(0, 22, 4);
  Vec3 edgeL_top(-12, -42, 0);
  Vec3 edgeL_base(-11, 22, 0);
  Vec3 edgeR_top(12, -42, 0);
  Vec3 edgeR_base(11, 22, 0);

  // Crossguard & Pommel
  Vec3 guardL(-24, 25, 3);
  Vec3 guardR(24, 25, 3);
  Vec3 guardC(0, 27, 6);
  Vec3 gripBase(0, 46, 0);
  Vec3 pommelL(-5, 52, 2);
  Vec3 pommelR(5, 52, 2);
  Vec3 pommelTip(0, 56, 0);

  // Transform all vertices
  Vec3 r_tip = rotate3D(tip, pitch, yaw, roll);
  Vec3 r_rt  = rotate3D(ridgeTop, pitch, yaw, roll);
  Vec3 r_rm  = rotate3D(ridgeMid, pitch, yaw, roll);
  Vec3 r_rb  = rotate3D(ridgeBase, pitch, yaw, roll);
  Vec3 r_elt = rotate3D(edgeL_top, pitch, yaw, roll);
  Vec3 r_elb = rotate3D(edgeL_base, pitch, yaw, roll);
  Vec3 r_ert = rotate3D(edgeR_top, pitch, yaw, roll);
  Vec3 r_erb = rotate3D(edgeR_base, pitch, yaw, roll);

  Vec3 r_gl  = rotate3D(guardL, pitch, yaw, roll);
  Vec3 r_gr  = rotate3D(guardR, pitch, yaw, roll);
  Vec3 r_gc  = rotate3D(guardC, pitch, yaw, roll);
  Vec3 r_gb  = rotate3D(gripBase, pitch, yaw, roll);
  Vec3 r_pl  = rotate3D(pommelL, pitch, yaw, roll);
  Vec3 r_pr  = rotate3D(pommelR, pitch, yaw, roll);
  Vec3 r_pt  = rotate3D(pommelTip, pitch, yaw, roll);

  // Project to screen
  Point2D p_tip = projectIso(r_tip, cx, cy);
  Point2D p_rt  = projectIso(r_rt, cx, cy);
  Point2D p_rm  = projectIso(r_rm, cx, cy);
  Point2D p_rb  = projectIso(r_rb, cx, cy);
  Point2D p_elt = projectIso(r_elt, cx, cy);
  Point2D p_elb = projectIso(r_elb, cx, cy);
  Point2D p_ert = projectIso(r_ert, cx, cy);
  Point2D p_erb = projectIso(r_erb, cx, cy);

  Point2D p_gl  = projectIso(r_gl, cx, cy);
  Point2D p_gr  = projectIso(r_gr, cx, cy);
  Point2D p_gc  = projectIso(r_gc, cx, cy);
  Point2D p_gb  = projectIso(r_gb, cx, cy);
  Point2D p_pl  = projectIso(r_pl, cx, cy);
  Point2D p_pr  = projectIso(r_pr, cx, cy);
  Point2D p_pt  = projectIso(r_pt, cx, cy);

  // 1. Shading: Left Bevel (Light Side) vs Right Bevel (Dark Side)
  float l_left1  = calculateFacetLight(r_rt, r_tip, r_elt, KEY_LIGHT);
  float l_left2  = calculateFacetLight(r_rm, r_rt, r_elt, KEY_LIGHT);
  float l_right1 = calculateFacetLight(r_rt, r_ert, r_tip, KEY_LIGHT);
  float l_right2 = calculateFacetLight(r_rm, r_ert, r_rt, KEY_LIGHT);

  uint16_t colGoldBase = 0xFE40; // Vibrant Gold
  uint16_t c_l1 = colorBlend(colGoldBase, TFT_WHITE, l_left1 * 0.5f);
  uint16_t c_l2 = colorScale(colGoldBase, l_left2 * 0.95f);
  uint16_t c_r1 = colorScale(0x94A0, l_right1 * 0.75f); // Shadowed steel/amber
  uint16_t c_r2 = colorScale(0x7380, l_right2 * 0.65f);

  // Render Beveled Blade Facets
  spr->fillTriangle(p_tip.x, p_tip.y, p_rt.x, p_rt.y, p_elt.x, p_elt.y, c_l1);
  spr->fillTriangle(p_tip.x, p_tip.y, p_ert.x, p_ert.y, p_rt.x, p_rt.y, c_r1);
  fillQuad(spr, p_rt, p_elt, p_elb, p_rm, c_l2);
  fillQuad(spr, p_rt, p_rm, p_erb, p_ert, c_r2);
  fillQuad(spr, p_rm, p_elb, Point2D{(int16_t)(cx), (int16_t)(cy + 22)}, p_rb, c_l2);
  fillQuad(spr, p_rm, p_rb, Point2D{(int16_t)(cx), (int16_t)(cy + 22)}, p_erb, c_r2);

  // 2. Glowing Energy Core (Pulsing Plasma Channel running down the center spine)
  float corePulse = 0.75f + sinf(angle * 6.0f) * 0.25f;
  uint16_t coreCol = colorBlend(TFT_CYAN, TFT_WHITE, corePulse);
  spr->drawLine(p_rt.x, p_rt.y, p_rm.x, p_rm.y, coreCol);
  spr->drawLine(p_rt.x + 1, p_rt.y, p_rm.x + 1, p_rm.y, TFT_WHITE);
  spr->drawLine(p_rm.x, p_rm.y, p_rb.x, p_rb.y, coreCol);

  // 3. Faceted Hexagonal Crossguard
  uint16_t c_guardL = colorScale(0x2965, 1.2f);
  uint16_t c_guardR = colorScale(0x10A2, 0.8f);
  spr->fillTriangle(p_gc.x, p_gc.y, p_gl.x, p_gl.y, p_rb.x, p_rb.y, c_guardL);
  spr->fillTriangle(p_gc.x, p_gc.y, p_rb.x, p_rb.y, p_gr.x, p_gr.y, c_guardR);
  spr->drawCircle(p_gc.x, p_gc.y, 2, TFT_CYAN); // Glowing energy conduit node

  // 4. Grip & Diamond Pommel
  spr->drawLine(p_gc.x, p_gc.y, p_gb.x, p_gb.y, 0x4208);
  spr->drawLine(p_gc.x + 1, p_gc.y, p_gb.x + 1, p_gb.y, 0x8410);
  spr->fillTriangle(p_gb.x, p_gb.y, p_pl.x, p_pl.y, p_pt.x, p_pt.y, 0xCE59);
  spr->fillTriangle(p_gb.x, p_gb.y, p_pt.x, p_pt.y, p_pr.x, p_pr.y, 0x8410);
}

// Case 13: Katana Murasama (Curved HF blood katana with dynamic light sheen & vibration)
static inline void drawKatanaMurasama(LGFX_Sprite* spr, int cx, int cy, float breath, float angle) {
  float yaw   = sinf(angle * 2.2f) * 0.42f;
  float pitch = 0.20f + cosf(angle * 1.6f) * 0.16f;
  float vib   = sinf(angle * 45.0f) * 1.5f; // High frequency blade vibration

  // Vertices along curved katana spline (Ha = edge, Shinogi = ridge, Mune = back)
  Vec3 tip(6, -62, 0);
  Vec3 tipRidge(4, -56, 3);
  Vec3 tipBack(1, -54, 0);

  Vec3 midEdge(4 + vib, -10, 0);
  Vec3 midRidge(1, -10, 3.5f);
  Vec3 midBack(-3, -10, 0);

  Vec3 baseEdge(2, 22, 0);
  Vec3 baseRidge(0, 22, 3);
  Vec3 baseBack(-3, 22, 0);

  Vec3 tsubaL(-9, 24, 4);
  Vec3 tsubaR(9, 24, 4);
  Vec3 tsubaF(0, 25, 7);
  Vec3 tsubaB(0, 23, -2);
  Vec3 gripTip(0, 52, -2);

  // Rotations
  Vec3 r_tip  = rotate3D(tip, pitch, yaw);
  Vec3 r_tr   = rotate3D(tipRidge, pitch, yaw);
  Vec3 r_tb   = rotate3D(tipBack, pitch, yaw);
  Vec3 r_me   = rotate3D(midEdge, pitch, yaw);
  Vec3 r_mr   = rotate3D(midRidge, pitch, yaw);
  Vec3 r_mb   = rotate3D(midBack, pitch, yaw);
  Vec3 r_be   = rotate3D(baseEdge, pitch, yaw);
  Vec3 r_br   = rotate3D(baseRidge, pitch, yaw);
  Vec3 r_bb   = rotate3D(baseBack, pitch, yaw);
  Vec3 r_tl   = rotate3D(tsubaL, pitch, yaw);
  Vec3 r_tr2  = rotate3D(tsubaR, pitch, yaw);
  Vec3 r_tf   = rotate3D(tsubaF, pitch, yaw);
  Vec3 r_tb2  = rotate3D(tsubaB, pitch, yaw);
  Vec3 r_gt   = rotate3D(gripTip, pitch, yaw);

  Point2D p_tip = projectIso(r_tip, cx, cy);
  Point2D p_tr  = projectIso(r_tr, cx, cy);
  Point2D p_tb  = projectIso(r_tb, cx, cy);
  Point2D p_me  = projectIso(r_me, cx, cy);
  Point2D p_mr  = projectIso(r_mr, cx, cy);
  Point2D p_mb  = projectIso(r_mb, cx, cy);
  Point2D p_be  = projectIso(r_be, cx, cy);
  Point2D p_br  = projectIso(r_br, cx, cy);
  Point2D p_bb  = projectIso(r_bb, cx, cy);
  Point2D p_tl  = projectIso(r_tl, cx, cy);
  Point2D p_tr2 = projectIso(r_tr2, cx, cy);
  Point2D p_tf  = projectIso(r_tf, cx, cy);
  Point2D p_tb2 = projectIso(r_tb2, cx, cy);
  Point2D p_gt  = projectIso(r_gt, cx, cy);

  // Bevel Shading: Cutting edge face (Hira) vs Spine face (Mune-te)
  float l_hira = calculateFacetLight(r_tr, r_tip, r_me, KEY_LIGHT);
  float l_mune = calculateFacetLight(r_tr, r_me, r_mb, KEY_LIGHT);

  uint16_t colCrimson = 0xF800; // Murasama Red
  uint16_t c_edge = colorBlend(colCrimson, TFT_WHITE, l_hira * 0.6f);
  uint16_t c_back = colorScale(0x4000, l_mune * 0.7f + 0.3f); // Dark blood steel

  // Draw Tip Kissaki
  spr->fillTriangle(p_tip.x, p_tip.y, p_tr.x, p_tr.y, p_tb.x, p_tb.y, c_edge);
  // Draw Upper Blade Segment
  fillQuad(spr, p_tr, p_me, p_mr, p_tip, c_edge);
  fillQuad(spr, p_tr, p_tip, p_tb, p_mb, c_back);
  // Draw Lower Blade Segment
  fillQuad(spr, p_mr, p_me, p_be, p_br, c_edge);
  fillQuad(spr, p_mr, p_br, p_bb, p_mb, c_back);

  // Glowing High-Frequency Edge Line
  spr->drawLine(p_tip.x, p_tip.y, p_me.x, p_me.y, 0xFFE0); // Electric white-gold arc
  spr->drawLine(p_me.x, p_me.y, p_be.x, p_be.y, 0xFD20);

  // Gold Habaki collar & Octagonal Tsuba
  spr->fillRect(p_br.x - 3, p_br.y - 2, 6, 4, 0xFE60);
  fillQuad(spr, p_tl, p_tf, p_tr2, p_tb2, 0x2104);
  spr->drawTriangle(p_tl.x, p_tl.y, p_tf.x, p_tf.y, p_tr2.x, p_tr2.y, 0x8000);

  // Tsuka (Handle) with braided wrap
  spr->drawLine(p_tf.x, p_tf.y, p_gt.x, p_gt.y, 0x8000);
  spr->drawLine(p_tf.x + 1, p_tf.y, p_gt.x + 1, p_gt.y, TFT_BLACK);
  spr->fillCircle(p_gt.x, p_gt.y, 3, 0xFE60); // Gold Kashira butt
}

// Case 14: Cyberpunk Thermal Katana (Superheated incandescent blade + carbon spine)
static inline void drawThermalKatana(LGFX_Sprite* spr, int cx, int cy, float breath, float angle) {
  float yaw   = cosf(angle * 2.5f) * 0.38f;
  float pitch = sinf(angle * 1.8f) * 0.22f;

  Vec3 tip(0, -60, 0);
  Vec3 edgeTop(-5, -50, 0);
  Vec3 edgeMid(-6, -10, 0);
  Vec3 edgeBase(-5, 20, 0);
  Vec3 heatRail(0, -10, 3.5f); // Center thermal induction rail
  Vec3 spineTop(5, -50, 0);
  Vec3 spineMid(5, -10, 0);
  Vec3 spineBase(4, 20, 0);

  Vec3 r_tip  = rotate3D(tip, pitch, yaw);
  Vec3 r_et   = rotate3D(edgeTop, pitch, yaw);
  Vec3 r_em   = rotate3D(edgeMid, pitch, yaw);
  Vec3 r_eb   = rotate3D(edgeBase, pitch, yaw);
  Vec3 r_hr   = rotate3D(heatRail, pitch, yaw);
  Vec3 r_st   = rotate3D(spineTop, pitch, yaw);
  Vec3 r_sm   = rotate3D(spineMid, pitch, yaw);
  Vec3 r_sb   = rotate3D(spineBase, pitch, yaw);

  Point2D p_tip = projectIso(r_tip, cx, cy);
  Point2D p_et  = projectIso(r_et, cx, cy);
  Point2D p_em  = projectIso(r_em, cx, cy);
  Point2D p_eb  = projectIso(r_eb, cx, cy);
  Point2D p_hr  = projectIso(r_hr, cx, cy);
  Point2D p_st  = projectIso(r_st, cx, cy);
  Point2D p_sm  = projectIso(r_sm, cx, cy);
  Point2D p_sb  = projectIso(r_sb, cx, cy);

  // Carbon Spine: Matte dark composite with bevel
  uint16_t colCarbon = 0x18C3;
  fillQuad(spr, p_tip, p_st, p_sm, p_hr, colCarbon);
  fillQuad(spr, p_hr, p_sm, p_sb, Point2D{(int16_t)(cx + 2), (int16_t)(cy + 20)}, colCarbon);

  // Superheated Cutting Bevel: Glowing gradient from Orange to Incandescent White-Yellow
  float heatPulse = 0.8f + sinf(angle * 10.0f) * 0.2f;
  uint16_t colHeatMid = colorBlend(0xFA60, TFT_YELLOW, heatPulse);
  uint16_t colHeatEdge = colorBlend(TFT_WHITE, TFT_YELLOW, heatPulse);

  fillQuad(spr, p_tip, p_hr, p_em, p_et, colHeatMid);
  fillQuad(spr, p_hr, Point2D{(int16_t)(cx + 2), (int16_t)(cy + 20)}, p_eb, p_em, colHeatMid);

  // Incandescent edge wire
  spr->drawLine(p_tip.x, p_tip.y, p_et.x, p_et.y, colHeatEdge);
  spr->drawLine(p_et.x, p_et.y, p_em.x, p_em.y, colHeatEdge);
  spr->drawLine(p_em.x, p_em.y, p_eb.x, p_eb.y, colHeatEdge);

  // Dual Laser Heating Filament
  spr->drawLine(p_tip.x, p_tip.y, p_hr.x, p_hr.y, TFT_CYAN);
  spr->drawLine(p_hr.x, p_hr.y, cx, cy + 20, TFT_CYAN);

  // Cyber Guard & Ergonomic Grip
  spr->fillRect(cx - 10, cy + 20, 20, 6, 0x0842);
  spr->drawRect(cx - 10, cy + 20, 20, 6, TFT_CYAN);
  spr->fillRect(cx - 4, cy + 26, 8, 22, 0x2124);
  spr->drawFastHLine(cx - 4, cy + 32, 8, TFT_MAGENTA);
  spr->drawFastHLine(cx - 4, cy + 38, 8, TFT_MAGENTA);
}

// Case 15: Plasma Buster (Heavy cannon with 3D hexagonal barrel, cooling vents & vortex core)
static inline void drawPlasmaBuster(LGFX_Sprite* spr, int cx, int cy, float breath, float angle) {
  float yaw   = sinf(angle * 1.5f) * 0.35f;
  float pitch = cosf(angle * 1.8f) * 0.15f;

  // Hexagonal Barrel Prism Vertices in 3D
  const int NUM_V = 6;
  Vec3 muzzle[NUM_V];
  Vec3 breech[NUM_V];
  float r_muzzle = 18.0f;
  float r_breech = 22.0f;

  for (int i = 0; i < NUM_V; i++) {
    float a = i * (6.28318f / NUM_V);
    muzzle[i] = Vec3(cosf(a) * r_muzzle, -38, sinf(a) * r_muzzle);
    breech[i] = Vec3(cosf(a) * r_breech, 18, sinf(a) * r_breech);
  }

  Point2D p_m[NUM_V];
  Point2D p_b[NUM_V];
  Vec3 rot_m[NUM_V], rot_b[NUM_V];

  for (int i = 0; i < NUM_V; i++) {
    rot_m[i] = rotate3D(muzzle[i], pitch, yaw);
    rot_b[i] = rotate3D(breech[i], pitch, yaw);
    p_m[i] = projectIso(rot_m[i], cx, cy);
    p_b[i] = projectIso(rot_b[i], cx, cy);
  }

  // Draw 6 Barrel Facets with Directional Shading
  for (int i = 0; i < NUM_V; i++) {
    int next = (i + 1) % NUM_V;
    float light = calculateFacetLight(rot_m[i], rot_m[next], rot_b[i], KEY_LIGHT);
    uint16_t facetCol = colorScale(0x041F, light * 0.8f + 0.3f); // Deep Cyan Mech Metal
    fillQuad(spr, p_m[i], p_m[next], p_b[next], p_b[i], facetCol);
    spr->drawLine(p_m[i].x, p_m[i].y, p_b[i].x, p_b[i].y, 0x07FF); // Edge chamfer
  }

  // Concentric Accelerator Rings
  for (int step = -20; step <= 6; step += 12) {
    int yOff = step;
    spr->drawEllipse(cx, cy + yOff, (int)(r_muzzle * 0.85f), (int)(r_muzzle * 0.45f), TFT_CYAN);
  }

  // Muzzle Aperture & Spinning Plasma Vortex
  Point2D p_center = projectIso(rotate3D(Vec3(0, -38, 0), pitch, yaw), cx, cy);
  spr->fillCircle(p_center.x, p_center.y, 11, TFT_BLACK); // Cavity depth

  float plasmaPulse = 7.0f + (sinf(angle * 8.0f) + 1.0f) * 3.5f;
  spr->fillCircle(p_center.x, p_center.y, (int)plasmaPulse, TFT_CYAN);
  spr->fillCircle(p_center.x, p_center.y, (int)(plasmaPulse * 0.5f), TFT_WHITE);

  // Electric Charge Arcs
  for (int i = 0; i < 4; i++) {
    float a = angle * 5.0f + i * 1.57f;
    int px = p_center.x + (int)(cosf(a) * 16);
    int py = p_center.y + (int)(sinf(a) * 10);
    spr->drawLine(p_center.x, p_center.y, px, py, TFT_WHITE);
  }
}

// Case 16: Frostmourne (Runeblade with jagged ice bevels, glowing runes & demonic horns)
static inline void drawFrostmourne(LGFX_Sprite* spr, int cx, int cy, float breath, float angle) {
  float yaw   = cosf(angle * 1.3f) * 0.28f;
  float pitch = sinf(angle * 1.7f) * 0.15f;

  Vec3 tip(0, -62, 0);
  Vec3 ridgeTop(0, -48, 4);
  Vec3 ridgeMid(0, -10, 4);
  Vec3 ridgeBase(0, 20, 3);
  Vec3 edgeL1(-11, -44, 0);
  Vec3 edgeL2(-8, -25, 0); // Jagged ice barb
  Vec3 edgeL3(-12, 18, 0);
  Vec3 edgeR1(11, -44, 0);
  Vec3 edgeR2(8, -25, 0);
  Vec3 edgeR3(12, 18, 0);

  Vec3 r_tip = rotate3D(tip, pitch, yaw);
  Vec3 r_rt  = rotate3D(ridgeTop, pitch, yaw);
  Vec3 r_rm  = rotate3D(ridgeMid, pitch, yaw);
  Vec3 r_rb  = rotate3D(ridgeBase, pitch, yaw);
  Vec3 r_l1  = rotate3D(edgeL1, pitch, yaw);
  Vec3 r_l2  = rotate3D(edgeL2, pitch, yaw);
  Vec3 r_l3  = rotate3D(edgeL3, pitch, yaw);
  Vec3 r_r1  = rotate3D(edgeR1, pitch, yaw);
  Vec3 r_r2  = rotate3D(edgeR2, pitch, yaw);
  Vec3 r_r3  = rotate3D(edgeR3, pitch, yaw);

  Point2D p_tip = projectIso(r_tip, cx, cy);
  Point2D p_rt  = projectIso(r_rt, cx, cy);
  Point2D p_rm  = projectIso(r_rm, cx, cy);
  Point2D p_rb  = projectIso(r_rb, cx, cy);
  Point2D p_l1  = projectIso(r_l1, cx, cy);
  Point2D p_l2  = projectIso(r_l2, cx, cy);
  Point2D p_l3  = projectIso(r_l3, cx, cy);
  Point2D p_r1  = projectIso(r_r1, cx, cy);
  Point2D p_r2  = projectIso(r_r2, cx, cy);
  Point2D p_r3  = projectIso(r_r3, cx, cy);

  // Crystalline Glacial Shading: Icy Blue highlight vs Abyssal Navy shadow
  float l_left  = calculateFacetLight(r_rt, r_tip, r_l1, KEY_LIGHT);
  float l_right = calculateFacetLight(r_rt, r_r1, r_tip, KEY_LIGHT);

  uint16_t c_iceLight = colorBlend(0x7FFF, TFT_WHITE, l_left * 0.55f);
  uint16_t c_iceDark  = colorScale(0x0A2B, l_right * 0.7f + 0.3f); // Deep oceanic ice

  // Faceted Blade with Jagged Edges
  spr->fillTriangle(p_tip.x, p_tip.y, p_rt.x, p_rt.y, p_l1.x, p_l1.y, c_iceLight);
  spr->fillTriangle(p_tip.x, p_tip.y, p_r1.x, p_r1.y, p_rt.x, p_rt.y, c_iceDark);
  fillQuad(spr, p_rt, p_l1, p_l2, p_rm, c_iceLight);
  fillQuad(spr, p_rt, p_rm, p_r2, p_r1, c_iceDark);
  fillQuad(spr, p_rm, p_l2, p_l3, p_rb, c_iceLight);
  fillQuad(spr, p_rm, p_rb, p_r3, p_r2, c_iceDark);

  // Glowing Glacial Runes down the Fuller
  float runePulse = 0.6f + sinf(angle * 4.0f) * 0.4f;
  uint16_t runeCol = colorBlend(0x07FF, TFT_WHITE, runePulse);
  for (int y = -35; y <= 5; y += 14) {
    Point2D p_rune = projectIso(rotate3D(Vec3(0, y, 4.5f), pitch, yaw), cx, cy);
    spr->drawPixel(p_rune.x, p_rune.y, runeCol);
    spr->drawPixel(p_rune.x - 1, p_rune.y, runeCol);
    spr->drawPixel(p_rune.x + 1, p_rune.y, runeCol);
    spr->drawPixel(p_rune.x, p_rune.y - 1, runeCol);
  }

  // Demonic Ram Horn Crossguard
  spr->fillTriangle(cx - 24, cy + 22, cx, cy + 20, cx - 12, cy + 12, 0x31A6);
  spr->fillTriangle(cx + 24, cy + 22, cx, cy + 20, cx + 12, cy + 12, 0x2124);
  spr->drawCircle(cx - 6, cy + 22, 2, TFT_CYAN); // Glowing eye
  spr->drawCircle(cx + 6, cy + 22, 2, TFT_CYAN);

  // Grip
  spr->fillRect(cx - 3, cy + 25, 6, 24, 0x10A2);
  spr->fillCircle(cx, cy + 51, 4, 0x52AA); // Spiked skull pommel
}

// Case 17: Mjolnir (Asgardian hammer: 3D beveled block + Norse runes + electric lightning arcs)
static inline void drawMjolnir(LGFX_Sprite* spr, int cx, int cy, float breath, float angle) {
  float yaw   = angle * 1.2f;
  float pitch = sinf(angle * 1.5f) * 0.35f;

  // Hammer Head: 8 Vertices of the Main Box
  Vec3 box[8] = {
    Vec3(-22, -35, -14), Vec3(22, -35, -14),
    Vec3(22, -8, -14),   Vec3(-22, -8, -14),
    Vec3(-22, -35, 14),  Vec3(22, -35, 14),
    Vec3(22, -8, 14),    Vec3(-22, -8, 14)
  };

  Vec3 rot_box[8];
  Point2D p_box[8];
  for (int i = 0; i < 8; i++) {
    rot_box[i] = rotate3D(box[i], pitch, yaw);
    p_box[i] = projectIso(rot_box[i], cx, cy);
  }

  // Face Normals and Shading for Front, Back, Top, Bottom, Left, Right
  // Top Face (0, 1, 5, 4)
  float l_top = calculateFacetLight(rot_box[0], rot_box[1], rot_box[5], KEY_LIGHT);
  fillQuad(spr, p_box[0], p_box[1], p_box[5], p_box[4], colorBlend(0x94B2, TFT_WHITE, l_top * 0.45f));

  // Front Face (4, 5, 6, 7)
  float l_front = calculateFacetLight(rot_box[4], rot_box[5], rot_box[6], KEY_LIGHT);
  fillQuad(spr, p_box[4], p_box[5], p_box[6], p_box[7], colorScale(0x6B4D, l_front * 0.8f + 0.3f));

  // Right Face (1, 2, 6, 5)
  float l_right = calculateFacetLight(rot_box[1], rot_box[2], rot_box[6], KEY_LIGHT);
  fillQuad(spr, p_box[1], p_box[2], p_box[6], p_box[5], colorScale(0x4228, l_right * 0.8f + 0.3f));

  // Left Face (0, 4, 7, 3)
  float l_left = calculateFacetLight(rot_box[0], rot_box[4], rot_box[7], KEY_LIGHT);
  fillQuad(spr, p_box[0], p_box[4], p_box[7], p_box[3], colorScale(0x52AA, l_left * 0.8f + 0.3f));

  // Norse Triskele Knot engraving on front face
  Point2D p_center = projectIso(rotate3D(Vec3(0, -21, 14.5f), pitch, yaw), cx, cy);
  spr->drawCircle(p_center.x, p_center.y, 5, 0x07FF);

  // Cylindrical Handle & Leather Wrap
  Point2D p_hTop = projectIso(rotate3D(Vec3(0, -8, 0), pitch, yaw), cx, cy);
  Point2D p_hBot = projectIso(rotate3D(Vec3(0, 36, 0), pitch, yaw), cx, cy);
  spr->drawLine(p_hTop.x - 2, p_hTop.y, p_hBot.x - 2, p_hBot.y, 0x6260); // Leather brown
  spr->drawLine(p_hTop.x, p_hTop.y, p_hBot.x, p_hBot.y, 0x8A22);
  spr->drawLine(p_hTop.x + 2, p_hTop.y, p_hBot.x + 2, p_hBot.y, 0x4100);
  spr->fillCircle(p_hBot.x, p_hBot.y, 4, 0xAD75); // Silver pommel ring

  // Procedural Lightning Arcs from Vertices
  for (int i = 0; i < 3; i++) {
    int vIdx = (i * 2 + (int)(angle * 8.0f)) % 8;
    int lx = p_box[vIdx].x + (int)(sinf(angle * 20.0f + i) * 14.0f);
    int ly = p_box[vIdx].y - 12 + (int)(cosf(angle * 16.0f + i) * 10.0f);
    spr->drawLine(p_box[vIdx].x, p_box[vIdx].y, lx, ly, TFT_WHITE);
    spr->drawLine(lx, ly, lx + 6, ly - 6, TFT_CYAN);
  }
}

// Case 18: Darksaber (Jet-black obsidian blade + pure white soundwave corona bevel)
static inline void drawDarksaber(LGFX_Sprite* spr, int cx, int cy, float breath, float angle) {
  float yaw   = sinf(angle * 2.0f) * 0.30f;
  float pitch = cosf(angle * 1.5f) * 0.20f;

  Vec3 tip(3, -62, 0); // Angular tanto tip
  Vec3 tipEdge(-5, -52, 0);
  Vec3 tipSpine(5, -50, 0);
  Vec3 midEdge(-6, -10, 0);
  Vec3 midSpine(5, -10, 0);
  Vec3 baseEdge(-5, 20, 0);
  Vec3 baseSpine(4, 20, 0);

  Vec3 r_tip = rotate3D(tip, pitch, yaw);
  Vec3 r_te  = rotate3D(tipEdge, pitch, yaw);
  Vec3 r_ts  = rotate3D(tipSpine, pitch, yaw);
  Vec3 r_me  = rotate3D(midEdge, pitch, yaw);
  Vec3 r_ms  = rotate3D(midSpine, pitch, yaw);
  Vec3 r_be  = rotate3D(baseEdge, pitch, yaw);
  Vec3 r_bs  = rotate3D(baseSpine, pitch, yaw);

  Point2D p_tip = projectIso(r_tip, cx, cy);
  Point2D p_te  = projectIso(r_te, cx, cy);
  Point2D p_ts  = projectIso(r_ts, cx, cy);
  Point2D p_me  = projectIso(r_me, cx, cy);
  Point2D p_ms  = projectIso(r_ms, cx, cy);
  Point2D p_be  = projectIso(r_be, cx, cy);
  Point2D p_bs  = projectIso(r_bs, cx, cy);

  // 1. Blade Core: Pure Obsidian Black
  uint16_t colBlack = 0x0841; // Extremely dark matte charcoal
  spr->fillTriangle(p_tip.x, p_tip.y, p_te.x, p_te.y, p_ts.x, p_ts.y, colBlack);
  fillQuad(spr, p_te, p_ts, p_ms, p_me, colBlack);
  fillQuad(spr, p_me, p_ms, p_bs, p_be, colBlack);

  // 2. Pure White Energy Corona (Double-layer high-contrast bevel)
  spr->drawLine(p_tip.x, p_tip.y, p_te.x, p_te.y, TFT_WHITE);
  spr->drawLine(p_te.x, p_te.y, p_me.x, p_me.y, TFT_WHITE);
  spr->drawLine(p_me.x, p_me.y, p_be.x, p_be.y, TFT_WHITE);

  spr->drawLine(p_tip.x, p_tip.y, p_ts.x, p_ts.y, TFT_WHITE);
  spr->drawLine(p_ts.x, p_ts.y, p_ms.x, p_ms.y, TFT_WHITE);
  spr->drawLine(p_ms.x, p_ms.y, p_bs.x, p_bs.y, TFT_WHITE);

  // Soundwave crackle along the blade edge
  for (int y = -45; y <= 15; y += 8) {
    float wave = sinf(angle * 35.0f + y) * 2.0f;
    spr->drawPixel((int)(cx - 6 + wave), cy + y, TFT_WHITE);
  }

  // Angular Beskar Hilt
  spr->fillRect(cx - 7, cy + 20, 14, 26, 0x73AE); // Beskar Silver
  spr->drawRect(cx - 7, cy + 20, 14, 26, TFT_WHITE);
  spr->fillRect(cx - 4, cy + 26, 8, 12, 0x18C3); // Dark handgrip
}

// Case 19: Dual Energy Daggers (Twin crossed aerodynamic daggers with counter 3D depth)
static inline void drawDualEnergyDaggers(LGFX_Sprite* spr, int cx, int cy, float breath, float angle) {
  float zDepth = sinf(angle * 2.0f) * 14.0f;

  auto drawSingleDagger = [&](int c_x, int c_y, float rollAng, float zOff, uint16_t neonCol) {
    float pitch = 0.25f;
    float yaw   = sinf(angle * 1.8f) * 0.3f;

    Vec3 tip(0, -42, zOff);
    Vec3 midL(-8, -10, zOff);
    Vec3 midR(8, -10, zOff);
    Vec3 ridge(0, -10, zOff + 4.0f);
    Vec3 base(0, 16, zOff);
    Vec3 pommel(0, 36, zOff);

    Vec3 r_tip = rotate3D(tip, pitch, yaw, rollAng);
    Vec3 r_ml  = rotate3D(midL, pitch, yaw, rollAng);
    Vec3 r_mr  = rotate3D(midR, pitch, yaw, rollAng);
    Vec3 r_rg  = rotate3D(ridge, pitch, yaw, rollAng);
    Vec3 r_b   = rotate3D(base, pitch, yaw, rollAng);
    Vec3 r_p   = rotate3D(pommel, pitch, yaw, rollAng);

    Point2D p_tip = projectIso(r_tip, c_x, c_y);
    Point2D p_ml  = projectIso(r_ml, c_x, c_y);
    Point2D p_mr  = projectIso(r_mr, c_x, c_y);
    Point2D p_rg  = projectIso(r_rg, c_x, c_y);
    Point2D p_b   = projectIso(r_b, c_x, c_y);
    Point2D p_p   = projectIso(r_p, c_x, c_y);

    // Bevels: Light side vs dark side
    uint16_t colLight = colorBlend(neonCol, TFT_WHITE, 0.5f);
    uint16_t colDark  = colorScale(neonCol, 0.45f);

    spr->fillTriangle(p_tip.x, p_tip.y, p_ml.x, p_ml.y, p_rg.x, p_rg.y, colLight);
    spr->fillTriangle(p_tip.x, p_tip.y, p_rg.x, p_rg.y, p_mr.x, p_mr.y, colDark);
    spr->fillTriangle(p_ml.x, p_ml.y, p_b.x, p_b.y, p_rg.x, p_rg.y, colLight);
    spr->fillTriangle(p_mr.x, p_mr.y, p_rg.x, p_rg.y, p_b.x, p_b.y, colDark);

    // Glowing core spine
    spr->drawLine(p_tip.x, p_tip.y, p_rg.x, p_rg.y, TFT_WHITE);
    spr->drawLine(p_rg.x, p_rg.y, p_b.x, p_b.y, TFT_WHITE);

    // Hilt & Ring Pommel
    spr->drawLine(p_b.x, p_b.y, p_p.x, p_p.y, 0xCE59);
    spr->drawCircle(p_p.x, p_p.y, 4, neonCol);
  };

  // Depth-sorted rendering: Draw rear dagger first, then front dagger
  if (zDepth >= 0.0f) {
    drawSingleDagger(cx + 8, cy, -0.65f, -zDepth, 0xF81F); // Magenta Dagger behind
    drawSingleDagger(cx - 8, cy, 0.65f, zDepth, 0x07FF);   // Cyan Dagger in front
  } else {
    drawSingleDagger(cx - 8, cy, 0.65f, zDepth, 0x07FF);   // Cyan Dagger behind
    drawSingleDagger(cx + 8, cy, -0.65f, -zDepth, 0xF81F); // Magenta Dagger in front
  }
}

// Case 20: Plasma Scythe (Curved crescent energy blade with titanium shaft & plasma aura)
static inline void drawPlasmaScythe(LGFX_Sprite* spr, int cx, int cy, float breath, float angle) {
  float yaw   = sinf(angle * 1.6f) * 0.40f;
  float pitch = -0.22f + cosf(angle * 1.2f) * 0.18f;

  // Titanium Shaft
  Vec3 shaftTop(0, -52, 0);
  Vec3 shaftBot(0, 50, 0);
  Point2D p_st = projectIso(rotate3D(shaftTop, pitch, yaw), cx, cy);
  Point2D p_sb = projectIso(rotate3D(shaftBot, pitch, yaw), cx, cy);

  spr->drawLine(p_st.x - 1, p_st.y, p_sb.x - 1, p_sb.y, 0xAD55); // Shaft Highlight
  spr->drawLine(p_st.x, p_st.y, p_sb.x, p_sb.y, 0x4A49);     // Shaft Shadow
  spr->fillCircle(p_sb.x, p_sb.y, 3, 0xFE60); // Gold counterweight

  // Mechanical Scythe Head Bracket
  spr->fillTriangle(p_st.x - 12, p_st.y - 4, p_st.x + 8, p_st.y - 8, p_st.x, p_st.y + 6, 0x2965);

  // Curved Crescent Plasma Blade (Multi-faceted energy arc)
  const int NUM_SEGS = 6;
  Point2D outerArc[NUM_SEGS];
  Point2D innerArc[NUM_SEGS];

  for (int i = 0; i < NUM_SEGS; i++) {
    float t_arc = i / (float)(NUM_SEGS - 1);
    float a = 3.14159f * 0.85f - t_arc * 2.2f;
    float r_out = 38.0f + sinf(angle * 6.0f + i) * 2.0f;
    float r_in  = 26.0f;

    Vec3 v_out(cosf(a) * r_out - 10, -32 + sinf(a) * r_out * 0.6f, 2.0f);
    Vec3 v_in(cosf(a) * r_in - 10, -32 + sinf(a) * r_in * 0.6f, -1.0f);

    outerArc[i] = projectIso(rotate3D(v_out, pitch, yaw), cx, cy);
    innerArc[i] = projectIso(rotate3D(v_in, pitch, yaw), cx, cy);
  }

  // Draw Crescent Energy Facets
  uint16_t colViolet = 0xA81F;
  for (int i = 0; i < NUM_SEGS - 1; i++) {
    uint16_t c_facet = (i % 2 == 0) ? colViolet : 0xD81F;
    fillQuad(spr, outerArc[i], outerArc[i+1], innerArc[i+1], innerArc[i], c_facet);
  }

  // White-hot plasma core along the spine of the blade
  for (int i = 0; i < NUM_SEGS - 1; i++) {
    spr->drawLine(outerArc[i].x, outerArc[i].y, outerArc[i+1].x, outerArc[i+1].y, TFT_WHITE);
  }
}

// Case 21: Quantum Blaster (Floating accelerator rails + spinning quantum core + holographic HUD)
static inline void drawQuantumBlaster(LGFX_Sprite* spr, int cx, int cy, float breath, float angle) {
  float yaw   = cosf(angle * 1.8f) * 0.28f;
  float pitch = sinf(angle * 2.5f) * 0.15f;

  // Upper & Lower Magnetic Accelerator Rails
  Vec3 railTopL(-28, -12, 5);
  Vec3 railTopR(18, -12, 5);
  Vec3 railBotL(-28, 12, 5);
  Vec3 railBotR(18, 12, 5);

  Point2D p_tl = projectIso(rotate3D(railTopL, pitch, yaw), cx, cy);
  Point2D p_tr = projectIso(rotate3D(railTopR, pitch, yaw), cx, cy);
  Point2D p_bl = projectIso(rotate3D(railBotL, pitch, yaw), cx, cy);
  Point2D p_br = projectIso(rotate3D(railBotR, pitch, yaw), cx, cy);

  // Draw Rails with Metallic Cyan Bevel
  spr->drawLine(p_tl.x, p_tl.y, p_tr.x, p_tr.y, TFT_CYAN);
  spr->drawLine(p_tl.x, p_tl.y + 3, p_tr.x, p_tr.y + 3, 0x0210);
  spr->drawLine(p_bl.x, p_bl.y, p_br.x, p_br.y, TFT_CYAN);
  spr->drawLine(p_bl.x, p_bl.y - 3, p_br.x, p_br.y - 3, 0x0210);

  // Central Quantum Singularity Chamber
  Point2D p_core = projectIso(rotate3D(Vec3(0, 0, 0), pitch, yaw), cx, cy);
  spr->fillCircle(p_core.x, p_core.y, 8, TFT_BLACK); // Singularity void

  // Dual Counter-Rotating Gyroscopic Rings
  float gyro1 = angle * 4.0f;
  float gyro2 = -angle * 3.5f;

  for (int step = 0; step < 16; step++) {
    float a1 = step * (6.283f / 16.0f);
    Vec3 ring1(cosf(a1) * 16.0f, sinf(a1) * 16.0f * cosf(gyro1), sinf(a1) * 16.0f * sinf(gyro1));
    Point2D pr1 = projectIso(rotate3D(ring1, pitch, yaw), cx, cy);
    spr->drawPixel(pr1.x, pr1.y, TFT_CYAN);

    Vec3 ring2(sinf(a1) * 14.0f * cosf(gyro2), cosf(a1) * 14.0f, sinf(a1) * 14.0f * sinf(gyro2));
    Point2D pr2 = projectIso(rotate3D(ring2, pitch, yaw), cx, cy);
    spr->drawPixel(pr2.x, pr2.y, TFT_MAGENTA);
  }

  // Glowing Core Singularity Flare
  spr->fillCircle(p_core.x, p_core.y, 3, TFT_WHITE);

  // Holographic HUD Targeting Reticle floating forward
  Point2D p_hud = projectIso(rotate3D(Vec3(26, 0, 12), pitch, yaw), cx, cy);
  spr->drawRect(p_hud.x - 6, p_hud.y - 6, 12, 12, TFT_GREEN);
  spr->drawPixel(p_hud.x, p_hud.y, TFT_GREEN);
}

// ============================================================================
// PART B: THE 10 LOVE & BLING GEMS (CASES 22 .. 31)
// ============================================================================

// Case 22: Crystal Faceted Heart (Brilliant-cut 3D heart with 12 polygonal facets)
static inline void drawCrystalFacetedHeart(LGFX_Sprite* spr, int cx, int cy, float breath, float angle) {
  float yaw   = cosf(angle * 1.6f) * 0.45f;
  float pitch = sinf(angle * 2.0f) * 0.32f;
  float s     = 1.0f + sinf(angle * 4.0f) * 0.12f; // Heartbeat expansion

  // 12-Facet Brilliant Cut Heart Topology
  Vec3 centerTable(0, -6 * s, 10 * s); // Elevated central table
  Vec3 topCleft(0, -18 * s, 4 * s);
  Vec3 leftLobe(-18 * s, -24 * s, 2 * s);
  Vec3 rightLobe(18 * s, -24 * s, 2 * s);
  Vec3 leftGirdle(-26 * s, -4 * s, 0);
  Vec3 rightGirdle(26 * s, -4 * s, 0);
  Vec3 bottomCulet(0, 30 * s, -6 * s);

  // Rotate Vertices
  Vec3 r_ct = rotate3D(centerTable, pitch, yaw);
  Vec3 r_tc = rotate3D(topCleft, pitch, yaw);
  Vec3 r_ll = rotate3D(leftLobe, pitch, yaw);
  Vec3 r_rl = rotate3D(rightLobe, pitch, yaw);
  Vec3 r_lg = rotate3D(leftGirdle, pitch, yaw);
  Vec3 r_rg = rotate3D(rightGirdle, pitch, yaw);
  Vec3 r_bc = rotate3D(bottomCulet, pitch, yaw);

  Point2D p_ct = projectIso(r_ct, cx, cy);
  Point2D p_tc = projectIso(r_tc, cx, cy);
  Point2D p_ll = projectIso(r_ll, cx, cy);
  Point2D p_rl = projectIso(r_rl, cx, cy);
  Point2D p_lg = projectIso(r_lg, cx, cy);
  Point2D p_rg = projectIso(r_rg, cx, cy);
  Point2D p_bc = projectIso(r_bc, cx, cy);

  // Calculate Light Reflection for all Facets
  uint16_t colRuby = 0xF800; // Deep Ruby Red

  auto drawFacet = [&](const Vec3& v0, const Vec3& v1, const Vec3& v2, const Point2D& p0, const Point2D& p1, const Point2D& p2) {
    float light = calculateFacetLight(v0, v1, v2, KEY_LIGHT);
    uint16_t col;
    if (light > 0.75f) {
      col = colorBlend(colRuby, TFT_WHITE, (light - 0.75f) * 3.5f); // Specular Glint
    } else {
      col = colorScale(colRuby, light * 0.9f + 0.2f);
    }
    spr->fillTriangle(p0.x, p0.y, p1.x, p1.y, p2.x, p2.y, col);
    spr->drawTriangle(p0.x, p0.y, p1.x, p1.y, p2.x, p2.y, 0xFCAE); // Crystal edge bevel
  };

  // Render Upper Star Facets
  drawFacet(r_ct, r_tc, r_ll, p_ct, p_tc, p_ll);
  drawFacet(r_ct, r_rl, r_tc, p_ct, p_rl, p_tc);
  // Render Girdle Kite Facets
  drawFacet(r_ct, r_ll, r_lg, p_ct, p_ll, p_lg);
  drawFacet(r_ct, r_rg, r_rl, p_ct, p_rg, p_rl);
  // Render Lower Pavilion Facets
  drawFacet(r_ct, r_lg, r_bc, p_ct, p_lg, p_bc);
  drawFacet(r_ct, r_bc, r_rg, p_ct, p_bc, p_rg);

  // Optical Star Glint on table apex
  if (r_ct.z > 2.0f) {
    spr->fillCircle(p_ct.x, p_ct.y, 2, TFT_WHITE);
    spr->drawFastHLine(p_ct.x - 4, p_ct.y, 9, TFT_WHITE);
    spr->drawFastVLine(p_ct.x, p_ct.y - 4, 9, TFT_WHITE);
  }
}

// Case 23: Double Hearts (Interlocking 3D crystal hearts orbiting in 3D depth)
static inline void drawDoubleHearts(LGFX_Sprite* spr, int cx, int cy, float breath, float angle) {
  float zOrbit = sinf(angle * 1.5f) * 16.0f;

  auto drawHeartRing = [&](int ox, int oy, float oz, uint16_t primaryCol, float localAng) {
    float yaw   = sinf(angle * 1.8f + localAng) * 0.35f;
    float pitch = cosf(angle * 1.4f + localAng) * 0.22f;

    const int PTS = 12;
    Point2D p[PTS];
    for (int i = 0; i < PTS; i++) {
      float t_h = i * (6.283f / PTS);
      // Parametric Heart Formula
      float hx = 16.0f * powf(sinf(t_h), 3.0f);
      float hy = -(13.0f * cosf(t_h) - 5.0f * cosf(2*t_h) - 2.0f * cosf(3*t_h) - cosf(4*t_h));
      Vec3 v(hx * 1.1f, hy * 1.1f, oz);
      p[i] = projectIso(rotate3D(v, pitch, yaw), ox, oy);
    }

    for (int i = 0; i < PTS; i++) {
      int next = (i + 1) % PTS;
      uint16_t c_seg = (i % 2 == 0) ? primaryCol : colorBlend(primaryCol, TFT_WHITE, 0.4f);
      spr->drawLine(p[i].x, p[i].y, p[next].x, p[next].y, c_seg);
      spr->drawLine(p[i].x + 1, p[i].y, p[next].x + 1, p[next].y, c_seg);
    }
  };

  // Interlocking 3D Lissajous Orbit with Depth Sorting
  if (zOrbit >= 0.0f) {
    drawHeartRing(cx + 14, cy + 6, -zOrbit, 0x07FF, 3.14f); // Cyan Heart behind
    drawHeartRing(cx - 14, cy - 6, zOrbit, 0xF81F, 0.0f);   // Pink Heart in front
  } else {
    drawHeartRing(cx - 14, cy - 6, zOrbit, 0xF81F, 0.0f);   // Pink Heart behind
    drawHeartRing(cx + 14, cy + 6, -zOrbit, 0x07FF, 3.14f); // Cyan Heart in front
  }
}

// Case 24: ECG Heartbeat (3D Holographic Isometric Waveform with Depth Extrusion)
static inline void drawECGHeartbeat(LGFX_Sprite* spr, int cx, int cy, float breath, float angle) {
  // Isometric Perspective Ground Grid
  for (int z = -20; z <= 20; z += 10) {
    Point2D g1 = projectIso(Vec3(-35, 18, z), cx, cy);
    Point2D g2 = projectIso(Vec3(35, 18, z), cx, cy);
    spr->drawLine(g1.x, g1.y, g2.x, g2.y, 0x0200); // Matrix green grid
  }

  // 3D ECG Coordinates along X-axis
  const int NUM_W = 7;
  Vec3 wave[NUM_W] = {
    Vec3(-36, 0, 0),
    Vec3(-18, 0, 0),
    Vec3(-10, -28, 0), // R peak
    Vec3(0, 24, 0),    // S trough
    Vec3(8, -12, 0),   // T wave
    Vec3(18, 0, 0),
    Vec3(36, 0, 0)
  };

  float pulse = fmodf(angle * 2.5f, 6.283f);
  float extrudeZ = 7.0f;

  for (int i = 0; i < NUM_W - 1; i++) {
    Point2D p_front0 = projectIso(wave[i], cx, cy);
    Point2D p_front1 = projectIso(wave[i+1], cx, cy);
    Point2D p_back0  = projectIso(Vec3(wave[i].x, wave[i].y, extrudeZ), cx, cy);
    Point2D p_back1  = projectIso(Vec3(wave[i+1].x, wave[i+1].y, extrudeZ), cx, cy);

    // Extruded vertical ribbon wall (Darker green)
    fillQuad(spr, p_front0, p_front1, p_back1, p_back0, 0x03E0);
    // Glowing neon front edge
    spr->drawLine(p_front0.x, p_front0.y, p_front1.x, p_front1.y, 0x07E0);
    spr->drawLine(p_front0.x, p_front0.y - 1, p_front1.x, p_front1.y - 1, TFT_WHITE);
  }

  // Leading Cardiac Pulse Dot with Sonar Ripples
  int pulseX = (int)(-36.0f + (pulse / 6.283f) * 72.0f);
  Point2D p_node = projectIso(Vec3(pulseX, 0, 0), cx, cy);
  spr->fillCircle(p_node.x, p_node.y, 3, TFT_WHITE);
  spr->drawCircle(p_node.x, p_node.y, 6 + (int)(sinf(angle * 12.0f) * 2.0f), 0x07E0);
}

// Case 25: Rose Bouquet (3D Origami Faceted Rose with spiral petals & emerald leaves)
static inline void drawRoseBouquet(LGFX_Sprite* spr, int cx, int cy, float breath, float angle) {
  float yaw   = cosf(angle * 1.8f) * 0.32f;
  float pitch = 0.25f + sinf(angle * 1.4f) * 0.16f;

  // Emerald Stem & Leaves
  Point2D p_stemTop = projectIso(rotate3D(Vec3(0, 10, 0), pitch, yaw), cx, cy);
  Point2D p_stemBot = projectIso(rotate3D(Vec3(0, 48, 0), pitch, yaw), cx, cy);
  spr->drawLine(p_stemTop.x, p_stemTop.y, p_stemBot.x, p_stemBot.y, 0x05E0);
  spr->drawLine(p_stemTop.x + 1, p_stemTop.y, p_stemBot.x + 1, p_stemBot.y, 0x07E0);

  // 3D Beveled Leaves
  Point2D p_leafL = projectIso(rotate3D(Vec3(-18, 26, 4), pitch, yaw), cx, cy);
  Point2D p_leafR = projectIso(rotate3D(Vec3(18, 32, -4), pitch, yaw), cx, cy);
  spr->fillTriangle(p_stemTop.x, p_stemTop.y + 12, p_leafL.x, p_leafL.y, p_stemTop.x, p_stemTop.y + 18, 0x04A0);
  spr->fillTriangle(p_stemTop.x, p_stemTop.y + 18, p_leafR.x, p_leafR.y, p_stemTop.x, p_stemTop.y + 24, 0x0380);

  // 3 Tiers of Concentric Faceted Petals
  const int PETALS = 6;
  for (int tier = 2; tier >= 0; tier--) {
    float r = 10.0f + tier * 8.0f;
    float zH = (2 - tier) * 5.0f;
    uint16_t baseCol = (tier == 0) ? 0xF800 : ((tier == 1) ? 0xD000 : 0x9800);

    for (int i = 0; i < PETALS; i++) {
      float a0 = i * (6.283f / PETALS) + tier * 0.5f;
      float a1 = a0 + (6.283f / PETALS);

      Vec3 v0(0, -6, zH + 6);
      Vec3 v1(cosf(a0) * r, -6 + sinf(a0) * r * 0.7f, zH);
      Vec3 v2(cosf(a1) * r, -6 + sinf(a1) * r * 0.7f, zH);

      Vec3 rot0 = rotate3D(v0, pitch, yaw);
      Vec3 rot1 = rotate3D(v1, pitch, yaw);
      Vec3 rot2 = rotate3D(v2, pitch, yaw);

      Point2D p0 = projectIso(rot0, cx, cy);
      Point2D p1 = projectIso(rot1, cx, cy);
      Point2D p2 = projectIso(rot2, cx, cy);

      float light = calculateFacetLight(rot0, rot1, rot2, KEY_LIGHT);
      uint16_t c_petal = colorBlend(baseCol, TFT_WHITE, light * 0.45f);
      spr->fillTriangle(p0.x, p0.y, p1.x, p1.y, p2.x, p2.y, c_petal);
      spr->drawTriangle(p0.x, p0.y, p1.x, p1.y, p2.x, p2.y, 0xFC00); // Highlight edge
    }
  }
}

// Case 26: Diamond Sparkle (Octagonal brilliant-cut diamond with dynamic optical flares)
static inline void drawDiamondSparkle(LGFX_Sprite* spr, int cx, int cy, float breath, float angle) {
  float yaw   = angle * 1.4f;
  float pitch = 0.35f + sinf(angle * 1.2f) * 0.20f;

  const int NUM_F = 8;
  Vec3 crown[NUM_F];
  Vec3 girdle[NUM_F];
  Vec3 culet(0, 24, 0); // Bottom point
  Vec3 table(0, -22, 5); // Elevated table

  for (int i = 0; i < NUM_F; i++) {
    float a = i * (6.283f / NUM_F);
    crown[i]  = Vec3(cosf(a) * 14.0f, -14.0f, sinf(a) * 14.0f);
    girdle[i] = Vec3(cosf(a) * 22.0f, 0.0f, sinf(a) * 22.0f);
  }

  Point2D p_c[NUM_F], p_g[NUM_F];
  Vec3 rot_c[NUM_F], rot_g[NUM_F];
  for (int i = 0; i < NUM_F; i++) {
    rot_c[i] = rotate3D(crown[i], pitch, yaw);
    rot_g[i] = rotate3D(girdle[i], pitch, yaw);
    p_c[i] = projectIso(rot_c[i], cx, cy);
    p_g[i] = projectIso(rot_g[i], cx, cy);
  }

  Point2D p_cul = projectIso(rotate3D(culet, pitch, yaw), cx, cy);
  Point2D p_tab = projectIso(rotate3D(table, pitch, yaw), cx, cy);

  // Render Table & Crown Kites
  for (int i = 0; i < NUM_F; i++) {
    int next = (i + 1) % NUM_F;
    float lightCrown = calculateFacetLight(rot_c[i], rot_c[next], rot_g[i], KEY_LIGHT);
    uint16_t col = (lightCrown > 0.65f) ? TFT_WHITE : colorScale(0x07FF, lightCrown * 0.8f + 0.3f);
    spr->fillTriangle(p_tab.x, p_tab.y, p_c[i].x, p_c[i].y, p_c[next].x, p_c[next].y, col);
    fillQuad(spr, p_c[i], p_c[next], p_g[next], p_g[i], colorScale(0x05BF, lightCrown * 0.7f + 0.3f));
    spr->drawTriangle(p_tab.x, p_tab.y, p_c[i].x, p_c[i].y, p_c[next].x, p_c[next].y, TFT_WHITE);
  }

  // Render Pavilion Triangles tapering to Culet
  for (int i = 0; i < NUM_F; i++) {
    int next = (i + 1) % NUM_F;
    float lightPav = calculateFacetLight(rot_g[i], rot_g[next], rotate3D(culet, pitch, yaw), KEY_LIGHT);
    uint16_t col = colorScale(0x0255, lightPav * 0.9f + 0.2f);
    spr->fillTriangle(p_g[i].x, p_g[i].y, p_g[next].x, p_g[next].y, p_cul.x, p_cul.y, col);
  }

  // 4-Point Prismatic Star Glint
  float glintPulse = 4.0f + sinf(angle * 8.0f) * 2.5f;
  spr->fillCircle(p_tab.x, p_tab.y, 2, TFT_WHITE);
  spr->drawLine(p_tab.x - (int)glintPulse, p_tab.y, p_tab.x + (int)glintPulse, p_tab.y, TFT_WHITE);
  spr->drawLine(p_tab.x, p_tab.y - (int)glintPulse, p_tab.x, p_tab.y + (int)glintPulse, TFT_WHITE);
}

// Case 27: Infinity Ring (3D Mobius-twisted infinity loop with circulating photon particles)
static inline void drawInfinityRing(LGFX_Sprite* spr, int cx, int cy, float breath, float angle) {
  float yaw   = cosf(angle * 1.5f) * 0.45f;
  float pitch = sinf(angle * 1.2f) * 0.30f;

  const int STEPS = 24;
  Point2D path[STEPS];
  for (int i = 0; i < STEPS; i++) {
    float u = i * (6.28318f / STEPS);
    // 3D Lemniscate of Gerono with Mobius height twist
    float x = cosf(u) * 28.0f;
    float y = sinf(2.0f * u) * 14.0f;
    float z = sinf(u) * 12.0f;
    path[i] = projectIso(rotate3D(Vec3(x, y, z), pitch, yaw), cx, cy);
  }

  // Draw 3D Beveled Ribbon Loop
  for (int i = 0; i < STEPS; i++) {
    int next = (i + 1) % STEPS;
    uint16_t col = (i % 2 == 0) ? 0xF81F : 0x07FF; // Gradient between Magenta and Cyan
    spr->drawLine(path[i].x, path[i].y, path[next].x, path[next].y, col);
    spr->drawLine(path[i].x, path[i].y + 1, path[next].x, path[next].y + 1, col);
    spr->drawLine(path[i].x, path[i].y - 1, path[next].x, path[next].y - 1, TFT_WHITE);
  }

  // 4 Circulating Photon Energy Particles
  for (int k = 0; k < 4; k++) {
    float pPos = fmodf(angle * 3.0f + k * 1.57f, 6.28318f);
    float px = cosf(pPos) * 28.0f;
    float py = sinf(2.0f * pPos) * 14.0f;
    float pz = sinf(pPos) * 12.0f;
    Point2D p_pt = projectIso(rotate3D(Vec3(px, py, pz), pitch, yaw), cx, cy);
    spr->fillCircle(p_pt.x, p_pt.y, 2, TFT_WHITE);
  }
}

// Case 28: Neon Wings (Articulated 3D cybernetic wings with yaw sweep & pitch flap)
static inline void drawNeonWings(LGFX_Sprite* spr, int cx, int cy, float breath, float angle) {
  float wingFlap  = cosf(angle * 3.5f) * 0.35f; // Flap up/down
  float wingSweep = sinf(angle * 3.5f) * 0.45f; // Sweep forward/back

  auto drawSingleWing = [&](float sideMul) {
    const int FEATHERS = 4;
    for (int f = 0; f < FEATHERS; f++) {
      float fLen = 38.0f - f * 6.0f;
      float fAngle = (0.2f + f * 0.25f) * sideMul;

      Vec3 root(sideMul * 4.0f, -6 + f * 5, 0);
      Vec3 tip(sideMul * (12.0f + cosf(fAngle) * fLen), -18 + sinf(fAngle) * fLen, f * 3.0f);
      Vec3 barb(sideMul * (8.0f + cosf(fAngle) * (fLen * 0.6f)), -10 + sinf(fAngle) * fLen * 0.6f, -3.0f);

      Vec3 rot_r = rotate3D(root, wingFlap, wingSweep * sideMul);
      Vec3 rot_t = rotate3D(tip, wingFlap, wingSweep * sideMul);
      Vec3 rot_b = rotate3D(barb, wingFlap, wingSweep * sideMul);

      Point2D pr = projectIso(rot_r, cx, cy);
      Point2D pt = projectIso(rot_t, cx, cy);
      Point2D pb = projectIso(rot_b, cx, cy);

      // Beveled Cyber Feather
      spr->fillTriangle(pr.x, pr.y, pt.x, pt.y, pb.x, pb.y, 0x031F); // Dark cyber cyan
      spr->drawLine(pr.x, pr.y, pt.x, pt.y, TFT_CYAN);               // Neon edge
      spr->drawLine(pr.x, pr.y, pb.x, pb.y, TFT_WHITE);
    }
  };

  drawSingleWing(-1.0f); // Left Wing
  drawSingleWing(1.0f);  // Right Wing

  // Central Core Nodule
  spr->fillCircle(cx, cy - 8, 5, TFT_YELLOW);
  spr->drawCircle(cx, cy - 8, 7, 0xFE40);
}

// Case 29: Halo Crown (Floating celestial coronet with 5 golden spires & glowing halo ring)
static inline void drawHaloCrown(LGFX_Sprite* spr, int cx, int cy, float breath, float angle) {
  float yaw   = angle * 1.5f;
  float pitch = 0.35f + sinf(angle * 1.8f) * 0.12f;

  // Floating Golden Aura Halo above
  Point2D pHalo = projectIso(rotate3D(Vec3(0, -32, 0), pitch, yaw), cx, cy);
  spr->drawEllipse(pHalo.x, pHalo.y, 28, 9, TFT_YELLOW);
  spr->drawEllipse(pHalo.x, pHalo.y, 26, 7, TFT_WHITE);

  // 3D Circular Beveled Band with 5 Triangular Spires
  const int SPIRES = 5;
  const float r_base = 24.0f;
  Point2D basePts[SPIRES];
  Point2D spirePts[SPIRES];

  for (int i = 0; i < SPIRES; i++) {
    float a = i * (6.28318f / SPIRES);
    Vec3 vb(cosf(a) * r_base, -10.0f, sinf(a) * r_base);
    Vec3 vs(cosf(a) * (r_base + 2.0f), -26.0f, sinf(a) * (r_base + 2.0f));

    basePts[i]  = projectIso(rotate3D(vb, pitch, yaw), cx, cy);
    spirePts[i] = projectIso(rotate3D(vs, pitch, yaw), cx, cy);
  }

  // Draw 5 Spires with Light / Shadow Facets
  for (int i = 0; i < SPIRES; i++) {
    int next = (i + 1) % SPIRES;
    spr->fillTriangle(basePts[i].x, basePts[i].y, spirePts[i].x, spirePts[i].y, basePts[next].x, basePts[next].y, 0xFE60); // Gold
    spr->drawTriangle(basePts[i].x, basePts[i].y, spirePts[i].x, spirePts[i].y, basePts[next].x, basePts[next].y, TFT_WHITE);
    // Studded Diamond Lozenges on spires
    spr->fillCircle(spirePts[i].x, spirePts[i].y, 2, TFT_WHITE);
  }

  // Lower Beveled Rim
  for (int i = 0; i < SPIRES; i++) {
    int next = (i + 1) % SPIRES;
    spr->drawLine(basePts[i].x, basePts[i].y, basePts[next].x, basePts[next].y, 0x94A0);
    spr->drawLine(basePts[i].x, basePts[i].y + 4, basePts[next].x, basePts[next].y + 4, 0xFE60);
  }
}

// Case 30: Shooting Star (3D Pyramidal star crystal with extruded trailing comet ribbon)
static inline void drawShootingStar(LGFX_Sprite* spr, int cx, int cy, float breath, float angle) {
  float sx = cosf(angle * 2.0f) * 28.0f;
  float sy = sinf(angle * 2.0f) * 22.0f;
  float starYaw = angle * 3.0f;

  // 3D Extruded Comet Tail (trailing into background depth)
  const int TAIL_SEGS = 5;
  for (int i = TAIL_SEGS - 1; i >= 1; i--) {
    float tPrev = angle * 2.0f - (i * 0.22f);
    float tx = cosf(tPrev) * 28.0f;
    float ty = sinf(tPrev) * 22.0f;
    Point2D p_tail = projectIso(Vec3(tx, ty, -i * 8.0f), cx, cy);
    int r_spark = (TAIL_SEGS - i) * 2;
    spr->fillCircle(p_tail.x, p_tail.y, r_spark, (i % 2 == 0) ? 0xFE40 : 0xFD20);
  }

  // 5-Pointed Star Head with 10 Pyramidal Facets (Elevated apex)
  const int PTS = 5;
  Vec3 outer[PTS];
  Vec3 inner[PTS];
  Vec3 apex(0, 0, 7.0f); // High central apex

  for (int i = 0; i < PTS; i++) {
    float a_out = i * (6.283f / PTS);
    float a_in  = a_out + (3.14159f / PTS);
    outer[i] = Vec3(cosf(a_out) * 14.0f, sinf(a_out) * 14.0f, 0);
    inner[i] = Vec3(cosf(a_in) * 6.0f, sinf(a_in) * 6.0f, 0);
  }

  Point2D p_apex = projectIso(rotate3D(apex, 0.2f, starYaw), cx + (int)sx, cy + (int)sy);

  for (int i = 0; i < PTS; i++) {
    int prev_in = (i - 1 + PTS) % PTS;
    Point2D p_out = projectIso(rotate3D(outer[i], 0.2f, starYaw), cx + (int)sx, cy + (int)sy);
    Point2D p_in1 = projectIso(rotate3D(inner[prev_in], 0.2f, starYaw), cx + (int)sx, cy + (int)sy);
    Point2D p_in2 = projectIso(rotate3D(inner[i], 0.2f, starYaw), cx + (int)sx, cy + (int)sy);

    spr->fillTriangle(p_apex.x, p_apex.y, p_out.x, p_out.y, p_in1.x, p_in1.y, TFT_WHITE); // Light bevel
    spr->fillTriangle(p_apex.x, p_apex.y, p_out.x, p_out.y, p_in2.x, p_in2.y, 0xFE40);    // Shadow gold bevel
  }
}

// Case 31: Fireworks (3D Spherical Chrysanthemum Burst with perspective depth sparks)
static inline void drawFireworks(LGFX_Sprite* spr, int cx, int cy, float breath, float angle) {
  float phase = fmodf(angle * 0.8f, 1.0f); // 0.0 to 1.0 explosion cycle
  float r_blast = 42.0f * (1.0f - expf(-phase * 4.5f));
  float gravity = phase * phase * 18.0f; // Gravity droop

  // 16 Streamers distributed evenly on the 3D sphere (Fibonacci lattice)
  const int NUM_SPARKS = 16;
  for (int i = 0; i < NUM_SPARKS; i++) {
    float y_norm = 1.0f - (i / (float)(NUM_SPARKS - 1)) * 2.0f; // -1 to 1
    float r_ring = sqrtf(1.0f - y_norm * y_norm);
    float phi = i * 2.3999632f; // Golden ratio angle

    float x = cosf(phi) * r_ring * r_blast;
    float y = y_norm * r_blast + gravity;
    float z = sinf(phi) * r_ring * r_blast;

    Vec3 rotSpark = rotate3D(Vec3(x, y, z), 0.25f, angle * 1.5f);
    Point2D p_sp = projectIso(rotSpark, cx, cy);

    // Depth-based luminosity & size: Front sparks are brighter & larger
    if (rotSpark.z > 0.0f) {
      spr->fillCircle(p_sp.x, p_sp.y, 2, (i % 2 == 0) ? TFT_YELLOW : TFT_WHITE);
      spr->drawPixel(p_sp.x, p_sp.y - 1, 0xF800); // Ruby glow
    } else {
      spr->drawPixel(p_sp.x, p_sp.y, (i % 2 == 0) ? 0xFE40 : 0xD800);
    }
  }

  // Central Flash Spark during early phase
  if (phase < 0.25f) {
    float flashR = (1.0f - phase / 0.25f) * 6.0f;
    spr->fillCircle(cx, cy, (int)flashR, TFT_WHITE);
  }
}

} // namespace Spatial3D
