#ifndef HEADER_H
#define HEADER_H

#include <QWidget>
#include <QDialog>
#include <QPalette>
#include <QBitmap>
#include <QPoint>
#include <QMouseEvent>
#include <QPainter>
#include <QContextMenuEvent>
#include <QMenu>
#include <QAction>
#include <QIcon>
#include <Qt>
#include <QMessageBox>
#include <QMessageBox>
#include <QCloseEvent>
#include <QTimer>
#include <QApplication>
#include <QDesktopWidget>
#include <QTime>
#include <QMatrix>
#include <QKeyEvent>
#include <QRect>
#include <QPen>
#include <QSound>
#include <QDebug>
#include <QFont>
#include <QMenu>
#include <QMainWindow>
#include <QMenuBar>

#include <iostream>
#include <ctime>
#include <sstream>
#include <string>
#include <istream>
#include <ostream>
#include <sstream>
#include <list>

// 关卡数量
const int CHAPTER_NUM = 3;
// 关卡时间
const int CHAPTER_TIME = 30000;

// 窗口默认大小
const int GAME_WINDOW_WIDTH = 800;
const int GAME_WINDOW_HEIGHT = 800;

// 窗口更新时间间隔（ms）
const int WINDOW_UPDATE_INTERVAL = 40;

// 飞机大小
const int PLANE_WIDTH = 50;
const int PLAYER_PLANE_WIDTH = 80;

// 飞机速度
const int PLANE_SPEED = 5;
const int PLAYER_PLANE_SPEED = 8;
const int BOSS_PLANE_SPEED = 7;

// 子弹速度
const int BULLET_SPEED = PLANE_SPEED * 2;

// 子弹大小
const int BULLET_WIDTH = 8;
const int PLAYER_BULLET_WIDTH = 15;

// 血量
const int PLANE_BLOOD = 1;
const int PLAYER_BLOOD = 100;
const int BOSS_PLANE_BLOOD = 500;
const int PASSENGER_PLANE_BLOOD = 10;
const int BOSS_BLOOD = 5 * PLAYER_BLOOD;

// 攻击力
const int PLANE_ATTACK = 1;
const int PLAYER_ATTACK = 3;
const int BOSS_PLANE_ATTACK = 3;

// 飞机方向
const int PLANE_DIR_UP = -1;
const int PLANE_DIR_DOWN = 1;

// 补寄类型
const int ATTACK_SUPPLY_TYPE = 100;
const int BLOOD_SUPPLY_TYPE = 101;

// 补寄量
const int BLOOD_SUPPLY = 10;

// 结束窗口参数
const int GAMEOVER = 102;
const int YOUAREWIN = 103;


QString IntToQString(int x);
QString DoubleToQString(double x);
int getRandom(int L, int R);
bool RectangleIntersection(QRect a, QRect b);

// 几何函数

double VectorDot(QPoint a, QPoint b);
double VectorLength(QPoint a);
double VectorAngle(QPoint a, QPoint b);
QPoint VectorRotate(QPoint a, double rad);
double VectorCross(QPoint a, QPoint b);

#endif // HEADER_H