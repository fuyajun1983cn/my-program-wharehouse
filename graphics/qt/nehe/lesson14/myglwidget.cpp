#include "myglwidget.h"
#include <QTimer>
#include <QKeyEvent>
#include <QMessageBox>
#include <QApplication>
#include <QDebug>

#include <math.h>
#include <GL/glu.h>

namespace {

#define USE_DISPLAY_LIST //使用显示列表

struct FyjStrokeVertex
{
    GLfloat x, y;
};

struct FyjStrokeStrip
{
    int number; //顶点数
    const FyjStrokeVertex *vertices;
};

struct FyjStrokeChar
{
    GLfloat right;
    int number; //strip数
    const FyjStrokeStrip *strips;
};

struct FyjStrokeFont
{
    char *name;     //字体名称
    int quality;    //字体中的字符数量
    GLfloat height;     //字符高度
    const FyjStrokeChar **characters;  //字符表
};

/* char: 0x20 */

static const FyjStrokeStrip ch32st[] =
{
  { 0, NULL }
};

static const FyjStrokeChar ch32 = {104.762f,0,ch32st};

/* char: 0x21 */

static const FyjStrokeVertex ch33st0[] =
{
 {13.3819f,100.0f},
 {13.3819f,33.3333f}
};

static const FyjStrokeVertex ch33st1[] =
{
 {13.3819f,9.5238f},
 {8.62f,4.7619f},
 {13.3819f,0.0f},
 {18.1438f,4.7619f},
 {13.3819f,9.5238f}
};

static const FyjStrokeStrip ch33st[] =
{
 {2,ch33st0},
 {5,ch33st1}
};

static const FyjStrokeChar ch33 = {26.6238f,2,ch33st};

/* char: 0x22 */

static const FyjStrokeVertex ch34st0[] =
{
 {4.02f,100.0f},
 {4.02f,66.6667f}
};

static const FyjStrokeVertex ch34st1[] =
{
 {42.1152f,100.0f},
 {42.1152f,66.6667f}
};

static const FyjStrokeStrip ch34st[] =
{
 {2,ch34st0},
 {2,ch34st1}
};

static const FyjStrokeChar ch34 = {51.4352f,2,ch34st};

/* char: 0x23 */

static const FyjStrokeVertex ch35st0[] =
{
 {41.2952f,119.048f},
 {7.9619f,-33.3333f}
};

static const FyjStrokeVertex ch35st1[] =
{
 {69.8667f,119.048f},
 {36.5333f,-33.3333f}
};

static const FyjStrokeVertex ch35st2[] =
{
 {7.9619f,57.1429f},
 {74.6286f,57.1429f}
};

static const FyjStrokeVertex ch35st3[] =
{
 {3.2f,28.5714f},
 {69.8667f,28.5714f}
};

static const FyjStrokeStrip ch35st[] =
{
 {2,ch35st0},
 {2,ch35st1},
 {2,ch35st2},
 {2,ch35st3}
};

static const FyjStrokeChar ch35 = {79.4886f,4,ch35st};

/* char: 0x24 */

static const FyjStrokeVertex ch36st0[] =
{
 {28.6295f,119.048f},
 {28.6295f,-19.0476f}
};

static const FyjStrokeVertex ch36st1[] =
{
 {47.6771f,119.048f},
 {47.6771f,-19.0476f}
};

static const FyjStrokeVertex ch36st2[] =
{
 {71.4867f,85.7143f},
 {61.9629f,95.2381f},
 {47.6771f,100.0f},
 {28.6295f,100.0f},
 {14.3438f,95.2381f},
 {4.82f,85.7143f},
 {4.82f,76.1905f},
 {9.5819f,66.6667f},
 {14.3438f,61.9048f},
 {23.8676f,57.1429f},
 {52.439f,47.619f},
 {61.9629f,42.8571f},
 {66.7248f,38.0952f},
 {71.4867f,28.5714f},
 {71.4867f,14.2857f},
 {61.9629f,4.7619f},
 {47.6771f,0.0f},
 {28.6295f,0.0f},
 {14.3438f,4.7619f},
 {4.82f,14.2857f}
};

static const FyjStrokeStrip ch36st[] =
{
 {2,ch36st0},
 {2,ch36st1},
 {20,ch36st2}
};

static const FyjStrokeChar ch36 = {76.2067f,3,ch36st};

/* char: 0x25 */

static const FyjStrokeVertex ch37st0[] =
{
 {92.0743f,100.0f},
 {6.36f,0.0f}
};

static const FyjStrokeVertex ch37st1[] =
{
 {30.1695f,100.0f},
 {39.6933f,90.4762f},
 {39.6933f,80.9524f},
 {34.9314f,71.4286f},
 {25.4076f,66.6667f},
 {15.8838f,66.6667f},
 {6.36f,76.1905f},
 {6.36f,85.7143f},
 {11.1219f,95.2381f},
 {20.6457f,100.0f},
 {30.1695f,100.0f},
 {39.6933f,95.2381f},
 {53.979f,90.4762f},
 {68.2648f,90.4762f},
 {82.5505f,95.2381f},
 {92.0743f,100.0f}
};

static const FyjStrokeVertex ch37st2[] =
{
 {73.0267f,33.3333f},
 {63.5029f,28.5714f},
 {58.741f,19.0476f},
 {58.741f,9.5238f},
 {68.2648f,0.0f},
 {77.7886f,0.0f},
 {87.3124f,4.7619f},
 {92.0743f,14.2857f},
 {92.0743f,23.8095f},
 {82.5505f,33.3333f},
 {73.0267f,33.3333f}
};

static const FyjStrokeStrip ch37st[] =
{
 {2,ch37st0},
 {16,ch37st1},
 {11,ch37st2}
};

static const FyjStrokeChar ch37 = {96.5743f,3,ch37st};

/* char: 0x26 */

static const FyjStrokeVertex ch38st0[] =
{
 {101.218f,57.1429f},
 {101.218f,61.9048f},
 {96.4562f,66.6667f},
 {91.6943f,66.6667f},
 {86.9324f,61.9048f},
 {82.1705f,52.381f},
 {72.6467f,28.5714f},
 {63.1229f,14.2857f},
 {53.599f,4.7619f},
 {44.0752f,0.0f},
 {25.0276f,0.0f},
 {15.5038f,4.7619f},
 {10.7419f,9.5238f},
 {5.98f,19.0476f},
 {5.98f,28.5714f},
 {10.7419f,38.0952f},
 {15.5038f,42.8571f},
 {48.8371f,61.9048f},
 {53.599f,66.6667f},
 {58.361f,76.1905f},
 {58.361f,85.7143f},
 {53.599f,95.2381f},
 {44.0752f,100.0f},
 {34.5514f,95.2381f},
 {29.7895f,85.7143f},
 {29.7895f,76.1905f},
 {34.5514f,61.9048f},
 {44.0752f,47.619f},
 {67.8848f,14.2857f},
 {77.4086f,4.7619f},
 {86.9324f,0.0f},
 {96.4562f,0.0f},
 {101.218f,4.7619f},
 {101.218f,9.5238f}
};

static const FyjStrokeStrip ch38st[] =
{
 {34,ch38st0}
};

static const FyjStrokeChar ch38 = {101.758f,1,ch38st};

/* char: 0x27 */

static const FyjStrokeVertex ch39st0[] =
{
 {4.44f,100.0f},
 {4.44f,66.6667f}
};

static const FyjStrokeStrip ch39st[] =
{
 {2,ch39st0}
};

static const FyjStrokeChar ch39 = {13.62f,1,ch39st};

/* char: 0x28 */

static const FyjStrokeVertex ch40st0[] =
{
 {40.9133f,119.048f},
 {31.3895f,109.524f},
 {21.8657f,95.2381f},
 {12.3419f,76.1905f},
 {7.58f,52.381f},
 {7.58f,33.3333f},
 {12.3419f,9.5238f},
 {21.8657f,-9.5238f},
 {31.3895f,-23.8095f},
 {40.9133f,-33.3333f}
};

static const FyjStrokeStrip ch40st[] =
{
 {10,ch40st0}
};

static const FyjStrokeChar ch40 = {47.1733f,1,ch40st};

/* char: 0x29 */

static const FyjStrokeVertex ch41st0[] =
{
 {5.28f,119.048f},
 {14.8038f,109.524f},
 {24.3276f,95.2381f},
 {33.8514f,76.1905f},
 {38.6133f,52.381f},
 {38.6133f,33.3333f},
 {33.8514f,9.5238f},
 {24.3276f,-9.5238f},
 {14.8038f,-23.8095f},
 {5.28f,-33.3333f}
};

static const FyjStrokeStrip ch41st[] =
{
 {10,ch41st0}
};

static const FyjStrokeChar ch41 = {47.5333f,1,ch41st};

/* char: 0x2a */

static const FyjStrokeVertex ch42st0[] =
{
 {30.7695f,71.4286f},
 {30.7695f,14.2857f}
};

static const FyjStrokeVertex ch42st1[] =
{
 {6.96f,57.1429f},
 {54.579f,28.5714f}
};

static const FyjStrokeVertex ch42st2[] =
{
 {54.579f,57.1429f},
 {6.96f,28.5714f}
};

static const FyjStrokeStrip ch42st[] =
{
 {2,ch42st0},
 {2,ch42st1},
 {2,ch42st2}
};

static const FyjStrokeChar ch42 = {59.439f,3,ch42st};

/* char: 0x2b */

static const FyjStrokeVertex ch43st0[] =
{
 {48.8371f,85.7143f},
 {48.8371f,0.0f}
};

static const FyjStrokeVertex ch43st1[] =
{
 {5.98f,42.8571f},
 {91.6943f,42.8571f}
};

static const FyjStrokeStrip ch43st[] =
{
 {2,ch43st0},
 {2,ch43st1}
};

static const FyjStrokeChar ch43 = {97.2543f,2,ch43st};

/* char: 0x2c */

static const FyjStrokeVertex ch44st0[] =
{
 {18.2838f,4.7619f},
 {13.5219f,0.0f},
 {8.76f,4.7619f},
 {13.5219f,9.5238f},
 {18.2838f,4.7619f},
 {18.2838f,-4.7619f},
 {13.5219f,-14.2857f},
 {8.76f,-19.0476f}
};

static const FyjStrokeStrip ch44st[] =
{
 {8,ch44st0}
};

static const FyjStrokeChar ch44 = {26.0638f,1,ch44st};

/* char: 0x2d */

static const FyjStrokeVertex ch45st0[] =
{
 {7.38f,42.8571f},
 {93.0943f,42.8571f}
};

static const FyjStrokeStrip ch45st[] =
{
 {2,ch45st0}
};

static const FyjStrokeChar ch45 = {100.754f,1,ch45st};

/* char: 0x2e */

static const FyjStrokeVertex ch46st0[] =
{
 {13.1019f,9.5238f},
 {8.34f,4.7619f},
 {13.1019f,0.0f},
 {17.8638f,4.7619f},
 {13.1019f,9.5238f}
};

static const FyjStrokeStrip ch46st[] =
{
 {5,ch46st0}
};

static const FyjStrokeChar ch46 = {26.4838f,1,ch46st};

/* char: 0x2f */

static const FyjStrokeVertex ch47st0[] =
{
 {7.24f,-14.2857f},
 {73.9067f,100.0f}
};

static const FyjStrokeStrip ch47st[] =
{
 {2,ch47st0}
};

static const FyjStrokeChar ch47 = {82.1067f,1,ch47st};

/* char: 0x30 */

static const FyjStrokeVertex ch48st0[] =
{
 {33.5514f,100.0f},
 {19.2657f,95.2381f},
 {9.7419f,80.9524f},
 {4.98f,57.1429f},
 {4.98f,42.8571f},
 {9.7419f,19.0476f},
 {19.2657f,4.7619f},
 {33.5514f,0.0f},
 {43.0752f,0.0f},
 {57.361f,4.7619f},
 {66.8848f,19.0476f},
 {71.6467f,42.8571f},
 {71.6467f,57.1429f},
 {66.8848f,80.9524f},
 {57.361f,95.2381f},
 {43.0752f,100.0f},
 {33.5514f,100.0f}
};

static const FyjStrokeStrip ch48st[] =
{
 {17,ch48st0}
};

static const FyjStrokeChar ch48 = {77.0667f,1,ch48st};

/* char: 0x31 */

static const FyjStrokeVertex ch49st0[] =
{
 {11.82f,80.9524f},
 {21.3438f,85.7143f},
 {35.6295f,100.0f},
 {35.6295f,0.0f}
};

static const FyjStrokeStrip ch49st[] =
{
 {4,ch49st0}
};

static const FyjStrokeChar ch49 = {66.5295f,1,ch49st};

/* char: 0x32 */

static const FyjStrokeVertex ch50st0[] =
{
 {10.1819f,76.1905f},
 {10.1819f,80.9524f},
 {14.9438f,90.4762f},
 {19.7057f,95.2381f},
 {29.2295f,100.0f},
 {48.2771f,100.0f},
 {57.801f,95.2381f},
 {62.5629f,90.4762f},
 {67.3248f,80.9524f},
 {67.3248f,71.4286f},
 {62.5629f,61.9048f},
 {53.039f,47.619f},
 {5.42f,0.0f},
 {72.0867f,0.0f}
};

static const FyjStrokeStrip ch50st[] =
{
 {14,ch50st0}
};

static const FyjStrokeChar ch50 = {77.6467f,1,ch50st};

/* char: 0x33 */

static const FyjStrokeVertex ch51st0[] =
{
 {14.5238f,100.0f},
 {66.9048f,100.0f},
 {38.3333f,61.9048f},
 {52.619f,61.9048f},
 {62.1429f,57.1429f},
 {66.9048f,52.381f},
 {71.6667f,38.0952f},
 {71.6667f,28.5714f},
 {66.9048f,14.2857f},
 {57.381f,4.7619f},
 {43.0952f,0.0f},
 {28.8095f,0.0f},
 {14.5238f,4.7619f},
 {9.7619f,9.5238f},
 {5.0f,19.0476f}
};

static const FyjStrokeStrip ch51st[] =
{
 {15,ch51st0}
};

static const FyjStrokeChar ch51 = {77.0467f,1,ch51st};

/* char: 0x34 */

static const FyjStrokeVertex ch52st0[] =
{
 {51.499f,100.0f},
 {3.88f,33.3333f},
 {75.3086f,33.3333f}
};

static const FyjStrokeVertex ch52st1[] =
{
 {51.499f,100.0f},
 {51.499f,0.0f}
};

static const FyjStrokeStrip ch52st[] =
{
 {3,ch52st0},
 {2,ch52st1}
};

static const FyjStrokeChar ch52 = {80.1686f,2,ch52st};

/* char: 0x35 */

static const FyjStrokeVertex ch53st0[] =
{
 {62.0029f,100.0f},
 {14.3838f,100.0f},
 {9.6219f,57.1429f},
 {14.3838f,61.9048f},
 {28.6695f,66.6667f},
 {42.9552f,66.6667f},
 {57.241f,61.9048f},
 {66.7648f,52.381f},
 {71.5267f,38.0952f},
 {71.5267f,28.5714f},
 {66.7648f,14.2857f},
 {57.241f,4.7619f},
 {42.9552f,0.0f},
 {28.6695f,0.0f},
 {14.3838f,4.7619f},
 {9.6219f,9.5238f},
 {4.86f,19.0476f}
};

static const FyjStrokeStrip ch53st[] =
{
 {17,ch53st0}
};

static const FyjStrokeChar ch53 = {77.6867f,1,ch53st};

/* char: 0x36 */

static const FyjStrokeVertex ch54st0[] =
{
 {62.7229f,85.7143f},
 {57.961f,95.2381f},
 {43.6752f,100.0f},
 {34.1514f,100.0f},
 {19.8657f,95.2381f},
 {10.3419f,80.9524f},
 {5.58f,57.1429f},
 {5.58f,33.3333f},
 {10.3419f,14.2857f},
 {19.8657f,4.7619f},
 {34.1514f,0.0f},
 {38.9133f,0.0f},
 {53.199f,4.7619f},
 {62.7229f,14.2857f},
 {67.4848f,28.5714f},
 {67.4848f,33.3333f},
 {62.7229f,47.619f},
 {53.199f,57.1429f},
 {38.9133f,61.9048f},
 {34.1514f,61.9048f},
 {19.8657f,57.1429f},
 {10.3419f,47.619f},
 {5.58f,33.3333f}
};

static const FyjStrokeStrip ch54st[] =
{
 {23,ch54st0}
};

static const FyjStrokeChar ch54 = {73.8048f,1,ch54st};

/* char: 0x37 */

static const FyjStrokeVertex ch55st0[] =
{
 {72.2267f,100.0f},
 {24.6076f,0.0f}
};

static const FyjStrokeVertex ch55st1[] =
{
 {5.56f,100.0f},
 {72.2267f,100.0f}
};

static const FyjStrokeStrip ch55st[] =
{
 {2,ch55st0},
 {2,ch55st1}
};

static const FyjStrokeChar ch55 = {77.2267f,2,ch55st};

/* char: 0x38 */

static const FyjStrokeVertex ch56st0[] =
{
 {29.4095f,100.0f},
 {15.1238f,95.2381f},
 {10.3619f,85.7143f},
 {10.3619f,76.1905f},
 {15.1238f,66.6667f},
 {24.6476f,61.9048f},
 {43.6952f,57.1429f},
 {57.981f,52.381f},
 {67.5048f,42.8571f},
 {72.2667f,33.3333f},
 {72.2667f,19.0476f},
 {67.5048f,9.5238f},
 {62.7429f,4.7619f},
 {48.4571f,0.0f},
 {29.4095f,0.0f},
 {15.1238f,4.7619f},
 {10.3619f,9.5238f},
 {5.6f,19.0476f},
 {5.6f,33.3333f},
 {10.3619f,42.8571f},
 {19.8857f,52.381f},
 {34.1714f,57.1429f},
 {53.219f,61.9048f},
 {62.7429f,66.6667f},
 {67.5048f,76.1905f},
 {67.5048f,85.7143f},
 {62.7429f,95.2381f},
 {48.4571f,100.0f},
 {29.4095f,100.0f}
};

static const FyjStrokeStrip ch56st[] =
{
 {29,ch56st0}
};

static const FyjStrokeChar ch56 = {77.6667f,1,ch56st};

/* char: 0x39 */

static const FyjStrokeVertex ch57st0[] =
{
 {68.5048f,66.6667f},
 {63.7429f,52.381f},
 {54.219f,42.8571f},
 {39.9333f,38.0952f},
 {35.1714f,38.0952f},
 {20.8857f,42.8571f},
 {11.3619f,52.381f},
 {6.6f,66.6667f},
 {6.6f,71.4286f},
 {11.3619f,85.7143f},
 {20.8857f,95.2381f},
 {35.1714f,100.0f},
 {39.9333f,100.0f},
 {54.219f,95.2381f},
 {63.7429f,85.7143f},
 {68.5048f,66.6667f},
 {68.5048f,42.8571f},
 {63.7429f,19.0476f},
 {54.219f,4.7619f},
 {39.9333f,0.0f},
 {30.4095f,0.0f},
 {16.1238f,4.7619f},
 {11.3619f,14.2857f}
};

static const FyjStrokeStrip ch57st[] =
{
 {23,ch57st0}
};

static const FyjStrokeChar ch57 = {74.0648f,1,ch57st};

/* char: 0x3a */

static const FyjStrokeVertex ch58st0[] =
{
 {14.0819f,66.6667f},
 {9.32f,61.9048f},
 {14.0819f,57.1429f},
 {18.8438f,61.9048f},
 {14.0819f,66.6667f}
};

static const FyjStrokeVertex ch58st1[] =
{
 {14.0819f,9.5238f},
 {9.32f,4.7619f},
 {14.0819f,0.0f},
 {18.8438f,4.7619f},
 {14.0819f,9.5238f}
};

static const FyjStrokeStrip ch58st[] =
{
 {5,ch58st0},
 {5,ch58st1}
};

static const FyjStrokeChar ch58 = {26.2238f,2,ch58st};

/* char: 0x3b */

static const FyjStrokeVertex ch59st0[] =
{
 {12.9619f,66.6667f},
 {8.2f,61.9048f},
 {12.9619f,57.1429f},
 {17.7238f,61.9048f},
 {12.9619f,66.6667f}
};

static const FyjStrokeVertex ch59st1[] =
{
 {17.7238f,4.7619f},
 {12.9619f,0.0f},
 {8.2f,4.7619f},
 {12.9619f,9.5238f},
 {17.7238f,4.7619f},
 {17.7238f,-4.7619f},
 {12.9619f,-14.2857f},
 {8.2f,-19.0476f}
};

static const FyjStrokeStrip ch59st[] =
{
 {5,ch59st0},
 {8,ch59st1}
};

static const FyjStrokeChar ch59 = {26.3038f,2,ch59st};

/* char: 0x3c */

static const FyjStrokeVertex ch60st0[] =
{
 {79.2505f,85.7143f},
 {3.06f,42.8571f},
 {79.2505f,0.0f}
};

static const FyjStrokeStrip ch60st[] =
{
 {3,ch60st0}
};

static const FyjStrokeChar ch60 = {81.6105f,1,ch60st};

/* char: 0x3d */

static const FyjStrokeVertex ch61st0[] =
{
 {5.7f,57.1429f},
 {91.4143f,57.1429f}
};

static const FyjStrokeVertex ch61st1[] =
{
 {5.7f,28.5714f},
 {91.4143f,28.5714f}
};

static const FyjStrokeStrip ch61st[] =
{
 {2,ch61st0},
 {2,ch61st1}
};

static const FyjStrokeChar ch61 = {97.2543f,2,ch61st};

/* char: 0x3e */

static const FyjStrokeVertex ch62st0[] =
{
 {2.78f,85.7143f},
 {78.9705f,42.8571f},
 {2.78f,0.0f}
};

static const FyjStrokeStrip ch62st[] =
{
 {3,ch62st0}
};

static const FyjStrokeChar ch62 = {81.6105f,1,ch62st};

/* char: 0x3f */

static const FyjStrokeVertex ch63st0[] =
{
 {8.42f,76.1905f},
 {8.42f,80.9524f},
 {13.1819f,90.4762f},
 {17.9438f,95.2381f},
 {27.4676f,100.0f},
 {46.5152f,100.0f},
 {56.039f,95.2381f},
 {60.801f,90.4762f},
 {65.5629f,80.9524f},
 {65.5629f,71.4286f},
 {60.801f,61.9048f},
 {56.039f,57.1429f},
 {36.9914f,47.619f},
 {36.9914f,33.3333f}
};

static const FyjStrokeVertex ch63st1[] =
{
 {36.9914f,9.5238f},
 {32.2295f,4.7619f},
 {36.9914f,0.0f},
 {41.7533f,4.7619f},
 {36.9914f,9.5238f}
};

static const FyjStrokeStrip ch63st[] =
{
 {14,ch63st0},
 {5,ch63st1}
};

static const FyjStrokeChar ch63 = {73.9029f,2,ch63st};

/* char: 0x40 */

static const FyjStrokeVertex ch64st0[] =
{
 {49.2171f,52.381f},
 {39.6933f,57.1429f},
 {30.1695f,57.1429f},
 {25.4076f,47.619f},
 {25.4076f,42.8571f},
 {30.1695f,33.3333f},
 {39.6933f,33.3333f},
 {49.2171f,38.0952f}
};

static const FyjStrokeVertex ch64st1[] =
{
 {49.2171f,57.1429f},
 {49.2171f,38.0952f},
 {53.979f,33.3333f},
 {63.5029f,33.3333f},
 {68.2648f,42.8571f},
 {68.2648f,47.619f},
 {63.5029f,61.9048f},
 {53.979f,71.4286f},
 {39.6933f,76.1905f},
 {34.9314f,76.1905f},
 {20.6457f,71.4286f},
 {11.1219f,61.9048f},
 {6.36f,47.619f},
 {6.36f,42.8571f},
 {11.1219f,28.5714f},
 {20.6457f,19.0476f},
 {34.9314f,14.2857f},
 {39.6933f,14.2857f},
 {53.979f,19.0476f}
};

static const FyjStrokeStrip ch64st[] =
{
 {8,ch64st0},
 {19,ch64st1}
};

static const FyjStrokeChar ch64 = {74.3648f,2,ch64st};

/* char: 0x41 */

static const FyjStrokeVertex ch65st0[] =
{
 {40.5952f,100.0f},
 {2.5f,0.0f}
};

static const FyjStrokeVertex ch65st1[] =
{
 {40.5952f,100.0f},
 {78.6905f,0.0f}
};

static const FyjStrokeVertex ch65st2[] =
{
 {16.7857f,33.3333f},
 {64.4048f,33.3333f}
};

static const FyjStrokeStrip ch65st[] =
{
 {2,ch65st0},
 {2,ch65st1},
 {2,ch65st2}
};

static const FyjStrokeChar ch65 = {80.4905f,3,ch65st};

/* char: 0x42 */

static const FyjStrokeVertex ch66st0[] =
{
 {11.42f,100.0f},
 {11.42f,0.0f}
};

static const FyjStrokeVertex ch66st1[] =
{
 {11.42f,100.0f},
 {54.2771f,100.0f},
 {68.5629f,95.2381f},
 {73.3248f,90.4762f},
 {78.0867f,80.9524f},
 {78.0867f,71.4286f},
 {73.3248f,61.9048f},
 {68.5629f,57.1429f},
 {54.2771f,52.381f}
};

static const FyjStrokeVertex ch66st2[] =
{
 {11.42f,52.381f},
 {54.2771f,52.381f},
 {68.5629f,47.619f},
 {73.3248f,42.8571f},
 {78.0867f,33.3333f},
 {78.0867f,19.0476f},
 {73.3248f,9.5238f},
 {68.5629f,4.7619f},
 {54.2771f,0.0f},
 {11.42f,0.0f}
};

static const FyjStrokeStrip ch66st[] =
{
 {2,ch66st0},
 {9,ch66st1},
 {10,ch66st2}
};

static const FyjStrokeChar ch66 = {83.6267f,3,ch66st};

/* char: 0x43 */

static const FyjStrokeVertex ch67st0[] =
{
 {78.0886f,76.1905f},
 {73.3267f,85.7143f},
 {63.8029f,95.2381f},
 {54.279f,100.0f},
 {35.2314f,100.0f},
 {25.7076f,95.2381f},
 {16.1838f,85.7143f},
 {11.4219f,76.1905f},
 {6.66f,61.9048f},
 {6.66f,38.0952f},
 {11.4219f,23.8095f},
 {16.1838f,14.2857f},
 {25.7076f,4.7619f},
 {35.2314f,0.0f},
 {54.279f,0.0f},
 {63.8029f,4.7619f},
 {73.3267f,14.2857f},
 {78.0886f,23.8095f}
};

static const FyjStrokeStrip ch67st[] =
{
 {18,ch67st0}
};

static const FyjStrokeChar ch67 = {84.4886f,1,ch67st};

/* char: 0x44 */

static const FyjStrokeVertex ch68st0[] =
{
 {11.96f,100.0f},
 {11.96f,0.0f}
};

static const FyjStrokeVertex ch68st1[] =
{
 {11.96f,100.0f},
 {45.2933f,100.0f},
 {59.579f,95.2381f},
 {69.1029f,85.7143f},
 {73.8648f,76.1905f},
 {78.6267f,61.9048f},
 {78.6267f,38.0952f},
 {73.8648f,23.8095f},
 {69.1029f,14.2857f},
 {59.579f,4.7619f},
 {45.2933f,0.0f},
 {11.96f,0.0f}
};

static const FyjStrokeStrip ch68st[] =
{
 {2,ch68st0},
 {12,ch68st1}
};

static const FyjStrokeChar ch68 = {85.2867f,2,ch68st};

/* char: 0x45 */

static const FyjStrokeVertex ch69st0[] =
{
 {11.42f,100.0f},
 {11.42f,0.0f}
};

static const FyjStrokeVertex ch69st1[] =
{
 {11.42f,100.0f},
 {73.3248f,100.0f}
};

static const FyjStrokeVertex ch69st2[] =
{
 {11.42f,52.381f},
 {49.5152f,52.381f}
};

static const FyjStrokeVertex ch69st3[] =
{
 {11.42f,0.0f},
 {73.3248f,0.0f}
};

static const FyjStrokeStrip ch69st[] =
{
 {2,ch69st0},
 {2,ch69st1},
 {2,ch69st2},
 {2,ch69st3}
};

static const FyjStrokeChar ch69 = {78.1848f,4,ch69st};

/* char: 0x46 */

static const FyjStrokeVertex ch70st0[] =
{
 {11.42f,100.0f},
 {11.42f,0.0f}
};

static const FyjStrokeVertex ch70st1[] =
{
 {11.42f,100.0f},
 {73.3248f,100.0f}
};

static const FyjStrokeVertex ch70st2[] =
{
 {11.42f,52.381f},
 {49.5152f,52.381f}
};

static const FyjStrokeStrip ch70st[] =
{
 {2,ch70st0},
 {2,ch70st1},
 {2,ch70st2}
};

static const FyjStrokeChar ch70 = {78.7448f,3,ch70st};

/* char: 0x47 */

static const FyjStrokeVertex ch71st0[] =
{
 {78.4886f,76.1905f},
 {73.7267f,85.7143f},
 {64.2029f,95.2381f},
 {54.679f,100.0f},
 {35.6314f,100.0f},
 {26.1076f,95.2381f},
 {16.5838f,85.7143f},
 {11.8219f,76.1905f},
 {7.06f,61.9048f},
 {7.06f,38.0952f},
 {11.8219f,23.8095f},
 {16.5838f,14.2857f},
 {26.1076f,4.7619f},
 {35.6314f,0.0f},
 {54.679f,0.0f},
 {64.2029f,4.7619f},
 {73.7267f,14.2857f},
 {78.4886f,23.8095f},
 {78.4886f,38.0952f}
};

static const FyjStrokeVertex ch71st1[] =
{
 {54.679f,38.0952f},
 {78.4886f,38.0952f}
};

static const FyjStrokeStrip ch71st[] =
{
 {19,ch71st0},
 {2,ch71st1}
};

static const FyjStrokeChar ch71 = {89.7686f,2,ch71st};

/* char: 0x48 */

static const FyjStrokeVertex ch72st0[] =
{
 {11.42f,100.0f},
 {11.42f,0.0f}
};

static const FyjStrokeVertex ch72st1[] =
{
 {78.0867f,100.0f},
 {78.0867f,0.0f}
};

static const FyjStrokeVertex ch72st2[] =
{
 {11.42f,52.381f},
 {78.0867f,52.381f}
};

static const FyjStrokeStrip ch72st[] =
{
 {2,ch72st0},
 {2,ch72st1},
 {2,ch72st2}
};

static const FyjStrokeChar ch72 = {89.0867f,3,ch72st};

/* char: 0x49 */

static const FyjStrokeVertex ch73st0[] =
{
 {10.86f,100.0f},
 {10.86f,0.0f}
};

static const FyjStrokeStrip ch73st[] =
{
 {2,ch73st0}
};

static const FyjStrokeChar ch73 = {21.3f,1,ch73st};

/* char: 0x4a */

static const FyjStrokeVertex ch74st0[] =
{
 {50.119f,100.0f},
 {50.119f,23.8095f},
 {45.3571f,9.5238f},
 {40.5952f,4.7619f},
 {31.0714f,0.0f},
 {21.5476f,0.0f},
 {12.0238f,4.7619f},
 {7.2619f,9.5238f},
 {2.5f,23.8095f},
 {2.5f,33.3333f}
};

static const FyjStrokeStrip ch74st[] =
{
 {10,ch74st0}
};

static const FyjStrokeChar ch74 = {59.999f,1,ch74st};

/* char: 0x4b */

static const FyjStrokeVertex ch75st0[] =
{
 {11.28f,100.0f},
 {11.28f,0.0f}
};

static const FyjStrokeVertex ch75st1[] =
{
 {77.9467f,100.0f},
 {11.28f,33.3333f}
};

static const FyjStrokeVertex ch75st2[] =
{
 {35.0895f,57.1429f},
 {77.9467f,0.0f}
};

static const FyjStrokeStrip ch75st[] =
{
 {2,ch75st0},
 {2,ch75st1},
 {2,ch75st2}
};

static const FyjStrokeChar ch75 = {79.3267f,3,ch75st};

/* char: 0x4c */

static const FyjStrokeVertex ch76st0[] =
{
 {11.68f,100.0f},
 {11.68f,0.0f}
};

static const FyjStrokeVertex ch76st1[] =
{
 {11.68f,0.0f},
 {68.8229f,0.0f}
};

static const FyjStrokeStrip ch76st[] =
{
 {2,ch76st0},
 {2,ch76st1}
};

static const FyjStrokeChar ch76 = {71.3229f,2,ch76st};

/* char: 0x4d */

static const FyjStrokeVertex ch77st0[] =
{
 {10.86f,100.0f},
 {10.86f,0.0f}
};

static const FyjStrokeVertex ch77st1[] =
{
 {10.86f,100.0f},
 {48.9552f,0.0f}
};

static const FyjStrokeVertex ch77st2[] =
{
 {87.0505f,100.0f},
 {48.9552f,0.0f}
};

static const FyjStrokeVertex ch77st3[] =
{
 {87.0505f,100.0f},
 {87.0505f,0.0f}
};

static const FyjStrokeStrip ch77st[] =
{
 {2,ch77st0},
 {2,ch77st1},
 {2,ch77st2},
 {2,ch77st3}
};

static const FyjStrokeChar ch77 = {97.2105f,4,ch77st};

/* char: 0x4e */

static const FyjStrokeVertex ch78st0[] =
{
 {11.14f,100.0f},
 {11.14f,0.0f}
};

static const FyjStrokeVertex ch78st1[] =
{
 {11.14f,100.0f},
 {77.8067f,0.0f}
};

static const FyjStrokeVertex ch78st2[] =
{
 {77.8067f,100.0f},
 {77.8067f,0.0f}
};

static const FyjStrokeStrip ch78st[] =
{
 {2,ch78st0},
 {2,ch78st1},
 {2,ch78st2}
};

static const FyjStrokeChar ch78 = {88.8067f,3,ch78st};

/* char: 0x4f */

static const FyjStrokeVertex ch79st0[] =
{
 {34.8114f,100.0f},
 {25.2876f,95.2381f},
 {15.7638f,85.7143f},
 {11.0019f,76.1905f},
 {6.24f,61.9048f},
 {6.24f,38.0952f},
 {11.0019f,23.8095f},
 {15.7638f,14.2857f},
 {25.2876f,4.7619f},
 {34.8114f,0.0f},
 {53.859f,0.0f},
 {63.3829f,4.7619f},
 {72.9067f,14.2857f},
 {77.6686f,23.8095f},
 {82.4305f,38.0952f},
 {82.4305f,61.9048f},
 {77.6686f,76.1905f},
 {72.9067f,85.7143f},
 {63.3829f,95.2381f},
 {53.859f,100.0f},
 {34.8114f,100.0f}
};

static const FyjStrokeStrip ch79st[] =
{
 {21,ch79st0}
};

static const FyjStrokeChar ch79 = {88.8305f,1,ch79st};

/* char: 0x50 */

static const FyjStrokeVertex ch80st0[] =
{
 {12.1f,100.0f},
 {12.1f,0.0f}
};

static const FyjStrokeVertex ch80st1[] =
{
 {12.1f,100.0f},
 {54.9571f,100.0f},
 {69.2429f,95.2381f},
 {74.0048f,90.4762f},
 {78.7667f,80.9524f},
 {78.7667f,66.6667f},
 {74.0048f,57.1429f},
 {69.2429f,52.381f},
 {54.9571f,47.619f},
 {12.1f,47.619f}
};

static const FyjStrokeStrip ch80st[] =
{
 {2,ch80st0},
 {10,ch80st1}
};

static const FyjStrokeChar ch80 = {85.6667f,2,ch80st};

/* char: 0x51 */

static const FyjStrokeVertex ch81st0[] =
{
 {33.8714f,100.0f},
 {24.3476f,95.2381f},
 {14.8238f,85.7143f},
 {10.0619f,76.1905f},
 {5.3f,61.9048f},
 {5.3f,38.0952f},
 {10.0619f,23.8095f},
 {14.8238f,14.2857f},
 {24.3476f,4.7619f},
 {33.8714f,0.0f},
 {52.919f,0.0f},
 {62.4429f,4.7619f},
 {71.9667f,14.2857f},
 {76.7286f,23.8095f},
 {81.4905f,38.0952f},
 {81.4905f,61.9048f},
 {76.7286f,76.1905f},
 {71.9667f,85.7143f},
 {62.4429f,95.2381f},
 {52.919f,100.0f},
 {33.8714f,100.0f}
};

static const FyjStrokeVertex ch81st1[] =
{
 {48.1571f,19.0476f},
 {76.7286f,-9.5238f}
};

static const FyjStrokeStrip ch81st[] =
{
 {21,ch81st0},
 {2,ch81st1}
};

static const FyjStrokeChar ch81 = {88.0905f,2,ch81st};

/* char: 0x52 */

static const FyjStrokeVertex ch82st0[] =
{
 {11.68f,100.0f},
 {11.68f,0.0f}
};

static const FyjStrokeVertex ch82st1[] =
{
 {11.68f,100.0f},
 {54.5371f,100.0f},
 {68.8229f,95.2381f},
 {73.5848f,90.4762f},
 {78.3467f,80.9524f},
 {78.3467f,71.4286f},
 {73.5848f,61.9048f},
 {68.8229f,57.1429f},
 {54.5371f,52.381f},
 {11.68f,52.381f}
};

static const FyjStrokeVertex ch82st2[] =
{
 {45.0133f,52.381f},
 {78.3467f,0.0f}
};

static const FyjStrokeStrip ch82st[] =
{
 {2,ch82st0},
 {10,ch82st1},
 {2,ch82st2}
};

static const FyjStrokeChar ch82 = {82.3667f,3,ch82st};

/* char: 0x53 */

static const FyjStrokeVertex ch83st0[] =
{
 {74.6667f,85.7143f},
 {65.1429f,95.2381f},
 {50.8571f,100.0f},
 {31.8095f,100.0f},
 {17.5238f,95.2381f},
 {8.0f,85.7143f},
 {8.0f,76.1905f},
 {12.7619f,66.6667f},
 {17.5238f,61.9048f},
 {27.0476f,57.1429f},
 {55.619f,47.619f},
 {65.1429f,42.8571f},
 {69.9048f,38.0952f},
 {74.6667f,28.5714f},
 {74.6667f,14.2857f},
 {65.1429f,4.7619f},
 {50.8571f,0.0f},
 {31.8095f,0.0f},
 {17.5238f,4.7619f},
 {8.0f,14.2857f}
};

static const FyjStrokeStrip ch83st[] =
{
 {20,ch83st0}
};

static const FyjStrokeChar ch83 = {80.8267f,1,ch83st};

/* char: 0x54 */

static const FyjStrokeVertex ch84st0[] =
{
 {35.6933f,100.0f},
 {35.6933f,0.0f}
};

static const FyjStrokeVertex ch84st1[] =
{
 {2.36f,100.0f},
 {69.0267f,100.0f}
};

static const FyjStrokeStrip ch84st[] =
{
 {2,ch84st0},
 {2,ch84st1}
};

static const FyjStrokeChar ch84 = {71.9467f,2,ch84st};

/* char: 0x55 */

static const FyjStrokeVertex ch85st0[] =
{
 {11.54f,100.0f},
 {11.54f,28.5714f},
 {16.3019f,14.2857f},
 {25.8257f,4.7619f},
 {40.1114f,0.0f},
 {49.6352f,0.0f},
 {63.921f,4.7619f},
 {73.4448f,14.2857f},
 {78.2067f,28.5714f},
 {78.2067f,100.0f}
};

static const FyjStrokeStrip ch85st[] =
{
 {10,ch85st0}
};

static const FyjStrokeChar ch85 = {89.4867f,1,ch85st};

/* char: 0x56 */

static const FyjStrokeVertex ch86st0[] =
{
 {2.36f,100.0f},
 {40.4552f,0.0f}
};

static const FyjStrokeVertex ch86st1[] =
{
 {78.5505f,100.0f},
 {40.4552f,0.0f}
};

static const FyjStrokeStrip ch86st[] =
{
 {2,ch86st0},
 {2,ch86st1}
};

static const FyjStrokeChar ch86 = {81.6105f,2,ch86st};

/* char: 0x57 */

static const FyjStrokeVertex ch87st0[] =
{
 {2.22f,100.0f},
 {26.0295f,0.0f}
};

static const FyjStrokeVertex ch87st1[] =
{
 {49.839f,100.0f},
 {26.0295f,0.0f}
};

static const FyjStrokeVertex ch87st2[] =
{
 {49.839f,100.0f},
 {73.6486f,0.0f}
};

static const FyjStrokeVertex ch87st3[] =
{
 {97.4581f,100.0f},
 {73.6486f,0.0f}
};

static const FyjStrokeStrip ch87st[] =
{
 {2,ch87st0},
 {2,ch87st1},
 {2,ch87st2},
 {2,ch87st3}
};

static const FyjStrokeChar ch87 = {100.518f,4,ch87st};

/* char: 0x58 */

static const FyjStrokeVertex ch88st0[] =
{
 {2.5f,100.0f},
 {69.1667f,0.0f}
};

static const FyjStrokeVertex ch88st1[] =
{
 {69.1667f,100.0f},
 {2.5f,0.0f}
};

static const FyjStrokeStrip ch88st[] =
{
 {2,ch88st0},
 {2,ch88st1}
};

static const FyjStrokeChar ch88 = {72.3667f,2,ch88st};

/* char: 0x59 */

static const FyjStrokeVertex ch89st0[] =
{
 {1.52f,100.0f},
 {39.6152f,52.381f},
 {39.6152f,0.0f}
};

static const FyjStrokeVertex ch89st1[] =
{
 {77.7105f,100.0f},
 {39.6152f,52.381f}
};

static const FyjStrokeStrip ch89st[] =
{
 {3,ch89st0},
 {2,ch89st1}
};

static const FyjStrokeChar ch89 = {79.6505f,2,ch89st};

/* char: 0x5a */

static const FyjStrokeVertex ch90st0[] =
{
 {69.1667f,100.0f},
 {2.5f,0.0f}
};

static const FyjStrokeVertex ch90st1[] =
{
 {2.5f,100.0f},
 {69.1667f,100.0f}
};

static const FyjStrokeVertex ch90st2[] =
{
 {2.5f,0.0f},
 {69.1667f,0.0f}
};

static const FyjStrokeStrip ch90st[] =
{
 {2,ch90st0},
 {2,ch90st1},
 {2,ch90st2}
};

static const FyjStrokeChar ch90 = {73.7467f,3,ch90st};

/* char: 0x5b */

static const FyjStrokeVertex ch91st0[] =
{
 {7.78f,119.048f},
 {7.78f,-33.3333f}
};

static const FyjStrokeVertex ch91st1[] =
{
 {12.5419f,119.048f},
 {12.5419f,-33.3333f}
};

static const FyjStrokeVertex ch91st2[] =
{
 {7.78f,119.048f},
 {41.1133f,119.048f}
};

static const FyjStrokeVertex ch91st3[] =
{
 {7.78f,-33.3333f},
 {41.1133f,-33.3333f}
};

static const FyjStrokeStrip ch91st[] =
{
 {2,ch91st0},
 {2,ch91st1},
 {2,ch91st2},
 {2,ch91st3}
};

static const FyjStrokeChar ch91 = {46.1133f,4,ch91st};

/* char: 0x5c */

static const FyjStrokeVertex ch92st0[] =
{
 {5.84f,100.0f},
 {72.5067f,-14.2857f}
};

static const FyjStrokeStrip ch92st[] =
{
 {2,ch92st0}
};

static const FyjStrokeChar ch92 = {78.2067f,1,ch92st};

/* char: 0x5d */

static const FyjStrokeVertex ch93st0[] =
{
 {33.0114f,119.048f},
 {33.0114f,-33.3333f}
};

static const FyjStrokeVertex ch93st1[] =
{
 {37.7733f,119.048f},
 {37.7733f,-33.3333f}
};

static const FyjStrokeVertex ch93st2[] =
{
 {4.44f,119.048f},
 {37.7733f,119.048f}
};

static const FyjStrokeVertex ch93st3[] =
{
 {4.44f,-33.3333f},
 {37.7733f,-33.3333f}
};

static const FyjStrokeStrip ch93st[] =
{
 {2,ch93st0},
 {2,ch93st1},
 {2,ch93st2},
 {2,ch93st3}
};

static const FyjStrokeChar ch93 = {46.3933f,4,ch93st};

/* char: 0x5e */

static const FyjStrokeVertex ch94st0[] =
{
 {44.0752f,109.524f},
 {5.98f,42.8571f}
};

static const FyjStrokeVertex ch94st1[] =
{
 {44.0752f,109.524f},
 {82.1705f,42.8571f}
};

static const FyjStrokeStrip ch94st[] =
{
 {2,ch94st0},
 {2,ch94st1}
};

static const FyjStrokeChar ch94 = {90.2305f,2,ch94st};

/* char: 0x5f */

static const FyjStrokeVertex ch95st0[] =
{
 {-1.1f,-33.3333f},
 {103.662f,-33.3333f},
 {103.662f,-28.5714f},
 {-1.1f,-28.5714f},
 {-1.1f,-33.3333f}
};

static const FyjStrokeStrip ch95st[] =
{
 {5,ch95st0}
};

static const FyjStrokeChar ch95 = {104.062f,1,ch95st};

/* char: 0x60 */

static const FyjStrokeVertex ch96st0[] =
{
 {33.0219f,100.0f},
 {56.8314f,71.4286f}
};

static const FyjStrokeVertex ch96st1[] =
{
 {33.0219f,100.0f},
 {28.26f,95.2381f},
 {56.8314f,71.4286f}
};

static const FyjStrokeStrip ch96st[] =
{
 {2,ch96st0},
 {3,ch96st1}
};

static const FyjStrokeChar ch96 = {83.5714f,2,ch96st};

/* char: 0x61 */

static const FyjStrokeVertex ch97st0[] =
{
 {63.8229f,66.6667f},
 {63.8229f,0.0f}
};

static const FyjStrokeVertex ch97st1[] =
{
 {63.8229f,52.381f},
 {54.299f,61.9048f},
 {44.7752f,66.6667f},
 {30.4895f,66.6667f},
 {20.9657f,61.9048f},
 {11.4419f,52.381f},
 {6.68f,38.0952f},
 {6.68f,28.5714f},
 {11.4419f,14.2857f},
 {20.9657f,4.7619f},
 {30.4895f,0.0f},
 {44.7752f,0.0f},
 {54.299f,4.7619f},
 {63.8229f,14.2857f}
};

static const FyjStrokeStrip ch97st[] =
{
 {2,ch97st0},
 {14,ch97st1}
};

static const FyjStrokeChar ch97 = {66.6029f,2,ch97st};

/* char: 0x62 */

static const FyjStrokeVertex ch98st0[] =
{
 {8.76f,100.0f},
 {8.76f,0.0f}
};

static const FyjStrokeVertex ch98st1[] =
{
 {8.76f,52.381f},
 {18.2838f,61.9048f},
 {27.8076f,66.6667f},
 {42.0933f,66.6667f},
 {51.6171f,61.9048f},
 {61.141f,52.381f},
 {65.9029f,38.0952f},
 {65.9029f,28.5714f},
 {61.141f,14.2857f},
 {51.6171f,4.7619f},
 {42.0933f,0.0f},
 {27.8076f,0.0f},
 {18.2838f,4.7619f},
 {8.76f,14.2857f}
};

static const FyjStrokeStrip ch98st[] =
{
 {2,ch98st0},
 {14,ch98st1}
};

static const FyjStrokeChar ch98 = {70.4629f,2,ch98st};

/* char: 0x63 */

static const FyjStrokeVertex ch99st0[] =
{
 {62.6629f,52.381f},
 {53.139f,61.9048f},
 {43.6152f,66.6667f},
 {29.3295f,66.6667f},
 {19.8057f,61.9048f},
 {10.2819f,52.381f},
 {5.52f,38.0952f},
 {5.52f,28.5714f},
 {10.2819f,14.2857f},
 {19.8057f,4.7619f},
 {29.3295f,0.0f},
 {43.6152f,0.0f},
 {53.139f,4.7619f},
 {62.6629f,14.2857f}
};

static const FyjStrokeStrip ch99st[] =
{
 {14,ch99st0}
};

static const FyjStrokeChar ch99 = {68.9229f,1,ch99st};

/* char: 0x64 */

static const FyjStrokeVertex ch100st0[] =
{
 {61.7829f,100.0f},
 {61.7829f,0.0f}
};

static const FyjStrokeVertex ch100st1[] =
{
 {61.7829f,52.381f},
 {52.259f,61.9048f},
 {42.7352f,66.6667f},
 {28.4495f,66.6667f},
 {18.9257f,61.9048f},
 {9.4019f,52.381f},
 {4.64f,38.0952f},
 {4.64f,28.5714f},
 {9.4019f,14.2857f},
 {18.9257f,4.7619f},
 {28.4495f,0.0f},
 {42.7352f,0.0f},
 {52.259f,4.7619f},
 {61.7829f,14.2857f}
};

static const FyjStrokeStrip ch100st[] =
{
 {2,ch100st0},
 {14,ch100st1}
};

static const FyjStrokeChar ch100 = {70.2629f,2,ch100st};

/* char: 0x65 */

static const FyjStrokeVertex ch101st0[] =
{
 {5.72f,38.0952f},
 {62.8629f,38.0952f},
 {62.8629f,47.619f},
 {58.101f,57.1429f},
 {53.339f,61.9048f},
 {43.8152f,66.6667f},
 {29.5295f,66.6667f},
 {20.0057f,61.9048f},
 {10.4819f,52.381f},
 {5.72f,38.0952f},
 {5.72f,28.5714f},
 {10.4819f,14.2857f},
 {20.0057f,4.7619f},
 {29.5295f,0.0f},
 {43.8152f,0.0f},
 {53.339f,4.7619f},
 {62.8629f,14.2857f}
};

static const FyjStrokeStrip ch101st[] =
{
 {17,ch101st0}
};

static const FyjStrokeChar ch101 = {68.5229f,1,ch101st};

/* char: 0x66 */

static const FyjStrokeVertex ch102st0[] =
{
 {38.7752f,100.0f},
 {29.2514f,100.0f},
 {19.7276f,95.2381f},
 {14.9657f,80.9524f},
 {14.9657f,0.0f}
};

static const FyjStrokeVertex ch102st1[] =
{
 {0.68f,66.6667f},
 {34.0133f,66.6667f}
};

static const FyjStrokeStrip ch102st[] =
{
 {5,ch102st0},
 {2,ch102st1}
};

static const FyjStrokeChar ch102 = {38.6552f,2,ch102st};

/* char: 0x67 */

static const FyjStrokeVertex ch103st0[] =
{
 {62.5029f,66.6667f},
 {62.5029f,-9.5238f},
 {57.741f,-23.8095f},
 {52.979f,-28.5714f},
 {43.4552f,-33.3333f},
 {29.1695f,-33.3333f},
 {19.6457f,-28.5714f}
};

static const FyjStrokeVertex ch103st1[] =
{
 {62.5029f,52.381f},
 {52.979f,61.9048f},
 {43.4552f,66.6667f},
 {29.1695f,66.6667f},
 {19.6457f,61.9048f},
 {10.1219f,52.381f},
 {5.36f,38.0952f},
 {5.36f,28.5714f},
 {10.1219f,14.2857f},
 {19.6457f,4.7619f},
 {29.1695f,0.0f},
 {43.4552f,0.0f},
 {52.979f,4.7619f},
 {62.5029f,14.2857f}
};

static const FyjStrokeStrip ch103st[] =
{
 {7,ch103st0},
 {14,ch103st1}
};

static const FyjStrokeChar ch103 = {70.9829f,2,ch103st};

/* char: 0x68 */

static const FyjStrokeVertex ch104st0[] =
{
 {9.6f,100.0f},
 {9.6f,0.0f}
};

static const FyjStrokeVertex ch104st1[] =
{
 {9.6f,47.619f},
 {23.8857f,61.9048f},
 {33.4095f,66.6667f},
 {47.6952f,66.6667f},
 {57.219f,61.9048f},
 {61.981f,47.619f},
 {61.981f,0.0f}
};

static const FyjStrokeStrip ch104st[] =
{
 {2,ch104st0},
 {7,ch104st1}
};

static const FyjStrokeChar ch104 = {71.021f,2,ch104st};

/* char: 0x69 */

static const FyjStrokeVertex ch105st0[] =
{
 {10.02f,100.0f},
 {14.7819f,95.2381f},
 {19.5438f,100.0f},
 {14.7819f,104.762f},
 {10.02f,100.0f}
};

static const FyjStrokeVertex ch105st1[] =
{
 {14.7819f,66.6667f},
 {14.7819f,0.0f}
};

static const FyjStrokeStrip ch105st[] =
{
 {5,ch105st0},
 {2,ch105st1}
};

static const FyjStrokeChar ch105 = {28.8638f,2,ch105st};

/* char: 0x6a */

static const FyjStrokeVertex ch106st0[] =
{
 {17.3876f,100.0f},
 {22.1495f,95.2381f},
 {26.9114f,100.0f},
 {22.1495f,104.762f},
 {17.3876f,100.0f}
};

static const FyjStrokeVertex ch106st1[] =
{
 {22.1495f,66.6667f},
 {22.1495f,-14.2857f},
 {17.3876f,-28.5714f},
 {7.8638f,-33.3333f},
 {-1.66f,-33.3333f}
};

static const FyjStrokeStrip ch106st[] =
{
 {5,ch106st0},
 {5,ch106st1}
};

static const FyjStrokeChar ch106 = {36.2314f,2,ch106st};

/* char: 0x6b */

static const FyjStrokeVertex ch107st0[] =
{
 {9.6f,100.0f},
 {9.6f,0.0f}
};

static const FyjStrokeVertex ch107st1[] =
{
 {57.219f,66.6667f},
 {9.6f,19.0476f}
};

static const FyjStrokeVertex ch107st2[] =
{
 {28.6476f,38.0952f},
 {61.981f,0.0f}
};

static const FyjStrokeStrip ch107st[] =
{
 {2,ch107st0},
 {2,ch107st1},
 {2,ch107st2}
};

static const FyjStrokeChar ch107 = {62.521f,3,ch107st};

/* char: 0x6c */

static const FyjStrokeVertex ch108st0[] =
{
 {10.02f,100.0f},
 {10.02f,0.0f}
};

static const FyjStrokeStrip ch108st[] =
{
 {2,ch108st0}
};

static const FyjStrokeChar ch108 = {19.34f,1,ch108st};

/* char: 0x6d */

static const FyjStrokeVertex ch109st0[] =
{
 {9.6f,66.6667f},
 {9.6f,0.0f}
};

static const FyjStrokeVertex ch109st1[] =
{
 {9.6f,47.619f},
 {23.8857f,61.9048f},
 {33.4095f,66.6667f},
 {47.6952f,66.6667f},
 {57.219f,61.9048f},
 {61.981f,47.619f},
 {61.981f,0.0f}
};

static const FyjStrokeVertex ch109st2[] =
{
 {61.981f,47.619f},
 {76.2667f,61.9048f},
 {85.7905f,66.6667f},
 {100.076f,66.6667f},
 {109.6f,61.9048f},
 {114.362f,47.619f},
 {114.362f,0.0f}
};

static const FyjStrokeStrip ch109st[] =
{
 {2,ch109st0},
 {7,ch109st1},
 {7,ch109st2}
};

static const FyjStrokeChar ch109 = {123.962f,3,ch109st};

/* char: 0x6e */

static const FyjStrokeVertex ch110st0[] =
{
 {9.18f,66.6667f},
 {9.18f,0.0f}
};

static const FyjStrokeVertex ch110st1[] =
{
 {9.18f,47.619f},
 {23.4657f,61.9048f},
 {32.9895f,66.6667f},
 {47.2752f,66.6667f},
 {56.799f,61.9048f},
 {61.561f,47.619f},
 {61.561f,0.0f}
};

static const FyjStrokeStrip ch110st[] =
{
 {2,ch110st0},
 {7,ch110st1}
};

static const FyjStrokeChar ch110 = {70.881f,2,ch110st};

/* char: 0x6f */

static const FyjStrokeVertex ch111st0[] =
{
 {28.7895f,66.6667f},
 {19.2657f,61.9048f},
 {9.7419f,52.381f},
 {4.98f,38.0952f},
 {4.98f,28.5714f},
 {9.7419f,14.2857f},
 {19.2657f,4.7619f},
 {28.7895f,0.0f},
 {43.0752f,0.0f},
 {52.599f,4.7619f},
 {62.1229f,14.2857f},
 {66.8848f,28.5714f},
 {66.8848f,38.0952f},
 {62.1229f,52.381f},
 {52.599f,61.9048f},
 {43.0752f,66.6667f},
 {28.7895f,66.6667f}
};

static const FyjStrokeStrip ch111st[] =
{
 {17,ch111st0}
};

static const FyjStrokeChar ch111 = {71.7448f,1,ch111st};

/* char: 0x70 */

static const FyjStrokeVertex ch112st0[] =
{
 {9.46f,66.6667f},
 {9.46f,-33.3333f}
};

static const FyjStrokeVertex ch112st1[] =
{
 {9.46f,52.381f},
 {18.9838f,61.9048f},
 {28.5076f,66.6667f},
 {42.7933f,66.6667f},
 {52.3171f,61.9048f},
 {61.841f,52.381f},
 {66.6029f,38.0952f},
 {66.6029f,28.5714f},
 {61.841f,14.2857f},
 {52.3171f,4.7619f},
 {42.7933f,0.0f},
 {28.5076f,0.0f},
 {18.9838f,4.7619f},
 {9.46f,14.2857f}
};

static const FyjStrokeStrip ch112st[] =
{
 {2,ch112st0},
 {14,ch112st1}
};

static const FyjStrokeChar ch112 = {70.8029f,2,ch112st};

/* char: 0x71 */

static const FyjStrokeVertex ch113st0[] =
{
 {61.9829f,66.6667f},
 {61.9829f,-33.3333f}
};

static const FyjStrokeVertex ch113st1[] =
{
 {61.9829f,52.381f},
 {52.459f,61.9048f},
 {42.9352f,66.6667f},
 {28.6495f,66.6667f},
 {19.1257f,61.9048f},
 {9.6019f,52.381f},
 {4.84f,38.0952f},
 {4.84f,28.5714f},
 {9.6019f,14.2857f},
 {19.1257f,4.7619f},
 {28.6495f,0.0f},
 {42.9352f,0.0f},
 {52.459f,4.7619f},
 {61.9829f,14.2857f}
};

static const FyjStrokeStrip ch113st[] =
{
 {2,ch113st0},
 {14,ch113st1}
};

static const FyjStrokeChar ch113 = {70.7429f,2,ch113st};

/* char: 0x72 */

static const FyjStrokeVertex ch114st0[] =
{
 {9.46f,66.6667f},
 {9.46f,0.0f}
};

static const FyjStrokeVertex ch114st1[] =
{
 {9.46f,38.0952f},
 {14.2219f,52.381f},
 {23.7457f,61.9048f},
 {33.2695f,66.6667f},
 {47.5552f,66.6667f}
};

static const FyjStrokeStrip ch114st[] =
{
 {2,ch114st0},
 {5,ch114st1}
};

static const FyjStrokeChar ch114 = {49.4952f,2,ch114st};

/* char: 0x73 */

static const FyjStrokeVertex ch115st0[] =
{
 {57.081f,52.381f},
 {52.319f,61.9048f},
 {38.0333f,66.6667f},
 {23.7476f,66.6667f},
 {9.4619f,61.9048f},
 {4.7f,52.381f},
 {9.4619f,42.8571f},
 {18.9857f,38.0952f},
 {42.7952f,33.3333f},
 {52.319f,28.5714f},
 {57.081f,19.0476f},
 {57.081f,14.2857f},
 {52.319f,4.7619f},
 {38.0333f,0.0f},
 {23.7476f,0.0f},
 {9.4619f,4.7619f},
 {4.7f,14.2857f}
};

static const FyjStrokeStrip ch115st[] =
{
 {17,ch115st0}
};

static const FyjStrokeChar ch115 = {62.321f,1,ch115st};

/* char: 0x74 */

static const FyjStrokeVertex ch116st0[] =
{
 {14.8257f,100.0f},
 {14.8257f,19.0476f},
 {19.5876f,4.7619f},
 {29.1114f,0.0f},
 {38.6352f,0.0f}
};

static const FyjStrokeVertex ch116st1[] =
{
 {0.54f,66.6667f},
 {33.8733f,66.6667f}
};

static const FyjStrokeStrip ch116st[] =
{
 {5,ch116st0},
 {2,ch116st1}
};

static const FyjStrokeChar ch116 = {39.3152f,2,ch116st};

/* char: 0x75 */

static const FyjStrokeVertex ch117st0[] =
{
 {9.46f,66.6667f},
 {9.46f,19.0476f},
 {14.2219f,4.7619f},
 {23.7457f,0.0f},
 {38.0314f,0.0f},
 {47.5552f,4.7619f},
 {61.841f,19.0476f}
};

static const FyjStrokeVertex ch117st1[] =
{
 {61.841f,66.6667f},
 {61.841f,0.0f}
};

static const FyjStrokeStrip ch117st[] =
{
 {7,ch117st0},
 {2,ch117st1}
};

static const FyjStrokeChar ch117 = {71.161f,2,ch117st};

/* char: 0x76 */

static const FyjStrokeVertex ch118st0[] =
{
 {1.8f,66.6667f},
 {30.3714f,0.0f}
};

static const FyjStrokeVertex ch118st1[] =
{
 {58.9429f,66.6667f},
 {30.3714f,0.0f}
};

static const FyjStrokeStrip ch118st[] =
{
 {2,ch118st0},
 {2,ch118st1}
};

static const FyjStrokeChar ch118 = {60.6029f,2,ch118st};

/* char: 0x77 */

static const FyjStrokeVertex ch119st0[] =
{
 {2.5f,66.6667f},
 {21.5476f,0.0f}
};

static const FyjStrokeVertex ch119st1[] =
{
 {40.5952f,66.6667f},
 {21.5476f,0.0f}
};

static const FyjStrokeVertex ch119st2[] =
{
 {40.5952f,66.6667f},
 {59.6429f,0.0f}
};

static const FyjStrokeVertex ch119st3[] =
{
 {78.6905f,66.6667f},
 {59.6429f,0.0f}
};

static const FyjStrokeStrip ch119st[] =
{
 {2,ch119st0},
 {2,ch119st1},
 {2,ch119st2},
 {2,ch119st3}
};

static const FyjStrokeChar ch119 = {80.4905f,4,ch119st};

/* char: 0x78 */

static const FyjStrokeVertex ch120st0[] =
{
 {1.66f,66.6667f},
 {54.041f,0.0f}
};

static const FyjStrokeVertex ch120st1[] =
{
 {54.041f,66.6667f},
 {1.66f,0.0f}
};

static const FyjStrokeStrip ch120st[] =
{
 {2,ch120st0},
 {2,ch120st1}
};

static const FyjStrokeChar ch120 = {56.401f,2,ch120st};

/* char: 0x79 */

static const FyjStrokeVertex ch121st0[] =
{
 {6.5619f,66.6667f},
 {35.1333f,0.0f}
};

static const FyjStrokeVertex ch121st1[] =
{
 {63.7048f,66.6667f},
 {35.1333f,0.0f},
 {25.6095f,-19.0476f},
 {16.0857f,-28.5714f},
 {6.5619f,-33.3333f},
 {1.8f,-33.3333f}
};

static const FyjStrokeStrip ch121st[] =
{
 {2,ch121st0},
 {6,ch121st1}
};

static const FyjStrokeChar ch121 = {66.0648f,2,ch121st};

/* char: 0x7a */

static const FyjStrokeVertex ch122st0[] =
{
 {56.821f,66.6667f},
 {4.44f,0.0f}
};

static const FyjStrokeVertex ch122st1[] =
{
 {4.44f,66.6667f},
 {56.821f,66.6667f}
};

static const FyjStrokeVertex ch122st2[] =
{
 {4.44f,0.0f},
 {56.821f,0.0f}
};

static const FyjStrokeStrip ch122st[] =
{
 {2,ch122st0},
 {2,ch122st1},
 {2,ch122st2}
};

static const FyjStrokeChar ch122 = {61.821f,3,ch122st};

/* char: 0x7b */

static const FyjStrokeVertex ch123st0[] =
{
 {31.1895f,119.048f},
 {21.6657f,114.286f},
 {16.9038f,109.524f},
 {12.1419f,100.0f},
 {12.1419f,90.4762f},
 {16.9038f,80.9524f},
 {21.6657f,76.1905f},
 {26.4276f,66.6667f},
 {26.4276f,57.1429f},
 {16.9038f,47.619f}
};

static const FyjStrokeVertex ch123st1[] =
{
 {21.6657f,114.286f},
 {16.9038f,104.762f},
 {16.9038f,95.2381f},
 {21.6657f,85.7143f},
 {26.4276f,80.9524f},
 {31.1895f,71.4286f},
 {31.1895f,61.9048f},
 {26.4276f,52.381f},
 {7.38f,42.8571f},
 {26.4276f,33.3333f},
 {31.1895f,23.8095f},
 {31.1895f,14.2857f},
 {26.4276f,4.7619f},
 {21.6657f,0.0f},
 {16.9038f,-9.5238f},
 {16.9038f,-19.0476f},
 {21.6657f,-28.5714f}
};

static const FyjStrokeVertex ch123st2[] =
{
 {16.9038f,38.0952f},
 {26.4276f,28.5714f},
 {26.4276f,19.0476f},
 {21.6657f,9.5238f},
 {16.9038f,4.7619f},
 {12.1419f,-4.7619f},
 {12.1419f,-14.2857f},
 {16.9038f,-23.8095f},
 {21.6657f,-28.5714f},
 {31.1895f,-33.3333f}
};

static const FyjStrokeStrip ch123st[] =
{
 {10,ch123st0},
 {17,ch123st1},
 {10,ch123st2}
};

static const FyjStrokeChar ch123 = {41.6295f,3,ch123st};

/* char: 0x7c */

static const FyjStrokeVertex ch124st0[] =
{
 {11.54f,119.048f},
 {11.54f,-33.3333f}
};

static const FyjStrokeStrip ch124st[] =
{
 {2,ch124st0}
};

static const FyjStrokeChar ch124 = {23.78f,1,ch124st};

/* char: 0x7d */

static const FyjStrokeVertex ch125st0[] =
{
 {9.18f,119.048f},
 {18.7038f,114.286f},
 {23.4657f,109.524f},
 {28.2276f,100.0f},
 {28.2276f,90.4762f},
 {23.4657f,80.9524f},
 {18.7038f,76.1905f},
 {13.9419f,66.6667f},
 {13.9419f,57.1429f},
 {23.4657f,47.619f}
};

static const FyjStrokeVertex ch125st1[] =
{
 {18.7038f,114.286f},
 {23.4657f,104.762f},
 {23.4657f,95.2381f},
 {18.7038f,85.7143f},
 {13.9419f,80.9524f},
 {9.18f,71.4286f},
 {9.18f,61.9048f},
 {13.9419f,52.381f},
 {32.9895f,42.8571f},
 {13.9419f,33.3333f},
 {9.18f,23.8095f},
 {9.18f,14.2857f},
 {13.9419f,4.7619f},
 {18.7038f,0.0f},
 {23.4657f,-9.5238f},
 {23.4657f,-19.0476f},
 {18.7038f,-28.5714f}
};

static const FyjStrokeVertex ch125st2[] =
{
 {23.4657f,38.0952f},
 {13.9419f,28.5714f},
 {13.9419f,19.0476f},
 {18.7038f,9.5238f},
 {23.4657f,4.7619f},
 {28.2276f,-4.7619f},
 {28.2276f,-14.2857f},
 {23.4657f,-23.8095f},
 {18.7038f,-28.5714f},
 {9.18f,-33.3333f}
};

static const FyjStrokeStrip ch125st[] =
{
 {10,ch125st0},
 {17,ch125st1},
 {10,ch125st2}
};

static const FyjStrokeChar ch125 = {41.4695f,3,ch125st};

/* char: 0x7e */

static const FyjStrokeVertex ch126st0[] =
{
 {2.92f,28.5714f},
 {2.92f,38.0952f},
 {7.6819f,52.381f},
 {17.2057f,57.1429f},
 {26.7295f,57.1429f},
 {36.2533f,52.381f},
 {55.301f,38.0952f},
 {64.8248f,33.3333f},
 {74.3486f,33.3333f},
 {83.8724f,38.0952f},
 {88.6343f,47.619f}
};

static const FyjStrokeVertex ch126st1[] =
{
 {2.92f,38.0952f},
 {7.6819f,47.619f},
 {17.2057f,52.381f},
 {26.7295f,52.381f},
 {36.2533f,47.619f},
 {55.301f,33.3333f},
 {64.8248f,28.5714f},
 {74.3486f,28.5714f},
 {83.8724f,33.3333f},
 {88.6343f,47.619f},
 {88.6343f,57.1429f}
};

static const FyjStrokeStrip ch126st[] =
{
 {11,ch126st0},
 {11,ch126st1}
};

static const FyjStrokeChar ch126 = {91.2743f,2,ch126st};

/* char: 0x7f */

static const FyjStrokeVertex ch127st0[] =
{
 {52.381f,100.0f},
 {14.2857f,-33.3333f}
};

static const FyjStrokeVertex ch127st1[] =
{
 {28.5714f,66.6667f},
 {14.2857f,61.9048f},
 {4.7619f,52.381f},
 {0.0f,38.0952f},
 {0.0f,23.8095f},
 {4.7619f,14.2857f},
 {14.2857f,4.7619f},
 {28.5714f,0.0f},
 {38.0952f,0.0f},
 {52.381f,4.7619f},
 {61.9048f,14.2857f},
 {66.6667f,28.5714f},
 {66.6667f,42.8571f},
 {61.9048f,52.381f},
 {52.381f,61.9048f},
 {38.0952f,66.6667f},
 {28.5714f,66.6667f}
};

static const FyjStrokeStrip ch127st[] =
{
 {2,ch127st0},
 {17,ch127st1}
};

static const FyjStrokeChar ch127 = {66.6667f,2,ch127st};

static const FyjStrokeChar *characters[] =
{
 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0,
 &ch32, &ch33, &ch34, &ch35, &ch36, &ch37, &ch38, &ch39,
 &ch40, &ch41, &ch42, &ch43, &ch44, &ch45, &ch46, &ch47,
 &ch48, &ch49, &ch50, &ch51, &ch52, &ch53, &ch54, &ch55,
 &ch56, &ch57, &ch58, &ch59, &ch60, &ch61, &ch62, &ch63,
 &ch64, &ch65, &ch66, &ch67, &ch68, &ch69, &ch70, &ch71,
 &ch72, &ch73, &ch74, &ch75, &ch76, &ch77, &ch78, &ch79,
 &ch80, &ch81, &ch82, &ch83, &ch84, &ch85, &ch86, &ch87,
 &ch88, &ch89, &ch90, &ch91, &ch92, &ch93, &ch94, &ch95,
 &ch96, &ch97, &ch98, &ch99, &ch100, &ch101, &ch102, &ch103,
 &ch104, &ch105, &ch106, &ch107, &ch108, &ch109, &ch110, &ch111,
 &ch112, &ch113, &ch114, &ch115, &ch116, &ch117, &ch118, &ch119,
 &ch120, &ch121, &ch122, &ch123, &ch124, &ch125, &ch126, &ch127
};

const  FyjStrokeFont fyjStrokeFont = { "-a-fyj-test-stroke-font",128,152.381f,characters };

