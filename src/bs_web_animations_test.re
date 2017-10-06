open Bs_web_animations;

/* Smokes */
let _ = Animation.make ();

let _ = KeyframeEffect.make ();

let _ = {
  let keyframeOptions =
     KeyframeOptions.make
       delay::1
       direction::Normal
       duration::500
       easing::Linear
       endDelay::0
       fill::None
       iterationStart::0.0
       iterations::1
       ();
  KeyframeEffect.makeWithInit (
    KeyframeEffectInit.make
      element::"ImAnElement" keyframeOptions::keyframeOptions ()
  );
};
let _ = DocumentTimeline.make ();
