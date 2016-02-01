#pragma once
#include <glm\vec4.hpp>
#include <array>

/*
 * Reference: https://docs.oracle.com/javase/7/docs/api/java/awt/Color.html
			  http://docs.unity3d.com/ScriptReference/Color.html
 * All colors are encoded as RGBA
*/

class Color
{
public:
	//TODO implement all these colors
	const static Color BLACK;
	const static Color BLUE;
	const static Color CYAN;
	const static Color DARK_GRAY;
	const static Color GRAY;
	const static Color GREEN;
	const static Color LIGHT_GRAY;
	const static Color MAGENTA;
	const static Color ORANGE;
	const static Color PINK;
	const static Color RED;
	const static Color WHITE;
	const static Color YELLOW;

	const static Color Darken(const Color color, float percent);
	const static Color Lighten(const Color color, float percent);

	const static Color HSV(float h, float s, float v, float a = 1.0);

	Color(float r = 0.0, float g = 0.0, float b = 0.0, float a = 1.0);
	Color(const Color& c);

	const float getRed() const;
	const float getGreen() const;
	const float getBlue() const;
	const float getAlpha() const;
	const std::array<float, 3> getHSV() const;

	const glm::vec4 toVec4() const;

	friend Color operator* (Color c1, Color c2);
	friend Color operator+ (Color c1, Color c2);
	friend bool operator== (Color c1, Color c2);

private:
	float r, g, b, a;
};