/* 0.0.3 Version
   Code by Utopia, update by wyb
*/
#ifndef _LINE2D_H_
#define _LINE2D_H_

#include <eigen3/Eigen/Dense>
using namespace Eigen;

class Line2d;
class Segment2d;

class Line2d {
	double line_d;
	/* 使用(N * P - d)来判断点在直线前/后，本质上是判断直线上某一点到点P的向量与法线N的夹角 */
	Vector2d line_normal;

public:
	Line2d() : line_normal(0, 0), line_d(0) {}

	/* 获取相关信息 */
	double getd() const { return line_d; }
	Vector2d getnormal() const {return line_normal; }

	/* 已知两点确定直线 */
	Line2d(const Vector2d& p1, const Vector2d& p2) : line_normal((p2 - p1)(0), -(p2 - p1)(1)), line_d(p2.dot(line_normal)) {}

	/* 判断点是在直线的前还是后 */
	int checkPoint(const Vector2d& point);

	/* 判断线段与分割直线的关系，-1在直线后，1在直线前，0在直线上，2为非重合相交 */
	int checkSegment(const Segment2d& seg);

};

class Segment2d {
	Vector2d endPoints[2];
	
public:
	Segment2d() { endPoints[0] = endPoints[1] = Vector2d(0, 0); }
	Segment2d(const Vector2d& p1, const Vector2d& p2) { endPoints[0] = p1; endPoints[1] = p2; }
	
	/* 获取线段所在的直线 */
	Line2d getLine() const { return Line2d(endPoints[0], endPoints[1]); }

	/* 获取线段的某个端点*/
	Vector2d getVertex(int i) const { return endPoints[i]; }
};

#endif