/* 0.0.2 Version
   Code by Utopia
*/

#pragma once

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

/* 用一条直线把一个线段分成两段分别放入前侧和后侧两个子结点线段集合中 */
void splitLineSegment(const Segment2d& seg, Line2d line, Segment2d& frontSeg, Segment2d& backSeg) {
	/* 我似乎暂时不会写这个。是要取交点一通操作？ */
}
