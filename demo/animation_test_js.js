

atestJSEl01.animate([
  { transform: 'none', easing: 'ease-out', },
  { offset: 0.1, transform: 'translateY(100px)', easing: 'ease-in-out',},
  { offset: 0.2, transform: 'translate(100px, 100px)', easing: 'ease-in-out',},
  { offset: 0.4, transform: 'translateX(100px)', easing: 'ease-out',},
  { transform: 'none',},
], {
  duration: 4000,
  iterations: Infinity,
});
