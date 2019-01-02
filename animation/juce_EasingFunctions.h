/**  ==============================================================================

  This file is part of juce_animation.
  Copyright (c) 2017 - Antonio Lassandro

  juce_animation is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  juce_animation is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with juce_animation.  If not, see <http://www.gnu.org/licenses/>.

  ==============================================================================
*/

#pragma once

// =============================================================================

/** No easing, linear tween
*/
struct EaseLinear
{
    double operator() (double t) const noexcept
    {
        return t;
    }
};

// =============================================================================

/** Quadratic easing (t^2): accelerating from zero
*/
struct EaseInQuad
{
    double operator() (double t) const noexcept
    {
        return t * t;
    }
};

/** Quadratic easing (t^2): decelerating to zero
*/
struct EaseOutQuad
{
    double operator() (double t) const noexcept
    {
        return -t * (t - 2.0);
    }
};

/** Quadratic easing (t^2): acceleration halfway, then deceleration
*/
struct EaseInOutQuad
{
    double operator() (double t) const noexcept
    {
        t *= 2.0;
        if (t < 1.0) return t * t / 2.0;

        --t;
        return -0.5 * (t * (t - 2.0) - 1.0);
    }
};

/** Quadratic easing (t^2): deceleration halfway, then acceleration
*/
struct EaseOutInQuad
{
    double operator() (double t) const noexcept
    {
        if (t < 0.5)
        {
            t *= 2.0;
            return (-t * (t - 2.0)) / 2.0;
        }

        t = 2.0 * t - 1.0;
        return (t * t) / 2.0 + 0.5;
    }
};

// =============================================================================

/** Cubic easing (t^3): accelerating from zero
*/
struct EaseInCubic
{
    double operator() (double t) const noexcept
    {
        return t * t * t;
    }
};

/** Cubic easing (t^3): decelerating to zero
*/
struct EaseOutCubic
{
    double operator() (double t) const noexcept
    {
        t -= 1.0;
        return t * t * t + 1.0;
    }
};

/** Cubic easing (t^3): acceleration halfway, then deceleration
*/
struct EaseInOutCubic
{
    double operator() (double t) const noexcept
    {
        t *= 2.0;
        if (t < 1.0) return 0.5 * t * t * t;

        t -= 2.0;
        return 0.5 * (t * t * t + 2.0);
    }
};

/** Cubic easing (t^3): deceleration halfway, then acceleration
*/
struct EaseOutInCubic
{
    double operator() (double t) const noexcept
    {
        if (t < 0.5)
        {
            t = 2.0 * t - 1.0;
            return (t * t * t + 1.0) / 2.0;
        }

        t = 2.0 * t - 1.0;
        return (t * t * t) / 2.0 + 0.5;
    }
};

// =============================================================================

/** Quartic easing (t^4): accelerating from zero
*/
struct EaseInQuart
{
    double operator() (double t) const noexcept
    {
        return t * t * t * t;
    }
};

/** Quartic easing (t^4): decelerating to zero
*/
struct EaseOutQuart
{
    double operator() (double t) const noexcept
    {
        t -= 1.0;
        return -(t * t * t * t - 1.0);
    }
};

/** Quartic easing (t^4): acceleration halfway, then deceleration
*/
struct EaseInOutQuart
{
    double operator() (double t) const noexcept
    {
        t *= 2.0;
        if (t < 1.0) return 0.5 * t * t * t * t;

        t -= 2.0;
        return -0.5 * (t * t * t * t - 2.0);
    }
};

/** Quartic easing (t^4): deceleration halfway, then acceleration
*/
struct EaseOutInQuart
{
    double operator() (double t) const noexcept
    {
        if (t < 0.5)
        {
            t = 2.0 * t - 1.0;
            return -(t * t * t * t - 1.0) / 2.0;
        }

        t = 2.0 * t - 1.0;
        return (t * t * t * t) / 2.0 + 0.5;
    }
};

// =============================================================================

/** Quintic easing (t^5): accelerating from zero
*/
struct EaseInQuint
{
    double operator() (double t) const noexcept
    {
        return t * t * t * t * t;
    }
};

/** Quintic easing (t^5): decelerating to zero
*/
struct EaseOutQuint
{
    double operator() (double t) const noexcept
    {
        t -= 1.0;
        return t * t * t * t * t + 1.0;
    }
};

