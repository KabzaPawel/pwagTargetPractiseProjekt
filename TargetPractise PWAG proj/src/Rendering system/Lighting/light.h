#pragma once

namespace Light
{
	class Light
	{
	public:
		Light(const glm::vec3& color);

#pragma region Inline functions
		const glm::vec3& getColor() const
		{
			return _color;
		}

		const glm::vec3& getAmbient() const
		{
			return _ambient;
		}

		const glm::vec3& getSpecular() const
		{
			return _specular;
		}

		const glm::vec3& getDiffuse() const
		{
			return _diffuse;
		}

		void setColor(const glm::vec3& color)
		{
			_color = color;
			_ambient = color * 0.05f;
			_specular = color * 1.0f;
			_diffuse = color * 0.8f;
		}
#pragma endregion

	protected:
		glm::vec3 _color;
		glm::vec3 _ambient;
		glm::vec3 _diffuse;
		glm::vec3 _specular;
	};
}
