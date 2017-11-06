open Webapi.Dom;

[@bs.send.pipe : NodeList.t]
external forEach : (Node.t => unit, NodeList.t) => unit =
  "";

external unsafeEventToObj : Dom.event => Js.t({..}) = "%identity";

let demosContainer =
  switch (Document.querySelector(".demos", document)) {
  | Some(demos) => demos
  | None => raise(Failure("No demo container element found."))
  };

let demos = Element.querySelectorAll(".demo", demosContainer);

let isDemo = (el) => el |> Element.classList |> DomTokenList.contains("demo");

let addActive = (el) =>
  el |> Element.classList |> DomTokenList.add("demo-active");

let removeActive = () =>
  demos
  |> forEach(
       (element) => {
         let el =
           switch (Element.ofNode(element)) {
           | Some(e) => e
           | None => raise(Failure("Nope."))
           };
         el |> Element.classList |> DomTokenList.remove("demo-active")
       }
     );

let _ =
  Element.addEventListener(
    "click",
    (e) =>
      unsafeEventToObj(e)##target |> isDemo ?
        {
          Js.log("doing some class stuff");
          /* let _ = removeActive(); */
          /* let _ = unsafeEventToObj(e)##target |> addActive; */
          ()
        } :
        (),
    demosContainer
  );
