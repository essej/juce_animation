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

namespace AnimatedPositionBehaviours
{

/** Abstract easing behaviour. Supports duration, looping, and ping-ponging.
*/
struct EasingFunction
{
    /** The number of times the animation should loop. If the loop count is zero
        the animation will play once and stop. If the loop count is less than
        zero the animation will loop indefinitely.
    */
    int loops = 0;

    /** The duration of the animation in seconds. If this is zero the
        animation will end immediately.
    */
    double duration = 0.0;

    /** Enables ping-pong mode when looping is also enabled. This will cause the
        next loop to start from the previous position instead of resetting the
        position.
    */
    bool pingpong = false;

    // =========================================================================

    virtual ~EasingFunction() {}

    /** Override this method to perform the easing function. */
    virtual double tick(double t) const noexcept = 0;

    /** Called by AnimatedPosition<> to provide a velocity and starting position
        to the animation behaviour. This allows an animation to start midway,
        such as a bouncing effect that follows dragging a view and releasing.
    */
    virtual void releasedWithVelocity(double p, double v) noexcept final
    {
        time = 0.0;
        offset = p;
        currentLoop = 0;
        pingpongStatus = false;
    }

    /** Called by AnimatedPosition<> to get the next position value. This method
        will convert the absolute milliseconds to a proportion of total elapsed
        time divded by duration. If duration is 0 this will return the provided
        position and the animation will subsequently end when isStopped() is
        called afterwards.
    */
    virtual double getNextPosition(double p, double t) noexcept final
    {
        if (duration > 0.0)
        {
            time += t;

            const double proportion = (pingpongStatus)
                ? 1.0 - (time / duration)
                : time / duration;

            return (offset != 1.0)
                ? (tick(proportion) / (1.0 / (1.0 - offset))) + offset
                : tick(1.0);
        }
        else
        {
            return p;
        }
    }

