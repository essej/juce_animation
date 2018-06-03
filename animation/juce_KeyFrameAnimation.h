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
    A struct containing keyframe information.
*/
struct KeyFrame
{
    /** Creates an empty keyframe at position 0.0. */
    KeyFrame() : position(0.0), value() {}

    /** Creates a keyframe for a value at a given position. */
    KeyFrame(double p, juce::var v) : position(p), value(v) {}

    KeyFrame operator=(const KeyFrame &k)
    {
        position = k.position;
        value    = k.value;
        return *this;
    }

    bool operator==(KeyFrame k) const { return (position == k.position); }
    bool operator!=(KeyFrame k) const { return !(*this == k);            }
    bool operator> (KeyFrame k) const { return (position >  k.position); }
    bool operator>=(KeyFrame k) const { return (position >= k.position); }
    bool operator< (KeyFrame k) const { return (position <  k.position); }
    bool operator<=(KeyFrame k) const { return (position <= k.position); }

    double getPosition() const { return position; }
    juce::var getValue() const { return value;    }

private:
    double position;
    juce::var value;
};

//==============================================================================

/**
	A base class for animations
*/
class KeyFrameAnimation : public Animation
{
public:
    /** Creates an empty animation */
    KeyFrameAnimation() {};

    /** Creates an animation with a specified range. */
    KeyFrameAnimation(var startValue, var endValue);

    /** Sets the animation curve of the animation */
    void setAnimationCurve(const AnimationCurve& newCurve);

    /** Returns the current AnimationCurve */
    AnimationCurve getAnimationCurve();

    /** Sets the starting value of the animation. */
    void setStartValue(var value);

    /** Returns the value set by setStartValue(). */
    var getStartValue() const;

    /** Sets the end value of the animation. */
    void setEndValue(var value);

    /** Returns the value set by setEndValue() */
    var getEndValue() const;

    /** Returns the current value the animation is at. */
    var getCurrentValue() const;

    /** Sets the value of a property at a specified keyframe */
    void setKeyValue(double, var);

    /** Returns the value of a property at a specified keyframe */
    var getKeyValue(double progress) const;

protected:
    void handleAnimationStarted() override;

    void handleAnimationLoopChanged() override;

    /** Called when the animation advances. This can be overriden to provide
        custom behavior for the animation.
    */
    virtual void update(const double progress) override;

    /** Called when the animation begins or its loop changes. This sets the
        animation to the correct keyframe based on direction.
    */
    void initKeyFrames();

    /** Returns the next upcoming keyframe.

        If the animation direction is Forward this will return the next
        keyframe closer to 1.0, otherwise this will return the next keyframe
        closer to 0.0.
    */
    KeyFrame getNextKeyFrame(const double progress) const;

private:
    var      currentValue;
    KeyFrame currentKeyStart;
    KeyFrame currentKeyEnd;

    AnimationCurve curve;

    SortedSet<KeyFrame> keyframes;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(KeyFrameAnimation)
};
