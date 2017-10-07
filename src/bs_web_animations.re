type animation;

type animationInit;

type documentTimeline;

type documentTimelineInit;

/* NOTE placeholder type */
type element = string;

type keyframeEffect;

type keyframeEffectInit;

type keyframeObject;

type keyframeOptions;

/* type animationTimingEffect =
   | None
   | Forwards
   | Backwards
   | Both
   | Auto; */
type animationEffectTimingPlaybackDirection =
  | Normal
  | Reverse
  | Alternate
  | AlternateReverse;

let encodeAnimationEffectTimingPlaybackDirection dir =>
  switch dir {
  | Normal => "normal"
  | Reverse => "reverse"
  | Alternate => "alternate"
  | AlternateReverse => "alternate-reverse"
  };

type animationPlayState =
  | Pending
  | Running
  | Paused
  | Finished;

let encodeAnimationPlayState state =>
  switch state {
  | Pending => "pending"
  | Running => "running"
  | Paused => "paused"
  | Finished => "finished"
  };

/* TODO Extend this by adding in standard easings: */
type easingType =
  | Linear
  | Ease
  | EaseIn
  | EaseOut
  | EaseInOut
  | CubicBezier (float, float, float, float);

let encodeEasingType easing =>
  switch easing {
  | Linear => "linear"
  | Ease => "ease"
  | EaseIn => "ease-in"
  | EaseOut => "ease-out"
  | EaseInOut => "ease-in-out"
  | CubicBezier (f1, f2, f3, f4) =>
    "cubic-bezier(" ^
    string_of_float f1 ^
    ", " ^
    string_of_float f2 ^
    ", " ^ string_of_float f3 ^ ", " ^ string_of_float f4 ^ ")"
  };

type fillType =
  | Backwards
  | Forwards
  | Both
  | None;

let encodeFillType fill =>
  switch fill {
  | Backwards => "backwards"
  | Forwards => "forwards"
  | Both => "both"
  | None => "none"
  };

module KeyframeOptions = {
  type t = keyframeOptions;
  external make :
    delay::int? =>
    /* Whether the animation runs forwards (normal), backwards (reverse),
     * switches direction after each iteration (alternate), or runs
     * backwards and switches direction after each iteration (alternate-reverse).
     * Defaults to "normal". */
    direction::string? =>
    /* The number of milliseconds each iteration of the animation takes to
     * complete. Defaults to 0. Although this is technically optional, keep
     * in mind that your animation will not run if this value is 0. */
    duration::int? =>
    /* The rate of the animation's change over time. Accepts
     * the pre-defined values "linear", "ease", "ease-in", "ease-out",
     * and "ease-in-out", or a custom "cubic-bezier" value like
     * "cubic-bezier(0.42, 0, 0.58, 1)". Defaults to "linear". */
    easing::string? =>
    /* The number of milliseconds to delay after the end of an animation.
     * This is primarily of use when sequencing animations based on the
     * end time of another animation. Defaults to 0. */
    endDelay::int? =>
    /* Dictates whether the animation's effects should be reflected
     * by the element(s) prior to playing ("backwards"), retained
     * after the animation has completed playing ("forwards"), or
     * both. Defaults to "none".*/
    fill::string? =>
    /* Describes at what point in the iteration the animation should
     * start. 0.5 would indicate starting halfway through the first
     * iteration for example, and with this value set, an animation
     * with 2 iterations would end halfway through a third iteration.
     * Defaults to 0.0. */
    iterationStart::float? =>
    /* The number of times the animation should repeat. Defaults to 1,
     * and can also take a value of Infinity to make it repeat for
     * as long as the element exists. */
    iterations::int? =>
    unit =>
    keyframeOptions =
    "" [@@bs.obj];
  let make
       delay::(delay: int)=0
       direction::(direction: animationEffectTimingPlaybackDirection)=Normal
       duration::(duration: int)=0
       easing::(easing: easingType)=Linear
       endDelay::(endDelay: int)=0
       fill::(fill: fillType)=Forwards
       iterationStart::(iterationStart: float)=0.0
       iterations::(iterations: int)=1 =>
     make
       ::delay
       direction::(encodeAnimationEffectTimingPlaybackDirection direction)
       ::duration
       easing::(encodeEasingType easing)
       ::endDelay
       fill::(encodeFillType fill)
       ::iterationStart
       ::iterations;
};

