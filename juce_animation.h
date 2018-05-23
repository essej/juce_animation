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

namespace juce
{
    class Animation;
    class AnimationGroup;
    class AnimationCurve;

    #include "animation/juce_AnimationCurve.h"
    #include "animation/juce_Animation.h"
    #include "animation/juce_AnimationGroup.h"
}
