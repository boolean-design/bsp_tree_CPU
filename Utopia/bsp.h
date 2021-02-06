/* 0.0.2 Version
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

struct bspNode2d {
	Line2d line; // 当前选择的分割直线
	vector<Segment2d> segs; // 当前节点的线段数组
	bspNode2d* front;
	bspNode2d* behind;

	bspNode2d() : front(nullptr), behind(nullptr) {}
	bspNode2d(Line2d l, bspNode2d* f, bspNode2d* b) : line(l), front(f), behind(b) {}
	bspNode2d(Line2d l, vector<Segment2d> s) : line(l), segs(s), front(nullptr), behind(nullptr) {}
};

class bspTree2d {
	bspNode2d* root;
	
public:
	bspTree2d() : root(nullptr) {}
	bspTree2d(bspNode2d* t) : root(t) {}
	~bspTree2d() { destroyBSPTree(root); }

	void destroyBSPTree(bspNode2d* root);

	/* 构建二维BSP树 */
	bspNode2d* buildBspTree2d(vector<Segment2d>& seg_v, int depth = 0);

	/* 判断某点是否在区域内 */
	bool checkPoint(Vector2d p, bspNode2d* node = nullptr);

	/* 选择一个较好的分割直线，目的是选择截断线段最少，且直线前后线段数较为均匀的直线 */
	Line2d pickSplittingLine(vector<Segment2d>& seg_v);
};

void bspTree2d::destroyBSPTree(bspNode2d* root) {
	if (root == nullptr) return;
	
	if (root->front) {
		destroyBSPTree(root->front);
	}
	if (root->behind) {
		destroyBSPTree(root->behind);
	}
	delete root;
	return;
}

bspNode2d* bspTree2d::buildBspTree2d(vector<Segment2d>& seg_v, int depth = 0) {
	/* 无边需要分割 */
	if (seg_v.empty()) return nullptr;
	
	size_t segsNum = seg_v.size();
	/* 最后一条边，直接构造叶结点 */
	if (segsNum == 1) return (new bspNode2d(seg_v[0].getLine(), seg_v));

	Line2d splitLine = pickSplittingLine(seg_v);
	/* 直线前，直线后，在直线上 */
	vector<Segment2d> frontList, backList, inList;

	/* 对于每条边 */
	for (int i = 0; i < segsNum; ++i) {
		Segment2d& seg = seg_v[i], frontPart, backPart;

		int lineSide = splitLine.checkSegment(seg);
		if (lineSide == 1) { // 在直线前
			frontList.push_back(seg);
			continue;
		} // 在直线上
		else if (lineSide == 0) {
			inList.push_back(seg);
			continue;
		} // 在直线后
		else if (lineSide == -1) {
			backList.push_back(seg);
			continue;
		} // 被直线分为两半（非重合相交）
		else {
			splitLineSegment(seg, splitLine, frontPart, backPart);
			frontList.push_back(frontPart);
			backList.push_back(backPart);
			continue;
		}
	}

	/* 构建当前BSP节点 */
	bspNode2d* curNode = new bspNode2d(splitLine, inList);

	curNode->front = buildBspTree2d(frontList, depth + 1);
	curNode->behind = buildBspTree2d(backList, depth + 1);

	/* 当前若为根结点，则为根结点单独赋值 */
	if (depth == 0 && root == nullptr) {
		root = curNode;
	}

	return curNode;
}

bool bspTree2d::checkPoint(Vector2d p, bspNode2d* node = nullptr) {
	/* 空指针表示刚调用此函数，从树根开始划分 */
	if (node == nullptr) {
		node = root;
	}
	
	int lineSide = node->line.checkPoint(p);
	if (lineSide > 0) {
		if (node->front) {
			/* 在直线前，调用前子树判断 */
			return checkPoint(p, node->front);
		}
		/* 无前子树，说明包含这个点 */
		return true;
	}
	else if (lineSide == 0) {
		/* 在直线上，想做什么自定义 */
		return true;
	}
	else {
		if (node->behind) {
			return checkPoint(p, node->behind);
		}
		/* 无后子树，说明不包含这个点 */
		return false;
	}

	/* 不知道出了什么bug，那就当这个点不在内部就好了 */
	return false;
}

Line2d bspTree2d::pickSplittingLine(vector<Segment2d>& seg_v) {
	/* 有一说一，这个不好写，现在占个位而已 */
	int segSize = seg_v.size();
	/* [0, segSize)随机取一个数，选取这条直线 */
	int i = rand() % segSize;
	return seg_v[i].getLine();
}
