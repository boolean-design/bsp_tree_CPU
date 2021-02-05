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
	Line2d line; // ��ǰѡ��ķָ�ֱ��
	vector<Segment2d> segs; // ��ǰ�ڵ���߶�����
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

	/* ������άBSP�� */
	bspTree2d* buildBspTree2d(vector<Segment2d>& seg_v, int depth = 0);

	/* �ж�ĳ���Ƿ��������� */
	bool checkPoint(Vector2d p, bspNode2d* Node = nullptr);

	/* ѡ��һ���Ϻõķָ�ֱ�� */
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