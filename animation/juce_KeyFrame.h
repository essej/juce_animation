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
    /** Creates a keyframe for a value at a given position. */
    KeyFrame(double p, juce::var v) : position(p), value(v) {}

    KeyFrame operator=(const KeyFrame &k)
    {
        jassert(value.hasSameTypeAs(k.value));
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
