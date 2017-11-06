/* The Web Animations API allows for synchronizing and timing changes to the
 * presentation of a Web page, i.e. animation of DOM elements. It does so by
 * combining two models: the Timing Model and the Animation Model.
 *
 * The API is in flux, but there is a robust polyfill for the current spec.*/
type animation;

type animationTimeline;

type keyframeOptions;

type keyframeEffect;

type document = Dom.document;

type element = Dom.element;

type response;

/* Either an integer representing the animation's duration (in milliseconds),
 * or an Object containing the animation configuration properties. */
module KeyframeOptions = {
  type t = keyframeOptions;
  /* FIXME the keyframeEffect `make` should take either the opts object or a duration -
   * need to add poly types to it - eg | `Duration int | Opts` Js.t */
  /* external makeDuration : int -> keyframeOptions = "" [@@bs.val] */
  [@bs.obj]
  external makeObj :
    (
      ~delay: int=?,
      ~direction: [@bs.string]
                  [
                    | `normal
                    | `reverse
                    | `alternate
                    [@bs.as "alternate-revese"] | `alternate_reverse
                  ]
                    =?,
      ~duration: int=?,
      /* NOTE to avoid the dance needed to input cubic beziers as floats,
       * I have just defined all of the Penner equations for now. */
      ~easing: [@bs.string]
               [
                 | `linear
                 | `ease
                 [@bs.as "ease-in"] | `ease_in
                 [@bs.as "ease-out"] | `ease_out
                 [@bs.as "ease-in-out"] | `ease_in_out
                 [@bs.as "cubic-bezier(0.47, 0, 0.745, 0.715)"] | `ease_in_sine
                 [@bs.as "cubic-bezier(0.39, 0.575, 0.565, 1)"]
                 | `ease_out_sine
                 [@bs.as "cubic-bezier(0.445, 0.05, 0.55, 0.95)"]
                 | `ease_in_out_sine
                 [@bs.as "cubic-bezier(0.55, 0.085, 0.68, 0.53)"]
                 | `ease_in_quad
                 [@bs.as "cubic-bezier(0.25, 0.46, 0.45, 0.94)"]
                 | `ease_out_quad
                 [@bs.as "cubic-bezier(0.455, 0.03, 0.515, 0.955)"]
                 | `ease_in_out_quad
                 [@bs.as "cubic-bezier(0.55, 0.055, 0.675, 0.19)"]
                 | `ease_in_cubic
                 [@bs.as "cubic-bezier(0.215, 0.61, 0.355, 1)"]
                 | `ease_out_cubic
                 [@bs.as "cubic-bezier(0.645, 0.045, 0.355, 1)"]
                 | `ease_in_out_cubic
                 [@bs.as "cubic-bezier(0.895, 0.03, 0.685, 0.22)"]
                 | `ease_in_quart
                 [@bs.as "cubic-bezier(0.165, 0.84, 0.44, 1)"]
                 | `ease_out_quart
                 [@bs.as "cubic-bezier(0.77, 0, 0.175, 1)"]
                 | `ease_in_out_quart
                 [@bs.as "cubic-bezier(0.755, 0.05, 0.855, 0.06)"]
                 | `ease_in_quint
                 [@bs.as "cubic-bezier(0.23, 1, 0.32, 1)"] | `ease_out_quint
                 [@bs.as "cubic-bezier(0.86, 0, 0.07, 1)"] | `ease_in_out_quint
                 [@bs.as "cubic-bezier(0.95, 0.05, 0.795, 0.035)"]
                 | `ease_in_expo
                 [@bs.as "cubic-bezier(0.19, 1, 0.22, 1)"] | `ease_out_expo
                 [@bs.as "cubic-bezier(1, 0, 0, 1)"] | `ease_in_out_expo
                 [@bs.as "cubic-bezier(0.6, 0.04, 0.98, 0.335)"]
                 | `ease_in_circ
                 [@bs.as "cubic-bezier(0.075, 0.82, 0.165, 1)"]
                 | `ease_out_circ
                 [@bs.as "cubic-bezier(0.785, 0.135, 0.15, 0.86)"]
                 | `ease_in_out_circ
                 [@bs.as "cubic-bezier(0.6, -0.28, 0.735, 0.045)"]
                 | `ease_in_back
                 [@bs.as "cubic-bezier(0.175, 0.885, 0.32, 1.275)"]
                 | `ease_out_back
                 [@bs.as "cubic-bezier(0.68, -0.55, 0.265, 1.55)"]
                 | `ease_in_out_back
               ]
                 =?,
      ~endDelay: int=?,
      ~fill: [@bs.string] [ | `none | `forwards | `backwards | `both]=?,
      ~iterationStart: float=?,
      ~iterations: int=?,
      unit
    ) =>
    keyframeOptions =
    "";
};

/* The KeyframeEffect interface of the Web Animations API allows
 * creation of sets of animatable properties and values, called keyframes.
 * These can then be played using the Animation() constructor. */
module KeyframeEffect = {
  type t = keyframeEffect;
  [@bs.new]
  external make :
    (
      ~element: element=?,
      ~keyframeSet: array(Js.t('a))=?,
      ~keyframeOptions: keyframeOptions=?,
      unit
    ) =>
    keyframeEffect =
    "KeyframeEffect";
  [@bs.send]
  external setKeyframes :
    (t, ~keyframeSet: array(Js.t('a))=?) => keyframeEffect =
    "";
};

/* IMPORTANT do NOT expose this in the .rei file */
module AnimationTimeline = {
  type t = animationTimeline;
  [@bs.get] external getCurrentTime : t => int = "currentTime";
  [@bs.set] external setCurrentTime : (t, int) => t = "currentTime";
};

/* The DocumentTimeline interface of the the Web Animations API represents animation
 * timelines, including the default document timeline (accessed via Document.timeline). */
module DocumentTimeline = {
  include AnimationTimeline;
  type options = {. "originTime": int};
  [@bs.new] external make : (~options: options=?, unit) => t =
    "DocumentTimeline";
  [@bs.get] external getOriginTime : t => int = "originTime";
  [@bs.set] external setOriginTime : (t, int) => t = "originTime";
};

/* The Animation interface of the Web Animations API represents a single animation player
 * and provides playback controls and a timeline for an animation node or source. */
module Animation = {
  type t = animation;
  type playbackRate('a) =
    | Float: playbackRate(float)
    | Int: playbackRate(int);
  /* Core Animation constructor: */
  [@bs.new]
  external make :
    (~effect: keyframeEffect=?, ~timeline: animationTimeline=?, unit) =>
    animation =
    "Animation";
  /* Getters/setters: */
  [@bs.get] external getCurrentTime : t => int = "currentTime";
  [@bs.get] external getEffect : t => keyframeEffect = "effect";
  [@bs.get] external getId : t => string = "id";
  [@bs.get] external getPlaybackRate : t => int = "playbackRate";
  [@bs.get] external getPlayState : t => string = "playState";
  [@bs.get] external getStartTime : t => float = "startTime";
  [@bs.get] external getTimeline : t => animationTimeline = "timeline";
  [@bs.set] external setCurrentTime : (t, int) => t = "currentTime";
  [@bs.set] external setEffect : (t, keyframeEffect) => t = "effect";
  [@bs.set] external setId : (t, string) => t = "id";
  /* REVIEW Not 100% on this API, maybe only allow floats? */
  [@bs.set]
  external setPlaybackRate : (t, [@bs.ignore] playbackRate('a), 'a) => t =
    "playbackRate";
  [@bs.set]
  external setPlayState :
    (
      t,
      ~playState: [@bs.string] [ | `pending | `running | `paused | `finished]
    ) =>
    t =
    "playState";
  [@bs.set] external setStartTime : (t, float) => t = "startTime";
  [@bs.set] external setTimeline : (t, animationTimeline) => t = "timeline";
  /* Promise-returning methods: */
  [@bs.get] external ready : t => Js.Promise.t(response) = "ready";
  [@bs.get] external finished : t => Js.Promise.t(response) = "finished";
  /* Animation control methods: */
  [@bs.send] external cancel : (t, unit) => unit = "cancel";
  [@bs.send] external finish : (t, unit) => unit = "finish";
  [@bs.send] external pause : (t, unit) => unit = "pause";
  [@bs.send] external play : (t, unit) => unit = "play";
  [@bs.send] external reverse : (t, unit) => unit = "reverse";
};

/* The Element interface's animate() method is a shortcut method which creates
 * a new Animation, applies it to the element, then plays the animation.
 * It returns the created Animation object instance. */
[@bs.send.pipe : element]
external animate :
  (~effect: keyframeEffect=?, ~timeline: animationTimeline=?, unit) => element =
  "";

/* The getAnimations() method of the Document interface returns an array of
 * all Animation objects currently in effect whose target elements are descendants
 * of the document. This array includes CSS Animations, CSS Transitions, and
 * Web Animations. */
[@bs.send.pipe : document] external getAnimations : unit => document = "";
