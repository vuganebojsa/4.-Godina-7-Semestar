fn main() {
   let x = 5;

   let p = &x;    // TODO

   println!("the memory address of x is {:p}", p); // Jedan mogući ispis: 0xcd8a16fa8c
}