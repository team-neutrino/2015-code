#include "DeadSpider.h"

DeadSpider::DeadSpider():
	whipUp(Constants::GetConstant("DeadSpiderUp")),
	whipDown(Constants::GetConstant("DeadSpiderDown"))
{

}

void DeadSpider::SpiderToggle(bool on)
{
	whipUp.Set(on);
	whipDown.Set(!on);
}
