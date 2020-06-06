#pragma once

/** Contains classes for different types of animation behaviours - these classes
    are used as template parameters for the AnimatedPosition class.
*/
namespace AnimatedPositionBehaviours
{

/** A behaviour that allows the animation to have an easing curve applied to it
    rather than simply following a linear interpolation.

    This behaviour also provides timing functionality to control the duration,
    number of loops, and loop behaviour (i.e. the auto reversing ping-pong mode)
    of the animation.
*/
class Eased
{
    friend class AnimatedPosition<Eased>;

public:
    /** The number of times the animation should loop. If the loop count is zero
        the animation will play once and stop. If the loop count is less than
        zero the animation will loop indefinitely.
    */
    int loops = 0;

    /** The duration of the animation in seconds. If this is zero the
        animation will end immediately.
    */
    double duration = 0.0;

    /** Enables ping-pong mode if looping is also enabled. This will cause the
        next loop to start from the animation's last position and the direction
        of the animation to reverse.
    */
    bool pingpong = false;

    /** The easing function to use when calculating the next animation position.

        If no easing function is provided the value will be interpolated
        linearly based on the duration.
    */
    std::function<double(double)> easing;

protected:
    /** Called by AnimatedPosition<> to provide a velocity and starting position
        to the animation behaviour. This allows an animation to start midway,
        such as a bouncing effect that follows dragging a view and releasing.
    */
    void releasedWithVelocity(double pos, double vel) noexcept
    {
        time = 0.0;
        offset = pos;
        currentLoop = 0;
        pingpongStatus = false;
    }

    /** Called by AnimatedPosition<> to get the next position value. This method
        will convert the absolute milliseconds to a proportion of total elapsed
        time divded by duration. If duration is 0 this will return the provided
        position and the animation will subsequently end when isStopped() is
        called afterwards.
    */
    double getNextPosition(double pos, double t) noexcept
    {
        if (duration > 0.0)
        {
            time += t;

            const double proportion = (pingpongStatus)
                ? 1.0 - (time / duration)
                : time / duration;

            if (easing == nullptr)
                return proportion;

            if (offset == 1.0)
                return easing(1.0);

            return easing(proportion) / (1.0 / (1.0 - offset)) + offset;
        }
        else
        {
            return pos;
        }
    }
    
public:

    /** Called by AnimatedPosition<> to determine whether or not the animation
        should end. This method handles the duration, looping, and ping-pong
        logic.
    */
    bool isStopped(double pos) noexcept
    {
        if (time >= duration)
        {
            time   = 0.0;
            offset = 0.0;

            if (loops != 0)
            {
                if (pingpong)
                    pingpongStatus = !pingpongStatus;

                if (loops > 0)
                {
                    if (currentLoop >= loops)
                    {
                        currentLoop = 0;
                        return true;
                    }
                    else
                    {
                        currentLoop++;
                    }
                }
            }
            else
            {
                return true;
            }
        }

        return false;
    }

protected:
    double time   = 0.0;
    double offset = 0.0;
    int currentLoop = 0;
    bool pingpongStatus = false;
};

}
