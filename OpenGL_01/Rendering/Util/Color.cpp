#include "Color.h"

/*
 * Static parameters
 */
const Color Color::RED		= Color(1.0, 0.0, 0.0, 1.0);
const Color Color::GREEN	= Color(0.0, 1.0, 0.0, 1.0);
const Color Color::BLUE		= Color(0.0, 0.0, 1.0, 1.0);

/*
 * Constructor
 */
Color::Color(float r, float g, float b, float a)
{
	//TODO throw exception if values out of range?? i.e, negative
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

Color::Color(const Color & c)
{
	this->r = c.r;
	this->g = c.g;
	this->b = c.b;
	this->a = c.a;
}

/*
 * Operator overloads
*/
Color operator*(const Color c1,const  Color c2)
{
	return Color(c1.r * c2.r,
		c1.g * c2.g,
		c1.b * c2.b,
		c1.a * c2.a);
}

Color operator+(const Color c1, const  Color c2)
{
	return Color(c1.r + c2.r,
		c1.g + c2.g,
		c1.b + c2.b,
		c1.a + c2.a);
}

bool operator==(const Color c1, const  Color c2)
{
	return c1.r == c2.r &&
		c1.g == c2.g &&
		c1.b == c2.b &&
		c1.a == c2.a;
}

/*
 * Getters
 */
const float Color::getRed() const
{
	return r;
}

const float Color::getGreen() const
{
	return g;
}

const float Color::getBlue() const
{
	return b;
}

const float Color::getAlpha() const
{
	return a;
}

const glm::vec4 Color::toVec4() const
{
	return glm::vec4(r, g, b, a);
}

/*
 * Static color creation methods
 */

const Color Color::Darken(const Color color, float percent)
{
	float n = 1 - percent;
	return color * Color(n, n, n, 1.0);
}

const Color Color::Lighten(const Color color, float percent)
{
	return color + Color(percent, percent, percent, 0.0);
}

const Color Color::HSV(int h, float s, float v, float a) {
	// hue is in range [0,360]
	// saturation, brightness, alpha is in range [0,1]
	
	// https://en.wikipedia.org/wiki/HSL_and_HSV#Converting_to_RGB

	h = h / 60;
	float C = v * s;
	float X = C * (1 - abs(h % 2 - 1));

	Color color = Color();
	if (h < 0)		return color;
	else if (h < 1) color = Color(C, X, 0);
	else if (h < 2)	color = Color(X, C, 0);
	else if (h < 3)	color = Color(0, C, X);
	else if (h < 4)	color = Color(0, X, C);
	else if (h < 5) color = Color(X, 0, C);
	else if (h < 6) color = Color(C, 0, X);
	else			return color;

	return color + Color(v - C, v - C, v - C, a);
}

const Color Color::HSV(int h, float s, float v)
{
	return HSV(h, s, v, 1);
}