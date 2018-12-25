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
    #include "animation/juce_AnimationPositionBehaviours.h"

    #if JUCE_ANIMATION_ENABLE_TYPEDEFS
    #define _ANIM_T(b, n) \
        typedef AnimatedPosition<AnimatedPositionBehaviours::b> n;

    /* Default JUCE animation behaviours */
    _ANIM_T(ContinuousWithMomentum, MomentumAnimation);
    _ANIM_T(SnapToPageBoundaries,   SnappingAnimation);

    /* Easing function behaviours */
    _ANIM_T(EaseLinear,       EaseLinearAnimation);
    _ANIM_T(EaseInQuad,       EaseInQuadAnimation);
    _ANIM_T(EaseOutQuad,      EaseOutQuadAnimation);
    _ANIM_T(EaseInOutQuad,    EaseInOutQuadAnimation);
    _ANIM_T(EaseOutInQuad,    EaseOutInQuadAnimation);
    _ANIM_T(EaseInCubic,      EaseInCubicAnimation);
    _ANIM_T(EaseOutCubic,     EaseOutCubicAnimation);
    _ANIM_T(EaseInOutCubic,   EaseInOutCubicAnimation);
    _ANIM_T(EaseOutInCubic,   EaseOutInCubicAnimation);
    _ANIM_T(EaseInQuart,      EaseInQuartAnimation);
    _ANIM_T(EaseOutQuart,     EaseOutQuartAnimation);
    _ANIM_T(EaseInOutQuart,   EaseInOutQuartAnimation);
    _ANIM_T(EaseOutInQuart,   EaseOutInQuartAnimation);
    _ANIM_T(EaseInQuint,      EaseInQuintAnimation);
    _ANIM_T(EaseOutQuint,     EaseOutQuintAnimation);
    _ANIM_T(EaseInOutQuint,   EaseInOutQuintAnimation);
    _ANIM_T(EaseOutInQuint,   EaseOutInQuintAnimation);
    _ANIM_T(EaseInSine,       EaseInSineAnimation);
    _ANIM_T(EaseOutSine,      EaseOutSineAnimation);
    _ANIM_T(EaseInOutSine,    EaseInOutSineAnimation);
    _ANIM_T(EaseOutInSine,    EaseOutInSineAnimation);
    _ANIM_T(EaseInExpo,       EaseInExpoAnimation);
    _ANIM_T(EaseOutExpo,      EaseOutExpoAnimation);
    _ANIM_T(EaseInOutExpo,    EaseInOutExpoAnimation);
    _ANIM_T(EaseOutInExpo,    EaseOutInExpoAnimation);
    _ANIM_T(EaseInCirc,       EaseInCircAnimation);
    _ANIM_T(EaseOutCirc,      EaseOutCircAnimation);
    _ANIM_T(EaseInOutCirc,    EaseInOutCircAnimation);
    _ANIM_T(EaseOutInCirc,    EaseOutInCircAnimation);
    _ANIM_T(EaseInElastic,    EaseInElasticAnimation);
    _ANIM_T(EaseOutElastic,   EaseOutElasticAnimation);
    _ANIM_T(EaseInOutElastic, EaseInOutElasticAnimation);
    _ANIM_T(EaseOutInElastic, EaseOutInElasticAnimation);
    _ANIM_T(EaseInBack,       EaseInBackAnimation);
    _ANIM_T(EaseOutBack,      EaseOutBackAnimation);
    _ANIM_T(EaseInOutBack,    EaseInOutBackAnimation);
    _ANIM_T(EaseOutInBack,    EaseOutInBackAnimation);
    _ANIM_T(EaseInBounce,     EaseInBounceAnimation);
    _ANIM_T(EaseOutBounce,    EaseOutBounceAnimation);
    _ANIM_T(EaseInOutBounce,  EaseInOutBounceAnimation);
    _ANIM_T(EaseOutInBounce,  EaseOutInBounceAnimation);

    #undef _ANIM_T
    #endif
}
