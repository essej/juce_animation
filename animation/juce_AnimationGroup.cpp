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

AnimationGroup::AnimationGroup() : Animation(juce::var(0.0f))
{
    setStartValue(0.0f);
    currentValue = 0.0f;
    setEndValue(1.0f);

    animationMode = Sequential;
}

AnimationGroup::~AnimationGroup()
{

}

void AnimationGroup::setAnimationMode(AnimationGroup::AnimationMode newMode)
{
    animationMode = newMode;
}

AnimationGroup::AnimationMode AnimationGroup::getAnimationMode() const
{
    return animationMode;
}

void AnimationGroup::addAnimation(Animation* animation)
{
    animations.add(animation);

    for (auto listener : listeners)
        animation->addListener(listener);

    if (animation->getDuration() > duration)
        duration = animation->getDuration();
}

void AnimationGroup::removeAnimation(Animation* animation)
{
    animations.remove(&animation);
}

void AnimationGroup::removeAnimation(int index)
{
    animations.remove(index);
}

void AnimationGroup::insertAnimation(int index, Animation* animation)
{
    if (animations.contains(animation))
        animations.remove(&animation);

    for (auto listener : listeners)
        animation->addListener(listener);

    animations.insert(index, animation);

    if (animation->getDuration() > duration)
        duration = animation->getDuration();
}

void AnimationGroup::swapAnimations(
    Animation *firstAnimation,
    Animation *secondAnimation)
{
    if (firstAnimation == secondAnimation)
        return;

    jassert(animations.contains(firstAnimation));
    jassert(animations.contains(secondAnimation));

    const int indexOne = animations.indexOf(firstAnimation);
    const int indexTwo = animations.indexOf(secondAnimation);

    animations.swap(indexOne, indexTwo);
}

void AnimationGroup::swapAnimations(int indexOne, int indexTwo)
{
    animations.swap(indexOne, indexTwo);
}

void AnimationGroup::moveAnimation(Animation *animation, int newIndex)
{
    jassert(animations.contains(animation));

    const int index = animations.indexOf(animation);
    animations.move(index, newIndex);
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
    stop();
    animations.clear();
}

void AnimationGroup::addListener(Animation::Listener *listener)
{
    for (auto animation : animations)
        animation->addListener(listener);

    listeners.addIfNotAlreadyThere(listener);
}

void AnimationGroup::removeListener(Animation::Listener *listener)
{
    for (auto animation : animations)
        animation->removeListener(listener);

    listeners.remove(&listener);
}

void AnimationGroup::update(double progress)
{
    // TODO: Implement animation mode
    for (auto animation : animations)
        animation->update(progress);
}
