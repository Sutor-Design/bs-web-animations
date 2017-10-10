open Bs_web_animations;

/* Smokes */
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

let testKeyframes1 = ();

let testAnimation = Animation.make ();

let testTimeline = DocumentTimeline.make ();
