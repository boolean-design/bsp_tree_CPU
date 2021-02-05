/* 0.0.1 Version
   Code by Utopia
*/

#pragma once

class Segment2d {
	Vector2d endPoints[2];
	
public:
	Segment2d() { endPoints[0] = endPoints[1] = Vector2d(0, 0); }
	Segment2d(const Vector2d& p1, const Vector2d& p2) { endPoints[0] = p1; endPoints[1] = p2; }
	
	/* ��ȡ�߶����ڵ�ֱ�� */
	Line2d getLine() const { return Line2d(endPoints[0], endPoints[1]); }

	/* ��ȡ�߶ε�ĳ���˵�*/
	Vector2d getVertex(int i) const { return endPoints[i]; }
};

/* ��һ��ֱ�߰�һ���߶ηֳ����ηֱ����ǰ��ͺ�������ӽ���߶μ����� */
void splitLineSegment(const Segment2d& seg, Line2d line, Segment2d& frontSeg, Segment2d& backSeg) {
	/* TODO; */
}
