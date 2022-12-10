console.log([]) //obiekt
console.log(![]) //false
console.log([] + []) // 
console.log((![] + [])) //false
console.log(+[]) // 0
console.log([+[]]) //[0]
console.log((![]+[])[+[]]) //false[0] = f

console.log([+!+[]]) // !0 = 1, + 1, [1]
console.log('f' + (![]+[])[+!+[]]) //false[1] = a, fa

console.log([[]]) // [Array(0)]
console.log([][[]]) // undefinded
console.log([![]]+[][[]]) //[false] + undefinded = falseundefinded
console.log(+[+[]]) //0
console.log([+!+[]+[+[]]]) //['1' + '0'] = ['10']
console.log(([![]]+[][[]])[+!+[]+[+[]]])//falseundefinded['10'] = i

console.log([!+[]]) //true
console.log([!+[]+!+[]]) //true + 1 = 2
console.log((![]+[])[!+[]+!+[]]) //false[2] = l

console.log( (![]+[])[+[]]+(![]+[])[+!+[]]+([![]]+[][[]])[+!+[]+[+[]]]+(![]+[])[!+[]+!+[]] );