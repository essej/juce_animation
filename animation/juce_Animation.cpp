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

Animation::Animation()
{
    speed       = 16;
    duration    = 0;
    loops       = 1;
    currentLoop = 0;
    direction   = Forward;
    state       = Stopped;
}

Animation::Animation(
    var startValue, var endValue,
    int length, int numLoops,
    Direction dir)
{
    jassert(!startValue.isVoid());
    jassert(!endValue.isVoid());

    setStartValue(startValue);
    currentValue = startValue;
    setEndValue(endValue);

    speed       = 16;
    duration    = length;
    loops       = numLoops;
    currentLoop = 0;
    direction   = dir;
    state       = Stopped;
}

void Animation::start()
{
    if (direction == Forward)
    {
        animationStartKey = {0.0, getStartValue()};
        animationEndKey   = getNextKeyFrame(0.0);
    }
    else
    {
        animationStartKey = {1.0, getEndValue()};
        animationEndKey   = getNextKeyFrame(1.0);
    }

    if (!isTimerRunning())
    {
        time = Time::getCurrentTime();
        startTimer(speed);
    }

    setState(Running);
    handleAnimationStarted();
}

void Animation::pause()
{
    stopTimer();
    setState(Paused);
}

void Animation::resume()
{
    if (getState() == Paused)
    {
        time = Time::getCurrentTime();
        startTimer(speed);
    }
}

void Animation::stop()
{
    stopTimer();
    currentLoop = 0;
    setState(Stopped);

    handleAnimationEnded();
}

void Animation::setState(Animation::State newState)
{
    if (newState != state)
    {
        state = newState;
        handleAnimationStateChanged();
    }
}

Animation::State Animation::getState() const
{
    return state;
}

bool Animation::isRunning() const
{
    return (state == Running || state == Paused);
}

bool Animation::isPaused() const
{
    return (state == Paused);
}

void Animation::setSpeed(int ms)
{
    speed = ms;
}

void Animation::setSpeedHz(int fps)
{
    speed = 1000 / fps;
    startTimer(speed);
}

int Animation::getSpeed() const
{
    return speed;
}

int Animation::getSpeedHz() const
{
    return speed / 1000;
}

void Animation::setDirection(Animation::Direction newDirection)
{
    if (newDirection != direction)
    {
        direction = newDirection;
        handleAnimationDirectionChanged();
    }
}

Animation::Direction Animation::getDirection() const
{
    return direction;
}

void Animation::setAnimationCurve(const AnimationCurve &newCurve)
{
    curve = newCurve;
}

AnimationCurve& Animation::getAnimationCurve()
{
    return curve;
}

void Animation::setNumLoops(int numloops)
{
    loops = numloops;
}

int Animation::getNumLoops() const
{
    return loops;
}

int Animation::getCurrentLoop() const
{
    return currentLoop;
}

void Animation::setDuration(int msDuration)
{
    // Duration must be a positive integer above zero
    jassert(msDuration > 0);
    duration = msDuration;
}

int Animation::getDuration() const
{
    return duration;
}

bool Animation::isEndless() const
{
    return (loops == -1);
}

void Animation::setStartValue(var value)
{
    jassert(!value.isVoid());
    setKeyValue(0.0, value);
}

var Animation::getStartValue() const
{
    return getKeyValue(0.0);
}

void Animation::setEndValue(var value)
{
    jassert(!value.isVoid());
    setKeyValue(1.0, value);
}

var Animation::getEndValue() const
{
    return getKeyValue(1.0);
}

var Animation::getCurrentValue() const
{
    return currentValue;
}

void Animation::setKeyValue(double progress, var value)
{
    // Keyframe must be in the valid range of 0.0 - 1.0
    jassert(progress >= 0.0 && progress <= 1.0);

    // No void values!
    jassert(!value.isVoid());

    if (progress == 0.0)
        currentKeyStart = KeyFrame(0.0, value);
    else if (progress == 1.0)
        currentKeyEnd = KeyFrame(1.0, value);

    keyframes.add(KeyFrame(progress, value));
}

var Animation::getKeyValue(double progress) const
{
    // Keyframe must be in the valid range of 0.0 - 1.0
    jassert(progress >= 0.0 && progress <= 1.0);

    for (auto keyframe : keyframes)
        if (keyframe.getPosition() == progress)
            return keyframe.getValue();

    return var();
}

