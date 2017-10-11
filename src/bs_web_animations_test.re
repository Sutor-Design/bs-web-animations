open Bs_web_animations;

open Webapi.Dom;

/* Do some horrible stuff for now: */
let unwrapElUnsafely =
  fun
  | Some e => e
  | None => raise (Invalid_argument "Passed `None` to unwrapUnsafely");

/* FIXME make useful tests */
let testKeyframeOptions = KeyframeOptions.makeObj ();

let testKeyframeOptions2 = KeyframeOptions.makeObj delay::1000 ();

let testKeyframeOptions3 = KeyframeOptions.makeObj easing::`ease_out ();

let testKeyframeEffect1 =
  KeyframeEffect.make
    keyframeSet::[|
      {"opacity": 1, "color": "foo"},
      {"opacity": 0, "color": "bar"}
    |]
    keyframeOptions::(KeyframeOptions.makeObj delay::1000 ())
    ();

let testKeyframeEffect2 =
  KeyframeEffect.make
    keyframeSet::[|
      {"opacity": 1, "color": "foo"},
      {"opacity": 0, "color": "bar"}
    |]
    keyframeOptions::(KeyframeOptions.makeDuration 1000)
    ();

let testEmptyAnimation = Animation.make ();

let testEmptyTimeline = DocumentTimeline.make ();

/* FIXME this generates horrible, horrible code, but hey ho. API
 * not quite right for `animate` */
let testAnimate1 =
  unwrapElUnsafely (Document.querySelector ".foo" document) |>
  animate
    effect::(
      KeyframeEffect.make
        keyframeSet::[|
          {"opacity": 1, "color": "foo"},
          {"opacity": 0, "color": "bar"}
        |]
        keyframeOptions::(KeyframeOptions.makeDuration 1000)
        ()
    );
