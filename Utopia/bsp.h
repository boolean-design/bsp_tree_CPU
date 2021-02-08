/* 0.0.4 Version
   code by Utopia, update by wyb
*/

#ifndef _BSP_H_
#define _BSP_H_

#include <eigen3/Eigen/Dense>
#include <vector>
#include "Line2d.h"
#include "Segment2d.h"
using namespace Eigen;
using std::vector;

void splitLineSegment(const Segment2d& seg, Line2d line, Segment2d& frontSeg, Segment2d& backSeg);

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
	bspNode2d* buildBspTree2d(vector<Segment2d>& seg_v, int depth);

	/* 判断某点是否在区域内 */
	bool checkPoint(Vector2d p, bspNode2d* node);

	/* 选择一个较好的分割直线，目的是选择截断线段最少，且直线前后线段数较为均匀的直线 */
	Line2d pickSplittingLine(vector<Segment2d>& seg_v);
};

#endif