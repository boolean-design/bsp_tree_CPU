/* 0.0.3 Version
   Code by Utopia, update by wyb
*/

#include <eigen3/Eigen/Dense>
#include <vector>
#include "Line2d.h"
#include "Segment2d.h"
#include "bsp.h"
using namespace Eigen;
using std::vector;

/* 用一条直线把一个线段分成两段分别放入前侧和后侧两个子结点线段集合中 */
void splitLineSegment(const Segment2d& seg, Line2d line, Segment2d& frontSeg, Segment2d& backSeg) {
	/* 我似乎暂时不会写这个。是要取交点一通操作？ */
	/* 因为后面调用该函数时进行了已经进行了相交检测, 故可直接求交点 */
	
	Line2d segLine=seg.getLine();
	Matrix2d n1, n2, d1;
	n1 <<	segLine.getnormal()(1),	line.getd(),
			line.getnormal()(1),	segLine.getd();
	n2 <<	segLine.getnormal()(0),	line.getd(),
			line.getnormal()(0),	segLine.getd();
	d1 <<	segLine.getnormal()(0),	segLine.getnormal()(1),
			line.getnormal()(0),	line.getnormal()(1);
	double x = n1.determinant() / d1.determinant(), y = - n2.determinant() / d1.determinant();
	Vector2d interPoint;
	interPoint << x, y;
	/* 以上为直线交点计算 */

	frontSeg = Segment2d(seg.getVertex(0), interPoint);
	backSeg = Segment2d(interPoint, seg.getVertex(1));
	return;
}

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

bool bspTree2d::checkPoint(Vector2d p, bspNode2d* node) {
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