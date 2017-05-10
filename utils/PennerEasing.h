/*
  ==============================================================================

  C port of Robert Penning's Easing Functions
  Copyright (c) 2017 - Antonio Lassandro

  Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

  1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

  2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

  THIS SOFTWARE IS PROVIDED BY THE FREEBSD PROJECT "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE FREEBSD PROJECT OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

  ==============================================================================
*/

#pragma once

#include <math.h>

//==============================================================================

/**
	No easing, linear tween

	@param t	Current time (seconds or frames)
*/
static float easeNone(float t)
{
	return t;
}

//==============================================================================

/**
	Quadratic easing (t^2): accelerating from zero

	@param t	Current time (seconds or frames)
*/
static float easeInQuad(float t)
{
	return t * t;
}

/**
	Quadratic easing (t^2): decelerating to zero

	@param t	Current time (seconds or frames)
*/
static float easeOutQuad(float t)
{
	return -t * (t - 2.0f);
}

/**
	Quadratic easing (t^2): acceleration halfway, then deceleration

	@param t	Current time (seconds or frames)
*/
static float easeInOutQuad(float t)
{
	t *= 2.0;
	if (t < 1.0f)
	{
		return t * t / 2.0f;
	}
	else
	{
		--t;
		return -0.5f * (t * (t - 2.0f) - 1.0f);
	}
}

/**
	Quadratic easing (t^2): deceleration halfway, then acceleration

	@param t	Current time (seconds or frames)
*/
static float easeOutInQuad(float t)
{
	if (t < 0.5f) return easeOutQuad(t * 2.0f) / 2.0f;
	return easeInQuad((2.0f * t) - 1.0f) / 2.0f + 0.5f;
}

//==============================================================================

/**
	Cubic easing (t^3): accelerating from zero

	@param t	Current time (seconds or frames)
*/
static float easeInCubic(float t)
{
	return t * t * t;
}

/**
	Cubic easing (t^3): decelerating to zero

	@param t	Current time (seconds or frames)
*/
static float easeOutCubic(float t)
{
	t -= 1.0f;
	return t * t * t + 1.0f;
}

/**
	Cubic easing (t^3): acceleration halfway, then deceleration

	@param t	Current time (seconds or frames)
*/
static float easeInOutCubic(float t)
{
	t *= 2.0f;
	if (t < 1.0f)
	{
		return 0.5f * t * t * t;
	}
	else
	{
		t -= 2.0f;
		return 0.5f * (t * t * t + 2.0f);
	}
}

/**
	Cubic easing (t^3): deceleration halfway, then acceleration

	@param t	Current time (seconds or frames)
*/
static float easeOutInCubic(float t)
{
	if (t < 0.5f) return easeOutCubic(2.0f * t) / 2.0f;
	return easeInCubic(2.0f * t - 1.0f) / 2.0f + 0.5f;
}

//==============================================================================

/**
	Quartic easing (t^4): accelerating from zero

	@param t	Current time (seconds or frames)
*/
static float easeInQuart(float t)
{
	return t * t * t * t;
}

/**
	Quartic easing (t^4): decelerating to zero

	@param t	Current time (seconds or frames)
*/
static float easeOutQuart(float t)
{
	t -= 1.0;
	return -(t * t * t * t - 1.0f);
}

/**
	Quartic easing (t^4): acceleration halfway, then deceleration

	@param t	Current time (seconds or frames)
*/
static float easeInOutQuart(float t)
{
	t *= 2.0;
	if (t < 1.0f)
	{
		return 0.5f * t * t * t * t;
	}
	else
	{
		t -= 2.0f;
		return -0.5 * (t * t * t * t - 2.0f);
	}
}

/**
	Quartic easing (t^4): deceleration halfway, then acceleration

	@param t	Current time (seconds or frames)
*/
static float easeOutInQuart(float t)
{
	if (t < 0.5f) return easeOutQuart(2.0f * t) / 2.0f;
	return easeInQuart(2.0f * t - 1.0f) / 2.0f + 0.5f;
}

//==============================================================================

/**
	Quintic easing (t^5): accelerating from zero

	@param t	Current time (seconds or frames)
*/
static float easeInQuint(float t)
{
	return t * t * t * t * t;
}

