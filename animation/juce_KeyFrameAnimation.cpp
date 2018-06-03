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

KeyFrameAnimation::KeyFrameAnimation(var startValue, var endValue)
{
    jassert(!startValue.isVoid());
    jassert(!endValue.isVoid());

    setStartValue(startValue);
    currentValue = startValue;
    setEndValue(endValue);
}

void KeyFrameAnimation::setAnimationCurve(const AnimationCurve &newCurve)
{
    curve = newCurve;
}

AnimationCurve KeyFrameAnimation::getAnimationCurve()
{
    return curve;
}

void KeyFrameAnimation::setStartValue(var value)
{
    jassert(!value.isVoid());
    setKeyValue(0.0, value);
}

var KeyFrameAnimation::getStartValue() const
{
    return getKeyValue(0.0);
}

void KeyFrameAnimation::setEndValue(var value)
{
    jassert(!value.isVoid());
    setKeyValue(1.0, value);
}

var KeyFrameAnimation::getEndValue() const
{
    return getKeyValue(1.0);
}

var KeyFrameAnimation::getCurrentValue() const
{
    return currentValue;
}

void KeyFrameAnimation::setKeyValue(double progress, var value)
{
    // Keyframe must be in the valid range of 0.0 - 1.0
    jassert(progress >= 0.0 && progress <= 1.0);

    // No void values!
    jassert(!value.isVoid());

    keyframes.add(KeyFrame(progress, value));
}

var KeyFrameAnimation::getKeyValue(double progress) const
{
    // Keyframe must be in the valid range of 0.0 - 1.0
    jassert(progress >= 0.0 && progress <= 1.0);

    for (auto keyframe : keyframes)
        if (keyframe.getPosition() == progress)
            return keyframe.getValue();

    return var();
}

//==============================================================================

void KeyFrameAnimation::handleAnimationStarted()
{
    initKeyFrames();
    Animation::handleAnimationStarted();
}

void KeyFrameAnimation::handleAnimationLoopChanged()
{
    initKeyFrames();
    Animation::handleAnimationLoopChanged();
}

void KeyFrameAnimation::update(const double progress)
{
    const KeyFrame &nextKey = getNextKeyFrame(progress);

    if (currentKeyEnd.getValue() != nextKey.getValue())
    {
        currentKeyStart = currentKeyEnd;
        currentKeyEnd   = nextKey;
    }

    double keyProgress = jmap(
        progress,
        currentKeyStart.getPosition(),
        currentKeyEnd.getPosition(),
        0.0,
        1.0
    );
    keyProgress = juce::jlimit(0.0, 1.0, keyProgress);
    keyProgress = getAnimationCurve().perform(keyProgress);

    if (currentValue.isInt())
    {
        int v1 = (int)currentKeyStart.getValue();
        int v2 = (int)currentKeyEnd.getValue();
        currentValue = v1 + (v2 - v1) * keyProgress;
    }
    else if (currentValue.isInt64())
    {
        int64 v1 = (int64)currentKeyStart.getValue();
        int64 v2 = (int64)currentKeyEnd.getValue();
        currentValue = v1 + (v2 - v1) * keyProgress;
    }
    else if (currentValue.isDouble())
    {
        int v1 = (double)currentKeyStart.getValue();
        int v2 = (double)currentKeyEnd.getValue();
        currentValue = v1 + (v2 - v1) * keyProgress;
    }
    else
    {
        const double animationEnd = (isForward()) ? 1.0 : 0.0;

        if (progress == animationEnd)
            currentValue = getEndValue();
        else
            currentValue = getStartValue();
    }

    handleAnimationAdvanced();
}

void KeyFrameAnimation::initKeyFrames()
{
    if (isForward())
    {
        currentKeyStart = {0.0, getStartValue()};
        currentKeyEnd   = getNextKeyFrame(0.0);
    }
    else
    {
        currentKeyStart = {1.0, getEndValue()};
        currentKeyEnd   = getNextKeyFrame(1.0);
    }
}

KeyFrame KeyFrameAnimation::getNextKeyFrame(const double progress) const
{
    if (isForward())
    {
        for (auto keyframe : keyframes)
            if (keyframe.getPosition() > progress)
                return keyframe;

        return {1.0, getEndValue()};
    }
    else
    {
        for (int i = keyframes.size() - 1; i > 0; --i)
        {
            const auto keyframe = keyframes[i];
            if (keyframe.getPosition() < progress)
                return keyframe;
        }

        return {0.0, getStartValue()};
    }
}
