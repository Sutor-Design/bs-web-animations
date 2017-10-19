open Bs_web_animations;

open Webapi.Dom;

/* To avoid options needing to be unwrapped, just
 * create an element to use as a test: */
let element = Document.createElement "div" document;

/* Smokes for Base interfaces: */
let _ = Animation.make ();

let _ = KeyframeEffect.make ();

let _ = DocumentTimeline.make ();

/* Document timeline takes an options object, though currently
 * that only takes an `originTime` property. */
let _ = DocumentTimeline.make options::{"originTime": 0} ();

let sharedTimeline = DocumentTimeline.make options::{"originTime": 0} ();

DocumentTimeline.getOriginTime sharedTimeline;

DocumentTimeline.getCurrentTime sharedTimeline;

DocumentTimeline.setOriginTime sharedTimeline 500;

DocumentTimeline.setCurrentTime sharedTimeline 500;

/* A KeyframeEffect takes an element, a keyframeSet and KeyFrameOptions */
let kfOpts =
  KeyframeOptions.makeObj
    delay::0
    direction::`normal
    duration::1000
    easing::`ease_out
    endDelay::0
    fill::`forwards
    ();

let _ =
  KeyframeEffect.make
    ::element
    keyframeOptions::(
      KeyframeOptions.makeObj
        delay::0
        direction::`normal
        duration::1000
        easing::`ease_out
        endDelay::0
        fill::`forwards
        ()
    )
    ();

let _ =
  KeyframeEffect.make
    ::element
    keyframeSet::[|{"foo": 0, "bar": 5}, {"foo": 1, "bar": 10}|]
    keyframeOptions::(
      KeyframeOptions.makeObj
        delay::0
        direction::`normal
        duration::1000
        easing::`ease_out
        endDelay::0
        fill::`forwards
        ()
    )
    ();

/* Animation get/set methods */
let keyframeEffect =
  KeyframeEffect.make
    ::element
    keyframeSet::[|{"foo": 0, "bar": 5}, {"foo": 1, "bar": 10}|]
    keyframeOptions::(
      KeyframeOptions.makeObj
        delay::0
        direction::`normal
        duration::1000
        easing::`ease_out
        endDelay::0
        fill::`forwards
        ()
    )
    ();

let myAnimation =
  Animation.make effect::keyframeEffect timeline::sharedTimeline ();

Animation.getCurrentTime myAnimation;

Animation.getEffect myAnimation;

Animation.getId myAnimation;

Animation.getPlaybackRate myAnimation;

Animation.getPlayState myAnimation;

Animation.getStartTime myAnimation;

Animation.getTimeline myAnimation;

Animation.setCurrentTime myAnimation 500;

Animation.setEffect myAnimation keyframeEffect;

Animation.setId myAnimation "foo";

Animation.setPlaybackRate myAnimation Int 5;

Animation.setPlaybackRate myAnimation Float 0.4;

Animation.setPlayState myAnimation `paused;

Animation.setStartTime myAnimation 10.;

Animation.setTimeline myAnimation sharedTimeline;

Animation.cancel myAnimation;

Animation.finish myAnimation ();

Animation.pause myAnimation ();

Animation.play myAnimation ();

Animation.reverse myAnimation ();

/* Promise-returning methods */
let readyPromise = Animation.ready myAnimation;

let finishedPromise = Animation.finished myAnimation;

/* `animate` shortcut method */
let _ = element |> animate ();

let _ = element |> animate effect::keyframeEffect timeline::sharedTimeline ();

let _ = document |> getAnimations ();