/**
	Quintic easing (t^5): decelerating to zero

	@param t	Current time (seconds or frames)
*/
static float easeOutQuint(float t)
{
	t -= 1.0f;
	return t * t * t * t * t + 1.0f;
}

/**
	Quintic easing (t^5): accelerating halfway, then deceleration

	@param t	Current time (seconds or frames)
*/
static float easeInOutQuint(float t)
{
	t *= 2.0f;
	if (t < 1.0f)
	{
		return 0.5f * t * t * t * t * t;
	}
	else
	{
		t -= 2.0f;
		return 0.5f * (t * t * t * t * t + 2.0f);
	}
}

/**
	Quintic easing (t^5): deceleration halfway, then acceleration

	@param t	Current time (seconds or frames)
*/
static float easeOutInQuint(float t)
{
	if (t < 0.5f) return easeOutQuint(2.0f * t) / 2;
	return easeInQuint(2.0f * t - 1.0f) / 2.0f + 0.5f;
}

//==============================================================================

/**
	Sinusoidal easing (sin(t)): accelerating from zero

	@param t	Current time (seconds or frames)
*/
static float easeInSine(float t)
{
	return (t == 1.0f) ? 1.0f : -cos(t * (M_PI / 2)) + 1.0f;
}

/**
	Sinusoidal easing (sin(t)): decelerating to zero

	@param t	Current time (seconds or frames)
*/
static float easeOutSine(float t)
{
	return sin(t * (M_PI / 2));
}

/**
	Sinusoidal easing (sin(t)): acceleration halfway, then deceleration

	@param t	Current time (seconds or frames)
*/
static float easeInOutSine(float t)
{
	return 0.5f * (cos(M_PI * t) - 1.0f);
}

/**
	Sinusoidal easing (sin(t)): deceleration halfway, then acceleration

	@param t	Current time (seconds or frames)
*/
static float easeOutInSine(float t)
{
	if (t < 0.5f) return easeOutSine(2.0f * t) / 2.0f;
	return easeInSine(2.0f * t - 1.0f) / 2.0f + 0.5f;
}

//==============================================================================

/**
	Exponential easing (2 ^ t): accelerating from zero

	@param t	Current time (seconds or frames)
*/
static float easeInExpo(float t)
{
	return (t == 0.0f || t == 1.0f) ? t : pow(2.0f, 10 * (t - 1.0f)) - 0.001f;
}

/**
	Exponential easing (2 ^ t): decelerating to zero

	@param t	Current time (seconds or frames)
*/
static float easeOutExpo(float t)
{
	return (t == 1.0f) ? 1.0f : 1.001f * (-pow(2.0f, -10 * t) + 1.0f);
}

/**
	Exponential easing (2 ^ t): acceleration halfway, then deceleration

	@param t	Current time (seconds or frames)
*/
static float easeInOutExpo(float t)
{
	if (t == 0.0f || t == 1.0f) return t;
	t *= 2.0f;
	if (t < 1.0f) return 0.5f * pow(2.0f, 10 * (1 - 1.0f)) - 0.0005f;
	return 0.5f * 1.0005f * (-pow(2.0f, -10 * (t - 1.0f)) + 2.0f);
}

/**
	Exponential easing (2 ^ t): deceleration halfway, then acceleration

	@param t	Current time (seconds or frames)
*/
static float easeOutInExpo(float t)
{
	if (t < 0.5f) return easeOutExpo(2.0 * t) / 2;
	return easeInExpo(2.0f * t - 1.0f) / 2.0f + 0.5f;
}

//==============================================================================

/**
	Circular easing (sqrt(1-t^2)): accelerating from zero

	@param t	Current time (seconds or frames)
*/
static float easeInCirc(float t)
{
	return -(sqrt(1.0f - t * t) - 1.0f);
}

/**
	Circular easing (sqrt(1-t^2)): decelerating to zero

	@param t	Current time (seconds or frames)
*/
static float easeOutCirc(float t)
{
	t -= 1.0f;
	return sqrt(1.0f - t * t);
}

