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

    #define ANIMATION_TYPEDEF(b, n) \
    typedef AnimatedPosition<AnimatedPositionBehaviours::EasingAnimation<b>> n;

    /* Easing animation typedefs */
    ANIMATION_TYPEDEF(EaseLinear,       EaseLinearAnimation);
    ANIMATION_TYPEDEF(EaseInQuad,       EaseInQuadAnimation);
    ANIMATION_TYPEDEF(EaseOutQuad,      EaseOutQuadAnimation);
    ANIMATION_TYPEDEF(EaseInOutQuad,    EaseInOutQuadAnimation);
    ANIMATION_TYPEDEF(EaseOutInQuad,    EaseOutInQuadAnimation);
    ANIMATION_TYPEDEF(EaseInCubic,      EaseInCubicAnimation);
    ANIMATION_TYPEDEF(EaseOutCubic,     EaseOutCubicAnimation);
    ANIMATION_TYPEDEF(EaseInOutCubic,   EaseInOutCubicAnimation);
    ANIMATION_TYPEDEF(EaseOutInCubic,   EaseOutInCubicAnimation);
    ANIMATION_TYPEDEF(EaseInQuart,      EaseInQuartAnimation);
    ANIMATION_TYPEDEF(EaseOutQuart,     EaseOutQuartAnimation);
    ANIMATION_TYPEDEF(EaseInOutQuart,   EaseInOutQuartAnimation);
    ANIMATION_TYPEDEF(EaseOutInQuart,   EaseOutInQuartAnimation);
    ANIMATION_TYPEDEF(EaseInQuint,      EaseInQuintAnimation);
    ANIMATION_TYPEDEF(EaseOutQuint,     EaseOutQuintAnimation);
    ANIMATION_TYPEDEF(EaseInOutQuint,   EaseInOutQuintAnimation);
    ANIMATION_TYPEDEF(EaseOutInQuint,   EaseOutInQuintAnimation);
    ANIMATION_TYPEDEF(EaseInSine,       EaseInSineAnimation);
    ANIMATION_TYPEDEF(EaseOutSine,      EaseOutSineAnimation);
    ANIMATION_TYPEDEF(EaseInOutSine,    EaseInOutSineAnimation);
    ANIMATION_TYPEDEF(EaseOutInSine,    EaseOutInSineAnimation);
    ANIMATION_TYPEDEF(EaseInExpo,       EaseInExpoAnimation);
    ANIMATION_TYPEDEF(EaseOutExpo,      EaseOutExpoAnimation);
    ANIMATION_TYPEDEF(EaseInOutExpo,    EaseInOutExpoAnimation);
    ANIMATION_TYPEDEF(EaseOutInExpo,    EaseOutInExpoAnimation);
    ANIMATION_TYPEDEF(EaseInCirc,       EaseInCircAnimation);
    ANIMATION_TYPEDEF(EaseOutCirc,      EaseOutCircAnimation);
    ANIMATION_TYPEDEF(EaseInOutCirc,    EaseInOutCircAnimation);
    ANIMATION_TYPEDEF(EaseOutInCirc,    EaseOutInCircAnimation);
    ANIMATION_TYPEDEF(EaseInElastic,    EaseInElasticAnimation);
    ANIMATION_TYPEDEF(EaseOutElastic,   EaseOutElasticAnimation);
    ANIMATION_TYPEDEF(EaseInOutElastic, EaseInOutElasticAnimation);
    ANIMATION_TYPEDEF(EaseOutInElastic, EaseOutInElasticAnimation);
    ANIMATION_TYPEDEF(EaseInBack,       EaseInBackAnimation);
    ANIMATION_TYPEDEF(EaseOutBack,      EaseOutBackAnimation);
    ANIMATION_TYPEDEF(EaseInOutBack,    EaseInOutBackAnimation);
    ANIMATION_TYPEDEF(EaseOutInBack,    EaseOutInBackAnimation);
    ANIMATION_TYPEDEF(EaseInBounce,     EaseInBounceAnimation);
    ANIMATION_TYPEDEF(EaseOutBounce,    EaseOutBounceAnimation);
    ANIMATION_TYPEDEF(EaseInOutBounce,  EaseInOutBounceAnimation);
    ANIMATION_TYPEDEF(EaseOutInBounce,  EaseOutInBounceAnimation);

    #undef ANIMATION_TYPEDEF
    #endif
}
