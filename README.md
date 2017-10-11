# bs-web-animations

Bucklescript/ReasonML bindings to the [Web Animations API](https://developer.mozilla.org/en-US/docs/Web/API/Web_Animations_API).

## Todo

- [x] Basic bindings for `Animation`
- [ ] Promise-returning methods for `Animation`
- [x] Basic bindings for `AnimationTimeline` (just using `DocumentTimeline` for now)
- [x] Basic bindings for `AnimationEffect` (just use `KeyframeEffect` for now)
- [ ] Basic bindings for `AnimationEvent`
- [ ] Basic bindings for `AnimationPlaybackEvent`
- [ ] Basic bindings for animation-specific extensions to the `Document` interface
- [ ] Basic bindings for the addition to the `Element` interface (i.e `Element.animate()`)
- [ ] Full smokes for above to check output code is clean
- [ ] Demo for above which can be used as a visual test - should show raw JS and BS-generated JS side-by-side - they should not be different, functionally in any way.
- [ ] Documentation for above (usage)