 /**
  * @param character 0~127
  */
void renderStrokeCharacter(int character)
{
    Q_ASSERT_X(character >= 0 && character <= 127,
               "renderCharacter", "invalid parameter");

    const FyjStrokeChar *schar;
    const FyjStrokeStrip *strip;
    int i, j;
    const FyjStrokeFont* font = &fyjStrokeFont;
    schar = font->characters[character];
    strip = schar->strips;

    for( i = 0; i < schar->number; i++, strip++ )
    {
        glBegin( GL_LINE_STRIP );
        for( j = 0; j < strip->number; j++ )
            glVertex2f( strip->vertices[ j ].x, strip->vertices[ j ].y );
        glEnd( );
        glBegin( GL_POINTS );
        for( j = 0; j < strip->number; j++ )
            glVertex2f( strip->vertices[ j ].x, strip->vertices[ j ].y );
        glEnd( );
    }
    glTranslatef( schar->right, 0.0, 0.0 );
}

void renderString(const unsigned char *string)
{
    unsigned char c;
    int i, j;
    float length = 0.0;
    const FyjStrokeFont* font = &fyjStrokeFont;

    if ( !string || ! *string )
        return;

    while( ( c = *string++) )
        if( c < font->quality )
        {
            if( c == '\n' )
            {
                glTranslatef ( -length, -( float )( font->height ), 0.0 );
                length = 0.0;
            }
            else  /* Not an EOL, draw the bitmap character */
            {
                const FyjStrokeChar *schar = font->characters[ c ];
                if( schar )
                {
                    const FyjStrokeStrip *strip = schar->strips;

                    for( i = 0; i < schar->number; i++, strip++ )
                    {
                        glBegin( GL_LINE_STRIP );
                        for( j = 0; j < strip->number; j++ )
                            glVertex2f( strip->vertices[ j ].x,
                                        strip->vertices[ j ].y);

                        glEnd();
                    }

                    length += schar->right;
                    glTranslatef( schar->right, 0.0, 0.0 );
                }
            }
        }
}

#ifdef USE_DISPLAY_LIST
//利用显示列表来重新实现上述函数
GLuint fontOffset;
void makeRasterFyjStrokeFont(void)
{
    GLuint i, j;
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    fontOffset = glGenLists(128);
    for (i = 33; i < 127; i++,j++) {
        glNewList(fontOffset + i, GL_COMPILE);
        renderStrokeCharacter(i);
        glEndList();
    }
}

void printString(const unsigned char *s)
{
    glPushAttrib(GL_LIST_BIT);
    glListBase(fontOffset);
    glCallLists(strlen(reinterpret_cast<const char *>(s)), GL_UNSIGNED_BYTE, (GLubyte *)(s));
    glPopAttrib();
}
#endif

void glPrint(const char *fmt, ...)
{
    char   text[256];              // Holds Our String
    va_list     ap;                 // Pointer To List Of Arguments
    if (fmt == NULL)                    // If There's No Text
        return;                     // Do Nothing
    va_start(ap, fmt);                  // Parses The String For Variables
        vsprintf(text, fmt, ap);                // And Converts Symbols To Actual Numbers
    va_end(ap);                     // Results Are Stored In Text

#ifdef USE_DISPLAY_LIST
    printString(reinterpret_cast<unsigned char *>(text));
#else
    renderString(reinterpret_cast<unsigned char *>(text));
#endif
}

GLfloat rot;                            // Used To Rotate The Text      ( ADD )

}


