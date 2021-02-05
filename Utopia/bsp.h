/* 0.0.1 Version
   Code by Utopia
*/

#pragma once
#include <iostream>
#include <Eigen\Dense>
#include <vector>
#include "Line2d.h"
#include "Segment2d.h"
using namespace Eigen;
using namespace std;

class bspNode2d {
	Line2d line; // 当前选择的分割直线
	vector<Segment2d> segs; // 当前节点的线段数组
	bspNode2d* front;
	bspNode2d* behind;

public:
	bspNode2d() : front(nullptr), behind(nullptr) {}
	bspNode2d(Line2d l, bspNode2d* f, bspNode2d* b) : line(l), front(f), behind(b) {}
};

class bspTree2d {
	bspNode2d* root;
	
public:
	bspTree2d() : root(nullptr) {}
	bspTree2d(bspNode2d* t) : root(t) {}
	~bspTree2d();

	/* 构建二维BSP树 */
	bspTree2d* buildBspTree2d(vector<Segment2d>& seg_v, int depth = 0);

	/* 判断某点是否在区域内 */
	bool checkPoint(Vector2d p, bspNode2d* Node = nullptr);

	/* 选择一个较好的分割直线 */
	Line2d pickSplittingLine(vector<Segment2d>& seg_v) { /* TODO */ }
};

bspTree2d::~bspTree2d() {
	/* TODO, just a recursion */
}

bspTree2d* bspTree2d::buildBspTree2d(vector<Segment2d>& seg_v, int depth = 0) {
	/* TODO */
}

bool bspTree2d::checkPoint(Vector2d p, bspNode2d* Node = nullptr) {
	/* TODO */
}