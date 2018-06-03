Animation::Animation()
{
    speed       = 16;
    duration    = 0;
    loops       = 1;
    currentLoop = 0;
    direction   = Forward;
    state       = Stopped;
}

void Animation::start()
{
    if (!isTimerRunning())
    {
        time = Time::getCurrentTime();
        startTimer(speed);
    }

    setState(Running);
    handleAnimationStarted();
}

void Animation::pause()
{
    stopTimer();
    setState(Paused);
}

void Animation::resume()
{
    if (state == Paused)
    {
        time = Time::getCurrentTime();
        startTimer(speed);
    }
}

void Animation::stop()
{
    stopTimer();
    currentLoop = 0;
    setState(Stopped);
    handleAnimationEnded();
}

void Animation::setState(Animation::State newState)
{
    if (newState != state)
    {
        state = newState;
        handleAnimationStateChanged();
    }
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

void Animation::setSpeed(int ms)
{
    if (ms != speed)
    {
        speed = ms;

        if (isTimerRunning())
            startTimer(speed);
    }
}

void Animation::setSpeedHz(int fps)
{
    setSpeed(1000 / fps);
}

int Animation::getSpeed() const
{
    return speed;
}

int Animation::getSpeedHz() const
{
    return 1000 / speed;
}

void Animation::setDirection(Animation::Direction newDirection)
{
    if (newDirection != direction)
    {
        direction = newDirection;
        handleAnimationDirectionChanged();
    }
}

Animation::Direction Animation::getDirection() const
{
    return direction;
}

bool Animation::isForward() const
{
    return (direction == Forward);
}

bool Animation::isBackward() const
{
    return (direction == Backward);
}

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

void Animation::setPingPongMode(bool shouldPingPong)
{
    pingPong = shouldPingPong;
}

bool Animation::getPingPongMode() const
{
    return pingPong;
}

void Animation::setDuration(int msDuration)
{
    // Duration must be a positive integer above zero
    jassert(msDuration > 0);
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

void Animation::addListener(Animation::Listener* newListener)
{
    if (!listeners.contains(newListener))
        listeners.add(newListener);
}

void Animation::removeListener(Animation::Listener* newListener)
{
    if (listeners.contains(newListener))
        listeners.remove(newListener);
}

void Animation::handleAnimationStarted()
{
    listeners.call(&Animation::Listener::animationStarted, this);

    if (animationStarted)
        animationStarted();
}

void Animation::handleAnimationEnded()
{
    listeners.call(&Animation::Listener::animationEnded, this);

    if (animationEnded)
        animationEnded();
}

void Animation::handleAnimationAdvanced()
{
    listeners.call(&Animation::Listener::animationAdvanced, this);

    if (animationAdvanced)
        animationAdvanced();
}

void Animation::handleAnimationStateChanged()
{
    listeners.call(&Animation::Listener::animationStateChanged, this);

    if (animationStateChanged)
        animationStateChanged();
}

void Animation::handleAnimationLoopChanged()
{
    listeners.call(&Animation::Listener::animationLoopChanged, this);

    if (animationLoopChanged)
        animationLoopChanged();
}

void Animation::handleAnimationDirectionChanged()
{
    listeners.call(&Animation::Listener::animationDirectionChanged, this);

    if (animationDirectionChanged)
        animationDirectionChanged();
}

void Animation::timerCallback()
{
    const auto currentTime = Time::getCurrentTime();
    const auto diff = currentTime.toMilliseconds() - time.toMilliseconds();

    if (diff > (int64)duration)
    {
        if (currentLoop < loops - 1 || isEndless())
        {
            time = currentTime;

            if (pingPong)
                direction = (direction == Forward) ? Backward : Forward;

            currentLoop++;
            handleAnimationLoopChanged();

            if (direction == Forward)
                update(0.0);
            else
                update(1.0);
        }
        else
        {
            if (direction == Forward)
                update(1.0);
            else
                update(0.0);

            stop();
        }
    }
    else
    {
        const double progress = (double)diff / (double)duration;

        if (direction == Forward)
            update(progress);
        else
            update(1.0 - progress);
    }
}
