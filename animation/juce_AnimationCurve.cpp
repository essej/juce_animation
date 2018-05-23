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

#include "../utils/PennerEasing.h"

AnimationCurve::AnimationCurve()
{
    function  = Linear;
    weight    = In;
    amplitude = 1.0f;
    overshoot = 0.0f;
    clipValue = false;
}

float AnimationCurve::perform(float progress)
{
    jassert(progress >= 0.0f && progress <= 1.0f);

    float value;

    switch (function)
    {
        case Linear:
            value = easeNone(progress) * amplitude;
            break;

        case Quadratic:
            switch (weight)
            {
                case In:
                    value = easeInQuad(progress);
                    break;

                case Out:
                    value = easeOutQuad(progress);
                    break;

                case InOut:
                    value = easeInOutQuad(progress);
                    break;

                case OutIn:
                    value = easeOutInQuad(progress);
                    break;
            }

            break;

        case Cubic:
            switch (weight)
            {
                case In:
                    value = easeInCubic(progress);
                    break;

                case Out:
                    value = easeOutCubic(progress);
                    break;

                case InOut:
                    value = easeInOutCubic(progress);
                    break;

                case OutIn:
                    value = easeOutInCubic(progress);
                    break;
            }
            break;

        case Quartic:
            switch (weight)
            {
                case In:
                    value = easeInQuart(progress);
                    break;

                case Out:
                    value = easeOutQuart(progress);
                    break;

                case InOut:
                    value = easeInOutQuart(progress);
                    break;

                case OutIn:
                    value = easeOutInQuart(progress);
                    break;
            }
            break;

        case Quintic:
            switch (weight)
            {
                case In:
                    value = easeInQuint(progress);
                    break;

                case Out:
                    value = easeOutQuint(progress);
                    break;

                case InOut:
                    value = easeInOutQuint(progress);
                    break;

                case OutIn:
                    value = easeOutInQuint(progress);
                    break;
            }
            break;

        case Sinusoidal:
            switch (weight)
            {
                case In:
                    value = easeInSine(progress);
                    break;

                case Out:
                    value = easeOutSine(progress);
                    break;

                case InOut:
                    value = easeInOutSine(progress);
                    break;

                case OutIn:
                    value = easeOutInSine(progress);
                    break;
            }
            break;

        case Exponential:
            switch (weight)
            {
                case In:
                    value = easeInExpo(progress);
                    break;

                case Out:
                    value = easeOutExpo(progress);
                    break;

                case InOut:
                    value = easeInOutExpo(progress);
                    break;

                case OutIn:
                    value = easeOutInExpo(progress);
                    break;
            }
            break;

        case Circular:
            switch (weight)
            {
                case In:
                    value = easeInCirc(progress);
                    break;

                case Out:
                    value = easeOutCirc(progress);
                    break;

                case InOut:
                    value = easeInOutCirc(progress);
                    break;

                case OutIn:
                    value = easeOutInCirc(progress);
                    break;
            }
            break;

        case Elastic:
            switch (weight)
            {
                case In:
                    value = easeInElastic(progress, amplitude, 1.0f);
                    break;

                case Out:
                    value = easeOutElastic(progress, amplitude, 1.0f);
                    break;

                case InOut:
                    value = easeInOutElastic(progress, amplitude, 1.0f);
                    break;

                case OutIn:
                    value = easeOutInElastic(progress, amplitude, 1.0f);
                    break;
            }
            break;

        case Back:
            switch (weight)
            {
                case In:
                    value = easeInBack(progress, overshoot);
                    break;

                case Out:
                    value = easeOutBack(progress, overshoot);
                    break;

                case InOut:
                    value = easeInOutBack(progress, overshoot);
                    break;

                case OutIn:
                    value = easeOutInBack(progress, overshoot);
                    break;
            }
            break;

        case Bounce:
            switch (weight)
            {
                case In:
                    value = easeInBounce(progress, amplitude);
                    break;

                case Out:
                    value = easeOutBounce(progress, amplitude);
                    break;

                case InOut:
                    value = easeInOutBounce(progress, amplitude);
                    break;

                case OutIn:
                    value = easeOutInBounce(progress, amplitude);
                    break;
            }
            break;
    }

    if (clipValue)
        value = jmax(0.0f, jmin(1.0f, value));

    return value;
}
