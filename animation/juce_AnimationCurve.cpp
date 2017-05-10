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

//==============================================================================

AnimationCurve::AnimationCurve()
{

    currentFunction  = Linear;
    currentWeight    = In;
    currentAmplitude = 1.0f;
    currentOvershoot = 0.0f;
    overshootStatus  = true;

}

AnimationCurve::~AnimationCurve()
{

}

//==============================================================================

void AnimationCurve::setFunction(AnimationCurve::Function newFunction)
{
    currentFunction = newFunction;
}

AnimationCurve::Function AnimationCurve::getFunction() const noexcept
{
    return currentFunction;
}

void AnimationCurve::setWeight(juce::AnimationCurve::Weight newWeight)
{
    currentWeight = newWeight;
}

AnimationCurve::Weight AnimationCurve::getWeight() const noexcept
{
    return currentWeight;
}

//==============================================================================

// ...

//==============================================================================

void AnimationCurve::setAmplitude(float newAmp)
{
    currentAmplitude = newAmp;
}

float AnimationCurve::getAmplitude() const noexcept
{
    return currentAmplitude;
}

void AnimationCurve::setOvershoot(float newOvershoot)
{
    currentOvershoot = newOvershoot;
}

float AnimationCurve::getOvershoot() const noexcept
{
    return currentOvershoot;
}

void AnimationCurve::setOvershootStatus(bool shouldClipOvershoot)
{
    overshootStatus = shouldClipOvershoot;
}

bool AnimationCurve::getOvershootStatus() const noexcept
{
    return overshootStatus;
}

//==============================================================================

float AnimationCurve::perform(float progress)
{
    jassert(progress >= 0.0f && progress <= 1.0f);

    float value;

    switch (currentFunction)
    {
        case Linear:

            value = easeNone(progress) * currentAmplitude; // Account for amplitude/overshot?

            break;

        case Quadratic:

            switch (currentWeight)
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

            switch (currentWeight)
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

            switch (currentWeight)
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

            switch (currentWeight)
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

            switch (currentWeight)
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

            switch (currentWeight)
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

            switch (currentWeight)
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

            switch (currentWeight)
            {
                case In:
                    value = easeInElastic(progress, currentAmplitude, 1.0f);
                    break;

                case Out:
                    value = easeOutElastic(progress, currentAmplitude, 1.0f);
                    break;

                case InOut:
                    value = easeInOutElastic(progress, currentAmplitude, 1.0f);
                    break;

                case OutIn:
                    value = easeOutInElastic(progress, currentAmplitude, 1.0f);
                    break;
            }

            break;

        case Back:

            switch (currentWeight)
            {
                case In:
                    value = easeInBack(progress, currentOvershoot);
                    break;

                case Out:
                    value = easeOutBack(progress, currentOvershoot);
                    break;

                case InOut:
                    value = easeInOutBack(progress, currentOvershoot);
                    break;

                case OutIn:
                    value = easeOutInBack(progress, currentOvershoot);
                    break;
            }

            break;

        case Bounce:

            switch (currentWeight)
            {
                case In:
                    value = easeInBounce(progress, currentAmplitude);
                    break;

                case Out:
                    value = easeOutBounce(progress, currentAmplitude);
                    break;

                case InOut:
                    value = easeInOutBounce(progress, currentAmplitude);
                    break;

                case OutIn:
                    value = easeOutInBounce(progress, currentAmplitude);
                    break;
            }

            break;

        case Custom:

            value = customCurve(progress, currentAmplitude, currentOvershoot, currentWeight);

            break;

    }

    if (!overshootStatus)
    {
        value = jmax(0.0f, jmin(1.0f, value));
    }

    return value;

}
