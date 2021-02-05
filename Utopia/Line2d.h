/* 0.0.1 Version
   Code by Utopia 
*/

#pragma once

class Line2d {
	double line_d;
	/* 使用(N * P - d)来判断点在直线前/后，本质上是判断直线上某一点到点P的向量与法线N的夹角 */
	Vector2d line_normal;

public:
	Line2d() : line_normal(0, 0), line_d(0) {}

	/* 已知两点确定直线 */
	Line2d(const Vector2d& p1, const Vector2d& p2) : line_normal((p2 - p1)(0), -(p2 - p1)(1)), line_d(p2.dot(line_normal)) {}

	/* 判断点是在直线的前还是后 */
	int checkPoint(const Vector2d& point);
};

int Line2d::checkPoint(const Vector2d& point) {
	int res = (*this).line_normal.dot(point) - (*this).line_d;
	/* res < 0在直线后；res > 0在直线前；否则在直线上 */
	return res;
}