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

#pragma once

//==============================================================================
/**
    An abstract base class for timer based animations.
*/
class Animation : private Timer
{
    friend class AnimationGroup;

public:
    /** */
    enum Direction
    {
        Forward,
        Backward
    };

     /** Creates an empty animation */
    Animation();

    /** Destructor */
    virtual ~Animation() {};

    /** Starts the animation */
    void start();

    /** Pauses the animation if running */
    void pause();

    /** Resumes the animation if paused */
    void resume();

    /** Stops the animation */
    void stop();

    /** Returns whether the animation is running or not. If the animation has
        started but is currently paused, this method will return true.
    */
    bool isRunning() const;

    /** Returns whether the animation is currently paused */
    bool isPaused() const;

    /** Set the frame speed of the animation */
    void setSpeed(int ms);

    /** Set the frames per second of the animation.

        Note that this may not be exact due to integer rounding.
    */
    void setSpeedHz(int fps);

    /** Returns the current speed of the animation in milliseconds */
    int getSpeed() const;

    /** Returns the current speed of the animation in Hertz.

        Note that this may not be exact due to integer rounding.
    */
    int getSpeedHz() const;

    /** Sets the animation's direction
        @param newDirection            the new direction of the animation
    */
    void setDirection(Direction newDirection);

    /** Returns the animation's current direction */
    Direction getDirection() const;

    /** Returns true if the animation direction is forwards. */
    bool isForward() const;

    /** Returns true if the animation direction is backwards. */
    bool isBackward() const;

    /** The number of times the animation should loop before stopping
        @param loops        the number of times to loop (0 disables the animation, -1 enables endless looping)
    */
    void setNumLoops(int numloops);

    /** Returns the numbers of times the animation will loop */
    int getNumLoops() const;

    /** Returns the current loop number the animation is on */
    int getCurrentLoop() const;

    /** Returns whether the animation is infinite */
    bool isEndless() const;

    /** When enabled, the animation will switch directions after it completes
        a loop.
    */
    void setPingPongMode(bool shouldPingPong);

    /** Returns whether ping-pong has been enabled. */
    bool getPingPongMode() const;

    /** Sets the length of the animation in milliseconds*/
    void setDuration(int msDuration);

    /** Returns length of the animation in milliseconds */
    int getDuration() const;

    /** Returns the amount of time the animation has been running. */
    int getElapsedTime() const;

    /** Returns the amount of time the current loop has been running. */
    int getElapsedLoopTime() const;

    /**    A class for receiving callbacks from an Animation.

        To be told when an animation changes, you can register an
        Animation::Listener object using Animation::addListener().

        @see Animation::addListener, Animation::removeListener
    */
    struct Listener
    {
        virtual ~Listener() {}

        /** Called when an animation begins. */
        virtual void animationStarted(Animation*) {}

        /** Called when the animation is paused. */
        virtual void animationPaused(Animation*) {}

        /** Called when the animation is resumed from a pause. */
        virtual void animationResumed(Animation*) {}

        /** Called when an animation is stopped. */
        virtual void animationStopped(Animation*) {}

        /** Called when an animation advances. */
        virtual void animationAdvanced(Animation*) {}

        /** Called when an animation's state changes. */
        virtual void animationStateChanged(Animation*) {}

        /** Called when an animation loop completes. */
        virtual void animationLoopChanged(Animation* animation) {}

        /** Called when an animation's direction changes. */
        virtual void animationDirectionChanged(Animation* animation) {}
    };

    /** Adds an AnimationListener to the Animation */
    void addListener(Listener* newListener);

    /** Removes an AnimationListener from the Animation */
    void removeListener(Listener* newListener);

    /** You can assign a lambda to this callback object to have it called when
        the animation begins.
    */
    std::function<void()> animationStarted;

    /** You can assign a lambda to this callback object to have it called when
        the animation pauses.
    */
    std::function<void()> animationPaused;

    /** You can assign a lambda to this callback object to have it called when
        the animation resumes from a pause.
    */
    std::function<void()> animationResumed;

    /** You can assign a lambda to this callback object to have it called when
        the animation is stopped.
    */
    std::function<void()> animationStopped;

    /** You can assign a lambda to this callback object to have it called when
        the animation advances.
    */
    std::function<void()> animationAdvanced;

    /** You can assign a lambda to this callback object to have it called when
        the animation state changes.
    */
    std::function<void()> animationStateChanged;

    /** You can assign a lambda to this callback object to have it called when
        the animation begins a new loop.
    */
    std::function<void()> animationLoopChanged;

    /** You can assign a lambda to this callback object to have it called when
        the animation's direction changes.
    */
    std::function<void()> animationDirectionChanged;

protected:
    /** */
    enum State
    {
        Stopped,
        Paused,
        Running
    };

    /** Explicitly sets the animation state

        @param newState            the state to set the animation to
    */
    void setState(State newState);

    /** Returns the animation's current state */
    State getState() const;

    /** Called when the animation starts, notifying listeners and running the
        animationStarted() lambda if set.
    */
    virtual void handleAnimationStarted();

    /** Called when the animation pauses, notifying listeners and running the
        animationPaused() lambda if set.
    */
    virtual void handleAnimationPaused();

    /** Called when the animation resumes from a pause, notifying listeners and
        running the animationResumed() lambda if set.
    */
    virtual void handleAnimationResumed();

    /** Called when the animation stops, notifying listeners and running the
        animationEnded() lambda if set.
    */
    virtual void handleAnimationStopped();

    /** Called when the animation advances, notifying listeners and running the
        animationAdvanced() lambda if set.
    */
    virtual void handleAnimationAdvanced();

    /** Called when the animation state changes, notifying listeners and running
        the animationStateChanged() lambda if set.
    */
    virtual void handleAnimationStateChanged();

    /** Called when the animation loop changes, notifying listeners and running
        the animationLoopChanged() lambda if set.
    */
    virtual void handleAnimationLoopChanged();

    /** Called when the animation direction changes, notifying listeners and
        running the animationDirectionChanged() lambda if set.
    */
    virtual void handleAnimationDirectionChanged();

    /** Called when the animation advances. This should be overriden to provide
        custom behavior for the animation.
    */
    virtual void update(const double progress) = 0;

    /** Calculates the animation progress and current loop count. */
    void timerCallback() override;

private:
    int speed;
    int duration;
    int loops;
    int currentLoop;

    bool pingPong;

    Direction direction;
    State state;

    Time origin, time;

    ListenerList<Animation::Listener> listeners;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Animation)
};
