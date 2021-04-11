#pragma once
#include<vector>
#include<opencv2/opencv.hpp>
#include<cmath>

using namespace std;
using namespace cv;

struct Note {
    int32_t x, y;
    int32_t f{0};
    int32_t g{0};
    int32_t h{0};

    Note *parent{nullptr};
    Note(int32_t x, int32_t y) :x(x), y(y) {}
};

class Astar
{
public:
    Mat img,resize_img;
    void InitAstar(vector<vector<int>> &_map)
    {
        map = _map;
        writer.open("Astar.avi", -1, 10, Size(675, 675), true);
        img.create(map.size(), map[0].size(), CV_8UC3);
        for (int i = 0; i < img.rows; i++)
            for (int j = 0; j < img.cols; j++)
            {
                if(map[i][j]==0)
                    img.at<Vec3b>(i, j) = Vec3b(255,255,255);
                else
                    img.at<Vec3b>(i, j) = Vec3b(0,0,0);
            }
    }
    vector<Note *> GetPath(Note &starNote, Note &endNote) //获得最短的路径
    {
        Note *result = findPath(starNote, endNote);
        vector<Note *> path;
        //返回路径，如果没找到路径，返回空
        while (result)
        {
            img.at<Vec3b>(result->x, result->y) = Vec3b(255, 0, 0);
            resize(img, resize_img, Size(675, 675), 0, 0, 3);
            writer << resize_img;
            imshow("find path", resize_img);
            waitKey(30);
            path.insert(path.begin(), result);
            result = result->parent;
        }
        writer.release();
        return path;
    }

private:
    vector<vector<int>> map;     //存放地图
    VideoWriter writer;
    vector<Note *> openList;     //开集
    vector<Note *> closeList;    //闭集

    Note *findPath(Note &startNote, Note &endNote) //找最短的路径
    {
        img.at<Vec3b>(startNote.x, startNote.y) = Vec3b(0, 0, 255);
        img.at<Vec3b>(endNote.x, endNote.y) = Vec3b(0, 0, 255);
        openList.push_back(new Note(startNote.x, startNote.y)); //起点放入开集
        while (!openList.empty())
        {
            auto currentNote = getLeastFNote(); //找到F值最小的点
            deleteNote(openList, currentNote);   //从开集中删除
            closeList.push_back(currentNote);   //放到关闭集
            img.at<Vec3b>(currentNote->x, currentNote->y) = Vec3b(0, 0, 255);
            resize(img, resize_img, Size(675, 675), 0, 0, 3);
            writer << resize_img;
            imshow("find path", resize_img);
            waitKey(120);
            auto surroundPoints = getSurroundNotes(currentNote);//寻找周围点
            for (auto &target : surroundPoints)
            {
                //对某一个格子，如果它不在开启列表中，加入到开启列表，设置当前格为其父节点，计算FGH
                if (!isInList(openList, target))
                {
                    target->parent = currentNote;
                    target->G = calcG(target);
                    target->H = calcH(target, &endNote);
                    target->F = calcF(target);
                    openList.push_back(target);
                    img.at<Vec3b>(target->x,target->y) = Vec3b(0, 255, 255);
                }
                    //对某一个格子，它在开启列表中，计算G值, 如果比原来的大, 就什么都不做, 否则设置它的父节点为当前点,并更新G和F
                else
                {
                    int tempG = calcG(target);
                    if (tempG < target->G)
                    {
                        target->parent = currentNote;
                        target->G = tempG;
                        target->F = calcF(target);
                    }
                }
                //如果终点出现在开集中，表明找到了路径，并返回。
                if (isInList(openList, &endNote))
                    return target; //返回列表里的节点指针
            }
            img.at<Vec3b>(currentNote->x, currentNote->y) = Vec3b(0,255, 0);
            resize(img, resize_img, Size(675, 675), 0, 0, 3);
            writer << resize_img;
            imshow("find path", resize_img);
            waitKey(20);
        }
        return NULL;
    }

    vector<Note *> getSurroundNotes(const Note *currentNote) const //遍历当前点的周围点
    {
        vector<Note *> surroundNotes;
        for (int x = currentNote->x - 1; x <= currentNote->x + 1; ++x)
            for (int y = currentNote->y - 1; y <= currentNote->y + 1; ++y)
                if (isReachable(currentNote, new Note(x, y)))
                    surroundNotes.push_back(new Note(x, y));
        return surroundNotes;
    }