/** Quintic easing (t^5): accelerating halfway, then deceleration
*/
struct EaseInOutQuint
{
    double operator() (double t) const noexcept
    {
        t *= 2.0;
        if (t < 1.0) return 0.5 * t * t * t * t * t;

        t -= 2.0;
        return 0.5 * (t * t * t * t * t + 2.0);
    }
};

/** Quintic easing (t^5): accelerating halfway, then deceleration
*/
struct EaseOutInQuint
{
    double operator() (double t) const noexcept
    {
        if (t < 0.5)
        {
            t = 2.0 * t - 1.0;
            return (t * t * t * t * t + 1.0) / 2.0;
        }

        t = 2.0 * t - 1.0;
        return (t * t * t * t * t) / 2.0 + 0.5;
    }
};

// =============================================================================

/** Sinusoidal easing (sin(t)): accelerating from zero
*/
struct EaseInSine
{
    double operator() (double t) const noexcept
    {
        const double PI = juce::MathConstants<double>::pi;
        return (t == 1.0) ? 1.0 : -cos(t * (PI / 2.0)) + 1.0;
    }
};

/** Sinusoidal easing (sin(t)): decelerating to zero
*/
struct EaseOutSine
{
    double operator() (double t) const noexcept
    {
        const double PI = juce::MathConstants<double>::pi;
        return sin(t * (PI / 2.0));
    }
};

/** Sinusoidal easing (sin(t)): acceleration halfway, then deceleration
*/
struct EaseInOutSine
{
    double operator() (double t) const noexcept
    {
        const double PI = juce::MathConstants<double>::pi;
        return 0.5 * (cos(PI * t) - 1.0);
    }
};

/** Sinusoidal easing (sin(t)): acceleration halfway, then deceleration
*/
struct EaseOutInSine
{
    double operator() (double t) const noexcept
    {
        const double PI = juce::MathConstants<double>::pi;

        if (t < 0.5)
        {
            t *= 2.0;
            return (sin(t * (PI / 2.0))) / 2.0;
        }

        t = 2.0 * t - 1.0;
        if (t == 1.0) return t / 2.0 + 0.5;
        return (-cos(t * (PI / 2.0)) + 1.0) / 2.0 + 0.5;
    }
};

// =============================================================================

/** Exponential easing (2 ^ t): accelerating from zero
*/
struct EaseInExpo
{
    double operator() (double t) const noexcept
    {
        if (t == 0.0 || t == 1.0) return t;
        return pow(2.0, 10.0 * (t - 1.0)) - 0.001;
    }
};

/** Exponential easing (2 ^ t): decelerating to zero
*/
struct EaseOutExpo
{
    double operator() (double t) const noexcept
    {
        if (t == 1.0) return t;
        return 1.001 * (-pow(2.0, -10.0 * t) + 1.0);
    }
};

/** Exponential easing (2 ^ t): acceleration halfway, then deceleration
*/
struct EaseInOutExpo
{
    double operator() (double t) const noexcept
    {
        if (t == 0.0 || t == 1.0) return t;

        t *= 2.0;

        if (t < 1.0) return 0.5 * pow(2.0, 10.0 * (1.0 - 1.0)) - 0.0005;
        return 0.5 * 1.0005 * -pow(2.0, -10 * (t - 1.0)) + 2.0;
    }
};

/** Exponential easing (2 ^ t): deceleration halfway, then acceleration
*/
struct EaseOutInExpo
{
    double operator() (double t) const noexcept
    {
        if (t < 0.5)
        {
            t *= 2.0;

            if (t == 0.0 || t == 1.0)
                return t / 2.0;

            return (1.001 * (-pow(2.0, -10.0 * t) + 1.0)) / 2.0;
        }

        t = 2.0 * t - 1.0;

        if (t == 0.0 || t == 1.0)
            return t / 2.0 + 0.5;

        return (pow(2.0, 10.0 * (t - 1.0)) - 0.001) / 2.0 + 0.5;
    }
};

//==============================================================================

/** Circular easing (sqrt(1-t^2)): accelerating from zero
*/
struct EaseInCirc
{
    double operator() (double t) const noexcept
    {
        return -(sqrt(1.0 - t * t) - 1.0);
    }
};