    /** Called by AnimatedPosition<> to determine whether or not the animation
        should end. This method handles the duration, looping, and ping-pong
        logic.
    */
    virtual bool isStopped(double p) noexcept final
    {
        if (time >= duration)
        {
            time   = 0.0;
            offset = 0.0;

            if (loops != 0)
            {
                if (pingpong)
                    pingpongStatus = !pingpongStatus;

                if (loops > 0)
                {
                    if (currentLoop >= loops)
                    {
                        currentLoop = 0;
                        return true;
                    }
                    else
                    {
                        currentLoop++;
                    }
                }
            }
            else
            {
                return true;
            }
        }

        return false;
    }

protected:
    double time     = 0.0;
    double offset   = 0.0;
    int currentLoop = 0;
    bool pingpongStatus = false;
};

// =============================================================================

/** No easing, linear tween
*/
struct EaseLinear final : EasingFunction
{
    double tick(double t) const noexcept override
    {
        return t;
    }
};

// =============================================================================

/** Quadratic easing (t^2): accelerating from zero
*/
struct EaseInQuad final : EasingFunction
{
    double tick(double t) const noexcept override
    {
        return t * t;
    }
};

/** Quadratic easing (t^2): decelerating to zero
*/
struct EaseOutQuad final : EasingFunction
{
    double tick(double t) const noexcept override
    {
        return -t * (t - 2.0);
    }
};

/** Quadratic easing (t^2): acceleration halfway, then deceleration
*/
struct EaseInOutQuad final : EasingFunction
{
    double tick(double t) const noexcept override
    {
        t *= 2.0;
        if (t < 1.0) return t * t / 2.0;

        --t;
        return -0.5 * (t * (t - 2.0) - 1.0);
    }
};

/** Quadratic easing (t^2): deceleration halfway, then acceleration
*/
struct EaseOutInQuad final : EasingFunction
{
    double tick(double t) const noexcept override
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
struct EaseInCubic final : EasingFunction
{
    double tick(double t) const noexcept override
    {
        return t * t * t;
    }
};

/** Cubic easing (t^3): decelerating to zero
*/
struct EaseOutCubic final : EasingFunction
{
    double tick(double t) const noexcept override
    {
        t -= 1.0;
        return t * t * t + 1.0;
    }
};

/** Cubic easing (t^3): acceleration halfway, then deceleration
*/
struct EaseInOutCubic final : EasingFunction
{
    double tick(double t) const noexcept override
    {
        t *= 2.0;
        if (t < 1.0) return 0.5 * t * t * t;

        t -= 2.0;
        return 0.5 * (t * t * t + 2.0);
    }
};

/** Cubic easing (t^3): deceleration halfway, then acceleration
*/
struct EaseOutInCubic final : EasingFunction
{
    double tick(double t) const noexcept override
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
struct EaseInQuart final : EasingFunction
{
    double tick(double t) const noexcept override
    {
        return t * t * t * t;
    }
};

/** Quartic easing (t^4): decelerating to zero
*/
struct EaseOutQuart final : EasingFunction
{
    double tick(double t) const noexcept override
    {
        t -= 1.0;
        return -(t * t * t * t - 1.0);
    }
};

/** Quartic easing (t^4): acceleration halfway, then deceleration
*/
struct EaseInOutQuart final : EasingFunction
{
    double tick(double t) const noexcept override
    {
        t *= 2.0;
        if (t < 1.0) return 0.5 * t * t * t * t;

        t -= 2.0;
        return -0.5 * (t * t * t * t - 2.0);
    }
};

/** Quartic easing (t^4): deceleration halfway, then acceleration
*/
struct EaseOutInQuart final : EasingFunction
{
    double tick(double t) const noexcept override
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
struct EaseInQuint final : EasingFunction
{
    double tick(double t) const noexcept override
    {
        return t * t * t * t * t;
    }
};

/** Quintic easing (t^5): decelerating to zero
*/
struct EaseOutQuint final : EasingFunction
{
    double tick(double t) const noexcept override
    {
        t -= 1.0;
        return t * t * t * t * t + 1.0;
    }
};

/** Quintic easing (t^5): accelerating halfway, then deceleration
*/
struct EaseInOutQuint final : EasingFunction
{
    double tick(double t) const noexcept override
    {
        t *= 2.0;
        if (t < 1.0) return 0.5 * t * t * t * t * t;

        t -= 2.0;
        return 0.5 * (t * t * t * t * t + 2.0);
    }
};

/** Quintic easing (t^5): accelerating halfway, then deceleration
*/
struct EaseOutInQuint final : EasingFunction
{
    double tick(double t) const noexcept override
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
struct EaseInSine final : EasingFunction
{
    double tick(double t) const noexcept override
    {
        const double PI = juce::MathConstants<double>::pi;
        return (t == 1.0) ? 1.0 : -cos(t * (PI / 2.0)) + 1.0;
    }
};

/** Sinusoidal easing (sin(t)): decelerating to zero
*/
struct EaseOutSine final : EasingFunction
{
    double tick(double t) const noexcept override
    {
        const double PI = juce::MathConstants<double>::pi;
        return sin(t * (PI / 2.0));
    }
};

/** Sinusoidal easing (sin(t)): acceleration halfway, then deceleration
*/
struct EaseInOutSine final : EasingFunction
{
    double tick(double t) const noexcept override
    {
        const double PI = juce::MathConstants<double>::pi;
        return 0.5 * (cos(PI * t) - 1.0);
    }
};

/** Sinusoidal easing (sin(t)): acceleration halfway, then deceleration
*/
struct EaseOutInSine final : EasingFunction
{
    double tick(double t) const noexcept override
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
struct EaseInExpo final : EasingFunction
{
    double tick(double t) const noexcept override
    {
        if (t == 0.0 || t == 1.0) return t;
        return pow(2.0, 10.0 * (t - 1.0)) - 0.001;
    }
};

/** Exponential easing (2 ^ t): decelerating to zero
*/
struct EaseOutExpo final : EasingFunction
{
    double tick(double t) const noexcept override
    {
        if (t == 1.0) return t;
        return 1.001 * (-pow(2.0, -10.0 * t) + 1.0);
    }
};

/** Exponential easing (2 ^ t): acceleration halfway, then deceleration
*/
struct EaseInOutExpo final : EasingFunction
{
    double tick(double t) const noexcept override
    {
        if (t == 0.0 || t == 1.0) return t;

        t *= 2.0;

        if (t < 1.0) return 0.5 * pow(2.0, 10.0 * (1.0 - 1.0)) - 0.0005;
        return 0.5 * 1.0005 * -pow(2.0, -10 * (t - 1.0)) + 2.0;
    }
};

/** Exponential easing (2 ^ t): deceleration halfway, then acceleration
*/
struct EaseOutInExpo final : EasingFunction
{
    double tick(double t) const noexcept override
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
struct EaseInCirc final : EasingFunction
{
    double tick(double t) const noexcept override
    {
        return -(sqrt(1.0 - t * t) - 1.0);
    }
};

/** Circular easing (sqrt(1-t^2)): decelerating to zero
*/
struct EaseOutCirc final : EasingFunction
{
    double tick(double t) const noexcept override
    {
        t -= 1.0;
        return sqrt(1.0 - t * t);
    }
};

/** Circular easing (sqrt(1-t^2)): acceleration halfway, then deceleration
*/
struct EaseInOutCirc final : EasingFunction
{
    double tick(double t) const noexcept override
    {
        t *= 2.0;
        if (t < 1.0) return -0.5 * (sqrt(1.0 - t * t) - 1.0);

        t -= 2.0;
        return 0.5 * (sqrt(1.0 - t * t) + 1.0);
    }
};

/** Circular easing (sqrt(1-t^2)): deceleration halfway, then acceleration
*/
struct EaseOutInCirc final : EasingFunction
{
    double tick(double t) const noexcept override
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
struct EaseInElastic final : EasingFunction
{
    double tick(double t) const noexcept override
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