    bool isReachable(const Note *currentNote, const Note *targetNote) const //判断某点是否可以用于下一步判断
    {
        //如果点超出地图、不是上下左右、是障碍物、或者在闭列表中，返回false。反之。
        if (targetNote->x < 0 || targetNote->x > (int)(map.size() - 1)
            || targetNote->y < 0 || targetNote->y > (int)(map[0].size() - 1)
            || (abs(currentNote->x - targetNote->x) + abs(currentNote->y - targetNote->y))!= 1
            || map[targetNote->x][targetNote->y] == 1
            || isInList(closeList, targetNote))
            return false;
        else
            return true;
    }
    bool isInList(const vector<Note *> &list, const Note *note) const //判断开/闭列表中是否包含某点
    {
        for (auto p : list)
            if (p->x == note->x && p->y == note->y)
                return true;
        return false;
    }
    void deleteNote(vector<Note *> &list,Note *note) //删除点
    {
        int pos=0;
        for (auto i = 0; i != list.size(); ++i)
        {
            if (list[i]->x == note->x && list[i]->y == note->y)
                break;
            ++pos;
        }
        list.erase(list.begin()+pos);
    }
    Note *getLeastFNote(); //从开列表中返回F值最小的节点
    {
        if (!openList.empty())
        {
            auto minFNote = openList.front();
            for (auto &note : openList)
                if (note->F < minFNote->F)
                    minFNote = note;
            return minFNote;
        }
        return NULL;
    }

    int calcG(Note *note)//计算FGH值
    {
        int parentG = note->parent == NULL ? 0 : note->parent->G; //如果是初始节点，则其父节点是空
        return ++parentG;
    }
    int calcH(Note *note, Note *end)
    {
        return abs(end->x - note->x)+ abs(end->y - note->y);
    }
    int calcF(Note *note)
    {
        return note->G + note->H;
    }
};

#if 0


#include <stdio.h>
#include <math.h>

#define MaxLength 100    //用于优先队列（Open表）的数组
#define Height     15    //地图高度
#define Width      20    //地图宽度

#define Reachable   0    //可以到达的结点
#define Bar         1    //障碍物
#define Pass        2    //需要走的步数
#define Source      3    //起点
#define Destination 4    //终点

#define Sequential  0    //顺序遍历
#define NoSolution  2    //无解决方案
#define Infinity    0xfffffff

#define East       (1 << 0)
#define South_East (1 << 1)
#define South      (1 << 2)
#define South_West (1 << 3)
#define West       (1 << 4)
#define North_West (1 << 5)
#define North      (1 << 6)
#define North_East (1 << 7)

typedef struct
{
    signed char x, y;
} Point;

const Point dir[8] = {
    {0, 1},   // East
    {1, 1},   // South_East
    {1, 0},   // South
    {1, -1},  // South_West
    {0, -1},  // West
    {-1, -1}, // North_West
    {-1, 0},  // North
    {-1, 1}   // North_East
};

unsigned char within(int x, int y)
{
    return (x >= 0 && y >= 0
            && x < Height && y < Width);
}

typedef struct
{
    int x, y;
    unsigned char reachable, sur, value;
} MapNode;

typedef struct Close
{
    MapNode *cur;
    char vis;
    struct Close *from;
    float F, G;
    int H;
} Close;

typedef struct //优先队列（Open表）
{
    int length;        //当前队列的长度
    Close* Array[MaxLength];    //评价结点的指针
} Open;

static MapNode graph[Height][Width];
static int srcX, srcY, dstX, dstY;    //起始点、终点
static Close close[Height][Width];

// 优先队列基本操作
void initOpen(Open *q)    //优先队列初始化
{
    q->length = 0;        // 队内元素数初始为0
}

void push(Open *q, Close cls[Height][Width], int x, int y, float g)
{    //向优先队列（Open表）中添加元素
    Close *t;
    int i, mintag;
    cls[x][y].G = g;    //所添加节点的坐标
    cls[x][y].F = cls[x][y].G + cls[x][y].H;
    q->Array[q->length++] = &(cls[x][y]);
    mintag = q->length - 1;
    for (i = 0; i < q->length - 1; i++)
    {
        if (q->Array[i]->F < q->Array[mintag]->F)
        {
            mintag = i;
        }
    }
    t = q->Array[q->length - 1];
    q->Array[q->length - 1] = q->Array[mintag];
    q->Array[mintag] = t;    //将评价函数值最小节点置于队头
}