/** Circular easing (sqrt(1-t^2)): decelerating to zero
*/
struct EaseOutCirc
{
    double operator() (double t) const noexcept
    {
        t -= 1.0;
        return sqrt(1.0 - t * t);
    }
};

/** Circular easing (sqrt(1-t^2)): acceleration halfway, then deceleration
*/
struct EaseInOutCirc
{
    double operator() (double t) const noexcept
    {
        t *= 2.0;
        if (t < 1.0) return -0.5 * (sqrt(1.0 - t * t) - 1.0);

        t -= 2.0;
        return 0.5 * (sqrt(1.0 - t * t) + 1.0);
    }
};

/** Circular easing (sqrt(1-t^2)): deceleration halfway, then acceleration
*/
struct EaseOutInCirc
{
    double operator() (double t) const noexcept
    {
        if (t < 0.5)
        {
            t = (2.0 * t) - 1.0;
            return sqrt(1.0 - t * t) / 2.0;
        }

        t = 2.0 * t - 1.0;
        return -(sqrt(1.0 - t * t) - 1.0) / 2.0 + 0.5;
    }
};

//==============================================================================

/** Elastic easing (exponentially decaying sinusoid): accelerating from zero
*/
struct EaseInElastic
{
    double amplitude = 1.0, period = 1.0;

    double operator() (double t) const noexcept
    {
        return helper(t, 0.0, 1.0, 1.0, amplitude, period);
    }

    static double
    helper(double t, double b, double c, double d, double a, double p)
    {
        const double PI = juce::MathConstants<double>::pi;

        if (t == 0.0) return b;

        double t_adj = t / d;

        if (t_adj == 1.0) return b + c;

        float s;
        if (a < fabs(c))
        {
            a = c;
            s = p / 4.0;
        }
        else
        {
            s = p / (2.0 * PI) * asin(c / a);
        }

        t_adj -= 1.0;

        return -(a * pow(2.0, 10.0 * t_adj)
               * sin((t_adj * d - s) * (2.0 * PI) / p));
    }
};

/** Elastic easing (exponentially decaying sinusoid): decelerating to zero
*/
struct EaseOutElastic
{
    double amplitude = 1.0, period = 1.0;

    double operator() (double t) const noexcept
    {
        return helper(t, 0.0, 1.0, 1.0, amplitude, period);
    }

    static double
    helper(double t, double b, double c, double d, double a, double p)
    {
        const double PI = juce::MathConstants<double>::pi;

        if (t == 0.0) return t;
        if (t == 1.0) return c;

        float s;
        if (a < c)
        {
            a = c;
            s = p / 4.0;
        }
        else
        {
            s = p / (2.0 * PI) * asin(c / a);
        }

        return a * pow(2.0, -10.0 * t) * sin((t - s) * (2.0 * PI) / p) + c;
    }
};

/** Elastic easing (exponentially decaying sinusoid): acceleration halfway, then
   deceleration
*/
struct EaseInOutElastic
{
    double amplitude = 1.0, period = 1.0;

    double operator() (double t) const noexcept
    {
        const double PI = juce::MathConstants<double>::pi;

        if (t == 0.0) return 0.0;

        t *= 2.0;

        if (t == 2.0) return 1.0;

        double s;
        double a = amplitude;

        if (amplitude < 1.0)
        {
            a = 1.0;
            s = period / 4.0;
        }
        else
        {
            s = period / (2.0 * PI) * asin(1.0 / a);
        }

        if (t < 1.0)
        {
            return -0.5 * (a * pow(2.0, 10.0 * (t - 1.0))
                   * sin((t - 1.0 - s) * (2.0 * PI) / period));
        }

        return a * pow(2.0, -10.0 * (t - 1.0))
               * sin((t - 1.0 - s) * (2.0 * PI) / period) * 0.5 + 1.0;
    }
};

/** Elastic easing (exponentially decaying sinusoid): deceleration halfway, then
   acceleration
*/
struct EaseOutInElastic
{
    double amplitude = 1.0, period = 1.0;

    double operator() (double t) const noexcept
    {
        if (t < 0.5)
        {
            return EaseOutElastic::helper(
                t * 2.0, 0.0, 0.5, 1.0, amplitude, period
            );
        }

        return EaseInElastic::helper(
            2.0 * t - 1.0, 0.5, 0.5, 1.0, amplitude, period
        );
    }
};

