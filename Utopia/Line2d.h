/* 0.0.1 Version
   Code by Utopia 
*/

#pragma once

class Line2d {
	double line_d;
	/* ʹ��(N * P - d)���жϵ���ֱ��ǰ/�󣬱��������ж�ֱ����ĳһ�㵽��P�������뷨��N�ļн� */
	Vector2d line_normal;

public:
	Line2d() : line_normal(0, 0), line_d(0) {}

	/* ��֪����ȷ��ֱ�� */
	Line2d(const Vector2d& p1, const Vector2d& p2) : line_normal((p2 - p1)(0), -(p2 - p1)(1)), line_d(p2.dot(line_normal)) {}

	/* �жϵ�����ֱ�ߵ�ǰ���Ǻ� */
	int checkPoint(const Vector2d& point);
};

int Line2d::checkPoint(const Vector2d& point) {
	int res = (*this).line_normal.dot(point) - (*this).line_d;
	/* res < 0��ֱ�ߺ�res > 0��ֱ��ǰ��������ֱ���� */
	return res;
}