void Animation::addListener(Animation::Listener* newListener)
{
    if (!listeners.contains(newListener))
        listeners.add(newListener);
}

void Animation::removeListener(Animation::Listener* newListener)
{
    if (listeners.contains(newListener))
        listeners.remove(newListener);
}

//==============================================================================

void Animation::update(const double progress)
{
    const KeyFrame &nextKey = getNextKeyFrame(progress);

    if (animationEndKey.getValue() != nextKey.getValue())
    {
        animationStartKey = animationEndKey;
        animationEndKey   = nextKey;
    }

    double keyProgress = jmap(
        progress,
        animationStartKey.getPosition(),
        animationEndKey.getPosition(),
        0.0,
        1.0
    );
    keyProgress = juce::jlimit(0.0, 1.0, keyProgress);
    keyProgress = curve.perform(keyProgress);

    if (currentValue.isInt())
    {
        int v1 = (int)animationStartKey.getValue();
        int v2 = (int)animationEndKey.getValue();
        currentValue = v1 + (v2 - v1) * keyProgress;
    }
    else if (currentValue.isInt64())
    {
        int64 v1 = (int64)animationStartKey.getValue();
        int64 v2 = (int64)animationEndKey.getValue();
        currentValue = v1 + (v2 - v1) * keyProgress;
    }
    else if (currentValue.isDouble())
    {
        int v1 = (double)animationStartKey.getValue();
        int v2 = (double)animationEndKey.getValue();
        currentValue = v1 + (v2 - v1) * keyProgress;
    }
    else
    {
        if (progress == 1.0)
            currentValue = animationEndKey.getValue();
        else
            currentValue = animationStartKey.getValue();
    }

    handleAnimationAdvanced();
}

//==============================================================================

void Animation::handleAnimationStarted()
{
    listeners.call(&Animation::Listener::animationStarted, this);

    if (animationStarted)
        animationStarted();
}

void Animation::handleAnimationEnded()
{
    listeners.call(&Animation::Listener::animationEnded, this);

    if (animationEnded)
        animationEnded();
}

void Animation::handleAnimationAdvanced()
{
    listeners.call(&Animation::Listener::animationAdvanced, this);

    if (animationAdvanced)
        animationAdvanced();
}

void Animation::handleAnimationStateChanged()
{
    listeners.call(&Animation::Listener::animationStateChanged, this);

    if (animationStateChanged)
        animationStateChanged();
}

void Animation::handleAnimationLoopChanged()
{
    listeners.call(&Animation::Listener::animationLoopChanged, this);

    if (animationLoopChanged)
        animationLoopChanged();
}

void Animation::handleAnimationDirectionChanged()
{
    listeners.call(&Animation::Listener::animationDirectionChanged, this);

    if (animationDirectionChanged)
        animationDirectionChanged();
}

KeyFrame Animation::getNextKeyFrame(const double progress) const
{
    if (direction == Forward)
    {
        for (auto keyframe : keyframes)
            if (keyframe.getPosition() > progress)
                return keyframe;
    }
    else
    {
        for (int i = keyframes.size() - 1; i > 0; --i)
        {
            const auto keyframe = keyframes[i];
            if (keyframe.getPosition() < progress)
                return keyframe;
        }
    }

    return currentKeyEnd;
}

void Animation::timerCallback()
{
    const auto currentTime = Time::getCurrentTime();
    const auto diff = currentTime.toMilliseconds() - time.toMilliseconds();

    if (diff > (int64)duration)
    {
        if (currentLoop < loops - 1 || isEndless())
        {
            time = currentTime;

            if (direction == Forward)
            {
                animationStartKey = {0.0, getStartValue()};
                animationEndKey   = getNextKeyFrame(0.0);

                update(0.0);
            }
            else
            {
                animationStartKey = {1.0, getEndValue()};
                animationEndKey   = getNextKeyFrame(1.0);

                update(1.0);
            }

            currentLoop++;
        }
        else
        {
            if (direction == Forward)
                update(1.0);
            else
                update(0.0);

            stop();
        }
    }
    else
    {
        const double progress = (double)diff / (double)duration;

        if (direction == Forward)
            update(progress);
        else
            update(1.0 - progress);
    }
}