//==============================================================================

/** Back easing (overshoot cubic: (s+1)*t^3 - s*t^2): accelerating from zero
*/
struct EaseInBack
{
    double overshoot = 1.70158;

    double operator() (double t) const noexcept
    {
        return t * t * ((overshoot + 1.0) * t - overshoot);
    }
};

/** Back easing (overshoot cubic: (s+1)*t^3 - s*t^2): decelerating to zero
*/
struct EaseOutBack
{
    double overshoot = 1.70158;

    double operator() (double t) const noexcept
    {
        t -= 1.0;
        return t * t * ((overshoot + 1.0) * t + overshoot) + 1.0;
    }
};

/** Back easing (overshoot cubic: (s+1)*t^3 - s*t^2): acceleration halfway, then
   deceleration
*/
struct EaseInOutBack
{
    double overshoot = 1.70158;

    double operator() (double t) const noexcept
    {
        double s = overshoot;

        t *= 2.0;
        if (t < 1.0)
        {
            s *= 1.525;
            return 0.5 * (t * t * ((s + 1.0) * t - s));
        }
        else
        {
            t -= 2.0;
            s *= 1.525;
            return 0.5 * (t * t * ((s + 1.0) * t + s) + 2.0);
        }
    }
};

/** Back easing (overshoot cubic: (s+1)*t^3 - s*t^2): deceleration halfway, then
    acceleration
*/
struct EaseOutInBack
{
    double overshoot = 1.70158;

    double operator() (double t) const noexcept
    {
        if (t < 0.5)
        {
            t = (2.0 * t) - 1.0;
            return (t * t * ((overshoot + 1.0) * t + overshoot) + 1.0) / 2.0;
        }

        t = 2.0 * t - 1.0;
        return (t * t * ((overshoot + 1.0) * t - overshoot)) / 2.0 + 0.5;
    }
};

//==============================================================================

/** Bounce easing (exponentially decaying parabola): decelerating to zero
*/
struct EaseOutBounce
{
    double amplitude = 1.0;

    double operator() (double t) const noexcept
    {
        return helper(t, 1.0, amplitude);
    }

    static double helper(double t, double c, double a)
    {
        if (t == 1.0) return c;

        if (t < 4.0 / 11.0)
        {
            return c * (7.5625 * t * t);
        }
        else if (t < 8.0 / 11.0)
        {
            t -= 6.0 / 11.0;
            return -a * (1.0 - (7.5625 * t * t + 0.75)) + c;
        }
        else if (t < 10.0 / 11.0)
        {
            t -= 9.0 / 11.0;
            return -a * (1.0 - (7.5625 * t * t + 0.9375)) + c;
        }
        else
        {
            t -= 21.0 / 22.0;
            return -a * (1.0 - (7.5625 * t * t + 0.984375)) + c;
        }
    }
};

/** Bounce easing (exponentially decaying parabola): accelerating from zero
*/
struct EaseInBounce
{
    double amplitude = 1.0;

    double operator() (double t) const noexcept
    {
        return 1.0 - EaseOutBounce::helper(1.0 - t, 1.0, amplitude);
    }
};

/** Bounce easing (exponentially decaying parabola): acceleration halfway, then
   deceleration
*/
struct EaseInOutBounce
{
    double amplitude = 1.0;

    double operator() (double t) const noexcept
    {
        if (t < 0.5)
        {
            t = 1.0 - (2.0 * t);
            return (1.0 - EaseOutBounce::helper(t, 1.0, amplitude)) / 2.0;
        }

        if (t == 1.0) return 1.0;

        t = 2.0 * t - 1.0;
        return EaseOutBounce::helper(t, 1.0, amplitude) / 2.0 + 0.5;
    }
};

/** Bounce easing (exponentially decaying parabola): deceleration halfway, then
    acceleration
*/
struct EaseOutInBounce
{
    double amplitude = 1.0;

    double operator() (double t) const noexcept
    {
        if (t < 0.5) return EaseOutBounce::helper(t * 2.0, 0.5, amplitude);
        return (1.0 - EaseOutBounce::helper(2.0 - 2.0 * t, 0.5, amplitude));
    }
};
