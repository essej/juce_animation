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
    keyStart = getStartValue();
    keyEnd   = getNextKeyValue(0.0);

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

        // directional stuff

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

void Animation::update(double progress)
{
    const var nextKey = getNextKeyValue(progress);

    if (keyEnd != nextKey)
    {
        keyStart = keyEnd;
        keyEnd   = nextKey;
    }

    progress = curve.perform(progress);

    if (currentValue.isInt())
    {
        int v1 = (int)keyStart;
        int v2 = (int)keyEnd;

        var result = v1 + (v2 - v1) * progress;

        currentValue = result;
    }
    else if (currentValue.isInt64())
    {
        int64 v1 = (int64)keyStart;
        int64 v2 = (int64)keyEnd;

        var result = v1 + (v2 - v1) * progress;

        currentValue = result;
    }
    else if (currentValue.isDouble())
    {
        int v1 = (double)keyStart;
        int v2 = (double)keyEnd;

        var result = v1 + (v2 - v1) * progress;

        currentValue = result;
    }
    else
    {
        if (progress == 1.0)
            currentValue = keyEnd;
        else
            currentValue = keyStart;
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

//==============================================================================

var Animation::getNextKeyValue(double progress)
{
    for (auto keyframe : keyframes)
        if (keyframe.getPosition() > progress)
            return keyframe.getValue();

    return endValue;
}

//==============================================================================

void Animation::timerCallback()
{
    auto diff = Time::getCurrentTime().toMilliseconds() - time.toMilliseconds();

    if (diff > (int64)duration)
    {
        if (currentLoop < loops - 1 || isEndless())
        {
            time = Time::getCurrentTime();

            keyStart = getStartValue();
            keyEnd   = getNextKeyValue(0.0);

            update(0.0);

            currentLoop++;
        }
        else
        {
            update(1.0);
            stop();
        }
    }
    else
    {
        double progress = (double)diff / (double)duration;
        update(progress);
    }
}