Close* shift(Open *q)
{
    return q->Array[--q->length];
}

// 地图初始化操作
void initClose(Close cls[Height][Width], int sx, int sy, int dx, int dy)
{    // 地图Close表初始化配置
    int i, j;
    for (i = 0; i < Height; i++)
    {
        for (j = 0; j < Width; j++)
        {
            cls[i][j].cur = &graph[i][j];        // Close表所指节点
            cls[i][j].vis = !graph[i][j].reachable;        // 是否被访问
            cls[i][j].from = NULL;                // 所来节点
            cls[i][j].G = cls[i][j].F = 0;
            cls[i][j].H = abs(dx - i) + abs(dy - j);    // 评价函数值
        }
    }
    cls[sx][sy].F = cls[sx][sy].H;            //起始点评价初始值
    //    cls[sy][sy].G = 0;                        //移步花费代价值
    cls[dx][dy].G = Infinity;
}

void initGraph(const int map[Height][Width], int sx, int sy, int dx, int dy)
{    //地图发生变化时重新构造地
    int i, j;
    srcX = sx;    //起点X坐标
    srcY = sy;    //起点Y坐标
    dstX = dx;    //终点X坐标
    dstY = dy;    //终点Y坐标
    for (i = 0; i < Height; i++)
    {
        for (j = 0; j < Width; j++)
        {
            graph[i][j].x = i; //地图坐标X
            graph[i][j].y = j; //地图坐标Y
            graph[i][j].value = map[i][j];
            graph[i][j].reachable = (graph[i][j].value == Reachable);    // 节点可到达性
            graph[i][j].sur = 0; //邻接节点个数
            if (!graph[i][j].reachable)
            {
                continue;
            }
            if (j > 0)
            {
                if (graph[i][j - 1].reachable)    // left节点可以到达
                {
                    graph[i][j].sur |= West;
                    graph[i][j - 1].sur |= East;
                }
                if (i > 0)
                {
                    if (graph[i - 1][j - 1].reachable
                        && graph[i - 1][j].reachable
                        && graph[i][j - 1].reachable)    // up-left节点可以到达
                    {
                        graph[i][j].sur |= North_West;
                        graph[i - 1][j - 1].sur |= South_East;
                    }
                }
            }
            if (i > 0)
            {
                if (graph[i - 1][j].reachable)    // up节点可以到达
                {
                    graph[i][j].sur |= North;
                    graph[i - 1][j].sur |= South;
                }
                if (j < Width - 1)
                {
                    if (graph[i - 1][j + 1].reachable
                        && graph[i - 1][j].reachable
                        && map[i][j + 1] == Reachable) // up-right节点可以到达
                    {
                        graph[i][j].sur |= North_East;
                        graph[i - 1][j + 1].sur |= South_West;
                    }
                }
            }
        }
    }
}

int bfs()
{
    int times = 0;
    int i, curX, curY, surX, surY;
    unsigned char f = 0, r = 1;
    Close *p;
    Close* q[MaxLength] = { &close[srcX][srcY] };

    initClose(close, srcX, srcY, dstX, dstY);
    close[srcX][srcY].vis = 1;

    while (r != f)
    {
        p = q[f];
        f = (f + 1) % MaxLength;
        curX = p->cur->x;
        curY = p->cur->y;
        for (i = 0; i < 8; i++)
        {
            if (! (p->cur->sur & (1 << i)))
            {
                continue;
            }
            surX = curX + dir[i].x;
            surY = curY + dir[i].y;
            if (! close[surX][surY].vis)
            {
                close[surX][surY].from = p;
                close[surX][surY].vis = 1;
                close[surX][surY].G = p->G + 1;
                q[r] = &close[surX][surY];
                r = (r + 1) % MaxLength;
            }
        }
        times++;
    }
    return times;
}

int astar()
{    // A*算法遍历
    //int times = 0;
    int i, curX, curY, surX, surY;
    float surG;
    Open q; //Open表
    Close *p;

    initOpen(&q);
    initClose(close, srcX, srcY, dstX, dstY);
    close[srcX][srcY].vis = 1;
    push(&q, close, srcX, srcY, 0);

    while (q.length)
    {    //times++;
        p = shift(&q);
        curX = p->cur->x;
        curY = p->cur->y;
        if (!p->H)
        {
            return Sequential;
        }
        for (i = 0; i < 8; i++)
        {
            if (! (p->cur->sur & (1 << i)))
            {
                continue;
            }
            surX = curX + dir[i].x;
            surY = curY + dir[i].y;
            if (!close[surX][surY].vis)
            {
                close[surX][surY].vis = 1;
                close[surX][surY].from = p;
                surG = p->G + sqrt((curX - surX) * (curX - surX) + (curY - surY) * (curY - surY));
                push(&q, close, surX, surY, surG);
            }
        }
    }
    //printf("times: %d\n", times);
    return NoSolution; //无结果
}

