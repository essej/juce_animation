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

Animation::Animation(var value)
{

    setStartValue(value);

    currentValue = value;

    setEndValue(value);

    speed       = 60;
    duration    = 0;
    loops       = 0;
    currentLoop = 0;
    direction   = Forward;
    state       = Stopped;
    curve       = AnimationCurve();

}

Animation::~Animation()
{
    
}

//==============================================================================

void Animation::start()
{

    keyStart = getStartValue();
    keyEnd   = getNextKeyValue(0.0);

    if (!isTimerRunning())
    {

        time = Time::getCurrentTime();

        startTimerHz(speed);

    }

    setState(Running);

    animationStarted();

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

        startTimerHz(speed);

    }

}

void Animation::stop()
{

    stopTimer();

    setState(Stopped);

    currentLoop = 0;

    animationEnded();

}

void Animation::update(double progress)
{



    if (keyEnd != getNextKeyValue(progress))
    {

        keyStart = keyEnd;
        keyEnd = getNextKeyValue(progress);

    }

    progress = curve.perform(progress);

    if (currentValue.isInt())
    {

        int v1 = (int)keyStart;
        int v2 = (int)keyEnd;

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
        {

            currentValue = keyEnd;

        }
        else
        {

            currentValue = keyStart;

        }

    }

    animationAdvanced();

}

//==============================================================================

void Animation::setState(Animation::State newState)
{

    state = newState;

    animationStateChanged();

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

//==============================================================================

void Animation::setSpeed(int ms)
{

    speed = ms;

}

void Animation::setSpeedHz(int fps)
{

    speed = 1000 / fps;

}

int Animation::getSpeed()
{

    return speed;

}

//==============================================================================

void Animation::setDirection(Animation::Direction newDirection)
{

    direction = newDirection;

    // directional stuff

    animationDirectionChanged();

}

Animation::Direction Animation::getDirection() const
{

    return direction;

}

//==============================================================================

void Animation::setAnimationCurve(AnimationCurve newCurve)
{

    curve = newCurve;

}

AnimationCurve& Animation::getAnimationCurve()
{

    return curve;

}

//==============================================================================

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

    jassert(msDuration > 0);    /* Cannot have an animation with negative duration! */

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

//==============================================================================

void Animation::setStartValue(var value)
{

    setKeyValue(0.0, value);

}

var Animation::getStartValue() const
{

    return getKeyValue(0.0);

}

void Animation::setEndValue(var value)
{

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

    jassert(progress >= 0.0 && progress <= 1.0); /* Keyframe must be in the valid range of 0.0 - 1.0! */

    progress = floorf(progress * 100.0);

    keyValues.set((int)progress, value);

}

var Animation::getKeyValue(double progress) const
{

    jassert(progress >= 0.0 && progress <= 1.0); /* Keyframe must be in the valid range of 0.0 - 1.0! */

    progress = floorf(progress * 100.0);

    return keyValues[(int)progress];

}

//==============================================================================

void Animation::addListener(Animation::Listener* newListener)
{

    if (!listeners.contains(newListener))
    {

        listeners.add(newListener);

    }

}

void Animation::removeListener(Animation::Listener* newListener)
{

    if (listeners.contains(newListener))
    {

        listeners.remove(newListener);

    }

}

//==============================================================================

void Animation::setAnimationGroup(AnimationGroup& group)
{

    parent = &group;

}

void Animation::removeAnimationGroup(AnimationGroup& group)
{

    if (&group == parent)
    {

        parent = nullptr;

    }

}

//==============================================================================

void Animation::animationEnded()
{

    listeners.call(&Animation::Listener::animationEnded, this);

}

void Animation::animationStarted()
{

    listeners.call(&Animation::Listener::animationStarted, this);

}

void Animation::animationAdvanced()
{

    listeners.call(&Animation::Listener::animationAdvanced, this);

}

void Animation::animationStateChanged()
{

    listeners.call(&Animation::Listener::animationStateChanged, this);

}

void Animation::animationLoopChanged()
{

    listeners.call(&Animation::Listener::animationLoopChanged, this);

}

void Animation::animationDirectionChanged()
{

    listeners.call(&Animation::Listener::animationDirectionChanged, this);

}

//==============================================================================

var Animation::getNextKeyValue(double progress)
{

    for(HashMap<int, var>::Iterator i (keyValues); i.next();)
    {

        if (i.getKey() > (int)floorf(progress * 100))
        {
            return i.getValue();
        }

    }

    return endValue;

}

//==============================================================================

void Animation::timerCallback()
{

    int64 diff = Time::getCurrentTime().toMilliseconds() - time.toMilliseconds();

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
