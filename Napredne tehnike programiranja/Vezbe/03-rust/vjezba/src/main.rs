fn main() {
    let s = String::from("hello");  // s comes into scope

    takes_ownership(&s);             
    println!("{}", s);

    let x = 5;                      

    makes_copy(x);   
    
    println!("{}", x)
  } 

  fn takes_ownership(some_string: &String) {
      println!("{}", some_string);
  } 
  fn makes_copy(some_integer: i32) {
      println!("{}", some_integer);
  }