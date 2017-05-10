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

struct AnimationProperties
{

    //==============================================================================
    /* Bounds Properties */

    /** The width of the animation target */
    static const Identifier width;

    /** The height of the animation target */
    static const Identifier height;

    /** Both the width and height of the animation target */
    static const Identifier scale;

    /** The X position of an animation target */
    static const Identifier x;

    /** The Y position of an animation target */
    static const Identifier y;

    /** Both the X and Y of an animation target */
    static const Identifier position;

    /** The rotation of an animation target */
    static const Identifier rotation;

    //==============================================================================
    /* Lines (1-2), Paths(1-3) */

    /** The first X value of a target such as a Line or Path */
    static const Identifier x1;

    /** The first Y value of a target such as a Line or Path */
    static const Identifier y1;

    /** The second X value of a target such as a Line or Path */
    static const Identifier x2;

    /** The second X value of a target such as a Line or Path */
    static const Identifier y2;

    /** The third X value of a Path */
    static const Identifier x3;

    /** The third Y value of a Path */
    static const Identifier y3;

    //==============================================================================
    /* Colour Properties */

    /** The argb (uint32) of an animation target colour */
    static const Identifier colour;

    /** The hue of an animation target colour */
    static const Identifier hue;

    /** The saturation of an animation target colour */
    static const Identifier saturation;

    /** The brightness of an animation target colour */
    static const Identifier brightness;

    /** The alpha of an animation target colour */
    static const Identifier alpha;

    /** The red of an animation target colour */
    static const Identifier red;

    /** The green of an animation target colour */
    static const Identifier green;

    /** The blue of an animation target colour */
    static const Identifier blue;

};
