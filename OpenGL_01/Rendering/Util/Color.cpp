#include "Color.h"
/*
 * Static parameters
 */
const Color Color::BLACK		= Color(0.0, 0.0, 0.0);
const Color Color::BLUE			= Color(0.0, 0.0, 1.0);
const Color Color::CYAN			= Color(0.0, 1.0, 1.0);
const Color Color::DARK_GRAY	= Color(0.25, 0.25, 0.25);
const Color Color::GRAY			= Color(0.5, 0.5, 0.5);
const Color Color::GREEN		= Color(0.0, 1.0, 0.0);
const Color Color::LIGHT_GRAY	= Color(0.75, 0.75, 0.75);
const Color Color::MAGENTA		= Color(1.0, 0.0, 1.0);
const Color Color::ORANGE		= Color(1.0, 0.80, 0.0);
const Color Color::PINK			= Color(1.0, 0.5, 0.5);
const Color Color::RED			= Color(1.0, 0.0, 0.0);
const Color Color::WHITE		= Color(1.0, 1.0, 1.0);
const Color Color::YELLOW		= Color(1.0, 1.0, 0.0);

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

const std::array<float, 3> Color::getHSV() const
{
	/* Credit: http://stackoverflow.com/a/6930407 */
	std::array<float, 3> output;
	float min, max, delta;

	min = (r < g) ? r : g;
	min = (min < b) ? min : b;
	max = (r > g) ? r : g;
	max = (max > b) ? max : b;
	delta = max - min;

	output[2] = max; // v

	if (delta < 0.00001)
	{
		output[0] = 0;
		output[1] = 0;
		return output;
	}
	if (max > 0.0)
	{
		output[1] = delta / max;
	}
	else
	{
		output[0] = NAN;
		output[1] = 0;
		return output;
	}
	if (r == max)
		output[0] = (g - b) / delta;		// between yellow & magenta
	else if (g == max)
		output[0] = 2 + (b - r) / delta;	// between cyan & yellow
	else
		output[0] = 4 + (r - g) / delta;	// between magenta & cyan

	output[0] *= 60.0f;
	if (output[0] < 0.0)
		output[0] += 360.0f;
	
	return output;
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

/**
 * Create color via HSV value
 * hue is in range [0,360]
 * saturation, brightness, alpha is in range [0,1]
 */
const Color Color::HSV(float h, float s, float v, float a) {
	
	// https://en.wikipedia.org/wiki/HSL_and_HSV#Converting_to_RGB

	h = h / 60;
	float C = v * s;
	float X = C * (1 - fabs( fmod(h,2) - 1));

	Color color = Color();
	if (h < 0)		return color;
	else if (h < 1) color = Color(C, X, 0);
	else if (h < 2)	color = Color(X, C, 0);
	else if (h < 3)	color = Color(0, C, X);
	else if (h < 4)	color = Color(0, X, C);
	else if (h < 5) color = Color(X, 0, C);
	else if (h < 6) color = Color(C, 0, X);
	else			return color;

	return Color(
		color.r + v - C,
		color.g + v - C,
		color.b + v - C,
		a);
}