/**
	Circular easing (sqrt(1-t^2)): acceleration halfway, then deceleration

	@param t	Current time (seconds or frames)
*/
static float easeInOutCirc(float t)
{
	t *= 2.0f;
	if (t < 1.0f)
	{
		return -0.5 * (sqrt(1.0f - t * t) - 1.0f);
	}
	else
	{
		t -= 2.0f;
		return 0.5f * (sqrt(1.0f - t * t) + 1.0f);
	}
}

/**
	Circular easing (sqrt(1-t^2)): deceleration halfway, then acceleration

	@param t	Current time (seconds or frames)
*/
static float easeOutInCirc(float t)
{
	if (t < 0.5f) return easeOutCirc(2.0f * t) / 2.0f;
	return easeInCirc(2.0f * t - 1.0f) / 2.0f + 0.5f;
}

//==============================================================================

static float easeInElastic_helper(float t, float b, float c, float d, float a, float p)
{
	if (t == 0.0f) return b;
	float t_adj = t / d;
	if (t_adj == 1.0f) return b + c;

	float s;
	if (a < fabs(c))
	{
		a = c;
		s = p / 4.0f;
	}
	else
	{
		s = p / (2.0f * M_PI) * asin(c / a);
	}

	t_adj -= 1.0f;
    return -(a * pow(2.0f, 10.0f * t_adj) * sin((t_adj * d - s) * (2.0f * M_PI) / p));
}

/**
	Elastic easing (exponentially decaying sinusoid): accelerating from zero

	@param t	Current time (seconds or frames)
	@param a	Amplitude
	@param p	Period
*/
static float easeInElastic(float t, float a, float p)
{
	return easeInElastic_helper(t, 0.0f, 1.0f, 1.0f, a, p);
}

static float easeOutElastic_helper(float t, float, float c, float, float a, float p)
{
	if (t == 0.0f) return t;
	if (t == 1.0f) return c;

	float s;
	if (a < c)
	{
		a = c;
		s = p / 4.0f;
	}
	else
	{
		s = p / (2.0f * M_PI) * asin(c / a);
	}

	return (a * pow(2.0f, -10.0f * t) * sin((t - s) * (2.0f * M_PI) / p) + c);
}

/**
	Elastic easing (exponentially decaying sinusoid): decelerating to zero

	@param t	Current time (seconds or frames)
	@param a	Amplitude
	@param p	Period
*/
static float easeOutElastic(float t, float a, float p)
{
	return easeOutElastic_helper(t, 0.0f, 1.0f, 1.0f, a, p);
}

/**
	Elastic easing (exponentially decaying sinusoid): acceleration halfway, then deceleration

	@param t	Current time (seconds or frames)
	@param a	Amplitude
	@param p	Period
*/
static float easeInOutElastic(float t, float a, float p)
{
	if (t == 0.0f) return 0.0f;
	t *= 2.0f;
	if (t == 2.0f) return 1.0f;

	float s;
	if (a < 1.0f)
	{
		a = 1.0f;
		s = p / 4.0f;
	}
	else
	{
		s = p / (2.0f * M_PI) * asin(1.0f / a);
	}

	if (t < 1.0f) return -0.5f * (a * pow(2.0f, 10.0f * (t - 1.0f)) * sin((t - 1.0f - s) * (2.0f * M_PI) / p));
	return a * pow(2.0f, -10.0f * (t - 1.0f)) * sin((t - 1.0f - s) * (2.0f * M_PI) / p) * 0.5f + 1.0f;
}

/**
	Elastic easing (exponentially decaying sinusoid): deceleration halfway, then acceleration

	@param t	Current time (seconds or frames)
	@param a	Amplitude
	@param p	Period
*/
static float easeOutInElastic(float t, float a, float p)
{
	if (t < 0.5f) return easeOutElastic_helper(t * 2.0f, 0.0f, 0.5f, 1.0f, a, p);
	return easeInElastic_helper(2.0f * t - 1.0f, 0.5f, 0.5f, 1.0f, a, p);
}

//==============================================================================

