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
    animationMode = Sequential;
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

void AnimationGroup::handleAnimationStarted()
{
    if (animationMode == Sequential)
    {
        if (isForward())
            currentIndex = 0;
        else
            currentIndex = animations.size() - 1;

        auto animation = animations[currentIndex];

        setDuration(animation->getDuration());
        setNumLoops(animation->getNumLoops());
        animation->setState(Running);
    }
    else
    {
        for (auto animation : animations)
            animation->setState(Running);
    }

    Animation::handleAnimationStarted();
}

void AnimationGroup::handleAnimationAdvanced()
{
    if (animationMode == Sequential)
    {
        auto animation = animations[currentIndex];

        if (getElapsedLoopTime() > animation->getDuration())
            changeAnimation();
    }
}

void AnimationGroup::handleAnimationLoopChanged()
{
    if (animationMode == Sequential)
    {
        auto animation = animations[currentIndex];

        if (getCurrentLoop() >= animation->getNumLoops())
            changeAnimation();
    }
    else
    {
        
    }
}

void AnimationGroup::handleAnimationStopped()
{
    if (animationMode == Sequential)
    {
        // Restart the group to move to the next animation
        if (changeAnimation())
            start();
    }
    else
    {
        // TODO: Don't send for animations that already ended
        for (auto animation : animations)
            animation->setState(Stopped);
    }

    Animation::handleAnimationStopped();
}

bool AnimationGroup::changeAnimation()
{
    jassert(animationMode == Sequential);

    auto animation = animations[currentIndex];

    if (isForward())
    {
        if (currentIndex < animations.size() - 1)
        {
            animation->setState(Stopped);

            currentIndex++;
            animation = animations[currentIndex];
            setDuration(animation->getDuration());
            setNumLoops(animation->getNumLoops());
            animation->setState(Running);
        }
        else
        {
            stop();
            return false;
        }
    }
    else
    {
        if (currentIndex > 0)
        {
            animation->setState(Stopped);

            currentIndex--;
            animation = animations[currentIndex];
            setDuration(animation->getDuration());
            setNumLoops(animation->getNumLoops());
            animation->setState(Running);
        }
        else
        {
            stop();
            return false;
        }
    }

    return true;
}

void AnimationGroup::update(const double progress)
{
    if (animationMode == Sequential)
    {
        auto animation = animations[currentIndex];

        if (animation->isForward())
            animation->update(progress);
        else
            animation->update(1.0 - progress);
    }
    else
    {
        for (auto animation : animations)
        {
            if (animation->isForward())
                animation->update(progress);
            else
                animation->update(1.0 - progress);
        }
    }

    handleAnimationAdvanced();
}
