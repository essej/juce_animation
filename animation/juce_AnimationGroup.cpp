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

AnimationGroup::AnimationGroup()
{

}

AnimationGroup::~AnimationGroup()
{

}

//==============================================================================

void AnimationGroup::addAnimation(Animation* animation)
{

}

void AnimationGroup::removeAnimation(Animation* animation)
{

}

Animation* AnimationGroup::removeAnimation(int index)
{
    Animation* animation = animations.removeAndReturn(index);
    return animation;
}

void AnimationGroup::insertAnimation(int index, Animation* animation)
{



}

Animation* AnimationGroup::getAnimation(int index)
{
    return animations[index];
}

int AnimationGroup::getIndexOfAnimation(Animation* animation)
{
    return animations.indexOf(animation);
}

void AnimationGroup::clear()
{

}

//==============================================================================
