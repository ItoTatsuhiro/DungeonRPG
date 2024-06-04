#include "Graphic.h"

#include "../../dxlib_ext/dxlib_ext.h"

ito::Graphic::Graphic(int hdl, float sizeMag, tnl::Vector3 pos)
	: hdl_(hdl), sizeMag_(sizeMag), ito::Transform(pos){


}


void ito::Graphic::draw(tnl::Vector3 basePos) {

	tnl::Vector3 drawPos = basePos + ito::Transform::pos_;

	DrawRotaGraph(drawPos.x, drawPos.y, sizeMag_, 0, hdl_, true);
	

}