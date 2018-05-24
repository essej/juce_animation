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
	A class for maintaining groups of animations
*/
class AnimationGroup : public Animation
{
public:
    enum AnimationMode
    {
        Sequential,
        Parallel
    };

	/** Creates an empty animation group. */
	AnimationGroup();

    /** Sets the mode to run the animations in.

        When the mode is sequential the group will run all animations, one after
        the other, in the order they were added. The group animation will end
        after the final animation has ended. If an animation in the group is
        endless, the group will not progress past that animation until it is
        marked as finite.

        If the mode is parallel, every animation in the group will be advanced
        when the group advances. The group will stop after the longest animation
        has finished. If an animation is marked as endless, all finite
        animations will end and the group will keep running until the endless
        animation is marked as finite.
    */
    void setAnimationMode(AnimationMode);

    /** Returns the mode set by setAnimationMode(). */
    AnimationMode getAnimationMode() const;

	/** Adds an animation to the group. */
	void addAnimation(Animation*);

	/** Removes a given animation. */
	void removeAnimation(Animation*);

	/** Removes an animation at a given index. */
	void removeAnimation(int);

	/** Inserts an animation at a given index.

        This will remove the animation from its current index, if it has been
        previously added.
    */
	void insertAnimation(int, Animation*);

    /** Swaps the indices of two animations. */
    void swapAnimations(Animation*, Animation*);

    /** Swaps two animations by their index. */
    void swapAnimations(int, int);

    /** Moves an animation to a new index. */
    void moveAnimation(Animation*, int);

	/** Returns the animation at a given index. */
	Animation* getAnimation(int);

	/** Returns the index of a given animation, or -1 if not found. */
	int getIndexOfAnimation(Animation*);

	/** Removes all animations from the group. */
	void clear();

    /** Adds a listener to all animations.

        Subsequent animations added to this group will also have this listener
        attached.
    */
    void addListener(Animation::Listener*);

    /** Removes a listener from all animations. */
    void removeListener(Animation::Listener*);

private:
    void update(const double progress) override;

    Array<Animation*> animations;
    Array<Animation::Listener*> listeners;

    AnimationMode animationMode;
    int currentAnimation;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AnimationGroup)
};
