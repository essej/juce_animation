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
class AnimationCurve
{
public:
	/** Determines how the function is weighted */
	enum Weight
	{
		In,
		Out,
		InOut,
		OutIn,
	};

	/** Function presets */
	enum Function
	{
		Linear,
		Quadratic,
		Cubic,
		Quartic,
		Quintic,
		Sinusoidal,
		Exponential,
		Circular,
		Elastic,
		Back,
		Bounce,
		Custom
	};

	/** */
	AnimationCurve();

	/** Destructor */
	virtual ~AnimationCurve();

	/** */
	void setFunction(Function);

	/** */
    Function getFunction() const noexcept;

    /** */
    void setWeight(Weight newWeight);

    /** */
    Weight getWeight() const noexcept;

	/** Adjusts the default custom curve using Bezier control points */
	void setBezier(float controlPoint1X, float controlPoint1Y);

	/** */
	void setBezier(float controlPoint1X, float controlPoint1Y, float controlPoint2X, float controlPoint2Y);

	/** Override this to make a custom equation */
    virtual float customCurve(float progress, float amplitude, float overshoot, Weight weight) { return progress; }

	/** Adjusts the amplitude of the current curve */
	void setAmplitude(float newAmp);

	/** Returns the amplitude multiplier applied to the current curve */
    float getAmplitude() const noexcept;

    /** */
    void setOvershoot(float newOvershoot);

    /** */
    float getOvershoot() const noexcept;

	/** Determines whether or not to clip the curve to 0-1, even if the function were to extend past */
	void setOvershootStatus(bool allowedToOvershoot);

	/** Returns whether the function is allowed to overshoot */
    bool getOvershootStatus() const noexcept;

    /** */
	float perform(float progress);

private:
    Function currentFunction;
    Weight   currentWeight;
    float    currentAmplitude;
    float    currentOvershoot;
    bool     overshootStatus;
};
