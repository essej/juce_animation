/*
  ==============================================================================

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

//==============================================================================
/**
    
*/
struct AnimationCurve
{
	/** Determines how the function is weighted */
	enum Weight
	{
        /** Accelerating from zero. */
		In,

        /** Decelerating to zero. */
		Out,

        /** Acceleration halfway, then deceleration. */
		InOut,

        /** Deceleration halfway, then acceleration. */
		OutIn,
	};

	/** Curve functions to apply to an animation's value. */
	enum Function
	{
        /** No easing, linear tween. */
		Linear,

        /** Quadratic easing (t^2). */
		Quadratic,

        /** Cubic easing (t^3). */
		Cubic,

        /** Quartic easing (t^4). */
		Quartic,

        /** Quintic easing (t^5). */
		Quintic,

        /** Sinusoidal easing (sin(t)). */
		Sinusoidal,

        /** Exponential easing (2^t). */
		Exponential,

        /** Circular easing (sqrt(1-t^2)). */
		Circular,

        /** Elastic easing (exponentially decaying sinusoid). */
		Elastic,

        /** Back easing (overshoot cubic: (s+1)*t^3 - s*t^2). */
		Back,

        /** Bounce easing (exponentially decaying parabola). */
		Bounce
	};

	/** Creates a default AnimationCurve (Linear function, In weighting, 1.0
        amplitude, 0.0 overshoot, and clipping off).
    */
	AnimationCurve();

    /** Destructor. */
    virtual ~AnimationCurve() {};

    /** Manipulates the input value by the curve's function.

        This can be overriden to provide a custom curve
    */
	virtual float perform(float progress);

    /** The curve function to apply to the animation. */
    Function function;

    /** The function weighting to apply to the animation. */
    Weight   weight;

    /** The curve amplitude to apply to the animation. */
    float    amplitude;

    /** The curve overshoot to apply to the animation.

        NOTE: Only Function::Back supports overshooting.
    */
    float    overshoot;

    /** Whether or not to clip overshooting. */
    bool     clipValue;
};
