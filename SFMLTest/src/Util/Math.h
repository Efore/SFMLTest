#pragma once
#include <SFML/System/Vector2.hpp>
#include <cmath>

namespace Util
{
	class Math
	{
		public:			
			static sf::Vector2f Normalize(const sf::Vector2f& vector)
			{
				sf::Vector2f normalized = vector / Magnitude(vector);
				return normalized;
			}

			static float Magnitude(const sf::Vector2f& vector)
			{
				return std::sqrtf(vector.x * vector.x + vector.y * vector.y);
			}

			static float SqrMagnitude(const sf::Vector2f& vector)
			{
				return (vector.x * vector.x + vector.y * vector.y);
			}

	};
}
