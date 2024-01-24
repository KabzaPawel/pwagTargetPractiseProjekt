#pragma once
#include "light.h"
#include "attenuation.h"
#include "../OpenGL Objects/fbo.h"

class MainLevel;

namespace Light
{
	class Point : public Light
	{
	public:
		Point(const glm::vec3& position, const glm::vec3& color);
		Point(const Point& light);

#pragma region Inline functions
#pragma region Getters
		const glm::vec3& getPosition() const
		{
			return _position;
		}

		const Attenuation& getAttenuation() const
		{
			return _attenuation;
		}

		float getRange() const
		{
			return _range;
		}

		const glm::mat4& getLightSpaceMatrix() const
		{
			return _lightSpaceMatrix[0];
		}
#pragma endregion

#pragma region Setters
		void setPosition(const glm::vec3& position)
		{
			_position = position;
		}

		void setAttenuation(const Attenuation& attenuation)
		{
			_attenuation = attenuation;
		}

		void setRange(float range)
		{
			_range = range;
		}

		void setAttenuationByRange(float range)
		{
			_range = range;
			_attenuation.setAttenuationByRange(_range);
		}

		void setColor(const glm::vec3& color)
		{
			_color = color;
			_ambient = color * 0.05f;
			_specular = color * 1.0f;
			_diffuse = color * 0.8f;
		}

		void setColorLevelight(const glm::vec3& color)
		{
			_color = color * 100.0f;
			_ambient = _color * 0.05f;
			_specular = _color * 1.0f;
			_diffuse = _color * 0.8f;
		}
#pragma endregion
#pragma endregion

	private:
		FBO _fbo;
		Texture _depthMap;
		Attenuation _attenuation;

		glm::vec3 _position;
		float _range = 15;
		std::array<glm::mat4, 6> _lightSpaceMatrix;
	};
}