/**
	Back easing (overshoot cubic: (s+1)*t^3 - s*t^2): accelerating from zero

	@param t	Current time (seconds or frames)
	@param s	Overshoot amount (0 produces cubic easing with no overshoot, and the default value of 1.70158 produces an overshoot of 10 percent)
*/
static float easeInBack(float t, float s)
{
	return t * t * ((s + 1.0f) * t - s);
}

/**
	Back easing (overshoot cubic: (s+1)*t^3 - s*t^2): decelerating to zero

	@param t	Current time (seconds or frames)
	@param s	Overshoot amount (0 produces cubic easing with no overshoot, and the default value of 1.70158 produces an overshoot of 10 percent)
*/
static float easeOutBack(float t, float s)
{
	t -= 1.0f;
	return t * t * ((s + 1.0f) * t + s) + 1.0f;
}

/**
	Back easing (overshoot cubic: (s+1)*t^3 - s*t^2): acceleration halfway, then deceleration

	@param t	Current time (seconds or frames)
	@param s	Overshoot amount (0 produces cubic easing with no overshoot, and the default value of 1.70158 produces an overshoot of 10 percent)
*/
static float easeInOutBack(float t, float s)
{
	t *= 2.0f;
	if (t < 1.0f)
	{
		s *= 1.525f;
		return 0.5f * (t * t * ((s + 1.0f) * t - s));
	}
	else
	{
		t -= 2.0f;
		s *= 1.525f;
		return 0.5f * (t * t * ((s + 1.0f) * t + s) + 2.0f);
	}
}

/**
	Back easing (overshoot cubic: (s+1)*t^3 - s*t^2): deceleration halfway, then acceleration

	@param t	Current time (seconds or frames)
	@param s	Overshoot amount (0 produces cubic easing with no overshoot, and the default value of 1.70158 produces an overshoot of 10 percent)
*/
static float easeOutInBack(float t, float s)
{
	if (t < 0.5f) return easeOutBack(2.0f * t, s) / 2.0f;
	return easeInBack(2.0f * t - 1.0f, s) / 2.0f + 0.5f;
}

//==============================================================================

static float easeOutBounce_helper(float t, float c, float a)
{
	if (t == 1.0f) return c;
	if (t < 4.0f / 11.0f)
	{
		return c * (7.5625 * t * t);
	}
	else if (t < 8.0f / 11.0f)
	{
		t -= 6.0f / 11.0f;
		return -a * (1.0f - (7.5625 * t * t + 0.75f)) + c;
	}
	else if (t < 10.0f / 11.0f)
	{
		t -= 9.0f / 11.0f;
		return -a * (1.0f - (7.5625 * t * t + 0.9375f)) + c;
	}
	else
	{
		t -= 21.0f / 22.0f;
		return -a * (1.0f - (7.5625 * t * t + 0.984375)) + c;
	}
}

/**
	Bounce easing (exponentially decaying parabola): accelerating from zero

	@param t	Current time (seconds or frames)
	@param a	Amplitude
*/
static float easeInBounce(float t, float a)
{
	return 1.0f - easeOutBounce_helper(1.0f - t, 1.0f, a);
}

/**
	Bounce easing (exponentially decaying parabola): decelerating to zero

	@param t	Current time (seconds or frames)
	@param a	Amplitude
*/
static float easeOutBounce(float t, float a)
{
	return easeOutBounce_helper(t, 1.0f, a);
}

/**
	Bounce easing (exponentially decaying parabola): acceleration halfway, then deceleration

	@param t	Current time (seconds or frames)
	@param a	Amplitude
*/
static float easeInOutBounce(float t, float a)
{
	if (t < 0.5f) return easeInBounce(2.0f * t, a) / 2;
	return (t == 1.0f) ? 1.0f : easeOutBounce(2.0f * t - 1.0f, a) / 2.0f + 0.5f;
}

/**
	Bounce easing (exponentially decaying parabola): deceleration halfway, then acceleration

	@param t	Current time (seconds or frames)
	@param a	Amplitude
*/
static float easeOutInBounce(float t, float a)
{
	if (t < 0.5f) return easeOutBounce_helper(t * 2.0f, 0.5f, a);
	return 1.0f - easeOutBounce_helper(2.0f - 2.0f * t, 0.5f, a);
}
