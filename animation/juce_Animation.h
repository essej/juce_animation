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
class JUCE_API Animation : private Timer
{
public:
	//==============================================================================
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

	//==============================================================================
    /** Creates a basic value animation */
    Animation(var value);

	/** Destructor */
	virtual ~Animation();

    //==============================================================================
    /** Starts the animation */
    void start();

    /** Pauses the animation if running */
    void pause();

    /** Resumes the animation if paused */
    void resume();

    /** Stops the animation */
    void stop();

    /** */
    virtual void update(double progress);

	//==============================================================================
	/** Explicitly sets the animation state
		@param newState			the state to set the animation to
	*/
	void setState(State newState);

	/** Returns the animation's current state */
	State getState() const;

	/** Returns whether the animation is running or not (returns true if paused) */
	bool isRunning() const;

	/** Returns whether the animation is currently paused */
	bool isPaused() const;

    //==============================================================================
    /** Set the frame speed of the animation */
    void setSpeed(int ms);

    /** Set the frames per second of the animation */
    void setSpeedHz(int fps);

    /** Returns the current frames per second speed of the animation */
    int getSpeed();

	//==============================================================================
	/** Sets the animation's direction
		@param newDirection			the new direction of the animation
	*/
	void setDirection(Direction newDirection);

	/** Returns the animation's current direction */
    Direction getDirection() const;

    //==============================================================================
    /** Sets the animation curve of the animation */
    void setAnimationCurve(AnimationCurve newCurve);

    /** Returns a reference to the current AnimationCurve */
    AnimationCurve& getAnimationCurve();

	//==============================================================================
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

	/** Returns the current duration of the current loop */
    int getDuration() const;

    /** Returns whether the animation is infinite */
    bool isEndless() const;

    //==============================================================================
    /** */
    void setStartValue(var value);

    /** */
    var getStartValue() const;

    /** */
    void setEndValue(var value);

    /** */
    var getEndValue() const;

    /** */
    var getCurrentValue() const;

    /** Sets the value of a property at a specified keyframe */
    void setKeyValue(double progress, var value);

        // This should be adding to some queue that keeps track of what the targets are for the current animation time

    /** */
//    void setKeyValueMs(Identifier Id, double msProgress, Value value);

    /** Returns the value of a property at a specified keyframe */
    var getKeyValue(double progress) const;

	//==============================================================================
	/**	A class for receiving callbacks from an Animation.

		To be told when an animation changes, you can register an Animation::Listener
		object using Animation::addListener().

		@see Animation::addListener, Animation::removeListener
	*/
	class JUCE_API Listener
	{
	public:
		//==============================================================================
		virtual ~Listener() {}

		//==============================================================================
		/** */
        virtual void animationEnded(Animation*) {}

		/** */
		virtual void animationStarted(Animation*) {}

        /** */
        virtual void animationAdvanced(Animation*) = 0;

		//==============================================================================
		/** */
		virtual void animationStateChanged(Animation*) {}

		//==============================================================================
		/** Called when an animation loop completes */
		virtual void animationLoopChanged(Animation* animation) {}

		//==============================================================================
		/** */
		virtual void animationDirectionChanged(Animation* animation) {}

	};

	/** Adds an AnimationListener to the Animation */
	void addListener(Listener* newListener);

	/** Removes an AnimationListener from the Animation */
	void removeListener(Listener* newListener);

protected:
    //==============================================================================
    /** */
    void setAnimationGroup(AnimationGroup& group);

    /** */
    void removeAnimationGroup(AnimationGroup& group);

    Identifier targetID;

private:
	//==============================================================================

    void animationEnded();
    void animationStarted();
    void animationAdvanced();
    void animationStateChanged();
    void animationLoopChanged();
    void animationDirectionChanged();

    var getNextKeyValue(double progress);

    //==============================================================================

    void timerCallback() override;

    //==============================================================================

    int speed;

    int duration;

    int loops;

    Direction direction;

    State state;

    Time time;

    var currentValue;
    var startValue;
    var endValue;

    ListenerList<Animation::Listener> listeners;

    HashMap<int, var> keyValues;

    AnimationCurve curve;

    AnimationGroup* parent;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Animation)

};
