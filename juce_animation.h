/*
 ==============================================================================

  This file is part of juce_animation.
  Copyright (c) 2018 - Antonio Lassandro

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

/*******************************************************************************
BEGIN_JUCE_MODULE_DECLARATION

 ID:               juce_animation
 vendor:           Antonio Lassandro
 version:          0.1.0
 name:             JUCE animation classes
 description:      Classes for creating animations
 website:          http://www.github.com/lassandroan/juce_animation
 license:          GPLv3

 dependencies:     juce_core, juce_data_structures, juce_events, juce_gui_basics

END_JUCE_MODULE_DECLARATION
******************************************************************************/

#pragma once
#define JUCE_ANIMATION_H_INCLUDED

#include <juce_core/juce_core.h>
#include <juce_data_structures/juce_data_structures.h>
#include <juce_events/juce_events.h>
#include <juce_gui_basics/juce_gui_basics.h>

//==============================================================================

/** Config: JUCE_ANIMATION_ENABLE_TYPEDEFS

    Enables a set of typedefs to access animation types more easily. Can be
    disabled if you would like to use your own or change them.

    The typedefs will be the easing function name with "Animation" appended. For
    example, "EaseInOutQuint" becomes "EaseInOutQuintAnimation".
*/
#ifndef JUCE_ANIMATION_ENABLE_TYPEDEFS
 #define JUCE_ANIMATION_ENABLE_TYPEDEFS 1
#endif

//==============================================================================

namespace juce
{
    #include "animation/juce_EasingFunctions.h"
    #include "animation/juce_AnimatedPositionBehaviours.h"

    #if JUCE_ANIMATION_ENABLE_TYPEDEFS

    #define ANIMATION_TYPEDEF(b)                                               \
    typedef AnimatedPosition<AnimatedPositionBehaviours::EasingAnimation<b>>   \
    b##Animation;

    ANIMATION_TYPEDEF(EaseLinear);
    ANIMATION_TYPEDEF(EaseInQuad);
    ANIMATION_TYPEDEF(EaseOutQuad);
    ANIMATION_TYPEDEF(EaseInOutQuad);
    ANIMATION_TYPEDEF(EaseOutInQuad);
    ANIMATION_TYPEDEF(EaseInCubic);
    ANIMATION_TYPEDEF(EaseOutCubic);
    ANIMATION_TYPEDEF(EaseInOutCubic);
    ANIMATION_TYPEDEF(EaseOutInCubic);
    ANIMATION_TYPEDEF(EaseInQuart);
    ANIMATION_TYPEDEF(EaseOutQuart);
    ANIMATION_TYPEDEF(EaseInOutQuart);
    ANIMATION_TYPEDEF(EaseOutInQuart);
    ANIMATION_TYPEDEF(EaseInQuint);
    ANIMATION_TYPEDEF(EaseOutQuint);
    ANIMATION_TYPEDEF(EaseInOutQuint);
    ANIMATION_TYPEDEF(EaseOutInQuint);
    ANIMATION_TYPEDEF(EaseInSine);
    ANIMATION_TYPEDEF(EaseOutSine);
    ANIMATION_TYPEDEF(EaseInOutSine);
    ANIMATION_TYPEDEF(EaseOutInSine);
    ANIMATION_TYPEDEF(EaseInExpo);
    ANIMATION_TYPEDEF(EaseOutExpo);
    ANIMATION_TYPEDEF(EaseInOutExpo);
    ANIMATION_TYPEDEF(EaseOutInExpo);
    ANIMATION_TYPEDEF(EaseInCirc);
    ANIMATION_TYPEDEF(EaseOutCirc);
    ANIMATION_TYPEDEF(EaseInOutCirc);
    ANIMATION_TYPEDEF(EaseOutInCirc);
    ANIMATION_TYPEDEF(EaseInElastic);
    ANIMATION_TYPEDEF(EaseOutElastic);
    ANIMATION_TYPEDEF(EaseInOutElastic);
    ANIMATION_TYPEDEF(EaseOutInElastic);
    ANIMATION_TYPEDEF(EaseInBack);
    ANIMATION_TYPEDEF(EaseOutBack);
    ANIMATION_TYPEDEF(EaseInOutBack);
    ANIMATION_TYPEDEF(EaseOutInBack);
    ANIMATION_TYPEDEF(EaseInBounce);
    ANIMATION_TYPEDEF(EaseOutBounce);
    ANIMATION_TYPEDEF(EaseInOutBounce);
    ANIMATION_TYPEDEF(EaseOutInBounce);

    #undef ANIMATION_TYPEDEF
    #endif
}
