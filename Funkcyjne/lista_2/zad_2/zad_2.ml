let rec sublists l = match l with 
                     | [] -> [[]] 
                     | hd::tl -> let sub = sublists tl in 
                       (List.map (fun ll -> hd::ll) sub) @ sub ;;