const int map[Height][Width] = {
        {0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,1,1},
        {0,0,1,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1},
        {0,0,0,0,0,0,1,0,0,0,0,0,0,1,1,0,0,0,0,1},
        {0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,1},
        {0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,1,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,1,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0},
        {0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0},
        {0,1,0,0,0,0,1,0,0,0,0,0,0,1,0,1,0,0,0,1},
        {0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0}
};

const char Symbol[5][3] = { "□", "▓", "▽", "☆", "◎" };

void printMap()
{
    int i, j;
    for (i = 0; i < Height; i++)
    {
        for (j = 0; j < Width; j++)
        {
            printf("%s", Symbol[graph[i][j].value]);
        }
        puts("");
    }
    puts("");
}

Close* getShortest()
{    // 获取最短路径
    int result = astar();
    Close *p, *t, *q = NULL;
    switch(result)
    {
        case Sequential:    //顺序最近
            p = &(close[dstX][dstY]);
            while (p)    //转置路径
            {
                t = p->from;
                p->from = q;
                q = p;
                p = t;
            }
            close[srcX][srcY].from = q->from;
            return &(close[srcX][srcY]);
        case NoSolution:
            return NULL;
    }
    return NULL;
}

static Close *start;
static int shortestep;
int printShortest()
{
    Close *p;
    int step = 0;

    p = getShortest();
    start = p;
    if (!p)
    {
        return 0;
    }
    else
    {
        while (p->from)
        {
            graph[p->cur->x][p->cur->y].value = Pass;
            printf("（%d，%d）→\n", p->cur->x, p->cur->y);
            p = p->from;
            step++;
        }
        printf("（%d，%d）\n", p->cur->x, p->cur->y);
        graph[srcX][srcY].value = Source;
        graph[dstX][dstY].value = Destination;
        return step;
    }
}

void clearMap()
{    // Clear Map Marks of Steps
    Close *p = start;
    while (p)
    {
        graph[p->cur->x][p->cur->y].value = Reachable;
        p = p->from;
    }
    graph[srcX][srcY].value = map[srcX][srcY];
    graph[dstX][dstY].value = map[dstX][dstY];
}

void printDepth()
{
    int i, j;
    for (i = 0; i < Height; i++)
    {
        for (j = 0; j < Width; j++)
        {
            if (map[i][j])
            {
                printf("%s ", Symbol[graph[i][j].value]);
            }
            else
            {
                printf("%2.0lf ", close[i][j].G);
            }
        }
        puts("");
    }
    puts("");
}

void printSur()
{
    int i, j;
    for (i = 0; i < Height; i++)
    {
        for (j = 0; j < Width; j++)
        {
            printf("%02x ", graph[i][j].sur);
        }
        puts("");
    }
    puts("");
}

void printH()
{
    int i, j;
    for (i = 0; i < Height; i++)
    {
        for (j = 0; j < Width; j++)
        {
            printf("%02d ", close[i][j].H);
        }
        puts("");
    }
    puts("");
}

int main(int argc, const char **argv)
{
    initGraph(map, 0, 0, 0, 0);
    printMap();

    while (scanf("%d %d %d %d", &srcX, &srcY, &dstX, &dstY) != EOF)
    {
        if (within(srcX, srcY) && within(dstX, dstY))
        {
            if (shortestep = printShortest())
            {
                printf("从（%d，%d）到（%d，%d）的最短步数是: %d\n",
                       srcX, srcY, dstX, dstY, shortestep);
                printMap();
                clearMap();
                bfs();
                //printDepth();
                puts((shortestep == close[dstX][dstY].G) ? "正确" : "错误");
                clearMap();
            }
            else
            {
                printf("从（%d，%d）不可到达（%d，%d）\n",
                       srcX, srcY, dstX, dstY);
            }
        }
        else
        {
            puts("输入错误！");
        }
    }
    return (0);
}
#endif