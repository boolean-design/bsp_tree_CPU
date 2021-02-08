/* 0.0.4 Version
   code by Utopia, update by wyb
*/

#include "Line2d.h"
#include "bsp.h"
#include <eigen3/Eigen/Dense>
using namespace Eigen;

int Line2d::checkPoint(const Vector2d& point) {
	int res = (*this).line_normal.dot(point) - (*this).line_d;
	if (res > 0) res = 1;
	if (res < 0) res = -1;
	/* res = -1 在直线后；res = 1 在直线前；res = 0 在直线上 */
	return res;
}

int Line2d::checkSegment(const Segment2d& seg){
	Vector2d endPoint[2] = {seg.getVertex(0), seg.getVertex(1)};
	int endPoint_pos[2];
	endPoint_pos[0] = checkPoint(endPoint[0]);
	endPoint_pos[1] = checkPoint(endPoint[1]);
	if (endPoint_pos[0] == 0 && endPoint_pos[1] == 0) 
		return 0;	// 2个端点均位于直线上, 故线段位于直线上
	if (endPoint_pos[0] + endPoint_pos[1] == 0)
		return 2;	// 2个端点位于直线两侧, 故线段与直线非重合相交
	if (endPoint_pos[0] + endPoint_pos[1] < 0)
		return -1;
	else 
		return 1;
	/* 2个端点均位于直线某一侧, 返回对应情况 */
}

