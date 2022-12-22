function bar (b: number): void{
    console.log(b);
}
function baz (c:number): number{
    return c * 10;
}
function qux (d:number): number{
    return d;
}
export {baz, bar};
export default qux;