MyGLWidget::MyGLWidget(QWidget *parent) :
    QGLWidget(parent), fullscreen(false)
{
    setWindowTitle(tr("nehe----lesson14"));
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateGL()));
    timer->start(10);
}

void MyGLWidget::initializeGL()
{
    glShadeModel(GL_SMOOTH);   // Enables Smooth Shading
    glClearColor(0.0f, 0.0f, 0.0f, 0.5f);  // Black Background
    glClearDepth(1.0f);             // Depth Buffer Setup
    glEnable(GL_DEPTH_TEST);        // Enables Depth Testing
    glDepthFunc(GL_LEQUAL);        // The Type Of Depth Test To Do
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // Really Nice Perspective Calculations

#ifdef USE_DISPLAY_LIST
    makeRasterFyjStrokeFont();
#endif
}

void MyGLWidget::resizeGL(int width, int height)
{
    if (height==0) {    // Prevent A Divide By Zero By
        height=1;    // Making Height Equal One
    }
    glViewport(0, 0, width, height);    // Reset The Current Viewport
    glMatrixMode(GL_PROJECTION);       // Select The Projection Matrix
    glLoadIdentity();                  // Reset The Projection Matrix

    // Calculate The Aspect Ratio Of The Window
    gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,10000.0f);
    gluLookAt(0, 0, -9500, 0, 0, 0, 0, 1, 0);

    glMatrixMode(GL_MODELVIEW);      // Select The Modelview Matrix
    glLoadIdentity();                // Reset The Modelview Matrix
}

void MyGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // Clear The Screen And The Depth Buffer
    glLoadIdentity();       // Reset The Current Modelview Matrix

  //  glTranslatef(0, 0, -5.0f);
      glScalef(2.0f, 2.0f, 1);
    glRotatef(rot,1.0f,0.0f,0.0f);              // Rotate On The X Axis
    glRotatef(rot*1.5f,0.0f,1.0f,0.0f);         // Rotate On The Y Axis
    glRotatef(rot*1.4f,0.0f,0.0f,1.0f);         // Rotate On The Z Axis

    // Pulsing Colors Based On The Rotation
    glColor3f(1.0f*float(cos(rot/20.0f)),1.0f*float(sin(rot/25.0f)),1.0f-0.5f*float(cos(rot/17.0f)));


  //    renderStrokeCharacter(126);

      glPrint("Active OpenGL Text With NeHe - %3.2f", rot/50);

      rot += 0.5f;
}

void MyGLWidget::keyPressEvent(QKeyEvent *e)
{
    switch (e->key()) {
    case Qt::Key_F:
        fullscreen = !fullscreen;
        if (fullscreen) {
            showFullScreen();
        } else {
            resize(640, 480);
            showNormal();
        }
        break;
    case Qt::Key_Escape:
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(NULL, "NeHe",
                           "Do you want to exit?",
                           QMessageBox::Yes | QMessageBox::No,
                           QMessageBox::Yes);
        if (reply == QMessageBox::Yes) {
                qApp->quit();
        }
        break;
    default:
        QGLWidget::keyPressEvent(e);
        break;
    }
}

void MyGLWidget::closeEvent(QCloseEvent *e)
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "NeHe",
                       "Do you want to exit?",
                       QMessageBox::Yes | QMessageBox::No,
                       QMessageBox::No);
    if (reply == QMessageBox::Yes) {
            e->accept();
    } else {
        e->ignore();
    }
}
