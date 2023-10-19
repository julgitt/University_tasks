let rec suffixes l = match l with
                      | [] -> [[]]
                      | hd::tl -> l :: suffixes tl;;

let rec prefixes xs = match l with 
                      | [] -> [[]]
                      | l -> l :: prefixes rev(List.tl (rev l));;

