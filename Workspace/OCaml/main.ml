open Printf
open Scanf
 
let ( ** ) a b = Int64.mul a b
let ( ++ ) a b = Int64.add a b
let ( -- ) a b = Int64.sub a b
let ( ^ ) a b = Int64.logxor a b
  
let read_int _ = bscanf Scanning.stdin " %d " (fun x -> x)
let read_long _ = bscanf Scanning.stdin " %Ld " (fun x -> x)  
let rec fold i j f init = if i>j then init else fold (i+1) j f (f i init)
let sum i j f = fold i j (fun i a -> (f i) ++ a) 0L
let xsum i j f = fold i j (fun i a -> (f i) ^ a) 0L
  
let () =
  let cases = read_int() in
  for case = 1 to cases do
    let n = read_int() in
    let ar = Array.init n read_long in
    let b = xsum 0 (n-1) (fun i -> ar.(i)) in
    let a = sum 0 (n-1) (fun i -> ar.(i)) in
    let x = b in
    let a' = x ++ a in
    let y = a' in
    printf "2\n";
    printf "%Ld %Ld\n" x y
  done