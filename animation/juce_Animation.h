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
	A base class for animations
*/
class Animation : private Timer
{
    friend class AnimationGroup;

public:
	/** */
	enum State
	{
		Stopped,
		Paused,
		Running
	};

	/** */
	enum Direction
	{
		Forward,
		Backward
	};

    /** Creates a basic value animation */
    Animation(var value);

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

	/** Explicitly sets the animation state

		@param newState			the state to set the animation to
	*/
	void setState(State newState);

	/** Returns the animation's current state */
	State getState() const;

	/** Returns whether the animation is running or not. If the animation has
        started but is currently paused, this method will return true.
    */
	bool isRunning() const;

	/** Returns whether the animation is currently paused */
	bool isPaused() const;

    /** Set the frame speed of the animation */
    void setSpeed(int ms);

    /** Set the frames per second of the animation */
    void setSpeedHz(int fps);

    /** Returns the current speed of the animation in milliseconds */
    int getSpeed() const;

    /** Returns the current speed of the animation in Hertz. */
    int getSpeedHz() const;

	/** Sets the animation's direction
		@param newDirection			the new direction of the animation
	*/
	void setDirection(Direction newDirection);

	/** Returns the animation's current direction */
    Direction getDirection() const;

    /** Sets the animation curve of the animation */
    void setAnimationCurve(const AnimationCurve& newCurve);

    /** Returns a reference to the current AnimationCurve */
    AnimationCurve& getAnimationCurve();

	/** The number of times the animation should loop before stopping
		@param loops		the number of times to loop (0 disables the animation, -1 enables endless looping)
	*/
	void setNumLoops(int numloops);

	/** Returns the numbers of times the animation will loop */
	int getNumLoops() const;

	/** Returns the current loop number the animation is on */
	int getCurrentLoop() const;

	/** Sets the length of the animation in milliseconds*/
	void setDuration(int msDuration);

	/** Returns length of the animation in milliseconds */
    int getDuration() const;

    /** Returns whether the animation is infinite */
    bool isEndless() const;

    /** Sets the starting value of the animation. */
    void setStartValue(var value);

    /** Returns the value set by setStartValue(). */
    var getStartValue() const;

    /** Sets the end value of the animation. */
    void setEndValue(var value);

    /** Returns the value set by setEndValue() */
    var getEndValue() const;

    /** Returns the current value the animation is at. */
    var getCurrentValue() const;

    /** Sets the value of a property at a specified keyframe */
    void setKeyValue(double progress, var value);

    // This should be adding to some queue that keeps track of what the targets are for the current animation time

    /** */
//    void setKeyValueMs(Identifier Id, double msProgress, Value value);

    /** Returns the value of a property at a specified keyframe */
    var getKeyValue(double progress) const;

	/**	A class for receiving callbacks from an Animation.

		To be told when an animation changes, you can register an
        Animation::Listener object using Animation::addListener().

		@see Animation::addListener, Animation::removeListener
	*/
	struct Listener
	{
		virtual ~Listener() {}

		/** Called when an animation begins. */
		virtual void animationStarted(Animation*) {}

        /** Called when an animation ends. */
        virtual void animationEnded(Animation*) {}

        /** Called when an animation advances. */
        virtual void animationAdvanced(Animation*) = 0;

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
        the animation ends.
    */
    std::function<void()> animationEnded;

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
    /** Called when the animation advances. This can be overriden to provide
        custom behavior for the animation.
    */
    virtual void update(double progress);

private:
    void handleAnimationStarted();
    void handleAnimationEnded();
    void handleAnimationAdvanced();
    void handleAnimationStateChanged();
    void handleAnimationLoopChanged();
    void handleAnimationDirectionChanged();

    var getNextKeyValue(double progress);

    void timerCallback() override;

    //==========================================================================

    int speed;
    int duration;
    int loops;
    int currentLoop;

    Direction direction;
    State state;
    Time time;

    var currentValue;
    var startValue;
    var endValue;

    var keyStart;
    var keyEnd;

    ListenerList<Animation::Listener> listeners;

    HashMap<int, var> keyValues;

    AnimationCurve curve;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Animation)
};