    double amplitude = 1.0, period = 1.0;
};

/** Elastic easing (exponentially decaying sinusoid): decelerating to zero
*/
struct EaseOutElastic final : EasingFunction
{
    double tick(double t) const noexcept override
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

    double amplitude = 1.0, period = 1.0;
};

/** Elastic easing (exponentially decaying sinusoid): acceleration halfway, then
   deceleration
*/
struct EaseInOutElastic final : EasingFunction
{
    double tick(double t) const noexcept override
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

    double amplitude = 1.0, period = 1.0;
};

/** Elastic easing (exponentially decaying sinusoid): deceleration halfway, then
   acceleration
*/
struct EaseOutInElastic final : EasingFunction
{
    double amplitude = 1.0, period = 1.0;

    double tick(double t) const noexcept override
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
struct EaseInBack final : EasingFunction
{
    double overshoot = 1.70158;

    double tick(double t) const noexcept override
    {
        return t * t * ((overshoot + 1.0) * t - overshoot);
    }
};

/** Back easing (overshoot cubic: (s+1)*t^3 - s*t^2): decelerating to zero
*/
struct EaseOutBack final : EasingFunction
{
    double overshoot = 1.70158;

    double tick(double t) const noexcept override
    {
        t -= 1.0;
        return t * t * ((overshoot + 1.0) * t + overshoot) + 1.0;
    }
};

/** Back easing (overshoot cubic: (s+1)*t^3 - s*t^2): acceleration halfway, then
   deceleration
*/
struct EaseInOutBack final : EasingFunction
{
    double overshoot = 1.70158;

    double tick(double t) const noexcept override
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
struct EaseOutInBack final : EasingFunction
{
    double overshoot = 1.70158;

    double tick(double t) const noexcept override
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
struct EaseOutBounce final : EasingFunction
{
    double tick(double t) const noexcept override
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

    double amplitude = 1.0;
};

/** Bounce easing (exponentially decaying parabola): accelerating from zero
*/
struct EaseInBounce final : EasingFunction
{
    double tick(double t) const noexcept override
    {
        return 1.0 - EaseOutBounce::helper(1.0 - t, 1.0, amplitude);
    }

    double amplitude = 1.0;
};

/** Bounce easing (exponentially decaying parabola): acceleration halfway, then
   deceleration
*/
struct EaseInOutBounce final : EasingFunction
{
    double tick(double t) const noexcept override
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

    double amplitude = 1.0;
};

/** Bounce easing (exponentially decaying parabola): deceleration halfway, then
    acceleration
*/
struct EaseOutInBounce final : EasingFunction
{
    double amplitude = 1.0;

    double tick(double t) const noexcept override
    {
        if (t < 0.5) return EaseOutBounce::helper(t * 2.0, 0.5, amplitude);
        return (1.0 - EaseOutBounce::helper(2.0 - 2.0 * t, 0.5, amplitude));
    }
};

}
