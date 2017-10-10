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

type playState =
  | Pending
  | Running
  | Paused
  | Finished;

let encodePlayState state =>
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

/* IMPORTANT Only allows the second type of keyframe object - an array
 * of objects (keyfames).
 * NOTE just allowing anything in the object - too much hassle to
 * typecheck atm. */
/* module KeyframeObject = {
     type t = keyframeObject;
   }; */
module KeyframeOptions = {
  type t = keyframeOptions;
  external makeObj :
    delay::int? =>
    direction::
      [ | `normal | `reverse | `alternate | `alternate_reverse [@bs.as "alternate-reverse"]] [@bs.string]? =>
    duration::int? =>
    easing::
      [ | `linear | `ease | `ease_in | `ease_out | `ease_in_out] [@bs.string]? =>
    endDelay::int? =>
    fill::[ | `none | `forwards | `backwards | `both] [@bs.string]? =>
    iterationStart::float? =>
    iterations::int? =>
    unit =>
    keyframeOptions =
    "" [@@bs.obj];
  external makeDuration : int => keyframeOptions = "%identity";
};

/* The KeyframeEffect interface of the Web Animations API lets us
 * create sets of animatable properties and values, called keyframes.
 * These can then be played using the Animation() constructor.*/
module KeyframeEffect = {
  type t = keyframeEffect;
  external make :
    element::element? =>
    /* A keyframe object, or null.
     * NOTE that the objects must match in type - cannot just add properties to
     * one or the other on an ad-hoc basis else typechecking will fail. */
    keyframeSet::array (Js.t 'a)? =>
    /* Either an integer representing the animation's
     * duration (in milliseconds), or an Object. */
    keyframeOptions::keyframeOptions? =>
    unit =>
    keyframeEffect =
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
  external make : unit => t = "DocumentTimeline" [@@bs.new];
  external makeWithInit : documentTimelineInit => t =
    "DocumentTimeline" [@@bs.new];
  /* Getters */
  external getOriginTime : t => float = "originTime" [@@bs.get];
  external getCurrentTime : t => float = "currentTime" [@@bs.get];
  /* Setters */
  external setOriginTime : t => float => t = "originTime" [@@bs.send];
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
  external getPlayState : t => playState = "playState" [@@bs.get];
  external getStartTime : t => float = "startTime" [@@bs.get];
  external getTimeline : t => documentTimeline = "timeline" [@@bs.get];
  /* Setters */
  external setCurrentTime : t => int => t = "currentTime" [@@bs.send];
  external setEffect : t => keyframeEffect => t = "effect" [@@bs.send];
  external setId : t => string => t = "id" [@@bs.send];
  external setPlaybackRate : t => int => t = "playbackRate" [@@bs.send];
  external setPlayState : t => playState => t = "playState" [@@bs.send];
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
