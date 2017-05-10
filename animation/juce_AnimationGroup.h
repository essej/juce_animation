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
class JUCE_API AnimationGroup
{
public:
    //==============================================================================
	/** */
	AnimationGroup();

	/** Destructor */
	~AnimationGroup();

	//==============================================================================
	/** */
	void addAnimation(Animation* animation);

	/** */
	void removeAnimation(Animation* animation);

	/** */
	Animation* removeAnimation(int index);

	/** */
	void insertAnimation(int index, Animation* animation);

	/** */
	Animation* getAnimation(int index);

	/** */
	int getIndexOfAnimation(Animation* animation);

	/** Removes all animations from the group */
	void clear();

    //==============================================================================

private:

    Array<Animation*> animations;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AnimationGroup)

};
