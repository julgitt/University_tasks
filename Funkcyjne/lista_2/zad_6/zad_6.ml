let rec permutation_insert l =
    let rec insert elem list = 
         match list with
         | []     -> [[elem]]
         | hd::tl -> (elem::list)::(List.map (fun perm -> hd::perm)(insert elem tl)) 
    in
    match l with
    | []     -> [[]]
    | hd::tl -> List.flatten (List.map (insert hd)(permutation_insert tl));;   


let rec delete x l =
    match l with
    | []     -> []
    | hd::tl -> if hd = x
              then tl
              else hd :: (delete x tl);;
           
let rec select_perm l =
    let select list =
      List.map (fun selected -> 
                     (List.map 
                     (fun perm -> selected :: perm)  
                     (select_perm (delete selected list))))
      list
  in 
  match l with
    |[]     -> [[]]
    |hd::tl -> List.flatten (select l);;
