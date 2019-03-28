#include "InterpolationHelper.h"

sf::Vector2f InterpolationHelper::Linear(float p_Progress, sf::Vector2f p_Prev, sf::Vector2f p_Next)
{
	sf::Vector2f l_TweenPos;
	l_TweenPos.x = p_Prev.x + p_Progress * (p_Next.x - p_Prev.x);
	l_TweenPos.y = p_Prev.y + p_Progress * (p_Next.y - p_Prev.y);
	return l_TweenPos;
}
