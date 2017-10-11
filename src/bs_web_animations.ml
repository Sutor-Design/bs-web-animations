(* The Web Animations API allows for synchronizing and timing changes to the
 * presentation of a Web page, i.e. animation of DOM elements. It does so by
 * combining two models: the Timing Model and the Animation Model.
 *
 * The API is in flux, but there is a robust polyfill for the current spec.*)
type animation
type documentTimeline
type keyframeOptions
type keyframeEffect

type document = Dom.document
type element = Dom.element

(* Either an integer representing the animation's duration (in milliseconds),
 * or an Object containing the animation configuration properties. *)
module KeyframeOptions =
  struct
    type t = keyframeOptions
    external makeDuration : int -> keyframeOptions = "%identity"
    external makeObj :
      ?delay:int ->
      ?direction:([
        | `normal
        | `reverse
        | `alternate
        | `alternate_reverse [@bs.as "alternate-revese"] ] [@bs.string ]) ->
      ?duration:int ->
      ?easing:([
        | `linear
        | `ease
        | `ease_in [@bs.as "ease-in"]
        | `ease_out [@bs.as "ease-out"]
        | `ease_in_out [@bs.as "ease-in-out" ] ] [@bs.string ]) ->
      ?endDelay:int ->
      ?fill:(([ `none  | `forwards  | `backwards  | `both ]) [@bs.string ]) ->
      ?iterationStart:float ->
      ?iterations:int ->
      unit -> keyframeOptions = "" [@@bs.obj]
  end

(* The KeyframeEffect interface of the Web Animations API allows
 * creation of sets of animatable properties and values, called keyframes.
 * These can then be played using the Animation() constructor. *)
module KeyframeEffect =
  struct
    type t = keyframeEffect
    external make :
      ?element:element ->
      ?keyframeSet:'a Js.t array ->
      ?keyframeOptions:keyframeOptions ->
      unit -> keyframeEffect = "KeyframeEffect" [@@bs.new ]
    external setKeyframes : t -> ?keyframeSet:'a Js.t array -> keyframeEffect = "" [@@bs.send]
  end

(* The DocumentTimeline interface of the the Web Animations API represents animation
 * timelines, including the default document timeline (accessed via Document.timeline). *)
module DocumentTimeline =
  struct
    type t = documentTimeline
    type options = < originTime: int > Js.t
    external make : ?options:options -> unit -> t = "DocumentTimeline" [@@bs.new ]
    external getOriginTime : t -> float = "originTime" [@@bs.get]
    external getCurrentTime : t -> float = "currentTime" [@@bs.get]
    external setOriginTime : t -> float -> t = "originTime" [@@bs.send]
    external setCurrentTime : t -> float -> t = "currentTime" [@@bs.send]
  end

(* The Animation interface of the Web Animations API represents a single animation player
 * and provides playback controls and a timeline for an animation node or source. *)
module Animation =
  struct
    type t = animation
    external make : ?effect:keyframeEffect -> ?timeline:documentTimeline -> unit -> animation = "Animation" [@@bs.new ]
    external getCurrentTime : t -> int = "currentTime" [@@bs.get]
    external getEffect : t -> keyframeEffect = "effect" [@@bs.get]
    external getId : t -> string = "id" [@@bs.get]
    external getPlaybackRate : t -> int = "playbackRate" [@@bs.get]
    external getPlayState : t -> string = "playState" [@@bs.get]
    external getStartTime : t -> float = "startTime" [@@bs.get]
    external getTimeline : t -> documentTimeline = "timeline" [@@bs.get]
    external setCurrentTime : t -> int -> t = "currentTime" [@@bs.send]
    external setEffect : t -> keyframeEffect -> t = "effect" [@@bs.send]
    external setId : t -> string -> t = "id" [@@bs.send]
    external setPlaybackRate : t -> int -> t = "playbackRate" [@@bs.send]
    external setPlayState : t -> playState:([
      | `pending
      | `running
      | `paused
      | `finished
    ] [@bs.string]) -> t = "playState" [@@bs.send]

    external setStartTime : t -> float -> t = "startTime" [@@bs.send]
    external setTimeline : t -> documentTimeline -> t = "timeline" [@@bs.send]
    external cancel : t -> unit -> unit = "cancel" [@@bs.send]
    external finish : t -> unit -> unit = "finish" [@@bs.send]
    external pause : t -> unit -> unit = "pause" [@@bs.send]
    external play : t -> unit -> unit = "play" [@@bs.send]
    external reverse : t -> unit -> unit = "reverse" [@@bs.send]
  end


(* The Element interface's animate() method is a shortcut method which creates
 * a new Animation, applies it to the element, then plays the animation.
 * It returns the created Animation object instance. *)
external animate : ?effect:keyframeEffect -> ?timeline:documentTimeline -> element = "" [@@bs.send.pipe : element]