module KeyframeEffectInit = {
  type t = keyframeEffectInit;
  external make :
    element::element? =>
    /* A keyframe object, or null. */
    keyframeSet::keyframeObject? =>
    /* Either an integer representing the animation's
     * duration (in milliseconds), or an Object. */
    keyframeOptions::keyframeOptions? =>
    /* sourceKeyFrames::keyframeEffectInit? => */
    unit =>
    keyframeEffectInit =
    "" [@@bs.obj];
  /* The DOM element to be animated, or null. */
};

/* The KeyframeEffect interface of the Web Animations API lets us
 * create sets of animatable properties and values, called keyframes.
 * These can then be played using the Animation() constructor.*/
module KeyframeEffect = {
  type t = keyframeEffect;
  external make : unit => t = "KeyframeEffect" [@@bs.new];
  external makeWithInit : keyframeEffectInit => t =
    "KeyframeEffect" [@@bs.new];
};


/**
 * The DocumentTimeline interface of the the Web Animations API represents animation
 * timelines, including the default document timeline (accessed via Document.timeline).
 * FIXME DocumentTimeline includes Document.timeline. Build this out.
 * FIXME DocumentTimeline inherits from AnimationTimeline; AnimationTimeline should
 * be defined and used as the base type. This is currently OK, as the only possible
 * timeline is DocumentTimeline, but for future-proofing, this needs to be integrated.
 */
module DocumentTimelineInit = {
  type t = documentTimelineInit;
  external make : originTime::int? => unit => documentTimelineInit =
    "" [@@bs.obj];
};

module DocumentTimeline = {
  type t = documentTimeline;
  type originTime = float;
  external make : unit => t = "DocumentTimeline" [@@bs.new];
  external makeWithInit : documentTimelineInit => t =
    "DocumentTimeline" [@@bs.new];
  /* Getters */
  external getOriginTime : t => originTime = "originTime" [@@bs.get];
  external getCurrentTime : t => float = "currentTime" [@@bs.get];
  /* Setters */
  external setOriginTime : t => originTime => t = "originTime" [@@bs.send];
  external setCurrentTime : t => float => t = "currentTime" [@@bs.send];
};


/**
 * The Animation interface of the Web Animations API represents a single animation player
 * and provides playback controls and a timeline for an animation node or source.
 * REVIEW in what situation would a bare call (`new Animation()`) be at all useful?
 * Should `make` be `makeWithInit` all the time, enforcing passing the animation effect/timeline.
 * FIXME makeWithInit needs to be defined.
 */
module Animation = {
  type t = animation;
  external make : unit => t = "Animation" [@@bs.new];
  /* Getters */
  external getCurrentTime : t => int = "currentTime" [@@bs.get];
  external getEffect : t => keyframeEffect = "effect" [@@bs.get];
  external getId : t => string = "id" [@@bs.get];
  external getPlaybackRate : t => int = "playbackRate" [@@bs.get];
  external getPlayState : t => animationPlayState = "playState" [@@bs.get];
  external getStartTime : t => float = "startTime" [@@bs.get];
  external getTimeline : t => documentTimeline = "timeline" [@@bs.get];
  /* Setters */
  external setCurrentTime : t => int => t = "currentTime" [@@bs.send];
  external setEffect : t => keyframeEffect => t = "effect" [@@bs.send];
  external setId : t => string => t = "id" [@@bs.send];
  external setPlaybackRate : t => int => t = "playbackRate" [@@bs.send];
  external setPlayState : t => animationPlayState => t =
    "playState" [@@bs.send];
  external setStartTime : t => float => t = "startTime" [@@bs.send];
  external setTimeline : t => documentTimeline => t = "timeline" [@@bs.send];
  /* Promise-returning getters */
  /* external finished : t => Js.Promise = "finished" [@@bs.get]; */
  /* external ready : t => Js.Promise = "ready" [@@bs.get]; */
  /* Event */
  /* external oncancel */
  /* external onfinish */
  external cancel : t => unit => unit = "cancel" [@@bs.send];
  external finish : t => unit => unit = "finish" [@@bs.send];
  external pause : t => unit => unit = "pause" [@@bs.send];
  external play : t => unit => unit = "play" [@@bs.send];
  external reverse : t => unit => unit = "reverse" [@@bs.send];
};

let _ = KeyframeEffect.make ();
